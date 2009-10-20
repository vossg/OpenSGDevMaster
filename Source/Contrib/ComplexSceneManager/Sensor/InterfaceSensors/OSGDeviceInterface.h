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

#ifndef _OSGDEVICEINTERFACE_H_
#define _OSGDEVICEINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGThread.h"
#include "OSGLock.h"
#include "OSGContribCSMDef.h"

OSG_BEGIN_NAMESPACE

class InterfaceOptions;

class OSG_CONTRIBCSM_DLLMAPPING DeviceInterface : public Thread
{

    /*==========================  PUBLIC  =================================*/

  public:

    OSG_GEN_INTERNAL_MEMOBJPTR(DeviceInterface);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    virtual bool start   (void);
    virtual void stop    (void);
    virtual void shutdown(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

            bool isRunning   (void);
            bool hasNewData  (void);
    virtual void clearNewData(void);

    void lock        (void);
    void unlock      (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    virtual void setOptions(InterfaceOptions *pOptions);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef  Thread      Inherited;

             LockRefPtr _pDataLock;
    volatile bool       _bRunning;
             bool       _bHasNewData;
             UInt32     _uiNapTime;
    
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    DeviceInterface(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DeviceInterface(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
   /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    DeviceInterface(const DeviceInterface &source);
    void operator =(const DeviceInterface &source);
};

OSG_GEN_MEMOBJPTR(DeviceInterface);

OSG_END_NAMESPACE

#include "OSGDeviceInterface.inl"

#endif // _OSGDEVICEINTERFACE_H_
