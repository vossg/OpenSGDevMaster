
#include "OSGMultiCore.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGPointLight.h"
#include "OSGNode.h"
#include "OSGSceneFileHandler.h"

#include "OSGBaseInitFunctions.h"

int main(int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::NodeUnrecPtr pNode = OSG::Node::create();

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo.osg");

    OSG::GroupUnrecPtr pGr = OSG::Group::create();
    OSG::addCoreToNode(pNode, pGr);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo1.osg");

    OSG::addCoreToNode(pNode, pGr);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo1a.osg");


    OSG::TransformUnrecPtr pTr = OSG::Transform::create();

    OSG::addCoreToNode(pNode, pTr);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo2.osg");

    OSG::addCoreToNode(pNode, pTr);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo2a.osg");

    OSG::subCoreFromNode(pNode, pTr);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo3.osg");

    OSG::addCoreToNode(pNode, pTr);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo4.osg");

    OSG::subCoreFromNode(pNode, pTr, false);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo5.osg");
    
    OSG::subCoreFromNode(pNode, pGr);

    OSG::SceneFileHandler::the()->write(pNode, "/tmp/mcore/foo6.osg");

    pNode = NULL;

    return 0;
}
