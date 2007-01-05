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

#include <OSGConfig.h>

#include "OSGShaderChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShaderChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderChunk::initMethod(InitPhase ePhase)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderChunk::ShaderChunk(void) :
    Inherited()
{
}

ShaderChunk::ShaderChunk(const ShaderChunk &source) :
    Inherited(source)
{
}

ShaderChunk::~ShaderChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderChunk::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ShaderChunk::dump(      UInt32    , 
                       const BitVector ) const
{
    SLOG << "Dump ShaderChunk NI" << std::endl;
}

/*---------------------------------- Access -------------------------------*/

/*! Read the program string from the given file
*/
bool ShaderChunk::readVertexProgram(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return readVertexProgram(s);
    }
    else
    {
        FWARNING(("ShaderChunk::readVertexProgram: couldn't open '%s' "
                  "for reading!\n", file));

        return false;
    }
}

/*! Read the program string from the given stream
*/
bool ShaderChunk::readVertexProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    editVertexProgram().erase();    

    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("SHLChunk::readVertexProgram: stream is not good!\n"));
        return false;
    }
    
    do
    {
        stream.read(buf, BUFSIZE);
        editVertexProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return true;
}

/*! Read the program string from the given file
*/

bool ShaderChunk::readFragmentProgram(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return readFragmentProgram(s);
    }
    else
    {
        FWARNING(("ShaderChunk::readFragmentProgram: couldn't open '%s' "
                  "for reading!\n",  file));

        return false;
    }
}

/*! Read the program string from the given stream
*/
bool ShaderChunk::readFragmentProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    editFragmentProgram().erase();    

    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("SHLChunk::readFragmentProgram: stream is not good!\n"));
        return false;
    }
    
    do
    {
        stream.read(buf, BUFSIZE);
        editFragmentProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return true;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGSHADERCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

