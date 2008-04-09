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
/*! \file PointerAccessHandlerDecl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Access Handling                                                         */

template<typename RefCountPolicyT> inline 
void PointerAccessHandler<RefCountPolicyT>::onAdd(SFieldBaseType * const, 
                                 FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

template<typename RefCountPolicyT> inline 
void PointerAccessHandler<RefCountPolicyT>::onAdd(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::addRef(pObj);
}

template<typename RefCountPolicyT> inline 
void PointerAccessHandler<RefCountPolicyT>::onSub(
        SFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

template<typename RefCountPolicyT> inline 
void PointerAccessHandler<RefCountPolicyT>::onSub(
        MFieldBaseType * const, FieldContainerPtrConst pObj)
{
    RefCountPolicyType::subRef(pObj);
}

template<typename RefCountPolicyT> inline 
void PointerAccessHandler<RefCountPolicyT>::onReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onAdd(pSField, pNewObj);
    onSub(pSField, pOldObj);
}

template<typename RefCountPolicyT> inline 
void
    PointerAccessHandler<RefCountPolicyT>::onReplace(
        MFieldBaseType         * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onAdd(pMField, pNewObj);
    onSub(pMField, pOldObj);
}

/*-------------------------------------------------------------------------*/
/* Sync Access Handling                                                    */

template<typename RefCountPolicyT> inline 
void
    PointerAccessHandler<RefCountPolicyT>::onSyncAdd(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onAdd(pSField, pObj);
}

template<typename RefCountPolicyT> inline 
void
    PointerAccessHandler<RefCountPolicyT>::onSyncAdd(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onAdd(pMField, pObj);
}

template<typename RefCountPolicyT> inline 
void
    PointerAccessHandler<RefCountPolicyT>::onSyncSub(
        SFieldBaseType * const pSField, FieldContainerPtrConst pObj)
{
    onSub(pSField, pObj);
}

template<typename RefCountPolicyT> inline 
void
    PointerAccessHandler<RefCountPolicyT>::onSyncSub(
        MFieldBaseType * const pMField, FieldContainerPtrConst pObj)
{
    onSub(pMField, pObj);
}

template<typename RefCountPolicyT> inline 
void
    PointerAccessHandler<RefCountPolicyT>::onSyncReplace(
        SFieldBaseType         * const pSField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pSField, pNewObj);
    onSyncSub(pSField, pOldObj);
}

template<typename RefCountPolicyT> inline 
void
    PointerAccessHandler<RefCountPolicyT>::onSyncReplace(
        MFieldBaseType         * const pMField,
        FieldContainerPtrConst         pOldObj,
        FieldContainerPtrConst         pNewObj)
{
    onSyncAdd(pMField, pNewObj);
    onSyncSub(pMField, pOldObj);
}

OSG_END_NAMESPACE
