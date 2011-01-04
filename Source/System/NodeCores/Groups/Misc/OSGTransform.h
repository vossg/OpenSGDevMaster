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

#ifndef _OSGTRANSFORM_H_
#define _OSGTRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGTransformBase.h"

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGActorBase.h"
#endif

OSG_BEGIN_NAMESPACE

/*! \brief Transform provides one matrix to transform objects.
    \ingroup GrpGroupMiscObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
 */

class OSG_GROUP_DLLMAPPING Transform : public TransformBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrix &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef TransformBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Transform(void);
    Transform(const Transform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Transform(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Init                                       */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume    (Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Intersect & Render                              */
    /*! \{                                                                 */

    ActionBase::ResultE     intersectEnter(Action    *action);
    ActionBase::ResultE     intersectLeave(Action    *action);

    ActionBase::ResultE     renderEnter   (Action    *action);
    ActionBase::ResultE     renderLeave   (Action    *action);

#ifdef OSG_HAVE_ACTION //CHECK
    NewActionTypes::ResultE 
        intersectActorEnter(ActorBase::FunctorArgumentType &funcArg);

    NewActionTypes::ResultE 
        intersectActorLeave(ActorBase::FunctorArgumentType &funcArg);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TransformBase;

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Transform &source);
};

typedef Transform *TransformP;

OSG_END_NAMESPACE

#include "OSGTransformBase.inl"
#include "OSGTransform.inl"

#endif /* _OSGTRANSFORM_H_ */
