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

#ifndef _OSGVRMLINTERPOLATOR_H_
#define _OSGVRMLINTERPOLATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVRMLInterpolatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief VRMLInterpolator class. See \ref
           PageSystemDynamicsVRMLInterpolator for a description.
    \ingroup GrpDynamicsVRMLAnimationObj
    \ingroup GrpLibOSGDynamics
    \includebasedoc
 */

class OSG_DYNAMICS_DLLMAPPING VRMLInterpolator : public VRMLInterpolatorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VRMLInterpolatorBase Inherited;
    typedef VRMLInterpolator     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VRMLInterpolatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VRMLInterpolator(void);
    VRMLInterpolator(const VRMLInterpolator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VRMLInterpolator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VRMLInterpolatorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VRMLInterpolator &source);
};

typedef VRMLInterpolator *VRMLInterpolatorP;

OSG_END_NAMESPACE

#include "OSGVRMLInterpolatorBase.inl"
#include "OSGVRMLInterpolator.inl"

#endif /* _OSGVRMLINTERPOLATOR_H_ */
