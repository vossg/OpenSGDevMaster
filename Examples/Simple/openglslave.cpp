// OpenSG Tutorial Example: OpenGL slave
//
// Many thanks to Gernot Ziegler <gz@lysator.liu.se> for distributing this example.
//
// It is often necessary to mix non-OpenSG code with OpenSG.
// This is a quick way to melt such code-bases together. 
// But remember that transparencies will be handled incorrectly
// as no polygon sorting happens between OpenSG and OpenGL. 
// And since the OpenGL part will be never be culled like the OpenSG
// scenegraph, it can easily happen that large OpenGL objects significantly
// affect performance.
//
// Thanks to nehe.gamedev.net for the BMP image loading routines 
// The mouse code is based on a tutorial from Dennis Gustavsson (dennis@meqon.com)

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGConfig.h>
#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLUT.h>
#include <OSGSimpleGeometry.h>
#include <OSGCamera.h>
#include <OSGMatrixCamera.h>
#include <OSGPerspectiveCamera.h>
#include <OSGViewport.h>
#include <OSGPassiveWindow.h>
#include <OSGPassiveBackground.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGComponentTransform.h>
#include <OSGImage.h>
#include <OSGFileSystem.h>
#else
// Headers
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGGLU.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGFileSystem.h>
#endif

OSG::PassiveWindowRefPtr      pwin;
OSG::SimpleSceneManagerRefPtr mgr;

int     window;         // The number of our GLUT window
GLuint  texture[3];     // Storage for 3 textures.

int Width = 640, Height = 480;

GLUquadricObj *quadric; // Storage For Our Quadric Objects

// The pointer to the transformation
OSG::TransformRefPtr         trans;
OSG::ViewportRefPtr          vp;
OSG::PerspectiveCameraRefPtr cam;
OSG::MatrixCameraRefPtr      newcam;
OSG::NodeRefPtr              scene;
OSG::NodeRefPtr              world;

int m_mouseX;
int m_mouseY;
float m_tiltAngle;
float m_twistAngle;
float m_distance;
bool m_bLeftMouseButtonDown;
bool m_bRightMouseButtonDown;
unsigned int m_lastTick;  // last idle calc timestamp
unsigned int m_lastRenderTick; // last rendering timestamp
bool m_bPaused;
bool m_bFullscreen, m_bCalibrate = false;

// Load texture into memory
void LoadGLTextures(void) 
{
    OSG::ImageRefPtr image = OSG::Image::create();
    if(!image->read("./worldground.jpg"))
    {
        printf("Could not read worldground.jpg!!\n");
        exit(1);
    }

    // create Texture
    glGenTextures(1, &texture[0]);

    // texture 2 (linear scaling)
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLsizei sWidth, GLsizei sHeight)  // We call this right after our OpenGL window is created.
{
    LoadGLTextures();                        // Load the textures
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    // This Will Clear The Background Color To Black
    glClearDepth(1.0);                       // Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);                    // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);                 // Enables Depth Testing
    glShadeModel(GL_SMOOTH);                 // Enables Smooth Color Shading
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                        // Reset The Projection Matrix
    
    gluPerspective(45.0, GLfloat(sWidth)/GLfloat(sHeight),0.1f,100.0f);    // Calculate The Aspect Ratio Of The Window  
    quadric=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW )
    
    // Can also use GLU_NONE, GLU_FLAT
    gluQuadricNormals(quadric, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadric, GL_TRUE);      // Create Texture Coords ( NEW )
    
    m_bFullscreen = false;
    m_mouseX = 0;
    m_mouseY = 0;
    m_tiltAngle = -70.0f;
    m_twistAngle = -45.0f;
    m_distance = 270.0f;
    m_bLeftMouseButtonDown = false;
    m_bRightMouseButtonDown = false;
    m_lastTick = 0;
    m_lastRenderTick = 0;
    m_bPaused = false;
}

//----------------------------------------------------------------------------//
// Handle an idle event
// does all the animation calculations                                                       //
//----------------------------------------------------------------------------//
void idleFunc()
{
    // update the screen
    glutPostRedisplay();
}

//----------------------------------------------------------------------------//
// Render the cursor                                                          //
//----------------------------------------------------------------------------//

void renderCursor()
{
    //printf("Cursor redraw\n");
    // switch to orthogonal projection for the cursor
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, GLdouble(Width), 0, GLdouble(Height), -1.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // render the cursor
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2i(m_mouseX, m_mouseY);
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glVertex2i(m_mouseX + 16, m_mouseY - 32);
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glVertex2i(m_mouseX + 32, m_mouseY - 16);
    glEnd();
    
    glDisable(GL_BLEND);
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glMatrixMode(GL_MODELVIEW);
}

/* ascii code for various keys */
#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77


/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int mWidth, int mHeight)
{
    Height = mHeight; 
    Width = mWidth; 
    
    if (Height==0)                      // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;
    
    glViewport(0, 0, Width, Height);    // Reset The Current Viewport And Perspective Transformation
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluPerspective(45.0, GLfloat(Width) / GLfloat(Height), 1, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    
    mgr->resize(mWidth,mHeight);
}  

void onMouseMove(int x, int y)
{
    // update twist/tilt angles
    if(m_bLeftMouseButtonDown)
    {
        // calculate new angles
        m_twistAngle += static_cast<float>(x - m_mouseX);
        m_tiltAngle  -= static_cast<float>(y - m_mouseY);
    }
    
    // update distance
    if(m_bRightMouseButtonDown)
    {
        // calculate new distance
        m_distance -= static_cast<float>(y - m_mouseY) / 3.0f;
        if(m_distance < 0.0f)
            m_distance = 0.0f;
    }
    
    // update internal mouse position
    m_mouseX = x;
    m_mouseY = y;
}

void motionFunc(int x, int y)
{
    // redirect the message to the viewer instance
    onMouseMove(x, Height - y - 1);
    
    //mgr->mouseMove(x, y);
}

//----------------------------------------------------------------------------//
// Handle a mouse button down event                                           //
//----------------------------------------------------------------------------//

void onMouseButtonDown(int button, int x, int y)
{
    // update mouse button states
    if(button == GLUT_LEFT_BUTTON)
        m_bLeftMouseButtonDown = true;
    
    if(button == GLUT_RIGHT_BUTTON)
        m_bRightMouseButtonDown = true;
    
    // update internal mouse position
    m_mouseX = x;
    m_mouseY = y;
}

//----------------------------------------------------------------------------//
// Handle a mouse button up event                                             //
//----------------------------------------------------------------------------//

void onMouseButtonUp(int button, int x, int y)
{
    // update mouse button states
    if(button == GLUT_LEFT_BUTTON)
        m_bLeftMouseButtonDown = false;
    
    if(button == GLUT_RIGHT_BUTTON)
        m_bRightMouseButtonDown = false;
    
    // update internal mouse position
    m_mouseX = x;
    m_mouseY = y;
}

void mouseFunc(int button, int state, int x, int y)
{
#if 0 
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
#endif

    // redirect the message to the viewer instance
    if(state == GLUT_DOWN)
    {
        onMouseButtonDown(button, x, Height - y - 1);
    }
    else if(state == GLUT_UP)
    {
        onMouseButtonUp(button, x, Height - y - 1);
    }
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
    /* avoid thrashing this procedure */
    OSG::osgSleep(100);
  
    switch (key) 
    { 
        case ESCAPE:
            // clean up gobal variables
            mgr     = NULL;
            pwin    = NULL;
            trans   = NULL;
            vp      = NULL;
            cam     = NULL;
            newcam  = NULL;
            scene   = NULL;
            world   = NULL;
            
            /* shut down our window */
            //glutDestroyWindow(window); 
            
            /* exit the program...normal termination. */
            
            exit(1);
        break; // redundant.
          
        default:
            printf ("Key %d pressed. No action there yet.\n", key);
        break;
    }
}

/* The main drawing function. */
void DrawGLScene(void)
{
    glMatrixMode(GL_MODELVIEW);
    
    // clear all the buffers - gives OpenGL full control
    // OpenSG doesn't clear the background because of the PassiveBackground object
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set the model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // set camera position from mouse movement
    glTranslatef(0.0f, 0.0f, -m_distance);
    glRotatef(m_tiltAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(m_twistAngle, 0.0f, 0.0f, 1.0f);
    //glTranslatef(0.0f, 0.0f, -90.0f);
    
    glPushMatrix(); // OpenSG will overwrite
    
    OSG::Real32 proj_matrix[16], model_matrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix);
    glGetFloatv(GL_MODELVIEW_MATRIX, model_matrix);
    
    // retrieve OpenGL's matrices
    OSG::Matrix proj, model;
    proj.setValue(proj_matrix);
    model.setValue(model_matrix);
    
    newcam->setProjectionMatrix(proj);
    
    // transform the world just like the OpenGL content
    // necessary since OpenSG's modelview transforms start from the unity matrix. 
    newcam->setModelviewMatrix(model);
    
    // setup an initial transformation
    OSG::Matrix m1;
    OSG::Quaternion q1;
  
    // mind that the VRML base coordinate system has different meanings for X, Y, Z, hence the rotation for 90 degrees.
    // this, together with the MatrixCamera code above hooks OpenSG to OpenGL ! 
    m1.setIdentity();
    q1.setValueAsAxisDeg(1, 0, 0., 90); // rotation 
    m1.setRotate(q1);
    trans->setMatrix(m1);

    OSG::commitChanges();
    
    // redraw the OpenSG window content - the calls are a bit after one's own taste 
    pwin->render(mgr->getRenderAction());
    //pwin->frameInit();
    //pwin->frameExit();
    //mgr->redraw();
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    //################ START FOR OPENGL STUFF
    
    // light attributes
    const GLfloat light_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
    const GLfloat light_diffuse[]  = { 0.52f, 0.5f, 0.5f, 1.0f };
    const GLfloat light_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    
    // setup the light attributes
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
    // set the light position
    GLfloat lightPosition[] = { 0.0f, -10.0f, 10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    glEnable(GL_NORMALIZE);
    
    glDisable(GL_NORMALIZE);
    //glDisable(GL_BLEND);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
    
    GLfloat TableDiffuse[] = { 0.3f, 0.0f, 1.0f, 0.5f };
    GLfloat TableSpecular[] = { 0.6f, 0.0f, 0.8f, 0.5f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, TableDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, TableSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.4f);
    glEnable(GL_BLEND);
    
    gluPartialDisk(quadric,0,12.0f,32,16, 0, 360);    // A Disk Like The One Before  
#if 1 
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    
    // X axis on table    
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(0,0,0.1f);
    glVertex3f(120,0,0.1f);
    glEnd();
    
    // Y axis on table 
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,0,0.1f);
    glVertex3f(0,120,0.1f);
    glEnd();
    
    glEnable(GL_LIGHTING);
#endif

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    glDisable(GL_LIGHTING);
    
    // render the cursor
    renderCursor();
    
    // swap the front- and back-buffer
    glutSwapBuffers();
}

int main(int argc, char **argv) 
{
    // we need to load some relative images and geometry files.
    // to make this work reliable (e.g. starting the tutorial via link)
    // we use the argv[0] parameter.
#ifdef WIN32
    std::string sep("\\");
#else
    std::string sep("/");
#endif
    std::string path = argv[0];
    // remove app name
    std::string::size_type i = path.rfind(sep);
    if(i != std::string::npos)
        path = path.substr(0, i);
    // set the current dir to the application dir.
    OSG::Directory::setCurrent(path.c_str());

    // OSG init
    OSG::osgInit(argc, argv);
    
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
    glutInit(&argc, argv);  
    
    /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported (use GLUT_ALPHA)
     Depth buffer */  
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |  GLUT_DEPTH );  
    
    /* get a 640 x 480 window */
    //glutInitWindowSize(640, 480);  
    glutInitWindowSize(Width, Height);
    
    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(300, 0);  
    
    /* Open a window */  
    window = glutCreateWindow("Oz, Mouse Control");
    
    if (m_bFullscreen)
        glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    
    glutDisplayFunc(&DrawGLScene); 
    
    // register all GLUT callback functions
    glutIdleFunc(idleFunc);
    
    /* Register the function called when our window is resized. */
    glutReshapeFunc(ReSizeGLScene);
    
    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(keyPressed);
    
    /* Register the function called when special keys (arrows, page down, etc) are pressed. */
    //glutSpecialFunc(&specialKeyPressed);
    
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutPassiveMotionFunc(motionFunc);
    
    /* Initialize our window. */
    InitGL(640, 480);
    
    pwin = OSG::PassiveWindow::create();
    pwin->init();
    
    /*
    All scene file loading is handled via the SceneFileHandler.
    */
    world = OSG::SceneFileHandler::the()->read("Data/tie.wrl");
    // create the main scene transformation node
    
    // 1. create the Node
    scene =OSG:: Node::create();
    
    // 2. create the core
    trans = OSG::Transform::create();
    
    // 3. associate the core with the node
    scene->setCore(trans);
    scene->addChild(world); // add the world as a child
    
    // create the SimpleSceneManager helper - it will be only partially used
    mgr = OSG::SimpleSceneManager::create();
    
    // tell the manager what to manage
    mgr->setWindow(pwin );
    mgr->setRoot  (scene);

    if (pwin->getMFPort()->size() != 0) 
    {
        OSG::PassiveBackgroundRefPtr bg = OSG::PassiveBackground::create();
        
        vp  = pwin->getPort(0);
        cam = dynamic_cast<OSG::PerspectiveCamera *>(vp->getCamera());
        newcam = OSG::MatrixCamera::create();  // the MatrixCamera will only be a slave to the OpenGL matrices
        vp->setCamera(newcam); // replace the cam
        vp->setBackground(bg); // keep OpenSG from deleting the background, we will do that ourselves
        if(cam == NULL)
            exit(1);
    }
    else
    {
        printf("Could not acquire pointer to camera !!\n");
        exit(1);
    }
    
    OSG::commitChanges();
    
    /* Start Event Processing Engine */  
    glutMainLoop();

    return 1;
}
