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

template <class ObjectTypeT, Int32 NamespaceI> inline 
FieldType const &ParentPointerSField<ObjectTypeT,
                                     NamespaceI >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI> inline
ParentPointerSField<ObjectTypeT,
                    NamespaceI >::ParentPointerSField(void) : 
     Inherited   (),
    _childIdValue()
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI> inline
ParentPointerSField<ObjectTypeT,
                    NamespaceI >::ParentPointerSField(Self const &source) :
     Inherited   (source              ),
    _childIdValue(source._childIdValue)
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI> inline
ParentPointerSField<ObjectTypeT,
                    NamespaceI >::ParentPointerSField(ValueType    ptrValue, 
                                                      IdStoredType idValue ) :
     Inherited   (ptrValue),
    _childIdValue(idValue )
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI> inline
ParentPointerSField<ObjectTypeT,
                    NamespaceI >::~ParentPointerSField(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* IdStore Interface                                                       */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class ObjectTypeT, Int32 NamespaceI> inline 
UInt16 const ParentPointerSField<ObjectTypeT, 
                                 NamespaceI >::idStoreGet(void) const
{
    return _childIdValue;
}
    
/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, 
                         NamespaceI >::idStoreSet(UInt16 const newId)
{
    _childIdValue = newId;
}

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, NamespaceI>::idStoreClear(void)
{
    _childIdValue = 0;
}

/*-------------------------------------------------------------------------*/
/* Raw IdStore Access                                                      */

template <class ObjectTypeT, Int32 NamespaceI> inline 
typename ParentPointerSField<ObjectTypeT, NamespaceI>::IdStoredTypeRef
    ParentPointerSField<ObjectTypeT, NamespaceI>::editRawIdStore(void)
{
    return _childIdValue;
}

template <class ObjectTypeT, Int32 NamespaceI> inline 
typename ParentPointerSField<ObjectTypeT, NamespaceI>::IdStoredTypeConstRef
    ParentPointerSField<ObjectTypeT, NamespaceI>::getRawIdStore (void) const
{
    return _childIdValue;
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <class ObjectTypeT, Int32 NamespaceI> inline
UInt32 ParentPointerSField<ObjectTypeT, NamespaceI>::getBinSize(void) const
{
    return
        Inherited::getBinSize() + IdBaseTraitsType::getBinSize(_childIdValue);
}

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, 
                         NamespaceI >::copyToBin(BinaryDataHandler &pMem) const
{
    Inherited::copyToBin(pMem);
    
    IdBaseTraitsType::copyToBin(pMem, _childIdValue);
}

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, 
                         NamespaceI>::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
    
    IdBaseTraitsType::copyFromBin(pMem, _childIdValue);
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

template <class ObjectTypeT, Int32 NamespaceI> inline 
void ParentPointerSField<ObjectTypeT, NamespaceI>::syncWith(Self &source)
{
    Inherited::syncWith(source);
    
    _childIdValue = source._childIdValue;
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class ObjectTypeT, Int32 NamespaceI> inline 
typename ParentPointerSField<ObjectTypeT,
                             NamespaceI >::const_reference
    ParentPointerSField<ObjectTypeT,
                        NamespaceI >::getValue(void) const
{
    return this->getRawStore();
}

/*-------------------------------------------------------------------------*/
/* Comparison                                                              */

// template <class ObjectTypeT, Int32 NamespaceI>
// inline bool
//     ParentPointerSField<ObjectTypeT,
//                         NamespaceI  >::operator==(Self const &other)
// {   
// }

OSG_END_NAMESPACE
