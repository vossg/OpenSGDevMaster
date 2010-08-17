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

#include "OSGConfig.h"

#include "OSGCgFXMaterial.h"

#include "OSGSceneFileHandler.h"
#include "OSGFileSystem.h"
#include "OSGImageFileHandler.h"
#include "OSGNameAttachment.h"

#include "OSGShaderVariableBool.h"
#include "OSGShaderVariableInt.h"
#include "OSGShaderVariableReal.h"

#include "OSGShaderVariableVec2f.h"
#include "OSGShaderVariableVec3f.h"
#include "OSGShaderVariableVec4f.h"

#include "OSGShaderVariableMatrix.h"

#include "OSGCgFXVariableTexObj.h"

OSG_BEGIN_NAMESPACE

/*! \class osg::CGFXMaterial
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CgFXMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void CgFXMaterial::resolveLinks(void)
{
    Inherited::resolveLinks();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CgFXMaterial::CgFXMaterial(void) :
     Inherited              (     ),
    _pCGcontext             (NULL ),
    _pCGeffect              (NULL ),
    _pTechIdx               (    0),
    _mDelayTextureExtraction(false)
{
    this->markFieldsThreadLocal ((Self::MapCacheFieldMask        | 
                                  Self::FallbackMaterialFieldMask));
    this->markFieldsClusterLocal((Self::MapCacheFieldMask        | 
                                  Self::FallbackMaterialFieldMask));
}

CgFXMaterial::CgFXMaterial(const CgFXMaterial &source) :
     Inherited              (source                         ),
    _pCGcontext             (NULL                           ),
    _pCGeffect              (NULL                           ),
    _pTechIdx               (source._pTechIdx               ),
    _mDelayTextureExtraction(source._mDelayTextureExtraction)
{
    this->markFieldsThreadLocal ((Self::MapCacheFieldMask        | 
                                  Self::FallbackMaterialFieldMask));
    this->markFieldsClusterLocal((Self::MapCacheFieldMask        | 
                                  Self::FallbackMaterialFieldMask));
}

CgFXMaterial::~CgFXMaterial(void)
{
}

void CgFXMaterial::onCreate (const CgFXMaterial *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                boost::bind(&CgFXMaterial::handleGL, 
                            CgFXMaterialMTUncountedPtr(this), 
                            _1, _2, _3, _4),
                &CgFXMaterial::handleDestroyGL));
}

void CgFXMaterial::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

bool CgFXMaterial::isTransparent(void) const
{
    // not sure, CHECK_TOOLBOX_MERGE
    //return true;
    
    return false;
}

UInt32 CgFXMaterial::handleGL(DrawEnv                 *pEnv, 
                              UInt32                   osgId, 
                              Window::GLObjectStatusE  mode,
                              UInt32                   uiOptions)

{
    if(mode == Window::initialize)
    {
        Window::GLObjectId glId = 
            reinterpret_cast<Window::GLObjectId>(_pCGcontext);

        pEnv->getWindow()->setGLObjectId(osgId, glId);

#if OSG_CGFX_DUMP_DEBUG
        fprintf(stderr, "setting gl id %"PRIUSize" | %p\n",
                glId,
               _pCGcontext);
#endif
    }
    else if(mode == Window::reinitialize)
    {
        Window::GLObjectId oldGlId = pEnv->getWindow()->getGLObjectId(osgId);

        Window::GLObjectId glId = 
            reinterpret_cast<Window::GLObjectId>(_pCGcontext);

        OSG_ASSERT(oldGlId != glId);

        CGcontext pOldCGcontext = reinterpret_cast<CGcontext>(oldGlId);

#if OSG_CGFX_DUMP_DEBUG
        fprintf(stderr, "destroying gl id %"PRIUSize" | %p\n",
                oldGlId,
                pOldCGcontext);
#endif

        if(pOldCGcontext != NULL)
        {
            cgDestroyContext(pOldCGcontext);
        }

        pEnv->getWindow()->setGLObjectId(osgId, glId);

#if OSG_CGFX_DUMP_DEBUG
        fprintf(stderr, "setting gl id %"PRIUSize" | %p\n",
                glId,
               _pCGcontext);
#endif
    }

    return 0;
}

void CgFXMaterial::handleDestroyGL(DrawEnv                 *pEnv, 
                                   UInt32                   osgId, 
                                   Window::GLObjectStatusE  mode)
{
    Window* win = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        Window::GLObjectId glId = win->getGLObjectId(osgId);

        CGcontext pCGcontext = reinterpret_cast<CGcontext>(glId);

        fprintf(stderr, "destroying gl id %"PRIUSize"\n",
                glId);

        if(pCGcontext != NULL)
        {
            cgDestroyContext(pCGcontext);
        }

        win->setGLObjectId(osgId, 0);
    }
}

/*----------------------------- class specific ----------------------------*/

void CgFXMaterial::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         detail)
{

    if(0x0000 != (whichField & EffectFileFieldMask))
    {
        this->readEffectFile();
    }

    if(0x0000 != (whichField & EffectStringFieldMask))
    {
        //Inherited::resolveLinks();

        this->processEffectString();

        Window::reinitializeGLObject(getGLId());
    }

    if(0x0000 != (whichField & VariablesFieldMask))
    {
        if(detail != 0x0001)
        {
            updateUniformVariables();
        }
    }

    Inherited::changed(whichField, origin, detail);
}

void CgFXMaterial::dump(      UInt32    ,
                        const BitVector ) const
{
    SLOG << "Dump CgFXMaterial NI" << std::endl;
}

PrimeMaterial *CgFXMaterial::finalize(MaterialMapKey  oKey,
                                      Window         *pWin)
{
    PrimeMaterial *returnValue = NULL;

    if(pWin == NULL)
        return returnValue;

    DrawEnv oEnv;

    oEnv.setWindow(pWin);

    pWin->validateGLObject(getGLId(), &oEnv);

    if(_sfTreatTechniquesAsVariants.getValue() == true)
    {
        if(_mfTechniques[_pTechIdx]->validate(this, &oEnv) == true)
        {   
            return _mfTechniques[_pTechIdx];
        }
    }

    // If the selected technique did not validate, pick the first one that
    // does
    MFTechniquesType::const_iterator tIt  = _mfTechniques.begin();
    MFTechniquesType::const_iterator tEnd = _mfTechniques.end  ();
       
    for(; tIt != tEnd; ++tIt)
    {
        if((*tIt)->validate(this, &oEnv) == true)
        {
            returnValue = *tIt;

            break;
        }
    }

    return returnValue;
}

/*---------------------------------- Access -------------------------------*/


/*------------------------------------ Set --------------------------------*/

bool CgFXMaterial::checkForCgError(const Char8     *szSituation, 
                                         CGcontext  pCGcontext )
{
    CGerror error;

    const Char8 *string = cgGetLastErrorString(&error);

    if(error != CG_NO_ERROR)
    {
        SWARNING << "CgfxMaterial Cgfx Error: " << szSituation << ": " 
                 << string << std::endl;

        if(error == CG_COMPILER_ERROR)
        {
            SWARNING << cgGetLastListing(pCGcontext) << std::endl;
        }

        return true;
    }

    return false;
}

/*------------------------------------ Get --------------------------------*/

void CgFXMaterial::readEffectFile(void)
{
    if(_sfEffectFile.getValue().empty() == true)
        return;

    const Char8 *szTmpCurrentDir = Directory::getCurrent();

    std::string szCurrentDir = szTmpCurrentDir;

    delete [] szTmpCurrentDir;

    PathHandler *pPathHandler = SceneFileHandler::the()->getPathHandler();

    std::string szFullFilePath;

    if(pPathHandler != NULL)
    {
        pPathHandler->pushState();

        pPathHandler->push_backPath(".");
        pPathHandler->push_backPath(szCurrentDir.c_str());

        szFullFilePath = 
            pPathHandler->findFile(_sfEffectFile.getValue().c_str());

        pPathHandler->popState();
    }
    else
    {
        szFullFilePath = _sfEffectFile.getValue();
    }

#if 0
    fprintf(stderr, "Read effect from %s\n",
            szFullFilePath.c_str());
#endif

    std::string szPath = szFullFilePath;

    while(szPath.length()             >   0  &&
          szPath[szPath.length() - 1] != '/' && 
          szPath[szPath.length() - 1] != '\\'  )
    {
        szPath.resize(szPath.length() - 1);
    }

    if(szPath.empty())
        szPath = ".";

#if 0
    fprintf(stderr, "use path %s\n", szPath.c_str());
#endif

    FILE *pFile = fopen(szFullFilePath.c_str(), "rb");

    if(pFile == NULL)
        return;

    fseek(pFile, 0, SEEK_END);

    long lFileSize = ftell(pFile);

    fseek(pFile, 0, SEEK_SET);

    std::string &szData = editEffectString();

    szData.erase();
    szData.resize(lFileSize);

    fread(&(szData[0]), 1, lFileSize, pFile);

    fclose(pFile);
}

void CgFXMaterial::processEffectString(void)
{
    checkForCgError("precheck", _pCGcontext);

    if(_sfEffectString.getValue().empty() == true)
        return;

    _pCGcontext = cgCreateContext();

    if( checkForCgError("Creating Cg Context", _pCGcontext) == true || 
        _pCGcontext                                          == NULL  )
    {
        return;
    }

    cgGLRegisterStates            (_pCGcontext         );
    cgGLSetManageTextureParameters(_pCGcontext, CG_TRUE);

    if(checkForCgError("Registering GL States", _pCGcontext) == true)
    {
        return;
    }

#if 0
#if CG_VERSION_NUM >= 2100
    registerIncludeCallback( (OSGCGcontext)context, this );
    cgSetCompilerIncludeCallback( context, 
                                  (CGIncludeCallbackFunc)cgIncludeCallback );
#endif
#endif

    // we have to transform _compilerOptions to an array of
    // const char* to feed it to cgCreateEffect
    std::vector<const char*> vOptions(_mfCompilerOptions.size());

    for(UInt32 i = 0; i < _mfCompilerOptions.size(); ++i)
        vOptions[i] = _mfCompilerOptions[i].c_str();

    vOptions.push_back(NULL);

    const char **pRawOptions = &(vOptions[0]);

    _pCGeffect = cgCreateEffect(_pCGcontext, 
                                _sfEffectString.getValue().c_str(), 
                                 pRawOptions                      );

    if( checkForCgError("Creating Cg Effect", _pCGcontext) == true ||
       _pCGeffect                                          == NULL )
    {
        return;
    }

    CGtechnique pFirstTechnique = cgGetFirstTechnique(_pCGeffect);

    if(pFirstTechnique == NULL)
        return;

    CGannotation pVarAnno  = 
        cgGetNamedTechniqueAnnotation(pFirstTechnique,
                                      "treatTechniqueAsVariant");

    if(pVarAnno != NULL)
    {
#if 0
        fprintf(stderr, "got var anno\n");
#endif

        int iNVals = 0;

        const int *pTechVar = cgGetBooleanAnnotationValues( pVarAnno,
                                                           &iNVals  );

        if(pTechVar != NULL)
        {
#if 0
            fprintf(stderr, "got tech var : %d\n", *pTechVar);
#endif

            setTreatTechniquesAsVariants(*pTechVar);
        }
    }

    // we might not want to extract the parameters just yet, 
    // check if this is the case and if so, skip parameter extraction
    extractParameters();

    CGtechnique pCGTech = cgGetFirstTechnique(_pCGeffect);

    while(pCGTech != NULL)  
    {
#if 0
        SLOG << "add Technique : "
             << cgGetTechniqueName(pCGTech) << std::endl;
#endif

        CgFXTechniqueUnrecPtr pTechnique = CgFXTechnique::create();

        pTechnique->setTechnique(pCGTech);
        
        this->pushToTechniques(pTechnique);

        pCGTech = cgGetNextTechnique(pCGTech);
    }

    setActiveTechnique(getSelectedTechnique());
}

bool CgFXMaterial::setActiveTechnique(std::string techniqueName)
{
    // if we don't have a valid effect yet, store the string and try
    // again after the effect is loaded up.
    if(_pCGeffect == NULL)
    {
        setSelectedTechnique(techniqueName);
    }

    // is this a valid technique name?
    CGtechnique pTech = cgGetNamedTechnique(_pCGeffect, techniqueName.c_str());

    if(pTech != NULL)
    { // if so, find the index of the technique to use for this material
        for(_pTechIdx = 0; _pTechIdx < _mfTechniques.size(); ++_pTechIdx)
        {
            if(pTech == _mfTechniques[_pTechIdx]->_pCGTechnique)
            {
                setTreatTechniquesAsVariants(true);

                return true;
            }
        }

    // if the technique name wasn't valid, we just use
    // the default behavior (use the first valid technique)
    setTreatTechniquesAsVariants(false);

    return false;
}

/*
  Function to get the names of all of the available techniques for this
  material. 
 */

std::vector<std::string> CgFXMaterial::getAvailableTechniques()
{
    std::vector<std::string> techNames;

    for(UInt32 i = 0; i < _mfTechniques.size(); ++i)
    {
        std::string curTechName = 
            cgGetTechniqueName(_mfTechniques[i]->_pCGTechnique);

        if(curTechName.compare("") != 0) 
            techNames.push_back(curTechName);
    }

    return techNames;
}

void CgFXMaterial::extractParameters(void)
{

#if OSG_CGFX_DUMP_DEBUG
    checkForCgError("extract precheck", _pCGcontext);
#endif

     CGparameter pParam = cgGetFirstEffectParameter(_pCGeffect);

    if(pParam != NULL)
    {

#if OSG_CGFX_DUMP_DEBUG
        fprintf(stderr, "Effect parameter : \n");
#endif

        editStateVariables() = 0x0000;
    }

    while(pParam)
    {
        CGtype oParamType      = cgGetParameterType   (pParam);
        UInt32 uiNumRows       = cgGetParameterRows   (pParam);
        UInt32 uiNumCols       = cgGetParameterColumns(pParam);

        UInt32 uiNumComponents = uiNumRows * uiNumCols;

        std::string szParamName     = 
            cgGetParameterName(pParam)     ? cgGetParameterName(pParam)    : "";

        std::string szParamSemantic = 
            cgGetParameterSemantic(pParam) ? cgGetParameterSemantic(pParam): "";

        if(szParamSemantic.empty() == false)
        {
            bool bFoundSemanticParam = false;

            if(osgStringCaseCmp(szParamSemantic.c_str(), "PROJECTION") == 0)
            {
                editStateVariables() |= CgProjectionMask;

                _vStateVarNames[CgProjection] = szParamName;

                bFoundSemanticParam = true;
            }

            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWPROJECTION"  ) == 0)
            {
                editStateVariables() |= CgModelViewProjectionMask;

                _vStateVarNames[CgModelViewProjection] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWPROJECTION"  ) == 0)
            {
                editStateVariables() |= CgModelViewProjectionMask;

                _vStateVarNames[CgModelViewProjection] = szParamName;

                bFoundSemanticParam = true;
            }


            // -------------
            // World
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLD") == 0)
            {
                editStateVariables() |= CgModelMask;

                _vStateVarNames[CgModel] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLDI") == 0)
            {
                editStateVariables() |= CgModelIMask; 

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDINVERSE") == 0   )
            {
                editStateVariables() |= CgModelIMask;

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLDIT") == 0)
            {
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDINVERSETRANSPOSE") == 0)
            {
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }


            // -------------
            // Model
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODEL") == 0)
            {
                editStateVariables() |= CgModelMask;

                _vStateVarNames[CgModel] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODELI") == 0)
            {
                editStateVariables() |= CgModelIMask; 

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELINVERSE"         ) == 0)
            {
                editStateVariables() |= CgModelIMask;

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODELIT") == 0)
            {
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELINVERSERTRANSPOSE") == 0)
            {
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }


            // -------------
            // WorldView
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLDVIEW") == 0)
            {
                editStateVariables() |= CgModelViewMask; 

                _vStateVarNames[CgModelView] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWI"           ) == 0)
            {
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWINVERSE"     ) == 0)
            {
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWIT"          ) == 0)
            {
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWINVERSETRANSPOSE") == 0)
            {
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;
                
                bFoundSemanticParam = true;
            }


            // -------------
            // ModelView
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODELVIEW") == 0)
            {
                editStateVariables() |= CgModelViewMask; 

                _vStateVarNames[CgModelView] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "ModelVIEWI"           ) == 0)
            {
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWINVERSE"     ) == 0)
            {
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWIT"          ) == 0)
            {
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWINVERSETRANSPOSE") == 0)
            {
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;
                
                bFoundSemanticParam = true;
            }


            // -------------
            // View
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "VIEW") == 0)
            {
                editStateVariables() |= CgViewMask;

                _vStateVarNames[CgView] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "VIEWI") == 0)
            {
                editStateVariables() |= CgViewIMask;

                _vStateVarNames[CgViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "VIEWINVERSE"          ) == 0)
            {
                editStateVariables() |= CgViewIMask;

                _vStateVarNames[CgViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "VIEWIT") == 0)
            {
                editStateVariables() |= CgViewITMask;

                _vStateVarNames[CgViewIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "VIEWINVERSETRANSPOSE" ) == 0)
            {
                editStateVariables() |= CgViewITMask;

                _vStateVarNames[CgViewIT] = szParamName;

                bFoundSemanticParam = true;
            }

            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "VIEWPROJECTION"       ) == 0)
            {
                editStateVariables() |= CgViewProjectionMask;

                _vStateVarNames[CgViewProjection] = szParamName;
                
                bFoundSemanticParam = true;
            } 

            // -------------
            // Time / Timer
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "TIME"       ) == 0)
            {
                editStateVariables() |= CgTimeMask;

                _vStateVarNames[CgTime] = szParamName;

                bFoundSemanticParam = true;
            }

            if(bFoundSemanticParam == true)
            {
                pParam = cgGetNextParameter(pParam);
                continue;
            }
        }

        switch(oParamType)
        {
            case CG_BOOL:
            {
                Int32 val;

                if(cgGetParameterValueir(pParam, 1, &val) == 1)
                {

                    // check where what values we should be using
                    if(this->getParameterValueSource() == CURRENT)
                    {   // check if this is already a variable
                        Int32 tmp;
                        if(this->getUniformVariable(szParamName.c_str(), tmp))
                        {   // if it is, set the variable to value we already
                            // have for it. 
                            cgSetParameterValueir(pParam,uiNumComponents, &tmp);
                        } // otherwise use the default value
                        else 
                        {
                            this->addUniformVariable(szParamName.c_str(), 
                                                     (val > 0)          );
                        }
                    }
                    else // use default value from .cgfx file
                    {
                        this->addUniformVariable(szParamName.c_str(), 
                                                 (val > 0)          );
                    }
                }
            }
            break;

            case CG_INT:
            {
                Int32 val;

                if(cgGetParameterValueir(pParam, 1, &val) == 1)
                {
                    // check where what values we should be using
                    if(this->getParameterValueSource() == CURRENT)
                    {   // check if this is already a variable
                        Int32 tmp;
                        if(this->getUniformVariable(szParamName.c_str(), tmp))
                        {   // if it is, set the variable to value we already
                            // have for it. 
                            cgSetParameterValueir(pParam,uiNumComponents, &tmp);
                        } // otherwise use the default value
                        else
                        {
                            this->addUniformVariable(szParamName.c_str(), 
                                                     val                );
                        }

                    }
                    else // use default value from .cgfx file
                    {
                        this->addUniformVariable(szParamName.c_str(), val);
                    }
                }
            }
            break;
            
            case CG_FLOAT:
            case CG_FLOAT2:
            case CG_FLOAT3:
            case CG_FLOAT4:
            case CG_FLOAT4x4:
            {
                switch(uiNumComponents)
                {
                    case 1:
                    {
                        Real32 val;

                        if(cgGetParameterValuefr(pParam, 1, &val) == 1)
                        {
                            // check where what values we should be using
                            if(this->getParameterValueSource() == CURRENT)
                            {   // check if this is already a variable
                                Real32 tmp;
                                if(this->getUniformVariable(
                                       szParamName.c_str(),
                                       tmp                ))
                                {   // if it is, set the variable to value we
                                    // already have for it. 
                                    cgSetParameterValuefr(pParam,
                                                          uiNumComponents,
                                                          &tmp           );
                                } // otherwise use the default value
                                else 
                                {
                                    this->addUniformVariable(
                                        szParamName.c_str(), 
                                        val                );
                                }
                            }
                            else // use default value from .cgfx file
                            {
                                this->addUniformVariable(szParamName.c_str(),
                                                         val                );
                            }
                        }
                    }
                    break;
                    
                    case 2:
                    {
                        Vec2f val;

                        if(cgGetParameterValuefr(pParam, 
                                                 2, 
                                                 val.getValues()) == 2)
                        {
                            // check where what values we should be using
                            if(this->getParameterValueSource() == CURRENT)
                            {   // check if this is already a variable
                                Vec2f tmp;
                                if(this->getUniformVariable(
                                       szParamName.c_str(),
                                       tmp                ))
                                {   // if it is, set the variable to value we
                                    // already have for it. 
                                    cgSetParameterValuefr(pParam,
                                                          uiNumComponents,
                                                          tmp.getValues());
                                } // otherwise use the default value
                                else
                                {
                                    this->addUniformVariable(
                                        szParamName.c_str(), 
                                        val                );
                                }
                            }
                            else // use default value from .cgfx file
                            {
                                this->addUniformVariable(szParamName.c_str(), 
                                                         val                );
                            }
                        }
                    }
                    break;

                    case 3:
                    {
                        Vec3f val;
                        
                        if(cgGetParameterValuefr(pParam, 
                                                 3, 
                                                 val.getValues()) == 3)
                        {
                            // check where what values we should be using
                            if(this->getParameterValueSource() == CURRENT)
                            {   // check if this is already a variable
                                Vec3f tmp;
                                if(this->getUniformVariable(
                                       szParamName.c_str(),
                                       tmp                ))
                                {   // if it is, set the variable to value we
                                    // already have for it. 
                                    cgSetParameterValuefr(
                                        pParam,
                                        uiNumComponents,
                                        tmp.getValues()       );
                                } // otherwise use the default value
                                else 
                                {
                                    this->addUniformVariable(
                                        szParamName.c_str(), 
                                        val                );
                                }
                            }
                            else // use default value from .cgfx file
                            {
                                this->addUniformVariable(szParamName.c_str(), 
                                                         val                );
                            }
                        }
                    }
                    break;

                    case 4:
                    {
                        Vec4f val;
                        
                        if(cgGetParameterValuefr(pParam, 
                                                 4, 
                                                 val.getValues()) == 4)
                        {
                            // check where what values we should be using
                            if(this->getParameterValueSource() == CURRENT)
                            {   // check if this is already a variable
                                Vec4f tmp;
                                if(this->getUniformVariable(
                                       szParamName.c_str(),
                                       tmp                ))
                                {   // if it is, set the variable to value we
                                    // already have for it. 
                                    cgSetParameterValuefr(pParam,
                                                          uiNumComponents,
                                                          tmp.getValues());
                                } // otherwise use the default value
                                else 
                                {
                                    this->addUniformVariable(
                                        szParamName.c_str(), 
                                        val                );
                                }
                            }
                            else // use default value from .cgfx file
                            {
                                this->addUniformVariable(szParamName.c_str(), 
                                                         val                );
                            }
                        }
                    }
                    break;

                    case 16:
                    {
                        // CHECK cgSetParameterValuefr or cgSetParameterValuefc
                        Matrix val;

                        if(cgGetParameterValuefr(pParam, 
                                                 16, 
                                                 val.getValues()) == 16)
                        {
                            val.transpose();
                            // check where what values we should be using
                            if(this->getParameterValueSource() == CURRENT)
                            {   // check if this is already a variable
                                Vec4f tmp;
                                if(this->getUniformVariable(
                                       szParamName.c_str(),
                                       tmp                ))
                                {   // if it is, set the variable to value we
                                    // already have for it. 
                                    cgSetParameterValuefr(pParam,
                                                          uiNumComponents,
                                                          tmp.getValues());
                                } // otherwise use the default value
                                else 
                                {
                                    this->addUniformVariable(
                                        szParamName.c_str(), 
                                        val                );
                                }
                            }
                            else // use default value from .cgfx file
                            {
                                this->addUniformVariable(szParamName.c_str(), 
                                                         val                );
                            }
                        }
                    }
                    break;
                }
            }
            break;
 
            case CG_TEXTURE:
                break;

            case CG_SAMPLER1D:
            case CG_SAMPLER2D:
            case CG_SAMPLER3D:
            case CG_SAMPLERRECT:
            case CG_SAMPLERCUBE:
            {
                CgFXVariableTexObjUnrecPtr pVar; 
                std::string                szFilename;
                bool                       varIsInitialized = false;
                bool                       readFile         = true;

                if(this->getParameterValueSource() == CURRENT)
                {
                    if(this->getVariable(szParamName.c_str()) != NULL)
                    {   // use the specified texture
                        szFilename = 
                            dynamic_cast<const CgFXVariableTexObj *>(
                                this->getVariable(
                                    szParamName.c_str()))->getFilePath();

                        varIsInitialized = true;

                        for(UInt32 i = 0; i < getMFTextures()->size(); ++i)
                        {
                            if(szParamName.compare(
                                   getName(getTextures(i))) == 0)
                            {   // image file is already loaded and ready to
                                // use, so skip reading it again. 
                                readFile = false;
                                break;
                            }
                        }
                    }
                }

                if(szFilename.empty())
                {
                    CGannotation pAnno = cgGetNamedParameterAnnotation(pParam, 
                                                                       "File");
                    if(pAnno == NULL)
                    {
                        pAnno = cgGetNamedParameterAnnotation(pParam, 
                                                              "ResourceName");
                    }

                    if(pAnno != NULL)
                    {
                        szFilename = cgGetStringAnnotationValue(pAnno);
                    }
                }

                if(szFilename.empty())
                {
                    CGstateassignment pSamplerState = 
                        cgGetFirstSamplerStateAssignment(pParam);

                    if(pSamplerState != NULL)
                    {
                        // cgGetSamplerStateAssignmentValue
                        CGparameter pTParam = 
                            cgGetTextureStateAssignmentValue(pSamplerState);

                        if(pTParam != NULL)
                        {
                            CGtype pTParamType = cgGetParameterType(pTParam);
                        
                            // get tweakable parameters
                            if(cgGetFirstParameterAnnotation(pTParam) != NULL &&
                               pTParamType == CG_TEXTURE                       )
                            {
                                CGannotation pAnno = 
                                    cgGetNamedParameterAnnotation(pTParam, 
                                                                  "File");
                                if(pAnno == NULL)
                                {
                                    pAnno = 
                                        cgGetNamedParameterAnnotation(
                                            pTParam, 
                                            "ResourceName");
                                }
                                
                                if(pAnno != NULL)
                                {
                                    szFilename = 
                                        cgGetStringAnnotationValue(pAnno);
                                }
                            }
                        }
                    }
                }

                if(readFile)
                {
                    Int32 uiSamplerId = -1;

                    ImageUnrecPtr pImg = 
                        ImageFileHandler::the()->read(szFilename.c_str());

                    if(pImg != NULL)
                    {
                        TextureObjChunkUnrecPtr pTexO = 
                            TextureObjChunk::create();

                        setName(pTexO, szParamName);

                        pTexO->setImage(pImg);

                        if(varInitialized == false)
                        {
                            pVar = CgFXVariableTexObj::create();

                            pVar->setName    (szParamName);
                            pVar->setValue   (uiSamplerId);
                            this->addVariable(pVar       );
                        }

                        this->pushToTextures(pTexO);
                    }
                }
            }
            break;
            
            case CG_ARRAY:
            {
            }
            break;

            case CG_STRUCT:
            {
            }
            break;

            case CG_STRING:
            {
            }
            break;

            default:
            {
                FWARNING(("CgFXMaterial : Unsupported parameter (%s) type "
                          "(%d)!\n", 
                          szParamName.c_str(), 
                          oParamType));
            }
            break;
        }

        pParam = cgGetNextParameter(pParam);
    }

#if OSG_CGFX_DUMP_DEBUG
    checkForCgError("extract postcheck", _pCGcontext);
#endif
}
   
void CgFXMaterial::updateUniformVariables(void)
{
#if OSG_CGFX_DUMP_DEBUG
    checkForCgError("update precheck", _pCGcontext);
#endif

    if(_pCGeffect == NULL) 
        return; // can't update variables w/out a program.

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
    ShaderProgramVariables::MFVariablesType::const_iterator mVarIt  =
        pMFVars->begin();
    ShaderProgramVariables::MFVariablesType::const_iterator mVarEnd =
        pMFVars->end  ();

    ShaderProgramVariables::MFVariableChangedType::iterator mVarChgIt =
        pMFVarChg->begin();

    for(; mVarIt != mVarEnd; ++mVarIt, ++mVarChgIt)
    {
        ShaderVariable *pVar = *mVarIt;

        if(pVar == NULL)
            continue;

        if(*mVarChgIt == false)
            continue;

        *mVarChgIt = false;

        CGparameter pParam = 
            cgGetNamedEffectParameter(_pCGeffect, 
                                      pVar->getName().c_str());

        switch(pVar->getTypeId())
        {
            case ShaderVariable::SHVTypeBool: 
            {
                ShaderVariableBool *p =
                    dynamic_cast<ShaderVariableBool *>(pVar);

                cgSetParameter1i(pParam, p->getValue() ? 1 : 0);
            }
            break;

            case ShaderVariable::SHVTypeInt:
            {
                ShaderVariableInt *p =
                    dynamic_cast<ShaderVariableInt *>(pVar);

                cgSetParameter1i(pParam, p->getValue());
            }
            break;

            case ShaderVariable::SHVTypeReal:
            {
                ShaderVariableReal *p =
                    dynamic_cast<ShaderVariableReal *>(pVar);

                cgSetParameter1f(pParam, p->getValue());
            }
            break;

            case ShaderVariable::SHVTypeVec2f:
            {
                ShaderVariableVec2f *p =
                    dynamic_cast<ShaderVariableVec2f *>(pVar);

                cgSetParameter2fv(pParam, p->getValue().getValues());
            }
            break;

            case ShaderVariable::SHVTypeVec3f:
            {
                ShaderVariableVec3f *p =
                    dynamic_cast<ShaderVariableVec3f *>(pVar);

                cgSetParameter3fv(pParam, p->getValue().getValues());
            }
            break;

            case ShaderVariable::SHVTypeVec4f:
            {
                ShaderVariableVec4f *p =
                    dynamic_cast<ShaderVariableVec4f *>(pVar);

                cgSetParameter4fv(pParam, p->getValue().getValues());
            }
            break;

            case ShaderVariable::SHVTypeMatrix:
            {
                ShaderVariableMatrix *p =
                    dynamic_cast<ShaderVariableMatrix *>(pVar);

                cgSetMatrixParameterfr(pParam, p->getValue().getValues());
            }
            break;

            default:
                break;
        };
    }

#if OSG_CGFX_DUMP_DEBUG
    checkForCgError("update postcheck", _pCGcontext);
#endif
}

OSG_END_NAMESPACE
