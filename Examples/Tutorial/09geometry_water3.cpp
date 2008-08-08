// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGGeometry.h>

#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>

OSG_USING_NAMESPACE

// this will specify the resolution of the mesh
#define N   100

//the two dimensional array that will store all height values
Real32 wMesh[N][N];

//the origin of the water mesh
Pnt3f wOrigin = Pnt3f(0,0,0);

//width and length of the mesh
UInt16 width = 100;
UInt16 length = 100;

SimpleSceneManager *mgr;
NodeRecPtr          scene;

int setupGLUT( int *argc, char *argv[] );

void updateMesh(Real32 time)
{
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++)
            wMesh[x][z] = 10*cos(time/1000.f + (x+z)/10.f);
}

NodeTransitPtr createScenegraph(void)
{
    // the scene must be created here
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            wMesh[i][j] = 0;
    
    // the types of primitives that are used - an integerer propery
    GeoUInt8PropertyRecPtr types = GeoUInt8Property::create();
    
    // we want to use quads ONLY 
    types->addValue(GL_QUADS);
    
    // the number of vertices (or indices) we want to use with the primitive
    // type; types and lengths always have the same number of elements
    // (here both have just one)
    GeoUInt32PropertyRecPtr lengths = GeoUInt32Property::create();
    // the length of our quads is four ;-)
    lengths->addValue(4 * (N - 1) * (N - 1));

    // GeoPnt3fProperty stores the positions of all vertices used in
    // this specific geometry core
    GeoPnt3fPropertyRecPtr pos = GeoPnt3fProperty::create();
    // here they all come
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++)
            pos->addValue(Pnt3f(x, wMesh[x][z], z));

    // GeoColor3fProperty stores all color values that will be used
    GeoColor3fPropertyRecPtr colors = GeoColor3fProperty::create();
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++)
            colors->addValue(Color3f(0,0,1));
    
    // and finally the normals are stored in a GeoVec3fProperty
    GeoVec3fPropertyRecPtr norms = GeoVec3fProperty::create();
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++)
            // As initially all heights are set to zero thus yielding a plane,
            // we set all normals to (0,1,0) parallel to the y-axis
            norms->addValue(Vec3f(0,1,0));
    
    SimpleMaterialRecPtr mat = SimpleMaterial::create();
    
    // Indices define the order in which the entries in the above properties
    // are used
    GeoUInt32PropertyRecPtr indices = GeoUInt32Property::create();
    for (int x = 0; x < N-1; x++)
    {
        for (int z = 0; z < N-1; z++)
        {
            // points to four vertices that will
            // define a single quad
            indices->addValue( z    * N + x    );
            indices->addValue((z+1) * N + x    );
            indices->addValue((z+1) * N + x + 1);
            indices->addValue( z    * N + x + 1);
        }
    }

    GeometryRecPtr geo = Geometry::create();

    geo->setTypes    (types  );
    geo->setLengths  (lengths);
    geo->setIndices  (indices);
    geo->setPositions(pos    );
    geo->setNormals  (norms  );
    geo->setMaterial (mat    );
    geo->setColors   (colors );
    
    // Turn off creation of display lists, since the geometry changes each
    // frame
    geo->setDlistCache(false);
    
    NodeRecPtr root = Node::create();
    root->setCore(geo);

    return NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        GLUTWindowRecPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        scene =createScenegraph();
    
        mgr = new SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        Navigator * nav = mgr->getNavigator();
        nav->setFrom(nav->getFrom()+Vec3f(0,50,0));
        
        commitChanges();
    }
    
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    Real32 time = glutGet(GLUT_ELAPSED_TIME);
    updateMesh(time);
    
    // we extract the core out of the root node
    // as we now this is a geometry node
    GeometryRecPtr geo = dynamic_cast<Geometry *>(scene->getCore());
    
    //now modify it's content
    
    // first we need a pointer to the position data field
    GeoPnt3fPropertyRecPtr pos = dynamic_cast<GeoPnt3fProperty *>(geo->getPositions());
    
    //get the data field the pointer is pointing at
    GeoPnt3fProperty::StoredFieldType *posfield = pos->editFieldPtr();
    //get some iterators
    GeoPnt3fProperty::StoredFieldType::iterator last, it;

    // set the iterator to the first data
    it = posfield->begin();
    
    //now simply run over all entires in the array
    for (int x = 0; x < N; x++)
    {
        for (int z = 0; z < N; z++)
        {
            (*it) = Pnt3f(x, wMesh[x][z], z);
            it++;
        }
    }
    
    mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    
    return winid;
}

