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

#ifndef _OSG_WALKENGINE_H_
#define _OSG_WALKENGINE_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGViewport.h"
#include "OSGFlyEngine.h"

OSG_BEGIN_NAMESPACE

class IntersectAction;

/*! \brief Base class for all navigator engines.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING WalkEngine : public FlyEngine
{
    typedef FlyEngine  Inherited;
    typedef WalkEngine Self;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    OSG_GEN_INTERNAL_MEMOBJPTR(WalkEngine);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Construction                                */
    /*! \{                                                                 */
 
    static ObjTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    const char *getClassname(void) { return "WalkEngine"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    void setGround  (Node * const new_ground);
    void setWorld   (Node * const new_world );
    
    void setGroundDistance  (Real32 groundDistance);
    void setMinWallDistance (Real32 wallDistance  );

    void setPersonDimensions(Real32 height, Real32 width, Real32 fatness);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              navigator engine callbacks                      */
    /*! \{                                                                 */

    virtual void idle(Int16 buttons, Int16 x, Int16 y, Navigator* nav);

    virtual void onViewportChanged(Navigator* nav);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Walker Transformations                      */
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

             WalkEngine(void);
    virtual ~WalkEngine(void);

    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    Node   *_ground;
    Node   *_world;

    Real32  _groundDistance;
    Real32  _wallDistance;
    Real32  _height;
    Real32  _width;
    Real32  _fatness;
    
    IntersectAction *_act;

    /*! \}                                                                 */

  private:

    /* Not implemented */
    WalkEngine(const WalkEngine &other);
    WalkEngine &operator =(const WalkEngine &other);
};

OSG_GEN_MEMOBJPTR(WalkEngine);

OSG_END_NAMESPACE

#endif
