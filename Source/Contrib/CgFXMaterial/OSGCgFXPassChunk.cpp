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

#ifdef OSG_LINUX_TYPES
#include <inttypes.h>
#endif
#include <stdlib.h>
#include <stdio.h>

#include <set>

// CgFX

#include "OSGConfig.h"

#include "OSGCgFXPassChunk.h"
#include "OSGCgFXMaterial.h"
#include "OSGDrawEnv.h"

#if CG_VERSION_NUM < 1500
#error CGFXMaterial2 needs Cg 1.5 or later
#endif

OSG_BEGIN_NAMESPACE

/*! \class osg::CgFXPassChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

// Techniques

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CgFXPassChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CgFXPassChunk::CgFXPassChunk(void) :
     Inherited(    ),
    _pCGPass  (NULL)
{
}

CgFXPassChunk::CgFXPassChunk(const CgFXPassChunk &source) :
     Inherited(source),
    _pCGPass  (NULL  )
{
}

CgFXPassChunk::~CgFXPassChunk(void)
{
}


/*----------------------------- class specific ----------------------------*/

void CgFXPassChunk::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         detail)
{
    Inherited::changed(whichField, origin, detail);
}

void CgFXPassChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CgFXPassChunk NI" << std::endl;
}


bool CgFXPassChunk::isTransparent(void) const
{
    // HACK need to test this!
    return true;
    //return false;
}

void CgFXPassChunk::activate(DrawEnv       *pEnv, 
                             State         *pState,
                             StateOverride *pOverride)
{
    cgSetPassState(_pCGPass);

    pEnv->setActiveShader(TypeTraits<UInt32>::BitsSet);

    updateStateUniforms(pEnv);
}

void CgFXPassChunk::deactivate(DrawEnv       *pEnv, 
                               State         *pState,
                               StateOverride *pOverride)
{
    cgResetPassState(_pCGPass);

    pEnv->setActiveShader(TypeTraits<UInt32>::BitsClear);

    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    GLfloat nul[4]={0,0,0,0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, nul);
    glLightfv(GL_LIGHT0, GL_SPECULAR, nul);
}

void CgFXPassChunk::changeFrom(DrawEnv       *pEnv, 
                               State         *pNewState,
                               StateOverride *pNewOverride,
                               State         *pOldState,
                               StateOverride *pOldOverride)
{
    cgSetPassState(_pCGPass);

    updateStateUniforms(pEnv);
}

void CgFXPassChunk::updateStateUniforms(DrawEnv  *pEnv)
{
    CgFXMaterial *pMat = _sfMaterial.getValue();

    OSG_ASSERT(pMat != NULL);

          CGeffect     pEffect        = pMat->getEffect        ();
          UInt32       uiStateVars    = pMat->getStateVariables();
    const std::string *vStateVarNames = pMat->getStateVarNames ();

          UInt32       uiMask         = 0x0001;


    OSG_ASSERT(pEffect != NULL);

    Matrix mObj2World = pEnv->getObjectToWorld();

    std::string szTmp;

    for(UInt32 i = 0; i < CgFXMaterial::NumStateVars; ++i)
    {
        if(uiStateVars == 0x0000)
            break;
        
        switch(uiStateVars & uiMask)
        {
            case CgFXMaterial::CgProjectionMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgProjection].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(
                    pMatrixParam,
                    pEnv->_openGLState.getProjection().getValues());
            }
            break;

            case CgFXMaterial::CgModelViewProjectionMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModelViewProjection].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mWorld2Scrn = pEnv->getWorldToScreen();

                mWorld2Scrn.mult(mObj2World);                

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mWorld2Scrn.getValues());
            }
            break;


            // -------------
            // Model | World
            // -------------
            case CgFXMaterial::CgModelMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModel].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mObj2World.getValues());
            }
            break;
            case CgFXMaterial::CgModelIMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModelI].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mModelI = mObj2World;

                mModelI.invert();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mModelI.getValues());
           }
            break;
            case CgFXMaterial::CgModelITMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgModelIT].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mModelIT = mObj2World;

                mModelIT.invert   ();
                mModelIT.transpose();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mModelIT.getValues());
            }
            break;


            // ---------------------
            // ModelView | WorldView
            // ---------------------
            case CgFXMaterial::CgModelViewMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[CgFXMaterial::CgModelView].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.mult(mObj2World);
                
                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;
            case CgFXMaterial::CgModelViewIMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[CgFXMaterial::CgModelViewI].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.mult(mObj2World);
                mCameraViewing.invert();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;
            case CgFXMaterial::CgModelViewITMask:
            {
                CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[CgFXMaterial::CgModelViewIT].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.mult     (mObj2World);
                mCameraViewing.invert   (          );
                mCameraViewing.transpose(          );

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;


            // -------------
            // View
            // -------------
            case CgFXMaterial::CgViewMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgView].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         pEnv->getCameraViewing().getValues());
            }
            break;
            case CgFXMaterial::CgViewIMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgViewI].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                OSG::Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.invert();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;
            case CgFXMaterial::CgViewITMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgViewIT].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                OSG::Matrix mCameraViewing = pEnv->getCameraViewing();

                mCameraViewing.invert   ();
                mCameraViewing.transpose();

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         mCameraViewing.getValues());
            }
            break;


            case CgFXMaterial::CgViewProjectionMask:
            {
                 CGparameter pMatrixParam = 
                    cgGetNamedEffectParameter(
                        pEffect, 
                        vStateVarNames[
                            CgFXMaterial::CgViewProjection].c_str());

                OSG_ASSERT(pMatrixParam != NULL);

                cgGLSetMatrixParameterfc(pMatrixParam,
                                         pEnv->getWorldToScreen().getValues());
            }
            break;

            default:
                break;
        };

        uiStateVars &= ~uiMask;
        uiMask      =   uiMask << 1;
    }
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CgFXPassChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CgFXPassChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CgFXPassChunk::operator == (const StateChunk &other) const
{
    CgFXPassChunk const *tother = dynamic_cast<CgFXPassChunk const*>(&other);

    if(!tother)
        return false;

#if 0
    if(_effectFile != tother->_effectFile)
        return false;
#endif

    return true;
}

bool CgFXPassChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

OSG_END_NAMESPACE

