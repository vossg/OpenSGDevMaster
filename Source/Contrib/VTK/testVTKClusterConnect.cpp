
#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

// testDynamicClusterClient2
//
// OpenSG cluster client program where you can dynamicly connect/disconnect
// to the servers.
// It is similar to testDynamicClusterClient but this time we create from the
// current state a changelist and send this to the cluster servers.
// This variant is much easier to implement in your own app but could be
// problematic if you use more than one aspect in your app.

// To test it, run 
//   ./testClusterServer -w pipe0 &
//   ./testDynamicClusterClient2 pipe0
//
// press 'c' to connect to the servers and 'd' to disconnect. 


#include "OSGConfig.h"

#ifdef OSG_WITH_VTK

#include "OSGGLUT.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGMultiDisplayWindow.h"
#include "OSGSceneFileHandler.h"
#include "OSGRemoteAspect.h"
#include "OSGFieldContainerFactory.h"

#include "OSGVTKPolyDataMapper.h"

#include "vtkStructuredGridReader.h"
#include "vtkStructuredGrid.h"
#include "vtkPointData.h"
#include "vtkActor.h"
#include "vtkStructuredGridOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkStructuredGridGeometryFilter.h"
#include "vtkPointSource.h"
#include "vtkRungeKutta4.h"
#include "vtkStreamLine.h"
#include "vtkTubeFilter.h"
#include "vtkPolyDataNormals.h"

#include <string>
#include <vector>

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager          *_mgr = NULL;
OSG::GLUTWindowRecPtr             _client_win = NULL;
OSG::MultiDisplayWindowRecPtr     _cluster_win = NULL;
OSG::NodeRecPtr                   _root = NULL;
std::vector<std::string>          _pipenames;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void display(void);

void addActor(OSG::Node *pRoot,
              vtkActor  *pActor)
{
    OSG::NodeUnrecPtr              pTmpNode   = OSG::Node     ::create();
    OSG::VTKPolyDataMapperUnrecPtr pTmpMapper = 
        OSG::VTKPolyDataMapper::create();

    pTmpMapper->setActor(pActor    );
    pTmpNode  ->setCore (pTmpMapper);
    pRoot     ->addChild(pTmpNode  );

    fprintf(stderr, "%016llx\n",
            OSG::VTKPolyDataMapper::ChangedCallbacksFieldMask);
    fprintf(stderr, "%016llx\n",
            OSG::VTKPolyDataMapper::AttachmentsFieldMask);
    fprintf(stderr, "%016llx\n",
            OSG::VTKPolyDataMapper::ParentsFieldMask);
    fprintf(stderr, "%016llx\n",
            OSG::VTKPolyDataMapper::RootFieldMask);
    fprintf(stderr, "%016llx\n",
            OSG::VTKPolyDataMapper::GeoRootsFieldMask);
    fprintf(stderr, "%016llx\n",
            OSG::VTKPolyDataMapper::NormalsFieldMask);

    fprintf(stderr, "%016llx %016llx\n",
            (OSG::VTKPolyDataMapper::GeoRootsFieldMask),
           ~(OSG::VTKPolyDataMapper::GeoRootsFieldMask));

    fprintf(stderr, "%016llx\n",
            pTmpMapper->getFieldFlags()->_bClusterLocalFlags);

//    pTmpMapper->execute();
}

OSG::NodeTransitPtr initVTK(void)
{
    OSG::NodeUnrecPtr returnValue = NULL;

    OSG::Char8 *szDataRoot = getenv("VTK_DATA_ROOT");

    if(szDataRoot == NULL)
    {
        fprintf(stderr, "VTK_DATA_ROOT not set\n");
        exit(0);
    }

    std::string szFilename;

    szFilename.assign(szDataRoot);
    szFilename += "/Data/office.binary.vtk";

    vtkStructuredGridReader *reader = vtkStructuredGridReader::New();

    reader->SetFileName(szFilename.c_str());
    reader->Update();

    OSG::Real64 length = reader->GetOutput()->GetLength();

    OSG::Real64 maxVelocity = 
        reader->GetOutput()->GetPointData()->GetVectors()->GetMaxNorm();

    OSG::Real64 maxTime = 35.0 * length / maxVelocity;



    returnValue = OSG::Node::create();

    returnValue->setCore(OSG::Group::create());

    // Create source for streamtubes
    vtkPointSource *seeds = vtkPointSource::New();
    seeds->SetRadius(0.15);
    seeds->SetCenter(0.1, 2.1, 0.5);
    seeds->SetNumberOfPoints(6);

    vtkRungeKutta4 *integ = vtkRungeKutta4::New();
    vtkStreamLine *streamer = vtkStreamLine::New();
    streamer->SetInputConnection(reader->GetOutputPort());
    streamer->SetSource(seeds->GetOutput());
    streamer->SetMaximumPropagationTime(500);
    streamer->SetStepLength(0.5);
    streamer->SetIntegrationStepLength(0.05);
    streamer->SetIntegrationDirectionToIntegrateBothDirections();
    streamer->SetIntegrator(integ);

    // The tube is wrapped around the generated streamline. By varying the
    // radius by the inverse of vector magnitude, we are creating a tube
    // whose radius is proportional to mass flux (in incompressible flow).
    vtkTubeFilter *streamTube = vtkTubeFilter::New();
    streamTube->SetInputConnection(streamer->GetOutputPort());
    streamTube->SetRadius(0.02);
    streamTube->SetNumberOfSides(12);
    streamTube->SetVaryRadiusToVaryRadiusByVector();
    vtkPolyDataMapper *mapStreamTube = vtkPolyDataMapper::New();
    mapStreamTube->SetInputConnection(streamTube->GetOutputPort());
    mapStreamTube->SetScalarRange(
        reader->GetOutput()->GetPointData()->GetScalars()->GetRange());
    vtkActor *streamTubeActor = vtkActor::New();
    streamTubeActor->SetMapper(mapStreamTube);
    streamTubeActor->GetProperty()->BackfaceCullingOn();

    addActor(returnValue, streamTubeActor);


    vtkStructuredGridGeometryFilter *table1 = 
        vtkStructuredGridGeometryFilter::New();

    table1->SetInputConnection(reader->GetOutputPort());
    table1->SetExtent(11, 15, 7, 9, 8, 8);

    vtkPolyDataNormals *normTable1 = vtkPolyDataNormals::New();
    normTable1->SetInputConnection(table1->GetOutputPort());

    vtkPolyDataMapper *mapTable1 = vtkPolyDataMapper::New();
    mapTable1->SetInputConnection(normTable1->GetOutputPort());
    mapTable1->ScalarVisibilityOff();
    
    vtkActor *table1Actor = vtkActor::New();
    table1Actor->SetMapper(mapTable1);
    table1Actor->GetProperty()->SetColor(.59, .427, .392);

    addActor(returnValue, table1Actor);



    vtkStructuredGridGeometryFilter *table2 = 
        vtkStructuredGridGeometryFilter::New();
    table2->SetInputConnection(reader->GetOutputPort());
    table2->SetExtent(11, 15, 10, 12, 8, 8);

    vtkPolyDataNormals *normTable2 = vtkPolyDataNormals::New();
    normTable2->SetInputConnection(table2->GetOutputPort());

    vtkPolyDataMapper *mapTable2 = vtkPolyDataMapper::New();
    mapTable2->SetInputConnection(normTable2->GetOutputPort());
    mapTable2->ScalarVisibilityOff();
    
    vtkActor *table2Actor = vtkActor::New();
    table2Actor->SetMapper(mapTable2);
    table2Actor->GetProperty()->SetColor(.59, .427, .392);

    addActor(returnValue, table2Actor);



    vtkStructuredGridGeometryFilter *FilingCabinet1 = 
        vtkStructuredGridGeometryFilter::New();

    FilingCabinet1->SetInputConnection(reader->GetOutputPort());
    FilingCabinet1->SetExtent(15, 15, 7, 9, 0, 8);

    vtkPolyDataNormals *normFilingCabinet1 = vtkPolyDataNormals::New();
    normFilingCabinet1->SetInputConnection(FilingCabinet1->GetOutputPort());

    vtkPolyDataMapper *mapFilingCabinet1 = vtkPolyDataMapper::New();
    mapFilingCabinet1->SetInputConnection(normFilingCabinet1->GetOutputPort());
    mapFilingCabinet1->ScalarVisibilityOff();

    vtkActor *FilingCabinet1Actor = vtkActor::New();
    FilingCabinet1Actor->SetMapper(mapFilingCabinet1);
    FilingCabinet1Actor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, FilingCabinet1Actor);



    vtkStructuredGridGeometryFilter *FilingCabinet2 = 
        vtkStructuredGridGeometryFilter::New();
    FilingCabinet2->SetInputConnection(reader->GetOutputPort());
    FilingCabinet2->SetExtent(15, 15, 10, 12, 0, 8);

    vtkPolyDataNormals *normFilingCabinet2 = vtkPolyDataNormals::New();
    normFilingCabinet2->SetInputConnection(FilingCabinet2->GetOutputPort());

    vtkPolyDataMapper *mapFilingCabinet2 = vtkPolyDataMapper::New();
    mapFilingCabinet2->SetInputConnection(normFilingCabinet2->GetOutputPort());
    mapFilingCabinet2->ScalarVisibilityOff();

    vtkActor *FilingCabinet2Actor = vtkActor::New();
    FilingCabinet2Actor->SetMapper(mapFilingCabinet2);
    FilingCabinet2Actor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, FilingCabinet2Actor);



    vtkStructuredGridGeometryFilter *bookshelf1Top = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf1Top->SetInputConnection(reader->GetOutputPort());
    bookshelf1Top->SetExtent(13, 13, 0, 4, 0, 11);

    vtkPolyDataNormals *normbookshelf1Top = vtkPolyDataNormals::New();
    normbookshelf1Top->SetInputConnection(bookshelf1Top->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf1Top = vtkPolyDataMapper::New();
    mapBookshelf1Top->SetInputConnection(normbookshelf1Top->GetOutputPort());
    mapBookshelf1Top->ScalarVisibilityOff();

    vtkActor *bookshelf1TopActor = vtkActor::New();
    bookshelf1TopActor->SetMapper(mapBookshelf1Top);
    bookshelf1TopActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf1TopActor);


    
    vtkStructuredGridGeometryFilter *bookshelf1Bottom = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf1Bottom->SetInputConnection(reader->GetOutputPort());
    bookshelf1Bottom->SetExtent(20, 20, 0, 4, 0, 11);

    vtkPolyDataNormals *normbookshelf1Bottom = vtkPolyDataNormals::New();
    normbookshelf1Bottom->SetInputConnection(
        bookshelf1Bottom->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf1Bottom = vtkPolyDataMapper::New();
    mapBookshelf1Bottom->SetInputConnection(
        normbookshelf1Bottom->GetOutputPort());
    mapBookshelf1Bottom->ScalarVisibilityOff();

    vtkActor *bookshelf1BottomActor = vtkActor::New();
    bookshelf1BottomActor->SetMapper(mapBookshelf1Bottom);
    bookshelf1BottomActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf1BottomActor);



    vtkStructuredGridGeometryFilter *bookshelf1Front = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf1Front->SetInputConnection(reader->GetOutputPort());
    bookshelf1Front->SetExtent(13, 20, 0, 0, 0, 11);

    vtkPolyDataNormals *normbookshelf1Front = vtkPolyDataNormals::New();
    normbookshelf1Front->SetInputConnection(bookshelf1Front->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf1Front = vtkPolyDataMapper::New();
    mapBookshelf1Front->SetInputConnection(
        normbookshelf1Front->GetOutputPort());
    mapBookshelf1Front->ScalarVisibilityOff();

    vtkActor *bookshelf1FrontActor = vtkActor::New();
    bookshelf1FrontActor->SetMapper(mapBookshelf1Front);
    bookshelf1FrontActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf1FrontActor);



    vtkStructuredGridGeometryFilter *bookshelf1Back = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf1Back->SetInputConnection(reader->GetOutputPort());
    bookshelf1Back->SetExtent(13, 20, 4, 4, 0, 11);

    vtkPolyDataNormals *normbookshelf1Back = vtkPolyDataNormals::New();
    normbookshelf1Back->SetInputConnection(bookshelf1Back->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf1Back = vtkPolyDataMapper::New();
    mapBookshelf1Back->SetInputConnection(normbookshelf1Back->GetOutputPort());
    mapBookshelf1Back->ScalarVisibilityOff();

    vtkActor *bookshelf1BackActor = vtkActor::New();
    bookshelf1BackActor->SetMapper(mapBookshelf1Back);
    bookshelf1BackActor->GetProperty()->SetColor(.8, .8, .6);
    
    addActor(returnValue, bookshelf1BackActor);



    vtkStructuredGridGeometryFilter *bookshelf1LHS = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf1LHS->SetInputConnection(reader->GetOutputPort());
    bookshelf1LHS->SetExtent(13, 20, 0, 4, 0, 0);

    vtkPolyDataNormals *normbookshelf1LHS = vtkPolyDataNormals::New();
    normbookshelf1LHS->SetInputConnection(bookshelf1LHS->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf1LHS = vtkPolyDataMapper::New();
    mapBookshelf1LHS->SetInputConnection(normbookshelf1LHS->GetOutputPort());
    mapBookshelf1LHS->ScalarVisibilityOff();

    vtkActor *bookshelf1LHSActor = vtkActor::New();
    bookshelf1LHSActor->SetMapper(mapBookshelf1LHS);
    bookshelf1LHSActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf1LHSActor);



    vtkStructuredGridGeometryFilter *bookshelf1RHS = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf1RHS->SetInputConnection(reader->GetOutputPort());
    bookshelf1RHS->SetExtent(13, 20, 0, 4, 11, 11);

    vtkPolyDataNormals *normbookshelf1RHS = vtkPolyDataNormals::New();
    normbookshelf1RHS->SetInputConnection(bookshelf1RHS->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf1RHS = vtkPolyDataMapper::New();
    mapBookshelf1RHS->SetInputConnection(normbookshelf1RHS->GetOutputPort());
    mapBookshelf1RHS->ScalarVisibilityOff();

    vtkActor *bookshelf1RHSActor = vtkActor::New();
    bookshelf1RHSActor->SetMapper(mapBookshelf1RHS);
    bookshelf1RHSActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf1RHSActor);



    vtkStructuredGridGeometryFilter *bookshelf2Top = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf2Top->SetInputConnection(reader->GetOutputPort());
    bookshelf2Top->SetExtent(13, 13, 15, 19, 0, 11);

    vtkPolyDataNormals *normbookshelf2Top = vtkPolyDataNormals::New();
    normbookshelf2Top->SetInputConnection(bookshelf2Top->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf2Top = vtkPolyDataMapper::New();
    mapBookshelf2Top->SetInputConnection(normbookshelf2Top->GetOutputPort());
    mapBookshelf2Top->ScalarVisibilityOff();

    vtkActor *bookshelf2TopActor = vtkActor::New();
    bookshelf2TopActor->SetMapper(mapBookshelf2Top);
    bookshelf2TopActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf2TopActor);


    vtkStructuredGridGeometryFilter *bookshelf2Bottom = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf2Bottom->SetInputConnection(reader->GetOutputPort());
    bookshelf2Bottom->SetExtent(20, 20, 15, 19, 0, 11);

    vtkPolyDataNormals *normbookshelf2Bottom = vtkPolyDataNormals::New();
    normbookshelf2Bottom->SetInputConnection(
        bookshelf2Bottom->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf2Bottom = vtkPolyDataMapper::New();
    mapBookshelf2Bottom->SetInputConnection(
        normbookshelf2Bottom->GetOutputPort());
    mapBookshelf2Bottom->ScalarVisibilityOff();

    vtkActor *bookshelf2BottomActor = vtkActor::New();
    bookshelf2BottomActor->SetMapper(mapBookshelf2Bottom);
    bookshelf2BottomActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf2BottomActor);



    vtkStructuredGridGeometryFilter *bookshelf2Front = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf2Front->SetInputConnection(reader->GetOutputPort());
    bookshelf2Front->SetExtent(13, 20, 15, 15, 0, 11);

    vtkPolyDataNormals *normbookshelf2Front = vtkPolyDataNormals::New();
    normbookshelf2Front->SetInputConnection(bookshelf2Front->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf2Front = vtkPolyDataMapper::New();
    mapBookshelf2Front->SetInputConnection(
        normbookshelf2Front->GetOutputPort());
    mapBookshelf2Front->ScalarVisibilityOff();

    vtkActor *bookshelf2FrontActor = vtkActor::New();
    bookshelf2FrontActor->SetMapper(mapBookshelf2Front);
    bookshelf2FrontActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf2FrontActor);



    vtkStructuredGridGeometryFilter *bookshelf2Back = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf2Back->SetInputConnection(reader->GetOutputPort());
    bookshelf2Back->SetExtent(13, 20, 19, 19, 0, 11);

    vtkPolyDataNormals *normbookshelf2Back = vtkPolyDataNormals::New();
    normbookshelf2Back->SetInputConnection(bookshelf2Back->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf2Back = vtkPolyDataMapper::New();
    mapBookshelf2Back->SetInputConnection(normbookshelf2Back->GetOutputPort());
    mapBookshelf2Back->ScalarVisibilityOff();

    vtkActor *bookshelf2BackActor = vtkActor::New();
    bookshelf2BackActor->SetMapper(mapBookshelf2Back);
    bookshelf2BackActor->GetProperty()->SetColor(.8, .8, .6);
    
    addActor(returnValue, bookshelf2BackActor);



    vtkStructuredGridGeometryFilter *bookshelf2LHS = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf2LHS->SetInputConnection(reader->GetOutputPort());
    bookshelf2LHS->SetExtent(13, 20, 15, 19, 0, 0);

    vtkPolyDataNormals *normbookshelf2LHS = vtkPolyDataNormals::New();
    normbookshelf2LHS->SetInputConnection(bookshelf2LHS->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf2LHS = vtkPolyDataMapper::New();
    mapBookshelf2LHS->SetInputConnection(normbookshelf2LHS->GetOutputPort());
    mapBookshelf2LHS->ScalarVisibilityOff();
    vtkActor *bookshelf2LHSActor = vtkActor::New();
    bookshelf2LHSActor->SetMapper(mapBookshelf2LHS);
    bookshelf2LHSActor->GetProperty()->SetColor(.8, .8, .6);

    addActor(returnValue, bookshelf2LHSActor);



    vtkStructuredGridGeometryFilter *bookshelf2RHS = 
        vtkStructuredGridGeometryFilter::New();
    bookshelf2RHS->SetInputConnection(reader->GetOutputPort());
    bookshelf2RHS->SetExtent(13, 20, 15, 19, 11, 11);

    vtkPolyDataNormals *normbookshelf2RHS = vtkPolyDataNormals::New();
    normbookshelf2RHS->SetInputConnection(bookshelf2RHS->GetOutputPort());

    vtkPolyDataMapper *mapBookshelf2RHS = vtkPolyDataMapper::New();
    mapBookshelf2RHS->SetInputConnection(normbookshelf2RHS->GetOutputPort());
    mapBookshelf2RHS->ScalarVisibilityOff();

    vtkActor *bookshelf2RHSActor = vtkActor::New();
    bookshelf2RHSActor->SetMapper(mapBookshelf2RHS);
    bookshelf2RHSActor->GetProperty()->SetColor(.8, .8, .6);
    
    addActor(returnValue, bookshelf2RHSActor);



    vtkStructuredGridGeometryFilter *window = 
        vtkStructuredGridGeometryFilter::New();
    window->SetInputConnection(reader->GetOutputPort());
    window->SetExtent(20, 20, 6, 13, 10, 13);

    vtkPolyDataNormals *normWindow = vtkPolyDataNormals::New();
    normWindow->SetInputConnection(window->GetOutputPort());

    vtkPolyDataMapper *mapWindow = vtkPolyDataMapper::New();
    mapWindow->SetInputConnection(normWindow->GetOutputPort());
    mapWindow->ScalarVisibilityOff(); 

    vtkActor *windowActor = vtkActor::New();
    windowActor->SetMapper(mapWindow);
    windowActor->GetProperty()->SetColor(.3, .3, .5);
    
    addActor(returnValue, windowActor);



    vtkStructuredGridGeometryFilter *outlet = 
        vtkStructuredGridGeometryFilter::New();
    outlet->SetInputConnection(reader->GetOutputPort());
    outlet->SetExtent(0, 0, 9, 10, 14, 16);

    vtkPolyDataNormals *normoutlet = vtkPolyDataNormals::New();
    normoutlet->SetInputConnection(outlet->GetOutputPort());

    vtkPolyDataMapper *mapOutlet = vtkPolyDataMapper::New();
    mapOutlet->SetInputConnection(normoutlet->GetOutputPort());
    mapOutlet->ScalarVisibilityOff();
    vtkActor *outletActor = vtkActor::New();
    outletActor->SetMapper(mapOutlet);
    outletActor->GetProperty()->SetColor(0, 0, 0);

    addActor(returnValue, outletActor);



    vtkStructuredGridGeometryFilter *inlet = 
        vtkStructuredGridGeometryFilter::New();
    inlet->SetInputConnection(reader->GetOutputPort());
    inlet->SetExtent(0, 0, 9, 10, 0, 6);

    vtkPolyDataNormals *norminlet = vtkPolyDataNormals::New();
    norminlet->SetInputConnection(inlet->GetOutputPort());

    vtkPolyDataMapper *mapInlet = vtkPolyDataMapper::New();
    mapInlet->SetInputConnection(norminlet->GetOutputPort());

    mapInlet->ScalarVisibilityOff();
    vtkActor *inletActor = vtkActor::New();
    inletActor->SetMapper(mapInlet);
    inletActor->GetProperty()->SetColor(0, 0, 0);



    vtkStructuredGridOutlineFilter *outline = 
        vtkStructuredGridOutlineFilter::New();
    
    outline->SetInputConnection(reader->GetOutputPort());
    
    vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
    mapOutline->SetInputConnection(outline->GetOutputPort());
    
    vtkActor *outlineActor = vtkActor::New();
    
    outlineActor->SetMapper(mapOutline);
    outlineActor->GetProperty()->SetColor(0, 0, 0);
    
    addActor(returnValue, outlineActor);

    OSG::Thread::getCurrentChangeList()->dump();

    return OSG::NodeTransitPtr(returnValue);
}


// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    std::cout << "start a cluster server with './testClusterServer -w pipe0'\n"
                 "press 'c' to connect to the servers.\n"
                 "press 'd' to disconnect from the servers.\n"
                 "press 'n' to delete current scene.\n"
                 "press 't' to create a torus.\n"
                 "press 'l' to load scene 'tie.wrl'.\n"
              << std::endl;
    
    // OSG init
    OSG::osgInit(argc,argv);

    OSG::VTKPolyDataMapper::getClassType().dump();

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG

    _client_win = OSG::GLUTWindow::create();

    _client_win->setGlutId(winid);
    _client_win->init();
    _client_win->setSize(300,300);
    
    for(OSG::UInt32 i=0;i<argc-1;++i)
    {
        if(argv[i+1] != NULL)
            _pipenames.push_back(argv[i+1]);
    }

    if(_pipenames.empty())
        _pipenames.push_back("pipe0");
    
    _root = OSG::Node::create();
    
    _root->setCore(OSG::Group::create());
    
    // create default scene
//    NodePtr scene = makeTorus(.5, 2, 16, 16);
    OSG::NodeUnrecPtr scene = initVTK();

    _root->addChild(scene);

    // create the SimpleSceneManager helper
    _mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(_client_win );
    _mgr->setRoot  (_root);

    // show the whole scene
    _mgr->showAll();
    

    return 0;
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    doMain(argc, argv);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

static void connectCluster(void)
{
    if(_cluster_win != NULL)
        return;

    OSG::Viewport *clientvp = _client_win->getPort(0);
    
    // create the viewports for the cluster just a simple one ...
    OSG::ViewportUnrecPtr vp = OSG::Viewport::create();

    vp->setCamera    (_mgr->getCamera());
    vp->setBackground(clientvp->getBackground());
    vp->setRoot      (clientvp->getRoot());
    vp->setSize      (0,0, 1,1);

    // the connection between this client and the servers
    _cluster_win = OSG::MultiDisplayWindow::create();

    // all changes must be enclosed in beginEditCP and endEditCP
    // otherwise the changes will not be transfered over the network.

    for(OSG::UInt32 i=0;i<_pipenames.size();++i)
        _cluster_win->editMFServers()->push_back(_pipenames[i]);
    // dummy size for navigator
    _cluster_win->setSize(300,300);
    _cluster_win->addPort(vp);

    OSG::Thread::getCurrentChangeList()->commitChangesAndClear();
    OSG::Thread::getCurrentChangeList()->fillFromCurrentState();
    OSG::Thread::getCurrentChangeList()->dump();
    // create from the current state a changelist.

    // initialize window
    _cluster_win->init();

    // apply changelist to the servers
    _cluster_win->render((OSG::RenderAction *) _mgr->getRenderAction());

    // clear changelist
    OSG::Thread::getCurrentChangeList()->clear();

    glutPostRedisplay();
}

static void disconnectCluster(void)
{
    if(_cluster_win == NULL)
        return;

    _cluster_win = NULL;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    // redraw the client window
    _mgr->redraw();


    OSG::commitChanges();

    try
    {
        if(_cluster_win != NULL)
        {
            OSG::Thread::getCurrentChangeList()->dump();

            // redraw the server windows
            _cluster_win->render((OSG::RenderAction *) _mgr->getRenderAction());
        }
    }
    
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        //printf("error: '%s'\n", e.what());
        printf("ClusterServer was killed!\n");

        _cluster_win = NULL;
    } 
    
    OSG::commitChanges();
    OSG::clearChangeList();
}

// react to size changes
void reshape(int w, int h)
{
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);

    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            delete _mgr;
            _client_win = NULL;
            _cluster_win = NULL;
            _root = NULL;
            OSG::osgExit();
            exit(0);
        }
        case 'n':
            while(_root->getNChildren() > 0)
                _root->subChild(_root->getChild(0));

            glutPostRedisplay();
        break;
        case 'l':
        {
            OSG::NodeUnrecPtr scene = 
                OSG::SceneFileHandler::the()->read("tie.wrl");

            if(scene != NULL)
            {
                _root->addChild(scene);

                _mgr->showAll();

                glutPostRedisplay();
            }
        }
        break;
        case 't':
        {
            OSG::NodeUnrecPtr scene = OSG::makeTorus(.5, 2, 16, 16);

            _root->addChild(scene);

            _mgr->showAll();

            glutPostRedisplay();
        }
        break;
        case 'c':
            connectCluster();
        break;
        case 'd':
            disconnectCluster();
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

#else

int main (int argc, char **argv)
{
    return 0;
}

#endif
