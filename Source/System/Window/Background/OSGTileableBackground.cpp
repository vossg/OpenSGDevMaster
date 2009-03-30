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

#include "OSGTileableBackground.h"
#include <OSGDrawEnv.h>
#include <OSGRenderActionBase.h>
#include <OSGTileCameraDecorator.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTileableBackgroundBase.cpp file.
// To modify it, please change the .fcd file (OSGTileableBackground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TileableBackground::initMethod(InitPhase ePhase)
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

TileableBackground::TileableBackground(void) :
    Inherited()
{
}

TileableBackground::TileableBackground(const TileableBackground &source) :
    Inherited(source)
{
}

TileableBackground::~TileableBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TileableBackground::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TileableBackground::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TileableBackground NI" << std::endl;
}

/*! Sets up an ortho projection for rendering 2D backgrounds. It handles tiling
    when a TileCameraDecorator is in use. When done you need to call
    endOrthoRender to clean up changes to the OpenGL matrix stacks.

    \param pEnv DrawEnv being used for rendering
    \param normX Wether x coordinates are going to be normalized.
    \param normY Wether y coordinates are going to be normalized.
    \param[out] fullWidth width of the viewport
    \param[out] fullHeight height of the viewport

    \note When the TileCameraDecorator is in use, the width and height of the
          viewport (fullWidth, fullHeight) are defined by the TileCameraDecorator.
 */
void TileableBackground::beginOrthoRender(
    DrawEnv *pEnv,
    bool     normX,
    bool     normY,
    UInt32  &fullWidth,
    UInt32  &fullHeight)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    UInt32               width   = pEnv->getPixelWidth ();
    UInt32               height  = pEnv->getPixelHeight();

    Camera              *cam     = pEnv->getAction()->getCamera();
    TileCameraDecorator *camDeco = dynamic_cast<TileCameraDecorator *>(cam);

    while(camDeco != NULL)
    {
        width  = camDeco->getFullWidth () ? camDeco->getFullWidth () : width;
        height = camDeco->getFullHeight() ? camDeco->getFullHeight() : height;

        cam     = camDeco->getDecoratee();
        camDeco = dynamic_cast<TileCameraDecorator *>(cam);
    }

    cam     = pEnv->getAction()->getCamera();
    camDeco = dynamic_cast<TileCameraDecorator *>(cam);

    if(camDeco != NULL && !getTile())
    {
        Matrix sm;
        cam->getDecoration(sm, width, height);

        glLoadMatrixf(sm.getValues());
    }

    fullWidth  = width;
    fullHeight = height;

    Real32 projWidth  = normX ? 1.0f : Real32(width );
    Real32 projHeight = normY ? 1.0f : Real32(height);

    glOrtho(0, projWidth, 0, projHeight, -1.0f, 1.0f);
}

/*! Clean up changes to the OpenGL matrix stacks done by beginOrthoRender
 */
void TileableBackground::endOrthoRender(DrawEnv *pEnv)
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

OSG_END_NAMESPACE
