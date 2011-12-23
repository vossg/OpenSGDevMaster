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

#include "OSGSysFields.h" // Step type
#include "OSGBaseFields.h"

OSG_BEGIN_NAMESPACE

//! \brief Real32Counter Base Class.

template<class Desc>
class SValueEmitter : public NodeCore
{
  public:

    typedef NodeCore      Inherited;
    typedef NodeCore      ParentContainer;
    typedef SValueEmitter Self;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Self);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        TriggerFieldId          = Inherited::NextFieldId,
        ValueFieldId            = TriggerFieldId + 1,
        IgnoreNextChangeFieldId = ValueFieldId + 1,
        NextFieldId             = IgnoreNextChangeFieldId + 1
    };

    static const OSG::BitVector TriggerFieldMask =
        (TypeTraits<BitVector>::One << TriggerFieldId);

    static const OSG::BitVector ValueFieldMask =
        (TypeTraits<BitVector>::One << ValueFieldId);

    static const OSG::BitVector IgnoreNextChangeFieldMask =
        (TypeTraits<BitVector>::One << IgnoreNextChangeFieldId);

    typedef typename Desc::SFValueType       SFValueType;
    typedef typename SFValueType::StoredType ValueType;

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


          SFValueType *editSFValue           (void);
    const SFValueType *getSFValue            (void) const;

          ValueType   &editValue             (void);
          ValueType    getValue              (void) const;

          SFBool      *editSFIgnoreNextChange(void);
    const SFBool      *getSFIgnoreNextChange (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setValue(const ValueType value);

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

    virtual SizeT  getBinSize (ConstFieldMaskArg  whichField);
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

    SFOSGAny    _sfTrigger;
    SFValueType _sfValue;
    SFBool      _sfIgnoreNextChange;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SValueEmitter(void);
    SValueEmitter(const SValueEmitter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SValueEmitter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

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
    void operator =(const SValueEmitter &source);
};

struct BoolEmitterDesc
{
    typedef SFBool SFValueType;

    static const Char8 *getClassname(void)
    {
        return "BoolEmitter";
    }

    static bool getDefault(void)
    {
        return true;
    }
};

struct Int32EmitterDesc
{
    typedef SFInt32 SFValueType;

    static const Char8 *getClassname(void)
    {
        return "Int32Emitter";
    }

    static Int32 getDefault(void)
    {
        return 0;
    }
};

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
typedef SValueEmitter<Int32EmitterDesc > Int32Emitter;
typedef SValueEmitter<Real32EmitterDesc> Real32Emitter;
typedef SValueEmitter<StringEmitterDesc> StringEmitter;

OSG_END_NAMESPACE

#include "OSGValueEmitter.inl"

#endif /* _OSGVALUEEMITTER_H_ */
