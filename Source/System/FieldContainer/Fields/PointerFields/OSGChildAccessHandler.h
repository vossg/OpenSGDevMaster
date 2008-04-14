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

#ifndef _OSGCHILDACCESSHANDLER_H_
#define _OSGCHILDACCESSHANDLER_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildAccessHandlerDecl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
class PointerMFieldBase;

class PointerSFieldBase;

template <typename AccessHandlerT, Int32 NamespaceI>
class ChildPointerMFieldBase;

template <typename AccessHandlerT, Int32 NamespaceI>
class ChildPointerSFieldBase;

template<typename RefCountPolicyT>
class ChildAccessHandler 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
  
    typedef ChildAccessHandler         Self;
               
    typedef RefCountPolicyT            RefCountPolicyType;
    
    typedef PointerMFieldBase          MFieldBaseType;
    typedef PointerSFieldBase          SFieldBaseType;
    
    typedef ChildPointerMFieldBase <Self, 0> MFieldType;
    typedef ChildPointerSFieldBase <Self, 0> SFieldType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access Handling                                              */
    /*! \{                                                                 */
    
    static void onAdd    (SFieldBaseType    * const pSField,
                          FieldContainerPtr   const pObj   );
    static void onAdd    (MFieldBaseType    * const pMField,
                          FieldContainerPtr   const pObj   );
    
    static void onSub    (SFieldBaseType    * const pSField,
                          FieldContainerPtr   const pObj   );
    static void onSub    (MFieldBaseType    * const pMField,
                          FieldContainerPtr   const pObj   );
    
    static void onReplace(SFieldBaseType    * const pSField,
                          FieldContainerPtr   const pOldObj,
                          FieldContainerPtr   const pNewObj);
    static void onReplace(MFieldBaseType    * const pMField,
                          FieldContainerPtr   const pOldObj,
                          FieldContainerPtr   const pNewObj);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Sync Access Handling                                         */
    /*! \{                                                                 */
    
    static void onSyncAdd    (SFieldBaseType    * const pSField,
                              FieldContainerPtr   const pObj   );
    static void onSyncAdd    (MFieldBaseType    * const pMField,
                              FieldContainerPtr   const pObj   );
    
    static void onSyncSub    (SFieldBaseType    * const pSField,
                              FieldContainerPtr   const pObj   );
    static void onSyncSub    (MFieldBaseType    * const pMField,
                              FieldContainerPtr   const pObj   );
    
    static void onSyncReplace(SFieldBaseType    * const pSField,
                              FieldContainerPtr   const pOldObj,
                              FieldContainerPtr   const pNewObj);
    static void onSyncReplace(MFieldBaseType    * const pMField,
                              FieldContainerPtr   const pOldObj,
                              FieldContainerPtr   const pNewObj);
                            
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    template <class ObjectT>
    static ObjectT *validate(ObjectT * const pObject)
    {
        return RefCountPolicyType::validate(pObject);
    }

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name Internal Helper                                              */
    /*! \{                                                                 */
  
    static SFieldType * const dcastSField(SFieldBaseType * const pSField);
    static MFieldType * const dcastMField(MFieldBaseType * const pMField);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Linking                                                      */
    /*! \{                                                                 */
    
//     static void unlinkChild (FieldContainerPtrConst pChild,
//                              UInt16 const           parentFieldId );
    static void linkParent  (FieldContainerPtr const pParent, 
                             UInt16            const childFieldId,
                             FieldContainerPtr const pChild,
                             UInt16            const parentFieldId);
    static void unlinkParent(FieldContainerPtr const pParent,
                             FieldContainerPtr const pChild,
                             UInt16            const parentFieldId);
                      
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

typedef ChildAccessHandler<UnrecordedRefCountPolicy> UnrecChildAccessHandler;

OSG_END_NAMESPACE

#include "OSGChildAccessHandler.inl"

#endif // _OSGCHILDACCESSHANDLER_H_
