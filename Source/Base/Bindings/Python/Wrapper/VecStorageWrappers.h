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

#ifndef _VEC_STORAGE_WRAPPERS_H_
#define _VEC_STORAGE_WRAPPERS_H_

#include <boost/python.hpp>
#include <OSGVector.h>


/**
 * @file
 *
 * Wrappers needed for vector base classes.
 */

namespace osgwrap
{

template<typename T>
boost::python::tuple
VecStorage2_getSeparateValues_tuple(OSG::VecStorage2<T>* vec)
{
   T v0, v1;
   vec->getSeparateValues(v0, v1);
   return boost::python::make_tuple(v0, v1);
}

template<typename T>
boost::python::tuple
VecStorage3_getSeparateValues_tuple(OSG::VecStorage3<T>* vec)
{
   T v0, v1, v2;
   vec->getSeparateValues(v0, v1, v2);
   return boost::python::make_tuple(v0, v1, v2);
}

template<typename T>
boost::python::tuple
VecStorage4_getSeparateValues_tuple(OSG::VecStorage4<T>* vec)
{
   T v0, v1, v2, v3;
   vec->getSeparateValues(v0, v1, v2, v3);
   return boost::python::make_tuple(v0, v1, v2, v3);
}

// Instantiations of the above functions.
#if defined(__GCCXML__)
template boost::python::tuple VecStorage2_getSeparateValues_tuple(OSG::VecStorage2<OSG::UInt8>*);
template boost::python::tuple VecStorage2_getSeparateValues_tuple(OSG::VecStorage2<OSG::Real32>*);
template boost::python::tuple VecStorage2_getSeparateValues_tuple(OSG::VecStorage2<OSG::Real64>*);
template boost::python::tuple VecStorage3_getSeparateValues_tuple(OSG::VecStorage3<OSG::UInt8>*);
template boost::python::tuple VecStorage3_getSeparateValues_tuple(OSG::VecStorage3<OSG::Real32>*);
template boost::python::tuple VecStorage3_getSeparateValues_tuple(OSG::VecStorage3<OSG::Real64>*);
template boost::python::tuple VecStorage4_getSeparateValues_tuple(OSG::VecStorage4<OSG::UInt8>*);
template boost::python::tuple VecStorage4_getSeparateValues_tuple(OSG::VecStorage4<OSG::Real32>*);
template boost::python::tuple VecStorage4_getSeparateValues_tuple(OSG::VecStorage4<OSG::Real64>*);
#endif

}


#endif /* _VEC_STORAGE_WRAPPERS_H_ */
