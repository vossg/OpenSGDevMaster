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

#ifndef _OSGLINUX2AXISEVENTINTERFACE_H_
#define _OSGLINUX2AXISEVENTINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMouseDataDeviceInterface.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBCSM_DLLMAPPING Linux2AxisEventInterface : 
    public MouseDataDeviceInterface
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static Linux2AxisEventInterface *get (Char8 *szName);
    static Linux2AxisEventInterface *find(Char8 *szName);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    virtual bool start   (void);
    virtual void shutdown(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    virtual void setOptions(InterfaceOptions *pOptions);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MouseDataDeviceInterface  Inherited;

    static  MPThreadType             _type;

            Real32                   _rTxRange;
            Real32                   _rTyRange;

            Int32                    _iFileDesc;
            std::string              _szPort;

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static BaseThread *create(const Char8  *szName, 
                                    UInt32  uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    Linux2AxisEventInterface(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Linux2AxisEventInterface(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual void workProc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    void getRawData(void);

    /*! \}                                                                 */
   /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    Linux2AxisEventInterface(const Linux2AxisEventInterface &source);
    void operator =(const Linux2AxisEventInterface &source);
};

OSG_END_NAMESPACE

#include "OSGLinux2AxisEventInterface.inl"

#endif //_OSGLINUX2AXISEVENTINTERFACE_H_
