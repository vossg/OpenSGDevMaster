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

#include "OSGGLEXT.h"
#include "OSGGLFuncProtos.h"

#include "OSGWindow.h"
#include "OSGDrawEnv.h"

#include "OSGPointChunk.h"
#include "OSGConceptPropertyChecks.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGPointChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGPointChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass PointChunk::_class("Point");

UInt32 PointChunk::_extPointParameters     = Window::invalidExtensionID;
UInt32 PointChunk::_extPointSpriteARB      = Window::invalidExtensionID;
UInt32 PointChunk::_extPointSpriteNV       = Window::invalidExtensionID;
UInt32 PointChunk::_funcIdPointParameterf  = Window::invalidFunctionID;
UInt32 PointChunk::_funcIdPointParameterfv = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PointChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extPointParameters     =
            Window::registerExtension("GL_ARB_point_parameters");
        _extPointSpriteARB      =
            Window::registerExtension("GL_ARB_point_sprite");
        _extPointSpriteNV       =
            Window::registerExtension("GL_NV_point_sprite");
        _funcIdPointParameterf  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glPointParameterfARB",
                _extPointParameters);
        _funcIdPointParameterfv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glPointParameterfvARB",
                _extPointParameters);
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PointChunk::PointChunk(void) :
    Inherited()
{
}

PointChunk::PointChunk(const PointChunk &source) :
    Inherited(source)
{
}

PointChunk::~PointChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *PointChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void PointChunk::changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PointChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PointChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void PointChunk::activate(DrawEnv *pEnv, UInt32)
{
#ifndef OSG_OGL_ES2
    if(getSize() != 1.f)
        glPointSize(getSize());
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(getSmooth())
        glEnable(GL_POINT_SMOOTH);
#endif

    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);

#if GL_ARB_point_parameters
    if(getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointParameters, 0x0104))
        {
            OSGGETGLFUNCBYID_GL3( glPointParameterf,
                                  osgGlPointParameterf,
                                 _funcIdPointParameterf,
                                  pWin);
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            OSGGETGLFUNCBYID_GL3( glPointParameterfv,
                                  osgGlPointParameterfv,
                                 _funcIdPointParameterfv,
                                  pWin);

            osgGlPointParameterf(GL_POINT_SIZE_MIN_ARB, getMinSize());
            osgGlPointParameterf(GL_POINT_SIZE_MAX_ARB, getMaxSize());
#endif
            osgGlPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 
                                 getFadeThreshold());
            
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            GLfloat att[3] = { getConstantAttenuation (),
                               getLinearAttenuation   (),
                               getQuadraticAttenuation() };
            
            osgGlPointParameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
#endif
        }
        
    }
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
#if GL_ARB_point_sprite
    if(getSprite())
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointSpriteARB, 0x0200))
        {
#if GL_NV_point_sprite
            if(pEnv->getWindow()->hasExtension(_extPointSpriteNV))
            {
                OSGGETGLFUNCBYID_GL3( glPointParameterf,
                                      osgGlPointParameterf,
                                     _funcIdPointParameterf,
                                      pWin);

                osgGlPointParameterf(GL_POINT_SPRITE_R_MODE_NV, 
                                     Real32(getRMode()));
            }
#endif
            
            glEnable(GL_POINT_SPRITE_ARB);
        }
        
    }
#endif
#endif
#if ! defined(GL_ARB_point_parameters) && ! defined(GL_ARB_point_sprite)
    pEnv;
#endif
}

void PointChunk::changeFrom(DrawEnv    *pEnv, 
                            StateChunk *old_chunk, 
                            UInt32               )
{
    PointChunk *old = dynamic_cast<PointChunk *>(old_chunk);

#ifndef OSG_OGL_ES2
    if(getSize() != old->getSize())
        glPointSize(getSize());
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(getSmooth() && !old->getSmooth())
    {
        glEnable(GL_POINT_SMOOTH);
    }
    else if(!getSmooth() && old->getSmooth())
    {
        glDisable(GL_POINT_SMOOTH);
    }
#endif

    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);

#if GL_ARB_point_parameters
    if(getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointParameters, 0x0104))
        {
            OSGGETGLFUNCBYID_GL3( glPointParameterf,
                                  osgGlPointParameterf,
                                 _funcIdPointParameterf,
                                  pWin);
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            OSGGETGLFUNCBYID_GL3( glPointParameterfv,
                                  osgGlPointParameterfv,
                                 _funcIdPointParameterfv,
                                  pWin);

            osgGlPointParameterf(GL_POINT_SIZE_MIN_ARB, getMinSize());
            osgGlPointParameterf(GL_POINT_SIZE_MAX_ARB, getMaxSize());
#endif
            osgGlPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 
                                 getFadeThreshold());
            
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            GLfloat att[3] = { getConstantAttenuation (),
                               getLinearAttenuation   (),
                               getQuadraticAttenuation() };
            
            osgGlPointParameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
#endif
        }
        
    }
    else if(old->getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointParameters, 0x0104))
        {
            OSGGETGLFUNCBYID_GL3( glPointParameterf,
                                  osgGlPointParameterf,
                                 _funcIdPointParameterf,
                                  pWin);
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            OSGGETGLFUNCBYID_GL3( glPointParameterfv,
                                  osgGlPointParameterfv,
                                 _funcIdPointParameterfv,
                                  pWin);

            osgGlPointParameterf(GL_POINT_SIZE_MIN_ARB, 0);
            osgGlPointParameterf(GL_POINT_SIZE_MAX_ARB, 1e10);
#endif
            osgGlPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 1);
            
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            GLfloat att[3] = { 1, 0, 0 };
            
            osgGlPointParameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
#endif
        }
    }
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
#if GL_ARB_point_sprite
    if(getSprite() && !old->getSprite())
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointSpriteARB, 0x0200))
        {
#if GL_NV_point_sprite
            if(pEnv->getWindow()->hasExtension(_extPointSpriteNV))
            {
                OSGGETGLFUNCBYID_GL3( glPointParameterf,
                                      osgGlPointParameterf,
                                     _funcIdPointParameterf,
                                      pWin);

                osgGlPointParameterf(GL_POINT_SPRITE_R_MODE_NV, 
                                     Real32(getRMode()));
            }
#endif
            
            glEnable(GL_POINT_SPRITE_ARB);
        }
        
    }
    else if(!getSprite() && old->getSprite())
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointSpriteARB, 0x0200))
        {
           glDisable(GL_POINT_SPRITE_ARB);
        }
        
    }
#endif
#endif

#if ! defined(GL_ARB_point_parameters) && ! defined(GL_ARB_point_sprite)
    pEnv;
#endif
}

void PointChunk::deactivate(DrawEnv *pEnv, UInt32)
{
#ifndef OSG_OGL_ES2
    if(getSize() != 1.f)
        glPointSize(1.f);
#endif

    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(getSmooth())
        glDisable(GL_POINT_SMOOTH);
#endif

#if GL_ARB_point_parameters
    if(getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointParameters, 0x0104))
        {
            OSGGETGLFUNCBYID_GL3( glPointParameterf,
                                  osgGlPointParameterf,
                                 _funcIdPointParameterf,
                                  pWin);
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            OSGGETGLFUNCBYID_GL3( glPointParameterfv,
                                  osgGlPointParameterfv,
                                 _funcIdPointParameterfv,
                                  pWin);
 
            osgGlPointParameterf(GL_POINT_SIZE_MIN_ARB, 0);
            osgGlPointParameterf(GL_POINT_SIZE_MAX_ARB, 1e10);
#endif
            osgGlPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 1);
            
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
            GLfloat att[3] = { 1, 0, 0 };
            
            osgGlPointParameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
#endif
        }
        
    }
#endif

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
#if GL_ARB_point_sprite
    if(getSprite())
    {
        if(pEnv->getWindow()->hasExtOrVersion(_extPointSpriteARB, 0x0200))
        {
            glDisable(GL_POINT_SPRITE_ARB);
        }
        
    }
#endif
#endif

#if ! defined(GL_ARB_point_parameters) && ! defined(GL_ARB_point_sprite)
    pEnv;
#endif
}

/*-------------------------- Comparison -----------------------------------*/

bool PointChunk::isTransparent(void) const
{
    return getMinSize() >= 0.f;
}

Real32 PointChunk::switchCost(StateChunk *)
{
    return 0;
}

bool PointChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool PointChunk::operator == (const StateChunk &other) const
{
    PointChunk const *tother = dynamic_cast<PointChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getSize()                    != tother->getSize()                    ||
       getSmooth()                  != tother->getSmooth()                  ||
       getMinSize()                 != tother->getMinSize()                 ||
       getMaxSize()                 != tother->getMaxSize()                 ||
       getConstantAttenuation()     != tother->getConstantAttenuation()     ||
       getLinearAttenuation()       != tother->getLinearAttenuation()       ||
       getQuadraticAttenuation()    != tother->getQuadraticAttenuation()    ||
       getFadeThreshold()           != tother->getFadeThreshold()           ||
       getSprite()                  != tother->getSprite()                  ||
       getRMode()                   != tother->getRMode()                    )
    {
        return false;
    }

    return true;
}

bool PointChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


