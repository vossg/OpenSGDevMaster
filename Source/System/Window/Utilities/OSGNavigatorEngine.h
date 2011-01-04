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

#ifndef _OSG_NAVIGATORENGINE_H_
#define _OSG_NAVIGATORENGINE_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGViewport.h"
#include "OSGMemoryObject.h"
#include "OSGNavigatorBase.h"

OSG_BEGIN_NAMESPACE

class Navigator;

/*! \brief Base class for all navigator engines.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING NavigatorEngine : public MemoryObject
{
    typedef MemoryObject    Inherited;
    typedef NavigatorEngine Self;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    OSG_GEN_INTERNAL_MEMOBJPTR(NavigatorEngine);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    const char *getClassname(void) { return "NavigatorEngine"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    NavigatorBase::State getState() const;

    virtual const Pnt3f  &getFrom(void)      = 0;
    virtual const Pnt3f  &getAt(void)        = 0;
    virtual const Vec3f  &getUp(void)        = 0;
    virtual const Matrix &getMatrix(void)    = 0;
    virtual Real32 getDistance(void)         = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    virtual void setFrom(Pnt3f new_from)                         = 0;
    virtual void setAt(Pnt3f new_at)                             = 0;
    virtual void setUp(Vec3f new_up)                             = 0;
    virtual void set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up) = 0;
    virtual void set(const Matrix & new_matrix)                  = 0;
    virtual void setDistance(Real32 new_distance)                = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              navigator engine callbacks                      */
    /*! \{                                                                 */

    virtual void buttonPress(Int16 button,Int16 x,Int16 y,Navigator* nav) = 0;
    virtual void buttonRelease(Int16 ,    Int16 x,Int16 y,Navigator* nav) = 0;
    virtual void keyPress(Int16 key,      Int16 x,Int16 y,Navigator* nav) = 0;
    virtual void moveTo(                  Int16 x,Int16 y,Navigator* nav) = 0;
    virtual void idle(Int16 buttons,      Int16 x,Int16 y,Navigator* nav) = 0;

    virtual void onViewportChanged(Navigator* nav);
    virtual void onActivation(Navigator* nav);
    virtual void onUpdateCameraTransformation(Navigator* nav);

    /*! \}                                                                 */
    /*==========================  PROTECTED  ==============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name              Constructors/Destructor                         */
    /*! \{                                                                 */

             NavigatorEngine(void);
    virtual ~NavigatorEngine(void) = 0;

    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    NavigatorBase::State _currentState;

    /*! \}                                                                 */

  private:

    /* Not implemented */
    NavigatorEngine(const NavigatorEngine &other);
    NavigatorEngine &operator =(const NavigatorEngine &other);
};

OSG_GEN_MEMOBJPTR(NavigatorEngine);

OSG_END_NAMESPACE

#endif
