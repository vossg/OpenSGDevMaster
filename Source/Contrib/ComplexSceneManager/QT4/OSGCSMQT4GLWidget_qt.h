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

#ifndef _OSGCSMQT4GLWIDGET_H_
#define _OSGCSMQT4GLWIDGET_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#ifdef OSG_WITH_QT

#include "OSGContribCSMDef.h"
#include "OSGBaseTypes.h"

#include "OSGQ4GLWidget_qt.h"

namespace OSG {

class CSMQT4Window;

/*! \brief OSGQGL widget class. See \ref PageWindowQT for a description. 
    \ingroup GrpWindowQt4Obj
    \ingroup GrpLibOSGWindowQt4
    \includebasedoc
 */

class OSG_CONTRIBCSM_DLLMAPPING CSMQT4GLWidget : public OSGQGLWidget
{
    Q_OBJECT

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CSMQT4GLWidget(      QWidget         *parent,
                   const Char8           *name         = 0,
                   const QGLWidget       *shareWidget  = 0,
                         Qt::WFlags       f            = 0                   );
    CSMQT4GLWidget(      GLContext       *context,
                         QWidget         *parent      = 0,
                   const QGLWidget       *shareWidget = 0,
                         Qt::WindowFlags  f           = 0                    );

    CSMQT4GLWidget(const QGLFormat       &format = QGLFormat::defaultFormat(),
                         QWidget         *parent      = 0,
                   const Char8           *name        = 0,
                   const QGLWidget       *shareWidget = 0,
                         Qt::WFlags       f           = 0                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Desstructor                                */
    /*! \{                                                                 */

    virtual ~CSMQT4GLWidget(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Desstructor                                */
    /*! \{                                                                 */

    void setQT4Window(CSMQT4Window *pWindow);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 OpenGL handling                              */
    /*! \{                                                                 */
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef OSGQGLWidget Inherited;

    CSMQT4Window *_pOSGWindow;

    /*---------------------------------------------------------------------*/
    /*! \name                 OpenGL handling                              */
    /*! \{                                                                 */

    virtual void resizeEvent      (QResizeEvent *pEvent);
    virtual void mousePressEvent  (QMouseEvent  *pEvent);
    virtual void mouseReleaseEvent(QMouseEvent  *pEvent);
    virtual void mouseMoveEvent   (QMouseEvent  *pEvent);
    virtual void wheelEvent       (QWheelEvent  *pEvent);
    virtual void keyPressEvent    (QKeyEvent    *pEvent);
    virtual void keyReleaseEvent  (QKeyEvent    *pEvent);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /* prohibit default function (move to 'public' if needed) */
    CSMQT4GLWidget(const CSMQT4GLWidget &source);
    /* prohibit default function (move to 'public' if needed) */
    void operator =(const CSMQT4GLWidget &source);
};

typedef CSMQT4GLWidget * CSMQT4GLWidgetP;                      

}

//#include "OSGQ4GLWidget_qt.inl"

#endif // OSG_WITH_QT

#endif // _OSGCSMQT4GLWIDGET_H_
