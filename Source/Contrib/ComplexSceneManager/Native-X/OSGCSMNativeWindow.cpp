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

#include "OSGCSMNativeWindow.h"
#include "OSGCSMDrawer.h"
#include "OSGComplexSceneManager.h"
#ifdef OSG_NEW_SHADER
#include "OSGShaderCache.h"
#endif
#include "OSGGLFuncProtos.h"

#include <X11/keysym.h>

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
    typedef ::Window GlobalWinType;

    return (event->type == MapNotify && 
            event->xmap.window == reinterpret_cast<GlobalWinType>(arg));
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

    // Sleep 2 sec to open the window;
    //sleep(_uiCreateNapTime);
    //sleep(1);
    osgSleep(100);

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
                        
#if 0
                        fprintf(stderr, "%x %x %x\n", 
                                keysym, 
                                XK_F12,
                                XK_Home);
#endif

                        if(keysym == XK_Escape) 
                        {
                            _bRun = false;
                            
                        }
                        else if(keysym == XK_End)
                        {
#ifdef OSG_NEW_SHADER
                            fprintf(stderr, "Dump\n");

                            (*winIt)->getWindow()->getShaderCache()->dump();
#endif
                        }
                        else if(keysym == XK_F12) 
                        {
                            FieldContainerFactory::the()->dump();
                        }
                        else if(keysym == XK_Home) 
                        {
                            ComplexSceneManager::the()->resetScene();
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

                    case KeyRelease:           
                        
                        XLookupString(&event.xkey, buffer, 30, &keysym, NULL);
                        
                        //fprintf(stderr, "%x\n", keysym);

                        if(keysym == XK_Escape) 
                        {
                        }
                        else if((XK_space      <= keysym) && 
                                (XK_asciitilde >= keysym))
                        {
                            ComplexSceneManager::the()->key(
                                event.xkey.x,
                                event.xkey.y,
                                CSMKeyData::ButtonUp,
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
    _pXWindow (NULL),
    _pDisplay (NULL)
{
}

CSMNativeWindow::CSMNativeWindow(const CSMNativeWindow &source) :
     Inherited(source),
    _pXWindow (NULL  ),
    _pDisplay (NULL  )
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

void CSMNativeWindow::resolveLinks(void)
{
    Inherited::resolveLinks();
}

void CSMNativeWindow::terminateGLContext(void)
{
    if(_pXWindow != NULL)
    {
        _pXWindow->terminate();
    }

    if(_pDisplay != NULL)
    {
        ::Window oHWin = _pXWindow->getWindow();
        
        if(oHWin != 0)
        {
            XDestroyWindow(_pDisplay, oHWin);
        }

        XCloseDisplay(_pDisplay);

        _pXWindow->setDisplay(NULL);
        _pXWindow->setWindow (0   );
    }
}

#ifdef OSG_DEBUG_OLD_C_CASTS
#ifdef ScreenOfDisplay
#undef ScreenOfDisplay
#endif
#ifdef DefaultScreen
#undef DefaultScreen
#endif
#define ScreenOfDisplay(dpy, scr)(&(_XPrivDisplay(dpy))->screens[scr])
#define DefaultScreen(dpy) 	((_XPrivDisplay(dpy))->default_screen)
#endif

bool CSMNativeWindow::init(void)
{
    CSMDrawer *pDrawer = this->getParent();

    std::string szDisplayName = ":0.0";

    if(pDrawer != NULL)
    {
        szDisplayName = pDrawer->getDisplayString();
    }

    _pDisplay = XOpenDisplay(szDisplayName.c_str());

    //fprintf(stderr, "Opened Display %p\n", _pDisplay);
    
    if(_pDisplay == NULL) 
    {
        fprintf(stderr, "Error: Could not open display: %s\n",
                szDisplayName.c_str());

        exit(0);
    }
    
    int iDummy;

    if(!glXQueryExtension(_pDisplay, &iDummy, &iDummy))
    {
        fprintf(stderr, 
                "Error: X server has no OpenGL GLX extension: :0.0\n"); 

        exit(0);
    }

    XWindowUnrecPtr  pXWindow = OSG::XWindow::create();
    XVisualInfo     *vi       = NULL;

    pXWindow->setRequestMajor     (this->getRequestMajor     ());
    pXWindow->setRequestMinor     (this->getRequestMinor     ());

    UInt32 uiDrawMode = this->getPartitionDrawMode();

    if(ComplexSceneManager::the()->getDrawManager()->getParallel() == true)
    {
        uiDrawMode |= Window::ParallelDrawer;
    }
    else
    {
        uiDrawMode |= Window::StdDrawer;
    }
    
    pXWindow->setPartitionDrawMode(uiDrawMode);
    pXWindow->setDrawerType       (uiDrawMode);

    Int32 iFlags = 0;

    if(this->getEnableForwardCompatContext() == true)
    {
        if(this->getRequestMajor() >= 3)
        {
            iFlags |= GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
        }
        else
        {
            FWARNING(("forward compat contexts require OpenGL major "
                      "> 3.0, requested %d\n", 
                      this->getRequestMajor()));
        }
    }

    if(this->getEnableDebugContext() == true)
    {
        iFlags |= GLX_CONTEXT_DEBUG_BIT_ARB;
    }

    if(iFlags != 0)
        pXWindow->setContextFlags(iFlags);

    OSGGETGLFUNCBYNAME(OSGglxChooseFBConfigProc, 
                       osgGlxChooseFBConfig,
                       "glXChooseFBConfig",
                       pXWindow);
    
    if(osgGlxChooseFBConfig == NULL)
    {
        std::vector<int> viForm;

        viForm.push_back(GLX_RGBA);
        viForm.push_back(GLX_DEPTH_SIZE);
        viForm.push_back(1); 
        viForm.push_back(GLX_DOUBLEBUFFER);

        if(_sfRequestSamples.getValue() > 0)
        {
            viForm.push_back(GLX_SAMPLE_BUFFERS_ARB);
            viForm.push_back(True);

            viForm.push_back(GLX_SAMPLES_ARB);
            viForm.push_back(_sfRequestSamples.getValue());
        }

        if(this->requestStereoVisual() == true)
        {
            fprintf(stderr, "Choose stereo visual\n");
            viForm.push_back(GLX_DOUBLEBUFFER); 
            viForm.push_back(True);
        }

        viForm.push_back(None);

#if 0
        int dblBuf[] = {GLX_RGBA, 
                        GLX_DEPTH_SIZE, 1, 
                        GLX_DOUBLEBUFFER, 
//                    (_pVSCWindow->stereo() == true) ? GLX_STEREO : None,
                        None};
#endif
        
        vi = glXChooseVisual(_pDisplay, 
                              DefaultScreen(_pDisplay), 
                             &(viForm.front()));
    }
    else
    {
        int iMatching;

#if 0
        int fbAttr[] =
        {
            GLX_RENDER_TYPE,   GLX_RGBA_BIT,
            GLX_RED_SIZE,      8,
            GLX_GREEN_SIZE,    8,
            GLX_BLUE_SIZE,     8,
            GLX_ALPHA_SIZE,    8,
            GLX_DEPTH_SIZE,    8,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_DOUBLEBUFFER,  True,
            GLX_X_RENDERABLE,  True,
            None
        };
#endif

        std::vector<int> fbAttr;
        
        fbAttr.push_back(GLX_RENDER_TYPE);
        fbAttr.push_back(GLX_RGBA_BIT);

        fbAttr.push_back(GLX_RED_SIZE);
        fbAttr.push_back(8);
        
        fbAttr.push_back(GLX_GREEN_SIZE);
        fbAttr.push_back(8);

        fbAttr.push_back(GLX_BLUE_SIZE);
        fbAttr.push_back(8);

        fbAttr.push_back(GLX_ALPHA_SIZE);
        fbAttr.push_back(8);

        fbAttr.push_back(GLX_DEPTH_SIZE);
        fbAttr.push_back(8);

        fbAttr.push_back(GLX_DRAWABLE_TYPE);
        fbAttr.push_back(GLX_WINDOW_BIT);

        fbAttr.push_back(GLX_DOUBLEBUFFER);
        fbAttr.push_back(True);

        fbAttr.push_back(GLX_X_RENDERABLE);
        fbAttr.push_back(True);

        if(_sfRequestSamples.getValue() > 0)
        {
            fbAttr.push_back(GLX_SAMPLE_BUFFERS_ARB);
            fbAttr.push_back(True);

            fbAttr.push_back(GLX_SAMPLES_ARB);
            fbAttr.push_back(_sfRequestSamples.getValue());
        }

        if(this->requestStereoVisual() == true)
        {
            fprintf(stderr, "FBConfig stereo\n");
            fbAttr.push_back(GLX_STEREO);
            fbAttr.push_back(True);
        }

        fbAttr.push_back(None);

        GLXFBConfig *fbConfigs = 
            osgGlxChooseFBConfig( _pDisplay,
                                   DefaultScreen(_pDisplay),
                                 &(fbAttr.front()),
                                 & iMatching);
        
        if(iMatching > 0)
        {
            vi = glXGetVisualFromFBConfig(_pDisplay, fbConfigs[0]);
            
            int iId;
            
            glXGetFBConfigAttrib( _pDisplay, 
                                   fbConfigs[0], 
                                   GLX_FBCONFIG_ID, 
                                 & iId);
            
            pXWindow->setFbConfigId(iId);

            XFree(fbConfigs);
        }
    }

    if(vi == NULL) 
    {
        fprintf(stderr, "no RGB visual with depth buffer : :0.0");

        exit(0);
    }


    Colormap cmap = XCreateColormap(_pDisplay, 
                                    RootWindow(_pDisplay,
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
        KeyReleaseMask     |
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
        uiWidth = DisplayWidth(_pDisplay, vi->screen);
    }
    else
    {
        uiWidth = UInt32(Real32(DisplayWidth(_pDisplay, vi->screen)) *
                         this->getXSize());
    }

    if(this->getYSize() >= 1.f)
    {
        uiHeight = UInt32(this->getYSize());
    }
    else if(this->getYSize() <= 0.f)
    {
        uiHeight = DisplayHeight(_pDisplay, vi->screen);
    }
    else
    {
        uiHeight = UInt32(Real32(DisplayHeight(_pDisplay, vi->screen)) *
                          this->getYSize());
    }

    


//    fprintf(stderr, "Win size %d %d at %d %d\n", 
//            uiWidth, uiHeight, iXPos, iYPos);

    ::Window pHWin = XCreateWindow(_pDisplay,
                                    RootWindow(_pDisplay,
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
    const Char8 *argv[] = { "testCSM" };


    XSetStandardProperties(_pDisplay, 
                            pHWin, 
                            "OpenSG - CSM", 
                            None,
                            None,
                            const_cast<Char8 **>(argv), 
                            argc, 
                            NULL);
        
    XMapWindow(_pDisplay, pHWin);

    if(this->getDecorEnabled() == false)
    {
        Atom noDecorAtom = XInternAtom(_pDisplay, 
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

        XChangeProperty(_pDisplay, 
                         pHWin,
                         noDecorAtom, 
                         noDecorAtom, 
                         32,
                         PropModeReplace, 
                         reinterpret_cast<unsigned char *>(&oHints), 4);
    }
    
    XEvent event;

    XIfEvent      (_pDisplay, 
                    &event, 
                    waitMapNotify,  
                    reinterpret_cast<char *>(pHWin));

    XSetInputFocus(_pDisplay,  pHWin, RevertToParent, CurrentTime);


    _pXWindow = pXWindow;

    _pXWindow->setDisplay(_pDisplay);
    _pXWindow->setWindow ( pHWin   );
    _pXWindow->init      (         );
    _pXWindow->resize    ( uiWidth,
                           uiHeight);

    std::string windowName("OpenSG - CSM - ");

#if 0
    _pXWindow->activate();

    windowName += reinterpret_cast<const char *>(glGetString(GL_VERSION));
    windowName += " - ";
    windowName += reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    _pXWindow->deactivate();
#endif

    windowName += _pXWindow->getRendererInfo();

    XStoreName(_pDisplay, pHWin, windowName.c_str());

    if(ComplexSceneManager::the() != NULL)
        ComplexSceneManager::the()->setMainloop(&CSMNativeWindow::xMainLoop);
    
    _pWindow = _pXWindow;

//    _uiCreateNapTime = pNativeWindow->getSFCreateNapTime()->getValue();

    _vWindowList.push_back(this);

    _bRun = true;

    XMoveResizeWindow(_pDisplay, pHWin, 
                      iXPos, iYPos,
                      uiWidth, uiHeight);

    Inherited::init();

//    _pXWindow->deactivate(         );

    return true;
}

OSG_END_NAMESPACE
