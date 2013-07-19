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

#ifndef _OSGVALUEACCUMULATOR_H_
#define _OSGVALUEACCUMULATOR_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGCounter.h" // Parent

#include "OSGSysFields.h" // Step type
#include "OSGBaseFields.h"
#include "OSGMathFields.h"
#include "OSGVecFields.h"

OSG_BEGIN_NAMESPACE

//! \brief Real32Counter Base Class.

template<class Desc>
class SValueAccumulator : public NodeCore
{
  public:

    typedef NodeCore          Inherited;
    typedef NodeCore          ParentContainer;
    typedef SValueAccumulator Self;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Self);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        ValueFieldId        = Inherited::NextFieldId,
        RhsFieldId          = ValueFieldId + 1,
        NextFieldId         = RhsFieldId + 1
    };

    static const OSG::BitVector ValueFieldMask =
        (TypeTraits<BitVector>::One << ValueFieldId);

    static const OSG::BitVector RhsFieldMask =
        (TypeTraits<BitVector>::One << RhsFieldId);

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


          SFValueType *editSFValue         (void);
    const SFValueType *getSFValue          (void) const;

          ValueType   &editValue           (void);
          ValueType    getValue            (void) const;

          SFValueType *editSFRhs           (void);
    const SFValueType *getSFRhs            (void) const;

          ValueType   &editRhs             (void);
          ValueType    getRhs              (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setValue(const ValueType value);
    void setRhs  (const ValueType value);

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

    SFValueType _sfValue;
    SFValueType _sfRhs;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SValueAccumulator(void);
    SValueAccumulator(const SValueAccumulator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SValueAccumulator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleValue          (void) const;
    EditFieldHandlePtr editHandleValue         (void);

    GetFieldHandlePtr  getHandleRhs            (void) const;
    EditFieldHandlePtr editHandleRhs           (void);


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
    void operator =(const SValueAccumulator &source);
};

#if 0
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
#endif

struct Real32AccumulatorDesc
{
    typedef SFReal32 SFValueType;

    static const Char8 *getClassname(void)
    {
        return "Real32Accumulator";
    }

    static Real32 getDefault(void)
    {
        return 0.f;
    }

    static void accumulate(      Real32 &result,
                           const Real32  rhs   )
    {
        result += rhs;
    }
};

struct Vec2fAccumulatorDesc
{
    typedef SFVec2f SFValueType;

    static const Char8 *getClassname(void)
    {
        return "Vec2fAccumulator";
    }

    static Vec2f getDefault(void)
    {
        return Vec2f(0.f, 0.f);
    }

    static void accumulate(      Vec2f &result,
                           const Vec2f  rhs   )
    {
        result += rhs;

        fprintf(stderr, "step : %f %f, res : %f %f\n",
                rhs[0],
                rhs[1],
                result[0],
                result[1]);
    }
};

struct MatrixAccumulatorDesc
{
    typedef SFMatrix SFValueType;

    static const Char8 *getClassname(void)
    {
        return "MatrixAccumulator";
    }

    static Matrix getDefault(void)
    {
        Matrix m;
        
        m.setIdentity();

        return m;
    }

    static void accumulate(      Matrix &result,
                           const Matrix &rhs   )
    {
        result.add(rhs);
    }
};

//typedef SValueEmitter<Int32EmitterDesc > Int32Emitter;
typedef SValueAccumulator<Real32AccumulatorDesc> Real32Accumulator;
typedef SValueAccumulator<Vec2fAccumulatorDesc > Vec2fAccumulator;
typedef SValueAccumulator<MatrixAccumulatorDesc> MatrixAccumulator;

OSG_END_NAMESPACE

#include "OSGValueAccumulator.inl"

#endif /* _OSGVALUEACCUMULATOR_H_ */
