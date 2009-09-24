
#include "OSGConfig.h"

#include "OSGAnimation.h"
#include "OSGAnimKeyFrameTemplate.h"
#include "OSGAnimVec3fChannel.h"
#include "OSGAnimVec3fDataSource.h"
#include "OSGAnimTimeSensor.h"

OSG_USING_NAMESPACE

void testAnimTemplate(void)
{
    AnimKeyFrameTemplateUnrecPtr at   = AnimKeyFrameTemplate::create();
    AnimVec3fDataSourceUnrecPtr  src0 = AnimVec3fDataSource ::create();
    AnimVec3fDataSourceUnrecPtr  src1 = AnimVec3fDataSource ::create();

    src0->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    src0->editMFInValues()->push_back(0.f);
    src0->editMFInValues()->push_back(1.f);
    src0->editMFInValues()->push_back(3.f);

    src0->editMFValues()->push_back(Vec3f(0.f, 0.f, 0.f));
    src0->editMFValues()->push_back(Vec3f(1.f, 0.f, 0.f));
    src0->editMFValues()->push_back(Vec3f(1.f, 2.f, 0.f));


    src1->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    src1->editMFInValues()->push_back(1.f );
    src1->editMFInValues()->push_back(2.f );
    src1->editMFInValues()->push_back(2.5f);
    src1->editMFInValues()->push_back(4.f );

    src1->editMFValues()->push_back(Vec3f(0.f, 1.f, 0.f));
    src1->editMFValues()->push_back(Vec3f(0.f, 0.f, 1.f));
    src1->editMFValues()->push_back(Vec3f(1.f, 0.f, 1.f));
    src1->editMFValues()->push_back(Vec3f(2.f, 2.f, 2.f));


    at->editMFSources  ()->push_back(src0);
    at->editMFTargetIds()->push_back("xform0.translate");


    at->editMFSources  ()->push_back(src1);
    at->editMFTargetIds()->push_back("xform0.scale");

    commitChanges();
}


void testAnim(void)
{
    AnimVec3fDataSourceUnrecPtr src0 = AnimVec3fDataSource::create();
    AnimVec3fDataSourceUnrecPtr src1 = AnimVec3fDataSource::create();

    src0->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    src0->editMFInValues()->push_back(0.f);
    src0->editMFInValues()->push_back(1.f);
    src0->editMFInValues()->push_back(3.f);

    src0->editMFValues()->push_back(Vec3f(0.f, 0.f, 0.f));
    src0->editMFValues()->push_back(Vec3f(1.f, 0.f, 0.f));
    src0->editMFValues()->push_back(Vec3f(1.f, 2.f, 0.f));

    
    src1->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    src1->editMFInValues()->push_back(1.f );
    src1->editMFInValues()->push_back(2.f );
    src1->editMFInValues()->push_back(2.5f);
    src1->editMFInValues()->push_back(4.f );

    src1->editMFValues()->push_back(Vec3f(0.f, 1.f, 0.f));
    src1->editMFValues()->push_back(Vec3f(0.f, 0.f, 1.f));
    src1->editMFValues()->push_back(Vec3f(1.f, 0.f, 1.f));
    src1->editMFValues()->push_back(Vec3f(2.f, 2.f, 2.f));


    AnimationUnrecPtr        a  = Animation::create();
    AnimVec3fChannelUnrecPtr c0 = AnimVec3fChannel::create();
    AnimVec3fChannelUnrecPtr c1 = AnimVec3fChannel::create();
    AnimTimeSensorUnrecPtr   t  = AnimTimeSensor::create();

    c0->setData(src0);
    c1->setData(src1);

    a->editMFChannels()->push_back(c0);
    a->editMFChannels()->push_back(c1);

    a->setTimeSensor(t);

    commitChanges();
}


int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    std::cout << "testAnimTemplate" << std::endl;
    testAnimTemplate();

    std::cout << "testAnim" << std::endl;
    testAnim();

    osgExit();

    return 0;
}
