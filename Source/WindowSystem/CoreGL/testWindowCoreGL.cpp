#include "OSGConfig.h"

#include <iostream>

#include "OSGFieldContainerFactory.h"
#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGBoxVolume.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGSimpleGeometry.h"
#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGDirectionalLight.h"

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGCoreGLWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"

#include "OSGTrackball.h"

#include <Carbon/Carbon.h>
#include <ApplicationServices/ApplicationServices.h>

OSG::CoreGLWindowUnrecPtr    win;

OSG::RenderAction    *ract;
OSG::NodeRecPtr           root;
OSG::NodeRecPtr           file;
OSG::ViewportRecPtr   vp;
OSG::TransformRecPtr  cam_trans;
OSG::Trackball     tball;
OSG::PerspectiveCameraRecPtr cam;

bool          stopIt = false;
int           lastx=0, lasty=0;

#if !defined(__LP64__)

void redraw ( void )
{
    OSG::Matrix m1, m2, m3;
    OSG::Quaternion q1;

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
    m1.mult( m2 );
    cam_trans->editSFMatrix()->setValue( m1 );

    OSG::Thread::getCurrentChangeList()->commitChanges();

    win->render(ract);
}

static OSStatus handleMouseEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;
    OSG::Real32 w,h,a,b,c,d;

    // Get the pressed mouse button
    EventMouseButton mouseButton;
    err = GetEventParameter(event, kEventParamMouseButton, typeMouseButton, 0, sizeof(mouseButton), 0, &mouseButton);
    if (err != noErr)
        return err;

    // Get the modifier keys
    ::UInt32 modifierKeys;
    err = GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, 0, sizeof(modifierKeys), 0, &modifierKeys);
    if (err != noErr)
        return err;

    // Traditionally, Apple mice just have one button. It is common practice to simulate
    // the middle and the right button by pressing the option or the control key.
    if (mouseButton == kEventMouseButtonPrimary)
    {
        if (modifierKeys & optionKey)
            mouseButton = kEventMouseButtonTertiary;
        if (modifierKeys & controlKey)
            mouseButton = kEventMouseButtonSecondary;
    }

    // Get the location of the mouse pointer
    ::Point location;
    err = GetEventParameter(event, kEventParamMouseLocation, typeQDPoint, 0, sizeof(location), 0, &location);
    if (err != noErr)
        return err;

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    switch (eventKind)
    {
    // mouse button pressed
    case kEventMouseDown:
        lastx = location.h;
        lasty = location.v;
        switch (mouseButton)
        {
        case kEventMouseButtonPrimary: // left button
            break;
        case kEventMouseButtonSecondary: // right button
            tball.setAutoPositionNeg(true);
            break;
        case kEventMouseButtonTertiary: // middle button
            tball.setAutoPosition(true);
            break;
        }
        break;

    // mouse button released
    case kEventMouseUp:
        switch (mouseButton)
        {
        case kEventMouseButtonPrimary: // left button
            break;
        case kEventMouseButtonSecondary: // right button
            tball.setAutoPositionNeg(false);
            break;
        case kEventMouseButtonTertiary: // middle button
            tball.setAutoPosition(false);
            break;
        }
        break;

    // mouse moved while a button is pressed
    case kEventMouseDragged:
        w = win->getWidth();
        h = win->getHeight();
        a = -2. * ( lastx / w - .5 );
        b = -2. * ( .5 - lasty / h );
        c = -2. * ( location.h / w - .5 );
        d = -2. * ( .5 - location.v / h );
        switch (mouseButton)
        {
        case kEventMouseButtonPrimary: // left button
            tball.updateRotation( a, b, c, d );
            break;
        case kEventMouseButtonSecondary: // right button
            tball.updatePositionNeg( a, b, c, d );
            break;
        case kEventMouseButtonTertiary: // middle button
            tball.updatePosition( a, b, c, d );
            break;
        }
        lastx = location.h;
        lasty = location.v;

        // Redraw the whole window
        redraw();

        break;
    }

    // We have to return eventNotHandledErr, otherwise the system is
    // not able to operate the menu and the window border
    return eventNotHandledErr;
}

static OSStatus handleKeyEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Try to determine the size of the text input
    ::UInt32 actualSize; 					
    err = GetEventParameter(event, kEventParamTextInputSendText, typeUnicodeText, 0, 0, &actualSize, 0);
    if (err != noErr)
        return err;

    // The input can actually consist of more than one character.
    // We are only interested in single character input
    if (actualSize == sizeof(UniChar))
    {
        // Get the character unicode
        UniChar c;
        err = GetEventParameter(event, kEventParamTextInputSendText, typeUnicodeText, 0, sizeof(UniChar), 0, &c);
        if (err != noErr)
            return err;

        // Handle different keyboard commands
        CGLSetCurrentContext(win->getContext());
        switch (c)
        {
        case kEscapeCharCode:
            QuitApplicationEventLoop();
            break;
        case 'a':
            glDisable( GL_LIGHTING );
            redraw();
            break;
        case 's':
            glEnable( GL_LIGHTING );
            redraw();
            break;
        case 'z':
            glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
            redraw();
            break;
        case 'x':
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            redraw();
            break;
        case 'c':
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            redraw();
            break;
        }
    }

    return noErr;
}

static pascal OSStatus eventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    ::UInt32 eventClass = GetEventClass(event);
    switch (eventClass)
    {
    // Mouse events
    case kEventClassMouse:
        return handleMouseEvent(nextHandler, event, userData);

    // Key press events
    case kEventClassTextInput:
        return handleKeyEvent(nextHandler, event, userData);

    default:
        return eventNotHandledErr;
    }
}

int doMain (int argc, char **argv)
{
    int dummy;

    // OSG init

    OSG::osgInit(argc, argv);

    // create the graph

    // beacon for camera and light
    OSG::NodeUnrecPtr b1n = OSG::Node::create();
    OSG::GroupUnrecPtr b1 = OSG::Group::create();
    b1n->setCore( b1 );

    // transformation
    OSG::NodeUnrecPtr t1n = OSG::Node::create();
    OSG::TransformUnrecPtr t1 = OSG::Transform::create();
    t1n->setCore( t1 );
    t1n->addChild( b1n );

    cam_trans = t1;

    // light

    OSG::NodeUnrecPtr dlight = OSG::Node::create();
    OSG::DirectionalLightUnrecPtr dl = OSG::DirectionalLight::create();

    dlight->setCore( dl );

    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);

    // root
    root = OSG::Node::create();
    OSG::GroupUnrecPtr gr1 = OSG::Group::create();

    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );

    // Load the file

    OSG::NodeUnrecPtr file = NULL;

    if ( argc > 1 )
        file = OSG::SceneFileHandler::the()->read(argv[1]);

    if ( file == NULL )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = OSG::makeTorus( .5, 2, 16, 16 );
    }

    OSG::Thread::getCurrentChangeList()->commitChanges();
    file->updateVolume();

    OSG::Vec3f min,max;
    file->getVolume().getBounds( min, max );

    std::cout << "Volume: from " << min << " to " << max << std::endl;

    dlight->addChild( file );

    std::cerr << "Tree: " << std::endl;
    //root->dump();

    // Camera
    cam = OSG::PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( OSG::osgDegree2Rad( 90 ) );
    cam->setNear( 0.1 );
    cam->setFar( 100000 );

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor(OSG::Color3f(0,0,1));

    // Viewport

    vp = OSG::Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Action

    ract = OSG::RenderAction::create();

    // tball

    OSG::Vec3f pos;
    pos.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                  min[1] + ((max[1] - min[1]) * 0.5), 
                  max[2] + ( max[2] - min[2] ) * 1.5 );
    
    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    OSG::Pnt3f tCenter(min[0] + (max[0] - min[0]) / 2,
                       min[1] + (max[1] - min[1]) / 2,
                       min[2] + (max[2] - min[2]) / 2);
    
    tball.setMode( OSG::Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(tCenter);

    // CoreGL init

    // Install event handler
    EventHandlerUPP eventHandlerUPP = NewEventHandlerUPP(eventHandler);
    EventTypeSpec eventList[] =
    {
        { kEventClassTextInput, kEventTextInputUnicodeForKeyEvent },
        { kEventClassMouse, kEventMouseDown },
        { kEventClassMouse, kEventMouseUp },
        { kEventClassMouse, kEventMouseDragged }
    };
    InstallApplicationEventHandler(eventHandlerUPP, GetEventTypeCount(eventList), eventList, 0, 0);

    CGDisplayCapture(kCGDirectMainDisplay);
    CGLPixelFormatAttribute attribs[] =
    {
        kCGLPFADoubleBuffer,
        kCGLPFAFullScreen,
        kCGLPFADepthSize,
        (CGLPixelFormatAttribute)16,
        kCGLPFADisplayMask,
        (CGLPixelFormatAttribute)CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
        (CGLPixelFormatAttribute)0
    };
    CGLPixelFormatObj pixelFormatObj;
    GLint numPixelFormats;
    CGLChoosePixelFormat(attribs, &pixelFormatObj, &numPixelFormats); 

    CGLContextObj contextObj;
    CGLCreateContext(pixelFormatObj, 0, &contextObj);

    CGLDestroyPixelFormat(pixelFormatObj);

    CGLSetCurrentContext(contextObj);
    CGLSetFullScreen(contextObj);

    // Create OpenSG window
    win = OSG::CoreGLWindow::create();
    win->addPort( vp );             
    win->setContext ( contextObj );
    win->init();
    win->resize( CGDisplayPixelsWide(kCGDirectMainDisplay), CGDisplayPixelsHigh(kCGDirectMainDisplay) );

    win->activate();

    // do some OpenGL init. Will move into State Chunks later.

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    redraw();

    // Main loop ( event dispatching )
    RunApplicationEventLoop();

    // Cleanup
    CGLSetCurrentContext(0);
    CGLClearDrawable(contextObj);
    CGLDestroyContext(contextObj);
    CGReleaseAllDisplays();
    DisposeEventHandlerUPP(eventHandlerUPP);

    delete ract;

    win       = NULL;
    root      = NULL;
    file      = NULL;
    vp        = NULL;
    cam_trans = NULL;
    cam       = NULL;

    return 0;
}

int main (int argc, char **argv)
{
    doMain(argc, argv);

    OSG::osgExit();

    return 0;
}

#else

int main (int argc, char **argv)
{
    fprintf(stderr, "CoreGL not available in 64bit\n");
}

#endif
