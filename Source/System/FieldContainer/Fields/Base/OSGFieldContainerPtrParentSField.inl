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

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> 
template<class To> inline
To &FieldContainerPtrParentSField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace>::dcast(void)
{
    return reinterpret_cast<To &>(Self::_fieldValue); 
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> 
template<class To> inline
const To &FieldContainerPtrParentSField<ValueT, 
                                        RefCountPolicy, 
                                        iNamespace    >::dcast(void) const 
{
    return reinterpret_cast<const To &>(Self::_fieldValue); 
}

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrParentSField<
    ValueT, 
    RefCountPolicy, 
    iNamespace    >::FieldContainerPtrParentSField(void) :

     Inherited       (      ),
    _uiParentFieldPos(0xFFFF)
{
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrParentSField<ValueT, 
                              RefCountPolicy, 
                              iNamespace    >::FieldContainerPtrParentSField(
    const FieldContainerPtrParentSField &obj) :

    Inherited()
{
    RefCountPolicy::setRefd(_fieldValue, obj._fieldValue); 

    _uiParentFieldPos = obj._uiParentFieldPos;
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrParentSField<ValueT, 
                              RefCountPolicy, 
                              iNamespace    >::FieldContainerPtrParentSField(
    ArgumentType value,
    UInt16       uiPos) : 

    Inherited()
{
    RefCountPolicy::setRefd(_fieldValue, value);
    _uiParentFieldPos = uiPos;
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrParentSField<ValueT, 
                              RefCountPolicy, 
                              iNamespace    >::~FieldContainerPtrParentSField(
                                  void)
{
    RefCountPolicy::subRef(_fieldValue);
}

#if 0
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrSField<ValueT, RefCountPolicy, iNamespace>::reference 
    FieldContainerPtrSField<ValueT, RefCountPolicy, iNamespace>::getValue(void)
{
    return this->template dcast<typename Self::StoredType>();
}
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrParentSField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::const_reference 
    FieldContainerPtrParentSField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::getValue(void) const
{
    return this->template dcast<typename Self::StoredType>();
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentSField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::setValue(
                                       ArgumentType value,
                                       UInt16       uiPos)
{
//    Inherited::setValue(value);
    RefCountPolicy::setRefd(_fieldValue, value);

    _uiParentFieldPos = uiPos;
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentSField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::setValue(const Self &obj)
{
//    Inherited::setValue(obj);
    RefCountPolicy::setRefd(_fieldValue, obj._fieldValue);
    _uiParentFieldPos = obj._uiParentFieldPos;
}


template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
UInt32 FieldContainerPtrParentSField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::getBinSize(void) const
{
    return (PtrSFieldTraits::getBinSize(_fieldValue      ) +
            PosSFieldTraits::getBinSize(_uiParentFieldPos));
        
}
    
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void   FieldContainerPtrParentSField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::copyToBin(
                                       BinaryDataHandler &pMem) const
{
    PtrSFieldTraits::copyToBin( pMem, 
                               _fieldValue);

    PosSFieldTraits::copyToBin( pMem, 
                               _uiParentFieldPos);    
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentSField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::copyFromBin(
    BinaryDataHandler &pMem)
{
    PtrSFieldTraits::copyFromBin( pMem, 
                                 _fieldValue );

    PosSFieldTraits::copyFromBin( pMem, 
                                 _uiParentFieldPos);
}

#ifdef OSG_MT_CPTR_ASPECT
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentSField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::syncWith(Self &source)
{
    Inherited::syncWith(source);
}
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
bool FieldContainerPtrParentSField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::operator ==(
                                       const Self &source) const
{
    return (_fieldValue       == source._fieldValue      && 
            _uiParentFieldPos == source._uiParentFieldPos  );
}

OSG_END_NAMESPACE
