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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGL.h"

#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGAction.h"
#include "OSGDrawActionBase.h"
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGGradientBackground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GradientBackground
    \ingroup GrpSystemWindowBackgrounds

A background showing a vertical color gradient, see
\ref PageSystemWindowBackgroundGradient. 

The colors (_mfColor) and positions (_mfPosition) correspond to each other, so
both have to have the same number of elements. The addColor() method should
be used for defining the gradient, as it ensures that constarint.

*/

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

void GradientBackground::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------- your_category---------------------------------*/

#ifdef OSG_OLD_RENDER_ACTION
void GradientBackground::clear(DrawActionBase *, Viewport *)
{
    if(_mfPosition.size() < 2)
    {
        if(_mfPosition.size() == 1)
        {
            Color3f col = _mfColor[0];
            Real32 r, g, b;
            col.getValuesRGB(r, g, b);
            glClearColor(r, g, b, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }
    else
    {
        GLboolean light = glIsEnabled(GL_LIGHTING);
        if(light)  
            glDisable(GL_LIGHTING);

        GLint fill[2];
        glGetIntegerv(GL_POLYGON_MODE, fill);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
        glDisable(GL_DEPTH_TEST);

        GLboolean colmat = glIsEnabled(GL_COLOR_MATERIAL);
        glDisable(GL_COLOR_MATERIAL);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 1, 0, 1, 0, 1);

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

        if(depth == GL_TRUE)    
            glEnable(GL_DEPTH_TEST);
        if(light == GL_TRUE)    
            glEnable(GL_LIGHTING);
        if(colmat == GL_TRUE)   
            glEnable(GL_COLOR_MATERIAL);
        glPolygonMode(GL_FRONT, fill[0]);
        glPolygonMode(GL_BACK , fill[1]);

        glClear(GL_DEPTH_BUFFER_BIT);
    }
}
#endif

void GradientBackground::clear(DrawEnv *, Viewport *)
{
    if(_mfPosition.size() < 2)
    {
        if(_mfPosition.size() == 1)
        {
            Color3f col = _mfColor[0];
            Real32 r, g, b;
            col.getValuesRGB(r, g, b);
            glClearColor(r, g, b, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }
    else
    {
        GLboolean light = glIsEnabled(GL_LIGHTING);

        if(light)  
            glDisable(GL_LIGHTING);

        GLint fill[2];
        glGetIntegerv(GL_POLYGON_MODE, fill);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
        glDisable(GL_DEPTH_TEST);

        GLboolean colmat = glIsEnabled(GL_COLOR_MATERIAL);
        glDisable(GL_COLOR_MATERIAL);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 1, 0, 1, 0, 1);

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

        if(depth == GL_TRUE)    
            glEnable(GL_DEPTH_TEST);

        if(light == GL_TRUE)    
            glEnable(GL_LIGHTING);

        if(colmat == GL_TRUE)   
            glEnable(GL_COLOR_MATERIAL);

        glPolygonMode(GL_FRONT, fill[0]);
        glPolygonMode(GL_BACK , fill[1]);

        glClear(GL_DEPTH_BUFFER_BIT);
    }
}

/*------------------------------- dump ----------------------------------*/

void GradientBackground::dump(     UInt32    OSG_CHECK_ARG(uiIndent), 
                              const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump GradientBackground NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGGRADIENTBACKGROUND_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRADIENTBACKGROUND_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRADIENTBACKGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


