/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
 * License along with this library; ifnot, write to the Free Software       *
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

#include "OSGGL.h"

#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGAction.h"
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGGradientBackground.h"
#include "OSGTileCameraDecorator.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGradientBackgroundBase.cpp file.
// To modify it, please change the .fcd file (OSGGradientBackground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector  GradientBackground::LineFieldMask = 
                     (GradientBackground::PositionFieldMask | 
                      GradientBackground::ColorFieldMask   );

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GradientBackground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

GradientBackground::GradientBackground(void) :
    Inherited()
{
}

GradientBackground::GradientBackground(const GradientBackground &source) :
    Inherited(source)
{
}

GradientBackground::~GradientBackground(void)
{
}

void GradientBackground::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/

void GradientBackground::clear(DrawEnv *pEnv)
{
    Int32 bit = getClearStencilBit();

    if(_mfPosition.size() < 2)
    {
        Real32 r = 0.f, g = 0.f, b = 0.f;

        if(_mfPosition.size() == 1)
        {
            Color3f col = _mfColor[0];
            col.getValuesRGB(r, g, b);
        }

        glClearColor(r, g, b, 1);
        
        if (bit >= 0)
        {
            glClearStencil(bit);
            glClear((GL_COLOR_BUFFER_BIT   | 
                     GL_DEPTH_BUFFER_BIT   | 
                     GL_STENCIL_BUFFER_BIT ));
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }
    else
    {
        glPushAttrib(GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | 
                     GL_LIGHTING_BIT);
        
        glDisable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_COLOR_MATERIAL);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

#if 0
        UInt32 width  = pEnv->getPixelWidth(),
               height = pEnv->getPixelHeight();

        Camera              *cP  = getCPtr(pPort->getCamera());
        TileCameraDecorator *cdP = dynamic_cast<TileCameraDecorator*>(cP);

        while(cdP != NULL)
        {
            width  = cdP->getFullWidth()  ? cdP->getFullWidth()  : width;
            height = cdP->getFullHeight() ? cdP->getFullHeight() : height;

            cP  = getCPtr(cdP->getDecoratee());
            cdP = dynamic_cast<TileCameraDecorator*>(cP);
        }

        cP  = getCPtr(pEnv->getCamera());
        cdP = dynamic_cast<TileCameraDecorator*>(cP);

        if(cdP != NULL)
        {
            Real32 left   = cdP->getLeft(),
                   right  = cdP->getRight(),
                   top    = cdP->getTop(),
                   bottom = cdP->getBottom();

            glOrtho(left , right, bottom, top, 0, 1);
        }
        else
        {
            glOrtho(0, 1, 0, 1, 0, 1);
        }
#endif

        glOrtho(pEnv->getPixelLeft  (), 
                pEnv->getPixelRight (),
                pEnv->getPixelBottom(),
                pEnv->getPixelTop   (), 
                0.f, 
                1.f);

        

        Real32 r1, g1, b1;
        UInt32 size = _mfPosition.size();

        glBegin(GL_QUAD_STRIP);
        
        Real32 pos = _mfPosition[0];

        if(pos > 0) 
        {
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);
        }

        for(UInt32 i = 0; i < size; i++)
        {
            pos = _mfPosition[i];

            Color3f col1 = _mfColor[i];
            col1.getValuesRGB(r1, g1, b1);

            glColor3f(r1, g1, b1);
            glVertex3f(0, pos, 0);
            glVertex3f(1, pos, 0);
        }

        if(pos < 1) 
        {
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(0, 1, 0);
            glVertex3f(1, 1, 0);
        }
        
        glEnd();

        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glPopAttrib();
        
        if(bit >= 0)
        {
            glClearStencil(bit);

            glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
        else
        {
            glClear(GL_DEPTH_BUFFER_BIT);
        }
     }
}

/*------------------------------- dump ----------------------------------*/

void GradientBackground::dump(     UInt32    OSG_CHECK_ARG(uiIndent), 
                              const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump GradientBackground NI" << std::endl;
}

