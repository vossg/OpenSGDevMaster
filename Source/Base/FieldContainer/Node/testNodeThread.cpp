
#include "OSGBaseInitFunctions.h"
#include "OSGNode.h"

#ifdef OSG_USE_PTHREADS
#include <pthread.h>

pthread_t oThread;

void *runThread(void *)
{
    fprintf(stderr, "run thread \n");

    fprintf(stderr, "th : %p %p %d 0x%016"PRIx64" 0x%016"PRIx64"\n",
            OSG::Thread::getCurrentChangeList   (),
            OSG::Thread::getCurrent             (),
            OSG::Thread::getCurrentAspect       (),
            OSG::Thread::getCurrentNamespaceMask(),
            OSG::Thread::getCurrentLocalFlags   ());

    fprintf(stderr, "th : %p %p %d 0x%016"PRIx64" 0x%016"PRIx64"\n",
            OSG::Thread::getCurrentChangeList   (),
            OSG::Thread::getCurrent             (),
            OSG::Thread::getCurrentAspect       (),
            OSG::Thread::getCurrentNamespaceMask(),
            OSG::Thread::getCurrentLocalFlags   ());
            
    OSG::NodeUnrecPtr pNode1 = OSG::Node::create();

    OSG::NodeUnrecPtr pNode2 = OSG::Node::create();
    OSG::NodeUnrecPtr pNode3 = OSG::Node::create();

    pNode1->addChild(pNode2);
    pNode1->addChild(pNode3);

    fprintf(stderr, "exit thread\n");

    return NULL;
}

void runThread1(void *)
{
    fprintf(stderr, "run thread \n");

    fprintf(stderr, "th : %p %p %d 0x%016"PRIx64" 0x%016"PRIx64"\n",
            OSG::Thread::getCurrentChangeList   (),
            OSG::Thread::getCurrent             (),
            OSG::Thread::getCurrentAspect       (),
            OSG::Thread::getCurrentNamespaceMask(),
            OSG::Thread::getCurrentLocalFlags   ());

    fprintf(stderr, "th : %p %p %d 0x%016"PRIx64" 0x%016"PRIx64"\n",
            OSG::Thread::getCurrentChangeList   (),
            OSG::Thread::getCurrent             (),
            OSG::Thread::getCurrentAspect       (),
            OSG::Thread::getCurrentNamespaceMask(),
            OSG::Thread::getCurrentLocalFlags   ());
            
    OSG::NodeUnrecPtr pNode1 = OSG::Node::create();

    OSG::NodeUnrecPtr pNode2 = OSG::Node::create();
    OSG::NodeUnrecPtr pNode3 = OSG::Node::create();

    pNode1->addChild(pNode2);
    pNode1->addChild(pNode3);

    fprintf(stderr, "exit thread\n");
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

#ifdef OSG_ENABLE_AUTOINIT_THREADS
    OSG::Thread::setFallbackAspectId(42);
#endif

#ifdef OSG_ENABLE_AUTOINIT_THREADS
    pthread_create(&oThread, NULL, runThread, NULL);

    pthread_join(oThread, NULL);
#endif

#if 1
    OSG::Thread *pThread = OSG::Thread::get(NULL);

    pThread->runFunction(runThread1, 0, NULL);

    OSG::Thread::join(pThread);

    OSG::subRef(pThread);
#endif
    OSG::osgExit();

    return 0;
}

#endif

#ifdef OSG_USE_WINTHREADS

OSG::Handle oThread;

void *runThread(void *)
{
    fprintf(stderr, "run thread \n");

#if 1
    fprintf(stderr, "%d ",
            OSG::Thread::getCurrentAspect       ());

    fprintf(stderr, "th : T:%p ",
            OSG::Thread::getCurrent             ());
    fprintf(stderr, "CL:%p ",
            OSG::Thread::getCurrentChangeList   ());

    fprintf(stderr, "0x%016"PRIx64" ",
            OSG::Thread::getCurrentNamespaceMask());

    fprintf(stderr, "0x%016"PRIx64"\n",
            OSG::Thread::getCurrentLocalFlags   ());
            
    OSG::NodeUnrecPtr pNode1 = OSG::Node::create();

    OSG::NodeUnrecPtr pNode2 = OSG::Node::create();
    OSG::NodeUnrecPtr pNode3 = OSG::Node::create();

    pNode1->addChild(pNode2);
    pNode1->addChild(pNode3);
#endif

    fprintf(stderr, "exit thread\n");

    return NULL;
}

void runThread1(void *)
{
    fprintf(stderr, "run thread \n");

    fprintf(stderr, "th : CL:%p T:%p %d 0x%016"PRIx64" 0x%016"PRIx64"\n",
            OSG::Thread::getCurrentChangeList   (),
            OSG::Thread::getCurrent             (),
            OSG::Thread::getCurrentAspect       (),
            OSG::Thread::getCurrentNamespaceMask(),
            OSG::Thread::getCurrentLocalFlags   ());

    fprintf(stderr, "th : CL:%p T:%p %d 0x%016"PRIx64" 0x%016"PRIx64"\n",
            OSG::Thread::getCurrentChangeList   (),
            OSG::Thread::getCurrent             (),
            OSG::Thread::getCurrentAspect       (),
            OSG::Thread::getCurrentNamespaceMask(),
            OSG::Thread::getCurrentLocalFlags   ());
            
    OSG::NodeUnrecPtr pNode1 = OSG::Node::create();

    OSG::NodeUnrecPtr pNode2 = OSG::Node::create();
    OSG::NodeUnrecPtr pNode3 = OSG::Node::create();

    pNode1->addChild(pNode2);
    pNode1->addChild(pNode3);

    fprintf(stderr, "exit thread\n");
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

#ifdef OSG_ENABLE_AUTOINIT_THREADS
    OSG::Thread::setFallbackAspectId(42);
#endif

#ifdef OSG_ENABLE_AUTOINIT_THREADS
    OSG::DWord  tmp;

    OSG::Handle rc = CreateThread(NULL,
                                  0,
                                  (LPTHREAD_START_ROUTINE) runThread,
                                  0,
                                  0,
                                  &tmp);
    
    WaitForSingleObject(rc, INFINITE);
#endif

#if 1
    OSG::Thread *pThread = OSG::Thread::get(NULL);

    pThread->runFunction(runThread1, 0, NULL);

    OSG::Thread::join(pThread);

    OSG::subRef(pThread);
#endif
    OSG::osgExit();

    return 0;
}

#endif
