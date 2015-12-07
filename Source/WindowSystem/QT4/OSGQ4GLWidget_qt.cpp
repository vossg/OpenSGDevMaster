/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGQ4GLWidget_qt.h"

#ifdef OSG_WITH_QT

#include <QtGui/qevent.h>

OSG_BEGIN_NAMESPACE

OSGQGLWidget::GLContext::GLContext(const QGLFormat & format) :
    QGLContext(format)
{
}
 
 // on makeCurrent() just do pretty nothing
void OSGQGLWidget::GLContext::makeCurrent(void)
{
    if(this != QGLContext::currentContext())
    {
        OSG_ASSERT(false);
    }
}

void OSGQGLWidget::GLContext::doneCurrent(void)
{
#ifndef WIN32 // have to figure out why (GV)
    OSG_ASSERT(false);
#endif
}

void OSGQGLWidget::GLContext::swapBuffers(void)
{
    OSG_ASSERT(false);
}

void OSGQGLWidget::GLContext::doMakeCurrent(void)
{
    QGLContext::makeCurrent();
}

void OSGQGLWidget::GLContext::doDoneCurrent(void)
{
    QGLContext::doneCurrent();
}

void OSGQGLWidget::GLContext::doSwapBuffers(void)
{
    QGLContext::swapBuffers();
}

/*! \class OSG::QTWindow

The class for QT-based windows. See \ref PageWindowQT for a description.

*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*! Constructor
*/


OSGQGLWidget::OSGQGLWidget(      QWidget        *parent,
                           const char           *name,
                           const QGLWidget      *shareWidget,
                                 Qt::WindowFlags f           ) :
    QGLWidget(new GLContext(QGLFormat::defaultFormat()),
              parent, 
              shareWidget, 
              f                                        ) 
{
}

OSGQGLWidget::OSGQGLWidget(      GLContext       *context,
                                 QWidget         *parent ,
                           const QGLWidget       *shareWidget,
                                 Qt::WindowFlags  f           ) :
    QGLWidget(context, parent, shareWidget, f)
{
}

OSGQGLWidget::OSGQGLWidget(const QGLFormat       &format,
                                 QWidget         *parent,
                           const char            *name,
                           const QGLWidget       *shareWidget,
                                 Qt::WindowFlags  f           ) :
    QGLWidget(new GLContext(format), parent, shareWidget, f)
{
}


/*! Destructor
*/

OSGQGLWidget::~OSGQGLWidget( void )
{
}


/*------------------------------ access -----------------------------------*/

void OSGQGLWidget::initializeGL(void) 
{
}

void OSGQGLWidget::paintGL(void) 
{
}

void OSGQGLWidget::resizeGL(int, int) 
{
}

void OSGQGLWidget::makeCurrent(void)
{
    OSG_ASSERT(false);
}

void OSGQGLWidget::doneCurrent(void)
{
    OSG_ASSERT(false);
}

void OSGQGLWidget::swapBuffers(void)
{
    OSG_ASSERT(false);
}

bool OSGQGLWidget::event(QEvent *pEvent)
{
#if defined(Q_WS_X11)
    if(pEvent->type() != QEvent::Hide &&
       pEvent->type() != QEvent::ParentChange) 
    {
        return Inherited::event(pEvent);
    }

    return true;
#else
    return Inherited::event(pEvent);
#endif
}

void OSGQGLWidget::resizeEvent(QResizeEvent *) 
{
    resizeGL(width(), height()); 
}

void OSGQGLWidget::glDraw(void) 
{
    paintGL();
}

void OSGQGLWidget::paintEvent(QPaintEvent *) 
{ 
    paintGL(); 
}

void OSGQGLWidget::doMakeCurrent(void)
{
    QGLContext *pQContext = const_cast  <QGLContext *>(this->context());
    GLContext  *pContext  = dynamic_cast<GLContext  *>(pQContext);


    if(pContext != NULL)
    {
        pContext->doMakeCurrent();
    }
#ifdef WIN32 // windows switches the context somewhere, find and fix (GV)
    else if(pQContext != NULL)
    {
        pQContext->makeCurrent();
    }
#endif
    else
    {
        fprintf(stderr, "qglw::mc no context\n");
    }
}

void OSGQGLWidget::doDoneCurrent(void)
{
    QGLContext *pQContext = const_cast  <QGLContext *>(this->context());
    GLContext  *pContext  = dynamic_cast<GLContext  *>(pQContext);

    if(pContext != NULL)
    {
        pContext->doDoneCurrent();
    }
#ifdef WIN32 // windows switches the context somewhere, find and fix (GV)
    else if(pQContext != NULL)
    {
        pQContext->doneCurrent();
    }
#endif
    else
    {
        fprintf(stderr, "qglw::dc no context\n");
    }
}

void OSGQGLWidget::doSwapBuffers(void)
{
    QGLContext *pQContext = const_cast  <QGLContext *>(this->context());
    GLContext  *pContext  = dynamic_cast<GLContext  *>(pQContext);

    if(pContext != NULL)
    {
        pContext->doSwapBuffers();
    }
#ifdef WIN32 // windows switches the context somewhere, find and fix (GV)
    else if(pQContext != NULL)
    {
        pQContext->swapBuffers();
    }
#endif
    else
    {
        fprintf(stderr, "qglw::sb no context\n");
    }
}


OSG_END_NAMESPACE

#endif /* OSG_WITH_QT */
