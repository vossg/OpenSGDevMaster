/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

template <class ValueT, 
          void (        *InitFunction )(ValueT *),
          void (ValueT::*ClearFunction)(void    )> inline
ValueT *Pool<ValueT, InitFunction, ClearFunction>::create(void)
{
    ValueT *returnValue = NULL;

    if(_currentFreeElement != _elementStore.end())
    {
        returnValue = *_currentFreeElement;

        ++_currentFreeElement;

        (returnValue->*ClearFunction)();

        ++_uiReused;
    }
    else
    {
        returnValue = new ValueT();

        InitFunction(returnValue);

        _elementStore.push_back(returnValue);

        _currentFreeElement = _elementStore.end();

        ++_uiAllocated;
    }
    
    return returnValue;
}

template <class ValueT, 
          void (        *InitFunction )(ValueT *),
          void (ValueT::*ClearFunction)(void    )> inline
void Pool<ValueT, InitFunction, ClearFunction>::freeAll(void)
{
    _currentFreeElement = _elementStore.begin();

    _uiAllocated = 0;
    _uiReused    = 0;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueT, 
          void (        *InitFunction )(ValueT *),
          void (ValueT::*ClearFunction)(void    )> inline
Pool<ValueT, InitFunction, ClearFunction>::Pool(void) :
    _elementStore      ( ),
    _currentFreeElement( ),
    _uiAllocated       (0),
    _uiReused          (0)
{
    _currentFreeElement = _elementStore.end();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueT, 
          void (        *InitFunction )(ValueT *),
          void (ValueT::*ClearFunction)(void    )> inline
Pool<ValueT, InitFunction, ClearFunction>::~Pool(void)
{
    for(UInt32 i = 0; i < _elementStore.size(); ++i)
    {
        delete _elementStore[i];
    }
}

template <class ValueT, 
          void (        *InitFunction )(ValueT *),
          void (ValueT::*ClearFunction)(void    )> inline
void Pool<ValueT, InitFunction, ClearFunction>::printStat(void)
{
    fprintf(stderr, "\n%d | %d | %d\n", 
            _uiAllocated, 
            _uiReused, 
            _elementStore.size());
}

OSG_END_NAMESPACE
