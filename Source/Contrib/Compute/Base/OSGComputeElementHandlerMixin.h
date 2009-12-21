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

#ifndef _OSGCOMPUTEELEMENTHANDLERMIXIN_H_
#define _OSGCOMPUTEELEMENTHANDLERMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDataSlotPool.h"
#include "OSGComputeElementIdPool.h"
#include "OSGComputeElementData.h"
#include "OSGHardwareContext.h"
#include "OSGOSGAnyFields.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerMixins
    \ingroup GrpLibOSGBase
 */
template <class ParentT>
class ComputeElementHandlerMixin  : public ParentT
{
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ParentT                    Inherited;
    typedef HardwareContext::Inherited DataSlotHandler;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          ComputeElementHandlerMixin<ParentT> Self;

    typedef typename ParentT::Desc                       Desc;
    typedef typename Desc::TypeObject                    TypeObject;

#if 0
    typedef          StageValidator::ValidationStatus  ValidationStatus;
#endif

    enum UpdateMode
    {
        PerVisit     = 0x0001,

        OnRequest    = 0x0002
    };


    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    OSG_RC_FIRST_FIELD_DECL(UpdateMode                   );

    OSG_RC_FIELD_DECL      (RequestRun,        UpdateMode);
    OSG_RC_FIELD_DECL      (DestroyedFunctors, RequestRun);
    OSG_RC_LAST_FIELD_DECL (DestroyedFunctors            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void   addDestroyedFunctor     (ChangedFunctor    func,
                                    std::string       createSymbol);

    template<class FunctorT>
    void   subDestroyedFunctor     (FunctorT          func        );

    template<class FunctorT>
    bool   hasDestroyedFunctor     (FunctorT          func        );

    void   clearDestroyedFunctors  (void                          );

    void   clearDestroyedFunctorFor(DataSlotHandler  *pHandler    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    bool requestRun(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void changed(ConstFieldMaskArg whichField, 
                 UInt32            origin,
                 BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

#if 0
    ValidationStatus validateOnEnter(RenderActionBase *pAction);
    ValidationStatus validateOnLeave(RenderActionBase *pAction);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

          void      setUpdateMode   (UpdateMode eMode);
          UInt32    getUpdateMode   (void            ) const;

          SFUInt32 *editSFUpdateMode(void            );
    const SFUInt32 *getSFUpdateMode (void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg   whichField);
    virtual void   copyToBin  (BinaryDataHandler  &pMem,
                               ConstFieldMaskArg   whichField);
    virtual void   copyFromBin(BinaryDataHandler  &pMem,
                               ConstFieldMaskArg   whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    void setData(ComputeElementData *pData, 
                 Int32               iDataSlotId,
                 HardwareContext    *pContext   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    Int32  _iDataSlotId;
    Int32  _iElementId;


#if 0
    StageValidator::ValidationStatus _tmpStatus;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

#if 0
    ValidationStatus validate(RenderActionBase *pAction);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFUInt32                 _sfUpdateMode;
    SFOSGAny                 _sfRequestRun;
    MFChangedFunctorCallback _mfDestroyedFunctors;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ComputeElementHandlerMixin(void);
    ComputeElementHandlerMixin(const ComputeElementHandlerMixin &source);

    virtual ~ComputeElementHandlerMixin(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    static void classDescInserter(TypeObject &oType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void execSync  (      Self              *pFrom,
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
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    EditFieldHandlePtr editHandleUpdateMode       (void);
    GetFieldHandlePtr  getHandleUpdateMode        (void) const;

    GetFieldHandlePtr  getHandleRequestRun        (void) const;

    GetFieldHandlePtr  getHandleDestroyedFunctors (void) const;
    EditFieldHandlePtr editHandleDestroyedFunctors(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

            void onCreateAspect (const Self   *createAspect,
                                 const Self   *source      = NULL);

            void onCreate       (const Self   *source      = NULL);

    virtual void onDestroy      (      UInt32  uiContainerId     );

    virtual void onDestroyAspect(      UInt32  uiContainerId,
                                       UInt32  uiAspect          );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ComputeElementHandlerMixin &source);
};

OSG_END_NAMESPACE

#include "OSGComputeElementHandlerMixin.inl"

#endif /* _OSGCOMPUTEELEMENTHANDLERMIXIN_H_ */
