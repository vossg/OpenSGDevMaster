#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNoRefCountAccessHandlerDecl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Access Handling                                                         */

inline void
    NoRefCountAccessHandler::onAdd(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    NoRefCountAccessHandler::onAdd(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    NoRefCountAccessHandler::onSub(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    NoRefCountAccessHandler::onSub(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    NoRefCountAccessHandler::onReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onAdd(pSField, pNewObj);
    onSub(pSField, pOldObj);
}

inline void
    NoRefCountAccessHandler::onReplace(
        MFieldBaseType         * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onAdd(pMField, pNewObj);
    onSub(pMField, pOldObj);
}

/*-------------------------------------------------------------------------*/
/* Sync Access Handling                                                    */

inline void
    NoRefCountAccessHandler::onSyncAdd(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onAdd(pSField, pObj);
}

inline void
    NoRefCountAccessHandler::onSyncAdd(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onAdd(pMField, pObj);
}

inline void
    NoRefCountAccessHandler::onSyncSub(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onSub(pSField, pObj);
}

inline void
    NoRefCountAccessHandler::onSyncSub(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onSub(pMField, pObj);
}

inline void
    NoRefCoountAccessHandler::onSyncReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pSField, pNewObj);
    onSyncSub(pSField, pOldObj);
}

inline void
    NoRefCountAccessHandler::onSyncReplace(
        MFieldBaseType         * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pMField, pNewObj);
    onSyncSub(pMField, pOldObj);
}

OSG_END_NAMESPACE
