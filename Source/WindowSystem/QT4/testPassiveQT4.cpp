// little example on how to use OpenSG with a standard QT OpenGL widget
// should be independent of QT version, and might also be used as an example
// on how ot integrate OpenSG into other windowing toolkits

// The only thing lost by doing it like this is the ability to separate the
// rendering and interface threads. If you need that you will have to 
// use the real OpenSG QT widget.

// It is ASAP (as simple as possible ;), and thus probably not a good example 
// for style, but I hope it's good enough to see what's going on.

// This code is based on the QT opengl/gear example.

#include <OSGGL.h>

#include <math.h>

#ifdef OSG_WITH_QT5
#include <QtWidgets/QApplication>
#else
#include <QtGui/qapplication.h>
#endif

#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>

#if defined(Q_CC_MSVC)
#pragma warning(disable:4305) // init: truncation from const double to float
#endif

#include "OSGConfig.h"
#include "OSGSceneFileHandler.h"
#include "OSGSimpleGeometry.h"
#include "OSGPassiveWindow.h"
#include "OSGSimpleSceneManager.h"

QApplication *a = NULL;

class OpenSGWidget : public QGLWidget
{
  public:

    OpenSGWidget(const QGLFormat &oF, QWidget *pParent=0);

    OSG::SimpleSceneManager *getManager(void);

  protected:

    void resizeGL         (int, 
                           int            );
    void paintGL          (void           );
    void initializeGL     (void           );

    virtual void mousePressEvent  (QMouseEvent *ev);
    virtual void mouseMoveEvent   (QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void wheelEvent       (QWheelEvent *ev);
    virtual void keyPressEvent    (QKeyEvent   *ev);

    OSG::SimpleSceneManagerRefPtr mgr;
    OSG::PassiveWindowRecPtr      pwin;
};

OpenSGWidget::OpenSGWidget(const QGLFormat &oF, QWidget *pParent) : 
    QGLWidget(oF, pParent),
    mgr      (nullptr    ),
    pwin     (nullptr    )
{
    setAutoBufferSwap(false);

    mgr  = OSG::SimpleSceneManager::create();
    pwin = OSG::PassiveWindow::create();

    mgr->setWindow(pwin);
}

OSG::SimpleSceneManager *OpenSGWidget::getManager(void)
{
    return mgr;
}


void OpenSGWidget::resizeGL( int iWidth, int iHeight )
{
    mgr->resize(iWidth, iHeight);
}

void OpenSGWidget::paintGL(void)
{
    mgr->redraw();
    swapBuffers();
}

void OpenSGWidget::initializeGL(void)
{
    if(pwin != NULL)
    {
        pwin->init();
    }
}

void OpenSGWidget::mousePressEvent(QMouseEvent *ev)
{
    OSG::UInt32 button;
    
    switch(ev->button()) 
    {
        case Qt::LeftButton:  
            button = OSG::SimpleSceneManager::MouseLeft;   
            break;
        case Qt::MidButton:   
            button = OSG::SimpleSceneManager::MouseMiddle; 
            break;
        case Qt::RightButton: 
            button = OSG::SimpleSceneManager::MouseRight;  
            break;
        default:  
            return;
    }

    mgr->mouseButtonPress(button, ev->x(), ev->y());

    update();
}

void OpenSGWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    OSG::UInt32 button;
    
    switch(ev->button()) 
    {
        case Qt::LeftButton:  
            button = OSG::SimpleSceneManager::MouseLeft;   
            break;
        case Qt::MidButton:   
            button = OSG::SimpleSceneManager::MouseMiddle; 
            break;
        case Qt::RightButton: 
            button = OSG::SimpleSceneManager::MouseRight;  
            break;
        default:
            return;
    }

    mgr->mouseButtonRelease(button, ev->x(), ev->y());

    update();
}

void OpenSGWidget::mouseMoveEvent(QMouseEvent *ev)
{
    mgr->mouseMove(ev->x(), ev->y());

    update();
}

void OpenSGWidget::wheelEvent(QWheelEvent *ev)
{
    mgr->mouseButtonPress(ev->delta() > 0 ? OSG::SimpleSceneManager::MouseUp
                                          : OSG::SimpleSceneManager::MouseDown, 
                          ev->x(), ev->y());
    
    ev->accept();

    update();
}

void OpenSGWidget::keyPressEvent(QKeyEvent *ke)
{
    if(ke->key() == Qt::Key_Escape)
    {
        a->quit();
    }
}

int main( int argc, char **argv )
{
    OSG::osgInit(argc,argv);
    
    QApplication::setColorSpec(QApplication::CustomColor);

    a = new QApplication(argc, argv);

    if(!QGLFormat::hasOpenGL()) 
    {
        qWarning( "This system has no OpenGL support. Exiting." );
        return -1;
    }
    
    OpenSGWidget *w = new OpenSGWidget(
        QGLFormat(QGL::DoubleBuffer   | 
                  QGL::DepthBuffer    | 
                  QGL::Rgba           |
                  QGL::DirectRendering));

    // create the scene
    OSG::NodeRecPtr scene;
    
    if(argc > 1)
    {
        scene = OSG::Node::create();

        OSG::GroupRecPtr g = OSG::Group::create();

        scene->setCore(g);
        
        for(OSG::UInt16 i = 1; i < argc; ++i)
            scene->addChild(OSG::SceneFileHandler::the()->read(argv[i]));
    }
    else
    {
        scene = OSG::makeTorus(.5, 3, 16, 16);
    }

    w->getManager()->setRoot(scene);
    w->getManager()->showAll();

    w->show();

    a->exec();

    delete w;
    delete a;
}
