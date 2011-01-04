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

#ifndef _OSGSTAGEHANDLERMIXIN_H_
#define _OSGSTAGEHANDLERMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTraversalValidationHandlerMixin.h"

#include "OSGStageData.h"

#include "OSGMultiCore.h"
#include "OSGViewport.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerMixins
    \ingroup GrpLibOSGBase
 */

template <class ParentT>
class StageHandlerMixin  : public TraversalValidationHandlerMixin<ParentT>
{
    /*==========================  PRIVATE  ================================*/

  protected:

    typedef          TraversalValidationHandlerMixin<ParentT> Inherited;
    typedef typename Inherited::DataSlotHandler               DataSlotHandler;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          StageHandlerMixin<ParentT>           Self;

    typedef typename ParentT::Desc                        Desc;
    typedef typename Desc::TypeObject                     TypeObject;

    typedef typename Inherited::ValidationStatus          ValidationStatus;

    enum GroupMode 
    {
        NoPartitionGroup = 0x0000,
        InPartitionGroup = 0x0001,
        InPartitionList  = 0x0002
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

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

    void changed(ConstFieldMaskArg whichField, 
                 UInt32            origin,
                 BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    ValidationStatus validateOnEnter(RenderActionBase *pAction);
    ValidationStatus validateOnLeave(RenderActionBase *pAction);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void pushPartition      (RenderActionBase          *pAction,
                             UInt32                     uiCopyOnPush = 0x0000, 
                             RenderPartitionBase::Mode  eMode        = 
                                            RenderPartitionBase::StateSorting);
    void popPartition       (RenderActionBase          *pAction);

    void beginPartitionGroup(RenderActionBase          *pAction);
    void endPartitionGroup  (RenderActionBase          *pAction);

    void beginPartitions    (RenderActionBase          *pAction);
    void endPartitions      (RenderActionBase          *pAction);

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

    void setData(StageData        *pData, 
                 Int32             iDataSlotId,
                 RenderActionBase *pAction    );

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

    TraversalValidator::ValidationStatus _tmpStatus;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    StageHandlerMixin(void);
    StageHandlerMixin(const StageHandlerMixin &source);

    virtual ~StageHandlerMixin(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    Action::ResultE recurseFromThis(Action   *action );

    Action::ResultE recurseFrom    (Action   *action,
                                    NodeCore *pFrom  );

    Action::ResultE recurse        (Action   *action,
                                    Node     *node   );
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const StageHandlerMixin &source);
};

OSG_END_NAMESPACE

#include "OSGStageHandlerMixin.inl"

#endif /* _OSGSTAGEHANDLERMIXIN_H_ */
