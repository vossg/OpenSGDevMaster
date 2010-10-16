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

#include "OSGCgFXTechnique.h"
#include "OSGCgFXPassChunk.h"
#include "OSGCgFXMaterial.h"

#include "OSGWindow.h"
#include "OSGDrawEnv.h"
#include "OSGNameAttachment.h"

#include "OSGCgFXVariableTexObj.h"

OSG_BEGIN_NAMESPACE

/*! \class osg::CGFXTechnique
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CgFXTechnique::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void CgFXTechnique::resolveLinks(void)
{
    _pCGTechnique = NULL;
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CgFXTechnique::CgFXTechnique(void) :
     Inherited         (    ),
    _pCGTechnique      (NULL),
    _uiValidationState(0    )
{
}

CgFXTechnique::CgFXTechnique(const CgFXTechnique &source) :
     Inherited        (source),
    _pCGTechnique     (NULL  ),
    _uiValidationState(0     )
{
}

CgFXTechnique::~CgFXTechnique(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CgFXTechnique::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         detail)
{
    Inherited::changed(whichField, origin, detail);
}

void CgFXTechnique::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CgFXTechnique NI" << std::endl;
}


/*---------------------------------- Access -------------------------------*/

void CgFXTechnique::rebuildState(void)
{
}

bool CgFXTechnique::isTransparent(void) const
{
    // not sure, CHECK_TOOLBOX_MERGE
    //return true;
    
    return false;
}

UInt32 CgFXTechnique::getNPasses(void)
{
    return _mfRenderPassStates.size();
}

State *CgFXTechnique::getState(UInt32 index)
{
    OSG_ASSERT(index < _mfRenderPassStates.size());

    return _mfRenderPassStates[index];
}

/*------------------------------------ Set --------------------------------*/

bool CgFXTechnique::validate(CgFXMaterial *pMat, 
                             DrawEnv      *pEnv)
{
    if(0x00 == (_uiValidationState & ValidationTried))
    {
#if 0
        fprintf(stderr, "Validate %p\n", _pCGTechnique);
#endif

        _uiValidationState = 0x03;

#if 0
        if(pWin != NULL)
        {
            pWin->activate();
        }
#endif

        if(_pCGTechnique                      == NULL     || 
           cgValidateTechnique(_pCGTechnique) == CG_FALSE  )
        {
            _uiValidationState = 0x02;
        }
        else
        {
            const CgFXMaterial::MFTexturesType *pTextures = 
                pMat->getMFTextures();

            CGpass pPass = cgGetFirstPass(_pCGTechnique);

            for(UInt32 i = 0; i < pTextures->size(); ++i)
            {
                const Char8 *szTexParamName = getName((*pTextures)[i]);
                      Int32  iTexParamVal   = -1;

                const ShaderVariable *pVar = pMat->getVariable(szTexParamName);
                
                OSG_ASSERT(pVar != NULL);

                const CgFXVariableTexObj *pTexVar = 
                    static_cast<const CgFXVariableTexObj *>(pVar);

                OSG_ASSERT(pTexVar != NULL);

                iTexParamVal = pTexVar->getValue();

                if(iTexParamVal == -1)
                {
                    CGparameter pParam = 
                        cgGetNamedEffectParameter(pMat->getEffect(), 
                                                  szTexParamName);

                    (*pTextures)[i]->activate(pEnv, 0);
                    
                    Window::GLObjectId texObjId = 
                        pEnv->getWindow()->getGLObjectId(
                            (*pTextures)[i]->getGLId());

                    cgGLSetTextureParameter(pParam, texObjId);
                    cgSetSamplerState      (pParam          );

                    CgFXVariableTexObj *pTexVarW = 
                        const_cast<CgFXVariableTexObj *>(pTexVar);
                    
                    pTexVarW->setValue(texObjId);

                    (*pTextures)[i]->deactivate(pEnv);
                }
            }

            int count = 0;
            
            while(pPass)
            {
                StateUnrecPtr         pState = State        ::create();
                CgFXPassChunkUnrecPtr pChunk = CgFXPassChunk::create();

                pChunk->setPass    (pPass);
                pChunk->setMaterial(pMat );

                pState->addChunk(pChunk);

                this->addPassState(pState);

                pPass = cgGetNextPass(pPass);
                count++;
            }

            pMat->updateUniformVariables();
        }

#if 0
        if(_pCGTechnique != NULL)
        {
            fprintf(stderr, "Validated technique %s : %x\n",
                    cgGetTechniqueName(_pCGTechnique),
                    UInt32(_uiValidationState));
        }
#endif

#if 0
        if(pWin != NULL)
        {
            pWin->deactivate();
        }
#endif
    }

    return (_uiValidationState & TechniqueValid);
}

/*------------------------------------ Get --------------------------------*/

OSG_END_NAMESPACE
