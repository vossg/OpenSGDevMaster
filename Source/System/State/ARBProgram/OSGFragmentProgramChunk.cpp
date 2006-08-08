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

#include <stdlib.h>
#include <stdio.h>

#include <boost/bind.hpp>

#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLEXT.h>

#include "OSGWindow.h"

#include "OSGFragmentProgramChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::FragmentProgramChunk
    \ingroup GrpSystemState

  See \ref PageSystemFragmentProgramChunk for a description. The 
  FragmentProgramChunk implements Fragment Programs as specified in the 
  GL_ARB_fragment_program extension.
  It is just a special version of the osg::ProgramChunk, which contains the
  whole public interface.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass FragmentProgramChunk::_class("FragmentProgram");

UInt32 FragmentProgramChunk::_arbFragmentProgram = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FragmentProgramChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _arbFragmentProgram = 
            Window::registerExtension("GL_ARB_fragment_program");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FragmentProgramChunk::FragmentProgramChunk(void) :
    Inherited()
{
}

FragmentProgramChunk::FragmentProgramChunk(
    const FragmentProgramChunk &source) :

    Inherited(source)
{
}

FragmentProgramChunk::~FragmentProgramChunk(void)
{
}

/*----------------------------- onCreate --------------------------------*/

void FragmentProgramChunk::onCreate(const FragmentProgramChunk *chunk)
{
    Inherited::onCreate(chunk); 

    if(GlobalSystemState == Startup)
        return;

    FragmentProgramChunkPtr tmpPtr = 
        Inherited::constructPtr<FragmentProgramChunk>(this);
        
    setGLId(Window::registerGLObject(
                boost::bind(&FragmentProgramChunk::handleGL, 
                            tmpPtr, _1, _2),
                1));

}


/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *FragmentProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void FragmentProgramChunk::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FragmentProgramChunk::dump(      UInt32    , 
                                const BitVector ) const
{
    SLOG << "Dump FragmentProgramChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

UInt32 FragmentProgramChunk::getExtension(void) const
{
    return _arbFragmentProgram;
}

GLenum FragmentProgramChunk::getTarget(void) const
{
    return GL_FRAGMENT_PROGRAM_ARB;
}

const char *FragmentProgramChunk::getTargetName(void) const
{
    return "Fragment Program";
}

void FragmentProgramChunk::handleGL(DrawEnv *pEnv, UInt32 idstatus)
{
    Inherited::handleGL(pEnv, 
                        idstatus, 
                        GL_FRAGMENT_PROGRAM_ARB, 
                        _arbFragmentProgram);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGFRAGMENTPROGRAMCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFRAGMENTPROGRAMCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = 
                                    OSGFRAGMENTPROGRAMCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

