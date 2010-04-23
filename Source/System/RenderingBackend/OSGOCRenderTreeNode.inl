/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                    Copyright (C) 2010 by the OpenSG Forum                 *
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

inline void
OCRenderTreeNode::setVolume(const BoxVolume &vol)
{
    _bVol = vol;
}

inline const BoxVolume &
OCRenderTreeNode::getVolume(void) const
{
    return _bVol;
}

inline void
OCRenderTreeNode::setResultNum(UInt32 resultNum)
{
    _resultNum = resultNum;
}

inline UInt32
OCRenderTreeNode::getResultNum(void) const
{
    return _resultNum;
}

inline void
OCRenderTreeNode::setIsRendered(bool value)
{
    _isRendered = value;
}

inline bool
OCRenderTreeNode::getIsRendered(void) const
{
    return _isRendered;
}

/*! \note Not virtual, because the pools always have a pointer
          of the exact type and we avoid the virtual call overhead.
 */
inline void
OCRenderTreeNode::reset(void)
{
    Inherited::reset();

    _bVol.setEmpty();
    _resultNum  = 0;
    _isRendered = false;
}

OSG_END_NAMESPACE
