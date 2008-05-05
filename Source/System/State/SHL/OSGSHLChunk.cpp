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

#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
//#include <OSGRemoteAspect.h>
#include <OSGWindow.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGStereoCameraDecorator.h>

#include <OSGDrawEnv.h>

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>
#include <OSGShaderParameterPnt2f.h>
#include <OSGShaderParameterPnt3f.h>

#include <OSGShaderParameterMInt.h>
#include <OSGShaderParameterMReal.h>
#include <OSGShaderParameterMVec2f.h>
#include <OSGShaderParameterMVec3f.h>
#include <OSGShaderParameterMVec4f.h>
#include <OSGShaderParameterMMatrix.h>

#include "OSGSHLChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSHLChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGSHLChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SHLChunk::_class("SHL", 1, 30);

UInt32 SHLChunk::_shl_extension            = Window::invalidExtensionID;
UInt32 SHLChunk::_cg_extension             = Window::invalidExtensionID;
UInt32 SHLChunk::_geometry_extension       = Window::invalidExtensionID;

UInt32 SHLChunk::_funcCreateProgramObject  = Window::invalidFunctionID;
UInt32 SHLChunk::_funcProgramParameteri    = Window::invalidFunctionID;
UInt32 SHLChunk::_funcCreateShaderObject   = Window::invalidFunctionID;
UInt32 SHLChunk::_funcDeleteObject         = Window::invalidFunctionID;
UInt32 SHLChunk::_funcDetachObject         = Window::invalidFunctionID;
UInt32 SHLChunk::_funcAttachObject         = Window::invalidFunctionID;

UInt32 SHLChunk::_funcShaderSource         = Window::invalidFunctionID;
UInt32 SHLChunk::_funcCompileShader        = Window::invalidFunctionID;
UInt32 SHLChunk::_funcLinkProgram          = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetInfoLog           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUseProgramObject     = Window::invalidFunctionID;

UInt32 SHLChunk::_funcGetObjectParameteriv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetObjectParameterfv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetUniformLocation   = Window::invalidFunctionID;

UInt32 SHLChunk::_funcBindAttribLocation   = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetAttribLocation    = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniform1i            = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform1iv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform2iv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform3iv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform4iv           = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniform1f            = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform1fv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform2fv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform3fv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform4fv           = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniformMatrix4fv     = Window::invalidFunctionID;

UInt32 SHLChunk::_funcGetUniformiv         = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetUniformfv         = Window::invalidFunctionID;

Int32 SHLChunk::_clusterId = -1;

SHLChunk::parametercbfp SHLChunk::_userParametersCallback = NULL;

volatile UInt16 SHLChunk::_uiChunkCounter = 1;

// prototypes

typedef GLuint  (OSG_APIENTRY * OSGGLCREATEPROGRAMOBJECTARBPROC) (void);
typedef void    (OSG_APIENTRY * OSGGLPROGRAMPARAMETERIEXTPROC) (GLuint program, GLenum pname, GLint value);
typedef void    (OSG_APIENTRY * OSGGLDELETEOBJECTARBPROC) (GLuint obj);
typedef GLuint  (OSG_APIENTRY * OSGGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
typedef void    (OSG_APIENTRY * OSGGLSHADERSOURCEARBPROC) (GLuint shaderObj, GLsizei count, const char **strings, const GLint *length);
typedef void    (OSG_APIENTRY * OSGGLCOMPILESHADERARBPROC) (GLuint shaderObj);
typedef void    (OSG_APIENTRY * OSGGLGETOBJECTPARAMETERIVARBPROC) (GLuint obj, GLenum pname, GLint *params);
typedef void    (OSG_APIENTRY * OSGGLGETINFOLOGARBPROC) (GLuint obj,GLsizei maxLength, GLsizei *length, char *infoLog);
typedef void    (OSG_APIENTRY * OSGGLATTACHOBJECTARBPROC) (GLuint containerObj, GLuint obj);
typedef void    (OSG_APIENTRY * OSGGLLINKPROGRAMARBPROC) (GLuint programObj);
typedef void    (OSG_APIENTRY * OSGGLUSEPROGRAMOBJECTARBPROC) (GLuint programObj);

typedef GLint   (OSG_APIENTRY * OSGGLGETUNIFORMLOCATIONARBPROC) (GLuint programObj, const char *name);

typedef void   (OSG_APIENTRY * OSGGLUNIFORM1IARBPROC) (GLint location, GLint value);
typedef void   (OSG_APIENTRY * OSGGLUNIFORMIVARBPROC) (GLint location, GLsizei count, GLint *value);

typedef void   (OSG_APIENTRY * OSGGLUNIFORM1FARBPROC) (GLint location, GLfloat value);
typedef void   (OSG_APIENTRY * OSGGLUNIFORMFVARBPROC) (GLint location, GLsizei count, GLfloat *value);

typedef void   (OSG_APIENTRY * OSGGLUNIFORMMATRIXFVARBPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat *value);

typedef void   (OSG_APIENTRY * OSGGLGETUNIFORMFIARBPROC) (GLuint programObj, GLint location, GLint *value);
typedef void   (OSG_APIENTRY * OSGGLGETUNIFORMFVARBPROC) (GLuint programObj, GLint location, GLfloat *value);


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SHLChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _shl_extension =
            Window::registerExtension("GL_ARB_shading_language_100");

        _cg_extension =
            Window::registerExtension("GL_EXT_Cg_shader");

        _geometry_extension = 
            Window::registerExtension("GL_EXT_geometry_shader4");

        _funcCreateProgramObject =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCreateProgramObjectARB",
                _shl_extension);

        _funcProgramParameteri =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glProgramParameteriEXT", 
                _geometry_extension);

        _funcCreateShaderObject =
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glCreateShaderObjectARB",
             _shl_extension);

        _funcDeleteObject =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDeleteObjectARB",
                _shl_extension);

        _funcDetachObject =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDetachObjectARB",
                _shl_extension);

        _funcAttachObject =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glAttachObjectARB",
                _shl_extension);

        _funcShaderSource =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glShaderSourceARB",
                _shl_extension);

        _funcCompileShader =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCompileShaderARB",
                _shl_extension);

        _funcLinkProgram =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glLinkProgramARB",
                _shl_extension);

        _funcGetInfoLog =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetInfoLogARB",
                _shl_extension);

        _funcUseProgramObject =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUseProgramObjectARB",
                _shl_extension);

        _funcGetObjectParameteriv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetObjectParameterivARB",
                _shl_extension);

        _funcGetObjectParameterfv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetObjectParameterfvARB",
                _shl_extension);

        _funcGetUniformLocation =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetUniformLocationARB",
                _shl_extension);

        _funcBindAttribLocation =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glBindAttribLocationARB",
                _shl_extension);

        _funcGetAttribLocation =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetAttribLocationARB",
                _shl_extension);

        _funcUniform1i =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1iARB",
                _shl_extension);

        _funcUniform1iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1ivARB", 
                _shl_extension);

        _funcUniform2iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2ivARB",
                _shl_extension);

        _funcUniform3iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3ivARB",
                _shl_extension);

        _funcUniform4iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4ivARB",
                _shl_extension);

        _funcUniform1f =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1fARB",
                _shl_extension);

        _funcUniform1fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1fvARB", 
                _shl_extension);

        _funcUniform2fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2fvARB",
                _shl_extension);

        _funcUniform3fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3fvARB",
                _shl_extension);

        _funcUniform4fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4fvARB",
                _shl_extension);

        _funcUniformMatrix4fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniformMatrix4fvARB",
                _shl_extension);

        _funcGetUniformiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetUniformivARB",
                _shl_extension);

        _funcGetUniformfv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetUniformfvARB",
                _shl_extension);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SHLChunk::SHLChunk(void) :
     Inherited             ( ),
    _uiChunkId             (0),
    _osgParametersCallbacks( ),
    _oldParameterSize      (0),
    _userParameterCallbacks( )
{
}

SHLChunk::SHLChunk(const SHLChunk &source) :
     Inherited             (source                        ),
    _uiChunkId             (0                             ),
    _osgParametersCallbacks(source._osgParametersCallbacks),
    _oldParameterSize      (source._oldParameterSize      ),
    _userParameterCallbacks(source._userParameterCallbacks)
{
}

SHLChunk::~SHLChunk(void)
{
}

void SHLChunk::onCreate(const SHLChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&SHLChunk::handleGL, this, 
                            _1, _2, _3),
            boost::bind(&SHLChunk::handleDestroyGL, this, 
                            _1, _2, _3)
            ));

    _uiChunkId = _uiChunkCounter++;
}

void SHLChunk::onCreateAspect(const SHLChunk *createAspect,
                              const SHLChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

void SHLChunk::onDestroy(UInt32 uiId)
{
    Inherited::onDestroy(uiId);

    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

const StateChunkClass *SHLChunk::getClass(void) const
{
    return &_class;
}

UInt16 SHLChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*----------------------------- class specific ----------------------------*/

void SHLChunk::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    typedef SHLChunk Self;

    if(origin == ChangedOrigin::Child)
    {
        if(whichField & ParametersFieldMask)
        {
            Window::refreshGLObject(
                static_cast<const Self *>(this)->getGLId());
        }
    }
    else
    {
        if((whichField & VertexProgramFieldMask  ) ||
           (whichField & FragmentProgramFieldMask) ||
           (whichField & GeometryProgramFieldMask) ||
           (whichField & CgFrontEndFieldMask     ))
        {
            Window::reinitializeGLObject(
                static_cast<const Self *>(this)->getGLId());
        }
        
        if((whichField & ParametersFieldMask           ) ||
           (whichField & ProgramParameterNamesFieldMask ) ||
           (whichField & ProgramParameterValuesFieldMask)  )
        {
            Window::refreshGLObject(
                static_cast<const Self *>(this)->getGLId());
        }
    }

    Inherited::changed(whichField, origin, details);
}

void SHLChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SHLChunk NI" << std::endl;
}

/*! GL object handler
    create the program
*/
void SHLChunk::handleGL(DrawEnv                 *pEnv, 
                               UInt32                   osgid, 
                               Window::GLObjectStatusE  mode)
{
    Window *win = pEnv->getWindow();

    if(!win->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find "
                  "extension 'GL_ARB_shading_language_100'!\n"));

        win->setGLObjectId(getGLId(), 0);

        return;
    }

    // BUG this is not called for every window!
    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh)
    {
        if(mode != Window::needrefresh)
        {
            updateProgram(win);
        }

        updateProgramParameters(win);
        updateParameters(win,
                         *getMFParameters(),
                         true,
                         true /*mode != Window::needrefresh*/);
    }
    else
    {
        SWARNING << "SHLChunk("
                 << this
                 << "::handleGL: Illegal mode: "
                 << mode
                 << " for id "
                 << osgid
                 << std::endl;
    }
}

/*! GL object handler
    destroy it
*/
void SHLChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                               UInt32                   id, 
                               Window::GLObjectStatusE  mode)
{
    Window *win = pEnv->getWindow();

    if(!win->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find "
                  "extension 'GL_ARB_shading_language_100'!\n"));

        win->setGLObjectId(getGLId(), 0);

        return;
    }

    // BUG this is not called for every window!
    if(mode == Window::destroy)
    {
        // This is called after the destructor so getGLId() doesn't work
        // anymore!

        //printf("Window::destroy: %p %u %x\n", win, id,
        //       win->getGLObjectId(id));

        GLuint program = (GLuint) win->getGLObjectId(id);

        if(program != 0)
        {
            // get "glDeleteObjectARB" function pointer
            OSGGLDELETEOBJECTARBPROC deleteObject =
             (OSGGLDELETEOBJECTARBPROC) win->getFunction(_funcDeleteObject);

            deleteObject(program);
            win->setGLObjectId(id, 0);
        }
    }
    else if(mode == Window::finaldestroy)
    {
        ;//SWARNING << "Last program user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "SHLChunk("
                 << this
                 << "::handleGL: Illegal mode: "
                 << mode
                 << " for id "
                 << id
                 << std::endl;
    }
}

void SHLChunk::updateProgram(Window *win)
{
    //printf("SHLChunk::updateProgram glid %u\n", getGLId());

    // get "glCreateProgramObjectARB" function pointer
    OSGGLCREATEPROGRAMOBJECTARBPROC createProgramObject =
        (OSGGLCREATEPROGRAMOBJECTARBPROC)
            win->getFunction(_funcCreateProgramObject);

    // get "glDeleteObjectARB" function pointer
    OSGGLDELETEOBJECTARBPROC deleteObject =
        (OSGGLDELETEOBJECTARBPROC)
            win->getFunction(_funcDeleteObject);

    // get "glCreateShaderObjectARB" function pointer
    OSGGLCREATESHADEROBJECTARBPROC createShaderObject =
        (OSGGLCREATESHADEROBJECTARBPROC)
            win->getFunction(_funcCreateShaderObject);

    // get "glShaderSourceARB" function pointer
    OSGGLSHADERSOURCEARBPROC shaderSource =
        (OSGGLSHADERSOURCEARBPROC)
            win->getFunction(_funcShaderSource);

    // get "glCompileShaderARB" function pointer
    OSGGLCOMPILESHADERARBPROC compileShader =
        (OSGGLCOMPILESHADERARBPROC)
            win->getFunction(_funcCompileShader);

    // get "glGetObjectParameterivARB" function pointer
    OSGGLGETOBJECTPARAMETERIVARBPROC getObjectParameteriv =
        (OSGGLGETOBJECTPARAMETERIVARBPROC)
            win->getFunction(_funcGetObjectParameteriv);

    // get "glGetInfoLogARB" function pointer
    OSGGLGETINFOLOGARBPROC getInfoLog =
        (OSGGLGETINFOLOGARBPROC)
            win->getFunction(_funcGetInfoLog);

    // get "glAttachObjectARB" function pointer
    OSGGLATTACHOBJECTARBPROC attachObject =
        (OSGGLATTACHOBJECTARBPROC)
            win->getFunction(_funcAttachObject);

    // get "glLinkProgramARB" function pointer
    OSGGLLINKPROGRAMARBPROC linkProgram =
        (OSGGLLINKPROGRAMARBPROC)
            win->getFunction(_funcLinkProgram);

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject =
        (OSGGLUSEPROGRAMOBJECTARBPROC)
            win->getFunction(_funcUseProgramObject);

    GLuint program = (GLuint) win->getGLObjectId(getGLId());
    // delete old program.
    if(program != 0)
        deleteObject(program);
    program = createProgramObject();
    //printf("updateProgram create: %p %u %x\n", win, getGLId(), program);
    win->setGLObjectId(getGLId(), (UInt32) program);

    UInt32 vShader = 0;
    GLint has_vertex = 0;
    // reload programs
    if(!getVertexProgram().empty())
    {
        GLenum shader_type = GL_VERTEX_SHADER_ARB;
        if(getCgFrontEnd())
        {
            if(win->hasExtension(_cg_extension))
                shader_type = GL_CG_VERTEX_SHADER_EXT;
            else
                FWARNING(("EXT_Cg_shader extension not supported, using GLSL front end!\n"));
        }

        vShader = createShaderObject(shader_type);
        const char *source = getVertexProgram().c_str();
        shaderSource(vShader, 1, (const char **) &source, 0);

        int success = 0;
        compileShader(vShader);
        getObjectParameteriv(vShader, GL_OBJECT_COMPILE_STATUS_ARB, &has_vertex);

        if(has_vertex == 0)
        {
            char *debug;
            GLint debugLength;
            getObjectParameteriv(vShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);

            debug = new char[debugLength];
            getInfoLog(vShader, debugLength, &debugLength, debug);

            FFATAL(("Couldn't compile vertex program!\n%s\n", debug));
            delete [] debug;
            deleteObject(vShader);
        }
    }

    UInt32 fShader = 0;
    GLint has_fragment = 0;
    if(!getFragmentProgram().empty())
    {
        GLenum shader_type = GL_FRAGMENT_SHADER_ARB;
        if(getCgFrontEnd())
        {
            if(win->hasExtension(_cg_extension))
                shader_type = GL_CG_FRAGMENT_SHADER_EXT;
            else
                FWARNING(("EXT_Cg_shader extension not supported, using GLSL front end!\n"));
        }

        fShader = createShaderObject(shader_type);
        const char *source = getFragmentProgram().c_str();
        shaderSource(fShader, 1, (const char **) &source, 0);

        compileShader(fShader);
        getObjectParameteriv(fShader, GL_OBJECT_COMPILE_STATUS_ARB, &has_fragment);

        if(has_fragment == 0)
        {
            char *debug;
            GLint debugLength;
            getObjectParameteriv(fShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);

            debug = new char[debugLength];
            getInfoLog(fShader, debugLength, &debugLength, debug);

            FFATAL(("Couldn't compile fragment program!\n%s\n", debug));
            delete [] debug;
            deleteObject(fShader);
        }
    }

    UInt32 gShader = 0;
    GLint has_geometry = 0;
    // reload programs
    if(!getGeometryProgram().empty())
    {
        if(win->hasExtension(_geometry_extension))
        {
            GLenum shader_type = GL_GEOMETRY_SHADER_EXT;

            gShader = createShaderObject(shader_type);
            const char *source = getGeometryProgram().c_str();
            shaderSource(gShader, 1, (const char **) &source, 0);

            int success = 0;
            compileShader(gShader);
            getObjectParameteriv(gShader, GL_OBJECT_COMPILE_STATUS_ARB, &has_geometry);

            if(has_geometry == 0)
            {
                char *debug;
                GLint debugLength;
                getObjectParameteriv(gShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);

                debug = new char[debugLength];
                getInfoLog(gShader, debugLength, &debugLength, debug);

                FFATAL(("Couldn't compile geometry program!\n%s\n", debug));
                delete [] debug;
                deleteObject(gShader);
            }
        }
        else
        {
            FWARNING(("GL_EXT_geometry_shader4 extension not supported!\n"));
        }
    }
	
	updateProgramParameters(win);

    if(has_vertex || has_fragment || has_geometry)
    {
        if(has_vertex)
        {
            attachObject(program, vShader);
            // just flagged for deletion
            deleteObject(vShader);
        }

        if(has_fragment)
        {
            attachObject(program, fShader);
            // just flagged for deletion
            deleteObject(fShader);
        }

        if(has_geometry)
        {
            attachObject(program, gShader);
            // just flagged for deletion
            deleteObject(gShader);
        }

        linkProgram(program);

        GLint success = 0;
        getObjectParameteriv(program, GL_OBJECT_LINK_STATUS_ARB, &success);
        char *debug;
        GLint debugLength;
        getObjectParameteriv(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);
        if(debugLength > 0)
        {
            debug = new char[debugLength];
            debug[0] = 0;
            getInfoLog(program, debugLength, &debugLength, debug);
        }

        if(success)
        {
            if(debug != NULL && debug[0] != 0)
                FWARNING(("SHLChunk: link status: %s\n", debug));
        }
        else
        {
            if(debug != NULL && debug[0] != 0)
                FFATAL(("Couldn't link vertex and fragment program!\n%s\n", debug));
            deleteObject(program);
            win->setGLObjectId(getGLId(), 0);
        }
        if(debug != NULL)
            delete [] debug;
    }
    else
    {
        deleteObject(program);
        win->setGLObjectId(getGLId(), 0);
    }
    // update all parameter locations
    updateParameterLocations(win, *getMFParameters());
    // update all parameters.
    updateParameters(win, *getMFParameters());
}

void SHLChunk::updateParameterLocation(Window *win, GLuint program,
                                        const ShaderParameterPtr &parameter)
{
    if(program == 0)
    {
        FNOTICE(("SHLChunk::updateParameterLocation: program == 0!\n"
                 "This frame will probably be rendered wrong!\n"));
        return;
    }

    // get "glGetUniformLocationARB" function pointer
    OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation = (OSGGLGETUNIFORMLOCATIONARBPROC)
        win->getFunction(_funcGetUniformLocation);

    // as the location won't change after linking we can store them for speedup.
    parameter->setLocation(getUniformLocation(program, 
                                              parameter->getName().c_str()));
}

void SHLChunk::updateParameterLocations(
          Window                         *win,
    const MFUnrecChildShaderParameterPtr &parameters)
{
    GLuint program = (GLuint) win->getGLObjectId(getGLId());

    if(program == 0)
    {
        FNOTICE(("SHLChunk::updateParameterLocations: program == 0!\n"
                 "This frame will probably be rendered wrong!\n"));
        return;
    }

    if(parameters.empty())
        return;

    // get "glGetUniformLocationARB" function pointer
    OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation = (OSGGLGETUNIFORMLOCATIONARBPROC)
        win->getFunction(_funcGetUniformLocation);

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        // as the location won't change after linking we can store them for speedup.
        parameter->setLocation(getUniformLocation(program, parameter->getName().c_str()));
    }

    // force a update of the osg parameters.
    checkOSGParameters(true);
}

void SHLChunk::updateParameters(      
          Window                         *win,
    const MFUnrecChildShaderParameterPtr &parameters,
          bool                            useProgram, 
          bool                            force,
          bool                            keepProgramActive)
{
    GLuint program = (GLuint) win->getGLObjectId(getGLId());

    if(program == 0)
    {
        FNOTICE(("SHLChunk::updateParameters: program == 0!\n"
                 "This frame will probably be rendered wrong!\n"));
        return;
    }

    checkOSGParameters();

    if(parameters.empty())
        return;

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject =
        (OSGGLUSEPROGRAMOBJECTARBPROC)
            win->getFunction(_funcUseProgramObject);

    if(useProgram)
        useProgramObject(program);

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        // ignore special osg parameters
        if(parameter->getName().size() > 3 &&
           parameter->getName()[0] == 'O' &&
           parameter->getName()[1] == 'S' &&
           parameter->getName()[2] == 'G')
        {
            continue;
        }

        // works also but is not possible with a switch and a switch is much faster.
        //UInt16 groupid = parameter->getType().getGroupId();
        //if(groupid == ShaderParameterInt::getClassType().getGroupId())

        if(!force)
        {
            if(!parameter->hasChanged())
                continue;
            parameter->resetChanged();
        }

        //printf("seeting parameter: '%s'\n", parameter->getName().c_str());

        switch(parameter->getTypeId())
        {
            case ShaderParameter::SHPTypeBool:
            {
                ShaderParameterBoolPtr p =
                    dynamic_cast<ShaderParameterBoolPtr>(parameter);

                // get "glUniform1iARB" function pointer
                OSGGLUNIFORM1IARBPROC uniform1i =
                    (OSGGLUNIFORM1IARBPROC)
                        win->getFunction(_funcUniform1i);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform1i(p->getLocation(), (GLint) p->getValue());
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeInt:
            {
                ShaderParameterIntPtr p =
                    dynamic_cast<ShaderParameterIntPtr>(parameter);

                // get "glUniform1iARB" function pointer
                OSGGLUNIFORM1IARBPROC uniform1i =
                    (OSGGLUNIFORM1IARBPROC)
                        win->getFunction(_funcUniform1i);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform1i(p->getLocation(), p->getValue());
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeReal:
            {
                ShaderParameterRealPtr p =
                    dynamic_cast<ShaderParameterRealPtr>(parameter);

                // get "glUniform1fARB" function pointer
                OSGGLUNIFORM1FARBPROC uniform1f =
                    (OSGGLUNIFORM1FARBPROC)
                        win->getFunction(_funcUniform1f);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform1f(p->getLocation(), p->getValue());
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeVec2f:
            {
                ShaderParameterVec2fPtr p =
                    dynamic_cast<ShaderParameterVec2fPtr>(parameter);

                // get "glUniform2fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform2fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform2fv);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform2fv(
                        p->getLocation(), 1, 
                        const_cast<Real32 *>(p->getValue().getValues()));
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeVec3f:
            {
                ShaderParameterVec3fPtr p =
                    dynamic_cast<ShaderParameterVec3fPtr>(parameter);

                // get "glUniform3fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform3fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform3fv);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform3fv(p->getLocation(), 1, 
                               const_cast<Real32 *>(p->getValue().getValues()));
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeVec4f:
            {
                ShaderParameterVec4fPtr p =
                    dynamic_cast<ShaderParameterVec4fPtr>(parameter);

                // get "glUniform4fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform4fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform4fv);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform4fv(p->getLocation(), 1, 
                               const_cast<Real32 *>(p->getValue().getValues()));
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeMatrix:
            {
                ShaderParameterMatrixPtr p =
                    dynamic_cast<ShaderParameterMatrixPtr>(parameter);

                // get "glUniformMatrix4fvARB" function pointer
                OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
                    (OSGGLUNIFORMMATRIXFVARBPROC)
                        win->getFunction(_funcUniformMatrix4fv);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniformMatrix4fv(p->getLocation(), 1, GL_FALSE, 
                                     const_cast<Real32 *>(p->getValue().getValues()));
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypePnt2f:
            {
                ShaderParameterPnt2fPtr p =
                    dynamic_cast<ShaderParameterPnt2fPtr>(parameter);

                // get "glUniform2fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform2fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform2fv);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform2fv(
                        p->getLocation(), 1, 
                        const_cast<Real32 *>(p->getValue().getValues()));
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypePnt3f:
            {
                ShaderParameterPnt3fPtr p =
                    dynamic_cast<ShaderParameterPnt3fPtr>(parameter);

                // get "glUniform3fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform3fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform3fv);

                if(p->getLocation() == -1)
                {
                    updateParameterLocation(win, program, p);
                }
                if(p->getLocation() != -1)
                {
                    uniform3fv(p->getLocation(), 1, 
                               const_cast<Real32 *>(p->getValue().getValues()));
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
                              p->getName().c_str()));
                }
            }
            break;



            // arrays
            case ShaderParameter::SHPTypeMInt:
            {
                ShaderParameterMIntPtr p = 
                    dynamic_cast<ShaderParameterMIntPtr>(parameter);
                // get "glUniform1ivARB" function pointer
                OSGGLUNIFORMIVARBPROC uniform1iv = (OSGGLUNIFORMIVARBPROC)
                    win->getFunction(_funcUniform1iv);
    
                //printf("setting: %s %d\n", p->getName().c_str(), p->getValue());
                if(p->getLocation() == -1)
                    updateParameterLocation(win, program, p);
                if(p->getLocation() != -1 && !p->getMFValue()->empty())
		  ; // XXX uniform1iv(p->getLocation(), p->getValue().size(), &p->getValue()[0]);
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeMReal:
            {
                ShaderParameterMRealPtr p = 
                    dynamic_cast<ShaderParameterMRealPtr>(parameter);
                // get "glUniform1fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform1fv = (OSGGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform1fv);

                //printf("setting: %s %f\n", p->getName().c_str(), p->getValue());
                if(p->getLocation() == -1)
                    updateParameterLocation(win, program, p);
                if(p->getLocation() != -1 && !p->getMFValue()->empty())
                    uniform1fv(p->getLocation(), 
                               p->getMFValue()->size(), 
                               const_cast<Real32 *>(
                                   &(p->getMFValue()->front())));
                else
                {
                    FWARNING(("Unknown parameter '%s'!\n", 
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeMVec2f:
            {
                ShaderParameterMVec2fPtr p = 
                    dynamic_cast<ShaderParameterMVec2fPtr>(parameter);
                // get "glUniform2fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform2fv = (OSGGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform2fv);

                if(p->getLocation() == -1)
                    updateParameterLocation(win, program, p);

                if(p->getLocation() != -1 && !p->getMFValue()->empty())
                    uniform2fv(p->getLocation(), 
                               p->getMFValue()->size(), 
                               const_cast<Real32 *>(
                                   (*(p->getMFValue()))[0].getValues()));
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeMVec3f:
            {
                ShaderParameterMVec3fPtr p = 
                    dynamic_cast<ShaderParameterMVec3fPtr>(parameter);
                // get "glUniform3fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform3fv = (OSGGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform3fv);

                if(p->getLocation() == -1)
                    updateParameterLocation(win, program, p);
                if(p->getLocation() != -1 && !p->getMFValue()->empty())
                    uniform3fv(p->getLocation(), 
                               p->getMFValue()->size(), 
                               const_cast<Real32 *>(
                                   (*(p->getMFValue()))[0].getValues()));
                else
                {
                    FWARNING(("Unknown parameter '%s'!\n", 
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeMVec4f:
            {
                ShaderParameterMVec4fPtr p = 
                    dynamic_cast<ShaderParameterMVec4fPtr>(parameter);
                // get "glUniform4fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform4fv = (OSGGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform4fv);

                if(p->getLocation() == -1)
                    updateParameterLocation(win, program, p);
                if(p->getLocation() != -1 && !p->getMFValue()->empty())
                    uniform4fv(p->getLocation(), 
                               p->getMFValue()->size(), 
                               const_cast<Real32 *>(
                                   (*(p->getMFValue()))[0].getValues()));
                else
                {
                    FWARNING(("Unknown parameter '%s'!\n", 
                              p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeMMatrix:
            {
                ShaderParameterMMatrixPtr p = 
                    dynamic_cast<ShaderParameterMMatrixPtr>(parameter);
                // get "glUniformMatrix4fvARB" function pointer
                OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
                    win->getFunction(_funcUniformMatrix4fv);

                if(p->getLocation() == -1)
                    updateParameterLocation(win, program, p);
                if(p->getLocation() != -1 && !p->getMFValue()->empty())
                    uniformMatrix4fv(p->getLocation(), 
                                     p->getMFValue()->size(), 
                                     GL_FALSE, 
                                     const_cast<Real32 *>(
                                         (*(p->getMFValue()))[0].getValues()));
                else
                {
                    FWARNING(("Unknown parameter '%s'!\n", 
                              p->getName().c_str()));
                }
            }
            break;
            default:
                FWARNING(("Parameter '%s' has unknown tpye %d!\n",
                          parameter->getName().c_str(),
                          parameter->getTypeId()));
            break;
        }
    }

    if(useProgram && !keepProgramActive)
        useProgramObject(0);
}

void SHLChunk::updateProgramParameters(Window *win)
{
    if(!win->hasExtension(_geometry_extension))
        return;

    GLuint program = (GLuint) win->getGLObjectId(getGLId());

    if(program == 0)
    {
        FNOTICE(("SHLChunk::updateParameters: program == 0!\n"
                 "This frame will probably be rendered wrong!\n"));
        return;
    }

    // get "glProgramParameteriEXT" function pointer
    OSGGLPROGRAMPARAMETERIEXTPROC programParameteri =
        (OSGGLPROGRAMPARAMETERIEXTPROC) win->getFunction(_funcProgramParameteri);

    // set program parameters.
    const MFGLenum *ppnames  = getMFProgramParameterNames();
    const MFUInt32 *ppvalues = getMFProgramParameterValues();

    for(UInt32 i = 0; i < ppnames->size(); ++i)
    {
        if(i < ppvalues->size()) 
        {
            programParameteri(program, (*ppnames)[i], (*ppvalues)[i]);
		}
    }
}

/*! Method to check for OSGParameters and add their callbacks
to the callback list if found.
*/
void SHLChunk::checkOSGParameters(bool force)
{
    // ok this can go wrong if you sub and add a parameter
    // between one begin/endEditCP ...
    if(!force && getMFParameters()->size() == _oldParameterSize)
        return;

    _oldParameterSize = getMFParameters()->size();

    _osgParametersCallbacks.clear();
    const MFUnrecChildShaderParameterPtr *parameters = getMFParameters();

    for(UInt32 i = 0; i < parameters->size(); ++i)
    {
        //
        // IMPORTANT: If you add a parameter here, add documentation for it
        //            in the class docs at the top of this file
        //
        ShaderParameterPtr parameter = (*parameters)[i];
        if(parameter->getName().size() > 3 &&
           parameter->getName()[0] == 'O' &&
           parameter->getName()[1] == 'S' &&
           parameter->getName()[2] == 'G')
        {
             if(parameter->getName() == "OSGWorldMatrix")
            {
                // .net compiler needs this workaround in opt mode ...
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateWorldMatrix;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGInvWorldMatrix")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateInvWorldMatrix;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGTransInvWorldMatrix")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateTransInvWorldMatrix;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGCameraOrientation")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateCameraOrientation;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGCameraPosition")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateCameraPosition;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGViewMatrix")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateViewMatrix;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGInvViewMatrix")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateInvViewMatrix;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGStereoLeftEye")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateStereoLeftEye;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGClusterId")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateClusterId;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGActiveLightsMask")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateActiveLightsMask;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight0Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight0Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight1Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight1Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight2Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight2Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight3Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight3Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight4Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight4Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight5Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight5Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight6Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight6Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else if(parameter->getName() == "OSGLight7Active")
            {
                parametercbfp oldfp = NULL;
                osgparametercbfp fp = updateLight7Active;
                _osgParametersCallbacks.push_back(
                    std::make_pair(std::make_pair(oldfp, fp), parameter));
            }
            else
            {
                // check user parameter callbacks.
                userParameterCallbacksMap::iterator it =
                    _userParameterCallbacks.find(parameter->getName());

                if(it != _userParameterCallbacks.end())
                {
                    parametercbfp oldfp = (*it).second.first;
                    osgparametercbfp fp = (*it).second.second;

                    _osgParametersCallbacks.push_back(
                        std::make_pair(std::make_pair(oldfp, fp), parameter));
                }
                else
                {
                    FWARNING(("SHLChunk::checkOSGParameters : unknown "
                              "osg paramter '%s'\n",
                              parameter->getName().c_str()));
                }
            }
        }
    }
}

void SHLChunk::addParameterCallback(const char *name, parametercbfp fp)
{
    if(name == NULL || fp == NULL)
        return;

//    std::string szName(name);

    osgparametercbfp nullfp = NULL;

    setUniformParameter(name, 0);

    _userParameterCallbacks.insert(
        std::make_pair(name, std::make_pair(fp, nullfp)));
}

void SHLChunk::addParameterCallback(const char *name, osgparametercbfp fp)
{
    if(name == NULL || fp == NULL)
        return;

//    std::string szName(name);

    parametercbfp nullfp = NULL;

    setUniformParameter(name, 0);
    _userParameterCallbacks.insert(
        std::make_pair(name, std::make_pair(nullfp, fp)));
}

void SHLChunk::setParameterCallback(parametercbfp fp)
{
    _userParametersCallback = fp;
}

void SHLChunk::addProgramParameter(GLenum name, UInt32 value)
{
    editMFProgramParameterNames ()->push_back(name );
    editMFProgramParameterValues()->push_back(value);
}

void SHLChunk::subProgramParameter(GLenum name)
{
    MFGLenum *ppnames  = editMFProgramParameterNames ();
    MFUInt32 *ppvalues = editMFProgramParameterValues();

    for(UInt32 i = 0; i < ppnames->size(); ++i)
    {
        if((*ppnames)[i] == name && i < ppvalues->size())
        {
            ppnames ->erase(ppnames ->begin() + i);
            ppvalues->erase(ppvalues->begin() + i);

            break;
        }
    }
}

void SHLChunk::setProgramParameter(GLenum name, UInt32 value)
{
    // remove old one.
    subProgramParameter(name);
    // add new one.
    addProgramParameter(name, value);
}

UInt32 SHLChunk::getProgramParameter(GLenum name)
{
    const MFGLenum *ppnames  = getMFProgramParameterNames();
    const MFUInt32 *ppvalues = getMFProgramParameterValues();

    for(UInt32 i = 0; i < ppnames->size(); ++i)
    {
        if((*ppnames)[i] == name && i < ppvalues->size())
            return (*ppvalues)[i];
    }

    FWARNING(("SHLChunk::getProgramParameter : Couldn't find program "
              "parameter %u!\n", name));

    return 0;
}

std::vector<std::pair<GLenum, UInt32> > SHLChunk::getProgramParameters(void)
{
    std::vector<std::pair<GLenum, UInt32> > parameters;

    const MFGLenum *ppnames  = getMFProgramParameterNames();
    const MFUInt32 *ppvalues = getMFProgramParameterValues();

    for(UInt32 i = 0; i < ppnames->size(); ++i)
    {
        if(i < ppvalues->size())
        {
            parameters.push_back(std::make_pair((*ppnames)[i], 
                                                (*ppvalues)[i]));
        }
    }

    return parameters;
}

void SHLChunk::clearProgramParameters(void)
{
    editMFProgramParameterNames ()->clear();
    editMFProgramParameterValues()->clear();
}

void SHLChunk::updateOSGParameters(DrawEnv *pEnv, 
                                   GLuint program,
                                   bool update)
{
    if(_osgParametersCallbacks.empty())
        return;

    // get "glGetUniformLocationARB" function pointer
    OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation =
        (OSGGLGETUNIFORMLOCATIONARBPROC)
            pEnv->getWindow()->getFunction(_funcGetUniformLocation);

    if(_userParametersCallback != NULL)
        _userParametersCallback(getUniformLocation, pEnv, program);

    if(_osgParametersCallbacks.empty())
        return;

    for(UInt32 i=0;i<_osgParametersCallbacks.size();++i)
    {
        parametercbfp oldfp = _osgParametersCallbacks[i].first.first;
        osgparametercbfp fp = _osgParametersCallbacks[i].first.second;
        if(oldfp != NULL)
        {
            oldfp(getUniformLocation, pEnv, program);
        }
        else if(fp != NULL)
        {
            // ok if update is true this means it was called from update()
            // in this case we only need set parameters which use the
            // object transformation (top_matrix())
            ShaderParameterPtr parameter = _osgParametersCallbacks[i].second;
            parameter->setFlags(update ? ShaderParameter::SHPFlagUpdate :
                                ShaderParameter::SHPFlagNone);
            fp(parameter, pEnv, program);
        }
    }
}

void SHLChunk::updateWorldMatrix(const ShaderParameterPtr &parameter,
                                 DrawEnv *pEnv, GLuint program)
{
#ifdef CHECK_OSG_PARRAM
    // this parameter needs to be updated for each object because it
    // is dependend from the object transformation!
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateWorldMatrix : Can't update OSGWorldMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        m = ra->top_matrix();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniformMatrix4fv(parameter->getLocation(), 1, GL_FALSE, m.getValues());
#endif
}

void SHLChunk::updateInvWorldMatrix(const ShaderParameterPtr &parameter,
                                    DrawEnv *pEnv, GLuint program)
{
#ifdef CHECK_OSG_PARRAM
    // this parameter needs to be updated for each object because it
    // is dependend from the object transformation!
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateInvWorldMatrix : Can't update OSGInvWorldMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        m = ra->top_matrix();
    m.invert();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniformMatrix4fv(parameter->getLocation(), 1, GL_FALSE, m.getValues());
#endif
}

void SHLChunk::updateTransInvWorldMatrix(const ShaderParameterPtr &parameter,
                                         DrawEnv *pEnv, GLuint program)
{
#ifdef CHECK_OSG_PARRAM
    // this parameter needs to be updated for each object because it
    // is dependend from the object transformation!
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateTransInvWorldMatrix : Can't update OSGTransInvWorldMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        m = ra->top_matrix();
    m.invert();
    m.transpose();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniformMatrix4fv(parameter->getLocation(), 1, GL_FALSE, m.getValues());
#endif
}

void SHLChunk::updateCameraOrientation(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    // the parameter is not object transformation dependend so we can leave now.
    if(parameter->getFlags() & ShaderParameter::SHPFlagUpdate)
        return;

    Matrix m = pEnv->getCameraToWorld();

    m[3].setValues(0, 0, 0, 1);

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
        (OSGGLUNIFORMMATRIXFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniformMatrix4fv);

    if(parameter->getLocation() == -1)
        updateParameterLocation(pEnv->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniformMatrix4fv(parameter->getLocation(), 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateCameraPosition(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    if(parameter->getFlags() & ShaderParameter::SHPFlagUpdate)
        return;

    Matrix m = pEnv->getCameraToWorld();

    Vec3f cameraPos(m[3][0], m[3][1], m[3][2]);

    // get "glUniform3fvARB" function pointer
    OSGGLUNIFORMFVARBPROC uniform3fv =
        (OSGGLUNIFORMFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform3fv);

    if(parameter->getLocation() == -1)
        updateParameterLocation(pEnv->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform3fv(parameter->getLocation(), 1, cameraPos.getValues());
}

void SHLChunk::updateViewMatrix(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    if(parameter->getFlags() & ShaderParameter::SHPFlagUpdate)
        return;

    Matrix m = pEnv->getCameraViewing();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
        (OSGGLUNIFORMMATRIXFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniformMatrix4fv);

    if(parameter->getLocation() == -1)
        updateParameterLocation(pEnv->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniformMatrix4fv(parameter->getLocation(), 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateInvViewMatrix(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    if(parameter->getFlags() & ShaderParameter::SHPFlagUpdate)
        return;

    Matrix m = pEnv->getCameraToWorld();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
        (OSGGLUNIFORMMATRIXFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniformMatrix4fv);

    if(parameter->getLocation() == -1)
        updateParameterLocation(pEnv->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniformMatrix4fv(parameter->getLocation(), 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateStereoLeftEye(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    if(parameter->getFlags() & ShaderParameter::SHPFlagUpdate)
        return;

    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateStereoLeftEye : Can't update OSGStereoLeftEye"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    // ok -1 is mono
    Int32 leftEye = -1;
    // now search for a stereo camera decorator and get the eye.
    CameraPtr camera(*action->getCamera());
    CameraDecoratorPtr decorator = CameraDecoratorPtr::dcast(camera);
    while(decorator != NullFC)
    {
        StereoCameraDecoratorPtr stereoDecorator = StereoCameraDecoratorPtr::dcast(decorator);
        if(stereoDecorator != NullFC)
        {
            if(stereoDecorator->getLeftEye())
                leftEye = 1;
            else
                leftEye = 0;
            break;
        }
        decorator = CameraDecoratorPtr::dcast(decorator->getDecoratee());
    }

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), leftEye);
#endif
}

void SHLChunk::setClusterId(Int32 id)
{
    _clusterId = id;
}

void SHLChunk::updateClusterId(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    if(parameter->getFlags() & ShaderParameter::SHPFlagUpdate)
        return;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    if(parameter->getLocation() == -1)
        updateParameterLocation(pEnv->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) _clusterId);
}

void SHLChunk::updateActiveLightsMask(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask());
#endif
}

void SHLChunk::updateLight0Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 1);
#endif
}

void SHLChunk::updateLight1Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 2);
#endif
}

void SHLChunk::updateLight2Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 4);
#endif
}

void SHLChunk::updateLight3Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 8);
#endif
}

void SHLChunk::updateLight4Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 16);
#endif
}

void SHLChunk::updateLight5Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 32);
#endif
}

void SHLChunk::updateLight6Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 64);
#endif
}

void SHLChunk::updateLight7Active(
    const ShaderParameterPtr &parameter,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);
    if(parameter->getLocation() == -1)
        updateParameterLocation(action->getWindow(), program, parameter);
    if(parameter->getLocation() != -1)
        uniform1i(parameter->getLocation(), (GLint) ract->getActiveLightsMask() & 128);
#endif
}

/*------------------------------ State ------------------------------------*/

void SHLChunk::update(DrawEnv *pEnv)
{
    pEnv->getWindow()->validateGLObject(getGLId(), pEnv);

    GLuint program = (GLuint) pEnv->getWindow()->getGLObjectId(getGLId());
    if(program == 0)
        return;

    updateOSGParameters(pEnv, program, true);
}

void SHLChunk::activate(DrawEnv *pEnv, UInt32 /*idx*/)
{
    //printf("SHLChunk::activate : %p\n", action->getWindow());
    pEnv->getWindow()->validateGLObject(getGLId(), pEnv);

    GLuint program = (GLuint) pEnv->getWindow()->getGLObjectId(getGLId());

    if(program == 0)
        return;


    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject =
        (OSGGLUSEPROGRAMOBJECTARBPROC)
            pEnv->getWindow()->getFunction(_funcUseProgramObject);

    useProgramObject(program);

    updateOSGParameters(pEnv, program);

#if 0
    updateParameters(pEnv->getWindow(), getParameters(),
                     false,  // don't use program
                     false,  // don't force updates
                     true);  // keep the program active
#endif

    if(getPointSize())
    {
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }

    pEnv->incNumShaderChanges();
}

void SHLChunk::changeFrom(DrawEnv    *pEnv,
                          StateChunk *old_chunk,
                          UInt32 /*idx*/)
{
    SHLChunk *old = dynamic_cast<SHLChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "SHLChunk::changeFrom: caught non-SHLChunk!\n"));
        return;
    }

    // SHLChunk didn't change so do nothing.
    if(old == this)
        return;

    pEnv->getWindow()->validateGLObject(getGLId(), pEnv);

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject =
        (OSGGLUSEPROGRAMOBJECTARBPROC)
            pEnv->getWindow()->getFunction(_funcUseProgramObject);

    GLuint program = (GLuint) pEnv->getWindow()->getGLObjectId(getGLId());

    if(program != 0)
    {
        useProgramObject(program);
        updateOSGParameters(pEnv, program);
#if 0
        updateParameters(pEnv->getWindow(), getParameters(),
                     false,  // don't use program
                     false,  // don't force updates
                     true);  // keep the program active
#endif

        if(getPointSize())
        {
            if(!old->getPointSize())
                glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
        }
        else
        {
            if(old->getPointSize())
                glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
        }
    }
    else
    {
        if(pEnv->getWindow()->getGLObjectId(old->getGLId()) != 0)
            useProgramObject(0);
    }

    pEnv->incNumShaderChanges();
}


void SHLChunk::deactivate(DrawEnv *pEnv, UInt32 /*idx*/)
{
    if(pEnv->getWindow()->getGLObjectId(getGLId()) == 0)
        return;

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject =
        (OSGGLUSEPROGRAMOBJECTARBPROC)
            pEnv->getWindow()->getFunction(_funcUseProgramObject);

    useProgramObject(0);

    if(getPointSize())
    {
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }
}

/*-------------------------- Comparison -----------------------------------*/

Real32 SHLChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool SHLChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool SHLChunk::operator == (const StateChunk &other) const
{
    SHLChunk const *tother = dynamic_cast<SHLChunk const*>(&other);

    if(!tother)
        return false;

    if(getVertexProgram       () != tother->getVertexProgram  ()        ||
       getFragmentProgram     () != tother->getFragmentProgram()        ||
       getMFParameters()->size() != tother->getMFParameters   ()->size() )
    {
        return false;
    }

    return true;
}

bool SHLChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}
