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

OSG_BEGIN_NAMESPACE


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
typename TypedGeoIntegralProperty<GeoPropertyDesc>::ObjCPtr 
    TypedGeoIntegralProperty<GeoPropertyDesc>::createAspectCopy(
        const FieldContainer *pRefAspect) const
{
    ObjCPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const Self *>(pRefAspect),
                  dynamic_cast<const Self *>(this)); 

    return returnValue; 
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

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    typedef typename Inherited::MFParentsType PFieldT;

    const Self *pThis = this;

    typename PFieldT::const_iterator parentsIt  = pThis->_mfParents.begin();
    typename PFieldT::const_iterator parentsEnd = pThis->_mfParents.end  ();

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
                TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
                ChangedOrigin::Child,
                0);

        ++parentsIt;
    }

    Inherited::changed(whichField, origin, details);
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

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the GeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType * 
    TypedGeoIntegralProperty<GeoPropertyDesc>::editFieldPtr(void)
{
    editMField(GeoPropDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the GeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class GeoPropertyDesc> inline 
const typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType * 
    TypedGeoIntegralProperty<GeoPropertyDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the GeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType & 
    TypedGeoIntegralProperty<GeoPropertyDesc>::editField(void)
{
    editMField(GeoPropDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the GeoIntegralProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class GeoPropertyDesc> inline 
const typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType & 
    TypedGeoIntegralProperty<GeoPropertyDesc>::getField(void) const
{
    return _field;
}

#ifdef OSG_1_GET_COMPAT
/*! \copydoc OSG::TypedGeoIntegralProperty<GeoPropertyDesc>::editFieldPtr
 */
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType *
    TypedGeoIntegralProperty<GeoPropertyDesc>::getFieldPtr (void)
{
    return this->editFieldPtr();
}

/*! \copydoc OSG::TypedGeoIntegralProperty<GeoPropertyDesc>::editField
 */
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType &
    TypedGeoIntegralProperty<GeoPropertyDesc>::getField(void)
{
    return this->editField();
}
#endif

/*! Returns a const reference to the given element of the stored field.
    There is no range check for \a index, it must be in [0, size()[.

    \param[in] index Index of the element to access.
    \return Reference to the given element.
 */
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::const_reference
    TypedGeoIntegralProperty<GeoPropertyDesc>::operator [](UInt32 index) const
{
    return _field[index];
}

/*! Returns a reference to the given element of the stored field.
    There is no range check for \a index, it must be in [0, size()[.

    \param[in] index Index of the element to access.
    \return Reference to the given element.
 */
template <class GeoPropertyDesc> inline 
typename TypedGeoIntegralProperty<GeoPropertyDesc>::reference 
    TypedGeoIntegralProperty<GeoPropertyDesc>::operator [](UInt32 index)
{
    editMField(GeoPropDataFieldMask, _field);

    return _field[index];
}

/*! Returns a copy of this property that holds the same data.

    \return A copy of this property.
 */
template <class GeoPropertyDesc> inline
GeoPropertyTransitPtr
TypedGeoIntegralProperty<GeoPropertyDesc>::clone(void)
{
    ObjTransitPtr obj = Self::create();

    editMField(GeoPropDataFieldMask, obj->_field);
    
    obj->_field.setValues(_field);

    return GeoPropertyTransitPtr(obj);
}

/*! \copydoc OSG::GeoIntegralProperty::getFormat
 */
template <class GeoPropertyDesc> inline 
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getFormat(void) const
{
    return GeoPropertyDesc::getFormat();
}

/*! \copydoc OSG::GeoIntegralProperty::getFormatSize
 */
template <class GeoPropertyDesc> inline 
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getFormatSize(void) const
{
    return GeoPropertyDesc::getFormatSize();
}

/*! \copydoc OSG::GeoIntegralProperty::getStride
 */
template <class GeoPropertyDesc> inline
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getStride(void) const
{
    return GeoPropertyDesc::getStride();
}

/*! \copydoc OSG::GeoIntegralProperty::getDimension
 */
template <class GeoPropertyDesc> inline
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::getDimension(void) const
{
    return GeoPropertyDesc::getDimension();
}

/*! \copydoc OSG::GeoIntegralProperty::size
 */
template <class GeoPropertyDesc> inline
UInt32 TypedGeoIntegralProperty<GeoPropertyDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::GeoIntegralProperty::getData
 */
template <class GeoPropertyDesc> inline
const UInt8 *TypedGeoIntegralProperty<GeoPropertyDesc>::getData(void) const
{
    return reinterpret_cast<const UInt8 *>(&(_field[0]));
}

/*! Returns a const reference to the stored field.

    This allows direct access to the data, which is faster than the access via
    the generic Interface that the GeoVectorProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class GeoPropertyDesc>
inline
const typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredFieldType &
TypedGeoIntegralProperty<GeoPropertyDesc>::operator->(void) const
{
    return _field;
}

/*! Returns the value stored at index \a index.
    There is no range check for \a index, it must be in [0, size()[.

    \param[in] index Index of the element to access.
    \return Value of the given element.
 */
template <class GeoPropertyDesc> inline
typename TypedGeoIntegralProperty<GeoPropertyDesc>::StoredType
    TypedGeoIntegralProperty<GeoPropertyDesc>::getValue(const UInt32 index) const
{
    return _field[index];
}

/*! Returns the value stored at index \a index in \a val.
    There is no range check for \a index, it must be in [0, size()[.

    \param[out] val Value at the given index.
    \param[in] index Index of the element to access.
 */
template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::getValue(
          StoredType &val,
    const UInt32      index) const
{
    val = _field[index];
}

/*! Sets the value stored at index \a index to \a value.
    There is no range check for \a index, it must be in [0, size()[.

    \note To change many entries of a property it is more efficient to obtain
    a pointer or reference to the stored field and modify that directly.

    \param[in] value Value to set the element at the given index to.
    \param[in] index Index of the element to set.
 */
template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::setValue(const StoredType &value,
                                                         const UInt32      index)
{
    editMField(GeoPropDataFieldMask, _field);

    _field[index] = value;
}

/*! Appends a value to this property.

    \note To change many entries of a property it is more efficient to obtain
    a pointer or reference to the stored field and modify that directly.

    \param[in] value Value to append to this property.
 */
template <class GeoPropertyDesc> inline 
void TypedGeoIntegralProperty<GeoPropertyDesc>::addValue(const StoredType &value)
{
    editMField(GeoPropDataFieldMask, _field);

    _field.push_back(value);
}

/*! Removes all values from this property.
 */
template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::clear(void)
{
    editMField(GeoPropDataFieldMask, _field);

    _field.clear();
}

/*! Appends a value to this property.

    \note To change many entries of a property it is more efficient to obtain
    a pointer or reference to the stored field and modify that directly.

    \param[in] value Value to append to this property.
 */
template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::push_back(
    const StoredType &value)
{
    addValue(value);
}

/*! Changes the size of this property to \a newsize. If the new size is smaller
    than the current size, excessive elements are deleted; if the new is greater
    than the current size, new elemnts are default constructed.

    \param[in] newsize New size for this property.
 */
template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::resize( size_t newsize )
{
    editMField(GeoPropDataFieldMask, _field);

    _field.resize(newsize);
}

/*! Returns the value at index \a index in \a val after converting it to the
    most generic type OSG::GeoIntegralProperty::MaxTypeT.
    There is no range check for \a index, it must be in [0, size()[.

    \param[out] val Value at the given index.
    \param[in] index Index of the element to access.
 */
template <class GeoPropertyDesc>
void
TypedGeoIntegralProperty<GeoPropertyDesc>::getGenericValue(
          MaxTypeT &val, const UInt32 index) const
{
    val = static_cast<MaxTypeT>(_field[index]);
}

/*! Sets the value at index \a index to \a val.
    There is no range check for \a index, it must be in [0, size()[.

    \param[in] val Value to set the element at the given index to.
    \param[in] index Index of the element to set.
*/
template <class GeoPropertyDesc>
void
TypedGeoIntegralProperty<GeoPropertyDesc>::setGenericValue(
    const MaxTypeT &val, const UInt32 index)
{
    editMField(GeoPropDataFieldMask, _field);

    _field[index] = static_cast<StoredType>(val);
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

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::exitMethod(InitPhase ePhase)
{
    GeoPropertyDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::onCreate(
    const Self *source)
{
    Inherited::onCreate(source);
    
    editSField(UsageFieldMask);
    
    _sfUsage.setValue(GeoPropertyDesc::getDefaultUsage());

    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&Self::handleGL, 
                        GeoPropertyMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &GeoProperty::handleDestroyGL));
}

template <class GeoPropertyDesc> inline
void TypedGeoIntegralProperty<GeoPropertyDesc>::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
    {
        Window::destroyGLObject(getGLId(), 1);
    }

    Inherited::onDestroy(uiContainerId);
}

template <class GeoPropertyDesc> inline
EditFieldHandlePtr TypedGeoIntegralProperty<GeoPropertyDesc>::editHandleField(
    void)
{
    StoredEditHandlePtr returnValue(
        new  StoredEditHandle(
             &_field, 
             this->getType().getFieldDesc(GeoPropDataFieldId),
             this));

    editMField(GeoPropDataFieldMask, _field);

    return returnValue;
}

template <class GeoPropertyDesc> inline
GetFieldHandlePtr TypedGeoIntegralProperty<GeoPropertyDesc>::getHandleField(
    void) const
{
    StoredGetHandlePtr returnValue(
        new  StoredGetHandle(
             &_field, 
             this->getType().getFieldDesc(GeoPropDataFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

OSG_END_NAMESPACE
