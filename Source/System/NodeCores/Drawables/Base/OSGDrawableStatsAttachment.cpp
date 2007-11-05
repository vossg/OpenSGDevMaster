/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGDrawableStatsAttachment.h"
#include "OSGDrawable.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDrawableStatsAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGDrawableStatsAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DrawableStatsAttachment::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DrawableStatsAttachment::DrawableStatsAttachment(void) :
    Inherited()
{
}

DrawableStatsAttachment::DrawableStatsAttachment(const DrawableStatsAttachment &source) :
    Inherited(source)
{
}

DrawableStatsAttachment::~DrawableStatsAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DrawableStatsAttachment::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DrawableStatsAttachment::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DrawableStatsAttachment NI" << std::endl;
}

void DrawableStatsAttachment::reset(void)
{
    // Don't change it unless it's valid.
    // Needed to protect intermediate results
    if(!getValid())
        return;

    setVertices               (0);
    setPoints                 (0);
    setLines                  (0);
    setTriangles              (0);
    setProcessedAttributeBytes(0);
    setStoredAttributeBytes   (0);

    setValid(false);
}

/*! Create a GeoStatsAttachment for the given Geometry
*/

DrawableStatsAttachmentPtr DrawableStatsAttachment::calcStatic(
    DrawablePtrArg pDrawable)
{
    DrawableStatsAttachmentPtr st = DrawableStatsAttachment::create();

    if(pDrawable != NullFC)
        pDrawable->fill(st); 

    return st;
}

/*! Add a new GeoStatsAttachment to the given \a obj.
*/

DrawableStatsAttachmentPtr DrawableStatsAttachment::addTo(
    AttachmentContainerPtr obj)
{
    DrawableStatsAttachmentPtr st = DrawableStatsAttachment::create();

    st->attachTo(obj);

    return st;
}

/*! Attach the current GeoStatsAttachment to the given \a obj.
 */

void DrawableStatsAttachment::attachTo(AttachmentContainerPtr obj)
{
    if(getParents().size())
    {
        FNOTICE(("GeoStatsAttachment::attachTo: "
                 "already attached, detaching!\n"));

        while(getParents().size())
        {
            AttachmentContainerPtr p =
                dynamic_cast<AttachmentContainerPtr>(this->getParent(0));

            p->subAttachment(this);
        }
    }

    obj->addAttachment(this);

    reset();

    obj->addChangedFunctor(DrawableStatsAttachment::invalidateFunctor,
                           "DrawableStats invalidator");
}

void DrawableStatsAttachment::validate(void)
{
    commitChanges();

    // Still valid? Do nothing.
    if(getValid())
        return;

    AttachmentContainerPtr cont =
        dynamic_cast<AttachmentContainerPtr>(this->getParent(0));

    // Called on a non-AttachmentContainer?
    if(cont == NullFC)
        return;

    reset();

    // Drawable?
    DrawablePtr g = dynamic_cast<DrawablePtr>(cont);

    if(g != NullFC)
    {
        //calc(g);
        g->fill(this);
    }

    // Node?
    NodePtr n = dynamic_cast<NodePtr>(cont);
    if(n != NullFC)
    {
        // Validate the core
        DrawablePtr g = dynamic_cast<DrawablePtr>(n->getCore());
        if(g != NullFC)
        {
            DrawableStatsAttachmentPtr s = get(g);

            if(s == NullFC)
            {
                s = DrawableStatsAttachment::addTo(g);
            }

            s->validate();

            *this += s;
            setValid(false); // Not done yet.
        }

        // Validate all the children
        for(UInt32 i = 0; i < n->getNChildren(); ++i)
        {
            NodePtr c = n->getChild(i);

            DrawableStatsAttachmentPtr s = get(c);

            if(s == NullFC)
            {
                s = DrawableStatsAttachment::addTo(c);
            }

            s->validate();

            *this += s;
            setValid(false); // Not done yet.
        }
    }
    setValid(true); // Done!
}

void DrawableStatsAttachment::operator +=(DrawableStatsAttachmentPtr arg)
{
    setVertices               (getVertices()  + arg->getVertices());
    setPoints                 (getPoints()    + arg->getPoints());
    setLines                  (getLines()     + arg->getLines());
    setTriangles              (getTriangles() + arg->getTriangles());
    setProcessedAttributeBytes(getProcessedAttributeBytes() +
                                   arg->getProcessedAttributeBytes());
    setStoredAttributeBytes   (getStoredAttributeBytes() +
                                   arg->getStoredAttributeBytes());
    setValid(true);
}

void DrawableStatsAttachment::operator -=(DrawableStatsAttachmentPtr arg)
{
    setVertices               (getVertices()  - arg->getVertices());
    setPoints                 (getPoints()    - arg->getPoints());
    setLines                  (getLines()     - arg->getLines());
    setTriangles              (getTriangles() - arg->getTriangles());
    setProcessedAttributeBytes(getProcessedAttributeBytes() -
                                   arg->getProcessedAttributeBytes());
    setStoredAttributeBytes   (getStoredAttributeBytes() -
                                   arg->getStoredAttributeBytes());
    setValid(true);
}



void DrawableStatsAttachment::invalidateFunctor(
    FieldContainerPtr obj,
    BitVector         mask)
{
    invalidate(obj);
}

void DrawableStatsAttachment::invalidate(FieldContainerPtrArg obj)
{
    if(obj == NullFC)
        return;

    AttachmentContainerPtr cont = dynamic_cast<AttachmentContainerPtr>(obj);

    // Called on a non-AttachmentContainer?
    if(cont == NullFC)
        return;

    // Find the attachment
    DrawableStatsAttachmentPtr st = get(cont);

    if(st == NullFC) // Found the end of the chain
        return;

    // Invalidate it
    st->reset();

    // Traverse upwards
    if(st->getParents().size())
    {
        // Can't have more than 1
        FieldContainerPtr p = 
            dynamic_cast<FieldContainerPtr>(st->getParent(0)); 

        // Is this attached to a NodeCore?
        NodeCorePtr c = dynamic_cast<NodeCorePtr>(p);
        if(c != NullFC)
        {
            MFParentFieldContainerPtr::const_iterator pnI;

            for(  pnI  = c->getMFParents()->begin();
                  pnI != c->getMFParents()->end  ();
                ++pnI)
            {
                NodePtr node = dynamic_cast<NodePtr>((*pnI).getCPtr());
                invalidate(node);
            }
        }

        // Is this attached to a Node?
        NodePtr n = dynamic_cast<NodePtr>(p);
        if(n != NullFC)
        {
            NodePtr par = n->getParent();
            invalidate(par);
        }
    }
}

OSG_END_NAMESPACE
