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

#ifndef _OSGCHILDPOINTERMFIELDBASE_H_
#define _OSGCHILDPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerMFieldCommon.h"
#include "OSGChildAccessHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerMFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <typename AccessHandlerT,
          Int32    NamespaceI = 0>
class ChildPointerMFieldBase : 
    public PointerMFieldCommon<AccessHandlerT, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
    typedef       PointerMFieldCommon<AccessHandlerT,
                                      NamespaceI    > Inherited;

    typedef       ChildPointerMFieldBase              Self;

    typedef const FieldContainerPtr                   const_value;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ChildPointerMFieldBase(const FieldContainerPtr  pParent,
                                 UInt16             usChildFieldId,
                                 UInt16             usParentFieldId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildPointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Child Linking Information                                    */
    /*! \{                                                                 */
    
    FieldContainerPtr getEnclosingObject(      void                  ) const;
    void              setEnclosingObject(const FieldContainerPtr pObj);
    
    UInt16            getChildFieldId   (      void                  ) const;
    void              setChildFieldId   (const UInt16 childFieldId   );
    
    UInt16            getParentFieldId  (      void                  ) const;
    void              setParentFieldId  (const UInt16 parentFieldId  );
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
  
    FieldContainerPtr _pEnclosingObj;
    UInt16            _childFieldId;
    UInt16            _parentFieldId;
  
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private: 

    template<typename RefCountPolicyT>
    friend class ChildAccessHandler;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ChildPointerMFieldBase(const Self &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator = (const Self &source);
};

OSG_END_NAMESPACE

#include "OSGChildPointerMFieldBase.inl"

#endif // _OSGCHILDPOINTERMFIELDBASE_H_
