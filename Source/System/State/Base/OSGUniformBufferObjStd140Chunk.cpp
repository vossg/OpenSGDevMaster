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

#include "OSGUniformBufferObjStd140Chunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUniformBufferObjStd140ChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGUniformBufferObjStd140Chunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

UInt32 UniformBufferObjStd140Chunk::_extUniformBufferObject   = Win::invalidExtensionID;
UInt32 UniformBufferObjStd140Chunk::_extVertexBufferObject    = Win::invalidExtensionID;

UInt32 UniformBufferObjStd140Chunk::_funcBindBuffer           = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcMapBuffer            = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcUnmapBuffer          = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcBufferData           = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcBufferSubData        = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcGenBuffers           = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcDeleteBuffers        = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcBindBufferBase       = Win::invalidFunctionID;
UInt32 UniformBufferObjStd140Chunk::_funcGetBufferParameteriv = Win::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UniformBufferObjStd140Chunk::initMethod(InitPhase ePhase)
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
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UniformBufferObjStd140Chunk::UniformBufferObjStd140Chunk(void) :
    Inherited()
{
}

UniformBufferObjStd140Chunk::UniformBufferObjStd140Chunk(const UniformBufferObjStd140Chunk &source) :
    Inherited(source)
{
}

UniformBufferObjStd140Chunk::~UniformBufferObjStd140Chunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UniformBufferObjStd140Chunk::changed(ConstFieldMaskArg whichField, 
                                          UInt32            origin,
                                          BitVector         details)
{
    GLenum id = _sfGLId.getValue();

    if((whichField & (UsageFieldMask | BufferFieldMask)) != 0)
    {
        Window::reinitializeGLObject(id);
    }

    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void UniformBufferObjStd140Chunk::onCreate(const UniformBufferObjStd140Chunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                boost::bind(&UniformBufferObjStd140Chunk::handleGL, 
                            UniformBufferObjStd140ChunkMTUncountedPtr(this), 
                            _1, _2, _3, _4),
                &UniformBufferObjStd140Chunk::handleDestroyGL));
}

void UniformBufferObjStd140Chunk::onCreateAspect(const UniformBufferObjStd140Chunk *createAspect,
                                                 const UniformBufferObjStd140Chunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void UniformBufferObjStd140Chunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void UniformBufferObjStd140Chunk::dump(      UInt32    uiIndent,
                                       const BitVector bvFlags) const
{
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
UInt32 UniformBufferObjStd140Chunk::handleGL(DrawEnv                 *pEnv, 
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
            ("UniformBufferObjStd140Chunk::handleGL: vertex buffer objects not "
             "supported for this window!\n"));
        return 0;
    }

    bool hasUBO = pWin->hasExtOrVersion(_extUniformBufferObject, 0x0300);
    if(!hasUBO)
    {
        FWARNING(
            ("UniformBufferObjStd140Chunk::handleGL: uniform buffer objects not "
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
                    osgGlBindBuffer    (GL_UNIFORM_BUFFER, id);
                    osgGlBufferData    (GL_UNIFORM_BUFFER, sz, &_mfBuffer[0], _sfUsage.getValue());
                    osgGlBindBuffer    (GL_UNIFORM_BUFFER, 0);
                }

                glErr("UniformBufferObjStd140Chunk::handleGL initialize");
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

                    osgGlBindBuffer(GL_UNIFORM_BUFFER, id);

                    GLint curr_size;
                    osgGlGetBufferParameteriv( GL_UNIFORM_BUFFER, 
                                               GL_BUFFER_SIZE, 
                                              &curr_size);

                    GLint curr_usage;
                    osgGlGetBufferParameteriv( GL_UNIFORM_BUFFER, 
                                               GL_BUFFER_USAGE, 
                                              &curr_usage);

                    if ( sz                 != SizeT (curr_size ) || 
                        _sfUsage.getValue() != GLenum(curr_usage)  )
                    {
                        osgGlBufferData(  GL_UNIFORM_BUFFER, 
                                          sz, 
                                        &_mfBuffer[0], 
                                         _sfUsage.getValue());
                    }
                    else
                    {
                        GLubyte* pBuffer = static_cast<GLubyte*>(
                            osgGlMapBuffer(GL_UNIFORM_BUFFER, 
                                           GL_WRITE_ONLY_ARB));

                        UInt8* p = &_mfBuffer[0];
                        memcpy(pBuffer, p, sizeof(UInt8) * _mfBuffer.size());
            
                        osgGlUnmapBuffer(GL_UNIFORM_BUFFER);
                    }
                    
                    osgGlBindBuffer    (GL_UNIFORM_BUFFER, 0);

                    glErr("UniformBufferObjStd140Chunk::handleGL reinitialize");
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
                                    osgGlMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY_ARB));

                UChar8* p = &_mfBuffer[0];
                memcpy(pBuffer, p, sizeof(UChar8) * _mfBuffer.size());
    
                osgGlUnmapBuffer(GL_UNIFORM_BUFFER);
                osgGlBindBuffer (GL_UNIFORM_BUFFER, 0);

                glErr("UniformBufferObjStd140Chunk::handleGL needrefresh");
            }
            break;
        default:
            {
                SWARNING << "UniformBufferObjStd140Chunk(" << this << "::handleGL: Illegal mode: "
                         << mode << " for id " << id << std::endl;
            }
    }

    return 0;
}

/*! GL object handler
    destroy it
*/
void UniformBufferObjStd140Chunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                                  UInt32                   osgid, 
                                                  Window::GLObjectStatusE  mode)
{
    Window *pWin = pEnv->getWindow();
    GLuint  id   = pWin->getGLObjectId(osgid);

    if(mode == Window::destroy)
    {
        OSGGETGLFUNCBYID_GL3_ES( glDeleteBuffers,
                                 osgGlDeleteBuffers,
                                _funcDeleteBuffers, 
                                 pWin);

        osgGlDeleteBuffers(1, &id);
        pWin->setGLObjectId(osgid, 0);

        glErr("UniformBufferObjStd140Chunk::handleDestroyGL");
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last buffer user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "UniformBufferObjStd140Chunk::handleDestroyGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

/*------------------------------ tools --------------------------------------*/

void UniformBufferObjStd140Chunk::validate(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(this->getGLId(),
                                        pEnv           );
}

Int32 UniformBufferObjStd140Chunk::getOpenGLId(DrawEnv *pEnv)
{
    return pEnv->getWindow()->getGLObjectId(this->getGLId());
}

/*------------------------------ activate -----------------------------------*/

void UniformBufferObjStd140Chunk::activate(DrawEnv *pEnv, UInt32 idx)
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

    osgGlBindBuffer    (GL_UNIFORM_BUFFER, id);
    osgGlBindBufferBase(GL_UNIFORM_BUFFER, idx, id);

    glErr("UniformBufferObjStd140Chunk::activate");
}

/*------------------------------ deactivate ---------------------------------*/

void UniformBufferObjStd140Chunk::deactivate(DrawEnv *pEnv, UInt32 idx)
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

    osgGlBindBufferBase(GL_UNIFORM_BUFFER, idx, 0);
    osgGlBindBuffer    (GL_UNIFORM_BUFFER, 0);

    glErr("UniformBufferObjStd140Chunk::deactivate");
}

/*------------------------------ changeFrom ---------------------------------*/

void UniformBufferObjStd140Chunk::changeFrom(DrawEnv    *pEnv,
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

