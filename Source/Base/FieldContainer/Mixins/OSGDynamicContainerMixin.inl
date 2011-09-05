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

//#define OSG_DBGPRINT_DYNFC 1

OSG_BEGIN_NAMESPACE

#ifndef OSG_DOXYGEN_REC_MACRO_PROBS
template <class ParentT> inline
typename DynFieldContainer<ParentT>::TypeObject &
    DynFieldContainer<ParentT>::getType(void)
{
    return _localType;
}

template <class ParentT> inline
const typename DynFieldContainer<ParentT>::TypeObject &
    DynFieldContainer<ParentT>::getType(void) const
{
    return _localType;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Field Access                                 */

template <class ParentT> inline
UInt32 DynFieldContainer<ParentT>::addField(
    const FieldDescriptionBase &fieldDesc)
{
    UInt32                returnValue = 0;
    Field                *fieldP      = NULL;
    FieldDescriptionBase *descP       = NULL;

    // do some basic sanity checking
    if(fieldDesc.getFieldType().getClass() != FieldType::ValueField)
    {
        if(fieldDesc.getFieldType().getClass() != FieldType::PtrField)
        {
            FWARNING(("DynFieldContainer<>:addField: ChildPtrField and "
                      "ParentPtrField are not supported.\n"              ));
            return 0;
        }
        else if(0x0000 == (fieldDesc.getFlags() & Field::FStdAccess      ) &&
                0x0000 == (fieldDesc.getFlags() & Field::FNullCheckAccess)    )
        {
            FWARNING(("DynFieldContainer<>::addField: Only 'FStdAccess' or "
                      "'FNullCheckAccess' are supported.\n"                  ));
            return 0;
        }
    }
    
    returnValue = _localType.addDescription(fieldDesc);

#ifdef OSG_DBGPRINT_DYNFC
    fprintf(stderr, "add field %s | %d | %d | %d | %d | %d\n", 
            fieldDesc.getCName(),
            returnValue,
            Inherited::NextFieldId,
            _uiDescStartIdx,
            returnValue - Inherited::NextFieldId,
            returnValue - _uiDescStartIdx);
#endif

    if(returnValue != 0)
    {
        descP = _localType.getFieldDesc(returnValue);

        if(descP != NULL)
        {
            descP->setDynamic  (true       );
            descP->setFieldId  (returnValue);
            descP->setFieldMask(
                        TypeTraits<BitVector>::One << returnValue);

            fieldP = fieldDesc.createField();

            if(_dynFieldsV.size() <=
               returnValue - _uiDescStartIdx)
            {
                _dynFieldsV.resize((returnValue - _uiDescStartIdx) + 1);
            }

            _dynFieldsV[returnValue - _uiDescStartIdx] = fieldP;

            Thread::getCurrentChangeList()->addNewField(this->getId(), 
                                                        descP->getFieldMask());

            this->editSField(descP->getFieldMask());
        }
    }

    return returnValue;
}

template <class ParentT> inline
UInt32 DynFieldContainer<ParentT>::addField(const UInt32  uiFieldTypeId,
                                            const Char8  *szFieldName  )
{
    FieldDescriptionBase *pDesc = 
        FieldDescFactory::the()->createIdx(
            uiFieldTypeId,
            szFieldName,
            static_cast<OSG::FieldIndexEditMethodSig>(
                &Self::editDynamicField),
            static_cast<OSG::FieldIndexGetMethodSig >(
                &Self::getDynamicField));

    UInt32 returnValue = this->addField(*pDesc);

    delete pDesc;

    return returnValue;
}

template <class ParentT> inline
UInt32 DynFieldContainer<ParentT>::addField(const Char8 *szFieldType,
                                            const Char8 *szFieldName)
{
    FieldDescriptionBase *pDesc = 
        FieldDescFactory::the()->createByNameIdx(
            szFieldType,
            szFieldName,
            static_cast<OSG::FieldIndexEditMethodSig>(
                &Self::editDynamicField),
            static_cast<OSG::FieldIndexGetMethodSig >(
                &Self::getDynamicField));

    UInt32 returnValue = this->addField(*pDesc);

    delete pDesc;

    return returnValue;
}

template <class ParentT> inline
void DynFieldContainer<ParentT>::subField(UInt32 fieldId)
{
    FieldDescriptionBase *descP = _localType.getFieldDesc(fieldId);
    
    if(descP != NULL)
    {
        std::vector<Field *>::iterator vIt = _dynFieldsV.begin();

        vIt += fieldId - _uiDescStartIdx;

        if(vIt != _dynFieldsV.end())
        {
            descP->destroyField(*vIt);

            (*vIt) = NULL;
        }

        _localType.subDescription(fieldId);
    }
}

template <class ParentT> inline
GetFieldHandlePtr DynFieldContainer<ParentT>::getDynamicField(
    UInt32 index) const
{
          FieldDescriptionBase *pDesc  = _localType.getFieldDesc(index);
    const Field                *pField = NULL;

    GetFieldHandlePtr returnValue;

    if(pDesc != NULL)
    {
        pField = _dynFieldsV[index - _uiDescStartIdx];

        returnValue = pDesc->createGetHandler(pField, const_cast<Self *>(this));
    }

    return returnValue;
}

template <class ParentT> inline
EditFieldHandlePtr DynFieldContainer<ParentT>::editDynamicField(
    UInt32 index)
{
    FieldDescriptionBase *pDesc  = _localType.getFieldDesc(index);
    Field                *pField = NULL;

    EditFieldHandlePtr returnValue;

    if(pDesc != NULL)
    {
        pField = _dynFieldsV[index - _uiDescStartIdx];

        returnValue = pDesc->createEditHandler(pField, this);

        this->editSField(pDesc->getFieldMask());

        if(returnValue->getCardinality() == FieldType::MultiField)
        {
#ifdef OSG_MT_CPTR_ASPECT
            if(pDesc->isShared(pField) == true)
            {
                AspectOffsetStore oOffsets;

                this->_pAspectStore->fillOffsetArray(oOffsets, this);
                
                pDesc->beginEdit(pField,
                                 Thread::getCurrentAspect(),
                                 oOffsets                  );
            }
#endif
        }
    }

    return returnValue;
}

template <class ParentT> inline
GetFieldHandlePtr DynFieldContainer<ParentT>::getDynamicFieldByName(
    const Char8 *szName) const
{
          GetFieldHandlePtr     returnValue;
    const FieldDescriptionBase *descP = NULL;

    descP = _localType.getFieldDesc(szName);

    if(descP != NULL)
    {
        returnValue = descP->getField(*this);
    }

    return returnValue;
}


template <class ParentT> inline
EditFieldHandlePtr DynFieldContainer<ParentT>::editDynamicFieldByName(
    const Char8 *szName)
{
          EditFieldHandlePtr    returnValue;
    const FieldDescriptionBase *descP = NULL;

    descP = _localType.getFieldDesc(szName);

    if(descP != NULL)
    {
        returnValue = descP->editField(*this);
    }

    return returnValue;
}


template <class ParentT> inline
UInt32 DynFieldContainer<ParentT>::getBinSize (ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

#if 0
    for(UInt32 i = _uiDescStartIdx; i <= getType().getNumFieldDescs(); i++)
    {
        BitVector bvDynMask = TypeTraits<BitVector>::One << i;

        if(FieldBits::NoField != (whichField & bvDynMask))
        {

            FieldDescriptionBase *pDesc = this->getType().getFieldDesc(i);

            if(pDesc != NULL)
            {
                returnValue += 
                    pDesc->getBinSize(_dynFieldsV[i - _uiDescStartIdx]);
            }
        }
    }
#endif

    return returnValue;
}

template <class ParentT> inline
void DynFieldContainer<ParentT>::copyToBin  (BinaryDataHandler &pMem,
                                             ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

#if 0
    for(UInt32 i = _uiDescStartIdx; i <= getType().getNumFieldDescs(); i++)
    {
        BitVector bvDynMask = TypeTraits<BitVector>::One << i;

        if(FieldBits::NoField != (whichField & bvDynMask))
        {
            FieldDescriptionBase *pDesc = this->getType().getFieldDesc(i);

            if(pDesc != NULL)
            {
                pDesc->copyToBin(pMem, _dynFieldsV[i - _uiDescStartIdx]);
            }
        }
    }
#endif
}

template <class ParentT> inline
void DynFieldContainer<ParentT>::copyFromBin(BinaryDataHandler &pMem,
                                             ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

#if 0
    for(UInt32 i = _uiDescStartIdx; i <= getType().getNumFieldDescs(); i++)
    {
        BitVector bvDynMask = TypeTraits<BitVector>::One << i;

        if(FieldBits::NoField != (whichField & bvDynMask))
        {
            FieldDescriptionBase *pDesc = this->getType().getFieldDesc(i);

            if(pDesc != NULL)
            {
                pDesc->copyFromBin(pMem, _dynFieldsV[i - _uiDescStartIdx]);
            }
        }
    }
#endif
}

#if 0
template <class ParentT> inline
FieldContainer *DynFieldContainer<ParentT>::emptyCopy(void)
{
    ObjCPtr returnValue = DynFieldContainer<ParentT>::createEmpty();

    for(UInt32 i  = _uiDescStartIdx;
               i <= _localType.getNumFieldDescs();
             ++i)
    {
        returnValue->addField(*(_localType.getFieldDesc(i)));
    }

    return returnValue;
}

template <class ParentT> inline
FieldContainer *DynFieldContainer<ParentT>::clone(void)
{
    ObjCPtr returnValue = 
        DynFieldContainer<ParentT>::createEmptyLocal(
            ~this->getFieldFlags()->_bNamespaceMask);

    for(UInt32 i  = _uiDescStartIdx;
               i <= _localType.getNumFieldDescs();
             ++i)
    {
        returnValue->addField(*(_localType.getFieldDesc(i)));
    }

    for(UInt32 i  = _uiDescStartIdx;
               i <= _localType.getNumFieldDescs();
             ++i)
    {
        EditFieldHandlePtr fTarget = returnValue->editDynamicField(i);

        if(fTarget != NULL && fTarget->isValid() == true)
        {
            if(fTarget->isPointerField() == true)
            {
                fTarget->cloneValues(this->getDynamicField(i));
            }
            else
            {
                fTarget->copyValues (this->getDynamicField(i));
            }
        }
    }

    return returnValue;
}
#endif

template <class ParentT> inline
void DynFieldContainer<ParentT>::dump(
          UInt32    uiIndent, 
    const BitVector bvFlags ) const
{
#if !defined(__GCCXML__)
    indentLog(uiIndent, PLOG);
    PLOG << "DynFieldContainer ("
         << _dynFieldsV.size()
         << " | "
         << getType().getNumFieldDescs()
         << ")"
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 4;

    indentLog(uiIndent, PLOG);
    PLOG << "static fields" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 4;

    for(UInt32 i = 1; i < _uiDescStartIdx; i++)
    {
        indentLog(uiIndent, PLOG);

        if(getType().getFieldDesc(i) != NULL)
        {
            PLOG << "[" << i << "] " 
                 << getType().getFieldDesc(i)->getCName ()
                 << " "
                 << getType().getFieldDesc(i)->getFieldType().getCName()
                 << " ("
                 << getType().getFieldDesc(i)->getFieldType().getId()
                 << ")"
                 << " ("
                 << i
                 << ")"
                 << " ("
                 << const_cast<Self *>(this)->getField(
                     getType().getFieldDesc(i)->getFieldId())
                 << ")"
                 << std::endl;

            fprintf(stderr, "[%d] : 0x%016"PRIx64"\n",
                    i,
                    getType().getFieldDesc(i)->getFieldMask());
        }
        else
        {
            PLOG << "(null)"
                 << " ("
                 << i
                 << ")"
                 << " (null)"
                 << std::endl;
        }
    }

    uiIndent -= 4;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "dynamic fields" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 4;

    for(UInt32 i = _uiDescStartIdx; i <= getType().getNumFieldDescs(); i++)
    {
        indentLog(uiIndent, PLOG);

        if(getType().getFieldDesc(i) != NULL)
        {
            PLOG << "[" << i << "] " 
                 << getType().getFieldDesc(i)->getCName ()
                 << " "
                 << getType().getFieldDesc(i)->getFieldType().getCName()
                 << " ("
                 << getType().getFieldDesc(i)->getFieldType().getId()
                 << ")"
                 << " ("
                 << i
                 << ")"
                 << " ("
                 << const_cast<Self *>(this)->getField(
                     getType().getFieldDesc(i)->getFieldId())
                 << ")"
                 << std::endl;

            fprintf(stderr, "[%d] : 0x%016"PRIx64"\n",
                    i,
                    getType().getFieldDesc(i)->getFieldMask());

            fprintf(stderr, "Field Content :\n");

            IndentOutStreamMixin<OutStream> os(std::cerr);
            
            this->getField(i)->pushValueToStream(os);

            os << EndElemNL;
        }
        else
        {
            PLOG << "(null)"
                 << " ("
                 << i
                 << ")"
                 << " (null)"
                 << std::endl;
        }
    }

    uiIndent -= 4;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    for(UInt32 i = 0; i < _dynFieldsV.size(); ++i)
    {
        fprintf(stderr, "[%d] : %p\n",
                i,
                _dynFieldsV[i]);
    }

    uiIndent -= 4;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
#endif
}

OSG_FIELD_CONTAINER_ABSTR_TMPL_NO_TYPE_DEF(DynFieldContainer, ParentT)
//OSG_RC_GET_STATIC_TYPE_INL_TMPL_DEF   (DynFieldContainer, ParentT)
OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(DynFieldContainer, ParentT)

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
DynFieldContainer<ParentT>::DynFieldContainer(void) :
     Inherited     (           ),
    _localType     (Self::_type),
    _uiDescStartIdx(          0),
    _dynFieldsV    (           )
{
    if(GlobalSystemState == Running)
        _localType.initialize();
}

template <class ParentT> inline
DynFieldContainer<ParentT>::DynFieldContainer(
    const DynFieldContainer &source) :

     Inherited     (source               ),
    _localType     (source.getFinalType()),
    _uiDescStartIdx(                    0),
    _dynFieldsV    (source._dynFieldsV   ) // Do a real copy soon ;-)
{
    if(GlobalSystemState == Running)
        _localType.initialize();

    _uiDescStartIdx = _localType.getNumFieldDescs() + 1;

#ifdef OSG_DBGPRINT_DYNFC
    fprintf(stderr, "uiStartIdx : %d\n", 
            _uiDescStartIdx);
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ParentT> inline
DynFieldContainer<ParentT>::~DynFieldContainer(void)
{
    for(UInt32 i  = _uiDescStartIdx;
               i <= _localType.getNumFieldDescs();
             ++i)
    {
        this->subField(i);
    }

    _localType.terminate();
}
 
#ifdef OSG_MT_CPTR_ASPECT
#if 0
template <class ParentT> inline
FieldContainer *DynFieldContainer<ParentT>::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ObjCPtr returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const Self *>(pRefAspect),
                  dynamic_cast<const Self *>(this));

    return returnValue;
}
#endif

template <class ParentT> inline
void DynFieldContainer<ParentT>::execSync (
          DynFieldContainer  *pFrom,
          ConstFieldMaskArg   whichField,
          AspectOffsetStore  &oOffsets,
          ConstFieldMaskArg   syncMode  ,
    const UInt32              uiSyncInfo)
{
    // At least sync the parents for now
    Inherited::execSync(pFrom,
                        whichField,
                        oOffsets,
                        syncMode,
                        uiSyncInfo);

    if(this->_dynFieldsV.size() != pFrom->_dynFieldsV.size())
    {
#ifdef OSG_DBGPRINT_DYNFC
        fprintf(stderr, "Sync %d %ld | %d %ld\n",
                getType().getNumFieldDescs(),
                _dynFieldsV.size(),
                pFrom->getType().getNumFieldDescs(),
                pFrom->_dynFieldsV.size());
#endif

        for(UInt32 i  = getType().getNumFieldDescs() + 1; 
                   i <= pFrom->getType().getNumFieldDescs();
                 ++i)
        {
#ifdef OSG_DBGPRINT_DYNFC
            fprintf(stderr, "add [%d] %s | %s | %d \n", 
                    i,
                    pFrom->getType().getFieldDesc(i)->getCName(),
                    pFrom->getType().getFieldDesc(i)->getFieldType().getCName(),
                    pFrom->getType().getFieldDesc(i)->getFieldType().getId());
#endif

            UInt32 rc = this->addField(*(pFrom->getType().getFieldDesc(i)));

            osgSinkUnusedWarning(rc);

            OSG_ASSERT(rc == i);

#ifdef OSG_DBGPRINT_DYNFC
            fprintf(stderr, "added %d\n", rc);
#endif
        }
    }

    BitVector bvMask = 0x1 << _uiDescStartIdx;

    for(UInt32 i = _uiDescStartIdx; i <= getType().getNumFieldDescs(); ++i)
    {
#ifdef OSG_DBGPRINT_DYNFC
        fprintf(stderr, "[%d] : 0x%016"PRIx64" (0x%016"PRIx64")\n",
                i,
                bvMask,
                whichField);
#endif

        if(0x0000 != (bvMask & whichField))
        {
#ifdef OSG_DBGPRINT_DYNFC
            fprintf(stderr, "DO CONTENT SYNC\n");
#endif

            FieldDescriptionBase *pDesc = this->getType().getFieldDesc(i);

#ifdef OSG_DBGPRINT_DYNFC
            fprintf(stderr, "sync this [%d] %s | %s | %d \n", 
                    i,
                    this->getType().getFieldDesc(i)->getCName(),
                    this->getType().getFieldDesc(i)->getFieldType().getCName(),
                    this->getType().getFieldDesc(i)->getFieldType().getId());
            fprintf(stderr, "sync from [%d] %s | %s | %d \n", 
                    i,
                    pFrom->getType().getFieldDesc(i)->getCName(),
                    pFrom->getType().getFieldDesc(i)->getFieldType().getCName(),
                    pFrom->getType().getFieldDesc(i)->getFieldType().getId());
#endif

            OSG_ASSERT(pDesc != NULL);

            pDesc->sync(this ->_dynFieldsV[i - _uiDescStartIdx],
                        pFrom->_dynFieldsV[i - _uiDescStartIdx],
                        oOffsets,
                        syncMode | Field::MFCopySync,
                        uiSyncInfo);
        }

        bvMask <<= 1;
    }
}

template <class ParentT> inline
void DynFieldContainer<ParentT>::execSyncV(
          FieldContainer     &oFrom,
          ConstFieldMaskArg   whichField,
          AspectOffsetStore  &oOffsets,
          ConstFieldMaskArg   syncMode  ,
    const UInt32              uiSyncInfo)
{
    this->execSync(static_cast<Self *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

template <class ParentT> inline
void DynFieldContainer<ParentT>::addPointerValue(
    FieldContainer *pVal, 
    UInt32          uiFieldId)
{
#if 0
    MFFieldContainerPtr *pField = static_cast<MFFieldContainerPtr *>(
        _dynFieldsV[uiFieldId - _uiDescStartIdx]);
    
    OSG::addRef(pVal);

    pField->push_back(pVal);
#endif
}

template <class ParentT> inline
void DynFieldContainer<ParentT>::setPointerValue(
    FieldContainer *pVal, 
    UInt32          uiFieldId)
{
#if 0
    SFFieldContainerPtr *pField = static_cast<SFFieldContainerPtr *>(
        _dynFieldsV[uiFieldId - _uiDescStartIdx]);

    OSG::setRefd(pField->getValue(), pVal);
#endif
}

OSG_END_NAMESPACE
