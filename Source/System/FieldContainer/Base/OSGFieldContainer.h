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
#include "OSGRefCountMixin.h"
#include "OSGContainerCreateMixin.h"
#include "OSGContainerMixinHead.h"
#include "OSGContainerIdMixin.h"
#include "OSGSystemProfile.h"
#include "OSGChangedFunctorMFields.h"
#include "OSGAspectStore.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

class FieldContainer : public FieldContainerParent
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Type definitions                          */
    /*! \{                                                                 */

    typedef FieldContainerParent                             Inherited;

    typedef FieldContainerType                               TypeObject;

    typedef PointerBuilder<FieldContainer>::ObjPtr           ObjPtr;
    typedef PointerBuilder<FieldContainer>::ObjPtrConst      ObjPtrConst;
    typedef PointerBuilder<FieldContainer>::ObjConstPtr      ObjConstPtr;

    typedef PointerBuilder<FieldContainer>::ObjConstPtrConst ObjConstPtrConst;

    typedef PointerBuilder<FieldContainer>::ObjPtrArg        ObjPtrArg;
    typedef PointerBuilder<FieldContainer>::ObjConstPtrArg   ObjConstPtrArg;
    typedef PointerBuilder<FieldContainer>::ObjPtrConstArg   ObjPtrConstArg;


    struct  attempt_to_create_CoredNodePtr_on_non_NodeCore_FC {};

    static const bool isNodeCore = false;

    OSG_RC_FIRST_FIELD_DECL(ChangedCallbacks);
    OSG_RC_LAST_FIELD_DECL (ChangedCallbacks);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Get Class Type Information                       */
    /*! \{                                                                 */

    static OSG_SYSTEM_DLLMAPPING TypeObject &getClassType   (void);
    static OSG_SYSTEM_DLLMAPPING UInt32      getClassTypeId (void);
    static OSG_SYSTEM_DLLMAPPING UInt16      getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual       TypeObject &getType(void);

    OSG_SYSTEM_DLLMAPPING
    virtual const TypeObject &getType(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual void    copyFromBin(BinaryDataHandler  &pMem,
                                ConstFieldMaskArg   whichField);

    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual ObjPtr shallowCopy(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void changed            (ConstFieldMaskArg whichField,
                                     UInt32            origin    );

            void callChangedFunctors(ConstFieldMaskArg whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual void pushToField     (      FieldContainerPtrConstArg pNewElement,
                                  const UInt32                    uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void insertIntoMField(const UInt32                    uiIndex,
                                        FieldContainerPtrConstArg pNewElement,
                                  const UInt32                    uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void replaceInMField (const UInt32                    uiIndex,
                                        FieldContainerPtrConstArg pNewElement,
                                  const UInt32                    uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                        FieldContainerPtrConstArg pNewElement,
                                  const UInt32                    uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void removeFromMField(const UInt32                    uiIndex,
                                  const UInt32                    uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void removeFromMField(      FieldContainerPtrConstArg pElement,
                                  const UInt32                    uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void clearField      (const UInt32                    uiFieldId  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    UInt32 addChangedFunctor   (ChangedFunctor func,
                                std::string    createSymbol);

    template<class FunctorT>
    void   subChangedFunctor   (FunctorT       func        );

    void   subChangedFunctor   (UInt32         uiId        );

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Helper                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual void invalidateVolume(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

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

    OSG_SYSTEM_DLLMAPPING
    FieldContainer(void);

    OSG_SYSTEM_DLLMAPPING
    FieldContainer(const FieldContainer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual ~FieldContainer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FieldContainerPtr getPtr          (void                 );

#ifdef OSG_MT_CPTR_ASPECT
    FieldContainerPtr getAspectPtr    (UInt32 uiAspect      );
    void              setupAspectStore(void                 );
    void              setupAspectStore(AspectStore *pStore  );
    AspectStoreP      getAspectStore  (void                 );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

#ifdef OSG_MT_FIELDCONTAINERPTR
    OSG_SYSTEM_DLLMAPPING
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset) = 0;

    OSG_SYSTEM_DLLMAPPING
            void execSync (      FieldContainer    *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    OSG_SYSTEM_DLLMAPPING
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg         syncMode  ,
                           const UInt32                    uiSyncInfo) = 0;

    OSG_SYSTEM_DLLMAPPING
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

#if 0
    OSG_SYSTEM_DLLMAPPING
    virtual void execBeginEditV(ConstFieldMaskArg whichField,
                                UInt32            uiAspect,
                                UInt32            uiContainerSize) = 0;

    OSG_SYSTEM_DLLMAPPING
            void execBeginEdit (ConstFieldMaskArg whichField,
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
            void onCreateAspect(const FieldContainer *createAspect,
                                const FieldContainer *source      = NULL);
    OSG_SYSTEM_DLLMAPPING
            void onCreate      (const FieldContainer *source      = NULL);

    OSG_SYSTEM_DLLMAPPING
    virtual void onDestroy     (      UInt32          uiContainerId     );

    OSG_SYSTEM_DLLMAPPING
    virtual bool deregister    (      UInt32          uiContainerId     );

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjPtr createAspectCopy(void) const = 0;
#endif

    OSG_SYSTEM_DLLMAPPING
    virtual void resolveLinks   (      void                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
            void registerChangedContainer (void);

    OSG_SYSTEM_DLLMAPPING
    virtual void registerChangedContainerV(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Local Edit                                */
    /*! \{                                                                 */

    void editSField(ConstFieldMaskArg whichField);

    template<class FieldT>
    void editMField(ConstFieldMaskArg whichField,
                    FieldT            &oField   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    friend struct PointerFuncs;
    friend struct CPointerFuncs;

    template<class ContainerPtr>
    friend ContainerPtr convertToCurrentAspect(ContainerPtr pFC);

#ifdef OSG_MT_CPTR_ASPECT
    friend struct HandledFieldContainerFactoryDesc;

    friend class  FieldContainerType;
    friend class  ChangeList;
#endif
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainer &source);
};

OSG_SYSTEM_DLLMAPPING
void
appendTypesVector (const std::vector<std::string>                &typeNames,
                         std::vector<const FieldContainerType *> &types       );

OSG_SYSTEM_DLLMAPPING
void
appendGroupsVector(const std::vector<std::string>                &groupNames,
                         std::vector<UInt16>                     &groupIds    );

OSG_SYSTEM_DLLMAPPING
void
appendTypesString (const std::string                             &typesString,
                         std::vector<const FieldContainerType *> &types       );

OSG_SYSTEM_DLLMAPPING
FieldContainerPtr
deepClone(      FieldContainerPtrConstArg                src,
          const std::vector<std::string>                &shareTypeNames,
          const std::vector<std::string>                &ignoreTypeNames   =
              std::vector<std::string>(),
          const std::vector<std::string>                &shareGroupNames   =
              std::vector<std::string>(),
          const std::vector<std::string>                &ignoreGroupNames  =
              std::vector<std::string>()                                    );

OSG_SYSTEM_DLLMAPPING
FieldContainerPtr
deepClone(      FieldContainerPtrConstArg                src,
          const std::vector<UInt16>                     &shareGroupIds,
          const std::vector<UInt16>                     &ignoreGroupIds    =
              std::vector<UInt16>()                                         );

OSG_SYSTEM_DLLMAPPING
FieldContainerPtr
deepClone(      FieldContainerPtrConstArg                src,
          const std::string                             &shareTypesString,
          const std::string                             &ignoreTypesString =
              std::string()                                                 );

OSG_SYSTEM_DLLMAPPING
FieldContainerPtr
deepClone(      FieldContainerPtrConstArg                src,
          const std::vector<const FieldContainerType *> &shareTypes        =
              std::vector<const FieldContainerType *>(),
          const std::vector<const FieldContainerType *> &ignoreTypes       =
              std::vector<const FieldContainerType *>(),
          const std::vector<UInt16>                     &shareGroupIds     =
              std::vector<UInt16>(),
          const std::vector<UInt16>                     &ignoreGroupIds    =
              std::vector<UInt16>()                                         );

#ifdef OSG_MT_CPTR_ASPECT
template<class ContainerPtr> inline
ContainerPtr convertToCurrentAspect(ContainerPtr pFC);
#endif

OSG_END_NAMESPACE

#define OSGFIELDCONTAINER_HEADER_CVSID "@(#)$Id$"

#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainer.inl"

#endif /* _OSGFIELDCONTAINER_H_ */
