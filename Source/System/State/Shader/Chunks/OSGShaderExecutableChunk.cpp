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

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGShaderExecutableChunk.h"
#include "OSGShaderProgramChunk.h"
#include "OSGShaderVariables.h"

#include "OSGGLFuncProtos.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderExecutableChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderExecutableChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ShaderExecutableChunk::_class("ShaderExecutable", 1, 7);
volatile UInt16 ShaderExecutableChunk::_uiChunkCounter = 1;

UInt32 ShaderExecutableChunk::_extSHL = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderExecutableChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extSHL = Window::registerExtension("GL_ARB_shading_language_100");
    }
}

void ShaderExecutableChunk::resolveLinks(void)
{
    FragmentShaderIt fIt  = _mfFragmentShader.begin();
    FragmentShaderIt fEnd = _mfFragmentShader.end  ();

    for(; fIt != fEnd; ++fIt)
    {
        if(*fIt != NULL)
            (*fIt)->subParent(this);
    }

    GeometryShaderIt gIt  = _mfGeometryShader.begin();
    GeometryShaderIt gEnd = _mfGeometryShader.end  ();

    for(; gIt != gEnd; ++gIt)
    {
        if(*gIt != NULL)
            (*gIt)->subParent(this);
    }

    VertexShaderIt vIt  = _mfVertexShader.begin();
    VertexShaderIt vEnd = _mfVertexShader.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        if(*vIt != NULL)
            (*vIt)->subParent(this);
    }
    
    Inherited::resolveLinks();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderExecutableChunk::ShaderExecutableChunk(void) :
    Inherited()
{
}

ShaderExecutableChunk::ShaderExecutableChunk(
    const ShaderExecutableChunk &source) :

    Inherited(source)
{
}

ShaderExecutableChunk::~ShaderExecutableChunk(void)
{
}

void ShaderExecutableChunk::onCreate(const ShaderExecutableChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&ShaderExecutableChunk::handleGL, 
                        ShaderExecutableChunkMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &ShaderExecutableChunk::handleDestroyGL));

    _uiChunkId = _uiChunkCounter++;
}

void ShaderExecutableChunk::onCreateAspect(
    const ShaderExecutableChunk *createAspect,
    const ShaderExecutableChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

void ShaderExecutableChunk::onDestroy(UInt32 uiId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiId);
}

const StateChunkClass *ShaderExecutableChunk::getClass(void) const
{
    return &_class;
}

UInt16 ShaderExecutableChunk::getChunkId(void)
{
    return _uiChunkId;
}

UInt32 ShaderExecutableChunk::handleGL(DrawEnv                 *pEnv, 
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
                    FWARNING(("SHLChunk: link status: %s\n", szInfoBuffer));
                }
            }

            pWin->setGLObjectId(getGLId(), uiProgram);

            updateVariableLocations(pEnv, uiProgram);
            
            delete [] szInfoBuffer;
        }

        if(uiProgram != 0)
        {
            OSGGETGLFUNC(OSGglUseProgramProc,
                         osgGlUseProgram,
                         ShaderProgram::getFuncIdUseProgram());

            pEnv->setActiveShader(uiProgram);
            osgGlUseProgram      (uiProgram);
        
            updateVariables(pEnv, uiProgram);
        
            if(0x0000 == (uiOptions & KeepProgActive))
            {
                pEnv->setActiveShader(0);
                osgGlUseProgram      (0);
            }
            else
            {
                returnValue |= ProgActive;
            }
        }
    }

    return returnValue;
}

void ShaderExecutableChunk::handleDestroyGL(DrawEnv                 *pEnv, 
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

/*----------------------------- class specific ----------------------------*/

void ShaderExecutableChunk::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    bool bMarkChanged = false;

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
        if(details == ShaderProgram::ProgramFieldMask)
        {
            Window::reinitializeGLObject(this->getGLId());
        }

        else if(details == ShaderProgram::VariablesFieldMask)
        {
            this->remergeVariables();

            Window::refreshGLObject(this->getGLId());
         }

        bMarkChanged = true;
    }

    if(0x0000 != (whichField & (GeometryVerticesOutFieldMask | 
                                GeometryInputTypeFieldMask   | 
                                GeometryOutputTypeFieldMask  )))
    {
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

void ShaderExecutableChunk::dump(      UInt32    ,
                                 const BitVector ) const
{
    SLOG << "Dump ShaderExecutableChunk NI" << std::endl;
}

void ShaderExecutableChunk::activate(DrawEnv    *pEnv,              
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

    if(0x0000 == (uiValRes & ProgActive))
    {
        OSGGETGLFUNC(OSGglUseProgramProc,
                     osgGlUseProgram,
                     ShaderProgram::getFuncIdUseProgram());

        pEnv->setActiveShader(uiProgId);
        osgGlUseProgram      (uiProgId);
    }

    updateProceduralVariables(pEnv, ShaderProcVariable::SHDAll);

    if(_sfPointSize.getValue() == true)
    {
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }

}

void ShaderExecutableChunk::changeFrom(DrawEnv    *pEnv, 
                                       StateChunk *pOther, 
                                       UInt32      uiIdx)
{
    ShaderExecutableChunk *pOld = dynamic_cast<ShaderExecutableChunk *>(pOther);

    Window   *pWin     = pEnv->getWindow();
    GLuint    uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

    UInt32 uiDep = ShaderProcVariable::SHDObject;

    if(uiProgId != pEnv->getActiveShader())
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

        UInt32 uiValRes = pWin->validateGLObject(getGLId(), 
                                                 pEnv, 
                                                 KeepProgActive);


        if(uiProgId == 0)
            return;

        if(0x0000 == (uiValRes & ProgActive))
        {
            OSGGETGLFUNC(OSGglUseProgramProc,
                         osgGlUseProgram,
                         ShaderProgram::getFuncIdUseProgram());

            pEnv->setActiveShader(uiProgId);
            osgGlUseProgram      (uiProgId);
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

void ShaderExecutableChunk::deactivate(DrawEnv    *pEnv,              
                                       UInt32      uiIdx)
{
    if(pEnv->getWindow()->getGLObjectId(getGLId()) == 0)
        return;

    OSGGETGLFUNC(OSGglUseProgramProc,
                 osgGlUseProgram,
                 ShaderProgram::getFuncIdUseProgram());

    if(_sfPointSize.getValue() == true)
    {
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }

    pEnv->setActiveShader(0);
    osgGlUseProgram      (0);
}

void ShaderExecutableChunk::merge(const ShaderProgramChunk *pChunk)
{
    editMField(VertexShaderFieldMask,   _mfVertexShader  );
    editMField(GeometryShaderFieldMask, _mfGeometryShader);
    editMField(FragmentShaderFieldMask, _mfFragmentShader);

    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pVar = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pVar);
    }

    _mfVertexShader.reserve(_mfVertexShader.size() + 
                             pChunk->getMFVertexShader()->size());

    ShaderProgramChunk::MFVertexShaderType::const_iterator sIt  = 
        pChunk->getMFVertexShader()->begin();

    ShaderProgramChunk::MFVertexShaderType::const_iterator sEnd = 
        pChunk->getMFVertexShader()->end();

    bool bPointSize = false;

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, VertexShaderFieldId);

        _mfVertexShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());

        bPointSize |= (*sIt)->getPointSize();
    }

    if(bPointSize != _sfPointSize.getValue())
    {
        this->setPointSize(bPointSize);
    }

    _mfGeometryShader.reserve(_mfGeometryShader.size() + 
                               pChunk->getMFGeometryShader()->size());

    sIt  = pChunk->getMFGeometryShader()->begin();
    sEnd = pChunk->getMFGeometryShader()->end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, GeometryShaderFieldId);

        _mfGeometryShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());

        if((*sIt)->hasParameter() == true)
        {
            ShaderProgram::MFParameterType::const_iterator pIt  = 
                (*sIt)->getMFParameter()->begin();

            ShaderProgram::MFParameterType::const_iterator pEnd = 
                (*sIt)->getMFParameter()->end  ();

            while(pIt != pEnd)
            {
                switch(pIt->first)
                {
                    case GL_GEOMETRY_INPUT_TYPE_EXT:
                        this->setGeometryInputType(pIt->second);
                        break;
                        
                    case GL_GEOMETRY_OUTPUT_TYPE_EXT:
                        this->setGeometryOutputType(pIt->second);
                        break;

                    case GL_GEOMETRY_VERTICES_OUT_EXT:
                        this->setGeometryVerticesOut(pIt->second);
                        break;
                }

                ++pIt;
            }
        }
    }


    _mfFragmentShader.reserve(_mfFragmentShader.size() + 
                               pChunk->getMFFragmentShader()->size());

    sIt  = pChunk->getMFFragmentShader()->begin();
    sEnd = pChunk->getMFFragmentShader()->end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, FragmentShaderFieldId);

        _mfFragmentShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());
    }
}

void ShaderExecutableChunk::remergeVariables(void)
{
    OSG_ASSERT(_sfVariables.getValue() != NULL);

    _sfVariables.getValue()->clearVariables();
    _sfVariables.getValue()->clearProceduralVariables();

    this->editMFVariableLocations          ()->clear();
    this->editMFProceduralVariableLocations()->clear();


    ShaderExecutableChunk::MFVertexShaderType::const_iterator sIt  = 
        _mfVertexShader.begin();

    ShaderExecutableChunk::MFVertexShaderType::const_iterator sEnd = 
        _mfVertexShader.end();


    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations(),
                this->editMFProceduralVariableLocations());
        }
    }



    sIt  = _mfGeometryShader.begin();
    sEnd = _mfGeometryShader.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations          (),
                this->editMFProceduralVariableLocations());
        }
    }



    sIt  = _mfFragmentShader.begin();
    sEnd = _mfFragmentShader.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations          (),
                this->editMFProceduralVariableLocations());
        }
    }
}

void ShaderExecutableChunk::updateVariableLocations(DrawEnv *pEnv,
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

void ShaderExecutableChunk::updateVariables(DrawEnv *pEnv,
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

void ShaderExecutableChunk::updateParameters(DrawEnv *pEnv,
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

void ShaderExecutableChunk::updateProceduralVariables(
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

#ifdef OSG_1_COMPATX
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
