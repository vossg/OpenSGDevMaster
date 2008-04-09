/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

/*-------------------------------------------------------------------------*/
/* OSBElementBase::BinaryReadHandler                                       */
/*-------------------------------------------------------------------------*/

/*! Skips \a size bytes of data from the underlying stream.

    \param[in] size Number of bytes to skip.
 */
inline void
OSBElementBase::BinaryReadHandler::skip(UInt32 size)
{
    char dummy;

    for(UInt32 i = 0; i < size; ++i)
    {
        get(&dummy, 1);
    }
}

/*-------------------------------------------------------------------------*/
/* OSBElementBase                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* State access                                                            */

inline FieldContainerPtr
OSBElementBase::getContainer(void)
{
    return _container;
}

inline void
OSBElementBase::setContainer(const FieldContainerPtr cont)
{
    _container = cont;
}

inline const OSBRootElement *
OSBElementBase::getRoot(void) const
{
    return _rootElement;
}

inline OSBRootElement *
OSBElementBase::editRoot(void)
{
    return _rootElement;
}

inline UInt16
OSBElementBase::getVersion(void) const
{
    return _version;
}

/*-------------------------------------------------------------------------*/
/* OSBElementBase::PtrFieldInfo                                            */
/*-------------------------------------------------------------------------*/

inline FieldContainerPtr
OSBElementBase::PtrFieldInfo::getContainer(void) const
{
    return _fc;
}

inline UInt32
OSBElementBase::PtrFieldInfo::getFieldId(void) const
{
    return _fieldId;
}

inline const OSBElementBase::PtrFieldInfo::PtrIdStore &
OSBElementBase::PtrFieldInfo::getIdStore(void) const
{
    return _ptrIds;
}

inline OSBElementBase::PtrFieldInfo::PtrIdStore &
OSBElementBase::PtrFieldInfo::editIdStore(void)
{
    return _ptrIds;
}

inline OSBElementBase::PtrFieldInfo::PtrIdStoreConstIt
OSBElementBase::PtrFieldInfo::beginIdStore(void) const
{
    return _ptrIds.begin();
}

inline OSBElementBase::PtrFieldInfo::PtrIdStoreIt
OSBElementBase::PtrFieldInfo::beginIdStore(void)
{
    return _ptrIds.begin();
}

inline OSBElementBase::PtrFieldInfo::PtrIdStoreConstIt
OSBElementBase::PtrFieldInfo::endIdStore(void) const
{
    return _ptrIds.end();
}

inline OSBElementBase::PtrFieldInfo::PtrIdStoreIt
OSBElementBase::PtrFieldInfo::endIdStore(void)
{
    return _ptrIds.end();
}

inline const OSBElementBase::PtrFieldInfo::BindingStore &
OSBElementBase::PtrFieldInfo::getBindingStore(void) const
{
    return _bindings;
}

inline OSBElementBase::PtrFieldInfo::BindingStore &
OSBElementBase::PtrFieldInfo::editBindingStore(void)
{
    return _bindings;
}

inline OSBElementBase::PtrFieldInfo::BindingStoreConstIt
OSBElementBase::PtrFieldInfo::beginBindingStore(void) const
{
    return _bindings.begin();
}

inline OSBElementBase::PtrFieldInfo::BindingStoreIt
OSBElementBase::PtrFieldInfo::beginBindingStore(void)
{
    return _bindings.begin();
}

inline OSBElementBase::PtrFieldInfo::BindingStoreConstIt
OSBElementBase::PtrFieldInfo::endBindingStore(void) const
{
    return _bindings.end();
}

inline OSBElementBase::PtrFieldInfo::BindingStoreIt
OSBElementBase::PtrFieldInfo::endBindingStore(void)
{
    return _bindings.end();
}

OSG_END_NAMESPACE
