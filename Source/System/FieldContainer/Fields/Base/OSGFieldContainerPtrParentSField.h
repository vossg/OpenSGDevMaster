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

#ifndef _OSGFIELDCONTAINERPTRPARENTSFIELD_H_
#define _OSGFIELDCONTAINERPTRPARENTSFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerPtrSFieldBase.h"

#include "OSGFieldContainerFieldTraits.h"
#include <boost/function.hpp>  

OSG_BEGIN_NAMESPACE

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace     = 0>
class FieldContainerPtrParentSField : public FieldContainerPtrSFieldBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef       FieldTraits                  <ValueT, 
                                                iNamespace    > PtrSFieldTraits;

    typedef       FieldTraits                  <UInt16,  0    > PosSFieldTraits;

    typedef       FieldContainerPtrParentSField<ValueT, 
                                                RefCountPolicy,
                                                iNamespace    > Self;

    typedef       ValueT                                        StoredType;
    typedef const ValueT                                        const_reference;
  
    typedef const ValueT                                        ArgumentType;

    typedef       FieldDescription             <
                      PtrSFieldTraits,
                      FieldType::SingleField,
                      RefCountPolicy,
                      FieldType::ParentPtrField               > Description;

    typedef       EditFCPtrSFieldHandle        <Self          > EditHandle;
    typedef       boost::shared_ptr            <EditHandle    > EditHandlePtr;

    typedef       GetFCPtrSFieldHandle         <Self          > GetHandle;
    typedef       boost::shared_ptr            <GetHandle     > GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32            Namespace = iNamespace;

    static const FieldType::Class Class     = FieldType::ParentPtrField;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             FieldContainerPtrParentSField(void                     );
             FieldContainerPtrParentSField(const Self         &obj  );
    explicit FieldContainerPtrParentSField(      ArgumentType  value,
                                                 UInt16        uiPos = 0xFFFF);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrParentSField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const_reference getValue(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setValue           (      ArgumentType  value,
                                   UInt16        uiPos);
    void setValue           (const Self         &obj  );

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

    bool operator ==(const Self &source) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assign                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt16 _uiParentFieldPos;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef FieldContainerPtrSFieldBase Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

    template<class To>
          To &dcast(void);

    template<class To>
    const To &dcast(void) const;

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType            _fieldType;
     
#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef PtrSFieldTraits SFieldTraits;

    void operator =(const Self &source);
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerPtrParentSField.inl"
#endif

#endif /* _OSGFIELDCONTAINERPTRPARENTSFIELD_H_ */
