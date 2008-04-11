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

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
FieldType const &ChildPointerSField<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerSField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::ChildPointerSField(
                       ParentT pParent,
                       UInt16  usParentFieldPos) : 
    Inherited(pParent, 
              usParentFieldPos)
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerSField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::ChildPointerSField(
                       const_value value,
                       ParentT     pParent,
                       UInt16      usParentFieldPos) :
    Inherited(value,
              pParent,
              usParentFieldPos)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerSField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::~ChildPointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerSField<ObjectTypeT,
                            RefCountPolicy,
                            NamespaceI    >::const_value
    ChildPointerSField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::getValue(void) const
{
    return static_cast<const_value>(this->ptrStoreGet());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerSField<ObjectTypeT,
                        RefCountPolicy,
                        NamespaceI    >::setValue(const_value value)
{
    this->ptrStoreSet(value);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerSField<ObjectTypeT,
                        RefCountPolicy,
                        NamespaceI    >::setValue(const Self &source)
{
    this->ptrStoreSet(source.ptrStoreGet());
}

template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void ChildPointerSField<ObjectTypeT,
                        RefCountPolicy,
                        NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
}

#ifdef OSG_MT_CPTR_ASPECT
template <class    ObjectTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void ChildPointerSField<ObjectTypeT,
                        RefCountPolicy,
                        NamespaceI    >::syncWith(Self &source)
{
    Inherited::syncWith(source);
}
#endif

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

OSG_END_NAMESPACE
