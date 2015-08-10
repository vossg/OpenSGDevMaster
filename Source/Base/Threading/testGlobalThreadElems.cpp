
#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wunused-variable"
#endif

#include "OSGBaseInitFunctions.h"
#include "OSGThreadManager.h"
#include "OSGThread.h"
#include "OSGBarrier.h"


//template<class ElemType>
//          void (OSG::ThreadManager::*RemoveElemF)(ElemType *) >
template<class ElemType>
void doIt(void)
{
    typedef OSG::RefCountPtr<ElemType, 
                             OSG::MemObjRefCountPolicy> ElemTypeRefPtr;

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    ElemTypeRefPtr pElem = ElemType::get("test1", true);

    fprintf(stderr, "%p \n", static_cast<void *>(pElem.get()));

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    OSG::ThreadManager::the()->remove(pElem);

    fprintf(stderr, "%p \n", static_cast<void *>(pElem.get()));

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    pElem = NULL;

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();


    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    pElem = ElemType::get("test1", false);

    fprintf(stderr, "%p \n", static_cast<void *>(pElem.get()));

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    OSG::ThreadManager::the()->remove(pElem);

    fprintf(stderr, "%p \n", static_cast<void *>(pElem.get()));

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    pElem = NULL;

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();


    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    pElem = ElemType::get("test1", true);

    fprintf(stderr, "%p \n", static_cast<void *>(pElem.get()));

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();


//    OSG::ThreadManager::the()->remove(pElem);

    pElem = NULL;

    fprintf(stderr, "%p \n", static_cast<void *>(pElem.get()));

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    pElem = ElemType::find("test1");

    fprintf(stderr, "%p \n", static_cast<void *>(pElem.get()));

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    OSG::ThreadManager::the()->remove(pElem);

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();

    pElem = NULL;

    fprintf(stderr, "====================================================\n");
    OSG::ThreadManager::the()->dump();
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    doIt<OSG::BaseThread>();
    doIt<OSG::Lock>();
    doIt<OSG::LockPool>();
    doIt<OSG::Barrier>();
    doIt<OSG::CondVar>();
    doIt<OSG::Semaphore>();

    doIt<OSG::Thread>();

    OSG::osgExit();
}
