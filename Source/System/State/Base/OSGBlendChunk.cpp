/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"

#include <OSGGL.h>

#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include "OSGBlendChunk.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::BlendChunk
    \ingroup GrpSystemState

  See \ref PageSystemBlendChunk for a description. 
  
  This chunk wraps glBlendFunc() (OSG::BlendChunk::_sfSrcFactor,
  OSG::BlendChunk::_sfDestFactor), glBlendEquation() or glBlendEquationEXT()
  (whichever is supported) (OSG::BlendChunk::_sfEquation), glBlendColor() 
  (OSG::BlendChunk::_sfColor) and glAlphaFunc() (OSG::BlendChunk::_sfAlphaFunc,
  OSG::BlendChunk::_sfAlphaValue) including glEnable(GL_ALPHA_TEST).
  
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass BlendChunk::_class("Blend");

UInt32 BlendChunk::_extBlend             = Window::invalidExtensionID;
UInt32 BlendChunk::_extImaging           = Window::invalidExtensionID;
UInt32 BlendChunk::_extBlendSubtract     = Window::invalidExtensionID;
UInt32 BlendChunk::_extBlendMinMax       = Window::invalidExtensionID;
UInt32 BlendChunk::_extBlendLogicOp      = Window::invalidExtensionID;
UInt32 BlendChunk::_extBlendFuncSeparate = Window::invalidExtensionID;

UInt32 BlendChunk::_funcBlendColor           = Window::invalidFunctionID;
UInt32 BlendChunk::_funcBlendEquation        = Window::invalidFunctionID;
UInt32 BlendChunk::_funcBlendEquationExt     = Window::invalidFunctionID;
UInt32 BlendChunk::_funcBlendFuncSeparateExt = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BlendChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extBlend             =
            Window::registerExtension("GL_EXT_blend_color");
        _extImaging           =
            Window::registerExtension("GL_ARB_imaging");
        _extBlendSubtract     =
            Window::registerExtension("GL_EXT_blend_subtract");
        _extBlendMinMax       =
            Window::registerExtension("GL_EXT_blend_minmax");
        _extBlendLogicOp      =
            Window::registerExtension("GL_EXT_blend_logic_op");
        _extBlendFuncSeparate      =
            Window::registerExtension("GL_EXT_blend_func_separate");

        _funcBlendColor       =
            Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBlendColorEXT",
                                      _extBlend);
        _funcBlendEquation    =
            Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBlendEquation",
                                      _extImaging);
        _funcBlendEquationExt =
           Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBlendEquationEXT",
                                     _extBlendLogicOp);

        _funcBlendFuncSeparateExt = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glBlendFuncSeparateEXT", 
            _extBlendFuncSeparate);
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

BlendChunk::BlendChunk(void) :
    Inherited()
{
}

BlendChunk::BlendChunk(const BlendChunk &source) :
    Inherited(source)
{
}

BlendChunk::~BlendChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *BlendChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void BlendChunk::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void BlendChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                      const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump BlendChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

#if OSG_GL_ES_VERSION == 100
void BlendChunk::activate(DrawEnv *pEnv, UInt32)
{
}
void BlendChunk::changeFrom(DrawEnv    *pEnv, 
                            StateChunk *old_chunk, 
                            UInt32               )
{
}

void BlendChunk::deactivate(DrawEnv *pEnv, UInt32 )
{
}
#else
void BlendChunk::activate(DrawEnv *pEnv, UInt32)
{
    GLenum src   = _sfSrcFactor.getValue();
    GLenum dest  = _sfDestFactor.getValue();
    GLenum asrc  = _sfAlphaSrcFactor.getValue();
    GLenum adest = _sfAlphaDestFactor.getValue();

    if((src   != GL_ONE        || dest  != GL_ZERO) ||
       (asrc  != OSG_GL_UNUSED && asrc  != GL_ONE ) || 
       (adest != OSG_GL_UNUSED && adest != GL_ZERO)  )
    {
        if(asrc != OSG_GL_UNUSED || adest != OSG_GL_UNUSED)
        {
            if(asrc == OSG_GL_UNUSED || adest == OSG_GL_UNUSED)
            {
                FWARNING(("BlendChunk::activate: only one of alpha src and"
                          " alpha dest is set. Ignored.\n"));
                
                glBlendFunc(src, dest);
            }
            else if(pEnv->getWindow()->hasExtension(_extBlendFuncSeparate))
            {
                // get "glBlendFuncSeparate" function pointer
                void (OSG_APIENTRY *blendfuncsep)(GLenum,
                                                  GLenum,
                                                  GLenum,
                                                  GLenum) =
                    
                    (void (OSG_APIENTRY*)(GLenum,
                                          GLenum,
                                          GLenum,
                                          GLenum))  
                    pEnv->getWindow()->getFunction(
                        _funcBlendFuncSeparateExt);

                blendfuncsep(src, dest, asrc, adest);
            }
            else
            {
                FWARNING(("BlendChunk::activate: Window %p doesn't "
                          "support EXT_blend_func_separate, ignored.\n"));

                glBlendFunc(src, dest);
            }
        }
        else
        {
            glBlendFunc(src, dest);
        }

#if GL_EXT_blend_color
        // This is not nice, but efficient
        // As the OpenGL constants are fixed it should be safe
        if((src  >= GL_CONSTANT_COLOR_EXT && 
            src  <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) ||
           (dest >= GL_CONSTANT_COLOR_EXT && 
            dest <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) ||
           (asrc  >= GL_CONSTANT_COLOR_EXT && 
            asrc  <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT) ||
           (adest >= GL_CONSTANT_COLOR_EXT && 
            adest <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT) )
        {
            if(pEnv->getWindow()->hasExtension(_extBlend))
            {
                // get "glBlendColorEXT" function pointer
                void (OSG_APIENTRY*blendcolor)(GLclampf red,
                                               GLclampf green,
                                               GLclampf blue,
                                               GLclampf alpha ) =
                    (void (OSG_APIENTRY*)(GLclampf red,
                                          GLclampf green,
                                          GLclampf blue,
                                          GLclampf alpha))
                    pEnv->getWindow()->getFunction(_funcBlendColor);

                 blendcolor(_sfColor.getValue().red(),
                            _sfColor.getValue().green(),
                            _sfColor.getValue().blue(),
                            _sfColor.getValue().alpha());
            }
        }
#endif
        glEnable(GL_BLEND);
    }

    if(_sfEquation.getValue() != GL_NONE)
    {
#if defined(GL_ARB_imaging)
        if(pEnv->getWindow()->hasExtension(_extImaging))
        {
            // get "glBlendEquation" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                pEnv->getWindow()->getFunction(_funcBlendEquation);

             blendeq(_sfEquation.getValue());
        }

#elif defined(GL_EXT_blend_subtract) || defined(GL_EXT_blend_minmax) || \
    defined(GL_EXT_blend_logic_op)
        if(pEnv->getWindow()->hasExtension(_extBlendSubtract) ||
           pEnv->getWindow()->hasExtension(_extBlendMinMax) ||
           pEnv->getWindow()->hasExtension(_extBlendLogicOp))
        {
            // get "glBlendEquationEXT" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                pEnv->getWindow()->getFunction(_funcBlendEquationExt);

             blendeq(_sfEquation.getValue());
        }
#endif
    }
    
    if(_sfAlphaFunc.getValue() != GL_NONE)
    {
        glAlphaFunc(_sfAlphaFunc.getValue(), _sfAlphaValue.getValue());
        glEnable(GL_ALPHA_TEST);
    }
}

void BlendChunk::changeFrom(DrawEnv    *pEnv, 
                            StateChunk *old_chunk, 
                            UInt32               )
{
    BlendChunk *old = dynamic_cast<BlendChunk *>(old_chunk);

    GLenum src    = _sfSrcFactor.getValue();
    GLenum dest   = _sfDestFactor.getValue();
    GLenum osrc   =  old->_sfSrcFactor.getValue();
    GLenum odest  =  old->_sfDestFactor.getValue();
    GLenum asrc   = _sfAlphaSrcFactor.getValue();
    GLenum adest  = _sfAlphaDestFactor.getValue();
    GLenum oasrc  =  old->_sfAlphaSrcFactor.getValue();
    GLenum oadest =  old->_sfAlphaDestFactor.getValue();

    if((src   != GL_ONE        || dest  != GL_ZERO) ||
       (asrc  != OSG_GL_UNUSED && asrc  != GL_ONE ) || 
       (adest != OSG_GL_UNUSED && adest != GL_ZERO)  )
    {
        if(asrc != OSG_GL_UNUSED || adest != OSG_GL_UNUSED)
        {
            if(asrc == OSG_GL_UNUSED || adest == OSG_GL_UNUSED)
            {
                FWARNING(("BlendChunk::changeFrom: only one of alpha src and"
                          " alpha dest is set. Ignored.\n"));

                glBlendFunc(src, dest);
            }
            else if(pEnv->getWindow()->hasExtension(_extBlendFuncSeparate))
            {
                if(osrc  != src  || odest  != dest ||
                   oasrc != asrc || oadest != adest )
                {
                    // get "glBlendFuncSeparate" function pointer
                    void (OSG_APIENTRY* blendfuncsep)(GLenum,GLenum,
                                                      GLenum,GLenum) =
                        (void (OSG_APIENTRY*)(GLenum,GLenum,GLenum,GLenum))
                        pEnv->getWindow()->getFunction(
                            _funcBlendFuncSeparateExt);

                    blendfuncsep(src, dest, asrc, adest);
                }
            }
            else
            {
                FWARNING(("BlendChunk::changeFrom: Window %p doesn't "
                          "support EXT_blend_func_separate, ignored.\n"));

                glBlendFunc(src, dest);
            }
        }
        else if(osrc != src || odest != dest)
        {
            glBlendFunc(src, dest);
        }

#if GL_EXT_blend_color
        // This is not nice, but efficient
        // As the OpenGL constants are fixed it should be safe
        if((src  >= GL_CONSTANT_COLOR_EXT && 
            src  <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) ||
           (dest >= GL_CONSTANT_COLOR_EXT && 
            dest <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) ||
           (asrc  >= GL_CONSTANT_COLOR_EXT && 
            asrc  <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) ||
           (adest >= GL_CONSTANT_COLOR_EXT && 
            adest <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) )
        {
            if ( pEnv->getWindow()->hasExtension(_extBlend ))
            {
                // get "glBlendColorEXT" function pointer
                void (OSG_APIENTRY*blendcolor)(GLclampf red,
                                               GLclampf green,
                                               GLclampf blue,
                                               GLclampf alpha ) =
                    (void (OSG_APIENTRY*)(GLclampf red,
                                          GLclampf green,
                                          GLclampf blue,
                                          GLclampf alpha))
                    pEnv->getWindow()->getFunction( _funcBlendColor );

                blendcolor(_sfColor.getValue().red(),
                           _sfColor.getValue().green(),
                           _sfColor.getValue().blue(),
                           _sfColor.getValue().alpha());
            }
        }
#endif
        if(osrc == GL_ONE && odest == GL_ZERO)
            glEnable(GL_BLEND);
    }
    else
    {
        if((osrc   != GL_ONE        || odest  != GL_ZERO) ||
           (oasrc  != OSG_GL_UNUSED && oasrc  != GL_ONE ) || 
           (oadest != OSG_GL_UNUSED && oadest != GL_ZERO) )
        {
            glDisable(GL_BLEND);
        }
    }

    if(_sfEquation.getValue() != old->_sfEquation.getValue())
    {
#if defined(GL_ARB_imaging)
        if(pEnv->getWindow()->hasExtension(_extImaging))
        {
            // get "glBlendEquation" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                pEnv->getWindow()->getFunction(_funcBlendEquation);

             blendeq(_sfEquation.getValue());
        }

#elif defined(GL_EXT_blend_subtract) || defined(GL_EXT_blend_minmax) || \
    defined(GL_EXT_blend_logic_op)
        if(pEnv->getWindow()->hasExtension(_extBlendSubtract) ||
           pEnv->getWindow()->hasExtension(_extBlendMinMax) ||
           pEnv->getWindow()->hasExtension(_extBlendLogicOp))
        {
            // get "glBlendEquationEXT" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                pEnv->getWindow()->getFunction(_funcBlendEquationExt);

             blendeq(_sfEquation.getValue());
        }
#endif
    }
    
    if(_sfAlphaFunc.getValue() != GL_NONE)
    {
        if(old->_sfAlphaFunc.getValue()  != _sfAlphaFunc.getValue() ||
           old->_sfAlphaValue.getValue() != _sfAlphaValue.getValue())
            glAlphaFunc(_sfAlphaFunc.getValue(), _sfAlphaValue.getValue());
        
        if(old->_sfAlphaFunc.getValue() == GL_NONE)
            glEnable(GL_ALPHA_TEST);
    }
    else
    {
        if(old->_sfAlphaFunc.getValue() != GL_NONE)
            glDisable(GL_ALPHA_TEST);        
    }
    
}

void BlendChunk::deactivate(DrawEnv *pEnv, UInt32 )
{
    GLenum src    = _sfSrcFactor.getValue();
    GLenum dest   = _sfDestFactor.getValue();
    GLenum asrc   = _sfAlphaSrcFactor.getValue();
    GLenum adest  = _sfAlphaDestFactor.getValue();

    if((src   != GL_ONE        || dest  != GL_ZERO) ||
       (asrc  != OSG_GL_UNUSED && asrc  != GL_ONE ) || 
       (adest != OSG_GL_UNUSED && adest != GL_ZERO)   )
    {
        glDisable(GL_BLEND);
    }

    if(_sfEquation.getValue() != GL_NONE)
    {
#if defined(GL_ARB_imaging)
        if(pEnv->getWindow()->hasExtension(_extImaging))
        {
            // get "glBlendEquation" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                pEnv->getWindow()->getFunction(_funcBlendEquation);

             blendeq(GL_FUNC_ADD);
        }

#elif defined(GL_EXT_blend_subtract) || defined(GL_EXT_blend_minmax) || \
    defined(GL_EXT_blend_logic_op)
        if(pEnv->getWindow()->hasExtension(_extBlendSubtract) ||
           pEnv->getWindow()->hasExtension(_extBlendMinMax) ||
           pEnv->getWindow()->hasExtension(_extBlendLogicOp))
        {
            // get "glBlendEquationEXT" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                pEnv->getWindow()->getFunction(_funcBlendEquationExt);

             blendeq(GL_FUNC_ADD_EXT);
        }
#endif
    }
    
    if(_sfAlphaFunc.getValue() != GL_NONE)
    {
        glDisable(GL_ALPHA_TEST);
    }
}
#endif

/*-------------------------- Comparison -----------------------------------*/

bool BlendChunk::isTransparent(void) const
{
    return getDestFactor() != GL_ZERO;
}

Real32 BlendChunk::switchCost(StateChunk *)
{
    return 0;
}

bool BlendChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool BlendChunk::operator == (const StateChunk &other) const
{
    BlendChunk const *tother = dynamic_cast<BlendChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getSrcFactor()  != tother->getSrcFactor()  ||
       getDestFactor() != tother->getDestFactor() ||
       getEquation()   != tother->getEquation()   ||
       getColor()      != tother->getColor()      ||
       getAlphaFunc()  != tother->getAlphaFunc()  ||
       getAlphaValue() != tother->getAlphaValue()   )
        return false;

    return true;
}

bool BlendChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGBLENDCHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBLENDCHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBLENDCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


