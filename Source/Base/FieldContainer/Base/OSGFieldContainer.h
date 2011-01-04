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

#ifndef _OSGFIELDCONTAINER_H_
#define _OSGFIELDCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <boost/function.hpp>

#include "OSGReflexiveContainer.h"
#include "OSGFieldContainerType.h"
#include "OSGContainerMixinHead.h"
#include "OSGChangedFunctorMFields.h"
#include "OSGAspectStore.h"
#include "OSGAtomic.h"

OSG_BEGIN_NAMESPACE

class FieldContainerFactoryBase;
class RemoteAspect;

template <class ObjectT>
class TransitPtr;

template <class ObjectT, class RefCountPolicyT>
class MTRefCountPtr;

template<typename RefCountPolicyT>
class ChildAccessHandler;

template <class FieldT>
class SFieldConnector;

template <class FieldT>
class MFieldConnector;

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */

class FieldContainer : public ReflexiveContainer
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Type definitions                          */
    /*! \{                                                                 */

    typedef ReflexiveContainer                               Inherited;

    typedef FieldContainerType                               TypeObject;

    typedef FieldContainer                                   Self;


    OSG_GEN_INTERNALPTR(FieldContainer);

    /*! \nohierarchy */
    struct  attempt_to_create_CoredNodePtr_on_non_NodeCore_FC {};

    static const bool isNodeCore = false;

    OSG_RC_FIRST_FIELD_DECL(ChangedCallbacks);
    OSG_RC_LAST_FIELD_DECL (ChangedCallbacks);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Get Class Type Information                       */
    /*! \{                                                                 */

    static OSG_BASE_DLLMAPPING TypeObject &getClassType   (void);
    static OSG_BASE_DLLMAPPING UInt32      getClassTypeId (void);
    static OSG_BASE_DLLMAPPING UInt16      getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual       TypeObject &getType(void);

    OSG_BASE_DLLMAPPING
    virtual const TypeObject &getType(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual void    copyFromBin(BinaryDataHandler  &pMem,
                                ConstFieldMaskArg   whichField);

    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual FieldContainer *findNamedComponent(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual ObjTransitPtr shallowCopy         (void             ) const = 0;
    virtual ObjTransitPtr shallowCopyLocal    (BitVector uiFlags) const = 0;
    virtual ObjTransitPtr shallowCopyDependent(BitVector uiFlags) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void changed            (ConstFieldMaskArg whichField,
                                     UInt32            origin,
                                     BitVector         details);

            void callChangedFunctors(ConstFieldMaskArg whichField );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    void   addChangedFunctor   (ChangedFunctor func,
                                std::string    createSymbol);

    template<class FunctorT>
    void   subChangedFunctor   (FunctorT       func        );

    template<class FunctorT>
    bool   hasChangedFunctor   (FunctorT       func        );

    void   clearChangedFunctors(void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Field Flags                                */
    /*! \{                                                                 */

    const FieldFlags *getFieldFlags(void);

          bool        isMTLocal    (void) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Field Flags                                */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    void markFieldsThreadLocal   (const BitVector bvFieldMasks);
    OSG_BASE_DLLMAPPING
    void unmarkFieldsThreadLocal (const BitVector bvFieldMasks);

    OSG_BASE_DLLMAPPING
    void markFieldsClusterLocal  (const BitVector bvFieldMasks);
    OSG_BASE_DLLMAPPING
    void unmarkFieldsClusterLocal(const BitVector bvFieldMasks);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual void invalidateVolume(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    RefCountStore getWeakRefCount(void);

    OSG_BASE_DLLMAPPING 
    RefCountStore getRefCount    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Parent Linking (Internal Use Only)                           */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual bool unlinkChild (      FieldContainer * const pChild,
                              const UInt16                 childFieldId);
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual void dump         (      UInt32    uiIndent = 0,
                               const BitVector bvFlags  = 0) const;

    OSG_BASE_DLLMAPPING
            void dumpFieldInfo(void                        ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    AspectStore *_pAspectStore;
#endif

    FieldFlags               *_pFieldFlags;
    MFChangedFunctorCallback  _mfChangedFunctors;

    RefCountStore             _iRefCount;
    RefCountStore             _iWeakRefCount;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    FieldContainer(void);

    OSG_BASE_DLLMAPPING
    FieldContainer(const FieldContainer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual ~FieldContainer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Helper                                 */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    void  addReferenceRecorded  (void);

    OSG_BASE_DLLMAPPING
    void  addReferenceUnrecorded(void);

    OSG_BASE_DLLMAPPING
    void  subReferenceRecorded  (void);

    OSG_BASE_DLLMAPPING
    void  subReferenceUnrecorded(void);


    OSG_BASE_DLLMAPPING
    void  addWeakReference      (void);

    OSG_BASE_DLLMAPPING
    void  subWeakReference      (void);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    FieldContainer *getAspectPtr    (UInt32 uiAspect      ) const;
    void            setupAspectStore(void                 );
    void            setupAspectStore(AspectStore *pStore  );
    AspectStoreP    getAspectStore  (void                 ) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    OSG_BASE_DLLMAPPING
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo) = 0;

    OSG_BASE_DLLMAPPING
            void execSync (      FieldContainer    *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         Edit                                 */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    void  subReferenceUnresolved(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
            void onCreateAspect(const FieldContainer *createAspect,
                                const FieldContainer *source      = NULL);
    OSG_BASE_DLLMAPPING
            void onCreate      (const FieldContainer *source      = NULL);

    OSG_BASE_DLLMAPPING
    virtual void onDestroy     (      UInt32          uiContainerId     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual bool deregister    (      UInt32          uiContainerId     );

    OSG_BASE_DLLMAPPING
    virtual void resolveLinks   (      void                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
            void            registerChangedContainer (void);

    OSG_BASE_DLLMAPPING
    virtual void            registerChangedContainerV(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainer *createAspectCopy(const FieldContainer *) const = 0;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Parent Linking (Internal Use Only)                           */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    virtual bool linkParent  (      FieldContainer * const pParent,
                              const UInt16                 childFieldId,
                              const UInt16                 parentFieldId);

    OSG_BASE_DLLMAPPING
    virtual bool unlinkParent(      FieldContainer * const pParent,
                              const UInt16                 parentFieldId);
            
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjCPtr &result, 
                              const          ObjectT          *prototypeP,
                                             BitVector         bFlags    );

    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjCPtr &result, 
                                             BitVector         bFlags);

#ifdef OSG_MT_CPTR_ASPECT
    template <class ObjectT>
    static void newAspectCopy(      typename ObjectT::ObjCPtr &result,
                              const          ObjectT          *pRefAspect,
                              const          ObjectT          *prototypeP);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Local Edit                                */
    /*! \{                                                                 */

    void editSField     (ConstFieldMaskArg whichField);

    template<class FieldT>
    void editMField     (ConstFieldMaskArg whichField,
                         FieldT            &oField   );

    void clearUncommited(ConstFieldMaskArg whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);
    static void exitMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainerFactoryBase;
    friend class RemoteAspect;

    template<class ContainerPtr>
    friend ContainerPtr convertToCurrentAspect(ContainerPtr pFC);

    friend struct RecordedRefCountPolicy;
    friend struct UnrecordedRefCountPolicy;
    friend struct WeakRefCountPolicy;

    template <class ObjectT>
    friend class TransitPtr;

    template <class ObjectT, class RefCountPolicyT>
    friend class MTRefCountPtr;

#ifdef OSG_MT_CPTR_ASPECT
    friend struct HandledFieldContainerFactoryDesc;

    friend class  FieldContainerType;
    friend class  ChangeList;
#endif

    template<typename RefCountPolicyT>
    friend class ChildAccessHandler;

    template <class FieldT>
    friend class SFieldConnector;

    template <class FieldT>
    friend class MFieldConnector;


    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainer &source);
};


OSG_BASE_DLLMAPPING
void appendTypesVector(
    const std::vector<std::string                   > &typeNames,
          std::vector<const OSG::ReflexiveContainerType *> &types      );

OSG_BASE_DLLMAPPING
void appendGroupsVector(
    const std::vector<std::string>                    &groupNames,
          std::vector<OSG::UInt16>                    &groupIds   );

OSG_BASE_DLLMAPPING
void appendTypesString(
    const std::string                                      &typesString,
          std::vector<const OSG::ReflexiveContainerType *> &types      );

OSG_BASE_DLLMAPPING
FieldContainerTransitPtr deepClone(      
          FieldContainer const *                       src,
    const std::vector<std::string>                    &shareTypeNames,

    const std::vector<std::string>                    &ignoreTypeNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                    &shareGroupNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                    &ignoreGroupNames  =
              std::vector<std::string>()                                  );

OSG_BASE_DLLMAPPING
FieldContainerTransitPtr deepClone(
          OSG::FieldContainer const *                       src,
    const std::vector<OSG::UInt16>                         &shareGroupIds,

    const std::vector<OSG::UInt16>                         &ignoreGroupIds =
              std::vector<OSG::UInt16>()                                     );

OSG_BASE_DLLMAPPING
FieldContainerTransitPtr deepClone(      
          OSG::FieldContainer const *                  src,
    const std::string                                 &shareTypesString,

    const std::string                                 &ignoreTypesString =
              std::string()                                               );

OSG_BASE_DLLMAPPING
FieldContainerTransitPtr deepClone(
          OSG::FieldContainer const *                       src,

    const std::vector<const OSG::ReflexiveContainerType *> &shareTypes        =
              std::vector<const OSG::ReflexiveContainerType *>(),

    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes       =
              std::vector<const OSG::ReflexiveContainerType *>(),

    const std::vector<OSG::UInt16>                         &shareGroupIds     =
              std::vector<OSG::UInt16>(),

    const std::vector<OSG::UInt16>                         &ignoreGroupIds    =
              std::vector<OSG::UInt16>()                                      );



#ifdef OSG_MT_CPTR_ASPECT
/*! \ingroup GrpBaseFieldContainerFuncs
    \relatesalso OSG::FieldContainer
 */
template<class ContainerPtr> inline
ContainerPtr convertToCurrentAspect(ContainerPtr pFC);
#endif


OSG_END_NAMESPACE

#include "OSGTransitPtr.h"
#include "OSGRefCountPtr.h"
#include "OSGMTRefCountPtr.h"

#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainer.inl"

#include "OSGBaseRefCountPolicies.h"
#include "OSGContainerRefCountPolicies.h"

#if defined(OSG_1_COMPAT)
#include "OSGContainerPtrFuncs.h"
#endif

#endif /* _OSGFIELDCONTAINER_H_ */

