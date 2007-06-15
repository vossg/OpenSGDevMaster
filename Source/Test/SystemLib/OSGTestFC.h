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

#ifndef _OSGTESTFC_H_
#define _OSGTESTFC_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMatrix.h"
#include "OSGFieldContainer.h"
#include "OSGAttachmentContainer.h"

#include "OSGUInt32Fields.h"

#include "OSGContainerPtrFuncs.h"
#include "OSGFieldContainerFactory.h"

OSG_BEGIN_NAMESPACE

//! Brief
//! \ingroup baselib

class OSG_SYSTEM_DLLMAPPING TestFC : public AttachmentContainer
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef AttachmentContainer                     Inherited;
    typedef AttachmentContainer                     ParentContainer;

    typedef PointerBuilder<TestFC>::ObjPtr          ObjPtr;
    typedef PointerBuilder<TestFC>::ObjConstPtr     ObjConstPtr;

    typedef Inherited::TypeObject                   TypeObject;
    
    typedef TestFC                                  Self;

    OSG_RC_FIRST_FIELD_DECL(Field1        );
    
    OSG_RC_FIELD_DECL      (Field2, Field1);
    OSG_RC_FIELD_DECL      (Field3, Field2);

    OSG_RC_LAST_FIELD_DECL (Field3        );

    static const BitVector bLocalFieldMask   = (Field1FieldMask |
                                                Field2FieldMask |
                                                Field3FieldMask );

    static const BitVector bInvLocalFieldMask = ~bLocalFieldMask;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_DECL;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual 
    void pushToField     (       FieldContainerPtrConstArg pNewElement, 
                           const UInt32                    uiFieldId );

    virtual 
    void insertIntoMField(const UInt32                    uiIndex, 
                                FieldContainerPtrConstArg pNewElement, 
                          const UInt32                    uiFieldId  );

    virtual 
    void replaceInMField (const UInt32                    uiIndex,
                                FieldContainerPtrConstArg pNewElement, 
                          const UInt32                    uiFieldId  );

    virtual 
    void replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                FieldContainerPtrConstArg pNewElement, 
                          const UInt32                    uiFieldId  );

    virtual 
    void removeFromMField(const UInt32                    uiIndex, 
                          const UInt32                    uiFieldId  );
    
    virtual 
    void removeFromMField(      FieldContainerPtrConstArg pElement, 
                          const UInt32                    uiFieldId  );

    virtual 
    void clearField      (const UInt32                    uiFieldId  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

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

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

          MFUInt32 *editMFField1(void);
    const MFUInt32 *getMFField1 (void) const;

          SFUInt32 *editSFField2(void);
    const SFUInt32 *getSFField2 (void) const;

          MFUInt32 *editMFField3(void);
    const MFUInt32 *getMFField3 (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    MFUInt32 _mfField1;
    SFUInt32 _sfField2;
    MFUInt32 _mfField3;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    TestFC(void);
    TestFC(const TestFC &source);

    virtual ~TestFC(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual void onDestroyAspect(UInt32 uiContainerId,
                                 UInt32 uiAspect     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjPtr createAspectCopy(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    OSG_SYSTEM_DLLMAPPING 
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

    OSG_SYSTEM_DLLMAPPING 
            void execSync (      TestFC            *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    friend class PointerFuncs;
    friend class CPointerFuncs;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TestFC &source);
};

typedef TestFC::ObjPtr      TestFCPtr;
typedef TestFC::ObjConstPtr TestFCConstPtr;

OSG_END_NAMESPACE

#include "OSGTestFC.inl"

#endif /* _OSGTESTFC_H_ */
