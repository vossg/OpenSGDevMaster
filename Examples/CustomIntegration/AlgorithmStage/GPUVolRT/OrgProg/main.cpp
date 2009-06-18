
// --------------------------------------------------------------------------
// GPU raycasting tutorial
// Made by Peter Trier jan 2007
//
// This file contains all the elements nessesary to implement a simple 
// GPU volume raycaster.
// Notice this implementation requires a shader model 3.0 gfxcard
// --------------------------------------------------------------------------

#define GL_GLEXT_PROTOTYPES

#define USE_CGX

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cassert>
#include "Vector3.h"

#define MAX_KEYS 256
#define WINDOW_SIZE 800
#define VOLUME_TEX_SIZE 128

using namespace std;

// Globals ------------------------------------------------------------------

bool gKeys[MAX_KEYS];
bool toggle_visuals = true;
GLuint renderbuffer; 
GLuint framebuffer; 
GLuint volume_texture; // the volume texture
GLuint backface_buffer; // the FBO buffers
GLuint final_image;
float stepsize = 1.0/50.0;
float mModelView[16];
float mProj[16];

GLuint vertexprog;
GLuint fragmentprog;
GLuint shaderprog;
GLuint stepsizeLoc;
GLuint mvLoc;
GLuint mpLoc;
GLuint texLoc;
GLuint volumeTexLoc;

/// Implementation ----------------------------------------

void set_tex_param(GLuint texLoc, GLuint tex, GLuint prog, 
                   GLuint unit,   GLuint target) 
{
    glActiveTexture(unit);
    glBindTexture(target, tex);

    glUniform1i(texLoc, unit - GL_TEXTURE0);

    glActiveTexture(GL_TEXTURE0);
}


bool readProgram(std::string  &szTarget,
                 std::istream &iStream)
{
#define BUFSIZE 200
    
    szTarget.erase();

    char buf[BUFSIZE];

    if(!iStream.good())
    {
        fprintf(stderr, "SHLChunk::readProgram: stream is not good!\n");

        return false;
    }
    
    do
    {
        iStream.read(buf, BUFSIZE);

        szTarget.append(buf, iStream.gcount());
    }
    while(!iStream.eof());
    
    return true;
}

void check_shader_status(GLuint uiShader)
{
    GLint iStatus = 0;
    
    glGetShaderiv( uiShader, 
                   GL_COMPILE_STATUS, 
                  &iStatus);

    if(iStatus == 0)
    {
        char *szDebug;
        GLint  iDebugLength;

        glGetShaderiv( uiShader, 
                       GL_INFO_LOG_LENGTH, 
                      &iDebugLength);

        szDebug = new char[iDebugLength];

        glGetShaderInfoLog( uiShader, 
                            iDebugLength, 
                           &iDebugLength, 
                            szDebug     );

        fprintf(stderr, "Couldn't compile shader program (0x%x)!\n%s\n", 
                uiShader,
                szDebug);

        delete [] szDebug;
    }
}

void check_program_status(GLuint uiProgram)
{
    GLint  iInfoLength;
    char  *szInfoBuffer = NULL;

    glGetProgramiv( uiProgram, 
                    GL_OBJECT_INFO_LOG_LENGTH_ARB, 
                   &iInfoLength);

    if(iInfoLength > 0)
    {
        szInfoBuffer = new char[iInfoLength];
        szInfoBuffer[0] = '\0';
        
        glGetProgramInfoLog( uiProgram, 
                             iInfoLength, 
                            &iInfoLength, 
                             szInfoBuffer);
    }

    GLint iStatus = 0;
    
    glGetProgramiv(uiProgram, GL_LINK_STATUS, &iStatus);
    
    if(iStatus == 0)
    {
        if(szInfoBuffer != NULL && szInfoBuffer[0] != '\0')
        {
            fprintf(stderr, "Couldn't link vertex and fragment program!\n%s\n",
                    szInfoBuffer);
        }
        else
        {
            fprintf(stderr,"Couldn't link vertex and fragment program!\n"
                    "No further info available\n");
        }
    }
}

// load_vertex_program: loading a vertex program
void load_vertex_program(GLuint &v_program, char *shader_path)
{
    std::ifstream s(shader_path);
    std::string   szTmp;

    if(readProgram(szTmp, s) == true)
    {
        v_program = glCreateShader(GL_CG_VERTEX_SHADER_EXT);

        const char *source = szTmp.c_str();
        glShaderSource(v_program, 
                       1, 
                       static_cast<const char **>(&source), 
                       0);

        glCompileShader(v_program);

        check_shader_status(v_program);
    }
}

// load_fragment_program: loading a fragment program
void load_fragment_program(GLuint &f_program, char *shader_path)
{
    std::ifstream s(shader_path);
    std::string   szTmp;

    if(readProgram(szTmp, s) == true)
    {
        f_program = glCreateShader(GL_CG_FRAGMENT_SHADER_EXT);

        const char *source = szTmp.c_str();
        glShaderSource(f_program, 
                       1, 
                       static_cast<const char **>(&source), 
                       0);

        glCompileShader(f_program);

        check_shader_status(f_program);
    }
}

void enable_renderbuffers()
{
	glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, framebuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
}

void disable_renderbuffers()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void vertex(float x, float y, float z)
{
	glColor3f(x,y,z);
	glMultiTexCoord3fARB(GL_TEXTURE1_ARB, x, y, z);
	glVertex3f(x,y,z);
}
// this method is used to draw the front and backside of the volume
void drawQuads(float x, float y, float z)
{
	
	glBegin(GL_QUADS);
	/* Back side */
	glNormal3f(0.0, 0.0, -1.0);
	vertex(0.0, 0.0, 0.0);
	vertex(0.0, y, 0.0);
	vertex(x, y, 0.0);
	vertex(x, 0.0, 0.0);

	/* Front side */
	glNormal3f(0.0, 0.0, 1.0);
	vertex(0.0, 0.0, z);
	vertex(x, 0.0, z);
	vertex(x, y, z);
	vertex(0.0, y, z);

	/* Top side */
	glNormal3f(0.0, 1.0, 0.0);
	vertex(0.0, y, 0.0);
	vertex(0.0, y, z);
    vertex(x, y, z);
	vertex(x, y, 0.0);

	/* Bottom side */
	glNormal3f(0.0, -1.0, 0.0);
	vertex(0.0, 0.0, 0.0);
	vertex(x, 0.0, 0.0);
	vertex(x, 0.0, z);
	vertex(0.0, 0.0, z);

	/* Left side */
	glNormal3f(-1.0, 0.0, 0.0);
	vertex(0.0, 0.0, 0.0);
	vertex(0.0, 0.0, z);
	vertex(0.0, y, z);
	vertex(0.0, y, 0.0);

	/* Right side */
	glNormal3f(1.0, 0.0, 0.0);
	vertex(x, 0.0, 0.0);
	vertex(x, y, 0.0);
	vertex(x, y, z);
	vertex(x, 0.0, z);
	glEnd();
	
}

// create a test volume texture, here you could load your own volume
void create_volumetexture()
{
	int size = VOLUME_TEX_SIZE*VOLUME_TEX_SIZE*VOLUME_TEX_SIZE* 4;
	GLubyte *data = new GLubyte[size];

	for(int x = 0; x < VOLUME_TEX_SIZE; x++)
	{for(int y = 0; y < VOLUME_TEX_SIZE; y++)
	{for(int z = 0; z < VOLUME_TEX_SIZE; z++)
	{
		data[(x*4)   + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = z%250;
		data[(x*4)+1 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = y%250;
		data[(x*4)+2 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		data[(x*4)+3 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 230;
	  	
		Vector3 p =	Vector3(x,y,z)- Vector3(VOLUME_TEX_SIZE-20,VOLUME_TEX_SIZE-30,VOLUME_TEX_SIZE-30);
		bool test = (p.length() < 42);
		if(test)
			data[(x*4)+3 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 0;

		p =	Vector3(x,y,z)- Vector3(VOLUME_TEX_SIZE/2,VOLUME_TEX_SIZE/2,VOLUME_TEX_SIZE/2);
		test = (p.length() < 24);
		if(test)
			data[(x*4)+3 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 0;

		
		if(x > 20 && x < 40 && y > 0 && y < VOLUME_TEX_SIZE && z > 10 &&  z < 50)
		{
			
			data[(x*4)   + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 100;
		    data[(x*4)+1 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		    data[(x*4)+2 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = y%100;
			data[(x*4)+3 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		}

		if(x > 50 && x < 70 && y > 0 && y < VOLUME_TEX_SIZE && z > 10 &&  z < 50)
		{
			
			data[(x*4)   + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		    data[(x*4)+1 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		    data[(x*4)+2 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = y%100;
			data[(x*4)+3 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		}

		if(x > 80 && x < 100 && y > 0 && y < VOLUME_TEX_SIZE && z > 10 &&  z < 50)
		{
			
			data[(x*4)   + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		    data[(x*4)+1 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 70;
		    data[(x*4)+2 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = y%100;
			data[(x*4)+3 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 250;
		}

		p =	Vector3(x,y,z)- Vector3(24,24,24);
		test = (p.length() < 40);
		if(test)
			data[(x*4)+3 + (y * VOLUME_TEX_SIZE * 4) + (z * VOLUME_TEX_SIZE * VOLUME_TEX_SIZE * 4)] = 0;

			
	}}}



	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, &volume_texture);
	glBindTexture(GL_TEXTURE_3D, volume_texture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexImage3D(GL_TEXTURE_3D, 0,GL_RGBA, VOLUME_TEX_SIZE, VOLUME_TEX_SIZE,VOLUME_TEX_SIZE,0, GL_RGBA, GL_UNSIGNED_BYTE,data);

	delete []data;
	cout << "volume texture created" << endl;

}

// ok let's start things up 

void init()
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0);
	create_volumetexture();

	load_vertex_program  (vertexprog,  "raycasting_shader.vp.cg");
	load_fragment_program(fragmentprog,"raycasting_shader.fp.cg");

    shaderprog = glCreateProgram();

    glAttachShader(shaderprog, vertexprog);
    glAttachShader(shaderprog, fragmentprog);

    glLinkProgram(shaderprog);

    check_program_status(shaderprog);

    stepsizeLoc  = glGetUniformLocation(shaderprog, "stepsize");
    mvLoc        = glGetUniformLocation(shaderprog, "ModelView");
    mpLoc        = glGetUniformLocation(shaderprog, "Proj");
    texLoc       = glGetUniformLocation(shaderprog, "tex");
    volumeTexLoc = glGetUniformLocation(shaderprog, "volume_tex");

	// Create the to FBO's one for the backside of the volumecube and one for the finalimage rendering
	glGenFramebuffersEXT(1, &framebuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,framebuffer);

	glGenTextures(1, &backface_buffer);
	glBindTexture(GL_TEXTURE_2D, backface_buffer);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, WINDOW_SIZE, WINDOW_SIZE, 0, GL_RGBA, GL_FLOAT, NULL);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, backface_buffer, 0);

	glGenTextures(1, &final_image);
	glBindTexture(GL_TEXTURE_2D, final_image);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, WINDOW_SIZE, WINDOW_SIZE, 0, GL_RGBA, GL_FLOAT, NULL);

	glGenRenderbuffersEXT(1, &renderbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, WINDOW_SIZE, WINDOW_SIZE);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderbuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
}


// for contiunes keypresses
void ProcessKeys()
{
	// Process keys
	for (int i = 0; i < 256; i++)
	{
		if (!gKeys[i])  { continue; }
		switch (i)
		{
		case ' ':
			break;
		case 'w':
			stepsize += 1.0/2048.0;
			if(stepsize > 0.25) stepsize = 0.25;
			break;
		case 'e':
			stepsize -= 1.0/2048.0;
			if(stepsize <= 1.0/200.0) stepsize = 1.0/200.0;
			break;
		}
	}

}

void key(unsigned char k, int x, int y)
{
	gKeys[k] = true;
}

void KeyboardUpCallback(unsigned char key, int x, int y)
{
	gKeys[key] = false;

	switch (key)
	{
	case 27 :
		{
			exit(0); break; 
		}
	case ' ':
		toggle_visuals = !toggle_visuals;
		break;
	}
}

// glut idle function
void idle_func()
{
	ProcessKeys();
	glutPostRedisplay();
}

void reshape_ortho(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


void resize(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.01, 400.0);
	glMatrixMode(GL_MODELVIEW);
}

void draw_fullscreen_quad()
{
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
   
	glTexCoord2f(0,0); 
	glVertex2f(0,0);

	glTexCoord2f(1,0); 
	glVertex2f(1,0);

	glTexCoord2f(1, 1); 

	glVertex2f(1, 1);
	glTexCoord2f(0, 1); 
	glVertex2f(0, 1);

	glEnd();
	glEnable(GL_DEPTH_TEST);

}

// display the final image on the screen
void render_buffer_to_screen()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	if(toggle_visuals)
		glBindTexture(GL_TEXTURE_2D,final_image);
	else
		glBindTexture(GL_TEXTURE_2D,backface_buffer);
	reshape_ortho(WINDOW_SIZE,WINDOW_SIZE);
	draw_fullscreen_quad();
	glDisable(GL_TEXTURE_2D);
}

// render the backface to the offscreen buffer backface_buffer
void render_backface()
{
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, backface_buffer, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	drawQuads(1.0,1.0, 1.0);
	glDisable(GL_CULL_FACE);
}

void raycasting_pass()
{
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, final_image, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glUseProgram(shaderprog);

    glUniform1f(stepsizeLoc, stepsize);
    glUniformMatrix4fv(mvLoc, 
                       1, 
                       GL_FALSE, 
                       mModelView);
    glUniformMatrix4fv(mpLoc, 
                       1, 
                       GL_FALSE, 
                       mProj);
	set_tex_param(texLoc,       backface_buffer, shaderprog, GL_TEXTURE0, GL_TEXTURE_2D);
	set_tex_param(volumeTexLoc, volume_texture,  shaderprog, GL_TEXTURE1, GL_TEXTURE_3D);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	drawQuads(1.0,1.0, 1.0);
	glDisable(GL_CULL_FACE);

    glUseProgram(0);
}

// This display function is called once pr frame 
void display()
{
	static float rotate = 0; 
	rotate += 0.25;

	resize(WINDOW_SIZE,WINDOW_SIZE);
	enable_renderbuffers();

	glLoadIdentity();
	glTranslatef(0,0,-2.25);
	glRotatef(rotate,0,1,1);
	glTranslatef(-0.5,-0.5,-0.5); // center the texturecube

    glGetFloatv(GL_MODELVIEW_MATRIX, mModelView);
    glGetFloatv(GL_PROJECTION_MATRIX, mProj);

	render_backface();
	raycasting_pass();
	disable_renderbuffers();
	render_buffer_to_screen();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("GPU raycasting tutorial");
	glutReshapeWindow(WINDOW_SIZE,WINDOW_SIZE);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(KeyboardUpCallback);
	
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);
	glutReshapeFunc(resize);
	resize(WINDOW_SIZE,WINDOW_SIZE);
	init();
	glutMainLoop();
	return 0;
}

