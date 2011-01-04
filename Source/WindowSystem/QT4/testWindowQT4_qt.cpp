// Single-threaded QT example

#include "OSGConfig.h"

#include <iostream>

#ifdef __sgi
#pragma set woff 1375
#endif

#include <Qt/qapplication.h>
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <QtOpenGL/QGLContext>

#ifdef __sgi
#pragma set woff 1375
#endif

#include "OSGFieldContainerFactory.h"
#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGBoxVolume.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGAttachment.h"
#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGDirectionalLight.h"
#include "OSGSimpleGeometry.h"

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGQT4Window.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGGradientBackground.h"

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

// We need our own context to prevent Qt to set its own context current
class MyQGLContext : public QGLContext
{
public:
    MyQGLContext (const QGLFormat & format) :
        QGLContext(format)
        {};
    virtual void makeCurrent (){}; // on makeCurrent() just do pretty nothing
};

class MyOSGQGLWidget : public OSG::OSGQGLWidget
{
    public:
        MyOSGQGLWidget( QWidget *parent=0, const char *name=0 );
        MyOSGQGLWidget( MyQGLContext * context,
            QWidget * parent = 0,
            const QGLWidget * shareWidget = 0,
            Qt::WindowFlags f = 0);

        OSG::Trackball   tball;
        OSG::QT4WindowRecPtr osgWin;

    protected:      
        virtual void initializeGL (void);
        virtual void paintGL (void);
        virtual void resizeGL (int w, int h);
        virtual void mousePressEvent ( QMouseEvent* );
        virtual void mouseReleaseEvent ( QMouseEvent* );
        virtual void mouseMoveEvent ( QMouseEvent* );
        virtual void keyPressEvent ( QKeyEvent* );
        
    static void initOpenGL(void);

        OSG::UInt32      mouseb;
        OSG::Int32       lastx;
        OSG::Int32       lasty;
};

MyOSGQGLWidget  *glWidget;
QApplication    *a;

OSG::RenderAction      *ract;
OSG::NodeRecPtr         root;
OSG::NodeRecPtr         file;
OSG::ViewportRecPtr     vp;
OSG::TransformRecPtr    cam_trans;
OSG::PerspectiveCameraRecPtr cam;

OSG::QT4WindowRecPtr osgTWin;

MyOSGQGLWidget::MyOSGQGLWidget ( QWidget *parent, const char *name ) :
    OSG::OSGQGLWidget( parent, name )
{
}

MyOSGQGLWidget::MyOSGQGLWidget( MyQGLContext * context,
    QWidget * parent,
    const QGLWidget * shareWidget,
    Qt::WindowFlags f) :
OSG::OSGQGLWidget(context, parent, shareWidget, f)
{}

void MyOSGQGLWidget::initOpenGL ( void )
{
    // some manual init
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT,   1);

    glDepthFunc(GL_LEQUAL    );
    glEnable   (GL_DEPTH_TEST);

    glEnable   (GL_NORMALIZE );

    // switch off default light
    OSG::Real32 nul[4]={0.f,0.f,0.f,0.f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE,  nul);
    glLightfv(GL_LIGHT0, GL_SPECULAR, nul);
}

void MyOSGQGLWidget::initializeGL ( void )
{
    osgWin->init(&MyOSGQGLWidget::initOpenGL);     // create the context

#if 0
    osgWin->activate(); // and activate it

    // some manual init
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT,   1);

    glDepthFunc(GL_LEQUAL    );
    glEnable   (GL_DEPTH_TEST);

    glEnable   (GL_NORMALIZE );

    // switch off default light
    Real32 nul[4]={0.f,0.f,0.f,0.f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE,  nul);
    glLightfv(GL_LIGHT0, GL_SPECULAR, nul);
#endif

    OSG::commitChanges();

#if 0
    osgWin->frameInit();    // call it to setup extensions
    osgWin->frameExit();    // for symmetry
#endif
}

void MyOSGQGLWidget::paintGL ( void )
{
    OSG::Matrix m1, m2, m3;
    OSG::Quaternion q1;

#if 0
    osgWin->frameInit();    // frame-init
#endif

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
    m1.mult( m2 );
    cam_trans->setMatrix( m1 );

    OSG::commitChanges();

    osgWin->render(ract);   // draw the viewports     

#if 0
    osgWin->renderAllViewports( ract );   // draw the viewports     
    osgWin->swap(); 

    osgWin->frameExit();    // frame-cleanup
#endif
}

void MyOSGQGLWidget::resizeGL ( int w, int h )
{   
    osgWin->resize( w, h );
}

void MyOSGQGLWidget::mousePressEvent ( QMouseEvent *me )
{
    switch ( me->button() ) 
    {
        case Qt::MidButton:
            tball.setAutoPosition(true);
            break;
        case Qt::RightButton:
            tball.setAutoPositionNeg(true);
            break;
        default:
            break;
    }
    mouseb |= me->button();     
    lastx = me->x();
    lasty = me->y();
}

void MyOSGQGLWidget::mouseReleaseEvent ( QMouseEvent *me )
{
    switch ( me->button() )
    {
        case Qt::MidButton:
            tball.setAutoPosition(false);
            break;
        case Qt::RightButton:
            tball.setAutoPositionNeg(false);
            break;
        default:
            break;
    }
    mouseb &= ~me->button();

    lastx = me->x();
    lasty = me->y();    
}

void MyOSGQGLWidget::mouseMoveEvent ( QMouseEvent *me )
{
    OSG::Real32 w = osgWin->getWidth();  // force the calc to Real32
    OSG::Real32 h = osgWin->getHeight();

    OSG::Real32 a = -2. * ( lastx / w - .5 );
    OSG::Real32 b = -2. * ( .5 - lasty / h );
    OSG::Real32 c = -2. * ( me->pos().x() / w - .5 );
    OSG::Real32 d = -2. * ( .5 - me->pos().y() / h );

    if ( mouseb & Qt::LeftButton )
    {
        tball.updateRotation( a, b, c, d );
    }
    else if ( mouseb & Qt::MidButton )
    {
        tball.updatePosition( a, b, c, d );
    }
    else if ( mouseb & Qt::RightButton )
    {
        tball.updatePositionNeg( a, b, c, d );
    }

    lastx = me->pos().x();
    lasty = me->pos().y();
    
    paintGL();
}


void MyOSGQGLWidget::keyPressEvent ( QKeyEvent *ke )
{
    if ( ke->key() == Qt::Key_Escape )
    {
        a->quit();
    }
}


int main( int argc, char **argv )
{
    // OSG init
    OSG::osgInit(argc, argv);

    OSG::SceneFileHandler::the()->print();

    // create the graph

    // beacon for camera and light  
    OSG::NodeRecPtr b1n = OSG::Node::create();
    OSG::GroupRecPtr b1 = OSG::Group::create();
    b1n->setCore( b1 );

    // transformation
    OSG::NodeRecPtr t1n = OSG::Node::create();
    OSG::TransformRecPtr t1 = OSG::Transform::create();
    t1n->setCore( t1 );
    t1n->addChild( b1n );

    cam_trans = t1;

    // light
    OSG::NodeRecPtr dlight = OSG::Node::create();
    OSG::DirectionalLightRecPtr dl = OSG::DirectionalLight::create();

    dlight->setCore( dl );
    
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);

    // root
    root = OSG::Node::create();
    OSG::GroupRecPtr gr1 = OSG::Group::create();
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );

    // Load the file
    OSG::NodeRecPtr file = NULL;
    
    if ( argc > 1 )
        file = OSG::SceneFileHandler::the()->read(argv[1]);
    
    if ( file == NULL )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = OSG::makeTorus( .5, 2, 16, 16 );
    }

    OSG::commitChanges();
    
    file->updateVolume();

    OSG::Vec3f min,max;
    file->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    dlight->addChild( file );

    std::cerr << "Tree: " << std::endl;
    root->dump();

    // Camera
    OSG::PerspectiveCameraRecPtr cam = OSG::PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( OSG::osgDegree2Rad( 60 ) );
    cam->setNear( 1 );
    cam->setFar( 4000 );

    // Background
    OSG::SolidBackgroundRecPtr bkgnd = OSG::SolidBackground::create();
    bkgnd->setColor( OSG::Color3f( 0,0,1 ) );

    // Viewport
    vp = OSG::Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );
    
    // Action
    ract = OSG::RenderAction::create();

    // QT init
    QApplication::setColorSpec( QApplication::CustomColor );
    a = new QApplication( argc, argv );

    if ( !QGLFormat::hasOpenGL() )
    {
        qWarning( "This system has no OpenGL support. Exiting." );
        return -1;
    }

    OSG::Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

    // Create Window
    glWidget = new MyOSGQGLWidget(new MyQGLContext(QGLFormat::defaultFormat()), 0, 0, 0);

    glWidget->tball.setMode( OSG::Trackball::OSGObject );
    glWidget->tball.setStartPosition( pos, true );
    glWidget->tball.setSum( true );
    glWidget->tball.setTranslationMode( OSG::Trackball::OSGFree );

    glWidget->osgWin = OSG::QT4Window::create();
    glWidget->osgWin->setGlWidget( glWidget );
    glWidget->osgWin->addPort( vp );

    a->processEvents();

    glWidget->show();

    a->exec(); // execute QT main loop

    root      = NULL;
    file      = NULL;
    vp        = NULL;
    cam_trans = NULL;
    cam       = NULL;
    osgTWin   = NULL;

    delete glWidget;
    glWidget = NULL;

    return 0;
}
