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
     Inherited (    ),
    _pCGcontext(NULL),
    _pCGeffect (NULL)
{
    this->markFieldsThreadLocal ((Self::MapCacheFieldMask        | 
                                  Self::FallbackMaterialFieldMask));
    this->markFieldsClusterLocal((Self::MapCacheFieldMask        | 
                                  Self::FallbackMaterialFieldMask));
}

CgFXMaterial::CgFXMaterial(const CgFXMaterial &source) :
     Inherited (source),
    _pCGcontext(NULL  ),
    _pCGeffect (NULL  )
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
    if(mode == Window::destroy)
    {
        Window::GLObjectId glId = pEnv->getWindow()->getGLObjectId(osgId);

        CGcontext pCGcontext = reinterpret_cast<CGcontext>(glId);

        fprintf(stderr, "destroying gl id %"PRIUSize"\n",
                glId);

        if(pCGcontext != NULL)
        {
            cgDestroyContext(pCGcontext);
        }
    }
}

/*----------------------------- class specific ----------------------------*/

void CgFXMaterial::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         detail)
{
    if(0x0000 != (whichField & EffectStringFieldMask))
    {
        Inherited::resolveLinks();

        this->processEffectString();

        Window::reinitializeGLObject(getGLId());
    }

    if(0x0000 != (whichField & EffectFileFieldMask))
    {
        this->readEffectFile();
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
    }
    else
    {
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

    CGparameter pParam = cgGetFirstEffectParameter(_pCGeffect);

    if(pParam != NULL)
    {
#if OSG_CGFX_DUMP_DEBUG
        fprintf(stderr, "Effect parameter : \n");
#endif

        editStateVariables() = 0x0000;

        extractParameters(pParam);
    }

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
}

void CgFXMaterial::extractParameters(CGparameter pBaseParam)
{
#if OSG_CGFX_DUMP_DEBUG
    checkForCgError("extract precheck", _pCGcontext);
#endif

    CGparameter pParam = pBaseParam;

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

#if 0
        fprintf(stderr, "    %s | %s | %d %d : %d\n",
                szParamName    .c_str(),
                szParamSemantic.c_str(),
                uiNumRows,
                uiNumCols,
                uiNumComponents);
#endif

        if(szParamSemantic.empty() == false)
        {
            bool bFoundSemanticParam = false;

            if(osgStringCaseCmp(szParamSemantic.c_str(), "PROJECTION") == 0)
            {
//                fprintf(stderr, "Use Projection\n");
                editStateVariables() |= CgProjectionMask;

                _vStateVarNames[CgProjection] = szParamName;

                bFoundSemanticParam = true;
            }

            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWPROJECTION"  ) == 0)
            {
//                fprintf(stderr, "Use WorldViewProjection\n");
                editStateVariables() |= CgModelViewProjectionMask;

                _vStateVarNames[CgModelViewProjection] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWPROJECTION"  ) == 0)
            {
//                fprintf(stderr, "Use ModelViewProjection\n");
                editStateVariables() |= CgModelViewProjectionMask;

                _vStateVarNames[CgModelViewProjection] = szParamName;

                bFoundSemanticParam = true;
            }


            // -------------
            // World
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLD") == 0)
            {
//                fprintf(stderr, "Use World\n");
                editStateVariables() |= CgModelMask;

                _vStateVarNames[CgModel] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLDI") == 0)
            {
//                fprintf(stderr, "Use WorldI\n");
                editStateVariables() |= CgModelIMask; 

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDINVERSE") == 0   )
            {
//                fprintf(stderr, "Use WorldInverse\n");
                editStateVariables() |= CgModelIMask;

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLDIT") == 0)
            {
//                fprintf(stderr, "Use WorldIT\n");
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDINVERSETRANSPOSE") == 0)
            {
//                fprintf(stderr, "Use WorldInverseTranspose\n");
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }


            // -------------
            // Model
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODEL") == 0)
            {
//                fprintf(stderr, "Use Model\n");
                editStateVariables() |= CgModelMask;

                _vStateVarNames[CgModel] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODELI") == 0)
            {
//                fprintf(stderr, "Use ModelI\n");
                editStateVariables() |= CgModelIMask; 

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELINVERSE"         ) == 0)
            {
//                fprintf(stderr, "Use ModelInverse\n");
                editStateVariables() |= CgModelIMask;

                _vStateVarNames[CgModelI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODELIT") == 0)
            {
//                fprintf(stderr, "Use ModelIT\n");
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELINVERSERTRANSPOSE") == 0)
            {
//                fprintf(stderr, "Use ModelInverseTranspose\n");
                editStateVariables() |= CgModelITMask;

                _vStateVarNames[CgModelIT] = szParamName;

                bFoundSemanticParam = true;
            }


            // -------------
            // WorldView
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "WORLDVIEW") == 0)
            {
//                fprintf(stderr, "Use WorldView\n");
                editStateVariables() |= CgModelViewMask; 

                _vStateVarNames[CgModelView] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWI"           ) == 0)
            {
//                fprintf(stderr, "Use WorldViewI\n");
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWINVERSE"     ) == 0)
            {
//                fprintf(stderr, "Use WorldViewInverse\n");
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWIT"          ) == 0)
            {
//                fprintf(stderr, "Use WorldViewIT\n");
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "WORLDVIEWINVERSETRANSPOSE") == 0)
            {
//                fprintf(stderr, "Use WorldViewInverseTranspose\n");
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;
                
                bFoundSemanticParam = true;
            }


            // -------------
            // ModelView
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "MODELVIEW") == 0)
            {
//                fprintf(stderr, "Use ModelView\n");
                editStateVariables() |= CgModelViewMask; 

                _vStateVarNames[CgModelView] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "ModelVIEWI"           ) == 0)
            {
//                fprintf(stderr, "Use ModelViewI\n");
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWINVERSE"     ) == 0)
            {
//                fprintf(stderr, "Use ModelViewInverse\n");
                editStateVariables() |= CgModelViewIMask;

                _vStateVarNames[CgModelViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWIT"          ) == 0)
            {
//                fprintf(stderr, "Use ModelViewIT\n");
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "MODELVIEWINVERSETRANSPOSE") == 0)
            {
//                fprintf(stderr, "Use ModelViewInverseTranspose\n");
                editStateVariables() |= CgModelViewITMask;

                _vStateVarNames[CgModelViewIT] = szParamName;
                
                bFoundSemanticParam = true;
            }


            // -------------
            // View
            // -------------
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "VIEW") == 0)
            {
//                fprintf(stderr, "Use View\n");
                editStateVariables() |= CgViewMask;

                _vStateVarNames[CgView] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "VIEWI") == 0)
            {
//                fprintf(stderr, "Use ViewI\n");
                editStateVariables() |= CgViewIMask;

                _vStateVarNames[CgViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "VIEWINVERSE"          ) == 0)
            {
//                fprintf(stderr, "Use ViewInverse\n");
                editStateVariables() |= CgViewIMask;

                _vStateVarNames[CgViewI] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), "VIEWIT") == 0)
            {
//                fprintf(stderr, "Use ViewIT\n");
                editStateVariables() |= CgViewITMask;

                _vStateVarNames[CgViewIT] = szParamName;

                bFoundSemanticParam = true;
            }
            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "VIEWINVERSETRANSPOSE" ) == 0)
            {
//                fprintf(stderr, "Use ViewInverseTranspose\n");
                editStateVariables() |= CgViewITMask;

                _vStateVarNames[CgViewIT] = szParamName;

                bFoundSemanticParam = true;
            }

            else if(osgStringCaseCmp(szParamSemantic.c_str(), 
                                     "VIEWPROJECTION"       ) == 0)
            {
//                fprintf(stderr, "Use ViewProjection\n");
                editStateVariables() |= CgViewProjectionMask;

                _vStateVarNames[CgViewProjection] = szParamName;
                
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
#if 0
                    printf("adding default parameter: '%s' (%d)\n", 
                           szParamName.c_str(), val);
#endif

                    this->addUniformVariable(szParamName.c_str(), (val > 0));
                }
            }
            break;

            case CG_INT:
            {
                Int32 val;

                if(cgGetParameterValueir(pParam, 1, &val) == 1)
                {
#if 0
                    printf("adding default parameter: '%s' (%d)\n", 
                           szParamName.c_str(), val);
#endif

                    this->addUniformVariable(szParamName.c_str(), val);
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
#if 0
                            printf("adding default parameter: '%s' (%f)\n", 
                                   szParamName.c_str(), val);
#endif

                            this->addUniformVariable(szParamName.c_str(), val);
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
#if 0
                            printf("adding default parameter: '%s' (%f, %f)\n",
                                   szParamName.c_str(), 
                                   val[0], 
                                   val[1]);
#endif

                            this->addUniformVariable(szParamName.c_str(), val);
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
#if 0
                            printf("adding default parameter: '%s' "
                                   "(%f, %f, %f)\n", 
                                   szParamName.c_str(), 
                                   val[0], 
                                   val[1], 
                                   val[2]);
#endif

                            this->addUniformVariable(szParamName.c_str(), val);
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
#if 0
                            printf("adding default parameter: '%s' "
                                   "(%f, %f, %f, %f)\n", 
                                   szParamName.c_str(), 
                                   val[0], 
                                   val[1], 
                                   val[2], 
                                   val[3]);
#endif

                            this->addUniformVariable(szParamName.c_str(), val);
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
#if 0
                            printf("adding default parameter: "
                                   "'%s' (%f, %f, %f, %f,  "
                                   "%f, %f, %f, %f,  %f, %f, %f, %f,  "
                                   "%f, %f, %f, %f)\n",
                                   szParamName.c_str(), 
                                   val[0][0], val[0][1], val[0][2], val[0][3],
                                   val[1][0], val[1][1], val[1][2], val[1][3],
                                   val[2][0], val[2][1], val[2][2], val[2][3],
                                   val[3][0], val[3][1], val[3][2], val[3][3]);
#endif
                            
                            val.transpose();

                            this->addUniformVariable(szParamName.c_str(), val);
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
                std::string  szFilename;

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

#if 0
                fprintf(stderr, "Got filename from sampler %s\n",
                        szFilename.c_str());
#endif

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
                
#if 0
                fprintf(stderr, "Got filename from sampler state %s\n",
                        szFilename.c_str());
#endif

                Int32 uiSamplerId = -1;

                ImageUnrecPtr pImg = 
                    ImageFileHandler::the()->read(szFilename.c_str());

                if(pImg != NULL)
                {
                    TextureObjChunkUnrecPtr pTexO = TextureObjChunk::create();

                    setName(pTexO, szParamName);

                    pTexO->setImage(pImg);

                    CgFXVariableTexObjUnrecPtr pVar = 
                        CgFXVariableTexObj::create();

                    pVar->setName (szParamName);
                    pVar->setValue(uiSamplerId);

                    this->addVariable   (pVar );
                    this->pushToTextures(pTexO);
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
