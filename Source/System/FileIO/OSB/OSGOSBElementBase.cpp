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

#include "OSGOSBElementBase.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBElementBase::BinaryReadHandler                                       */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBElementBase::BinaryReadHandler
    Helper class for binary read operations.
 */

/*! \fn OSG::OSBElementBase::read(const std::string& typeName)
    Reads the object of type \a typeName and stores it as its container.

    \param[in] typeName Type of the object to read.
 */

/*! \fn OSG::OSBElementBase::postRead(void)
    Performs any post processing on the object read by this element. Usually
    this is used to perform conversions from older file formats and similar
    tasks.
 */

/*! \fn OSG::OSBElementBase::preWrite(FieldContainer * const fc)
    Examines the FieldContainer \a fc and creates elements for all containers
    referenced by any of its fields and calls preWrite for these elements.
    This recursively traverses the part of the scene that can be reached from
    the root and records the objects to be written.

    \param[in] fc The container this element is processing.
 */

/*! \fn OSG::OSBElementBase::write(void)
    Writes the container it is responsible for.
 */

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBElementBase::BinaryReadHandler::BinaryReadHandler(std::istream &inStream)
    : BinaryDataHandler(1       ),
      _readMemory      (8192    ),
      _is              (inStream)
{
    readBufAdd(&_readMemory[0], _readMemory.size());
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBElementBase::BinaryReadHandler::~BinaryReadHandler(void)
{
}

/*-------------------------------------------------------------------------*/
/* Read                                                                    */

/*! Reads \a size bytes from the underlying stream to the position indicated
    by \a mem.

    \param[in] mem Destination for read data.
    \param[in] size Number of bytes to read.
 */
void
OSBElementBase::BinaryReadHandler::read(MemoryHandle mem, UInt32 size)
{
    _is.read(reinterpret_cast<char *>(mem), size);
}

/*-------------------------------------------------------------------------*/
/* OSBElementBase::BinaryWriteHandler                                      */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBElementBase::BinaryWriteHandler
    Helper class for binary write operations.
 */

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBElementBase::BinaryWriteHandler::BinaryWriteHandler(std::ostream &outStream)
    : BinaryDataHandler(1        ),
      _writeMemory     (8192     ),
      _os              (outStream)
{
    writeBufAdd(&_writeMemory[0], _writeMemory.size());
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

/*! Destructor.
 */
OSBElementBase::BinaryWriteHandler::~BinaryWriteHandler(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Write                                                                   */

/*! Writes \a size bytes from the position indicated by \a mem to the
    underlying stream.

    \param[in] mem Data to write.
    \param[in] size Number of bytes to write.
 */
void
OSBElementBase::BinaryWriteHandler::write(MemoryHandle mem, UInt32 size)
{
    _os.write(reinterpret_cast<const char *>(mem), size);
}

/*-------------------------------------------------------------------------*/
/* OSBElementBase::PtrFieldInfo                                            */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBElementBase::PtrFieldInfo
    This holds information about a SField or MField that holds pointers to
    FieldContainers (or derived types).

    \dev
    It is needed while reading an OSB file, because containers pointed to from
    fields of the currently read container might not be loaded yet. To resolve
    this, for each such field an instance of this type is created and the
    container ids read from the file are stored therein. After the postRead
    processing is complete, this information is used to fill the pointer fields
    with the correct data.
    \enddev
 */

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

/*! Constructs an new PtrFieldInfo instance that describes the field with the
    given \a fieldId of the given FieldContainer \a fc.
 */
OSBElementBase::PtrFieldInfo::PtrFieldInfo(
    FieldContainer * const fc, UInt32 fieldId)
    : _fc           (fc     ),
      _fieldId      (fieldId),
      _ptrIds       (       ),
      _bindings     (       ),
      _bHandledField(false  )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

/*! Destructor.
 */
OSBElementBase::PtrFieldInfo::~PtrFieldInfo(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* OSBElementBase                                                          */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBElementBase
    The base class for all OSB IO "elements". An element is a type that
    provides the ability to read and write one or more OpenSG classes
    (especially FieldContainers).

    \dev
    This class holds a pointer to the OSG::OSBRootElement that holds the
    shared state for the IO operation and the FieldContainer this element
    is responsible for.
    To create your own element you probably want to derive from
    OSBCommonElement that provides functions that cover the typical steps
    necessary during IO.
    \enddev
 */

/*-------------------------------------------------------------------------*/
/* Constants                                                               */

const UInt16      OSBElementBase::OSGOSBHeaderVersion100 = 100;
const UInt16      OSBElementBase::OSGOSBHeaderVersion200 = 200;
// const UInt16      OSBElementBase::OSGOSBHeaderVersion201 = 201;

const std::string OSBElementBase::OSGOSB_HEADER_ID_1  ("OpenSG binary V1.0" );
const std::string OSBElementBase::OSGOSB_HEADER_ID_2  ("OpenSG binary V2.0" );
// const std::string OSBElementBase::OSGOSB_HEADER_ID_201("OpenSG binary V2.01");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBElementBase::OSBElementBase(OSBRootElement *root, const UInt16 version)
    : _container  (NULL   ),
      _rootElement(root   ),
      _fcIdFile   (0      ),
      _version    (version)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

/*! Destructor.
 */
OSBElementBase::~OSBElementBase(void)
{
    // nothing to do.
}
