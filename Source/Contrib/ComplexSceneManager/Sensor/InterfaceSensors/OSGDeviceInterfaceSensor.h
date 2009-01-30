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

#ifndef _OSGDEVICEINTERFACESENSOR_H_
#define _OSGDEVICEINTERFACESENSOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGInterfaceOptions.h"
#include "OSGDeviceInterfaceSensorBase.h"
#include "OSGDeviceInterface.h"

OSG_BEGIN_NAMESPACE

/*! \brief DeviceInterfaceSensor class. See \ref
           PageContribCSMDeviceInterfaceSensor for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING DeviceInterfaceSensor : 
    public DeviceInterfaceSensorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DeviceInterfaceSensorBase Inherited;
    typedef DeviceInterfaceSensor     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual bool init    (void);
    virtual void shutdown(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TimeSensorBase.

    DeviceInterfaceRefPtr _pDevice;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DeviceInterfaceSensor(void);
    DeviceInterfaceSensor(const DeviceInterfaceSensor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DeviceInterfaceSensor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DeviceInterfaceSensorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DeviceInterfaceSensor &source);
};

typedef DeviceInterfaceSensor *DeviceInterfaceSensorP;

OSG_END_NAMESPACE

#include "OSGDeviceInterfaceSensorBase.inl"
#include "OSGDeviceInterfaceSensor.inl"

#endif /* _OSGDEVICEINTERFACESENSOR_H_ */
