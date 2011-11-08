/*---------------------------------------------------------------------------*\
 *                              OpenSG ToolBox                               *
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

#ifndef _OSGPERLINNOISE_H_
#define _OSGPERLINNOISE_H_

#include "OSGVector.h"
#include "OSGBaseFunctions.h"

OSG_BEGIN_NAMESPACE

namespace Perlin
{
    enum NoiseInterpolation
    {
        InterpolateLinear    = 0, 
        InterpolateQuadratic = 2, 
        InterpolateCosine    = 1
    };
    
    OSG_BASE_DLLMAPPING 
    Real32 calcPerlinNoise(         Real32  t, 
                                    Real32  fAmplitude, 
                                    Real32  fFrequency, 
                                    Real32  fPhase, 
                                    Real32  fPersistance, 
                                    UInt32  fOctaves, 
                                    UInt32  uiInterpolMode = InterpolateCosine, 
                                    bool    bSmoothing     = true             );

    OSG_BASE_DLLMAPPING
    Real32 interpolateCosine(       Real32  a, 
                                    Real32  b, 
                                    Real32  t                                 );
    
    OSG_BASE_DLLMAPPING
    Real32 interpolateLinear(       Real32  a, 
                                    Real32  b, 
                                    Real32  t                                 );
    
    OSG_BASE_DLLMAPPING
    Real32 interpolatedNoise(       Real32  t, 
                                    UInt32  uiOctave, 
                                    UInt32  uiInterpolMode, 
                                    bool    bSmoothing                        );
    
    OSG_BASE_DLLMAPPING
    Real32  getNoise        (       Int32   t, 
                                    UInt32  uiOctave                          );

    OSG_BASE_DLLMAPPING
    Real32 calcPerlinNoise   (const Pnt2f  &t, 
                                    Real32  fAmplitude, 
                                    Real32  fFrequency, 
                              const Vec2f  &vPhase, 
                                    Real32  fPersistance, 
                                    UInt32  uiOctaves, 
                                    UInt32  uiInterpolMode = InterpolateCosine, 
                                    bool    bSmoothing     = true             );

    OSG_BASE_DLLMAPPING
    Real32  interpolatedNoise(const Pnt2f  &t, 
                                    UInt32 &uiOctave, 
                                    UInt32  uiInterpolMode, 
                                    bool    bSmoothing                        );

    OSG_BASE_DLLMAPPING
    Real32  smoothNoise      (      Real32  x, 
                                    Real32  y, 
                                    UInt32 &uiOctave                          );

    OSG_BASE_DLLMAPPING
    Real32  getNoise         (      Int32   t1, 
                                    Int32   t2, 
                                    UInt32 &uiOctave                          );
    
    OSG_BASE_DLLMAPPING
    Real32  calcPerlinNoise  (const Pnt3f  &t, 
                                    Real32  fAmplitude, 
                                    Real32  fFrequency, 
                              const Vec3f  &vPhase, 
                                    Real32  fPersistance, 
                                    UInt32  uiOctaves, 
                                    UInt32  uiInterpolMode = InterpolateCosine, 
                                    bool    bSmoothing     = true             );

    OSG_BASE_DLLMAPPING 
    Real32 interpolatedNoise (const Pnt3f  &t, 
                                    UInt32 &uiOctave, 
                                    UInt32  uiInterpolNode, 
                                    bool    bSmoothing                        );

    OSG_BASE_DLLMAPPING
    Real32 smoothNoise       (      Real32  x, 
                                    Real32  y, 
                                    Real32  z, 
                                    UInt32  uiOctave                          );

    OSG_BASE_DLLMAPPING
    Real32 getNoise          (      Int32   t1, 
                                    Int32   t2, 
                                    Int32   t3, 
                                    UInt32  uiOctave                          );
}

OSG_END_NAMESPACE

#endif


