/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2009 by the OpenSG Forum                   *
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

#ifndef _OSGUPDATEACTION_H_
#define _OSGUPDATEACTION_H_

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGAction.h"
#include "OSGMixinHead.h"
#include "OSGDataSlotMixin.h"

#include "OSGUpdatePartition.h"
#include "OSGUpdatePartitionPool.h"
#include "OSGCamera.h"
#include "OSGDrawEnv.h"
#include "OSGViewport.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

struct UpdateDataSlotDesc
{
    typedef Action                   ParentT;
    typedef MFUnrecFieldContainerPtr DataStore;
    
    static void dumpElement(const FieldContainer *pVal)
    {
        fprintf(stderr, "%p", pVal);

        if(pVal != NULL)
        {
            fprintf(stderr, " (%s)", pVal->getType().getCName());
        }
    }
};

typedef DataSlotMixin< 
    MixinHead< UpdateDataSlotDesc > > UpdateActionParent;


class OSG_SYSTEM_DLLMAPPING UpdateAction : public UpdateActionParent
{
  public:
    typedef UpdateActionParent  Inherited;
    typedef UpdateAction        Self;

    typedef Inherited::FunctorStore        FunctorStore;

    typedef UpdatePartition::MatrixStore   MatrixStore;
    typedef UpdatePartition::MatrixStack   MatrixStack;

    typedef std::vector<UpdatePartition *> UpdatePartitionStack;



    virtual ~UpdateAction(void);

    static UpdateAction *create(void);

    static void registerEnterDefault(const FieldContainerType &type,
                                     const Action::Functor    &func );
    static void registerLeaveDefault(const FieldContainerType &type,
                                     const Action::Functor    &func );

    virtual ResultE start(void       );  
    virtual ResultE stop (ResultE res);


    void             pushPartition     (UInt32 copyOnPush = 0);
    void             popPartition      (void                 );
    UpdatePartition *getActivePartition(void                 ) const;


    template <class MatrixT>
    void pushMatrix(const MatrixT &matrix);
    void popMatrix (void                 );

    const Matrix &getModelMatrix    (void) const;
    const Matrix &getModelViewMatrix(void) const;

    const DrawEnv &getDrawEnv (void) const;
          DrawEnv &editDrawEnv(void);


    Camera   *getCamera  (void            ) const;
    void      setCamera  (Camera   *camera);

    Viewport *getViewport(void            ) const;
    void      setViewport(Viewport *port  );
    
    Window   *getWindow  (void            ) const;
    void      setWindow  (Window   *window);



  protected:
    UpdateAction(void                      );
    UpdateAction(const UpdateAction &source);

    virtual FunctorStore *getDefaultEnterFunctors(void);
    virtual FunctorStore *getDefaultLeaveFunctors(void);

    static bool terminateEnter(void);
    static bool terminateLeave(void);


    static FunctorStore *_defaultEnterFunctors;
    static FunctorStore *_defaultLeaveFunctors;

    Camera           *_camera;
    Viewport         *_viewport;
    Window           *_window;


    UpdatePartition      *_activePartition;
    UpdatePartitionStack  _partitionStack;
    UpdatePartitionPool   _partitionPool;
};

OSG_END_NAMESPACE

#include "OSGUpdateAction.inl"

#endif // _OSGUPDATEACTION_H_
