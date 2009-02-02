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
/* OSBRootElement                                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* State access                                                            */

inline OSBRootElement::BinaryReadHandler *
OSBRootElement::getReadHandler(void)
{
    return _readHandler;
}

inline OSBRootElement::BinaryWriteHandler *
OSBRootElement::getWriteHandler(void)
{
    return _writeHandler;
}

inline const NFIOOptions &
OSBRootElement::getOptions(void) const
{
    return _options;
}

inline NFIOOptions &
OSBRootElement::editOptions(void)
{
    return _options;
}

inline void
OSBRootElement::setHeaderVersion(const UInt16 version)
{
    _readHeaderVersion = version;
}

inline UInt16
OSBRootElement::getHeaderVersion(void) const
{
    return _readHeaderVersion;
}

inline const OSBRootElement::FieldContainerIdMap &
OSBRootElement::getIdMap(void) const
{
    return _readIdMap;
}

inline OSBRootElement::FieldContainerIdMap &
OSBRootElement::editIdMap(void)
{
    return _readIdMap;
}

inline const OSBRootElement::PtrFieldList &
OSBRootElement::getPtrFieldList(void) const
{
    return _readPtrFields;
}

inline OSBRootElement::PtrFieldList &
OSBRootElement::editPtrFieldList(void)
{
    return _readPtrFields;
}

inline const OSBRootElement::ElementList &
OSBRootElement::getElementList(void) const
{
    return _elements;
}

inline OSBRootElement::ElementList &
OSBRootElement::editElementList(void)
{
    return _elements;
}

inline const OSBRootElement::IdElemMap &
OSBRootElement::getIdElemMap(void) const
{
    return _idElemMap;
}

inline OSBRootElement::IdElemMap &
OSBRootElement::editIdElemMap(void)
{
    return _idElemMap;
}

inline const OSBRootElement::FieldContainerList &
OSBRootElement::getContainerList(void) const
{
    return _writeFCList;
}

inline OSBRootElement::FieldContainerList &
OSBRootElement::editContainerList(void)
{
    return _writeFCList;
}

inline const OSBRootElement::FieldContainerIdSet &
OSBRootElement::getIdSet(void) const
{
    return _writeIdSet;
}

inline OSBRootElement::FieldContainerIdSet &
OSBRootElement::editIdSet(void)
{
    return _writeIdSet;
}

OSG_END_NAMESPACE
