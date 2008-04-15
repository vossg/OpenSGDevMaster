#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGFieldContainerFactory.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAction.h>
#include <OSGRenderAction.h>
#include <OSGSimpleGeometry.h>
#include <OSGSceneFileHandler.h>
#include <OSGMaterialGroup.h>
#include <OSGSimpleMaterial.h>

#include <OSGDirectionalLight.h>
#include <OSGLine.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
//#include "OSGUniformBackground.h"
#include "OSGVTKMapper.h"

#include "OSGTrackball.h"
#include "OSGOSGWriter.h"

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

using namespace OSG;



RenderAction *renact;

NodeUnrecPtr  root;

NodeUnrecPtr  file;

PerspectiveCameraUnrecPtr cam;
ViewportUnrecPtr vp;
WindowUnrecPtr win;

TransformUnrecPtr cam_trans;
TransformUnrecPtr scene_trans;

Trackball tball;

bool move_obj = false;

int mouseb = 0;
int lastx=0, lasty=0;

Quaternion oldq;
Vec3f      oldv;

void 
display(void)
{
    Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);

    q1.setValue(m3);

    m1.setRotate(q1);
    
//    std::cout << "TBROT" << std::endl << tball.getRotation() << endl;
//    std::cout << "M3" << std::endl << m3 << std::endl;
//    std::cout << "Q1" << std::endl << q1 << std::endl;
//    std::cout << "M1" << std::endl << m1 << std::endl;

//  m1.setRotate( tball.getRotation() );
    m2.setTranslate( tball.getPosition() );
    
//std::cout << "Pos: " << tball.getPosition() << ", Rot: " << tball.getRotation() << std::endl;

//    std::cout << tball.getRotation() << std::endl;

    m1.mult( m2 );

//    std::cerr << m1 << std::endl;
    

    if(move_obj == true)
    {
        scene_trans->editSFMatrix()->setValue( m1 );
    }
    else
    {
        cam_trans->editSFMatrix()->setValue( m1 );
    }

    Thread::getCurrentChangeList()->commitChanges();

//    win->draw( ract );
    win->render(renact);
}

void reshape( int w, int h )
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    win->resize( w, h );
}


void
animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void
motion(int x, int y)
{   
    Real32 w = win->getWidth(), h = win->getHeight();
    

    Real32  a = -2. * ( lastx / w - .5 ),
                b = -2. * ( .5 - lasty / h ),
                c = -2. * ( x / w - .5 ),
                d = -2. * ( .5 - y / h );

    if ( mouseb & ( 1 << GLUT_LEFT_BUTTON ) )
    {
        tball.updateRotation( a, b, c, d );     
    }
    else if ( mouseb & ( 1 << GLUT_MIDDLE_BUTTON ) )
    {
        tball.updatePosition( a, b, c, d );     
    }
    else if ( mouseb & ( 1 << GLUT_RIGHT_BUTTON ) )
    {
        tball.updatePositionNeg( a, b, c, d );  
    }
    lastx = x;
    lasty = y;
}

void
mouse(int button, int state, int x, int y)
{
    if ( state == 0 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(true);
                                break;
        case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(true);
                                break;
        }
        mouseb |= 1 << button;
    }
    else if ( state == 1 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(false);
                                break;
        case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(false);
                                break;
        }       
        mouseb &= ~(1 << button);
    }
    lastx = x;
    lasty = y;
}

void
vis(int visible)
{
    if (visible == GLUT_VISIBLE) 
    {
        glutIdleFunc(animate);
    } 
    else 
    {
        glutIdleFunc(NULL);
    }
}

void key(unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 27:    
            root        = NullFC;
            file        = NullFC;
            cam         = NullFC;
            vp          = NullFC;
            win         = NullFC;
            cam_trans   = NullFC;
            scene_trans = NullFC;
            osgExit(); 
            exit(0);
        case 'a':   glDisable( GL_LIGHTING );
            std::cerr << "Lighting disabled." << std::endl;
            break;
        case 's':   glEnable( GL_LIGHTING );
            std::cerr << "Lighting enabled." << std::endl;
            break;
        case 'z':   glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
            std::cerr << "PolygonMode: Point." << std::endl;
            break;
        case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            std::cerr << "PolygonMode: Line." << std::endl;
            break;
        case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            std::cerr << "PolygonMode: Fill." << std::endl;
            break;
        case 'r':   
        {
            std::cerr << "Sending ray through " << x << "," << y << std::endl;
            Line l;
            cam->calcViewRay( l, x, y, *vp );
            std::cerr << "From " << l.getPosition() << ", dir " 
                      << l.getDirection()
                      << std::endl;
        }
        break;

        case ' ':
        {
            Matrix     m;
            Quaternion q;
            Vec3f      v;

            q = oldq;
            v = oldv;

            oldq = tball.getRotation();
            oldv = tball.getPosition();

            move_obj = ! move_obj;
            if ( move_obj )
            {
                puts("moving object");
//                m = scene_trans->getSFMatrix()->getValue();
                tball.setMode( OSG::Trackball::OSGCamera );

            }
            else
            {
                puts("moving camera");
//                m = cam_trans->getSFMatrix()->getValue();
                tball.setMode( OSG::Trackball::OSGObject );
            }
            
//            q.setValue(m);
            tball.setStartPosition( v, true );
            tball.setStartRotation( q, true );

//            std::cout << q << std::endl;
//            std::cout << v << std::endl;

//            std::cout << " " << m[3][0] << " " << m[3][1] << " " << m[3][2] << std::endl;
            
        }
        break;
    }
}

void addActor(OSG::NodePtr pRoot,
              vtkActor    *pActor)
{
    OSG::NodeUnrecPtr      pTmpNode   = OSG::Node     ::create();
    OSG::VTKMapperUnrecPtr pTmpMapper = OSG::VTKMapper::create();

    pTmpMapper->setActor(pActor    );
    pTmpNode  ->setCore (pTmpMapper);
    pRoot     ->addChild(pTmpNode  );

//    pTmpMapper->execute();
}

OSG::NodeTransitPtr initVTK(void)
{
    OSG::NodeUnrecPtr returnValue = OSGNullFC;

    Char8 *szDataRoot = getenv("VTK_DATA_ROOT");

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

    Real64 length = reader->GetOutput()->GetLength();

    Real64 maxVelocity = 
        reader->GetOutput()->GetPointData()->GetVectors()->GetMaxNorm();

    Real64 maxTime = 35.0 * length / maxVelocity;



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

    return NodeTransitPtr(returnValue);
}

int main (int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    
    glutIdleFunc(display);  

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // OSG

    SceneFileHandler::the()->print();

    // create the graph

    // beacon for camera and light  
    NodeUnrecPtr b1n = Node::create();
    GroupUnrecPtr b1 = Group::create();
    b1n->setCore( b1 );

    // transformation
    NodeUnrecPtr t1n = Node::create();
    TransformUnrecPtr t1 = Transform::create();
    t1n->setCore( t1 );
    t1n->addChild( b1n );

    cam_trans = t1;

    // light
    
    NodeUnrecPtr dlight = Node::create();
    DirectionalLightUnrecPtr dl = DirectionalLight::create();

    dlight->setCore( dl );
    
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);

    // root
    root = Node::create();
    GroupUnrecPtr gr1 = Group::create();
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );

    // Load the file

    NodeUnrecPtr file = NullFC;
    NodeUnrecPtr file1 = NullFC;

    if ( argc > 1 )
        file1 = SceneFileHandler::the()->read(argv[1]);
    
    if ( file1 == NullFC )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file1 = initVTK();
    }
    
    Thread::getCurrentChangeList()->commitChanges();
    file1->updateVolume();

#if 0
    OSG::IndentFileOutStream outFileStream("/tmp/vsc_out.osg");
    
    if(outFileStream)
    {
        std::cerr << "STARTING PRINTOUT:" << std::endl;
        OSG::OSGWriter writer(outFileStream, 4);
        writer.write(file1);
        outFileStream.close(); 
    }
#endif
   
//    file->dump();

//    subRefCP(file);

//    return 0;


    Vec3f min,max;
    file1->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;


    file = Node::create();
    MaterialGroupUnrecPtr testMat = MaterialGroup::create();

    SimpleMaterialUnrecPtr defaultMaterial = SimpleMaterial::create();

    defaultMaterial->setDiffuse(Color3f(1,.0,.0));
    defaultMaterial->setAmbient(Color3f(0.1,0.1,0.1));
    defaultMaterial->setSpecular(Color3f(1,1,1));
    defaultMaterial->setShininess(20);


    testMat->setMaterial(defaultMaterial);

    file->setCore(OSG::Group::create());
    file->addChild(file1);

    scene_trans      = Transform::create();
    NodeUnrecPtr sceneTrN = Node::create();

    sceneTrN->setCore(scene_trans);
    sceneTrN->addChild(file);
//        sceneTrN->addChild(makeTorus( .5, 2, 16, 16 ));

    dlight->addChild(sceneTrN);

    std::cerr << "Tree: " << std::endl;
//  root->dump();

    // Camera
    
    cam = PerspectiveCamera::create();
    cam->setBeacon( b1n );
    cam->setFov( osgDegree2Rad( 90 ) );
    cam->setNear( 0.1 );
    cam->setFar( 100000 );

    // Background
    SolidBackgroundUnrecPtr bkgnd = SolidBackground::create();
    bkgnd->setColor(Color3f(1,1,1));
    
    // Viewport

    vp = Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLUTWindowUnrecPtr gwin;

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort( vp );

    win->init();

    // Action
    
    renact = RenderAction::create();

    // tball

    Vec3f pos;
    pos.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                  min[1] + ((max[1] - min[1]) * 0.5), 
                  max[2] + ( max[2] - min[2] ) * 1.5 );
    
    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    Pnt3f tCenter(min[0] + (max[0] - min[0]) / 2,
                  min[1] + (max[1] - min[1]) / 2,
                  min[2] + (max[2] - min[2]) / 2);

    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(tCenter);

    // run...
    
    glutMainLoop();
    
    return 0;
}

