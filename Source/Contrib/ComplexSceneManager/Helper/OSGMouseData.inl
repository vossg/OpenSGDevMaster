/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

OSG_BEGIN_NAMESPACE


inline
Int32 MouseData::getButton(void) const
{
    return _iButton;
}

inline
Int32 MouseData::getState(void) const
{
    return _iState;
}

inline
Int32 MouseData::getModifier(void) const
{
    return _iModifier;
}

inline
Real32 MouseData::getX(void) const
{
    return _rX;
}

inline
Real32 MouseData::getY(void) const
{
    return _rY;
}

inline
Window *MouseData::getWindow(void) const
{
    return _pWindow;
}

inline
Viewport *MouseData::getViewport(void) const
{
    return _pViewport;
}

inline
UInt32 MouseData::getMode(void) const
{
    return _uiMode;
}

inline
void MouseData::setViewport(Viewport *pViewport)
{
    _pViewport = pViewport;
}

OSG_END_NAMESPACE
