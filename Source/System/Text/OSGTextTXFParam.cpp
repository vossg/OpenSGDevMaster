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

#ifdef _MSC_VER
# pragma warning (disable: 4786)
#endif

#include "OSGTextTXFParam.h"

#include <algorithm>


using namespace std;


OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Static Class Variable implementations
// Author: pdaehne
//----------------------------------------------------------------------
wstring TextTXFParam::_defaultCharacters =
    L" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";


//----------------------------------------------------------------------
// Compares the Param object with another Param object
// Author: pdaehne
//----------------------------------------------------------------------
bool TextTXFParam::operator==(const TextTXFParam &other) const
{
    return (size == other.size) && (gap == other.gap) &&
           (textureWidth == other.textureWidth) && (_characters == other._characters);
}


//----------------------------------------------------------------------
// Sorts the characters in the character string and removes duplicates
// Author: pdaehne
//----------------------------------------------------------------------
void TextTXFParam::normalizeCharacters()
{
    sort(_characters.begin(),  _characters.end());
    wstring::iterator newEnd = unique(_characters.begin(),  _characters.end());
    _characters.erase(newEnd, _characters.end());
}


OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static OSG::Char8 cvsid_cpp[] = "@(#)$Id: OSGTextTXFParam.cpp,v 1.1.4.2 2006/05/08 06:01:15 vossg Exp $";
    static OSG::Char8 cvsid_hpp[] = OSGTEXTTXFPARAM_HEADER_CVSID;
    static OSG::Char8 cvsid_inl[] = OSGTEXTTXFPARAM_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
