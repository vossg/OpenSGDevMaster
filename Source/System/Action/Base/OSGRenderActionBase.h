/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGRENDERACTIONBASE_H_
#define _OSGRENDERACTIONBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGAction.h"
#include "OSGStatElemTypes.h"
#include "OSGFrustumVolume.h"

#include "OSGMixinHead.h"
#include "OSGDataSlotMixin.h"
#include "OSGDataSlotPool.h"

#include "OSGRenderPartitionBase.h"
#include "OSGRenderPropertiesPool.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class Viewport;
class Camera;
class Background;
class Window;
class StatCollector;
class Material;
class TraversalValidator;

template <class ParentT>
class StageHandlerMixin;

/*! \ingroup GrpSystemActionBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

struct RenderDataSlotDesc
{
    typedef Action                   ParentT;
    typedef MFUnrecFieldContainerPtr DataStore;
    
    typedef ActionDataSlotPool       DataSlotIdPool;


    static void dumpElement(const FieldContainer *pVal)
    {
        fprintf(stderr, "%p", pVal);

        if(pVal != NULL)
        {
            fprintf(stderr, " (%s)", pVal->getType().getCName());
        }
    }
};

/*! \ingroup GrpSystemActionBase
 */

typedef DataSlotMixin< 
            MixinHead < 
                RenderDataSlotDesc > > RenderActionBaseParent;



/*! \brief Base class using the render action interface of window
    \ingroup GrpSystemActionBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING RenderActionBase : public RenderActionBaseParent
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef RenderActionBaseParent                     Inherited;
    typedef RenderPropertiesPool::Singleton::ValueType RenderPropType;

    static StatElemDesc<StatTimeElem> statTravTime;
//    static StatElemDesc<StatIntElem>  statCullTestedNodes;
//    static StatElemDesc<StatIntElem>  statCulledNodes;


    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~RenderActionBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Rendering Environment                          */
    /*! \{                                                                 */

          Viewport      *getViewport      (void                      ) const;
          void           setViewport      (Viewport      *pViewport  );
    
          Camera        *getCamera        (void                      ) const;
          void           setCamera        (Camera        *pCamera    );

          Background    *getBackground    (void                      ) const;
          void           setBackground    (Background    *pBackground);
    
          Window        *getWindow        (void                      ) const;
          void           setWindow        (Window        *pWindow    );
    
          StatCollector *getStatCollector (void                      ) const;
          void           setStatCollector (StatCollector *pStat      );

          Material      *getGlobalOverride(void                      ) const;
          void           setGlobalOverride(Material      *pMat       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Culling                                    */
    /*! \{                                                                 */

    // control activation of frustum culling
    virtual bool getFrustumCulling         (void            ) const;
    virtual void setFrustumCulling         (bool val = true );

    virtual bool getCorrectTwoSidedLighting(void            ) const;    
    virtual void setCorrectTwoSidedLighting(bool val = true );    

    // control drawing of checked volumes
    virtual bool getVolumeDrawing          (void            ) const;
    virtual void setVolumeDrawing          (bool val = false);

    virtual bool getZWriteTrans            (void            ) const;
    virtual void setZWriteTrans            (bool val = false);
    
    // control automatic frustum calculation
            bool                 getAutoFrustum   (void                ) const;
            void                 setAutoFrustum   (bool val = true     );

    // control frustum
    virtual const FrustumVolume &getFrustum       (void                ) const;
    virtual void                 setFrustum       (FrustumVolume &frust);    


    /*----------- multi-frame buffering / split cull/draw -------------------*/

    void setUseGLFinish(bool bVal);
    bool getUseGLFinish(void     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lights                                     */
    /*! \{                                                                 */

    virtual ActionBase::ResultE start    (void                   );
    virtual ActionBase::ResultE stop     (ActionBase::ResultE res);

    virtual void                frameInit(void                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lights                                     */
    /*! \{                                                                 */

    TraversalValidator *getTravValidator (void     );
    UInt16              getFrameTravCount(void     );

    void                setDrawerId      (Int32 iId);
    void                setDrawableId    (Int32 iId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lights                                     */
    /*! \{                                                                 */

    RenderPropType getRenderProperties  (void                );
    void           setRenderProperties  (RenderPropType oProp);
    void           resetRenderProperties(void                );

    void           setDrawPartPar       (bool           bVal );
    bool           getDrawPartPar       (void                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lights                                     */
    /*! \{                                                                 */

    // tmp for testing
    virtual Int32 getActivePartitionIdx(void                              )= 0;
    virtual Int32 getLastPartitionIdx  (void                              )= 0;

    virtual void  readdPartitionByIndex(UInt32                uiPartIdx   )= 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    template <class ParentT>
    friend class StageHandlerMixin;

    friend class Viewport;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RenderActionBase(void);
    RenderActionBase(const RenderActionBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*---------------------------------------------------------------------*/
    /*! \name                   Internal updates                           */
    /*! \{                                                                 */

    // tmp for testing
    virtual void  pushPartition        (UInt32                    uiCopyOnPush,
                                        RenderPartitionBase::Mode eMode   )= 0;

    virtual void  popPartition         (void                              )= 0;

    virtual void  beginPartitionGroup  (void                              )= 0;
    virtual void  endPartitionGroup    (void                              )= 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Internal updates                           */
    /*! \{                                                                 */

    Int32 getDrawerId  (void);
    Int32 getDrawableId(void);

    /*! \}                                                                 */
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Camera             *_pCamera;
    Background         *_pBackground;
    Window             *_pWindow;
    Viewport           *_pViewport;
    Material           *_pGlobalOverride;

    StatCollector      *_pStatistics;
    TraversalValidator *_pTravValidator;

    bool                _bUseGLFinish;

    // frustum culling attributes
    
    bool                _bFrustumCulling;
    bool                _bVolumeDrawing;
    bool                _bZWriteTrans;
    bool                _bAutoFrustum;
    bool                _bCorrectTwoSidedLighting;

    FrustumVolume       _oFrustum;

    UInt16              _uiFrameTravCount;

    Int32               _iDrawerId;
    Int32               _iDrawableId;

    RenderPropType      _oCurrentRenderProp;
    bool                _bDrawPartPar;

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const RenderActionBase &source);
};


OSG_END_NAMESPACE

#include "OSGRenderActionBase.inl"

#endif /* _OSGRENDERACTIONBASE_H_ */
