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

#ifndef _OSGREFLEXIVECONTAINER_H_
#define _OSGREFLEXIVECONTAINER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGReflexiveContainerType.h"
#include "OSGContainerBase.h"
#include "OSGContainerDefines.h"
#include "OSGField.h"
#include "OSGFieldType.h"
#include "OSGBinaryDataHandler.h"
#include "OSGThread.h"
#include "OSGChangeList.h"

#include "OSGSystemDef.h"

OSG_BEGIN_NAMESPACE

class FieldContainerPtrBase;
class FieldDesciptionBase;

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! FieldDescriptionBase point less than
    \ingroup GrpSystemFieldContainerFuncs
    \hideinhierarchy
 */

class OSG_SYSTEM_DLLMAPPING FieldHandle
{
  private:

    void operator =(const FieldHandle &source);

  protected:

          Field                *_pField;
    const FieldDescriptionBase *_pDescription;

  public:

    FieldHandle(const FieldHandle          &source);

    FieldHandle(const Field                *pField, 
                const FieldDescriptionBase *pDescription);


    ~FieldHandle(void);


    bool                   isInternal    (void) const;
    bool                   isValid       (void) const;

    FieldType::Cardinality getCardinality(void) const;


    const FieldType &getType (void) const;
    const Field     *getField(void) const;

    const IDString  &getName (void) const;



    void pushValueToStream(OutStream &str) const;
    void pushSizeToStream (OutStream &str) const;
};

class OSG_SYSTEM_DLLMAPPING EditFieldHandle : public FieldHandle
{
  private:
    
    void operator =(const EditFieldHandle &source);

  protected:

    typedef FieldHandle Inherited;

  public:

    EditFieldHandle(const EditFieldHandle      &source);
    EditFieldHandle(      Field                *pField, 
                    const FieldDescriptionBase *pDescription);


    ~EditFieldHandle(void);
};

/*! \ingroup GrpSystemFieldContainer
 */

class ReflexiveContainer 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Type definitions                          */
    /*! \{                                                                 */
    
    typedef ReflexiveContainerType TypeObject;
    typedef TypeObject::InitPhase  InitPhase;

typedef       Field *(ReflexiveContainer::*FieldEditMethod)(void);

typedef const Field *(ReflexiveContainer::*FieldGetMethod )(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Constants                               */
    /*! \{                                                                 */

    static const UInt32    NextFieldId   =    1;
    static const BitVector NextFieldMask = 0x01;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Get Class Type Information                       */
    /*! \{                                                                 */
     
    static OSG_SYSTEM_DLLMAPPING TypeObject &getClassType   (void); 
    static OSG_SYSTEM_DLLMAPPING UInt32      getClassTypeId (void);
    static OSG_SYSTEM_DLLMAPPING UInt16      getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    virtual       TypeObject &getType    (void);

    OSG_SYSTEM_DLLMAPPING 
    virtual const TypeObject &getType    (void) const;

    OSG_SYSTEM_DLLMAPPING 
                  UInt32      getTypeId  (void) const;

    OSG_SYSTEM_DLLMAPPING
                  UInt16      getGroupId (void) const;

    OSG_SYSTEM_DLLMAPPING 
            const Char8      *getTypeName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    virtual UInt32 getContainerSize(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, UInt32 origin) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Field                                   */
    /*! \{                                                                 */


    OSG_SYSTEM_DLLMAPPING
          UInt32  getNumFields(      void            ) const;

    OSG_SYSTEM_DLLMAPPING 
          Field  *editField   (      UInt32 fieldId  );
    
    OSG_SYSTEM_DLLMAPPING 
          Field  *editField   (const Char8 *fieldName);

    OSG_SYSTEM_DLLMAPPING 
    const Field  *getField    (      UInt32 fieldId  ) const;
    
    OSG_SYSTEM_DLLMAPPING 
    const Field  *getField    (const Char8 *fieldName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Field                                   */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    EditFieldHandle editHandledField(      UInt32 fieldId  );
    
    OSG_SYSTEM_DLLMAPPING 
    EditFieldHandle editHandledField(const Char8 *fieldName);

    OSG_SYSTEM_DLLMAPPING 
    FieldHandle     getHandledField (      UInt32 fieldId  ) const;
    
    OSG_SYSTEM_DLLMAPPING 
    FieldHandle     getHandledField (const Char8 *fieldName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Get Field Description                        */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    FieldDescriptionBase *getFieldDescription(      UInt32 fieldId  );
    
    OSG_SYSTEM_DLLMAPPING 
    FieldDescriptionBase *getFieldDescription(const Char8 *fieldName);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    virtual UInt32  getBinSize (ConstFieldMaskArg   whichField);

    OSG_SYSTEM_DLLMAPPING 
    virtual void    copyToBin  (BinaryDataHandler  &pMem, 
                                ConstFieldMaskArg   whichField);

    OSG_SYSTEM_DLLMAPPING 
    virtual void    copyFromBin(BinaryDataHandler  &pMem, 
                                ConstFieldMaskArg   whichField);

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

    OSG_SYSTEM_DLLMAPPING 
          Field *invalidEditField(void);

    OSG_SYSTEM_DLLMAPPING 
    const Field *invalidGetField (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    ReflexiveContainer(void);

    OSG_SYSTEM_DLLMAPPING 
    ReflexiveContainer(const ReflexiveContainer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    virtual ~ReflexiveContainer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */
    
    BitVector             _bvChanged;
    ContainerChangeEntry *_pContainerChanges;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
            void onCreate       (const ReflexiveContainer *source = NULL);

    OSG_SYSTEM_DLLMAPPING
    virtual void onDestroy      (      UInt32              uiContainerId);

    OSG_SYSTEM_DLLMAPPING
    virtual void onDestroyAspect(      UInt32              uiContainerId,
                                       UInt32              uiAspect     );

    OSG_SYSTEM_DLLMAPPING
    virtual void resolveLinks   (      void                             );

    OSG_SYSTEM_DLLMAPPING       
    virtual bool deregister     (      UInt32              uiContainerId) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    virtual void registerChangedContainerV(void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    void                  execEndEdit   (ConstFieldMaskArg whichField);

    ContainerChangeEntry *getChangeEntry(void                        );
    void                  setChangeEntry(ContainerChangeEntry *pEntry);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainerPtrBase;
    friend class ChangeList;
    friend struct ContainerChangeEntry;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ReflexiveContainer &source);
};

#define OSG_RC_FIRST_FIELD_DECL(OSG_ELEMNAME)                                 \
    static const OSG::UInt32                                                  \
        OSG_ELEMNAME##FieldId   = Inherited::NextFieldId;                     \
    static const OSG::BitVector                                               \
        OSG_ELEMNAME##FieldMask =                                             \
                        (TypeTraits<BitVector>::One << OSG_ELEMNAME##FieldId)

#define OSG_RC_FIELD_DECL(OSG_ELEMNAME, OSG_PREV_ELEMNAME)                    \
    static const OSG::UInt32    OSG_ELEMNAME##FieldId   =                     \
        OSG_PREV_ELEMNAME##FieldId + 1;                                       \
    static const OSG::BitVector                                               \
        OSG_ELEMNAME##FieldMask =                                             \
                        (TypeTraits<BitVector>::One << OSG_ELEMNAME##FieldId)

#define OSG_RC_LAST_FIELD_DECL(OSG_PREV_ELEMNAME)                             \
  static const OSG::UInt32    NextFieldId   = OSG_PREV_ELEMNAME##FieldId + 1; \
  static const OSG::BitVector NextFieldMask =                                 \
                         (TypeTraits<BitVector>::One << NextFieldId)

#define OSG_RC_NO_FIELD_DECL                                                  \
  static const OSG::UInt32    NextFieldId   = Inherited::NextFieldId;         \
  static const OSG::BitVector NextFieldMask = Inherited::NextFieldMask

#define OSG_RC_FIELD_DESC(OSG_FIELDNAME)                                      \
    OSG_FIELDNAME##FieldId, OSG_FIELDNAME##FieldMask

OSG_END_NAMESPACE

#define OSGREFLEXIVECONTAINER_HEADER_CVSID "@(#)$Id: $"

#include "OSGFieldDescriptionBase.h"
#include "OSGReflexiveContainer.inl"

#endif /* _OSGREFLEXIVECONTAINER_H_ */
