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
    Int32      stencilBit = getClearStencilBit();   // 0x0
    GLbitfield clearMask  = 0;

    if(getClearColor() == true)
    {
        if(_mfPosition.size() < 2)
        {
            // too few positions for a real gradient - just clear the buffer

            clearMask |= GL_COLOR_BUFFER_BIT;

            if(_mfPosition.size() == 1)
            {
                const Color3f &col = _mfColor[0];

                glClearColor(col[0], col[1], col[2], 1.0);
            }
        }
        else
        {
            // draw gradient - don't need to clear the color buffer

            glPushAttrib(GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT |
                         GL_LIGHTING_BIT                       );

            glDisable(GL_LIGHTING);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_COLOR_MATERIAL);

            UInt32 fullWidth;
            UInt32 fullHeight;

            // setup ortho projection
            beginOrthoRender(pEnv, getNormPosition(), getNormPosition(),
                                   fullWidth,         fullHeight        );

            glBegin(GL_QUAD_STRIP);

            UInt32 size  = _mfPosition.size();
            Real32 pos   = _mfPosition[0];
            UInt32 style = getStyle();

            switch(style)
            {
            case VERTICAL:
            {
                if(pos > 0)
                {
                    glColor3f(0.0, 0.0, 0.0);
                    glVertex2f(0.0f,      0.0f);
                    glVertex2f(fullWidth, 0.0f);
                }

                for(UInt32 i = 0; i < size; ++i)
                {
                                   pos = _mfPosition[i];
                    const Color3f &col = _mfColor   [i];

                    glColor3f(col[0], col[1], col[2]);
                    glVertex2f(0.0f,      pos);
                    glVertex2f(fullWidth, pos);
                }

                if(pos < 1)
                {
                    glColor3f(0.0, 0.0, 0.0);
                    glVertex2f(0.0f,      fullHeight);
                    glVertex2f(fullWidth, fullHeight);
                }

                break;
            }

            case HORIZONTAL:
            {
                if(pos > 0)
                {
                    glColor3f(0.0, 0.0, 0.0);
                    glVertex2f(0.0f, 0.0f      );
                    glVertex2f(0.0f, fullHeight);
                }

                for(UInt32 i = 0; i < size; i++)
                {
                                   pos = _mfPosition[i];
                    const Color3f &col = _mfColor   [i];

                    glColor3f(col[0], col[1], col[2]);
                    glVertex2f(pos, 0.0f      );
                    glVertex2f(pos, fullHeight);
                }

                if(pos < 1)
                {
                    glColor3f(0.0, 0.0, 0.0);
                    glVertex2f(fullWidth, 0.0f      );
                    glVertex2f(fullWidth, fullHeight);
                }

                break;
            }

            default:
            {
                FWARNING(("GradientBackground: "
                          "SFStyle has invalid value [%u].\n", style));
                break;
            }
            };

            glEnd();

            endOrthoRender(pEnv);

            glPopAttrib();
        }
    }

    if(getClearDepth() == true)
    {
        clearMask |= GL_DEPTH_BUFFER_BIT;

        glClearDepth(getDepth());
    }

    if(stencilBit >= 0)
    {
        clearMask |= GL_STENCIL_BUFFER_BIT;

        glClearStencil(stencilBit);
    }

    if(clearMask != 0)
    {
        glClear(clearMask);
    }
}

/*------------------------------- dump ----------------------------------*/

void GradientBackground::dump(     UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump GradientBackground NI" << std::endl;
}

