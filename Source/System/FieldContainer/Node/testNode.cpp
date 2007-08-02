
#include <OSGBaseInitFunctions.h>
#include <OSGNode.h>
#include <OSGNameAttachment.h>
#include <OSGDynamicAttachmentMixin.h>

OSG_BEGIN_NAMESPACE

struct TestAttDesc
{
    typedef OSG::FieldContainerAttachment    Parent;
    typedef OSG::FieldContainerAttachmentPtr ParentPtr;
    
    // TODO rename it to VRMLGenericAtt ????
    static const OSG::Char8 *getTypeName        (void) { return "TestAtt";    }
    static const OSG::Char8 *getParentTypeName  (void) 
    {
        return "FieldContainerAttachment"; 
    }
    static const OSG::Char8 *getGroupName       (void) { return "TestGenAtt"; }
    
    static OSG::InitContainerF     getInitMethod(void) { return NULL; }
    
    static OSG::FieldDescriptionBase **getDesc  (void) { return NULL; }
};

typedef OSG::DynFieldAttachment<TestAttDesc>  TestAtt;
typedef TestAtt::ObjPtr                       TestAttPtr;

OSG_DYNFIELDATTACHMENT_INST(TestAttDesc)

OSG_END_NAMESPACE

int main(int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::TestAttPtr tp = OSG::TestAtt::create();

    OSG::FieldDescriptionBase *pDesc = NULL;

    pDesc = new OSG::SFInt32::Description(
        OSG::SFInt32::getClassType(),
        "foo",
        "bar",
        0, 
        0,
        false,
        OSG::Field::SFDefaultFlags,
        static_cast<OSG::FieldIndexEditMethodSig>(
            &OSG::TestAtt::editDynamicField),
        static_cast<OSG::FieldIndexGetMethodSig >(
            &OSG::TestAtt::getDynamicField ));

    
//    CHECK(tp != OSG::NullFC);

    OSG::UInt32 fIndex = tp->addField(*pDesc);

//    CHECK(fIndex != 0);

    OSG::GetFieldHandlePtr pFI = tp->getDynamicField(fIndex);

//    CHECK(pFI != NULL);

    OSG::GetFieldHandlePtr pFN = tp->getDynamicFieldByName("foo");

//    CHECK(pFI != NULL);

    OSG::FieldContainerAttachment::getClassType().dump();
    OSG::TestAtt::getClassType().dump();
    tp->getType().dump();

    OSG::SFNodePtr::getClassType().dump();
    OSG::MFNodePtr::getClassType().dump();

    OSG::SFFieldContainerPtr::getClassType().dump();
    OSG::MFFieldContainerPtr::getClassType().dump();

    return 0;
}
