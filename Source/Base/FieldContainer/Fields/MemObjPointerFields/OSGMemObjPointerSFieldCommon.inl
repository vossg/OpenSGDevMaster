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

/*! \class MemObjPointerSFieldCommon

 */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class AccessHandlerT, Int32 NamespaceI> inline
MemObjPointerSFieldCommon<AccessHandlerT,
                          NamespaceI    >::MemObjPointerSFieldCommon(void) :
    Inherited()
{
}

template <class AccessHandlerT, Int32 NamespaceI> inline
MemObjPointerSFieldCommon<AccessHandlerT,
                          NamespaceI    >::MemObjPointerSFieldCommon(
                              const Self &source) :
    Inherited()
{
    _fieldValue = source._fieldValue;

    AccessHandler::onAdd(this, _fieldValue);
}

template <class AccessHandlerT, Int32 NamespaceI> inline
MemObjPointerSFieldCommon<AccessHandlerT,
                          NamespaceI    >::MemObjPointerSFieldCommon(
                              const_value value) :
    Inherited()
{
    _fieldValue = value;

    AccessHandler::onAdd(this, _fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class AccessHandlerT, Int32 NamespaceI> inline
MemObjPointerSFieldCommon<AccessHandlerT,
                          NamespaceI    >::~MemObjPointerSFieldCommon(void)
{
    AccessHandler::onSub(this, _fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Store Interface                                                         */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class AccessHandlerT, Int32 NamespaceI> inline 
typename MemObjPointerSFieldCommon<AccessHandlerT,
                                   NamespaceI    >::value_type 
    MemObjPointerSFieldCommon<AccessHandlerT,
                              NamespaceI    >::ptrStoreGet(void) const
{
    return AccessHandler::validate(_fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class AccessHandlerT, Int32 NamespaceI> inline 
void MemObjPointerSFieldCommon<AccessHandlerT,
                               NamespaceI    >::ptrStoreSet(const_value pNewObj)
{
    AccessHandler::onReplace(this, _fieldValue, pNewObj);
    
    _fieldValue = pNewObj;
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
void MemObjPointerSFieldCommon<AccessHandlerT,
                               NamespaceI    >::ptrStoreClear(void)
{
    AccessHandler::onSub(this, _fieldValue);
    
    _fieldValue = NULL;
}


/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

        
template <class AccessHandlerT, Int32 NamespaceI> inline 
void MemObjPointerSFieldCommon<AccessHandlerT,
                               NamespaceI    >::copyFromBin(
                                   BinaryDataHandler &pMem)
{
    MemoryObject *pNewObj = NULL;
    
    PtrBaseTraitsType::copyFromBin  ( pMem, 
                                      pNewObj   );

    AccessHandler    ::onSyncReplace( this, 
                                     _fieldValue, 
                                      pNewObj   );
    
    _fieldValue = pNewObj;
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
template <class AccessHandlerT, Int32 NamespaceI> inline 
void MemObjPointerSFieldCommon<AccessHandlerT,
                               NamespaceI     >::syncWith(Self &source)
{
    MemoryObject *pNewObj = convertToCurrentAspect(source.ptrStoreGet());
    
    AccessHandler::onSyncReplace( this, 
                                 _fieldValue, 
                                  pNewObj);
    
    _fieldValue = pNewObj;
}
#endif

OSG_END_NAMESPACE
