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
#include "OSGLinux2AxisEventInterface.h"
#include "OSGThreadManager.h"
#include "OSGLinuxEventOptions.h"

#if defined(__linux)
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MPThreadType Linux2AxisEventInterface::_type(
    "Linux2AxisEventInterface",
    "OSGThread",
    static_cast<CreateThreadF>(Linux2AxisEventInterface::create),
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

Linux2AxisEventInterface *Linux2AxisEventInterface::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<Linux2AxisEventInterface *>(pThread);
}

Linux2AxisEventInterface::ObjTransitPtr 
    Linux2AxisEventInterface::get(Char8 *szName, bool bGlobal) 
{
    BaseThreadTransitPtr pThread = ThreadManager::the()->getThread(
        szName,
        bGlobal,
        "Linux2AxisEventInterface");

    return dynamic_pointer_cast<Linux2AxisEventInterface>(pThread);
}


BaseThread *Linux2AxisEventInterface::create(const Char8  *szName, 
                                                   UInt32  uiId,
                                                   bool    bGlobal)
{
    return new Linux2AxisEventInterface(szName, uiId, bGlobal);
}

Linux2AxisEventInterface::Linux2AxisEventInterface(const Char8  *szName, 
                                                         UInt32  uiId,
                                                         bool    bGlobal) :
     Inherited (szName, 
                uiId,
                bGlobal),
    _rTxRange  (1.f    ),
    _rTyRange  (1.f    ),
    _iFileDesc (-1     ),
#ifdef __linux
    _rFds      (       ),
#endif
    _szPort    (       )
{
}

Linux2AxisEventInterface::~Linux2AxisEventInterface(void)
{
}

bool Linux2AxisEventInterface::start(void)
{
    bool returnValue = Inherited::start();

#if defined(__linux)

    if(_szPort.empty() == true)
        return false;    

    _iFileDesc = open(_szPort.c_str(), O_RDONLY); // | O_NONBLOCK);

    if(_iFileDesc == -1)
    {
        returnValue = false;
    }

#endif

    return returnValue;
}

void Linux2AxisEventInterface::shutdown(void)
{
#if defined(__linux)
    if(_iFileDesc != -1)
        ::close(_iFileDesc);
#endif
}

void Linux2AxisEventInterface::workProc(void)
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
#undef __FDMASK
#define __FDMASK(d)     (__fd_mask(1) << ((d) % __NFDBITS))
#endif
#endif

void Linux2AxisEventInterface::getRawData(void)
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

            Int32 iButton      = -1;
            Int32 iButtonState = -1;

            Real32 rX = 0.0f;
            Real32 rY = 0.0f;

            bool  bSetButton   = false;
            
            bool  bGotData     = false;

            for (UInt32 i = 0;
                        i < UInt32(iBytesRead / sizeof(input_event));
                      ++i)
            {
                if(ev[i].type == EV_KEY)
                {
                    switch(ev[i].code)
                    {
                        case BTN_LEFT:
                            iButton = MouseData::LeftButton;
                            break;
                        case BTN_RIGHT:
                            iButton = MouseData::RightButton;
                            break;
                        case BTN_MIDDLE:
                            iButton = MouseData::MiddleButton;
                            break;
                        default:
                            break;
                    }
                    
                    iButtonState = 1 - ev[i].value;
                    bSetButton   = true;
                    bGotData     = true;
                }
                else if(ev[i].type == EV_REL)
                {
                    switch(ev[i].code)
                    {
                        case REL_X:
                            rX = ev[i].value;
                            bGotData = true;
                            break;
                        case REL_Y:
                            rY = ev[i].value;
                            bGotData = true;
                            break;
                        default:
                            break;
                    }
                    
                }
                else if(ev[i].type == EV_SYN)
                {
                    break;
                }
            }
            
            if(bGotData == true)
            {
                MouseData tmpElem;

                rX /= _rTxRange;
                rY /= _rTyRange;
            
                if(bSetButton == true)
                {
                    tmpElem.setData(iButton,
                                    iButtonState,
                                    MouseData::NoModifier,
                                    rX, 
                                    rY,
                                    NULL,
                                    MouseData::RelValues);
                }
                else
                {
                    tmpElem.updateData(rX, 
                                       rY,
                                       NULL,
                                       MouseData::RelValues);
                }
                
                _cbMouseData.push_back(tmpElem);

                _bHasNewData = true;
            }

            Inherited::unlock();
        }
    }
#endif
}

void Linux2AxisEventInterface::setOptions(InterfaceOptions *pOptions)
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

        _cbMouseData.set_capacity(pOpts->getBufferSize());
    }
}

OSG_END_NAMESPACE
