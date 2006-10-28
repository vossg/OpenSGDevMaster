/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2006 by the OpenSG Forum                          *
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

#include <UnitTest++.h>

#include <OpenSG/OSGTypeBasePredicates.h>
#include <OpenSG/OSGReflexiveContainerTypePredicates.h>

#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGFieldContainerAttachment.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>

#include <vector>

// This test is for the type prediactes in OSGTypeBasePredicates.h and
// OSGReflexiveContainerTypePredicates.h .
// The former is not tested in the Base library, because there are too few types
// with interesting relationships to test there.

namespace {

TEST(TypeBasePredicates)
{
    const OSG::FieldContainerType& nodeType     = OSG::Node::getClassType();
    const OSG::FieldContainerType& nodeCoreType = OSG::NodeCore::getClassType();
    const OSG::FieldContainerType& attConType   =
        OSG::AttachmentContainer::getClassType();
    const OSG::FieldContainerType& fieldConType =
        OSG::FieldContainer::getClassType();

    // Test TypePredicates::IsBaseOf

    OSG::TypePredicates::IsBaseOf baseOfNode    (nodeType    );
    OSG::TypePredicates::IsBaseOf baseOfNodeCore(nodeCoreType);

    CHECK_EQUAL(baseOfNode    (&attConType),   true);
    CHECK_EQUAL(baseOfNodeCore(&attConType),   true);
    CHECK_EQUAL(baseOfNode    (&nodeCoreType), false);
    CHECK_EQUAL(baseOfNodeCore(&nodeType),     false);

    // Test sequence functions

    std::vector<const OSG::FieldContainerType *> typeVec1;
    std::vector<const OSG::FieldContainerType *> typeVec2;

    typeVec1.push_back(&nodeType);
    typeVec1.push_back(&nodeCoreType);
    typeVec1.push_back(&fieldConType);

    typeVec2.push_back(&attConType);
    typeVec2.push_back(&fieldConType);

    CHECK_EQUAL(OSG::TypePredicates::typeDerivedFrom(
        typeVec1.begin(), typeVec1.end(), attConType), true);
    CHECK_EQUAL(OSG::TypePredicates::typeDerivedFromAll(
        typeVec2.begin(), typeVec2.end(), nodeType), true);

    // Test TypePredicates::IsDerivedFrom

    OSG::TypePredicates::IsDerivedFrom derivFromAttCon(attConType);
    OSG::TypePredicates::IsDerivedFrom derivFromFC(fieldConType);

    CHECK_EQUAL(derivFromAttCon(&nodeType),     true);
    CHECK_EQUAL(derivFromAttCon(&nodeCoreType), true);
    CHECK_EQUAL(derivFromAttCon(&fieldConType), false);

    CHECK_EQUAL(derivFromFC(&nodeType),   true);
    CHECK_EQUAL(derivFromFC(&attConType), true);
}

TEST(ReflexiveContainerTypePredicates)
{
    const OSG::FieldContainerType& nodeType     = OSG::Node::getClassType();
    const OSG::FieldContainerType& nodeCoreType = OSG::NodeCore::getClassType();
    const OSG::FieldContainerType& attConType   =
        OSG::AttachmentContainer::getClassType();
    const OSG::FieldContainerType& fieldConType =
        OSG::FieldContainer::getClassType();

    OSG::TypePredicates::IsSameGroupAs sameGroupAsNode    (nodeType    );
    OSG::TypePredicates::IsSameGroupAs sameGroupAsNodeCore(nodeCoreType);

    // TODO: Find types that are actually in the same group
    CHECK_EQUAL(sameGroupAsNode(&attConType),   false);
    CHECK_EQUAL(sameGroupAsNode(&nodeCoreType), false);
    CHECK_EQUAL(sameGroupAsNode(&fieldConType), false);
}

} // namespace
