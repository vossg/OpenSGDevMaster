/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

/*! \class PointerMFieldCommon

    Common interface implementation for pointer MFields. This class exists
    only to facilitate code reuse; to actually use the provided ptrStore
    interface use the derived classes ( \c ChildPointerMField,
    \c ParentPointerMField and \c PointerMField ).
    All non-const functions of this class call static member functions of the
    \c AccessHandlerT template parameter (onAdd, onSub, onReplace), whenever
    values are added, removed or replaced respectively. This is used to
    implement reference counting and child/parent linking.
 */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerMFieldCommon<AccessHandlerT,
                    NamespaceI    >::PointerMFieldCommon(void) : 
                        Inherited()
{
}

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerMFieldCommon<AccessHandlerT,
                    NamespaceI     >::PointerMFieldCommon(const Self &source) :
    Inherited()
{
    if(source.size() > 0)
    {
        _ptrStore.resize(source.size(), NULL);

        PtrStoreItType      sI = _ptrStore.begin();
        PtrStoreConstItType sE = _ptrStore.end  ();

        PtrStoreConstItType sSE = source._ptrStore.begin();

        for(; sI != sE; ++sI, ++sSE)
        {
            AccessHandler::onAdd(this, *sI);

            *sI = *sSE;
        }
    }
}

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerMFieldCommon<AccessHandlerT,
                    NamespaceI    >::PointerMFieldCommon(const UInt32 size) :
    Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class AccessHandlerT, Int32 NamespaceI> inline
PointerMFieldCommon<AccessHandlerT,
                    NamespaceI    >::~PointerMFieldCommon(void)
{
    Self::ptrStoreClear();
}

/*-------------------------------------------------------------------------*/
/* Store Interface                                                         */

/*! This interface fully handles reference counting and child/parent linking,
    but uses FieldContainerPtr instead of the real pointer type stored in the
    field.

    The biggest caveat with this interface is, when you attempt to use it
    with ParentPointerMField, as that will only give you the pointers,
    \em NOT the child field ids as well. To access those, use the
    functions of ParentPointerMFieldBase, that have a "idStore" instead of
    a "ptrStore" prefix.
 */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI    >::value_type
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreGet(const UInt32 index) const
{
    return AccessHandler::validate(_ptrStore[index]);
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI    >::value_type
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreGet(PtrStoreItType pos) const
{
    return AccessHandler::validate(*pos);
}

template <class AccessHandlerT, Int32 NamespaceI> inline
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI    >::value_type
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreGet(
                            PtrStoreConstItType pos) const
{
    return AccessHandler::validate(*pos);
}

/*-------------------------------------------------------------------------*/
/* Adding Values                                                           */

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::ptrStoreAppend(const_value pNewObj)
{
    AccessHandler::onAdd(this, pNewObj);

    _ptrStore.push_back(pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
template <class InputIteratorT                  > inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI     >::ptrStoreAssign(InputIteratorT first,
                                                          InputIteratorT last )
{
    PtrStoreItType sI = _ptrStore.begin();
    PtrStoreItType sE = _ptrStore.end  ();
    
    InputIteratorT iI = first;
    InputIteratorT iE = last;
    
    for(; (iI != iE) && (sI != sE); ++iI, ++sI)
    {
        AccessHandler::onReplace(this, *sI, *iI);

        *sI = *iI;
    }
    
    if(iI != iE)
    {
        for(; iI != iE; ++iI)
            this->ptrStoreAppend(*iI);
    }
    else if(sI != sE)
    {
        this->ptrStoreErase(sI, sE);
    }
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI     >::PtrStoreItType
     PointerMFieldCommon<AccessHandlerT,
                         NamespaceI     >::ptrStoreInsert(
                             PtrStoreItType pos, 
                             const_value     pNewObj)
{
    AccessHandler::onAdd(this, pNewObj);

    return _ptrStore.insert(pos, pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI> inline
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI     >::ptrStoreInsert(
                            PtrStoreItType pos,
                            size_type      n,
                            const_value    pNewObj)
{
    for(size_type i = 0; i < n; ++i)
        AccessHandler::onAdd(this, pNewObj);

    _ptrStore.insert(pos, n, pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI     >::ptrStoreInsert(
                             const UInt32      index, 
                                   const_value pNewObj)
{
    this->ptrStoreInsert(_ptrStore.begin() + index, pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
template <class InputIteratorT                  > inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::ptrStoreInsert(
                             PtrStoreItType pos, 
                             InputIteratorT first, 
                             InputIteratorT last)
{
    InputIteratorT iI = first;
    InputIteratorT iE = last;

    for(; iI != iE; ++iI)
        AccessHandler::onAdd(this, *iI);

    _ptrStore.insert(pos, first.base(), last.base());
}

/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::ptrStoreReplace(
                             PtrStoreItType pos, 
                             const_value    pNewObj)
{
    AccessHandler::onReplace(this, *pos, pNewObj);

    *pos = pNewObj;
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::ptrStoreReplace(
                             const UInt32      index, 
                                   const_value pNewObj)
{
    this->ptrStoreReplace(_ptrStore.begin() + index, pNewObj);
}

/*-------------------------------------------------------------------------*/
/* Removing Values                                                         */


template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI    >::PtrStoreItType
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreErase(PtrStoreItType pos)
{
    AccessHandler::onSub(this, *pos);

    return _ptrStore.erase(pos);
}


template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI    >::PtrStoreItType
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreErase(PtrStoreItType begin, 
                                                       PtrStoreItType end  )
{
    for(PtrStoreConstItType sI = begin; sI != end; ++sI)
        AccessHandler::onSub(this, *sI);

    return _ptrStore.erase(begin, end);
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreErase(const UInt32 index)
{
    this->ptrStoreErase(_ptrStore.begin() + index);
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::ptrStoreErase(
                             const UInt32 beginIndex, 
                             const UInt32 endIndex  )
{
    this->ptrStoreErase(_ptrStore.begin() + beginIndex,
                        _ptrStore.begin() + endIndex   );
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI     >::ptrStoreClear(void)
{
    PtrStoreConstItType sI = _ptrStore.begin();
    PtrStoreConstItType sE = _ptrStore.end  ();

    for(; sI != sE; ++sI)
        AccessHandler::onSub(this, *sI);

    _ptrStore.clear();
}

/*-------------------------------------------------------------------------*/
/* Resizing                                                                */

template <class AccessHandlerT, Int32 NamespaceI> inline
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::ptrStoreResize(
                             const UInt32      newSize, 
                                   const_value pNewObj)
{
    size_type oldSize = _ptrStore.size();

    if(newSize > oldSize)
    {
        _ptrStore.resize(newSize, pNewObj);

        PtrStoreConstItType sI = _ptrStore.begin() + oldSize;
        PtrStoreConstItType sE = _ptrStore.end  ();

        for(; sI != sE; ++sI)
            AccessHandler::onAdd(this, *sI);
    }
    else if(newSize < oldSize)
    {
        PtrStoreConstItType sI = _ptrStore.begin() + newSize;
        PtrStoreConstItType sE = _ptrStore.end  ();

        for(; sI != sE; ++sI)
            AccessHandler::onSub(this, *sI);

        _ptrStore.resize(newSize);
    }
}

/*-------------------------------------------------------------------------*/
/* Finding Values                                                          */


template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI    >::PtrStoreItType
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreFind(const_value pObj)
{
    return std::find(_ptrStore.begin(),
                     _ptrStore.end  (), pObj);
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
typename PointerMFieldCommon<AccessHandlerT,
                             NamespaceI    >::PtrStoreConstItType
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::ptrStoreFind(const_value pObj) const
{
    return std::find(_ptrStore.begin(),
                     _ptrStore.end  (), pObj);
}

/*-------------------------------------------------------------------------*/
/* Std library interface                                                   */

template <class AccessHandlerT, Int32 NamespaceI> inline 
FieldDescriptionBase *
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::createFieldDescription   (
                            const Char8                *szFieldname,
                                  UInt32                uiFieldFlags,
                                  FieldEditMethod       fEditMethod,
                                  FieldGetMethod        fGetMethod  )
{
    return NULL;
}

template <class AccessHandlerT, Int32 NamespaceI> inline 
FieldDescriptionBase *
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI    >::createIdxFieldDescription(
                            const Char8                *szFieldname,
                                  UInt32                uiFieldFlags,
                                  FieldIndexEditMethod  fEditMethod,
                                  FieldIndexGetMethod   fGetMethod  )
{
    return NULL;
}


/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */


template <class AccessHandlerT, Int32 NamespaceI> inline
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    UInt32 n;

    pMem.getValue(n);

    if(n != 0)
    {
        if(_ptrStore.size() == 0)
        {
            _ptrStore.resize(n, NULL);

            MFieldTraits::copyFromBin(   pMem, 
                                      &(_ptrStore[0]),
                                         n);
            
            PtrStoreConstItType sIt  = _ptrStore.begin();
            PtrStoreConstItType sEnd = _ptrStore.end  ();
            
            for(;sIt != sEnd; ++sIt)
                AccessHandler::onSyncAdd(this, *sIt);
        }
        else
        {
            if(n > _ptrStore.size())
            {
                _ptrStore.resize(n, NULL);
            }
            
            PtrStoreItType      sIt  = _ptrStore.begin();
            PtrStoreConstItType sEnd = _ptrStore.end  ();

            FieldContainer *tmpVal;

            for(UInt32 i = 0; i < n; ++i)
            {
                MFieldTraits::copyFromBin(pMem, 
                                          tmpVal);

                AccessHandler::onSyncReplace(this, *sIt, tmpVal);

                *sIt = tmpVal;
                
                ++sIt;
            }

            if(n < _ptrStore.size())
            {
                for(; sIt != sEnd; ++sIt)
                {
                    AccessHandler::onSyncSub(this, *sIt);
                };

                _ptrStore.resize(n);
            }
        }
    }
    else
    {
        Self::ptrStoreClear();
    }
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

/*! Syncronizes this field with a different Aspect.

    Two things need to be carefully handled here: First, depending on whether
    the size increases or decreases some values are replaced, added or removed
    and their reference count has to be adjusted accordingly.
    Second, the onSync{Add,Sub,Replace} functions of the AccessHandler have to
    be called.
 */

template <class AccessHandlerT, Int32 NamespaceI> inline
void PointerMFieldCommon<AccessHandlerT,
                         NamespaceI    >::syncWith(
                             Self              &source,     
                             ConstFieldMaskArg  syncMode,
                             UInt32             uiSyncInfo, 
                             AspectOffsetStore &oOffsets )
{
    size_type n = source.size();

    if(n != 0)
    {
        if(n > _ptrStore.size())
        {
            _ptrStore.resize(n, NULL);
        }

        PtrStoreConstItType sIt     = source._ptrStore.begin();
        PtrStoreConstItType sEnd    = source._ptrStore.end  ();

        PtrStoreItType      fIt     =        _ptrStore.begin();
        
        n = 0;
        for(; sIt != sEnd; ++sIt)
        {
            FieldContainer *pNewObj = convertToCurrentAspect(*sIt);
            
            if(pNewObj != NULL                                ||
               0x0000  == (syncMode & Field::MFNullCheckSync)  )
            {
                AccessHandler::onSyncReplace(this, *fIt, pNewObj);
            
                *fIt = pNewObj;

                ++fIt;
                ++n;
            }
        }
        
        if(n < _ptrStore.size())
        {
            PtrStoreConstItType fEnd  = _ptrStore.end();
            
            for(; fIt != fEnd; ++fIt)
                AccessHandler::onSyncSub(this, *fIt);

            _ptrStore.resize(n);
        }
    }
    else
    {
        this->ptrStoreClear();
    }
}

OSG_END_NAMESPACE
