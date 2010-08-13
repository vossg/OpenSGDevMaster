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

#ifndef _OSGMEMOBJPOINTERACCESSHANDLERDECL_H_
#define _OSGMEMOBJPOINTERACCESSHANDLERDECL_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

// forward declarations
class MemObjPointerMFieldBase;
class MemObjPointerSFieldBase;

/*! \ingroup GrpBaseMemoryObjectsFields
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template<typename RefCountPolicyT>
class MemObjPointerAccessHandler
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef MemObjPointerAccessHandler  Self;
      
    typedef RefCountPolicyT             RefCountPolicyType;
    
    typedef MemObjPointerMFieldBase     MFieldBaseType;
    typedef MemObjPointerSFieldBase     SFieldBaseType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access Handling                                              */
    /*! \{                                                                 */
    
    static void onAdd    (SFieldBaseType    * const pSField,
                          MemoryObject      * const pObj   );
    static void onAdd    (MFieldBaseType    * const pMField,
                          MemoryObject      * const pObj   );
    
    static void onSub    (SFieldBaseType    * const pSField,
                          MemoryObject      * const pObj   );
    static void onSub    (MFieldBaseType    * const pMField,
                          MemoryObject      * const pObj   );
    
    static void onReplace(SFieldBaseType    * const pSField,
                          MemoryObject      * const pOldObj,
                          MemoryObject      * const pNewObj);
    static void onReplace(MFieldBaseType    * const pMField,
                          MemoryObject      * const pOldObj,
                          MemoryObject      * const pNewObj);
                   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Sync Access Handling                                         */
    /*! \{                                                                 */
    
    static void onSyncAdd    (SFieldBaseType    * const pSField,
                              MemoryObject      * const pObj   );
    static void onSyncAdd    (MFieldBaseType    * const pMField,
                              MemoryObject      * const pObj   );
    
    static void onSyncSub    (SFieldBaseType    * const pSField,
                              MemoryObject      * const pObj   );
    static void onSyncSub    (MFieldBaseType    * const pMField,
                              MemoryObject      * const pObj   );
    
    static void onSyncReplace(SFieldBaseType    * const pSField,
                              MemoryObject      * const pOldObj,
                              MemoryObject      * const pNewObj);
    static void onSyncReplace(MFieldBaseType    * const pMField,
                              MemoryObject      * const pOldObj,
                              MemoryObject      * const pNewObj);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    template <class ObjectT>
    static ObjectT *validate(ObjectT * const pObject)
    {
        return RefCountPolicyType::validate(pObject);
    }
};

OSG_END_NAMESPACE

#include "OSGMemObjPointerAccessHandler.inl"

#endif // _OSGMEMOBJPOINTERACCESSHANDLER_H_
