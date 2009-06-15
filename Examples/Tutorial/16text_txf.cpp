// Some needed include files
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGTextTXFFace.h>
#include <OpenSG/OSGTextLayoutParam.h>
#include <OpenSG/OSGTextLayoutResult.h>
#include <iostream>

// The SimpleSceneManager is a little usefull class which helps us to
// manage little scenes. It will be discussed in detail later on
OSG::SimpleSceneManager *mgr;

// We have a forward declaration here, just to sort the code
int setupGLUT(int *argc, char *argv[]);

int main(int argc, char *argv[])
{
    // Init the OpenSG subsystem
    OSG::osgInit(argc, argv);

    {
        // We create a GLUT Window (that is almost the same for most applications)
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // Create the face
        std::string family = "SANS";
        OSG::TextFace::Style style = OSG::TextFace::STYLE_PLAIN;
        OSG::TextTXFParam txfParam;
        txfParam.size = 46;
        txfParam.gap = 1;
        txfParam.setCharacters("Hello World!");
        txfParam.textureWidth = 0;
        OSG::TextTXFFaceRefPtr face = 
            OSG::TextTXFFace::create(family, style, txfParam);
        if (face == 0)
        {
            std::cerr << "ERROR: Cannot create face object!" << std::endl;
            return -1;
        }
    
        // Lay out one single line of text
        std::string text = "Hello World!"; // Use UTF-8 encoding!
        OSG::TextLayoutParam layoutParam;
        layoutParam.horizontal = true;
        layoutParam.leftToRight = true;
        layoutParam.topToBottom = true;
        layoutParam.majorAlignment = OSG::TextLayoutParam::ALIGN_FIRST;
        layoutParam.minorAlignment = OSG::TextLayoutParam::ALIGN_FIRST;
        layoutParam.spacing = 1.f;
        layoutParam.length.push_back(0.f);
        layoutParam.maxExtend = 0.f;
        OSG::TextLayoutResult layoutResult;
        face->layout(text, layoutParam, layoutResult);
    
        // Create the text geometry
        OSG::Real32 scale = 1.f;
        OSG::NodeRecPtr scene = face->makeNode(layoutResult, scale);
    
        // Get the texture that contains the characters of the font
        OSG::ImageRecPtr image = face->getTexture();
    
        // Create the texture that will hold the image
        OSG::SimpleTexturedMaterialRecPtr tex = 
            OSG::SimpleTexturedMaterial::create();
        tex->setImage(image);
        tex->setEnvMode(GL_MODULATE);
        tex->setDiffuse(OSG::Color3f(1, 0, 0));
    
        // Assign the texture to the geometry
        OSG::GeometryRecPtr geo = 
            dynamic_cast<OSG::Geometry *>(scene->getCore());
        geo->setMaterial(tex);
    
        // Create and setup the SSM
        mgr = new OSG::SimpleSceneManager;
        mgr->setWindow(gwin);
        mgr->setRoot(scene);
    
        // Create a blue background
        OSG::SolidBackgroundRecPtr bg = OSG::SolidBackground::create();
        bg->setColor(OSG::Color3f(0.1, 0.1, 0.5));
        
        gwin->getPort(0)->setBackground(bg);
    
        mgr->showAll();
        
        OSG::commitChanges();
    }

    // Give Control to the GLUT Main Loop
    glutMainLoop();

    return 0;
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// just redraw our scene if this GLUT callback is invoked
void display()
{
    mgr->redraw();
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

// The GLUT subsystem is set up here. This is very similar to other GLUT
// applications If you have worked with GLUT before, you may have the feeling
// of meeting old friends again, if you have not used GLUT before that is no
// problem. GLUT will be introduced briefly in the next section.

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG TXF Text Example");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);

    return winid;
}
