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

#import <Cocoa/Cocoa.h>

#include "OSGCSMNativeWindow.h"
#include "OSGCSMDrawer.h"
#include "OSGComplexSceneManager.h"
#ifdef OSG_NEW_SHADER
#include "OSGShaderCache.h"
#endif
#include "OSGGLFuncProtos.h"

/***************************************************************************\
 *                           local support classes                         *
\***************************************************************************/

@interface CSMOpenGLView: NSOpenGLView
{
    OSG::CSMNativeWindow *_pWin;
}
- (BOOL) acceptsFirstResponder;

- (void) keyDown:           (NSEvent*) event;

- (void) handleMouseEvent:  (NSEvent*) event;

- (void) mouseDown:         (NSEvent*) event;
- (void) mouseDragged:      (NSEvent*) event;
- (void) mouseUp:           (NSEvent*) event;
- (void) rightMouseDown:    (NSEvent*) event;
- (void) rightMouseDragged: (NSEvent*) event;
- (void) rightMouseUp:      (NSEvent*) event;
- (void) otherMouseDown:    (NSEvent*) event;
- (void) otherMouseDragged: (NSEvent*) event;
- (void) otherMouseUp:      (NSEvent*) event;


- (void) setWindow: (OSG::CSMNativeWindow *) pWin;

- (void) reshape;
- (void) drawRect: (NSRect) bounds;

- (void) frame: (id) userInfo;

@end

@implementation CSMOpenGLView

- (BOOL) acceptsFirstResponder
{
    return YES;
}

- (void) keyDown: (NSEvent*) event
{
    if ([[event characters] length] != 1)
        return;

    switch ([[event characters] characterAtIndex: 0])
    {
        case 27:
            [NSApp stop:nil];
            break;
        default:
            OSG::ComplexSceneManager::the()->key(
                0,
                0,
                OSG::CSMKeyData::ButtonDown,
                [[event characters] characterAtIndex: 0]);
            break;
    }
}

- (void) handleMouseEvent: (NSEvent*) event
{
    int          buttonNumber  = [event buttonNumber];
    unsigned int modifierFlags = [event modifierFlags];

    // Traditionally, Apple mice just have one button. It is common practice
    // to simulate the middle and the right button by pressing the option or
    // the control key. 

    if(buttonNumber == 0)
    {
        if(modifierFlags & NSAlternateKeyMask)
            buttonNumber = 2;

        if(modifierFlags & NSControlKeyMask)
            buttonNumber = 1;
    }

    NSPoint location = [event locationInWindow];

    OSG::UInt32 uiHeight = _pWin->getWindow()->getHeight();

    switch ([event type])
    {
        case NSLeftMouseDown:
        case NSRightMouseDown:
        case NSOtherMouseDown:
        {
            switch (buttonNumber)
            {
                case 0: // left button
                    _pWin->mouse(OSG::MouseData::LeftButton,
                                 OSG::MouseData::ButtonDown,
                                 0,
                                 location.x,
                                 uiHeight - location.y);
                    break;
                case 1: // right button
                    _pWin->mouse(OSG::MouseData::RightButton,
                                 OSG::MouseData::ButtonDown,
                                 0,
                                 location.x,
                                 uiHeight - location.y);
                    break;
                case 2: // middle button
                    _pWin->mouse(OSG::MouseData::MiddleButton,
                                 OSG::MouseData::ButtonDown,
                                 0,
                                 location.x,
                                 uiHeight - location.y);
                    break;
            }
            break;
        }
   
        case NSLeftMouseUp:
        case NSRightMouseUp:
        case NSOtherMouseUp:
        {
            switch (buttonNumber)
            {
                case 0: // left button
                    _pWin->mouse(OSG::MouseData::LeftButton,
                                 OSG::MouseData::ButtonUp,
                                 0,
                                 location.x,
                                 uiHeight - location.y);
                    break;
                case 1: // right button
                    _pWin->mouse(OSG::MouseData::RightButton,
                                 OSG::MouseData::ButtonUp,
                                 0,
                                 location.x,
                                 uiHeight - location.y);
                    break;
                case 2: // middle button
                    _pWin->mouse(OSG::MouseData::MiddleButton,
                                 OSG::MouseData::ButtonUp,
                                 0,
                                 location.x,
                                 uiHeight - location.y);
                    break;
            }
            break;
        }
            
        case NSLeftMouseDragged:
        case NSRightMouseDragged:
        case NSOtherMouseDragged:
        {
            _pWin->motion(location.x, uiHeight - location.y);

            break;
        }
   
        default:
            break;
    }
}

- (void) mouseDown: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) mouseDragged: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) mouseUp: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) rightMouseDown: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) rightMouseDragged: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) rightMouseUp: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) otherMouseDown: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) otherMouseDragged: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) otherMouseUp: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) setWindow: (OSG::CSMNativeWindow *) pWin
{
    _pWin = pWin;
}

- (void) reshape
{
    [self update];

    NSRect frame = [self bounds];

    _pWin->reshape(static_cast<int>(frame.size.width), 
                   static_cast<int>(frame.size.height));
}

- (void) drawRect: (NSRect) bounds
{
    [self frame: nil];
}

- (void) frame: (id) userInfo
{
    if(OSG::CSMNativeWindow::isRunning() == true)
    {
        OSG::ComplexSceneManager::the()->frame();
        
        OSG::Thread::getCurrentChangeList()->commitChangesAndClear();
    }
}

@end

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMNativeWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMNativeWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NSAutoreleasePool *CSMNativeWindow::_pPool = NULL;
bool               CSMNativeWindow::_bRun  = false;

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

void CSMNativeWindow::cocoaMainLoop(void)
{
    _bRun = true;

    [NSApp run];

    _bRun = false;

    ComplexSceneManager::the()->terminate();

    [_pPool release];
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMNativeWindow::CSMNativeWindow(void) :
     Inherited    (    ),
    _pCocoaWindow (NULL),
    _pGLView      (NULL)
{
}

CSMNativeWindow::CSMNativeWindow(const CSMNativeWindow &source) :
     Inherited    (source),
    _pCocoaWindow (NULL  ),
    _pGLView      (NULL  )
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
    if(_pCocoaWindow != NULL)
    {
        _pCocoaWindow->setContext(NULL);
    }

    _pCocoaWindow = NULL;

    Inherited::resolveLinks();
}

void CSMNativeWindow::terminateGLContext(void)
{
    if(_pCocoaWindow != NULL)
    {
        _pCocoaWindow->terminate();
    }

    _pGLView = NULL;
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

    if(_pPool == NULL)
    {
        // Create application
        [NSApplication sharedApplication];

        _pPool = [[NSAutoreleasePool alloc] init];
    }

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

    NSRect nsScreenRect = [[NSScreen mainScreen] frame];

    iYPos = nsScreenRect.size.height - iYPos - uiHeight;

    // Create the window
    NSWindow *window = [NSWindow alloc];
    NSRect    rect   = { { 0, 0 }, { 300, 300 } };

    rect.origin.x = iXPos;
    rect.origin.y = iYPos;

    rect.size.height = uiHeight;
    rect.size.width  = uiWidth;

    [window initWithContentRect: rect 
            styleMask: (NSTitledWindowMask         | 
                        NSClosableWindowMask       | 
                        NSMiniaturizableWindowMask | 
                        NSResizableWindowMask) 
             backing: NSBackingStoreBuffered 
             defer: YES];

    [window setTitle: @"OpenSG - CSM"];
    [window setReleasedWhenClosed: NO];

    _pGLView = [[CSMOpenGLView alloc] autorelease];

    rect.origin.x = 0;
    rect.origin.y = 0;

    [_pGLView initWithFrame: rect];
    [_pGLView setAutoresizingMask: (NSViewMaxXMargin   | 
                                    NSViewWidthSizable | 
                                    NSViewMaxYMargin   | 
                                    NSViewHeightSizable )];

    [[window contentView] addSubview: _pGLView];

    std::vector<NSOpenGLPixelFormatAttribute> attrs;

    attrs.push_back(NSOpenGLPFAWindow);
    attrs.push_back(NSOpenGLPFADoubleBuffer);

    attrs.push_back(NSOpenGLPFADepthSize);
    attrs.push_back(NSOpenGLPixelFormatAttribute(16));
    

    if(_sfRequestSamples.getValue() > 0)
    {
        attrs.push_back(NSOpenGLPFAMultisample);

        attrs.push_back(NSOpenGLPFASampleBuffers);
        attrs.push_back(1);

        attrs.push_back(NSOpenGLPFASamples);
        attrs.push_back(
            NSOpenGLPixelFormatAttribute(_sfRequestSamples.getValue()));
    }

    if(this->requestStereoVisual() == true)
    {
        fprintf(stderr, "Choose stereo format\n");
        attrs.push_back(NSOpenGLPFAStereo); 
    }


    attrs.push_back(NSOpenGLPixelFormatAttribute(0));

    NSOpenGLPixelFormat *pixFmt = 
        [[NSOpenGLPixelFormat alloc] initWithAttributes: &(attrs.front())];

    if(pixFmt == NULL) 
    {
        fprintf(stderr, "no RGB visual with depth buffer : :0.0");

        exit(0);
    }

    [_pGLView setPixelFormat: pixFmt];


    // Create OpenSG window
    CocoaWindowUnrecPtr pCocoaWindow = CocoaWindow::create();

    pCocoaWindow->setContext([_pGLView openGLContext]);
    pCocoaWindow->init      (                        );
    pCocoaWindow->resize    (uiWidth, uiHeight       );

    _pCocoaWindow = pCocoaWindow;
    _pWindow      = pCocoaWindow;

    [_pGLView setWindow: this];

	// Show the window
    [window makeKeyAndOrderFront: nil];
    [window makeFirstResponder:_pGLView];


    NSTimer *timer = [NSTimer timerWithTimeInterval: 0.0f
                     target: _pGLView
                     selector: @selector( frame: )
                     userInfo: nil
                     repeats: YES];

    [[NSRunLoop currentRunLoop] addTimer: timer
                                forMode: NSDefaultRunLoopMode];



    if(ComplexSceneManager::the() != NULL)
    {
        ComplexSceneManager::the()->setMainloop(
            &CSMNativeWindow::cocoaMainLoop);
    }

    Inherited::init();

    return true;
}

void CSMNativeWindow::reshape(Int32 w, 
                              Int32 h)
{
    Inherited::reshape(w, h);
}

void CSMNativeWindow::mouse(Int32 iButton, 
                            Int32 iState,
                            Int32 iModifier,
                            Int32 x,       
                            Int32 y        )
{
    Inherited::mouse(iButton, iState, iModifier, x, y);
}

void CSMNativeWindow::motion (Int32 x, 
                              Int32 y)
{
    Inherited::motion(x, y);
}

OSG_END_NAMESPACE
