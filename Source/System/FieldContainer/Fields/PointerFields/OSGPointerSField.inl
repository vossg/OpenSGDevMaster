/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file PointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* PointerSField<ObjectTypeT,                                          */
/*               NamespaceI  >                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
FieldType const &PointerSField<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<ObjectTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerSField(void) : 
    Inherited()
{
    // nothing to do
}

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<ObjectTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerSField(Self const &source) :
     Inherited(source)
{
    // nothing to do
}

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<ObjectTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerSField(ValueType value) :
    Inherited(value)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<ObjectTypeT, 
              RefCountPolicy,
              NamespaceI    >::~PointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
typename PointerSField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_reference
    PointerSField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::getValue(void) const
{
    return reinterpret_cast<const_reference>(this->getRawStore());
}

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::setValue(ValueType value)
{
    this->ptrStoreSet(value);
}

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::setValue(Self const &source)
{
    this->ptrStoreSet(source.ptrStoreGet());
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::operator =(Self const &other)
{
    this->ptrStoreSet(other.ptrStoreGet());
}

OSG_END_NAMESPACE
