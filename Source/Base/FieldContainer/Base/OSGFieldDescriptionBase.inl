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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
const Char8 *FieldDescriptionBase::getCName(void) const
{
    return _szName.c_str();
}

inline
std::string FieldDescriptionBase::getName(void) const
{
    return _szName;
}

inline
std::string  FieldDescriptionBase::getDocumentation (void) const
{
    return _documentation;
}

inline
UInt32 FieldDescriptionBase::getTypeId(void) const
{
    return _fieldType.getId();
}

inline
BitVector FieldDescriptionBase::getFieldMask(void) const
{
    return _vFieldMask;
}

inline
void FieldDescriptionBase::setFieldMask(ConstFieldMaskArg vFieldMask)
{
    _vFieldMask = vFieldMask;
}

inline
UInt32 FieldDescriptionBase::getFieldId(void) const
{
    return _uiFieldId;
}

inline
void FieldDescriptionBase::setFieldId(UInt32 uiFieldId)
{
    _uiFieldId = uiFieldId;
}

inline
const FieldType &FieldDescriptionBase::getFieldType(void) const
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/*                                Is                                       */

inline
bool FieldDescriptionBase::isInternal(void)  const
{
    return _bInternal;
}

inline
bool FieldDescriptionBase::isSField(void) const
{
    return (_fieldType.getCardinality() == FieldType::SingleField);
}

inline
bool FieldDescriptionBase::isMField(void) const
{
    return (_fieldType.getCardinality() == FieldType::MultiField);
}

inline
bool FieldDescriptionBase::isDynamic(void) const
{
    return _bDynamic;
}

inline
void FieldDescriptionBase::setFlags(UInt32 uiFlags)
{
    _uiFieldFlags = uiFlags;
}

inline
UInt32 FieldDescriptionBase::getFlags(void) const
{
    return _uiFieldFlags;
}

inline
bool FieldDescriptionBase::isValid(void)  const
{
    return (_szName.size()) ? true : false;
}

inline
EditFieldHandlePtr FieldDescriptionBase::editField(
    ReflexiveContainer &oContainer) const
{
    EditFieldHandlePtr pFieldHandle;

#ifdef FDESC_USE_BOOST
    if(_fEditMethod.empty() == false)
    {
        pField = _fEditMethod(&oContainer);
    }
    else if(_fIndexedEditMethod.empty() == false)
    {
        pField = _fIndexedEditMethod(&oContainer, _uiFieldId);
    }
#else
    if(_fEditMethod != 0)
    {
        pFieldHandle = ( (&oContainer)->*_fEditMethod) ();
    }
    else if(_fIndexedEditMethod != 0)
    {
        pFieldHandle = ( (&oContainer)->*_fIndexedEditMethod)(_uiFieldId);
    }
#endif

    return pFieldHandle;
}

inline
GetFieldHandlePtr FieldDescriptionBase::getField(
    const ReflexiveContainer &oContainer) const
{
    GetFieldHandlePtr pFieldHandle;
    
#ifdef FDESC_USE_BOOST
    if(_fGetMethod.empty() == false)
    {
        pField = _fGetMethod(&oContainer);
    }
    else if(_fIndexedGetMethod.empty() == false)
    {
        pField = _fIndexedGetMethod(&oContainer, _uiFieldId);
    }
#else
    if(_fGetMethod != 0)
    {
        pFieldHandle = ( (&oContainer)->*_fGetMethod) ();
    }
    else if(_fIndexedGetMethod != 0)
    {
        pFieldHandle = ( (&oContainer)->*_fIndexedGetMethod)(_uiFieldId);
    }
#endif

    return pFieldHandle;
}

inline
void FieldDescriptionBase::setDynamic(bool bDynamic)
{
    _bDynamic = bDynamic;
}

#if 0
inline
FieldDescriptionBase *FieldDescriptionBase::clone(void) const
{
    return new FieldDescriptionBase(*this);
}
#endif

inline
bool FieldDescriptionBasePLT::operator()(
    const FieldDescriptionBase *pElemDesc1, 
    const FieldDescriptionBase *pElemDesc2) const
{
    return (pElemDesc1->getFieldId() < pElemDesc2->getFieldId());
}



template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
FieldDescription<DescT, 
                 eFieldCard, 
                 RefCountPolicy, 
                 eFieldClass   >::FieldDescription(
    const FieldType       &elementType,
    const Char8           *szName,
          std::string      documentation,
    const UInt32           uiFieldId,
    const BitVector        vFieldMask,
    const bool             bInternal,
    const UInt32           uiFieldFlags,
          FieldEditMethod  fEditMethod,
          FieldGetMethod   fGetMethod) :

    Inherited(elementType,
              szName,
              documentation,
              uiFieldId,
              vFieldMask,
              bInternal,
              uiFieldFlags,
              fEditMethod,
              fGetMethod)
{
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
FieldDescription<DescT, 
                 eFieldCard, 
                 RefCountPolicy, 
                 eFieldClass   >::FieldDescription(
    const FieldType            &elementType,
    const Char8                *szName,
    std::string                 documentation,
    const UInt32                uiFieldId,
    const BitVector             vFieldMask,
    const bool                  bInternal,
    const UInt32                uiFieldFlags,
          FieldIndexEditMethod  fIndexedEditMethod,
          FieldIndexGetMethod   fIndexedGetMethod) :

    Inherited(elementType,
              szName,
              documentation,
              uiFieldId,
              vFieldMask,
              bInternal,
              uiFieldFlags,
              fIndexedEditMethod,
              fIndexedGetMethod)
{
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
FieldDescription<DescT, 
                 eFieldCard, 
                 RefCountPolicy, 
                 eFieldClass   >::FieldDescription(
    const FieldDescription &source) :

    Inherited(source)
{
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
FieldDescription<DescT, 
                 eFieldCard, 
                 RefCountPolicy, 
                 eFieldClass   >::~FieldDescription(void)
{
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
const typename FieldDescription<DescT, 
                                eFieldCard, 
                                RefCountPolicy, 
                                eFieldClass   >::HandledField *
    FieldDescription<DescT, 
                     eFieldCard,  
                     RefCountPolicy,
                     eFieldClass   >::dcast_const(const Field *pField) const
{
    return static_cast<const HandledField *>(pField);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
typename FieldDescription<DescT, 
                          eFieldCard, 
                          RefCountPolicy, 
                          eFieldClass   >::HandledField *
    FieldDescription<DescT, 
                     eFieldCard, 
                     RefCountPolicy, 
                     eFieldClass   >::dcast(Field *pField) const
{
    return static_cast<HandledField *>(pField);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
Field *FieldDescription<DescT, 
                        eFieldCard, 
                        RefCountPolicy, 
                        eFieldClass   >::createField(void) const
{
    return FieldCreateHandler::createField(); //return new HandledField();
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT, 
                      eFieldCard,  
                      RefCountPolicy,
                      eFieldClass   >::destroyField(Field *pField) const
{
    HandledField *pDelField = dcast(pField);

    delete pDelField;
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
FieldDescriptionBase *FieldDescription<DescT, 
                                       eFieldCard,  
                                       RefCountPolicy,
                                       eFieldClass   >::clone(void) const
{
    return new Self(*this);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
GetFieldHandlePtr 
    FieldDescription<DescT, 
                     eFieldCard,  
                     RefCountPolicy,
                     eFieldClass   >::createGetHandler(
                         const Field          *pField,
                               FieldContainer *pCnt  )
{
    const HandledField *pTypedField = dcast_const(pField);

    GetHandlePtr returnValue(new GetHandle(pTypedField, this, pCnt));

    return returnValue;
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
EditFieldHandlePtr 
    FieldDescription<DescT, 
                     eFieldCard,  
                     RefCountPolicy,
                     eFieldClass   >::createEditHandler(Field          *pField,
                                                        FieldContainer *pCnt)
{
    return CreateEditHandler::createHandler(pField, this, pCnt);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
BasicFieldConnector *FieldDescription<
          DescT, 
          eFieldCard,  
          RefCountPolicy,
          eFieldClass   >::DefaultFieldCreateHandler::createConnector(

    const FieldDescriptionBase *pSrcDesc,
    const HandledField         *pSrc,
    const FieldDescriptionBase *pDstDesc,
          HandledField         *pDst)
{
    typedef typename FieldFunctions::FConnector ReturnType;

    BasicFieldConnector *returnValue = NULL;

    if(                    pSrc == NULL ||
       pDstDesc == NULL || pDst == NULL  )
    {
        return returnValue;
    }        

    if(pSrcDesc->getFieldType() != pDstDesc->getFieldType())
    {
#if 0
        fprintf(stderr, "typemismatch try fact (%s | %s)\n",
                pSrcDesc->getFieldType().getCName(),
                pDstDesc->getFieldType().getCName());
#endif

        returnValue = FieldConnectorFactory::the()->createConnector(pSrcDesc,
                                                                    pSrc,
                                                                    pDstDesc,
                                                                    pDst    );

        if(returnValue == NULL)
        {
            fprintf(stderr, "typemismatch failed (%s | %s)\n",
                    pSrcDesc->getFieldType().getCName(),
                    pDstDesc->getFieldType().getCName());
        }

#if 0 // needs more infrastructure
        if(pSrcDesc->getFieldType().isPtrField() == true &&
           pDstDesc->getFieldType().isPtrField() == true  )
        {
            fprintf(stderr, "try ptr field content (%s | %s)\n",
                    pSrcDesc->getFieldType().getContentType().getCName(),
                    pDstDesc->getFieldType().getContentType().getCName());

            if(pSrcDesc->getFieldType().getContentType() != 
               pDstDesc->getFieldType().getContentType()   )
            {
                fprintf(stderr, "failed\n");

                return returnValue;
            }
        }
        else
        {
            return returnValue;
        }
#else
        return returnValue;
#endif

    }
    else
    {
        returnValue = new ReturnType(pSrc, pSrcDesc->getFieldMask(),
                                     pDst, pDstDesc->getFieldMask());
    }

    return returnValue;
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
BasicFieldConnector *FieldDescription<DescT, 
                     eFieldCard,  
                     RefCountPolicy,
                     eFieldClass   >::createConnector(
    const Field                *pSrc,
    const FieldDescriptionBase *pDstDesc,
          Field                *pDst) const
{
    return FieldCreateHandler::createConnector(this,
                                               dcast_const(pSrc),
                                               pDstDesc,
                                               dcast      (pDst));
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                     eFieldCard, 
                     RefCountPolicy,
                     eFieldClass   >::SFieldFunctions::beginEdit(
                          HandledField       *,
                          UInt32              ,
                          AspectOffsetStore  &)
{
}

template<class    DescT,
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                      eFieldCard, 
                      RefCountPolicy,
                      eFieldClass   >::MFieldFunctions::beginEdit(
                          HandledField       *pField,
                          UInt32              uiAspect,
                          AspectOffsetStore  &oOffsets)
{
    pField->beginEdit(uiAspect, oOffsets);
}


template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
bool FieldDescription<DescT,
                      eFieldCard,
                      RefCountPolicy,
                      eFieldClass   >::SFieldFunctions::isShared(
                          HandledField *)
{
    return false;
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
bool FieldDescription<DescT,
                      eFieldCard,  
                      RefCountPolicy,
                      eFieldClass   >::MFieldFunctions::isShared(
                          HandledField *pField)
{
    return pField->isShared();
}
template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                      eFieldCard,
                      RefCountPolicy,
                      eFieldClass   >::SFieldFunctions::sync(      
                                HandledField      *pTo, 
                                HandledField      *pFrom,
                                AspectOffsetStore &oOffsets,
                                ConstFieldMaskArg  syncMode,
                          const UInt32             uiSyncInfo)
{
    pTo->syncWith(*pFrom);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                      eFieldCard,  
                      RefCountPolicy,
                      eFieldClass   >::MFieldFunctions::sync(      
                                HandledField      *pTo, 
                                HandledField      *pFrom,
                                AspectOffsetStore &oOffsets,
                                ConstFieldMaskArg  syncMode,
                          const UInt32             uiSyncInfo)
{
    pTo->syncWith(*pFrom,
                   syncMode, 
                   uiSyncInfo,
                   oOffsets  );
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                      eFieldCard, 
                      RefCountPolicy,
                      eFieldClass   >::beginEdit(Field              *pField,
                                                 UInt32              uiAspect,
                                                 AspectOffsetStore  &oOffsets)
{
    HandledField *pTypedField = dcast(pField);
    
    FieldFunctions::beginEdit(pTypedField, uiAspect, oOffsets);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
bool FieldDescription<DescT,
                      eFieldCard, 
                      RefCountPolicy,
                      eFieldClass   >::isShared(Field *pField)
{
    HandledField *pTypedField = dcast(pField);
    
    return FieldFunctions::isShared(pTypedField);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                      eFieldCard, 
                      RefCountPolicy,
                      eFieldClass   >::sync(      
                                Field             *pTo, 
                                Field             *pFrom,
                                AspectOffsetStore &oOffsets,
                                ConstFieldMaskArg  syncMode,
                          const UInt32             uiSyncInfo) const
{
    HandledField *pTypedTo   = dcast(pTo  );
    HandledField *pTypedFrom = dcast(pFrom);

    FieldFunctions::sync(pTypedTo,
                         pTypedFrom,
                         oOffsets,
                         syncMode,
                         uiSyncInfo );
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
SizeT FieldDescription<DescT,
                       eFieldCard, 
                       RefCountPolicy,
                       eFieldClass   >::getBinSize (Field *pField) const
{
    const HandledField *pTypedField = dcast_const(pField);

    return pTypedField->getBinSize();
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                      eFieldCard, 
                      RefCountPolicy,
                      eFieldClass   >::copyToBin(
                          BinaryDataHandler &pMem,
                          Field             *pField) const
{
    const HandledField *pTypedField = dcast_const(pField);

    pTypedField->copyToBin(pMem);
}

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy,
         enum     FieldType::Class       eFieldClass> inline
void FieldDescription<DescT,
                      eFieldCard, 
                      RefCountPolicy,
                      eFieldClass   >::copyFromBin(
                          BinaryDataHandler &pMem,
                          Field             *pField) 
{
    HandledField *pTypedField = dcast(pField);

    pTypedField->copyFromBin(pMem);
}

OSG_END_NAMESPACE

