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


template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class     LockPolicy> inline
NamedSplitFinitePool<ValueT, 
                     SplitInfo, 
                     PoolTag,
                     LockPolicy>::NamedSplitFinitePool(void) :

    _oLockPolicy    ( ),
    _oDefaultElement( ),
    _vElementStore1 ( ),
    _vElementStore2 ( ),
    _mNameValueMap  ( ),
    _mValueNameMap  ( )
{
    initialize();
}

template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class    LockPolicy> inline
NamedSplitFinitePool<ValueT, 
                     SplitInfo, 
                     PoolTag, 
                     LockPolicy>::~NamedSplitFinitePool(void)
{
    
}

template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class    LockPolicy> inline
typename NamedSplitFinitePool<ValueT, 
                              SplitInfo, 
                              PoolTag, 
                              LockPolicy>::StoredType
    NamedSplitFinitePool<ValueT, 
                         SplitInfo, 
                         PoolTag, 
                         LockPolicy>::getFrom1(const Char8 *szName)
{
    StoredType returnValue = _oDefaultElement;

    if(szName == NULL || szName[0] == '\0')
    {
        return returnValue;

    }

    _oLockPolicy.acquire();

    NameValueMapIt mIt = _mNameValueMap.find(szName);

    if(mIt == _mNameValueMap.end())
    {
        if(_vElementStore1.empty() == false)
        {
            returnValue = _vElementStore1.back();
            
            _vElementStore1.pop_back();

            _mNameValueMap[szName     ] = returnValue;
            _mValueNameMap[returnValue] = szName;
        }
    }
    else
    {
        returnValue = mIt->second;
    }

    _oLockPolicy.release();

    return returnValue;
}

template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class    LockPolicy> inline
typename NamedSplitFinitePool<ValueT, 
                              SplitInfo, 
                              PoolTag, 
                              LockPolicy>::StoredType
    NamedSplitFinitePool<ValueT, 
                         SplitInfo, 
                         PoolTag, 
                         LockPolicy>::getFrom2(const Char8 *szName)
{
    StoredType returnValue = _oDefaultElement;

    if(szName == NULL || szName[0] == '\0')
    {
        return returnValue;

    }

    _oLockPolicy.acquire();

    NameValueMapIt mIt = _mNameValueMap.find(szName);

    if(mIt == _mNameValueMap.end())
    {
        if(_vElementStore2.empty() == false)
        {
            returnValue = _vElementStore2.back();
            
            _vElementStore2.pop_back();

            _mNameValueMap[szName     ] = returnValue;
            _mValueNameMap[returnValue] = szName;
        }
    }
    else
    {
        returnValue = mIt->second;
    }

    _oLockPolicy.release();

    return returnValue;
}

template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class    LockPolicy> inline
typename NamedSplitFinitePool<ValueT, 
                              SplitInfo, 
                              PoolTag, 
                              LockPolicy>::StoredType
    NamedSplitFinitePool<ValueT, 
                         SplitInfo, 
                         PoolTag, 
                         LockPolicy>::getAuto(const Char8 *szName)
{
    StoredType returnValue = _oDefaultElement;

    if(szName == NULL || szName[0] == '\0')
    {
        return returnValue;

    }
    _oLockPolicy.acquire();

    ValueStore *pActiveStore = &_vElementStore1;

    std::string tmpName(szName);

    std::string::iterator nIt = tmpName.end();

    --nIt;

    if(*nIt == '@')
    {
        *nIt = '\0';
    }
    else if(*nIt == '$')
    {
        pActiveStore = &_vElementStore2;
        *nIt = '\0';
    }

    NameValueMapIt mIt = _mNameValueMap.find(tmpName);

    if(mIt == _mNameValueMap.end())
    {
        if(pActiveStore->empty() == false)
        {
            returnValue = pActiveStore->back();
            
            pActiveStore->pop_back();

            _mNameValueMap[tmpName    ] = returnValue;
            _mValueNameMap[returnValue] = tmpName;
        }
    }
    else
    {
        returnValue = mIt->second;
    }

    _oLockPolicy.release();

    return returnValue;
}

template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class    LockPolicy> inline
const Char8 *NamedSplitFinitePool<ValueT, 
                                  SplitInfo,
                                  PoolTag, 
                                  LockPolicy>::findName(const StoredType &val) 
{
    const Char8 *returnValue = NULL;

    _oLockPolicy.acquire();

    ValueNameMapIt mIt = _mValueNameMap.find(val);

    if(mIt != _mValueNameMap.end())
    {
        returnValue = mIt->second.c_str();
    }

    _oLockPolicy.release();

    return returnValue;
}

template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class    LockPolicy> inline
typename NamedSplitFinitePool<ValueT, 
                              SplitInfo, 
                              PoolTag, 
                              LockPolicy>::StoredType 
    NamedSplitFinitePool<ValueT, 
                         SplitInfo, 
                         PoolTag, 
                         LockPolicy>::getDefault(void) const
{
    return _oDefaultElement;
}

template <class    ValueT, 
          typename SplitInfo, 
          class    PoolTag, 
          class    LockPolicy> inline
void NamedSplitFinitePool<ValueT, 
                         SplitInfo, 
                         PoolTag, 
                         LockPolicy>::dump(void)
{
    fprintf(stderr, "split  \n");
    fprintf(stderr, "=======\n");

    SplitInfo::dump();

    fprintf(stderr, "store 1\n");
    fprintf(stderr, "=======\n");

    ValueNameMapConstIt vnIt  = _mValueNameMap.begin();
    ValueNameMapConstIt vnEnd = _mValueNameMap.end  ();

    for(; vnIt != vnEnd; ++vnIt)
    {
        if(0x0000 != (vnIt->first & SplitInfo::SplitMask::Lower))
        {
            fprintf(stderr, "[key/value] : %s / ",
                    vnIt->second.c_str());
            
            this->dumpValue(vnIt->first);
            
            fprintf(stderr, "\n");
        }
    }


    fprintf(stderr, "store 2\n");
    fprintf(stderr, "=======\n");

    vnIt  = _mValueNameMap.begin();
    vnEnd = _mValueNameMap.end  ();

    for(; vnIt != vnEnd; ++vnIt)
    {
        if(0x0000 != (vnIt->first & SplitInfo::SplitMask::Upper))
        {
            fprintf(stderr, "[key/value] : %s / ",
                    vnIt->second.c_str());
            
            this->dumpValue(vnIt->first);
            
            fprintf(stderr, "\n");
        }
    }
}

OSG_END_NAMESPACE


