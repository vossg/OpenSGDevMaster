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

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::pushValueFromCString(
    const Char8        *str,
          HandledField *pField)
{
    pField->setValueFromCString(str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::pushValueToCString(
                          const HandledField *pField,
                                Char8        *str   )
{
    std::string tmpVal;

    pField->pushValueToString(tmpVal);

    osgStringCopy(tmpVal.c_str(), str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::pushValueFromString(
                          const std::string  &in,
                                HandledField *pField)
{
    pField->setValueFromCString(in.c_str());
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::pushValueToString(
                          const HandledField *pField,
                                std::string  &out   )
{
    pField->pushValueToString(out);
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::pushValueFromStream(
                          std::istream &str,
                          HandledField *pField )
{
    pField->pushValueFromStream(str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::pushValueToStream(
                          const HandledField *pField,
                                OutStream    &str    )
{
    pField->pushValueToStream(str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::pushSizeToStream(
                          const HandledField *pField,
                                OutStream    &str    )
{
    pField->pushSizeToStream(str);
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::SFieldFunctions::copyValues(
    const HandledField *pSrc,
          HandledField *pDst)
{
    pDst->setValue(*pSrc);
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::pushValueFromCString(
    const Char8        *str,
          HandledField *pField)
{
    pField->addValueFromCString(str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::pushValueToCString(
                          const HandledField *pField,
                                Char8        *str   )
{
    std::string tmpVal;

    pField->pushValuesToString(tmpVal);

    osgStringCopy(tmpVal.c_str(), str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::pushValueFromString(
                          const std::string  &in,
                                HandledField *pField)
{
    pField->addValueFromCString(in.c_str());
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::pushValueToString(
                          const HandledField *pField,
                                std::string  &out   )
{
    pField->pushValuesToString(out);
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::pushValueFromStream(
                          std::istream &str,
                          HandledField *pField )
{
    pField->pushValuesFromStream(str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::pushValueToStream(
                          const HandledField *pField,
                          OutStream          &str    )
{
    pField->pushValuesToStream(str);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::pushSizeToStream(
                          const HandledField *pField,
                          OutStream          &str    )
{
    pField->pushSizeToStream(str);
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::MFieldFunctions::copyValues(
    const HandledField *pSrc,
          HandledField *pDst  )
{
    pDst->setValues(*pSrc);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::cloneValues(
    const Field                     *,
          ConstFieldMaskArg          ,
    const StringVector              &,
          FieldContainerPtrConstArg  ) const
{
    FWARNING(("illegal clone values called for %s\n", this->getCName()));
    OSG_ASSERT(false);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::shareValues(
    const Field                     *,
          ConstFieldMaskArg          ,
          FieldContainerPtrConstArg  ) const
{
    FWARNING(("illegal share values called for %s\n", this->getCName()));
    OSG_ASSERT(false);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
FieldDescription<DescT, eFieldCard>::FieldDescription(
    const FieldType       &elementType,
    const Char8           *szName,
    std::string            documentation,
    const UInt32           uiFieldId,
    const BitVector        vFieldMask,
    const bool             bInternal,
    const UInt32           uiFieldFlags,
          FieldEditMethod  fEditMethod,
          FieldGetMethod   fGetMethod,
    const Char8           *defaultValue) :

    Inherited(elementType,
              szName,
              documentation,
              uiFieldId,
              vFieldMask,
              bInternal,
              uiFieldFlags,
              fEditMethod,
              fGetMethod,
              defaultValue)
{
}

template<class DescT, enum FieldCardinality eFieldCard> inline
FieldDescription<DescT, eFieldCard>::FieldDescription(
    const FieldType            &elementType,
    const Char8                *szName,
    std::string                 documentation,
    const UInt32                uiFieldId,
    const BitVector             vFieldMask,
          FieldIndexEditMethod  fIndexedEditMethod,
          FieldIndexGetMethod   fIndexedGetMethod,
    const bool                  bInternal,
    const UInt32                uiFieldFlags,
    const Char8                *defaultValue      ) :

    Inherited(elementType,
              szName,
              documentation,
              uiFieldId,
              vFieldMask,
              fIndexedEditMethod,
              fIndexedGetMethod,
              bInternal,
              uiFieldFlags,
              defaultValue)
{
}

template<class DescT, enum FieldCardinality eFieldCard> inline
FieldDescription<DescT, eFieldCard>::FieldDescription(
    const FieldDescription &source) :

    Inherited(source)
{
}

template<class DescT, enum FieldCardinality eFieldCard> inline
FieldDescription<DescT, eFieldCard>::~FieldDescription(void)
{
}

template<class DescT, enum FieldCardinality eFieldCard> inline
typename FieldDescription<DescT, eFieldCard>::HandledField *
    FieldDescription<DescT, eFieldCard>::dcast(Field *pField) const
{
    return static_cast<HandledField *>(pField);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
const typename FieldDescription<DescT, eFieldCard>::HandledField *
    FieldDescription<DescT, eFieldCard>::dcast_const(const Field *pField) const
{
    return static_cast<const HandledField *>(pField);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::pushValueFromCString(
    const Char8 *str,
          Field *pField) const
{
    HandledField *pConcreteField = dcast(pField);

    if(pConcreteField != NULL)
    {
        FieldFunctions::pushValueFromCString(str, pConcreteField);
    }
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::pushValueToCString(
    const Field *pField,
          Char8 *str) const
{
    const HandledField *pConcreteField = dcast_const(pField);

    if(pConcreteField != NULL)
    {
        FieldFunctions::pushValueToCString(pConcreteField, str);
    }
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::pushValueFromString(
    const std::string &in,
          Field       *pField) const
{
    HandledField *pConcreteField = dcast(pField);

    if(pConcreteField != NULL)
    {
        FieldFunctions::pushValueFromString(in, pConcreteField);
    }
}



template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::pushValueToString(
    const Field       *pField,
          std::string &out   ) const
{
    const HandledField *pConcreteField = dcast_const(pField);

    if(pConcreteField != NULL)
    {
        FieldFunctions::pushValueToString(pConcreteField, out);
    }
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::pushValueFromStream(
    std::istream &in,
    Field        *pField) const
{
    HandledField *pConcreteField = dcast(pField);

    if(pConcreteField != NULL)
    {
        FieldFunctions::pushValueFromStream(in, pConcreteField);
    }
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::pushValueToStream(
    const Field        *pField,
          OutStream    &out   ) const
{
    const HandledField *pConcreteField = dcast_const(pField);

    if(pConcreteField != NULL)
    {
        FieldFunctions::pushValueToStream(pConcreteField, out);
    }
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::pushSizeToStream(
    const Field        *pField,
          OutStream    &out   ) const
{
    const HandledField *pConcreteField = dcast_const(pField);

    if(pConcreteField != NULL)
    {
        FieldFunctions::pushSizeToStream(pConcreteField, out);
    }
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::copyValues(
    const Field *pSrc,
          Field *pDst) const
{
    const HandledField *pSrcField = dcast_const(pSrc);
          HandledField *pDstField = dcast      (pDst);

    if(pSrcField != NULL && pDstField != NULL)
    {
        FieldFunctions::copyValues(pSrcField, pDstField);
    }
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::cloneValuesV(
    const Field                     *pSrc,
          ConstFieldMaskArg          whichField,
    const StringVector              &share,
          FieldContainerPtrConstArg  pDst) const
{
    cloneValues(pSrc, whichField, share, pDst);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::shareValuesV(
    const Field                     *pSrc,
          ConstFieldMaskArg          whichField,
          FieldContainerPtrConstArg  pDst      ) const
{
    shareValues(pSrc, whichField, pDst);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
bool FieldDescription<DescT, eFieldCard>::equal(const Field *lhs,
                                                const Field *rhs) const
{
    const HandledField *lhsField = dcast_const(lhs);
    const HandledField *rhsField = dcast_const(rhs);

    return (*lhsField) == (*rhsField);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
Field *FieldDescription<DescT, eFieldCard>::createField(void) const
{
    return new HandledField();
}


template<class DescT, enum FieldCardinality eFieldCard> inline
FieldDescriptionBase *FieldDescription<DescT, eFieldCard>::clone(void) const
{
    return new Self(*this);
}


OSG_END_NAMESPACE

#define OSGFIELDTRAITS_INLINE_CVSID "@(#)$Id$"

