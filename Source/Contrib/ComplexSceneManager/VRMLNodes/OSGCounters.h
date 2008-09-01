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

#ifndef _OSGCOUNTERS_H_
#define _OSGCOUNTERS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGBaseTypes.h"

#include "OSGCounter.h" // Parent

#include "OSGReal32Fields.h" // Step type

OSG_BEGIN_NAMESPACE

//! \brief Real32Counter Base Class.

template<class Desc>
class CounterImpl : public Counter
{
  public:

    typedef Counter     Inherited;
    typedef Counter     ParentContainer;
    typedef CounterImpl Self;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Self);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        StepFieldId       = Inherited::NextFieldId,
        ResetValueFieldId = StepFieldId + 1,
        ValueFieldId      = ResetValueFieldId + 1,
        NextFieldId       = ValueFieldId + 1
    };

    static const OSG::BitVector StepFieldMask =
        (TypeTraits<BitVector>::One << StepFieldId);

    static const OSG::BitVector ResetValueFieldMask =
        (TypeTraits<BitVector>::One << ResetValueFieldId);

    static const OSG::BitVector ValueFieldMask =
        (TypeTraits<BitVector>::One << ValueFieldId);

    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef typename Desc::SFValueType       SFValueType;
    typedef          SFValueType             SFStepType;
    typedef          SFValueType             SFResetValueType;

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


                  SFValueType          *editSFStep           (void);
            const SFValueType          *getSFStep            (void) const;

                  SFValueType         *editSFResetValue     (void);
            const SFValueType         *getSFResetValue      (void) const;

                  SFValueType         *editSFValue          (void);
            const SFValueType         *getSFValue           (void) const;


                  ValueType       &editStep           (void);
                  ValueType        getStep            (void) const;

                  ValueType      &editResetValue     (void);
                  ValueType       getResetValue      (void) const;

                  ValueType           &editValue          (void);
                  ValueType            getValue           (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setStep           (const ValueType  value);
            void setResetValue     (const ValueType  value);
            void setValue          (const ValueType  value);

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

    static  ObjTransitPtr  create          (void);
    static  Self           *createEmpty     (void);

    static  ObjTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  Self            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerTransitPtr shallowCopy     (void) const;
    virtual FieldContainerTransitPtr shallowCopyLocal(
                                       BitVector bFlags = FCLocal::All) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFValueType          _sfStep;
    SFValueType          _sfResetValue;
    SFValueType          _sfValue;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CounterImpl(void);
    CounterImpl(const CounterImpl &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CounterImpl(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleStep            (void) const;
    EditFieldHandlePtr editHandleStep           (void);
    GetFieldHandlePtr  getHandleResetValue      (void) const;
    EditFieldHandlePtr editHandleResetValue     (void);
    GetFieldHandlePtr  getHandleValue           (void) const;
    EditFieldHandlePtr editHandleValue          (void);

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
    virtual FieldContainer *createAspectCopy(void) const;
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
    void operator =(const CounterImpl &source);
};

struct Int32CounterDesc
{
    typedef SFInt32 SFValueType;

    static const Char8 *getClassname(void)
    {
        return "Int32Counter";
    }
};

struct Real32CounterDesc
{
    typedef SFReal32 SFValueType;

    static const Char8 *getClassname(void)
    {
        return "Real32Counter";
    }
};

typedef CounterImpl<Int32CounterDesc > Int32Counter;
typedef CounterImpl<Real32CounterDesc> Real32Counter;

OSG_END_NAMESPACE

#include "OSGCounters.inl"


#endif /* _OSGCOUNTERS_H_ */
