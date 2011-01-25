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

#include "OSGConfig.h"

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

DrawableStatsAttachmentTransitPtr DrawableStatsAttachment::calcStatic(
    Drawable *pDrawable)
{
    DrawableStatsAttachmentUnrecPtr st = DrawableStatsAttachment::create();

    if(pDrawable != NULL)
        pDrawable->fill(st); 

    return DrawableStatsAttachmentTransitPtr(st);
}

/*! Add a new GeoStatsAttachment to the given \a obj.
*/

DrawableStatsAttachmentTransitPtr DrawableStatsAttachment::addTo(
    AttachmentContainer *obj)
{
    DrawableStatsAttachmentTransitPtr st = DrawableStatsAttachment::create();

    st->attachTo(obj);

    return st;
}

/*! Attach the current GeoStatsAttachment to the given \a obj.
 */

void DrawableStatsAttachment::attachTo(AttachmentContainer *obj)
{
    if(getMFParents()->size())
    {
        FNOTICE(("GeoStatsAttachment::attachTo: "
                 "already attached, detaching!\n"));

        while(getMFParents()->size())
        {
            AttachmentContainer *p =
                dynamic_cast<AttachmentContainer *>(this->getParents(0));

            p->subChangedFunctor(&DrawableStatsAttachment::invalidateFunctor);
            p->subAttachment    (this                                       );
        }
    }

    obj->addAttachment(this);

    reset();

    obj->addChangedFunctor(&DrawableStatsAttachment::invalidateFunctor,
                           "DrawableStats invalidator");
}

void DrawableStatsAttachment::validate(void)
{
    commitChanges();

    // Still valid? Do nothing.
    if(getValid())
        return;

    AttachmentContainer *cont =
        dynamic_cast<AttachmentContainer *>(this->getParents(0));

    // Called on a non-AttachmentContainer?
    if(cont == NULL)
        return;

    reset();

    // Drawable?
    Drawable *g = dynamic_cast<Drawable *>(cont);

    if(g != NULL)
    {
        //calc(g);
        g->fill(this);
    }

    // Node?
    Node *n = dynamic_cast<Node *>(cont);
    if(n != NULL)
    {
        // Validate the core
        Drawable *g = dynamic_cast<Drawable *>(n->getCore());
        if(g != NULL)
        {
            DrawableStatsAttachmentUnrecPtr s = get(g);

            if(s == NULL)
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
            Node *c = n->getChild(i);

            DrawableStatsAttachmentUnrecPtr s = get(c);

            if(s == NULL)
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

void DrawableStatsAttachment::operator +=(DrawableStatsAttachment *arg)
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

void DrawableStatsAttachment::operator -=(DrawableStatsAttachment *arg)
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
    FieldContainer *obj,
    BitVector       mask)
{
    invalidate(obj);
}

void DrawableStatsAttachment::invalidate(FieldContainer *obj)
{
    if(obj == NULL)
        return;

    AttachmentContainer *cont = dynamic_cast<AttachmentContainer *>(obj);

    // Called on a non-AttachmentContainer?
    if(cont == NULL)
        return;

    // Find the attachment
    DrawableStatsAttachment *st = get(cont);

    if(st == NULL) // Found the end of the chain
        return;

    // Invalidate it
    st->reset();

    // Traverse upwards
    if(st->getMFParents()->size())
    {
        // Can't have more than 1
        FieldContainer *p = 
            dynamic_cast<FieldContainer *>(st->getParents(0)); 

        // Is this attached to a NodeCore?
        NodeCore *c = dynamic_cast<NodeCore *>(p);
        if(c != NULL)
        {
            MFParentFieldContainerPtr::const_iterator pnI;

            for(  pnI  = c->getMFParents()->begin();
                  pnI != c->getMFParents()->end  ();
                ++pnI)
            {
                Node *node = dynamic_cast<Node *>(*pnI);

                invalidate(node);
            }
        }

        // Is this attached to a Node?
        Node *n = dynamic_cast<Node *>(p);

        if(n != NULL)
        {
            Node *par = n->getParent();

            invalidate(par);
        }
    }
}

OSG_END_NAMESPACE
