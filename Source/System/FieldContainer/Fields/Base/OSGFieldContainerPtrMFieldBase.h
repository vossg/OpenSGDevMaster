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

#ifndef _OSGFIELDCONTAINERMFIELDBASE_H_
#define _OSGFIELDCONTAINERMFIELDBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGMField.h"
#include "OSGFieldContainerFieldTraits.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING FieldContainerPtrMFieldBase : public Field
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef       MFieldVector<FieldContainerPtr>     StorageType;
    typedef       StorageType::Inherited              StorageTypeParent;

    typedef       StorageType::const_iterator         const_iterator;

    typedef const FieldContainerPtr                   const_reference;

    typedef       StorageType::size_type              size_type;

    typedef       FieldTraits<FieldContainerPtr, 0>   MFieldTraits;
 
    typedef       FieldContainerPtrMFieldBase         Self;

    typedef       FieldContainerPtr                   StoredType;
    typedef       FieldContainerPtr                   ArgumentType;

    typedef       EditMFieldHandle <Self      >       EditHandle;
    typedef       boost::shared_ptr<EditHandle>       EditHandlePtr;

    typedef       GetMFieldHandle  <Self     >        GetHandle;
    typedef       boost::shared_ptr<GetHandle>        GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const bool isSField       = false;
    static const bool isMField       = true;

    static const bool isPointerField = true;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;
    
    void   copyToBin  (BinaryDataHandler &pMem) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */

    const_iterator begin    (void              ) const;
    const_iterator end      (void              ) const;
    
    Int32          findIndex(ArgumentType value) const;

    size_type      size     (void              ) const;
    size_type      capacity (void              ) const;
    bool           empty    (void              ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Compare                                     */
    /*! \{                                                                 */

    bool operator ==(const Self &source) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

    void dump(      UInt32    uiIndent = 0, 
              const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void beginEdit      (UInt32              uiAspect,
                         AspectOffsetStore  &oOffsets    );

    Self *resolveShare  (UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    void  terminateShare(UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );

    bool  isShared      (void                            );
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef StorageType::iterator iterator;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef Field Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             FieldContainerPtrMFieldBase(void);
//    explicit FieldContainerPtrMFieldBase(const UInt32  size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrMFieldBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    void operator =(const Self &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static FieldType   _fieldType;

           StorageType _values;

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    FieldContainerPtrMFieldBase(const Self &obj);
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerPtrMFieldBase.inl"
#endif

#endif /* _OSGFIELDCONTAINERMFIELDBASE_H_ */
