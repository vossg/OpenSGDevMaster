#include <OpenSG/OSGBackgroundLoader.h>

#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGThreadManager.h>
#include <OpenSG/OSGLock.h>
#include <OpenSG/OSGCondVar.h>
#include <OpenSG/OSGBaseInitFunctions.h>
#include <boost/lexical_cast.hpp>
#include <OpenSG/OSGChangeList.h>
#include <boost/format.hpp>

#include <OpenSG/OSGSingletonHolder.ins>
OSG_USING_NAMESPACE
OSG_BEGIN_NAMESPACE
OSG_SINGLETON_INST(BackgroundLoaderBase)

BackgroundLoaderBase::BackgroundLoaderBase(void)
   : mLoadThreads()
   , mFinishedLock(NULL)
   , mLoadCondVar(NULL)
   , mStopRunning(false)
{
   mStopRunning = false;
   mFinishedLock = Lock::get("BackgroundLoader-FinishedLock");
   mLoadCondVar = CondVar::get("BackgroundLoader-CondVar");
}

BackgroundLoaderBase::~BackgroundLoaderBase(void)
{
   stop();
}

void BackgroundLoaderBase::stop(void)
{
   if (mLoadThreads.size() > 0)
   {
      OSG_ASSERT(!mStopRunning && "BackgroundLoaderBase::stop() Already stopped, but thread is not NULL");
      mStopRunning = true;
      mLoadCondVar->broadcast();

      for (std::vector<OSG::Thread*>::iterator itr = mLoadThreads.begin();
           itr != mLoadThreads.end(); itr++)
      {
         OSG::Thread::join(*itr);
         (*itr) = NULL;
      }
      mLoadThreads.clear();
   }
}

void BackgroundLoaderBase::addRequest(RequestPtr req)
{
   mLoadCondVar->acquire();
   mPendingRequests.push_back(req);
   mLoadCondVar->release();
   mLoadCondVar->signal();
}

void BackgroundLoaderBase::removeRequest(RequestPtr req)
{
   mLoadCondVar->acquire();
   request_queue_t::iterator found = std::find(mPendingRequests.begin(), mPendingRequests.end(), req);
   if (found != mPendingRequests.end())
   {
      mPendingRequests.erase(found);
   }
   mLoadCondVar->release();
   // XXX: We should not need this.
   mLoadCondVar->signal();
}

void BackgroundLoaderBase::start(const OSG::UInt16 numThreads)
{
   OSG_ASSERT(0 == mLoadThreads.size() && "Can't have threads before starting.");
   for (OSG::UInt16 i = 0; i < numThreads; i++)
   {
      OSG::Thread* new_thread = dynamic_cast<Thread *>(ThreadManager::the()->getThread(NULL));
      new_thread->runFunction((Thread::ThreadFuncF)loadProc, Thread::getCurrentAspect(), this);
      mLoadThreads.push_back(new_thread);
   }
}

void BackgroundLoaderBase::processOne()
{
   OSG_ASSERT(0 == mLoadThreads.size() && "processOne can not be called with background thread active.");

   mLoadCondVar->acquire();
   if (!mPendingRequests.empty())
   {
      OSG_ASSERT(!mPendingRequests.empty());

      // Get the pending request with the highest priority.
      RequestPtr req = RequestPtr();
      request_queue_t::iterator next_i = 
         std::min_element(mPendingRequests.begin(), mPendingRequests.end(), Request::comparePriority);
      req = *next_i;

      // Erase our request from the pending list.
      mPendingRequests.erase(next_i);

      if (NULL != req.get())
      {
         req->execute();
         OSG::commitChanges();

         mFinishedLock->acquire();
         mFinishedRequests.push_back(req);
         mFinishedLock->release();
      }
   }
   mLoadCondVar->release();
}

unsigned BackgroundLoaderBase::getNumPendingRequests()
{
   unsigned ret_val(0);
   mLoadCondVar->acquire();
   ret_val = mPendingRequests.size();
   mLoadCondVar->release();

   return ret_val;
}

BackgroundLoaderBase::desc_list_t BackgroundLoaderBase::getPendingDescriptionList()
{
   BackgroundLoaderBase::desc_list_t ret_list;

   mLoadCondVar->acquire();
   for(request_queue_t::iterator i = mPendingRequests.begin(); i!=mPendingRequests.end(); i++)
   {
      std::string desc = boost::str(boost::format("[%4.2f]: %s") % (*i)->getPriority() % (*i)->getDescription());
      ret_list.push_back(desc);
   }
   mLoadCondVar->release();

   return ret_list;
}

void BackgroundLoaderBase::loadProc(void* arg)
{
   // Get a pointer to the singleton object.
   BackgroundLoaderBase* the = reinterpret_cast<BackgroundLoaderBase*>(arg);
   OSG_ASSERT(NULL != the && "Should have a pointer to BackgroundLoader.");

   while(false == the->mStopRunning)
   {
      // Wait on a new request.
      the->mLoadCondVar->acquire();
      while(false == the->mStopRunning &&
            the->mPendingRequests.empty())
      {
         the->mLoadCondVar->wait();
      }

      // Early out if we are exiting the loop.
      if (the->mStopRunning)
      { continue; }

      OSG_ASSERT(!the->mPendingRequests.empty() && "Can't have empty pending list.");

      // Get the pending request with the highest priority.
      RequestPtr req = RequestPtr();
      request_queue_t::iterator next_i = 
         std::min_element(the->mPendingRequests.begin(), the->mPendingRequests.end(), Request::comparePriority);
      req = *next_i;

      // Erase our request from the pending list.
      the->mPendingRequests.erase(next_i);

      // Now that we have a request to process, release condition variable.
      the->mLoadCondVar->release();

      // If we have a valid request, execute it and commit changes.
      if (NULL != req.get())
      {
         try
         {
            req->execute();
            OSG::commitChanges();
         }
         catch (std::exception& ex)
         {
            std::cout << "ERROR: Exception thrown in execute: " << ex.what() << std::endl;
         }
         catch(...)
         {
            std::cout << "ERROR: Unknown exception thrown in execute." << std::endl;
         }

         // Commit our changes to our aspect (shared) and clear out change list 
         // since we don't need it around any more.
         // OSG::commitChanges();
         //OSG::Thread::getCurrentChangeList()->commitChangesAndClear();

         the->mFinishedLock->acquire();
         the->mFinishedRequests.push_back(req);
         the->mFinishedLock->release();
      }
   }
}

void BackgroundLoaderBase::sync(unsigned reqLimit)
{
   mFinishedLock->acquire();

   if (0 == reqLimit)
   { reqLimit = mFinishedRequests.size(); }

   while((!mFinishedRequests.empty()) && (reqLimit-- >= 0))
   {
      RequestPtr req = mFinishedRequests.front();
      mFinishedRequests.pop_front();

      try
      {
         req->sync();
      }
      catch (std::exception& ex)
      {
         std::cout << "ERROR: Exception thrown in sync: " << ex.what() << std::endl;
      }
      catch(...)
      {
         std::cout << "ERROR: Unknown exception thrown in sync." << std::endl;
      }

      req->mCompleted = true;
   }

   // XXX: Don't know if this is needed to keep the change list from growing out of control.
   //OSG::Thread::getCurrentChangeList()->commitChangesAndClear();
   mFinishedLock->release();
}

OSG_END_NAMESPACE
