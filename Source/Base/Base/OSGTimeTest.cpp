/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2006 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
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

#include <UnitTest++.h>

#include "OSGConfig.h"
#include "OSGTime.h"
#include <iostream>

using namespace UnitTest;

SUITE(TimeTests)
{

TEST(TestCallingAll)
{
   CHECK( OSG::getSystemTime() > 0.0);
   CHECK( OSG::getTimeStamp() > 0);
   OSG::Real64 ts_ms(OSG::getTimeStampMsecs(OSG::getTimeStamp()) );

   if (! (ts_ms>0.0))
   {  std::cout << "ts_ms: " << ts_ms << std::endl; }
   
   CHECK( ts_ms > 0.0);
}

TEST(CheckMSecs)
{
   //std::cout << "freq: " << OSG::getTimeStampFreq() << std::endl;
   //std::cout << std::setprecision(16) << std::fixed;
   //std::cout << "Time: " << OSG::getSystemTime() << std::endl;
   //std::cout << "TS: " << OSG::getTimeStamp() << std::endl;
   //std::cout << "Msecs: " << OSG::getTimeStampMsecs(OSG::getTimeStamp()) << std::endl;

   OSG::Real64 start_ms = OSG::getTimeStampMsecs(OSG::getTimeStamp());
   OSG::osgSleep(200);
   OSG::Real64 end_ms   = OSG::getTimeStampMsecs(OSG::getTimeStamp());
   OSG::Real64 ms_diff  = end_ms-start_ms;

   // Check that the time has changed a bit but not too much
   CHECK( (ms_diff > 100) && (ms_diff < 400));

   //std::cout << "Time: " << OSG::getSystemTime() << std::endl;
   //std::cout << "TS: " << OSG::getTimeStamp() << std::endl;
   //std::cout << "Msecs: " << OSG::getTimeStampMsecs(OSG::getTimeStamp()) << std::endl;
   //std::cout << "ms_diff: " << ms_diff << std::endl;
}

TEST(TimeStampMovesForward)
{
   // With some version of Linux, the assembly version of the timestamp code
   // used to have issues with going backward during context switches and the like
   OSG::UInt64 prev_ts(0);

   for (unsigned i=0; i<100; i++)
   {
      OSG::UInt64 cur_ts = OSG::getTimeStamp();
      //std::cout << " cur: " << cur_ts  << "  diff: " << (cur_ts-prev_ts) << std::endl;
      if (cur_ts < prev_ts)
      {
        std::cout << " cur: " << cur_ts  << "  diff: " << (cur_ts-prev_ts) << std::endl;
      }

      CHECK(cur_ts >= prev_ts);
      OSG::osgSleep(0);  // yield
      prev_ts = cur_ts;
   }

}

} // SUITE
