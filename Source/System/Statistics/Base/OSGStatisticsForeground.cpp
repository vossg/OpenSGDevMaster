/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGStatisticsForeground.h"

OSG_USING_NAMESPACE

/*! \class OSG::StatisticsForeground
    \ingroup GrpSystemWindowForegrounds
    
StatisticsForeground is the base class for all foregrounds that process
statistics.  See \ref
PageSystemWindowForegroundStatistics for a description.

The elements to display are selected using the _mfElementIDs Field. The
collector to use is stored in the _sfCollector Field.
*/

/*----------------------- constructors & destructors ----------------------*/

StatisticsForeground::StatisticsForeground(void) :
    Inherited()
{
}

StatisticsForeground::StatisticsForeground(const StatisticsForeground &source) :
    Inherited(source)
{
}

StatisticsForeground::~StatisticsForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StatisticsForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void StatisticsForeground::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void StatisticsForeground::dump(      UInt32    , 
                                const BitVector ) const
{
    SLOG << "Dump StatisticsForeground NI" << std::endl;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGStatisticsForeground.cpp,v 1.1.2.1 2006/04/21 02:27:50 vossg Exp $";
    static char cvsid_hpp[] = OSGSTATISTICSFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGSTATISTICSFOREGROUND_INLINE_CVSID;
}
