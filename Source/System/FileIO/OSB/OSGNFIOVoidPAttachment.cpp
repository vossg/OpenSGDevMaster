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

#include "OSGConfig.h"
#include "OSGNFIOVoidPAttachment.h"
#include "OSGNFIOFactory.h"
#include "OSGNFIOGeneric.h"

#include "vector"

#include "OSGLog.h"
#include "OSGImageFileHandler.h"
#include "OSGNameAttachment.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NFIOVoidPAttachment
           reads and writes a image.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NFIOVoidPAttachment NFIOVoidPAttachment::_the;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOVoidPAttachment::NFIOVoidPAttachment(void) :
    NFIOBase("VoidPAttachment")
{
    _version = 200;
}

/*------------------------------ destructor -------------------------------*/

NFIOVoidPAttachment::~NFIOVoidPAttachment(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

FieldContainerPtr NFIOVoidPAttachment::readFC(const std::string &)
{
    FDEBUG(("NFIOVoidPAttachment::readFC\n"));

    UInt8 fcPtrType;
    _in->getValue(fcPtrType);

    UInt16 version = 0;
    _in->getValue(version);
    skipFCFields();

    return NullFC;
}

void NFIOVoidPAttachment::writeFC(const FieldContainerPtr &)
{
    FDEBUG(("NFIOVoidPAttachment::witeFC\n"));

    // just write a empty dummy out.
    _out->putValue(NFIOGeneric::FCPtrAttachment);
    _out->putValue(_version);

    writeEndMarker();
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGNFIOVOIDPATTACHMENT_HEADER_CVSID;
}
