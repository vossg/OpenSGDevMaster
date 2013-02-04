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

#include <cstdlib>
#include <cstdio>

#include <QtGui/qapplication.h>
#include <QtGui/QDesktopWidget>

#include "OSGConfig.h"

#include "OSGCSMQT4Window.h"
#include "OSGCSMQT4GLWidget_qt.h"
#include "OSGQT4Window.h"
#include "OSGComplexSceneManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMQT4WindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMQT4Window.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

bool          CSMQT4Window::_bRun = false;
QApplication *CSMQT4Window::_pApp = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMQT4Window::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMQT4Window::CSMQT4Window(void) :
     Inherited(    ),
    _pQTWidget(NULL)
{
}

CSMQT4Window::CSMQT4Window(const CSMQT4Window &source) :
     Inherited(source),
    _pQTWidget(NULL  )
{
}

CSMQT4Window::~CSMQT4Window(void)
{
}

void CSMQT4Window::resolveLinks(void)
{
    Inherited::resolveLinks();
}

void CSMQT4Window::terminateGLContext(void)
{
    if(_pWindow != NULL)
    {
        _pWindow->terminate();
    }

    if(_pQTWidget != NULL)
    {
        delete _pQTWidget;

        _pQTWidget = NULL;
    }
}

/*----------------------------- class specific ----------------------------*/

void CSMQT4Window::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMQT4Window::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMQT4Window NI" << std::endl;
}

bool CSMQT4Window::init(void)
{
    if(_pApp == NULL)
    {
        QApplication::setColorSpec(QApplication::CustomColor);

        static       Int32  argc   = 1;
        static const Char8 *argv[] = { "testCSM" };

        _pApp = new QApplication(argc, const_cast<Char8 **>(argv));
    }

    UInt32 uiWidth;
    UInt32 uiHeight;

    Int32  iXPos = 0;
    Int32  iYPos = 0;

    const QRect screenGeometry = QApplication::desktop()->screenGeometry();

    if(this->getXPos() > 0.f && this->getYPos() > 0.f)
    {
        iXPos = Int32(this->getXPos());
        iYPos = Int32(this->getYPos());
    }

    if(this->getXSize() >= 1.f) 
    {
        uiWidth = UInt32(this->getXSize());
    }
    else if(this->getXSize() <= 0.f)
    {
        uiWidth = screenGeometry.width();
    }
    else
    {
        uiWidth = UInt32(Real32(screenGeometry.width()) *
                         this->getXSize());
    }

    if(this->getYSize() >= 1.f)
    {
        uiHeight = UInt32(this->getYSize());
    }
    else if(this->getYSize() <= 0.f)
    {
        uiHeight = screenGeometry.height();
    }
    else
    {
        uiHeight = UInt32(Real32(screenGeometry.height()) *
                          this->getYSize());
    }



    QT4WindowUnrecPtr pQT4Window = QT4Window::create();

    _pQTWidget = 
        new CSMQT4GLWidget(
            new OSGQGLWidget::GLContext(QGLFormat::defaultFormat()), 
            NULL, 
            NULL, 
            0                                                      );

    _pQTWidget->setQT4Window(this);

    if(this->getDecorEnabled() == false)
    {
        _pQTWidget->setWindowFlags(Qt::FramelessWindowHint);
    }

    _pQTWidget->show();
    _pQTWidget->setGeometry(iXPos, iYPos, uiWidth, uiHeight);

    pQT4Window->setGlWidget(_pQTWidget);

    _pApp->processEvents();

    pQT4Window->init();
    pQT4Window->resize(uiWidth,
                       uiHeight);

    if(ComplexSceneManager::the() != NULL)
        ComplexSceneManager::the()->setMainloop(&CSMQT4Window::qtMainLoop);
    
    _pWindow = pQT4Window;

    _bRun = true;

    _pApp->processEvents();


    Inherited::init();

    return true;
}

void CSMQT4Window::qtMainLoop(void)
{
    if(!QGLFormat::hasOpenGL() || _pApp == NULL)
    {
        qWarning( "This system has no OpenGL support. Exiting." );

        return;
    }

    while(_bRun == true)
    {
        _pApp->processEvents(); // execute QT main loop

        ComplexSceneManager::the()->frame();
        
        Thread::getCurrentChangeList()->commitChangesAndClear();
    }

    ComplexSceneManager::the()->terminate();

    delete _pApp;
    
    _pApp = NULL;
}

OSG_END_NAMESPACE
