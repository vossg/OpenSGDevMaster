/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <OSGViewport.h>
#include <OSGMaterial.h>

#include "OSGPolygonForeground.h"

#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PolygonForeground
    \ingroup GrpSystemWindowForegrounds
    
A foreground that renders a single polygon used the specified material, 
see \ref PageSystemPolygonForeground for a
description. 

The polygon material is defined by _sfMaterial, the positions by _mfPositions,
the texture coordinates by _mfTexCoords. The interpretation of the positions is
controlled by _sfNormalizedX and _sfNormalizedY.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PolygonForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PolygonForeground::PolygonForeground(void) :
    Inherited()
{
}

PolygonForeground::PolygonForeground(const PolygonForeground &source) :
    Inherited(source)
{
}

PolygonForeground::~PolygonForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PolygonForeground::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PolygonForeground::dump(      UInt32    , 
                             const BitVector ) const
{
    SLOG << "Dump PolygonForeground NI" << std::endl;
}

Real32 PolygonForeground::mapCoordinate(Real32 val, Real32 max, bool norm)
{
    if(val >= 0)
    {
        if(norm)
            val *= max;
    }
    else
    {
        val += 1;
        
        if(norm)
            val *= max;
        
        val = max + val;
    }
   
    return val;
}
    
void PolygonForeground::draw(DrawEnv *pEnv, Viewport *pPort)
{
    if(getPositions().size() == 0) // nothing to render
        return;

    if(pPort->getPixelWidth()  == 0 ||
       pPort->getPixelHeight() == 0   ) // nothing to render to
        return;
        
    if(getPositions().size() != getTexCoords().size())
    {
        FWARNING(("PolygonForeground::draw: positions and texcoords have "
                  "different sizes (%d vs. %d)!\n", 
                  getPositions().size(), getTexCoords().size()));
        return;
    }
       
    glPushAttrib(GL_ALL_ATTRIB_BITS);
 
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    glOrtho(0, pPort->getPixelWidth(), 0, pPort->getPixelHeight(), 0, 1);
    
    getMaterial()->getState()->activate(pEnv);
   
    UInt16 i;
    
    const Vec3f *tc  = &(getTexCoords()[0]);
    const Pnt2f *pos = &(getPositions()[0]);
    
    glBegin(GL_POLYGON);
    
    for(i = 0; i < getPositions().size(); i++)
    {
        glTexCoord3fv( tc[i].getValues() );
        glVertex2f( mapCoordinate(pos[i][0], Real32(pPort->getPixelWidth()),
                                             getNormalizedX()),
                    mapCoordinate(pos[i][1], Real32(pPort->getPixelHeight()),
                                             getNormalizedY()) );
    }

    glEnd();
    
    getMaterial()->getState()->deactivate(pEnv);
    
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGPOLYGONFOREGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPOLYGONFOREGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPOLYGONFOREGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

