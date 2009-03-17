/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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
GetSFieldHandle<SFChunkBlockPtrMap>::GetSFieldHandle(
    const GetSFieldHandle &source) :

    Inherited(source)
{
}

inline
GetSFieldHandle<SFChunkBlockPtrMap>::GetSFieldHandle(
    const SFChunkBlockPtrMap   *pField, 
    const FieldDescriptionBase *pDescription,
          FieldContainer       *pContainer  ) :

    Inherited(pField, pDescription, pContainer)
{
}

inline
bool GetSFieldHandle<SFChunkBlockPtrMap>::isPointerField(void) const
{
    return true;
}

inline
bool GetSFieldHandle<SFChunkBlockPtrMap>::empty(void)
{
    bool returnValue = true;

    SFChunkBlockPtrMap const *pLhs = 
        static_cast<SFChunkBlockPtrMap const *>(_pField);

    if(pLhs != NULL)
    {
        returnValue = pLhs->getValue().empty();
    }

    return returnValue;
}

inline
void GetSFieldHandle<SFChunkBlockPtrMap>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void GetSFieldHandle<SFChunkBlockPtrMap>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool GetSFieldHandle<SFChunkBlockPtrMap>::equal(Base::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<GetSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    SFChunkBlockPtrMap const *pLhs = 
        static_cast<SFChunkBlockPtrMap const *>(        _pField);

    SFChunkBlockPtrMap const *pRhs = 
        static_cast<SFChunkBlockPtrMap const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
SFChunkBlockPtrMap const *
    GetSFieldHandle<SFChunkBlockPtrMap>::operator ->(void)
{
    return static_cast<SFChunkBlockPtrMap const *>(_pField);
}

inline
SFChunkBlockPtrMap const &
    GetSFieldHandle<SFChunkBlockPtrMap>::operator * (void)
{
    return *(static_cast<SFChunkBlockPtrMap const *>(_pField));
}

/*---------------------------------------------------------------------*/

inline
EditSFieldHandle<SFChunkBlockPtrMap>::EditSFieldHandle(
    const EditSFieldHandle &source) :

     Inherited (source            ),
    _pContainer(source._pContainer),
    _fAddMethod(source._fAddMethod)
{
}

inline
EditSFieldHandle<SFChunkBlockPtrMap>::EditSFieldHandle(      
          SFChunkBlockPtrMap   *pField, 
    const FieldDescriptionBase *pDescription,
          FieldContainer       *pContainer  ) :

     Inherited (pField, 
                pDescription,
                pContainer  ),
    _pContainer(NULL        ),
    _fAddMethod(NULL        )
{
}


inline
bool EditSFieldHandle<SFChunkBlockPtrMap>::isPointerField(void) const
{
    return true;
}

inline
bool EditSFieldHandle<SFChunkBlockPtrMap>::empty(void)
{
    bool returnValue = true;

    SFChunkBlockPtrMap *pLhs = static_cast<SFChunkBlockPtrMap *>(_pField);

    if(pLhs != NULL)
    {
        returnValue = pLhs->getValue().empty();
    }

    return returnValue;
}

inline
void EditSFieldHandle<SFChunkBlockPtrMap>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFChunkBlockPtrMap>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool EditSFieldHandle<SFChunkBlockPtrMap>::equal(Base::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<EditSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    SFChunkBlockPtrMap *pLhs = 
        static_cast<SFChunkBlockPtrMap *>(        _pField);

    SFChunkBlockPtrMap *pRhs = 
        static_cast<SFChunkBlockPtrMap *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
void EditSFieldHandle<SFChunkBlockPtrMap>::setAddMethod(
    AddMethod fMethod)
{
    _fAddMethod = fMethod;
}

inline
void EditSFieldHandle<SFChunkBlockPtrMap>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFChunkBlockPtrMap>::copyValues(
    GetFieldHandlePtr source) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFChunkBlockPtrMap>::shareValues(
    GetFieldHandlePtr source) const
{
    SFChunkBlockPtrMap::GetHandlePtr pGetHandle = 
        boost::dynamic_pointer_cast<
            SFChunkBlockPtrMap::GetHandle>(source);

    if(pGetHandle == NULL || pGetHandle->isValid() == false)
        return;

    const SFChunkBlockPtrMap &pMatMap = **pGetHandle;

    ChunkBlockMap::const_iterator mapIt  = pMatMap.getValue().begin();
    ChunkBlockMap::const_iterator mapEnd = pMatMap.getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        ChunkBlock *att       = mapIt->second;
        KeyType     uiBinding = mapIt->first;

        if(_fAddMethod)
        {
            _fAddMethod(att, uiBinding);
        }
    }
}

OSG_END_NAMESPACE
