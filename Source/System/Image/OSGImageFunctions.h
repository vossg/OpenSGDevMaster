/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGIMAGEFUNCTIONS_H_
#define _OSGIMAGEFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGColor.h"
#include "OSGImage.h"

#include <vector>
#include <string>
#include <iostream>


OSG_BEGIN_NAMESPACE

enum SliceDataType 
{
    INVALID_SDT = 0,
    DEPTH_SDT,
    FRAME_SDT,
    SIDE_SDT
};

OSG_SYSTEM_DLLMAPPING
bool createComposedImage ( std::vector<ImagePtr> srcImageVec,
                           ImagePtr              dstImage,
                           SliceDataType sliceDataType = DEPTH_SDT );


OSG_SYSTEM_DLLMAPPING 
bool createNormalMapFromBump ( ImagePtr srcImage,
                               ImagePtr dstImage,
                               Vec3f    normalMapScale);

OSG_SYSTEM_DLLMAPPING
bool createNormalVolume (       ImagePtr     srcImage,
                                ImagePtr     dstImage,
                          const std::string &outputFormat );

OSG_SYSTEM_DLLMAPPING 
bool create2DPreIntegrationLUT ( ImagePtr dstImage,
                                 ImagePtr srcImage,
                                 Real32   thickness = 1.0 );
OSG_SYSTEM_DLLMAPPING 
bool splitRGBA ( ImagePtr rgba,
                 ImagePtr rgb,
                 ImagePtr alpha);

OSG_SYSTEM_DLLMAPPING 
bool mergeRGBA ( ImagePtr rgb,
                 ImagePtr alpha,
                 ImagePtr rgba);

OSG_SYSTEM_DLLMAPPING
bool blendImage ( ImagePtr canvas, 
                  ImagePtr brush,
                  Vec3f    position,
                  Color4f  color, 
                  Real32   alphaScale = 1,
                  Real32   paintZ  = 0 );

OSG_SYSTEM_DLLMAPPING 
bool createPhongTexture (ImagePtr image,
                         UInt32   size = 512,
                         Real32   specular_exponent = 10,
                         Real32   ka = 0,
                         Real32   kd = 0,
                         Real32   ks = 1);

OSG_SYSTEM_DLLMAPPING 
bool createPhongVolume ( ImagePtr image,
                         Color3f  diffuseColor,
                         Color3f  specularColor,
                         UInt32   lutSize,
                         UInt32   lutScalar,
                         Real32   lutIncr );

OSG_SYSTEM_DLLMAPPING
bool createNormalizationCubeMap ( std::vector<ImagePtr> imageVec,
                                  UInt32 size );

OSG_SYSTEM_DLLMAPPING
bool createNoise ( ImagePtr image,
                   Image::PixelFormat pixelformat = Image::OSG_RGBA_PF,
                   UInt16 numOctaves = 6,
                   UInt16 size = 128,
                   UInt8  dim  = 2,
                   bool   splitOctaves = false);

OSG_SYSTEM_DLLMAPPING
bool createGamma(ImagePtr image, 
                 UInt32   size, 
                 Real32   gamma);

OSG_SYSTEM_DLLMAPPING
bool createVignette(ImagePtr image, 
                    UInt32   width, 
                    UInt32   height, 
                    Real32   r0, 
                    Real32   r1);

OSG_SYSTEM_DLLMAPPING
bool convertCrossToCubeMap(ImageConstPtrArg pIn,
                           ImagePtr         pOut);
                           
OSG_END_NAMESPACE

#include "OSGImageFunctions.inl"

#endif /* _OSGIMAGEFUNCTIONS_H_ */
