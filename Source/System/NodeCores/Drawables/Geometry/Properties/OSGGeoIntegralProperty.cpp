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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGLEXT.h"
#include "OSGWindow.h"
#include "OSGGeoIntegralProperty.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GeoIntegralProperty
Parent class for integral (i.e. one dimensional integer typed) properties.  The main reason for this class is as a parent class for indices, lengths and  types for the Geometry.  
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass GeoIntegralProperty::_class("GeoIntegralProperty", 1);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoIntegralProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoIntegralProperty::getClass(void) const
{
    return GeoProperty::getClass();
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoIntegralProperty::GeoIntegralProperty(void) :
    Inherited()
{
}

GeoIntegralProperty::GeoIntegralProperty(const GeoIntegralProperty &source) :
    Inherited(source)
{
    // for some reason using VBo for elemnts doesn't work right now, disable it
    _sfUseVBO.setValue(false);
}

GeoIntegralProperty::~GeoIntegralProperty(void)
{
}


/*! State Chunk handling */

GLenum GeoIntegralProperty::getBufferType(void)
{
#ifndef OSG_WINCE
    return GL_ELEMENT_ARRAY_BUFFER_ARB;
#else
    return GL_NONE;
#endif 
}

void GeoIntegralProperty::activate(DrawEnv *pEnv, UInt32 slot)
{
#ifndef OSG_WINCE
    Window *win = pEnv->getWindow();
    
    if(win->hasExtension(_extVertexBufferObject) &&
       getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        win->validateGLObject(getGLId(), pEnv);

         // get "glBindBufferARB" function pointer
        void (OSG_APIENTRY*_glBindBufferARB)
            (GLenum target, GLuint buffer) =
            (void (OSG_APIENTRY*)(GLenum target, GLuint buffer))
            pEnv->getWindow()->getFunction(_funcBindBuffer);

        _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 
                         win->getGLObjectId(getGLId()));
    }
#endif
}

void GeoIntegralProperty::changeFrom(DrawEnv    *pEnv, 
                                     StateChunk *old, 
                                     UInt32      slot)
{
#ifndef OSG_WINCE
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    if(old == this)
        return;

    Window *win = pEnv->getWindow();
    GeoIntegralProperty *o = dynamic_cast<GeoIntegralProperty*>(old);
    
    if(!win->hasExtension(_extVertexBufferObject))
        return;

    // get "glBindBufferARB" function pointer
    void (OSG_APIENTRY*_glBindBufferARB)
        (GLenum target, GLuint buffer) =
        (void (OSG_APIENTRY*)(GLenum target, GLuint buffer))
        pEnv->getWindow()->getFunction(_funcBindBuffer);

    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        win->validateGLObject(getGLId(), pEnv);

        _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 
                         win->getGLObjectId(getGLId()));
    }
    else if(o != NULL && o->getGLId() != 0 && o->getUseVBO())
    {
        _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);            
    }
#endif
}

void GeoIntegralProperty::deactivate(DrawEnv *pEnv, UInt32 slot)
{
#ifndef OSG_WINCE
    Window *win = pEnv->getWindow();
        
    if(win->hasExtension(_extVertexBufferObject) &&
       getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
         // get "glBindBufferARB" function pointer
        void (OSG_APIENTRY*_glBindBufferARB)
            (GLenum target, GLuint buffer) =
            (void (OSG_APIENTRY*)(GLenum target, GLuint buffer))
            pEnv->getWindow()->getFunction(_funcBindBuffer);

        _glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }
#endif
}

bool GeoIntegralProperty::isInVBO(DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();
    
    if(getGLId() != 0 && getUseVBO()) // Do we have a VBO?
    {
        return true;
    }
    
    return false;    
}

/*----------------------------- class specific ----------------------------*/

void GeoIntegralProperty::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GeoIntegralProperty::dump(      UInt32 i, 
                         const BitVector v) const
{
    Inherited::dump(i,v);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGGEOINTEGRALPROPERTYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOINTEGRALPROPERTYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEOINTEGRALPROPERTYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

