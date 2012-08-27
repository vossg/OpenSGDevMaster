/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QWheelEvent>

#include "OSGConfig.h"

#include "OSGCSMQT4GLWidget_qt.h"
#include "OSGCSMQT4Window.h"
#include "OSGComplexSceneManager.h"

OSG_BEGIN_NAMESPACE

namespace
{
    Int32 mapModifier(Qt::KeyboardModifiers modifier)
    {
        if(0x0000 != (modifier & Qt::ShiftModifier))
        {
            return MouseData::ShiftActive;
        }
        else if(0x0000 != (modifier & Qt::ControlModifier))
        {
            return MouseData::CtrlActive;
        }
        else if(0x0000 != (modifier & Qt::AltModifier))
        {
            return MouseData::AltActive;
        }
        
        return 0x0001;
    }
    
    Int32 mapButton(Qt::MouseButton button)
    {
        if(0x0000 != (button & Qt::LeftButton))
        {
            return MouseData::LeftButton;
        }
        else if(0x0000 != (button & Qt::RightButton))
        {
            return MouseData::RightButton;
        }
#if QT_VERSION <= 0x040700
        else if(0x0000 != (button & Qt::MidButton))
        {
            return MouseData::MiddleButton;
        }
#else
        else if(0x0000 != (button & Qt::MiddleButton))
        {
            return MouseData::MiddleButton;
        }
#endif
        
        return 0x0001;
    }
}

CSMQT4GLWidget::CSMQT4GLWidget(      QWidget         *parent     ,
                               const Char8           *name       ,
                               const QGLWidget       *shareWidget,
                                     Qt::WFlags       f          ) :
     Inherited (parent, 
                name, 
                shareWidget, 
                f          ),
    _pOSGWindow(NULL        )
{
}

CSMQT4GLWidget::CSMQT4GLWidget(      GLContext       *context    ,
                                     QWidget         *parent     ,
                               const QGLWidget       *shareWidget,
                                     Qt::WindowFlags  f          ) :
     Inherited (context, 
                parent, 
                shareWidget, 
                f          ),
    _pOSGWindow(NULL       )
{
}

CSMQT4GLWidget::CSMQT4GLWidget(const QGLFormat       &format     ,
                                     QWidget         *parent     ,
                               const Char8           *name       ,
                               const QGLWidget       *shareWidget,
                                     Qt::WFlags       f          ) :
     Inherited (format, 
                parent, 
                name, 
                shareWidget, 
                f          ),
    _pOSGWindow(NULL       )
{
}

CSMQT4GLWidget::~CSMQT4GLWidget(void)
{
}


void CSMQT4GLWidget::setQT4Window(CSMQT4Window *pWindow)
{
    _pOSGWindow = pWindow;
}

void CSMQT4GLWidget::resizeEvent(QResizeEvent *)
{
    if(_pOSGWindow != NULL)
    {
        _pOSGWindow->reshape(width(), height());
    }
}

void CSMQT4GLWidget::mousePressEvent(QMouseEvent *pEvent)
{
    if(_pOSGWindow != NULL)
    {
        _pOSGWindow->mouse(mapButton(pEvent->button()),
                           MouseData::ButtonDown,
                           mapModifier(pEvent->modifiers()),
                           pEvent->x(),
                           pEvent->y());
    }
}

void CSMQT4GLWidget::mouseReleaseEvent(QMouseEvent *pEvent)
{
    if(_pOSGWindow != NULL)
    {
        _pOSGWindow->mouse(mapButton(pEvent->button()),
                           MouseData::ButtonUp,
                           mapModifier(pEvent->modifiers()),
                           pEvent->x(),
                           pEvent->y());
    }
}

void CSMQT4GLWidget::mouseMoveEvent(QMouseEvent *pEvent)
{
    if(_pOSGWindow != NULL)
    {
        _pOSGWindow->motion(pEvent->x(), 
                            pEvent->y(),
                            mapModifier(pEvent->modifiers()));
    }
}

void CSMQT4GLWidget::wheelEvent(QWheelEvent *pEvent)
{
    if(_pOSGWindow != NULL)
    {
        if(pEvent->delta() < 0)
        {
            _pOSGWindow->mouse(MouseData::WheelUpButton,
                               MouseData::ButtonDown,
                               mapModifier(pEvent->modifiers()),
                               pEvent->x(),
                               pEvent->y());
        }
        else
        {
            _pOSGWindow->mouse(MouseData::WheelDownButton,
                               MouseData::ButtonDown,
                               mapModifier(pEvent->modifiers()),
                               pEvent->x(),
                               pEvent->y());
        }
    }
}

void CSMQT4GLWidget::keyPressEvent(QKeyEvent *pEvent)
{
    if(pEvent->key() == Qt::Key_Escape)
    {
        if(_pOSGWindow != NULL)
        {
            _pOSGWindow->_bRun = false;
        }
    }
    else
    {
        std::string szKey = pEvent->text().toStdString();

        if(szKey.empty() == false)
        {
            ComplexSceneManager::the()->key(0,
                                            0,
                                            CSMKeyData::ButtonDown,
                                            szKey[0]              );
        }
    }
}

void CSMQT4GLWidget::keyReleaseEvent(QKeyEvent *pEvent)
{
    std::string szKey = pEvent->text().toStdString();

    if(szKey.empty() == false)
    {
        ComplexSceneManager::the()->key(0,
                                        0,
                                        CSMKeyData::ButtonUp,
                                        szKey[0]            );
    }
}

OSG_END_NAMESPACE
