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

// This file contains code that has to appear *before* any Boost.Python code
// gets included. In other words, this has to be included before
// boost/python.hpp, and that means that it needs to be among the first
// headers included by osgmodule_mainheader.h.

#ifndef _OSG_MODULE_PRE_BOOST_PYTHON_H_
#define _OSG_MODULE_PRE_BOOST_PYTHON_H_

#include <boost/get_pointer.hpp>
#include <OSGConfig.h>
#include <OSGFieldContainer.h>
#include <OSGContainerRefCountPolicies.h>

/**
 * @file
 *
 * This file contains specializatoins of boost::get_pointer<T>() for OpenSG
 * smart pointer types. This must be included before any Boost.Python header
 * in order for these specializations to be known to the compiler by the time
 * that Boost.Python tries to use them.
 */

namespace boost
{

template<class ObjectType>
ObjectType*
get_pointer(const OSG::RefCountPtr<ObjectType, OSG::RecordedRefCountPolicy>& p)
{
   return p.get();
}

template<class ObjectType>
ObjectType*
get_pointer(OSG::RefCountPtr<ObjectType, OSG::RecordedRefCountPolicy>& p)
{
   return p.get();
}

template<class ObjectType>
ObjectType*
get_pointer(const OSG::RefCountPtr<ObjectType,
            OSG::UnrecordedRefCountPolicy>& p)
{
   return p.get();
}

template<class ObjectType>
ObjectType*
get_pointer(OSG::RefCountPtr<ObjectType, OSG::UnrecordedRefCountPolicy>& p)
{
   return p.get();
}

template<class ObjectType>
ObjectType*
get_pointer(const OSG::RefCountPtr<ObjectType, OSG::WeakRefCountPolicy>& p)
{
   return p.get();
}

template<class ObjectType>
ObjectType*
get_pointer(OSG::RefCountPtr<ObjectType, OSG::WeakRefCountPolicy>& p)
{
   return p.get();
}

}

#endif /* _OSG_MODULE_PRE_BOOST_PYTHON_H_ */
