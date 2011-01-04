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

#ifndef _OSGTRAVERSALVALIDATIONHANDLERMIXIN_H_
#define _OSGTRAVERSALVALIDATIONHANDLERMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGOSGAnyFields.h"

#include <boost/bind.hpp>

#include "OSGWindow.h"
#include "OSGTraversalValidator.h"
#include "OSGRenderActionBase.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerMixins
    \ingroup GrpLibOSGSystem
 */
template <class ParentT>
class TraversalValidationHandlerMixin  : public ParentT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          TraversalValidationHandlerMixin<ParentT> Self;

    typedef typename ParentT::Desc                            Desc;
    typedef typename Desc::TypeObject                         TypeObject;

    /*==========================  PRIVATE  ================================*/

  protected:

    typedef ParentT                                  Inherited;
    typedef typename Desc::DataSlotHandler           DataSlotHandler;
    typedef typename DataSlotHandler::DataSlotIdPool DataSlotIdPool;
    typedef typename Desc::ElementIdPool             ElementIdPool;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TraversalValidator::ValidationStatus  ValidationStatus;

    enum UpdateMode
    {
        PerWindow    = 0x0001,
        PerViewport  = 0x0002,
        PerTraversal = 0x0003,

        PerVisit     = 0x0004,

        OnRequest    = 0x0005
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

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    ValidationStatus validate(RenderActionBase *pAction);

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

    TraversalValidationHandlerMixin(void);
    TraversalValidationHandlerMixin(const Self &source);

    virtual ~TraversalValidationHandlerMixin(void);

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
    void operator =(const TraversalValidationHandlerMixin &source);
};

OSG_END_NAMESPACE

#include "OSGTraversalValidationHandlerMixin.inl"

#endif /* _OSGTRAVERSALVALIDATIONHANDLERMIXIN_H_ */
