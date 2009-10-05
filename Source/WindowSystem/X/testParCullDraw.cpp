// Parallel Culling/Drawing
// This is a very ugly hack and more a tesbed than an actually usable
// application. For that it's much too brittle...

#define OSG_LOG_MODULE "testParCullDraw"

#include <fstream>

// GLUT is used for window handling
#include "OSGGLUT.h"

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

#include "OSGXWindow.h"
#include "OSGPassiveWindow.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

#include "OSGGradientBackground.h"

#include "OSGImageFileHandler.h"
#include "OSGPathHandler.h"

#include "OSGSceneFileHandler.h"
#include "OSGThread.h"
#include "OSGBarrier.h"

#include "OSGRenderAction.h"


OSG::SimpleSceneManager  *mgr;
OSG::XWindowRecPtr        xwin;
OSG::PassiveWindowRecPtr  pwin;

OSG::NodeRecPtr scene = NULL;

// Threading stuff

bool doThreading = true;
bool doParDraw   = true;

OSG::UInt16 numBuf = 2;

// The three threads
OSG::Thread *appthread, *cullthread, *drawthread;

// barriers to sync app, cull and draw
OSG::Barrier *cullenter, *cullleave;
OSG::Barrier *drawenter;
OSG::Barrier *exitB;

// Action to use
OSG::RenderAction *rentravact;

bool doExit = false;
OSG::UInt16 numthreads;

// Do the drawing for one frame
// extra function to test in sequential

#if 0
void doDraw(void)
{
    static int curBuf = 0;
    
    pwin->frameInit();
    FNOTICE(("doDraw:start Draw buf %d\n", curBuf));
    rentravact->drawBuffer(curBuf);
    FNOTICE(("doDraw:finished Draw buf %d\n", curBuf));
    xwin->swap();
    pwin->frameExit();
    FNOTICE(("doDraw:swapped buf %d\n", curBuf));
    
    if(0)
    {
        std::string stats;

        if(rentravact->getStatCollector() != NULL)
            rentravact->getStatCollector()->putToString(stats);

        std::cout << stats << std::endl;
    }
    
    curBuf = (curBuf + 1) % numBuf;
}

// Drawer function executed in a third thread

void draw(void* data)
{
    // need my own Display connection
    Display *dpy = XOpenDisplay(NULL);
    xwin->setDisplay(dpy);
    xwin->init();
    
    while(!doExit)
    {
        FNOTICE(("draw:enter Barrier\n"));
        // Wait for the cull thread to finish culling
        drawenter->enter(2);
        FNOTICE(("draw:left Barrier\n"));
            
        // Do the drawing
        doDraw();
    };
    FNOTICE(("draw: waiting for exit\n"));
    exitB->enter(numthreads);
    FNOTICE(("draw: exit\n"));
}

// Do the culling for one frame
// extra function to test in sequential

void doCull(void)
{
    static int curBuf = 0;
    
    rentravact->setCurrentBuffer(curBuf);
    FNOTICE(("doCull:start culling buf %d\n", curBuf));
    pwin->renderAllViewports(rentravact);
    FNOTICE(("doCull:done culling buf %d\n", curBuf));
    
    curBuf = (curBuf + 1) % numBuf;
}

// Culler function executed in a second thread

void cull(void* data)
{
    appthread->getChangeList()->applyAndClear();
    if(!doParDraw)
    {
        // need my own Display connection
        Display *dpy = XOpenDisplay(NULL);
        xwin->setDisplay(dpy);
        xwin->init();
    }
    else
    {
        drawthread = Thread::get("drawThread");
        drawthread->runFunction(draw, 1, NULL);
    }
    
    while(!doExit)
    {
        // Wait for the app thread to commit changes
        FNOTICE(("cull:enter barrier\n"));
        cullenter->enter(2);
       
        //Sync them into my aspect
        FNOTICE(("cull:start sync\n"));
        appthread->getChangeList()->applyAndClear();
        Thread::getCurrentChangeList()->commitChanges();
        FNOTICE(("cull:finished sync\n"));
        // Tell the App thread to continue
        cullleave->enter(2);
        
        // Do the culling
        doCull();
        
        // Now draw
        if(doParDraw)
        {
            // Wait for drawer to finish last frame
            FNOTICE(("cull:wait for draw\n"));
            drawenter->enter(2);
            FNOTICE(("cull:got draw\n"));
        }
        else
        {
            doDraw();
        }
    }
    FNOTICE(("cull: waiting for exit\n"));
    exitB->enter(numthreads);
    FNOTICE(("cull: exit\n"));
}

// Standard GLUT callback functions
void display( void )
{
    Thread::getCurrentChangeList()->commitChanges();
    mgr->update();
    if(doThreading)
    {
        // Wait for the cull thrad to finish culling the last frame
        cullenter->enter(2); 
        // Wait for it to do the sync
        cullleave->enter(2);
        // Now continue apping
    }
    else
    {
        doCull();
        doDraw();
    }
}

void reshape( int w, int h )
{
    mgr->resize( w, h );
}

void
motion(int x, int y)
{
    mgr->mouseMove( x, y );
}

void
mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
}


// Open X Window

int wait_for_map_notify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == ::Window(arg) );
}

#ifdef OSG_DEBUG_OLD_C_CASTS
#ifdef DefaultScreen
#undef DefaultScreen
#endif
#ifdef ScreenOfDisplay
#undef ScreenOfDisplay
#endif

#define DefaultScreen(dpy)((reinterpret_cast<_XPrivDisplay>(dpy))->default_screen)

#define ScreenOfDisplay(dpy, scr)(&(reinterpret_cast<_XPrivDisplay>(dpy))->screens[scr])
#endif

Display *openWindow(XWindow *xwin, char **argv, int &argc)
{
    static int dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, 
                           None};
    static int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
    
    DisplayP      dpy;
    X11Window     hwin;

    XVisualInfo   *vi;
    Colormap      cmap;
    XEvent        event;
    XSetWindowAttributes swa;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) 
    {
        std::cerr << "Error: Could not open display!" << std::endl;
    }
    
    int dummy;
    if( ! glXQueryExtension( dpy, &dummy, &dummy ) )
    {
        std::cerr << "Error: X server has no OpenGL GLX extension" << std::endl;
    }

    vi = glXChooseVisual( dpy, DefaultScreen(dpy), dblBuf );
    if ( vi == NULL ) 
    {

       vi = glXChooseVisual( dpy, DefaultScreen(dpy), snglBuf );
       if (vi == NULL)
       {
           std::cerr << "no RGB visual with depth buffer" << std::endl;
       }
    }
    if (vi->c_class != TrueColor)
    {
        std::cerr << "TrueColor visual required for this program" << std::endl;
    }

    cmap = XCreateColormap( dpy, 
                            RootWindow(dpy, vi->screen), 
                            vi->visual, 
                            AllocNone );
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | 
                     ButtonPressMask | 
                     ButtonReleaseMask |
                     KeyPressMask |
                     Button1MotionMask |
                     Button2MotionMask |
                     Button3MotionMask | 
                     StructureNotifyMask;

    // Create Window
    
    // Create a Window and connect it to the main display dpy
    hwin = XCreateWindow( dpy, 
                          RootWindow(dpy, vi->screen), 
                          0, 0, 300, 300, 
                          0, 
                          vi->depth,
                          InputOutput, 
                          vi->visual, 
                          CWBorderPixel | CWColormap | CWEventMask, 
                          &swa );
                            
    XSetStandardProperties(dpy, hwin, "testWindowX", "testWindowX", None, argv, argc, NULL);
    
    xwin->setDisplay ( dpy );
    xwin->setWindow ( hwin );    
        
    XMapWindow(dpy, hwin);
    XIfEvent(dpy, &event, wait_for_map_notify, reinterpret_cast<char *>(hwin));
    
    return dpy;
}

// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    // Add Timestamps to log output
    osgLog().addHeaderElem(LOG_TIMESTAMP_HEADER);
    
    // Passive Window for culling
    pwin = PassiveWindow::create();
    
    Real32 cnear = -1., cfar = -1.;
    
    // check command line options
    while(argc > 1 && argv[1][0] == '-')
    {
        switch(argv[1][1])
        {
        case 's':   doThreading = false;
                    break;
        case 'c':   doParDraw = false;
                    break;
        case 'n':   cnear = atof(argv[2]);
                    argc --;
                    argv ++;
                    break;
        case 'f':   cfar = atof(argv[2]);
                    argc --;
                    argv ++;
                    break;
        default:    FFATAL(("Unknown option '%s'!\n", argv[1]));
                    exit(1);
        }
        argc --;
        argv ++;
    }
    
    // create the scene

    const char *fileName = (argc > 1) ? argv[1] : "None";

    FNOTICE(("Reading file %s...\n",fileName));
    
    scene = SceneFileHandler::the()->read(fileName, NULL);
    
    FNOTICE(("File read\n"));
    
    if(scene == NULL)
    {
        std::cerr << "Error loading " << fileName << "!" << std::endl;
        
        scene = makeCoredNode<Group>();
        
        SimpleMaterialUnrecPtr sm = SimpleMaterial::create();
        
        sm->setDiffuse(Color3f(0,1,1));
        sm->setSpecular(Color3f(1,1,1));
        sm->setTransparency(.5);
       
        GeometryUnrecPtr geo = makeTorusGeo( .5, 2, 16, 16 );
        geo->setMaterial(sm);
        scene->addChild(makeNodeFor(geo));
       
        geo = makeTorusGeo( .3, .5, 16, 16 );
        geo->setMaterial(sm);
        scene->addChild(makeNodeFor(geo));
    }

    //scene->dump();
    Thread::getCurrentChangeList()->commitChanges();

    // file out test.
    //SceneFileHandler::the()->write(scene, "torus2.osb");


    // X init   
    xwin = XWindow::create();
    Display *dpy = openWindow(xwin, argv, argc);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( pwin );
    mgr->setRoot( scene );

    mgr->showAll();

    if(cnear != -1)
        mgr->getCamera()->setNear(mgr->getCamera()->getNear() * cnear);

    if(cfar != -1)
        mgr->getCamera()->setFar(mgr->getCamera()->getFar() * cfar);
        
    // We'll be using the new style action here
    rentravact = RenderAction::create();
    
    rentravact->setDoCullOnly(true);       
    rentravact->setNumBuffers(numBuf);

#if 0    
    // create a gradient background.
    GradientBackgroundPtr gback = GradientBackground::create();
    gback->clearLines();
    gback->addLine(Color3f(0.7, 0.7, 0.8), 0);
    gback->addLine(Color3f(0.0, 0.1, 0.3), 1);

    WindowPtr win = mgr->getWindow();
    for(int i=0;i<win->getPort().size();++i)
    {
        ViewportPtr vp = win->getPort()[i];
        vp->setBackground(gback);
    }
#endif

    // Start threading
    
    if(doThreading)
    {
        // Create barriers for syncing
        cullenter = Barrier::create();
        cullleave = Barrier::create();
        drawenter = Barrier::create();
        exitB = Barrier::create();

        numthreads = 1 + (doThreading?1:0) + (doParDraw?1:0);
        
        appthread = Thread::getCurrent();

        cullthread = Thread::get("cullThread");
        cullthread->runFunction(cull, 1, NULL);
    }
    else
    {
        xwin->init();
    }
    
    // main loop ( event dispatching )

    bool stopIt = false;
    // First redraw
    display();
    
    while ( !stopIt ) 
    {
        XEvent event;
        bool needRedraw = false;
        
        do
        {
            XNextEvent(dpy, &event);
            switch (event.type) 
            {
                case KeyPress:           
                    FINFO(("Key pressed: %d \n",event.xkey.keycode));
                    switch ( event.xkey.keycode ) 
                    {
                        case 9: 
                            stopIt = true;
                            doExit = true;
                            // need to render a frame to get the other threads
                            // out of their barriers
                            FNOTICE(("app: Display for exit\n"));
                            display();
                            FNOTICE(("app: Waiting for exit\n"));
                            exitB->enter(numthreads);
                            FNOTICE(("app: Got exit\n"));
                            

                            delete mgr;

                            xwin  = NULL;
                            pwin  = NULL;
                            scene = NULL;

                            osgExit();

                            exit(0);
                    }
                    break;

                case ButtonPress:
                    FINFO(("Button pressed: %d\n", event.xbutton.button)); 
                    mouse(event.xbutton.button - 1, 0, event.xbutton.x,
                                event.xbutton.y);
                    break;
                    
                case ButtonRelease:
                    FINFO(("Button released: %d\n", event.xbutton.button));               
                    mouse(event.xbutton.button - 1, 1, event.xbutton.x,
                                event.xbutton.y);
                    break;
                    
                case MotionNotify:
                    FINFO(("MotionNotify %d %d\n",event.xmotion.x,
                                event.xmotion.y));
                    
                    motion(event.xmotion.x, event.xmotion.y);
                    needRedraw = true;
                    break;
                    
                case ConfigureNotify:
                    FINFO(("ConfigureNotify\n"));
                    reshape(event.xconfigure.width, event.xconfigure.height );
                    needRedraw = true;
                    break;
                
                case Expose:
                    needRedraw = true;
                    break;
             }
             
        }     
        while ( XPending(dpy) );
        if(needRedraw)
            display();
    }   
    return 0;
}
#else
int main (int argc, char **argv)
{
    return 0;
}
#endif
