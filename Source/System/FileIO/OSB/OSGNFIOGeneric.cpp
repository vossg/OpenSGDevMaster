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

#include <OSGConfig.h>

#include <string>

#include "OSGNFIOGeneric.h"
#include "OSGNFIOFactory.h"

#include <OSGLog.h>
#include <OSGGroup.h>
//#include <OSGSimpleAttachments.h>
#include <OSGChunkMaterial.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NFIOGeneric
           reads and writes a fieldcontainer.
 */

// Format
// <FieldContainerPtrType(UInt8)><version(UInt16)>
// <FieldName><FieldType><Size><FieldData>
// "" empty field name string as fieldcontainer endmarker
// ...

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt8 NFIOGeneric::FCPtrUnknown = 0;
const UInt8 NFIOGeneric::FCPtrFieldContainer = 1;
const UInt8 NFIOGeneric::FCPtrNode = 2;
const UInt8 NFIOGeneric::FCPtrNodeCore = 3;
const UInt8 NFIOGeneric::FCPtrAttachment = 4;
const UInt8 NFIOGeneric::FCPtrMaterial = 5;
const UInt8 NFIOGeneric::FCPtrStateChunk = 6;

NFIOGeneric NFIOGeneric::_the;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOGeneric::NFIOGeneric(void) :
    NFIOBase("")
{
    _version = 200;
}

/*------------------------------ destructor -------------------------------*/

NFIOGeneric::~NFIOGeneric(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                            Reader                                       *
\***************************************************************************/

FieldContainerPtr NFIOGeneric::readFC(const std::string &typeName)
{
    FDEBUG(("NFIOGeneric::readFCPtr\n"));

    UInt8 fcPtrType;
    _in->getValue(fcPtrType);
    _in->getValue(_version);
        
    FDEBUG(("NFIOGeneric::readFCPtr: got: '%s' %u\n", typeName.c_str(),
            _version));
    
    FieldContainerPtr fc = FieldContainerFactory::the()
                           ->createContainer(typeName.c_str());
    if(fc == NullFC)
    {
        FWARNING(("NFIOGeneric::readFCPtr: skipping unknown "
                  "field container '%s'.\n", typeName.c_str()));
        skipFCFields();
        
        // try to create a similar fieldcontainer to keep a working scenegraph.
        return createFCReplacement(fcPtrType);
    }
    
    readFCFields(fc);

    return fc;
}

/***************************************************************************\
 *                            Writer                                       *
\***************************************************************************/

void NFIOGeneric::writeFC(const FieldContainerPtr &fc)
{
    if(fc == NullFC)
    {
        FWARNING(("NFIOGeneric::writeFCPtr: fc == NullFC\n"));
        return;
    }
    
    FDEBUG(("NFIOGeneric::writeFCPtr: writeFCPtr: %s\n",
            fc->getType().getCName()));
    // write field container header.
    _out->putValue(getFCPtrType(fc));
    _out->putValue(_version);
    
    writeFCFields(fc);
}


UInt8 NFIOGeneric::getFCPtrType(const FieldContainerPtr &fc)
{
    FieldContainerType  &fcType = fc->getType();
    UInt8 type = NFIOGeneric::FCPtrFieldContainer;
    
    if(fcType.isNode())
        return NFIOGeneric::FCPtrNode;
    if(fcType.isNodeCore())
        return NFIOGeneric::FCPtrNodeCore;
    if(fcType.isDerivedFrom(Material::getClassType()))
        return NFIOGeneric::FCPtrMaterial;
    if(fcType.isDerivedFrom(StateChunk::getClassType()))
        return NFIOGeneric::FCPtrStateChunk;
    if(fcType.isAttachment())
        return NFIOGeneric::FCPtrAttachment;
    
    return type;
}

FieldContainerPtr NFIOGeneric::createFCReplacement(UInt8 fcPtrType)
{
    FieldContainerPtr fc = NullFC;
    switch(fcPtrType)
    {
        case NFIOGeneric::FCPtrNode:
            fc = Node::create();
        break;
        case NFIOGeneric::FCPtrNodeCore:
            fc = Group::create();
        break;
        case FCPtrMaterial:
            fc = ChunkMaterial::create();
        break;
        case FCPtrStateChunk:
            // do nothing.
        break;
        case NFIOGeneric::FCPtrAttachment:
            // do nothing.
        break;
        default:
            fc = Node::create();
        break;
    }
    return fc;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNFIOGeneric.cpp,v 1.1.2.2 2005/09/21 16:19:23 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGNFIOATEST_HEADER_CVSID;
}
