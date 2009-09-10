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

/*! \class MultiPool

MultiPool is a pool class that can handle multiple, different types of
elements. It is useful for managing a pool where it's not clear which of 
a variety of types might be used. Other than that it is very similar to
SimplePool.

A difference is that because it can handle multiple types, there is no
argument-less create(). create() needs to be called with a reference to an
instance of the class to create. (I'd love to use a type_info for this, but
that can't be used for creating instances. :( ). The best way to supply this
is a static instance, e.g. called Proto, that is accessible from the class
(see the OSGMultiPoolTest.cpp unit tests for an example). Make sure you don't
make the Proto const, or you won't be able to create non-const objects!

The stored types need to be derived from a common base class (which needs to
be used as the template argument of MultiPool). This base class needs to
have a default constructor, a virtual destructor and a virtual void reset();
method that is called when an instance is reused. reset() can be made private,
if MultiPool<>::TypeStore is made a friend.

*/

template<class ValueBaseT>
template<class ParameterT> inline
ParameterT *MultiPool<ValueBaseT>::create(ParameterT &oParam)
{
    TypesStoreIt el = _typesStore.find(typeid(ParameterT).name());
    
    if(el == _typesStore.end())
    {
        // New type
        _typesStore[typeid(ParameterT).name()] = 
                new TypeStore(sizeof(ParameterT));
        el = _typesStore.find(typeid(ParameterT).name());
    }
    
    return el->second->create(oParam);
}

template<class ValueBaseT>
void MultiPool<ValueBaseT>::freeAll(void)
{
    for(TypesStoreIt it = _typesStore.begin();
        it != _typesStore.end(); ++it)
    {
        it->second->freeAll();
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template<class ValueBaseT>
MultiPool<ValueBaseT>::MultiPool(void) :
    _typesStore()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template<class ValueBaseT>
MultiPool<ValueBaseT>::~MultiPool(void)
{
    for(TypesStoreIt it  = _typesStore.begin();
                     it != _typesStore.end(); 
                   ++it)
    {
        delete it->second;
    }
}


// MultiPool Helper class TypeStore
        
template<class ValueBaseT>
MultiPool<ValueBaseT>::TypeStore::TypeStore(int size) :
    _instSize(size),
    _currentFreeElement(0),
    _currentInitElement(0),
    _data()
{            
}

template<class ValueBaseT>
MultiPool<ValueBaseT>::TypeStore::~TypeStore()
{
    UInt32 ind = 0;

    for(std::vector<UInt8*>::iterator it = _data.begin();
        it != _data.end(); ++it)
    {
        UInt8 *p = *it;

        for(UInt32 i = 0; i < BLOCKSIZE && ind < _currentInitElement; 
            ++i, p += _instSize, ++ind)
        {
            reinterpret_cast<ValueBaseT *>(p)->~ValueBaseT();
        }

        delete [] *it;
    }
}

template<class ValueBaseT>
void MultiPool<ValueBaseT>::TypeStore::freeAll(void)
{
    _currentFreeElement = 0;
}

template<class ValueBaseT>
template<class ParameterT>
ParameterT *MultiPool<ValueBaseT>::TypeStore::create(ParameterT &oParam)
{
    OSG_ASSERT((sizeof(ParameterT) == _instSize));

    UInt32 bind = _currentFreeElement / BLOCKSIZE;
    UInt32 offset = (_currentFreeElement % BLOCKSIZE) * _instSize;    

    if(bind >= _data.size())
    {
        // Need new block
        _data.push_back(new UInt8 [BLOCKSIZE * _instSize]);
    }

    ParameterT *p = reinterpret_cast<ParameterT *>
                            (_data[bind] + offset);

    if(_currentFreeElement >= _currentInitElement)
    {
        // Construct
        new(p) ParameterT();
        ++_currentInitElement;
    }
    else
    {
        // Reset
        p->reset();
    }

    ++_currentFreeElement;
    return p;
}


OSG_END_NAMESPACE
