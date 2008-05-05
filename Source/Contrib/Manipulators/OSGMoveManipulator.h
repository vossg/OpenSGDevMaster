/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGMOVEMANIPULATOR_H_
#define _OSGMOVEMANIPULATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGMoveManipulatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MoveManipulator class. See \ref
           PageManipulatorsMoveManipulator for a description.
*/

class OSG_CONTRIBGUI_DLLMAPPING MoveManipulator : public MoveManipulatorBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MoveManipulatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MoveManipulator(void);
    MoveManipulator(const MoveManipulator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MoveManipulator(void);


    /*! \}                                                                 */

    virtual NodeTransitPtr makeHandleGeo();
    virtual void           doMovement(      Transform    *t,
                                      const Int32         coord,
                                      const Real32        value,
                                      const Vec3f        &translation,
                                      const Quaternion   &rotation,
                                      const Vec3f        &scaleFactor,
                                      const Quaternion   &scaleOrientation);

    /*==========================  PRIVATE  ================================*/
private:

    typedef MoveManipulatorBase Inherited;

    friend class FieldContainer;
    friend class MoveManipulatorBase;

    static void initMethod(InitPhase ePhase);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MoveManipulator &source);
};

typedef MoveManipulator *MoveManipulatorP;

OSG_END_NAMESPACE

#include "OSGMoveManipulatorBase.inl"
#include "OSGMoveManipulator.inl"

#endif /* _OSGMOVEMANIPULATOR_H_ */
