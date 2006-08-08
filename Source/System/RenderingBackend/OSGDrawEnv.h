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

#ifndef _OSGDRAWENV_H_
#define _OSGDRAWENV_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGSystemProfile.h"

OSG_BEGIN_NAMESPACE

class RenderTraversalActionBase;
class DrawActionBase;

class Window;
class Viewport;
class State;
class StateOverride;


/*! \ingroup GrpSystemRenderingBackend
*/

class OSG_SYSTEM_DLLMAPPING DrawEnv 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef RenderTraversalActionBase RTAction;
    typedef DrawActionBase            RAction;

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    void setAction       (      RAction  *pAction    );
    void setAction       (      RTAction *pAction    );
    void setViewport     (      Viewport *pViewport  );
    void setWindow       (      Window   *pWindow    );

    void setupProjection (const Matrixr  &projection,
                          const Matrixr  &translation);
    void setupViewing    (const Matrixr  &matrix     );
    void setObjectToWorld(const Matrixr  &matrix     );

    void setCameraNear   (const Real     &camNear    ); 
    void setCameraFar    (const Real     &camFar     ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    const Matrixr  &getCameraFullProjection (void) const;
    const Matrixr  &getCameraProjection     (void) const;
    const Matrixr  &getCameraProjectionTrans(void) const;

    const Matrixr  &getCameraViewing        (void) const;
    const Matrixr  &getCameraToWorld        (void) const; //CamViewing^-1
    const Matrixr  &getObjectToWorld        (void) const;

          Real      getCameraNear           (void) const;
          Real      getCameraFar            (void) const;

          RAction  *getRAction              (void) const;
          RTAction *getRTAction             (void) const;
          Viewport *getViewport             (void) const;
          Window   *getWindow               (void) const;
               
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void clearState(void);

    void activateState  (State         *pNewState,
                         StateOverride *pNewStateOverride);

    void deactivateState(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DrawEnv(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawEnv(void); 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    RAction       *_pRAction;
    RTAction      *_pRTAction;

    Matrixr        _cameraFullProjection;
    Matrixr        _cameraProjection;
    Matrixr        _cameraProjectionTrans;
    Matrixr        _cameraViewing;
    Matrixr        _cameraToWorld;
    Matrixr        _objectToWorld;

    Real           _cameraNear;
    Real           _cameraFar;

    Window        *_pWindow;
    Viewport      *_pViewport;
    
    State         *_pActiveState;
    StateOverride *_pActiveStateOverride;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    void activate  (State         *pState     );
    void activate  (State         *pState,
                    StateOverride *pOverride  );

    void changeTo  (State         *pState, 
                    State         *old        );

    void changeTo  (State         *pState, 
                    State         *old,
                    StateOverride *oldOverride);

    void changeTo  (State         *pState, 
                    StateOverride *pOverride,
                    State         *old);

    void changeTo  (State         *pState, 
                    StateOverride *pOverride,
                    State         *old,
                    StateOverride *oldOverride);

    void deactivate(State         *pState);
    void deactivate(State         *pState,
                    StateOverride *pOverride  );


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class DrawEnvFactory;

    /*! \brief prohibit default function (move to 'public' if needed) */
    DrawEnv(const DrawEnv &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const DrawEnv &source);
};

OSG_END_NAMESPACE

#include "OSGDrawEnv.inl"

#define OSGDRAWENV_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDRAWENV_H_ */
