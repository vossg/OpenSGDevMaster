/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGDRAWENV_H_
#define _OSGDRAWENV_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGMatrix.h"
#include "OSGGLEXT.h"
#include "OSGStatCollector.h"
#include "OSGContainerForwards.h"

#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

class RenderActionBase;
class RenderPartition;
class Window;
class State;
class StateOverride;

/*! \ingroup GrpSystemRenderingBackendBase
    \ingroup GrpLibOSGSystem

   \brief Old OpenGL State Uniforms so this can be passed to the shader.
 */

class OpenGLState
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

          void    setModelView          (const Matrix   &matrix);
    const Matrix &getModelView          (      void            ) const;

          void    setProjection         (const Matrix   &matrix);
    const Matrix &getProjection         (      void            ) const;

#ifdef OSG_OGL_COREONLY
    const Matrix &getModelViewProjection(      void            ) const;
    const Matrix &getNormalMatrix       (      void            ) const;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OpenGLState(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OpenGLState(void);

    /*! \}                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#ifdef OSG_OGL_COREONLY
    Matrix _mModelViewProjection;
    Matrix _mNormalMatrix;
#endif
    Matrix _mProjection;
    Matrix _mModelView;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    OpenGLState(const OpenGLState &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const OpenGLState &source);
};

/*! \ingroup GrpSystemRenderingBackendBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING DrawEnv
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef RenderFunctor    DrawFunctor;

    typedef RenderActionBase RAction;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Vars                                    */
    /*! \{                                                                 */

    OpenGLState _openGLState;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void   setWindow            (      Window   *pWindow       );
    void   setSGNode            (      Node     *pSGNode       );

    void   setupProjection      (const Matrix   &projection,
                                 const Matrix   &translation   );
    void   setupViewing         (const Matrix   &matrix        );
    void   setObjectToWorld     (const Matrix   &matrix        );

    void   setCameraNear        (const Real32   &camNear       );
    void   setCameraFar         (const Real32   &camFar        );

    void   setActiveTexTarget   (      UInt32    uiSlot,
                                       GLenum    uiTarget      );

    void   setActiveShader      (      UInt32    uiActiveShader);
    UInt32 getActiveShader      (      void                    );

    UInt32 getRequiredOGLFeature(      void                    );
    void   addRequiredOGLFeature(      UInt32    uiFeatureMask );
    void   subRequiredOGLFeature(      UInt32    uiFeatureMask );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    const Matrix        &getCameraProjection     (void         ) const;
    const Matrix        &getCameraProjectionTrans(void         ) const;
    const Matrix        &getCameraDecoration     (void         ) const;

    const Matrix        &getCameraViewing        (void         ) const;

    //CamViewing^-1
    const Matrix        &getCameraToWorld        (void         ) const;

    const Matrix        &getObjectToWorld        (void         ) const;

    const Matrix        &getWorldToScreen        (void         ) const;

          Real32         getCameraNear           (void         ) const;
          Real32         getCameraFar            (void         ) const;

          Window        *getWindow               (void         ) const;
          Node          *getSGNode               (void         ) const;

          GLenum         getActiveTexTarget      (UInt32 uiSlot) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void           setStatCollector(StatCollector *pStatCollector);
    StatCollector *getStatCollector(void                         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    const Matrix   &getVPCameraFullProjection (void         ) const;
    const Matrix   &getVPCameraProjection     (void         ) const;
    const Matrix   &getVPCameraProjectionTrans(void         ) const;

    const Matrix   &getVPCameraViewing        (void         ) const;

    //VPCamViewing^-1
    const Matrix   &getVPCameraToWorld        (void         ) const; 

    const Matrix   &getVPWorldToScreen        (void         ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void setVPCameraMatrices     (const Matrix  &mFullprojection,
                                  const Matrix  &mProjection,
                                  const Matrix  &mProjectionTrans,
                                  const Matrix  &mViewing,
                                  const Matrix  &mToWorld,
                                  const Matrix  &mWorldToScreen  );
    
    void initVPMatricesFromCamera(void                           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */


    UInt32 getNumStateChanges      (void) const;
    UInt32 getNumShaderChanges     (void) const;
    UInt32 getNumShaderParamChanges(void) const;

    void   incNumShaderChanges     (void);
    void   incNumShaderParamChanges(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void clearState(void);

    void activateState  (State         *pNewState,
                         StateOverride *pNewStateOverride);

    void deactivateState(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void  setViewportDimension(Int32  iPixelLeft,
                               Int32  iPixelBottom,
                               Int32  iPixelRight,
                               Int32  iPixelTop,
                               bool   bFull        );

    Int32 getPixelLeft        (void                ) const;
    Int32 getPixelRight       (void                ) const;
    Int32 getPixelBottom      (void                ) const;
    Int32 getPixelTop         (void                ) const;

    Int32 getPixelWidth       (void                ) const;
    Int32 getPixelHeight      (void                ) const;
    bool  getFull             (void                ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

          void     setTileFullSize         (const Vec2u &uiTileFullSize);
          void     setTileRegion           (const Vec4f &vTileRegion   );

    const Vec2u   &getTileFullSize         (void                       ) const;
    const Vec4f   &getTileRegion           (void                       ) const;

          Matrix   calcTileDecorationMatrix(void                       ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Int32 getDrawerId  (void     ) const;
    void  setDrawerId  (Int32 iId);
          
    Int32 getDrawableId(void     ) const;
    void  setDrawableId(Int32 iId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void   setLightState(UInt32 uiState);
    UInt32 getLightState(void          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    template<class ValuePtr>
    ValuePtr getData(Int32 iSlotId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DrawEnv(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawEnv(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    RAction       *_pRenderAction;

    Matrix         _cameraProjection;
    Matrix         _cameraProjectionTrans;
    Matrix         _cameraViewing;
    Matrix         _cameraToWorld;
    Matrix         _cameraDecoration;

    Matrix         _objectToWorld;
    Matrix         _worldToScreen;

    Matrix         _vpCameraFullProjection;
    Matrix         _vpCameraProjection;
    Matrix         _vpCameraProjectionTrans;
    Matrix         _vpCameraViewing;
    Matrix         _vpCameraToWorld;
    Matrix         _vpWorldToScreen;

    Real32         _cameraNear;
    Real32         _cameraFar;

    Int32          _iPixelLeft;
    Int32          _iPixelRight;
    Int32          _iPixelBottom;
    Int32          _iPixelTop;

    Vec2u          _uiTileFullSize;
    Vec4f          _vTileRegion;

    bool           _bFull;

    Int32          _iDrawerId;
    Int32          _iDrawableId;

    UInt32         _uiLightState;

    Window        *_pWindow;
    Node          *_pSGNode;

    State         *_pActiveState;
    StateOverride *_pActiveStateOverride;

    UInt32         _uiNumStateChanges;
    UInt32         _uiNumShaderChanges;
    UInt32         _uiNumShaderParamChanges;
    StatCollector *_pStatCollector;

    GLenum         _aActiveTexTargets[osgMaxTexImages];
    UInt32         _uiActiveShader;
    UInt32         _uiRequiredOGLFeature;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    void activate  (State         *pState     );
    void activate  (State         *pState,
                    StateOverride *pOverride  );

    void changeTo  (State         *pState,
                    State         *old        );

    void changeTo  (State         *pState,
                    State         *old,
                    StateOverride *oldOverride);

    void changeTo  (State         *pState,
                    StateOverride *pOverride,
                    State         *old);

    void changeTo  (State         *pState,
                    StateOverride *pOverride,
                    State         *old,
                    StateOverride *oldOverride );

    void deactivate(State         *pState);
    void deactivate(State         *pState,
                    StateOverride *pOverride   );

    void update     (State         *pState);
    void update     (State         *pState,
                     StateOverride *pOverride  );
    void updateChunk(State         *pState);
    void updateChunk(State         *pState,
                     StateOverride *pOverride);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    void     setAction(RAction *pAction);
    RAction *getAction(void            ) const;

    template<class Action, class Result> 
    static Result doGetData(Action *pA, UInt32 iSlotId);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class RenderPartition;
    
    /*! \brief prohibit default function (move to 'public' if needed) */
    DrawEnv(const DrawEnv &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const DrawEnv &source);
};

OSG_END_NAMESPACE

#include "OSGDrawEnv.inl"

#endif /* _OSGDRAWENV_H_ */
