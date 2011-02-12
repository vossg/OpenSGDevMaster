// PyOpenSG is (C) Copyright 2005-2009 by Allen Bierbaum
//
// This file is part of PyOpenSG.
//
// PyOpenSG is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// PyOpenSG is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

//#include "module/OSGBase_mainheader.h"
#include <OSGLine.h>
#include <OSGContainerPtrFuncs.h>
#include <boost/bind.hpp>
#include <boost/python.hpp>
#include "BaseWrappers.h"

namespace bp = boost::python;

namespace osgwrap
{

bool osgInitWrapper(bp::list pythonArgv)
{
   // Construct a vector of strings from the given list of Python strings.
   const unsigned int argc =
      bp::extract<unsigned int>(pythonArgv.attr("__len__")());
   std::vector<char*> argv(argc);

   for ( unsigned int i = 0; i < argc; ++i )
   {
      argv[i] = bp::extract<char*>(pythonArgv[i]);
   }

   return OSG::osgInit(argc, &argv[0]);
}

} // namespace osgwrap

// Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if defined(_WIN32)
# ifdef __MWERKS__
#  pragma ANSI_strict off
# endif
# include <windows.h>
# ifdef __MWERKS__
#  pragma ANSI_strict reset
# endif

# ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable:4297)
#  pragma warning(disable:4535)
extern "C" void straight_to_debugger(unsigned int, EXCEPTION_POINTERS*)
{
   throw;
}
extern "C" void (*old_translator)(unsigned, EXCEPTION_POINTERS*)
         = _set_se_translator(straight_to_debugger);
#  pragma warning(pop)
# endif

#endif // _WIN32
