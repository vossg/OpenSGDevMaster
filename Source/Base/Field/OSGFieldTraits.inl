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
FieldDescription<DescT, eFieldCard>::FieldDescription(
    const FieldType       &elementType,
    const Char8           *szName,
          std::string      documentation,
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
    const bool                  bInternal,
    const UInt32                uiFieldFlags,
          FieldIndexEditMethod  fIndexedEditMethod,
          FieldIndexGetMethod   fIndexedGetMethod,
    const Char8                *defaultValue      ) :

    Inherited(elementType,
              szName,
              documentation,
              uiFieldId,
              vFieldMask,
              bInternal,
              uiFieldFlags,
              fIndexedEditMethod,
              fIndexedGetMethod,
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
const typename FieldDescription<DescT, eFieldCard>::HandledField *
    FieldDescription<DescT, eFieldCard>::dcast_const(const Field *pField) const
{
    return static_cast<const HandledField *>(pField);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
typename FieldDescription<DescT, eFieldCard>::HandledField *
    FieldDescription<DescT, eFieldCard>::dcast(Field *pField) const
{
    return static_cast<HandledField *>(pField);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
Field *FieldDescription<DescT, eFieldCard>::createField(void) const
{
    return new HandledField();
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT, eFieldCard>::destroyField(Field *pField) const
{
    HandledField *pDelField = dcast(pField);

    delete pDelField;
}

template<class DescT, enum FieldCardinality eFieldCard> inline
FieldDescriptionBase *FieldDescription<DescT, eFieldCard>::clone(void) const
{
    return new Self(*this);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
GetFieldHandlePtr 
    FieldDescription<DescT, eFieldCard>::createGetHandler(const Field *pField)
{
    const HandledField *pTypedField = dcast_const(pField);

    GetHandlePtr returnValue(new GetHandle(pTypedField, this));

    return returnValue;
}

template<class DescT, enum FieldCardinality eFieldCard> inline
EditFieldHandlePtr 
    FieldDescription<DescT, eFieldCard>::createEditHandler(Field *pField)
{
    HandledField *pTypedField = dcast(pField);

    EditHandlePtr returnValue(new EditHandle(pTypedField, this));

    return returnValue;
}


template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::beginEdit(
                          HandledField       *,
                          UInt32              ,
                          AspectOffsetStore  &)
{
}

template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::beginEdit(
                          HandledField       *pField,
                          UInt32              uiAspect,
                          AspectOffsetStore  &oOffsets)
{
    pField->beginEdit(uiAspect, oOffsets);
}


template<class DescT, enum FieldCardinality eFieldCard> inline
bool FieldDescription<DescT,
                      eFieldCard>::SFieldFunctions::isShared(
                          HandledField *)
{
    return false;
}

template<class DescT, enum FieldCardinality eFieldCard> inline
bool FieldDescription<DescT,
                      eFieldCard>::MFieldFunctions::isShared(
                          HandledField *pField)
{
    return pField->isShared();
}



template<class DescT, enum FieldCardinality eFieldCard> inline
void FieldDescription<DescT,
                      eFieldCard>::beginEdit(Field              *pField,
                                             UInt32              uiAspect,
                                             AspectOffsetStore  &oOffsets)
{
    HandledField *pTypedField = dcast(pField);
    
    FieldFunctions::beginEdit(pTypedField, uiAspect, oOffsets);
}

template<class DescT, enum FieldCardinality eFieldCard> inline
bool FieldDescription<DescT,
                      eFieldCard>::isShared(Field *pField)
{
    HandledField *pTypedField = dcast(pField);
    
    return FieldFunctions::isShared(pTypedField);
}

OSG_END_NAMESPACE

