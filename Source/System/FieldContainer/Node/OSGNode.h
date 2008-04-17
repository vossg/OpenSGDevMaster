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

#ifndef _OSGNODE_H_
#define _OSGNODE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGReflexiveContainer.h"
#include "OSGMatrix.h"
#include "OSGFieldContainer.h"
#include "OSGAttachmentContainer.h"

#include "OSGDynamicVolumeFields.h"
#include "OSGUInt32Fields.h"

#include "OSGNodeFields.h"
#include "OSGNodeCoreFields.h"
#include "OSGFieldContainerFactory.h"

#include <boost/assign/list_of.hpp>

OSG_BEGIN_NAMESPACE

/**
 * A Node in OpenSG is a node in the graph.
 *
 * Nodes are responsible for holding children nodes and a link to their parent
 * node.
 *
 * \ingroup baselib
 */
class OSG_SYSTEM_DLLMAPPING Node : public AttachmentContainer
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef AttachmentContainer                    Inherited;
    typedef AttachmentContainer                    ParentContainer;

    OSG_GEN_INTERNALPTR(Node);

    typedef Inherited::TypeObject                  TypeObject;

    typedef Node                                   Self;

    OSG_RC_FIRST_FIELD_DECL(Volume            );

    OSG_RC_FIELD_DECL      (TravMask, Volume  );
    OSG_RC_FIELD_DECL      (Parent,   TravMask);
    OSG_RC_FIELD_DECL      (Core,     Parent  );
    OSG_RC_FIELD_DECL      (Children, Core    );

    OSG_RC_LAST_FIELD_DECL (Children          );

    static const BitVector bLocalFieldMask   = (VolumeFieldMask    |
                                                TravMaskFieldMask  |
                                                ParentFieldMask    |
                                                ChildrenFieldMask  |
                                                CoreFieldMask      );

    static const BitVector bInvLocalFieldMask = ~bLocalFieldMask;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_DECL;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NodeCorePtr getCore(void                    );
    NodeCorePtr getCore(void                    ) const;

    void        setCore(NodeCorePtrConstArg core);
    
    template <class ObjectT>
    void        setCore(TransitPtr<ObjectT>  core);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    NodePtr getParent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    UInt32  getNChildren  (void                      ) const;

    void    addChild      (NodePtrConstArg childP    );
    void    addChild      (NodeTransitPtr  childP    );

    void    insertChild   (UInt32          childIndex,
                           NodePtrConstArg childP    );

    void    replaceChild  (UInt32          childIndex,
                           NodePtrConstArg childP    );

    bool    replaceChildBy(NodePtrConstArg childP,
                           NodePtrConstArg newChildP );

    Int32   findChild     (NodePtrConstArg childP    ) const;

    void    subChild      (NodePtrConstArg childP    );
    void    subChild      (UInt32          childIndex);

    NodePtr getChild      (UInt32          childIndex);

    void    clearChildren (void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    void   setTravMask     (UInt32 uiMask);
    UInt32 getTravMask     (void         ) const;

#ifdef OSG_1_COMPAT
    bool   getActive       (void         ) const;
    void   setActive       (bool      val);

    void   setOcclusionMask(UInt8     val);
    UInt8  getOcclusionMask(void         ) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    Matrixr getToWorld(void           );

    void    getToWorld(Matrixr &result);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

#ifdef OSG_1_GET_COMPAT
            DynamicVolume &getVolume       (bool update = false  );
#endif

            DynamicVolume &editVolume      (bool update = false  );

    const   DynamicVolume &getVolume       (void                 ) const;

            void           getWorldVolume  (DynamicVolume &result);

            void           updateVolume    (void                 );

    virtual void           invalidateVolume(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

          SFDynamicVolume         *editSFVolume  (void);
    const SFDynamicVolume         *getSFVolume   (void) const;

          SFUInt32                *editSFTravMask(void);
    const SFUInt32                *getSFTravMask (void) const;

    const SFUncountedNodePtr      *getSFParent   (void) const;
    const SFUnrecChildNodeCorePtr *getSFCore     (void) const;
    const MFUnrecChildNodePtr     *getMFChildren (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFDynamicVolume         _sfVolume;

    SFUInt32                _sfTravMask;

    SFUncountedNodePtr      _sfParent;
    MFUnrecChildNodePtr     _mfChildren;

    SFUnrecChildNodeCorePtr _sfCore;

#ifdef OSG_1_COMPAT
    UInt8                   _occlusionMask;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    Node(void);
    Node(const Node &source);

    virtual ~Node(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual bool linkParent  (const FieldContainerPtr pParent,
                              const UInt16            childFieldId,
                              const UInt16            parentFieldId);

    virtual bool unlinkParent(const FieldContainerPtr pParent,
                              const UInt16            parentFieldId);
            
    virtual bool unlinkChild (const FieldContainerPtr pChild,
                              const UInt16            childFieldId ); 


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjPtr createAspectCopy(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      Node              *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    EditFieldHandlePtr editHandleVolume  (void);
    GetFieldHandlePtr  getHandleVolume   (void) const;
    
    EditFieldHandlePtr editHandleTravMask(void);
    GetFieldHandlePtr  getHandleTravMask (void) const;
    
    GetFieldHandlePtr  getHandleParent   (void) const;
    
    EditFieldHandlePtr editHandleCore    (void);
    GetFieldHandlePtr  getHandleCore     (void) const;

    EditFieldHandlePtr editHandleChildren(void);
    GetFieldHandlePtr  getHandleChildren (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class  FieldContainer;
    template<class    ValueT, 
             typename RefCountPolicy, 
             Int32    iNamespace    >
    friend class FieldContainerPtrChildMField;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Node &source);
};

OSG_SYSTEM_DLLMAPPING
NodeTransitPtr cloneTree(      
          NodePtrConstArg                          rootNode,
    const std::vector<std::string>                &cloneTypeNames,

    const std::vector<std::string>                &ignoreTypeNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                &cloneGroupNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                &ignoreGroupNames  =
              std::vector<std::string>()                              );

OSG_SYSTEM_DLLMAPPING
NodeTransitPtr cloneTree(      
          NodePtrConstArg                          rootNode,
    const std::vector<UInt16>                     &cloneGroupIds,
    const std::vector<UInt16>                     &ignoreGroupIds    =
              std::vector<UInt16>()                                   );

OSG_SYSTEM_DLLMAPPING
NodeTransitPtr cloneTree(      
          NodePtrConstArg                          rootNode,
    const std::string                             &cloneTypesString,
    const std::string                             &ignoreTypesString =
              std::string()                                           );

#ifdef OSG_1_COMPAT
OSG_SYSTEM_DLLMAPPING
NodeTransitPtr cloneTree(      
          NodePtrConstArg                              rootNode,

    const std::vector<const ReflexiveContainerType *> &cloneTypes        =
              std::vector<const ReflexiveContainerType *>(),

    const std::vector<const ReflexiveContainerType *> &ignoreTypes       =
          boost::assign::list_of(
              &FieldContainerAttachment::getClassType()),

    const std::vector<UInt16>                     &cloneGroupIds     =
              std::vector<UInt16>(),
    const std::vector<UInt16>                     &ignoreGroupIds    =
              std::vector<UInt16>()                                          );
#else
OSG_SYSTEM_DLLMAPPING
NodeTransitPtr cloneTree(      
          NodePtrConstArg                          rootNode,

    const std::vector<const ReflexiveContainerType *> &cloneTypes        =
              std::vector<const ReflexiveContainerType *>(),

    const std::vector<const ReflexiveContainerType *> &ignoreTypes       =
              std::vector<const ReflexiveContainerType *>(),

    const std::vector<UInt16>                     &cloneGroupIds     =
              std::vector<UInt16>(),

    const std::vector<UInt16>                     &ignoreGroupIds    =
              std::vector<UInt16>()                                          );
#endif

OSG_SYSTEM_DLLMAPPING
NodeTransitPtr deepCloneTree(
          NodePtrConstArg                          rootNode,
    const std::vector<std::string>                &shareTypeNames,

    const std::vector<std::string>                &ignoreTypeNames  =
              std::vector<std::string>(),

    const std::vector<std::string>                &shareGroupNames  =
              std::vector<std::string>(),

    const std::vector<std::string>                &ignoreGroupNames =
              std::vector<std::string>()                                  );

OSG_SYSTEM_DLLMAPPING
NodeTransitPtr deepCloneTree(      
          NodePtrConstArg                          rootNode,
    const std::vector<UInt16>                     &shareGroupIds,

    const std::vector<UInt16>                     &ignoreGroupIds   =
              std::vector<UInt16>()                                       );

OSG_SYSTEM_DLLMAPPING
NodeTransitPtr deepCloneTree(      
          NodePtrConstArg                          rootNode,
    const std::string                             &shareTypesString,

    const std::string                             &ignoreTypesString =
              std::string()                                               );

OSG_SYSTEM_DLLMAPPING
NodeTransitPtr deepCloneTree(      
          NodePtrConstArg                          rootNode,

    const std::vector<const ReflexiveContainerType *> &shareTypes     =
              std::vector<const ReflexiveContainerType *>(),

    const std::vector<const ReflexiveContainerType *> &ignoreTypes    =
              std::vector<const ReflexiveContainerType *>(),

    const std::vector<UInt16>                     &shareGroupIds  =
              std::vector<UInt16>(),
    const std::vector<UInt16>                     &ignoreGroupIds =
              std::vector<UInt16>()                                       );

template <class Core> inline
NodeTransitPtr makeCoredNode(typename Core::ObjRecPtr *coreP = NULL);

template <class CorePtr> inline
NodeTransitPtr makeNodeFor(CorePtr core);

OSG_END_NAMESPACE

#include "OSGNodeCore.h"
#include "OSGNode.inl"
#include "OSGCoredNodePtr.h"

#endif /* _OSGNODE_H_ */
