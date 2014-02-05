// the general scene file loading handler
#include "OSGSceneFileHandler.h"
#include "OSGVerifyGraphOp.h"

#include "OSGModelRequest.h"
#include "OSGGraphOpSeq.h"

#include <iostream>

OSG_BEGIN_NAMESPACE

ModelRequest::ModelRequest(void) : 
    mParent     (NULL     ),
    mModel      (NULL     ),
    mFilename   (         ),
    pChangeList (NULL     ),
    bVerifyModel(true     ),
    szGraphOp   ("default")
{
}

ModelRequest::~ModelRequest(void)
{
    mParent     = NULL;
    mModel      = NULL;
    pChangeList = NULL;
}

std::string ModelRequest::getDescription(void)
{
   return std::string("ModelRequest: ") + mFilename;
}

void ModelRequest::execute(void)
{
   std::cout << "ModelRequest: loading model: " << mFilename << std::endl;

   GraphOpSeqRefPtr pGraphOp = NULL;
        
   if(szGraphOp.compare("none") == 0)
   {
       // leave it NULL
   }
   else if(szGraphOp.compare("default") == 0)
   {
       pGraphOp = SceneFileHandler::the()->getDefaultGraphOp();
   }
   else
   {
       pGraphOp = GraphOpSeq::create(szGraphOp);
   }
   
   fprintf(stderr, "Using graphop %p\n", pGraphOp.get());

   mModel = SceneFileHandler::the()->read(mFilename.c_str(),
                                          pGraphOp         );

   if(bVerifyModel == true)
   {
       std::cout << "verify model" << std::endl;

       VerifyGraphOpRefPtr vop = VerifyGraphOp::create();
       
       vop->setRepair (true);
       vop->setVerbose(true);
       
       vop->traverse(mModel.get());
   }

   commitChanges();

   pChangeList->merge(*Thread::getCurrentChangeList());

   clearChangeList();
}

void ModelRequest::sync(void)
{
   if (mParent != NULL && mModel != NULL)
   {
      std::cout << "ModelRequest: adding model to scene: " 
                << mFilename 
                << std::endl; 

      mParent->addChild(mModel);

      Thread::getCurrentChangeList()->merge(*pChangeList);
   }

   mCompleted = true;
}

void ModelRequest::setVerifyModel(bool bVal)
{
    bVerifyModel = bVal;
}

void ModelRequest::setGraphOp(const std::string &szVal)
{
    szGraphOp = szVal;
}

OSG_END_NAMESPACE
