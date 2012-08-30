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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGLinux3AxisEventInterface.h"
#include "OSGThreadManager.h"
#include "OSGLinuxEventOptions.h"

#if defined(__linux)
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <sys/time.h>
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MPThreadType Linux3AxisEventInterface::_type(
    "Linux3AxisEventInterface",
    "OSGThread",
    static_cast<CreateThreadF>(Linux3AxisEventInterface::create),
    NULL);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

Linux3AxisEventInterface *Linux3AxisEventInterface::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<Linux3AxisEventInterface *>(pThread);
}

Linux3AxisEventInterface::ObjTransitPtr 
    Linux3AxisEventInterface::get(Char8 *szName, bool bGlobal) 
{
    BaseThreadTransitPtr pThread = ThreadManager::the()->getThread(
        szName,
        bGlobal,
        "Linux3AxisEventInterface");

    return dynamic_pointer_cast<Linux3AxisEventInterface>(pThread);
}


BaseThread *Linux3AxisEventInterface::create(const Char8  *szName, 
                                                   UInt32  uiId,
                                                   bool    bGlobal)
{
    return new Linux3AxisEventInterface(szName, uiId, bGlobal);
}

Linux3AxisEventInterface::Linux3AxisEventInterface(const Char8  *szName, 
                                                         UInt32  uiId,
                                                         bool    bGlobal) :
     Inherited(szName, 
               uiId,
               bGlobal),
    _rTxRange (450.f  ),
    _rTyRange (450.f  ),
    _rTzRange (450.f  ),
    _rRxRange (450.f  ),
    _rRyRange (450.f  ),
    _rRzRange (450.f  ),
    _iFileDesc(-1     ),
#ifdef __linux
    _rFds     (       ),
#endif
    _szPort   (       )
{
}

Linux3AxisEventInterface::~Linux3AxisEventInterface(void)
{
}

bool Linux3AxisEventInterface::start(void)
{
    bool returnValue = Inherited::start();

#if defined(__linux)

    if(_szPort.empty() == true)
        return false;    

    _iFileDesc = open(_szPort.c_str(), O_RDONLY); // | O_NONBLOCK);

    if(_iFileDesc == -1)
    {
        FWARNING(("Could not open device at %s\n", _szPort.c_str()));

        returnValue = false;
    }

#endif

    return returnValue;
}

void Linux3AxisEventInterface::shutdown(void)
{
#if defined(__linux)
    if(_iFileDesc != -1)
        ::close(_iFileDesc);
#endif
}

void Linux3AxisEventInterface::workProc(void)
{
    while(_bRunning == true)
    {
        getRawData();

        if(_uiNapTime > 0)
            osgSleep(_uiNapTime);
    }
}

#ifdef OSG_DEBUG_OLD_C_CASTS

// For my debugging, should not be active for any other case (GV)
#ifdef __FDMASK
# undef __FDMASK
# define __FDMASK(d)     (__fd_mask(1) << ((d) % __NFDBITS))
#endif
#ifdef __FD_MASK
# undef __FD_MASK
# define __FD_MASK(d) (__fd_mask(1) << ((d) % __NFDBITS))
#endif
#ifdef  __NFDBITS
# undef  __NFDBITS
# define __NFDBITS	(8 * int(sizeof (__fd_mask)))
#endif
#if defined(__FD_SET) && defined(__FD_ELT) && defined(__FD_MASK)
# undef __FD_SET
# define __FD_SET(d, set) \
    (void ((__FDS_BITS (set)[__FD_ELT (d)] |= __FD_MASK (d))))
#endif
#if  defined(__FD_CLR) && defined(__FD_ELT) && defined(__FD_MASK)
#  undef __FD_CLR
#  define __FD_CLR(d, set) \
    (void ((__FDS_BITS (set)[__FD_ELT (d)] &= ~__FD_MASK (d))))
#endif

#endif

void Linux3AxisEventInterface::getRawData(void)
{
    Int32 iBytesRead = 0;

#if defined(__linux)

    input_event ev[64];
 
    struct timeval tv;
    Int32  iSelRet = 0;

    FD_ZERO(&_rFds);
    FD_SET (_iFileDesc, &_rFds);

    tv.tv_sec  = 0;
    tv.tv_usec = 500000;
 
    iSelRet = select(_iFileDesc + 1, &_rFds, NULL, NULL, &tv);
 
    if(iSelRet > 0 && FD_ISSET(_iFileDesc, &_rFds) == true)
    {
        iBytesRead = read(_iFileDesc, ev, sizeof(input_event) * 64);
 
        if(iBytesRead > 0)
        {
            Inherited::lock();

            _bHasNewData = false;

            for (UInt32 i = 0;
                        i < UInt32(iBytesRead / sizeof(input_event));
                      ++i)
            {
                if(ev[i].type == EV_REL)
                {
                    if(ev[i].code == REL_X)
                    {
                        _vTranslate[0] = Real32(ev[i].value) / _rTxRange;
                    }
                    else if(ev[i].code == REL_Y)
                    {
                        _vTranslate[2] = Real32(ev[i].value) / _rTyRange;
                    }
                    else if(ev[i].code == REL_Z)
                    {
                        _vTranslate[1] = -(Real32(ev[i].value) / _rTzRange);
                    }
                    else if(ev[i].code == REL_RX)
                    {
                        _qRotate[0] =  Real32(ev[i].value) / _rRxRange;
                    }
                    else if(ev[i].code == REL_RY)
                    {
                        _qRotate[2] = Real32(ev[i].value) / _rRzRange;
                    }
                    else if(ev[i].code == REL_RZ)
                    {
                        _qRotate[1] =  -(Real32(ev[i].value) / _rRyRange);
                    }
                    
                }
            }
            
            _bHasNewData = true;
            
            Inherited::unlock();
        }
    }
#endif
}

void Linux3AxisEventInterface::setOptions(InterfaceOptions *pOptions)
{
    if(pOptions == NULL)
        return;

    Inherited::setOptions(pOptions);

    LinuxEventOptions *pOpts = 
        dynamic_cast<LinuxEventOptions *>(pOptions);

    if(pOpts != NULL)
    {
        _szPort = pOpts->getDevice();

        _rTxRange = pOpts->getTRange()[0];
        _rTyRange = pOpts->getTRange()[1];
        _rTzRange = pOpts->getTRange()[2];
        _rRxRange = pOpts->getRRange()[0];
        _rRyRange = pOpts->getRRange()[1];
        _rRzRange = pOpts->getRRange()[2];
    }
}

OSG_END_NAMESPACE
