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

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMNativeWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMNativeWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

bool CSMNativeWindow::_bRun = false;

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

OSStatus CSMNativeWindow::handleMouseEvent(EventHandlerCallRef  nextHandler, 
                                           EventRef             event      )
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, 
                            kEventParamWindowRef, 
                            typeWindowRef, 0, 
                            sizeof(window), 0, &window);

    if (err != noErr)
        return err;

    // Get the window rectangle
    Rect portRect;
    GetWindowPortBounds(window, &portRect);

    // Get the pressed mouse button
    EventMouseButton mouseButton;
    err = GetEventParameter(event, 
                            kEventParamMouseButton, 
                            typeMouseButton, 0, 
                            sizeof(mouseButton), 0, &mouseButton);

    if (err != noErr)
        return err;
    
    // Get the modifier keys
    ::UInt32 modifierKeys;
    err = GetEventParameter(event, 
                            kEventParamKeyModifiers, 
                            typeUInt32, 0, 
                            sizeof(modifierKeys), 0, &modifierKeys);

    if (err != noErr)
        return err;

    // Traditionally, Apple mice just have one button. It is common practice 
    // to simulate the middle and the right button by pressing the option or
    // the control key. 

    if(mouseButton == kEventMouseButtonPrimary)
    {
        if(modifierKeys & optionKey)
            mouseButton = kEventMouseButtonTertiary;

        if(modifierKeys & controlKey)
            mouseButton = kEventMouseButtonSecondary;
    }

    // Get the location of the mouse pointer
    ::Point location;
    err = GetEventParameter(event, 
                            kEventParamMouseLocation, 
                            typeQDPoint, 0, 
                            sizeof(location), 0, &location);

    if (err != noErr)
        return err;

    // The location of the mouse pointer is in screen coordinates, so
    // we have to transform it into the local coordinate system of the
    // window content area.
    SetPortWindowPort(window   );
    GlobalToLocal    (&location);

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);

    switch (eventKind)
    {
        // mouse button pressed
        case kEventMouseDown:
        {
            switch (mouseButton)
            {
                case kEventMouseButtonPrimary: // left button
                    this->mouse(MouseData::LeftButton, 
                                MouseData::ButtonDown,
                                0,
                                location.h,
                                location.v);
                    break;
                case kEventMouseButtonSecondary: // right button
                    this->mouse(MouseData::RightButton, 
                                MouseData::ButtonDown,
                                0,
                                location.h,
                                location.v);
                    break;
                case kEventMouseButtonTertiary: // middle button
                    this->mouse(MouseData::MiddleButton, 
                                MouseData::ButtonDown,
                                0,
                                location.h,
                                location.v);
                    break;
            }
        }
        break;
            
            // mouse button released
        case kEventMouseUp:
        {
            switch (mouseButton)
            {
                case kEventMouseButtonPrimary: // left button
                    this->mouse(MouseData::LeftButton, 
                                MouseData::ButtonUp,
                                0,
                                location.h,
                                location.v);
                    break;
                case kEventMouseButtonSecondary: // right button
                    this->mouse(MouseData::RightButton, 
                                MouseData::ButtonUp,
                                0,
                                location.h,
                                location.v);
                    break;
                case kEventMouseButtonTertiary: // middle button
                    this->mouse(MouseData::MiddleButton, 
                                MouseData::ButtonUp,
                                0,
                                location.h,
                                location.v);
                    break;
            }
        }
        break;
            
            // mouse moved while a button is pressed
        case kEventMouseDragged:

            this->motion(location.h, location.v);
            
            // Redraw the whole window
            InvalWindowRect(window, &portRect);
            
            break;
    }
    
    // We have to return eventNotHandledErr, otherwise the system is
    // not able to operate the menu and the window border
    return eventNotHandledErr;
}

OSStatus CSMNativeWindow::handleKeyEvent(EventHandlerCallRef  nextHandler, 
                                         EventRef             event      )
{
    OSStatus err;

    // Try to determine the size of the text input
    ::UInt32 actualSize; 					
    
    err = GetEventParameter(event, 
                            kEventParamTextInputSendText, 
                            typeUnicodeText, 0, 0, &actualSize, 0);

    if (err != noErr)
        return err;

    // The input can actually consist of more than one character.
    // We are only interested in single character input
    if (actualSize == sizeof(UniChar))
    {
        // Get the character unicode
        UniChar c;

        err = GetEventParameter(event, 
                                kEventParamTextInputSendText, 
                                typeUnicodeText, 0, 
                                sizeof(UniChar), 0, &c);

        if (err != noErr)
            return err;

        switch (c)
        {
            case kEscapeCharCode:
                //QuitApplicationEventLoop();
                _bRun = false;
                break;

            default:
                ComplexSceneManager::the()->key(
                    0,
                    0,
                    CSMKeyData::ButtonDown,
                    c);
                break;
        }
    }

    return noErr;
}

OSStatus CSMNativeWindow::handleWindowEvent(EventHandlerCallRef  nextHandler, 
                                            EventRef             event      )
{
    OSStatus err;

    // Get the window
    WindowRef window;
    
    err = GetEventParameter(event, 
                            kEventParamDirectObject, 
                            typeWindowRef, 0, sizeof(window), 0, &window);

    if (err != noErr)
        return err;
    
    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    
    switch (eventKind)
    {
        // Quit the application when the user closes the window
        case kEventWindowClose:
            //QuitApplicationEventLoop();
            _bRun = false;
            return noErr;
            
            // Draw the contents of the window
        case kEventWindowDrawContent:
            //ComplexSceneManager::the()->frame();
        
            //Thread::getCurrentChangeList()->commitChangesAndClear();
            return noErr;
            
        case kEventWindowBoundsChanged:
        {
            // Update the GL context 
            // WARNING this crap might crash later
            aglUpdateContext(_pCarbWindow->getContext());
            
            // Find out if we have a move or a resize situation
            ::UInt32 attributes;
            GetEventParameter(event, 
                              kEventParamAttributes, 
                              typeUInt32, 
                              0, 
                              sizeof(attributes), 
                              0, 
                              &attributes);
            
            if ((attributes & kWindowBoundsChangeSizeChanged) != 0)
            {
                // Get the new bounds of the window
                Rect bounds;
                GetEventParameter(event, 
                                  kEventParamCurrentBounds, 
                                  typeQDRectangle, 
                                  0, 
                                  sizeof(Rect), 
                                  0, 
                                  &bounds);

                // Resize the OpenSG Window
                GLsizei width  = bounds.right - bounds.left;
                GLsizei height = bounds.bottom - bounds.top;

                this->reshape(width, height);

                // Redraw the whole window
                Rect portRect;
                GetWindowPortBounds(window, &portRect);
                InvalWindowRect    (window, &portRect);
            }
            
            return noErr;
        }
        
        default:
            return eventNotHandledErr;
    }
}

static pascal OSStatus eventHandler(EventHandlerCallRef  nextHandler, 
                                    EventRef             event, 
                                    void                *userData   )
{
    ::UInt32 eventClass = GetEventClass(event);

    CSMNativeWindow *pWin = reinterpret_cast<CSMNativeWindow *>(userData);

    OSG_ASSERT(pWin != NULL);

    switch (eventClass)
    {
        // Mouse events
        case kEventClassMouse:
            return pWin->handleMouseEvent(nextHandler, event);
            
            // Key press events
        case kEventClassTextInput:
            return pWin->handleKeyEvent(nextHandler, event);
            
            // Window events
        case kEventClassWindow:
            return pWin->handleWindowEvent(nextHandler, event);
            
        default:
            return eventNotHandledErr;
    }
}

void CSMNativeWindow::carbonMainLoop(void)
{
    EventRef       pEvent;
    EventTargetRef pTarget = GetEventDispatcherTarget();

    while(_bRun == true)
    {
        while(ReceiveNextEvent(0, 
                               NULL, 
                               0, //kEventDurationForever, 
                               true, 
                               &pEvent) == noErr)
        {
            SendEventToEventTarget(pEvent, pTarget);
            ReleaseEvent          (pEvent         );
        }
        
        ComplexSceneManager::the()->frame();
        
        Thread::getCurrentChangeList()->commitChangesAndClear();
    }

    ComplexSceneManager::the()->terminate();
}

#if 0
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
#endif

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMNativeWindow::CSMNativeWindow(void) :
     Inherited    (    ),
    _pCarbWindow  (NULL),
    _pContext     (NULL),
    _pLocalWindow (NULL),
    _pEventHandler(NULL)

{
}

CSMNativeWindow::CSMNativeWindow(const CSMNativeWindow &source) :
     Inherited    (source),
    _pCarbWindow  (NULL  ),
    _pContext     (NULL  ),
    _pLocalWindow (NULL  ),
    _pEventHandler(NULL  )
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
    if(_pCarbWindow != NULL)
    {
        _pCarbWindow->setContext(NULL);
    }

    if(_pContext != NULL)
        aglDestroyContext(_pContext);

    if(_pLocalWindow != NULL)
        DisposeWindow(_pLocalWindow);

    if(_pEventHandler != NULL)
        DisposeEventHandlerUPP(_pEventHandler);

    Inherited::resolveLinks();
}

void CSMNativeWindow::terminateGLContext(void)
{
}

// A magic method that allows applications to react to events even
// when they are not organized in a bundle
static void osx_AllowForeground(void)
{
    ProcessSerialNumber psn = { 0, kCurrentProcess };
    TransformProcessType(&psn, kProcessTransformToForegroundApplication);
    SetFrontProcess(&psn);
}

bool CSMNativeWindow::init(void)
{
    osx_AllowForeground();

    CSMDrawer            *pDrawer       = this->getParent();

    CarbonWindowUnrecPtr  pCarbonWindow = OSG::CarbonWindow::create();
    AGLPixelFormat        pixelFormat   = NULL;

    std::vector<int> pfForm;

    pfForm.push_back(AGL_RGBA);
    pfForm.push_back(AGL_DEPTH_SIZE);
    pfForm.push_back(16); 
    pfForm.push_back(AGL_DOUBLEBUFFER);

    if(_sfRequestSamples.getValue() > 0)
    {
        pfForm.push_back(AGL_SAMPLE_BUFFERS_ARB);
        pfForm.push_back(1);

        pfForm.push_back(AGL_SAMPLES_ARB);
        pfForm.push_back(_sfRequestSamples.getValue());
    }

    if(this->requestStereoVisual() == true)
    {
        fprintf(stderr, "Choose stereo format\n");
        pfForm.push_back(AGL_STEREO); 
    }

    pfForm.push_back(AGL_NONE);

    pixelFormat = aglChoosePixelFormat(NULL, 0, &(pfForm.front()));
    
    fprintf(stderr, "Got pf : %p\n", pixelFormat);

    if(pixelFormat == NULL) 
    {
        fprintf(stderr, "no RGB visual with depth buffer : :0.0");

        exit(0);
    }

    _pContext = aglCreateContext(pixelFormat, 0);

    aglDestroyPixelFormat(pixelFormat);

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
        uiWidth = 300; //DisplayWidth(_pDisplay, vi->screen);
    }
    else
    {
        uiWidth = 300; //UInt32(Real32(DisplayWidth(_pDisplay, vi->screen)) *
                       //       this->getXSize());
    }

    if(this->getYSize() >= 1.f)
    {
        uiHeight = UInt32(this->getYSize());
    }
    else if(this->getYSize() <= 0.f)
    {
        uiHeight = 300; //DisplayHeight(_pDisplay, vi->screen);
    }
    else
    {
        uiHeight = 300; //UInt32(Real32(DisplayHeight(_pDisplay, vi->screen)) *
                        //              this->getYSize());
    }

    WindowAttributes windowAttrs = (kWindowStandardDocumentAttributes |
                                    kWindowLiveResizeAttribute        |
                                    kWindowStandardHandlerAttribute   );
    Rect contentRect;
    SetRect(&contentRect, iXPos,  iYPos, iXPos + uiWidth, iYPos + uiHeight);

    CreateNewWindow(kDocumentWindowClass, windowAttrs, &contentRect, 
                    &_pLocalWindow);

    SetWindowTitleWithCFString(_pLocalWindow, CFSTR("OpenSG - CSM"));

    // Install event handler
    _pEventHandler = NewEventHandlerUPP(eventHandler);

    EventTypeSpec eventList[] =
    {
        { kEventClassTextInput, kEventTextInputUnicodeForKeyEvent },
        { kEventClassMouse,     kEventMouseDown                   },
        { kEventClassMouse,     kEventMouseUp                     },
        { kEventClassMouse,     kEventMouseDragged                },
        { kEventClassWindow,    kEventWindowClose                 },
        { kEventClassWindow,    kEventWindowDrawContent           },
        { kEventClassWindow,    kEventWindowBoundsChanged         }
    };

    InstallWindowEventHandler(_pLocalWindow, _pEventHandler, 
                              GetEventTypeCount(eventList), 
                              eventList, this, 0);

    aglSetWindowRef(_pContext, _pLocalWindow);

    _pCarbWindow = pCarbonWindow;

    _pCarbWindow->setContext(_pContext);
    _pCarbWindow->init      (         );
    _pCarbWindow->resize    ( uiWidth,
                              uiHeight);

    std::string windowName(" OpenSG - CSM - ");

    _pCarbWindow->activate();

    windowName += reinterpret_cast<const char *>(glGetString(GL_VERSION));
    windowName += " - ";
    windowName += reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    _pCarbWindow->deactivate();

    SetWTitle(_pLocalWindow, 
              reinterpret_cast<const unsigned char *>(windowName.c_str()));

    // Show window
    RepositionWindow(_pLocalWindow, 0, kWindowCascadeOnMainScreen);
    ShowWindow      (_pLocalWindow                               );

    if(ComplexSceneManager::the() != NULL)
        ComplexSceneManager::the()->setMainloop(
            &CSMNativeWindow::carbonMainLoop);
    
    _pWindow = _pCarbWindow;

    _bRun = true;

    Inherited::init();

    return true;
}

OSG_END_NAMESPACE
