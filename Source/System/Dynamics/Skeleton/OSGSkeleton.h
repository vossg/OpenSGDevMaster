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

#ifndef _OSGSKELETON_H_
#define _OSGSKELETON_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkeletonBase.h"
#include "OSGBaseSkeletonJoint.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

/*! \brief Skeleton class. See \ref
           PageDynamicsSkeleton for a description.
*/

class OSG_DYNAMICS_DLLMAPPING Skeleton : public SkeletonBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef SkeletonBase Inherited;
    typedef Skeleton     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Render                                  */
    /*! \{                                                                 */

    Action::ResultE renderEnter   (Action *action, NodeCore *parent);
    Action::ResultE renderLeave   (Action *action, NodeCore *parent);

    Action::ResultE intersectEnter(Action *action, NodeCore *parent);

    Action::ResultE animBindEnter (Action *action, NodeCore *parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkeletonBase.
    typedef std::vector<BaseSkeletonJoint *> JointStack;
    typedef JointStack::iterator             JointStackIt;
    typedef JointStack::const_iterator       JointStackConstIt;

    bool _jointMatricesValid;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Skeleton(void);
    Skeleton(const Skeleton &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Skeleton(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Update                                  */
    /*! \{                                                                 */

    void            updateJoints   (void                              );
    Action::ResultE findJointsEnter(JointStack *jointStack, Node *node);
    Action::ResultE findJointsLeave(JointStack *jointStack, Node *node);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Skeleton &source);
};

typedef Skeleton *SkeletonP;

OSG_END_NAMESPACE

#include "OSGSkeletonBase.inl"
#include "OSGSkeleton.inl"

#endif /* _OSGSKELETON_H_ */
