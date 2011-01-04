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

#include "OSGGLFuncProtos.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoPropertyBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoProperty.fcd) and
// regenerate the base file.

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
UInt32 GeoProperty::_funcMapBuffer;
UInt32 GeoProperty::_funcUnmapBuffer;
UInt32 GeoProperty::_funcBufferData;
UInt32 GeoProperty::_funcBufferSubData;
UInt32 GeoProperty::_funcGenBuffers;
UInt32 GeoProperty::_funcDeleteBuffers;
UInt32 GeoProperty::_funcglVertexAttribPointerARB;
UInt32 GeoProperty::_funcglEnableVertexAttribArrayARB;
UInt32 GeoProperty::_funcglDisableVertexAttribArrayARB;

UInt32 GeoProperty::_glSecondaryColorPointerEXT;
UInt32 GeoProperty::_glClientActiveTextureARB;

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

        _funcMapBuffer       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glMapBufferARB",   
            _extVertexBufferObject);

        _funcUnmapBuffer     = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glUnmapBufferARB",   
            _extVertexBufferObject);

        _funcBufferData       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBufferDataARB",   
            _extVertexBufferObject);

        _funcBufferSubData    = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBufferSubDataARB",   
            _extVertexBufferObject);

        _funcDeleteBuffers       = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glDeleteBuffersARB",   
            _extVertexBufferObject);

        _funcGenBuffers         = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGenBuffersARB",   
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
}


/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoProperty::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void GeoProperty::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if(0x0000 != (whichField & ~UsageFieldMask))
    {
        if(getGLId() > 0)
        {
            Window::refreshGLObject(getGLId());
        }
    }
}

void GeoProperty::dump(      UInt32    , 
                       const BitVector ) const
{
    SLOG << "GeoProperty:"
         << "Format: "      << getFormat() 
         << " FormatSize: " << getFormatSize()
         << " Stride: "     << getStride()
         << " Dim: "        << getDimension() 
         << " Size: "       << getSize() << std::endl;
}

/*------------------------------ State ------------------------------------*/


/*! GL object handler
    create the VBO and destroy it
*/

UInt32 GeoProperty::handleGL(DrawEnv                 *pEnv, 
                             UInt32                   id, 
                             Window::GLObjectStatusE  mode,
                             UInt32                   uiOptions)
{
    GLuint  glid;
    Window *win = pEnv->getWindow();

    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh )
    {
        if(mode == Window::initialize)
        {
            OSGGETGLFUNCBYID(OSGglGenBuffersARB, osgGlGenBuffersARB,
                             _funcGenBuffers, win);

            osgGlGenBuffersARB(1, &glid);

            win->setGLObjectId(id, glid);
        }
        else
        {
            glid = win->getGLObjectId(id);
        }

        OSGGETGLFUNCBYID(OSGglBindBufferARB, osgGlBindBufferARB,
                         _funcBindBuffer, win);

        OSGGETGLFUNCBYID(OSGglBufferDataARB, osgGlBufferDataARB,
                         _funcBufferData, win);

        OSGGETGLFUNCBYID(OSGglBufferSubDataARB, osgGlBufferSubDataARB,
                         _funcBufferSubData, win);

        osgGlBindBufferARB(getBufferType(), glid);

        if(mode == Window::initialize || mode == Window::reinitialize)
        {
            osgGlBufferDataARB(getBufferType(), 
                               getFormatSize() * getDimension() * getSize(), 
                               NULL, //getData      (), 
                               getVboUsage  ());
        }

        if(getData() != NULL)
        {
            osgGlBufferSubDataARB(getBufferType(),
                                  0,
                                  getFormatSize() * getDimension() * getSize(), 
                                  getData());
        }

        osgGlBindBufferARB(getBufferType(), 0);
    }
    else
    {
        SWARNING << "GeoProperty(" << this << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

    return 0;
}

void GeoProperty::handleDestroyGL(DrawEnv                 *pEnv, 
                               UInt32                   id, 
                               Window::GLObjectStatusE  mode)
{
    GLuint glid;
    Window *win = pEnv->getWindow();

    if(mode == Window::destroy)
    {   
        OSGGETGLFUNCBYID(OSGglDeleteBuffersARB, osgGlDeleteBuffers,
                         _funcDeleteBuffers, win);

        glid = win->getGLObjectId(id);

        osgGlDeleteBuffers(1, &glid);

        win->setGLObjectId(id, 0);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "GeoProperty::handleDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
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

