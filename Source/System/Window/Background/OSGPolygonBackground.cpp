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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>
#include <OSGMaterial.h>
#include <OSGViewport.h>

#include "OSGPolygonBackground.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGPolygonBackgroundBase.cpp file.
// To modify it, please change the .fcd file (OSGPolygonBackground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PolygonBackground::initMethod(InitPhase ePhase)
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

PolygonBackground::PolygonBackground(void) :
    Inherited()
{
}

PolygonBackground::PolygonBackground(const PolygonBackground &source) :
    Inherited(source)
{
}

PolygonBackground::~PolygonBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

Real32 PolygonBackground::mapCoordinate(Real32 val, Real32 max, bool norm)
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

void PolygonBackground::clear(DrawEnv *pEnv, Viewport *pPort)
{
    if(pPort->getPixelWidth()  == 0 ||
       pPort->getPixelHeight() == 0 ) 
    {   
        FWARNING(("Port has zero size: nothing to render to!\n"));
        return;
    }
        
    if(getPositions().size() == 0 ||
       getPositions().size() != getTexCoords().size())
    {
        FWARNING(("PolygonBackground::clear: positions and texcoords have "
                  "different/ invalid sizes (%d vs. %d)!\n", 
                  getPositions().size(), getTexCoords().size()));
        return;
    }
       
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    GLint depthFunc;
    glGetIntegerv(GL_DEPTH_FUNC, &depthFunc);
    glDepthFunc(GL_ALWAYS);

    glDepthMask(GL_FALSE);

    Real32 aspectX = 1.0f, aspectY = 1.0f;
    
    if (getAspectHeight() && getAspectWidth())
    {
        aspectX = ((Real32)pPort->getPixelHeight()/getAspectHeight()) /
                  ((Real32)pPort->getPixelWidth() / getAspectWidth());
    }
 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    glScalef(aspectX, aspectY, 1);
    glOrtho(0, pPort->getPixelWidth(), 0, pPort->getPixelHeight(), 0, 1);

    getMaterial()->getState()->activate(pEnv);
    
    const Vec3f *tc  = &getTexCoords()[0];
    const Pnt2f *pos = &getPositions()[0];
    
    glBegin(GL_POLYGON);
    
    for (UInt16 i=0; i<getPositions().size(); i++)
    {
        glTexCoord3fv( tc[i].getValues() );
        glVertex2f( mapCoordinate(pos[i][0], Real32(pPort->getPixelWidth()),
                                             getNormalizedX()),
                    mapCoordinate(pos[i][1], Real32(pPort->getPixelHeight()),
                                             getNormalizedY()) );
    }

    glEnd();
    
    getMaterial()->getState()->deactivate(pEnv);

    glScalef(1, 1, 1);

    glClear(GL_DEPTH_BUFFER_BIT);
    
    glDepthMask(GL_TRUE);

    if (depth)    
        glEnable(GL_DEPTH_TEST);
    glDepthFunc(depthFunc);
    
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}

void PolygonBackground::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PolygonBackground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PolygonBackground NI" << std::endl;
}

