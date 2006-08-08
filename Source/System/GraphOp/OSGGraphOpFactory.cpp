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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include <OSGGraphOpFactory.h>

#include <OSGGeoTypeGraphOp.h>
#include <OSGMakeTransparentGraphOp.h>
#include <OSGMaterialMergeGraphOp.h>
#include <OSGMergeGraphOp.h>
#include <OSGPruneGraphOp.h>
#include <OSGSharePtrGraphOp.h>
#include <OSGSplitGraphOp.h>
#include <OSGStripeGraphOp.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGVerifyGraphOp.h>

OSG_USING_NAMESPACE

GraphOpFactory *GraphOpFactory::_the=NULL;

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GraphOpFactory
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


void GraphOpFactory::registerOp(GraphOp* prototype)
{
    _typeMap[prototype->getName()]=prototype;
}

void GraphOpFactory::unRegisterOp(GraphOp* prototype)
{
    unRegisterOp(prototype->getName().c_str());
}

void GraphOpFactory::unRegisterOp(const char* name)
{
    _typeMap.erase(name);
}
    
GraphOp *GraphOpFactory::create(const char* name)
{
    GraphOp *proto = _typeMap[name];     
    if (proto != NULL)
        return proto->create();
    else
        return NULL;
}

GraphOpFactory& GraphOpFactory::the()
{
    if(_the == NULL)
        _the=new GraphOpFactory();
    return *_the;
}

GraphOpFactory::iterator GraphOpFactory::begin()
{
    return _typeMap.begin();;
}

GraphOpFactory::iterator GraphOpFactory::end()
{
    return _typeMap.end();;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

GraphOpFactory::GraphOpFactory()
{
    registerOp(new GeoTypeGraphOp);
    registerOp(new MakeTransparentGraphOp);
    registerOp(new MaterialMergeGraphOp);
    registerOp(new MergeGraphOp);
    registerOp(new PruneGraphOp);
    registerOp(new SharePtrGraphOp);
    registerOp(new SplitGraphOp);
    registerOp(new StripeGraphOp);
    registerOp(new VerifyGeoGraphOp);
    registerOp(new VerifyGraphOp);
}
