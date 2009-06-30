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

#include <OSGViewport.h>
#include <OSGMaterial.h>

#include "OSGPolygonForeground.h"

#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGTileCameraDecorator.h"
#include "OSGDrawEnv.h"
#include "OSGRenderActionBase.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGPolygonForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGPolygonForeground.fcd) and
// regenerate the base file.

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

void PolygonForeground::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
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
    if(getActive() == false)
        return;

    if(getMFPositions()->size() == 0) // nothing to render
        return;

    if(pPort->getPixelWidth()  == 0 ||
       pPort->getPixelHeight() == 0   ) // nothing to render to
        return;
        
    bool bUseTC = true;

    if(getMFPositions()->size() != getMFTexCoords()->size())
    {
#if 0
        FWARNING(("PolygonForeground::draw: positions and texcoords have "
                  "different sizes (%d vs. %d)!\n", 
                  getMFPositions()->size(), getMFTexCoords()->size()));
        return;
#endif

        bUseTC = false;
    }
       
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    Real32 aspectX = 1.0f, aspectY = 1.0f;
    
    if(getAspectHeight() && getAspectWidth())
    {
        aspectX = 
            (Real32(pPort->getPixelHeight()) / getAspectHeight()) /
            (Real32(pPort->getPixelWidth())  / getAspectWidth());
    }
 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
	Real32 sFac = getScale() > 0 ? getScale() : 1.0f;
	
	UInt32 width  = pPort->getPixelWidth(),
		   height = pPort->getPixelHeight();
    
    if(pEnv->getTileFullSize()[0] != 0 && getTile() == false)
    {
        width  = pEnv->getTileFullSize()[0];
        height = pEnv->getTileFullSize()[1];

        Real32 t = 0;
        Real32 left   = pEnv->getTileRegion()[0]; //cdP->getLeft(),
        Real32 right  = pEnv->getTileRegion()[1]; //cdP->getRight(),
        Real32 top    = pEnv->getTileRegion()[3]; //cdP->getTop(),
        Real32 bottom = pEnv->getTileRegion()[2]; //cdP->getBottom();
        
        if (getAspectHeight() && getAspectWidth() &&
            height != 0 && width != 0)
        {
            aspectX = 
                (Real32(height/getAspectHeight())) /
                (Real32(width / getAspectWidth()));

            t  = Real32(width) * (1 - aspectX) * 0.5f;
            t *= Real32(pPort->getPixelWidth()) / width;
        }
		
        Matrix sm = pEnv->calcTileDecorationMatrix();
        
        glLoadMatrixf(sm.getValues());
        glOrtho(0, pPort->getPixelWidth(), 0, pPort->getPixelHeight(), 0, 1);

        glTranslatef(t, 0, 0);
        glScalef(aspectX, aspectY, 1);

        float t1 = (1 - sFac) * 0.5f * Real32(pPort->getPixelWidth());
        float t2 = (1 - sFac) * 0.5f * Real32(pPort->getPixelHeight());
        glTranslatef(t1, t2, 0);
        glScalef(sFac,sFac,1);
    }
    else
    {
        glScalef(sFac,sFac,1);
        
        glScalef(aspectX, aspectY, 1);
        
        glOrtho(0, pPort->getPixelWidth(), 0, pPort->getPixelHeight(), 0, 1);
    }

    getMaterial()->getState()->activate(pEnv);
   
    const Vec3f *tc  = NULL;

    if(bUseTC == true)
    {
        tc = &((*getMFTexCoords())[0]);
    }

    const Pnt2f *pos = &((*getMFPositions())[0]);
    
    glBegin(GL_POLYGON);
    
    for(UInt16 i = 0; i < getMFPositions()->size(); i++)
    {
        if(bUseTC == true)
        {
            glTexCoord3fv( tc[i].getValues() );
        }

        glVertex2f( mapCoordinate(pos[i][0], Real32(pPort->getPixelWidth()),
                                             getNormalizedX()),
                    mapCoordinate(pos[i][1], Real32(pPort->getPixelHeight()),
                                             getNormalizedY()) );
    }

    glEnd();
    
    getMaterial()->getState()->deactivate(pEnv);

    glScalef(1, 1, 1);
    
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}
