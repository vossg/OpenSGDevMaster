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


#ifndef _OSGOFFCENTERPERSPECTIVECAMERA_H_
#define _OSGOFFCENTERPERSPECTIVECAMERA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGOffCenterPerspectiveCameraBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief OffCenter Perspective Camera class. 
           See for example \ref PageSystemWindowCameraPerspective 
           for a description or take a look at the details.
    \ingroup GrpWindowCameraObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING OffCenterPerspectiveCamera : 
    public OffCenterPerspectiveCameraBase
{
   /*==========================  PUBLIC  =================================*/

 public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    transformation                            */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    virtual void getProjection(Matrix &result, 
                               UInt32  width, 
                               UInt32  height);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    dump                                      */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
 
    /*---------------------------------------------------------------------*/
    /*! \name                    Constructors                              */
    /*! \{                                                                 */

    OffCenterPerspectiveCamera(void);
    OffCenterPerspectiveCamera(const OffCenterPerspectiveCamera &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~OffCenterPerspectiveCamera(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  

 private:

    typedef OffCenterPerspectiveCameraBase Inherited;

    friend class FieldContainer;
    friend class OffCenterPerspectiveCameraBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const OffCenterPerspectiveCamera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef OffCenterPerspectiveCamera *OffCenterPerspectiveCameraP;

OSG_END_NAMESPACE

#include "OSGOffCenterPerspectiveCameraBase.inl"
#include "OSGOffCenterPerspectiveCamera.inl"

#endif /* _OSGOFFCENTERPERSPECTIVECAMERA_H_ */
