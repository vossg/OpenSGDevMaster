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
/*! \file OSGParentPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ParentPointerSField<ObjectTypeT,                                        */
/*                     NamespaceI  >                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
const FieldType &ParentPointerSField<ObjectTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ParentPointerSField<ObjectTypeT,
                    RefCountPolicy,
                    NamespaceI    >::ParentPointerSField(void) : 
     Inherited       (      ),
    _uiParentFieldPos(0xFFFF)
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ParentPointerSField<ObjectTypeT,
                    RefCountPolicy,
                    NamespaceI    >::ParentPointerSField(
                        const_value value, 
                        UInt16      uiParentFieldPos) :
     Inherited       (value           ),
    _uiParentFieldPos(uiParentFieldPos)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ParentPointerSField<ObjectTypeT,
                    RefCountPolicy,
                    NamespaceI    >::~ParentPointerSField(void)
{
}


/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
UInt16 ParentPointerSField<ObjectTypeT, 
                           RefCountPolicy,
                           NamespaceI    >::getParentFieldPos(void) const
{
    return _uiParentFieldPos;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerSField<ObjectTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    ParentPointerSField<ObjectTypeT,
                        RefCountPolicy,
                        NamespaceI >::getValue(void) const
{
    return static_cast<const_value>(this->ptrStoreGet());
}
    
/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, 
                           RefCountPolicy,
                           NamespaceI    >::setValue(
                               const_value  value,
                               UInt16       uiParentFieldPos)
{
    this->ptrStoreSet(value);
    
    _uiParentFieldPos = uiParentFieldPos;
}


/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
UInt32 ParentPointerSField<ObjectTypeT, 
                           RefCountPolicy,
                           NamespaceI    >::getBinSize(void) const
{
    return (Inherited      ::getBinSize() + 
            PosSFieldTraits::getBinSize(_uiParentFieldPos));
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, 
                         RefCountPolicy,
                         NamespaceI    >::copyToBin(
                             BinaryDataHandler &pMem) const
{
    Inherited      ::copyToBin(pMem);
    
    PosSFieldTraits::copyToBin(pMem, _uiParentFieldPos);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, 
                         RefCountPolicy,
                         NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
    
    PosSFieldTraits::copyFromBin(pMem, _uiParentFieldPos);
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, 
                         RefCountPolicy,
                         NamespaceI    >::syncWith(Self &source)
{
    Inherited::syncWith(source);
    
    _uiParentFieldPos = source._uiParentFieldPos;
}
#endif

/*-------------------------------------------------------------------------*/
/* Access                                                                  */


/*-------------------------------------------------------------------------*/
/* Comparison                                                              */

// template <class ObjectTypeT, Int32 NamespaceI>
// inline bool
//     ParentPointerSField<ObjectTypeT,
//                         NamespaceI  >::operator==(Self const &other)
// {   
// }

OSG_END_NAMESPACE
