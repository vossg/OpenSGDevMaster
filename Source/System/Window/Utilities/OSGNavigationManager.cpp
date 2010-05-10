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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGImageFileType.h"
#include "OSGSolidBackground.h"
#include "OSGViewport.h"
#include "OSGDrawable.h"
#include "OSGTransform.h"

#include "OSGNavigationManager.h"

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NavigationManager
    \ingroup GrpSystemWindow

    The NavigationManager manages a navigator that is needed to do a
    basic navigation within a subscene of a scenegraph (specified by the
    beacon). It also takes care of creating the necessary additional OpenSG 
    objects, like a viewport for the window (if not already present).
 */

/*! \var NavigationManager::MouseLeft
    The constant for the left mouse button.
 */

/*! \var NavigationManager::MouseMiddle
    The constant for the middle mouse button.
 */

/*! \var NavigationManager::MouseRight
    The constant for the right mouse button.
 */

/*! \var NavigationManager::MouseUp
    The constant for the mouse wheel up (away from the hand) motion.
 */

/*! \var NavigationManager::MouseDown
    The constant for the mouse wheel down (towards the hand) motion.
 */

/*! \var NavigationManager::_win
    The managed window. Has to be set by the user.
 */

/*! \var NavigationManager::_navigator
    The navigator for viewer manipulation.
 */

/*! \var NavigationManager::_lastx
    The x position of the last mouse event, needed by the navigator.
 */

/*! \var NavigationManager::_lasty
    The y position of the last mouse event, needed by the navigator.
 */

/*! \var NavigationManager::_mousebuttons
    Storage for the actively pressed mouse buttons. Needed to do the right
    thing for mouse motions, as mouseMove() doesn't get them.
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 */

NavigationManager::NavigationManager(void) :
    _win            (NULL),
    _navigator      (      ),
    _lastx          (TypeTraits<Int16>::getMax()),
    _lasty          (TypeTraits<Int16>::getMax()),
    _mousebuttons   (0                          )
{
    _navigator.setMode(Navigator::TRACKBALL);
}


/*! pseudo constructor. Standard interface for OpenSG object creation.
 */
NavigationManager* NavigationManager::create(void)
{
    return new NavigationManager;
}

/*! Destructor
 */

NavigationManager::~NavigationManager(void)
{
    _win = NULL;

}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

/*! get the window to be used for display
 */
Window *NavigationManager::getWindow(void)
{
    return _win;
}

/*! get the navigator
 */
Navigator *NavigationManager::getNavigator(void)
{
    return &_navigator;
}

/*-------------------------------------------------------------------------*/
/*                               Set                                       */

/*! set the window to be used for display
 */
void NavigationManager::setWindow(Window *win)
{
    if(win == NULL)
    {
        FWARNING(("NavigationManager::setWindow: new window is NULL, "
                  "ignoring!\n"));
        return;
    }

    _win = win;
    if(_win->getMFPort()->size() > 0 && _win->getPort(0) != NULL)
        _navigator.setViewport(_win->getPort(0));
}

/*! Sets the navigator's camera transformation
    If newBeacon is null, a dummy beacon will be added instead.
 */
void NavigationManager::setBeacon(Node * const newBeacon)
{
    if (newBeacon == NULL) {
        setNavigationMode(Navigator::NONE);
        TransformNodeRefPtr xnode = TransformNodeRefPtr::create();
        _navigator.setCameraTransformation(xnode);
    }
    else
        _navigator.setCameraTransformation(newBeacon);
}

/*! Sets the navigation mode
 */
void NavigationManager::setNavigationMode (Navigator::Mode new_mode)
{
    Matrix m=_navigator.getMatrix();
    _navigator.setMode(new_mode);
    _navigator.set(m);
}

/*-------------------------------------------------------------------------*/
/*                         Interaction handling                            */

/*! resize
 */
void NavigationManager::resize(UInt16 width, UInt16 height)
{
    _win->resize(width, height);
}

/*! motion
 */
void NavigationManager::mouseMove(Int16 x, Int16 y)
{
    if ( _mousebuttons) _navigator.moveTo(x,y);
    _lastx = x;
    _lasty = y;

}

/*! call when a mouse button is pressed. button is the number of the pressed
    button, starting at 0, ordered from left to right. A wheel should be
    mapped to buttons 3 and 4. The position is in pixel, starting at the
    upper left corner.
 */

void NavigationManager::mouseButtonPress(UInt16 button, Int16 x, Int16 y)
{
    switch (button)
    {
    case MouseLeft:    _navigator.buttonPress(Navigator::LEFT_MOUSE,x,y);
      break;
    case MouseMiddle:  _navigator.buttonPress(Navigator::MIDDLE_MOUSE,x,y);
      break;
    case MouseRight:   _navigator.buttonPress(Navigator::RIGHT_MOUSE,x,y);
      break;
    case MouseUp:      _navigator.buttonPress(Navigator::UP_MOUSE,x,y);
      break;
    case MouseDown:    _navigator.buttonPress(Navigator::DOWN_MOUSE,x,y);
      break;
    }

    updateMouseButtonPress(button, x, y);
}


/*! call when a mouse button is released. button is the number of the pressed
    button, starting at 0, ordered from left to right. A wheel should be
    mapped to buttons 3 and 4. The position is in pixel, starting at the
    upper left corner.
 */
void NavigationManager::mouseButtonRelease(UInt16 button, Int16 x, Int16 y)
{
    switch (button)
    {
    case MouseLeft:     _navigator.buttonRelease(Navigator::LEFT_MOUSE,x,y);
                        break;
    case MouseMiddle:   _navigator.buttonRelease(Navigator::MIDDLE_MOUSE,x,y);
                        break;
    case MouseRight:    _navigator.buttonRelease(Navigator::RIGHT_MOUSE,x,y);
                        break;
    case MouseUp:       _navigator.buttonRelease(Navigator::UP_MOUSE,x,y);
                        break;
    case MouseDown:     _navigator.buttonRelease(Navigator::DOWN_MOUSE,x,y);
                        break;
    }

    updateMouseButtonRelease(button, x, y);
}

void NavigationManager::key(UChar8 key, Int16 x, Int16 y)
{
    switch ( key )
    {
        case 'j': _navigator.keyPress(Navigator::LEFT,x,y); break;
        case 'g': _navigator.keyPress(Navigator::RIGHT,x,y); break;
        case 'u': _navigator.keyPress(Navigator::LEFTROT,x,y); break;
        case 't': _navigator.keyPress(Navigator::RIGHTROT,x,y); break;
        case 'y': _navigator.keyPress(Navigator::FORWARDS,x,y); break;
        case 'h': _navigator.keyPress(Navigator::BACKWARDS,x,y); break;
    }
}



/*-------------------------------------------------------------------------*/
/*                                Actions                                  */

/*! Draw the next frame, update if needed.
 */
void NavigationManager::idle(void)
{
    _navigator.idle(_mousebuttons,_lastx, _lasty);
}

/*! Update data needed for rendering.
 */
void NavigationManager::update(void)
{
    // Check necessary stuff
    if(_win == NULL)
    {
        FWARNING(("NavigationManager::update: window not set, "
                  "ignoring!\n"));
        return;
    }

    // need a viewport?
    if(_win->getMFPort()->size() == 0)
    {
        SolidBackgroundUnrecPtr bg = SolidBackground::create();

        bg->setColor(Color3f(0.2, 0.2, 0.2));

        ViewportUnrecPtr vp = Viewport::create();

        vp->setSize      (0,0, 1,1);
        vp->setBackground(bg);

        _win->addPort(vp);
        _navigator.setViewport(_win->getPort(0));
    }

    _navigator.updateCameraTransformation();
}

/*! Draw the next frame, update if needed.
 */
void NavigationManager::redraw(void)
{
    update();
}

/*-------------------------------------------------------------------------*/
/*                               Updates                                   */

/*! called internally by mouseButtonRelease() to keep track of the
    current status of _mousebuttons, _lastx and _lasty 
 */
void NavigationManager::updateMouseButtonPress(UInt16 button,
                                               Int16 x, Int16 y)
{
    _mousebuttons |= 1 << button;
    _lastx = x;
    _lasty = y;
}


/*! called internally by mouseButtonRelease() to keep track of the
    current status of _mousebuttons, _lastx and _lasty 
 */
void NavigationManager::updateMouseButtonRelease(UInt16 button,
                                                 Int16 x, Int16 y)
{
    _mousebuttons &= ~(1 << button);
    _lastx = x;
    _lasty = y;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*! less
 */

bool NavigationManager::operator < (const NavigationManager &other) const
{
    return this < &other;
}

