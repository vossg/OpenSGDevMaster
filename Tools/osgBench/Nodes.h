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

#ifndef _NODES_H_
#define _NODES_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGLight.h>

class NodeIterator;
class Geometry;
class Transform;

template<class type> class TypedNodeIterator;


class NodeBase
{
     /*==========================  PUBLIC  =================================*/
  public:
 
    NodeBase(void);
 
    NodeBase(const NodeBase &copy);
 
    NodeBase(OSG::NodePtr node);
 
    NodeBase(OSG::NodeCorePtr core);
    
    ~NodeBase();
    
    const char *getType(void);

    static const char * getCoreName(void) { return "<none>"; }
    
    void dump(void);
    
    inline OSG::NodePtr getNode(void);

    void save(const char * name);

    NodeBase clone(void);
    
    NodeIterator iter(const char * name);
    
    TypedNodeIterator<Geometry>  geometries(void);
    TypedNodeIterator<Transform> transforms(void);
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    OSG::NodePtr _node;

    /*==========================  PRIVATE  ================================*/
  private:

};

class Group : public NodeBase
{
    /*==========================  PUBLIC  =================================*/
  public:
 
    Group(void);
  
    Group(const Group &copy);
  
    Group(OSG::NodePtr node);
  
    Group(OSG::GroupPtr group);
   
    ~Group();

    static const char * getCoreName(void) { return "Group"; }
    
    void addChild(NodeBase &node);
    
    void subChild(NodeBase &node);
         
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:

    OSG::GroupPtr _group;
};

class Transform : public Group
{
    /*==========================  PUBLIC  =================================*/
  public:
 
    Transform(void);
 
    Transform(const Transform &copy);
 
    Transform(OSG::NodePtr node);
 
    Transform(OSG::TransformPtr transform);
    
    ~Transform();

    static const char * getCoreName(void) { return "Transform"; }
    
    void setTranslation(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z);    
         
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:

    OSG::TransformPtr _transform;
};

class Light : public Group
{
    /*==========================  PUBLIC  =================================*/
  public:
 
    Light(void);
 
    Light(const Light &copy);
 
    Light(OSG::NodePtr node);
 
    Light(OSG::LightPtr light);
    
    ~Light();
 
    static const char * getCoreName(void) { return "Light"; }
        
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:

    OSG::LightPtr _transform;
};

class Geometry : public NodeBase
{
    /*==========================  PUBLIC  =================================*/
  public:
 
    Geometry(void);

    Geometry(const Geometry &node);

    Geometry(OSG::NodePtr node);

    Geometry(OSG::GeometryPtr node);
    
    ~Geometry();

    static const char * getCoreName(void) { return "Geometry"; }

    void translate(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z);

    void scale(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z);
    
    void merge(Geometry &geo);
    
    void setDlistCache(bool cache);
    
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:

    OSG::GeometryPtr _geometry;
};

class NodeIterator
{
  public:
  
    NodeIterator(void);
    NodeIterator(NodeBase &start, const char *name);
    NodeIterator(const NodeIterator &copy);
    
    ~NodeIterator();
    
    NodeIterator __iter__(void);
    
    NodeBase next(void);

  protected:
  
    OSG::FieldContainerType *_type;
    
  private:
  
    std::vector<OSG::NodePtr> _stack;
};

template <class type>
class TypedNodeIterator : public NodeIterator
{
  public:
    
    TypedNodeIterator(void);

    TypedNodeIterator(NodeBase &start);
    TypedNodeIterator(const TypedNodeIterator<type> &copy);
    
    ~TypedNodeIterator();
    
    TypedNodeIterator<type> __iter__(void);
    
    type next(void);
};

// Functions

Geometry makeBox(OSG::Real32 x, OSG::Real32 y, OSG::Real32 z,
                 OSG::UInt16 hor, OSG::UInt16 vert, OSG::UInt16 depth);

Geometry makeTorus(OSG::Real32 inner, OSG::Real32 outer,
                   OSG::UInt16 sides, OSG::UInt16 rings);

Geometry makeSphere(OSG::UInt16 latres, OSG::UInt16 longres, 
                    OSG::Real32 radius);

Geometry makePlane(OSG::Real32 x, OSG::Real32 y,
                   OSG::UInt16 hor, OSG::UInt16 vert);

void addRef(NodeBase &node);

void subRef(NodeBase &node);

NodeBase makeShared(NodeBase &node);

NodeBase loadScene(char *filename);

#include "Nodes.inl"

#endif
