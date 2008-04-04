
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedAccessHandlerDecl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Access Handling                                                         */

inline void
    UnrecordedAccessHandler::onAdd(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    UnrecordedAccessHandler::onAdd(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

inline void
    UnrecordedAccessHandler::onSub(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    UnrecordedAccessHandler::onSub(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

inline void
    UnrecordedAccessHandler::onReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onAdd(pSField, pNewObj);
    onSub(pSField, pOldObj);
}

inline void
    UnrecordedAccessHandler::onReplace(
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
    UnrecordedAccessHandler::onSyncAdd(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onAdd(pSField, pObj);
}

inline void
    UnrecordedAccessHandler::onSyncAdd(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onAdd(pMField, pObj);
}

inline void
    UnrecordedAccessHandler::onSyncSub(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onSub(pSField, pObj);
}

inline void
    UnrecordedAccessHandler::onSyncSub(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onSub(pMField, pObj);
}

inline void
    UnrecordedAccessHandler::onSyncReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pSField, pNewObj);
    onSyncSub(pSField, pOldObj);
}

inline void
    UnrecordedAccessHandler::onSyncReplace(
        MFieldBaseType         * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pMField, pNewObj);
    onSyncSub(pMField, pOldObj);
}

OSG_END_NAMESPACE
