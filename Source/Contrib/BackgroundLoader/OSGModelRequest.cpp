// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGVerifyGraphOp.h>

#include <OpenSG/OSGModelRequest.h>
#include <iostream>

OSG_USING_NAMESPACE
OSG_BEGIN_NAMESPACE

ModelRequest::ModelRequest()
   : mParent(NULL)
   , mModel (NULL)
{;}

ModelRequest::~ModelRequest()
{;}

std::string ModelRequest::getDescription()
{
   return std::string("ModelRequest: ") + mFilename;
}

void ModelRequest::execute()
{
   std::cout << "ModelRequest: loading model: " << mFilename << std::endl;
   mModel = OSG::NodeRefPtr(OSG::SceneFileHandler::the()->read(mFilename.c_str()));

#if 1
   VerifyGraphOpRefPtr vop = new VerifyGraphOp;
   vop->setRepair(true);
   vop->setVerbose(true);
   Node *node(mModel);
   vop->traverse(node);
#endif
}

void ModelRequest::sync()
{
   if (mParent && mModel)
   {
      std::cout << "ModelRequest: adding model to scene: " << mFilename << std::endl;
      mParent->addChild(mModel);
   }
   mCompleted = true;
}

OSG_END_NAMESPACE
