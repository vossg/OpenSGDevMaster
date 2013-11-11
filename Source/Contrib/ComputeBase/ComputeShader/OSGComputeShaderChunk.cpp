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

#include "OSGComputeShaderChunk.h"
#include "OSGDrawEnv.h"

#include "OSGShaderVariables.h"
#include "OSGConceptPropertyChecks.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComputeShaderChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGComputeShaderChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ComputeShaderChunk::_class("ShaderProgram", 1, 40);

volatile UInt16 ComputeShaderChunk::_uiChunkCounter = 1;

UInt32 ComputeShaderChunk::_arbComputeShader = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComputeShaderChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _arbComputeShader = 
            Window::registerExtension("GL_ARB_compute_shader");
    }
}

UInt32 ComputeShaderChunk::handleGL(DrawEnv                 *pEnv, 
                                    UInt32                   id, 
                                    Window::GLObjectStatusE  mode,
                                    UInt32                   uiOptions)
{
    UInt32  returnValue = 0;
    Window *pWin        = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_arbComputeShader, 0x0403, 0xFFFF))
    {
        FWARNING(("OpenGL compute shader is not supported, couldn't find "
                  "extension 'GL_ARB_compute_shader'!\n"));

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
                OSGGETGLFUNCBYID_GL3_ES(glDeleteProgram,
                                        osgGlDeleteProgram,
                                        ShaderProgram::getFuncIdDeleteProgram(),
                                        pWin);

                osgGlDeleteProgram(uiProgram);
            }

            OSGGETGLFUNCBYID_GL3_ES(glCreateProgram,
                                    osgGlCreateProgram,
                                    ShaderProgram::getFuncIdCreateProgram(),
                                    pWin);

            OSGGETGLFUNCBYID_GL3_ES(glAttachShader,
                                    osgGlAttachShader,
                                    ShaderProgram::getFuncIdAttachShader(),
                                    pWin);

            OSGGETGLFUNCBYID_GL3_ES(glLinkProgram,
                                    osgGlLinkProgram,
                                    ShaderProgram::getFuncIdLinkProgram(),
                                    pWin);

            uiProgram = osgGlCreateProgram();
        
            ComputeShaderIt vIt  = _mfComputeShader.begin();
            ComputeShaderIt vEnd = _mfComputeShader.end  ();
            
            for(; vIt != vEnd; ++vIt)
            {
                (*vIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*vIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }

            osgGlLinkProgram(uiProgram);

            GLint  iInfoLength;
            Char8 *szInfoBuffer = NULL;

            OSGGETGLFUNCBYID_GL3_ES(glGetProgramiv,
                                    osgGlGetProgramiv,
                                    ShaderProgram::getFuncIdGetProgramiv(),
                                    pWin);

            osgGlGetProgramiv(uiProgram, 
                              GL_OBJECT_INFO_LOG_LENGTH_ARB, 
                              &iInfoLength);

            if(iInfoLength > 0)
            {
                szInfoBuffer = new Char8[iInfoLength];
                szInfoBuffer[0] = '\0';

                OSGGETGLFUNCBYID_GL3_ES(
                    glGetProgramInfoLog,
                    osgGlGetProgramInfoLog,
                    ShaderProgram::getFuncIdGetProgramInfoLog(),
                    pWin);

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
                    FFATAL(("Couldn't link compute program!\n%s\n",
                            szInfoBuffer));
                }
                else
                {
                    FFATAL(("Couldn't link compute program!\n"
                            "No further info available\n"));
                }

                OSGGETGLFUNCBYID_GL3_ES(glDeleteProgram,
                                        osgGlDeleteProgram,
                                        ShaderProgram::getFuncIdDeleteProgram(),
                                        pWin);

                osgGlDeleteProgram(uiProgram);

                uiProgram = 0;
            }
            else
            {
                if(szInfoBuffer != NULL && szInfoBuffer[0] != '\0')
                {
                    FWARNING(("ComputeShaderChunk: link status: %s\n", 
                              szInfoBuffer));
                }
            }

            pWin->setGLObjectId(getGLId(), uiProgram);

            updateVariableLocations(pEnv, uiProgram);
        }

        if(uiProgram != 0)
        {
            OSGGETGLFUNCBYID_GL3_ES(glUseProgram,
                                    osgGlUseProgram,
                                    ShaderProgram::getFuncIdUseProgram(),
                                    pWin);
        
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

void ComputeShaderChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                         UInt32                   id, 
                                         Window::GLObjectStatusE  mode)
{
    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_arbComputeShader, 0x0403, 0xFFFF))
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
            OSGGETGLFUNCBYID_GL3_ES(glDeleteProgram,
                                    osgGlDeleteProgram,
                                    ShaderProgram::getFuncIdDeleteProgram(),
                                    pWin);

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

ComputeShaderChunk::ComputeShaderChunk(void) :
    Inherited()
{
}

ComputeShaderChunk::ComputeShaderChunk(const ComputeShaderChunk &source) :
    Inherited(source)
{
}

ComputeShaderChunk::~ComputeShaderChunk(void)
{
}

void ComputeShaderChunk::onCreate(const ComputeShaderChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&ComputeShaderChunk::handleGL, 
                        ComputeShaderChunkMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &ComputeShaderChunk::handleDestroyGL));

    _uiChunkId = ComputeShaderChunk::_uiChunkCounter++;
}

void ComputeShaderChunk::onCreateAspect(const ComputeShaderChunk *createAspect,
                                        const ComputeShaderChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

void ComputeShaderChunk::onDestroy(UInt32 uiId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiId);
}

const StateChunkClass *ComputeShaderChunk::getClass(void) const
{
    return &_class;
}

UInt16 ComputeShaderChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*----------------------------- class specific ----------------------------*/

void ComputeShaderChunk::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    bool bMarkChanged = false;

    if(0x0000 != (whichField & ComputeProgramFieldMask) &&
       0      != _sfComputeProgram.getValue().size()     )
    {
        if(_mfComputeShader.size() == 0)
        {
            ShaderProgramUnrecPtr pProg = ShaderProgram::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

            pProg->setShaderType(GL_COMPUTE_SHADER);

            addComputeShader(pProg);

            pProg->setVariables(this->getVariables());
        }
        else if(_mfComputeShader.size() > 1)
        {
            editMFComputeShader()->resize(1);
        }
        
        _mfComputeShader[0]->setProgram(_sfComputeProgram.getValue());

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

    if(0x0000 != (whichField & ComputeShaderFieldMask))
    {
        bMarkChanged = true;

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

void ComputeShaderChunk::activate(DrawEnv    *pEnv,              
                                  UInt32      uiIdx)
{
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
        OSGGETGLFUNCBYID_GL3_ES(glUseProgram,
                                osgGlUseProgram,
                                ShaderProgram::getFuncIdUseProgram(),
                                pWin);

        osgGlUseProgram(uiProgId);
    }

    pEnv->incNumShaderChanges();
        
    updateProceduralVariables(pEnv, ShaderProcVariable::SHDAll);

}

void ComputeShaderChunk::changeFrom(DrawEnv    *pEnv, 
                                    StateChunk *pOther, 
                                    UInt32      uiIdx)
{
    ComputeShaderChunk *pOld = dynamic_cast<ComputeShaderChunk *>(pOther);

    // pOther can be a ShaderExecutableChunk, since we share the StateClass id
    // with it
    if(pOld != NULL)
    {
        Window   *pWin     = pEnv->getWindow();
        GLuint    uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

        UInt32 uiDep = ShaderProcVariable::SHDObject;

        if(uiProgId != pEnv->getActiveShader())
        {
            UInt32 uiValRes = pWin->validateGLObject(getGLId(),
                                                     pEnv,
                                                     KeepProgActive);

            uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

            if(uiProgId == 0)
                return;

            pEnv->setActiveShader(uiProgId);

            if(0x0000 == (uiValRes & ProgActive))
            {
                OSGGETGLFUNCBYID_GL3_ES(glUseProgram,
                                        osgGlUseProgram,
                                        ShaderProgram::getFuncIdUseProgram(),
                                        pWin);

                osgGlUseProgram(uiProgId);
            }

            uiDep = ShaderProcVariable::SHDAll;

            pEnv->incNumShaderChanges();
        }

        updateProceduralVariables(pEnv, uiDep);
    }
    else
    {
        pOther->deactivate(pEnv, uiIdx);
        activate          (pEnv, uiIdx);

        pEnv->incNumShaderChanges();
    }
}

void ComputeShaderChunk::deactivate(DrawEnv    *pEnv,              
                                    UInt32      uiIdx)
{
    if(pEnv->getWindow()->getGLObjectId(getGLId()) == 0)
        return;

    pEnv->setActiveShader(0);

    OSGGETGLFUNC_GL3_ES(glUseProgram,
                        osgGlUseProgram,
                        ShaderProgram::getFuncIdUseProgram());

    osgGlUseProgram(0);
}

void ComputeShaderChunk::dump(      UInt32    ,
                              const BitVector ) const
{
    SLOG << "Dump ComputeShaderChunk NI" << std::endl;
}

bool ComputeShaderChunk::readComputeProgram(const Char8 *file)
{
    return readProgram(editSFComputeProgram()->getValue(), file);
}

bool ComputeShaderChunk::readProgram(      std::string  &szTarget,
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

bool ComputeShaderChunk::readProgram(std::string  &szTarget,
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

bool ComputeShaderChunk::subUniformVariable(const Char8 *name)
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

void ComputeShaderChunk::clearUniformVariables(void)
{
    if(_sfVariables.getValue() != NULL)
    {
        _sfVariables.getValue()->clearUniformVariables();
    }

    editMFVariableLocations          ()->clear();
    editMFProceduralVariableLocations()->clear();
}

bool ComputeShaderChunk::addOSGVariable(const Char8 *name)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pVar = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pVar);
        
        if(_mfComputeShader.size() > 0)
        {
            _mfComputeShader[0]->setVariables(this->getVariables());
        }
    }

    return _sfVariables.getValue()->addOSGVariable(
        name, 
        editMFProceduralVariableLocations());
}

bool ComputeShaderChunk::addProceduralVariable(
    const Char8          *name,
          ProcVarFunctor  pFunc,
          UInt32          uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);

        if(_mfComputeShader.size() > 0)
        {
            _mfComputeShader[0]->setVariables(this->getVariables());
        }
    }

    return _sfVariables.getValue()->addProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        editMFProceduralVariableLocations());
}

bool ComputeShaderChunk::updateNodeProceduralVariable(
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

        if(_mfComputeShader.size() > 0)
        {
            _mfComputeShader[0]->setVariables(this->getVariables());
        }
    }

    return _sfVariables.getValue()->updateNodeProceduralVariable(name, 
                                                                 pFunc,
                                                                 uiDependency);
}

bool ComputeShaderChunk::addNodeProceduralVariable(
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

        if(_mfComputeShader.size() > 0)
        {
            _mfComputeShader[0]->setVariables(this->getVariables());
        }
    }

    return _sfVariables.getValue()->addNodeProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        editMFProceduralVariableLocations());
}

bool ComputeShaderChunk::updateProceduralVariable(
    const Char8         *name,
          ProcVarFunctor pFunc,
          UInt32         uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pParam);

        if(_mfComputeShader.size() > 0)
        {
            _mfComputeShader[0]->setVariables(this->getVariables());
        }
    }

    return _sfVariables.getValue()->updateProceduralVariable(name, 
                                                             pFunc,
                                                             uiDependency);
}

#if 0
void ComputeShaderChunk::updateParameters(      
    Window                         *win,
    const UInt32                         &parameters,
    bool                            useProgram,
    bool                            force,
    bool                            keepProgramActive)
{
}

const UInt32 *ComputeShaderChunk::getMFParameters(void) const
{
    static UInt32 foo;

    return &foo;
}
#endif

void ComputeShaderChunk::updateVariableLocations(DrawEnv *pEnv,
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
        
        OSGGETGLFUNC_GL3_ES(glGetUniformLocation,
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
        
        OSGGETGLFUNC_GL3_ES(glGetUniformLocation,
                            osgGlGetUniformLocation,
                            ShaderProgram::getFuncIdGetUniformLocation());

        for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
        {
            *mLocIt = osgGlGetUniformLocation(uiProgram,
                                              (*mVarIt)->getName().c_str());
        }
    }
}

void ComputeShaderChunk::updateVariables(DrawEnv *pEnv,
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

    bool warnUnknown = ShaderVariable::WarnUnknown;

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

void ComputeShaderChunk::updateProceduralVariables(
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

    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);

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
                    OSGGETGLFUNCBYID_GL3_ES(
                        glGetUniformLocation,
                        osgGlGetUniformLocation,
                        ShaderProgram::getFuncIdGetUniformLocation(),
                        pWin);

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
                    OSGGETGLFUNCBYID_GL3_ES(
                        glGetUniformLocation,
                        osgGlGetUniformLocation,
                        ShaderProgram::getFuncIdGetUniformLocation(),
                        pWin);

                    *mLocIt = osgGlGetUniformLocation(uiProgram,
                                                      p->getName().c_str());
                }

                p->evaluate(pEnv, *mLocIt);                
            }
            break;

            default:
                break;
        }
    }
}


OSG_END_NAMESPACE
