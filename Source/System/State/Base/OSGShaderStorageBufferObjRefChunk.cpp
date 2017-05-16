/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGLFuncProtos.h"

#include "OSGDrawEnv.h"

#include "OSGShaderStorageBufferObjRefChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderStorageBufferObjRefChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderStorageBufferObjRefChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

UInt32 ShaderStorageBufferObjRefChunk::_extUniformBufferObject        = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjRefChunk::_extVertexBufferObject         = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjRefChunk::_extShaderStorageBufferObject  = Win::invalidExtensionID;

UInt32 ShaderStorageBufferObjRefChunk::_funcBindBuffer                = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjRefChunk::_funcBindBufferBase            = Win::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderStorageBufferObjRefChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extVertexBufferObject=
            Window::registerExtension("GL_ARB_vertex_buffer_object");

        _extUniformBufferObject  =
            Window::registerExtension("GL_ARB_uniform_buffer_object"  );

        _extShaderStorageBufferObject =
            Window::registerExtension("GL_ARB_shader_storage_buffer_object");

        _funcBindBuffer = 
            Window::registerFunction(
                OSG_DLSYM_UNDERSCORE"glBindBufferARB",   
                _extVertexBufferObject);

        _funcBindBufferBase = 
            Window::registerFunction(
                OSG_DLSYM_UNDERSCORE"glBindBufferBase",   
                _extUniformBufferObject);
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderStorageBufferObjRefChunk::ShaderStorageBufferObjRefChunk(void) :
    Inherited()
{
}

ShaderStorageBufferObjRefChunk::ShaderStorageBufferObjRefChunk(
    const ShaderStorageBufferObjRefChunk &source) :
    Inherited(source)
{
}

ShaderStorageBufferObjRefChunk::~ShaderStorageBufferObjRefChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderStorageBufferObjRefChunk::changed(ConstFieldMaskArg whichField, 
                                             UInt32            origin,
                                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void ShaderStorageBufferObjRefChunk::onCreate(const ShaderStorageBufferObjRefChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;
}

void ShaderStorageBufferObjRefChunk::onCreateAspect(
    const ShaderStorageBufferObjRefChunk *createAspect,
    const ShaderStorageBufferObjRefChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void ShaderStorageBufferObjRefChunk::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void ShaderStorageBufferObjRefChunk::dump(UInt32          uiIndent,
                                          const BitVector bvFlags) const
{
    SLOG << "Dump ShaderStorageBufferObjRefChunk NI" << std::endl;

    Inherited::dump(uiIndent, bvFlags);
}

/*------------------------------ tools --------------------------------------*/

void ShaderStorageBufferObjRefChunk::validate(DrawEnv *pEnv)
{
    if(this->getOsgGLId() != 0)
    {
        pEnv->getWindow()->validateGLObject(this->getOsgGLId(),
                                            pEnv              );
    }
}

Int32 ShaderStorageBufferObjRefChunk::getOpenGLId(DrawEnv *pEnv)
{
    if(this->getOsgGLId() != 0)
    {
        return pEnv->getWindow()->getGLObjectId(this->getOsgGLId());
    }
    else
    {
        return this->getOglGLId();
    }
}

/*------------------------------ activate -----------------------------------*/

void ShaderStorageBufferObjRefChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    Window *pWin = pEnv->getWindow();

    validate(pEnv);
    GLuint id = this->getOpenGLId(pEnv);

    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                             osgGlBindBuffer,
                            _funcBindBuffer, 
                             pWin);

    OSGGETGLFUNCBYID_GL3_ES( glBindBufferBase, 
                             osgGlBindBufferBase,
                            _funcBindBufferBase, 
                             pWin);

    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, id);
    osgGlBindBufferBase(GL_SHADER_STORAGE_BUFFER, idx, id);

    glErr("ShaderStorageBufferObjRefChunk::activate");
}

/*------------------------------ deactivate ---------------------------------*/

void ShaderStorageBufferObjRefChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    Window *pWin = pEnv->getWindow();

    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                             osgGlBindBuffer,
                            _funcBindBuffer, 
                             pWin);

    OSGGETGLFUNCBYID_GL3_ES( glBindBufferBase, 
                             osgGlBindBufferBase,
                            _funcBindBufferBase, 
                             pWin);

    osgGlBindBufferBase(GL_SHADER_STORAGE_BUFFER, idx, 0);
    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, 0);

    glErr("ShaderStorageBufferObjRefChunk::deactivate");
}

/*------------------------------ changeFrom ---------------------------------*/

void ShaderStorageBufferObjRefChunk::changeFrom(DrawEnv    *pEnv,
                                       StateChunk *old,
                                       UInt32      idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    // is that a valid assumption?
    if (old == this)
        return;

    old->deactivate(pEnv, idx);
    this->activate(pEnv, idx);
}

OSG_END_NAMESPACE
