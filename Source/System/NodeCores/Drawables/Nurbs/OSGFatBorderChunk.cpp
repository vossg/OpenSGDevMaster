/*---------------------------------------------------------------------------*\
*                           OpenSG NURBS Library                            *
*                                                                           *
*                                                                           *
* Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
*                                                                           *
*                         http://cg.cs.uni-bonn.de/                         *
*                                                                           *
* contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEMYEXTENSIONLIB

#include "OSGConfig.h"

#include "OSGFatBorderChunk.h"

OSG_BEGIN_NAMESPACE

namespace
{

// vertex programs
const char* vertexProgStandard =
    "!!ARBvp1.0\n"

    "PARAM  mvp[]   = { state.matrix.mvp };\n"
    "PARAM  mv[]    = { state.matrix.modelview[0] };\n"
    "PARAM  m_one   = { -1.0, -1.0, -1.0, 0.0 };\n"
    "PARAM  small   = { 0.00001, 0.00001, 0.00001, 0.0 };\n"
    "TEMP   temp, temp2, temp3;\n"

//  ###########################################################
//  # preserve texture coordinates
//  ###########################################################

    "MOV        result.texcoord[0], vertex.texcoord[1];\n"
//  # just for debugging
//  "MOV        result.color, vertex.texcoord[1];\n"

//  ###########################################################
//  # compute per vertex lighting (only one lightsource)
//  # if normal maps are used, this could be switched off
//  ###########################################################

    "DP3        temp2.x, mv[0], vertex.normal;\n"
    "DP3        temp2.y, mv[1], vertex.normal;\n"
    "DP3        temp2.z, mv[2], vertex.normal;\n"
    "DP3        temp, temp2, temp2;\n"
    "RSQ        temp, temp.x;\n"
    "MUL        temp2, temp, temp2;\n"

    "DP3        temp.x, state.light[0].position, temp2;\n"
    "DP3        temp.y, state.light[0].half, temp2;\n"
    "MOV        temp.w, state.material.shininess.x;\n"
    "LIT        temp, temp;\n"
    "MAD        temp3, temp.y, state.lightprod[0].front.diffuse, state.lightprod[0].front.ambient;\n"
    "ADD        temp3, temp3, state.material.emission;\n"
    "MAD        temp3, temp.z, state.lightprod[0].front.specular, temp3;\n"

//  # double sided lighting
    "MUL        temp2, temp2, m_one;\n"
    "DP3        temp.x, state.light[0].position, temp2;\n"
    "DP3        temp.y, state.light[0].half, temp2;\n"
    "MOV        temp.w, state.material.shininess.x;\n"
    "LIT        temp, temp;\n"
    "MAD        temp3, temp.y, state.lightprod[0].back.diffuse, temp3;\n"
    "MAD        result.color, temp.z, state.lightprod[0].back.specular, temp3;\n"

//  ###########################################################
//  # compute view direction
//  ###########################################################

    "MUL        temp2, m_one, mv[2];\n"
    "DP3        temp, temp2, temp2;\n"
    "RSQ        temp, temp.x;\n"
    "MUL        temp2, temp, temp2;\n"

//  ###########################################################
//  # compute movement based on texture coordinate 1
//  # squared length of texcoord should be half width of fat border
//  ###########################################################

//  # calculate direction in sceen plane
    "XPD        temp, temp2, vertex.texcoord[0];\n"
    "DP3        temp3, temp, temp;\n"
    "ADD        temp3, temp3, small;\n"
    "RSQ        temp3, temp3.x;\n"
    "MUL    temp, temp3, temp;\n"
//  # calculate factor from texture coordinate squarelength
    "DP3        temp3, vertex.texcoord[0], vertex.texcoord[0];\n"
    "MUL        temp3, {1,1,1,0}, temp3.x;\n"
//  # apply movement
    "MAD        temp, temp, temp3, vertex.position;\n"
    "MAD        temp, temp2, temp3, temp;\n"


//  ###########################################################
//  # transform and project vertex
//  ###########################################################

    "DP4        result.position.x, mvp[0], temp;\n"
    "DP4        result.position.y, mvp[1], temp;\n"
    "DP4        result.position.z, mvp[2], temp;\n"
    "DP4        result.position.w, mvp[3], temp;\n"

    "END\n";

const char* vertexProgFBasedLight =
    "!!ARBvp1.0\n"

    "PARAM  mvp[]   = { state.matrix.mvp };\n"
    "PARAM  mv[]    = { state.matrix.modelview[0] };\n"
    "PARAM  m_one   = { -1.0, -1.0, -1.0, 0.0 };\n"
    "PARAM  small   = { 0.00001, 0.00001, 0.00001, 0.0 };\n"
    "TEMP   temp, temp2, temp3;\n"

//  ###########################################################
//  # preserve texture coordinates and store normal for fragment program
//  ###########################################################

    "MOV        result.texcoord[1], vertex.texcoord[1];\n"
    "MOV        result.texcoord[0], vertex.normal;\n"

//  ###########################################################
//  # compute view direction
//  ###########################################################

    "MUL        temp2, m_one, mv[2];\n"
    "DP3        temp, temp2, temp2;\n"
    "RSQ        temp, temp.x;\n"
    "MUL        temp2, temp, temp2;\n"

//  ###########################################################
//  # compute movement based on texture coordinate 1
//  # squared length of texcoord should be half width of fat border
//  ###########################################################

//  # calculate direction in sceen plane
    "XPD        temp, temp2, vertex.texcoord[0];\n"
    "DP3        temp3, temp, temp;\n"
    "ADD        temp3, temp3, small;\n"
    "RSQ        temp3, temp3.x;\n"
    "MUL        temp, temp3, temp;\n"
//  # calculate factor from texture coordinate squarelength
    "DP3        temp3, vertex.texcoord[0], vertex.texcoord[0];\n"
    "MUL        temp3, {1,1,1,0}, temp3.x;\n"
//  # apply movement
    "MAD        temp, temp, temp3, vertex.position;\n"
    "MAD        temp, temp2, temp3, temp;\n"


//  ###########################################################
//  # transform and project vertex
//  ###########################################################

    "DP4        result.position.x, mvp[0], temp;\n"
    "DP4        result.position.y, mvp[1], temp;\n"
    "DP4        result.position.z, mvp[2], temp;\n"
    "DP4        result.position.w, mvp[3], temp;\n"

//  # Just for testing the fragment shader's presence
//  "MOV     result.color, {1,0,0,0};\n"

    "END\n";

} // namespace

/*! \class OSG::FatBorderChunk
*/

/***************************************************************************\
*                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/

void FatBorderChunk::initMethod(InitPhase ePhase)
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

FatBorderChunk::FatBorderChunk(void) :
    Inherited()
{
}

FatBorderChunk::FatBorderChunk(const FatBorderChunk &source) :
    Inherited(source)
{
}


void FatBorderChunk::onCreate(const FatBorderChunk *)
{
    if(GlobalSystemState == Startup)
        return;

    Inherited::onCreate(NULL);
    activateWithStandardLighting();
}

FatBorderChunk::~FatBorderChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FatBorderChunk::changed(ConstFieldMaskArg whichField,
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FatBorderChunk::dump(      UInt32    , 
                        const BitVector ) const
{
    SLOG << "Dump FatBorderChunk NI" << std::endl;
}

void FatBorderChunk::activateWithStandardLighting(void)
{
    setProgram( vertexProgStandard );
}

void FatBorderChunk::activateWithFragmentBasedLighting(void)
{
    setProgram( vertexProgFBasedLight );
}

OSG_END_NAMESPACE
