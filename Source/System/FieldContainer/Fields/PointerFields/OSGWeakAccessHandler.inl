
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakAccessHandlerDecl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Access Handling                                                         */

inline void
    WeakAccessHandler::onAdd(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    WeakAccessHandler::onAdd(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    WeakAccessHandler::onSub(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    WeakAccessHandler::onSub(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    WeakAccessHandler::onReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onAdd(pSField, pNewObj);
    onSub(pSField, pOldObj);
}

inline void
    WeakAccessHandler::onReplace(
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
    WeakAccessHandler::onSyncAdd(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onAdd(pSField, pObj);
}

inline void
    WeakAccessHandler::onSyncAdd(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onAdd(pMField, pObj);
}

inline void
    WeakAccessHandler::onSyncSub(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onSub(pSField, pObj);
}

inline void
    WeakAccessHandler::onSyncSub(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onSub(pMField, pObj);
}

inline void
    WeakAccessHandler::onSyncReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pSField, pNewObj);
    onSyncSub(pSField, pOldObj);
}

inline void
    WeakAccessHandler::onSyncReplace(
        MFieldBaseType         * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pMField, pNewObj);
    onSyncSub(pMField, pOldObj);
}

OSG_END_NAMESPACE
