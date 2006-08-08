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
#include "OSGNFIOGenericAtt.h"
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

/*! \class osg::NFIOGenericAtt
           reads and writes a image.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NFIOGenericAtt NFIOGenericAtt::_the;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOGenericAtt::NFIOGenericAtt(void) :
    NFIOBase("GenericAtt")
{
    _version = 200;
}

/*------------------------------ destructor -------------------------------*/

NFIOGenericAtt::~NFIOGenericAtt(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

FieldContainerPtr NFIOGenericAtt::readFC(const std::string &/*typeName*/)
{
    FDEBUG(("NFIOGenericAtt::readFC\n"));

    UInt8 fcPtrType;
    _in->getValue(fcPtrType);

    UInt16 version = 0;

    // with the old format we get fcPtrType and version number.
    // with the new format only the version number.
    if(fcPtrType == NFIOGeneric::FCPtrAttachment)
    {
        _in->getValue(version);
    }
    else
    {
        // The first byte is the most significant byte
        // of the 16 bit version number.
        version = (fcPtrType << 8);
        _in->getValue(fcPtrType);
        version |= fcPtrType;
    }

    skipFCFields();

    //NamePtr dummy = Name::create();
    // BUG dummy->editFieldPtr() returns a invalid pointer!
    //dummy->editFieldPtr()->getValue().assign("GenericAtt dummy");  

    return NullFC;
}

void NFIOGenericAtt::writeFC(const FieldContainerPtr &/*fc*/)
{
    FDEBUG(("NFIOGenericAtt::witeFC\n"));

    // GenericAtt is not yet supported so just write a empty dummy out.
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNFIOGenericAtt.cpp,v 1.1.2.4 2006/05/08 06:01:07 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGNFIOGENERICATT_HEADER_CVSID;
}
