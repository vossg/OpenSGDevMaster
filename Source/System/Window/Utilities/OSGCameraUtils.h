/*---------------------------------------------------------------------------*\
 *                             OpenSG Toolbox                                *
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

#ifndef _OSGCAMERAUTILS_H_
#define _OSGCAMERAUTILS_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

/**
 * \brief Set position and direction of camera to show all of a node.
 * 
 * Sets the position and direction of a perspective camera such that the
 * volume bounding the node is contained in the view of the camera.  The near
 * clipping plane is set to 0.1 times of the maximum axis of the volume of the
 * node.  The far clipping plane is set to 10 times of the maximum axis of the
 * volume of the node.  The Up direction is used when calculating the camera's
 * orientation. 
 * @param[in,out] TheCamera The camera
 * @param[in] Scene The node to view
 * @param[in] Up The direction to use as the up direction when calculating the
 *               camera orientation 
 */

OSG_UTIL_DLLMAPPING
void showAll(PerspectiveCamera *pCamera, 
             Node              *pScene, 
             Vec3f              vUp    = Vec3f(0.0f, 1.0f, 0.0f));

/**
 * \brief Set position and direction of camera to show all of a node.
 * 
 * Sets the position and direction of a perspective camera such that the
 * volume bounding the node is contained in the view of the camera.  The near
 * clipping plane is set to 0.1 times of the maximum axis of the volume of the
 * node.  The far clipping plane is set to 10 times of the maximum axis of the
 * volume of the node.  The Up direction is used when calculating the camera's
 * orientation.  Currently this only works for perspective cameras.
 * @param[in,out] TheCamera The camera
 * @param[in] Scene The node to view
 * @param[in] Up The direction to use as the up direction when calculating the
 *               camera orientation 
 */

OSG_UTIL_DLLMAPPING 
void showAll(Camera *pCamera, 
             Node   *pScene, 
             Vec3f   vUp    = Vec3f(0.0f, 1.0f, 0.0f));

OSG_END_NAMESPACE

#endif //_OSGCAMERAUTILS_H_


