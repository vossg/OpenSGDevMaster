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
/*! \file OSGChildPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ChildPointerSField<ObjectTypeT,                                         */
/*                    NamespaceI  >                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI> inline 
FieldType const &ChildPointerSField<ObjectTypeT,
                                    NamespaceI >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI> inline
ChildPointerSField<ObjectTypeT,
                   NamespaceI >::ChildPointerSField(void) : 
    Inherited()
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI> inline
ChildPointerSField<ObjectTypeT,
                   NamespaceI >::ChildPointerSField(Self const &source) :
    Inherited(source)
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI> inline
ChildPointerSField<ObjectTypeT,
                   NamespaceI >::ChildPointerSField(ValueType value) :
    Inherited(value)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI> inline
ChildPointerSField<ObjectTypeT,
                   NamespaceI >::~ChildPointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class ObjectTypeT, Int32 NamespaceI> inline 
typename ChildPointerSField<ObjectTypeT,
                            NamespaceI >::const_reference
    ChildPointerSField<ObjectTypeT,
                       NamespaceI >::getValue(void) const
{
    return reinterpret_cast<const_reference>(this->getRawStore());
}

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ChildPointerSField<ObjectTypeT,
                        NamespaceI >::setValue(ValueType value)
{
    this->ptrStoreSet(value);
}

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ChildPointerSField<ObjectTypeT,
                        NamespaceI >::setValue(Self const &source)
{
    this->ptrStoreSet(source.ptrStoreGet());
}

/*-------------------------------------------------------------------------*/
/* Comparison                                                              */

// template <class ObjectTypeT, Int32 NamespaceI>
// inline bool
//     ChildPointerSField<ObjectTypeT,
//                        NamespaceI  >::operator==(Self const &other)
// {   
// }

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ChildPointerSField<ObjectTypeT,
                        NamespaceI >::operator =(Self const &other)
{   
    this->ptrStoreSet(other.ptrStoreGet());
}

OSG_END_NAMESPACE
