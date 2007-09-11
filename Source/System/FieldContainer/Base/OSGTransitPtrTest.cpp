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
#include <OpenSG/OSGRefPtr.h>
#include <OpenSG/OSGTransitPtr.h>
#include <OpenSG/OSGNode.h>

#include <iostream>
#include <string>
#include <vector>

using namespace OSG;

typedef TransitPtr<NodePtr>  NodeTransitPtr;

SUITE(TransitPtrTests)
{

TEST(create)
{    
    NodePtr np = Node::create();
    NodeRefPtr r(np);
    CHECK(np->getRefCount() == 1);
    
    NodeRefPtr r2 = r;
    CHECK(np->getRefCount() == 2);
    
    NodeTransitPtr t(r);
    CHECK(r == NullFC);
    CHECK(np->getRefCount() == 2);
    
    NodeRefPtr r3;
    r3 = t;
    CHECK(np->getRefCount() == 2);
    CHECK(r3 == r2);
    
    r = r2;
    NodeTransitPtr t2(r);
    CHECK(r == NullFC);
    CHECK(np->getRefCount() == 3);
       
    NodeTransitPtr t3(t2);
    CHECK(np->getRefCount() == 3);
    
    r3 = t3;
    CHECK(np->getRefCount() == 3);
    CHECK(r3 == r2);     
}

} // SUITE
