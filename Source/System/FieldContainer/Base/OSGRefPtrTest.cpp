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

SUITE(RefPtrTests)
{

TEST(create)
{    
    NodePtr np = Node::create();
    CHECK(np->getRefCount() == 0);
    
    NodeRefPtr r;
    CHECK(r == NullFC);
    
    NodeRefPtr r2(np);
    CHECK(r2.get() == np);
    CHECK(np->getRefCount() == 1);
    
    NodeRefPtr r3(r2);
    CHECK(r3.get() == np);
    CHECK(np->getRefCount() == 2);
}

TEST(convertAndAssign)
{
    NodePtr np = Node::create();

    NodeRefPtr r(np); 
    CHECK(np->getRefCount() == 1);
    
    NodePtr n2 = r;
    CHECK(np == n2);

    NodeRefPtr r2 = r;
    CHECK(r.get() == r2.get());

    NodeRefPtr r3;
    CHECK(r3 == NullFC);
    
    r3.swap(r2);
    CHECK(r2 == NullFC);
    CHECK(r3.get() == np);
}

static bool fcptrF(NodePtr np)
{
    return true;
}

static bool refptrF(NodeRefPtr nrp)
{
    return true;
}

static bool fcptrRefF(NodePtr &np)
{
    return true;
}

static bool refptrRefF(NodeRefPtr &nrp)
{
    return true;
}

TEST(pass)
{
    NodePtr np = Node::create();
    NodeRefPtr r(np); 

    CHECK(fcptrF(np));
    CHECK(fcptrF(r));
    
    CHECK(refptrF(r));

    CHECK(fcptrRefF(np));
    // CHECK(fcptrRefF(r)); // I couldn't get this to work...
    
    CHECK(refptrRefF(r));
}

TEST(compare)
{
    NodePtr np = Node::create();
    NodePtr np2 = Node::create();

    NodeRefPtr r(np), r2(np2);
    
    CHECK(r == r); 
    CHECK(r != r2); 
    CHECK(r < r2 || r2 < r); 

    NodeRefPtr r3;
    CHECK(!r3);
}

} // SUITE
