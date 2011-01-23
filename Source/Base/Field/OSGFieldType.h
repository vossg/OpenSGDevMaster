/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGFIELDTYPE_H_
#define _OSGFIELDTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <typeinfo>
#include "OSGDataType.h"
#include "OSGFieldForwards.h"

OSG_BEGIN_NAMESPACE

class Field;

#ifdef OSG_1_GET_COMPAT
#define SINGLE_FIELD SingleField
#define MULTI_FIELD  MultiField
#endif

/*! \ingroup GrpBaseField
    \ingroup GrpLibOSGBase 
 */

class OSG_BASE_DLLMAPPING FieldType : public DataType
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum Cardinality 
    { 
        SingleField,
        MultiField
    };

    
    enum Class
    {
        ValueField,
        PtrField,
        ParentPtrField,
        ChildPtrField
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldType(const Char8                   *szName, 
              const Char8                   *szParentName,
              const DataType                &contentType,
                    Cardinality              cardinality,
                    Class                    fieldClass,
                    FieldDescCreator         fCreator    = NULL,
                    IndexedFieldDescCreator  fIdxCreator = NULL,
              const UInt32                   uiNameSpace = GlobalNamespace);

    FieldType(const Char8                   *szName, 
              const Char8                   *szParentName,
              const DataType                &contentType ,
                    Cardinality              cardinality ,
                    Class                    fieldClass,
              const FieldType               &pScanAsType,
                    FieldDescCreator         fCreator    = NULL,
                    IndexedFieldDescCreator  fIdxCreator = NULL,
              const UInt32                   uiNameSpace = GlobalNamespace);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Is                                      */
    /*! \{                                                                 */

//    bool isFieldContainerPtrField(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const DataType    &getContentType(void) const;
          Cardinality  getCardinality(void) const;
          Class        getClass      (void) const;

          UInt32       getScanTypeId (void) const;
          bool         isPtrField    (void) const;

    /*! \}                                                                 */

#if defined(OSG_STATIC_MEMEBER_NEEDS_COPY_ASIGN_INIT)
    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldType(const FieldType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldType &operator =(const FieldType &obj);
#endif

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef DataType Inherited;

    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

          Cardinality  _cardinality;
          UInt32       _uiLoadTypeId;
          Class        _fieldClass;

    const DataType    &_contentType;
    const FieldType   *_pScanAsType;

    /*==========================  PRIVATE  ================================*/

  private:

#if !defined(OSG_STATIC_MEMEBER_NEEDS_COPY_ASIGN_INIT)
    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldType(const FieldType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldType &operator =(const FieldType &obj);
#endif
};

OSG_END_NAMESPACE

#include "OSGFieldType.inl"

#endif /* _OSGFIELDTYPE_H_ */



