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
GetSFieldHandle<SFMaterialPtrMap>::GetSFieldHandle(
    const GetSFieldHandle &source) :

    Inherited(source)
{
}

inline
GetSFieldHandle<SFMaterialPtrMap>::GetSFieldHandle(
    const SFMaterialPtrMap     *pField, 
    const FieldDescriptionBase *pDescription,
          FieldContainer       *pContainer  ) :

    Inherited(pField, pDescription, pContainer)
{
}

inline
bool 
   GetSFieldHandle<SFMaterialPtrMap>::isPointerField(void) const
{
    return true;
}

inline
bool GetSFieldHandle<SFMaterialPtrMap>::empty(void)
{
    bool returnValue = true;

    SFMaterialPtrMap const *pLhs = 
        static_cast<SFMaterialPtrMap const *>(_pField);

    if(pLhs != NULL)
    {
        returnValue = pLhs->getValue().empty();
    }

    return returnValue;
}

inline
void GetSFieldHandle<SFMaterialPtrMap>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void GetSFieldHandle<SFMaterialPtrMap>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool GetSFieldHandle<SFMaterialPtrMap>::equal(
    Base::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<GetSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    SFMaterialPtrMap const *pLhs = 
        static_cast<SFMaterialPtrMap const *>(        _pField);

    SFMaterialPtrMap const *pRhs = 
        static_cast<SFMaterialPtrMap const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
SFMaterialPtrMap const *
    GetSFieldHandle<SFMaterialPtrMap>::operator ->(void)
{
    return static_cast<SFMaterialPtrMap const *>(_pField);
}

inline
SFMaterialPtrMap const &
    GetSFieldHandle<SFMaterialPtrMap>::operator * (void)
{
    return *(static_cast<SFMaterialPtrMap const *>(_pField));
}

/*---------------------------------------------------------------------*/

inline
EditSFieldHandle<SFMaterialPtrMap>::EditSFieldHandle(
    const EditSFieldHandle &source) :

     Inherited (source            ),
    _pContainer(source._pContainer),
    _fAddMethod(source._fAddMethod)
{
}

inline
EditSFieldHandle<SFMaterialPtrMap>::EditSFieldHandle(      
          SFMaterialPtrMap     *pField, 
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
bool EditSFieldHandle<SFMaterialPtrMap>::isPointerField(void) const
{
    return true;
}

inline
bool EditSFieldHandle<SFMaterialPtrMap>::empty(void)
{
    bool returnValue = true;

    SFMaterialPtrMap *pLhs = static_cast<SFMaterialPtrMap *>(_pField);

    if(pLhs != NULL)
    {
        returnValue = pLhs->getValue().empty();
    }

    return returnValue;
}

inline
void EditSFieldHandle<SFMaterialPtrMap>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFMaterialPtrMap>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool EditSFieldHandle<SFMaterialPtrMap>::equal(
    Base::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<EditSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    SFMaterialPtrMap *pLhs = 
        static_cast<SFMaterialPtrMap *>(        _pField);

    SFMaterialPtrMap *pRhs = 
        static_cast<SFMaterialPtrMap *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
void EditSFieldHandle<SFMaterialPtrMap>::setAddMethod(
    AddMethod fMethod)
{
    _fAddMethod = fMethod;
}

inline
void EditSFieldHandle<SFMaterialPtrMap>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFMaterialPtrMap>::copyValues(
    GetFieldHandlePtr source) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFMaterialPtrMap>::shareValues(
    GetFieldHandlePtr source) const
{
    SFMaterialPtrMap::GetHandlePtr pGetHandle = 
        boost::dynamic_pointer_cast<
            SFMaterialPtrMap::GetHandle>(source);

    if(pGetHandle == NULL || pGetHandle->isValid() == false)
        return;

    const SFMaterialPtrMap &pMatMap = **pGetHandle;

    MaterialMap::const_iterator mapIt  = pMatMap.getValue().begin();
    MaterialMap::const_iterator mapEnd = pMatMap.getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        PrimeMaterial *att       = mapIt->second;
        KeyType        uiBinding = mapIt->first;

        if(_fAddMethod)
        {
            _fAddMethod(att, uiBinding);
        }
    }
}

OSG_END_NAMESPACE
