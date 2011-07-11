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

#ifndef _OSGOFCONTROLRECORDS_H_
#define _OSGOFCONTROLRECORDS_H_

#include "OSGFileIODef.h"
#include "OSGOFRecords.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFPushLevelRecord : public OFControlRecord
{
  public:
    static const UInt16 OpCode = 10;

    /*---------------------------------------------------------------------*/

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     );

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

  protected:
    typedef OFControlRecord  Inherited;

             OFPushLevelRecord(const OFRecordHeader &oHeader,
                                     OFDatabase     &oDB     );
    virtual ~OFPushLevelRecord(void                          );

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFPopLevelRecord : public OFControlRecord
{
  public:
    static const UInt16 OpCode = 11;

    /*---------------------------------------------------------------------*/

    static OFRecordTransitPtr create(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     );

    /*---------------------------------------------------------------------*/

    virtual bool read(std::istream &is);

    /*---------------------------------------------------------------------*/

    virtual UInt16 getOpCode(void) const;

  protected:
    typedef OFControlRecord  Inherited;

             OFPopLevelRecord(const OFRecordHeader &oHeader,
                                    OFDatabase     &oDB     );
    virtual ~OFPopLevelRecord(void                          );

    /*---------------------------------------------------------------------*/

    static OFRecordFactoryBase::RegisterRecord _regHelper;
};

OSG_END_NAMESPACE

#endif /* _OSGOFCONTROLRECORDS_H_ */

