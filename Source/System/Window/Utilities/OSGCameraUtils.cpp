/*---------------------------------------------------------------------------*\
 *                              OpenSG Toolbox                               *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include "OSGCameraUtils.h"
#include "OSGTransform.h"
#include "OSGMatrixUtility.h"

OSG_BEGIN_NAMESPACE

void showAll(Camera *pCamera, Node *pScene, Vec3f vUp)
{
    if(pCamera->getType() == PerspectiveCamera::getClassType())
    {
        showAll(dynamic_cast<PerspectiveCamera *>(pCamera), pScene, vUp);
    }
}

void showAll(PerspectiveCamera *pCamera, Node *pScene, Vec3f vUp)
{
    commitChanges();

    //Make sure the volume is up to date for the Scene
    pScene->updateVolume();

    //Get the Minimum and Maximum bounds of the volume
    Vec3f min,max;

    pScene->getVolume().getBounds( min, max );

    Vec3f d = max - min;

    if(d.length() < Eps) //The volume is 0
    {
        //Default to a 1x1x1 box volume
        min.setValues(-0.5f,-0.5f,-0.5f);
        max.setValues( 0.5f, 0.5f, 0.5f);

        d = max - min;
    }

    Real32 dist = osgMax(d[0], d[1]) / (2 * osgTan(pCamera->getFov() / 2.f));

    Pnt3f   at((min[0] + max[0]) * .5f,
               (min[1] + max[1]) * .5f,
               (min[2] + max[2]) * .5f);

    Pnt3f from = at;

    from[2] += (dist + fabs(max[2] - min[2]) * 0.5f); 

    //If the Camera Beacon is a node with a transfrom core
    if(pCamera->getBeacon()                                     != NULL &&
       pCamera->getBeacon()->getCore()                          != NULL &&
       pCamera->getBeacon()->getCore()->getType().isDerivedFrom(
           Transform::getClassType())                            == true)
    {
        Matrix m;

        if(!MatrixLookAt(m, from, at, vUp))
        {
            dynamic_cast<Transform *>(
                pCamera->getBeacon()->getCore())->setMatrix(m);
        }
    }

    //Set the camera to go from 1% of the object to 10 times its size
    Real32 diag = osgMax(osgMax(d[0], d[1]), d[2]);

    pCamera->setNear (diag / 100.f);
    pCamera->setFar  (10.f * diag);
}

OSG_END_NAMESPACE

