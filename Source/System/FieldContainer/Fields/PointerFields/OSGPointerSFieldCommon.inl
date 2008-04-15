
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerSFieldCommon.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class PointerSFieldCommon<AccessHandlerT,NamespaceI>

 */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerSFieldCommon<AccessHandlerT,
                    NamespaceI    >::PointerSFieldCommon(void) :
    Inherited()
{
}

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerSFieldCommon<AccessHandlerT,
                    NamespaceI    >::PointerSFieldCommon(const Self &source) :
    Inherited()
{
    _fieldValue = source._fieldValue;

    AccessHandler::onAdd(this, _fieldValue);
}

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerSFieldCommon<AccessHandlerT,
                    NamespaceI    >::PointerSFieldCommon(const_value value) :
    Inherited()
{
    _fieldValue = value;

    AccessHandler::onAdd(this, _fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerSFieldCommon<AccessHandlerT,
                    NamespaceI    >::~PointerSFieldCommon(void)
{
    AccessHandler::onSub(this, _fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Store Interface                                                         */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerSFieldCommon<AccessHandlerT,
                             NamespaceI    >::const_value 
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreGet(void) const
{
    return AccessHandler::validate(_fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerSFieldCommon<AccessHandlerT,
                         NamespaceI     >::ptrStoreSet(const_value pNewObj)
{
    AccessHandler::onReplace(this, _fieldValue, pNewObj);
    
    _fieldValue = pNewObj;
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerSFieldCommon<AccessHandlerT,
                         NamespaceI    >::ptrStoreClear(void)
{
    AccessHandler::onSub(this, _fieldValue);
    
    _fieldValue = NullFC;
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

        
template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerSFieldCommon<AccessHandlerT,
                         NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    FieldContainerPtr pNewObj;
    
    PtrBaseTraitsType::copyFromBin  ( pMem, 
                                      pNewObj   );

    AccessHandler    ::onSyncReplace( this, 
                                     _fieldValue, 
                                      pNewObj   );
    
    _fieldValue = pNewObj;
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerSFieldCommon<AccessHandlerT,
                         NamespaceI     >::syncWith(Self &source)
{
    FieldContainerPtr pNewObj = convertToCurrentAspect(source.ptrStoreGet());
    
    AccessHandler::onSyncReplace( this, 
                                 _fieldValue, 
                                  pNewObj);
    
    _fieldValue = pNewObj;
}
#endif

OSG_END_NAMESPACE
