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
/* ChildPointerSField<PtrTypeT,                                         */
/*                    NamespaceI  >                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
FieldType const &ChildPointerSField<PtrTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::ChildPointerSField(
                       ParentT pParent,
                       UInt16  usChildFieldId,
                       UInt16  usParentFieldId) : 
    Inherited(pParent, 
              usChildFieldId,
              usParentFieldId)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::ChildPointerSField(
                       const_value value,
                       ParentT     pParent,
                       UInt16      usChildFieldId,
                       UInt16      usParentFieldId) :
    Inherited(value,
              pParent,
              usChildFieldId,
              usParentFieldId)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::~ChildPointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerSField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::const_value
    ChildPointerSField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::getValue(void) const
{
    return static_cast<const_value>(this->ptrStoreGet());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerSField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::setValue(const_value value)
{
    this->ptrStoreSet(value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerSField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::setValue(const Self &source)
{
    this->ptrStoreSet(source.ptrStoreGet());
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void ChildPointerSField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
}

#ifdef OSG_MT_CPTR_ASPECT
template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void ChildPointerSField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::syncWith(Self &source)
{
    Inherited::syncWith(source);
}
#endif

/*-------------------------------------------------------------------------*/
/* Comparison                                                              */

// template <class PtrTypeT, Int32 NamespaceI>
// inline bool
//     ChildPointerSField<ObjectTypeT,
//                        NamespaceI  >::operator==(Self const &other)
// {   
// }

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

OSG_END_NAMESPACE
