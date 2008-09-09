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

    OSG_GEN_INTERNALPTR(TestFC);

    typedef Inherited::TypeObject                   TypeObject;
    
    typedef TestFC                                  Self;

    OSG_RC_FIRST_FIELD_DECL(Field1        );
    
    OSG_RC_FIELD_DECL      (Field2, Field1);
    OSG_RC_FIELD_DECL      (Field3, Field2);
    OSG_RC_FIELD_DECL      (Field4, Field3);

    OSG_RC_LAST_FIELD_DECL (Field4        );

    static const BitVector bLocalFieldMask   = (Field1FieldMask |
                                                Field2FieldMask |
                                                Field3FieldMask |
                                                Field4FieldMask );

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
                         UInt32            origin,
                         BitVector         detail);

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

          SFUInt32 *editSFField4(void);
    const SFUInt32 *getSFField4 (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    MFUInt32 _mfField1;
    SFUInt32 _sfField2;
    MFUInt32 _mfField3;
    SFUInt32 _sfField4;

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
    virtual ObjCPtr createAspectCopy(const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

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

    MFUInt32::EditHandlePtr editHandleField1(void);
    MFUInt32::GetHandlePtr  getHandleField1 (void) const;

    SFUInt32::EditHandlePtr editHandleField2(void);
    SFUInt32::GetHandlePtr  getHandleField2 (void) const;

    MFUInt32::EditHandlePtr editHandleField3(void);
    MFUInt32::GetHandlePtr  getHandleField3 (void) const;

    SFUInt32::EditHandlePtr editHandleField4(void);
    SFUInt32::GetHandlePtr  getHandleField4 (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TestFC &source);
};

typedef TestFC::ObjUnrecPtr TestFCUnrecPtr;

OSG_END_NAMESPACE

#include "OSGTestFC.inl"

#endif /* _OSGTESTFC_H_ */
