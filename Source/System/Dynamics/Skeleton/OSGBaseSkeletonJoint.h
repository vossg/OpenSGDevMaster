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

#ifndef _OSGBASESKELETONJOINT_H_
#define _OSGBASESKELETONJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseSkeletonJointBase.h"
#include "OSGSkeletonFields.h"

OSG_BEGIN_NAMESPACE

// forward declaration
class Skeleton;

/*! \brief BaseSkeletonJoint class. See \ref
           PageDynamicsBaseSkeletonJoint for a description.
*/

class OSG_DYNAMICS_DLLMAPPING BaseSkeletonJoint : public BaseSkeletonJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef BaseSkeletonJointBase Inherited;
    typedef BaseSkeletonJoint     Self;

    class JointTraverser
    {
      public:
        explicit JointTraverser(Skeleton *skel);

        void          pushMatrix(const Matrix &m);
        void          popMatrix (void           );
        const Matrix &topMatrix (void           ) const;

        Action::ResultE enter(Node * const node                     );
        Action::ResultE leave(Node * const node, Action::ResultE res);

      protected:
        typedef std::vector<Matrix> MatrixStack;

        Skeleton    *_skel;
        Matrix       _topMatrix;
        MatrixStack  _matStack;

      private:
        JointTraverser(const JointTraverser &other);
    };

    static const Int16 INVALID_JOINT_ID;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Skeleton                                */
    /*! \{                                                                 */

    const SFParentSkeletonPtr *getSFSkeleton(void) const;
    Skeleton                  *getSkeleton  (void) const;

    virtual Action::ResultE jointUpdateEnter(JointTraverser *jt) = 0;
    virtual Action::ResultE jointUpdateLeave(JointTraverser *jt) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in BaseSkeletonJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BaseSkeletonJoint(void);
    BaseSkeletonJoint(const BaseSkeletonJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BaseSkeletonJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BaseSkeletonJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const BaseSkeletonJoint &source);
};

typedef BaseSkeletonJoint *BaseSkeletonJointP;

OSG_END_NAMESPACE

// include this here, so that it is available in the .inl
#include "OSGSkeleton.h"

#include "OSGBaseSkeletonJointBase.inl"
#include "OSGBaseSkeletonJoint.inl"

#endif /* _OSGBASESKELETONJOINT_H_ */
