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

// Unit tests for vec classes

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGFieldContainerAttachment.h>
#include <OpenSG/OSGDynamicAttachmentMixin.h>

#include <OpenSG/OSGBillboard.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSwitch.h>
#include <OpenSG/OSGTransform.h>

#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

struct TestAttDesc
{
    typedef OSG::FieldContainerAttachment    Parent;
    typedef OSG::FieldContainerAttachmentPtr ParentPtr;
    
    // TODO rename it to VRMLGenericAtt ????
    static const OSG::Char8 *getTypeName        (void) { return "TestAtt";    }
    static const OSG::Char8 *getParentTypeName  (void) 
    {
        return "FieldContainerAttachment"; 
    }
    static const OSG::Char8 *getGroupName       (void) { return "TestGenAtt"; }
    
    static OSG::InitContainerF     getInitMethod(void) { return NULL; }
    
    static OSG::FieldDescriptionBase **getDesc  (void) { return NULL; }
};

typedef OSG::DynFieldAttachment<TestAttDesc>  TestAtt;
typedef TestAtt::ObjPtr                       TestAttPtr;

OSG_DYNFIELDATTACHMENT_INST(TestAttDesc)

OSG_END_NAMESPACE

SUITE(NodeTests)
{

TEST(CreateNode)
{
   OSG::NodePtr n = OSG::Node::create();
   CHECK(n != OSGNullFC);
}

// --- Cloning --- //
TEST(TreeCloningName)
{
    OSG::NodePtr root = OSG::Node::create();
    OSG::NodePtr child_node = OSG::Node::create();
    root->addChild(child_node);
    OSG::setName(root, "root");
    OSG::setName(child_node, "child_node");

    OSG::NodePtr new_root = OSG::cloneTree(root);

    CHECK(new_root->getNChildren() == 1);
    CHECK(new_root != root);
    CHECK(new_root->getChild(0) != child_node);

    std::string new_name = OSG::getName(new_root);
    CHECK(new_name == "root");
}

// build a test tree (left is top)
//
// Group01 - Switch01 ---- Billboard01
//         |          |
//         |          ---- Group03
//         |
//         + Transform01 - Group04
//         |
//         - Group02 ----- Billboard02
//                   |
//                   ----- Switch02 ---- Group05
//                                  |
//                                  ---- Group06

struct CloneFixture
{
    CloneFixture(void)
    {
        g01Node = OSG::makeCoredNode<OSG::Group>(&g01Core);
        s01Node = OSG::makeCoredNode<OSG::Switch>(&s01Core);
        t01Node = OSG::makeCoredNode<OSG::Transform>(&t01Core);
        g02Node = OSG::makeCoredNode<OSG::Group>(&g02Core);
        b01Node = OSG::makeCoredNode<OSG::Billboard>(&b01Core);
        g03Node = OSG::makeCoredNode<OSG::Group>(&g03Core);
        g04Node = OSG::makeCoredNode<OSG::Group>(&g04Core);
        b02Node = OSG::makeCoredNode<OSG::Billboard>(&b02Core);
        s02Node = OSG::makeCoredNode<OSG::Switch>(&s02Core);
        g05Node = OSG::makeCoredNode<OSG::Group>(&g05Core);
        g06Node = OSG::makeCoredNode<OSG::Group>(&g06Core);

        g01Node->addChild(s01Node);
        g01Node->addChild(t01Node);
        g01Node->addChild(g02Node);
        s01Node->addChild(b01Node);
        s01Node->addChild(g03Node);
        t01Node->addChild(g04Node);
        g02Node->addChild(b02Node);
        g02Node->addChild(s02Node);
        s02Node->addChild(g05Node);
        s02Node->addChild(g06Node);
    }

    OSG::GroupPtr     g01Core;
    OSG::SwitchPtr    s01Core;
    OSG::TransformPtr t01Core;
    OSG::GroupPtr     g02Core;
    OSG::BillboardPtr b01Core;
    OSG::GroupPtr     g03Core;
    OSG::GroupPtr     g04Core;
    OSG::BillboardPtr b02Core;
    OSG::SwitchPtr    s02Core;
    OSG::GroupPtr     g05Core;
    OSG::GroupPtr     g06Core;

    OSG::NodePtr      g01Node;
    OSG::NodePtr      s01Node;
    OSG::NodePtr      t01Node;
    OSG::NodePtr      g02Node;
    OSG::NodePtr      b01Node;
    OSG::NodePtr      g03Node;
    OSG::NodePtr      g04Node;
    OSG::NodePtr      b02Node;
    OSG::NodePtr      s02Node;
    OSG::NodePtr      g05Node;
    OSG::NodePtr      g06Node;
};

TEST_FIXTURE(CloneFixture, CloneTree)
{
    // test cloneTree - all shared
    OSG::NodePtr clone01 = OSG::cloneTree(g01Node);

    CHECK(clone01                                      != g01Node);
    CHECK(clone01->getCore()                           == g01Core);
    CHECK(clone01->getChild(0)->getCore()              == s01Core);
    CHECK(clone01->getChild(1)->getChild(0)->getCore() == g04Core);
    CHECK(clone01->getChild(2)->getCore()              == g02Core);

    // test cloneTree - clone Switch
    OSG::NodePtr clone02 = OSG::cloneTree(g01Node, "Switch", "");

    CHECK(clone02->getCore()                           == g01Core);
    CHECK(clone02->getChild(0)->getCore()              != s01Core);
    CHECK(OSG::osgStringCmp(clone02->getChild(0)->getCore()->getType().getCName(),
                            "Switch")                  == 0      );
    CHECK(clone02->getChild(1)->getChild(0)->getCore() == g04Core);
    CHECK(clone02->getChild(2)->getCore()              == g02Core);

    // test cloneTree - clone Billboard, ignore Switch
    OSG::NodePtr clone03 = OSG::cloneTree(g01Node, "Billboard", "Switch");

    CHECK(clone03->getCore() == g01Core);
    CHECK(clone03->getChild(0)->getChild(0)->getCore() != b01Core);
    CHECK(clone03->getChild(0)->getCore() == OSGNullFC);
    CHECK(clone03->getChild(2)->getChild(0)->getCore() != b02Core);
    CHECK(clone03->getChild(2)->getChild(1)->getCore() == OSGNullFC);
}

TEST_FIXTURE(CloneFixture, DeepCloneTree)
{
    // test deepCloneTree - all cloned
    OSG::NodePtr clone01 = OSG::deepCloneTree(g01Node);

    CHECK(clone01                         != g01Node);
    CHECK(clone01->getCore()              != g01Core);
    CHECK(OSG::osgStringCmp(clone01->getCore()->getType().getCName(),
                            "Group")      == 0                       );
    CHECK(clone01->getChild(0)            != s01Node);
    CHECK(clone01->getChild(0)->getCore() != s01Core);
    CHECK(OSG::osgStringCmp(clone01->getChild(0)->getCore()->getType().getCName(),
                            "Switch")     == 0                                    );

    // test deepCloneTree - share Switch
    OSG::NodePtr clone02 = OSG::deepCloneTree(g01Node, "Switch");

    CHECK(clone02->getCore()              != g01Core);
    CHECK(clone02->getChild(0)            != s01Node);
    CHECK(clone02->getChild(0)->getCore() == s01Core);

    // test deepCloneTree - share Billboard, ignore Switch
    OSG::NodePtr clone03 = OSG::deepCloneTree(g01Node, "Billboard", "Switch");

    CHECK(clone03->getCore()                           != g01Core);
    CHECK(clone03->getChild(0)->getCore()              == OSGNullFC);
    CHECK(clone03->getChild(0)->getChild(0)->getCore() == b01Core);
    CHECK(clone03->getChild(2)->getChild(0)->getCore() == b02Core);
    CHECK(clone03->getChild(2)->getChild(1)->getCore() == OSGNullFC);
}

TEST(DynFieldAttachment)
{
    OSG::TestAttPtr pT = OSG::TestAtt::create();

    OSG::FieldDescriptionBase *pDesc = NULL;

    pDesc = new OSG::SFInt32::Description(
        OSG::SFInt32::getClassType(),
        "foo",
        "bar",
        0, 
        0,
        false,
        OSG::Field::SFDefaultFlags,
        static_cast<OSG::FieldIndexEditMethodSig>(
            &OSG::TestAtt::editDynamicField),
        static_cast<OSG::FieldIndexGetMethodSig >(
            &OSG::TestAtt::getDynamicField ));

    CHECK(pT != OSGNullFC);

    OSG::UInt32 fIndex = pT->addField(*pDesc);

    CHECK(fIndex != 0);

    OSG::GetFieldHandlePtr pFI = pT->getDynamicField(fIndex);

    CHECK(pFI != NULL);

    OSG::GetFieldHandlePtr pFN = pT->getDynamicFieldByName("foo");

    CHECK(pFN != NULL);

    CHECK(pFN == pFI);
}

} // SUITE
