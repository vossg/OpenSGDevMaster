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

#ifndef _PYOPENSG_ALIASES_H_
#define _PYOPENSG_ALIASES_H_

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <OSGBaseTypes.h>
#include <OSGContainerForwards.h>
#include <OSGPerfMonitor.h>

/**
 * @file
 *
 * List of aliases to use with Py++. These make smaller, more friendly file
 * names and type names.
 */

OSG_BEGIN_NAMESPACE

class GeoPumpGroup;
class Light;
class GeoIntegralProperty;

OSG_END_NAMESPACE

namespace pyplusplus
{

namespace aliases
{
   typedef std::vector<std::string> string_vector_t;

   typedef std::vector<OSG::GeoPumpGroup*> geo_pump_group_vector_t;
   typedef std::vector<OSG::Light*> light_vector_t;
   typedef std::vector<unsigned short> ushort_vector_t;
   typedef std::vector<bool> bool_vector_t;
   typedef std::vector<int> int_vector_t;
   typedef std::map<unsigned int, unsigned int> uint_uint_map_t;

   typedef std::vector<OSG::NestedSampleInfoPtr> sample_stack_t;
   typedef std::vector<float> float_vector_t;
   typedef std::vector<OSG::NestedPerfTracker::SamplePair> sample_pair_vector_t;

   typedef std::vector<std::pair<OSG::GeoIntegralProperty*, std::vector<OSG::UInt16> > > index_bag_t;
   typedef std::vector<OSG::RenderFunctor> render_functor_vector_t;
   typedef std::vector<std::pair<OSG::UInt32, OSG::UInt32> > uint_uint_vector_t;
}

}


#endif /* _PYOPENSG_ALIASES_H_ */
