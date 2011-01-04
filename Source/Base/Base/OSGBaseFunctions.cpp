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
    if(getenv("OSG_HOSTNAME") != NULL)
    {
        strncpy(szBuffer, getenv("OSG_HOSTNAME"), uiSize);
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


/*! \class string_token_iterator

    \brief Iterator over tokens in a std::string, separated by a specifiable
    set of separator characters.

    Provides an STL iterator like interface to access parts of a std::string.
    The individual parts are separated by at least one character from the set
    of separator characters.

    \note Based on code by Daniel Andersson
    from http://www.codeproject.com/string/stringsplitter.asp

    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn 
 */

/*! Default constructs a new iterator that has no string and no separators.
    This constructor exists only to make this type default constructible, but
    since there is no way to later set the string or the separators it's quite
    useless.
 */
string_token_iterator::string_token_iterator() : 
    _separator(0),
    _str      (0), 
    _start    (0), 
    _end      (0) 
{
}

/*! Creates a new iterator that operates on the string \a str and splits it
    at the separators given in the C string \a separator.

    \param[in] str String to iterator over.
    \param[in] separator Characters at which the string is split.

    \warning The strings \a str and \a separator are not copied, be sure not to
    delete them before you are done with this iterator.
 */
string_token_iterator::string_token_iterator(const std::string &str, 
                                             const char        *separator) :
    _separator( separator),
    _str      (&str      ),
    _start    ( 0        ),
    _end      ( 0        )
{
    find_next();
}

/*! Creates a new iterator with the internal state of \a rhs, i.e. the new
    iterator operates on the same string with the same separators as \a rhs and
    operator*() will return the same substring on its next call for both
    iterators.

    \param[in] rhs Iterator to copy.

    \warning The string and separator are not copied, be sure not to delete them
    before you are done with this iterator.
 */
string_token_iterator::string_token_iterator(
    const string_token_iterator & rhs) :

    _separator(rhs._separator),
    _str      (rhs._str      ),
    _start    (rhs._start    ),
    _end      (rhs._end      )
{
}

/*! Advances to the next token.

    \return The iterator after it was advanced.
 */
string_token_iterator & string_token_iterator::operator++()
{
    find_next();

    return *this;
}

/*! Advances to the next token and returns a copy of \c this from before it was
    advanced.

    \return A copy of this iterator before it was advanced.
 */
string_token_iterator string_token_iterator::operator++(int)
{
    string_token_iterator temp(*this);

    ++(*this);

    return temp;
}

/*! Returns the next token from the string or an empty string if there are no
    further tokens.

    \return Next token from the string.
 */
std::string string_token_iterator::operator*() const
{
    std::string returnValue;

    if(_end == std::string::npos)
    {
        returnValue = _str->substr(_start);
    }
    else
    {
        returnValue = _str->substr(_start, _end - _start);
    }

    return returnValue;
}

/*! Compares \c this to another string_token_iterator \a rhs for equality. They
    are considered equal if they operator on the same string and will return
    the same token on the next call to operator*().

    \param[in] rhs Iterator to compare \c this with.
    \return \c true if the iterators are equal, false otherwise.
 */
bool string_token_iterator::operator==(const string_token_iterator & rhs) const
{
    return (rhs._str == _str && rhs._start == _start && rhs._end == _end);
}

/*! Compares \c this to another string_token_iterator \a rhs for inequality.
    They are considered not equal, if a comparison for equality would return
    \c false.

    \param[in] rhs Iterator to compare \c this with.
    \return \c true if the iterators are not equal, false otherwise.
 */
bool string_token_iterator::operator!=(const string_token_iterator & rhs) const
{
    return !(rhs == *this);
}

/*! Advances the internal state to the next token.
 */
void string_token_iterator::find_next(void)
{
    _start = _str->find_first_not_of(_separator, _end);

    // Apparently some STL implementations don't do npos !?!
    if(_start == std::string::npos || _start >= _str->length())
    {
        _start = _end = 0;
        _str   = 0;
        return;
    }

    _end = _str->find_first_of(_separator, _start);
}

OSG_END_NAMESPACE
