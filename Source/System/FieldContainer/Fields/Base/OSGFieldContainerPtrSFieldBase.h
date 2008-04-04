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

#ifndef _OSGFIELDCONTAINERPTRSFIELDBASE_H_
#define _OSGFIELDCONTAINERPTRSFIELDBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGSField.h"
#include "OSGFieldContainerFieldTraits.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING FieldContainerPtrSFieldBase : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef       FieldTraits      <FieldContainerPtr, 0>  SFieldTraits;
    typedef       FieldContainerPtrSFieldBase              Self;

    typedef       FieldContainerPtr                        StoredType;
    typedef       FieldContainerPtr                       &reference;
    typedef const FieldContainerPtr                        const_reference;

    typedef       FieldContainerPtr                        ArgumentType;

//    typedef       SFieldTraits::ArgumentType               ArgumentType;

//    typedef       FieldDescription<SFieldTraits,
//                                   SingleField        >    Description;


    typedef       EditSFieldHandle <Self      >            EditHandle;
    typedef       boost::shared_ptr<EditHandle>            EditHandlePtr;

    typedef       GetSFieldHandle  <Self     >             GetHandle;
    typedef       boost::shared_ptr<GetHandle>             GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32 Namespace = 0;

    static const bool isSField       = true;
    static const bool isMField       = false;

    static const bool isPointerField = true;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const_reference getValue(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize(void                   ) const;
    
    void   copyToBin (BinaryDataHandler &pMem) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Compare                                 */
    /*! \{                                                                 */

    bool operator ==(const Self &source) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef Field Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             FieldContainerPtrSFieldBase(void                     );
             FieldContainerPtrSFieldBase(const Self         &obj  );
    explicit FieldContainerPtrSFieldBase(      ArgumentType  value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrSFieldBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    reference getValue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

#if 0
    void setValue           (      ArgumentType  value);
    void setValue           (const Self         &obj  );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

//    void copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith(Self &source);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assign                                  */
    /*! \{                                                                 */

    void operator =(const Self &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType            _fieldType;
     
           FieldContainerPtr    _fieldValue;

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerPtrSFieldBase.inl"
#endif

#endif /* _OSGFIELDCONTAINERPTRSFIELDBASE_H_ */
