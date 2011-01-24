/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

/*------------------------------ access -----------------------------------*/
inline void GradientBackground::addLine(Color3f col, Real32 pos)
{
    editMFColor   ()->push_back(col);
    editMFPosition()->push_back(pos);
}

inline void GradientBackground::clearLines(void)
{
    editMFColor   ()->clear();
    editMFPosition()->clear();
}

inline const MFColor3f *GradientBackground::getMFColor(void) const
{
    return &_mfColor;
}

inline const Color3f &GradientBackground::getColor(const UInt32 index) const
{
    return _mfColor[index];
}

inline const MFReal32 *GradientBackground::getMFPosition(void) const
{
    return &_mfPosition;
}

inline const Real32 &GradientBackground::getPosition(const UInt32 index) const
{
    return _mfPosition[index];
}

OSG_END_NAMESPACE
