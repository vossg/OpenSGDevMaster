
#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#include "OSGConfig.h"

#ifdef OSG_WITH_VTK

// #define FRAMEINTERLEAVE
#include "OSGGLUT.h"
#include "OSGGLU.h"
#include "OSGConfig.h"
#include <iostream>
#include "OSGLog.h"
#include "OSGTransform.h"
#include "OSGGroup.h"
#include "OSGNode.h"
#include "OSGClusterWindow.h"
#include "OSGSceneFileHandler.h"
#include "OSGDirectionalLight.h"
#include "OSGSimpleGeometry.h"
#include "OSGCamera.h"
#include "OSGViewport.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
//#include "OSGGradientBackground.h"
#include "OSGTrackball.h"
#include "OSGVolumeDraw.h"
#include "OSGGLUTWindow.h"
#include "OSGRenderAction.h"
//#include "OSGDrawAction.h"
#include "OSGMultiDisplayWindow.h"
//#include "OSGSortFirstWindow.h"
#include "OSGChunkMaterial.h"
#include "OSGPolygonChunk.h"
#include "OSGTriangleIterator.h"
#include "OSGMaterialGroup.h"
//#include "OSGSortLastWindow.h"
#include "OSGImageComposer.h"
#include "OSGProxyGroup.h"
#ifdef FRAMEINTERLEAVE
#include "OSGFrameInterleaveWindow.h"
#endif
#include "OSGShearedStereoCameraDecorator.h"
#include "OSGNameAttachment.h"
#include "OSGColorBufferViewport.h"

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

OSG::Trackball                   tball;
int                              mouseb = 0;
int                              lastx=0, lasty=0;
int                              winwidth  = 300;
int                              winheight = 300;
OSG::NodeRecPtr		         root;
OSG::TransformRecPtr             cam_trans;
OSG::PerspectiveCameraRecPtr     cam;
OSG::ClusterWindowRecPtr         clusterWindow;
OSG::RenderActionRefPtr          ract;
OSG::GLUTWindowRecPtr            clientWindow;

#ifdef HAVE_SORT
OSG::SortFirstWindowRecPtr       sortfirst;
OSG::SortLastWindowRecPtr        sortlast;
#endif

#ifdef FRAMEINTERLEAVE
OSG::FrameInterleaveWindowRecPtr frameinterleave;
#endif
OSG::MultiDisplayWindowRecPtr    multidisplay;
bool                     animate=false;
int                      animLoops=-1;
int                      animLength=30;
bool                     multiport=false;
float                    ca=-1,cb=-1,cc=-1;
OSG::Int32                    stereoMode=0;
float                    eyedistance=1,zeroparallax=10;
int                      serverx=-1,servery=-1;
std::vector<OSG::Quaternion>  animOri;
std::vector<OSG::Vec3f     >  animPos;
std::string              animName="animation.txt";
OSG::Real32                   animTime=0;
std::string              serviceAddress;
bool                     serviceAddressValid = false;
OSG::UInt32                   interleave=0;
OSG::Real32                   _dsFactor = 1.0; // scale down factor.
bool                     _enablecc = true; // enable color correction.
OSG::PolygonChunkRecPtr       polygonChunk;
bool                     prepared=false;
bool                     showInfo=false;
OSG::Time                frame_time=0;
OSG::UInt32                   sum_positions=0;
OSG::UInt32                   sum_geometries=0;
OSG::UInt32                   sum_triangles=0;
bool                     info = false;
std::string              connectionDestination="";
std::string              connectionInterface="";
OSG::SolidBackgroundRecPtr  bkgnd;
OSG::UInt32                   subtilesize=32;

void cleanup(void)
{
    ract = NULL;
    root = NULL;
    cam_trans = NULL;
    cam = NULL;
    clusterWindow = NULL;
    clientWindow = NULL;
#ifdef HAVE_SORT
    sortfirst = NULL;
    sortlast = NULL;
 #endif
#ifdef FRAMEINTERLEAVE
    frameinterleave = NULL;
#endif
    multidisplay = NULL;
    polygonChunk = NULL;
    bkgnd = NULL;

    OSG::osgExit(); 
}

/*! Simple show text function
 */
void displayInfo(int x, int y)
{
  int len, i;
#ifdef WIN32
#ifdef OSG_WIN32_CL
  void *font = (void *) 2;
#else
  void *font = 2;
#endif
#else
  void *font = GLUT_BITMAP_9_BY_15;
#endif

  char text[1024];
  sprintf(text,
          "FPS:        %12.1f\n"
          "Positions:  %12u\n"
          "Triangles:  %12u\n"
          "Geometries: %12u",
          1.0/frame_time,
          sum_positions,
          sum_triangles,
          sum_geometries);

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0,clientWindow->getWidth(),0,clientWindow->getHeight());
  glDisable(GL_DEPTH_TEST);  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  int x1=x-5;
  int x2=x1+24*9+10;
  int y1=y+14;
  int y2=y1-4*20;
  glBegin(GL_QUADS);
  glColor4f(.1, .1, .7, .5);
  glVertex2i(x1,y1);
  glVertex2i(x1,y2);
  glVertex2i(x2,y2);
  glVertex2i(x2,y1);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0, 1.0, 0.0);
  glVertex2i(x1,y1);
  glVertex2i(x1,y2);
  glVertex2i(x2,y2);
  glVertex2i(x2,y1);
  glEnd();

  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2f(x, y);
  len = int(strlen(text));
  for (i = 0; i < len; i++) {
      if(text[i] == '\n')
      {
          y-=20;
          glRasterPos2f(x, y);
      }
      else
          glutBitmapCharacter(font, text[i]);
  }
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glPopAttrib();
}

void prepareSceneGraph(OSG::Node * const node)
{
    OSG::TriangleIterator f;

    if(!prepared)
    {
        polygonChunk = OSG::PolygonChunk::create();
        prepared = true;
    }

    OSG::NodeCore *core  =node->getCore();
    if(core != NULL)
    {
        OSG::Geometry *geo   = dynamic_cast<OSG::Geometry *>(core);
        if(geo != NULL)
        {
            OSG::Material *mat = geo->getMaterial();
            if(mat != NULL)
            {
                OSG::ChunkMaterial *cmat = 
                    dynamic_cast<OSG::ChunkMaterial *>(mat);

                if(cmat->find(OSG::PolygonChunk::getClassType()) == NULL)
                {
                    cmat->addChunk(polygonChunk);
                }
            }
            // get num positions
            OSG::GeoVectorProperty *positionsPtr=geo->getPositions();
            if(positionsPtr != NULL)
                sum_positions += positionsPtr->size();
            // get num triangles
            for(f=geo->beginTriangles() ; f!=geo->endTriangles() ; ++f)
                ++sum_triangles;
            // sum of geometry nodes
            ++sum_geometries;
        }
        else
        {
            OSG::MaterialGroup *matGrp = 
                dynamic_cast<OSG::MaterialGroup *>(core);
            if(matGrp != NULL)
            {
                OSG::Material *mat = matGrp->getMaterial();
                if(mat != NULL)
                {
                    OSG::ChunkMaterial *cmat = 
                        dynamic_cast<OSG::ChunkMaterial *>(mat);

                    if(cmat->find(OSG::PolygonChunk::getClassType()) == NULL)
                    {
                        cmat->addChunk(polygonChunk);
                    }
                }
            }
            else
            {
                OSG::ProxyGroup *proxy = dynamic_cast<OSG::ProxyGroup *>(core);
                if(proxy != NULL)
                {
                    sum_triangles += proxy->getTriangles();
                    sum_positions += proxy->getPositions();
                    sum_geometries += proxy->getGeometries();
                }
            }
        }
    }
    for(OSG::MFUnrecChildNodePtr::const_iterator nI=node->getMFChildren()->begin();
        nI != node->getMFChildren()->end();
        ++nI)
    {
        prepareSceneGraph(*nI);
    }
}

void loadAnim()
{
    OSG::Real32 ax,ay,az,r,x,y,z;
    FILE *file=fopen(animName.c_str(),"r");
    
    animOri.clear();
    animPos.clear();
    if(!file)
        return;
    while(fscanf(file,"%f %f %f %f,%f %f %f",&ax,&ay,&az,&r,&x,&y,&z)==7)
    {
        animOri.push_back(OSG::Quaternion(OSG::Vec3f(ax,ay,az),r));
        animPos.push_back(OSG::Vec3f(x,y,z));
    }
    fclose(file);
}

void display(void)
{
    OSG::Time t;

    t=-OSG::getSystemTime();

    if(animate && animPos.size()>1)
    {
        OSG::UInt32 i= OSG::UInt32(animTime);
        OSG::Real32 a=animTime-i;

        printf("%d %" PRISize "\n",i,animPos.size());
        OSG::Vec3f v=animPos[i] + (animPos[i+1] - animPos[i]) * a; 

        cam_trans->editMatrix().setTranslate(v[0],v[1],v[2]);
        cam_trans->editMatrix().setRotate(
            OSG::Quaternion::slerp(animOri[i],animOri[i+1],a));
    }
    else
    {
        cam_trans->editSFMatrix()->setValue( tball.getFullTrackballMatrix() );
    }

    try
    {
        OSG::Thread::getCurrentChangeList()->commitChanges();
#if 0
        clusterWindow->activate();	
        clusterWindow->frameInit();	
        clusterWindow->renderAllViewports(ract);	
#endif
        clusterWindow->renderNoFinish(ract);
#if 0
        if(showInfo)
        {
            displayInfo(10,90);
/*
            char text[1024];
            sprintf(text,"FPS:        %12.1f",1.0/frame_time);
            showText(10,70,text);
            sprintf(text,"Positions:  %12d",sum_positions);
            showText(10,50,text);
            sprintf(text,"Triangles:  %12d",sum_triangles);
            showText(10,30,text);
            sprintf(text,"Geometries: %12d",sum_geometries);
            showText(10,10,text);
*/
        }
#endif
#if 0
        clusterWindow->swap();	
        clusterWindow->frameExit();	
#endif
        clusterWindow->frameFinish();

        // clear changelist from prototypes
        OSG::Thread::getCurrentChangeList()->clear();
	}
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        std::cout << e.what() << std::endl;
        cleanup();
        exit(0);
    }
    
    t+=OSG::getSystemTime();
    frame_time = t;

    if(animate)
    {
//        OSG::Real32 a;
        OSG::Vec3f v;

        printf("Frame %8.3f %8.5f %8.3f\n",
               animTime,
               t,1/t);

        animTime += (animPos.size()/float(animLength));
        if(OSG::SizeT(animTime)+1 >= animPos.size())
        {
            animTime = 0;

            if(animLoops > 0)
            {
                animLoops--;
                if(!animLoops) 
                {
                    cleanup();
                    exit(0);
                }
            }
        }
    }
}

void reshape( int width, int height )
{
    printf("reshape %d %d\n",width,height);
    glViewport(0, 0, width, height);
	clientWindow->resize( width, height );
	glutPostRedisplay();
}

void motion(int x, int y)
{
    OSG::Real32 w = clientWindow->getWidth(), h = clientWindow->getHeight();


    OSG::Real32 a = -2. * ( lastx / w - .5 ),
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
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if ( state == 0 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(true);
                                break;
        case GLUT_RIGHT_BUTTON: tball.setAutoPositionNeg(true);
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
        case GLUT_RIGHT_BUTTON: tball.setAutoPositionNeg(false);
                                break;
        }
        mouseb &= ~(1 << button);
    }
    lastx = x;
    lasty = y;
	glutPostRedisplay();
}

void setHEyeWallParameter(OSG::Real32 dsFactor, bool enablecc)
{
    static char str[1024];
    
    OSG::NameUnrecPtr parameters = dynamic_cast<OSG::Name *>(clusterWindow->findAttachment(OSG::Name::getClassType()));

    if(parameters == NULL)
    {
        parameters = OSG::Name::create();
        clusterWindow->addAttachment(parameters);
    }
    
    sprintf(str, "downScale=%f colorCorrection=%d", dsFactor, enablecc);
    parameters->editFieldPtr()->getValue().assign(str);
}

void key(unsigned char key, int /*x*/, int /*y*/)
{
	switch ( key )
	{
        case 'l':
        {
            loadAnim();
            break;
        }
        case 'c':
        {
            FILE *file=fopen(animName.c_str(),"w");
            fclose(file);
            animOri.clear();
            animPos.clear();
            break;
        }
        case 's':
        {
            FILE *file=fopen(animName.c_str(),"a");
            OSG::Matrix m=cam_trans->getMatrix();
            OSG::Quaternion q(m);
            OSG::Real32 ax,ay,az,r;
            animPos.push_back(OSG::Vec3f(m[3][0],
                                         m[3][1],
                                         m[3][2]));
            animOri.push_back(q);
            q.getValueAsAxisRad(ax,ay,az,r);
            fprintf(file,"%f %f %f %f,%f %f %f\n",ax,ay,az,r,
                    m[3][0],
                    m[3][1],
                    m[3][2]);
            fclose(file);
            break;
        }
        case 'S':
        {
            FILE *file=fopen((animName+".wrl").c_str(),"w");
            std::vector<OSG::Quaternion>::iterator qit;
            
            fprintf(file,"DEF OriInter OrientationInterpolator {\n\tkey [");
            for(OSG::SizeT i = 0; i < animOri.size(); ++i)
            {               
                fprintf(file, "%f", i / OSG::Real32(animOri.size() - 1) );
                if(i < animOri.size() - 1)
                    fprintf(file,", ");
            }
            fprintf(file,"]\n\tkeyValue [");
            for(qit = animOri.begin(); qit != animOri.end(); ++qit)
            {
                OSG::Real32 ax,ay,az,r;
                (*qit).getValueAsAxisRad(ax,ay,az,r);
                
                fprintf(file, "%f %f %f %f", ax, ay, az, r );
                if(qit < animOri.end() - 1)
                    fprintf(file,", ");
            }
            fprintf(file,"]\n}\n\n");

            std::vector<OSG::Vec3f>::iterator vit;
            
            fprintf(file,"DEF PosInter PositionInterpolator {\n\tkey [");
            for(OSG::SizeT i = 0; i < animPos.size(); ++i)
            {               
                fprintf(file, "%f", i / OSG::Real32(animPos.size() - 1) );
                if(i < animPos.size() - 1)
                    fprintf(file,", ");
            }
            fprintf(file,"]\n\tkeyValue [");
            for(vit = animPos.begin(); vit != animPos.end(); ++vit)
            {
                OSG::Vec3f v = *vit;
                
                fprintf(file, "%f %f %f, ", v[0], v[1], v[2] );
            }
            fprintf(file,"]\n}\n\n");

            fclose(file);
            break;
        }
#ifdef HAVE_SORT
        case 'j':
            if(sortfirst!=NULL)
            {
                sortfirst->setCompression("JPEG");
            }
            break;
        case 'r':
            if(sortfirst!=NULL)
            {
                sortfirst->setCompression("RLE");
            }
            break;
        case 'n':
            if(sortfirst!=NULL)
            {
                sortfirst->getCompression().erase();
            }
            break;
#endif
        case 'i':
            showInfo = !showInfo;
            break;
        case 'w':
            if(polygonChunk->getFrontMode() == GL_FILL)
                polygonChunk->setFrontMode(GL_LINE);
            else
                polygonChunk->setFrontMode(GL_FILL);

            if(polygonChunk->getBackMode() == GL_FILL)
                polygonChunk->setBackMode(GL_LINE);
            else
                polygonChunk->setBackMode(GL_FILL);

            break;
        case 'a':
            if(animate)
            {
                glutIdleFunc(NULL);       
                animate=false;
            }
            else
            {
                glutIdleFunc(display);       
                animate=true;
            }
            break;
        case 'd':
            // remove tree
            while(root->getNChildren())
            {
                root->subChild(0u);
            }
            break;
        case '+':
            _dsFactor += 0.01f;
            if(_dsFactor > 1.0f)
                _dsFactor = 1.0f;
            setHEyeWallParameter(_dsFactor, _enablecc);
            break;
        case '-':
            _dsFactor -= 0.01f;
            if(_dsFactor <= 0.0f)
                _dsFactor = 0.01f;
            setHEyeWallParameter(_dsFactor, _enablecc);
            break;
        case 'f':
            if(_enablecc)
                _enablecc = false;
            else
                _enablecc = true;
            setHEyeWallParameter(_dsFactor, _enablecc);
            break;
        case 'B':
            if(bkgnd->getColor()[0] == 0.0)
                bkgnd->setColor( OSG::Color3f(1,1,1) );
            else
                bkgnd->setColor( OSG::Color3f(0,0,0) );
            break;
        case 27:	// should kill the clients here
            // exit
            cleanup();
            exit(0);
	}
	
	glutPostRedisplay();
}

void addActor(OSG::Node *pRoot,
              vtkActor  *pActor)
{
    OSG::NodeUnrecPtr              pTmpNode   = OSG::Node     ::create();
    OSG::VTKPolyDataMapperUnrecPtr pTmpMapper = 
        OSG::VTKPolyDataMapper::create();

    pTmpMapper->setActor(pActor    );
    pTmpNode  ->setCore (pTmpMapper);
    pRoot     ->addChild(pTmpNode  );

//    pTmpMapper->execute();
}

OSG::NodeTransitPtr initVTK(void)
{
    OSG::NodeUnrecPtr returnValue = NULL;

    OSG::Char8 *szDataRoot = getenv("VTK_DATA_ROOT");

    if(szDataRoot == NULL)
    {
        fprintf(stderr, "VTK_DATA_ROOT not set\n");
        cleanup();
        exit(0);
    }

    std::string szFilename;

    szFilename.assign(szDataRoot);
    szFilename += "/Data/office.binary.vtk";

    vtkStructuredGridReader *reader = vtkStructuredGridReader::New();

    reader->SetFileName(szFilename.c_str());
    reader->Update();

#if 0
    OSG::Real64 length = reader->GetOutput()->GetLength();

    OSG::Real64 maxVelocity = 
        reader->GetOutput()->GetPointData()->GetVectors()->GetMaxNorm();

    OSG::Real64 maxTime = 35.0 * length / maxVelocity;
#endif


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

    return OSG::NodeTransitPtr(returnValue);
}

void init(std::vector<std::string> &filenames)
{
    OSG::SizeT i;
    OSG::DirectionalLightUnrecPtr dl;
    OSG::Real32 x,y,z;
    OSG::BoxVolume volume;
    OSG::Vec3f min,max;
    OSG::Vec3f size;

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // create the graph

    // beacon for camera and light
    OSG::NodeUnrecPtr b1n = OSG::Node::create();
    OSG::GroupUnrecPtr b1 = OSG::Group::create();

    b1n->setCore( b1 );

    // transformation
    OSG::NodeUnrecPtr t1n = OSG::Node::create();
    OSG::TransformUnrecPtr t1 = OSG::Transform::create();

    t1n->setCore( t1 );
    t1n->addChild( b1n );

    cam_trans = t1;

    // light

    OSG::NodeUnrecPtr dlight = OSG::Node::create();
    dl = OSG::DirectionalLight::create();


    dlight->setCore( dl );


    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);

    // root
    root = OSG::Node::create();
    OSG::GroupUnrecPtr gr1 = OSG::Group::create();

    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );

    // Load the file
    OSG::NodeUnrecPtr scene = OSG::Node::create();

    scene->setCore(OSG::Group::create());

    OSG::NodeUnrecPtr file;

    for(i=0;i<filenames.size();i++)
    {
        file = OSG::SceneFileHandler::the()->read(filenames[i].c_str(),0);
        if(file != NULL)
            scene->addChild(file);
        else
            std::cerr << "Couldn't load file, ignoring " << filenames[i] << std::endl;
    }
	if ( filenames.size()==0 )
	{
//        scene->addChild(makeTorus( .5, 2, 16, 16 ));
//        scene->addChild(makeBox(.6,.6,.6,5,5,5));
        scene->addChild(initVTK());
    }

    prepareSceneGraph(scene);
    
    OSG::Thread::getCurrentChangeList()->commitChanges();

    scene->invalidateVolume();
    scene->updateVolume();
    volume=scene->getVolume();
    volume.getBounds(min,max);
    size = max-min;


    if(ca>0)
    {
        if(cb==-1)
            cb=ca;
        if(cc==-1)
            cc=cb;
            
        OSG::NodeUnrecPtr node;
        OSG::NodeUnrecPtr geoNode;
        OSG::TransformUnrecPtr trans;
        for(x=-ca/2.0 ; x<ca/2.0 ; x++)
            for(y=-cb/2.0 ; y<cb/2.0 ; y++)
                for(z=-cc/2.0 ; z<cc/2.0 ; z++)
                {
                    trans=OSG::Transform::create();
                    node=OSG::Node::create();
                    
                    node->setCore(trans);
                    trans->editMatrix().setTranslate(
                        x*size[0]*1.1,
                        y*size[1]*1.1,
                        z*size[2]*1.1);
                    node->addChild( OSG::cloneTree(scene) );
                    dlight->addChild(node);
                }
    }
    else
    {
        dlight->addChild(scene);
	}

    if(ca>0)
    {
        sum_geometries*= OSG::UInt32(ca*cb*cc);
        sum_triangles *= OSG::UInt32(ca*cb*cc);
        sum_positions *= OSG::UInt32(ca*cb*cc);
    }
//    dlight->invalidateVolume();

    dlight->updateVolume();

    // should check first. ok for now.
    const OSG::BoxVolume &vol = dlight->getVolume();

    OSG::Pnt3f center;

    vol.getBounds(min, max);
    vol.getCenter(center);

    size = max - min;

    std::cout << "Volume: from " << min << " to " << max << std::endl;


    // Camera

    OSG::PerspectiveCameraUnrecPtr cam = OSG::PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( OSG::osgDegree2Rad( 60 ) );
    cam->setNear( 10 );
    cam->setFar( 50000 );

    // Solid Background
    bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor( OSG::Color3f(0,0,0) );
//    bkgnd->setColor( OSG::Color3f(.1,.1,.6) );
//    bkgnd->setColor( OSG::Color3f(1,1,1) );

    // Viewport
    OSG::ViewportUnrecPtr vp1;
    OSG::ViewportUnrecPtr vp2;
    if(stereoMode == 0)
    {
        vp1 = OSG::Viewport::create();

        vp1->setCamera    ( cam );
        vp1->setBackground( bkgnd );
        vp1->setRoot      ( root );
        vp1->setSize      ( 0,0, 1,1 );

        if(multiport)
        {
            vp2 = OSG::Viewport::create();

            vp2->setCamera    ( cam );
            vp2->setBackground( bkgnd );
            vp2->setRoot      ( root );
            vp2->setSize      ( .1, .55, .7,.95 );
        }
    }
    else if(stereoMode == 1)
    {
        OSG::ShearedStereoCameraDecoratorUnrecPtr deco;
        // left
        deco=OSG::ShearedStereoCameraDecorator::create();

        deco->setLeftEye(true);
        deco->setEyeSeparation(eyedistance);
        deco->setDecoratee(cam);
        deco->setZeroParallaxDistance(zeroparallax);
        vp1 = OSG::Viewport::create();

        vp1->setCamera    ( deco );
        vp1->setBackground( bkgnd );
        vp1->setRoot      ( root );
        vp1->setSize      ( 0,0, .5,1 );

        // right
        deco=OSG::ShearedStereoCameraDecorator::create();

        deco->setLeftEye(false);
        deco->setEyeSeparation(eyedistance);
        deco->setDecoratee(cam);
        deco->setZeroParallaxDistance(zeroparallax);
        vp2 = OSG::Viewport::create();

        vp2->setCamera    ( deco );
        vp2->setBackground( bkgnd );
        vp2->setRoot      ( root );
        vp2->setSize      ( .5,0,1,1 );
    }
    else if(stereoMode == 2)
    {
        OSG::ShearedStereoCameraDecoratorUnrecPtr deco;
        // left
        deco=OSG::ShearedStereoCameraDecorator::create();

            deco->setLeftEye(true);
            deco->setEyeSeparation(eyedistance);
            deco->setDecoratee(cam);
            deco->setZeroParallaxDistance(zeroparallax);
        
        OSG::ColorBufferViewportUnrecPtr cvp1 = 
            OSG::ColorBufferViewport::create();

            cvp1->setCamera    ( deco );
            cvp1->setBackground( bkgnd );
            cvp1->setRoot      ( root );
            cvp1->setSize      ( 0,0, 1,1 );
            cvp1->setRed(GL_FALSE);
            cvp1->setGreen(GL_TRUE);
            cvp1->setBlue(GL_TRUE);
            cvp1->setAlpha(GL_TRUE);

        vp1 = cvp1;
        
        // right
        deco=OSG::ShearedStereoCameraDecorator::create();

            deco->setLeftEye(false);
            deco->setEyeSeparation(eyedistance);
            deco->setDecoratee(cam);
            deco->setZeroParallaxDistance(zeroparallax);
        
        OSG::ColorBufferViewportUnrecPtr cvp2 = 
            OSG::ColorBufferViewport::create();

            cvp2->setCamera    ( deco );
            cvp2->setBackground( bkgnd );
            cvp2->setRoot      ( root );
            cvp2->setSize      ( 0,0,1,1 );
            cvp2->setRed(GL_TRUE);
            cvp2->setGreen(GL_FALSE);
            cvp2->setBlue(GL_FALSE);
            cvp2->setAlpha(GL_FALSE);

        vp2 = cvp2;
    }

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );
    

    if(serverx>0 && servery>0)
        clusterWindow->setSize( serverx, servery );
    else
        clusterWindow->setSize( glvp[2], glvp[3] );
    clusterWindow->addPort( vp1 );

    if(multiport || stereoMode > 0)
        clusterWindow->addPort( vp2 );

    if(serviceAddressValid == true)
    {
        clusterWindow->setServiceAddress(serviceAddress);

        fprintf(stderr, "tcclient use ba %s\n", serviceAddress.c_str());
    }

    // tball

    OSG::Vec3f pos(min[0] + ((max[0] - min[0]) * 0.5),
                   min[1] + ((max[1] - min[1]) * 0.5),
                   max[2] + ( max[2] - min[2] ) * 1.5 );

    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    tball.setMode( OSG::Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(center);
    tball.setTranslationGen(OSG::Trackball::OSGAbsoluteTranslation);

    // run...
    std::cout << size.length() << std::endl;
    cam->setFar (size.length() * 100.0);
    cam->setNear(size.length() * 100.0 / 10000.0);
}

int doMain(int argc,char **argv)
{
    int                      i,winid;
    char                    *opt;
    std::vector<std::string> filenames;
    std::vector<std::string> servers;
    std::string              connectionType = "Multicast";
//    std::string              connectionType = "StreamSock";
    std::string              connectionParameters;
    int                      rows=1;
    char                     type='M';
    bool                     clientRendering=true;
#ifdef HAVE_SORT
    bool                     compose=false;
#endif

    std::string              composerType="";
#ifdef HAVE_SORT
    OSG::ImageComposer           *composer=NULL;
#endif
    std::string              autostart;
    
    for(i=1;i<argc;i++)
    {
        if(strlen(argv[i])>1 && argv[i][0]=='-')
        {
            switch(argv[i][1])
            {
                case 'o':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    connectionParameters = opt;
                    printf("connectionParameters: '%s'\n", connectionParameters.c_str());
                    break;
                case 'A':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    autostart = opt;
                    break;
                case 'D':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    if(sscanf(opt,"%f,%f,%f",&ca,&cb,&cc)!=3)
                    {
                        std::cout << "Copy opton -D x,y,z" << std::endl;
                        return 1;
                    }
                    break;
                case 'b':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    serviceAddress.assign(opt);
                    serviceAddressValid = true;
                    break;
                case 'f':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    filenames.push_back(opt);
                    printf("<%s>\n",opt);
                    break;
                case 'm':
                    connectionType="Multicast";
                    break;
                case 'r':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    rows=atoi(opt);
                    break;
                case 't':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    subtilesize=atoi(opt);
                    break;
#ifdef FRAMEINTERLEAVE
                case 'i':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    interleave=atoi(opt);
                    break;
#endif
#ifdef HAVE_SORT
                case 'C':
                    compose=true;
                    break;
#endif
                case 'F':
                    type='F';
                    break;
                case 'P':
                    type='P';
                    break;
                case 'L':
                {
                    type='L';
                    int lpos=2;
                    while(argv[i][lpos])
                    {
                        if(argv[i][lpos] == 'B') 
                            composerType = "BinarySwapComposer";
                        if(argv[i][lpos] == 'P')
                            composerType = "PipelineComposer";
                        if(argv[i][lpos] == 'S')
                            composerType = "SepiaComposer";
                        ++lpos;
                    }
                    break;
                }
                case 'M':
                    type='M';
                    break;
                case 'I':
                    type='I';
                    break;
                case 's':
                    stereoMode=1;
                    break;
                case 'c':
                    stereoMode=2;
                    break;
                case 'p':
                    info=true;
                    break;
                case 'e':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    sscanf(opt,"%f",&eyedistance);
                    break;
                case 'z':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    sscanf(opt,"%f",&zeroparallax);
                    break;
                case 'd':
                    clientRendering=false;
                    break;
                case 'v':
                    multiport=true;
                    break;
                case 'x':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    sscanf(opt,"%d",&serverx);
                    break;
                case 'y':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    sscanf(opt,"%d",&servery);
                    break;
                case 'a':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    animName=opt;
                    loadAnim();
                    glutIdleFunc(display);       
                    animate=true;
                    break;
                case 'l':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    if(sscanf(opt,"%d,%d",&animLoops,&animLength) != 2)
                    {
                        animLength = 30;
                        if(sscanf(opt,"%d",&animLoops) != 1)
                        {
                            animLoops = -1;
                        }
                    }
                    break;
                case 'g':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    sscanf(opt,"%d,%d",&winwidth,&winheight);
                    break;
                case 'G':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    connectionDestination = opt;
                    break;
                case 'i':
                    argv[i][2] != '\0' ? opt=argv[i]+2 : opt=argv[++i];
                    connectionInterface = opt;
                    break;
                case 'h':
                    std::cout << argv[0] 
                              << "-ffile -m -rrows -C -M"
                              << std::endl;
                    std::cout << "-m  use multicast" << std::endl
                              << "-G  multicast group" << std::endl
                              << "-i  interface" << std::endl
                              << "-M  multi display" << std::endl
#ifdef FRAMEINTERLEAVE
                              << "-I  frame interleave" << std::endl
#endif
                              << "-r  number of display rows" << std::endl
                              << "-C  compose" << std::endl
                              << "-F  sort-first" << std::endl
                              << "-L  sort-last" << std::endl
                              << "-h  this msg" << std::endl
                              << "-s  stereo" << std::endl
                              << "-c  red/cyan stereo" << std::endl
                              << "-e  eye distance" << std::endl
                              << "-z  zero parallax" << std::endl
                              << "-d  disable client rendering"<<std::endl
                              << "-v  use two viewports" << std::endl
                              << "-x  server x resolution" << std::endl
                              << "-y  server y resolution" << std::endl
                              << "-t  subtile size for img composition" << std::endl
                              << "-D  x,y,z duplicate geometry" << std::endl
                              << "-A  Autostart command" << std::endl
                              << "-o  connection parameter string e.g. \"TTL=8\"" << std::endl;
                    return 0;
            }
        }
        else
        {
            servers.push_back(argv[i]);
        }
    }

    if(servers.size() == 0)
    {
        servers.push_back("foo");
    }

    OSG::osgInit(argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize(winwidth,winheight);
    winid = glutCreateWindow("OpenSG Cluster Client");
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    ract = OSG::RenderAction::create();
    
    // clear changelist from prototypes
    OSG::Thread::getCurrentChangeList()->clear();

    // create cluster window
    switch(type)
    {
        case 'M': 
            multidisplay=OSG::MultiDisplayWindow::create();
            clusterWindow=multidisplay;
            break;
#ifdef HAVE_SORT
        case 'F':
            sortfirst=OSG::SortFirstWindow::create();
            
            if(compose)
                sortfirst->setCompose(true);
            else
                sortfirst->setCompose(false);
            
            clusterWindow=sortfirst;
            break;
        case 'L':
            sortlast=OSG::SortLastWindow::create();
            
            if(!composerType.empty())
            {
                OSG::FieldContainerPtr fcPtr = 
                    OSG::FieldContainerFactory::the()->
                    createFieldContainer(composerType.c_str());
                OSG::ImageComposerPtr icPtr = cast
                    _dynamic<OSG::ImageComposerPtr>(fcPtr);
                
                if(icPtr != NULL)
                {
/*
  if(PipelineComposerPtr::dcast(icPtr) != NULL)
  PipelineComposerPtr::dcast(icPtr)->setTileSize(subtilesize);
  if(BinarySwapComposerPtr::dcast(icPtr) != NULL)
  BinarySwapComposerPtr::dcast(icPtr)->setTileSize(subtilesize);
 */
                    icPtr->setStatistics(info);
//                        icPtr->setShort(false);
                    sortlast->setComposer(icPtr);
                }
            }
            clusterWindow=sortlast;
            break;
#endif
#ifdef FRAMEINTERLEAVE
        case 'I':
            frameinterleaveOSG::=FrameInterleaveWindow::create();
            clusterWindow=frameinterleave;
            if(compose)
                frameinterleave->setCompose(true);
            else
                frameinterleave->setCompose(false);
            break;
#endif
#ifdef HAVE_SORT
        case 'P':
            sortfirst=OSG::SortFirstWindow::create();
            sortfirst->setCompose(false);
            clusterWindow=sortfirst;
            break;
#endif
    }
    
    if(!autostart.empty())
        clusterWindow->editMFAutostart()->push_back(autostart);
    
    for(i=0 ; OSG::SizeT(i)<servers.size() ; ++i)
        clusterWindow->editMFServers()->push_back(servers[i]);
    switch(type)
    {
        case 'M': 
            multidisplay->setHServers(
                clusterWindow->getMFServers()->size()/rows);
            multidisplay->setVServers(
                rows);
            break;
    }
#ifdef FRAMEINTERLEAVE
    clusterWindow->setInterleave(interleave);
#endif
    
    // create client window
    clientWindow=OSG::GLUTWindow::create();
//        glutReshapeWindow(800,600);
    glutReshapeWindow(winwidth,winheight);
    clientWindow->setGlutId(winid);
    clientWindow->init();
    
    // init scene graph
    init(filenames);
    
    // init client
    clusterWindow->setConnectionType(connectionType);
    // needs to be called before init()!
    clusterWindow->setConnectionParams(connectionParameters);
    if(clientRendering)
    {
        clusterWindow->setClientWindow(clientWindow);
    }
    clusterWindow->init();
    clusterWindow->resize(winwidth,winheight);
    clientWindow->resize(winwidth,winheight);
    clusterWindow->setConnectionDestination(connectionDestination);
    clusterWindow->setConnectionInterface(connectionInterface);
    
    return 0;
}

int main(int argc,char **argv)
{
    doMain(argc, argv);

    glutMainLoop();

    return 0;
}

#else

int main (int argc, char **argv)
{
    return 0;
}

#endif

