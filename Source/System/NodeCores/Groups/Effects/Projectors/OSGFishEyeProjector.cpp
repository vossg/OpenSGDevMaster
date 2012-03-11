/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include <sstream>
#include <fstream>

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGFishEyeProjector.h"
#include "OSGFishEyeProjectorData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGDrawEnv.h"
#include "OSGImageFunctions.h"
#include "OSGStateOverride.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleSHLFunctions.h"
#include "OSGPerspectiveCamera.h"

#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"


#include "OSGMatrixUtility.h"

#include "OSGGLU.h"


OSG_USING_NAMESPACE

/*! \class OSG::FishEyeProjector

  based on ideas/publications/samples from
  http://local.wasp.uwa.edu.au/~pbourke/miscellaneous/fisheye/

 */

UInt32 FishEyeProjector::_uiFramebufferObjectExt = 
    Window::invalidExtensionID;

UInt32 FishEyeProjector::_uiFuncDrawBuffers      =
    Window::invalidFunctionID;

typedef void   (OSG_APIENTRY *GLDrawBuffersEXTProcT)(
    GLsizei  n, 
    const GLenum  *buffers);




void osgMedian(Vec3d &vRes, const Vec3d &v1, const Vec3d &v2)
{
    vRes[0] = (v1[0] + v2[0]) * 0.5;
    vRes[1] = (v1[1] + v2[1]) * 0.5;
    vRes[2] = (v1[2] + v2[2]) * 0.5;
}

void osgMedian(Vec2d &vRes, const Vec2d &v1, const Vec2d &v2)
{
    vRes[0] = (v1[0] + v2[0]) * 0.5;
    vRes[1] = (v1[1] + v2[1]) * 0.5;
}


Vec3d osgRotateX(Vec3d p,double theta)
{
	Vec3d q;

	q[0] =  p[0];
	q[1] =  p[1] * cos(theta) + p[2] * sin(theta);
	q[2] = -p[1] * sin(theta) + p[2] * cos(theta);

	return q;
}

int FishEyeProjector::MirrorPosition(Vec3d   c, 
                                     Real64  r, 
                                     Vec3d   p1, 
                                     Vec3d   p2,
                                     Vec3d  &p0)
{
    int i;
    int nres = 1000;

    double theta,thetamax,thetamin,phi;
    double ctheta,stheta;
    double l1,l2,val,valmin;
    Vec3d  p; 
   
    p0.setValues(0.0, 0.0, 0.0);
   
    if(p1[2] < 0)
        return 1;
      
    // Translate to origin
    p1[0] -= c[0]; 
    p2[0] -= c[0];

    // Rotate about z axis so p1 lies in x-z plane
    phi = atan2(p1[1], p1[2]);

    p1 = osgRotateX(p1, -phi);

    if(fabs(p1[1]) > 0.00001)
        return 2;

    // Calculate the maximum possible value of theta
    // Mirror is at origin
    if(fabs(p2[0]) <= r)
        return 3;

    thetamax = acos(r / fabs(p2[0]));

    // Iterate to find the minimum light path length
    thetamin = thetamax;
    valmin   = 1e32;

    for(i = 0; i <= nres; i++) 
    {
        theta = i * PiHalf / double(nres);

        if(theta >= thetamax)
            break;

        ctheta = cos(theta);
        stheta = sin(theta);

        l1 = ((p2[0] + r * ctheta) *(p2[0] + r * ctheta) + 
              (r * stheta)*(r * stheta));

        l2 = ((p1[0] + r * ctheta) *(p1[0] + r * ctheta) + 
              (p1[2] - r * stheta) *(p1[2] - r * stheta));

        val = sqrt(l1) + sqrt(l2);

        if (val < valmin) 
        {
            valmin   = val;
            thetamin = theta;
        }
    }

    if(thetamin < 0)
        return 4;

    // Calculate p0
    p[0] = -r * cos(thetamin);
    p[1] =  0;
    p[2] =  r * sin(thetamin);

    // Rotate back
    p = osgRotateX(p, phi);

    // Translate back
    p[0] += c[0];

    p0 = p;

    return 0;
}

void FishEyeProjector::EstimateWarp(Real64  u, Real64 v, 
                                    Real64 &x, Real64 &z, 
                                    Real64 &br)
{
#if 0
    Int32  ix,iy;
    Real64 tu,tv;
#endif
    Int32  n;
    Real64 mu,longitude,latitude;
    Vec3d  p1,p,p0;
  
    Real64 domeradius   = this->getDomeRadius  (); // 2.5;
    Real64 mirrorradius = this->getMirrorRadius(); //0.3;
    Vec3d  mirrorpos    = this->getMirrorPos   (); //(2.4,0,0);
    Vec3d  projectorpos = this->getProjectorPos(); //(1.85,0,0);
    Real64 aspectratio  = this->getAspectRatio (); // 4/3.0;
    Real64 throwdist    = this->getThrowDist   (); //1.5;

    Vec3d  frustum[4];
 
    if(this->getMode() == FishEyeProjector::MirrorDome)
    {
        // Location of projection plane, 1 unit in front of projector
        for(Int32 i = 0; i < 4; i++)
            frustum[i][0] = projectorpos[0] + 1;

        frustum[0][1] = -0.5 / throwdist;
        frustum[1][1] = -0.5 / throwdist;
        frustum[2][1] =  0.5 / throwdist;
        frustum[3][1] =  0.5 / throwdist;
        frustum[0][2] =  0;
        frustum[1][2] =  1.0 / (throwdist * aspectratio);
        frustum[2][2] =  1.0 / (throwdist * aspectratio);
        frustum[3][2] =  0;

        // longitude and latitude, latitude clampd at pi/2
        // latitude = 0 at north pole of dome, pi/2 at horizon of dome
        longitude = atan2(v, u); // -pi to pi
        latitude  = PiHalf * sqrt(u * u + v * v);

        if (latitude > PiHalf)
            latitude = PiHalf;

        // p1 is the point on the dome, dome centered at the origin
        p1[0] = domeradius * sin(latitude) * sin(longitude);
        p1[1] = domeradius * sin(latitude) * cos(longitude);
        p1[2] = domeradius * cos(latitude);
      
        // Calculate the reflection position on the dome
        if ((n = MirrorPosition(mirrorpos,
                                mirrorradius,
                                p1,
                                projectorpos,
                                p0          )) != 0) 
        {
            fprintf(stderr,"Error %d, at (%g,%g) = (%g,%g)\n",
                    n,u,v,latitude,longitude);
        }
 
        // Calculate the point "p" on the projection plane
        mu = (frustum[0][0] - projectorpos[0]) / (p0[0] - projectorpos[0]);

        p[0] = frustum[0][0];
        p[1] = projectorpos[1] + mu * (p0[1] - projectorpos[1]);
        p[2] = projectorpos[2] + mu * (p0[2] - projectorpos[2]);

        // Set brigthness
        br = 1;

        if (p1[0] > 0)
            br = 1 - p1[0] / domeradius;

        if (br < 0)
            br = 0;

        if (p1[0] >= mirrorpos[0])
            br = -1;

        p[1] *= throwdist;
        p[1] *= 2;
        p[1] *= aspectratio;

        p[2] *= throwdist;
        p[2] *= aspectratio;
        p[2] *= 2;
        p[2] -= 1;
        
        x = p[1];
        z = p[2];

    } 
    else 
    { 
        // warp mesh ToDo
    }
}

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void FishEyeProjector::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    if(0x0000 != (whichField & (ModeFieldMask | MeshRefinementLevelFieldMask)))
    {
        if(_sfMode.getValue() < 0x0001)
            _sfMode.setValue(0x0001);

        if(_sfMode.getValue() > 0x0006)
            _sfMode.setValue(0x0006);

        fprintf(stderr, "Rebuild for %d %d\n", 
                _sfMode.getValue(),
                _sfMeshRefinementLevel.getValue());

        rebuildGeometries();
    }

    if(0x0000 != (whichField & ShowDomeIntensityFieldMask))
    {
        for(UInt32 i = 0; i < 4; ++i)
        {
            Geometry *pGeo = _mfGeometries[i];

            if(pGeo == NULL)
                continue;

            GeoVectorProperty *pColProp = 
                pGeo->getProperty(Geometry::ColorsIndex);
        
            if(pColProp != NULL)
            {
                pColProp->setIgnore(!this->getShowDomeIntensity());
            }
        }
    }

    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void FishEyeProjector::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FishEyeProjector::FishEyeProjector(void) :
    Inherited  (  )
{
}

FishEyeProjector::FishEyeProjector(const FishEyeProjector &source) :

    Inherited  (source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FishEyeProjector::~FishEyeProjector(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */

Action::ResultE FishEyeProjector::renderEnter(Action *action)
{
    static Matrix transforms[] = 
        { 
            // left
            Matrix( 1,  0,  0,  0,
                    0,  1,  0,  0,
                    0,  0,  1,  0,
                    0,  0,  0,  1),

            // right
            Matrix( 0,  0, -1,  0,
                    0,  1,  0,  0,
                    1,  0,  0,  0,
                    0,  0,  0,  1),

            // bottom
            Matrix( 1,  0,  0,  0,
                    0,  0,  1,  0,
                    0, -1,  0,  0,
                    0,  0,  0,  1),

            // top
            Matrix( 1,  0,  0,  0,
                    0,  0, -1,  0,
                    0,  1,  0,  0,
                    0,  0,  0,  1),
        };

    static Matrix deltaTr[] =
        {
            Matrix ( 0.70710678f,  0,  0.70710678f,  0,
                     0,            1,  0,            0,
                     -0.70710678f, 0,  0.70710678f,  0,
                     0,            0,  0,            1),

            Matrix ( 0.70710678f,  0,  0.70710678f,  0,
                     0,            1,  0,            0,
                     -0.70710678f, 0,  0.70710678f,  0,
                     0,            0,  0,            1),

            Matrix (-0.70710678f, 0, -0.70710678f,  0,
                    0,            1,  0,            0,
                    0.70710678f,  0, -0.70710678f,  0,
                    0,            0,  0,            1),

            Matrix ( 0.70710678f, 0, -0.70710678f, 0,
                     0,           1,  0,           0,
                     0.70710678f, 0,  0.70710678f, 0,
                     0,           0,  0,           1)
        };

    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->disableDefaultPartition();


    Background      *pBack      = a->getBackground();

#if 0
    Viewport        *pPort      = a->getViewport();
#endif

    FishEyeProjectorData *pData = 
        a->getData<FishEyeProjectorData *>(_iDataSlotId);


    if(pData == NULL)
    {
        pData = this->initData(a);
    }

    this->beginPartitionGroup(a);
    {

        FrameBufferObject *pTarget  = pData->getRenderTarget();

        Matrix mGlobalCam;

#if 0
        if(pPort != NULL)
        {
            Camera *pGlobalCam = pPort->getCamera();


            pGlobalCam->getViewing(mGlobalCam, 
                                   pPort->getPixelWidth (),
                                   pPort->getPixelHeight());
        }
#endif

        mGlobalCam = a->getActivePartition()->getDrawEnv().getVPCameraViewing();

        Camera *pCam = pData->getCamera();

        for(UInt32 i = 0; i < 4; ++i)
        {
            this->pushPartition(a);
            {
                RenderPartition   *pPart    = a->getActivePartition();
                
                pPart->setVolumeDrawing(false);

                pPart->setRenderTarget(pTarget       );
                pPart->setWindow      (a->getWindow());

                pPart->calcViewportDimension(0,
                                             0,
                                             1,
                                             1,
                                             this->getResolution(),
                                             this->getResolution());
                
                Matrix m, t;
            
                // set the projection
                pCam->getProjection          (m, 
                                              pPart->getViewportWidth (), 
                                              pPart->getViewportHeight());
                
                pCam->getProjectionTranslation(t, 
                                               pPart->getViewportWidth (), 
                                               pPart->getViewportHeight());
                
                pPart->setupProjection(m, t);

                m = transforms[i];
            
                m.multLeft(deltaTr[i]);

                m.invert();

                m.mult(mGlobalCam);

                pPart->setupViewing(m);
            
                pPart->setNear     (pCam->getNear());
                pPart->setFar      (pCam->getFar ());
                
                pPart->calcFrustum();
                
                pPart->setBackground(pBack);

               
                a->useNodeList(false);

                this->recurseFromThis(a);

                pPart->setDrawBuffer(GL_COLOR_ATTACHMENT0_EXT + i);

#ifdef OSG_DEBUGX
                std::string szMessage("fishX\n");
                pPart->setDebugString(szMessage          );
#endif
            }
            this->popPartition(a);
        }


        
        this->pushPartition(a,
                            (RenderPartition::CopyWindow      |
                             RenderPartition::CopyViewportSize),
                            RenderPartition::SimpleCallback);
        {
            RenderPartition *pPart  = a->getActivePartition();

#ifdef OSG_DEBUGX
            std::string szMessage("PostProcessPartition\n");
            pPart->setDebugString(szMessage          );
#endif
           
            Matrix m, t;
                
            m.setIdentity();
            t.setIdentity();
                
            MatrixOrthogonal( m,
                              0.f, 1.f,
                              0.f, 1.f,
                              -1.f, 1.f);
            
            pPart->setupProjection(m, t);
                
            RenderPartition::SimpleDrawCallback f;
                
            f = boost::bind(&FishEyeProjector::postProcess, this, _1);
                
            pPart->dropFunctor(f);
        }
        this->popPartition(a);
    }
    this->endPartitionGroup(a);

    return Action::Skip;
}

Action::ResultE FishEyeProjector::renderLeave(Action *action)
{
    return Action::Skip;
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void FishEyeProjector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            FishEyeProjector::getClassType(), 
            reinterpret_cast<Action::Callback>(&FishEyeProjector::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            FishEyeProjector::getClassType(), 
            reinterpret_cast<Action::Callback>(&FishEyeProjector::renderLeave));

        _uiFramebufferObjectExt = 
            Window::registerExtension("GL_EXT_framebuffer_object");

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebufferObjectExt);
    }
}

void FishEyeProjector::warpData(Geometry *pGeo)
{
    GeoVec3dPropertyUnrecPtr pPosProp =
        dynamic_cast<GeoVec3dProperty *>(
            pGeo->getProperty(Geometry::PositionsIndex));

    GeoVec2dPropertyUnrecPtr pUVProp  = 
        dynamic_cast<GeoVec2dProperty *>(
            pGeo->getProperty(Geometry::TexCoordsIndex));

    GeoColor3fPropertyUnrecPtr pColProp = 
        dynamic_cast<GeoColor3fProperty *>(
            pGeo->getProperty(Geometry::ColorsIndex));

    if(pColProp == NULL)
    {
        pColProp = GeoColor3fProperty::create();

        GeoUInt32Property *pIdx = 
            dynamic_cast<GeoUInt32Property *>(
                pGeo->getIndex(Geometry::TexCoordsIndex));


        pGeo->setProperty(pColProp, Geometry::ColorsIndex);
        pGeo->setIndex   (pIdx,     Geometry::ColorsIndex);
    }

    if(this->getShowDomeIntensity() == false)
        pColProp->setIgnore(true);

    MFVec3d   &oPos = *(pPosProp->editFieldPtr());
    MFVec2d   &oUV  = *(pUVProp ->editFieldPtr());
    MFColor3f &oCol = *(pColProp->editFieldPtr());

    oCol.resize(oPos.size());

    Real64 x[3], z[3], b[3];

    UInt32 uiNumTris = oPos.size32() / 3;

    UInt32 uiCurrIdx = 0;

    for(UInt32 i = 0; i < uiNumTris; ++i)
    {

        EstimateWarp(oPos[i * 3 + 0][0],
                     oPos[i * 3 + 0][2], (x[0]), (z[0]), (b[0]));

        EstimateWarp(oPos[i * 3 + 1][0],
                     oPos[i * 3 + 1][2], (x[1]), (z[1]), (b[1]));

        EstimateWarp(oPos[i * 3 + 2][0],
                     oPos[i * 3 + 2][2], (x[2]), (z[2]), (b[2]));

        if(b[0] < 0 || b[1] < 0 || b[2] < 0)
        {
            continue;
        }

        for(UInt32 j = 0; j < 3; ++j)
        {
            oPos[uiCurrIdx][0] = x[j];
            oPos[uiCurrIdx][1] = 0;
            oPos[uiCurrIdx][2] = z[j];
        
            oUV[uiCurrIdx] = oUV[i * 3 + j];

            oCol[uiCurrIdx].setValuesRGB(b[j], b[j], b[j]);
            
            ++uiCurrIdx;
        }
    }

    oPos.resize(uiCurrIdx);
    oUV .resize(uiCurrIdx);
    oCol.resize(uiCurrIdx);
}


void FishEyeProjector::flattenVertex(Vec3d  &oVertex, 
                                     Real64  aperture)
{
	double phi,r;

	r   = atan2(osgSqrt(oVertex[0] * oVertex[0] + oVertex[2] * oVertex[2]), 
                oVertex[1]) / (osgDegree2Rad(aperture) / 2);

	phi = atan2(oVertex[2], oVertex[0]);
	
	oVertex[0] = r * osgCos(phi);
	oVertex[1] = 0;
	oVertex[2] = r * osgSin(phi);
}

void FishEyeProjector::splitFaces(MFVec2d &vUV,
                                  MFVec3d &vP,
                                  UInt32  &uiSize)
{
	UInt32 oldSize = uiSize;
    UInt32 n2      = uiSize;

	for(UInt32 i = 0; i < oldSize; i++) 
    {
        osgMedian(vP[n2 * 3 + 0], vP[i * 3 + 0], vP[i * 3 + 1]);

        vP[n2 * 3 + 1] = vP[i * 3 + 1];

        osgMedian(vP[n2 * 3 + 2], vP[i * 3 + 1], vP[i * 3 + 2]);


        osgMedian(vUV[n2 * 3 + 0], vUV[i * 3 + 0], vUV[i * 3 + 1]);

        vUV[n2 * 3 + 1] = vUV[i * 3 + 1];

        osgMedian(vUV[n2 * 3 + 2], vUV[i * 3 + 1], vUV[i * 3 + 2]);
        
        

        osgMedian(vP[(n2+1) * 3 + 0], vP[i * 3 + 1],vP[i * 3 + 2]);

        vP[(n2+1) * 3 + 1] = vP[i * 3 + 2];

        osgMedian(vP[(n2+1) * 3 + 2], vP[i * 3 + 2],vP[i * 3 + 0]);


        osgMedian(vUV[(n2+1) * 3 + 0], vUV[i * 3 + 1], vUV[i * 3 + 2]);

        vUV[(n2+1) * 3 + 1] = vUV[i * 3 + 2];

        osgMedian(vUV[(n2+1) * 3 + 2], vUV[i * 3 + 2], vUV[i * 3 + 0]);
        


        osgMedian(vP[(n2+2) * 3 + 0], vP[i * 3 + 0], vP[i * 3 + 1]);
        osgMedian(vP[(n2+2) * 3 + 1], vP[i * 3 + 1], vP[i * 3 + 2]);
        osgMedian(vP[(n2+2) * 3 + 2], vP[i * 3 + 2], vP[i * 3 + 0]);

        osgMedian(vUV[(n2+2) * 3 + 0], vUV[i * 3 + 0], vUV[i * 3 + 1]);
        osgMedian(vUV[(n2+2) * 3 + 1], vUV[i * 3 + 1], vUV[i * 3 + 2]);
        osgMedian(vUV[(n2+2) * 3 + 2], vUV[i * 3 + 2], vUV[i * 3 + 0]);



        osgMedian(vP[i * 3 + 1], vP[i * 3 + 0], vP[i * 3 + 1]);
        osgMedian(vP[i * 3 + 2], vP[i * 3 + 0], vP[i * 3 + 2]);

        osgMedian(vUV[i * 3 + 1], vUV[i * 3 + 0], vUV[i * 3 + 1]);
        osgMedian(vUV[i * 3 + 2], vUV[i * 3 + 0], vUV[i * 3 + 2]);

		n2 += 3;
	}

	uiSize = n2;
}


void FishEyeProjector::initTopMesh(Geometry *pGeo)
{
    GeoVec2dPropertyUnrecPtr pUVProp  = 
        dynamic_cast<GeoVec2dProperty *>(
            pGeo->getProperty(Geometry::TexCoordsIndex));

    GeoVec3dPropertyUnrecPtr pPosProp =
        dynamic_cast<GeoVec3dProperty *>(
            pGeo->getProperty(Geometry::PositionsIndex));

    OSG_ASSERT(pUVProp  != NULL);
    OSG_ASSERT(pPosProp != NULL);

    MFVec2d  &oUV  = *(pUVProp ->editFieldPtr());
    MFVec3d  &oPos = *(pPosProp->editFieldPtr());

    Real32 rSq2H = osgSqrt(2.0) / 2.0;

    oUV .resize(3);
    oPos.resize(3);

    oPos[0].setValues(-rSq2H,   0.0, 0.5);
    oPos[1].setValues(   0.0, rSq2H, 0.5);
    oPos[2].setValues( rSq2H,   0.0, 0.5);

    
    oUV[0].setValues(0.0, 1.0);
    oUV[1].setValues(0.0, 0.0);
    oUV[2].setValues(1.0, 0.0);
}

void FishEyeProjector::initBottomMesh(Geometry *pGeo)
{
    GeoVec2dPropertyUnrecPtr pUVProp  = 
        dynamic_cast<GeoVec2dProperty *>(
            pGeo->getProperty(Geometry::TexCoordsIndex));

    GeoVec3dPropertyUnrecPtr pPosProp =
        dynamic_cast<GeoVec3dProperty *>(
            pGeo->getProperty(Geometry::PositionsIndex));

    OSG_ASSERT(pUVProp  != NULL);
    OSG_ASSERT(pPosProp != NULL);

    MFVec2d  &oUV  = *(pUVProp ->editFieldPtr());
    MFVec3d  &oPos = *(pPosProp->editFieldPtr());

    Real32 rSq2H = osgSqrt(2.0) / 2.0;

    oUV .resize(3);
    oPos.resize(3);
 
    oPos[0].setValues(-rSq2H,   0.0, -0.5);
    oPos[1].setValues( rSq2H,   0.0, -0.5);
    oPos[2].setValues(   0.0, rSq2H, -0.5);
  
    oUV[0].setValues(1.0, 0.0);
    oUV[1].setValues(0.0, 1.0);
    oUV[2].setValues(0.0, 0.0);
}

void FishEyeProjector::initLeftMesh(Geometry *pGeo)
{
    GeoVec2dPropertyUnrecPtr pUVProp  = 
        dynamic_cast<GeoVec2dProperty *>(
            pGeo->getProperty(Geometry::TexCoordsIndex));

    GeoVec3dPropertyUnrecPtr pPosProp =
        dynamic_cast<GeoVec3dProperty *>(
            pGeo->getProperty(Geometry::PositionsIndex));

    OSG_ASSERT(pUVProp  != NULL);
    OSG_ASSERT(pPosProp != NULL);

    MFVec2d  &oUV  = *(pUVProp ->editFieldPtr());
    MFVec3d  &oPos = *(pPosProp->editFieldPtr());

    Real32 rSq2H = osgSqrt(2.0) / 2.0;

    oUV .resize(6);
    oPos.resize(6);

    oPos[0].setValues(-rSq2H,   0.0, -0.5);
    oPos[1].setValues(   0.0, rSq2H, -0.5);
    oPos[2].setValues(-rSq2H,   0.0,  0.5);

    oUV[0].setValues(0.0, 0.0);
    oUV[1].setValues(1.0, 0.0);
    oUV[2].setValues(0.0, 1.0);


    oPos[3].setValues(-rSq2H,   0.0,  0.5);
    oPos[4].setValues(   0.0, rSq2H, -0.5);
    oPos[5].setValues(   0.0, rSq2H,  0.5);

    oUV[3].setValues(0.0, 1.0);
    oUV[4].setValues(1.0, 0.0);
    oUV[5].setValues(1.0, 1.0);
}

void FishEyeProjector::initRightMesh(Geometry *pGeo)
{
    GeoVec2dPropertyUnrecPtr pUVProp  = 
        dynamic_cast<GeoVec2dProperty *>(
            pGeo->getProperty(Geometry::TexCoordsIndex));

    GeoVec3dPropertyUnrecPtr pPosProp =
        dynamic_cast<GeoVec3dProperty *>(
            pGeo->getProperty(Geometry::PositionsIndex));

    OSG_ASSERT(pUVProp  != NULL);
    OSG_ASSERT(pPosProp != NULL);

    MFVec2d  &oUV  = *(pUVProp ->editFieldPtr());
    MFVec3d  &oPos = *(pPosProp->editFieldPtr());

    Real32 rSq2H = osgSqrt(2.0) / 2.0;

    oUV .resize(6);
    oPos.resize(6);

    oPos[0].setValues(0.0, rSq2H, -0.5);
    oPos[1].setValues(rSq2H, 0.0, -0.5);
    oPos[2].setValues(rSq2H, 0.0, 0.5);

    oUV[0].setValues(0.0, 0.0);
    oUV[1].setValues(1.0, 0.0);
    oUV[2].setValues(1.0, 1.0);


    oPos[3].setValues(  0.0, rSq2H, -0.5);
    oPos[4].setValues(rSq2H,   0.0,  0.5);
    oPos[5].setValues(  0.0, rSq2H,  0.5);

    oUV[3].setValues(0.0, 0.0);
    oUV[4].setValues(1.0, 1.0);
    oUV[5].setValues(0.0, 1.0);
}

void FishEyeProjector::updateMesh(Geometry *pGeo)
{
    GeoVec2dPropertyUnrecPtr pUVProp  = 
        dynamic_cast<GeoVec2dProperty *>(
            pGeo->getProperty(Geometry::TexCoordsIndex));

    GeoVec3dPropertyUnrecPtr pPosProp =
        dynamic_cast<GeoVec3dProperty *>(
            pGeo->getProperty(Geometry::PositionsIndex));

    OSG_ASSERT(pUVProp  != NULL);
    OSG_ASSERT(pPosProp != NULL);

    MFVec2d  &oUV  = *(pUVProp ->editFieldPtr());
    MFVec3d  &oPos = *(pPosProp->editFieldPtr());

    UInt32 uiNumTris = oPos.size32() / 3;

    for(UInt32 i = 0; i < this->getMeshRefinementLevel(); i++) 
    {
        oUV .resize(4 * uiNumTris * 3);
        oPos.resize(4 * uiNumTris * 3);
        
        splitFaces(oUV, oPos, uiNumTris);
    }
    
    for(UInt32 i = 0; i < oPos.size(); i++)
        oPos[i].normalize();
    
    for(UInt32 i = 0; i < oPos.size(); i++)
    {
        flattenVertex(oPos[i], 180.0);
    }
    
    
    GeoUInt32Property *pIdx = 
        dynamic_cast<GeoUInt32Property *>(
            pGeo->getIndex(Geometry::TexCoordsIndex));
    
    GeoUInt32Property *pLen = 
        dynamic_cast<GeoUInt32Property *>(pGeo->getLengths());
    
    GeoUInt8Property  *pTyp = 
        dynamic_cast<GeoUInt8Property   *>(pGeo->getTypes());
    
    OSG_ASSERT(pIdx != NULL);
    OSG_ASSERT(pLen != NULL);
    OSG_ASSERT(pTyp != NULL);
    
    
//    if(this->getMode() == FishEyeProjector::WarpMap || ToDo
    if(this->getMode() == FishEyeProjector::MirrorDome ) 
    {
        warpData(pGeo);
    }
    else
    {
        GeoVectorProperty *pColProp = pGeo->getProperty(Geometry::ColorsIndex);
        
        if(pColProp != NULL)
        {
            pColProp->setIgnore(true);
        }
    }

    pTyp->clear();
    pLen->clear();

    pTyp->push_back(GL_TRIANGLES );
    pLen->push_back(oPos.size32());

    pIdx->clear();

    for(UInt32 i = 0; i < oPos.size(); ++i)
    {
        pIdx->push_back(i);
    }
}

void FishEyeProjector::rebuildGeometries(void)
{
    if(this->_mfGeometries.size() == 0)
    {
        for(UInt32 i = 0; i < 4; ++i)
        {
            GeometryUnrecPtr pGeo = Geometry::create();

            GeoVec2dPropertyUnrecPtr pUV  = GeoVec2dProperty::create();
            GeoVec3dPropertyUnrecPtr pPos = GeoVec3dProperty::create();
            
            GeoUInt32PropertyUnrecPtr pIdx = GeoUInt32Property::create();
            GeoUInt32PropertyUnrecPtr pLen = GeoUInt32Property::create();
            GeoUInt8PropertyUnrecPtr  pTyp = GeoUInt8Property ::create();

            pGeo->setProperty(pUV,  Geometry::TexCoordsIndex);
            pGeo->setProperty(pPos, Geometry::PositionsIndex);

            pGeo->setTypes  (pTyp);
            pGeo->setLengths(pLen);

            pGeo->setIndex(pIdx, Geometry::PositionsIndex);
            pGeo->setIndex(pIdx, Geometry::TexCoordsIndex);

            this->pushToGeometries(pGeo);
        }
    }


    initTopMesh   (this->getGeometries(0));
    updateMesh    (this->getGeometries(0));

    initBottomMesh(this->getGeometries(1));
    updateMesh    (this->getGeometries(1));

    initLeftMesh  (this->getGeometries(2));
    updateMesh    (this->getGeometries(2));

    initRightMesh (this->getGeometries(3));
    updateMesh    (this->getGeometries(3));
}

FishEyeProjectorData *FishEyeProjector::initData(RenderActionBase *pAction)
{
    FishEyeProjectorDataUnrecPtr pData = 
        pAction->getData<FishEyeProjectorData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pAction);
        
        this->setData(pData, _iDataSlotId, pAction);
    }

    return pData;
}

FishEyeProjectorDataTransitPtr FishEyeProjector::setupStageData(
    RenderActionBase *pAction)
{
    FishEyeProjectorDataTransitPtr returnValue = 
        FishEyeProjectorData::createLocal();
    
    if(returnValue == NULL)
        return returnValue;

    FrameBufferObjectUnrecPtr pTarget      = NULL;
    RenderBufferUnrecPtr      pDepthBuffer = NULL;

    pTarget      = FrameBufferObject::createLocal();
    pDepthBuffer = RenderBuffer     ::createLocal();

    pDepthBuffer->setInternalFormat (GL_DEPTH_COMPONENT24);

    pTarget     ->setDepthAttachment(pDepthBuffer        );

    returnValue ->setRenderTarget   (pTarget             );


    for(UInt32 i = 0; i < 4; ++i)
    {
        TextureObjChunkUnrecPtr pTex = TextureObjChunk::createLocal();

        ImageUnrecPtr pImg = Image::createLocal();
    
        pImg->set(Image::OSG_RGB_PF, 
                  this->getResolution(), 
                  this->getResolution(),
                  1,
                  1,
                  1,
                  0.0,
                  0,
                  Image::OSG_UINT8_IMAGEDATA,
                  false,
                  1);
        
        pTex   ->setImage         (pImg                   ); 
        pTex   ->setMinFilter     (GL_LINEAR              );
        pTex   ->setMagFilter     (GL_LINEAR              );
        pTex   ->setWrapS         (GL_CLAMP_TO_EDGE       );
        pTex   ->setWrapT         (GL_CLAMP_TO_EDGE       );
        pTex   ->setInternalFormat(this->getBufferFormat());


        TextureBufferUnrecPtr pTexBuffer = TextureBuffer::createLocal();
    
        pTexBuffer->setTexture  (pTex         );
        pTexBuffer->setTexTarget(GL_TEXTURE_2D);

        pTarget->setColorAttachment(pTexBuffer, i);

        returnValue->editMFTextures()->push_back(pTex);
    }



    pTarget->setSize(this->getResolution(),
                     this->getResolution());
    


    PerspectiveCameraUnrecPtr pCam = PerspectiveCamera::createLocal();

    pCam->setNear(pAction->getCamera()->getNear());
    pCam->setFar (pAction->getCamera()->getFar ());
        
    pCam->setFov (osgDegree2Rad(90.f));

    returnValue->setCamera(pCam);

    
    returnValue->setTextureRes   (this->getResolution  ());
    returnValue->setTextureFormat(this->getBufferFormat());


    commitChanges();


    return returnValue;
}


void FishEyeProjector::resizeStageData(FishEyeProjectorData *pData,
                                       Int32                 iPixelWidth,
                                       Int32                 iPixelHeight)
{
    FWARNING(("FishEyeProjector resize not implemented ==> wrong results\n"));
}


void FishEyeProjector::postProcess(DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtOrVersion(_uiFramebufferObjectExt, 0x0300, 0x0200) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

    FishEyeProjectorData *pData = 
        pEnv->getData<FishEyeProjectorData *>(_iDataSlotId);

    
    if(pData == NULL)
        return;



 
    if(this->getMode() == WarpMap)
    {
        glClearColor(0.0,0.0,0.0,0.0);
    }
    else
    {
        glClearColor(0.05f,0.05f,0.05f,0.0f);
    }


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Create camera projection for dome
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    switch(this->getMode())
    {
        case TruncateBottom:
            gluLookAt(0.0,-1.0,0.25,0.0,0.0,0.25,0.0,0.0,1.0);
            break;

        case TruncateTop:
            gluLookAt(0.0,-1.0,-0.25,0.0,0.0,-0.25,0.0,0.0,1.0);
            break;

        case DomeVertical:
        case DomeHorizontal:
        case WarpMap:
        case MirrorDome:
        default:
            gluLookAt(0.0,-1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0);
            break;
    }


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    

    glViewport(0,0,
               pEnv->getPixelWidth (),  
               pEnv->getPixelHeight()); 
    
    double r = pEnv->getPixelWidth () / double(pEnv->getPixelHeight());

    switch(this->getMode())
    {
        case TruncateBottom:
        case TruncateTop:
            glOrtho(-r*0.75,r*0.75,-0.75,0.75,0.1,10.0);
            break;

        case DomeHorizontal:
            glOrtho(-r*0.75,r*0.75,-0.75,0.75,0.1,10.0);
            break;

        case DomeVertical:
        case WarpMap:
        case MirrorDome:
        default:
            glOrtho(-r,r,-1.0,1.0,0.1,10.0);
            break;
    }


    // Finally draw the dome geometry

    if(this->getShowMesh() == true)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glColor3f(1.0,1.0,1.0);


    TextureObjChunk *pTexT = pData->getTextures (3);
    Geometry        *pGeoT = this->getGeometries(0);

    pTexT->activate(pEnv);

    pGeoT->drawPrimitives(pEnv);


    TextureObjChunk *pTexB = pData->getTextures (2);
    Geometry        *pGeoB = this->getGeometries(1);

    pTexB->changeFrom(pEnv, pTexT);

    pGeoB->drawPrimitives(pEnv);


    TextureObjChunk *pTexL = pData->getTextures (0);
    Geometry        *pGeoL = this->getGeometries(2);

    pTexL->changeFrom(pEnv, pTexB);

    pGeoL->drawPrimitives(pEnv);


    TextureObjChunk *pTexR = pData->getTextures (1);
    Geometry        *pGeoR = this->getGeometries(3);

    pTexR->changeFrom(pEnv, pTexL);

    pGeoR->drawPrimitives(pEnv);

    pTexR->deactivate(pEnv);

    if(this->getShowMesh() == true)
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


#ifdef OSG_DRAW_FACES
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0,1.0,-1.0,1.0,0.1,10.0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glDisable(GL_DEPTH_TEST);
    
    TextureObjChunk *pTex1 = pData->getTextures(0);

    pTex1->activate(pEnv);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.9, -0.9, -1.0);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(-0.6, -0.9, -1.0);

        glTexCoord2f(1.0, 1.0);
        glVertex3f(-0.6, -0.6, -1.0);

        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.9, -0.6, -1.0);
    }
    glEnd();

    TextureObjChunk *pTex2 = pData->getTextures(1);

    pTex2->changeFrom(pEnv, pTex1);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, -0.9, -1.0);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(-0.2, -0.9, -1.0);

        glTexCoord2f(1.0, 1.0);
        glVertex3f(-0.2, -0.6, -1.0);

        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, -0.6, -1.0);
    }
    glEnd();

    pTex1 = pData->getTextures(2);

    pTex1->changeFrom(pEnv, pTex2);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.1, -0.9, -1.0);

        glTexCoord2f(1.0, 0.0);
        glVertex3f( 0.2, -0.9, -1.0);

        glTexCoord2f(1.0, 1.0);
        glVertex3f( 0.2, -0.6, -1.0);

        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.1, -0.6, -1.0);
    }
    glEnd();

    pTex2 = pData->getTextures(3);

    pTex2->changeFrom(pEnv, pTex1);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.3, -0.9, -1.0);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.6, -0.9, -1.0);

        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.6, -0.6, -1.0);

        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.3, -0.6, -1.0);
    }
    glEnd();

    pTex2->deactivate(pEnv);

	glEnable(GL_DEPTH_TEST);
#endif


    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

}

