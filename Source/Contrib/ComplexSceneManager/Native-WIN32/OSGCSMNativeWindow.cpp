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
#include "OSGComplexSceneManager.h"

#define OSG_REG_CLASS_PERWINDOW 1

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


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMNativeWindow::CSMNativeWindow(void) :
     Inherited   (    ),
    _pWin32Window(NULL),
    _pHWND       (NULL)
{
}

CSMNativeWindow::CSMNativeWindow(const CSMNativeWindow &source) :
     Inherited   (source),
    _pWin32Window(NULL  ),
    _pHWND       (NULL  )
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

struct WindowBinderHWNDCompare
{
    HWND _rhs;

    bool operator()(CSMNativeWindow *pBinder)
    {
        return pBinder->getHWND() == _rhs;
    }
};

CSMNativeWindow *CSMNativeWindow::findWindowBy(HWND hwnd)
{
    CSMNativeWindow         *returnValue = NULL;
    WindowBinderHWNDCompare  oCmp;

    oCmp._rhs = hwnd;

    WindowListIt wIt = std::find_if(_vWindowList.begin(),
                                    _vWindowList.end  (),
                                     oCmp);

    if(wIt != _vWindowList.end())
    {
        returnValue = *wIt;
    }

    return returnValue;
}


LRESULT CALLBACK  CSMNativeWindow::WndProc(HWND   hwnd, 
                                           UINT   uMsg,
                                           WPARAM wParam, 
                                           LPARAM lParam)
{
    CSMNativeWindow *pNWin = CSMNativeWindow::findWindowBy(hwnd);

    switch(uMsg)
    {       
        case WM_LBUTTONDOWN:

            if(pNWin != NULL)
            {
                pNWin->mouse(MouseData::LeftButton,
                             MouseData::ButtonDown,
                             0,
                             LOWORD(lParam),
                             HIWORD(lParam));
            }
            break;

        case WM_MBUTTONDOWN:

            if(pNWin != NULL)
            {
                pNWin->mouse(MouseData::MiddleButton,
                             MouseData::ButtonDown,
                             0,
                             LOWORD(lParam),
                             HIWORD(lParam));
            }
            break;

        case WM_RBUTTONDOWN:

            if(pNWin != NULL)
            {
                pNWin->mouse(MouseData::RightButton,
                             MouseData::ButtonDown,
                             0,
                             LOWORD(lParam),
                             HIWORD(lParam));
            }
            break;   

        case WM_LBUTTONUP:

            if(pNWin != NULL)
            {
                pNWin->mouse(MouseData::LeftButton,
                             MouseData::ButtonUp,
                             0,
                             LOWORD(lParam),
                             HIWORD(lParam));
            }
            break;              

        case WM_MBUTTONUP:

            if(pNWin != NULL)
            {
                pNWin->mouse(MouseData::MiddleButton,
                             MouseData::ButtonUp,
                             0,
                             LOWORD(lParam),
                             HIWORD(lParam));
            }
            break;

        case WM_RBUTTONUP:

            if(pNWin != NULL)
            {
                pNWin->mouse(MouseData::RightButton,
                             MouseData::ButtonUp,
                             0,
                             LOWORD(lParam),
                             HIWORD(lParam));
            }
            break;

        case WM_MOUSEMOVE:

            if(pNWin != NULL)
            {
                pNWin->motion(LOWORD(lParam),
                              HIWORD(lParam));
            }
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
                                    
        case WM_KEYDOWN:

            if((int) wParam == VK_ESCAPE)
            {
                _bRun = false;
            }
            else
            {
#if 0
                fprintf(stderr, "%WM_KEYDOWN : d\n", (int) wParam);
#endif

                ComplexSceneManager::the()->key(
                    0,
                    0,
                    CSMKeyData::ButtonDown,
                    Char8(wParam));
            }
            break;

        case WM_KEYUP:

            if((int) wParam == VK_ESCAPE)
            {
                _bRun = false;
            }
            else
            {
#if 0
                fprintf(stderr, "%WM_KEYUP : %d (%c)\n", 
                        Int32(wParam),
                        Char8(wParam));
#endif

                ComplexSceneManager::the()->key(
                    0,
                    0,
                    CSMKeyData::ButtonUp,
                    Char8(wParam));
            }
            break;
            
        case WM_CHAR:
            fprintf(stderr, "WM_CHAR : %d\n", (int) wParam);
            break;

        case WM_SIZE:
            if(pNWin != NULL)
            {
                pNWin->reshape(LOWORD(lParam), HIWORD(lParam));
            }
            break;
                                    
        case WM_CREATE:
        {
            CREATESTRUCT          *pCStruct;

            pCStruct = (LPCREATESTRUCT)lParam;
            
            CSMNativeWindow UNALIGNED *pWin =
                (CSMNativeWindow UNALIGNED *) pCStruct->lpCreateParams;

            if(pWin != NULL)
            {
                PIXELFORMATDESCRIPTOR  pfd;    
                HDC                    hDC;

                int                   iPixelFormat;
                
                memset(&pfd, 0, sizeof(pfd));
                
                pfd.nSize = sizeof(pfd);
                pfd.nVersion = 1;
                
                pfd.dwFlags = 
                    PFD_DRAW_TO_WINDOW | 
                    PFD_SUPPORT_OPENGL | 
                    PFD_DOUBLEBUFFER;
                
                pfd.iPixelType = PFD_TYPE_RGBA;
                pfd.iLayerType = PFD_MAIN_PLANE;
                pfd.cDepthBits = 16;            
                
                WIN32Window *pOSGWin = pWin->_pWin32Window;
                
                pOSGWin->setHwnd(hwnd);
                
                // init the OSG window  
                hDC = GetDC(hwnd);
                
                iPixelFormat = ChoosePixelFormat(hDC, &pfd);
                
                SetPixelFormat(hDC, iPixelFormat, &pfd);    
                
//            win->setHDC ( hDC );
                
                pOSGWin->init();
                pOSGWin->deactivate();
            }
        }
        break;

        case WM_CLOSE:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void OSG_APIENTRY CSMNativeWindow::win32MainLoop(void)
{
    MSG           msg;

    // main loop 
    while(_bRun == true)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
            DispatchMessage(&msg);

        ComplexSceneManager::the()->frame();
        
        Thread::getCurrentChangeList()->commitChangesAndClear();
    }

    ComplexSceneManager::the()->terminate();

   
#if !defined(OSG_REG_CLASS_PERWINDOW)
    if(!UnregisterClass("OSG-CSM",
                        GetModuleHandle(NULL)))
    {
        fprintf(stderr, "unregister window class failed %ld\n", 
                GetLastError());
    }
#else
    WindowListConstIt wIt  = _vWindowList.begin();
    WindowListConstIt wEnd = _vWindowList.end  ();

    for(; wIt != wEnd; ++wIt)
    {
        Char8 szClassName[64];

        sprintf(szClassName, "OSG-CSM-%x", *wIt);

        fprintf(stderr, "deregister %s\n", szClassName);

        if(!UnregisterClass(szClassName,
                            GetModuleHandle(NULL)))
        {
            fprintf(stderr, "unregister window class failed %ld\n", 
                    GetLastError());
        }
    }
#endif
}

void CSMNativeWindow::resolveLinks(void)
{
    Inherited::resolveLinks();
}

void CSMNativeWindow::terminateGLContext(void)
{
    if(_pWin32Window != NULL)
    {
        _pWin32Window->terminate();
    }

    DestroyWindow(_pHWND);

    _pHWND = NULL;
}
bool CSMNativeWindow::init(void)
{
    WIN32WindowUnrecPtr pWin32Win = OSG::WIN32Window::create();

    _pWin32Window = pWin32Win;
    _pWindow      = pWin32Win;

    _vWindowList.push_back(this);

#if !defined(OSG_REG_CLASS_PERWINDOW)
    static bool bClassRegistered = false;

    if(bClassRegistered == false)
    {
        WNDCLASS wndClass;

        memset(&wndClass, 0, sizeof(wndClass));

        wndClass.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc   = CSMNativeWindow::WndProc;
        wndClass.hInstance     = GetModuleHandle(NULL);
        wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wndClass.lpszClassName = "OSG-CSM";

        if (!RegisterClass(&wndClass)) 
        {
            fprintf(stderr, "register window class failed %ld\n", 
                    GetLastError());

            return false;
        }

        bClassRegistered = true;
    }
#else
    Char8 szClassName[64];

    sprintf(szClassName, "OSG-CSM-%x", this);

    fprintf(stderr, "register %s\n", szClassName);

    WNDCLASS wndClass;

    memset(&wndClass, 0, sizeof(wndClass));

    wndClass.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc   = CSMNativeWindow::WndProc;
    wndClass.hInstance     = GetModuleHandle(NULL);
    wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpszClassName = szClassName;

    if (!RegisterClass(&wndClass)) 
    {
        fprintf(stderr, "register window class failed %ld\n", 
                GetLastError());

        return false;
    }
#endif

    Int32 iWidth  = CW_USEDEFAULT;
    Int32 iHeight = 0;

    Int32  iXPos    = CW_USEDEFAULT;
    Int32  iYPos    = 0;

    if(this->getXPos() >= 0.f && this->getYPos() >= 0.f)
    {
        iXPos = Int32(this->getXPos());
        iYPos = Int32(this->getYPos());
    }

    if(this->getXSize() >= 1.f) 
    {
        iWidth = Int32(this->getXSize());
    }
    if(this->getYSize() >= 1.f)
    {
        iHeight = Int32(this->getYSize());
    }

#if 0
    _pHWND = CreateWindow("OSG-CSM", "OpenSG - CSM",
                          (WS_OVERLAPPEDWINDOW |
                           WS_CLIPCHILDREN     | 
                           WS_CLIPSIBLINGS     ),
                          iXPos, 
                          iYPos, 
                          iWidth,
                          iHeight, 
                          NULL, 
                          NULL, 
                          GetModuleHandle(NULL), 
                          this);
#else
    DWORD dwExtStyle;
    DWORD dwStyle;

    if(this->getDecorEnabled() == false)
    {
        fprintf(stderr, "no border\n");
        dwExtStyle = WS_EX_APPWINDOW;
        dwStyle    = (WS_OVERLAPPED    |
                      WS_CLIPCHILDREN  | 
                      WS_CLIPSIBLINGS  );
    }
    else
    {
        dwExtStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle    = (WS_OVERLAPPEDWINDOW |
                      WS_CLIPCHILDREN     | 
                      WS_CLIPSIBLINGS     );
    }

    _pHWND = CreateWindowEx(dwExtStyle,
#if !defined(OSG_REG_CLASS_PERWINDOW)
                            "OSG-CSM", 
#else
                            szClassName,
#endif
                            "OpenSG - CSM",
                            dwStyle,
                            iXPos, 
                            iYPos, 
                            iWidth,
                            iHeight, 
                            NULL, 
                            NULL, 
                            GetModuleHandle(NULL), 
                            this);
#endif
    if(this->getDecorEnabled() == false)
    {
        DWORD winStyle = ::GetWindowLong(_pHWND, GWL_STYLE);

        winStyle  &= ~(WS_BORDER | WS_CAPTION);

        ::SetWindowLong(_pHWND, GWL_STYLE, winStyle);
     }

    ShowWindow(_pHWND, SW_SHOWNORMAL);
    SetActiveWindow(_pHWND);

    if(ComplexSceneManager::the() != NULL)
    {
        ComplexSceneManager::the()->setMainloop(
            &CSMNativeWindow::win32MainLoop);
    }

    this->reshape(iWidth, iHeight);
    _pWin32Window->init();

    _bRun = true;

    Inherited::init();

    return true;
}

OSG_END_NAMESPACE
