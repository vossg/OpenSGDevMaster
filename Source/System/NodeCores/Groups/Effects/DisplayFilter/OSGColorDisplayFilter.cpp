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

#include "OSGColorDisplayFilter.h"
#include "OSGDisplayFilterStageData.h"
#include "OSGDrawEnv.h"
#include "OSGTextureObjChunk.h"
#include "OSGImage.h"
#include "OSGSimpleSHLChunk.h"
#include "OSGChunkMaterial.h"

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
// OSGColorDisplayFilterBase.cpp file.
// To modify it, please change the .fcd file (OSGColorDisplayFilter.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ColorDisplayFilter::initMethod(InitPhase ePhase)
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

ColorDisplayFilter::ColorDisplayFilter(void) :
    Inherited()
{
}

ColorDisplayFilter::ColorDisplayFilter(const ColorDisplayFilter &source) :
    Inherited(source)
{
}

ColorDisplayFilter::~ColorDisplayFilter(void)
{
}

void ColorDisplayFilter::onCreate(const ColorDisplayFilter *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    SimpleSHLChunkUnrecPtr pShader = 
        SimpleSHLChunk::createLocal(FCLocal::Cluster);
            
    pShader->setVertexProgram  (vp_program         );
    pShader->setFragmentProgram(fp_program         );
    pShader->addUniformVariable("grabTexture",    0);
    pShader->addUniformVariable("shadingTexture", 1);

    this->setFilterShader(pShader);
}

/*----------------------------- class specific ----------------------------*/

void ColorDisplayFilter::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & (ColorTableWidthFieldMask  |
                                ColorTableHeightFieldMask |
                                ColorTableDepthFieldMask  |
                                ColorTableFieldMask       )))
    {
        UInt32 c;
        std::vector<UChar8> vImageData;

        UInt32 uiWidth  = getColorTableWidth ();
        UInt32 uiHeight = getColorTableHeight();
        UInt32 uiDepth  = getColorTableDepth ();

        UInt32 uiSize = (uiWidth * uiHeight * uiDepth);

        if(uiSize != getMFColorTable()->size() || uiDepth < 2)
        {
            // create default linear table
            //FWARNING(("Wrong shading table size\n"));

            uiWidth = uiHeight = 1;

            uiDepth = 2;

            vImageData.push_back(0);
            vImageData.push_back(0);
            vImageData.push_back(0);

            vImageData.push_back(255);
            vImageData.push_back(255);
            vImageData.push_back(255);
        } 
        else
        {
            const MFColor3f &vColors = *(this->getMFColorTable());

            vImageData.resize(uiSize * 3);

            for(c = 0; c < uiSize ; ++c)
            {
                vImageData[c * 3 + 0] = UChar8(vColors[c][0] * 255);
                vImageData[c * 3 + 1] = UChar8(vColors[c][1] * 255);
                vImageData[c * 3 + 2] = UChar8(vColors[c][2] * 255);
            }
        }

        Image *pImg = this->getTableImage();

        if(pImg == NULL)
        {
            // Make Cluster Local
            ImageUnrecPtr pImage = Image::createLocal(FCLocal::Cluster);

            pImg = pImage;

            this->setTableImage(pImage);
        }

        pImg->set( Image::OSG_RGB_PF,
                   uiWidth, uiHeight, uiDepth,
                   1, 1, 0,
                  &vImageData[0]);

        
        SimpleSHLChunk *pShader = this->getFilterShader();

        if(pShader != NULL)
        {
            pShader->addUniformVariable("shadingWidth",  Int32(uiWidth));
            pShader->addUniformVariable("shadingHeight", Int32(uiHeight));
            pShader->addUniformVariable("shadingDepth",  Int32(uiDepth));
        }
    }
  
    if(0x0000 != (whichField & (MatrixFieldMask)))
    {
        SimpleSHLChunk *pShader = this->getFilterShader();

        if(pShader != NULL)
        {
            pShader->addUniformVariable("colorMatrix", getMatrix());
        }
    }

    if(0x0000 != (whichField & (GammaFieldMask)))
    {
        SimpleSHLChunk *pShader = this->getFilterShader();

        if(pShader != NULL)
        {
            pShader->addUniformVariable("gamma", getGamma());
        }
    }
}

void ColorDisplayFilter::dump(      UInt32    ,
                              const BitVector ) const
{
    SLOG << "Dump ColorDisplayFilter NI" << std::endl;
}

void ColorDisplayFilter::process(DisplayFilterStageData *pData)
{
    SimpleSHLChunk *pShader = pData->getColorFilterShader();

    if(pShader == NULL || this->getFilterShader() != pShader)
    {
        pShader = this->getFilterShader();

        OSG_ASSERT(pShader != NULL);
        
        ChunkMaterial *pCMat = pData->getBaseMaterial();

        OSG_ASSERT(pCMat != NULL);

        pCMat->addChunk(pShader);

        commitChanges();

        pData->setColorFilterShader(pShader);
    }



    TextureObjChunk *pColTex = pData->getColorFilterTexture();

    if(pData->getInitColTableFrom() != this)
    {
        if(pColTex == NULL)
        {
            TextureObjChunkUnrecPtr pTex = TextureObjChunk::createLocal();

            pTex->setMinFilter(GL_LINEAR            );
            pTex->setMagFilter(GL_LINEAR            );
            pTex->setWrapS    (GL_CLAMP_TO_EDGE     );
            pTex->setWrapT    (GL_CLAMP_TO_EDGE     );
            pTex->setWrapR    (GL_CLAMP_TO_EDGE     );

            pData->setColorFilterTexture(pTex);

            ChunkMaterial *pCMat = pData->getBaseMaterial();
            
            OSG_ASSERT(pCMat != NULL);
            
            pCMat->addChunk(pTex, 1);

            pColTex = pTex;
        }

        pData->setInitColTableFrom(this);

        pColTex->setImage(this->getTableImage());

        commitChanges();
    }

    OSG_ASSERT(pShader != NULL);
    OSG_ASSERT(pColTex != NULL);

    pShader->setIgnore(false);
    pColTex->setIgnore(false);
}

void ColorDisplayFilter::deactivate(DisplayFilterStageData *pData)
{
    SimpleSHLChunk  *pShader = pData->getColorFilterShader ();
    TextureObjChunk *pTex    = pData->getColorFilterTexture();

    if(pShader != NULL)
        pShader->setIgnore(true);

    if(pTex != NULL)
        pTex->setIgnore(true);
}

OSG_END_NAMESPACE
