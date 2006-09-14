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
To &SFieldAdaptor<ValueT, ParentT, iNamespace>::dcast(void)
{
    return reinterpret_cast<To &>(Self::_fieldValue); 
}

template <class ValueT, class ParentT, Int32 iNamespace>
template<class To> inline
const To &SFieldAdaptor<ValueT, ParentT, iNamespace>::dcast(void) const 
{
    return reinterpret_cast<const To &>(Self::_fieldValue); 
}

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

template<class ValueT, class ParentT, Int32 iNamespace> inline
SFieldAdaptor<ValueT, ParentT, iNamespace>::SFieldAdaptor(void) :
    Inherited()
{
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
SFieldAdaptor<ValueT, ParentT, iNamespace>::SFieldAdaptor(
    const SFieldAdaptor &source) :

    Inherited(source)
{
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
SFieldAdaptor<ValueT, ParentT, iNamespace>::SFieldAdaptor(ArgumentType value) :
    Inherited(value)
{
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
SFieldAdaptor<ValueT, ParentT, iNamespace>::~SFieldAdaptor(void)
{
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename SFieldAdaptor<ValueT, ParentT, iNamespace>::reference 
    SFieldAdaptor<ValueT, ParentT, iNamespace>::getValue(void)
{
    return this->template dcast<typename Self::StoredType>();
}

template<class ValueT, class ParentT, Int32 iNamespace> inline
typename SFieldAdaptor<ValueT, ParentT, iNamespace>::const_reference 
    SFieldAdaptor<ValueT, ParentT, iNamespace>::getValue(void) const
{
    return this->template dcast<typename Self::StoredType>();
}


OSG_END_NAMESPACE

#define OSGSFIELDADAPTOR_INLINE_CVSID "@(#)$Id$"

