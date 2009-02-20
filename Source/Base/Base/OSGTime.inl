/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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


OSG_BEGIN_NAMESPACE

inline
OSG::Time getSystemTime (void)
{
    Time time;

#ifdef WIN32

    time = Time(timeGetTime()) / 1000.0;

#else

    struct timeval tv;
    gettimeofday(&tv, 0);
    time = Time(tv.tv_usec) / 1000000.0 + Time(tv.tv_sec);

#endif

    return time;
}


inline
OSG::TimeStamp getTimeStamp(void)
{
#ifdef WIN32

    Int64 iCounter;
    
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&iCounter));

    return  static_cast<TimeStamp>(iCounter);

/*  NOTE: Not reliable on multi-core processors
#elif defined(__linux) && (defined(__i386) || defined(__x86_64))

    register uint64_t result;
    //asm volatile ("rdtsc" : "=A"(result));
    // same thing as rdtsc... inject the bytes for the opcode.
    asm volatile (".byte 0x0f, 0x31" : "=A" (result)); 

    return static_cast<TimeStamp>(result);
*/
    
#else

    return static_cast<TimeStamp>(getSystemTime() * 1000000.f);

#endif
}


inline
OSG::TimeStamp getTimeStampFreq(void)
{
#ifdef WIN32

    Int64 iCounterFreq;
    
    QueryPerformanceFrequency(
        reinterpret_cast<LARGE_INTEGER *>(&iCounterFreq));

    return static_cast<TimeStamp>(iCounterFreq);
    
/*
#elif defined(__linux) && (defined(__i386) || defined(__x86_64))

    static Int64 iCounterFreq = 0;
    
    if(iCounterFreq == 0)
    {
        // Calibrate against gettimeofday

        Time start, end;
        Int64 cstart, cend;

        cstart = getTimeStamp();
        start = getSystemTime();

        osgSleep(200);

        cend = getTimeStamp();
        end = getSystemTime();

        iCounterFreq = static_cast<Int64>((cend - cstart) / (end - start));    
    }

    return static_cast<TimeStamp>(iCounterFreq);
*/
    
#else

    return static_cast<TimeStamp>(1000000);

#endif
}

inline
OSG::Real64 getTimeStampMsecs(OSG::TimeStamp ticks)
{
    return ticks * 1000. / getTimeStampFreq();
}

OSG_END_NAMESPACE
