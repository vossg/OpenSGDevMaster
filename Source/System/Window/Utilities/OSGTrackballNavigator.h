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

#ifndef _OSG_TRACKBALLNAVIGATOR_H_
#define _OSG_TRACKBALLNAVIGATOR_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGViewport.h"

OSG_BEGIN_NAMESPACE

/*! \brief Navigator for trackball model. See \ref 
    PageSystemWindowNavigatorsTrackball for a description.
*/
class OSG_UTIL_DLLMAPPING TrackballNavigator
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum State
    {
        IDLE=0,
        ROTATING,
        TRANSLATING_XY,
        TRANSLATING_Z
    };


    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TrackballNavigator(Real32 rSize=0.8);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    ~TrackballNavigator();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    const char *getClassname(void) { return "TrackballNavigator"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    Matrix &getMatrix();
    Pnt3f  &getFrom();
    Pnt3f  &getAt();
    Vec3f  &getUp();
    Real32  getDistance();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    void setAt       (Pnt3f  new_at);
    void setFrom     (Pnt3f  new_from);
    void setDistance (Real32 new_distance);
    void setUp       (Vec3f  new_up);
    void set         (Pnt3f  new_from, Pnt3f new_center, Vec3f new_up);
    void set         (Matrix new_matrix);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Trackball Transformations                       */
    /*! \{                                                                 */

    void rotate     (Real32 fromX, Real32 fromY,
                     Real32 toX,   Real32 toY);
    void translateXY(Real32 distanceX, Real32 distanceY);
    void translateZ (Real32 distance);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    Real32 _rRadius, _rDistance;
    Matrix _tMatrix, _finalMatrix;
    State  _currentState;
    Pnt3f  _pFrom, _pAt;
    Vec3f  _vUp;

    /*! \}                                                                 */

    void updateFinalMatrix();

    Real32 projectToSphere(Real32 rRadius, Real32 rX, Real32 rY);
};

OSG_END_NAMESPACE

#endif
