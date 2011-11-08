/*---------------------------------------------------------------------------*\
 *                           OpenSG Toolbox                                  *
 *                                                                           *
 *                                                                           *
 *                        Authors: David Kabala                              *
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

#include "OSGPerlinNoise.h"

OSG_BEGIN_NAMESPACE

namespace Perlin
{

Real32 calcPerlinNoise(Real32 t, 
                       Real32 fAmplitude, 
                       Real32 fFrequency, 
                       Real32 fPhase, 
                       Real32 fPersistance, 
                       UInt32 uiOctaves, 
                       UInt32 uiInterpolMode, 
                       bool   bSmoothing)
{
    Real32 total     = 0.0f;
    Real32 amplitude = fAmplitude;
    Real32 frequency = fFrequency;
    Real32 pos       = t + fPhase;
    
    for(UInt32 i = 0; i < uiOctaves; ++i)
    {
        if(i > 0)
        {
            frequency *= 2.0f;
            amplitude *= fPersistance;
        }
        
        total += interpolatedNoise(pos * frequency, 
                                   i, 
                                   uiInterpolMode, 
                                   bSmoothing     ) * amplitude;
    }
    
    return total;
}


Real32 interpolateCosine(Real32 a, Real32 b, Real32 t)
{
    // returns cosine interpolation of t between a and b
    
    Real32 f = (1.f - std::cos(t * 3.1415927f)) * .5f;
    
    return  a * (1.0f - f) + b * f;
}

Real32 interpolateLinear(Real32 a, Real32 b, Real32 t)
{
    return  a * (1.0f - t) + b * t;
}

Real32 interpolatedNoise(Real32 t, 
                         UInt32 uiOctave, 
                         UInt32 uiInterpolMode, 
                         bool   bSmoothing)
{
    Real32 intT      = osgFloor(t);
    Real32 fractionT = t - intT;
    Real32 v1;
    Real32 v2;
    
    if(bSmoothing == true)
    {
        v1 = (getNoise(intT,        uiOctave) / 2.0f + 
              getNoise(intT - 1.0f, uiOctave) / 4.0f + 
              getNoise(intT + 1.0f, uiOctave) / 4.0f );
        
        intT += 1.0f;
        
        v2 = (getNoise(intT,        uiOctave) / 2.0f + 
              getNoise(intT - 1.0f, uiOctave) / 4.0f + 
              getNoise(intT + 1.0f, uiOctave) / 4.0f );
    } 
    else
    {
        v1 = getNoise(intT,        uiOctave);
        v2 = getNoise(intT + 1.0f, uiOctave);
    }
    
    Real32 returnValue = 0.f;
    
    if(uiInterpolMode == InterpolateCosine) 
    {
        returnValue = interpolateCosine(v1 , v2 , fractionT);
    }
    else if(uiInterpolMode == InterpolateLinear) 
    {
        returnValue = interpolateLinear(v1 , v2 , fractionT);
    }

    return returnValue;
}

Real32 getNoise(Int32 t, UInt32 uiOctave)
{
    Real32 noiseVal = 0.0f;

    switch(uiOctave % 6)
    {
        case 0:
            t = (t << 13) ^ t;

            noiseVal = (1.0f - ((t * (t * t * 15731 + 789221) + 1376312579) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 1:
            t = (t << 11) ^ t;

            noiseVal = (1.0f - ((t * (t * t * 15683 + 789017) + 1376311273) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 2:
            t = (t << 15) ^ t;

            noiseVal = (1.0f - ((t * (t * t * 15733 + 789121) + 1376313067) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 3:
            t = (t << 17) ^ t;

            noiseVal = (1.0f - ((t * (t * t * 15761 + 789673) + 1376318989) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 4:
            t = (t << 13) ^ t;

            noiseVal = (1.0f - ((t * (t * t * 15787 + 789251) + 1376312689) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 5:
            t = (t << 7) ^ t;

            noiseVal = (1.0f - ((t * (t * t * 15667 + 789323) + 1376313793) & 
                                0x7fffffff) / 1073741824.0); 
            break;

    }

    return noiseVal;
}

Real32 calcPerlinNoise(const Pnt2f  &t, 
                             Real32  fAmplitude, 
                             Real32  fFrequency, 
                       const Vec2f  &vPhase, 
                             Real32  fPersistance, 
                             UInt32  uiOctaves, 
                             UInt32  uiInterpolMode, 
                             bool    bSmoothing)
{    
    Real32 total     = 0.0f;
    Real32 amplitude = fAmplitude;
    Real32 frequency = fFrequency;
    Pnt2f  pos       = t + vPhase;

    for(UInt32 i = 0; i < uiOctaves; ++i)
    {
        if(i > 0)
        {
            frequency *= 2;
            amplitude *= fPersistance;
        }

        total += interpolatedNoise(pos * frequency, 
                                   i, 
                                   uiInterpolMode, 
                                   bSmoothing     ) * amplitude;
    }

    return total;
}

Real32 interpolatedNoise(const Pnt2f&  t, 
                               UInt32 &uiOctave, 
                               UInt32  uiInterpolMode, 
                               bool    bSmoothing)
{
    Real32 intX        = osgFloor(t[0]);
    Real32 intY        = osgFloor(t[1]);
    Real32 fractionX   = t[0] - intX;
    Real32 fractionY   = t[1] - intY;

    Real32 i1          = 0.0f;
    Real32 i2          = 0.0f;
    Real32 returnValue = 0.0f;

    if(bSmoothing)
    {
        if(uiInterpolMode == InterpolateCosine)
        {
            i1 = interpolateCosine(smoothNoise(intX,        intY, uiOctave),
                                   smoothNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);
            intY += 1.0f;

            i2 = interpolateCosine(smoothNoise(intX,        intY, uiOctave),
                                   smoothNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);

            returnValue = interpolateCosine(i1 , i2 , fractionY);
        }
        else if(uiInterpolMode == InterpolateLinear)
        {
            i1 = interpolateLinear(smoothNoise(intX,        intY, uiOctave),
                                   smoothNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);

            intY += 1.0f;

            i2 = interpolateLinear(smoothNoise(intX,        intY, uiOctave),
                                   smoothNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);

            returnValue = interpolateLinear(i1 , i2 , fractionY);
        }
    } 
    else
    {
        if(uiInterpolMode == InterpolateCosine)
        {
            i1 = interpolateCosine(getNoise(intX,        intY, uiOctave),
                                   getNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);

            intY += 1.0f;

            i2 = interpolateCosine(getNoise(intX,        intY, uiOctave),
                                   getNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);

            returnValue = interpolateCosine(i1 , i2 , fractionY);
        }
        else if(uiInterpolMode == InterpolateLinear)
        {
            i1 = interpolateLinear(getNoise(intX,        intY, uiOctave),
                                   getNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);

            intY += 1.0f;

            i2 = interpolateLinear(getNoise(intX,        intY, uiOctave),
                                   getNoise(intX + 1.0f, intY, uiOctave), 
                                   fractionX);

            returnValue = interpolateLinear(i1 , i2 , fractionY);
        }
    }

    return returnValue;
}

Real32 smoothNoise(Real32 x, Real32 y, UInt32 &uiOctave)
{
    Real32 corners = (getNoise(x - 1, y - 1, uiOctave) + 
                      getNoise(x + 1, y - 1, uiOctave) + 
                      getNoise(x - 1, y + 1, uiOctave) + 
                      getNoise(x + 1, y + 1, uiOctave)) / 16.f;

    Real32 edges   = (getNoise(x - 1, y,     uiOctave) + 
                      getNoise(x + 1, y,     uiOctave) + 
                      getNoise(x,     y - 1, uiOctave) + 
                      getNoise(x,     y + 1, uiOctave)) / 8.f;

    Real32 center  =  getNoise(x,     y,     uiOctave)  / 4.f;

    return corners + edges + center;
}


Real32 getNoise(Int32 t1, Int32 t2, UInt32 &uiOctave)
{
    Real32 noiseVal = 0.0f;
    Int32  n        = 0;

    switch(uiOctave % 6)
    {
        case 0:
            n = t1 + t2 * 53;
            n = (n << 13) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15731 + 789221) + 1376312579) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 1:
            n = t1 + t2 * 61;
            n = (n << 11) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15683 + 789017) + 1376311273) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 2:
            n = t1 + t2 * 47;
            n = (n << 15) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15733 + 789121) + 1376313067) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 3:
            n = t1 + t2 * 67;
            n = (n << 17) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15761 + 789673) + 1376318989) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 4:
            n = t1 + t2 * 43;
            n = (n << 13) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15787 + 789251) + 1376312689) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 5:
            n = t1 + t2 * 59;
            n = (n << 7) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15667 + 789323) + 1376313793) & 
                                0x7fffffff) / 1073741824.0); 
            break;

    }
    
    return noiseVal;
}

Real32 calcPerlinNoise(const Pnt3f  &t, 
                             Real32  fAmplitude, 
                             Real32  fFrequency, 
                       const Vec3f  &vPhase, 
                             Real32  fPersistance, 
                             UInt32  uiOctaves, 
                             UInt32  uiInterpolMode, 
                             bool    bSmoothing    )
{
    
    Real32 total     = 0.0f;
    Real32 amplitude = fAmplitude;
    Real32 frequency = fFrequency;
    Pnt3f  pos       = t + vPhase;

    for(UInt32 i = 0; i < uiOctaves ; ++i)
    {
        if(i > 0)
        {
            frequency *= 2;
            amplitude *= fPersistance;
        }

        total += interpolatedNoise(pos * frequency, 
                                   i, 
                                   uiInterpolMode,
                                   bSmoothing     ) * amplitude;
    }

    return total;
}

Real32 interpolatedNoise(const Pnt3f  &t, 
                               UInt32 &uiOctave, 
                               UInt32  uiInterpolMode, 
                               bool    bSmoothing)
{
    Real32 intX        = osgFloor(t[0]);
    Real32 intY        = osgFloor(t[1]);
    Real32 intZ        = osgFloor(t[2]);
    Real32 fractionX   = t[0] - intX;
    Real32 fractionY   = t[1] - intY;
    Real32 fractionZ   = t[2] - intZ;
    Real32 returnValue = 0.0f;

    Real32 v1,v2,v3,v4,v5,v6,v7,v8,i1,i2,i3,i4;
    
    if(bSmoothing == true)
    {
        v1 = smoothNoise(intX,        intY,        intZ,        uiOctave);
        v2 = smoothNoise(intX + 1.0f, intY,        intZ,        uiOctave);
        v3 = smoothNoise(intX,        intY + 1.0f, intZ,        uiOctave);
        v4 = smoothNoise(intX + 1.0f, intY + 1.0f, intZ,        uiOctave);
        v5 = smoothNoise(intX,        intY,        intZ + 1.0f, uiOctave);
        v6 = smoothNoise(intX + 1.0f, intY,        intZ + 1.0f, uiOctave);
        v7 = smoothNoise(intX,        intY + 1.0f, intZ + 1.0f, uiOctave);
        v8 = smoothNoise(intX + 1.0f, intY + 1.0f, intZ + 1.0f, uiOctave);

        if(uiInterpolMode == InterpolateCosine)
        {
            i1 = interpolateCosine(v1, v2, fractionX);
            i2 = interpolateCosine(v3, v4, fractionX);
            i3 = interpolateCosine(v5, v6, fractionX);
            i4 = interpolateCosine(v7, v8, fractionX);

            i1 = interpolateCosine(i1, i2, fractionY);
            i2 = interpolateCosine(i3, i4, fractionY);

            returnValue = interpolateCosine(i1, i2, fractionZ);

        } 
        else if(uiInterpolMode == InterpolateLinear)
        {
            i1 = interpolateLinear(v1, v2, fractionX);
            i2 = interpolateLinear(v3, v4, fractionX);
            i3 = interpolateLinear(v5, v6, fractionX);
            i4 = interpolateLinear(v7, v8, fractionX);

            i1 = interpolateLinear(i1, i2, fractionY);
            i2 = interpolateLinear(i3, i4, fractionY);

            returnValue = interpolateLinear(i1, i2, fractionZ);

        }
    } 
    else
    {
        v1 = getNoise(intX,        intY,        intZ,        uiOctave);
        v2 = getNoise(intX + 1.0f, intY,        intZ,        uiOctave);
        v3 = getNoise(intX,        intY + 1.0f, intZ,        uiOctave);
        v4 = getNoise(intX + 1.0f, intY + 1.0f, intZ,        uiOctave);
        v5 = getNoise(intX,        intY,        intZ + 1.0f, uiOctave);
        v6 = getNoise(intX + 1.0f, intY,        intZ + 1.0f, uiOctave);
        v7 = getNoise(intX,        intY + 1.0f, intZ + 1.0f, uiOctave);
        v8 = getNoise(intX + 1.0f, intY + 1.0f, intZ + 1.0f, uiOctave);

        if(uiInterpolMode == InterpolateCosine)
        {
            i1 = interpolateCosine(v1, v2, fractionX);
            i2 = interpolateCosine(v3, v4, fractionX);
            i3 = interpolateCosine(v5, v6, fractionX);
            i4 = interpolateCosine(v7, v8, fractionX);

            i1 = interpolateCosine(i1, i2, fractionY);
            i2 = interpolateCosine(i3, i4, fractionY);

            returnValue = interpolateCosine(i1, i2, fractionZ);

        } 
        else if(uiInterpolMode == InterpolateLinear)
        {
            i1 = interpolateLinear(v1, v2, fractionX);
            i2 = interpolateLinear(v3, v4, fractionX);
            i3 = interpolateLinear(v5, v6, fractionX);
            i4 = interpolateLinear(v7, v8, fractionX);

            i1 = interpolateLinear(i1, i2, fractionY);
            i2 = interpolateLinear(i3, i4, fractionY);

            returnValue = interpolateLinear(i1, i2, fractionZ);
        }
    }

    return returnValue;
}

Real32 smoothNoise(Real32 x, Real32 y, Real32 z, UInt32 uiOctave)
{    // averages out the values from the corners, center of the sides, and the
     // center of a 1x1 cube, centered @ (x,y,z) 
    // where each side weighs 1/24, each corner weighs 1/16, and the center
    // weighs 1/4. 

    Real32 center  =  getNoise(x,     y,     z,     uiOctave)  / 4.f;
    
    Real32 corners = (getNoise(x + 1, y - 1, z - 1, uiOctave) + 
                      getNoise(x - 1, y - 1, z - 1, uiOctave) + 
                      getNoise(x + 1, y + 1, z - 1, uiOctave) + 
                      getNoise(x - 1, y + 1, z - 1, uiOctave) +
                      getNoise(x + 1, y - 1, z + 1, uiOctave) + 
                      getNoise(x - 1, y - 1, z + 1, uiOctave) + 
                      getNoise(x + 1, y + 1, z + 1, uiOctave) + 
                      getNoise(x - 1, y + 1, z + 1, uiOctave)) / 16.f;
    
    Real32 sides   = (getNoise(x + 1, y,     z,     uiOctave) + 
                      getNoise(x - 1, y,     z,     uiOctave) + 
                      getNoise(x,     y + 1, z,     uiOctave) +
                      getNoise(x,     y - 1, z,     uiOctave) + 
                      getNoise(x,     y,     z + 1, uiOctave) + 
                      getNoise(x,     y,     z - 1, uiOctave)) / 24.f;
        
    return center + corners + sides;
}

Real32 getNoise(Int32 t1, Int32 t2, Int32 t3, UInt32 uiOctave)
{
    Real32 noiseVal = 0.0f;
    Int32  n        = 0;

    switch(uiOctave % 6)
    {
        case 0:
            n = t1 * 23 + t2 * 53 + t3 * 31;
            n = (n << 13) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15731 + 789221) + 1376312579) & 
                                0x7fffffff) / 1073741824.0); 
            break;
            
        case 1:
            n = t1 * 71 + t2 * 53 + t3 * 3;
            n = (n << 11) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15683 + 789017) + 1376311273) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 2:
            n = t1 + t2 * 47 - t3 * 17;
            n = (n << 15) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15733 + 789121) + 1376313067) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 3:
            n = t1 * 29 + t2 * 67 - t3 * 61;
            n = (n << 17) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15761 + 789673) + 1376318989) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 4:
            n = t1 + t2 * 43 + t3 * 11;
            n = (n << 13) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15787 + 789251) + 1376312689) & 
                                0x7fffffff) / 1073741824.0); 
            break;

        case 5:
            n = t1 * 17 + t2 * 59 + t3;
            n = (n << 7) ^ n;

            noiseVal = (1.0f - ((n * (n * n * 15667 + 789323) + 1376313793) & 
                                0x7fffffff) / 1073741824.0); 
            break;

    }
    
    return noiseVal;
}

}

OSG_END_NAMESPACE

