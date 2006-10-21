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

#include "OSGSHLChunk.h"

OSG_USING_NAMESPACE

/*! \class OSG::SHLChunk

This chunk provides support for GLSL.  It provides a wrapper for setting vertex
and fragment programs.  Because it is derived from OSG::ShaderParameter it also
allows setting uniform parameters for the shaders.

The primary way to use this class is to:

  - set/getVertexProgram
  - set/getFragmentProgram
  - setUniform


To help with OpenSG application development this chunk provides support for
derived uniform parameters.  The uniform parameters all start with the
characters "OSG" and are derived from the internal state of OpenSG in some way.
It is possible for users to make use of this system to add their own derived
"OSG" parameters using a user callback.  (see addParameterCallback)

To use these parameters, simply call setUniform() with the name of the parameter
and set it to some default value of the correct type.  After that point OpenSG
will ensure that the parameter is automatically updated each frame.

The derived parameters supported by default are:
   - OSGCameraOrientation: Camera orientation matrix in world coords.
   - OSGCameraPosition: Camera position vec3 in world coordinates.
   - OSGViewMatrix: Camera viewing matrix in world coordinates.
   - OSGInvViewMatrix: Inverse camera viewing matrix in world coordinates.
   - OSGStereoLeftEye: Integer: -1 mono, 1 left eye, 0 right eye
   - OSGClusterId: The int id set with setClusterId()
   - OSGActiveLightsMast: The active lights mast from the render action.
   - OSGLight0Active ... OSGLight7Active: int/bool flag of wether the light is active.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SHLChunk::_class("SHL", 1, 30);

UInt32 SHLChunk::_shl_extension            = Window::invalidExtensionID;
UInt32 SHLChunk::_cg_extension             = Window::invalidExtensionID;

UInt32 SHLChunk::_funcCreateProgramObject  = Window::invalidFunctionID;
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
UInt32 SHLChunk::_funcUniform2iv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform3iv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform4iv           = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniform1f            = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform2fv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform3fv           = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform4fv           = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniformMatrix4fv     = Window::invalidFunctionID;

UInt32 SHLChunk::_funcGetUniformiv         = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetUniformfv         = Window::invalidFunctionID;

Int32 SHLChunk::_clusterId = -1;

volatile UInt16 SHLChunk::_uiChunkCounter = 1;

// prototypes

typedef GLuint  (OSG_APIENTRY * OSGGLCREATEPROGRAMOBJECTARBPROC) (void);
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

        _funcCreateProgramObject =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCreateProgramObjectARB",
                _shl_extension);

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

    SHLChunkPtr tmpPtr = Inherited::constructPtr<SHLChunk>(this);;

    setGLId(
        Window::registerGLObject(
            boost::bind(&SHLChunk::handleGL, tmpPtr, _1, _2),
            1));

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

void SHLChunk::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    if((whichField & VertexProgramFieldMask) ||
       (whichField & FragmentProgramFieldMask) ||
       (whichField & CgFrontEndFieldMask))
    {
        Window::reinitializeGLObject(getGLId());
    }

    if(whichField & ParametersFieldMask)
    {
        Window::refreshGLObject(getGLId());
    }

    Inherited::changed(whichField, origin);
}

void SHLChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SHLChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/

void SHLChunk::handleGL(DrawEnv *pEnv, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    Window *win = pEnv->getWindow();

    Window::unpackIdStatus(idstatus, id, mode);

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
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh)
    {
        if(mode != Window::needrefresh)
        {
            updateProgram(win);
        }

        updateParameters(win,
                         getParameters(),
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

    if(has_vertex || has_fragment)
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

        linkProgram(program);

        GLint success = 0;
        getObjectParameteriv(program, GL_OBJECT_LINK_STATUS_ARB, &success);
        if(!success)
        {
            char *debug;
            GLint debugLength;
            getObjectParameteriv(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);

            debug = new char[debugLength];
            getInfoLog(program, debugLength, &debugLength, debug);

            FFATAL(("Couldn't link vertex and fragment program!\n%s\n", debug));
            delete [] debug;
            deleteObject(program);
            win->setGLObjectId(getGLId(), 0);
        }
    }
    else
    {
        deleteObject(program);
        win->setGLObjectId(getGLId(), 0);
    }
    // update all parameters.
    updateParameters(win, getParameters());
}

void SHLChunk::updateParameters(Window *win,
                                const MFShaderParameterPtr &parameters,
                                bool useProgram, bool force,
                                bool keepProgramActive)
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

    // get "glGetUniformLocationARB" function pointer
    OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation =
        (OSGGLGETUNIFORMLOCATIONARBPROC)
            win->getFunction(_funcGetUniformLocation);

    // just a example showing how to get parameter values.
#if 0
    // get "glGetUniformfvARB" function pointer
    OSGGLGETUNIFORMFVARBPROC getUniformfv =
        (OSGGLGETUNIFORMFVARBPROC)
            win->getFunction(_funcGetUniformfv);

    GLfloat values[2];
    getUniformfv(program, location, values);
#endif

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
                    cast_dynamic<ShaderParameterBoolPtr>(parameter);

                // get "glUniform1iARB" function pointer
                OSGGLUNIFORM1IARBPROC uniform1i =
                    (OSGGLUNIFORM1IARBPROC)
                        win->getFunction(_funcUniform1i);

                GLint location = getUniformLocation(program,
                                                    p->getName().c_str());
                if(location != -1)
                {
                    uniform1i(location, (GLint) p->getValue());
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
                    cast_dynamic<ShaderParameterIntPtr>(parameter);

                // get "glUniform1iARB" function pointer
                OSGGLUNIFORM1IARBPROC uniform1i =
                    (OSGGLUNIFORM1IARBPROC)
                        win->getFunction(_funcUniform1i);

                GLint location = getUniformLocation(program,
                                                    p->getName().c_str());
                if(location != -1)
                {
                    uniform1i(location, p->getValue());
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
                    cast_dynamic<ShaderParameterRealPtr>(parameter);

                // get "glUniform1fARB" function pointer
                OSGGLUNIFORM1FARBPROC uniform1f =
                    (OSGGLUNIFORM1FARBPROC)
                        win->getFunction(_funcUniform1f);

                GLint location = getUniformLocation(program,
                                                    p->getName().c_str());
                if(location != -1)
                {
                    uniform1f(location, p->getValue());
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
                    cast_dynamic<ShaderParameterVec2fPtr>(parameter);

                // get "glUniform2fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform2fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform2fv);

                GLint location = getUniformLocation(program,
                                                    p->getName().c_str());
                if(location != -1)
                {
                    uniform2fv(location,
                               1,
                               const_cast<Real32 *>(
                                   p->getValue().getValues()));
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
                    cast_dynamic<ShaderParameterVec3fPtr>(parameter);

                // get "glUniform3fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform3fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform3fv);

                GLint location = getUniformLocation(program,
                                                    p->getName().c_str());
                if(location != -1)
                {
                    uniform3fv(location,
                               1,
                               const_cast<Real32 *>(
                                   p->getValue().getValues()));
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
                    cast_dynamic<ShaderParameterVec4fPtr>(parameter);

                // get "glUniform4fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform4fv =
                    (OSGGLUNIFORMFVARBPROC)
                        win->getFunction(_funcUniform4fv);

                GLint location = getUniformLocation(program,
                                                    p->getName().c_str());
                if(location != -1)
                {
                    uniform4fv(location,
                               1,
                               const_cast<Real32 *>(
                                   p->getValue().getValues()));
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
                    cast_dynamic<ShaderParameterMatrixPtr>(parameter);

                // get "glUniformMatrix4fvARB" function pointer
                OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
                    (OSGGLUNIFORMMATRIXFVARBPROC)
                        win->getFunction(_funcUniformMatrix4fv);

                GLint location = getUniformLocation(program,
                                                    p->getName().c_str());
                if(location != -1)
                {
                    uniformMatrix4fv(location,
                                     1,
                                     GL_FALSE,
                                     const_cast<Real32 *>(
                                         p->getValue().getValues()));
                }
                else
                {
                    FWARNING(("Parameter '%s' not found in active uniform variables of the shader!\n",
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

/*! Method to check for OSGParameters and add their callbacks
to the callback list if found.
*/
void SHLChunk::checkOSGParameters(void)
{
    // ok this can go wrong if you sub and add a parameter
    // between one begin/endEditCP ...
    if(getParameters().size() == _oldParameterSize)
        return;
    _oldParameterSize = getParameters().size();

    _osgParametersCallbacks.clear();
    const MFShaderParameterPtr &parameters = getParameters();
    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        //
        // IMPORTANT: If you add a parameter here, add documentation for it
        //            in the class docs at the top of this file
        //
        ShaderParameterPtr parameter = parameters[i];
        if(parameter->getName().size() > 3 &&
           parameter->getName()[0] == 'O' &&
           parameter->getName()[1] == 'S' &&
           parameter->getName()[2] == 'G')
        {
            if(parameter->getName() == "OSGCameraOrientation")
            {
                // .net compiler needs this workaround in opt mode ...
                paramtercbfp fp = updateCameraOrientation;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGCameraPosition")
            {
                paramtercbfp fp = updateCameraPosition;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGViewMatrix")
            {
                paramtercbfp fp = updateViewMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGInvViewMatrix")
            {
                paramtercbfp fp = updateInvViewMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGStereoLeftEye")
            {
                paramtercbfp fp = updateStereoLeftEye;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGClusterId")
            {
                paramtercbfp fp = updateClusterId;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGActiveLightsMask")
            {
                paramtercbfp fp = updateActiveLightsMask;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight0Active")
            {
                paramtercbfp fp = updateLight0Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight1Active")
            {
                paramtercbfp fp = updateLight1Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight2Active")
            {
                paramtercbfp fp = updateLight2Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight3Active")
            {
                paramtercbfp fp = updateLight3Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight4Active")
            {
                paramtercbfp fp = updateLight4Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight5Active")
            {
                paramtercbfp fp = updateLight5Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight6Active")
            {
                paramtercbfp fp = updateLight6Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight7Active")
            {
                paramtercbfp fp = updateLight7Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else
            {
                // check user parameter callbacks.
                userParameterCallbacksMap::iterator it =
                    _userParameterCallbacks.find(parameter->getName());

                if(it != _userParameterCallbacks.end())
                {
                    paramtercbfp fp = (*it).second;
                    _osgParametersCallbacks.push_back(fp);
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

void SHLChunk::addParameterCallback(const char *name, paramtercbfp fp)
{
    if(name == NULL)
        return;

//    std::string szName(name);

    setUniformParameter(name, 0);
    _userParameterCallbacks.insert(std::make_pair<std::string,
                                                  paramtercbfp>(name, fp));
}

void SHLChunk::updateOSGParameters(DrawEnv *pEnv, GLuint program)
{
    if(_osgParametersCallbacks.empty())
        return;

    // get "glGetUniformLocationARB" function pointer
    OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation =
        (OSGGLGETUNIFORMLOCATIONARBPROC)
            pEnv->getWindow()->getFunction(_funcGetUniformLocation);

    for(UInt32 i=0;i<_osgParametersCallbacks.size();++i)
        _osgParametersCallbacks[i](getUniformLocation, pEnv, program);
}

void SHLChunk::updateCameraOrientation(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    Matrix m = pEnv->getCameraToWorld();

    m[3].setValues(0, 0, 0, 1);

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
        (OSGGLUNIFORMMATRIXFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniformMatrix4fv);

    GLint location = getUniformLocation(program, "OSGCameraOrientation");

    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateCameraPosition(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    Matrix m = pEnv->getCameraToWorld();

    Vec3f cameraPos(m[3][0], m[3][1], m[3][2]);

    // get "glUniform3fvARB" function pointer
    OSGGLUNIFORMFVARBPROC uniform3fv =
        (OSGGLUNIFORMFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform3fv);

    GLint location = getUniformLocation(program, "OSGCameraPosition");

    if(location != -1)
        uniform3fv(location, 1, cameraPos.getValues());
}

void SHLChunk::updateViewMatrix(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    Matrix m = pEnv->getCameraViewing();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
        (OSGGLUNIFORMMATRIXFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniformMatrix4fv);

    GLint location = getUniformLocation(program, "OSGViewMatrix");

    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateInvViewMatrix(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    Matrix m = pEnv->getCameraToWorld();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv =
        (OSGGLUNIFORMMATRIXFVARBPROC)
            pEnv->getWindow()->getFunction(_funcUniformMatrix4fv);

    GLint location = getUniformLocation(program, "OSGInvViewMatrix");

    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateStereoLeftEye(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateStereoLeftEye : Can't update "
                  "OSGStereoLeftEye "
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    // ok -1 is mono
    Int32 leftEye = -1;
    // now search for a stereo camera decorator and get the eye.

    CameraPtr camera = Inherited::constructPtr<Camera>(action->getCamera());

    CameraDecoratorPtr decorator = cast_dynamic<CameraDecoratorPtr>(camera);

    while(decorator != NullFC)
    {
        StereoCameraDecoratorPtr stereoDecorator =
            cast_dynamic<StereoCameraDecoratorPtr>(decorator);

        if(stereoDecorator != NullFC)
        {
            if(stereoDecorator->getLeftEye())
                leftEye = 1;
            else
                leftEye = 0;
            break;
        }

        decorator =
            cast_dynamic<CameraDecoratorPtr>(decorator->getDecoratee());
    }

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGStereoLeftEye");

    if(location != -1)
        uniform1i(location, leftEye);
#endif
}

void SHLChunk::setClusterId(Int32 id)
{
    _clusterId = id;
}

void SHLChunk::updateClusterId(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGClusterId");

    if(location != -1)
        uniform1i(location, (GLint) _clusterId);
}

void SHLChunk::updateActiveLightsMask(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderActionBase *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGActiveLightsMask");

    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask());
#endif
}

void SHLChunk::updateLight0Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderActionBase *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight0Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 1);
#endif
}

void SHLChunk::updateLight1Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderAction *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight1Active");

    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 2);
#endif
}

void SHLChunk::updateLight2Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderAction *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight2Active");

    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 4);
#endif
}

void SHLChunk::updateLight3Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderAction *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight3Active");

    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 8);
#endif
}

void SHLChunk::updateLight4Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderAction *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight4Active");

    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 16);
#endif
}

void SHLChunk::updateLight5Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderAction *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight5Active");

    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 32);
#endif
}

void SHLChunk::updateLight6Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderAction *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight6Active");

    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 64);
#endif
}

void SHLChunk::updateLight7Active(
    OSGGLGETUNIFORMLOCATIONARBPROC  getUniformLocation,
    DrawEnv                        *pEnv,
    GLuint                          program)
{
#ifdef CHECK_OSG_PARRAM
    RenderActionBase *ract = dynamic_cast<RenderAction *>(action);

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i =
        (OSGGLUNIFORM1IARBPROC)
            pEnv->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight7Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 128);
#endif
}

/*------------------------------ State ------------------------------------*/

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

    updateParameters(pEnv->getWindow(), getParameters(),
                     false,  // don't use program
                     false,  // don't force updates
                     true);  // keep the program active

    if(getPointSize())
    {
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }
    else
    {
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
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

    if(pEnv->getWindow()->getGLObjectId(old->getGLId()) != 0)
        useProgramObject(0);

    GLuint program = (GLuint) pEnv->getWindow()->getGLObjectId(getGLId());

    if(program != 0)
    {
        useProgramObject(program);
        updateOSGParameters(pEnv, program);
        updateParameters(pEnv->getWindow(), getParameters(),
                     false,  // don't use program
                     false,  // don't force updates
                     true);  // keep the program active

        if(getPointSize())
        {
            glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
        }
        else
        {
            glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
        }
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

    if(getVertexProgram    () != tother->getVertexProgram  () ||
       getFragmentProgram  () != tother->getFragmentProgram() ||
       getParameters().size() != tother->getParameters     ().size())
        return false;

    return true;
}

bool SHLChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGSHLCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHLCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHLCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
