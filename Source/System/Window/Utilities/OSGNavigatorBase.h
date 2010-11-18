/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2009 by the OpenSG Forum                    *
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

#ifndef _OSG_NAVIGATORBASE_H_
#define _OSG_NAVIGATORBASE_H_

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING NavigatorBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    enum Mode
    {
        TRACKBALL=0,
        FLY,
        WALK,
        NAVBALL,
        NONE,
        USER
    };

    enum State
    {
        IDLE=0,
        ROTATING,
        TRANSLATING_XY,
        TRANSLATING_Z,

        TRANSLATING_ZPLUS=10,
        TRANSLATING_ZMINUS
    };

    enum MouseButton
    {
        LEFT_MOUSE=0,
        MIDDLE_MOUSE,
        RIGHT_MOUSE,
        UP_MOUSE,
        DOWN_MOUSE
    };

    enum Key
    {
        LEFT=0,
        RIGHT,
        FORWARDS,
        BACKWARDS,
        LEFTROT,
        RIGHTROT
    };

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#endif //_OSG_NAVIGATORBASE_H_
