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

#ifndef _OSGSFIELD_H_
#define _OSGSFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGField.h"
#include "OSGFieldTraits.h"
#include "OSGFieldType.h"
#include "OSGFieldHandle.h"
#include "OSGFieldDescFactory.h"

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

/*! Base class for all single fields, for example SFMatrix.
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
    \ingroup GrpLibOSGBase 
 */

template<class ValueT, Int32 iNamespace = 0>
class SField : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          FieldTraits      <ValueT, iNamespace>  SFieldTraits;
    typedef          SField           <ValueT, iNamespace>  Self;

    typedef          ValueT                                 StoredType;
    typedef          ValueT                                &reference;
    typedef const    ValueT                                &const_reference;

    typedef typename SFieldTraits::ArgumentType             ArgumentType;

    typedef          FieldDescription<
                         SFieldTraits,
                         FieldType::SingleField  >          Description;

    typedef          EditSFieldHandle <Self      >          EditHandle;
    typedef          boost::shared_ptr<EditHandle>          EditHandlePtr;


    typedef          GetSFieldHandle  <Self     >           GetHandle;
    typedef          boost::shared_ptr<GetHandle>           GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32            Namespace     = iNamespace;

    static const bool             isSField       = true;
    static const bool             isMField       = false;

    static const bool             isPointerField = false;

    static const FieldType::Class Class          = FieldType::ValueField;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             SField(void                     );
             SField(const SField       &obj  );
    explicit SField(      ArgumentType  value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~SField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          reference getValue(void);
    const_reference getValue(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setValue           (      ArgumentType  value);
    void setValue           (const Self         &obj  );

    void setValueFromCString(const Char8        *str  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Push                                    */
    /*! \{                                                                 */

    void pushValueToString  (std::string  &str) const;
    void pushValueFromStream(std::istream &str);
    void pushValueToStream  (OutStream    &str) const;
    void pushSizeToStream   (OutStream    &str) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;
    
    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith(Self &source);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Compare                                 */
    /*! \{                                                                 */

    bool operator ==(const SField &source) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assign                                  */
    /*! \{                                                                 */

    void operator =(const SField &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:


    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef Field Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType _fieldType;
     
           ValueT    _fieldValue;

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    static FieldDescriptionBase *
        createFieldDescription   (const Char8                *szFieldname,
                                        UInt32                uiFieldFlags,
                                        FieldEditMethod       fEditMethod,
                                        FieldGetMethod        fGetMethod  );

    static FieldDescriptionBase *
        createIdxFieldDescription(const Char8                *szFieldname,
                                        UInt32                uiFieldFlags,
                                        FieldIndexEditMethod  fEditMethod,
                                        FieldIndexGetMethod   fGetMethod  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#include "OSGSField.inl"

#endif /* _OSGSFIELD_H_ */
