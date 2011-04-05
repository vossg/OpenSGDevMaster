/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include "OSGConfig.h"

#include "OSGSimpleSHLChunk.h"
#include "OSGDrawEnv.h"

#include "OSGShaderVariables.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSimpleSHLChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleSHLChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

#if 0
volatile UInt16 SimpleSHLChunk::_uiChunkCounter = 1;
#endif

#ifdef OSG_1_COMPAT
SimpleSHLChunk::ParamFunctor SimpleSHLChunk::_fParameterCallback;
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SimpleSHLChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

UInt32 SimpleSHLChunk::handleGL(DrawEnv                 *pEnv, 
                                UInt32                   id, 
                                Window::GLObjectStatusE  mode,
                                UInt32                   uiOptions)
{
    UInt32  returnValue = 0;
    Window *pWin        = pEnv->getWindow();

    if(!pWin->hasExtension(_extSHL))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find "
                  "extension 'GL_ARB_shading_language_100'!\n"));

        pWin->setGLObjectId(getGLId(), 0);

        return returnValue;
    }

    if(mode == Window::initialize   || 
       mode == Window::reinitialize ||
       mode == Window::needrefresh   )
    {
        GLuint uiProgram = GLuint(pWin->getGLObjectId(getGLId()));;

        if(mode != Window::needrefresh)
        {
            if(uiProgram != 0)
            {
                OSGGETGLFUNC(OSGglDeleteProgramProc,
                             osgGlDeleteProgram,
                             ShaderProgram::getFuncIdDeleteProgram());

                osgGlDeleteProgram(uiProgram);
            }

            OSGGETGLFUNC(OSGglCreateProgramProc,
                         osgGlCreateProgram,
                         ShaderProgram::getFuncIdCreateProgram());

            OSGGETGLFUNC(OSGglAttachShaderProc,
                         osgGlAttachShader,
                         ShaderProgram::getFuncIdAttachShader());

            OSGGETGLFUNC(OSGglLinkProgramProc,
                         osgGlLinkProgram,
                         ShaderProgram::getFuncIdLinkProgram());

            uiProgram = osgGlCreateProgram();

            FragmentShaderIt fIt  = _mfFragmentShader.begin();
            FragmentShaderIt fEnd = _mfFragmentShader.end  ();
            
            for(; fIt != fEnd; ++fIt)
            {
                (*fIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*fIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }
    
            GeometryShaderIt gIt  = _mfGeometryShader.begin();
            GeometryShaderIt gEnd = _mfGeometryShader.end  ();
            
            for(; gIt != gEnd; ++gIt)
            {
                (*gIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*gIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }
        
            VertexShaderIt vIt  = _mfVertexShader.begin();
            VertexShaderIt vEnd = _mfVertexShader.end  ();
            
            for(; vIt != vEnd; ++vIt)
            {
                (*vIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*vIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }

            // parameters must be set before linking
            updateParameters(pEnv, uiProgram);

            osgGlLinkProgram(uiProgram);

            GLint  iInfoLength;
            Char8 *szInfoBuffer = NULL;

            OSGGETGLFUNC(OSGglGetProgramivProc,
                         osgGlGetProgramiv,
                         ShaderProgram::getFuncIdGetProgramiv());

            osgGlGetProgramiv(uiProgram, 
                              GL_OBJECT_INFO_LOG_LENGTH_ARB, 
                              &iInfoLength);

            if(iInfoLength > 0)
            {
                szInfoBuffer = new Char8[iInfoLength];
                szInfoBuffer[0] = '\0';

                OSGGETGLFUNC(OSGglGetProgramInfoLogProc,
                             osgGlGetProgramInfoLog,
                             ShaderProgram::getFuncIdGetProgramInfoLog());

                osgGlGetProgramInfoLog( uiProgram, 
                                        iInfoLength, 
                                       &iInfoLength, 
                                        szInfoBuffer);
            }

            GLint iStatus = 0;

            osgGlGetProgramiv(uiProgram, GL_LINK_STATUS, &iStatus);

            if(iStatus == 0)
            {
                if(szInfoBuffer != NULL && szInfoBuffer[0] != '\0')
                {
                    FFATAL(("Couldn't link vertex and fragment program!\n%s\n",
                            szInfoBuffer));
                }
                else
                {
                    FFATAL(("Couldn't link vertex and fragment program!\n"
                            "No further info available\n"));
                }

                OSGGETGLFUNC(OSGglDeleteProgramProc,
                             osgGlDeleteProgram,
                             ShaderProgram::getFuncIdDeleteProgram());

                osgGlDeleteProgram(uiProgram);

                uiProgram = 0;
            }
            else
            {
                if(szInfoBuffer != NULL && szInfoBuffer[0] != '\0')
                {
                    FWARNING(("SimpleSHLChunk: link status: %s\n", 
                              szInfoBuffer));
                }
            }

            pWin->setGLObjectId(getGLId(), uiProgram);

            updateVariableLocations(pEnv, uiProgram);
        }

        if(uiProgram != 0)
        {
            OSGGETGLFUNC(OSGglUseProgramProc,
                         osgGlUseProgram,
                         ShaderProgram::getFuncIdUseProgram());
        
            osgGlUseProgram(uiProgram);
        
            updateVariables(pEnv, uiProgram);
        
            if(0x0000 == (uiOptions & KeepProgActive))
            {
                osgGlUseProgram(0);
            }
            else
            {
                returnValue |= ProgActive;
            }
        }
    }

    return returnValue;
}

void SimpleSHLChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                     UInt32                   id, 
                                     Window::GLObjectStatusE  mode)
{
    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtension(_extSHL))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find "
                  "extension 'GL_ARB_shading_language_100'!\n"));

        pWin->setGLObjectId(id, 0);

        return;
    }

    // BUG this is not called for every window!
    if(mode == Window::destroy)
    {
        GLuint uiProgram = GLuint(pWin->getGLObjectId(id));

        if(uiProgram != 0)
        {
            OSGGETGLFUNC(OSGglDeleteProgramProc,
                         osgGlDeleteProgram,
                         ShaderProgram::getFuncIdDeleteProgram());

            osgGlDeleteProgram(uiProgram);

            pWin->setGLObjectId(id, 0);
        }
    }
    else if(mode == Window::finaldestroy)
    {
        ;//SWARNING << "Last program user destroyed" << std::endl;
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SimpleSHLChunk::SimpleSHLChunk(void) :
    Inherited()
{
}

SimpleSHLChunk::SimpleSHLChunk(const SimpleSHLChunk &source) :
    Inherited(source)
{
}

SimpleSHLChunk::~SimpleSHLChunk(void)
{
}

void SimpleSHLChunk::onCreate(const SimpleSHLChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&SimpleSHLChunk::handleGL, 
                        SimpleSHLChunkMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &SimpleSHLChunk::handleDestroyGL));

    _uiChunkId = ShaderExecutableChunk::_uiChunkCounter++;
}

void SimpleSHLChunk::onCreateAspect(const SimpleSHLChunk *createAspect,
                                    const SimpleSHLChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

void SimpleSHLChunk::onDestroy(UInt32 uiId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiId);
}

const StateChunkClass *SimpleSHLChunk::getClass(void) const
{
    return ShaderExecutableChunk::getStaticClass();
}

UInt16 SimpleSHLChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*----------------------------- class specific ----------------------------*/

void SimpleSHLChunk::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    bool bMarkChanged = false;

    if(0x0000 != (whichField & FragmentProgramFieldMask) &&
       0      != _sfFragmentProgram.getValue().size()     )
    {
        if(_mfFragmentShader.size() == 0)
        {
            ShaderProgramUnrecPtr pProg = ShaderProgram::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

            pProg->setShaderType(GL_FRAGMENT_SHADER);

            addFragmentShader(pProg);
        }
        else if(_mfFragmentShader.size() > 1)
        {
            editMFFragmentShader()->resize(1);
        }

        _mfFragmentShader[0]->setProgram   (_sfFragmentProgram.getValue());
        _mfFragmentShader[0]->setCgFrontEnd(_sfCgFrontEnd     .getValue());

        bMarkChanged = true;

        Window::reinitializeGLObject(this->getGLId());
    }

    if(0x0000 != (whichField & GeometryProgramFieldMask) &&
       0      != _sfGeometryProgram.getValue().size()     )
    {
        if(_mfGeometryShader.size() == 0)
        {
            ShaderProgramUnrecPtr pProg = ShaderProgram::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

            pProg->setShaderType(GL_GEOMETRY_SHADER_EXT);

            addGeometryShader(pProg);
        }
        else if(_mfGeometryShader.size() > 1)
        {
            editMFGeometryShader()->resize(1);
        }

        _mfGeometryShader[0]->setProgram   (_sfGeometryProgram.getValue());
        _mfGeometryShader[0]->setCgFrontEnd(_sfCgFrontEnd     .getValue());

        bMarkChanged = true;

        Window::reinitializeGLObject(this->getGLId());
    }
   
    if(0x0000 != (whichField & VertexProgramFieldMask) &&
       0      != _sfVertexProgram.getValue().size()     )
    {
        if(_mfVertexShader.size() == 0)
        {
            ShaderProgramUnrecPtr pProg = ShaderProgram::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

            pProg->setShaderType(GL_VERTEX_SHADER);

            addVertexShader(pProg);
        }
        else if(_mfVertexShader.size() > 1)
        {
            editMFVertexShader()->resize(1);
        }
        
        _mfVertexShader[0]->setProgram   (_sfVertexProgram.getValue());
        _mfVertexShader[0]->setCgFrontEnd(_sfCgFrontEnd   .getValue());

        bMarkChanged = true;

        Window::reinitializeGLObject(this->getGLId());
    }


    if(0x0000 != (whichField & VariablesFieldMask))
    {
        ShaderProgramVariables *pVars = _sfVariables.getValue();

        if(pVars != NULL)
        {
            if(details == 0x0001)
            {
                // be save reset all locations

                if(pVars->getMFVariables()->size() == 0)
                {
                    editMFVariableLocations()->clear();
                }
                else
                {
                    editMFVariableLocations()->resize(
                        pVars->getMFVariables()->size(), 
                        -1);

                    std::fill(editMFVariableLocations()->begin(),
                              editMFVariableLocations()->end  (),
                              -1);
                }

                // be save reset all locations

                if(pVars->getMFProceduralVariables()->size() == 0     )
                {
                    editMFProceduralVariableLocations()->clear();
                }
                else
                {
                    editMFProceduralVariableLocations()->resize(
                        pVars->getMFProceduralVariables()->size(), 
                        -1);

                    std::fill(editMFProceduralVariableLocations()->begin(),
                              editMFProceduralVariableLocations()->end  (),
                              -1);
                }
            }
        }

        Window::refreshGLObject(this->getGLId());
    }

    if(0x0000 != (whichField & (VertexShaderFieldMask   | 
                                GeometryShaderFieldMask |
                                FragmentShaderFieldMask )))
    {
        bMarkChanged = true;

        Window::reinitializeGLObject(this->getGLId());
    }

    if(0x0000 != (whichField & (GeometryVerticesOutFieldMask | 
                                GeometryInputTypeFieldMask   | 
                                GeometryOutputTypeFieldMask  )))
    {
        bMarkChanged = true;

        // changing parameters requires re-linking the shader
        Window::reinitializeGLObject(this->getGLId());
    }

    if(bMarkChanged == true)
    {
        // be save reset all locations

        std::fill(editMFVariableLocations()->begin(),
                  editMFVariableLocations()->end  (),
                  -1);

        std::fill(editMFProceduralVariableLocations()->begin(),
                  editMFProceduralVariableLocations()->end  (),
                  -1);
    
        if(_sfVariables.getValue() != NULL)
        {
            _sfVariables.getValue()->markAllChanged();
        }
    }

    Inherited::changed(whichField, origin, details);
}

void SimpleSHLChunk::activate(DrawEnv    *pEnv,              
                              UInt32      uiIdx)
{
#if 0
    FragmentShaderIt fIt  = _mfFragmentShader.begin();
    FragmentShaderIt fEnd = _mfFragmentShader.end  ();

    for(; fIt != fEnd; ++fIt)
    {
        (*fIt)->validate(pEnv);
    }

    GeometryShaderIt gIt  = _mfGeometryShader.begin();
    GeometryShaderIt gEnd = _mfGeometryShader.end  ();

    for(; gIt != gEnd; ++gIt)
    {
        (*gIt)->validate(pEnv);
    }

    VertexShaderIt vIt  = _mfVertexShader.begin();
    VertexShaderIt vEnd = _mfVertexShader.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        (*vIt)->validate(pEnv);
    }
#endif
      
    Window *pWin    = pEnv->getWindow();

    UInt32 uiValRes = pWin->validateGLObject(getGLId(), 
                                             pEnv, 
                                             KeepProgActive);    

    GLuint uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

    if(uiProgId == 0)
        return;

    pEnv->setActiveShader(uiProgId);

    if(0x0000 == (uiValRes & ProgActive))
    {
        OSGGETGLFUNC(OSGglUseProgramProc,
                     osgGlUseProgram,
                     ShaderProgram::getFuncIdUseProgram());

        osgGlUseProgram(uiProgId);
    }

    updateProceduralVariables(pEnv, ShaderProcVariable::SHDAll);

    if(_sfPointSize.getValue() == true)
    {
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }

}

void SimpleSHLChunk::changeFrom(DrawEnv    *pEnv, 
                                StateChunk *pOther, 
                                UInt32      uiIdx)
{
    SimpleSHLChunk *pOld = dynamic_cast<SimpleSHLChunk *>(pOther);

    Window   *pWin     = pEnv->getWindow();
    GLuint    uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

    UInt32 uiDep = ShaderProcVariable::SHDObject;

    if(uiProgId != pEnv->getActiveShader())
    {
        FragmentShaderIt fIt  = _mfFragmentShader.begin();
        FragmentShaderIt fEnd = _mfFragmentShader.end  ();

        for(; fIt != fEnd; ++fIt)
        {
            (*fIt)->validate(pEnv);
        }

        GeometryShaderIt gIt  = _mfGeometryShader.begin();
        GeometryShaderIt gEnd = _mfGeometryShader.end  ();
        
        for(; gIt != gEnd; ++gIt)
        {
            (*gIt)->validate(pEnv);
        }
        
        VertexShaderIt vIt  = _mfVertexShader.begin();
        VertexShaderIt vEnd = _mfVertexShader.end  ();
        
        for(; vIt != vEnd; ++vIt)
        {
            (*vIt)->validate(pEnv);
        }

        UInt32 uiValRes = pWin->validateGLObject(getGLId(), 
                                                 pEnv, 
                                                 KeepProgActive);


        if(uiProgId == 0)
            return;

        pEnv->setActiveShader(uiProgId);

        if(0x0000 == (uiValRes & ProgActive))
        {
            OSGGETGLFUNC(OSGglUseProgramProc,
                         osgGlUseProgram,
                         ShaderProgram::getFuncIdUseProgram());

            osgGlUseProgram(uiProgId);
        }

        if(_sfPointSize.getValue() == true)
        {
            if(pOld->getPointSize() == false)
            {
                glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
            }
        }
        else
        {
            if(pOld->getPointSize() == true)
            {
                glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
            }
        }

        uiDep = ShaderProcVariable::SHDAll;
    }

    updateProceduralVariables(pEnv, uiDep);
}

void SimpleSHLChunk::deactivate(DrawEnv    *pEnv,              
                                UInt32      uiIdx)
{
    if(pEnv->getWindow()->getGLObjectId(getGLId()) == 0)
        return;

    pEnv->setActiveShader(0);

    OSGGETGLFUNC(OSGglUseProgramProc,
                 osgGlUseProgram,
                 ShaderProgram::getFuncIdUseProgram());

    if(_sfPointSize.getValue() == true)
    {
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }

    osgGlUseProgram(0);
}

void SimpleSHLChunk::dump(      UInt32    ,
                          const BitVector ) const
{
    SLOG << "Dump SimpleSHLChunk NI" << std::endl;
}

bool SimpleSHLChunk::readFragmentProgram(const Char8 *file)
{
    return readProgram(editSFFragmentProgram()->getValue(), file);
}

bool SimpleSHLChunk::readGeometryProgram(const Char8 *file)
{
    return readProgram(editSFGeometryProgram()->getValue(), file);
}

bool SimpleSHLChunk::readVertexProgram(const Char8 *file)
{
    return readProgram(editSFVertexProgram()->getValue(), file);
}

bool SimpleSHLChunk::readProgram(      std::string  &szTarget,
                                 const Char8        *szFilename)
{
    std::ifstream s(szFilename);
    
    if(s.good())
    {
        return readProgram(szTarget, s);
    }
    else
    {
        FWARNING(("ShaderChunk::readProgram: couldn't open '%s' "
                  "for reading!\n", szFilename));

        return false;
    }

}

bool SimpleSHLChunk::readProgram(std::string  &szTarget,
                                 std::istream &iStream)
{
#define BUFSIZE 200
    
    szTarget.erase();

    Char8 buf[BUFSIZE];

    if(!iStream.good())
    {
        FWARNING(("SHLChunk::readProgram: stream is not good!\n"));

        return false;
    }
    
    do
    {
        iStream.read(buf, BUFSIZE);

        szTarget.append(buf, iStream.gcount());
    }
    while(!iStream.eof());
    
    return true;
}

#ifdef OSG_1_COMPAT
void SimpleSHLChunk::addProgramParameter(GLenum name, UInt32 value)
{
    switch(name)
    {
        case GL_GEOMETRY_VERTICES_OUT_EXT:
            this->setGeometryVerticesOut(value);
            break;

        case GL_GEOMETRY_INPUT_TYPE_EXT:
            this->setGeometryInputType(value);
            break;

        case GL_GEOMETRY_OUTPUT_TYPE_EXT:
            this->setGeometryOutputType(value);
            break;

        default:
            break;
    }
}

void SimpleSHLChunk::subProgramParameter(GLenum name)
{
    switch(name)
    {
        case GL_GEOMETRY_VERTICES_OUT_EXT:
            this->setGeometryVerticesOut(0);
            break;

        case GL_GEOMETRY_INPUT_TYPE_EXT:
            this->setGeometryInputType(GL_TRIANGLES);
            break;

        case GL_GEOMETRY_OUTPUT_TYPE_EXT:
            this->setGeometryOutputType(GL_TRIANGLE_STRIP);
            break;

        default:
            break;
    }
}
#endif

void SimpleSHLChunk::setProgramParameter(GLenum name, UInt32 value)
{
    switch(name)
    {
        case GL_GEOMETRY_VERTICES_OUT_EXT:
            this->setGeometryVerticesOut(value);
            break;

        case GL_GEOMETRY_INPUT_TYPE_EXT:
            this->setGeometryInputType(value);
            break;

        case GL_GEOMETRY_OUTPUT_TYPE_EXT:
            this->setGeometryOutputType(value);
            break;

        default:
            break;
    }
}

UInt32 SimpleSHLChunk::getProgramParameter(GLenum name)
{
    switch(name)
    {
        case GL_GEOMETRY_VERTICES_OUT_EXT:
            return this->getGeometryVerticesOut();
            break;

        case GL_GEOMETRY_INPUT_TYPE_EXT:
            return this->getGeometryInputType();
            break;

        case GL_GEOMETRY_OUTPUT_TYPE_EXT:
            return this->getGeometryOutputType();
            break;

        default:
            return 0;
            break;
    }
}

void SimpleSHLChunk::clearProgramParameters(void)
{
    setGeometryVerticesOut(0                );
    setGeometryInputType  (GL_TRIANGLES     );
    setGeometryOutputType (GL_TRIANGLE_STRIP);
}

#ifdef OSG_1_COMPAT
bool SimpleSHLChunk::subUniformParameter(const Char8 *name)
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->subUniformVariable(
            name,
            editMFVariableLocations(),
            editMFProceduralVariableLocations());
                                                     
    }
    
    return false;
}

void SimpleSHLChunk::clearUniformParameters(void)
{
    if(_sfVariables.getValue() != NULL)
    {
        _sfVariables.getValue()->clearUniformVariables();
    }

    editMFVariableLocations          ()->clear();
    editMFProceduralVariableLocations()->clear();
}
#endif

bool SimpleSHLChunk::subUniformVariable(const Char8 *name)
{
    if(_sfVariables.getValue() != NULL)
    {
        return _sfVariables.getValue()->subUniformVariable(
            name,
            editMFVariableLocations(),
            editMFProceduralVariableLocations());
                                                     
    }

    return false;
}

void SimpleSHLChunk::clearUniformVariables(void)
{
    if(_sfVariables.getValue() != NULL)
    {
        _sfVariables.getValue()->clearUniformVariables();
    }

    editMFVariableLocations          ()->clear();
    editMFProceduralVariableLocations()->clear();
}

bool SimpleSHLChunk::addOSGVariable(const Char8 *name)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pVar = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pVar);
    }

    return _sfVariables.getValue()->addOSGVariable(
        name, 
        editMFProceduralVariableLocations());
}

bool SimpleSHLChunk::addProceduralVariable(const Char8          *name,
                                                 ProcVarFunctor  pFunc,
                                                 UInt32          uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    return _sfVariables.getValue()->addProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        editMFProceduralVariableLocations());
}

bool SimpleSHLChunk::updateNodeProceduralVariable(
    const Char8             *name,
          ProcVarNodeFunctor pFunc,
          UInt32             uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    return _sfVariables.getValue()->updateNodeProceduralVariable(name, 
                                                                 pFunc,
                                                                 uiDependency);
}

bool SimpleSHLChunk::addNodeProceduralVariable(
    const Char8              *name,
          ProcVarNodeFunctor  pFunc,
          UInt32              uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    return _sfVariables.getValue()->addNodeProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        editMFProceduralVariableLocations());
}

bool SimpleSHLChunk::updateProceduralVariable(const Char8         *name,
                                                    ProcVarFunctor pFunc,
                                                    UInt32         uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    return _sfVariables.getValue()->updateProceduralVariable(name, 
                                                             pFunc,
                                                             uiDependency);
}

#ifdef OSG_1_COMPAT
void SimpleSHLChunk::addParameterCallback(const Char8 *name, ParamFunctor fp)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    _sfVariables.getValue()->addProceduralVariable(
        name, 
        fp,
        editMFProceduralVariableLocations());
}

void SimpleSHLChunk::addParameterCallback(const Char8 *name, OSGParamFunctor fp)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);
    }

    _sfVariables.getValue()->addProceduralVariable(
        name, 
        fp,
        editMFProceduralVariableLocations());
}

void SimpleSHLChunk::setParameterCallback(ParamFunctor fp)
{
    _fParameterCallback = fp;
}
#endif

#if 1
void SimpleSHLChunk::updateParameters(      
    Window                         *win,
    const UInt32                         &parameters,
    bool                            useProgram,
    bool                            force,
    bool                            keepProgramActive)
{
}

const UInt32 *SimpleSHLChunk::getMFParameters(void) const
{
    static UInt32 foo;

    return &foo;
}
#endif

void SimpleSHLChunk::updateVariableLocations(DrawEnv *pEnv,
                                             UInt32   uiProgram)
{
    if(uiProgram == 0)
        return;

    const ShaderProgramVariables::MFVariablesType           *pMFVars     = NULL;
    const ShaderProgramVariables::MFProceduralVariablesType *pMFProcVars = NULL;

    if(_sfVariables.getValue() != NULL)
    {
        pMFVars     = _sfVariables.getValue()->getMFVariables          ();
        pMFProcVars = _sfVariables.getValue()->getMFProceduralVariables();
    }

    if(pMFVars != NULL && pMFVars->size() != 0)
    {
        MFInt32 &vVarLocations = *this->editMFVariableLocations();

        OSG_ASSERT(pMFVars->size() == vVarLocations.size());

        MFInt32::iterator mLocIt = vVarLocations.begin();
        
        ShaderProgramVariables::MFVariablesType::const_iterator mVarIt  =
            pMFVars->begin();
        ShaderProgramVariables::MFVariablesType::const_iterator mVarEnd =
            pMFVars->end  ();
        
        OSGGETGLFUNC(OSGglGetUniformLocationProc,
                     osgGlGetUniformLocation,
                     ShaderProgram::getFuncIdGetUniformLocation());

        for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
        {
            *mLocIt = osgGlGetUniformLocation(uiProgram,
                                              (*mVarIt)->getName().c_str());
        }
    }

    if(pMFProcVars != NULL && pMFProcVars->size() != 0)
    {
        MFInt32 &vVarLocations = *this->editMFProceduralVariableLocations();

        OSG_ASSERT(pMFProcVars->size() == vVarLocations.size());

        MFInt32::iterator mLocIt = vVarLocations.begin();
        
        ShaderProgramVariables::MFProceduralVariablesType::const_iterator 
            mVarIt  = pMFProcVars->begin();
        ShaderProgramVariables::MFProceduralVariablesType::const_iterator 
            mVarEnd = pMFProcVars->end  ();
        
        OSGGETGLFUNC(OSGglGetUniformLocationProc,
                     osgGlGetUniformLocation,
                     ShaderProgram::getFuncIdGetUniformLocation());

        for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
        {
            *mLocIt = osgGlGetUniformLocation(uiProgram,
                                              (*mVarIt)->getName().c_str());
        }
    }
}

void SimpleSHLChunk::updateVariables(DrawEnv *pEnv,
                                     UInt32   uiProgram)
{
    if(uiProgram == 0)
        return;

    const ShaderProgramVariables::MFVariablesType       *pMFVars   = NULL;
          ShaderProgramVariables::MFVariableChangedType *pMFVarChg = NULL;

    if(_sfVariables.getValue() != NULL)
    {
        pMFVars   = _sfVariables.getValue()->getMFVariables       ();
        pMFVarChg = _sfVariables.getValue()->editMFVariableChanged();
    }

    if(pMFVars == NULL || pMFVars->size() == 0 || pMFVarChg == NULL)
    {
        return;
    }

    OSG_ASSERT(pMFVars->size() == pMFVarChg->size());

    MFInt32 &vVarLocations = *this->editMFVariableLocations();

    OSG_ASSERT(pMFVars->size() == vVarLocations.size());

    MFInt32::iterator mLocIt = vVarLocations.begin();

    ShaderProgramVariables::MFVariablesType::const_iterator mVarIt  =
        pMFVars->begin();
    ShaderProgramVariables::MFVariablesType::const_iterator mVarEnd =
        pMFVars->end  ();

    ShaderProgramVariables::MFVariableChangedType::iterator mVarChgIt =
        pMFVarChg->begin();

    bool warnUnknown = true;

    for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt, ++mVarChgIt)
    {
        ShaderVariable *pVar = *mVarIt;

        if(pVar == NULL)
            continue;

        if(*mVarChgIt == false)
            continue;

        *mVarChgIt = false;

        osgUniformShaderVariableSwitch(pEnv,    pVar,
                                       *mLocIt, uiProgram, warnUnknown);
    }
}

void SimpleSHLChunk::updateParameters(DrawEnv *pEnv,
                                      UInt32   uiProgram)
{
    if(uiProgram == 0 || this->getGeometryVerticesOut() == 0)
        return;

    OSGGETGLFUNC(OSGglProgramParameteriEXTProc,
                 osgGlProgramParameteriEXT,
                 ShaderProgram::getFuncIdProgramParameteri());

    osgGlProgramParameteriEXT(uiProgram,
                              GL_GEOMETRY_VERTICES_OUT_EXT, 
                              this->getGeometryVerticesOut());
    osgGlProgramParameteriEXT(uiProgram,
                              GL_GEOMETRY_INPUT_TYPE_EXT, 
                              this->getGeometryInputType());
    osgGlProgramParameteriEXT(uiProgram,
                              GL_GEOMETRY_OUTPUT_TYPE_EXT, 
                              this->getGeometryOutputType());
}

void SimpleSHLChunk::updateProceduralVariables(
    DrawEnv *pEnv,
    UInt32   uiUpdateDependents)
{
    UInt32 uiProgram = pEnv->getActiveShader();

    if(uiProgram == 0)
        return;

    const ShaderProgramVariables::MFProceduralVariablesType *pMFVars = NULL;

    if(_sfVariables.getValue() != NULL)
    {
        pMFVars   = _sfVariables.getValue()->getMFProceduralVariables();
    }

    if(pMFVars == NULL || pMFVars->size() == 0)
    {
        return;
    }

    MFInt32 &vVarLocations = *this->editMFProceduralVariableLocations();

    OSG_ASSERT(pMFVars->size() == vVarLocations.size());

    MFInt32::iterator mLocIt = vVarLocations.begin();

    ShaderProgramVariables::MFProceduralVariablesType::const_iterator mVarIt  =
        pMFVars->begin();
    ShaderProgramVariables::MFProceduralVariablesType::const_iterator mVarEnd =
        pMFVars->end  ();

#ifdef OSG_1_COMPAT
    if(_fParameterCallback)
    {
        OSGGETGLFUNC(OSGglGetUniformLocationProc,
                     osgGlGetUniformLocation,
                     ShaderProgram::getFuncIdGetUniformLocation());

        _fParameterCallback(osgGlGetUniformLocation, pEnv, uiProgram);
    }
#endif

    for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
    {
        ShaderVariable *pVar = *mVarIt;

        switch(pVar->getTypeId())
        {
            case ShaderVariable::SHVTypeOSG:
            {
                ShaderVariableOSG *p =
                    dynamic_cast<ShaderVariableOSG *>(pVar);

                if(0x0000 == (p->getDependency() & uiUpdateDependents))
                    continue;

                if(*mLocIt == -1)
                {
                    OSGGETGLFUNC(OSGglGetUniformLocationProc,
                                 osgGlGetUniformLocation,
                                 ShaderProgram::getFuncIdGetUniformLocation());

                    *mLocIt = osgGlGetUniformLocation(uiProgram,
                                                      p->getName().c_str());
                }

                p->evaluate(pEnv, *mLocIt);                
            }
            break;

            case ShaderVariable::SHVTypeFunctor:
            {
                ShaderVariableFunctor *p =
                    dynamic_cast<ShaderVariableFunctor *>(pVar);

                if(0x0000 == (p->getDependency() & uiUpdateDependents))
                    continue;

                if(*mLocIt == -1)
                {
                    OSGGETGLFUNC(OSGglGetUniformLocationProc,
                                 osgGlGetUniformLocation,
                                 ShaderProgram::getFuncIdGetUniformLocation());

                    *mLocIt = osgGlGetUniformLocation(uiProgram,
                                                      p->getName().c_str());
                }

#ifdef OSG_1_COMPAT
                switch(p->getFuncMode())
                {
                    case 0:
                    {
                        p->evaluate(pEnv, *mLocIt);                
                    }
                    break;
                        
                    case 1:
                    {
                        OSGGETGLFUNC(
                            OSGglGetUniformLocationProc,
                            osgGlGetUniformLocation,
                            ShaderProgram::getFuncIdGetUniformLocation());

                        p->evaluate(osgGlGetUniformLocation,
                                    pEnv,
                                    uiProgram);
                    }
                    break;

                    case 2:
                    {
                        p->evaluate(p,
                                    pEnv,
                                    uiProgram);
                    }
                    break;
                }
#else
                p->evaluate(pEnv, *mLocIt);                
#endif
            }
            break;

            default:
                break;
        }
    }
}


OSG_END_NAMESPACE
