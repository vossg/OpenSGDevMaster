/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

OSG_BEGIN_NAMESPACE

inline
void SimpleTextForeground::addLine(const std::string &szText)
{
    editMFLines()->push_back(szText);
}

inline
void SimpleTextForeground::clear(void)
{
    editMFLines()->clear();
}

inline
bool SimpleTextForeground::TextColoredRange::isBounded(UInt32 uiPosition) const
{
    return (uiPosition >= _uiStart &&
            uiPosition <= _uiEnd);
}

inline
SimpleTextForeground::TextColoredRange::TextColoredRange(      UInt32  uiStart,
                                                               UInt32  uiEnd,
                                                         const Color4f &cColor):
    _uiStart(uiStart),
    _uiEnd  (uiEnd  ),
    _cColor (cColor )
{
}

inline
const Color4f &SimpleTextForeground::TextColoredRange::getColor(void) const
{
    return _cColor;
}

inline
UInt32 SimpleTextForeground::TextColoredRange::getStart(void) const
{
    return _uiStart;
}

inline
UInt32 SimpleTextForeground::TextColoredRange::getEnd(void) const
{
    return _uiEnd;
}


OSG_END_NAMESPACE
