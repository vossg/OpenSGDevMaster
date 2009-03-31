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

// Unit tests for nodes, attachments various core types

#include <OSGNode.h>
#include <OSGNameAttachment.h>
#include <OSGAttachment.h>
#include <OSGDynamicAttachmentMixin.h>

#include <OSGBillboard.h>
#include <OSGGroup.h>
#include <OSGSwitch.h>
#include <OSGTransform.h>

#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

struct TestAttDesc
{
    typedef OSG::Attachment    Parent;
    
    // TODO rename it to VRMLGenericAtt ????
    static const OSG::Char8 *getTypeName        (void) { return "TestAtt";    }
    static const OSG::Char8 *getParentTypeName  (void) 
    {
        return "Attachment"; 
    }
    static const OSG::Char8 *getGroupName       (void) { return "TestGenAtt"; }
    
    static OSG::InitContainerF     getInitMethod(void) { return NULL; }
    
    static OSG::FieldDescriptionBase **getDesc  (void) { return NULL; }
};

typedef OSG::DynFieldAttachment<TestAttDesc>  TestAtt;
typedef TestAtt::ObjTransitPtr                TestAttTransitPtr;
typedef TestAtt::ObjRecPtr                    TestAttRecPtr;
typedef TestAtt::ObjUnrecPtr                  TestAttUnrecPtr;
typedef TestAtt::ObjWeakPtr                   TestAttWeakPtr;

OSG_DYNFIELDATTACHMENT_INST(TestAttDesc)

OSG_END_NAMESPACE

SUITE(NodeTests)
{

TEST(CreateNode)
{
   OSG::NodeUnrecPtr n = OSG::Node::create();
   CHECK(n != NULL);
}

// --- Cloning --- //
TEST(TreeCloningName)
{
    OSG::NodeUnrecPtr root       = OSG::Node::create();
    OSG::NodeUnrecPtr child_node = OSG::Node::create();
    root->addChild(child_node);
    OSG::setName(root, "root");
    OSG::setName(child_node, "child_node");

    OSG::NodeUnrecPtr new_root = OSG::cloneTree(root);

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

    ~CloneFixture(void)
    {
        g01Core = NULL;
        s01Core = NULL;
        t01Core = NULL;
        g02Core = NULL;
        b01Core = NULL;
        g03Core = NULL;
        g04Core = NULL;
        b02Core = NULL;
        s02Core = NULL;
        g05Core = NULL;
        g06Core = NULL;

        g01Node = NULL;
        s01Node = NULL;
        t01Node = NULL;
        g02Node = NULL;
        b01Node = NULL;
        g03Node = NULL;
        g04Node = NULL;
        b02Node = NULL;
        s02Node = NULL;
        g05Node = NULL;
        g06Node = NULL;

        OSG::commitChanges();
    }

    OSG::GroupRecPtr     g01Core;
    OSG::SwitchRecPtr    s01Core;
    OSG::TransformRecPtr t01Core;
    OSG::GroupRecPtr     g02Core;
    OSG::BillboardRecPtr b01Core;
    OSG::GroupRecPtr     g03Core;
    OSG::GroupRecPtr     g04Core;
    OSG::BillboardRecPtr b02Core;
    OSG::SwitchRecPtr    s02Core;
    OSG::GroupRecPtr     g05Core;
    OSG::GroupRecPtr     g06Core;

    OSG::NodeRecPtr      g01Node;
    OSG::NodeRecPtr      s01Node;
    OSG::NodeRecPtr      t01Node;
    OSG::NodeRecPtr      g02Node;
    OSG::NodeRecPtr      b01Node;
    OSG::NodeRecPtr      g03Node;
    OSG::NodeRecPtr      g04Node;
    OSG::NodeRecPtr      b02Node;
    OSG::NodeRecPtr      s02Node;
    OSG::NodeRecPtr      g05Node;
    OSG::NodeRecPtr      g06Node;
};

TEST_FIXTURE(CloneFixture, CloneTree)
{
    // test cloneTree - all shared
    OSG::NodeUnrecPtr clone01 = OSG::cloneTree(g01Node);

    CHECK(clone01                                      != g01Node);
    CHECK(clone01->getCore()                           == g01Core);
    CHECK(clone01->getChild(0)->getCore()              == s01Core);
    CHECK(clone01->getChild(1)->getChild(0)->getCore() == g04Core);
    CHECK(clone01->getChild(2)->getCore()              == g02Core);

    // test cloneTree - clone Switch
    OSG::NodeUnrecPtr clone02 = OSG::cloneTree(g01Node, "Switch", "");

    CHECK(clone02->getCore()                           == g01Core);
    CHECK(clone02->getChild(0)->getCore()              != s01Core);
    CHECK(OSG::osgStringCmp(clone02->getChild(0)->getCore()->getType().getCName(),
                            "Switch")                  == 0      );
    CHECK(clone02->getChild(1)->getChild(0)->getCore() == g04Core);
    CHECK(clone02->getChild(2)->getCore()              == g02Core);

    // test cloneTree - clone Billboard, ignore Switch
    OSG::NodeUnrecPtr clone03 = OSG::cloneTree(g01Node, "Billboard", "Switch");

    CHECK(clone03->getCore() == g01Core);
    CHECK(clone03->getChild(0)->getChild(0)->getCore() != b01Core);
    CHECK(clone03->getChild(0)->getCore() == NULL);
    CHECK(clone03->getChild(2)->getChild(0)->getCore() != b02Core);
    CHECK(clone03->getChild(2)->getChild(1)->getCore() == NULL);
}

TEST_FIXTURE(CloneFixture, DeepCloneTree)
{
    // test deepCloneTree - all cloned
    OSG::NodeUnrecPtr clone01 = OSG::deepCloneTree(g01Node);

    CHECK(clone01                         != g01Node);
    CHECK(clone01->getCore()              != g01Core);
    CHECK(OSG::osgStringCmp(clone01->getCore()->getType().getCName(),
                            "Group")      == 0                       );
    CHECK(clone01->getChild(0)            != s01Node);
    CHECK(clone01->getChild(0)->getCore() != s01Core);
    CHECK(OSG::osgStringCmp(clone01->getChild(0)->getCore()->getType().getCName(),
                            "Switch")     == 0                                    );

    // test deepCloneTree - share Switch
    OSG::NodeUnrecPtr clone02 = OSG::deepCloneTree(g01Node, "Switch");

    CHECK(clone02->getCore()              != g01Core);
    CHECK(clone02->getChild(0)            != s01Node);
    CHECK(clone02->getChild(0)->getCore() == s01Core);

    // test deepCloneTree - share Billboard, ignore Switch
    OSG::NodeUnrecPtr clone03 = OSG::deepCloneTree(g01Node, "Billboard", "Switch");

    CHECK(clone03->getCore()                           != g01Core);
    CHECK(clone03->getChild(0)->getCore()              == NULL);
    CHECK(clone03->getChild(0)->getChild(0)->getCore() == b01Core);
    CHECK(clone03->getChild(2)->getChild(0)->getCore() == b02Core);
    CHECK(clone03->getChild(2)->getChild(1)->getCore() == NULL);
}

TEST(DynFieldAttachment)
{
    OSG::TestAttUnrecPtr pT = OSG::TestAtt::create();

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

    CHECK(pT != NULL);

    OSG::UInt32 fIndex = pT->addField(*pDesc);

    CHECK(fIndex != 0);

    OSG::GetFieldHandlePtr pFI = pT->getDynamicField(fIndex);

    CHECK(pFI != NULL);

    OSG::GetFieldHandlePtr pFN = pT->getDynamicFieldByName("foo");

    CHECK(pFN != NULL);

    CHECK(*pFN == *pFI);
}

} // SUITE
