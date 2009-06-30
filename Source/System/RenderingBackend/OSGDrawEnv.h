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
#include "OSGSystemProfile.h"
#include "OSGGLEXT.h"
#include "OSGStatCollector.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;
class RenderPartition;
class Window;
class State;
class StateOverride;

/*! \ingroup GrpSystemRenderingBackend
 */

class OSG_SYSTEM_DLLMAPPING DrawEnv
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef RenderActionBase RAction;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void   setWindow         (      Window   *pWindow       );

    void   setupProjection   (const Matrixr  &projection,
                              const Matrixr  &translation   );
    void   setupViewing      (const Matrixr  &matrix        );
    void   setObjectToWorld  (const Matrixr  &matrix        );

    void   setCameraNear     (const Real     &camNear       );
    void   setCameraFar      (const Real     &camFar        );

    void   setActiveTexTarget(      UInt32    uiSlot,
                                    GLenum    uiTarget      );

    void   setActiveShader   (      UInt32    uiActiveShader);
    UInt32 getActiveShader   (      void                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    const Matrixr       &getCameraFullProjection (void         ) const;
    const Matrixr       &getCameraProjection     (void         ) const;
    const Matrixr       &getCameraProjectionTrans(void         ) const;
    const Matrixr       &getCameraDecoration     (void         ) const;

    const Matrixr       &getCameraViewing        (void         ) const;

    //CamViewing^-1
    const Matrixr       &getCameraToWorld        (void         ) const;

    const Matrixr       &getObjectToWorld        (void         ) const;

    const Matrixr       &getWorldToScreen        (void         ) const;

          Real           getCameraNear           (void         ) const;
          Real           getCameraFar            (void         ) const;

          Window        *getWindow               (void         ) const;

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

    const Matrixr  &getVPCameraFullProjection (void         ) const;
    const Matrixr  &getVPCameraProjection     (void         ) const;
    const Matrixr  &getVPCameraProjectionTrans(void         ) const;

    const Matrixr  &getVPCameraViewing        (void         ) const;

    //VPCamViewing^-1
    const Matrixr  &getVPCameraToWorld        (void         ) const; 

    const Matrixr  &getVPWorldToScreen        (void         ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void setVPCameraMatrices     (const Matrixr &mFullprojection,
                                  const Matrixr &mProjection,
                                  const Matrixr &mProjectionTrans,
                                  const Matrixr &mViewing,
                                  const Matrixr &mToWorld,
                                  const Matrixr &mWorldToScreen  );
    
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

    Int32 getPixelLeft        (void                );
    Int32 getPixelRight       (void                );
    Int32 getPixelBottom      (void                );
    Int32 getPixelTop         (void                );

    Int32 getPixelWidth       (void                );
    Int32 getPixelHeight      (void                );
    bool  getFull             (void                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

          void     setTileFullSize         (const Vec2u &uiTileFullSize);
          void     setTileRegion           (const Vec4f &vTileRegion   );

    const Vec2u   &getTileFullSize         (void                       ) const;
    const Vec4f   &getTileRegion           (void                       ) const;

          Matrixr  calcTileDecorationMatrix(void                       ) const;

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

    Matrixr        _cameraFullProjection;
    Matrixr        _cameraProjection;
    Matrixr        _cameraProjectionTrans;
    Matrixr        _cameraViewing;
    Matrixr        _cameraToWorld;
    Matrixr        _cameraDecoration;

    Matrixr        _objectToWorld;
    Matrixr        _worldToScreen;

    Matrixr        _vpCameraFullProjection;
    Matrixr        _vpCameraProjection;
    Matrixr        _vpCameraProjectionTrans;
    Matrixr        _vpCameraViewing;
    Matrixr        _vpCameraToWorld;
    Matrixr        _vpWorldToScreen;

    Real           _cameraNear;
    Real           _cameraFar;

    Int32          _iPixelLeft;
    Int32          _iPixelRight;
    Int32          _iPixelBottom;
    Int32          _iPixelTop;

    Vec2u          _uiTileFullSize;
    Vec4f          _vTileRegion;

    bool           _bFull;

    UInt32         _uiLightState;

    Window        *_pWindow;

    State         *_pActiveState;
    StateOverride *_pActiveStateOverride;

    UInt32         _uiNumStateChanges;
    UInt32         _uiNumShaderChanges;
    UInt32         _uiNumShaderParamChanges;
    StatCollector *_pStatCollector;

    GLenum         _aActiveTexTargets[osgMaxTexImages];
    UInt32         _uiActiveShader;

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
