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

#ifndef _OSGMEMOBJPOINTERSFIELDCOMMON_H_
#define _OSGMEMOBJPOINTERSFIELDCOMMON_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGMemObjPointerSFieldBase.h"
#include "OSGBinaryDataHandler.h"


OSG_BEGIN_NAMESPACE

// forward declarations
template <Int32 NamespaceI>
class MemObjPointerFieldTraitsBase;

/*! \ingroup GrpBaseMemoryObjectsFields
    \ingroup GrpLibOSGBase
 */

template <class AccessHandlerT,
          Int32 NamespaceI     = 0>
class MemObjPointerSFieldCommon : public MemObjPointerSFieldBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    

    typedef          MemObjPointerSFieldBase             Inherited;
    typedef          MemObjPointerSFieldCommon           Self;

    typedef typename Inherited::const_value              const_value;
    typedef typename Inherited::value_type               value_type;

    typedef typename Inherited::StoredType               StoredType;

    typedef          AccessHandlerT                      AccessHandler;

    typedef          FieldTraitsFCPtrBase<
                         MemoryObject *, 
                         NamespaceI       >              PtrBaseTraitsType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static const Int32 Namespace = NamespaceI;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             MemObjPointerSFieldCommon(      void               );
             MemObjPointerSFieldCommon(const Self        &source);
    explicit MemObjPointerSFieldCommon(      const_value  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~MemObjPointerSFieldCommon(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Store Interface                                              */
    /*! \{                                                                 */
    
    value_type  ptrStoreGet  (void               ) const;
    
    void        ptrStoreSet  (const_value pNewObj);
    void        ptrStoreClear(void               );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    void copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith(Self &source);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Self &source);
};

OSG_END_NAMESPACE

#include "OSGMemObjPointerSFieldCommon.inl"

#endif // _OSGMEMOBJPOINTERSFIELDCOMMON_H_
