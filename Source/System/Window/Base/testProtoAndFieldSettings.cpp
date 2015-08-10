
#include "OSGBaseFunctions.h"
#include "OSGMatrixCamera.h"
#include "OSGNodeCore.h"
#include "OSGGroup.h"
#include "OSGComponentTransform.h"

void testClassType(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "create marking class type\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCamera::getClassType().setFieldsUnmarkedOnCreate(
        OSG::MatrixCamera::BeaconFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCamera::getClassType().clearFieldsUnmarkedOnCreate(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCamera::getClassType().clearFieldsUnmarkedOnCreate(
        OSG::MatrixCamera::BeaconFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "cluster local class type\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCamera::getClassType().markFieldsClusterLocal(
        OSG::MatrixCamera::BeaconFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCamera::getClassType().unmarkFieldsClusterLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCamera::getClassType().unmarkFieldsClusterLocal(
        OSG::MatrixCamera::BeaconFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();


    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "thread local class type\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCamera::getClassType().markFieldsThreadLocal(
        OSG::MatrixCamera::BeaconFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCamera::getClassType().unmarkFieldsThreadLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCamera::getClassType().unmarkFieldsThreadLocal(
        OSG::MatrixCamera::BeaconFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    fprintf(stderr, "\n\n");
}

void testCreateMarking(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "create marking container\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCameraUnrecPtr pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    OSG::MatrixCamera::getClassType().setFieldsUnmarkedOnCreate(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pCam1 = NULL;

    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    OSG::MatrixCamera::getClassType().clearFieldsUnmarkedOnCreate(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    fprintf(stderr, "\n\n");
}

void testClusterLocalType(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "cluster local container/type\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCameraUnrecPtr pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    OSG::MatrixCamera::getClassType().markFieldsClusterLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    OSG::MatrixCamera::getClassType().unmarkFieldsClusterLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    fprintf(stderr, "\n\n");
}

void testThreadLocalType(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "thread local container/type\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCameraUnrecPtr pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    OSG::MatrixCamera::getClassType().markFieldsThreadLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    OSG::MatrixCamera::getClassType().unmarkFieldsThreadLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    fprintf(stderr, "\n\n");
}
  
void testClusterLocalContainer(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "cluster local container/container\n");
    fprintf(stderr, "====================================================\n");


    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "A|\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCameraUnrecPtr pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1->markFieldsClusterLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    pCam1->dumpFieldInfo();
    
    pCam1 = NULL;

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "B|\n");
    fprintf(stderr, "====================================================\n");

    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1->markFieldsClusterLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    pCam1->dumpFieldInfo();

    pCam1->unmarkFieldsClusterLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "C|\n");
    fprintf(stderr, "====================================================\n");


    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    fprintf(stderr, "\n\n");
}

void testThreadLocalContainer(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "thread local container/container\n");
    fprintf(stderr, "====================================================\n");


    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "A|\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    OSG::MatrixCameraUnrecPtr pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1->markFieldsThreadLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    pCam1->dumpFieldInfo();
    
    pCam1 = NULL;

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "B|\n");
    fprintf(stderr, "====================================================\n");

    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1->markFieldsThreadLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    pCam1->dumpFieldInfo();

    pCam1->unmarkFieldsThreadLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "C|\n");
    fprintf(stderr, "====================================================\n");


    pCam1 = OSG::MatrixCamera::create();

    pCam1->dumpFieldInfo();

    pCam1 = NULL;

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    fprintf(stderr, "\n\n");
}

void testPrototypeReplacement(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "replace proto\n");
    fprintf(stderr, "====================================================\n");

    OSG::FieldContainer *pNCProto = 
        OSG::NodeCore::getClassType().getPrototype();

    fprintf(stderr, "node core proto %p\n", static_cast<void *>(pNCProto));

    OSG::FieldContainer *pMCProto =
        OSG::MatrixCamera::getClassType().getPrototype();

    fprintf(stderr, "matrix cam proto %p\n", static_cast<void *>(pMCProto));


    OSG::GroupUnrecPtr        pGroup     = OSG::Group       ::create();
    OSG::MatrixCameraUnrecPtr pMatrixCam = OSG::MatrixCamera::create();

    fprintf(stderr, "tmp group ptr %p | tmp matrix cam ptr %p\n",
            static_cast<void *>(pGroup.get()),
            static_cast<void *>(pMatrixCam.get()));
            

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "replace abstract proto\n");
    fprintf(stderr, "====================================================\n");

    bool rc = OSG::NodeCore::getClassType().setPrototype(pGroup);

    fprintf(stderr, "set proto result %d\n", rc);

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "remove proto\n");
    fprintf(stderr, "====================================================\n");

    rc = OSG::MatrixCamera::getClassType().setPrototype(NULL);

    fprintf(stderr, "set proto result %d\n", rc);

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "set incompatible proto\n");
    fprintf(stderr, "====================================================\n");

    rc = OSG::MatrixCamera::getClassType().setPrototype(pGroup);

    fprintf(stderr, "set proto result %d\n", rc);
    

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "check\n");
    fprintf(stderr, "====================================================\n");

    pMCProto = OSG::MatrixCamera::getClassType().getPrototype();

    fprintf(stderr, "matrix cam proto %p\n", static_cast<void *>(pMCProto));

    OSG::MatrixCameraUnrecPtr pNewMatrixCam = OSG::MatrixCamera::create();

    fprintf(stderr, "new matrix cam ptr %p\n", 
            static_cast<void *>(pNewMatrixCam.get()));

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "set same type proto\n");
    fprintf(stderr, "====================================================\n");

    rc = OSG::MatrixCamera::getClassType().setPrototype(pMatrixCam);

    fprintf(stderr, "set proto result %d\n", rc);
    
    pMCProto = OSG::MatrixCamera::getClassType().getPrototype();

    fprintf(stderr, "matrix cam proto %p\n", static_cast<void *>(pMCProto));

    pNewMatrixCam = OSG::MatrixCamera::create();

    fprintf(stderr, "new matrix cam ptr %p\n", 
            static_cast<void *>(pNewMatrixCam.get()));

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "set derived type proto\n");
    fprintf(stderr, "====================================================\n");

    OSG::ComponentTransformUnrecPtr pCTr = OSG::ComponentTransform::create();

    fprintf(stderr, "comp tr ptr %p\n", static_cast<void *>(pCTr.get()));

    rc = OSG::Transform::getClassType().setPrototype(pCTr);

    fprintf(stderr, "set proto result %d\n", rc);
    
    pMCProto = OSG::Transform::getClassType().getPrototype();

    fprintf(stderr, "transform proto %p\n", static_cast<void *>(pMCProto));

    OSG::TransformUnrecPtr pTr = OSG::Transform::create();

    fprintf(stderr, "new tr ptr %p", static_cast<void *>(pTr.get()));

    if(pTr != NULL)
    {
        fprintf(stderr, "new tr type %s\n", pTr->getType().getCName());
    }

    pGroup        = NULL;
    pMatrixCam    = NULL;
    pNewMatrixCam = NULL;
    pCTr          = NULL;
    pTr           = NULL;
}


void testPrototypeReplacementWithFlags(void)
{
    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "replace proto with flags\n");
    fprintf(stderr, "====================================================\n");

    OSG::FieldContainer *pMCProto =
        OSG::MatrixCamera::getClassType().getPrototype();

    fprintf(stderr, "matrix cam proto %p\n", static_cast<void *>(pMCProto));


    OSG::MatrixCameraUnrecPtr pMatrixCam = OSG::MatrixCamera::create();
    OSG::UInt32               rc         = 0;

    fprintf(stderr, "tmp matrix cam ptr %p\n",
            static_cast<void *>(pMatrixCam.get()));


    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pMatrixCam->dumpFieldInfo();

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "A|\n");
    fprintf(stderr, "====================================================\n");

    OSG::MatrixCameraUnrecPtr pNewMatrixCam = OSG::MatrixCamera::create();

    fprintf(stderr, "new matrix cam ptr %p\n", 
            static_cast<void *>(pNewMatrixCam.get()));

    pNewMatrixCam->markFieldsThreadLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    pNewMatrixCam->markFieldsClusterLocal(
        OSG::MatrixCamera::NearFieldMask |
        OSG::MatrixCamera::ProjectionMatrixFieldMask);

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pNewMatrixCam->dumpFieldInfo();

    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "set same type proto\n");
    fprintf(stderr, "====================================================\n");

    rc = OSG::MatrixCamera::getClassType().setPrototype(pNewMatrixCam);

    fprintf(stderr, "set proto result %d\n", rc);
    
    pMCProto = OSG::MatrixCamera::getClassType().getPrototype();

    fprintf(stderr, "matrix cam proto %p\n", static_cast<void *>(pMCProto));

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pNewMatrixCam->dumpFieldInfo();
    pMCProto->dumpFieldInfo();


    fprintf(stderr, "====================================================\n");
    fprintf(stderr, "B|\n");
    fprintf(stderr, "====================================================\n");

    pNewMatrixCam = OSG::MatrixCamera::create();

    fprintf(stderr, "new matrix cam ptr %p\n", 
            static_cast<void *>(pNewMatrixCam.get()));

    OSG::MatrixCamera::getClassType().dumpFieldInfo();

    pNewMatrixCam->dumpFieldInfo();

    pMatrixCam    = NULL;
    pNewMatrixCam = NULL;
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

//    testClassType();
//    testCreateMarking();
//    testClusterLocalType();
//    testThreadLocalType();
//    testClusterLocalContainer();
//    testThreadLocalContainer();
//    testPrototypeReplacement();
    testPrototypeReplacementWithFlags();

    OSG::osgExit();

    return 0;
}

    
