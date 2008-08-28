// OpenSG Tutorial Example: Identification buffer
//
// This tutorial shows how to use the identification color technique so as to
// identify objects in a fast way. ( get its Node * )
//
//  - This method is view dependant (we do picking only from the viewpoint), but you can specify
//      your viewpoint with setCamera().
//  - This method doesn't handle transparency.
//  - This method doesn't handle anti-aliasing, this can lead to some imperfections in
//      identification.
//
// If you need more, it is possible to retreive the 3D point by using Z-buffer information.
// It's also possible to send a ray throught the geometry of the identified object so as to
// retrieve the corresponding triangle. (Sending ray through the whole scene is really
// computationaly expensive in OpenSG).
//
// To do that we add a switchMaterial to each geometry. In this way, we can choose between
// the normal material, and the color identification one. Then when requested, we render
// the scene to a RAM-buffer (with the GrabForeground method), and call the getObject() 
// method on it.
//
// Note that this method is suitable for high amount of getObject() calls over a single
// frame.
//
// Use Space to pick.
//

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGGrabForeground.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSwitchMaterial.h>

#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>

#include <map>
#include <list>

OSG_USING_NAMESPACE
using namespace std;

struct color_compare
{
    bool operator()(const Color4ub &s1, const Color4ub &s2) const
    {
        return s1.getRGBA() < s2.getRGBA();
    }
};


class IDbuffer
{
public:
    IDbuffer(void)
    {
        _ID_buffer = NULL;
        
        // We fix the Sky color to black
        _solidBkg = SolidBackground::create();
        _solidBkg->setColor(Color3f(0,0,0));

        _ID_viewport = Viewport::create();
        _ID_viewport->setBackground(_solidBkg);
        _ID_viewport->setSize(0,0,1,1);

        _window = PassiveWindow::create();
        _window->addPort(_ID_viewport);

        _ID_renderAction = RenderAction::create();

        // These parameters depends of your implementation. Use the sames as in your project.
        _ID_renderAction->setAutoFrustum(true);
        _ID_renderAction->setOcclusionCulling(true);

        initColors();
    }

    ~IDbuffer(void)
    {
        delete _ID_renderAction;
    }

    void setRoot(Node * const value)
    {
        _switches.clear();
        convertToColorIdentificationSwitchable(value);
        _ID_viewport->setRoot(value);
    }

    void setCamera(Camera * const value)
    {
        _ID_viewport->setCamera(value);
    }

    Node *getSky(void) 
    {
        return _sky;
    }

    Node *get_object(int x, int y)
    {
        if(x>=_w || y >=_h || _ID_buffer==NULL)
            return NULL;
        y = _h - y;
        // Once rendered, we check in the buffer to get the Object ID color.
        Color4ub c = Color4ub(  _ID_buffer[4*(y*_w+x)],
                                _ID_buffer[4*(y*_w+x)+1],
                                _ID_buffer[4*(y*_w+x)+2],
                                _ID_buffer[4*(y*_w+x)+3] );
        
        // And we find the corresponding Node.
        NodeIndexMap::iterator i = _node_index.find(c);
        if(i != _node_index.end())
        {
            return (*i).second;
        }
        else
        {
            return NULL;
        }
    }

    void reshape(int x, int y)
    {
        _w=x;
        _h=y;
        _window->resize(x,y);
    }

    void update_render_GrabForeGround(void)
    {
        // Setup the GrabForeground
        _grabber = GrabForeground::create();

        ImageRefPtr img = Image::create();
        img->set(GL_RGBA,_w,_h);
        _grabber->setImage(img);
        _grabber->setAutoResize(false);
        _grabber->setActive(false);

        // Putting it to the viewport
        _window->getPort(0)->editMFForegrounds()->push_back(_grabber);

        // We toggle the switch material so as to render identification colors.
        switchToIDbuffer();

        _grabber->setActive(true);

        commitChanges();
        
        // We render to the grabber
        _window->render(_ID_renderAction);

        _grabber->setActive(false);
        
        // We get the data back
        if(_grabber->getImage()->getData() != NULL)
            _ID_buffer = _grabber->getImage()->getData();

        // We toggle to standard materials
        switchToNormal();

        // we remove the Grabber
        Viewport::MFForegroundsType::iterator i =
            _window->getPort(0)->editMFForegrounds()->find(_grabber);
        
        if(i != _window->getPort(0)->getMFForegrounds()->end())
            _window->getPort(0)->editMFForegrounds()->erase(i);
    }

private:
    // Methods
    void initColors()
    {
        ci = 255;
        cj = 255;
        ck = 255;

        _sky = Node::create();
        Color4ub c = Color4ub(0,0,0,255);
        _node_index[c] = _sky;
    }

    Color4ub create_new_color()
    {
        // With this, we are ready for 255^3 objects.
        if(ci > 1)
        {
            ci--;
        }
        else if(cj > 1)
        {
            cj--;
            ci = 255;
        }
        else if(ck > 1)
        {
            ck--;
            ci = cj = 255;
        }
        else
        {
            cerr << "Cdrawing::create_new_color()  NO MORE COLOR FREE !!!! TOO MANY OBJECTS ... Gloups " << endl;
            // Note that we can extend to 255^4 objects with the alpha channel
        }
        return Color4ub(ci,cj,ck,255);
        // Note that the color (0,0,0,255) is reserved so as to identify the sky
    }

    void convertToColorIdentificationSwitchable(Node * const root)
    {
        // This is a recursive traversal of the Scene Graph, so as to replace
        // each material by a SwitchMaterial, in wich we put the normal one on one
        // side, and the color identification one in other side.
        UInt32 children = root->getNChildren();

        if(root->getCore()->getType().isDerivedFrom(MaterialGroup::getClassType()))
        {
            // Need to turn off material groups, as they would override our
            // geo-specific materials
            // Just record them here.
            
            MaterialGroup *mg = dynamic_cast<MaterialGroup *>(root->getCore());

            _mgswitches.push_back(MaterialGroupList::value_type(mg, NULL));
        }
        
        if(root->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
        {

            Geometry *geo = dynamic_cast<Geometry *>(root->getCore());

            // If we get a Geometry, we replace it by a switch, 
            // we add this geometry a SwitchMaterial, with its original material
            // in one case, and a chunkmaterial corresponding to the node ID in the other.
            Color4ub c = create_new_color();
            Color4f cf;
            cf.setRGBA(c.getRGBA());
            // We add the associated pair color/node to the map
            //_node_index[c] = root;
            _node_index [c] = root;

            PolygonChunkRefPtr  pc = PolygonChunk::create();
            pc->setSmooth(false);

            MaterialChunkRefPtr mc = MaterialChunk::create();
            mc->setLit(false);
            mc->setEmission(cf);
            mc->setDiffuse(cf);

            ChunkMaterialRefPtr cm = ChunkMaterial::create();
            cm->addChunk(pc);
            cm->addChunk(mc);

            Material             *mat = geo->getMaterial();
            SwitchMaterialRefPtr  sw  = SwitchMaterial::create();

            sw->addMaterial(mat);        // Choice 0
            sw->addMaterial(cm);        // Choice 1

            geo->setMaterial(sw);

            _switches.push_back(sw);
        }
        
        // check all children
        for (int i = 0; i < children; i++)
        {
            convertToColorIdentificationSwitchable(root->getChild(i));
        }
    }

    // Toggles to color identification
    void switchToIDbuffer(void)
    {
        SwitchList::iterator i = _switches.begin();
        while(i != _switches.end())
        {
            (*i)->setChoice(1);
            i++;
        }
        
        MaterialGroupList::iterator j = _mgswitches.begin();
        while(j != _mgswitches.end())
        {
            (*j).second = (*j).first->getMaterial();
            (*j).first->setMaterial(NULL);
            j++;
        }
    }

    // Toggles to normal materials.
    void switchToNormal(void)
    {
        SwitchList::iterator i = _switches.begin();
        while(i != _switches.end())
        {
            (*i)->setChoice(0);
            i++;
        }
        
        MaterialGroupList::iterator j = _mgswitches.begin();
        while(j != _mgswitches.end())
        {
            (*j).first->setMaterial((*j).second);
            j++;
        }
    }

    // Types
    typedef std::map<Color4ub, NodeRefPtr, color_compare> NodeIndexMap;
    typedef std::list<SwitchMaterialRefPtr>               SwitchList;
    typedef std::list<std::pair<MaterialGroupRefPtr,
                                MaterialRefPtr      > >   MaterialGroupList;
    
    // Variables
    GrabForegroundRefPtr        _grabber;
    ViewportRefPtr              _ID_viewport;
    RenderAction *              _ID_renderAction;
    PassiveWindowRefPtr         _window;
    SolidBackgroundRefPtr       _solidBkg;        // Sky color is black
    NodeRefPtr                  _sky;

    SwitchList                  _switches;        // Switchs to change from normal to ID material
    MaterialGroupList           _mgswitches;

    // List of used colors for Identification
    NodeIndexMap                _node_index;

    const UInt8 *               _ID_buffer;         // Ram version of the ID buffer
    int                         _w, _h;            // buffer size

    int ci,cj,ck;    // for colors generations
};

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
// The file root node, needed for intersection
NodeRefPtr fileroot;
// The points used for visualising the ray and hit object
GeoPnt3fPropertyRefPtr isectPoints;
// The visualisation geometry, needed for update.
GeometryRefPtr testgeocore;

IDbuffer*    _idbuff;



// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            delete mgr;
            delete _idbuff;
            
            fileroot    = NULL;
            isectPoints = NULL;
            testgeocore = NULL;
            
            OSG::osgExit();
            exit(0);
        }
        break;

        case ' ':   // check the object under the clicked pixel
        {
            _idbuff->update_render_GrabForeGround();
            Node *found = _idbuff->get_object(x,y);  

            if( found == _idbuff->getSky() )
            {
                std::cout<<"Picking : Sky found"<<std::endl;
            }
            else if( found != NULL )
            {
                const Char8 *n = getName(found);
                if(n == NULL)
                    n = "Unnamed";
                
                std::cout << "Picking : Object found : " 
                          << n << " (node=" << found << ")" << std::endl;
            }
            else
            {
                std::cerr << "Problem..." << std::endl;
            }

        }
        break;
    }
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        GLUTWindowRefPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // The scene group
        
        NodeRefPtr  scene = Node::create();
        GroupRefPtr g     = Group::create();
        
        scene->setCore(g);
        
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
            FWARNING(("Supported file formats:\n"));
            
            std::list<const char*> suffixes;
            SceneFileHandler::the()->getSuffixList(suffixes);
            
            for(std::list<const char*>::iterator it  = suffixes.begin();
                                                 it != suffixes.end();
                                               ++it)
            {
                FWARNING(("%s\n", *it));
            }
    
            fileroot = makeTorus(.5, 2, 16, 16);
        }
        else
        {
            fileroot = SceneFileHandler::the()->read(argv[1]);
            /*
                All scene file loading is handled via the SceneFileHandler.
            */
        }
    
        scene->addChild(fileroot);
        
        // Create a small geometry to show the ray and what was hit
        // Contains a line and a single triangle.
        // The line shows the ray, the triangle whatever was hit.
        
        SimpleMaterialRefPtr red = SimpleMaterial::create();
        
        red->setDiffuse     (Color3f( 1,0,0 ));   
        red->setTransparency(0.5);   
        red->setLit         (false);   
    
        isectPoints = GeoPnt3fProperty::create();
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
    
        GeoUInt32PropertyRefPtr index = GeoUInt32Property::create();
        index->addValue(0);
        index->addValue(1);
        index->addValue(2);
        index->addValue(3);
        index->addValue(4);
    
        GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
        lens->addValue(2);
        lens->addValue(3);
        
        GeoUInt8PropertyRefPtr type = GeoUInt8Property::create();
        type->addValue(GL_LINES);
        type->addValue(GL_TRIANGLES);
    
        testgeocore = Geometry::create();
        testgeocore->setPositions(isectPoints);
        testgeocore->setIndices(index);
        testgeocore->setLengths(lens);
        testgeocore->setTypes(type);
        testgeocore->setMaterial(red);
        
        NodeRefPtr testgeo = Node::create();
        testgeo->setCore(testgeocore);
        
        scene->addChild(testgeo);
    
        // create the SimpleSceneManager helper
        mgr = new SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
    
        // show the whole scene
        mgr->showAll();
    
        mgr->getCamera()->setNear(mgr->getCamera()->getNear() / 10);
    
        // Show the bounding volumes? Not for now
        mgr->getRenderAction()->setVolumeDrawing(false);
    
        _idbuff = new IDbuffer();
        _idbuff->setCamera(mgr->getCamera());
        _idbuff->setRoot(scene);
    }
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    _idbuff->reshape(w,h);

    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
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

