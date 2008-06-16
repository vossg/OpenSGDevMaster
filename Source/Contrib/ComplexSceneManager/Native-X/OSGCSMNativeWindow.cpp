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

#include "OSGCSMNativeWindow.h"
#include "OSGDrawer.h"
#include "OSGComplexSceneManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMNativeWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMNativeWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

bool                        CSMNativeWindow::_bRun        = false;
CSMNativeWindow::WindowList CSMNativeWindow::_vWindowList;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMNativeWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


static int waitMapNotify(Display *, XEvent *event, char *arg)
{
    return (event->type == MapNotify && event->xmap.window == (::Window) arg);
}

static UInt32 mapModifier(int iState)
{
    if(0x0000 != (iState & ShiftMask))
    {
        return MouseData::ShiftActive;
    }
    else if(0x0000 != (iState & ControlMask))
    {
        return MouseData::CtrlActive;
    }
    else if(0x0000 != (iState & Mod1Mask))
    {
        return MouseData::AltActive;
    }

    return 0x0001;
}

void CSMNativeWindow::xMainLoop(void)
{
    XEvent event;
    char   buffer[31];
    KeySym keysym;
    bool   bDoFrame = false;

    // Sleep 2 sec to open the window;
    //sleep(_uiCreateNapTime);
    sleep(1);

    while(_bRun == true)
    {
        WindowListIt      winIt  = _vWindowList.begin();
        WindowListConstIt winEnd = _vWindowList.end  ();
        
        while(winIt != winEnd)
        {
            Display *pDisplay = (*winIt)->getDisplay();

            while(XPending(pDisplay))
            {
                XNextEvent(pDisplay, &event);

                switch(event.type) 
                {
                    case KeyPress:           
                        
                        XLookupString(&event.xkey, buffer, 30, &keysym, NULL);
                        
                        fprintf(stderr, "%x\n", keysym);

                        if(keysym == XK_Escape) 
                        {
                            _bRun = false;
                            
                        }
                        else if((XK_space      <= keysym) && 
                                (XK_asciitilde >= keysym))
                        {
                            ComplexSceneManager::the()->key(
                                event.xkey.x,
                                event.xkey.y,
                                CSMKeyData::ButtonDown,
                                Char8(keysym));
                        }
                        break;


                    case ButtonPress:
                        
                        (*winIt)->mouse(event.xbutton.button - 1,
                                        MouseData::ButtonDown,
                                        mapModifier(event.xbutton.state) >> 1,
                                        event.xbutton.x,
                                        event.xbutton.y);

                        break;

                    case ButtonRelease:

                        (*winIt)->mouse(event.xbutton.button - 1,
                                        MouseData::ButtonUp,
                                        mapModifier(event.xbutton.state) >> 1,
                                        event.xbutton.x,
                                        event.xbutton.y);

                    break;

                    case MotionNotify:

                    (*winIt)->motion(event.xbutton.x, event.xbutton.y);

                    break;

                    case ConfigureNotify:
                    {
                        (*winIt)->reshape(event.xconfigure.width,
                                          event.xconfigure.height);
                    }                
                    break;

                    default:
                        break;
                }
                
            }
            
            ++winIt;
        }

        ComplexSceneManager::the()->frame();
        
        Thread::getCurrentChangeList()->commitChangesAndClear();
    }

    ComplexSceneManager::the()->terminate();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMNativeWindow::CSMNativeWindow(void) :
     Inherited(    ),
    _pXWindow (NULL)
{
}

CSMNativeWindow::CSMNativeWindow(const CSMNativeWindow &source) :
     Inherited(source),
    _pXWindow (NULL  )
{
}

CSMNativeWindow::~CSMNativeWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CSMNativeWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMNativeWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMNativeWindow NI" << std::endl;
}

bool CSMNativeWindow::init(void)
{
    Drawer *pDrawer = this->getParent();

    std::string szDisplayName = ":0.0";

    if(pDrawer != NULL)
    {
        szDisplayName = pDrawer->getDisplayString();
    }

    Display *pDisplay = XOpenDisplay(szDisplayName.c_str());

    fprintf(stderr, "Opened Display %p\n", pDisplay);
    
    if(pDisplay == NULL) 
    {
        fprintf(stderr, "Error: Could not open display: %s\n",
                szDisplayName.c_str());

        exit(0);
    }
    
    int iDummy;

    if(!glXQueryExtension(pDisplay, &iDummy, &iDummy))
    {
        fprintf(stderr, 
                "Error: X server has no OpenGL GLX extension: :0.0\n"); 

        exit(0);
    }

    int dblBuf[] = {GLX_RGBA, 
                    GLX_DEPTH_SIZE, 1, 
                    GLX_DOUBLEBUFFER, 
//                    (_pVSCWindow->stereo() == true) ? GLX_STEREO : None,
                    None};

    XVisualInfo          *vi = glXChooseVisual(pDisplay, 
                                               DefaultScreen(pDisplay), 
                                               dblBuf);

    if(vi == NULL) 
    {
        fprintf(stderr, "no RGB visual with depth buffer : :0.0");

        exit(0);
    }


    Colormap cmap = XCreateColormap(pDisplay, 
                                    RootWindow(pDisplay,
                                               vi->screen), 
                                    vi->visual, 
                                    AllocNone);

    XSetWindowAttributes swa;

    swa.colormap     = cmap;
    swa.border_pixel = 0;
    swa.event_mask   = 
        ExposureMask       | 
        ButtonPressMask    | 
        ButtonReleaseMask  |
        KeyPressMask       |
        Button1MotionMask  |
        Button2MotionMask  |
        Button3MotionMask  | 
        EnterWindowMask    |
        LeaveWindowMask    |
        FocusChangeMask    |
        StructureNotifyMask;
    swa.override_redirect = 0; 

    UInt32 uiWidth;
    UInt32 uiHeight;

    Int32  iXPos = 0;
    Int32  iYPos = 0;

    
    if(this->getXPos() > 0.f && this->getYPos() > 0.f)
    {
        iXPos = Int32(this->getXPos());
        iYPos = Int32(this->getYPos());
    }

    if(this->getXSize() >= 1.f) 
    {
        uiWidth = UInt32(this->getXSize());
    }
    else if(this->getXSize() <= 0.f)
    {
        uiWidth = DisplayWidth(pDisplay, vi->screen);
    }
    else
    {
        uiWidth = UInt32(Real32(DisplayWidth(pDisplay, vi->screen)) *
                         this->getXSize());
    }

    if(this->getYSize() >= 1.f)
    {
        uiHeight = UInt32(this->getYSize());
    }
    else if(this->getYSize() <= 0.f)
    {
        uiHeight = DisplayHeight(pDisplay, vi->screen);
    }
    else
    {
        uiHeight = UInt32(Real32(DisplayHeight(pDisplay, vi->screen)) *
                          this->getYSize());
    }

    fprintf(stderr, "Win size %d %d\n", uiWidth, uiHeight);

    ::Window pHWin = XCreateWindow( pDisplay,
                                    RootWindow(pDisplay,
                                               vi->screen),
                                    0, 
                                    0, 
                                    uiWidth, 
                                    uiHeight, 
                                    0,
                                    vi->depth,
                                    InputOutput, 
                                    vi->visual, 
                                    (CWBorderPixel | 
                                     CWColormap    | 
                                     CWEventMask   |
                                     CWOverrideRedirect),
                                   &swa);

    XFree(vi);

    Int32  argc   = 1;
    Char8 *argv[] = { "testCSM" };


    XSetStandardProperties(pDisplay, 
                           pHWin, 
                           "OpenSG - CSM", 
                           None,
                           None,
                           argv, 
                           argc, 
                           NULL);
        
    XMapWindow(pDisplay, pHWin);

    XMoveWindow(pDisplay, pHWin, iXPos, iYPos);

    if(this->getDecorEnabled() == false)
    {
        Atom noDecorAtom = XInternAtom(pDisplay, 
                                       "_MOTIF_WM_HINTS",
                                       0);

        if(noDecorAtom == None) 
        {
            fprintf(stderr,"Could not intern X atom for _MOTIF_WM_HINTS.\n");
        }

        struct NoDecorHints 
        {
            long flags;
            long functions;
            long decorations;
            long input_mode;
        };

        NoDecorHints oHints;
        
        oHints.flags = 2;
        oHints.decorations = 0;

        XChangeProperty(pDisplay, 
                        pHWin,
                        noDecorAtom, 
                        noDecorAtom, 
                        32,
                        PropModeReplace, 
                        (unsigned char *) &oHints, 4);
    }
    
    XEvent event;

    XIfEvent      (pDisplay, &event, waitMapNotify,  (char *) pHWin);
    XSetInputFocus(pDisplay,  pHWin, RevertToParent, CurrentTime);

    XWindowUnrecPtr pXWindow = OSG::XWindow::create();

    _pXWindow = pXWindow;

    _pXWindow->setDisplay(pDisplay);
    _pXWindow->setWindow (pHWin   );
    _pXWindow->init      (        );
    _pXWindow->resize    (uiWidth,
                          uiHeight);
    _pXWindow->deactivate(        );

    ComplexSceneManager::the()->setMainloop(&CSMNativeWindow::xMainLoop);
    
    _pWindow = _pXWindow;

//    _uiCreateNapTime = pNativeWindow->getSFCreateNapTime()->getValue();

    _vWindowList.push_back(this);

    _bRun = true;

    Inherited::init();

    return true;
}

OSG_END_NAMESPACE
