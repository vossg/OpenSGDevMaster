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

#include "OSGCalibrationPatternFilter.h"
#include "OSGDisplayFilterStageData.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

static std::string vp_program =
    "varying vec2 position;\n"
    "varying mat4 shadingTexMat;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
    "   shadingTexMat  = gl_TextureMatrix[1];\n"
    "   gl_Position    = ftransform();\n"
    "   position       = gl_Vertex.xy;\n"
    "}\n";

static std::string fp_program =
    "varying vec2 position;\n"
    "varying mat4 shadingTexMat;\n"
    "\n"
    "uniform sampler2D grabTexture;\n"
    "uniform sampler3D shadingTexture;\n"
    "\n"
    "uniform mat4      colorMatrix;\n"
    "uniform float     gamma;\n"
    "uniform int       shadingWidth;\n"
    "uniform int       shadingHeight;\n"
    "uniform int       shadingDepth;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "   // read color from grab texture\n"
    "   vec4 color=texture2D(grabTexture,gl_TexCoord[0].xy);\n"
    "   vec2 pos;\n"
    "\n"
    "   // clamp to 0-1\n"
    "   color.rgb = clamp(color.rgb,0.0,1.0);\n"
    "\n"
    "   // make linear\n"
    "   color.r = pow(color.r,gamma);\n"
    "   color.g = pow(color.g,gamma);\n"
    "   color.b = pow(color.b,gamma);\n"
    "\n"
    "   // color matrix transformation\n"
    "   color *= colorMatrix;\n"
    "\n"
    "   // Scale color from the center of the first texel to the center of\n"
    "   // the last texel\n"
    "   float shadingScale  = (float(shadingDepth)-1.0)/float(shadingDepth);\n"
    "   float shadingOffset = (1.0 - shadingScale) / 2.0;\n"
    "   color.rgb *= shadingScale;\n"
    "   color.rgb += vec3(shadingOffset);\n"
    "\n"
    "   shadingScale  = (float(shadingWidth)-1.0)/float(shadingWidth);\n"
    "   shadingOffset = (1.0 - shadingScale) / 2.0;\n"
    "   pos.x  = position.x * shadingScale;\n"
    "   pos.x +=              shadingOffset;\n"
    "\n"
    "   shadingScale  = (float(shadingHeight)-1.0)/float(shadingHeight);\n"
    "   shadingOffset = (1.0 - shadingScale) / 2.0;\n"
    "   pos.y  = position.y * shadingScale;\n"
    "   pos.y +=              shadingOffset;\n"
    "\n"
    "   vec4 lutCoordR = vec4(pos,color.r,1.0);\n"
    "   lutCoordR = shadingTexMat * lutCoordR;\n"
    "   vec4 lutCoordG = vec4(pos,color.g,1.0);\n"
    "   lutCoordG = shadingTexMat * lutCoordG;\n"
    "   vec4 lutCoordB = vec4(pos,color.b,1.0);\n"
    "   lutCoordB = shadingTexMat * lutCoordB;\n"
    "\n"   
    "   // shading\n"
    "   color.r = texture3D(shadingTexture,lutCoordR.rgb).r;\n"
    "   color.g = texture3D(shadingTexture,lutCoordG.rgb).g;\n"
    "   color.b = texture3D(shadingTexture,lutCoordB.rgb).b;\n"
    "\n"
    "   gl_FragColor = color;\n"
    "}\n";

// Documentation for this class is emitted in the
// OSGCalibrationPatternFilterBase.cpp file.
// To modify it, please change the .fcd file (OSGCalibrationPatternFilter.fcd)
// and regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CalibrationPatternFilter::initMethod(InitPhase ePhase)
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

CalibrationPatternFilter::CalibrationPatternFilter(void) :
    Inherited()
{
}

CalibrationPatternFilter::CalibrationPatternFilter(
    const CalibrationPatternFilter &source) :

    Inherited(source)
{
}

CalibrationPatternFilter::~CalibrationPatternFilter(void)
{
}

void CalibrationPatternFilter::onCreate(const CalibrationPatternFilter *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;
}

/*----------------------------- class specific ----------------------------*/

void CalibrationPatternFilter::changed(ConstFieldMaskArg whichField, 
                                       UInt32            origin,
                                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CalibrationPatternFilter::dump(      UInt32    ,
                                    const BitVector ) const
{
    SLOG << "Dump CalibrationPatternFilter NI" << std::endl;
}

void CalibrationPatternFilter::process(DisplayFilterStageData *pData,
                                       DrawEnv                *pEnv)
{
}


OSG_END_NAMESPACE
