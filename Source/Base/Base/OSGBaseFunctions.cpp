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

#include "OSGConfig.h"

#include <string>
#include <vector>

#include "OSGBaseFunctions.h"
#include "OSGGLU.h"

#include <boost/filesystem/operations.hpp>

// XXX: Hack for right now, just assume we have it
#if defined(__linux) && defined(__GNUC__) 
#define HAVE_BACKTRACE
#endif

#if defined(HAVE_BACKTRACE)
#  include <sys/types.h>
#  include <unistd.h>
#  include <execinfo.h>
#  include <sstream>
#endif

#if (! defined(__INTEL_COMPILER) && defined(__GNUC__) && \
     ((__GNUC__ == 3 && __GNUC_MINOR__ >= 3) || __GNUC__ > 3)) || \
    (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 810 && defined(__GNUC__))

#define USE_CXA_DEMANGLE 1
#include <cxxabi.h>

#endif

namespace
{
std::string demangleTraceString(char* traceLine)
{
#ifdef USE_CXA_DEMANGLE
   // Try to extract the mangled name from the line (if it exists)
   // and replace it with a demangled version of the name.
   // Example: build.linux/stuff/classfile(_ZN4vpr11Someing33methodEv+0xd3) [0x80cfa29]

   std::string trace_line(traceLine);
   std::string mangled_name, demangled_name;

   std::string::size_type start(std::string::npos), end(std::string::npos);
   start = trace_line.find("(_");
   if(std::string::npos != start)
   {
      end = trace_line.find_first_of("+)",start);
   }

   if(std::string::npos != end)
   {
      mangled_name.assign(trace_line, start+1, end-start-1);
      int status;
      char* demangled_buf = abi::__cxa_demangle(mangled_name.c_str(), NULL,
                                                NULL, &status);
      if(0==status)
      {
         demangled_name = std::string(demangled_buf);
         free(demangled_buf);

         trace_line.replace(start+1, (end-start-1), demangled_name);
      }
      else if(-1==status)
      {
//         std::cerr << "vpr::SystemBase::dmangleTraceString: "
//                   << "A memory allocation failiure occurred.\n";
      }
      else if(-2 == status)
      {
//         std::cerr << "vpr::SystemBase::demangleTraceString: mangled_name "
//                   << "is not a valid name under the C++ ABI mangling '
//                   << "rules.\n";
      }
      else if(-3 == status)
      {
//         std::cerr << "vpr::SystemBase::demangleTraceString: One of the "
//                   << "arguments is invalid.\n";
      }
   }

//   trace_line += std::string(" mangle:") + mangled_name +
//                 std::string(" demangled:") + demangled_name;
   return trace_line;

#else
   return std::string(traceLine);
#endif
}

}


OSG_BEGIN_NAMESPACE

OSG_BASE_DLLMAPPING GLErrorFunctor GLErrorCallback;

void osgGetHostname(char *szBuffer, UInt32 uiSize)
{
    // get local host name
    if(getenv(OSG_NAMESPACE_PREFIX"_HOSTNAME") != NULL)
    {
        strncpy(szBuffer, getenv(OSG_NAMESPACE_PREFIX"_HOSTNAME"), uiSize);
    }
    else
    {
        gethostname(szBuffer, uiSize);
    }
}

/** Return the callstack at the current point. 
 * See vrjuggler: juggler/modules/vapor/vpr/SystemBase.cpp for complete impl
 * details 
 */

std::string getCallStack()
{
   std::string ret_stack(
       "Stack trace:\n   <Call stack printing not supported>\n");

#if defined(HAVE_BACKTRACE)
   void*  trace_syms[1000];
   size_t size;
   char** strings;

   pid_t cur_pid = getpid();
   size = backtrace(trace_syms, 100);
   strings = backtrace_symbols(trace_syms, size);

   std::ostringstream trace_stream;
   trace_stream << "Stack trace: thread: " << cur_pid << std::endl;

   for (size_t i = 0; i < size; ++i)
   {
      trace_stream << "   " << i << ":" << demangleTraceString(strings[i])
                   << std::endl;
   }

   free(strings);

   ret_stack = trace_stream.str();
#endif

   return ret_stack;
}

/*---------------------------------------------------------------------*/
/* BoostPath Utils, merged from OpenSGToolbox,  Author: David Kabala   */

BoostPath makeRelative(const BoostPath &oRoot, const BoostPath &oToPath)
{
    BoostPath oRootComplete   = boost::filesystem::system_complete(oRoot  );
    BoostPath oToPathComplete = boost::filesystem::system_complete(oToPath);

    BoostPath oResult;

    boost::filesystem::path::iterator rootIt   = oRootComplete  .begin();
    boost::filesystem::path::iterator toPathIt = oToPathComplete.begin();

    while(rootIt   != oRootComplete  .end()                        &&
          toPathIt != oToPathComplete.end()                        &&
          0        == rootIt->string().compare(toPathIt->string())  )
    {
        ++rootIt;
        ++toPathIt;
    }

    while(toPathIt != oToPathComplete.end())
    {
        if(oResult.empty())
        {
            oResult = *toPathIt;
        }
        else
        {
            oResult = oResult / *toPathIt;
        }

        ++toPathIt;
    }

    if(rootIt != oRootComplete.end())
    {
        ++rootIt;
    }

    while(rootIt != oRootComplete.end())
    {
        oResult = BoostPath("..") / oResult;

        ++rootIt;
    }

    return oResult;
} 

OSG_END_NAMESPACE
