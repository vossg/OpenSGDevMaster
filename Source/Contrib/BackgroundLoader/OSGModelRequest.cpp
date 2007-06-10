// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGVerifyGraphOp.h>

#include <OpenSG/OSGModelRequest.h>
#include <iostream>

OSG_USING_NAMESPACE
OSG_BEGIN_NAMESPACE

ModelRequest::ModelRequest()
   : mParent(NullFC)
   , mModel (NullFC)
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
   VerifyGraphOp* vop = new VerifyGraphOp;
   vop->setRepair(true);
   vop->setVerbose(true);
   NodePtr node(mModel);
   vop->traverse(node);
   delete vop;
#endif
}

void ModelRequest::sync()
{
   if (mParent != NullFC && mModel != NullFC)
   {
      std::cout << "ModelRequest: adding model to scene: " << mFilename << std::endl;
      mParent->addChild(mModel);
   }
   mCompleted = true;
}

OSG_END_NAMESPACE
