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

#ifndef _OSGRENDERTRAVERSALACTIONBASE_H_
#define _OSGRENDERTRAVERSALACTIONBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGAction.h"
#include "OSGStatElemTypes.h"
#include "OSGFrustumVolume.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;
class Viewport;
class Camera;
class Background;
class Window;
class StatCollector;

/*! \brief Base class using the render action interface of window
 */

class OSG_SYSTEM_DLLMAPPING RenderTraversalActionBase : public Action
{
    /*==========================  PUBLIC  =================================*/

  public:

    static StatElemDesc<StatTimeElem> statTravTime;
//    static StatElemDesc<StatIntElem>  statCullTestedNodes;
//    static StatElemDesc<StatIntElem>  statCulledNodes;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~RenderTraversalActionBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Rendering Environment                          */
    /*! \{                                                                 */

          Viewport      *getViewport     (void                      ) const;
          void           setViewport     (Viewport      *pViewport  );
    
          Camera        *getCamera       (void                      ) const;
          void           setCamera       (Camera        *pCamera    );

          Background    *getBackground   (void                      ) const;
          void           setBackground   (Background    *pBackground);
    
          Window        *getWindow       (void                      ) const;
          void           setWindow       (Window        *pWindow    );
    
          StatCollector *getStatCollector(void                      ) const;
          void           setStatCollector(StatCollector *pStat      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Culling                                    */
    /*! \{                                                                 */

    // control activation of frustum culling
    virtual bool                 getFrustumCulling(void                ) const;
    virtual void                 setFrustumCulling(bool val = true     );
    
    // control drawing of checked volumes
    virtual bool                 getVolumeDrawing (void                ) const;
    virtual void                 setVolumeDrawing (bool val = false    );
    
    // control automatic frustum calculation
            bool                 getAutoFrustum   (void                ) const;
            void                 setAutoFrustum   (bool val = true     );

    // control frustum
    virtual const FrustumVolume &getFrustum       (void                ) const;
    virtual void                 setFrustum       (FrustumVolume &frust);    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lights                                     */
    /*! \{                                                                 */

#if 0
           // select all visible nodes
            UInt32  selectVisibles(void      );
#endif

    virtual bool    isVisible     (Node *node) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lights                                     */
    /*! \{                                                                 */

    virtual ActionBase::ResultE start(void                   );
    virtual ActionBase::ResultE stop (ActionBase::ResultE res);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lights                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RenderTraversalActionBase(void);
    RenderTraversalActionBase(const RenderTraversalActionBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*---------------------------------------------------------------------*/
    /*! \name                   Internal updates                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Camera        *_pCamera;
    Background    *_pBackground;
    Window        *_pWindow;
    Viewport      *_pViewport;

    StatCollector *_pStatistics;

    // frustum culling attributes
    
    bool          _bFrustumCulling;
    bool          _bVolumeDrawing;
    bool          _bAutoFrustum;
    FrustumVolume _oFrustum;

    /*==========================  PRIVATE  ================================*/

  private:

    typedef Action Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const RenderTraversalActionBase &source);
};

OSG_END_NAMESPACE

#include "OSGRenderTraversalActionBase.inl"

#endif /* _OSGRENDERACTIONBASE_H_ */
