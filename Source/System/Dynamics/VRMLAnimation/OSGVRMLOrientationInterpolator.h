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

#ifndef _OSGVRMLORIENTATIONINTERPOLATOR_H_
#define _OSGVRMLORIENTATIONINTERPOLATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVRMLOrientationInterpolatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief VRMLOrientationInterpolator class. See \ref
           PageSystemDynamicsVRMLOrientationInterpolator for a description.
    \ingroup GrpDynamicsVRMLAnimationObj
    \ingroup GrpLibOSGDynamics
    \includebasedoc
 */

class OSG_DYNAMICS_DLLMAPPING VRMLOrientationInterpolator : 
    public VRMLOrientationInterpolatorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VRMLOrientationInterpolatorBase Inherited;
    typedef VRMLOrientationInterpolator     Self;

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

    // Variables should all be in VRMLOrientationInterpolatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VRMLOrientationInterpolator(void);
    VRMLOrientationInterpolator(const VRMLOrientationInterpolator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VRMLOrientationInterpolator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VRMLOrientationInterpolatorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VRMLOrientationInterpolator &source);
};

typedef VRMLOrientationInterpolator *VRMLOrientationInterpolatorP;

OSG_END_NAMESPACE

#include "OSGVRMLOrientationInterpolatorBase.inl"
#include "OSGVRMLOrientationInterpolator.inl"

#endif /* _OSGVRMLORIENTATIONINTERPOLATOR_H_ */
