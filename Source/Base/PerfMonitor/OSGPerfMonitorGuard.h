/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSG_PERF_MONITOR_GUARD_
#define _OSG_PERF_MONITOR_GUARD_

#include "OSGPerfMonitor.h"


OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBasePerfMon
 *  \nohierarchy
 * Helper class that uses the guard idiom to create and monitor performance.
 * To use, just create a PerfMonitorGuard with the name of the perf sample
 * point. It will automatically call enter on creation and exit on destruction.
 */
class PerfMonitorGuard
{
public:
    PerfMonitorGuard(const std::string& name, const std::string& desc = "")
        : mName(name)
        , mDesc(desc)
    {      
        PerfMonitor::the()->sample(OSG::PerfMonitorBase::ENTER, mName, 0.0,                                        mDesc);
     }
    ~PerfMonitorGuard()
    {
        PerfMonitor::the()->sample(OSG::PerfMonitorBase::EXIT, mName, 0.0,
                                   mDesc);
    }

    std::string mName;         /**< The name of the sample point. */
    std::string mDesc;
};

   
OSG_END_NAMESPACE

#endif
