/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <boost/python/errors.hpp> 
#include <Python.h>
#include <Nodes.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSceneFileHandler.h>

// Basic Node

NodeBase::NodeBase()
{
    _node = OSG::Node::create();
}

NodeBase::NodeBase(const NodeBase &copy) : _node(copy._node)
{
}

NodeBase::NodeBase(OSG::NodePtr node) : _node(node)
{
}

NodeBase::NodeBase(OSG::NodeCorePtr core)
{
    _node = OSG::Node::create();
    
    // beginEditCP(_node);
    _node->setCore(core);
    // endEditCP(_node);    
}

NodeBase::~NodeBase()
{    
}

const char *NodeBase::getType(void)
{
    if(_node->getCore() == OSG::NullFC)
        return "<uncored>";
    
    return _node->getCore()->getType().getCName();
}

void NodeBase::dump(void)
{
    _node->dump();
}

void NodeBase::save(const char * name)
{
    OSG::SceneFileHandler::the()->write(_node, name);
}

NodeBase NodeBase::clone(void)
{
    return NodeBase(OSG::deepCloneTree(_node));
}


NodeIterator NodeBase::iter(const char * name)
{
    return NodeIterator(*this, name);
}
    
TypedNodeIterator<Geometry> NodeBase::geometries(void)
{
    return TypedNodeIterator<Geometry>(*this);
}
    
TypedNodeIterator<Transform> NodeBase::transforms(void)
{
    return TypedNodeIterator<Transform>(*this);
}

// Group Node

Group::Group() : NodeBase()
{
    _group = OSG::Group::create();
    
    // OSG::beginEditCP(_node);
    _node->setCore(_group);
    // OSG::endEditCP(_node);
}

Group::Group(const Group &group) : NodeBase(group)
{
    _group = group._group;
}

Group::Group(OSG::NodePtr node) : NodeBase(node)
{
    _group = OSG::cast_dynamic<OSG::GroupPtr>(node->getCore());
   
    // OSG::beginEditCP(_node);
    _node->setCore(_group);
    // OSG::endEditCP(_node);
}

Group::Group(OSG::GroupPtr group) : NodeBase()
{
    // OSG::beginEditCP(_node);
    _node->setCore(_group);
    // OSG::endEditCP(_node);
}

Group::~Group()
{    
}


void Group::addChild(NodeBase &child) 
{
    // OSG::beginEditCP(_node);
    _node->addChild(child.getNode());
    // OSG::endEditCP(_node);
}


void Group::subChild(NodeBase &child) 
{
    // OSG::beginEditCP(_node);
    _node->subChild(child.getNode());
    // OSG::endEditCP(_node);
}

// Transform Node

Transform::Transform() 
{
    _transform = OSG::Transform::create();
    
    // OSG::beginEditCP(_node);
    _node->setCore(_transform);
    // OSG::endEditCP(_node);
}

Transform::Transform(const Transform &trans) : Group(trans)
{
    _transform = trans._transform;
}

Transform::Transform(OSG::NodePtr node) : Group(node)
{
    _transform = OSG::cast_dynamic<OSG::TransformPtr>(node->getCore());
   
    // OSG::beginEditCP(_node);
    _node->setCore(_transform);
    // OSG::endEditCP(_node);
}

Transform::Transform(OSG::TransformPtr transform) : Group()
{
    // OSG::beginEditCP(_node);
    _node->setCore(_transform);
    // OSG::endEditCP(_node);
}

Transform::~Transform()
{    
}


void Transform::setTranslation(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z) 
{
    OSG::Matrix m;
    
    m.setTransform(OSG::Vec3f(x,y,z));
    
    // OSG::beginEditCP(_transform);
    _transform->setMatrix(m);
    // OSG::endEditCP(_transform);
}


// Geometry Node

Geometry::Geometry() 
{
    _geometry = OSG::Geometry::create();
    
    // OSG::beginEditCP(_node);
    _node->setCore(_geometry);
    // OSG::endEditCP(_node);
}

Geometry::Geometry(const Geometry &geo) : NodeBase(geo)
{
    _geometry = geo._geometry;
}

Geometry::Geometry(OSG::NodePtr node) : NodeBase(node)
{
    _geometry = OSG::cast_dynamic<OSG::GeometryPtr>(node->getCore());
   
    // OSG::beginEditCP(_node);
    _node->setCore(_geometry);
    // OSG::endEditCP(_node);
}

Geometry::Geometry(OSG::GeometryPtr geometry) : NodeBase()
{
    // OSG::beginEditCP(_node);
    _node->setCore(_geometry);
    // OSG::endEditCP(_node);
}

Geometry::~Geometry()
{    
}


void Geometry::translate(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z) 
{
    OSG::Vec3f d(x,y,z);
    OSG::Pnt3f p;
    OSG::GeoPositionsPtr pos = _geometry->getPositions();
    
    // OSG::beginEditCP(_geometry, OSG::Geometry::PositionsFieldMask);
    
    for(OSG::UInt32 i = 0; i < pos->size(); ++i)
    {
        pos->getValue(p, i);
        p += d;
        pos->setValue(p,i);
    }

    // OSG::endEditCP(_geometry, OSG::Geometry::PositionsFieldMask);
}

void Geometry::scale(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z) 
{
    OSG::Pnt3f p;
    OSG::GeoPositionsPtr pos = _geometry->getPositions();
    
    // OSG::beginEditCP(_geometry, OSG::Geometry::PositionsFieldMask);
    
    for(OSG::UInt32 i = 0; i < pos->size(); ++i)
    {
        pos->getValue(p, i);
        p[0] *= x;
        p[1] *= y;
        p[2] *= z;
        pos->setValue(p,i);
    }

    // OSG::endEditCP(_geometry, OSG::Geometry::PositionsFieldMask);
}


void Geometry::setDlistCache(bool cache) 
{
    _geometry->setDlistCache(cache);
}


// Node Iterator

NodeIterator::NodeIterator(void)
{
}

NodeIterator::NodeIterator(NodeBase &start, const char *name)
{
    _stack.push_back(start.getNode());
    
    _type = OSG::FieldContainerFactory::the()->findType(name);
    
}

NodeIterator::NodeIterator(const NodeIterator &copy) : 
    _type(copy._type), _stack(copy._stack)
{
}

NodeIterator::~NodeIterator()
{
}

NodeIterator NodeIterator::__iter__(void)
{
    return *this;
}

NodeBase NodeIterator::next(void)
{
    while(!_stack.empty())
    {
        OSG::NodePtr act = _stack.back();

        _stack.pop_back();

        for(OSG::UInt32 i = 0; i < act->getNChildren(); ++i)
            _stack.push_back(act->getChild(i));

        if(act->getCore()->getType().isDerivedFrom(*_type))
        {
            return NodeBase(act);
        }    
    }
   
    PyErr_SetString(PyExc_StopIteration, "Out of Nodes");   
    boost::python::throw_error_already_set();
}


template <class type>    
TypedNodeIterator<type>::TypedNodeIterator(void) : NodeIterator()
{
    _type = OSG::FieldContainerFactory::the()->findType(type::getCoreName());
}

template <class type>    
TypedNodeIterator<type>::TypedNodeIterator(NodeBase &start) : 
    NodeIterator(start, type::getCoreName())
{
}

template <class type>    
TypedNodeIterator<type>::TypedNodeIterator(const TypedNodeIterator<type> &copy)
: NodeIterator(copy)
{
}
    
template <class type>    
TypedNodeIterator<type>::~TypedNodeIterator()
{
}
    
template <class type>       
TypedNodeIterator<type> TypedNodeIterator<type>::__iter__(void)
{
    return *this;
}
    
template <class type>    
type TypedNodeIterator<type>::next(void)
{
    return type(NodeIterator::next().getNode());
}


template class TypedNodeIterator<Geometry>;
template class TypedNodeIterator<Transform>;

// Functions


Geometry makeBox(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z,
                 OSG::UInt16 hor, OSG::UInt16 vert, OSG::UInt16 depth)
{
    Geometry g(OSG::makeBox(x,y,z,hor,vert,depth));
    
    return g;
}

Geometry makeTorus(OSG::Real32 inner, OSG::Real32 outer,
                   OSG::UInt16 sides, OSG::UInt16 rings)
{
    Geometry g(OSG::makeTorus(inner,outer,sides,rings));
    
    return g;
}

Geometry makeSphere(OSG::UInt16 latres, OSG::UInt16 longres, 
                    OSG::Real32 radius)
{
    Geometry g(OSG::makeLatLongSphere(latres,longres,radius));
    
    return g;
}


Geometry makePlane(OSG::Real32 x, OSG::Real32 y,
                   OSG::UInt16 hor, OSG::UInt16 vert)
{
    Geometry g(OSG::makePlane(x, y, hor, vert));
    
    return g;
}

NodeBase makeShared(NodeBase &node)
{
    return NodeBase(node.getNode()->getCore());
}

void addRef(NodeBase &node)
{
    OSG::addRef(node.getNode());
}

void subRef(NodeBase &node)
{
    OSG::subRef(node.getNode());
}

NodeBase loadScene(char *filename)
{
    OSG::NodePtr node = OSG::SceneFileHandler::the()->read(filename);
    
    return NodeBase(node);
}
