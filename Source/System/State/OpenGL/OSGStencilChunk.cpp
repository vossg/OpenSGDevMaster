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

#include <OSGConfig.h>

#include <OSGGL.h>

#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include "OSGStencilChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StencilChunk
  The stencil chunk handles OpenGL stencil tests by wrapping 
  glStencilFunc() and glStencilOp().
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
StateChunkClass StencilChunk::_class("Stencil");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StencilChunk::initMethod(InitPhase ePhase)
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

StencilChunk::StencilChunk(void) :
    Inherited()
{
}

StencilChunk::StencilChunk(const StencilChunk &source) :
    Inherited(source)
{
}

StencilChunk::~StencilChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

const StateChunkClass *StencilChunk::getClass(void) const
{
    return &_class;
}

void StencilChunk::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void StencilChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                        const BitVector OSG_CHECK_ARG(bvFlags ) ) const
{
    SLOG << "Dump StencilChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void StencilChunk::activate(DrawEnv *pEnv, UInt32)
{
    if (_sfStencilFunc.getValue() != GL_NONE)
    {
        glEnable(GL_STENCIL_TEST);
        
        if(_sfClearBuffer.getValue() == 1)
            glClear(GL_STENCIL_BUFFER_BIT);
        
        glStencilFunc(_sfStencilFunc   .getValue(), 
                      _sfStencilValue  .getValue(), 
                      _sfStencilMask   .getValue());
        glStencilOp  (_sfStencilOpFail .getValue(), 
                      _sfStencilOpZFail.getValue(), 
                      _sfStencilOpZPass.getValue());
    }
}

void StencilChunk::changeFrom(DrawEnv    *pEnv, 
                              StateChunk *old_chunk, 
                              UInt32               )
{
    StencilChunk *old = dynamic_cast<StencilChunk *>(old_chunk);
    
    if (_sfStencilFunc.getValue() != GL_NONE)
    {
        if ( old->_sfStencilFunc.getValue()  != _sfStencilFunc.getValue()    ||
             old->_sfStencilValue.getValue() != _sfStencilValue.getValue()   ||
             old->_sfStencilMask.getValue()  != _sfStencilMask.getValue() )
        { 
             glStencilFunc( _sfStencilFunc.getValue(), 
                            _sfStencilValue.getValue(), 
                            _sfStencilMask.getValue() );
        }
    
        if(old->_sfStencilOpFail.getValue()  != _sfStencilOpFail.getValue()  ||
           old->_sfStencilOpZFail.getValue() != _sfStencilOpZFail.getValue() ||
           old->_sfStencilOpZPass.getValue() != _sfStencilOpZPass.getValue() ) 
        {
             glStencilOp( _sfStencilOpFail.getValue(), 
                          _sfStencilOpZFail.getValue(), 
                          _sfStencilOpZPass.getValue() );
        }
        if(old->_sfStencilFunc.getValue() == GL_NONE) 
        {     
            glEnable(GL_STENCIL_TEST);
            
            /*
            if (_sfClearBuffer.getValue() == 1)
                glClear(GL_STENCIL_BUFFER_BIT);
            */
        }
    }
    else 
    {
        if(old->_sfStencilFunc.getValue() != GL_NONE) 
        {      
            /*
            if (_sfClearBuffer.getValue() == 2)
                glClear(GL_STENCIL_BUFFER_BIT);
            */
                      
            glDisable(GL_STENCIL_TEST); 
        }
    }
    
}

void StencilChunk::deactivate(DrawEnv *pEnv, UInt32 )
{
    if (_sfStencilFunc.getValue() != GL_NONE)
    {
        if(_sfClearBuffer.getValue() == 2)
            glClear(GL_STENCIL_BUFFER_BIT);
        
        glDisable(GL_STENCIL_TEST);
    }
}

/*-------------------------- Comparison -----------------------------------*/

Real32 StencilChunk::switchCost(StateChunk *)
{
    return 0;
}

bool StencilChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool StencilChunk::operator == (const StateChunk &other) const
{
    StencilChunk const *tother = dynamic_cast<StencilChunk const*>(&other);

    if (!tother)
        return false;

    if (tother == this)
        return true;

    if (getStencilFunc()    != tother->getStencilFunc()    ||
        getStencilValue()   != tother->getStencilValue()   ||
        getStencilMask()    != tother->getStencilMask()    ||
        getStencilOpFail()  != tother->getStencilOpFail()  ||
        getStencilOpZFail() != tother->getStencilOpZFail() ||
        getStencilOpZPass() != tother->getStencilOpZPass() ||
        getClearBuffer()    != tother->getClearBuffer())
    {
        return false;
    }

    return true;
}

bool StencilChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_hpp       [] = OSGSTENCILCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTENCILCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSTENCILCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

