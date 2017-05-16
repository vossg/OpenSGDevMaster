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

#include "OSGShaderStorageBufferObjStdLayoutChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderStorageBufferObjStdLayoutChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderStorageBufferObjStdLayoutChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

UInt32 ShaderStorageBufferObjStdLayoutChunk::_extUniformBufferObject        = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_extVertexBufferObject         = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_extProgramInterfaceQuery      = Win::invalidExtensionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_extShaderStorageBufferObject  = Win::invalidExtensionID;

UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcBindBuffer                = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcMapBuffer                 = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcUnmapBuffer               = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcBufferData                = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcBufferSubData             = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcGenBuffers                = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcDeleteBuffers             = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcBindBufferBase            = Win::invalidFunctionID;
UInt32 ShaderStorageBufferObjStdLayoutChunk::_funcGetBufferParameteriv      = Win::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderStorageBufferObjStdLayoutChunk::initMethod(InitPhase ePhase)
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

        _funcGetBufferParameteriv = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glGetBufferParameterivARB",   
            _extVertexBufferObject);


        _extUniformBufferObject  =
            Window::registerExtension("GL_ARB_uniform_buffer_object"  );

        _funcBindBufferBase     = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBindBufferBase",   
            _extUniformBufferObject);


        _extProgramInterfaceQuery =
            Window::registerExtension("GL_ARB_program_interface_query");

        _extShaderStorageBufferObject =
            Window::registerExtension("GL_ARB_shader_storage_buffer_object");
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderStorageBufferObjStdLayoutChunk::ShaderStorageBufferObjStdLayoutChunk(void) :
    Inherited()
{
}

ShaderStorageBufferObjStdLayoutChunk::ShaderStorageBufferObjStdLayoutChunk(
    const ShaderStorageBufferObjStdLayoutChunk &source) :
    Inherited(source)
{
}

ShaderStorageBufferObjStdLayoutChunk::~ShaderStorageBufferObjStdLayoutChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderStorageBufferObjStdLayoutChunk::changed(ConstFieldMaskArg whichField, 
                                                   UInt32            origin,
                                                   BitVector         details)
{
    GLenum id = _sfGLId.getValue();

    if( (whichField & (UsageFieldMask | BufferFieldMask)) != 0 )
    {
        Window::reinitializeGLObject(id);
    }

    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void ShaderStorageBufferObjStdLayoutChunk::onCreate(const ShaderStorageBufferObjStdLayoutChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                boost::bind(&ShaderStorageBufferObjStdLayoutChunk::handleGL, 
                            ShaderStorageBufferObjStdLayoutChunkMTUncountedPtr(this), 
                            _1, _2, _3, _4),
                &ShaderStorageBufferObjStdLayoutChunk::handleDestroyGL));
}

void ShaderStorageBufferObjStdLayoutChunk::onCreateAspect(
    const ShaderStorageBufferObjStdLayoutChunk *createAspect,
    const ShaderStorageBufferObjStdLayoutChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void ShaderStorageBufferObjStdLayoutChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void ShaderStorageBufferObjStdLayoutChunk::dump(      UInt32    uiIndent,
                                                const BitVector bvFlags) const
{
    SLOG << "Dump ShaderStorageBufferObjStdLayoutChunk NI" << std::endl;

    Inherited::dump(uiIndent, bvFlags);

    if((bvFlags & UsageFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "usage " << _sfUsage.getValue() << "\n";
    }
    if((bvFlags & BufferFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "buffer " << "content changed" << "\n";// _mfBuffer.getValue() << "\n";
    }
}

/*------------------------------ GL -----------------------------------------*/

/*! GL object handler                                                        */
UInt32 ShaderStorageBufferObjStdLayoutChunk::handleGL(
    DrawEnv                 *pEnv, 
    UInt32                   osgid, 
    Window::GLObjectStatusE  mode,
    UInt64                   uiOptions)
{
    Window *pWin = pEnv->getWindow();
    GLuint  id  = pWin->getGLObjectId(osgid);

    bool hasVBO = pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200);
    if(!hasVBO)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: vertex buffer objects not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasUBO = pWin->hasExtOrVersion(_extUniformBufferObject, 0x0301);
    if(!hasUBO)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: uniform buffer objects not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasSSBO = pWin->hasExtOrVersion(_extShaderStorageBufferObject, 0x0403);
    if(!hasSSBO)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: GL_ARB_uniform_buffer_object not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasPIQ = pWin->hasExtOrVersion(_extProgramInterfaceQuery, 0x0402);
    if(!hasPIQ)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleGL: GL_ARB_program_interface_query not "
             "supported for this window!\n"));
        return 0;
    }

    switch (mode)
    {
        case Window::initialize:
            {
                OSGGETGLFUNCBYID_GL3_ES( glGenBuffers, 
                                         osgGlGenBuffers,
                                        _funcGenBuffers, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                                         osgGlBindBuffer,
                                        _funcBindBuffer, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glBufferData, 
                                         osgGlBufferData,
                                        _funcBufferData, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glBindBufferBase, 
                                         osgGlBindBufferBase,
                                        _funcBindBufferBase, 
                                         pWin);

                osgGlGenBuffers(1, &id);
                pWin->setGLObjectId(osgid, id);

                std::size_t sz = _mfBuffer.size();
                if (sz > 0)
                {
                    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, id);
                    osgGlBufferData    (GL_SHADER_STORAGE_BUFFER, sz, &_mfBuffer[0], _sfUsage.getValue());
                    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, 0);
                }

                glErr("ShaderStorageBufferObjStdLayoutChunk::handleGL initialize");
            }
            break;
        case Window::reinitialize:
            {
                std::size_t sz = _mfBuffer.size();
                if (sz > 0)
                {
                    OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                                             osgGlBindBuffer,
                                            _funcBindBuffer, 
                                             pWin);

                    OSGGETGLFUNCBYID_GL3_ES( glGetBufferParameteriv,
                                             osgGlGetBufferParameteriv,
                                            _funcGetBufferParameteriv, 
                                             pWin);

                    OSGGETGLFUNCBYID_GL3_ES( glBufferData, 
                                             osgGlBufferData,
                                            _funcBufferData, 
                                             pWin);

                    OSGGETGLFUNCBYID_GL3_ES( glMapBuffer, 
                                             osgGlMapBuffer,
                                            _funcMapBuffer, 
                                             pWin);

                    OSGGETGLFUNCBYID_GL3_ES( glUnmapBuffer, 
                                             osgGlUnmapBuffer,
                                            _funcUnmapBuffer, 
                                             pWin);

                    OSGGETGLFUNCBYID_GL3_ES( glBindBufferBase, 
                                             osgGlBindBufferBase,
                                            _funcBindBufferBase, 
                                             pWin);

                    osgGlBindBuffer(GL_SHADER_STORAGE_BUFFER, id);

                    GLint curr_size;
                    osgGlGetBufferParameteriv( GL_SHADER_STORAGE_BUFFER, 
                                               GL_BUFFER_SIZE, 
                                              &curr_size);

                    GLint curr_usage;
                    osgGlGetBufferParameteriv( GL_SHADER_STORAGE_BUFFER, 
                                               GL_BUFFER_USAGE, 
                                              &curr_usage);

                    if ( sz                 != SizeT (curr_size ) || 
                        _sfUsage.getValue() != GLenum(curr_usage)  )
                    {
                        osgGlBufferData(  GL_SHADER_STORAGE_BUFFER, 
                                          sz, 
                                        &_mfBuffer[0], 
                                         _sfUsage.getValue());
                    }
                    else
                    {
                        GLubyte* pBuffer = static_cast<GLubyte*>(
                            osgGlMapBuffer(GL_SHADER_STORAGE_BUFFER, 
                                           GL_WRITE_ONLY_ARB));

                        UInt8* p = &_mfBuffer[0];
                        memcpy(pBuffer, p, sizeof(UInt8) * _mfBuffer.size());
            
                        osgGlUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
                    }
                    
                    osgGlBindBuffer    (GL_SHADER_STORAGE_BUFFER, 0);

                    glErr("ShaderStorageBufferObjStdLayoutChunk::handleGL reinitialize");
                }
            }
            break;
        case Window::needrefresh:
            {
                OSGGETGLFUNCBYID_GL3_ES( glBindBuffer,
                                         osgGlBindBuffer,
                                        _funcBindBuffer, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glMapBuffer, 
                                         osgGlMapBuffer,
                                        _funcMapBuffer, 
                                         pWin);

                OSGGETGLFUNCBYID_GL3_ES( glUnmapBuffer, 
                                         osgGlUnmapBuffer,
                                        _funcUnmapBuffer, 
                                         pWin);

                osgGlBindBuffer(GL_UNIFORM_BUFFER, id);
                GLubyte* pBuffer = static_cast<GLubyte*>(
                                    osgGlMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY_ARB));

                UChar8* p = &_mfBuffer[0];
                memcpy(pBuffer, p, sizeof(UChar8) * _mfBuffer.size());
    
                osgGlUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
                osgGlBindBuffer (GL_SHADER_STORAGE_BUFFER, 0);

                glErr("ShaderStorageBufferObjStdLayoutChunk::handleGL needrefresh");
            }
            break;
        default:
            {
                SWARNING << "ShaderStorageBufferObjStdLayoutChunk(" << this << "::handleGL: Illegal mode: "
                         << mode << " for id " << id << std::endl;
            }
    }

    return 0;
}

/*! GL object handler
    destroy it
*/
void ShaderStorageBufferObjStdLayoutChunk::handleDestroyGL(
    DrawEnv                 *pEnv, 
    UInt32                   osgid, 
    Window::GLObjectStatusE  mode)
{
    Window *pWin = pEnv->getWindow();
    GLuint  id   = pWin->getGLObjectId(osgid);

    bool hasVBO = pWin->hasExtOrVersion(_extVertexBufferObject, 0x0105, 0x0200);
    if(!hasVBO)
    {
        FWARNING(
            ("ShaderStorageBufferObjStdLayoutChunk::handleDestroyGL: vertex buffer objects not "
             "supported for this window!\n"));
        return;
    }

    if(mode == Window::destroy)
    {
        OSGGETGLFUNCBYID_GL3_ES( glDeleteBuffers,
                                 osgGlDeleteBuffers,
                                _funcDeleteBuffers, 
                                 pWin);

        osgGlDeleteBuffers(1, &id);
        pWin->setGLObjectId(osgid, 0);

        glErr("ShaderStorageBufferObjStdLayoutChunk::handleDestroyGL");
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last buffer user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "ShaderStorageBufferObjStdLayoutChunk::handleDestroyGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

/*------------------------------ tools --------------------------------------*/

void ShaderStorageBufferObjStdLayoutChunk::validate(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(this->getGLId(),
                                        pEnv           );
}

Int32 ShaderStorageBufferObjStdLayoutChunk::getOpenGLId(DrawEnv *pEnv)
{
    return pEnv->getWindow()->getGLObjectId(this->getGLId());
}

/*------------------------------ activate -----------------------------------*/

void ShaderStorageBufferObjStdLayoutChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
    Window *pWin = pEnv->getWindow();

    pWin->validateGLObject(getGLId(), pEnv);

    GLuint id = pWin->getGLObjectId(getGLId());

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

    glErr("ShaderStorageBufferObjStdLayoutChunk::activate");
}

/*------------------------------ deactivate ---------------------------------*/

void ShaderStorageBufferObjStdLayoutChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
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

    glErr("ShaderStorageBufferObjStdLayoutChunk::deactivate");
}

/*------------------------------ changeFrom ---------------------------------*/

void ShaderStorageBufferObjStdLayoutChunk::changeFrom(DrawEnv    *pEnv,
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
