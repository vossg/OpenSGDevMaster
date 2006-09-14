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

template <class ValueT, class ParentT, Int32 iNamespace>
template<class To> inline
To &MFieldAdaptor<ValueT, ParentT, iNamespace>::dcast(void)
{
    return reinterpret_cast<To &>(Self::_values); 
}

template <class ValueT, class ParentT, Int32 iNamespace>
template<class To> inline
const To &MFieldAdaptor<ValueT, ParentT, iNamespace>::dcast(void) const 
{
    return reinterpret_cast<const To &>(Self::_values); 
}

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

template<class ValueT, class ParentT, Int32 iNamespace> inline
MFieldAdaptor<ValueT, ParentT, iNamespace>::MFieldAdaptor(void) :
    Inherited()
{
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
MFieldAdaptor<ValueT, ParentT, iNamespace>::MFieldAdaptor(
    const MFieldAdaptor &source) :

    Inherited(source)
{
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
MFieldAdaptor<ValueT, ParentT, iNamespace>::~MFieldAdaptor(void)
{
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::reference 
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::operator [](UInt32 index)
{

    return (this->template dcast<typename Self::StorageType>())[index];
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_reference 
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::operator [](UInt32 index) const
{
    return (this->template dcast<typename Self::StorageType>())[index];
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::begin(void)
{
    return (this->template dcast<typename Self::StorageType>()).begin();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::end(void)
{
    return (this->template dcast<typename Self::StorageType>()).end();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::reverse_iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::rbegin(void)
{
    return (this->template dcast<typename Self::StorageType>()).rbegin();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::reverse_iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::rend(void)
{
    return (this->template dcast<typename Self::StorageType>()).rend();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::begin(void) const
{
    return (this->template dcast<typename Self::StorageType>()).begin();
    }

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::end(void) const
{
    return (this->template dcast<typename Self::StorageType>()).end();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_reverse_iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::rbegin(void) const
{
    return (this->template dcast<typename Self::StorageType>()).rbegin();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_reverse_iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::rend(void) const
{
    return (this->template dcast<typename Self::StorageType>()).rend();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::reference
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::front(void)
{
    return (this->template dcast<typename Self::StorageType>()).front();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_reference
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::front(void) const
{
    return (this->template dcast<typename Self::StorageType>()).front();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::reference
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::back(void)
{
    return (this->template dcast<typename Self::StorageType>()).back();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_reference
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::back(void) const
{
    return (this->template dcast<typename Self::StorageType>()).back();
}


template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::insert(iterator     pos, 
                                      ArgumentType value)
{
    return (this->template dcast<typename Self::StorageType>()).insert(pos, 
                                                                       value);
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::erase(iterator pos)
{
    return (this->template dcast<typename Self::StorageType>()).erase(pos);
}
    

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::find(ArgumentType value)
{
    return std::find(Self::begin(), Self::end(), value);
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::const_iterator
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::find(ArgumentType value) const
{
    return std::find(Self::begin(), Self::end(), value);
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename MFieldAdaptor<ValueT, ParentT, iNamespace>::StorageType &
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::getValues(void)
{
    return (this->template dcast<typename Self::StorageType>());
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
const typename MFieldAdaptor<ValueT, ParentT, iNamespace>::StorageType &
    MFieldAdaptor<ValueT, 
                  ParentT, 
                  iNamespace>::getValues(void) const
{
    return (this->template dcast<typename Self::StorageType>());
}

OSG_END_NAMESPACE

#define OSGMFIELDADAPTOR_INLINE_CVSID "@(#)$Id$"

