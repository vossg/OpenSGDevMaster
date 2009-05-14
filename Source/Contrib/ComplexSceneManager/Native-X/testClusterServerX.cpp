// OpenSG Tutorial Example: Cluster Server
//
// This is a full functional OpenSG cluster server. In OpenSG
// the terms server and client are used similar to X11. The
// application is the client. Instances that are used for 
// rendering are called server.
//
// See the ClusterClient.cpp for an example of how to use them.

#ifndef WIN32

#include <iostream>

#include <unistd.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>
// The Cluster server definition
#include <OSGClusterServer.h>
// The GLUT-OpenSG connection class
#include <OSGXWindow.h>
// Render action definition. 
#include <OSGRenderAction.h>

// local glut window
OSG::XWindowRefPtr    window;
// render action
OSG::RenderAction    *ract;
// pointer the the cluster server instance
OSG::ClusterServer   *server;
bool                  exitOnError = false;
int                   iCache      = 0;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(int width, int height);

int wait_for_map_notify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

// Initialize GLUT & OpenSG and start the cluster server
int main(int argc,char **argv)
{
          int             winid          = 0;
    const char           *name           = "ClusterServer";
    const char           *connectionType = "StreamSock";
          bool            fullscreen     = true;
          std::string     address        = "";
          char           *opt            = NULL;
          bool            doStereo       = false;
          OSG::UInt32     servicePort    = 8437;
          std::string     serviceGroup   = "224.245.211.234";


    FILE *pOut = fopen("/tmp/cluster_server.log", "w");

    if(pOut != NULL)
    {
        char **pVal = environ;

        while(*pVal != NULL)
        {
            fprintf(pOut, "%s\n", *pVal);

            ++pVal;
        }

        fclose(pOut);
    }

    // evaluate params
    for(int a = 1 ; a < argc ; ++a)
    {
        if(argv[a][0] == '-')
        {
            switch(argv[a][1])
            {
                case 'm': 
                    connectionType="Multicast";
                    break;

                case 's':
                    doStereo=true;
                    break;
                    
                case 'w': 
                    fullscreen=false;
                    break;

                case 'e':
                    exitOnError=true;
                    break;

                case 'a': address = argv[a][2] ? argv[a]+2 : argv[++a];
                    if(address == argv[argc])
                    { 
                        SLOG << "address missing" << OSG::endLog;
                        return 0;
                    }

                    std::cout << address << OSG::endLog;
                    break;


                case 'p':
                    if(argv[a][2] != '\0')
                        servicePort=atoi(argv[a]+2);
                    else
                        servicePort=atoi(argv[++a]);
                    break;

                case 'j':
                    if(argv[a][2] != '\0')
                        serviceGroup=argv[a]+2;
                    else
                        serviceGroup=argv[++a];
                    break;
              
                case 'h':
                default:  
                    std::cout << argv[0] 
                              << "-m "
                              << "-s "
                              << "-w "
                              << "-e "
                              << "-a Address "
                              << "-j group "
                              << "-p servicePort "
                              << std::endl;
                    std::cout << "-m         use multicast" << std::endl;
                    std::cout << "-s         enable stereo" << std::endl;
                    std::cout << "-w         no fullscreen" << std::endl;
                    std::cout << "-e         exit after closed connection" 
                              << std::endl;
                    std::cout << "-a Address Server network address"
                              << std::endl;
                    std::cout << "-m Address wait for requests on "
                              << "multicast group" << std::endl;
                    std::cout << "-p port    wait for requests on port"
                              << std::endl;
                    return 0;
            }
        }
        else
        {
            name=argv[a];
        }
    }
    try
    {
        // init OpenSG
        OSG::osgInit(argc, argv);

        int snglBuf[] = {GLX_RGBA, 
                         GLX_DEPTH_SIZE, 16, 
                         None};
        
        int dblBuf[16];

        dblBuf[0] = GLX_RGBA;
        dblBuf[1] = GLX_DEPTH_SIZE;
        dblBuf[2] = 16;
        dblBuf[3] = GLX_DOUBLEBUFFER;
        dblBuf[4] = (doStereo == true) ? GLX_STEREO : None;
        dblBuf[5] = None;

        GLboolean doubleBuffer = GL_FALSE;

        // X init
        OSG::DisplayP dpy = XOpenDisplay(NULL);

        if(dpy == NULL) 
        {
            std::cerr << "Error: Could not open display!" << std::endl;
        }

        int dummy;

        if(!glXQueryExtension( dpy, &dummy, &dummy))
        {
            std::cerr << "Error: X server has no OpenGL GLX extension"
                      << std::endl;
        }
        
        XVisualInfo *vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);

        if(vi == NULL) 
        {
            vi = glXChooseVisual(dpy, DefaultScreen(dpy), snglBuf);

            if(vi == NULL)
            {
                std::cerr << "no RGB visual with depth buffer" << std::endl;
            }
            
            doubleBuffer = GL_FALSE;
        }

        if(vi->c_class != TrueColor)
        {
            std::cerr << "TrueColor visual required for this program"
                      << std::endl;
        }
        
        Colormap cmap = XCreateColormap(dpy, 
                                        RootWindow(dpy, vi->screen), 
                                        vi->visual, 
                                        AllocNone);
        XSetWindowAttributes swa;

        swa.colormap = cmap;
        swa.border_pixel = 0;
        swa.event_mask = 
            ExposureMask      | 
            ButtonPressMask   | 
            ButtonReleaseMask |
            KeyPressMask      |
            Button1MotionMask |
            Button2MotionMask |
            Button3MotionMask | 
            StructureNotifyMask;
        
        // Create Window
        
        // Create a Window and connect it to the main display dpy
        OSG::X11Window hwin = XCreateWindow(dpy, 
                                            RootWindow(dpy, vi->screen), 
                                            0, 0, 300, 300, 
                                            0, 
                                            vi->depth,
                                            InputOutput, 
                                            vi->visual, 
                                            CWBorderPixel | 
                                            CWColormap    | 
                                            CWEventMask, 
                                            &swa );
        
        XSetStandardProperties(dpy, hwin, "testWindowX", "testWindowX", 
                               None, argv, argc, NULL);
        
        if(fullscreen == true)
        {
            Atom noDecorAtom = XInternAtom(dpy, 
                                           "_MOTIF_WM_HINTS",
                                           0);
            
            if(noDecorAtom == None) 
            {
                fprintf(stderr,
                        "Could not intern X atom for _MOTIF_WM_HINTS.\n");
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
            
            XChangeProperty(dpy, 
                            hwin,
                            noDecorAtom, 
                            noDecorAtom, 
                            32,
                            PropModeReplace, 
                            (unsigned char *) &oHints, 4);

        }
        

        // create the render action
        ract = OSG::RenderAction::create();

        // setup the OpenSG Glut window
        window     = OSG::XWindow::create();

        window->setDisplay(dpy );
        window->setWindow (hwin);    

        window->init();
 
        XEvent        event;

        XMapWindow(dpy, hwin);
        XIfEvent(dpy, &event, wait_for_map_notify, (char *)hwin);

        if(fullscreen == true)
        {
            XMoveWindow  (dpy, hwin, 0, 0);
            XResizeWindow(dpy, hwin,
                          DisplayWidth (dpy, vi->screen),
                          DisplayHeight(dpy, vi->screen));

            static char data[1] = {0};

            Cursor cursor;
            Pixmap blank;
            XColor dummyCol;
            
            blank = XCreateBitmapFromData(dpy, 
                                          hwin,
                                          data, 1, 1);

            cursor = XCreatePixmapCursor(dpy, 
                                         blank, 
                                         blank,
                                         &dummyCol, &dummyCol, 0, 0);

            XFreePixmap(dpy, blank);

            XDefineCursor(dpy,
                          hwin, 
                          cursor);
            XFlush(dpy);
        }

        window->activate();
       
        glEnable(GL_LIGHTING );
        glEnable(GL_LIGHT0   );
        glEnable(GL_NORMALIZE);

        // create the cluster server
        server     = new OSG::ClusterServer(window, 
                                            name,
                                            connectionType,
                                            address       );
        // start the server
        server->start();

        OSG::Real32 w,h,a,b,c,d;
        bool        stopIt = false;
        int         ip;

        while(!stopIt) 
        {
            while(ip = XPending(dpy))
            {
                XNextEvent(dpy, &event);

                switch (event.type) 
                {
                    case ConfigureNotify:
                    {
                        reshape(event.xconfigure.width,
                                event.xconfigure.height);
                    }                                                   
                    break;

                    case Expose:
                        display();
                        break;

                } 
                
            }

            display();
        }   
    }

    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SLOG << e.what() << OSG::endLog;
        delete server;
        OSG::osgExit(); 
    }

    return 0;
}

/* render loop */
void display(void)
{
    try
    {
        if(iCache < 5)
        {
            fprintf(stderr, "cache %d\n", iCache);

            ract->setFrustumCulling(false);
        }

        // receive scenegraph and do rendering
        server->render(ract);

        if(iCache < 5)
        {
            ract->setFrustumCulling(false);
            ++iCache;
        }


        // clear changelist 
        OSG::Thread::getCurrentChangeList()->clear();
    } 

    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        if(exitOnError)
        {
            SLOG << e.what() << std::endl;

            try
            {
                delete server;
            }
            catch(...)
            {
            }

            printf("Exit on error %s",e.what());

            OSG::osgExit();
            exit(0);
        }
        else
        {
            SLOG << e.what() << OSG::endLog;
            // try to restart server
            server->stop();
            // start server, wait for client to connect
            server->start();
        }
    }
}

/* window reshape */
void reshape( int width, int height )
{
    // set new window size
	window->resize( width, height );
}

#else

#include <iostream>

int main(int argc,char **argv)
{
    std::cerr << "Not supported on windows platform!" << std::endl;
}

#endif // WIN32
