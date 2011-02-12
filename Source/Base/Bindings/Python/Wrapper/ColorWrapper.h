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

#include <boost/python.hpp>
#include <OSGColor.h>

/**
 * @file
 *
 * Wrappers needed for color classes.
 */

namespace
{

template<typename T>
boost::python::tuple Color3_getValuesRGB_tuple(OSG::Color3<T>* color)
{
   typename OSG::Color3<T>::ValueType r, g, b;
   color->getValuesRGB(r, g, b);
   return boost::python::make_tuple(r, g, b);
}

template<typename T>
boost::python::tuple Color4_getValuesRGBA_tuple(OSG::Color4<T>* color)
{
   typename OSG::Color4<T>::ValueType r, g, b, a;
   color->getValuesRGBA(r, g, b, a);
   return boost::python::make_tuple(r, g, b, a);
}

template<typename T>
boost::python::tuple Color_getValuesHSV(T* color)
{
   OSG::Real32 h, s, v;
   color->getValuesHSV(h, s, v);
   return boost::python::make_tuple(h, s, v);
}

// Instantiations of the above functions.
template boost::python::tuple Color3_getValuesRGB_tuple(OSG::Color3<OSG::Real32>*);
template boost::python::tuple Color3_getValuesRGB_tuple(OSG::Color3<OSG::UInt8>*);
template boost::python::tuple Color_getValuesHSV(OSG::Color3<OSG::Real32>*);
template boost::python::tuple Color_getValuesHSV(OSG::Color3<OSG::UInt8>*);

template boost::python::tuple Color4_getValuesRGBA_tuple(OSG::Color4<OSG::Real32>*);
template boost::python::tuple Color4_getValuesRGBA_tuple(OSG::Color4<OSG::UInt8>*);
template boost::python::tuple Color_getValuesHSV(OSG::Color4<OSG::Real32>*);
template boost::python::tuple Color_getValuesHSV(OSG::Color4<OSG::UInt8>*);

}
