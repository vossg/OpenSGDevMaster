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

#ifndef _OSGFRAMETASKINTERFACE_H_
#define _OSGFRAMETASKINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicsDef.h"
#include "OSGBaseTypes.h"
#include "OSGTime.h"

OSG_BEGIN_NAMESPACE

/*! \brief FrameTask class. See \ref
           PageDynamicsFrameTask for a description.
    \ingroup GrpDynamicsBaseObj
    \ingroup GrpLibOSGDynamics
 */

class OSG_DYNAMICS_DLLMAPPING FrameTaskInterface
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FrameTaskInterface Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual bool  init       (void                      );
    virtual void  frame      (Time oTime, UInt32 uiFrame) = 0;
    virtual void  shutdown   (void                      );

    virtual Int32 getPriority(void                      ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FrameTaskBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FrameTaskInterface(void);
    FrameTaskInterface(const FrameTaskInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FrameTaskInterface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FrameTaskInterface &source);
};

typedef FrameTaskInterface *FrameTaskInterfaceP;

OSG_END_NAMESPACE

#endif /* _OSGFRAMETASKINTERFACE_H_ */
