/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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
const Char8 *IDString::str(void) const
{
    return _str; 
}

inline
bool IDString::isEmpty(void) const
{
    return (_str != NULL && *_str != '\0') ? false : true; 
}

inline
const IDString &IDString::operator =(const IDString &obj)
{
    set(obj._str);
    
    return *this;
}

inline
bool IDString::operator ==(const IDString &obj)   const
{
    return ((_str == obj._str) ? 
            1 : 
            (_str != NULL && obj._str != NULL && !::strcmp(_str, obj._str)));
}

inline 
bool IDString::operator !=(const IDString &obj)   const
{
    return ! (*this == obj);
}

inline 
bool IDString::operator <(const IDString &obj) const
{
    return (    _str != NULL && 
            obj._str != NULL && 
            (::strcmp(_str, obj._str) < 0));
}

inline 
bool IDString::operator >(const IDString &obj) const
{
        return ! (*this < obj) && ! (*this == obj);
}

inline
bool IDString::operator >=(const IDString &obj) const
{
    return ! (*this < obj);
}

inline
bool IDString::operator <=(const IDString &obj) const
{
    return (*this < obj) || (*this == obj);
}

OSG_END_NAMESPACE


