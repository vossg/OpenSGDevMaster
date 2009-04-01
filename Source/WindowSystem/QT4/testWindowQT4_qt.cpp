// Single-threaded QT example

#include <OSGConfig.h>

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

#include <OSGFieldContainerFactory.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGAction.h>
#include <OSGRenderAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGDirectionalLight.h>
#include <OSGSimpleGeometry.h>

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

OSG_BEGIN_NAMESPACE

// We need our own context to prevent Qt to set its own context current
class MyQGLContext : public QGLContext
{
public:
    MyQGLContext (const QGLFormat & format) :
        QGLContext(format)
        {};
    virtual void makeCurrent (){}; // on makeCurrent() just do pretty nothing
};

class MyOSGQGLWidget : public OSGQGLWidget
{
    public:
        MyOSGQGLWidget( QWidget *parent=0, const char *name=0 );
        MyOSGQGLWidget( MyQGLContext * context,
            QWidget * parent = 0,
            const QGLWidget * shareWidget = 0,
            Qt::WindowFlags f = 0);

        Trackball   tball;
        QT4WindowRecPtr osgWin;

    protected:      
        virtual void initializeGL (void);
        virtual void paintGL (void);
        virtual void resizeGL (int w, int h);
        virtual void mousePressEvent ( QMouseEvent* );
        virtual void mouseReleaseEvent ( QMouseEvent* );
        virtual void mouseMoveEvent ( QMouseEvent* );
        virtual void keyPressEvent ( QKeyEvent* );
        
        UInt32      mouseb;
        Int32       lastx;
        Int32       lasty;
};

OSG_END_NAMESPACE

using namespace OSG;

MyOSGQGLWidget  *glWidget;
QApplication    *a;

RenderAction      *ract;
NodeRecPtr         root;
NodeRecPtr         file;
ViewportRecPtr     vp;
TransformRecPtr    cam_trans;
PerspectiveCameraRecPtr cam;

QT4WindowRecPtr osgTWin;

MyOSGQGLWidget::MyOSGQGLWidget ( QWidget *parent, const char *name ) :
    OSGQGLWidget( parent, name )
{
}

MyOSGQGLWidget::MyOSGQGLWidget( MyQGLContext * context,
    QWidget * parent,
    const QGLWidget * shareWidget,
    Qt::WindowFlags f) :
OSGQGLWidget(context, parent, shareWidget, f)
{}

void MyOSGQGLWidget::initializeGL ( void )
{
    osgWin->init();     // create the context
    osgWin->activate(); // and activate it

    // some manual init
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT,   1);

    glDepthFunc(GL_LEQUAL    );
    glEnable   (GL_DEPTH_TEST);

    glEnable   (GL_NORMALIZE );

    // switch off default light
    Real nul[4]={0.f,0.f,0.f,0.f};

    GLP::glLightfv(GL_LIGHT0, GL_DIFFUSE,  nul);
    GLP::glLightfv(GL_LIGHT0, GL_SPECULAR, nul);

    commitChanges();

    osgWin->frameInit();    // call it to setup extensions
    osgWin->frameExit();    // for symmetry
}

void MyOSGQGLWidget::paintGL ( void )
{
    Matrix m1, m2, m3;
    Quaternion q1;

    osgWin->frameInit();    // frame-init

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
    m1.mult( m2 );
    cam_trans->setMatrix( m1 );

    commitChanges();
    osgWin->renderAllViewports( ract );   // draw the viewports     
    osgWin->swap(); 

    osgWin->frameExit();    // frame-cleanup
}

void MyOSGQGLWidget::resizeGL ( int w, int h )
{   
   if ( ! osgWin->isResizePending() )
   {
        osgWin->resize( w, h );
        osgWin->resizeGL(); // handle resize events
   }
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
    Real32 w = osgWin->getWidth();  // force the calc to Real32
    Real32 h = osgWin->getHeight();

    Real32 a = -2. * ( lastx / w - .5 );
    Real32 b = -2. * ( .5 - lasty / h );
    Real32 c = -2. * ( me->pos().x() / w - .5 );
    Real32 d = -2. * ( .5 - me->pos().y() / h );

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
    osgInit(argc, argv);

    SceneFileHandler::the()->print();

    // create the graph

    // beacon for camera and light  
    NodeRecPtr b1n = Node::create();
    GroupRecPtr b1 = Group::create();
    b1n->setCore( b1 );

    // transformation
    NodeRecPtr t1n = Node::create();
    TransformRecPtr t1 = Transform::create();
    t1n->setCore( t1 );
    t1n->addChild( b1n );

    cam_trans = t1;

    // light
    NodeRecPtr dlight = Node::create();
    DirectionalLightRecPtr dl = DirectionalLight::create();

    dlight->setCore( dl );
    
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);

    // root
    root = Node::create();
    GroupRecPtr gr1 = Group::create();
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );

    // Load the file
    NodeRecPtr file = NULL;
    
    if ( argc > 1 )
        file = SceneFileHandler::the()->read(argv[1]);
    
    if ( file == NULL )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = makeTorus( .5, 2, 16, 16 );
    }

    commitChanges();
    
    file->updateVolume();

    Vec3f min,max;
    file->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    dlight->addChild( file );

    std::cerr << "Tree: " << std::endl;
    root->dump();

    // Camera
    PerspectiveCameraRecPtr cam = PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( osgDegree2Rad( 60 ) );
    cam->setNear( 1 );
    cam->setFar( 4000 );

    // Background
    SolidBackgroundRecPtr bkgnd = SolidBackground::create();
    bkgnd->setColor( Color3f( 0,0,1 ) );

    // Viewport
    vp = Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );
    
    // Action
    ract = RenderAction::create();

    // QT init
    QApplication::setColorSpec( QApplication::CustomColor );
    a = new QApplication( argc, argv );

    if ( !QGLFormat::hasOpenGL() )
    {
        qWarning( "This system has no OpenGL support. Exiting." );
        return -1;
    }

    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

    // Create Window
    glWidget = new MyOSGQGLWidget(new MyQGLContext(QGLFormat::defaultFormat()), 0, 0, 0);

    glWidget->tball.setMode( Trackball::OSGObject );
    glWidget->tball.setStartPosition( pos, true );
    glWidget->tball.setSum( true );
    glWidget->tball.setTranslationMode( Trackball::OSGFree );

    glWidget->osgWin = QT4Window::create();
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
