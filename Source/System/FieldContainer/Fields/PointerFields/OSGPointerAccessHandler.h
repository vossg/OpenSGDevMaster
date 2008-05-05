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

#ifndef _OSGPOINTERACCESSHANDLERDECL_H_
#define _OSGPOINTERACCESSHANDLERDECL_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakAccessHandlerDecl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
class PointerMFieldBase;
class PointerSFieldBase;

template<typename RefCountPolicyT>
class PointerAccessHandler
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef PointerAccessHandler  Self;
      
    typedef RefCountPolicyT       RefCountPolicyType;
    
    typedef PointerMFieldBase     MFieldBaseType;
    typedef PointerSFieldBase     SFieldBaseType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access Handling                                              */
    /*! \{                                                                 */
    
    static void onAdd    (SFieldBaseType    * const pSField,
                          FieldContainer    * const pObj   );
    static void onAdd    (MFieldBaseType    * const pMField,
                          FieldContainer    * const pObj   );
    
    static void onSub    (SFieldBaseType    * const pSField,
                          FieldContainer    * const pObj   );
    static void onSub    (MFieldBaseType    * const pMField,
                          FieldContainer    * const pObj   );
    
    static void onReplace(SFieldBaseType    * const pSField,
                          FieldContainer    * const pOldObj,
                          FieldContainer    * const pNewObj);
    static void onReplace(MFieldBaseType    * const pMField,
                          FieldContainer    * const pOldObj,
                          FieldContainer    * const pNewObj);
                   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Sync Access Handling                                         */
    /*! \{                                                                 */
    
    static void onSyncAdd    (SFieldBaseType    * const pSField,
                              FieldContainer    * const pObj   );
    static void onSyncAdd    (MFieldBaseType    * const pMField,
                              FieldContainer    * const pObj   );
    
    static void onSyncSub    (SFieldBaseType    * const pSField,
                              FieldContainer    * const pObj   );
    static void onSyncSub    (MFieldBaseType    * const pMField,
                              FieldContainer    * const pObj   );
    
    static void onSyncReplace(SFieldBaseType    * const pSField,
                              FieldContainer    * const pOldObj,
                              FieldContainer    * const pNewObj);
    static void onSyncReplace(MFieldBaseType    * const pMField,
                              FieldContainer    * const pOldObj,
                              FieldContainer    * const pNewObj);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    template <class ObjectT>
    static ObjectT *validate(ObjectT * const pObject)
    {
        return RefCountPolicyType::validate(pObject);
    }
};

typedef PointerAccessHandler<NoRefCountPolicy        > NoRefCountAccessHandler;
typedef PointerAccessHandler<WeakRefCountPolicy      > WeakAccessHandler;
typedef PointerAccessHandler<UnrecordedRefCountPolicy> UnrecordedAccessHandler;

OSG_END_NAMESPACE

#include "OSGPointerAccessHandler.inl"

#endif // _OSGWEAKACCESSHANDLERDECL_H_
