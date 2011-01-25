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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* PointerSField<PtrTypeT,                                          */
/*               NamespaceI  >                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<PtrTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerSField(void) : 
    Inherited()
{
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<PtrTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerSField(const Self &source) :
     Inherited(source)
{
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<PtrTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerSField(const_value value) :
    Inherited(value)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline
PointerSField<PtrTypeT, 
              RefCountPolicy,
              NamespaceI    >::~PointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
typename PointerSField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_value
    PointerSField<PtrTypeT,
                  RefCountPolicy,
                  NamespaceI    >::getValue(void) const
{
    return static_cast<const_value>(this->ptrStoreGet());
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::setValue(const_value value)
{
    this->ptrStoreSet(value);
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::setValue(const Self &source)
{
    this->ptrStoreSet(source.ptrStoreGet());
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
FieldDescriptionBase *
    PointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::createFieldDescription   (
                       const Char8                *szFieldname,
                             UInt32                uiFieldFlags,
                             FieldEditMethod       fEditMethod,
                             FieldGetMethod        fGetMethod  )
{
    if(szFieldname == NULL)
    {
        FWARNING(("createFieldDescription no fieldname given"));

        return NULL;
    }

    if(uiFieldFlags == FieldDescFactoryBase::AutoFlags)
    {
        uiFieldFlags = (Field::SFDefaultFlags | Field::FStdAccess);
    }

    FieldDescriptionBase *returnValue = new typename Self::Description(
        _fieldType, 
        szFieldname,
        "",
        0,
        0,
        false,
        uiFieldFlags,
        fEditMethod,
        fGetMethod);

    return returnValue;
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
FieldDescriptionBase *
    PointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::createIdxFieldDescription(
                       const Char8                *szFieldname,
                             UInt32                uiFieldFlags,
                             FieldIndexEditMethod  fEditMethod,
                             FieldIndexGetMethod   fGetMethod  )
{
    if(szFieldname == NULL)
    {
        FWARNING(("createFieldDescriptionIdx no fieldname given"));

        return NULL;
    }

    if(uiFieldFlags == FieldDescFactoryBase::AutoFlags)
    {
        uiFieldFlags = (Field::SFDefaultFlags | Field::FStdAccess);
    }

    FieldDescriptionBase *returnValue = new typename Self::Description(
        _fieldType, 
        szFieldname,
        "",
        0,
        0,
        false,
        uiFieldFlags,
        fEditMethod,
        fGetMethod);

    return returnValue;
}

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
}

#ifdef OSG_MT_CPTR_ASPECT
template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::syncWith(Self &source)
{
    Inherited::syncWith(source);
}
#endif

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class    PtrTypeT, 
          typename RefCountPolicy,
          Int32    NamespaceI    > inline 
void PointerSField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::operator =(const Self &other)
{
    this->ptrStoreSet(other.ptrStoreGet());
}

OSG_END_NAMESPACE
