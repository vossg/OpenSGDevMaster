/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGRENDERCALLBACKSTAGE_H_
#define _OSGRENDERCALLBACKSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include <queue>

#include "OSGRenderCallbackStageBase.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

class RenderPartition;

/*! Stage
    \ingroup GrpGroupStageObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING RenderCallbackStage : public RenderCallbackStageBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef std::vector<RenderFunctor> RenderFunctorStore;

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    UInt32 addPreRenderFunctor    (RenderFunctor func,
                                   std::string    createSymbol);

    template<class FunctorT>
    void   subPreRenderFunctor    (FunctorT       func        );

    void   subPreRenderFunctor    (UInt32         uiId        );

    void   clearPreRenderFunctors (void                       );


    UInt32 addPostRenderFunctor   (RenderFunctor func,
                                   std::string    createSymbol);

    template<class FunctorT>
    void   subPostRenderFunctor   (FunctorT       func        );

    void   subPostRenderFunctor   (UInt32         uiId        );

    void   clearPostRenderFunctors(void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void fillPreRenderStore (RenderFunctorStore &vStore);
    void fillPostRenderStore(RenderFunctorStore &vStore);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef RenderCallbackStageBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RenderCallbackStage(void);
    RenderCallbackStage(const RenderCallbackStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RenderCallbackStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    void addCallbacks(RenderPartition *pPartition);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RenderCallbackStageBase;

    /*---------------------------------------------------------------------*/
    /*! \name                   thread local                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    load thread                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const RenderCallbackStage &source);
};

typedef RenderCallbackStage              *RenderCallbackStageP;

OSG_END_NAMESPACE

#include "OSGRenderCallbackStageBase.inl"
#include "OSGRenderCallbackStage.inl"

#endif /* _OSGRENDERCALLBACKSTAGE_H_ */
