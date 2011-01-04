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

#ifndef _OSGVOLUME_INL_
#define _OSGVOLUME_INL_

OSG_BEGIN_NAMESPACE

inline
Volume::~Volume(void)
{
}

/*-------------------------- state -----------------------------------------*/

/** set the volume to be static */

inline
void Volume::setStatic(const bool value)
{
    if(value == true)
        _state |= OSGSTATIC;
    else
        _state &= ~OSGSTATIC;
}

/**  Checks if the volume is static */

inline
bool Volume::isStatic(void) const
{
    return (_state & OSGSTATIC) ? true : false;
}

/*! set the volume to be valid */

inline
void Volume::setValid(const bool value)
{
    if(!isStatic())
    {
        if(value == true)
            _state |=  OSGVALID;
        else
            _state &= ~OSGVALID;
    }
}

/*!  Checks if the volume is valid */

inline
bool Volume::isValid(void) const
{
    return (_state & OSGVALID) ? true : false;
}

/*! set the volume to contain nothing */

inline
void Volume::setEmpty(const bool value)
{
    if(value == true)
    {
        _state |=  OSGEMPTY;
        _state |=  OSGVALID;
        _state &= ~OSGINFINITE;
    }
    else
    {
        _state &= ~OSGEMPTY;
    }
}

/*! Checks if the volume is empty */

inline
bool Volume::isEmpty(void) const
{
    return (_state & OSGEMPTY) ? true : false;
}

/** set the volume to be infinite */

inline
void Volume::setInfinite(const bool value)
{
    if(value == true)
    {
        _state |=  OSGINFINITE;
        _state |=  OSGVALID;
        _state &= ~OSGEMPTY;
    }
    else
    {
        _state &= ~OSGINFINITE;
    }
}

/**  Checks if the volume is infinite */

inline
bool Volume::isInfinite(void) const
{
    return (_state & OSGINFINITE) ? true : false;
}


/*! Checks if the volume is untouchable, i.e. it's values should not be 
    changed. Mainly used internally to speed up early outs in extendBy(). 
*/

inline
bool Volume::isUntouchable(void) const
{
    return (_state & (OSGINFINITE | OSGVALID | OSGSTATIC)) != OSGVALID;
}


/*! get the volume's state */

inline
UInt16 Volume::getState(void) const
{
    return _state;
}

/*! set the volume's state */

inline
void Volume::setState(UInt16 val)
{
    _state = val;
}

/*!  Return the lowest point of the volume. Just a convience wrapper for
     getBounds()
*/

inline
Pnt3f Volume::getMin(void) const
{
    Pnt3f pmin; 
    Pnt3f pmax;

    getBounds(pmin, pmax);

    return pmin;
}

/*!  Return the highest point of the volume. Just a convience wrapper for
     getBounds() 
*/

inline
Pnt3f Volume::getMax(void) const
{
    Pnt3f pmin;
    Pnt3f pmax;

    getBounds(pmin, pmax);

    return pmax;
}

inline
Volume::Volume(void) : 
    _state(OSGVALID | OSGEMPTY) 
{
}

inline
Volume::Volume(const Volume &obj) : 
    _state(obj._state) 
{
}

OSG_END_NAMESPACE

#endif // _OSGVOLUME_INL_
