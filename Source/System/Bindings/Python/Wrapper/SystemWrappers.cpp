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
#include <OSGViewport.h>
#include <boost/bind.hpp>
#include <boost/python.hpp>
#include "SystemWrappers.h"

namespace bp = boost::python;

namespace osgwrap
{

/**
 * Wraps the traversal entry callback invocation. The callback to invoke is
 * the given boost::python::object instance. The given callable must accept an
 * osg2.Node object as its only argument and return a value of type
 * OSG::ActionBase::ResultE.
 *
 * @param obj  A Python callable.
 * @param node The node that has been entered by OSG::traverse().
 *
 * @return The traversal continue/skip/stop value returned by the given
 *         Python callable is returned.
 *
 * @see OSG::traverse()
 * @see osgwrap::traverseWrapper1()
 * @see osgwrap::traverseWrapper2()
 * @see osgwrap::traverseWrapper3()
 * @see osgwrap::traverseWrapper4()
 */
OSG::ActionBase::ResultE wrapEnterCallback(bp::object obj, OSG::Node* node)
{
   return bp::extract<OSG::ActionBase::ResultE>(
             obj(OSG::Node::ObjRecPtr(node))
          );
}

/**
 * Wraps the traversal exit callback invocation. The callback to invoke is
 * the given boost::python::object instance. The given callable must accept an
 * osg2.Node object and an osg2.ActionBase.ResultE value. The node is the same
 * as the node passed to wrapEnterCallback(), and the result value is what
 * wrapEnterCallback() returned.
 *
 * @param obj    A Python callable.
 * @param node   The node that has been entered by OSG::traverse().
 * @param result The value returned by wrapEnterCallback().
 *
 * @return The traversal continue/skip/stop value returned by the given
 *         Python callable is returned.
 *
 * @see OSG::traverse()
 * @see osgwrap::traverseWrapper1()
 * @see osgwrap::traverseWrapper2()
 * @see osgwrap::traverseWrapper3()
 * @see osgwrap::traverseWrapper4()
 */
OSG::ActionBase::ResultE wrapExitCallback(bp::object obj, OSG::Node* node,
                                          OSG::Action::ResultE result)
{
   return bp::extract<OSG::ActionBase::ResultE>(
             obj(OSG::Node::ObjRecPtr(node), result)
          );
}

OSG::ActionBase::ResultE traverseWrapper1(OSG::Node::ObjRecPtr root,
                                          bp::object func)
{
   return OSG::traverse(root, boost::bind(wrapEnterCallback, func, _1));
}

OSG::ActionBase::ResultE traverseWrapper2(bp::list nodeList, bp::object func)
{
   // Construct a vector of OSG::Node objects from the given Python list
   // of osg2.Node objects.
   const unsigned int node_count =
      bp::extract<unsigned int>(nodeList.attr("__len__")());
   std::vector<OSG::Node*> node_vec(node_count);

   for ( unsigned int i = 0; i < node_count; ++i )
   {
      OSG::NodeRecPtr cur_node = bp::extract<OSG::NodeRecPtr>(nodeList[i]);
      node_vec[i] = cur_node.get();
   }

   return OSG::traverse(node_vec, boost::bind(wrapEnterCallback, func, _1));
}

OSG::ActionBase::ResultE traverseWrapper3(OSG::Node::ObjRecPtr root,
                                          bp::object enterFunc,
                                          bp::object exitFunc)
{
   return OSG::traverse(root, boost::bind(wrapEnterCallback, enterFunc, _1),
                        boost::bind(wrapExitCallback, exitFunc, _1, _2));
}

OSG::ActionBase::ResultE traverseWrapper4(bp::list nodeList,
                                          bp::object enterFunc,
                                          bp::object exitFunc)
{
   // Construct a vector of OSG::Node objects from the given Python list
   // of osg2.Node objects.
   const unsigned int node_count =
      bp::extract<unsigned int>(nodeList.attr("__len__")());
   std::vector<OSG::Node*> node_vec(node_count);

   for ( unsigned int i = 0; i < node_count; ++i )
   {
      OSG::NodeRecPtr cur_node = bp::extract<OSG::NodeRecPtr>(nodeList[i]);
      node_vec[i] = cur_node.get();
   }

   return OSG::traverse(node_vec,
                        boost::bind(wrapEnterCallback, enterFunc, _1),
                        boost::bind(wrapExitCallback, exitFunc, _1, _2));
}


boost::python::tuple calcViewRay(OSG::Camera* self, OSG::Int32 x,
                                 OSG::Int32 y, OSG::Viewport& port)
{
   OSG::Line line;
   OSG::Real32 t;
   bool result = self->calcViewRay(line, x, y, port, &t);
   return boost::python::make_tuple(result, line, t);
}

boost::python::tuple getNormalizedCoordinates(OSG::Viewport* self,
                                              const OSG::Int32 vpX,
                                              const OSG::Int32 vpY)
{
   OSG::Real32 norm_x, norm_y;
   self->getNormalizedCoordinates(norm_x, norm_y, vpX, vpY);
   return boost::python::make_tuple(norm_x, norm_y);
}

} // namespace osgwrap

