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
/*! \file OSGChildAccessHandlerDecl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class ChildAccessHandler

    Access handler for child pointer fields.
    This class handles all reference counting and child/parent linking
    operations for child pointer fields. The fields only call the respective
    members when an operation on one of their values is performed.
 */

/*-------------------------------------------------------------------------*/
/* Internal Helper                                                         */

template<typename RefCountPolicyT> inline 
typename ChildAccessHandler<RefCountPolicyT>::SFieldType * const
    ChildAccessHandler<RefCountPolicyT>::dcastSField(
        SFieldBaseType * const pSField)
{
    return static_cast<SFieldType *>(pSField);
}

template<typename RefCountPolicyT> inline 
typename ChildAccessHandler<RefCountPolicyT>::MFieldType * const
    ChildAccessHandler<RefCountPolicyT>::dcastMField(
        MFieldBaseType * const pMField)
{
    return static_cast<MFieldType *>(pMField);
}

/*-------------------------------------------------------------------------*/
/* Linking                                                                 */

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::linkParent(
    FieldContainerPtr const pParent,
    UInt16            const childFieldId,
    FieldContainerPtr const pChild,
    UInt16            const parentFieldId)
{
    pChild->linkParent(pParent, childFieldId, parentFieldId);
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::unlinkParent(
    FieldContainerPtr const pParent,
    FieldContainerPtr const pChild,
    UInt16            const parentFieldId)
{
    pChild->unlinkParent(pParent, parentFieldId);
}

/*-------------------------------------------------------------------------*/
/* Access Handling                                                         */

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onAdd(
    SFieldBaseType    * const pSField, 
    FieldContainerPtr   const pObj   )
{
    if(pObj != NULL)
    {
        RefCountPolicyType::addRef(pObj /*, false*/);

        linkParent(dcastSField(pSField)->getEnclosingObject(),
                   dcastSField(pSField)->getChildFieldId   (),
                   pObj,
                   dcastSField(pSField)->getParentFieldPos () );
    }
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onAdd(
    MFieldBaseType    * const pMField, 
    FieldContainerPtr   const pObj   )
{
    if(pObj != NULL)
    {
        RefCountPolicyType::addRef(pObj /*, false*/);

        linkParent(dcastMField(pMField)->getEnclosingObject(),
                   dcastMField(pMField)->getChildFieldId   (),
                   pObj,
                   dcastMField(pMField)->getParentFieldPos () );
    }
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSub(
    SFieldBaseType    * const pSField, 
    FieldContainerPtr   const pObj   )
{
    if(pObj != NULL)
    {
        unlinkParent(dcastSField(pSField)->getEnclosingObject(),
                     pObj,
                     dcastSField(pSField)->getParentFieldPos() );

        RefCountPolicyType::subRef(pObj/*, false*/);
    }
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSub(
    MFieldBaseType    * const pMField, 
    FieldContainerPtr   const pObj   )
{
    if(pObj != NULL)
    {
        unlinkParent(dcastMField(pMField)->getEnclosingObject(),
                     pObj,
                     dcastMField(pMField)->getParentFieldPos() );

        RefCountPolicyType::subRef(pObj/*, false*/);
    }
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onReplace(
    SFieldBaseType    * const pSField,
    FieldContainerPtr   const pOldObj, 
    FieldContainerPtr   const pNewObj)
{
    RefCountPolicyType::addRef(pNewObj);

    if(pOldObj != NULL)
    {
        unlinkParent(dcastSField(pSField)->getEnclosingObject(),
                     pOldObj,
                     dcastSField(pSField)->getParentFieldPos());

        RefCountPolicyType::subRef(pOldObj/*, false*/);
    }

    if(pNewObj != NULL)
    {
        linkParent(dcastSField(pSField)->getEnclosingObject(),
                   dcastSField(pSField)->getChildFieldId   (),
                   pNewObj,
                   dcastSField(pSField)->getParentFieldPos ());
    }
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onReplace(
    MFieldBaseType    * const pMField,
    FieldContainerPtr   const pOldObj,
    FieldContainerPtr   const pNewObj)
{
    RefCountPolicyType::addRef(pNewObj);

    if(pOldObj != NULL)
    {
        unlinkParent(dcastMField(pMField)->getEnclosingObject(),
                     pOldObj,
                     dcastMField(pMField)->getParentFieldPos() );

        RefCountPolicyType::subRef(pOldObj/*, false*/);
    }

    if(pNewObj != NULL)
    {
        linkParent(dcastMField(pMField)->getEnclosingObject(),
                   dcastMField(pMField)->getChildFieldId   (),
                   pNewObj,
                   dcastMField(pMField)->getParentFieldPos ());
    }
}

/*-------------------------------------------------------------------------*/
/* Sync Access Handling                                                    */

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSyncAdd(
    SFieldBaseType    * const, 
    FieldContainerPtr   const pObj)
{
    RefCountPolicyType::addRef(pObj);
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSyncAdd(
    MFieldBaseType    * const, 
    FieldContainerPtr   const pObj)
{
    RefCountPolicyType::addRef(pObj);
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSyncSub(
    SFieldBaseType    * const, 
    FieldContainerPtr   const pObj)
{
    RefCountPolicyType::subRef(pObj);
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSyncSub(
    MFieldBaseType    * const, 
    FieldContainerPtr   const pObj)
{
    RefCountPolicyType::subRef(pObj);
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSyncReplace(
    SFieldBaseType    * const pSField,
    FieldContainerPtr   const pOldObj,
    FieldContainerPtr   const pNewObj)
{
    onSyncAdd(pSField, pNewObj);

    if(pOldObj != NullFC)
    {
        Thread::getCurrentChangeList()->addDelayedSubRef<
            RefCountPolicyT>(pOldObj);
    }

//    onSyncSub(pSField, pOldObj);
}

template<typename RefCountPolicyT> inline 
void ChildAccessHandler<RefCountPolicyT>::onSyncReplace(
    MFieldBaseType    * const pMField,
    FieldContainerPtr   const pOldObj,
    FieldContainerPtr   const pNewObj)
{
    onSyncAdd(pMField, pNewObj);

    if(pOldObj != NullFC)
    {
        Thread::getCurrentChangeList()->addDelayedSubRef<
            RefCountPolicyT>(pOldObj);
    }

//    onSyncSub(pMField, pOldObj);
}

OSG_END_NAMESPACE
