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

#include "OSGConfig.h"
#include "OSGMaterial.h"
#include "OSGViewport.h"

#include "OSGPolygonBackground.h"
#include "OSGTileCameraDecorator.h"
#include "OSGDrawEnv.h"
#include "OSGRenderActionBase.h"

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

void PolygonBackground::clear(DrawEnv *pEnv)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(pEnv->getPixelWidth()  == 0 ||
       pEnv->getPixelHeight() == 0 )
    {
        FWARNING(("Port has zero size: nothing to render to!\n"));
        return;
    }

    if(getMFPositions()->size() == 0 ||
       getMFPositions()->size() != getMFTexCoords()->size())
    {
        FWARNING(("PolygonBackground::clear: positions and texcoords have "
                  "different/ invalid sizes (%d vs. %d)!\n",
                  getMFPositions()->size(), getMFTexCoords()->size()));
        return;
    }

    Int32 bit = getClearStencilBit();      // 0x0

    if(bit >= 0)
    {
        glClearStencil(bit);

        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT |
                GL_STENCIL_BUFFER_BIT);
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    if(getCleanup())
        glDepthMask(GL_FALSE);

    Real32 aspectX = 1.0f, aspectY = 1.0f;

    if(getAspectHeight() != 0 && getAspectWidth() != 0)
    {
        aspectX = (Real32(pEnv->getPixelHeight()) / getAspectHeight()) /
                  (Real32(pEnv->getPixelWidth ()) / getAspectWidth ());
    }

    Real32 sFac        = getScale() > 0 ? getScale() : 1.0f;
    UInt32 fullWidth;
    UInt32 fullHeight;

    if(!getTile())
    {
        beginOrthoRender(pEnv, getNormalizedX(), getNormalizedY(),
                               fullWidth,        fullHeight       );

        Real32 t = 0;

        if(getAspectHeight() != 0 && getAspectWidth() != 0 &&
           fullHeight        != 0 && fullHeight       != 0   )
        {
            aspectX = (Real32(fullHeight) / getAspectHeight()) /
                      (Real32(fullWidth ) / getAspectWidth ());

            t  = Real32(fullWidth) * (1.0f - aspectX) * 0.5f;
            t *= Real32(pEnv->getPixelWidth()) / fullWidth;
        }

        glTranslatef(t,       0.0f,    0.0f);
        glScalef    (aspectX, aspectY, 1.0f);

        Real32 tW = (1.0f - sFac) * 0.5f * Real32(pEnv->getPixelWidth ());
        Real32 tH = (1.0f - sFac) * 0.5f * Real32(pEnv->getPixelHeight());

        glTranslatef(tW,   tH,   0.0f);
        glScalef    (sFac, sFac, 1.0f);
    }
    else
    {
        glScalef(sFac,    sFac,    1.0f);
        glScalef(aspectX, aspectY, 1.0f);

        beginOrthoRender(pEnv, getNormalizedX(), getNormalizedY(),
                               fullWidth,        fullHeight       );
    }


    getMaterial()->getState()->activate(pEnv);

    const Vec3f *tc  = &getMFTexCoords()->front();
    const Pnt2f *pos = &getMFPositions()->front();

    glBegin(GL_POLYGON);

    for (UInt16 i=0; i < getMFPositions()->size(); i++)
    {
        glTexCoord3fv( tc[i].getValues());
        glVertex2fv  (pos[i].getValues());
    }

    glEnd();

    getMaterial()->getState()->deactivate(pEnv);

    glScalef(1, 1, 1);

    if(getCleanup())
    {
        if(bit >= 0)
        {
            glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
        else
        {
            glClear(GL_DEPTH_BUFFER_BIT);
        }
    }

    endOrthoRender(pEnv);

    glPopAttrib();
#endif
}

void PolygonBackground::changed(ConstFieldMaskArg whichField,
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PolygonBackground::dump(      UInt32    ,
                             const BitVector ) const
{
    SLOG << "Dump PolygonBackground NI" << std::endl;
}

