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


#ifndef _OSGDRAWACTIONBASE_H_
#define _OSGDRAWACTIONBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGFrustumVolume.h"
#include "OSGStatElemTypes.h"
#include "OSGStatCollector.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Camera;
class Background;
class Window;
class Node;
class Viewport;
class Material;
class DrawEnv;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_SYSTEM_DLLMAPPING DrawActionBase : public Action
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static StatElemDesc<StatTimeElem> statTravTime;
    static StatElemDesc<StatIntElem>  statCullTestedNodes;
    static StatElemDesc<StatIntElem>  statCulledNodes;
    
    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~DrawActionBase(void); 

    /*------------------------- your_category -------------------------------*/

    // rendering state handling
       
          Viewport      *getViewport     (void                  ) const;    
          void           setViewport     (Viewport   *viewport  );
    
          Camera        *getCamera       (void                  ) const;    
          void           setCamera       (Camera     *cam       );
    const Matrixr       &getCameraToWorld(void                  );

          Background    *getBackground   (void                  ) const;
          void           setBackground   (Background *background);
    
          Window        *getWindow       (void                  ) const;
          void           setWindow       (Window * window       );
    
          StatCollector *getStatistics   (void                  );
          void           setStatistics   (StatCollector * stat  );
          bool           hasOwnStat      (void                  );

    // frustum culling functions
    // these are just temporary, sooner or later they'll move into a 
    // cacaded action
    
    // control activation of frustum culling
         bool            getFrustumCulling(void             ) const;
         void            setFrustumCulling(bool val = true  );
    
    // control drawing of checked volumes
          bool           getVolumeDrawing(void              ) const;
          void           setVolumeDrawing(bool val = false  );
    
    // control automatic frustum calculation
          bool           getAutoFrustum(void                ) const;
          void           setAutoFrustum(bool val = true     );

    // control frustum
    const FrustumVolume &getFrustum    (void                ) const;
          void           setFrustum    (FrustumVolume &frust);    
    
    DrawEnv *getDrawEnv(void) const;

    /*------------------------- your_operators ------------------------------*/

    virtual bool    isVisible     (Node* node) = 0;

    // select all visible nodes
            UInt32  selectVisibles(void      );
    


    Material   *getMaterial    (void                             ) const;
    NodePtr     getMaterialNode(void                             ) const;
    void        setMaterial    (Material *pMaterial, NodePtr node);

    /*------------------------- your_operators ------------------------------*/

    // initialisation
    virtual ActionBase::ResultE start(void                   );
    virtual ActionBase::ResultE stop (ActionBase::ResultE res);

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Camera        *_camera;
    Background    *_background;
    Window        *_window;
    Viewport      *_viewport;
    StatCollector *_statistics;
    bool           _ownStat;

    // frustum culling attributes
    
    bool           _frustumCulling;
    bool           _volumeDrawing;
    bool           _autoFrustum;
    FrustumVolume  _frustum;

    Material      *_pMaterial;
    NodePtr        _pMaterialNode;

    Matrixr        _mCameraToWorld;

    DrawEnv       *_pDrawEnv;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    DrawActionBase(void);

    DrawActionBase(const DrawActionBase &source);
    void operator =(const DrawActionBase &source);

    virtual std::vector<Functor> *getDefaultEnterFunctors(void) = 0;
    virtual std::vector<Functor> *getDefaultLeaveFunctors(void) = 0;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Action Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef DrawActionBase *DrawActionBaseP;

OSG_END_NAMESPACE

#define OSGDRAWACTIONBASE_HEADER_CVSID "@(#)$Id$"

#include "OSGDrawActionBase.inl"

#endif /* _OSGDRAWACTIONBASE_H_ */
