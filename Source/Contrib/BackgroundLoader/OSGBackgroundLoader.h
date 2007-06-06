#ifndef _OSG_BACKGROUND_LOADER_H_
#define _OSG_BACKGROUND_LOADER_H_

#include <OpenSG/OSGContribBackgroundLoaderDef.h>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGSingletonHolder.h>
#include <OpenSG/OSGRequest.h>

#include <deque>

OSG_BEGIN_NAMESPACE

class CondVar;
class Lock;
class Thread;

/** Helper class that supports processing requests
 * such as loading files in a background thread.
 */
class OSG_CONTRIBBACKGROUNDLOADER_DLLMAPPING BackgroundLoaderBase
{
public:
   typedef std::vector<std::string> desc_list_t;

public:
   /**
    * Start load thread and start handling background requests.
    */
   void start(const OSG::UInt16 numThreads = 1);

   /**
    * Stop load thread and handling background requests.
    */
   void stop(void);

   /** Add a new request to the queue to be processed. */
   void addRequest(RequestPtr req);

   /** Request removal of an existing request.
    * If request is found, it is removed.
    */
   void removeRequest(RequestPtr req);

   /** Sync up with the background loader and it's pending changes.
    * @args reqLimit The max number of requests to process.  0-All
    */
   void sync(unsigned reqLimit=0);

   /** Process a single request.
    * This method can only be called if we are not running
    * in a background thread but instead want to run synchronously.
    */
   void processOne();

   /** Return the number of pending requests. */
   unsigned    getNumPendingRequests();

   /** Return a list of the descriptions of all pending requests. */
   desc_list_t getPendingDescriptionList();

protected:
   //void workerThread(void *);
   //void renderThread(void *);
   BackgroundLoaderBase(void);
   virtual ~BackgroundLoaderBase(void); 

   static void loadProc(void* arg);

private:
   template <class SingletonT>
   friend class SingletonHolder;
   /** default function (move to 'public' if needed). */
   BackgroundLoaderBase(const BackgroundLoaderBase &source);
   /** \brief prohibit default function (move to 'public' if needed) */
   void operator =(const BackgroundLoaderBase &source);

   typedef std::list<RequestPtr> request_queue_t;
   request_queue_t      mPendingRequests;
   request_queue_t      mFinishedRequests;
   std::vector<Thread*> mLoadThreads;
   Lock*                mFinishedLock;
   CondVar*             mLoadCondVar;           // Cond var to protect the request queue
   bool                 mStopRunning;
};

typedef SingletonHolder<BackgroundLoaderBase> BackgroundLoader;

OSG_END_NAMESPACE

#endif /*_OSG_BACKGROUND_LOADER_H_*/
