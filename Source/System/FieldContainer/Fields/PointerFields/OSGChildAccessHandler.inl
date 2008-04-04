
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildAccessHandlerDecl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class ChildAccessHandler

    Access handler for child pointer fields.
    This class handles all reference counting and child/parent linking
    operations for child pointer fields. The fields only call the respective
    members when an operation on one of their values is performed.
 */

/*-------------------------------------------------------------------------*/
/* Internal Helper                                                         */

inline ChildAccessHandler::SFieldType * const
    ChildAccessHandler::dcastSField(SFieldBaseType * const pSField)
{
    return static_cast<SFieldType *>(pSField);
}

inline ChildAccessHandler::MFieldType * const
    ChildAccessHandler::dcastMField(MFieldBaseType * const pMField)
{
    return static_cast<MFieldType *>(pMField);
}

/*-------------------------------------------------------------------------*/
/* Linking                                                                 */

inline void
    ChildAccessHandler::linkParent(
        FieldContainerPtrConst pParent,
        UInt16 const           childFieldId,
        FieldContainerPtrConst pChild,
        UInt16 const           parentFieldId )
{
        pChild->linkParent(pParent, childFieldId, parentFieldId);
}

inline void
    ChildAccessHandler::unlinkParent(
        FieldContainerPtrConst pParent,
        FieldContainerPtrConst pChild,
        UInt16 const           parentFieldId)
{
    pChild->unlinkParent(pParent, parentFieldId);
}

/*-------------------------------------------------------------------------*/
/* Access Handling                                                         */

inline void
    ChildAccessHandler::onAdd(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    if(pObj != NULL)
    {
        RefCountPolicyType::addRef(pObj, false);

        linkParent(dcastSField(pSField)->getEnclosingObject(),
                   dcastSField(pSField)->getChildFieldId   (),
                   pObj,
                   dcastSField(pSField)->getParentFieldId  () );
    }
}

inline void
    ChildAccessHandler::onAdd(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    if(pObj != NULL)
    {
        RefCountPolicyType::addRef(pObj, false);

        linkParent(dcastMField(pMField)->getEnclosingObject(),
                   dcastMField(pMField)->getChildFieldId   (),
                   pObj,
                   dcastMField(pMField)->getParentFieldId  () );
    }
}

inline void
    ChildAccessHandler::onSub(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    if(pObj != NULL)
    {
        unlinkParent(dcastSField(pSField)->getEnclosingObject(),
                     pObj,
                     dcastSField(pSField)->getParentFieldId()   );

        RefCountPolicyType::subRef(pObj, false);
    }
}

inline void
    ChildAccessHandler::onSub(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    if(pObj != NULL)
    {
        unlinkParent(dcastMField(pMField)->getEnclosingObject(),
                     pObj,
                     dcastMField(pMField)->getParentFieldId()   );

        RefCountPolicyType::subRef(pObj, false);
    }
}

inline void
    ChildAccessHandler::onReplace(
        SFieldBaseType * const pSField,
        FieldContainerPtrConst pOldObj, FieldContainerPtrConst pNewObj)
{
    RefCountPolicyType::addRef(pNewObj);

    if(pOldObj != NULL)
    {
        unlinkParent(dcastSField(pSField)->getEnclosingObject(),
                     pOldObj,
                     dcastSField(pSField)->getParentFieldId()   );

        RefCountPolicyType::subRef(pOldObj, false);
    }

    if(pNewObj != NULL)
        linkParent(dcastSField(pSField)->getEnclosingObject(),
                   dcastSField(pSField)->getChildFieldId   (),
                   pNewObj,
                   dcastSField(pSField)->getParentFieldId  () );
}

inline void
    ChildAccessHandler::onReplace(
        MFieldBaseType      * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    RefCountPolicyType::addRef(pNewObj);

    if(pOldObj != NULL)
    {
        unlinkParent(dcastMField(pMField)->getEnclosingObject(),
                     pOldObj,
                     dcastMField(pMField)->getParentFieldId()   );

        RefCountPolicyType::subRef(pOldObj, false);
    }

    if(pNewObj != NULL)
        linkParent(dcastMField(pMField)->getEnclosingObject(),
                   dcastMField(pMField)->getChildFieldId   (),
                   pNewObj,
                   dcastMField(pMField)->getParentFieldId  () );
}

/*-------------------------------------------------------------------------*/
/* Sync Access Handling                                                    */

inline void
    ChildAccessHandler::onSyncAdd(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    ChildAccessHandler::onSyncAdd(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    ChildAccessHandler::onSyncSub(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    ChildAccessHandler::onSyncSub(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    ChildAccessHandler::onSyncReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj )
{
    onSyncAdd(pSField, pNewObj);
    onSyncSub(pSField, pOldObj);
}

inline void
    ChildAccessHandler::onSyncReplace(
        MFieldBaseType         * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pMField, pNewObj);
    onSyncSub(pMField, pOldObj);
}

OSG_END_NAMESPACE
