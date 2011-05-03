/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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
#include "OSGViewport.h"
#include "OSGTextureObjChunk.h"

#include "OSGTextureBackground.h"

#include<iostream>

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTextureBackgroundBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureBackground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureBackground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
  -  private                                                                 -
  \*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextureBackground::TextureBackground(void) :
     Inherited         (   ),
    _textureCoordArray (   ),
    _vertexCoordArray  (   ),
    _indexArray        (   ),
    _hor               (0  ),
    _vert              (0  ),
    _radialDistortion  (0.f),
    _centerOfDistortion(   )
{
}

TextureBackground::TextureBackground(const TextureBackground &source) :
     Inherited         (source                    ),
    _textureCoordArray (source._textureCoordArray ),
    _vertexCoordArray  (source._vertexCoordArray  ),
    _indexArray        (source._indexArray        ),
    _hor               (source._hor               ),
    _vert              (source._vert              ),
    _radialDistortion  (source._radialDistortion  ),
    _centerOfDistortion(source._centerOfDistortion)
{
}

TextureBackground::~TextureBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/




void TextureBackground::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
 
    // all updates are handled in updateGrid()
}


void TextureBackground::updateGrid(void)
{
    bool gridChanged=( (getHor() != _hor) || 
                       (getVert() != _vert) );
                       
    if(gridChanged)
    {
        //resize grid
	    UInt32 gridCoords=(getHor()+2)*(getVert()+2);

	    _textureCoordArray.resize(gridCoords);
	    _vertexCoordArray .resize(gridCoords);
        
	    int indexArraySize=(getHor()+2)*((getVert()+1)*2);
	    _indexArray.resize(indexArraySize);
        
        _hor = getHor();
        _vert = getVert();
    }
    
    if(gridChanged || _radialDistortion   != getRadialDistortion() ||
                      _centerOfDistortion != getCenterOfDistortion() )
    {
        _radialDistortion = getRadialDistortion();
        _centerOfDistortion = getCenterOfDistortion();
        
	    // calculate grid coordinates and triangle strip indices
	    float xStep=1.0/float(getHor()+1);
	    float yStep=1.0/float(getVert()+1);
	    std::vector<Vec2f>::iterator texCoord=_textureCoordArray.begin();
	    std::vector<Vec2f>::iterator vertexCoord=_vertexCoordArray.begin();
	    std::vector<UInt32>::iterator index=_indexArray.begin();
	    UInt32 coord0(0),coord1(0);
	    GLfloat x,y;
	    Int16 xx,yy;
	    Int16 xxmax=getHor()+2,yymax=getVert()+2;
	    for(yy=0,y=0.0f;yy<yymax;yy++,y+=yStep)
	    {
	        if(yy>0)
	        {
		        coord1=yy*xxmax;
		        coord0=coord1-xxmax;
		        *index++=coord1++;
		        *index++=coord0++;
	        }
	        float dy=y-getCenterOfDistortion().y();
	        float dy2=dy*dy;
	        for(xx=0,x=0.0f;xx<xxmax;xx++,x+=xStep)
	        {
		        *texCoord++=Vec2f(x,y);
		        float dx=(x-getCenterOfDistortion().x());
		        float dx2=dx*dx;
		        float dist2=dx2+dy2;
		        float deltaX=dx*getRadialDistortion()*dist2;
		        float deltaY=dy*getRadialDistortion()*dist2;
		        *vertexCoord++=Vec2f(x+deltaX,y+deltaY);
		        if(yy>0&&xx>0)
		        {
		            *index++=coord1++;
		            *index++=coord0++;
		        }
	        }
	    }
    }
}

void TextureBackground::clear(DrawEnv  *pEnv)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    TextureBaseChunk *tex = getTexture();

    if(tex == NULL)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return;
    }

    glPushAttrib(GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | 
                 GL_LIGHTING_BIT);

    glDisable(GL_LIGHTING);

#if 1
    // original mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#else
    // for testing the grid
    glColor3f(1.0f, 1.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
    glClear(GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glDepthMask(GL_FALSE);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);

    glColor4fv(getColor().getValuesRGBA());

    tex->activate(pEnv);

    if(tex->isTransparent())
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }
    if(osgAbs(getRadialDistortion()) < TypeTraits<Real32>::getDefaultEps())
    {
	    if(getMFTexCoords()->size() < 4)
	    {
	        // set some default texture coordinates.
	        glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1.0f, 0.0f, 0.0f);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1.0f, 1.0f, 0.0f);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
	        glEnd();
	    }
	    else
	    {
	        glBegin(GL_QUADS);
            {
                glTexCoord2f(getTexCoords(0).getValues()[0],
                             getTexCoords(0).getValues()[1]);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glTexCoord2f(getTexCoords(1).getValues()[0],
                             getTexCoords(1).getValues()[1]);
                glVertex3f(1.0f, 0.0f, 0.0f);
                glTexCoord2f(getTexCoords(2).getValues()[0],
                             getTexCoords(2).getValues()[1]);
                glVertex3f(1.0f, 1.0f, 0.0f);
                glTexCoord2f(getTexCoords(3).getValues()[0],
                             getTexCoords(3).getValues()[1]);
                glVertex3f(0.0f, 1.0f, 0.0f);
            }
	        glEnd();
	    }
    }
    else // map texture to distortion grid
    {
        updateGrid();
	    Int16 xxmax=getHor()+2,yymax=getVert()+2;

	    UInt32 gridCoords=xxmax*yymax;
	    UInt32 indexArraySize=xxmax*((getVert()+1)*2);

	    if(_vertexCoordArray.size()==gridCoords &&
	       _textureCoordArray.size()==gridCoords &&
	       _indexArray.size()==indexArraySize)
	    {
	        // clear background, because possibly the distortion grid 
            // could not cover th whole window
	        glClearColor(.5f, 0.5f, 0.5f, 1.0f);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	        std::vector<UInt32>::iterator i;
	        UInt32 yMax=getVert()+1;
	        for(UInt32 y=0;y<yMax;y++)
	        {
		        glBegin(GL_TRIANGLE_STRIP);
		        std::vector<UInt32>::iterator begin=_indexArray.begin()+(y*2*xxmax);
		        std::vector<UInt32>::iterator end=begin+2*xxmax;
		        for(std::vector<UInt32>::iterator i=begin;i!=end;i++)
		        {
		            glTexCoord2fv(_textureCoordArray[*i].getValues());
		            glVertex2fv(_vertexCoordArray[*i].getValues());

		        }
		        glEnd();
	        }
	    }
    }
    if(tex->isTransparent())
    {
        glDisable(GL_BLEND);
    }

    tex->deactivate(pEnv);

    Int32 bit = getClearStencilBit();
    
    if (bit >= 0)
    {
        glClearStencil(bit);
        glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    else
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();

    glColor3f(1.0f, 1.0f, 1.0f);
#endif
}


void TextureBackground::dump(      UInt32    ,
				   const BitVector ) const
{
    SLOG << "Dump TextureBackground NI" << std::endl;
}

