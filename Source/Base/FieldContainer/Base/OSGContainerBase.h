/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2002 by the OpenSG Forum                    *
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

#ifndef _OSGCONTAINERBASE_H_
#define _OSGCONTAINERBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainer
    \ingroup GrpBaseFieldContainerBase 
 */

namespace FieldBits
{
    const BitVector AllFields = OSGLL(0xFFFFFFFFFFFFFFFF);

    const BitVector NoField   = OSGLL(0x0000000000000000);


    const BitVector Field0    = OSGLL(0x0000000000000001);
    const BitVector Field1    = OSGLL(0x0000000000000002);
    const BitVector Field2    = OSGLL(0x0000000000000004);
    const BitVector Field3    = OSGLL(0x0000000000000008);

    const BitVector Field4    = OSGLL(0x0000000000000010);
    const BitVector Field5    = OSGLL(0x0000000000000020);
    const BitVector Field6    = OSGLL(0x0000000000000040);
    const BitVector Field7    = OSGLL(0x0000000000000080);

    const BitVector Field8    = OSGLL(0x0000000000000100);
    const BitVector Field9    = OSGLL(0x0000000000000200);
    const BitVector Field10   = OSGLL(0x0000000000000400);
    const BitVector Field11   = OSGLL(0x0000000000000800);

    const BitVector Field12   = OSGLL(0x0000000000001000);
    const BitVector Field13   = OSGLL(0x0000000000002000);
    const BitVector Field14   = OSGLL(0x0000000000004000);
    const BitVector Field15   = OSGLL(0x0000000000008000);

    const BitVector Field16   = OSGLL(0x0000000000010000);
    const BitVector Field17   = OSGLL(0x0000000000020000);
    const BitVector Field18   = OSGLL(0x0000000000040000);
    const BitVector Field19   = OSGLL(0x0000000000080000);

    const BitVector Field20   = OSGLL(0x0000000000100000);
    const BitVector Field21   = OSGLL(0x0000000000200000);
    const BitVector Field22   = OSGLL(0x0000000000400000);
    const BitVector Field23   = OSGLL(0x0000000000800000);

    const BitVector Field24   = OSGLL(0x0000000001000000);
    const BitVector Field25   = OSGLL(0x0000000002000000);
    const BitVector Field26   = OSGLL(0x0000000004000000);
    const BitVector Field27   = OSGLL(0x0000000008000000);

    const BitVector Field28   = OSGLL(0x0000000010000000);
    const BitVector Field29   = OSGLL(0x0000000020000000);
    const BitVector Field30   = OSGLL(0x0000000040000000);
    const BitVector Field31   = OSGLL(0x0000000080000000);
}

/*! \ingroup GrpBaseFieldContainer
    \ingroup GrpBaseFieldContainerBase 
 */

namespace ChangedOrigin
{
    const UInt32 External         = 0x0001;
    const UInt32 Sync             = 0x0002;
    const UInt32 Child            = 0x0004;
    const UInt32 Commit           = 0x0008;
}

/*! \ingroup GrpBaseFieldContainer
    \ingroup GrpBaseFieldContainerBase 
 */

namespace FCDumpFlags
{
    const BitVector RefCount   = 0x00000001;

    const BitVector AllAspects = 0x00000002;

    const BitVector All        = 0xFFFFFFFF;
}

/*! \ingroup GrpBaseFieldContainerBase 
 */

static const OSG::UInt16 InvalidParentEPos = 0xFFFF;

OSG_END_NAMESPACE

#endif /* _OSGCONTAINERBASE_H_ */

