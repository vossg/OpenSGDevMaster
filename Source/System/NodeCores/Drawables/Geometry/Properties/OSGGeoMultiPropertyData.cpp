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
#include "OSGGeoMultiPropertyData.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoMultiPropertyDataBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoMultiPropertyData.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass GeoMultiPropertyData::_class("GeoMultiPropertyData", 1);

UInt32 GeoMultiPropertyData::_extVertexBufferObject;
UInt32 GeoMultiPropertyData::_funcBindBuffer;
UInt32 GeoMultiPropertyData::_funcBufferData;
UInt32 GeoMultiPropertyData::_funcDeleteBuffers;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoMultiPropertyData::initMethod(InitPhase ePhase)
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
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoMultiPropertyData::GeoMultiPropertyData(void) :
    Inherited()
{
}

GeoMultiPropertyData::GeoMultiPropertyData(const GeoMultiPropertyData &source) :
    Inherited(source)
{
}

GeoMultiPropertyData::~GeoMultiPropertyData(void)
{
}

/*----------------------------- onCreate --------------------------------*/

void GeoMultiPropertyData::onCreate(const GeoMultiPropertyData *)
{
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&GeoMultiPropertyData::handleGL, this, 
                            _1, _2, _3),
            &GeoMultiPropertyData::handleDestroyGL
            ));
}

void GeoMultiPropertyData::onDestroy(UInt32)
{
    if(getGLId() > 0)
    {
        Window::destroyGLObject(getGLId(), 1);
    }
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *GeoMultiPropertyData::getClass(void) const
{
    return &_class;
}


/*----------------------------- class specific ----------------------------*/

void GeoMultiPropertyData::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}


/*------------------------------ State ------------------------------------*/


/*! GL object handler
    create the VBO and destroy it
*/
void GeoMultiPropertyData::handleGL(DrawEnv                 *pEnv, 
                               UInt32                   id, 
                               Window::GLObjectStatusE  mode)
{
    Window *win = pEnv->getWindow();

    if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh )
    {
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
    
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, id);
        _glBufferDataARB(GL_ARRAY_BUFFER_ARB, 
                            getIData().size(), 
                            &getIData()[0], 
                            GL_STATIC_DRAW_ARB);
        _glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    }
    else
    {
        SWARNING << "GeoMultiPropertyData(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}


/*! GL object handler
    destroy it
*/
void GeoMultiPropertyData::handleDestroyGL(DrawEnv                 *pEnv, 
                               UInt32                   id, 
                               Window::GLObjectStatusE  mode)
{
    Window *win = pEnv->getWindow();
    
    if(mode == Window::destroy)
    {   
        // get "glDeleteBuffersARB" function pointer
        void (OSG_APIENTRY*_glDeleteBuffers)
            (GLsizei n, const GLuint *buffers) =
            (void (OSG_APIENTRY*)(GLsizei n, const GLuint *buffers))
            win->getFunction(_funcDeleteBuffers);

        GLuint buf = id;
        _glDeleteBuffers(1, &buf);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "GeoMultiPropertyData::handleDestroyGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

/*---------------------------------------------------------------------*/
/*! \name                    State Commands                            */
/*! \{                                                                 */

void GeoMultiPropertyData::activate(DrawEnv *pEnv, 
                                    UInt32   index)
{
}

void GeoMultiPropertyData::changeFrom(DrawEnv    *pEnv, 
                                      StateChunk *old,
                                      UInt32      index)
{
}

void GeoMultiPropertyData::deactivate(DrawEnv *pEnv, 
                                      UInt32   index)
{
}

/*-------------------------- Comparison -----------------------------------*/

bool GeoMultiPropertyData::isTransparent(void) const
{
    return false;
}

Real32 GeoMultiPropertyData::switchCost(StateChunk *)
{
    return 0;
}

bool GeoMultiPropertyData::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool GeoMultiPropertyData::operator == (const StateChunk &other) const
{
    GeoMultiPropertyData const *tother = dynamic_cast<GeoMultiPropertyData const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return false;
}

bool GeoMultiPropertyData::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}



void GeoMultiPropertyData::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeoMultiPropertyData NI" << std::endl;
}

