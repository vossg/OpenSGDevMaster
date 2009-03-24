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

OSG_USING_NAMESPACE

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


OSGQGLWidget::OSGQGLWidget(      QWidget    *parent,
                           const char       *name,
                           const QGLWidget  *shareWidget,
                                 Qt::WFlags  f           ) :
    QGLWidget( parent, shareWidget, f ) 
{
}

OSGQGLWidget::OSGQGLWidget(      QGLContext      *context,
                                 QWidget         *parent ,
                           const QGLWidget       *shareWidget,
                                 Qt::WindowFlags  f           ) :
    QGLWidget(context, parent, shareWidget, f)
{
}

OSGQGLWidget::OSGQGLWidget(const QGLFormat  &format,
                                 QWidget    *parent,
                           const char       *name,
                           const QGLWidget  *shareWidget,
                                 Qt::WFlags  f           ) :
    QGLWidget(format, parent, shareWidget, f)
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
}

void OSGQGLWidget::swapBuffers(void)
{
}

#endif /* OSG_WITH_QT */
