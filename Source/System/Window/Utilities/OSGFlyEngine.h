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

#ifndef _OSG_FLYENGINE_H_
#define _OSG_FLYENGINE_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGViewport.h"
#include "OSGNavigatorEngine.h"

OSG_BEGIN_NAMESPACE

/*! \brief Navigator engine for simple fly model. See \ref 
           PageSystemWindowNavigatorsFly for a description.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING FlyEngine : public NavigatorEngine
{
    typedef NavigatorEngine Inherited;
    typedef FlyEngine       Self;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Types                                  */
    /*! \{                                                                 */

    OSG_GEN_INTERNAL_MEMOBJPTR(FlyEngine);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static ObjTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    const char *getClassname(void) { return "FlyEngine"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    virtual const Pnt3f  &getFrom(void);
    virtual const Pnt3f  &getAt(void);
    virtual const Vec3f  &getUp(void);
    virtual const Matrix &getMatrix(void);
    virtual Real32 getDistance(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    virtual void setFrom(Pnt3f new_from);
    virtual void setAt(Pnt3f new_at);
    virtual void setUp(Vec3f new_up);
    virtual void set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up);
    virtual void set(const Matrix & new_matrix);
    virtual void setDistance(Real32 dist);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              navigator engine callbacks                      */
    /*! \{                                                                 */

    virtual void buttonPress(Int16 button,Int16 x,Int16 y,Navigator* nav);
    virtual void buttonRelease(Int16 ,    Int16 x,Int16 y,Navigator* nav);
    virtual void keyPress(Int16 key,      Int16 x,Int16 y,Navigator* nav);
    virtual void moveTo(                  Int16 x,Int16 y,Navigator* nav);
    virtual void idle(Int16 buttons,      Int16 x,Int16 y,Navigator* nav);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Flyer Transformations                       */
    /*! \{                                                                 */

    virtual void   rotate (Real32 deltaX, Real32 deltaY);
    virtual Real32 forward(Real32 step);
    virtual Real32 right  (Real32 step);

    /*! \}                                                                 */
    /*==========================  PROTECTED  ==============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Constructors/Destructor                          */
    /*! \{                                                                 */

             FlyEngine(void);
    virtual ~FlyEngine(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    Pnt3f  _rFrom;
    Pnt3f  _rAt;
    Vec3f  _vUp;
    Matrix _tMatrix;

    /*! \}                                                                 */

  private:

    /* Not implemented */
    FlyEngine(const FlyEngine &other);
    FlyEngine &operator =(const FlyEngine &other);
};

OSG_GEN_MEMOBJPTR(FlyEngine);

OSG_END_NAMESPACE

#endif
