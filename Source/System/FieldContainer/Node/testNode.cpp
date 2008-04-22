
#include <OSGBaseInitFunctions.h>
#include <OSGNode.h>
#include <OSGNameAttachment.h>
#include <OSGDynamicAttachmentMixin.h>

OSG_BEGIN_NAMESPACE

struct TestAttDesc
{
    typedef OSG::Attachment    Parent;
    typedef OSG::AttachmentPtr ParentPtr;
    
    // TODO rename it to VRMLGenericAtt ????
    static const OSG::Char8 *getTypeName        (void) { return "TestAtt";    }
    static const OSG::Char8 *getParentTypeName  (void) 
    {
        return "Attachment"; 
    }
    static const OSG::Char8 *getGroupName       (void) { return "TestGenAtt"; }
    
    static OSG::InitContainerF     getInitMethod(void) { return NULL; }
    
    static OSG::FieldDescriptionBase **getDesc  (void) { return NULL; }
};

typedef OSG::DynFieldAttachment<TestAttDesc>  TestAtt;
typedef TestAtt::ObjPtr                       TestAttPtr;
typedef TestAtt::ObjRecPtr                    TestAttRecPtr;

OSG_DYNFIELDATTACHMENT_INST(TestAttDesc)

OSG_END_NAMESPACE

int main(int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::TestAttRecPtr tp = OSG::TestAtt::create();

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

    OSG::Attachment::getClassType().dump();
    OSG::TestAtt::getClassType().dump();
    tp->getType().dump();

    OSG::SFUnrecNodePtr::getClassType().dump();
    OSG::MFUnrecNodePtr::getClassType().dump();

    OSG::SFUnrecFieldContainerPtr::getClassType().dump();
    OSG::MFUnrecFieldContainerPtr::getClassType().dump();

    tp = NullFC;

    return 0;
}
