/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#ifndef GL_GLEXT_PROTOTYPES
# define GL_GLEXT_PROTOTYPES
#endif

#if defined (WIN32)
#include <GL/glew.h>
#include <GL/wglew.h>
#endif

#include "OSGGLU.h"
#include "OSGGPUVolRTV1.h"
#include "OSGDrawEnv.h"
#include "Vector3.h"

#define VOLUME_TEX_SIZE 128

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGPUVolRTV1Base.cpp file.
// To modify it, please change the .fcd file (OSGGPUVolRTV1.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GPUVolRTV1::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GPUVolRTV1::GPUVolRTV1(void) :
    Inherited(),
    bInitialized(false)
{
    stepsize = 1.0f/50.0f;
    toggle_visuals = true;
}

GPUVolRTV1::GPUVolRTV1(const GPUVolRTV1 &source) :
    Inherited(source),
    bInitialized(false)
{
    stepsize = 1.0f/50.0f;
    toggle_visuals = true;
}

GPUVolRTV1::~GPUVolRTV1(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GPUVolRTV1::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GPUVolRTV1::setStepsize(Real32 rVal)
{
    stepsize = rVal;
}

Real32 GPUVolRTV1::getStepsize(void)
{
    return stepsize;
}


void GPUVolRTV1::setToggleVisuals(bool bVal)
{
    toggle_visuals = bVal;
}

bool GPUVolRTV1::getToggleVisuals(void)
{
    return toggle_visuals;
}

Action::ResultE GPUVolRTV1::renderEnter(Action *pAction)
{
    return Action::Continue;
}

Action::ResultE GPUVolRTV1::renderLeave(Action *pAction)
{
    return Action::Continue;
}

void GPUVolRTV1::execute(DrawEnv *pEnv)
{
    // Make sure we don't trash the state
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    if(bInitialized == false)
    {
#if _WIN32
        glewInit();
#endif
        init(pEnv);
    }

    display(pEnv);

    glPopAttrib();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void GPUVolRTV1::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GPUVolRTV1 NI" << std::endl;
}


// ok let's start things up 
void GPUVolRTV1::init(DrawEnv *pEnv)
{
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
//	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, WINDOW_SIZE, WINDOW_SIZE, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, 
                 pEnv->getPixelWidth(),
                 pEnv->getPixelHeight(), 
                 0, GL_RGBA, GL_FLOAT, NULL);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, backface_buffer, 0);

	glGenTextures(1, &final_image);
	glBindTexture(GL_TEXTURE_2D, final_image);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, WINDOW_SIZE, WINDOW_SIZE, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, 
                 pEnv->getPixelWidth(), 
                 pEnv->getPixelHeight(), 
                 0, GL_RGBA, GL_FLOAT, NULL);
	glGenRenderbuffersEXT(1, &renderbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
//	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, WINDOW_SIZE, WINDOW_SIZE);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 
                             pEnv->getPixelWidth(), pEnv->getPixelHeight());
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderbuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
    bInitialized = true;
}


// This display function is called once pr frame 
void GPUVolRTV1::display(DrawEnv *pEnv)
{
    // was in init before. As OpenSG resets those they have to be
    // restored to the required values
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0);
    glDisable(GL_LIGHTING);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    // end

	static float rotate = 0; 
	rotate += 0.25;

//	resize(WINDOW_SIZE,WINDOW_SIZE);
    resize(pEnv, pEnv->getPixelWidth(), pEnv->getPixelHeight());
	enable_renderbuffers();

	glLoadIdentity();
//	glTranslatef(0,0,-2.25);
//	glRotatef(rotate,0,1,1);
//	glTranslatef(-0.5,-0.5,-0.5); // center the texturecube

    glLoadMatrixf(pEnv->getVPCameraViewing().getValues());

    glGetFloatv(GL_MODELVIEW_MATRIX, mModelView);
    glGetFloatv(GL_PROJECTION_MATRIX, mProj);

	render_backface();
	raycasting_pass();
	disable_renderbuffers();
	render_buffer_to_screen(pEnv);
//	glutSwapBuffers();
}

void GPUVolRTV1::resize(DrawEnv *pEnv, int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.01, 400.0);
    glLoadMatrixf(pEnv->getVPCameraProjection().getValues());

	glMatrixMode(GL_MODELVIEW);
}

// create a test volume texture, here you could load your own volume
void GPUVolRTV1::create_volumetexture()
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

// load_vertex_program: loading a vertex program
void GPUVolRTV1::load_vertex_program(GLuint &v_program, const char *shader_path)
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
void GPUVolRTV1::load_fragment_program(GLuint &f_program, 
                                       const char *shader_path)
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

void GPUVolRTV1::check_program_status(GLuint uiProgram)
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

void GPUVolRTV1::enable_renderbuffers()
{
	glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, framebuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
}

void GPUVolRTV1::disable_renderbuffers()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

// render the backface to the offscreen buffer backface_buffer
void GPUVolRTV1::render_backface()
{
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, backface_buffer, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	drawQuads(1.0,1.0, 1.0);
	glDisable(GL_CULL_FACE);
}

void GPUVolRTV1::raycasting_pass()
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

// display the final image on the screen
void GPUVolRTV1::render_buffer_to_screen(DrawEnv *pEnv)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	if(toggle_visuals)
		glBindTexture(GL_TEXTURE_2D,final_image);
	else
		glBindTexture(GL_TEXTURE_2D,backface_buffer);
//	reshape_ortho(WINDOW_SIZE,WINDOW_SIZE);
	reshape_ortho(pEnv->getPixelWidth(), pEnv->getPixelHeight());
	draw_fullscreen_quad();
	glDisable(GL_TEXTURE_2D);
}

bool GPUVolRTV1::readProgram(std::string  &szTarget,
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

void GPUVolRTV1::check_shader_status(GLuint uiShader)
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

// this method is used to draw the front and backside of the volume
void GPUVolRTV1::drawQuads(float x, float y, float z)
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

void GPUVolRTV1::set_tex_param(GLuint texLoc, GLuint tex, GLuint prog, 
                               GLuint unit,   GLuint target) 
{
    glActiveTexture(unit);
    glBindTexture(target, tex);

    glUniform1i(texLoc, unit - GL_TEXTURE0);

    glActiveTexture(GL_TEXTURE0);
}

void GPUVolRTV1::reshape_ortho(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

void GPUVolRTV1::draw_fullscreen_quad(void)
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

void GPUVolRTV1::vertex(float x, float y, float z)
{
	glColor3f(x,y,z);
	glMultiTexCoord3fARB(GL_TEXTURE1_ARB, x, y, z);
	glVertex3f(x,y,z);
}


OSG_END_NAMESPACE
