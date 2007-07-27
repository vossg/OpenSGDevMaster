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

#include <OSGGLEXT.h>

#include "OSGWindow.h"
#include "OSGDrawEnv.h"

#include "OSGPointChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGPointChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGPointChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass PointChunk::_class("Point");

UInt32 PointChunk::_arbPointParameters;
UInt32 PointChunk::_nvPointSprite;
UInt32 PointChunk::_funcPointParameterf;
UInt32 PointChunk::_funcPointParameterfv;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PointChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

#ifndef GL_VERSION_1_4
# define GL_FUNC_POINT_PARAMETERF  OSG_DLSYM_UNDERSCORE"glPointParameterfEXT"
# define GL_FUNC_POINT_PARAMETERFV OSG_DLSYM_UNDERSCORE"glPointParameterfvEXT"
#else
# define GL_FUNC_POINT_PARAMETERF  OSG_DLSYM_UNDERSCORE"glPointParameterf"
# define GL_FUNC_POINT_PARAMETERFV OSG_DLSYM_UNDERSCORE"glPointParameterfv"
#endif

/*----------------------- constructors & destructors ----------------------*/

PointChunk::PointChunk(void) :
    Inherited()
{
    _arbPointParameters   =
        Window::registerExtension("GL_EXT_point_parameters");
    _nvPointSprite        =
        Window::registerExtension("GL_NV_point_sprite");
    _funcPointParameterf  =
        Window::registerFunction (GL_FUNC_POINT_PARAMETERF,  
                                  _arbPointParameters, 
                                  0x0104);
    _funcPointParameterfv =
        Window::registerFunction (GL_FUNC_POINT_PARAMETERFV, 
                                  _arbPointParameters, 
                                  0x0104);
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
    if(getSize() != 1.f)
        glPointSize(getSize());
    
    if(getSmooth())
        glEnable(GL_POINT_SMOOTH);

#if GL_ARB_point_parameters
    if(getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtension(_arbPointParameters))
        {
            // get "glPointParameterfARB" function pointer
            void (OSG_APIENTRY*pointparameterf)(GLenum pname, GLfloat param) =
                  (void (OSG_APIENTRY*)(GLenum pname, GLfloat param))
                  pEnv->getWindow()->getFunction( _funcPointParameterf );
            // get "glPointParameterfvARB" function pointer
            void (OSG_APIENTRY*pointparameterfv)(GLenum pname, 
                  const GLfloat *param) =
                  (void (OSG_APIENTRY*)(GLenum pname, const GLfloat *param))
                  pEnv->getWindow()->getFunction( _funcPointParameterfv );

            pointparameterf(GL_POINT_SIZE_MIN_ARB, getMinSize());
            pointparameterf(GL_POINT_SIZE_MAX_ARB, getMaxSize());
            pointparameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 
                            getFadeThreshold());
            
            GLfloat att[3] = { getConstantAttenuation(),
                               getLinearAttenuation(),
                               getQuadraticAttenuation() };
            
            pointparameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
        }
        
    }
#endif

#if GL_NV_point_sprite
    if(getSprite())
    {
        if(pEnv->getWindow()->hasExtension(_nvPointSprite))
        {
            // get "glPointParameterfARB" function pointer
            void (OSG_APIENTRY*pointparameterf)(GLenum pname, GLfloat param) =
                  (void (OSG_APIENTRY*)(GLenum pname, GLfloat param))
                  pEnv->getWindow()->getFunction( _funcPointParameterf );

            pointparameterf(GL_POINT_SPRITE_R_MODE_NV, Real32(getRMode()));
            
            glEnable(GL_POINT_SPRITE_NV);
        }
        
    }
#endif

#if ! defined(GL_ARB_point_parameters) && ! defined(GL_NV_point_sprite)
    pEnv;
#endif
}

void PointChunk::changeFrom(DrawEnv    *pEnv, 
                            StateChunk *old_chunk, 
                            UInt32               )
{
    PointChunk *old = dynamic_cast<PointChunk *>(old_chunk);

    if(getSize() != old->getSize())
        glPointSize(getSize());
    
    if(getSmooth() && !old->getSmooth())
    {
        glEnable(GL_POINT_SMOOTH);
    }
    else if(!getSmooth() && old->getSmooth())
    {
        glDisable(GL_POINT_SMOOTH);
    }
    
#if GL_ARB_point_parameters
    if(getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtension(_arbPointParameters))
        {
            // get "glPointParameterfARB" function pointer
            void (OSG_APIENTRY*pointparameterf)(GLenum pname, GLfloat param) =
                  (void (OSG_APIENTRY*)(GLenum pname, GLfloat param))
                  pEnv->getWindow()->getFunction( _funcPointParameterf );
            // get "glPointParameterfvARB" function pointer
            void (OSG_APIENTRY*pointparameterfv)(GLenum pname, 
                  const GLfloat *param) =
                  (void (OSG_APIENTRY*)(GLenum pname, const GLfloat *param))
                  pEnv->getWindow()->getFunction( _funcPointParameterfv );

            pointparameterf(GL_POINT_SIZE_MIN_ARB, getMinSize());
            pointparameterf(GL_POINT_SIZE_MAX_ARB, getMaxSize());
            pointparameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 
                            getFadeThreshold());
            
            GLfloat att[3] = { getConstantAttenuation(),
                               getLinearAttenuation(),
                               getQuadraticAttenuation() };
            
            pointparameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
        }
        
    }
    else if(old->getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtension(_arbPointParameters))
        {
            // get "glPointParameterfARB" function pointer
            void (OSG_APIENTRY*pointparameterf)(GLenum pname, GLfloat param) =
                  (void (OSG_APIENTRY*)(GLenum pname, GLfloat param))
                  pEnv->getWindow()->getFunction( _funcPointParameterf );
            // get "glPointParameterfvARB" function pointer
            void (OSG_APIENTRY*pointparameterfv)(GLenum pname, 
                  const GLfloat *param) =
                  (void (OSG_APIENTRY*)(GLenum pname, const GLfloat *param))
                  pEnv->getWindow()->getFunction( _funcPointParameterfv );

            pointparameterf(GL_POINT_SIZE_MIN_ARB, 0);
            pointparameterf(GL_POINT_SIZE_MAX_ARB, 1e10);
            pointparameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 1);
            
            GLfloat att[3] = { 1, 0, 0 };
            
            pointparameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
        }
    }
#endif

#if GL_NV_point_sprite
    if(getSprite() && !old->getSprite())
    {
        if(pEnv->getWindow()->hasExtension(_nvPointSprite))
        {
            // get "glPointParameterfARB" function pointer
            void (OSG_APIENTRY*pointparameterf)(GLenum pname, GLfloat param) =
                  (void (OSG_APIENTRY*)(GLenum pname, GLfloat param))
                  pEnv->getWindow()->getFunction( _funcPointParameterf );

            pointparameterf(GL_POINT_SPRITE_R_MODE_NV, Real32(getRMode()));
            
            glEnable(GL_POINT_SPRITE_NV);
        }
        
    }
    else if(!getSprite() && old->getSprite())
    {
        if(pEnv->getWindow()->hasExtension(_nvPointSprite))
        {
           glDisable(GL_POINT_SPRITE_NV);
        }
        
    }
#endif

#if ! defined(GL_ARB_point_parameters) && ! defined(GL_NV_point_sprite)
    pEnv;
#endif
}

void PointChunk::deactivate(DrawEnv *pEnv, UInt32)
{
    if(getSize() != 1.f)
        glPointSize(1.f);
    
    if(getSmooth())
        glDisable(GL_POINT_SMOOTH);

#if GL_ARB_point_parameters
    if(getMinSize() >= 0.f)
    {
        if(pEnv->getWindow()->hasExtension(_arbPointParameters))
        {
            // get "glPointParameterfARB" function pointer
            void (OSG_APIENTRY*pointparameterf)(GLenum pname, GLfloat param) =
                  (void (OSG_APIENTRY*)(GLenum pname, GLfloat param))
                  pEnv->getWindow()->getFunction( _funcPointParameterf );
            // get "glPointParameterfvARB" function pointer
            void (OSG_APIENTRY*pointparameterfv)(GLenum pname, 
                  const GLfloat *param) =
                  (void (OSG_APIENTRY*)(GLenum pname, const GLfloat *param))
                  pEnv->getWindow()->getFunction( _funcPointParameterfv );

            pointparameterf(GL_POINT_SIZE_MIN_ARB, 0);
            pointparameterf(GL_POINT_SIZE_MAX_ARB, 1e10);
            pointparameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 1);
            
            GLfloat att[3] = { 1, 0, 0 };
            
            pointparameterfv(GL_POINT_DISTANCE_ATTENUATION_ARB, att);
        }
        
    }
#endif

#if GL_NV_point_sprite
    if(getSprite())
    {
        if(pEnv->getWindow()->hasExtension(_nvPointSprite))
        {
            glDisable(GL_POINT_SPRITE_NV);
        }
        
    }
#endif

#if ! defined(GL_ARB_point_parameters) && ! defined(GL_NV_point_sprite)
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


