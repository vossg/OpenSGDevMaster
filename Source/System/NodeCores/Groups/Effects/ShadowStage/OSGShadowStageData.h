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

#ifndef _OSGSHADOWSTAGEDATA_H_
#define _OSGSHADOWSTAGEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShadowStageDataBase.h"
#include "OSGShadowTreeHandler.h"
#include "OSGTextureEnvChunk.h"

#include "OSGLight.h"
#include "OSGTransform.h"
#include "OSGCamera.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShadowStageData class. See \ref
           PageGroupShadowStageData for a description.

    \ingroup GrpEffectsGroupsShadowObj
    \ingroup GrpLibOSGEffectsGroups
    \includebasedoc
 */

class OSG_EFFECTGROUPS_DLLMAPPING ShadowStageData : public ShadowStageDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShadowStageDataBase Inherited;
    typedef ShadowStageData     Self;

    /*! \nohierarchy
     */
    struct ShadowMapElem
    {
        static const UInt32 DepthShadowMap = 0x0001;
        static const UInt32 ColorShadowMap = 0x0002;

        UInt32                    uiType;
        ImageUnrecPtr             pImage;
        TextureObjChunkUnrecPtr   pTexO;
        TextureEnvChunkUnrecPtr   pTexE;
        FrameBufferObjectUnrecPtr pFBO;

        ShadowMapElem(void) :
            uiType(DepthShadowMap),
            pImage(NULL          ),
            pTexO (NULL          ),
            pTexE (NULL          ),
            pFBO  (NULL          )
        {
        }

        ShadowMapElem(const ShadowMapElem &src) :
            uiType(src.uiType),
            pImage(src.pImage),
            pTexO (src.pTexO ),
            pTexE (src.pTexE ),
            pFBO  (src.pFBO  )
        {
        }

        ~ShadowMapElem(void)
        {
            pImage = NULL;
            pTexO  = NULL;
            pTexE  = NULL;
            pFBO   = NULL;
        }

        void operator =(const ShadowMapElem &src)
        {
            if(this != &src)
                return;

            uiType = src.uiType;
            pImage = src.pImage;
            pTexO  = src.pTexO;
            pTexE  = src.pTexE;
            pFBO   = src.pFBO;
        }

        bool operator ==(const ShadowMapElem &other) const
        {
            return uiType == other.uiType &&
                   pImage == other.pImage &&
                   pTexO  == other.pTexO  &&
                   pTexE  == other.pTexE  &&
                   pFBO   == other.pFBO;
        }

        bool operator !=(const ShadowMapElem &other) const
        {
            return ! (*this == other);
        }
    };

    typedef std::vector<ShadowMapElem> ShadowMapStore;

    typedef std::vector<NodeUnrecPtr>                            NodeStore;
    typedef std::vector<std::pair<NodeUnrecPtr, LightUnrecPtr> > LightStore;
    typedef std::vector<CameraUnrecPtr>                          CamStore;
    typedef std::vector<TransformUnrecPtr>                       TransStore;
    typedef std::vector<UInt32>                                  LStateStore;
    typedef std::vector<bool>                                    StatusStore;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void setRunning(bool bVal);
    bool getRunning(void     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void               setTreeHandler(ShadowTreeHandler *pHandler);
    ShadowTreeHandler *getTreeHandler(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    ShadowMapStore &getShadowMaps       (void);

    NodeStore      &getTransparents     (void);
    LightStore     &getLights           (void);
    LightStore     &getOldLights        (void);
    CamStore       &getLightCameras     (void);
    TransStore     &getLightCamTrans    (void);
    NodeStore      &getLightCamBeacons  (void);
    LStateStore    &getLightStates      (void);

    StatusStore    &getExcludeNodeActive(void);
    StatusStore    &getRealPointLight   (void);

    void            clearLightData      (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    Node *getLightRoot(UInt32 index);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShadowStageDataBase.

    bool                     _bRunning;
    ShadowTreeHandlerRefPtr  _pTreeHandler;

    ShadowMapStore           _vShadowMaps;

    NodeStore                _vTransparents;
    LightStore               _vLights;
    LightStore               _vOldLights;
    CamStore                 _vLightCameras;
    TransStore               _vLightCamTrans;
    NodeStore                _vLightCamBeacons;
    LStateStore              _vLightStates;

    StatusStore              _vExcludeNodeActive;
    StatusStore              _vRealPointLight;
#if 0
    std::vector<bool*> _renderSide;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShadowStageData(void);
    ShadowStageData(const ShadowStageData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShadowStageData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShadowStageDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShadowStageData &source);
};

OSG_END_NAMESPACE

#include "OSGShadowStageDataBase.inl"
#include "OSGShadowStageData.inl"

#endif /* _OSGSHADOWSTAGEDATA_H_ */
