/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#if !defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) && \
    !defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGTypedGeoIntegralPropertyFuncs.ins"

#endif

OSG_BEGIN_NAMESPACE

OSG_FIELD_CONTAINER_TMPL_DEF(TypedGeoIntegralProperty,
                             GeoPropertyDesc)


template <class GeoPropertyDesc> inline 
TypedGeoIntegralProperty<GeoPropertyDesc>::TypedGeoIntegralProperty(void) :
     GeoIntegralProperty(),
    _field         ()
{
}

template <class GeoPropertyDesc> inline 
TypedGeoIntegralProperty<GeoPropertyDesc>::TypedGeoIntegralProperty(
    const TypedGeoIntegralProperty &source ) :

     GeoIntegralProperty(source),
    _field         (source._field)
{
}

template <class GeoPropertyDesc> inline 
TypedGeoIntegralProperty<GeoPropertyDesc>::~TypedGeoIntegralProperty(void)
{
}

#ifdef OSG_MT_CPTR_ASPECT
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::ObjPtr 
    TypedGeoIntegralProperty<GeoPropertyDesc>::createAspectCopy(void) const
{
    ObjPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const Self *>(this)); 

    return returnValue; 
}
#endif

#ifdef OSG_MT_FIELDCONTAINERPTR
template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::execSync(      
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo,
          UInt32             uiCopyOffset)
{
    Inherited::execSync(pFrom, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.syncWith(pFrom->_field, syncMode, uiSyncInfo, uiCopyOffset);
    }
}

template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::execSyncV(      
          FieldContainer    &oFrom,
          ConstFieldMaskArg  whichField,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo,
          UInt32             uiCopyOffset)
{
    this->execSync(static_cast<Self *>(&oFrom),
                   whichField,
                   syncMode,
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::execSync(
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.syncWith(pFrom->_field, syncMode, uiSyncInfo, oOffsets);
    }
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::execSyncV(     
          FieldContainer    &oFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<Self *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::execBeginEdit (
    ConstFieldMaskArg whichField, 
    UInt32            uiAspect,
    UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.beginEdit(uiAspect, uiContainerSize);
    }
}

template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::execBeginEditV(
    ConstFieldMaskArg whichField, 
    UInt32            uiAspect,
    UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32    origin    )
{
    typedef typename Inherited::ParentField PFieldT;

    typename PFieldT::iterator parentsIt  = Self::_mfParents.begin();
    typename PFieldT::iterator parentsEnd = Self::_mfParents.end  ();

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
                TypeTraits<BitVector>::One << parentsIt->getParentFieldPos(),
                ChangedOrigin::Child);
        ++parentsIt;
    }

    Inherited::changed(whichField, origin);
}

template <class GeoPropertyDesc> inline 
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = GeoIntegralProperty::getBinSize(whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    GeoIntegralProperty::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    GeoIntegralProperty::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractTypedGeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.
*/

template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType * 
    TypedGeoIntegralProperty<GeoPropertyDesc>::editFieldPtr(void)
{
    editMField(GeoPropDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractTypedGeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.
*/

template <class GeoPropertyDesc> inline 
const typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType * 
    TypedGeoIntegralProperty<GeoPropertyDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractTypedGeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types. 
*/
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType & 
    TypedGeoIntegralProperty<GeoPropertyDesc>::editField(void)
{
    editMField(GeoPropDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractTypedGeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types. 
*/
template <class GeoPropertyDesc> inline 
const typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType & 
    TypedGeoIntegralProperty<GeoPropertyDesc>::getField(void) const
{
    return _field;
}

#ifdef OSG_1_COMPAT
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType *
    TypedGeoIntegralProperty<GeoPropertyDesc>::getFieldPtr (void)
{
    return this->editFieldPtr();
}

template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType &
    TypedGeoIntegralProperty<GeoPropertyDesc>::getField(void)
{
    return this->editField();
}
#endif


template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::const_reference
    TypedGeoIntegralProperty<GeoPropertyDesc>::operator [](UInt32 index) const
{
    return _field[index];
}

template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::reference 
    TypedGeoIntegralProperty<GeoPropertyDesc>::operator [](UInt32 index)
{
    return _field[index];
}


template <class GeoPropertyDesc> inline
GeoIntegralPropertyPtr
TypedGeoIntegralProperty<GeoPropertyDesc>::clone(void)
{
    ObjPtr obj = TypedGeoIntegralProperty<GeoPropertyDesc>::create();

    editMField(GeoPropDataFieldMask, obj->_field);
    
    obj->_field.setValues(_field);

    return obj;
}


/*! Returns the format of this property. 
*/

template <class GeoPropertyDesc> inline 
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getFormat(void) const
{
    return GeoPropertyDesc::getFormat();
}


template <class GeoPropertyDesc> inline 
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getFormatSize(void) const
{
    return GeoPropertyDesc::getFormatSize();
}


template <class GeoPropertyDesc> inline
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getStride(void) const
{
    return GeoPropertyDesc::getStride();
}


template <class GeoPropertyDesc> inline
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getDimension(void) const
{
    return GeoPropertyDesc::getDimension();
}


template <class GeoPropertyDesc> inline
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::size(void) const
{
    return _field.size();
}


template <class GeoPropertyDesc> inline
const UInt8 *TypedGeoIntegralProperty<GeoPropertyDesc>::getData(void) const
{
    return (const UInt8 *) &(_field[0]);
}


template <class GeoPropertyDesc> inline
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredType
    TypedGeoIntegralProperty<GeoPropertyDesc>::getValue(const UInt32 index) const
{
    return _field[index];
}


template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::getValue(
          StoredType &val,
    const UInt32             index) const
{
    val = _field[index];
}


template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::setValue(const StoredType &value,
                                            const UInt32             index)
{
    editMField(GeoPropDataFieldMask, _field);

    _field[index] = value;
}

template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::addValue(const StoredType & value)
{
    editMField(GeoPropDataFieldMask, _field);

    _field.push_back(value);
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::clear( void )
{
    editMField(GeoPropDataFieldMask, _field);

    _field.clear();
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::push_back(
    const StoredType &value)
{
    addValue(value);
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::resize( size_t newsize )
{
    editMField(GeoPropDataFieldMask, _field);

    _field.resize(newsize);
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    GeoIntegralProperty::dump(uiIndent, bvFlags);
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::initMethod(InitPhase ePhase)
{
    GeoPropertyDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

OSG_END_NAMESPACE
