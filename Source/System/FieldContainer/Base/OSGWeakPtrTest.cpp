/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2006 by the OpenSG Forum                   *
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

#include <UnitTest++.h>

#include <OpenSG/OSGFieldContainer.h>
#include <OpenSG/OSGWeakPtr.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGTransform.h>

#include <iostream>
#include <string>
#include <vector>

using namespace OSG;

typedef WeakPtr<NodePtr>       NodeWeakPtr;
typedef WeakPtr<NodeCorePtr>   NodeCoreWeakPtr;
typedef WeakPtr<TransformPtr>  TransformWeakPtr;

SUITE(WeakPtrTests)
{

TEST(create)
{    
    NodePtr np = Node::create();
    NodeRefPtr r(np);

    NodeWeakPtr w;
    CHECK(w == NullFC);

    {
        NodeWeakPtr w2(np);
        CHECK(np->getWeakRefCount() == 1);   
    }
    CHECK(np->getWeakRefCount() == 0);   
    
    NodeWeakPtr w3(r);
    CHECK(np->getWeakRefCount() == 1);   
    
    {
        NodeWeakPtr w4(w3);
        CHECK(np->getWeakRefCount() == 2);   
    }
    CHECK(np->getWeakRefCount() == 1);   
}

TEST(convertAndAssign)
{
    NodePtr np = Node::create();
    NodeRefPtr r(np);
    CHECK(np->getWeakRefCount() == 0); 
    CHECK(np->getRefCount()     == 1); 
    
    NodeWeakPtr w;
    w = np;
    CHECK(np->getWeakRefCount() == 1); 
    
    NodeWeakPtr w2;    
    w2 = w;
    CHECK(np->getWeakRefCount() == 2); 
    
    NodeWeakPtr w3;    
    w3 = r;
    CHECK(np->getWeakRefCount() == 3); 
    
    NodeRefPtr r2;    
    r2 = w;
    CHECK(np->getRefCount() == 2); 
   
    NodeRefPtr r3;    
    r3 = w.get();
    CHECK(np->getRefCount() == 3); 
}

TEST(compare)
{
    NodePtr np = Node::create();
    NodePtr np2 = Node::create();

    NodeRefPtr r(np), r2(np2);
    
    NodeWeakPtr w(np), w2(np), w3(np2);
    
    CHECK(w == w2); 
    CHECK(w != w3); 
    
    CHECK(w == np);
    CHECK(w != np2);
    
    
    CHECK(w);
    
    NodeWeakPtr w4;
    
    CHECK(!w4);
}

} // SUITE
