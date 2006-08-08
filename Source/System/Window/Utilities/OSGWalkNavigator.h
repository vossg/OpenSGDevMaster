/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSG_WALKNAVIGATOR_H_
#define _OSG_WALKNAVIGATOR_H_

#include "OSGFlyNavigator.h"
#include "OSGIntersectAction.h"

OSG_BEGIN_NAMESPACE

/*! \brief WalkNavigator class
 */

class OSG_UTIL_DLLMAPPING WalkNavigator: public FlyNavigator
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WalkNavigator();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    ~WalkNavigator();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */
    
    void setGround  (const NodePtr &new_ground);
    void setWorld   (const NodePtr &new_world );
    
    void setGroundDistance  (Real32 groundDistance);
    void setMinWallDistance (Real32 wallDistance  );

    void setPersonDimensions(Real32 height, Real32 width, Real32 fatness);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Walker Transformations                      */
    /*! \{                                                                 */

    void   rotate (Real32 deltaX, Real32 deltaY);
    Real32 forward(Real32 step);
    Real32 right  (Real32 step);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */    
  
    NodePtr _ground;
    NodePtr _world;

    Real32 _groundDistance;
    Real32 _wallDistance;
    Real32 _height;
    Real32 _width;
    Real32 _fatness;
    
    IntersectAction *_act;
          
    /*! \}                                                                 */
};

OSG_END_NAMESPACE
#endif
