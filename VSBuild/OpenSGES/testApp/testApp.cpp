/******************************************************************************
** Copyright (C) 2004. Intel Corporation. All Rights Reserved. 
**
** The source code contained or described herein and all documents related to the
** source code ("Material") are owned by Intel Corporation or its suppliers or 
** licensors. Title to the Material remains with Intel Corporation or its suppliers
** and licensors. The Material contains trade secrets and proprietary and 
** confidential information of Intel or its suppliers and licensors. The Material 
** is protected by worldwide copyright and trade secret laws and treaty provisions.
** No part of the Material may be used, copied, reproduced, modified, published, 
** uploaded, posted, transmitted, distributed, or disclosed in any way without 
** Intel’s prior express written permission.
** 
** No license under any patent, copyright, trade secret or other intellectual 
** property right is granted to or conferred upon you by disclosure or delivery 
** of the Materials, either expressly, by implication, inducement, estoppel or 
** otherwise. Any license under such intellectual property rights must be express 
** and approved by Intel in writing.
******************************************************************************/
// GLTex+Lights
//

#include <stdio.h>
#include <windows.h>
#include <aygshell.h>
#include <math.h>
#include <gx.h>

#include "gles/egl.h"
#include "gles/gl.h"
#include "gles/glext.h"
//#include "t2700G.h"


#include "OSGBaseInitFunctions.h"
#include "OSGNode.h"
#include "OSGEGLWindow.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGDirectionalLight.h"
#include "OSGThread.h"
#include "OSGViewport.h"
#include "OSGPerspectiveCamera.h"
#include "OSGChangeList.h"
#include "OSGSolidBackground.h"
#include "OSGRenderAction.h"
#include "OSGGeometry.h"
#include "OSGSimpleMaterial.h"

#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"

//-----------------------------------------------------------------------------
// Parameterization
//-----------------------------------------------------------------------------
#define TEST_NAME _T("OpenSG-ES")
#define TEST_VERSION 1.1001f

#define WORLD_SIZE (50<<16)
#define RADIUS (15<<16)

#ifdef _DEBUG
#define NUM_FLAKES (5)
#else
#define NUM_FLAKES (15)
#endif

#define FLAKE_SIZE (10)
#define REFECT_SIZE (WORLD_SIZE - (RADIUS))
#define BG_SIZE (210)
#define REFECT_SIZE_FLOAT 50

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define WND_CLASS_NAME TEST_NAME _T("_CLASS_NAME")
#define WND_TITLE TEST_NAME

//-----------------------------------------------------------------------------
// Logging
//-----------------------------------------------------------------------------

FILE* g_LogFile = NULL;

//-----------------------------------------------------------------------------
// Fixed point support
//-----------------------------------------------------------------------------

#define ONE_FX 0x00010000
#define HALF_FX 0x00008000
#define PI_FX 0x0003243F		//
#define TWOPI_FX 0x0006487E		//

__inline GLfixed MulFX(GLfixed x, GLfixed y)
{
	__int64 r = ((__int64)x) * y;
	return (GLint)(r >> 16);
}

__inline GLfixed DivFX(GLfixed x, GLfixed y)
{
	__int64 r = ((__int64)x)<<16;
	return (GLint)(r/y);
}

__inline GLfixed RandFX()
{
	return (rand() & 0xFFFF);
}


#define IToFX(x) ((x) << 16)
#define FToFX(x) ((GLfixed)((x)*65536.0f))
#define FXFACTOR (1.0f/65536.0f)
#define FXToF(x) ((float)(x)*FXFACTOR)

__inline GLfixed SinFX(GLfixed x)
{
	return FToFX((float)sin(FXToF(x)));
}

__inline GLfixed CosFX(GLfixed x)
{
	return FToFX((float)cos(FXToF(x)));
}

__inline GLfixed TanFX(GLfixed x)
{
	return FToFX((float)tan(FXToF(x)));
}

// Global Variables:
static HINSTANCE s_hInstance;								// current instance
static HDC s_hdc = 0;
static HWND s_hwnd = 0;

static EGLDisplay egl_display = EGL_NO_DISPLAY;
static EGLSurface egl_window = EGL_NO_SURFACE;
static EGLContext context = EGL_NO_CONTEXT;
static EGLConfig config;
static int majorVersion, minorVersion;

static GXKeyList gxKeys;

OSG::EGLWindowPtr  pWin;
OSG::RenderAction *rAct;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, bool);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
static EGLConfig	FindConfig();
void				reshape (int w, int h);
void				display (void);
void				update (void);
void				init(void) ;


typedef struct tagFlake
{
    GLfloat Rotation;
    GLfloat Axis[3];
    GLfloat Position[3];
    GLfloat Velocity[3];
    OSG::GeometryPtr  pGeo;
    OSG::TransformPtr pTr;
    OSG::NodePtr      pTN;
} Flake;

static tagFlake s_pFlakes[NUM_FLAKES];

void SolidSphere(OSG::GeometryPtr pGeo,
                 GLfixed in_Radius,
                 GLuint in_NumSections,
                 GLuint in_NumSlices)
{
	GLint VtxIdx = 0;
	GLfixed Rad = 0;
	GLfixed SectionStep = DivFX(TWOPI_FX, IToFX(in_NumSections));
	GLfixed SliceStep = DivFX(PI_FX, IToFX(in_NumSlices));
	GLfixed Theta, Phi = SliceStep;
	GLfixed nfactor;
	GLfixed Position[3];
	GLfixed Normal[3];
	GLfixed a,b;
	GLuint clr = 0x0000000;
	GLuint colorDelta = 0x00010101;

	GLushort * pFaces;
	GLushort PrevSliceStart = 0;
	GLushort SliceStart = 1;

	GLint NumVert = 0;
	GLint NumIndices = 0;
	GLint NumPrims = 0;
	GLuint i = 0, j = 0;

	// Validate parameters
	if(in_Radius == 0 || in_NumSections <= 1 || in_NumSlices <= 1)
	{
		return;
	}

	// ------------------------------------------------------------------------
	// Calculate the number of Vertex and the number of indices

	NumVert = (in_NumSections * (in_NumSlices-1)) + 2;
	NumPrims = 
        (((in_NumSlices-2) * 2 * in_NumSections) + (in_NumSections * 2));

	NumIndices = 3 * NumPrims;

    OSG::GeoPnt3fxPropertyPtr  pnts  = OSG::GeoPnt3fxProperty ::create();
    OSG::GeoVec3fxPropertyPtr  norms = OSG::GeoVec3fxProperty ::create();

    OSG::GeoUInt16PropertyPtr index = OSG::GeoUInt16Property::create();   
    OSG::GeoUInt16PropertyPtr lens  = OSG::GeoUInt16Property::create();  
    OSG::GeoUInt8PropertyPtr  types = OSG::GeoUInt8Property ::create();     
    
    OSG::GeoPnt3fxProperty::StoredFieldType *p  = pnts ->editFieldPtr();
    OSG::GeoVec3fxProperty::StoredFieldType *n  = norms->editFieldPtr();

    OSG::GeoUInt16Property::StoredFieldType *idx  = index->editFieldPtr();
    OSG::GeoUInt16Property::StoredFieldType *len  = lens ->editFieldPtr();
    OSG::GeoUInt8Property ::StoredFieldType *typ  = types->editFieldPtr();

    typ->push_back(GL_TRIANGLES);
    len->push_back(NumIndices  );

    p->resize(NumVert);
    n->resize(NumVert);

    pGeo->setTypes  (types);
    pGeo->setLengths(lens);
    
    pGeo->setProperty(pnts,  OSG::Geometry::PositionsIndex);
    pGeo->setProperty(norms, OSG::Geometry::NormalsIndex  );
    pGeo->setIndex   (index, OSG::Geometry::PositionsIndex);

	// ------------------------------------------------------------------------
	// Generate Vertex

	// Top Vertex
    (*p)[0][0].setFixedValue(0);
    (*p)[0][1].setFixedValue(in_Radius);
    (*p)[0][2].setFixedValue(0);

    (*n)[0][0].setFixedValue(0);
    (*n)[0][1].setFixedValue(ONE_FX);
    (*n)[0][2].setFixedValue(0);

	VtxIdx++;
	clr += colorDelta;

	// Slice Vertex
	for(i = 1; i < in_NumSlices; ++i)
	{
		Theta = 0;
		nfactor = SinFX(Phi);
		Rad = MulFX( in_Radius, SinFX(Phi));
		a = CosFX(Phi);
		b = MulFX(in_Radius, a);
		for(j = 0; j < in_NumSections; ++j)
		{
			Normal[0] = CosFX(Theta);
			Normal[2] = SinFX(Theta);
			Position[0] = MulFX(Rad, Normal[0]);
			Position[2] = MulFX(Rad, Normal[2]);
			Normal[0] = MulFX(Normal[0], nfactor);
			Normal[2] = MulFX(Normal[2], nfactor);

			Normal[1] = a;
			Position[1] = b;

            (*p)[VtxIdx][0].setFixedValue(Position[0]);
            (*p)[VtxIdx][1].setFixedValue(Position[1]);
            (*p)[VtxIdx][2].setFixedValue(Position[2]);
            
            (*n)[VtxIdx][0].setFixedValue(Normal[0]);
            (*n)[VtxIdx][1].setFixedValue(Normal[1]);
            (*n)[VtxIdx][2].setFixedValue(Normal[2]);

			Theta+=SectionStep;
			VtxIdx++;
		}
		Phi += SliceStep;
		clr += colorDelta;
	}

	// Bottom Vertex
    (*p)[VtxIdx][0].setFixedValue(0);
    (*p)[VtxIdx][1].setFixedValue(-in_Radius);
    (*p)[VtxIdx][2].setFixedValue(0);

    (*n)[VtxIdx][0].setFixedValue(0);
    (*n)[VtxIdx][1].setFixedValue(-ONE_FX);
    (*n)[VtxIdx][2].setFixedValue(0);

	// ------------------------------------------------------------------------
	// Build Faces


	in_NumSections -= 1;

	// Top Cap
	for(i = 0; i < in_NumSections; ++i)
	{
        idx->push_back(0);
        idx->push_back(SliceStart+i+1);
        idx->push_back(SliceStart+i);
	}
	// Stitch first and last section together
	idx->push_back(0);
	idx->push_back(SliceStart);
	idx->push_back(in_NumSections+1);

	// Middle Slices
	for(i = 2; i < in_NumSlices; ++i)
	{
		PrevSliceStart = SliceStart;
		SliceStart += in_NumSections + 1;
		for(j = 0; j < in_NumSections; ++j)
		{
			idx->push_back(PrevSliceStart+j);
			idx->push_back(PrevSliceStart+j+1);
			idx->push_back(SliceStart+j);

			idx->push_back(SliceStart+j);
			idx->push_back(PrevSliceStart+j+1);
			idx->push_back(SliceStart+j+1);
		}

		// Stitch first and last section together
		idx->push_back(SliceStart+in_NumSections);
		idx->push_back(PrevSliceStart+in_NumSections);
		idx->push_back(PrevSliceStart);


		idx->push_back(SliceStart+in_NumSections);
		idx->push_back(PrevSliceStart);
		idx->push_back(SliceStart);
	}

	// Bottom Cap
	for(i = 0; i < in_NumSections; ++i)
	{
		idx->push_back(NumVert-1);
		idx->push_back(SliceStart+i);
		idx->push_back(SliceStart+i+1);
	}

	// Stitch first and last section together
	idx->push_back(NumVert-1);
	idx->push_back(SliceStart+in_NumSections);
	idx->push_back(SliceStart);
}

void InitFlake(Flake *pFlake)
{
	GLfixed t;
	memset(pFlake, 0, sizeof(Flake));

    pFlake->pGeo = OSG::Geometry::create();
    pFlake->pTr  = OSG::Transform::create();

    OSG::SimpleMaterialPtr pMat = OSG::SimpleMaterial::create();

    pMat->editDiffuse().setValuesRGB(1.f, 0.f, 0.f);

        /*
          0.1f + (float(rand()) / float(RAND_MAX)),
                                     0.1f + (float(rand()) / float(RAND_MAX)),
                                     0.1f + (float(rand()) / float(RAND_MAX)));
        */

    pFlake->pGeo->setMaterial(pMat);

    SolidSphere(pFlake->pGeo, RADIUS>>2, FLAKE_SIZE, FLAKE_SIZE);

	pFlake->Rotation = MulFX(360<<16, RandFX())>>16;

	t = MulFX(TWOPI_FX, RandFX()) - PI_FX;

	pFlake->Axis[0] = 0; //FXToF( (SinFX(t)) );
	pFlake->Axis[1] = 1; //FXToF( (CosFX(t)) );
	pFlake->Axis[2] = 0;

	// Initial position

	// Initial Velocity
	pFlake->Velocity[0] = 0.2f + (float(rand()) / float(RAND_MAX));
	pFlake->Velocity[1] = 0.2f + (float(rand()) / float(RAND_MAX));
	pFlake->Velocity[2] = 0.2f + (float(rand()) / float(RAND_MAX));
    

	OSG::Vec3r tr(pFlake->Position[0],
                  pFlake->Position[1],
                  pFlake->Position[2]);
	OSG::Vec3r sc(1.f, 1.f, 1.f);
	OSG::Quaternionr r;

    r.setValueAsAxisDeg(pFlake->Axis[0],
                        pFlake->Axis[1],
                        pFlake->Axis[2],
                        pFlake->Rotation);

    pFlake->pTr->editMatrix().setTransform(tr, r, sc);

    OSG::NodePtr pGN = OSG::Node::create();

    pGN->setCore(pFlake->pGeo);    


    pFlake->pTN = OSG::Node::create();
    pFlake->pTN->setCore(pFlake->pTr);
    pFlake->pTN->addChild(pGN);


    OSG::NodePtr      pGTN = OSG::Node::create();
    OSG::TransformPtr pGT  = OSG::Transform::create();

    tr[0].setFixedValue(RADIUS);
    tr[1].setFixedValue(0);
    tr[2].setFixedValue(0);

    pGT->editMatrix().setTransform(tr);

    pGN = OSG::Node::create();

    pGN->setCore(pFlake->pGeo);

    pGTN->setCore(pGT);
    pGTN->addChild(pGN);

    pFlake->pTN->addChild(pGTN);

    // -----------------------------
    pGTN = OSG::Node::create();
    pGT  = OSG::Transform::create();

    tr[0].setFixedValue(-RADIUS);
    tr[1].setFixedValue(0);
    tr[2].setFixedValue(0);

    pGT->editMatrix().setTransform(tr);

    pGN = OSG::Node::create();

    pGN->setCore(pFlake->pGeo);

    pGTN->setCore(pGT);
    pGTN->addChild(pGN);

    pFlake->pTN->addChild(pGTN);


    // -----------------------------
    pGTN = OSG::Node::create();
    pGT  = OSG::Transform::create();

    tr[0].setFixedValue(0);
    tr[1].setFixedValue(RADIUS);
    tr[2].setFixedValue(0);

    pGT->editMatrix().setTransform(tr);

    pGN = OSG::Node::create();

    pGN->setCore(pFlake->pGeo);

    pGTN->setCore(pGT);
    pGTN->addChild(pGN);

    pFlake->pTN->addChild(pGTN);


    // -----------------------------
    pGTN = OSG::Node::create();
    pGT  = OSG::Transform::create();

    tr[0].setFixedValue(0);
    tr[1].setFixedValue(-RADIUS);
    tr[2].setFixedValue(0);

    pGT->editMatrix().setTransform(tr);

    pGN = OSG::Node::create();

    pGN->setCore(pFlake->pGeo);

    pGTN->setCore(pGT);
    pGTN->addChild(pGN);

    pFlake->pTN->addChild(pGTN);


    // -----------------------------
    pGTN = OSG::Node::create();
    pGT  = OSG::Transform::create();

    tr[0].setFixedValue(0);
    tr[1].setFixedValue(0);
    tr[2].setFixedValue(RADIUS);

    pGT->editMatrix().setTransform(tr);

    pGN = OSG::Node::create();

    pGN->setCore(pFlake->pGeo);

    pGTN->setCore(pGT);
    pGTN->addChild(pGN);

    pFlake->pTN->addChild(pGTN);


    // -----------------------------
    pGTN = OSG::Node::create();
    pGT  = OSG::Transform::create();

    tr[0].setFixedValue(0);
    tr[1].setFixedValue(0);
    tr[2].setFixedValue(-RADIUS);

    pGT->editMatrix().setTransform(tr);

    pGN = OSG::Node::create();

    pGN->setCore(pFlake->pGeo);

    pGTN->setCore(pGT);
    pGTN->addChild(pGN);

    pFlake->pTN->addChild(pGTN);
}



void UpdateFlake(Flake *pFlake)
{
	GLuint i = 0;
	pFlake->Rotation += 1.f;

	for(i = 0; i < 3; ++i)
	{
		pFlake->Position[i] += pFlake->Velocity[i];

		if(pFlake->Position[i] > REFECT_SIZE_FLOAT)
		{
			pFlake->Position[i] = 
                REFECT_SIZE_FLOAT - (pFlake->Position[i] - REFECT_SIZE_FLOAT);
			pFlake->Velocity[i] = -pFlake->Velocity[i];
		}

		if(pFlake->Position[i] < -REFECT_SIZE_FLOAT)
		{
			pFlake->Position[i] = 
                -REFECT_SIZE_FLOAT + (abs(pFlake->Position[i]) - 
                                      REFECT_SIZE_FLOAT);

			pFlake->Position[i] = pFlake->Position[i];
			pFlake->Velocity[i] = -pFlake->Velocity[i];
		}
	}    

	OSG::Vec3r tr(pFlake->Position[0],
                  pFlake->Position[1],
                  pFlake->Position[2]);
	OSG::Vec3r sc(1.f, 1.f, 1.f);
	OSG::Quaternionr r;

    r.setValueAsAxisDeg(pFlake->Axis[0],
                        pFlake->Axis[1],
                        pFlake->Axis[2],
                        pFlake->Rotation);

    pFlake->pTr->editMatrix().setTransform(tr, r, sc);
}

void DoReleaseGL(bool bNoRotation)
{
	eglSwapBuffers (egl_display, egl_window);
	eglMakeCurrent(egl_display, 
                   EGL_NO_SURFACE, 
                   EGL_NO_SURFACE, 
                   EGL_NO_CONTEXT) ;

	eglDestroyContext(egl_display, context);
	eglDestroySurface(egl_display,egl_window);

    eglTerminate(egl_display);


//todo: screen rotation
/*	if (!bNoRotation)  //don't do this if releasing GL to restore from sleep
	{
		//code to restore the display orientation to the original setting
		DEVMODE * p_dm = (DEVMODE *) malloc(sizeof(DEVMODE));
		p_dm->dmSize=sizeof(DEVMODE);
		p_dm->dmFields=DM_DISPLAYORIENTATION;
		p_dm->dmDisplayOrientation=origOrientation;
		ChangeDisplaySettingsEx(NULL,p_dm,NULL,0,NULL); 
	}
*/
//	if (s_pBG) FreeMesh(s_pBG);
//	if (p_dm) free(p_dm);

	GXCloseInput();
}

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR     lpCmdLine,
				   int       nCmdShow)
{
	MSG msg;
	bool done=FALSE;
	// Initialize global strings
	MyRegisterClass(hInstance);

	// Remove for repeatable behavior.
	srand(timeGetTime());

	OSG::osgInit(0, NULL);
    
    rAct = OSG::RenderAction::create();
    pWin = OSG::EGLWindow   ::create();

    rAct->setFrustumCulling(false);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow, false))
	{
		return FALSE;
	}

    // create the graph

    // root
    OSG::NodePtr  root      = OSG::Node::create();
    OSG::GroupPtr rootGroup = OSG::Group::create();

    root->setCore(rootGroup);

    // Cam Transform
    OSG::NodePtr      camTrans     = OSG::Node::create();
    OSG::TransformPtr camTransCore = OSG::Transform::create();

    camTrans->setCore(camTransCore);

    camTransCore->editMatrix().setIdentity();
    camTransCore->editMatrix()[3][2] = 300.f;

    // beacon for camera and light  

    OSG::NodePtr  camBeacon = OSG::Node::create();
    OSG::GroupPtr camCore   = OSG::Group::create();

    camBeacon->setCore(camCore);

    camTrans->addChild(camBeacon);

//    cam_trans = t1;

    OSG::NodePtr             dlight = OSG::Node::create();
    OSG::DirectionalLightPtr dl     = OSG::DirectionalLight::create();

    dlight->setCore(dl);

    dl->setAmbient( .0f, .0f, .0f, 1.f );
    dl->setDiffuse  ( 7.f, 7.f, 7.f, 1.f );
    dl->setDirection(0.f,0.f,1.f);
    dl->setBeacon(camBeacon);

    root->addChild(camTrans);
    root->addChild(dlight  );

    
    OSG::NodePtr file = OSG::Node::create();
    
    file->setCore(OSG::Group::create());

    for(int i = 0; i < NUM_FLAKES; ++i)
	{
//        OSG::NodePtr pG = OSG::Node::create();
//        OSG::NodePtr pT = OSG::Node::create();

//        pT->setCore(s_pFlakes[i].pTr);
//        pG->setCore(s_pFlakes[i].pGeo);

//        pT->addChild(pG);
        file->addChild(s_pFlakes[i].pTN);
	}


    OSG::Thread::getCurrentChangeList()->commitChanges();

    file->updateVolume();

	OSG::Vec3r min,max;
    file->getVolume().getBounds(min, max);
    
    OSG::TransformPtr scene_trans = OSG::Transform::create();
    OSG::NodePtr      sceneTrN    = OSG::Node::create();

    sceneTrN->setCore(scene_trans);
    sceneTrN->addChild(file);

    dlight->addChild(sceneTrN);


    // Camera   
    OSG::PerspectiveCameraPtr cam = OSG::PerspectiveCamera::create();

    cam->setBeacon(camBeacon);
	cam->setFov( OSG::deg2rad( 45 ) );
    cam->setNear( 1.0 );
    cam->setFar( 1000 );

    // Background
    OSG::SolidBackgroundPtr bkgnd = OSG::SolidBackground::create();

	bkgnd->setColor(OSG::Color3r(0.f,1.f,0.f));
    
    // Viewport

    OSG::ViewportPtr vp = OSG::Viewport::create();

    vp->setCamera    (cam  );
    vp->setBackground(bkgnd);
    vp->setRoot      (root );
    vp->setSize      (0, 0, 1, 1);

    pWin->addPort(vp);

	// Main message loop:
	while(!done)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if ((msg.message==WM_QUIT))
			{
				done=TRUE;
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		update ();
		display();

		//How to detect key press and how to display a GDI message box
		if (GetAsyncKeyState(gxKeys.vkStart))
		{
			DoReleaseGL(true);

			MessageBox(s_hwnd,
                       TEXT("vkStart Keypress Detected\0"),
                       TEXT("GLTex+Lights Message\0"), 
                       MB_OK);

			InitInstance(hInstance, nCmdShow, true);
		}
	}

	if(g_LogFile)
	{
		_ftprintf(g_LogFile,_T("-------------------------------------------------------------------------------\n"));
		fclose(g_LogFile);
		g_LogFile = NULL;
	}

    // Release the current surface first
	DoReleaseGL(false);

	return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = WND_CLASS_NAME;

	return RegisterClass(&wc);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, bool bNoWindowInit)
{
	DWORD exmode = 0;
	RECT r;

	s_hInstance = hInstance; // Store instance handle in our global variable

	exmode = WS_EX_TOPMOST;
#if 0
	SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
#else
	r.top = 0;
	r.left = 0;
	r.bottom = GetSystemMetrics(SM_CYSCREEN);
	r.right = GetSystemMetrics(SM_CXSCREEN);

#endif

	if (!bNoWindowInit)
	{
#if 0
		s_hwnd = CreateWindowEx(exmode, 
                                WND_CLASS_NAME, 
                                WND_TITLE,
                                WS_VISIBLE , // | WS_OVERLAPPED
                                r.left, 
                                r.top, 
                                r.right - r.left, 
                                r.bottom - r.top,
                                NULL, 
                                NULL, 
                                hInstance, 
                                NULL);
#endif

		s_hwnd = CreateWindowEx(exmode, 
                                WND_CLASS_NAME, 
                                WND_TITLE,
                                WS_VISIBLE , // | WS_OVERLAPPED
                                CW_USEDEFAULT, 
                                CW_USEDEFAULT, 
                                CW_USEDEFAULT, 
                                CW_USEDEFAULT,
                                NULL, 
                                NULL, 
                                hInstance, 
                                NULL);

        if (!s_hwnd)
		{
			return FALSE;
		}
        
#if 0
		if (!SHFullScreen(s_hwnd, 
                          SHFS_HIDETASKBAR   | 
                          SHFS_HIDESIPBUTTON | 
                          SHFS_HIDESTARTICON))
		{
			// SHFullScreen failed.
			return FALSE;  // Replace with specific error handling.
		}
#endif

		s_hdc = GetDC(s_hwnd);
	}

	egl_display = eglGetDisplay((NativeDisplayType)s_hdc);

    pWin->setDisplay(egl_display);

	if (!eglInitialize(egl_display, &majorVersion, &minorVersion))
	{
		OutputDebugString(TEXT("Unable to initialise egl"));
        return FALSE;
	}

	config = FindConfig();

    context = eglCreateContext(egl_display, config, NULL, NULL);

    pWin->setContext(context);

    if(!context)
	{
		OutputDebugString(TEXT("Unable to create a context"));
        return FALSE;
    }

    egl_window = eglCreateWindowSurface(egl_display, config, s_hwnd, NULL);

    pWin->setWindow(egl_window);

    if(egl_window == EGL_NO_SURFACE)
	{
		OutputDebugString(TEXT("Unable to create window surface"));

        return FALSE;
    }

    pWin->init();

/*
    if(!eglMakeCurrent(egl_display, egl_window, egl_window, context))
	{
		OutputDebugString(TEXT("Unable to make current context"));

        return FALSE;
	}
*/

	//Check for existence of Intel 2700G hardware
	const GLubyte * vendor, *version, *extensions, *renderer;

	vendor     = glGetString(GL_VENDOR);
	renderer   = glGetString(GL_RENDERER);
	version    = glGetString(GL_VERSION);
	extensions = glGetString(GL_EXTENSIONS);

	if (strcmp((char*)glGetString(GL_RENDERER), 
               "Intel(r) 2700G Multimedia Accelerator")!=0)
	{
		OutputDebugString(
            TEXT("Intel(r) 2700G Multimedia Accelerator Driver Not Detected\n"));
		return FALSE;
	}
	else 
    {
        OutputDebugString(
            TEXT("Intel(r) 2700G Multimedia Accelerator Driver Confirmed\n"));
    }

	init();

//	reshape(r.right - r.left, r.bottom - r.top);

	GXOpenInput();

	gxKeys = GXGetDefaultKeys(GX_NORMALKEYS);


	ShowWindow(s_hwnd, nCmdShow);

	UpdateWindow(s_hwnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int tmp1, tmp2;

	switch (message)
	{
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if(s_hwnd)
		{
			RECT rc;
			GetClientRect(hWnd,&rc);
			reshape(rc.right-rc.left,rc.bottom-rc.top);
		}
		break;
	case WM_KEYUP:
		tmp1=wParam;
		tmp2=lParam;
		break;
	case WM_KEYDOWN:
		tmp1=wParam;
		tmp2=lParam;
		break;

	default:	
        return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

static EGLConfig FindConfig()
{
    EGLint num_config;
    EGLint list[32];
    int i;

    i = 0;

    list[i++] = EGL_LEVEL;
    list[i++] = 0;
	list[i++] = EGL_SURFACE_TYPE;
	list[i++] = EGL_WINDOW_BIT ;


	list[i++] = EGL_NONE;

    if (!eglChooseConfig(egl_display, 
                         list, 
                         &config, 
                         1, 
                         &num_config) || num_config != 1)
	{
		return 0;
    }

    return config;
}

void init(void)
{
	GLuint i;
//	GLfixed white[4] = { ONE_FX, ONE_FX, ONE_FX, ONE_FX };
//	GLfixed grey[4] = { ONE_FX>>1, ONE_FX>>1, ONE_FX>>1, ONE_FX>>1 };
	glClearColorx(0, 0, 0, 0);
	glShadeModel (GL_SMOOTH);

    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatex(0, 0, -(WORLD_SIZE<<1) + -(WORLD_SIZE<<2));
*/
 
	for(i = 0; i < NUM_FLAKES; ++i)
	{
		InitFlake(&(s_pFlakes[i]));
	}

	//
	g_LogFile = _tfopen(_T("\\release\\") TEST_NAME _T(".txt"), _T("wa+"));
	if(!g_LogFile)
	{
		g_LogFile = _tfopen(TEST_NAME _T(".txt"), _T("wa+"));
	}

	if(g_LogFile)
	{
		_ftprintf(g_LogFile,_T("-------------------------------------------------------------------------------\n"));
		_ftprintf(g_LogFile,_T("\n%s Version:%f\n\n"), TEST_NAME, TEST_VERSION);
		_ftprintf(g_LogFile,_T("-------------------------------------------------------------------------------\n"));
#if 0
		_ftprintf(g_LogFile,_T("%d Triangles Per Frame\n"), NUM_FLAKES * 7 * s_pMesh->numPrims + s_pBG->numPrims);
		_ftprintf(g_LogFile,_T("%d Vertices Per Frame\n"), NUM_FLAKES * 7 * s_pMesh->numVertices + s_pBG->numVertices);
		_ftprintf(g_LogFile,_T("%d Draw Commands Per Frame\n"), NUM_FLAKES * 7 + 1);
		_ftprintf(g_LogFile,_T("%d Average Triangles Per Draw Command \n"), s_pMesh->numPrims);
#endif

        for(i = 0; i < NUM_FLAKES; ++i)
        {
            _ftprintf(g_LogFile,_T("%d : %f %f %f | %f %f %f\n"),
                      i,
                      s_pFlakes[i].Position[0],
                      s_pFlakes[i].Position[1],
                      s_pFlakes[i].Position[2],
                      s_pFlakes[i].Velocity[0],
                      s_pFlakes[i].Velocity[1],
                      s_pFlakes[i].Velocity[2]);

        }
	}
}

void reshape (int w, int h)
{
    pWin->resize(w, h);
}

void update(void)
{
	int i = 0;
	for(i = 0; i < NUM_FLAKES; ++i)
	{
		UpdateFlake(&(s_pFlakes[i]));
	}
};

void display(void)
{
	static int framecount=0;
	static DWORD dwOldCount=0;
	int i = 0;
	static GLfixed light_position[]	= { FToFX(-50.f), 
                                        FToFX(50.f), 
                                        FToFX(200.f), 
                                        FToFX(1.f) };
	static const GLfixed light_ambient[]	= { FToFX(0.25f), 
                                                FToFX(0.25f), 
                                                FToFX(0.25f), 
                                                ONE_FX };
	static const GLfixed light_diffuse[]	= { ONE_FX, 
                                                ONE_FX, 
                                                ONE_FX, 
                                                ONE_FX };

	const double time = fmod(GetTickCount() / 1000.0, 360.0);

	if(dwOldCount == 0)
	{
		dwOldCount = timeGetTime();
	}

    pWin->frameInit();
    pWin->resizeGL();

#if 0
	glMatrixMode(GL_MODELVIEW);


	light_position[0]=FToFX((100)*(sin(time)));
	light_position[1]=FToFX((100)*(cos(time)));
	light_position[2]=FToFX(200-(200*(cos(time))));
	
	
	glLightxv(GL_LIGHT0, GL_POSITION, light_position);
	glLightxv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightxv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightxv(GL_LIGHT0, GL_SPECULAR, light_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
#endif

	glEnable(GL_NORMALIZE);

    pWin->renderAllViewports(rAct);

	framecount++;

	if((framecount&0x0F)==0)
	{
		DWORD dwTimeCount;
		float fTime;

		dwTimeCount = timeGetTime();

		fTime = (float)(dwTimeCount - dwOldCount);

		dwOldCount=dwTimeCount;
		// Frame count should always be 16
		// fps = frames/S = frames/(ms/1000) = (1000*frames)/ms
		_ftprintf(g_LogFile, _T("FPS = %f\n"),16000.0f/fTime);
		framecount = 0;
	}

    if(!pWin->swap())
    {
#if 0
        GLenum err = eglGetError();
        
        if(err == EGL_CONTEXT_LOST_IMG)
        {	
            //release surfaces
            DoReleaseGL(true);
            //reinit app
            InitInstance(hInstance, nCmdShow, true);
        }
#endif
    }

    pWin->frameExit();
}

