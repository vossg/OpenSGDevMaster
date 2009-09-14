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

#ifndef _OSGCOLLADAGLOBAL_H_
#define _OSGCOLLADAGLOBAL_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaGlobal.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGColladaElement.h"

#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaGlobal : public ColladaElement
{
  public:
    typedef ColladaElement    Inherited;
    typedef ColladaGlobal     Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    
    typedef std::vector<ColladaElementRefPtr      > ColladaElementStore;
    typedef ColladaElementStore::iterator           ColladaElementStoreIt;

    static inline ObjTransitPtr create(void);
    
    virtual void read(void);
    
    inline DAE               &getDAE     (void                      );
    
    inline void               setDocPath (const std::string &docPath);
    inline const std::string &getDocPath (void                      ) const;
    
    inline Node *getRootNode  (void) const;
    inline Node *getLightsNode(void) const;
    
    bool invertTransparency(void) const;

  protected:
    friend class OSG::ColladaElement;
    
             ColladaGlobal(void);
    virtual ~ColladaGlobal(void);
      
    inline void addElement(ColladaElement *elem);
    inline void subElement(ColladaElement *elem);
      
      
    std::string         _docPath;
    
    NodeUnrecPtr        _rootN;
    NodeUnrecPtr        _lightsN;
    
    DAE                 _dae;
    ColladaElementStore _elements;

    bool                _invertTransparency;
};

typedef ColladaGlobal::ObjRefPtr      ColladaGlobalRefPtr;
typedef ColladaGlobal::ObjTransitPtr  ColladaGlobalTransitPtr;

OSG_END_NAMESPACE

#include "OSGColladaGlobal.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAGLOBAL_H_
