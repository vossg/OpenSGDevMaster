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

#ifndef _OSG_NONEENGINE_H_
#define _OSG_NONEENGINE_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGViewport.h"
#include "OSGNavigatorEngine.h"

OSG_BEGIN_NAMESPACE

/*! \brief Base class for all navigator engines.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING NoneEngine : public NavigatorEngine
{
    typedef NavigatorEngine Inherited;
    typedef NoneEngine      Self;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    OSG_GEN_INTERNAL_MEMOBJPTR(NoneEngine);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Construction                              */
    /*! \{                                                                 */

    static ObjTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    const char *getClassname(void) { return "NoneEngine"; }

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
    virtual void setDistance(Real32 new_distance);

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
    /*==========================  PROTECTED  ==============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name              Constructors/Destructor                         */
    /*! \{                                                                 */

             NoneEngine(void);
    virtual ~NoneEngine(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    Matrix _noneMatrix;

    /*! \}                                                                 */

  private:

    /* Not implemented */
    NoneEngine(const NoneEngine &other);
    NoneEngine &operator =(const NoneEngine &other);
};

OSG_GEN_MEMOBJPTR(NoneEngine);

OSG_END_NAMESPACE

#endif
