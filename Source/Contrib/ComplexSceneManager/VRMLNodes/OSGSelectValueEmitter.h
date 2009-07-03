/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGVALUEEMITTER_H_
#define _OSGVALUEEMITTER_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGCounter.h" // Parent

#include "OSGMathFields.h" // Step type
#include "OSGSysFields.h"
#include "OSGMaterialMapFields.h"

OSG_BEGIN_NAMESPACE

//! \brief Real32Counter Base Class.

template<class Desc>
class SelectSValueEmitter : public NodeCore
{
  public:

    typedef NodeCore            Inherited;
    typedef NodeCore            ParentContainer;
    typedef SelectSValueEmitter Self;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Self);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        TriggerFieldId          = Inherited::NextFieldId,
        ChoiceFieldId           = TriggerFieldId + 1,
        ChoiceValuesFieldId     = ChoiceFieldId + 1,
        ValueFieldId            = ChoiceValuesFieldId + 1,
        IgnoreNextChangeFieldId = ValueFieldId + 1,
        NextFieldId             = IgnoreNextChangeFieldId + 1
    };

    static const OSG::BitVector TriggerFieldMask =
        (TypeTraits<BitVector>::One << TriggerFieldId);

    static const OSG::BitVector ChoiceFieldMask =
        (TypeTraits<BitVector>::One << ChoiceFieldId);

    static const OSG::BitVector ChoiceValuesFieldMask =
        (TypeTraits<BitVector>::One << ChoiceValuesFieldId);

    static const OSG::BitVector ValueFieldMask =
        (TypeTraits<BitVector>::One << ValueFieldId);

    static const OSG::BitVector IgnoreNextChangeFieldMask =
        (TypeTraits<BitVector>::One << IgnoreNextChangeFieldId);

    typedef          SFUInt32                       SFChoiceType;
    typedef          SFUInt32::StoredType           ChoiceType;

    typedef typename Desc::MFChoiceValuesType       MFChoiceValuesType;
    typedef typename MFChoiceValuesType::StoredType ChoiceValuesType;

    typedef typename Desc::SFValueType              SFValueType;
    typedef typename SFValueType::StoredType        ValueType;
    
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static       FieldContainerType &getClassType   (void);
    static       UInt32              getClassTypeId (void);
    static       UInt16              getClassGroupId(void);
    static const Char8              *getClassname   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType         (void);
    virtual const FieldContainerType &getType         (void) const;

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

          SFChoiceType        *editSFChoice         (      void        );
    const SFChoiceType        *getSFChoice          (      void        ) const;

          ChoiceType          &editChoice           (      void        );
          ChoiceType           getChoice            (      void        ) const;


          MFChoiceValuesType *editMFChoiceValues    (      void        );
    const MFChoiceValuesType *getMFChoiceValues     (      void        ) const;

          ChoiceValuesType   &editChoiceValue       (const UInt32 index);
          ChoiceValuesType    getChoiceValue        (const UInt32 index) const;


          SFValueType        *editSFValue           (      void        );
    const SFValueType        *getSFValue            (      void        ) const;

          ValueType          &editValue             (      void        );
          ValueType           getValue              (      void        ) const;


          SFBool             *editSFIgnoreNextChange(      void        );
    const SFBool             *getSFIgnoreNextChange (      void        ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setChoice(const ChoiceType choice);
    void setValue (const ValueType  value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  ObjTransitPtr  create          (void                           );
    static  Self          *createEmpty     (void                           );

    static  ObjTransitPtr  createLocal     (BitVector bFlags = FCLocal::All);
    static  ObjTransitPtr  createDependent (BitVector bFlags = FCLocal::All);

    static  Self          *createEmptyLocal(BitVector bFlags = FCLocal::All);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerTransitPtr shallowCopy     (void) const;
    virtual FieldContainerTransitPtr shallowCopyLocal(
                                       BitVector bFlags = FCLocal::All) const;
    virtual FieldContainerTransitPtr shallowCopyDependent(
                                       BitVector bFlags               ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static void classDescInserter(TypeObject &oType);

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFOSGAny           _sfTrigger;
    SFChoiceType       _sfChoice;
    MFChoiceValuesType _mfChoiceValues;
    SFValueType        _sfValue;
    SFBool             _sfIgnoreNextChange;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SelectSValueEmitter(void);
    SelectSValueEmitter(const SelectSValueEmitter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SelectSValueEmitter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleChoice           (void) const;
    EditFieldHandlePtr editHandleChoice          (void);

    GetFieldHandlePtr  getHandleChoiceValues     (void) const;
    EditFieldHandlePtr editHandleChoiceValues    (void);
    
    GetFieldHandlePtr  getHandleValue            (void) const;
    EditFieldHandlePtr editHandleValue           (void);

    GetFieldHandlePtr  getHandleIgnoreNextChange (void) const;
    EditFieldHandlePtr editHandleIgnoreNextChange(void);

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

            void execSync (      Self              *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainer *createAspectCopy(
                                      const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;

    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SelectSValueEmitter &source);
};

struct SelectInt32EmitterDesc
{
    typedef MFInt32 MFChoiceValuesType;
    typedef SFInt32 SFValueType;

    static const Char8 *getClassname(void)
    {
        return "SelectInt32Emitter";
    }

    static Int32 getDefault(void)
    {
        return 0;
    }

    static Int32 convert(const Int32 iVal)
    {
        return iVal;
    }
};

struct SelectMaterialKeyEmitterDesc
{
    typedef MFString         MFChoiceValuesType;
    typedef SFMaterialMapKey SFValueType;

    static const Char8 *getClassname(void)
    {
        return "SelectMaterialKeyEmitter";
    }

    static MaterialMapKey getDefault(void)
    {
        return 0x0000;
    }

    static MaterialMapKey convert(const std::string &szVal)
    {
        MaterialMapKey returnValue = 
            RenderPropertiesPool::the()->getAuto(szVal.c_str());

        return returnValue;
    }
};

#if 0
struct Real32EmitterDesc
{
    typedef SFReal32 SFValueType;

    static const Char8 *getClassname(void)
    {
        return "Real32Emitter";
    }

    static Real32 getDefault(void)
    {
        return 0.f;
    }
};

struct StringEmitterDesc
{
    typedef SFString SFValueType;

    static const Char8 *getClassname(void)
    {
        return "StringEmitter";
    }

    static std::string getDefault(void)
    {
        return std::string();
    }
};

typedef SValueEmitter<BoolEmitterDesc  > BoolEmitter;
typedef SValueEmitter<Real32EmitterDesc> Real32Emitter;
typedef SValueEmitter<StringEmitterDesc> StringEmitter;
#endif

typedef SelectSValueEmitter<
            SelectInt32EmitterDesc       > SelectInt32Emitter;
typedef SelectSValueEmitter<
            SelectMaterialKeyEmitterDesc > SelectMaterialKeyEmitter;

OSG_END_NAMESPACE

#include "OSGSelectValueEmitter.inl"

#endif /* _OSGSELECTVALUEEMITTER_H_ */
