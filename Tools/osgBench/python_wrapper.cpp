#include <boost/python.hpp>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>

#include <OpenSG/OSGGraphOp.h>
#include <OpenSG/OSGGraphOpFactory.h>
#include <OpenSG/OSGGraphOpSeq.h>

#include "Nodes.h"
#include "TestWindow.h"
#include "Test.h"


void doExit()
{
    OSG::osgExit();
}


OSG::GraphOp* createGraphOp(const char* name) 
{
    return OSG::GraphOpFactory::the().create(name);
}

OSG::GraphOpSeq* createGraphOpSeq(const char* ops) 
{
    OSG::GraphOpSeq *seq = new OSG::GraphOpSeq;
    
    seq->setGraphOps(ops);
    
    return seq;
}


void traverse(OSG::GraphOp& g, NodeBase& b) 
{
    OSG::NodePtr p = b.getNode();
    g.traverse(p);
}

void traverseSeq(OSG::GraphOpSeq& g, NodeBase& b) 
{
    OSG::NodePtr p = b.getNode();
    g.run(p);
}


BOOST_PYTHON_MODULE(osgbench)
{
    using namespace boost::python;

    class_<NodeBase>("NodeBase")
        .def("dump", &NodeBase::dump)
        .def("save", &NodeBase::save)
        .def("iter", &NodeBase::iter)
        .def("geometries", &NodeBase::geometries)
        .def("transforms", &NodeBase::transforms)
        .def("clone", &NodeBase::clone)
       ;
    
    class_<Group, bases<NodeBase> >("Group")
        .def("addChild", &Group::addChild)
        .def("subChild", &Group::subChild)
        ;
    
    class_<Transform, bases<Group> >("Transform")
        .def("setTranslation", &Transform::setTranslation)
        ;
    
    class_<Geometry, bases<NodeBase> >("Geometry")
        .def("translate", &Geometry::translate)
        .def("scale", &Geometry::scale)
        .def("setDlistCache", &Geometry::setDlistCache)
        ;
    
    class_<NodeIterator>("NodeIterator")
        .def("next", &NodeIterator::next)
        .def("__iter__", &NodeIterator::__iter__)
        ;
    
    class_<TypedNodeIterator<Geometry> >("GeometryNodeIterator")
        .def("next", &TypedNodeIterator<Geometry>::next)
        .def("__iter__", &TypedNodeIterator<Geometry>::__iter__)
        ;
    
    class_<TypedNodeIterator<Transform> >("TransformNodeIterator")
        .def("next", &TypedNodeIterator<Transform>::next)
        .def("__iter__", &TypedNodeIterator<Transform>::__iter__)
        ;
    
    class_<Image>("Image")
        .def("write", &Image::write)
        .def("clone", &Image::clone)
        .def("diff", &Image::diff)
        ;
    
    def("makeBox", &makeBox);      
    def("makeTorus", &makeTorus);   
    def("makeSphere", &makeSphere);   
    def("makePlane", &makePlane);   
    def("makeShared", &makeShared);   
    def("addRef", &addRef);   
    def("subRef", &subRef);   
    def("loadScene", &loadScene);   


    void (TestWindow::*twSetScene)(NodeBase&) = &TestWindow::setScene;
    void (TestWindow::*twSetCamera)(OSG::Real32,OSG::Real32,OSG::Real32,
                                    OSG::Real32,OSG::Real32,OSG::Real32,
                                    OSG::Real32,OSG::Real32,OSG::Real32) = 
                                    &TestWindow::setCamera;
    
    class_<TestWindow>("TestWindow")
        .def("setSize", &TestWindow::setSize)
        .def("setFullscreen", &TestWindow::setFullscreen)
        .def("setViewport", &TestWindow::setViewport)
        .def("getWidth", &TestWindow::getWidth)
        .def("getHeight", &TestWindow::getHeight)
        .def("getScene", &TestWindow::getScene)
        .def("setScene", twSetScene)
        .def("setCamera", twSetCamera)
        .def("open", &TestWindow::open)
        .def("close", &TestWindow::close)
        .def("redraw", &TestWindow::redraw)
        .def("setNearFar", &TestWindow::setNearFar)
        .def("setFov", &TestWindow::setFov)
        .def("showAll", &TestWindow::showAll)
      ;
    
    
    void (Test::*tSetScene)(NodeBase&) = &Test::setScene;
    void (Test::*taddFAU)
                    (OSG::Real32 fromx, OSG::Real32 fromy, OSG::Real32 fromz, 
                     OSG::Real32 atx,   OSG::Real32 aty,   OSG::Real32 atz, 
                     OSG::Real32 upx,   OSG::Real32 upy,   OSG::Real32 upz) 
                     = &Test::addFromAtUp;
                     
    class_<Test>("Test")
        .def("setScene", tSetScene)
        .def("setWindow", &Test::setWindow)
        .def("setHeadlight", &Test::setHeadlight)
        .def("setNearFar", &Test::setNearFar)
        .def("clear", &Test::clear)
        .def("setNFrames", &Test::setNFrames)
        .def("setMinTime", &Test::setMinTime)
        .def("addFromAtUp", taddFAU)
        .def("addFromOri", &Test::addFromOri)
        .def("makeOrbit", &Test::makeOrbit)
        .def("makePirouette", &Test::makePirouette)
        .def("addFov", &Test::addFov)
        .def("setStatistics", &Test::setStatistics)
        .def("run", &Test::run)
        .def("snapshot", &Test::snapshot)
        .def("getFPS", &Test::getFPS)
        .def("getTime", &Test::getTime)
        .def("getNRenderedFrames", &Test::getNRenderedFrames)
        .def("getStatValue", &Test::getStatValue)
        .def("setVerbose", &Test::setVerbose)
        .def("setIgnoreGeometry", &Test::setIgnoreGeometry)
        .def("useRenderTraversal", &Test::useRenderTraversal)
      ;

    class_<OSG::GraphOp, boost::noncopyable>("GraphOp", no_init)
        .def("traverse", &traverse)
        ;

    class_<OSG::GraphOpSeq, boost::noncopyable>("GraphOpSeq", no_init)
        .def("traverseSeq", &traverseSeq)
        ;

    def("createGraphOp", &createGraphOp,
        return_value_policy<manage_new_object>());

    def("createGraphOpSeq", &createGraphOpSeq,
        return_value_policy<manage_new_object>());
    
    // Module Initialization
    
    OSG::osgInit(0, NULL);
    
    Py_AtExit(doExit);
}
