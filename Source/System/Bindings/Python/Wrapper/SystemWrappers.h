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

#ifndef _PYOPENSG_SYSTEMWRAPPERS_H_
#define _PYOPENSG_SYSTEMWRAPPERS_H_

#include <boost/python.hpp>

#include <OSGCamera.h>
#include <OSGAction.h>

namespace bp = boost::python;

/** Wrapper methods for getting values from some types. */
namespace osgwrap
{
/** @name OSG::traverse() Wrappers */
//@{
/**
 * Wraps the overload of OSG::traverse() that takes a single node and a
 * single callback. The Python interface is simply a free function that
 * accepts a scene graph node (osg2.Node) and a Python callable. The
 * callable must accept an osg2.Node object as its only argument and return a
 * value of type OSG::ActionBase::ResultE.
 *
 * @param root The root of the scene graph to traverse.
 * @param func The callable used as the traversal node entry callback.
 *
 * @return The traversal continue/skip/stop value is returned. This is the
 *         return value from the OSG::traverse() call.
 */
OSG::ActionBase::ResultE traverseWrapper1(OSG::Node::ObjRecPtr root,
                                          bp::object func);

/**
 * Wraps the overload of OSG::traverse() that takes a vector of nodes and a
 * single callback. The Python interface is a free function that accepts a
 * Python list of scene graph nodes (osg2.Node objects) and a Python callable.
 * The callable must accept an osg2.Node object as its only argument and
 * return a value of type OSG::ActionBase::ResultE.
 *
 * @param nodeList The list of root nodes whose subtrees will be traversed.
 * @param func     The callable used as the traversal node entry callback.
 *
 * @return The traversal continue/skip/stop value is returned. This is the
 *         return value from the OSG::traverse() call.
 */
OSG::ActionBase::ResultE traverseWrapper2(bp::list nodeList, bp::object func);

/**
 * Wraps the overload of OSG::traverse() that takes a single node and
 * traversal entry and exit callbacks. The Python interface is a free function
 * that accepts a scene graph node (osg2.Node) and two Python callables. The
 * first callable, \p enterFunc, must accept an osg2.Node object as its only
 * argument and return a value of type OSG::ActionBase::ResultE. The second
 * callable, \p exitFunc, must accept an osg2.Node object and an
 * osg2.ActionBase.ResultE value. The node is the same as the node passed to
 * \p enterFunc, and the result value is what \p enterFunc returned. In
 * general, \p exitFunc should return the same value as \p enterFunc.
 *
 * @param root      The root of the scene graph to traverse.
 * @param enterFunc The callable used as the traversal node entry callback.
 * @param exitFunc  The callable used as the traversal node exit callback.
 *
 * @return The traversal continue/skip/stop value is returned. This is the
 *         return value from the OSG::traverse() call.
 */
OSG::ActionBase::ResultE traverseWrapper3(OSG::Node::ObjRecPtr root,
                                          bp::object enterFunc,
                                          bp::object exitFunc);

/**
 * Wraps the overload of OSG::traverse() that takes a vector of nodes and
 * traversal entry and exit callbacks. The Python interface is a free function
 * that accepts a Python list of scene graph nodes (osg2.Node objects) and two
 * Python callables. The first callable, \p enterFunc, must accept an
 * osg2.Node object as its only argument and return a value of type
 * OSG::ActionBase::ResultE. The second callable, \p exitFunc, must accept an
 * osg2.Node object and an osg2.ActionBase.ResultE value. The node is the same
 * as the node passed to \p enterFunc, and the result value is what
 * \p enterFunc returned. In general, \p exitFunc should return the same value
 * as \p enterFunc.
 *
 * @param nodeList  The list of root nodes whose subtrees will be traversed.
 * @param enterFunc The callable used as the traversal node entry callback.
 * @param exitFunc  The callable used as the traversal node exit callback.
 *
 * @return The traversal continue/skip/stop value is returned. This is the
 *         return value from the OSG::traverse() call.
 */
OSG::ActionBase::ResultE traverseWrapper4(bp::list nodeList,
                                          bp::object enterFunc,
                                          bp::object exitFunc);
//@}

/** @name General Wrapper Functions */
//@{
// NOTE: This does not take a const reference to an OSG::Viewport object to
// avoid complications resulting from OSG::Viewport having a protected
// destructor. (We do not want Boost.Pythoon trying to make a copy of an
// OSG::Viewport behind the scenes.)
boost::python::tuple calcViewRay(OSG::Camera* self, OSG::Int32 x,
                                 OSG::Int32 y, OSG::Viewport& port);

boost::python::tuple getNormalizedCoordinates(OSG::Viewport* self,
                                              const OSG::Int32 vpX,
                                              const OSG::Int32 vpY);
//@}
}

#endif /* _PYOPENSG_SYSTEMWRAPPERS_H_ */
