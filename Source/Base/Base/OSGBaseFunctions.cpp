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

#include "OSGConfig.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string.h>


#include <vector>

#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

/*! String tokenizer
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn 
    
    Based on code by Daniel Andersson
    from http://www.codeproject.com/string/stringsplitter.asp

    Useable to iterate over tokens in a std::string, separated by a specifiable
    set of separator characters.
 */

string_token_iterator::string_token_iterator() : 
    _separator(0),
    _str      (0), 
    _start    (0), 
    _end      (0) 
{
}
  
string_token_iterator::string_token_iterator(const std::string &str, 
                                             const char        *separator) :
    _separator( separator),
    _str      (&str      ),
    _start    ( 0        ),
    _end      ( 0        )
{
    find_next();
}
  
string_token_iterator::string_token_iterator(
    const string_token_iterator & rhs) :

    _separator(rhs._separator),
    _str      (rhs._str      ),
    _start    (rhs._start    ),
    _end      (rhs._end      )
{
}

string_token_iterator & string_token_iterator::operator++()
{
    find_next();

    return *this;
}

string_token_iterator string_token_iterator::operator++(int)
{
    string_token_iterator temp(*this);

    ++(*this);

    return temp;
}

std::string string_token_iterator::operator*() const
{
    return std::string(*_str, _start, _end - _start);
}

bool string_token_iterator::operator==(const string_token_iterator & rhs) const
{
    return (rhs._str == _str && rhs._start == _start && rhs._end == _end);
}

bool string_token_iterator::operator!=(const string_token_iterator & rhs) const
{
    return !(rhs == *this);
}

void string_token_iterator::find_next(void)
{
    _start = _str->find_first_not_of(_separator, _end);

    // Apparently some STL implementations don't do npos !?!
    if(_start == std::string::npos || _start >= _str->length())
    {
        _start = _end = 0;
        _str   = 0;
        return;
    }

    _end = _str->find_first_of(_separator, _start);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGBASEFUNCTIONS_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGBASEFUNCTIONS_INLINE_CVSID;
}
