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
/* Access Handling                                                         */

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onAdd(
    SFieldBaseType * const, 
    MemoryObject   * const pObj)
{
    RefCountPolicyType::addRef(pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onAdd(
    MFieldBaseType * const, 
    MemoryObject   * const pObj)
{
    RefCountPolicyType::addRef(pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSub(
    SFieldBaseType * const, 
    MemoryObject   * const pObj)
{
    RefCountPolicyType::subRef(pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSub(
    MFieldBaseType * const, 
    MemoryObject   * const pObj)
{
    RefCountPolicyType::subRef(pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onReplace(
    SFieldBaseType * const pSField,
    MemoryObject   * const pOldObj,
    MemoryObject   * const pNewObj)
{
    onAdd(pSField, pNewObj);
    onSub(pSField, pOldObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onReplace(
    MFieldBaseType * const pMField,
    MemoryObject   * const pOldObj,
    MemoryObject   * const pNewObj)
{
    onAdd(pMField, pNewObj);
    onSub(pMField, pOldObj);
}

/*-------------------------------------------------------------------------*/
/* Sync Access Handling                                                    */

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSyncAdd(
    SFieldBaseType * const pSField, 
    MemoryObject   * const pObj   )
{
    onAdd(pSField, pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSyncAdd(
    MFieldBaseType * const pMField, 
    MemoryObject   * const pObj   )
{
    onAdd(pMField, pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSyncSub(
    SFieldBaseType * const pSField, 
    MemoryObject   * const pObj   )
{
    if(pObj != NULL)
    {
        Thread::getCurrentChangeList()->addDelayedSubRef<
            RefCountPolicyT>(pObj);
    }

//    onSub(pSField, pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSyncSub(
    MFieldBaseType * const pMField, 
    MemoryObject   * const pObj   )
{
    if(pObj != NULL)
    {
        Thread::getCurrentChangeList()->addDelayedSubRef<
            RefCountPolicyT>(pObj);
    }

//    onSub(pMField, pObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSyncReplace(
    SFieldBaseType * const pSField,
    MemoryObject   * const pOldObj,
    MemoryObject   * const pNewObj)
{
    onSyncAdd(pSField, pNewObj);
    onSyncSub(pSField, pOldObj);
}

template<typename RefCountPolicyT> inline 
void MemObjPointerAccessHandler<RefCountPolicyT>::onSyncReplace(
    MFieldBaseType * const pMField,
    MemoryObject   * const pOldObj,
    MemoryObject   * const pNewObj)
{
    onSyncAdd(pMField, pNewObj);
    onSyncSub(pMField, pOldObj);
}

OSG_END_NAMESPACE
