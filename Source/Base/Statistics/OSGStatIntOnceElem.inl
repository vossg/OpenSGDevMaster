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

OSG_BEGIN_NAMESPACE


inline 
void StatIntOnceElem::add(UInt32 contributorId, Int64 v)
{
    if(_ids.find(contributorId) == _ids.end())
    {
        _value += v;
        _ids.insert(contributorId);
    }
}

inline 
void StatIntOnceElem::sub(UInt32 contributorId, Int64 v)
{
    if(_ids.find(contributorId) == _ids.end())
    {
        _value -= v;
        _ids.insert(contributorId);
    }
}

inline 
void StatIntOnceElem::inc(UInt32 contributorId)
{
    if(_ids.find(contributorId) == _ids.end())
    {
        _value ++;
        _ids.insert(contributorId);
    }
}

inline 
void StatIntOnceElem::dec(UInt32 contributorId)
{
    if(_ids.find(contributorId) == _ids.end())
    {
        _value --;
        _ids.insert(contributorId);
    }
}

inline 
Int64 StatIntOnceElem::get() const
{
    return _value;
}


OSG_END_NAMESPACE
