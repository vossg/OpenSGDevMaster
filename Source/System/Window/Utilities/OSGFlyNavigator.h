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

#ifndef _OSG_FLYNAVIGATOR_H_
#define _OSG_FLYNAVIGATOR_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"

OSG_BEGIN_NAMESPACE

/*! \brief Navigator for simple fly model. See \ref 
    PageSystemWindowNavigatorsFly for a description.
*/

class OSG_UTIL_DLLMAPPING FlyNavigator
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FlyNavigator();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FlyNavigator();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    Matrix &getMatrix(void);
    Pnt3f  &getFrom  (void);
    Pnt3f  &getAt    (void);
    Vec3f  &getUp    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    void setFrom   (Pnt3f new_from);
    void setAt     (Pnt3f new_at);
    void setUp     (Vec3f new_up);
    void set       (Pnt3f new_from, Pnt3f new_at, Vec3f new_up);
    void set       (Matrix new_matrix);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Flyer Transformations                       */
    /*! \{                                                                 */

    void   rotate (Real32 deltaX, Real32 deltaY);
    Real32 forward(Real32 step);
    Real32 right  (Real32 step);

    /*! \}                                                                 */
    /*==========================  PROTECTED  ==============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    Pnt3f  _rFrom;
    Pnt3f  _rAt;
    Vec3f  _vUp;
    Matrix _tMatrix;

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#endif
