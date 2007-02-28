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
#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGeoProperty.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoProperty.fcd) and
// regenerate the base file.

/*! \fn GeoProperty::

/*! \fn UInt32  GeoProperty::getFormat    (void)
    Returns the OpenGL type constant identifying the data type of the
    properties values.
*/

/*! \fn UInt32  GeoProperty::getFormatSize(void)
    Returns the size (as a multiple of <code>sizeof(char)</code>) of the data
    type of the properties values.
*/

/*! \fn UInt32  GeoProperty::getStride    (void)
    Returns the stride (the distance between successive values) of the
    properties values.
*/

/*! \fn UInt32  GeoProperty::getDimension (void)
    Returns the number of dimensions a single value of the property has.
*/

/*! \fn UInt32  GeoProperty::getSize      (void)
    Returns the number of values the property holds.
*/

/*! \fn UInt32  GeoProperty::size         (void)
    Returns the number of values the property holds.

    \return Size of this property.
*/

/*! \fn UInt8* GeoProperty::getData      (void)
    Returns a pointer to the values stored in this property. This mainly exists
    to pass arrays to OpenGL.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass GeoProperty::_class("GeoProperty", 16);

UInt32 GeoProperty::_extVertexBufferObject;
UInt32 GeoProperty::_extMultitexture;
UInt32 GeoProperty::_arbVertexProgram;
UInt32 GeoProperty::_extSecondaryColor;
UInt32 GeoProperty::_funcBindBuffer;
UInt32 GeoProperty::_funcBufferData;
UInt32 GeoProperty::_funcDeleteBuffers;
UInt32 GeoProperty::_glClientActiveTextureARB;
UInt32 GeoProperty::_funcglVertexAttribPointerARB;
UInt32 GeoProperty::_funcglEnableVertexAttribArrayARB;
UInt32 GeoProperty::_funcglDisableVertexAttribArrayARB;
UInt32 GeoProperty::_glSecondaryColorPointerEXT;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoProperty::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extVertexBufferObject=
            Window::registerExtension("GL_ARB_vertex_buffer_object");
        
        _funcBindBuffer       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBindBufferARB",   
            _extVertexBufferObject);

        _funcBufferData       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBufferDataARB",   
            _extVertexBufferObject);

        _funcDeleteBuffers       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDeleteBuffersARB",   
            _extVertexBufferObject);

        _arbVertexProgram       = 
            Window::registerExtension("GL_ARB_vertex_program");
        
        _funcglVertexAttribPointerARB   = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glVertexAttribPointerARB",
            _arbVertexProgram);

        _funcglEnableVertexAttribArrayARB   = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glEnableVertexAttribArrayARB",
            _arbVertexProgram);

        _funcglDisableVertexAttribArrayARB   = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDisableVertexAttribArrayARB",
            _arbVertexProgram);

    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoProperty::GeoProperty(void) :
    Inherited()
{
}

GeoProperty::GeoProperty(const GeoProperty &source) :
    Inherited(source)
{
}

GeoProperty::~GeoProperty(void)
{
    if(getGLId() > 0)
    {
        Window::destroyGLObject(getGLId(), 1);
    }
}


/*----------------------------- onCreate --------------------------------*/

void GeoProperty::onCreate(const GeoProperty *)
{
    if(GlobalSystemState == Startup)
        return;

    GeoPropertyPtr tmpPtr = Inherited::constructPtr<GeoProperty>(this);

    setGLId(
        Window::registerGLObject(
            boost::bind(&GeoProperty::handleGL, tmpPtr, _1, _2),
            1));
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoProperty::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void GeoProperty::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if(getGLId() > 0)
    {
        Window::refreshGLObject(getGLId());
    }
}

void GeoProperty::dump(      UInt32    , 
                       const BitVector ) const
{
    SLOG << "GeoProperty:"
         << "Format: " << getFormat() << " FormatSize: " << getFormatSize()
         << " Stride: " << getStride()
         << " Dim: " << getDimension() << " Size: " << getSize() << std::endl;
}

/*------------------------------ State ------------------------------------*/


/*! GL object handler
    create the VBO and destroy it
*/
void GeoProperty::handleGL(DrawEnv *pEnv, UInt32 idstatus)
{
#ifndef OSG_WINCE
    Window::GLObjectStatusE mode;
    UInt32 id;
    GLuint glid;
    Window *win = pEnv->getWindow();

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::destroy)
    {   
        // get "glDeleteBuffersARB" function pointer
        void (OSG_APIENTRY*_glDeleteBuffers)
            (GLsizei n, const GLuint *buffers) =
            (void (OSG_APIENTRY*)(GLsizei n, const GLuint *buffers))
            win->getFunction(_funcDeleteBuffers);

        glid = win->getGLObjectId(id);

        _glDeleteBuffers(1, &glid);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh )
    {
        if(mode == Window::initialize)
        {
            glid = glGenLists(1);
            win->setGLObjectId(id, glid);
        }
        else
        {
            glid = win->getGLObjectId(id);
        }

        // get "glBindBufferARB" function pointer
        void (OSG_APIENTRY*_glBindBufferARB)
            (GLenum target, GLuint buffer) =
            (void (OSG_APIENTRY*)(GLenum target, GLuint buffer))
            win->getFunction(_funcBindBuffer);

        // get "glBufferDataARB" function pointer
        void (OSG_APIENTRY*_glBufferDataARB)
            (GLenum target, long size, const void *data,
                           GLenum usage) =
            (void (OSG_APIENTRY*)(GLenum target, long size, const void *data,
                           GLenum usage))
            win->getFunction(_funcBufferData);
    
        _glBindBufferARB(getBufferType(), glid);
        _glBufferDataARB(getBufferType(), 
                            getFormatSize() * getDimension() * getSize(), 
                            getData(), 
                            GL_STATIC_DRAW_ARB);
        _glBindBufferARB(getBufferType(), 0);
    }
    else
    {
        SWARNING << "GeoProperty(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
#endif
}

/*-------------------------- Comparison -----------------------------------*/

bool GeoProperty::isTransparent(void) const
{
    return false;
}

Real32 GeoProperty::switchCost(StateChunk *)
{
    return 0;
}

bool GeoProperty::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool GeoProperty::operator == (const StateChunk &other) const
{
    GeoProperty const *tother = dynamic_cast<GeoProperty const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return false;
}

bool GeoProperty::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

