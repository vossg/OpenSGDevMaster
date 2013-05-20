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

template <class ValueT> inline
ValueT NamedPool<ValueT>::get(const Char8 *szName)
{
    ValueT returnValue = this->getInvalidValue();

    if(szName == NULL)
    {
        return returnValue;
    }

    std::string szKey(szName);

    ValueStoreIt mapIt = _elementStore.lower_bound(szKey);

    if(mapIt != _elementStore.end())
    {
        if(szKey == mapIt->first)
        {
            returnValue = mapIt->second;
        }
        else
        {
            returnValue = this->getNextValue();

            mapIt = _elementStore.insert(mapIt, 
                                         std::make_pair(szKey, returnValue));
        }
    }
    else
    {
        returnValue = this->getNextValue();


        mapIt = _elementStore.insert(mapIt, 
                                     std::make_pair(szKey, returnValue));

    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueT> inline
NamedPool<ValueT>::NamedPool(void) :
    _elementStore(),
    _currentValue()
{
    this->initCurrentValue();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueT> inline
NamedPool<ValueT>::~NamedPool(void)
{
}

template <class ValueT> inline
void NamedPool<ValueT>::printStat(void)
{
    fprintf(stderr, "\n%d\n", 
            _elementStore.size());
}

template <class ValueT> inline
void NamedPool<ValueT>::dump(void)
{
    ValueStoreConstIt eIt  = _elementStore.begin();
    ValueStoreConstIt eEnd = _elementStore.end  ();

    for(; eIt != eEnd; ++eIt)
    {
        fprintf(stderr, "[key/value] : %s / ", 
                eIt->first.c_str());

        this->dumpValue(eIt->second);

        fprintf(stderr, "\n");
    }
}

OSG_END_NAMESPACE

