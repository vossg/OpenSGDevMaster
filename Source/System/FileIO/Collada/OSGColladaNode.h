/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADANODE_H_
#define _OSGCOLLADANODE_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaNode.h
    \ingroup GrpLoader
 */

#include <OSGConfig.h>

#ifdef OSG_WITH_COLLADA

#include <OSGFileIODef.h>
#include <OSGColladaInstantiableElement.h>

#include <OSGNode.h>
#include <OSGTransform.h>

// forward declarations
class domLookat;
class domMatrix;
class domRotate;
class domScale;
class domSkew;
class domTranslate;
class domInstance_node;
class domInstance_geometry;
class domInstance_light;
class domNode;

OSG_BEGIN_NAMESPACE

class ColladaGlobal;
class ColladaInstanceNode;


class OSG_FILEIO_DLLMAPPING ColladaNode : public ColladaInstantiableElement
{
  public:
    typedef ColladaInstantiableElement              Inherited;
    typedef ColladaNode                             Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    static inline ObjTransitPtr create(domNode *node, ColladaGlobal *global);
    
    virtual void read   (void);
    
    inline Node *getNode(void) const;
    
  protected:
    friend class ColladaInstanceNode;

    NodeUnrecPtr      _transNode;
    TransformUnrecPtr _trans;
    
             ColladaNode(domNode *node, ColladaGlobal *global);
    virtual ~ColladaNode(void                                );
    
    void handleLookAt          (domLookat            *lookAt   );
    void handleMatrix          (domMatrix            *matrix   );
    void handleRotate          (domRotate            *rotate   );
    void handleScale           (domScale             *scale    );
    void handleSkew            (domSkew              *skew     );
    void handleTranslate       (domTranslate         *translate);
    void handleInstanceNode    (domInstance_node     *instNode );
    void handleInstanceGeometry(domInstance_geometry *instGeo  );
    void handleInstanceLight   (domInstance_light    *instLight);
    void handleNode            (domNode              *node     );
};

typedef ColladaNode::ObjRefPtr     ColladaNodeRefPtr;
typedef ColladaNode::ObjTransitPtr ColladaNodeTransitPtr;

OSG_END_NAMESPACE

#include <OSGColladaNode.inl>

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADANODE_H_
