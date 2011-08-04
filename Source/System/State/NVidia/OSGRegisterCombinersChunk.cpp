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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLEXT.h"
#include "OSGGLU.h"

#include "OSGDrawEnv.h"

#include "OSGRegisterCombinersChunk.h"
#include "OSGWindow.h"

#include "OSGGLFuncProtos.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGRegisterCombinersChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGRegisterCombinersChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass RegisterCombinersChunk::_class("RegisterCombiners");

UInt32 RegisterCombinersChunk::_nvRegisterCombiners  
                                            = Window::invalidExtensionID;;
UInt32 RegisterCombinersChunk::_nvRegisterCombiners2 
                                            = Window::invalidExtensionID;;

UInt32 RegisterCombinersChunk::_funcCombinerParameterfv 
                                            = Window::invalidFunctionID; 
UInt32 RegisterCombinersChunk::_funcCombinerStageParameterfv 
                                            = Window::invalidFunctionID; 
UInt32 RegisterCombinersChunk::_funcCombinerInput
                                            = Window::invalidFunctionID; 
UInt32 RegisterCombinersChunk::_funcCombinerOutput
                                            = Window::invalidFunctionID; 
UInt32 RegisterCombinersChunk::_funcFinalCombinerInput
                                            = Window::invalidFunctionID; 
                                                
// can't use GL_NONE as flag, as GL_ZERO is equal and valid
static const UInt32 unused = 0xffff;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RegisterCombinersChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _nvRegisterCombiners      = 
            Window::registerExtension("GL_NV_register_combiners"  );
        _nvRegisterCombiners2     = 
            Window::registerExtension("GL_NV_register_combiners2" );

        _funcCombinerParameterfv      = 
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCombinerParameterfvNV"     );

        _funcCombinerStageParameterfv = 
            Window::registerFunction(
                OSG_DLSYM_UNDERSCORE"glCombinerStageParameterfvNV");

        _funcCombinerInput            =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCombinerInputNV"           );

        _funcCombinerOutput           = 
            Window::registerFunction(
                OSG_DLSYM_UNDERSCORE"glCombinerOutputNV"          );

        _funcFinalCombinerInput       = 
            Window::registerFunction(
                OSG_DLSYM_UNDERSCORE"glFinalCombinerInputNV"      );
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

RegisterCombinersChunk::RegisterCombinersChunk(void) :
    Inherited()
{
}

RegisterCombinersChunk::RegisterCombinersChunk(
    const RegisterCombinersChunk &source) :
    
    Inherited(source)
{
}

RegisterCombinersChunk::~RegisterCombinersChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *RegisterCombinersChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void RegisterCombinersChunk::changed(ConstFieldMaskArg whichField, 
                                     UInt32            origin,
                                     BitVector         details)
{
    // does it make sense to put the combiner settings into a dlist?
    // if yes we would need to invalidate it here

    Inherited::changed(whichField, origin, details);
}

/*------------------------------ Output ----------------------------------*/

void RegisterCombinersChunk::dump(      UInt32    , 
                                  const BitVector ) const
{
    SLOG << "Dump RegisterCombinersChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void RegisterCombinersChunk::activate(DrawEnv *pEnv, UInt32)
{
    Window *win = pEnv->getWindow();
    
    if(! win->hasExtension(_nvRegisterCombiners))
        return;

    // setup register combiners
 
    // functions
 
    OSGGETGLFUNCBYID_EXT( glCombinerParameterfvNV,
                          osgGlCombinerParameterfvNV,
                         _funcCombinerParameterfv,
                          win);

    OSGGETGLFUNCBYID_EXT( glCombinerStageParameterfvNV,
                          osgGlCombinerStageParameterfvNV,
                         _funcCombinerStageParameterfv,
                          win);
  
    OSGGETGLFUNCBYID_EXT( glCombinerInputNV,
                          osgGlCombinerInputNV,
                         _funcCombinerInput,
                          win);

    OSGGETGLFUNCBYID_EXT( glCombinerOutputNV,
                          osgGlCombinerOutputNV,
                         _funcCombinerOutput,
                          win);

    OSGGETGLFUNCBYID_EXT( glFinalCombinerInputNV,
                          osgGlFinalCombinerInputNV,
                         _funcFinalCombinerInput,
                          win);

   
    // how many combiners do we need?
    
    Int32 ncomb;
 
    for(ncomb = OSG_NUM_COMBINERS - 1; ncomb >= 0; ncomb--)
    {
        if(getVariableArgb(ncomb * 3) != unused)
            break;
    }

    if(ncomb < 0)
    {
        // no combiner active, return
        
        glDisable(GL_REGISTER_COMBINERS_NV);
        return;
    }
    
    ncomb++;
    
    GLfloat dummy = GLfloat(ncomb);
    osgGlCombinerParameterfvNV(GL_NUM_GENERAL_COMBINERS_NV, &dummy);

    osgGlCombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, 
                               const_cast<GLfloat *>(
                                   getColor0().getValuesRGBA()));

    osgGlCombinerParameterfvNV(GL_CONSTANT_COLOR1_NV, 
                               const_cast<GLfloat *>(
                                   getColor1().getValuesRGBA()));
    
    dummy = getColorSumClamp();
    osgGlCombinerParameterfvNV(GL_COLOR_SUM_CLAMP_NV, &dummy);
    
    // setup the general combiners

    bool hasRC2 = win->hasExtension(_nvRegisterCombiners2);
     
    for(UInt16 i = 0; i < ncomb; i++)
    {
        if(getVariableArgb(i * 3) != unused)
        {
            // RGB inputs
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_A_NV,
                                 getVariableArgb(i * 3),
                                 getVariableArgb(i * 3 + 1),
                                 getVariableArgb(i * 3 + 2) );
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_B_NV,
                                 getVariableBrgb(i * 3),
                                 getVariableBrgb(i * 3 + 1),
                                 getVariableBrgb(i * 3 + 2) );
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_C_NV,
                                 getVariableCrgb(i * 3),
                                 getVariableCrgb(i * 3 + 1),
                                 getVariableCrgb(i * 3 + 2) );
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_D_NV,
                                 getVariableDrgb(i * 3),
                                 getVariableDrgb(i * 3 + 1),
                                 getVariableDrgb(i * 3 + 2) );

            // RGB output
            osgGlCombinerOutputNV(GL_COMBINER0_NV + i, GL_RGB, 
                                  getOutputABrgb    (i),
                                  getOutputCDrgb    (i),
                                  getOutputSumrgb   (i),
                                  getScalergb       (i),
                                  getBiasrgb        (i),
                                  getDotABrgb       (i),
                                  getDotCDrgb       (i),
                                  getMuxSumrgb      (i) );

        }
        else
        {
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_A_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_B_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_C_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_RGB, GL_VARIABLE_D_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB); 

            osgGlCombinerOutputNV(GL_COMBINER0_NV + i, GL_RGB, 
                                  GL_DISCARD_NV, GL_DISCARD_NV, GL_DISCARD_NV,
                                  GL_NONE, GL_NONE,
                                  GL_FALSE, GL_FALSE, GL_FALSE );   
                            
        }
        
        if(getVariableAalpha(i * 3) != unused)
        {
            // Alpha inputs
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, 
                                 GL_ALPHA, GL_VARIABLE_A_NV,
                                 getVariableAalpha(i * 3),
                                 getVariableAalpha(i * 3 + 1),
                                 getVariableAalpha(i * 3 + 2) );
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                 GL_VARIABLE_B_NV,
                                 getVariableBalpha(i * 3),
                                 getVariableBalpha(i * 3 + 1),
                                 getVariableBalpha(i * 3 + 2) );
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                 GL_VARIABLE_C_NV,
                                 getVariableCalpha(i * 3),
                                 getVariableCalpha(i * 3 + 1),
                                 getVariableCalpha(i * 3 + 2) );
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                 GL_VARIABLE_D_NV,
                                 getVariableDalpha(i * 3),
                                 getVariableDalpha(i * 3 + 1),
                                 getVariableDalpha(i * 3 + 2) );

            // ALPHA output
            osgGlCombinerOutputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                  getOutputABalpha    (i),
                                  getOutputCDalpha    (i),
                                  getOutputSumalpha   (i),
                                  getScalealpha       (i),
                                  getBiasalpha        (i),
                                  GL_FALSE,
                                  GL_FALSE,
                                  getMuxSumalpha      (i) );
        }
        else
        {
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, 
                                 GL_ALPHA, GL_VARIABLE_A_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                 GL_VARIABLE_B_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                 GL_VARIABLE_C_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 
            osgGlCombinerInputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                 GL_VARIABLE_D_NV,
                                 GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA); 

            osgGlCombinerOutputNV(GL_COMBINER0_NV + i, GL_ALPHA, 
                                  GL_DISCARD_NV, GL_DISCARD_NV, GL_DISCARD_NV,
                                  GL_NONE, GL_NONE,
                                  GL_FALSE, GL_FALSE, GL_FALSE );   
        }
        
        if(getPerStageConstants())
        {
            if(hasRC2)
            {
                osgGlCombinerStageParameterfvNV(
                    GL_COMBINER0_NV + i, 
                    GL_CONSTANT_COLOR0_NV, 
                    const_cast<GLfloat *>(
                        getCombinerColor0(i).getValuesRGBA()));

                osgGlCombinerStageParameterfvNV(
                    GL_COMBINER0_NV + i, 
                    GL_CONSTANT_COLOR1_NV, 
                    const_cast<GLfloat *>(
                        getCombinerColor1(i).getValuesRGBA()));
                
            }
            else
            {
                FWARNING(("RegisterCombinersChunk::register_combiners2 not"
                           "supported, constant colors ignored!!\n"));
            }
        }
    }
    
    if(hasRC2)
    {
        if(getPerStageConstants())
        {
            glEnable(GL_PER_STAGE_CONSTANTS_NV);
        }
        else
        {
            glDisable(GL_PER_STAGE_CONSTANTS_NV);
        }
    }
    
    glErr("RegisterCombinersChunk::general combiners setup");
 
    // setup the final combiner
     
    osgGlFinalCombinerInputNV(GL_VARIABLE_A_NV,
                              getVariableArgb(OSG_NUM_COMBINERS * 3),
                              getVariableArgb(OSG_NUM_COMBINERS * 3 + 1),
                              getVariableArgb(OSG_NUM_COMBINERS * 3 + 2));
    
    glErr("RegisterCombinersChunk::final combiner var a setup");
 
    osgGlFinalCombinerInputNV(GL_VARIABLE_B_NV,
                              getVariableBrgb(OSG_NUM_COMBINERS * 3),
                              getVariableBrgb(OSG_NUM_COMBINERS * 3 + 1),
                              getVariableBrgb(OSG_NUM_COMBINERS * 3 + 2));
 
    glErr("RegisterCombinersChunk::final combiner var b setup");
    
    osgGlFinalCombinerInputNV(GL_VARIABLE_C_NV,
                              getVariableCrgb(OSG_NUM_COMBINERS * 3),
                              getVariableCrgb(OSG_NUM_COMBINERS * 3 + 1),
                              getVariableCrgb(OSG_NUM_COMBINERS * 3 + 2));
 
    glErr("RegisterCombinersChunk::final combiner var c setup");
 
    osgGlFinalCombinerInputNV(GL_VARIABLE_D_NV,
                              getVariableDrgb(OSG_NUM_COMBINERS * 3),
                              getVariableDrgb(OSG_NUM_COMBINERS * 3 + 1),
                              getVariableDrgb(OSG_NUM_COMBINERS * 3 + 2));
 
    glErr("RegisterCombinersChunk::final combiner var d setup");
 
    osgGlFinalCombinerInputNV(GL_VARIABLE_E_NV,
                              getVariableE(0),
                              getVariableE(1),
                              getVariableE(2));
 
    glErr("RegisterCombinersChunk::final combiner var e setup");
 
    osgGlFinalCombinerInputNV(GL_VARIABLE_F_NV,
                              getVariableF(0),
                              getVariableF(1),
                              getVariableF(2));
 
    glErr("RegisterCombinersChunk::final combiner var f setup");
 
    osgGlFinalCombinerInputNV(GL_VARIABLE_G_NV,
                              getVariableG(0),
                              getVariableG(1),
                              getVariableG(2));
    
    glErr("RegisterCombinersChunk::final combiner setup");
    // and activate everything
    
    glEnable(GL_REGISTER_COMBINERS_NV);

    glErr("RegisterCombinersChunk::activate");
}


void RegisterCombinersChunk::changeFrom(DrawEnv    *pEnv, 
                                        StateChunk *old   , 
                                        UInt32      idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;

    old->deactivate(pEnv, idx);
    activate(pEnv, idx);
}

void RegisterCombinersChunk::deactivate(DrawEnv *, UInt32)
{
    glDisable(GL_REGISTER_COMBINERS_NV);

    glErr("RegisterCombinersChunk::deactivate");
}

bool RegisterCombinersChunk::isTransparent(void) const
{
    return false;
}

/*--------------------- Register Combiner Specific ------------------------*/

void RegisterCombinersChunk::ensureSizes()
{
    editMFVariableArgb  ()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFVariableBrgb  ()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFVariableCrgb  ()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFVariableDrgb  ()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFVariableAalpha()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFVariableBalpha()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFVariableCalpha()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFVariableDalpha()->resize(OSG_NUM_COMBINERS * 3 + 3);
    editMFOutputABrgb   ()->resize(OSG_NUM_COMBINERS);
    editMFOutputCDrgb   ()->resize(OSG_NUM_COMBINERS);
    editMFOutputSumrgb  ()->resize(OSG_NUM_COMBINERS);
    editMFScalergb      ()->resize(OSG_NUM_COMBINERS);
    editMFBiasrgb       ()->resize(OSG_NUM_COMBINERS);
    editMFDotABrgb      ()->resize(OSG_NUM_COMBINERS);
    editMFDotCDrgb      ()->resize(OSG_NUM_COMBINERS);
    editMFMuxSumrgb     ()->resize(OSG_NUM_COMBINERS);
    editMFScalealpha    ()->resize(OSG_NUM_COMBINERS);
    editMFBiasalpha     ()->resize(OSG_NUM_COMBINERS);
    editMFMuxSumalpha   ()->resize(OSG_NUM_COMBINERS);
    editMFCombinerColor0()->resize(OSG_NUM_COMBINERS);
    editMFCombinerColor1()->resize(OSG_NUM_COMBINERS);
    editMFVariableE     ()->resize(3);
    editMFVariableF     ()->resize(3);
    editMFVariableG     ()->resize(3);
}

void RegisterCombinersChunk::onCreate(const RegisterCombinersChunk *source)
{
    clearCombiners();
}

/*! Set all combiners to unused.
*/

void RegisterCombinersChunk::clearCombiners(void)
{
    ensureSizes();
    
    for(UInt16 i = 0; i < OSG_NUM_COMBINERS * 3; i += 3)
    {
        editVariableArgb  (i) = unused;
        editVariableAalpha(i) = unused;
    }
    
    setPerStageConstants(false);
}

void RegisterCombinersChunk::clearCombiner(UInt16 which)
{
    ensureSizes();
    
    editVariableArgb  (which * 3) = unused;
    editVariableAalpha(which * 3) = unused;
}

void RegisterCombinersChunk::setCombinerRGB(UInt16 which, 
      GLenum ainput,   GLenum amapping, GLenum acompusage, 
      GLenum binput,   GLenum bmapping, GLenum bcompusage, 
      GLenum cinput,   GLenum cmapping, GLenum ccompusage, 
      GLenum dinput,   GLenum dmapping, GLenum dcompusage, 
      GLenum outputAB, GLenum outputCD, GLenum outputSum,
      GLenum scale,    GLenum bias, 
      GLboolean dotAB, GLboolean dotCD, GLboolean muxSum)
{
    ensureSizes();
    
    const UInt16 ibase = which * 3;
    
    editVariableArgb(ibase    ) = ainput;
    editVariableArgb(ibase + 1) = amapping;
    editVariableArgb(ibase + 2) = acompusage;
    
    editVariableBrgb(ibase    ) = binput;
    editVariableBrgb(ibase + 1) = bmapping;
    editVariableBrgb(ibase + 2) = bcompusage;
    
    editVariableCrgb(ibase    ) = cinput;
    editVariableCrgb(ibase + 1) = cmapping;
    editVariableCrgb(ibase + 2) = ccompusage;
    
    editVariableDrgb(ibase    ) = dinput;
    editVariableDrgb(ibase + 1) = dmapping;
    editVariableDrgb(ibase + 2) = dcompusage;
    
    editOutputABrgb (which) = outputAB;
    editOutputCDrgb (which) = outputCD;
    editOutputSumrgb(which) = outputSum;
    editScalergb    (which) = scale;
    editBiasrgb     (which) = bias;
    editDotABrgb    (which) = dotAB;
    editDotCDrgb    (which) = dotCD;
    editMuxSumrgb   (which) = muxSum;
}

void RegisterCombinersChunk::setCombinerAlpha(UInt16 which, 
      GLenum ainput,   GLenum amapping, GLenum acompusage, 
      GLenum binput,   GLenum bmapping, GLenum bcompusage, 
      GLenum cinput,   GLenum cmapping, GLenum ccompusage, 
      GLenum dinput,   GLenum dmapping, GLenum dcompusage, 
      GLenum outputAB, GLenum outputCD, GLenum outputSum,
      GLenum scale,    GLenum bias,     GLboolean muxSum)
{
    ensureSizes();
    
    const UInt16 ibase = which * 3;
    
    editVariableAalpha(ibase    ) = ainput;
    editVariableAalpha(ibase + 1) = amapping;
    editVariableAalpha(ibase + 2) = acompusage;
    
    editVariableBalpha(ibase    ) = binput;
    editVariableBalpha(ibase + 1) = bmapping;
    editVariableBalpha(ibase + 2) = bcompusage;
    
    editVariableCalpha(ibase    ) = cinput;
    editVariableCalpha(ibase + 1) = cmapping;
    editVariableCalpha(ibase + 2) = ccompusage;
    
    editVariableDalpha(ibase    ) = dinput;
    editVariableDalpha(ibase + 1) = dmapping;
    editVariableDalpha(ibase + 2) = dcompusage;
    
    editOutputABalpha (which) = outputAB;
    editOutputCDalpha (which) = outputCD;
    editOutputSumalpha(which) = outputSum;
    editScalealpha    (which) = scale;
    editBiasalpha     (which) = bias;
    editMuxSumalpha   (which) = muxSum;
}

void RegisterCombinersChunk::setFinalCombiner(
      GLenum ainput, GLenum amapping, GLenum acompusage, 
      GLenum binput, GLenum bmapping, GLenum bcompusage, 
      GLenum cinput, GLenum cmapping, GLenum ccompusage, 
      GLenum dinput, GLenum dmapping, GLenum dcompusage, 
      GLenum einput, GLenum emapping, GLenum ecompusage, 
      GLenum finput, GLenum fmapping, GLenum fcompusage, 
      GLenum ginput, GLenum gmapping, GLenum gcompusage)
{    
    UInt16 ibase = OSG_NUM_COMBINERS * 3;
    
    editVariableArgb(ibase    ) = ainput;
    editVariableArgb(ibase + 1) = amapping;
    editVariableArgb(ibase + 2) = acompusage;
    
    editVariableBrgb(ibase    ) = binput;
    editVariableBrgb(ibase + 1) = bmapping;
    editVariableBrgb(ibase + 2) = bcompusage;
    
    editVariableCrgb(ibase    ) = cinput;
    editVariableCrgb(ibase + 1) = cmapping;
    editVariableCrgb(ibase + 2) = ccompusage;
    
    editVariableDrgb(ibase    ) = dinput;
    editVariableDrgb(ibase + 1) = dmapping;
    editVariableDrgb(ibase + 2) = dcompusage;
    
    editVariableE(0) = einput;
    editVariableE(1) = emapping;
    editVariableE(2) = ecompusage;
    
    editVariableF(0) = finput;
    editVariableF(1) = fmapping;
    editVariableF(2) = fcompusage;
    
    editVariableG(0) = ginput;
    editVariableG(1) = gmapping;
    editVariableG(2) = gcompusage;
}

void RegisterCombinersChunk::setConstantColors(Color4f &color0, 
                                               Color4f &color1)
{
    setColor0(color0);
    setColor1(color1);
}

void RegisterCombinersChunk::setCombinerColors(UInt16   which, 
                                               Color4f &color0, 
                                               Color4f &color1)
{
    setPerStageConstants(true);
    
    editCombinerColor0(which) = color0;
    editCombinerColor1(which) = color1;
}

/*-------------------------- Comparison -----------------------------------*/

Real32 RegisterCombinersChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool RegisterCombinersChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool RegisterCombinersChunk::operator == (const StateChunk &other) const
{
    RegisterCombinersChunk const *tother = 
        dynamic_cast<RegisterCombinersChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    // TODO compare reg comb
    return false;
}

bool RegisterCombinersChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

