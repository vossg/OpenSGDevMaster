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

#ifndef _OSGLINUX3AXISEVENTINTERFACE_H_
#define _OSGLINUX3AXISEVENTINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTransformationDeviceInterface.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBCSM_DLLMAPPING Linux3AxisEventInterface : 
    public TransformationDeviceInterface
{

    /*==========================  PUBLIC  =================================*/

  public:

    OSG_GEN_INTERNAL_MEMOBJPTR(Linux3AxisEventInterface);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static ObjTransitPtr             get (Char8 *szName, bool bGlobal);
    static Linux3AxisEventInterface *find(Char8 *szName);

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

    typedef TransformationDeviceInterface  Inherited;

    static  MPThreadType                  _type;

            Real32                        _rTxRange;
            Real32                        _rTyRange;
            Real32                        _rTzRange;
            Real32                        _rRxRange;
            Real32                        _rRyRange;
            Real32                        _rRzRange;

            Int32                         _iFileDesc;
#ifdef __linux
            fd_set                        _rFds;
#endif
            std::string                   _szPort;


    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static BaseThread *create(const Char8  *szName, 
                                    UInt32  uiId,
                                    bool    bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    Linux3AxisEventInterface(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Linux3AxisEventInterface(void); 

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
    Linux3AxisEventInterface(const Linux3AxisEventInterface &source);
    void operator =(const Linux3AxisEventInterface &source);
};

OSG_GEN_MEMOBJPTR(Linux3AxisEventInterface);

OSG_END_NAMESPACE

#include "OSGLinux3AxisEventInterface.inl"

#endif //_OSGLINUX3AXISEVENTINTERFACE_H_
