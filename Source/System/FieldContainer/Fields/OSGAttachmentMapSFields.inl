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

/*---------------------------------------------------------------------*/

inline
EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::EditSFieldHandle(
    const EditSFieldHandle &source) :

     Inherited (source            ),
    _pContainer(source._pContainer),
    _fAddMethod(source._fAddMethod)
{
}

inline
EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::EditSFieldHandle(      
          SFFieldContainerAttachmentPtrMap *pField, 
    const FieldDescriptionBase             *pDescription) :

     Inherited (pField, 
                pDescription),
    _pContainer(NULL        ),
    _fAddMethod(NULL        )
{
}

inline
const FieldType &
    EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::getType(void) const
{
    return SFFieldContainerAttachmentPtrMap::getClassType();
}

inline
bool EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::isPointerField(
    void) const
{
    return true;
}

inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::add(
    FieldContainerPtrConstArg rhs,
    UInt32                    uiBindings)
{
    FieldContainerAttachmentPtrConstArg pVal = 
        dynamic_cast<FieldContainerAttachmentPtrConstArg>(rhs);

    if(rhs != NULL && pVal == NULL)
        return;

    // for whatever reason VS2003 does not like == NULL
    if(_fAddMethod)
    {
        _fAddMethod(pVal, uiBindings);
    }
}

inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::equal(
    Inherited::Ptr rhs)
{
    Ptr pOther = boost::dynamic_pointer_cast<EditSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    SFFieldContainerAttachmentPtrMap *pLhs = 
        static_cast<SFFieldContainerAttachmentPtrMap *>(        _pField);

    SFFieldContainerAttachmentPtrMap *pRhs = 
        static_cast<SFFieldContainerAttachmentPtrMap *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::setAddMethod(
    AddMethod fMethod)
{
    _fAddMethod = fMethod;
}

inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::copyValues(
    GetFieldHandlePtr source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::shareValues(
    GetFieldHandlePtr source)
{
    OSG_ASSERT(false);
}


inline
void EditSFieldHandle<SFFieldContainerAttachmentPtrMap>::cloneValues(
          GetFieldHandlePtr  pSrc,
    const TypePtrVector     &shareTypes,
    const TypePtrVector     &ignoreTypes,
    const TypeIdVector      &shareGroupIds,
    const TypeIdVector      &ignoreGroupIds) const
{
    OSG_ASSERT(false);
}


OSG_END_NAMESPACE
