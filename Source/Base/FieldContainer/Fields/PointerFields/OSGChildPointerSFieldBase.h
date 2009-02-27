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

#ifndef _OSGCHILDPOINTERSFIELDBASE_H_
#define _OSGCHILDPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerSFieldCommon.h"
#include "OSGChildAccessHandler.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerFields
    \ingroup GrpLibOSGBase
 */

template <typename AccessHandlerT,
          Int32    NamespaceI = 0>
class ChildPointerSFieldBase 
    : public PointerSFieldCommon<AccessHandlerT, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
    typedef PointerSFieldCommon   <AccessHandlerT,
                                   NamespaceI    > Inherited;
    typedef ChildPointerSFieldBase                 Self;
    
    typedef FieldContainer * const                 const_value;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Child Linking Information                                    */
    /*! \{                                                                 */

    FieldContainer *getEnclosingObject(void) const;
    UInt16          getChildFieldId   (void) const;
    UInt16          getParentFieldId  (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ChildPointerSFieldBase(FieldContainer * const  pParent,
                           UInt16                  usChildFieldId,
                           UInt16                  usParentFieldId);

    ChildPointerSFieldBase(const_value            value,
                           FieldContainer * const pParent,
                           UInt16                 usChildFieldId,
                           UInt16                 usParentFieldId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildPointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Child Linking Information                                    */
    /*! \{                                                                 */
    
    void setEnclosingObject(FieldContainer * const pObj           );
    void setChildFieldId   (UInt16           const childFieldId   );
    void setParentFieldId  (UInt16           const usParentFieldId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
  
    FieldContainer *_pEnclosingObj;
    UInt16          _childFieldId;
    UInt16          _usParentFieldId;
  
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private: 

    template<typename RefCountPolicyT>
    friend class ChildAccessHandler;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ChildPointerSFieldBase(const Self &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator = (const Self &source);
};

OSG_END_NAMESPACE

#include "OSGChildPointerSFieldBase.inl"

#endif // _OSGCHILDPOINTERSFIELDBASE_H_
