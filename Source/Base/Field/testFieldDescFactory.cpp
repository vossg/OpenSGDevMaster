
#include "stdio.h"
#include "OSGNode.h"
#include "OSGBaseInitFunctions.h"
#include "OSGFieldDescFactory.h"
#include "OSGBaseSFields.h"
#include "OSGBaseMFields.h"

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

//    fprintf(stderr, "%d field types\n");

    for(OSG::UInt32 i = 0; 
                    i < OSG::FieldDescFactory::the()->getNumFieldTypes(); 
                  ++i                                                   )
    {
//        fprintf(stderr, "Field
    }

    OSG::FieldDescriptionBase *pDesc = 
        OSG::FieldDescFactory::the()->createByNameIdx(
            NULL,
            NULL,
            NULL,
            NULL);

    pDesc = OSG::FieldDescFactory::the()->createByNameIdx(
        "SFUInt32",
        "myfield",
        NULL,
        NULL);
    
    fprintf(stderr, "got %p\n", static_cast<void *>(pDesc));

    if(pDesc != NULL)
    {
        pDesc->getFieldType().dump();
    }

    pDesc = OSG::FieldDescFactory::the()->createByNameIdx(
        "MFUInt32",
        "myfield",
        NULL,
        NULL);

    fprintf(stderr, "got %p\n", static_cast<void *>(pDesc));

    if(pDesc != NULL)
    {
        pDesc->getFieldType().dump();
    }


    pDesc = OSG::FieldDescFactory::the()->createIdx(
        OSG::SFUInt32::getClassType().getId(),
        "myfield",
        NULL,
        NULL);
    
    fprintf(stderr, "got %p\n", static_cast<void *>(pDesc));

    if(pDesc != NULL)
    {
        pDesc->getFieldType().dump();
    }

    pDesc = OSG::FieldDescFactory::the()->createIdx(
        OSG::MFUInt32::getClassType().getId(),
        "myfield",
        NULL,
        NULL);

    fprintf(stderr, "got %p\n", static_cast<void *>(pDesc));

    if(pDesc != NULL)
    {
        pDesc->getFieldType().dump();
    }



    pDesc = OSG::FieldDescFactory::the()->createIdx(
        OSG::SFUnrecFieldContainerPtr::getClassType().getId(),
        "myfield",
        NULL,
        NULL);
    
    fprintf(stderr, "got %p\n", static_cast<void *>(pDesc));

    if(pDesc != NULL)
    {
        pDesc->getFieldType().dump();
    }

    pDesc = OSG::FieldDescFactory::the()->createIdx(
        OSG::MFUnrecFieldContainerPtr::getClassType().getId(),
        "myfield",
        NULL,
        NULL);

    fprintf(stderr, "got %p\n", static_cast<void *>(pDesc));

    if(pDesc != NULL)
    {
        pDesc->getFieldType().dump();
    }


    OSG::osgExit();

    return 0;
}
