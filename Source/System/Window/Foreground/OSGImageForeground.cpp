/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2005 by the OpenSG Forum                   *
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

#include "OSGGL.h"

#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGAction.h"
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGImage.h"

#include "OSGImageForeground.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGImageForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGImageForeground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void ImageForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

ImageForeground::ImageForeground(void) :
    Inherited()
{
}

ImageForeground::ImageForeground(const ImageForeground &source) :
    Inherited(source)
{
}

ImageForeground::~ImageForeground(void)
{
}

void ImageForeground::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*------------------------------- dump ----------------------------------*/

void ImageForeground::dump(     UInt32    OSG_CHECK_ARG(uiIndent), 
                           const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump ImageForeground NI" << std::endl;
}


void ImageForeground::draw(DrawEnv *, Viewport *vp)
{
    if(getActive() == false)
        return;

    UInt16 i;
    
    for(i = 0; i < getPositions().size(); i++)
    {
        if(getImages(i) != NullFC)
            break;
    }
    
    if(i == getPositions().size())   // all images == NULL?
        return; 
        
    glPushAttrib(GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | 
                 GL_LIGHTING_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_DEPTH_TEST);

    glDisable(GL_COLOR_MATERIAL);

    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    float vpWidth = 1.0, vpHeight = 1.0;
    if(vp != NULL)
    {
        // for absolute pixel position
        vpWidth  = 1.0/vp->getPixelWidth();
        vpHeight = 1.0/vp->getPixelHeight();
    }

    for(i = 0; i < getPositions().size(); i++)
    {
        ImagePtr img = getImages(i);

        if(img == NullFC)
            continue;

        Pnt2f p = getPositions(i);

        if( p[0] >= 1.0 || p[1] >= 1.0 )
            glRasterPos2f(p[0]*vpWidth, p[1]*vpHeight); // absolute position
        else
            glRasterPos2f(p[0], p[1]); // relative position

        glDrawPixels(img->getWidth(), img->getHeight(),
                     img->getPixelFormat(), GL_UNSIGNED_BYTE,
                     img->getData());
    }
    glDisable(GL_BLEND);
        

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}
