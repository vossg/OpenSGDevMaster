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

#ifndef _OSGFIELDCONTAINERPTRMFIELD_H_
#define _OSGFIELDCONTAINERPTRMFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerPtrMFieldBase.h"

#include "OSGFieldContainerFieldTraits.h"
#include <boost/function.hpp>  

OSG_BEGIN_NAMESPACE

template<class ValueT, Int32 iNamespace = 0>
class FieldContainerPtrMField : public FieldContainerPtrMFieldBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          MFieldVector <ValueT>                 StorageType;
    typedef typename StorageType::Inherited                StorageTypeParent;

    typedef typename StorageType::iterator                 iterator;
    typedef typename StorageType::const_iterator           const_iterator;

    typedef typename StorageType::reverse_iterator         reverse_iterator;
    typedef typename StorageType::const_reverse_iterator const_reverse_iterator;


    typedef typename StorageType::reference                reference;
    typedef typename StorageType::const_reference          const_reference;

    typedef          FieldTraits            <ValueT, 
                                             iNamespace>   MFieldTraits;
 
    typedef          FieldContainerPtrMField<ValueT, 
                                             iNamespace>   Self;

    typedef          ValueT                                StoredType;

    typedef typename MFieldTraits::ArgumentType            ArgumentType;

    typedef          FieldDescription       <MFieldTraits,
                                             MultiField,
                                             PtrField    > Description;

    typedef          EditFCPtrMFieldHandle  <Self        > EditHandle;
    typedef          boost::shared_ptr      <EditHandle  > EditHandlePtr;

    typedef          GetFCPtrMFieldHandle   <Self        > GetHandle;
    typedef          boost::shared_ptr      <GetHandle   > GetHandlePtr;

    /*---------------------------------------------------------------------*/

    static const Int32 Namespace     = iNamespace;

    static const bool isSField       = false;
    static const bool isMField       = true;

    static const bool isPointerField = true;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             FieldContainerPtrMField(void);
             FieldContainerPtrMField(const Self   &obj );
    explicit FieldContainerPtrMField(const UInt32  size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrMField(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          StorageType &getValues(void);
    const StorageType &getValues(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setValues          (const StorageType       &value);
    void setValues          (const StorageTypeParent &value);
    void setValues          (const Self              &obj  );
    
#if 0
    void addValueFromCString(const Char8             *str  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Push                                    */
    /*! \{                                                                 */

    void pushValuesToString  (std::string  &str) const;
    void pushValuesFromStream(std::istream &str);
    void pushValuesToStream  (OutStream    &str) const;
    void pushSizeToStream    (OutStream    &str) const;
#endif
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Interface                           */
    /*! \{                                                                 */

    void   copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   STL Interface                              */
    /*! \{                                                                 */

    iterator               begin    (void                              );
    iterator               end      (void                              );

    reverse_iterator       rbegin   (void                              );
    reverse_iterator       rend     (void                              );

    const_iterator         begin    (void                              ) const;
    const_iterator         end      (void                              ) const;
    
    const_reverse_iterator rbegin   (void                              ) const;
    const_reverse_iterator rend     (void                              ) const;

    reference              front    (void                              );
    const_reference        front    (void                              ) const;

    reference              back     (void                              );
    const_reference        back     (void                              ) const;
    
   
    iterator               insert   (iterator     pos, 
                                     ArgumentType value                );
#ifdef __STL_MEMBER_TEMPLATES
    template <class InputIterator>
    void                   insert   (iterator      pos, 
                                     InputIterator first, 
                                     InputIterator last                );
#else
    void                   insert   (iterator      pos, 
                                     iterator      first,
                                     iterator      last                );
#endif /* __STL_MEMBER_TEMPLATES */
 
    iterator               erase    (iterator     pos                  );
    
    iterator               find     (ArgumentType value                );
    const_iterator         find     (ArgumentType value                ) const;

    void                   push_back(ArgumentType value                );

    void                   resize   (size_t       newsize, 
                                     StoredType   t      = StoredType());
    void                   reserve  (size_t       newsize              );

    void                   swap     (Self                        &right);

#ifdef OSG_1_COMPAT
    void                   addValue (ArgumentType value                );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

          reference operator [](UInt32 index);
    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Compare                                     */
    /*! \{                                                                 */

    bool operator ==(const Self &source) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Assignment                                  */
    /*! \{                                                                 */

    void operator =(const Self &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      MT Sync                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith       (Self               &source, 
                         ConstFieldMaskArg   syncMode,
                         UInt32              uiSyncInfo,
                         AspectOffsetStore  &oOffsets    );
#endif

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

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef FieldContainerPtrMFieldBase Inherited;

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

    static FieldType   _fieldType;

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerPtrMField.inl"
#endif

#endif /* _OSGFIELDCONTAINERPTRMFIELD_H_ */
