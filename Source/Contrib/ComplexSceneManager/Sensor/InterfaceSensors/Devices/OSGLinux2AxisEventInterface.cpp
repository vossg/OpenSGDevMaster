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

#include <OSGConfig.h>
#include <OSGLinux2AxisEventInterface.h>
#include <OSGThreadManager.h>
#include <OSGLinuxEventOptions.h>

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

#if defined(__linux)

struct usbspmdata
{
    short buttons;
    short x,y,z, a,b,c;
    short count;
    char type;                          /*| type of data package ... |*/
};

                          /* driver version */
#define USBSPM_GETVERSION            _IOR('3', 0x01, unsigned int)
                          /* read timeout value in 100ms steps */
#define USBSPM_GETTIMEOUT            _IOR('3', 0x02, unsigned int)
                          /* read timeout value */
#define USBSPM_SETTIMEOUT            _IOW('3', 0x03, unsigned int)
                          /* read product id */
#define USBSPM_GETPRODUCTID          _IOR('3', 0x04, unsigned int)
                          /* read vendor id */
#define USBSPM_GETVENDORID           _IOR('3', 0x05, unsigned int)
                          /* read current led status */
#define USBSPM_GETLED                _IOR('3', 0x06, unsigned int)
                          /* read current led status */
#define USBSPM_SETLED                _IOW('3', 0x07, unsigned int)
                          /* read current mode status */
#define USBSPM_GETMODE               _IOR('3', 0x08, unsigned int)
                          /* read current mode status */
#define USBSPM_SETMODE               _IOW('3', 0x09, unsigned int)
                          /* get product name */
#define USBSPM_GETPRODUCTSTRING      _IOR('3', 0x0A, char *)
                          /* read manufacturer name */
#define USBSPM_GETMANUFACTURERSTRING _IOR('3', 0x0B, char *) 
                          /* read firmware version */
#define USBSPM_GETFIRMWAREVERSION    _IOR('3', 0x0C, unsigned int)
                          /* sleep for 250ms */
#define USBSPM_250msDELAY            _IOR('3', 0x0D, unsigned int)
                          /* beep command */
#define USBSPM_BEEP                  _IOW('3', 0x0E, unsigned int)
                          /* rezero command */
#define USBSPM_REZERO                _IOW('3', 0x0F, unsigned int)

#endif

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

Linux2AxisEventInterface *Linux2AxisEventInterface::get(Char8 *szName) 
{
    BaseThread *pThread = ThreadManager::the()->getThread(
        szName,
        "Linux2AxisEventInterface");

    return dynamic_cast<Linux2AxisEventInterface *>(pThread);
}


BaseThread *Linux2AxisEventInterface::create(const Char8  *szName, 
                                                    UInt32  uiId)
{
    return new Linux2AxisEventInterface(szName, uiId);
}

Linux2AxisEventInterface::Linux2AxisEventInterface(const Char8  *szName, 
                                                           UInt32  uiId) :
     Inherited (szName, 
                uiId  ),
    _rTxRange  (1.f   ),
    _rTyRange  (1.f   ),
    _iFileDesc (-1    ),
    _szPort    (      )
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

    _iFileDesc = open(_szPort.c_str(), O_RDONLY | O_NONBLOCK);

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

        osgSleep(_uiNapTime);
    }
}

void Linux2AxisEventInterface::getRawData(void)
{
    Int32 iBytesRead = 0;

#if defined(__linux)

    input_event ev[64];
 
    iBytesRead = read(_iFileDesc, ev, sizeof(input_event) * 64);
 
    if(iBytesRead > 0)
    {
        Inherited::lock();

        _bHasNewData = false;

        Int32 iButton      = -1;
        Int32 iButtonState = -1;

        Real32 rX = 0.5f;
        Real32 rY = 0.5f;

        bool  bSetButton   = false;

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
            }
            else if(ev[i].type == EV_REL)
            {
                switch(ev[i].code)
                {
                    case REL_X:
                        rX = ev[i].value;
                        break;
                    case REL_Y:
                        rY = ev[i].value;
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

//        rX = -rX / 100.f;
//        rY =  rY / 100.f;

        rX /= _rTxRange;
        rY /= _rTyRange;

        if(bSetButton == true)
        {
            _oMouseData.setData(iButton,
                                iButtonState,
                                MouseData::NoModifier,
                                rX, 
                                rY,
                                NULL,
                                MouseData::RelValues);
        }
        else
        {
            _oMouseData.setData(rX, 
                                rY,
                                NULL,
                                MouseData::RelValues);
        }

        _bHasNewData = true;
        
        Inherited::unlock();
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
    }
}

OSG_END_NAMESPACE
