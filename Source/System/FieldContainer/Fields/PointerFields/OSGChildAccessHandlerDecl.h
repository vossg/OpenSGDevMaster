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

#ifndef _OSGCHILDACCESSHANDLERDECL_H_
#define _OSGCHILDACCESSHANDLERDECL_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGRefCountPolicies.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildAccessHandlerDecl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
class PointerMFieldBase;

class PointerSFieldBase;

template <Int32 NamespaceI>
class ChildPointerMFieldBase;

template <Int32 NamespaceI>
class ChildPointerSFieldBase;


class ChildAccessHandler 
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
  
    typedef ChildAccessHandler         Self;
    typedef UnrecordedRefCountPolicy   Inherited;
               
    typedef UnrecordedRefCountPolicy   RefCountPolicyType;
    
    typedef PointerMFieldBase          MFieldBaseType;
    typedef PointerSFieldBase          SFieldBaseType;
    
    typedef ChildPointerMFieldBase <0> MFieldType;
    typedef ChildPointerSFieldBase <0> SFieldType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access Handling                                              */
    /*! \{                                                                 */
    
    static void onAdd    (SFieldBaseType         * const pSField,
                          FieldContainerPtrConst         pObj    );
    static void onAdd    (MFieldBaseType         * const pMField,
                          FieldContainerPtrConst         pObj    );
    
    static void onSub    (SFieldBaseType         * const pSField,
                          FieldContainerPtrConst         pObj    );
    static void onSub    (MFieldBaseType         * const pMField,
                          FieldContainerPtrConst         pObj    );
    
    static void onReplace(SFieldBaseType         * const pSField,
                          FieldContainerPtrConst         pOldObj,
                          FieldContainerPtrConst         pNewObj );
    static void onReplace(MFieldBaseType         * const pMField,
                          FieldContainerPtrConst         pOldObj,
                          FieldContainerPtrConst         pNewObj );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Sync Access Handling                                         */
    /*! \{                                                                 */
    
    static void onSyncAdd    (SFieldBaseType         * const pSField,
                              FieldContainerPtrConst         pObj    );
    static void onSyncAdd    (MFieldBaseType         * const pMField,
                              FieldContainerPtrConst         pObj    );
    
    static void onSyncSub    (SFieldBaseType         * const pSField,
                              FieldContainerPtrConst         pObj    );
    static void onSyncSub    (MFieldBaseType         * const pMField,
                              FieldContainerPtrConst         pObj    );
    
    static void onSyncReplace(SFieldBaseType         * const pSField,
                              FieldContainerPtrConst         pOldObj,
                              FieldContainerPtrConst         pNewObj );
    static void onSyncReplace(MFieldBaseType         * const pMField,
                              FieldContainerPtrConst         pOldObj,
                              FieldContainerPtrConst         pNewObj );
                            
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
    static void linkParent  (FieldContainerPtrConst pParent, 
                             UInt16 const           childFieldId,
                             FieldContainerPtrConst pChild,
                             UInt16 const           parentFieldId );
    static void unlinkParent(FieldContainerPtrConst pParent,
                             FieldContainerPtrConst pChild,
                             UInt16 const           parentFieldId );
                      
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

#endif // _OSGCHILDACCESSHANDLERDECL_H_
