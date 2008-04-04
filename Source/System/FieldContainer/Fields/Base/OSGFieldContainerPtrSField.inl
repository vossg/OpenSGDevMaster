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
To &FieldContainerPtrSField<ValueT, RefCountPolicy, iNamespace>::dcast(void)
{
    return reinterpret_cast<To &>(Self::_fieldValue); 
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> 
template<class To> inline
const To FieldContainerPtrSField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::dcast(void) const 
{
    return reinterpret_cast<const To>(Self::_fieldValue); 
}

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrSField<ValueT, 
                        RefCountPolicy, 
                        iNamespace    >::FieldContainerPtrSField(void) :
    Inherited()
{
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrSField<ValueT, 
                        RefCountPolicy, 
                        iNamespace    >::FieldContainerPtrSField(
    const FieldContainerPtrSField &obj) :

    Inherited()
{
    RefCountPolicy::setRefd(_fieldValue, obj._fieldValue);   
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrSField<ValueT, 
                        RefCountPolicy, 
                        iNamespace    >::FieldContainerPtrSField(
    ArgumentType value) : 

    Inherited()
{
    RefCountPolicy::setRefd(_fieldValue, value);
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrSField<ValueT, 
                        RefCountPolicy, 
                        iNamespace    >::~FieldContainerPtrSField(void)
{
    RefCountPolicy::subRef(_fieldValue);
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrSField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::const_reference 
    FieldContainerPtrSField<ValueT, 
                            RefCountPolicy, 
                            iNamespace    >::getValue(void) const
{
    return RefCountPolicy::validate(
        this->template dcast<typename Self::StoredType>());
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrSField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::setValue(ArgumentType value)
{
//    Inherited::setValue(value);
    RefCountPolicy::setRefd(_fieldValue, value);
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrSField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::setValue(const Self &obj)
{
//    Inherited::setValue(obj);
    RefCountPolicy::setRefd(_fieldValue, obj._fieldValue);
}


template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrSField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::copyFromBin(
    BinaryDataHandler &pMem)
{
    FieldContainerPtr tmpVal;

    SFieldTraits::copyFromBin(pMem, 
                              tmpVal);

    if(_fieldValue != NullFC)
    {
        Thread::getCurrentChangeList()->addSyncAddRef<
            RefCountPolicy>(_fieldValue);
    }

    RefCountPolicy::addRef(tmpVal);

    _fieldValue = tmpVal;
}

#ifdef OSG_MT_CPTR_ASPECT
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrSField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::syncWith(Self &source)
{
    if(_fieldValue != NullFC)
    {
        Thread::getCurrentChangeList()->addSyncAddRef<
            RefCountPolicy>(_fieldValue);
    }

    FieldContainerPtr tmpVal = convertToCurrentAspect(source.getValue());

    RefCountPolicy::addRef(tmpVal);

    _fieldValue = tmpVal;
}
#endif

OSG_END_NAMESPACE
