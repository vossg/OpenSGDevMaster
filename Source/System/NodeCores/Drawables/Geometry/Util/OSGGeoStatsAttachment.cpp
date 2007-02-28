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

#include "OSGContainerPtrFuncs.h"
#include "OSGGeoStatsAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoStatsAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoStatsAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoStatsAttachment::initMethod(InitPhase ePhase)
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

GeoStatsAttachment::GeoStatsAttachment(void) :
    Inherited()
{
}

GeoStatsAttachment::GeoStatsAttachment(const GeoStatsAttachment &source) :
    Inherited(source)
{
}

GeoStatsAttachment::~GeoStatsAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoStatsAttachment::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GeoStatsAttachment::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeoStatsAttachment NI" << std::endl;
}


void GeoStatsAttachment::reset(void)
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

void GeoStatsAttachment::calc(GeometryPtrArg geo)
{
    if(geo == NullFC)
    {
        FINFO(("No geo in calcGeoStats\n"));
        return;
    }

    // Att Bytes

    UInt32 storedAttBytes = 0;
    
    UInt32 attBytesPerVertex = 0;
    
    for(UInt16 i = 0; i < Geometry::MaxAttribs; ++i)
    {
        if(geo->getProperty(i) == NullFC)
            continue;
            
        attBytesPerVertex += geo->getProperty(i)->getFormatSize() * 
                             geo->getProperty(i)->getDimension();

        storedAttBytes += geo->getProperty(i)->getFormatSize() * 
                          geo->getProperty(i)->getDimension() *
                          geo->getProperty(i)->size();
    }


    GeoIntegralPropertyPtr geoTypePtr;
    GeoIntegralPropertyPtr lensPtr;

    UInt32 lN, tN, len, type;   
    
    lensPtr = geo->getLengths();

    lN = (lensPtr == NullFC) ? 0 : lensPtr->getSize();
    
    geoTypePtr = geo->getTypes();

    tN = (geoTypePtr == NullFC) ? 0 : geoTypePtr->getSize();

    if((tN == 0) || (lN != 0 && tN != lN) || (lN == 0 && tN != 1))
    {
        return;
    }

    UInt32 triangle = 0, line = 0, point = 0, vertices = 0, 
           procAttBytes = 0;
    
    for(UInt32 i = 0; i < geoTypePtr->size(); ++i)
    {
        geoTypePtr->getValue(type, i);

        if(lN != 0)
        {
            lensPtr->getValue(len, i);
        }
        else
        {
            GeoVectorPropertyPtr pos = geo->getPositions();
            
            if(pos == NullFC)
            {
                FINFO(("GeoStatsAttachment::calc: no Points!\n"));
                return;
            }
            
            len = pos->size();
        }
        
        vertices += len;
        procAttBytes += len * attBytesPerVertex;
        
        switch(type)
        {
            case GL_POINTS:
                point += len;
                break;
            case GL_LINES:
                line += len / 2;
                break;
            case GL_LINE_LOOP:
                line += len;
                break;
            case GL_LINE_STRIP:
                line += len - 1;
                break;
            case GL_TRIANGLES:
                triangle += len / 3;
                break;
            case GL_TRIANGLE_STRIP:
                triangle += len - 2;
                break;
            case GL_TRIANGLE_FAN:
                triangle += len - 2;
                break;
            case GL_QUADS:
                triangle += len / 2;
                break;
            case GL_QUAD_STRIP:
                triangle += len - 2;
                break;
            case GL_POLYGON:
                triangle += len - 2;
                break;
            default:
                FWARNING(("GeoStatsAttachment::calc: Invalid geoType: %d\n", 
                          type));
                break;
        }
        
    }

    setVertices(vertices);
    setPoints(point);
    setLines(line);
    setTriangles(triangle);
    setStoredAttributeBytes(storedAttBytes);
    setProcessedAttributeBytes(procAttBytes);
    setValid(true);
}

/*! Create a GeoStatsAttachment for the given Geometry
*/
GeoStatsAttachmentPtr GeoStatsAttachment::calcStatic(GeometryPtrArg geo)
{
    GeoStatsAttachmentPtr st = GeoStatsAttachment::create();
    
    st->calc(geo);
    
    return st;
}

#if 0
/*! Access the GeoStatsAttachemnt in \a arg, if it has one. Return NullFC
otherwise.
*/
GeoStatsAttachmentPtr GeoStatsAttachment::get(AttachmentContainer *arg)
{
    return cast_dynamic<GeoStatsAttachmentPtr>(
            arg->findAttachment(GeoStatsAttachment::getClassType()));

}
#endif

/*------------------------------------------------------------------------*/
/*                              Updates                                   */

/*! Add a new GeoStatsAttachment to the given \a obj.
*/
GeoStatsAttachmentPtr GeoStatsAttachment::addTo(AttachmentContainerPtr obj)
{
    GeoStatsAttachmentPtr st = GeoStatsAttachment::create();
    
    st->attachTo(obj);
    
    return st;
}

/*! Attach the current GeoStatsAttachment to the given \a obj.
*/
void GeoStatsAttachment::attachTo(AttachmentContainerPtr obj)
{
    GeoStatsAttachmentPtr st = cast_dynamic<GeoStatsAttachmentPtr>(getPtr());
    
    if(getParents().size())
    {
        FNOTICE(("GeoStatsAttachment::attachTo: already "
                    "attached, detaching!\n"));
        
        while(getParents().size())
        {
            AttachmentContainerPtr p = 
                cast_dynamic<AttachmentContainerPtr>(getParents()[0]);
                
            p->subAttachment(st);
        }
    }
    
    obj->addAttachment(st);
    
    reset();
    
    obj->addChangedFunctor(GeoStatsAttachment::invalidateFunctor, 
                           "GeoStats invalidator");
}

void GeoStatsAttachment::validate(void)
{
    commitChanges();
    
    // Still valid? Do nothing.
    if(getValid())
        return; 
        
    AttachmentContainerPtr cont = 
        cast_dynamic<AttachmentContainerPtr>(getParents()[0]);
    
    // Called on a non-AttachmentContainer?
    if(cont == NullFC)
        return;
    
    reset();
    
    // Geometry?
    GeometryPtr g = cast_dynamic<GeometryPtr>(cont);
    if(g != NullFC)
    {
        calc(g);
    }
    
    // Node?
    NodePtr n = cast_dynamic<NodePtr>(cont);
    if(n != NullFC)
    {
        // Validate the core
        GeometryPtr g = cast_dynamic<GeometryPtr>(n->getCore());
        if(g != NullFC)
        {
            GeoStatsAttachmentPtr s = get(g);
            
            if(s == NullFC)
            {
                s = GeoStatsAttachment::addTo(g);
            }
            
            s->validate();
            
            *this += s;
            setValid(false); // Not done yet.
        }
        
        // Validate all the children
        for(UInt32 i = 0; i < n->getNChildren(); ++i)
        {
            NodePtr c = n->getChild(i);
            
            GeoStatsAttachmentPtr s = get(c);
            
            if(s == NullFC)
            {
                s = GeoStatsAttachment::addTo(c);
            }
            
            s->validate();
            
            *this += s;
            setValid(false); // Not done yet.
        }
    }
    setValid(true); // Done!
}

void GeoStatsAttachment::invalidateFunctor(FieldContainerPtr obj,
    BitVector mask)
{
    invalidate(obj);
}

void GeoStatsAttachment::invalidate(FieldContainerPtrArg obj)
{
    if(obj == NullFC)
        return;

    AttachmentContainerPtr cont = cast_dynamic<AttachmentContainerPtr>(obj);
    
    // Called on a non-AttachmentContainer?
    if(cont == NullFC)
        return;
    
    // Find the attachment
    GeoStatsAttachmentPtr st = get(cont);
    
    if(st == NullFC) // Found the end of the chain
        return;

    // Invalidate it        
    st->reset();
    
    // Traverse upwards
    if(st->getParents().size())
    {
        FieldContainerPtr p = st->getParents()[0]; // Can't have more than 1
        
        // Is this attached to a NodeCore?
        NodeCorePtr c = cast_dynamic<NodeCorePtr>(p);        
        if(c != NullFC)
        {
            MFParentFieldContainerPtr::const_iterator pnI;

            for(  pnI  = c->getMFParents()->begin();
                  pnI != c->getMFParents()->end  ();
                ++pnI)
            {
                NodePtr node = cast_dynamic<NodePtr>(*pnI);
                invalidate(node);
            }
        }
        
        // Is this attached to a Node?
        NodePtr n = cast_dynamic<NodePtr>(p);        
        if(n != NullFC)
        {
            NodePtr par = n->getParent();
            invalidate(par);
        }
    }
}

void GeoStatsAttachment::operator +=(GeoStatsAttachmentPtr arg)
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

void GeoStatsAttachment::operator -=(GeoStatsAttachmentPtr arg)
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


/*------------------------------------------------------------------------*/
/*                             Operators                                  */

OSG_BEGIN_NAMESPACE

#if 0
void operator +=(GeoStatsAttachmentPtr op, GeoStatsAttachmentPtr arg)
{
    (*op) += arg;
}

void operator -=(GeoStatsAttachmentPtr op, GeoStatsAttachmentPtr arg)
{
    (*op) -= arg;
}
#endif

OSG_END_NAMESPACE
