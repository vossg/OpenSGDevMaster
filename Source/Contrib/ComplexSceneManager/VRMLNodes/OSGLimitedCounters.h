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

#ifndef _OSGLIMITEDCOUNTERS_H_
#define _OSGLIMITEDCOUNTERS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGBaseTypes.h"

#include "OSGCounters.h" // Parent

#include "OSGBoolFields.h" // Loop type

OSG_BEGIN_NAMESPACE


//! \brief LimitedReal32Counter Base Class.

template<class Desc>
class LimitedCounterImpl : public CounterImpl<typename Desc::BaseCounterDesc>
{
  public:

    typedef CounterImpl<typename Desc::BaseCounterDesc> Inherited;
    typedef CounterImpl<typename Desc::BaseCounterDesc> ParentContainer;
    typedef LimitedCounterImpl                          Self;

    typedef typename Inherited::TypeObject TypeObject;
    typedef typename TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(Self);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        UpperLimitFieldId = Inherited::NextFieldId,
        LowerLimitFieldId = UpperLimitFieldId + 1,
        LoopFieldId       = LowerLimitFieldId + 1,
        NextFieldId       = LoopFieldId + 1
    };

    static const OSG::BitVector UpperLimitFieldMask =
        (TypeTraits<BitVector>::One << UpperLimitFieldId);

    static const OSG::BitVector LowerLimitFieldMask =
        (TypeTraits<BitVector>::One << LowerLimitFieldId);

    static const OSG::BitVector LoopFieldMask =
        (TypeTraits<BitVector>::One << LoopFieldId);

    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef typename Desc::SFLimitType       SFLimitType;
    typedef typename Desc::SFLimitType       SFUpperLimitType;
    typedef typename Desc::SFLimitType       SFLowerLimitType;

    typedef          SFBool                  SFLoopType;

    typedef typename SFLimitType::StoredType LimitType;

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


                  SFLimitType            *editSFUpperLimit     (void);
            const SFLimitType            *getSFUpperLimit      (void) const;

                  SFLimitType            *editSFLowerLimit     (void);
            const SFLimitType            *getSFLowerLimit      (void) const;

                  SFBool              *editSFLoop           (void);
            const SFBool              *getSFLoop            (void) const;


                  LimitType           &editUpperLimit     (void);
                  LimitType            getUpperLimit      (void) const;

                  LimitType           &editLowerLimit     (void);
                  LimitType            getLowerLimit      (void) const;

                  bool                &editLoop           (void);
                  bool                 getLoop            (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setUpperLimit     (const LimitType value);
            void setLowerLimit     (const LimitType value);
            void setLoop           (const bool value);

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

    SFLimitType       _sfUpperLimit;
    SFLimitType       _sfLowerLimit;
    SFBool            _sfLoop;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LimitedCounterImpl(void);
    LimitedCounterImpl(const LimitedCounterImpl &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LimitedCounterImpl(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleUpperLimit      (void) const;
    EditFieldHandlePtr editHandleUpperLimit     (void);
    GetFieldHandlePtr  getHandleLowerLimit      (void) const;
    EditFieldHandlePtr editHandleLowerLimit     (void);
    GetFieldHandlePtr  getHandleLoop            (void) const;
    EditFieldHandlePtr editHandleLoop           (void);

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
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;

    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LimitedCounterImpl &source);
};

struct LimitedInt32CounterDesc
{
    typedef Int32CounterDesc              BaseCounterDesc;
    typedef Int32CounterDesc::SFValueType SFLimitType;

    static const Char8 *getClassname(void)
    {
        return "LimitedInt32Counter";
    }
};

struct LimitedReal32CounterDesc
{
    typedef Real32CounterDesc              BaseCounterDesc;
    typedef Real32CounterDesc::SFValueType SFLimitType;

    static const Char8 *getClassname(void)
    {
        return "LimitedReal32Counter";
    }
};

typedef LimitedCounterImpl<LimitedInt32CounterDesc > LimitedInt32Counter;
typedef LimitedCounterImpl<LimitedReal32CounterDesc> LimitedReal32Counter;

OSG_END_NAMESPACE

#include "OSGLimitedCounters.inl"

#endif /* _OSGLIMITEDCOUNTERS_H_ */
