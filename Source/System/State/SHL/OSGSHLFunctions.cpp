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
//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <sstream>
#include <fstream>

#include <OSGConfig.h>
#include <OSGLog.h>
#include <OSGImage.h>
#include <OSGBaseFunctions.h>

#include "OSGSHLFunctions.h"


OSG_BEGIN_NAMESPACE

// 1d Gaussian distribution, s is standard deviation
Real32 gaussian(Real32 x, Real32 s)
{
    return expf(-x*x/(2.0f*s*s)) / (s*sqrtf(2.0f*Pi));
}

// generate array of weights for Gaussian blur
void generateGaussianWeights(Real32               fBlurWidth, 
                             std::vector<Real32> &vWeights,
                             Int32               &iFilterWidth)
{
    iFilterWidth = (int) floor(3.0f * fBlurWidth) - 1;

    Int32 size = iFilterWidth * 2 + 1;

    vWeights.resize(size);

    Real32 sum = 0.0;

    for(Int32 x = 0; x < size; x++) 
    {
        vWeights[x] = gaussian((float) x - iFilterWidth, fBlurWidth);

        sum += vWeights[x];
    }

    for(Int32 x = 0; x < size; x++) 
    {
        vWeights[x] /= sum;
    }
}

SHLChunkPtr generate1DConvolutionFilterFP(Real32 fBlurWidth,
                                          bool   vertical, 
                                          bool   tex2D, 
                                          Int32  imgWidth, 
                                          Int32  imgHeight)
{
    SHLChunkPtr returnValue = SHLChunk::create();
    
    int width;
    std::vector<Real32> weights;

    generateGaussianWeights(fBlurWidth, weights, width);

    // calculate new set of weights and offsets
    int nsamples = 2*width+1;
    int nsamples2 = (int) ceilf(nsamples/2.0f);
    float *weights2 = new float [nsamples2];
    float *offsets = new float [nsamples2];

    for(int i=0; i<nsamples2; i++) 
    {
        float a = weights[i*2];
        float b;
        if (i*2+1 > nsamples-1)
            b = 0;
        else
            b = weights[i*2+1];
        weights2[i] = a + b;
        offsets[i] = b / (a + b);
        //    printf("%d: %f %f\n", i, weights2[i], offsets[i]);
    }
//    printf("nsamples = %d\n", nsamples2);

    std::ostringstream ost;
    ost << "\n"
        << "uniform sampler2D inputTex;\n"
        << "\n"
        << "void main(void)\n"
        << "{\n"
        << "    vec2 texCoord;\n"
        << "    vec4 sum = vec4(0., 0., 0., 0.);\n"
        << "\n";


    for(int i=0; i<nsamples2; i++) {
        float x_offset = 0, y_offset = 0;
        if (vertical) {
            y_offset = (i*2)-width+offsets[i];
        } else {
            x_offset = (i*2)-width+offsets[i];
        }
        if (tex2D) {
            x_offset = x_offset / imgWidth;
            y_offset = y_offset / imgHeight;
        }
        float weight = weights2[i];


        ost << "    texCoord = gl_TexCoord[0].xy + vec2(" 
            << x_offset << ", " 
            << y_offset << ");\n";

//        if (tex2D) {
//            ost << "TEX  H1, R0, texture[0], 2D;\n";
//        } else {
//            ost << "TEX  H1, R0, texture[0], RECT;\n";
//        }

        if (i==-width) 
        {
//            ost << "MUL H2, H1, {" << weight << "}.x;\n";
        } 
        else 
        {
//            ost << "MAD H2, H1, {" << weight << "}.x, H2;\n";
            ost << "    sum += texture2D(inputTex, texCoord) * "
                << weight
                << ";\n";
        }
    }

    ost << "\n"
        << "    gl_FragColor = sum;\n"
        << "}\n";

    returnValue->setFragmentProgram(ost.str());

    delete [] weights2;
    delete [] offsets;

    return returnValue;
}

SHLChunkPtr generate2DShrinkHalfFilterFP(UInt32 uiTexCoord)
{
    std::ostringstream ost;

    ost << "uniform sampler2D inputTex;"
        << ""
        << "void main(void)"
        << "{"
        << "    gl_FragColor = texture2D(inputTex, gl_TexCoord["
        << uiTexCoord << "].xy);"
        << "}";

    SHLChunkPtr returnValue = SHLChunk::create();

    returnValue->setFragmentProgram(ost.str());

    return returnValue;
}

OSG_END_NAMESPACE
