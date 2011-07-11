/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGOFControlRecords.h"

#include "OSGOFDatabase.h"
#include "OSGOpenFlightLog.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------
// OFPushLevelRecord
//---------------------------------------------------------------------

/* static */
OFRecordTransitPtr OFPushLevelRecord::create(const OFRecordHeader &oHeader,
                                                   OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFPushLevelRecord(oHeader, oDB));
}

/* virtual */
bool OFPushLevelRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFPushLevelRecord::read\n"));

    _oDB.pushLevel();

    return true;
}

/* virtual */
UInt16 OFPushLevelRecord::getOpCode(void) const
{
    return OpCode;
}

OFPushLevelRecord::OFPushLevelRecord(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB)
{
}

/* virtual */
OFPushLevelRecord::~OFPushLevelRecord(void)
{
}

/* static */
OFRecordFactoryBase::RegisterRecord OFPushLevelRecord::_regHelper(
    &OFPushLevelRecord::create,
    OFPushLevelRecord::OpCode  );

//---------------------------------------------------------------------
// OFPopLevelRecord
//---------------------------------------------------------------------

/* static */
OFRecordTransitPtr OFPopLevelRecord::create(const OFRecordHeader &oHeader,
                                                  OFDatabase     &oDB     )
{
    return OFRecordTransitPtr(new OFPopLevelRecord(oHeader, oDB));
}

/* virtual */
bool OFPopLevelRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFPopLevelRecord::read\n"));

    _oDB.popLevel();

    return true;
}

/* virtual */
UInt16 OFPopLevelRecord::getOpCode(void) const
{
    return OpCode;
}

OFPopLevelRecord::OFPopLevelRecord(const OFRecordHeader &oHeader,
                                         OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB)
{
}

/* virtual */
OFPopLevelRecord::~OFPopLevelRecord(void)
{
}

/* static */
OFRecordFactoryBase::RegisterRecord OFPopLevelRecord::_regHelper(
    &OFPopLevelRecord::create,
    OFPopLevelRecord::OpCode  );


OSG_END_NAMESPACE
