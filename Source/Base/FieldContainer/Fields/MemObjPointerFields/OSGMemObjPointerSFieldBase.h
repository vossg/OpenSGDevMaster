/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifndef _OSGMEMOBJPOINTERSFIELDBASE_H_
#define _OSGMEMOBJPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseDef.h"
#include "OSGSField.h"
#include "OSGMemoryObjectFieldTraits.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseMemoryObjectsFields
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING MemObjPointerSFieldBase : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef Field                                    Inherited;

    typedef MemObjPointerSFieldBase                  Self;
    typedef FieldTraits      <MemoryObject *, 0>     SFieldTraits;
    
    // storage
    typedef MemoryObject *                           StoredType;
    typedef MemoryObject * const                     const_value;
    typedef MemoryObject *                           value_type;

    typedef EditSFieldHandle <Self      >            EditHandle;
    typedef boost::shared_ptr<EditHandle>            EditHandlePtr;

    typedef GetSFieldHandle  <Self     >             GetHandle;
    typedef boost::shared_ptr<GetHandle>             GetHandlePtr;
    
    /*---------------------------------------------------------------------*/

    static const bool isSField       = true;
    static const bool isMField       = false;

    static const bool isPointerField = true;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw Store Access                                             */
    /*! \{                                                                 */
    
    value_type getValue(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize(void                   ) const;
    
    void   copyToBin (BinaryDataHandler &pMem) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw Store Access                                             */
    /*! \{                                                                 */

    bool operator ==(const Self &source) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType  _fieldType;

           StoredType _fieldValue;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    MemObjPointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~MemObjPointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assign                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

    StoredType       &editRawStore(void);
    StoredType const &getRawStore (void) const;

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MemObjPointerSFieldBase(const Self &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Self &source);
};

typedef MemObjPointerSFieldBase MemoryObjectPtrSFieldBase;

OSG_END_NAMESPACE

#include "OSGMemObjPointerSFieldBase.inl"

#endif // _OSGMEMOBJPOINTERSFIELDBASE_H_
