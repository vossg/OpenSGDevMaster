/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGFIELDDESCRIPTIONBASE_H_
#define _OSGFIELDDESCRIPTIONBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/function.hpp>
#include <boost/functional.hpp>

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGFieldType.h"
#include "OSGContainerForwards.h"
#include "OSGField.h"

OSG_BEGIN_NAMESPACE

class Field;

#if 0
typedef       Field *(ReflexiveContainer::*FieldEditMethodSig)(void);
typedef const Field *(ReflexiveContainer::*FieldGetMethodSig )(void) const;

typedef       Field *(ReflexiveContainer::*FieldIndexEditMethodSig)(UInt32);
typedef const Field *(
    ReflexiveContainer::*FieldIndexGetMethodSig )(UInt32) const;
#endif

typedef 
    EditFieldHandlePtr(ReflexiveContainer::*FieldEditMethodSig)(void);
typedef 
    GetFieldHandlePtr (ReflexiveContainer::*FieldGetMethodSig )(void) const;


typedef EditFieldHandlePtr (ReflexiveContainer::*FieldIndexEditMethodSig)(
    UInt32);
typedef GetFieldHandlePtr  (ReflexiveContainer::*FieldIndexGetMethodSig )(
    UInt32) const;

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifdef FDESC_USE_BOOST
typedef boost::function<Field *(ReflexiveContainer *)> FieldEditMethod;
#else
#if 0
typedef Field              *(ReflexiveContainer::*FieldEditMethod  )(void  );
#endif
typedef EditFieldHandlePtr (ReflexiveContainer::*FieldEditMethod)(void  );
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifdef FDESC_USE_BOOST
typedef boost::function<
          const Field *(const ReflexiveContainer *)> FieldGetMethod;
#else
#if 0
typedef 
    const Field      *(ReflexiveContainer::*FieldGetMethod  )(void  ) const;
#endif
typedef GetFieldHandlePtr (ReflexiveContainer::*FieldGetMethod)(void) const;
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifdef FDESC_USE_BOOST
typedef boost::function<
          Field *(ReflexiveContainer *, int)>             FieldIndexEditMethod;
#else
#if 0
typedef 
    Field              *(ReflexiveContainer::*FieldIndexEditMethod)(UInt32);
#endif
typedef EditFieldHandlePtr (ReflexiveContainer::*FieldIndexEditMethod)(UInt32);
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifdef FDESC_USE_BOOST
typedef boost::function<
          const Field *(const ReflexiveContainer *, int)> FieldIndexGetMethod;
#else
#if 0
typedef const Field       *(ReflexiveContainer::*FieldIndexGetMethod  )(
    UInt32) const;
#endif
typedef GetFieldHandlePtr (ReflexiveContainer::*FieldIndexGetMethod)(
    UInt32) const;
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

class OSG_SYSTEM_DLLMAPPING FieldDescriptionBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef std::vector<      std::string         > StringVector;
    typedef std::vector<const FieldContainerType *> TypePtrVector;
    typedef std::vector<      UInt16              > TypeIdVector;

    typedef FieldContainerPtrConstArg               FCPtrConstArg;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldDescriptionBase(const FieldType       &elementType,
                         const Char8           *szName,
                         const std::string      fieldDocumentation,
                         const UInt32           uiFieldId,
                         const BitVector        vFieldMask,
                         const bool             bInternal,
                         const UInt32           uiFieldFlags,
                               FieldEditMethod  fEditMethod,
                               FieldGetMethod   fGetMethod,
                         const Char8           *defaultValue = NULL);

    FieldDescriptionBase(const FieldType            &elementType,
                         const Char8                *szName,
                         const std::string           fieldDocumentation,
                         const UInt32                uiFieldId,
                         const BitVector             vFieldMask,
                         const bool                  bInternal,
                         const UInt32                uiFieldFlags,
                               FieldIndexEditMethod  fIndexedEditMethod,
                               FieldIndexGetMethod   fIndexedGetMethod,
                         const Char8                *defaultValue = NULL);

    FieldDescriptionBase(const FieldDescriptionBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldDescriptionBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    const Char8       *getCName       (void                        ) const;
          std::string  getName        (void                        ) const;

          std::string  getDocumentation (void                      ) const;

          UInt32       getTypeId      (void                        ) const;

          BitVector    getFieldMask   (void                        ) const;
          void         setFieldMask   (ConstFieldMaskArg vFieldMask);

          UInt32       getFieldId     (void                        ) const;
          void         setFieldId     (UInt32 uiFieldId            );

    const Char8       *getDefaultValue(void                        ) const;

    const FieldType   &getFieldType   (void                        ) const;

          bool         isInternal     (void                        ) const;

          UInt32       getFlags       (void                        ) const;

          bool         isValid        (void                        ) const;

          bool         isSField       (void                        ) const;
          bool         isMField       (void                        ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    EditFieldHandlePtr editField(      ReflexiveContainer &oContainer) const;
    GetFieldHandlePtr  getField (const ReflexiveContainer &oContainer) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Set from String                             */
    /*! \{                                                                 */

#if 0
    virtual void pushValueFromCString(const Char8        *str,
                                            Field        *pField) const;

    virtual void pushValueFromCString(const Char8        *str,
                                            Field        *pField) const = 0;

    virtual void pushValueToCString  (const Field        *pField,
                                            Char8        *str   ) const = 0;


    virtual void pushValueFromString (const std::string  &in,
                                            Field        *pField) const = 0;

    virtual void pushValueToString   (const Field        *pField,
                                            std::string  &out   ) const = 0;


    virtual void pushValueFromStream (      std::istream &str,
                                            Field        *pField) const = 0;

    virtual void pushValueToStream   (const Field        *pField,
                                            OutStream    &str   ) const = 0;

    virtual void pushSizeToStream    (const Field        *pField,
                                            OutStream    &str   ) const = 0;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Set from Field                           */
    /*! \{                                                                 */

#if 0
    virtual void copyValues  (const Field *pSrc,
                                    Field *pDst  ) const;
    virtual void copyValues  (const Field *pSrc,
                                    Field *pDst  ) const = 0;

    virtual void cloneValuesV(
        const Field         *pSrc,
        const UInt32         fieldId,
              FCPtrConstArg  pDst,
        const TypePtrVector &shareTypes     = TypePtrVector(),
        const TypePtrVector &ignoreTypes    = TypePtrVector(),
        const TypeIdVector  &shareGroupIds  = TypeIdVector (),
        const TypeIdVector  &ignoreGroupIds = TypeIdVector ()) const;

    virtual void shareValuesV(
        const Field         *pSrc,
        const UInt32         fieldId,
              FCPtrConstArg  pDst,
        const TypePtrVector &cloneTypes     = TypePtrVector(),
        const TypePtrVector &ignoreTypes    = TypePtrVector(),
        const TypeIdVector  &cloneGroupIds  = TypeIdVector (),
        const TypeIdVector  &ignoreGroupIds = TypeIdVector ()) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */
#endif

    virtual Field *createField(void          ) const = 0;
    virtual void   destroyField(Field *pField) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    virtual FieldDescriptionBase *clone(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    virtual GetFieldHandlePtr  createGetHandler (const Field *pField) = 0;
    virtual EditFieldHandlePtr createEditHandler(      Field *pField) = 0;

#if 0
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual bool equal(const Field *lhs,
                       const Field *rhs) const = 0;

#endif


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

          std::string           _szName;
          std::string           _documentation; 

    const FieldType            &_fieldType;

          UInt32                _uiFieldId;
          BitVector             _vFieldMask;

          bool                  _bInternal;
          UInt32                _uiFieldFlags;

          FieldEditMethod       _fEditMethod;
          FieldGetMethod        _fGetMethod;
          FieldIndexGetMethod   _fIndexedGetMethod;
          FieldIndexEditMethod  _fIndexedEditMethod;

          IDString              _defaultValue;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldDescriptionBase &source);
};

//---------------------------------------------------------------------------
//   Class
//---------------------------------------------------------------------------

/*! FieldDescriptionBase point less than
    \ingroup GrpSystemFieldContainerFuncs
    \hideinhierarchy
 */

struct FieldDescriptionBasePLT
{
    bool operator()(const FieldDescriptionBase *pElemDesc1,
                    const FieldDescriptionBase *pElemDesc2) const;
};


OSG_END_NAMESPACE

#include "OSGFieldDescriptionBase.inl"

#endif /* _OSGFIELDDESCRIPTIONBASE_H_ */
