/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaDomProfileCgFXHandler.h"
#include "OSGColladaLog.h"

#include "OSGColladaEffect.h"

#include "OSGCgFXMaterial.h"
#include "OSGCgFXVariableTexObj.h"

#if 0
#include "OSGCgFXPassChunk.h"
#include "OSGNameAttachment.h"
#endif

#ifdef OSG_WITH_COLLADA

#include <dae.h>
#include <dom/domEffect.h>
#include <dom/domInstance_effect.h>
#include <dom/domProfile_COMMON.h>
#include <dom/domProfile_GLSL.h>
#include <dom/domGl_pipeline_settings.h>


OSG_BEGIN_NAMESPACE

ColladaDomProfileHandlerRegHelper 
    ColladaDomProfileCgFXHandler::_regHelper(
         domProfile_CG::ID(),
        &ColladaDomProfileCgFXHandler::create);

void ColladaDomProfileCgFXHandler::readProfile(domFx_profile_abstract *pProf)
{
    //SWARNING << "ColladaEffect::readProfileCG: NIY." << std::endl;
}

MaterialTransitPtr ColladaDomProfileCgFXHandler::createInstProfile(
    domFx_profile_abstract *pProf,
    domEffect              *pEffect,
    domInstance_effect     *pInstEffect)
{
    MaterialTransitPtr returnValue(NULL);

    domProfile_CG *pProfCG = daeSafeCast<domProfile_CG>(pProf);

    if(pProfCG == NULL)
        return returnValue;

    bool materialInitialized = false;

    /* first things first, we need to find either the .cgfx file associated
     * with the  effect, or grab the string embedded in the .dae file which
     * has the .cgfx code text 
     * 
     * Check for file reference first.
     */

    domFx_include_common_Array  includeArr = pProfCG->getInclude_array();

    CgFXMaterialTransitPtr newCgFXmat = OSG::CgFXMaterial::create();

    std::string cgfxFileLocation("");

    if(includeArr.getCount() > 0)
    {
        bool foundFilepath = false;

        for(unsigned int i = 0; i < includeArr.getCount(); i++)
        {
            domFx_include_common_complexType *cur = includeArr[i];

            cgfxFileLocation = std::string(cur->getUrl().originalStr());

            // check if the url points to something in the collada file
            // (denoted by a #).  If it DOESN'T, then it is the file 
            // path to the .cgfx file used for this effect
    
            std::string::size_type loc = 0;

            if((loc = cgfxFileLocation.find_last_of('.')) != std::string::npos)
            {

                if(cgfxFileLocation.substr(loc).compare(".cgfx") == 0 &&  
                   cgfxFileLocation[0] != '#')
                {  
                    /* we assume this is the location of a cgfx file
                       so we use it to create the material */
                    foundFilepath = true;
                    break;
                }
                else if(cgfxFileLocation.substr(loc).compare(".cg") == 0)
                {
                    SWARNING << "ColladaEffect::createInstanceProfileCG: "
                             << "CG effects are not supported. " 
                             << "Must use CgFX instead."  << std::endl;
                    break;
                }
            }
        }
        if(foundFilepath)
        {   
            // use the file to initialize the material
            newCgFXmat->setEffectFile(
                ColladaGlobal::fixFilepath(cgfxFileLocation));

            materialInitialized = true;
        }
    } 
    else // check that there is inline code for the effect
    {
        // We need to build up the state and technique info from scratch,
        // since this info isn't included in the embedded code.

        domFx_code_profile_Array inlineCode = pProfCG->getCode_array();

        if(inlineCode.getCount() > 0)
        {
            // In the event that there is more than one available code string,
            // the first one is used 

            std::string effectCode = inlineCode[0]->getValue();

            // build up the code to set up techniques, passes, etc.
            UInt32 codeSize = effectCode.size();

            effectCode.append(buildCgFXCode(pProfCG));

            if(!(effectCode.size() == codeSize)) // true if code was appended...
            {
                newCgFXmat->setEffectString(effectCode);
            
                materialInitialized = true;
            } 
            else // error, since we can't set techniques, passes, etc.
            {
                SWARNING << "Error appending Cg code for " 
                         << pProfCG->getID() << ". Material will be null!" 
                         << std::endl;
            }
        } 
        else
        { 
            // no code inline code was found, return a null material.
            SWARNING << "No .cgfx file found and no inline code found for " 
                     << pEffect->getID()
                     << ". Material will be null!" << std::endl;
        }
    }

    if(materialInitialized)
    {
        // Since the CgFXMaterial isn't initialized (i.e., the code compiled)
        // until commitChanges() is called, we call it here so that we can
        // update the variables according to their values in the COLLADA file

        newCgFXmat->setParameterValueSource(CgFXMaterial::CURRENT);

        // In the event that there are samplers/texture, we handle them
        // separately from the uniform variables for now, if we find one,
        // we'll just push it onto a vector and handle it later. 

        std::vector<domInstance_effect::domSetparamRef> samplerParams;
        std::vector<domInstance_effect::domSetparamRef> surfaceParams;
        std::vector<domInstance_effect::domSetparamRef> matrixParams;

        // now update the variables, updated values come from the setparam
        // array Supported types are those supported by the
        // ShaderProgramVariable class 

        domInstance_effect::domSetparam_Array setParams = 
            pInstEffect->getSetparam_array(); 

        for(UInt32 i = 0; i < setParams.getCount(); ++i)
        {
            // We only handle types that CgFXMaterial handles
            // This is ugly, the collada DOM doesn't have a way to easily
            // determine what type of parameter a <setparam> is holding.  

            domFx_basic_type_commonRef curParam = 
                setParams[i]->getFx_basic_type_common();

            if(curParam == NULL) 
                continue;

            std::string paramName = setParams[i]->getRef();
            
            if(curParam->getBool() != NULL)
            {
                newCgFXmat->addUniformVariable(
                    paramName.c_str(),
                    bool(curParam->getBool()->getValue()));
            }
            else if(curParam->getInt() != NULL)
            {
                newCgFXmat->addUniformVariable(
                    paramName.c_str(),
                    Int32(curParam->getInt()->getValue()));
            }
            else if(curParam->getFloat() != NULL)
            {   
                newCgFXmat->addUniformVariable(
                    paramName.c_str(),
                    Real32(curParam->getFloat()->getValue()));
            }
            else if(curParam->getFloat2() != NULL)
            {
                Vec2f val(curParam->getFloat2()->getValue()[0],
                          curParam->getFloat2()->getValue()[1]);

                newCgFXmat->addUniformVariable(paramName.c_str(), 
                                               val              );
            }
            else if(curParam->getFloat3() != NULL)
            {
                
                Vec3f val(curParam->getFloat3()->getValue()[0],
                          curParam->getFloat3()->getValue()[1],
                          curParam->getFloat3()->getValue()[2]);

                newCgFXmat->addUniformVariable(paramName.c_str(),
                                               val              );
            }
            else if(curParam->getFloat4() != NULL)
            {
                
                Vec3f val(curParam->getFloat4()->getValue()[0],
                          curParam->getFloat4()->getValue()[1],
                          curParam->getFloat4()->getValue()[2],
                          curParam->getFloat4()->getValue()[3]);

                newCgFXmat->addUniformVariable(paramName.c_str(),
                                               val              );
            }
            else if(curParam->getFloat4x4() != NULL)
            {
                // set matrices later, after checking if they are state
                // matrices, which we don't want to set.

                matrixParams.push_back(setParams[i]);
            } 
            else if(curParam->getSurface() != NULL)
            { 
                // handle surfaces later...
                surfaceParams.push_back(setParams[i]);
            }
            else if(isCGSampler(curParam))
            { 
                // handle samplers later
                samplerParams.push_back(setParams[i]);
            } 
            else
            {
                SWARNING << "Profile_CG variable " 
                         << paramName
                         << "'s type is not supported by CgFXMaterial, "
                         << " and will be ignored." 
                         << std::endl;
                
            } // end if/else chain
        } // end for(params.getCount())      

        // now checking the matrices to make sure they are not state matrices
        // before setting them

        domCg_newparam_Array newParams = pProfCG->getNewparam_array();

        for(UInt32 i = 0; i < matrixParams.size(); ++i)
        {
            std::string matrixName = matrixParams[i]->getRef();

            for(UInt32 j = 0; j < newParams.getCount(); ++j)
            {
                std::string newParamName = newParams[j]->getSid();

                if(newParamName.compare(matrixName) == 0)
                {
                    // now check the semantic property of the newParam, 
                    // to see if it is a state matrix

                    if(newParams[j]->getSemantic() != NULL)
                    {
                        if(isStateMatrix(
                               newParams[j]->getSemantic()->getValue()))
                        { 
                            // is it a state matrix? then don't set the new
                            // values 

                            break;
                        }
                    } 
                    
                    domFloat4x4 val = 
                        matrixParams[i]->getFx_basic_type_common()->
                            getFloat4x4()->getValue();

                    Matrix tmp(
                        val.get(0 ), val.get(1 ), val.get(2 ), val.get(3 ),
                        val.get(4 ), val.get(5 ), val.get(6 ), val.get(7 ),
                        val.get(8 ), val.get(9 ), val.get(10), val.get(11),
                        val.get(12), val.get(13), val.get(14), val.get(15));

                    newCgFXmat->addUniformVariable(matrixName.c_str(),tmp);

                    break;
                     
                } // end if(!isStateMatrix)
            } //end for(newParams.size())
        } // end for(matrixParams.size())

    
        //pairs from the name of the surface to its filepath
        std::map<std::string,std::string> imgPaths; 

        // now we need to handle samplers/surfaces
        for(UInt32 i = 0; i < surfaceParams.size(); ++i)
        {
            domFx_surface_commonRef surf = 
                surfaceParams[i]->getFx_basic_type_common()->getSurface();

            // Checking if there is an associated image to init this surface
            // from. There is no guarantee of an associated type for a
            // <surface> in the Cg scope, so we just check what the associated
            // image is. 

            domFx_surface_init_from_common_Array inits = 
                surf->getFx_surface_init_common()->getInit_from_array();

            for(UInt32 j = 0; j < inits.getCount(); ++j)
            { 
                // there can be only one
                domImage *image = 
                    daeSafeCast<domImage>(inits[j]->getValue().getElement());

                if(image != NULL) 
                {
                    imgPaths[surfaceParams[i]->getRef()] = 
                        // can be used to get absolute filepath
                        //  image->getInit_from()->getValue().getURI() 
                        image->getInit_from()->getValue().getOriginalURI();
                }
            }
        }

        // now we update the samplers' texture references
        for(UInt32 i = 0; i < samplerParams.size(); ++i)
        {
            std::string sourceName;

            domFx_sampler1D_commonRef samp1d = 
                samplerParams[i]->getFx_basic_type_common()->getSampler1D(); 

            if(samp1d != NULL)
            {
                sourceName = samp1d->getSource()->getValue();
            }

            domFx_sampler2D_commonRef samp2d = 
                samplerParams[i]->getFx_basic_type_common()->getSampler2D(); 

            if(samp2d != NULL)
            {
                sourceName = samp2d->getSource()->getValue();
            }

            domFx_sampler3D_commonRef samp3d = 
                samplerParams[i]->getFx_basic_type_common()->getSampler3D(); 

            if(samp3d != NULL)
            {
                sourceName = samp3d->getSource()->getValue();
            }

            domFx_samplerCUBE_commonRef sampCube = 
                samplerParams[i]->getFx_basic_type_common()->getSamplerCUBE();

            if(sampCube != NULL)
            {
                sourceName = sampCube->getSource()->getValue();
            }

            domFx_samplerRECT_commonRef sampRect = 
                samplerParams[i]->getFx_basic_type_common()->getSamplerRECT();

            if(sampRect != NULL)
            {
                sourceName = sampRect->getSource()->getValue();
            }

            domFx_samplerDEPTH_commonRef sampDepth = 
                samplerParams[i]->getFx_basic_type_common()->getSamplerDEPTH();

            if(sampDepth != NULL)
            {   
                sourceName = sampDepth->getSource()->getValue();
            }
            
            std::string szFilename = imgPaths[sourceName];

            if(!szFilename.empty())
            {
                // we have the new path of the file
                // set it as a variable, so it will be initialized later
                // by the material when it is initialized
                Int32 uiSamplerId = -1;

                CgFXVariableTexObjUnrecPtr pVar = CgFXVariableTexObj::create();

                pVar->setName    (samplerParams[i]->getRef()            );
                pVar->setValue   (uiSamplerId                           );
                pVar->setFilePath(ColladaGlobal::fixFilepath(szFilename));

                newCgFXmat->addVariable(pVar);

            } // end if(!szFilename.empty())
        } // end for(samplerParams.size())

        // set the technique for this effect
        domInstance_effect::domTechnique_hint_Array techHnts = 
            pInstEffect->getTechnique_hint_array();

        std::string techName;

        for(UInt32 i = 0; i < techHnts.getCount(); ++i)
        {
            // we are interested in "ref", which is the name of the technique
            // this CgFXMaterial is to use. if there are more than 1, we use
            // the last one listed 

            techName = techHnts[i]->getRef();
        }

        if(techName.compare("") != 0 && techHnts.getCount() > 0)
        { 
            // a name was given for which technique to use, so we will use it

            newCgFXmat->setActiveTechnique(techName);
        }
    } // end if(materialInitialized)
    
//        OSG::commitChanges();

    returnValue = newCgFXmat;

    return returnValue;
}


ColladaDomProfileHandlerTransitPtr ColladaDomProfileCgFXHandler::create(
    void)
{
    ColladaDomProfileHandlerTransitPtr returnValue(
        new ColladaDomProfileCgFXHandler);

    return returnValue;
}

ColladaDomProfileCgFXHandler::ColladaDomProfileCgFXHandler(void) :
    Inherited()
{
}

ColladaDomProfileCgFXHandler::~ColladaDomProfileCgFXHandler(void)
{
}

/*
 * Gets the string equivalent representation of a domGl_func_type needed by
 * the Cg compiler. 
 */

std::string ColladaDomProfileCgFXHandler::getFuncTypeString(
    domGl_func_type func)
{
    std::string funcVal;

    switch(func)
    {
        case GL_FUNC_TYPE_NEVER :
            funcVal = "Never";
            break;
        case GL_FUNC_TYPE_LESS:
            funcVal = "Less";
            break;
        case GL_FUNC_TYPE_LEQUAL:
            funcVal = "LEqual";
            break;
        case GL_FUNC_TYPE_EQUAL: 
            funcVal = "Equal";
            break;
        case GL_FUNC_TYPE_GREATER: 
            funcVal = "Greater";
            break;
        case GL_FUNC_TYPE_NOTEQUAL:
            funcVal = "NotEqual";
            break;
        case GL_FUNC_TYPE_GEQUAL:
            funcVal = "GEqual";
            break;
        case GL_FUNC_TYPE_ALWAYS:
            funcVal = "Always";
            break;
        case GL_FUNC_TYPE_COUNT:
            funcVal = "Count";
            break;
        default:
            funcVal = "LEqual";
    } // end switch

    return funcVal;
}

std::string ColladaDomProfileCgFXHandler::getBlendEquationString(
    domGl_blend_equation_type eq)
{
    std::string eqVal;

    switch(eq)
    {
        case GL_BLEND_EQUATION_TYPE_FUNC_ADD: 
            eqVal = "FuncAdd";
            break;
        case GL_BLEND_EQUATION_TYPE_FUNC_SUBTRACT:
            eqVal = "FuncSubtract";
            break;
        case GL_BLEND_EQUATION_TYPE_FUNC_REVERSE_SUBTRACT: 
            eqVal = "FuncReverseSubtract";
            break;
        case GL_BLEND_EQUATION_TYPE_MIN:
            eqVal = "Min";
            break;
        case GL_BLEND_EQUATION_TYPE_MAX:
            eqVal = "Max";
            break;
        default:
            eqVal = "FuncAdd";
    }

    return eqVal;
}

std::string ColladaDomProfileCgFXHandler::getBlendFuncTypeString(
    domGl_blend_type func)
{
    std::string funcVal;

    switch(func)
    {
        case GL_BLEND_TYPE_ZERO:
            funcVal = "Zero";
            break;
        case GL_BLEND_TYPE_ONE:
            funcVal = "One";
            break;
        case GL_BLEND_TYPE_SRC_COLOR:
            funcVal = "SrcColor";
            break;
        case GL_BLEND_TYPE_ONE_MINUS_SRC_COLOR:
            funcVal = "OneMinusSrcAlpha";
            break;
        case GL_BLEND_TYPE_DEST_COLOR:
            funcVal = "DestColor";
            break;
        case GL_BLEND_TYPE_ONE_MINUS_DEST_COLOR:
            funcVal = "OneMinusDestColor";
            break;
        case GL_BLEND_TYPE_SRC_ALPHA:
            funcVal = "SrcAlpha";
            break;
        case GL_BLEND_TYPE_ONE_MINUS_SRC_ALPHA:
            funcVal = "OneMinusSrcAlpha";
            break;
        case GL_BLEND_TYPE_DST_ALPHA:
            funcVal = "DstAlpha";
            break;
        case GL_BLEND_TYPE_ONE_MINUS_DST_ALPHA:
            funcVal = "OneMinusDstAlpha";
            break;
        case GL_BLEND_TYPE_CONSTANT_COLOR:
            funcVal = "ConstantColor";
            break;
        case GL_BLEND_TYPE_ONE_MINUS_CONSTANT_COLOR:
            funcVal = "OneMinusConstantColor";
            break;
        case GL_BLEND_TYPE_CONSTANT_ALPHA:
            funcVal = "ConstantAlpha";
            break;
        case GL_BLEND_TYPE_ONE_MINUS_CONSTANT_ALPHA:
            funcVal = "OneMinusConstantAlpha";
            break;
        case GL_BLEND_TYPE_SRC_ALPHA_SATURATE:
            funcVal = "SrcAlphaSaturate";
            break;
        default:
            funcVal = "Zero";
    }

    return funcVal;
}


std::string ColladaDomProfileCgFXHandler::getFaceTypeString(
    domGl_face_type face)
{
    std::string faceVal;

    switch(face)
    {
        case GL_FACE_TYPE_FRONT:
            faceVal = "Front";
            break;
        case GL_FACE_TYPE_BACK:
            faceVal = "Back";
            break;
        case GL_FACE_TYPE_FRONT_AND_BACK:
            faceVal = "FrontAndBack";
            break;
        default:
            faceVal = "Back";
    }

    return faceVal;
}

std::string ColladaDomProfileCgFXHandler::getMaterialModeTypeString(
    domGl_material_type mat)
{
    std::string matVal;

    switch(mat)
    {
        case GL_MATERIAL_TYPE_EMISSION:
            matVal = "Emission";
            break;
        case GL_MATERIAL_TYPE_AMBIENT:
            matVal = "Ambient";
            break;
        case GL_MATERIAL_TYPE_DIFFUSE:
            matVal = "Diffuse";
            break;
        case GL_MATERIAL_TYPE_SPECULAR:
            matVal = "Specular";
            break;
        case GL_MATERIAL_TYPE_AMBIENT_AND_DIFFUSE:
            matVal = "AmbientAndDiffuse";
            break;

        default:
            break;
    }

    return matVal;
}

std::string ColladaDomProfileCgFXHandler::getLogicOpTypeString(
    domGl_logic_op_type logicOp)
{
    std::string logicOpType;

    switch(logicOp)
    {
        case GL_LOGIC_OP_TYPE_CLEAR:
            logicOpType = "Clear";
            break;
        case GL_LOGIC_OP_TYPE_AND: 
            logicOpType = "And";
            break;
        case GL_LOGIC_OP_TYPE_AND_REVERSE:
            logicOpType = "AndReverse";
            break;  
        case GL_LOGIC_OP_TYPE_COPY: 
            logicOpType = "Copy";
            break;  
        case GL_LOGIC_OP_TYPE_AND_INVERTED: 
            logicOpType = "AndInverted";
            break;  
        case GL_LOGIC_OP_TYPE_NOOP: 
            logicOpType = "Noop";
            break;  
        case GL_LOGIC_OP_TYPE_XOR: 
            logicOpType = "Xor";
            break;  
        case GL_LOGIC_OP_TYPE_OR:
            logicOpType = "Or";
            break;  
        case GL_LOGIC_OP_TYPE_NOR:
            logicOpType = "Nor";
            break;  
        case GL_LOGIC_OP_TYPE_EQUIV:
            logicOpType = "Equiv";
            break;  
        case GL_LOGIC_OP_TYPE_INVERT:
            logicOpType = "Invert";
            break;  
        case GL_LOGIC_OP_TYPE_OR_REVERSE:
            logicOpType = "OrReverse";
            break;  
        case GL_LOGIC_OP_TYPE_COPY_INVERTED:
            logicOpType = "CopyInverted";
            break;  
        case GL_LOGIC_OP_TYPE_NAND:
            logicOpType = "Nand";
            break;  
        case GL_LOGIC_OP_TYPE_SET:
            logicOpType = "Set";
            break;
        default:
            logicOpType = "Or";
    }

    return logicOpType;
}

std::string ColladaDomProfileCgFXHandler::getStencilOpTypeString(
    domGl_stencil_op_type stopType)
{
    std::string stopVal;

    switch(stopType)
    {
        case GL_STENCIL_OP_TYPE_KEEP:
            stopVal = "Keep";
            break;
        case GL_STENCIL_OP_TYPE_ZERO:
            stopVal = "Zero";
            break;
        case GL_STENCIL_OP_TYPE_REPLACE:
            stopVal = "Replace";
            break;
        case GL_STENCIL_OP_TYPE_INCR:
            stopVal = "Incr";
            break;
        case GL_STENCIL_OP_TYPE_DECR:
            stopVal = "Decr";
            break;
        case GL_STENCIL_OP_TYPE_INVERT:
            stopVal = "Invert";
            break;
        case GL_STENCIL_OP_TYPE_INCR_WRAP:
            stopVal = "IncrWrap";
            break;
        case GL_STENCIL_OP_TYPE_DECR_WRAP:
            stopVal = "DecrWrap";
            break;
        default:
            stopVal = "Keep";
    }

    return stopVal;
}


std::string ColladaDomProfileCgFXHandler::getBoolStringRep(
    std::string stateName, 
    UInt32      idx, 
    bool        state    )
{
    std::stringstream buf;

    buf << stateName 
        << "[" 
        << idx 
        << "] = " 
        << ((state)?("true"):("false")) 
        << "; ";

    return buf.str();
}

std::string ColladaDomProfileCgFXHandler::getBoolStringRep(
    std::string stateName, 
    bool        state    )
{
    if(state) 
    {
        return stateName.append(" = true; ");
    }
    else 
    {
        return stateName.append(" = false; ");
    }
}

bool ColladaDomProfileCgFXHandler::isCGSampler(domFx_basic_type_commonRef param)
{
        if(param->getSampler1D        () != NULL) 
            return true;
        else if(param->getSampler2D   () != NULL) 
            return true;
        else if(param->getSampler3D   () != NULL) 
            return true;
        else if(param->getSamplerCUBE () != NULL) 
            return true;
        else if(param->getSamplerDEPTH() != NULL) 
            return true;
        else if(param->getSamplerRECT () != NULL) 
            return true;
        else return false;
}

/*
 * Checks whether a semantic represents a state matrix
 *
 */

bool ColladaDomProfileCgFXHandler::isStateMatrix(std::string semantic)
{
    if(semantic.length() < 4) 
        return false; // early out

    static std::string stateMatrixNames[] = 
    {
        "TIME",
        "VIEWPROJECTION",
        "VIEWINVERSETRANSPOSE",
        "VIEWIT",
        "VIEWINVERSE",
        "VIEWI",
        "VIEW",
        "MODELVIEWINVERSETRANSPOSE",
        "MODELVIEWIT",
        "MODELVIEWINVERSE",
        "MODELVIEWI",
        "MODELVIEW",
        "WORLDVIEWINVERSETRANSPOSE",
        "WORLDVIEWIT",
        "WORLDVIEWINVERSE",
        "WORLDVIEWI",
        "WORLDVIEW",
        "MODELINVERSERTRANSPOSE",
        "MODELIT",
        "MODELINVERSE",
        "MODELI",
        "MODEL",
        "WORLDINVERSETRANSPOSE",
        "WORLDIT",
        "WORLDINVERSE",
        "WORLDI",
        "WORLD",
        "MODELVIEWPROJECTION",
        "WORLDVIEWPROJECTION",
        "PROJECTION"
    };
    
    for(UInt32 i = 0; i < 30; ++i)
    {
        if(osgStringCaseCmp(stateMatrixNames[i].c_str(),semantic.c_str()) == 0)
            return true;
    }

    return false;
}

/*
 *  Generates   techniques, passes, and bindings embedded in the COLLADA file
 *  are converting them to compileable code for the Cg compiler to
 *  use. Requires valid vertex and fragment shaders.
 */

std::string ColladaDomProfileCgFXHandler::buildCgFXCode(domProfile_CG *pProf)
{
    std::stringstream buf;

    buf << std::endl;

    // getting the techniques. There must be at least one
    domProfile_CG::domTechnique_Array techs = pProf->getTechnique_array();

    for(UInt32 i = 0; i < techs.getCount(); ++i) 
    {
        buf << std::endl << "technique " << techs[i]->getSid() << " { ";

        domProfile_CG::domTechnique::domPass_Array passes = 
            techs[i]->getPass_array();

        for(UInt32 j = 0; j < passes.getCount(); ++j)
        {
            
            buf << " pass " << passes[j]->getSid() << " { ";

            domProfile_CG::domTechnique::domPass::domShader *vertex   = NULL;
            domProfile_CG::domTechnique::domPass::domShader *fragment = NULL;

            domProfile_CG::domTechnique::domPass::domShader_Array shds = 
                passes[j]->getShader_array();

            for(UInt32 k = 0; k < shds.getCount(); ++k)
            {
                if(shds[k]->getStage() == CG_PIPELINE_STAGE_FRAGMENT &&
                   fragment            == NULL                        )
                {
                    fragment = shds[k];
                    continue;
                }

                if(shds[k]->getStage() == CG_PIPELINE_STAGE_VERTEX &&
                   vertex              == NULL                      )
                {
                    vertex = shds[k];

                    continue;
                }
            }

            if(vertex == NULL || fragment == NULL) 
                return ""; // can't continue
            
            std::string compTargV = 
                vertex->getCompiler_target()->getCharData();

            std::string compNameV = 
                vertex->getName()           ->getCharData();


            if(compTargV.size() == 0 || compNameV.size() == 0) 
                return ""; // can't continue

            buf << "VertexProgram = compile " << compTargV << " " << compNameV
                << "(" << extractCgBindParams(vertex) << "); ";

            // need to get render state information
            buf << extractCgStates(passes[j]);

            // add in fragment program stuff...  
            std::string compTargF =
                fragment->getCompiler_target()->getCharData();

            std::string compNameF =
                fragment->getName()           ->getCharData();

            if(compTargF.size() == 0 || compNameF.size() == 0) 
                return "";

            buf << "FragmentProgram = compile " << compTargF << " " 
                << compNameF
                << "(" << extractCgBindParams(fragment) << ");}";
            
        }
        
        buf << " } " << std::endl;
    }
    
    return buf.str();
}

/*
 * Helper function for extracting names of parameters that need to be bound
 * to the compilers. 
 */

std::string ColladaDomProfileCgFXHandler::extractCgBindParams(
    domShader *pShader)
{
    std::stringstream buf;

    domProfile_CG::domTechnique::domPass::domShader::domBind_Array arr = 
        pShader->getBind_array();

    for(UInt32 i = 0; i < arr.getCount(); ++i)
    {
        buf << arr[i]->getParam()->getRef();

        if(i < arr.getCount() - 1) 
            buf << ",";
    }

    return buf.str();
}


/*
 *   Extracts all explicitly defined states for a given pass.  There are a LOT
 *   of different states, so this function is quite long...
 *
 */

std::string ColladaDomProfileCgFXHandler::extractCgStates(domPassRef pPass)
{
    std::stringstream buf;

    // rendering to texture not currently supported, may do so in the future.

    buf << " ";
    // now handle all of the possible states assignments...

    domGl_pipeline_settings_Array states = 
        pPass->getGl_pipeline_settings_array();

    for(UInt32 i = 0; i < states.getCount(); ++i)
    {   
        domGl_pipeline_settings::domAlpha_funcRef af = 
            states[i]->getAlpha_func();

        if(af != NULL)
        {
            buf << " AlphaFunc = float2(" 
                << getFuncTypeString(af->getFunc()->getValue()) 
                << "," 
                << af->getValue()->getValue() << "); ";

            continue;
        }

        domGl_pipeline_settings::domBlend_funcRef bf = 
            states[i]->getBlend_func();

        if(bf != NULL)
        {
            buf << " BlendFunc = int2(" 
                << getBlendFuncTypeString(bf->getSrc()->getValue())
                << "," 
                << getBlendFuncTypeString(bf->getDest()->getValue()) << "); ";

            continue;
        }

        domGl_pipeline_settings::domBlend_func_separateRef bfs = 
            states[i]->getBlend_func_separate();

        if(bfs != NULL)
        {
            buf << " BlendFuncSeparate = int4(" 
                << getBlendFuncTypeString(bfs->getSrc_rgb   ()->getValue()) 
                << ","
                << getBlendFuncTypeString(bfs->getDest_rgb  ()->getValue()) 
                << ","
                << getBlendFuncTypeString(bfs->getSrc_alpha ()->getValue()) 
                << ","
                << getBlendFuncTypeString(bfs->getDest_alpha()->getValue()) 
                << "); ";

            continue;
        }

        domGl_pipeline_settings::domBlend_equationRef ble = 
            states[i]->getBlend_equation();

        if(ble != NULL)
        {   
            buf<< " BlendEquation = " 
               << getBlendEquationString(ble->getValue()) << "; ";

            continue;
        }

        domGl_pipeline_settings::domBlend_equation_separateRef bles = 
            states[i]->getBlend_equation_separate();

        if(bles != NULL)
        {
            buf << " BlendEquationSeparate = int2(" 
                << getBlendEquationString(bles->getRgb  ()->getValue())
                << "," 
                << getBlendEquationString(bles->getAlpha()->getValue()) 
                << "); ";
            
            continue;
        }

        domGl_pipeline_settings::domDepth_funcRef df = 
            states[i]->getDepth_func();

        if(df != NULL)
        {
            buf << " DepthFunc = " << getFuncTypeString(df->getValue()) << "; ";

            continue;
        } 

        domGl_pipeline_settings::domDepth_maskRef dm = 
            states[i]->getDepth_mask();

        if(dm != NULL)
        {
            buf << " DepthMask = " 
                << (dm->getValue() ? ("true") : ("false")) << "; ";

            continue;
        }

        domGl_pipeline_settings::domColor_materialRef cm = 
            states[i]->getColor_material();

        if(cm != NULL)
        {
            buf << " ColorMaterial = int2(" 
                << getFaceTypeString(cm->getFace()->getValue()) 
                << "," 
                << getMaterialModeTypeString(cm->getMode()->getValue()) 
                << "); ";

            continue;
        }

        domGl_pipeline_settings::domCull_faceRef cf = states[i]->getCull_face();

        if(cf != NULL)
        {
            buf << " CullFace = " << getFaceTypeString(cf->getValue())<< "; ";

            continue;
        }

        domGl_pipeline_settings::domFog_modeRef fm = states[i]->getFog_mode();

        if(fm != NULL)
        {
            std::string fogMode;

            switch(fm->getValue())
            {
                case GL_FOG_TYPE_LINEAR:
                    fogMode = "Linear";
                    break;
                case GL_FOG_TYPE_EXP:
                    fogMode = "Exp";
                    break;
                case GL_FOG_TYPE_EXP2:
                    fogMode = "Exp2";
                    break;
                    
                default:
                    break;
            }

            buf << " FogMode = " << fogMode << "; "; 

            continue;
        }

        domGl_pipeline_settings::domFog_coord_srcRef fcs = 
            states[i]->getFog_coord_src();

        if(fcs != NULL)
        {   
            buf << " FogCoordSrc = " 
                << ((fcs->getValue() == GL_FOG_COORD_SRC_TYPE_FOG_COORDINATE) ?
                        ("FogCoord") : ("FragmentDepth")) << "; ";

            continue;
        }

        domGl_pipeline_settings::domFront_faceRef ff = 
            states[i]->getFront_face();

        if(ff != NULL)
        {
            buf << " FrontFace = " 
                << ((ff->getValue() == GL_FRONT_FACE_TYPE_CW) ? 
                        ("CW") : ("CCW")) << "; ";

            continue;
        }

        domGl_pipeline_settings::domLight_model_color_controlRef lmcc = 
            states[i]->getLight_model_color_control();

        if(lmcc != NULL)
        {
            buf << " LightModelColorControl = " 
                << ((lmcc->getValue() == 
                              GL_LIGHT_MODEL_COLOR_CONTROL_TYPE_SINGLE_COLOR) ?
                        ("SingleColor") : ("SeparateSpecular"))  << "; ";

            continue;
        }

        domGl_pipeline_settings::domLogic_opRef lop = states[i]->getLogic_op();

        if(lop != NULL)
        {
            buf << " LogicOp = " 
                << getLogicOpTypeString(lop->getValue()) << "; ";

            continue;
        }

        domGl_pipeline_settings::domPolygon_modeRef pm = 
            states[i]->getPolygon_mode();

        if(pm != NULL)
        {
            std::string mode;

            switch(pm->getMode()->getValue())
            {
                case GL_POLYGON_MODE_TYPE_POINT:
                    mode = "Point";
                    break;
                case GL_POLYGON_MODE_TYPE_LINE:
                    mode = "Line";
                    break;
                case GL_POLYGON_MODE_TYPE_FILL:
                    mode = "Fill";
                    break;
                default:
                    mode = "Fill";
            }

            buf << " PolygonMode = int2(" 
                << getFaceTypeString(pm->getFace()->getValue())
                << "," 
                << mode << "); ";

            continue;
        }

        domGl_pipeline_settings::domShade_modelRef shm = 
            states[i]->getShade_model();

        if(shm != NULL)
        {
            buf << " ShadeModel = " 
                << ((shm->getValue() == GL_SHADE_MODEL_TYPE_FLAT) ? 
                        ("Flat") : ("Smooth")) << "; ";
            continue;
        }

        domGl_pipeline_settings::domStencil_funcRef stf = 
            states[i]->getStencil_func();

        if(stf != NULL)
        {   
            buf << " StencilFunc = int3(" 
                << getFuncTypeString(stf->getFunc()->getValue()) 
                << "," 
                << UInt32(stf->getMask()->getValue()) 
                << "," 
                << UInt32(stf->getRef ()->getValue()) << "); ";

            continue;
        }

        domGl_pipeline_settings::domStencil_opRef sto = 
            states[i]->getStencil_op();

        if(sto != NULL)
        {
            buf << " StencilOp = int3(" 
                << getStencilOpTypeString(sto->getZfail()->getValue())
                << "," 
                << getStencilOpTypeString(sto->getFail ()->getValue())
                << "," 
                << getStencilOpTypeString(sto->getZpass()->getValue()) 
                << "); ";

            continue;
        }

        domGl_pipeline_settings::domStencil_op_separateRef stos = 
            states[i]->getStencil_op_separate();

        if(stos != NULL)
        {
            buf << " StencilOpSeparate = int4(" 
                << getFaceTypeString(stos->getFace()->getValue())
                << "," 
                << getStencilOpTypeString(stos->getZfail()->getValue())
                << "," 
                << getStencilOpTypeString(stos->getFail ()->getValue())
                << "," 
                << getStencilOpTypeString(stos->getZpass()->getValue()) 
                << "); ";

            continue;

        }
    
        domGl_pipeline_settings::domStencil_mask_separateRef stms = 
            states[i]->getStencil_mask_separate();

        if(stms != NULL)
        {
            buf << " StencilMaskSeparate = (" 
                << getFaceTypeString(stms->getFace()->getValue())
                << "," 
                << (unsigned int)stms->getMask()->getValue() << "); ";

            continue;
        }

        domGl_pipeline_settings::domLight_ambientRef la = 
            states[i]->getLight_ambient();

        if(la != NULL)
        {
            domFloat4 ambient = la->getValue();

            buf << " LightAmbient" 
                << "[" << la->getIndex() << "] = float4(" << ambient[0] 
                << "," << ambient[1] << "," << ambient[2] << "," 
                << ambient[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domLight_diffuseRef ld = 
            states[i]->getLight_diffuse();

        if(ld != NULL)
        {
            domFloat4 diffuse = ld->getValue();

            buf << " LightDiffuse" 
                << "[" << ld->getIndex() << "] = float4(" << diffuse[0] 
                << "," << diffuse[1] << "," << diffuse[2] << "," 
                << diffuse[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domLight_specularRef ls = 
            states[i]->getLight_specular();

        if(ld != NULL)
        {
            domFloat4 specular = ls->getValue();

            buf << " LightSpecular" << "[" << ls->getIndex() << "] = float4(" 
                << specular[0] << "," << specular[1] << "," << specular[2] 
                << "," << specular[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domLight_positionRef lp = 
            states[i]->getLight_position();

        if(lp != NULL)
        {
            domFloat4 position = lp->getValue();

            buf << " LightPosition" << "[" << lp->getIndex() << "] = float4("
                << position[0] << "," << position[1] << "," << position[2] 
                << "," << position[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domLight_constant_attenuationRef lca = 
            states[i]->getLight_constant_attenuation();

        if(lca != NULL)
        {
            buf << " LightConstantAttenuation" << "[" << lca->getIndex() 
                << "] = " << lca->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domLight_linear_attenuationRef lla = 
            states[i]->getLight_linear_attenuation();

        if(lla != NULL)
        {
            buf << " LightLinearAttenuation" << "[" << lla->getIndex() 
                << "] = " << lla->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domLight_quadratic_attenuationRef lqa = 
            states[i]->getLight_quadratic_attenuation();

        if(lqa != NULL)
        {
            buf << " LightQuadraticAttenuation" << "[" << lqa->getIndex()
                << "] = " << lqa->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domLight_spot_cutoffRef lsc = 
            states[i]->getLight_spot_cutoff();

        if(lsc != NULL)
        {
            buf << " LightSpotCutoff" << "[" << lsc->getIndex() << "] = " 
                << lsc->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domLight_spot_exponentRef lse = 
            states[i]->getLight_spot_exponent();

        if(lse != NULL)
        {
            buf << " LightSpotExponent" << "[" << lse->getIndex() << "] = " 
                << lse->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domLight_spot_directionRef lsd = 
            states[i]->getLight_spot_direction();

        if(lsd != NULL)
        {
            domFloat3 direction = lsd->getValue();

            buf << " LightSpotDirection" << "[" << lsd->getIndex() 
                << "] = float3(" << direction[0] << "," << direction[1] 
                << "," << direction[2] << "); ";

            continue;
        }
    
        domGl_pipeline_settings::domClip_planeRef cp = 
            states[i]->getClip_plane();

        if(cp != NULL)
        {
            domFloat4 clip = cp->getValue();

            buf << " ClipPlane" << cp->getIndex() << " = float4(" << clip[0]
                << "," << clip[1] << "," << clip[2] << "," << clip[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domBlend_colorRef bc = 
            states[i]->getBlend_color();

        if(bc != NULL)
        {
            domFloat4 color = bc->getValue();

            buf << " BlendColor = float4(" << color[0] << "," << color[1] 
                << "," << color[2] << "," << color[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domClear_colorRef cc = 
            states[i]->getClear_color();

        if(cc != NULL)
        {
            domFloat4 color = cc->getValue();

            buf << " ClearColor = float4(" << color[0] << "," << color[1]
                << "," << color[2] << "," << color[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domClear_stencilRef cs = 
            states[i]->getClear_stencil();

        if(cs != NULL)
        {
            buf << " ClearStencil = " << cs->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domClear_depthRef cd = 
            states[i]->getClear_depth();

        if(cd != NULL)
        {
            buf << " ClearDepth = " << cd->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domColor_maskRef cmk = 
            states[i]->getColor_mask();

        if(cmk != NULL)
        {
            domBool4 mask = cmk->getValue();

            buf << " ColorMask = bool4(" 
                <<        ((mask[0]) ? ("true") : ("false")) 
                << "," << ((mask[1]) ? ("true") : ("false")) 
                << "," << ((mask[2]) ? ("true") : ("false")) 
                << "," << ((mask[3]) ? ("true") : ("false")) << "); ";
            continue;
        }

        domGl_pipeline_settings::domDepth_boundsRef db = 
            states[i]->getDepth_bounds();

        if(db != NULL)
        {
            domFloat2 bounds = db->getValue();

            buf << " DepthBounds = float2( " << bounds[0] << "," 
                << bounds[1] << "); ";

            continue;
        }


        domGl_pipeline_settings::domDepth_rangeRef dr = 
            states[i]->getDepth_range();

        if(dr != NULL)
        {
            domFloat2 range = dr->getValue();

            buf << " DepthRange = float2( " << range[0] << "," 
                << range[1] << "); ";    

            continue;
        }

        domGl_pipeline_settings::domFog_densityRef fd = 
            states[i]->getFog_density();

        if(fd != NULL)
        {
            buf << " FogDensity = " << fd->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domFog_startRef fs = states[i]->getFog_start();

        if(fs != NULL)
        {
            buf << " FogStart= " << fs->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domFog_endRef fe = states[i]->getFog_end();

        if(fe != NULL)
        {
            buf << " FogEnd= " << fe->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domFog_colorRef fc = states[i]->getFog_color();

        if(fc != NULL)
        {
            domFloat4 color = fc->getValue();

            buf << " FogColor = float4(" << color[0] << "," << color[1] 
                << "," << color[2] << "," << color[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domLight_model_ambientRef lma = 
            states[i]->getLight_model_ambient();

        if(lma != NULL)
        {
            domFloat4 light = lma->getValue();

            buf << " LightModelAmbient = float4(" << light[0] << "," 
                << light[1] << "," << light[2] << "," << light[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domLine_stippleRef lst = 
            states[i]->getLine_stipple();

        if(lst != NULL)
        {
            domInt2 stipple = lst->getValue();

            buf << " LineStipple = int2(" << stipple[0] << "," 
                << stipple[1] << "); ";

            continue;
        }

        domGl_pipeline_settings::domLine_widthRef lw = 
            states[i]->getLine_width();

        if(lw != NULL)
        {
            buf << " LineWidth = " << lw->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domMaterial_ambientRef mam = 
            states[i]->getMaterial_ambient();

        if(mam != NULL)
        {
            domFloat4 ambient = mam->getValue();
            buf << " MaterialAmbient = float4(" << ambient[0] << "," 
                << ambient[1] << "," << ambient[2] << "," << ambient[3] 
                << "); ";

            continue;
        }

        domGl_pipeline_settings::domMaterial_diffuseRef mdf = 
            states[i]->getMaterial_diffuse();

        if(mdf != NULL)
        {
            domFloat4 diffuse = mdf->getValue();

            buf << " MaterialDiffuse = float4(" << diffuse[0] << "," 
                << diffuse[1] << "," << diffuse[2] << "," << diffuse[3] 
                << "); ";

            continue;
        }

        domGl_pipeline_settings::domMaterial_emissionRef mem = 
            states[i]->getMaterial_emission();

        if(mem != NULL)
        {
            domFloat4 emission = mem->getValue();

            buf << " MaterialEmission = float4(" << emission[0] << "," 
                << emission[1] << "," << emission[2] << "," << emission[3] 
                << "); ";

            continue;
        }

        domGl_pipeline_settings::domMaterial_specularRef msp = 
            states[i]->getMaterial_specular();

        if(msp != NULL)
        {
            domFloat4 spec = msp->getValue();

            buf << " MaterialSpecular = float4(" << spec[0] << "," << spec[1] 
                << "," << spec[2] << "," << spec[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domMaterial_shininessRef msh = 
            states[i]->getMaterial_shininess();

        if(msh != NULL)
        {
            buf << " MaterialShininess = " << msh->getValue() << "; ";

            continue;
        }
        
        domGl_pipeline_settings::domPoint_distance_attenuationRef pda = 
            states[i]->getPoint_distance_attenuation();

        if(pda != NULL)
        {
            domFloat3 atten = pda->getValue();

            buf << " PointDistanceAttenuation = float3(" << atten[0] << "," 
                << atten[1] << "," << atten[2]  << "); ";

            continue;
        }
        
        domGl_pipeline_settings::domPoint_fade_threshold_sizeRef pfts = 
            states[i]->getPoint_fade_threshold_size();

        if(pfts != NULL)
        {
            buf << " PointFadeThresholdSize = " << pfts->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domPoint_sizeRef pts = 
            states[i]->getPoint_size();

        if(pts != NULL)
        {
            buf << " PointSize = " << pts->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domPoint_size_minRef ptsmn = 
            states[i]->getPoint_size_min();

        if(ptsmn != NULL)
        {
            buf << " PointSizeMin = " << ptsmn->getValue() << "; ";
            continue;
        }

        domGl_pipeline_settings::domPoint_size_maxRef ptsmx = 
            states[i]->getPoint_size_max();

        if(ptsmx != NULL)
        {
            buf << " PointSizeMax = " << ptsmx->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domPolygon_offsetRef po = 
            states[i]->getPolygon_offset();

        if(po != NULL)
        {
            domFloat2 offset = po->getValue();

            buf << " PolygonOffset = float2(" << offset[0] << "," 
                << offset[1] << "); ";

            continue;
        }

        domGl_pipeline_settings::domScissorRef sc = states[i]->getScissor();

        if(sc != NULL)
        {   
            domInt4 scissor = sc->getValue();

            buf << " Scissor = int4(" << scissor[0] << "," << scissor[1] << "," 
                << scissor[2] << "," << scissor[3] << "); ";

            continue;
        }

        domGl_pipeline_settings::domModel_view_matrixRef mvm = 
            states[i]->getModel_view_matrix();

        if(mvm != NULL)
        {
            domFloat4x4 mat = mvm->getValue();

            buf << " ModelViewMatrix = float4x4(" 
                << mat[0] << "," << mat[1] << mat[2] << "," << mat[2] << "," 
                << mat[2] << "," << mat[2] << "," << mat[2] << "," 
                << mat[2] << "," << mat[2] << "," << mat[2] << "," 
                << mat[2] << "," << mat[2] << "," << mat[2] << "," 
                << mat[2] << "," << mat[2] << "," << mat[2] << "); "; 

            continue;
        }

        domGl_pipeline_settings::domProjection_matrixRef pjm = 
            states[i]->getProjection_matrix();

        if(pjm != NULL)
        {
            domFloat4x4 mat = pjm->getValue();

            buf << " ProjectionMatrix = float4x4(" 
                << mat[0] << "," << mat[1] << mat[2] << "," << mat[2] << "," 
                << mat[2] << "," << mat[2] << "," << mat[2] << "," << mat[2] 
                << "," << mat[2] << "," << mat[2] << "," << mat[2] << "," 
                << mat[2] << "," << mat[2] << "," << mat[2] << "," 
                << mat[2] << "," << mat[2] << "); "; 
            continue;
        }

        domGl_pipeline_settings::domStencil_maskRef stm = 
            states[i]->getStencil_mask();

        if(stm != NULL)
        {
            buf << " StencilMask = " << stm->getValue() << "; ";

            continue;
        }

        domGl_pipeline_settings::domClip_plane_enableRef cpe = 
            states[i]->getClip_plane_enable();

        if(cpe != NULL)
        {
            buf << getBoolStringRep("ClipPlaneEnable",
                                    cpe->getIndex(),
                                    cpe->getValue());

            continue;
        }

        domGl_pipeline_settings::domLight_enableRef le = 
            states[i]->getLight_enable();

        if(le != NULL)
        {
            buf << getBoolStringRep("LightEnable", 
                                    le->getIndex(),
                                    le->getValue());

            continue;
        }

        domGl_pipeline_settings::domLighting_enableRef len = 
            states[i]->getLighting_enable();

        if(len != NULL)
        {
            buf << getBoolStringRep("LightingEnable", len->getValue());

            continue;
        }

        domGl_pipeline_settings::domDepth_test_enableRef dte = 
            states[i]->getDepth_test_enable();

        if(dte != NULL)
        {
            buf << getBoolStringRep("DepthTestEnable", dte->getValue());

            continue;
        }

        domGl_pipeline_settings::domAlpha_test_enableRef ate = 
            states[i]->getAlpha_test_enable();

        if(ate != NULL)
        {
            buf << getBoolStringRep("AlphaTestEnable", ate->getValue());

            continue;
        }

        domGl_pipeline_settings::domAuto_normal_enableRef ane = 
            states[i]->getAuto_normal_enable();

        if(ane != NULL)
        {
            buf << getBoolStringRep("AutoNormalEnable", ane->getValue());

            continue;
        }

        domGl_pipeline_settings::domColor_logic_op_enableRef cloe = 
            states[i]->getColor_logic_op_enable();

        if(cloe != NULL)
        {
            buf << getBoolStringRep("ColorLogicOpEnable", cloe->getValue());

            continue;
        }

        domGl_pipeline_settings::domColor_material_enableRef cme = 
            states[i]->getColor_material_enable();

        if(cme != NULL)
        {
            buf << getBoolStringRep("ColorMaterialEnable", cme->getValue());

            continue;
        }

        domGl_pipeline_settings::domBlend_enableRef be = 
            states[i]->getBlend_enable();

        if(be != NULL)
        {
            buf << getBoolStringRep("BlendEnable", be->getValue());

            continue;
        }

        domGl_pipeline_settings::domCull_face_enableRef cfe = 
            states[i]->getCull_face_enable();

        if(cfe != NULL)
        {
            buf << getBoolStringRep("CullFaceEnable", cfe->getValue());

            continue;
        }

        domGl_pipeline_settings::domDepth_bounds_enableRef dbe = 
            states[i]->getDepth_bounds_enable();

        if(dbe != NULL)
        {
            buf << getBoolStringRep("DepthBoundsEnable", dbe->getValue());

            continue;
        }

        domGl_pipeline_settings::domDither_enableRef dthe = 
            states[i]->getDither_enable();

        if(dthe != NULL)
        {
            buf << getBoolStringRep("DitherEnable", dthe->getValue());

            continue;
        }

        domGl_pipeline_settings::domFog_enableRef foge = 
            states[i]->getFog_enable();

        if(foge != NULL)
        {
            buf << getBoolStringRep("FogEnable", foge->getValue());

            continue;
        }

        domGl_pipeline_settings::domLight_model_local_viewer_enableRef lmlve = 
            states[i]->getLight_model_local_viewer_enable();

        if(lmlve != NULL)
        {
            buf << getBoolStringRep("LightModelLocalViewerEnable", 
                                    lmlve->getValue());

            continue;
        }

        domGl_pipeline_settings::domLight_model_two_side_enableRef lmtse = 
            states[i]->getLight_model_two_side_enable();

        if(lmtse != NULL)
        {
            buf << getBoolStringRep("LightModelTwoSideEnable", 
                                    lmtse->getValue());

            continue;
        }

        domGl_pipeline_settings::domLine_smooth_enableRef lnse = 
            states[i]->getLine_smooth_enable();

        if(lnse != NULL)
        {
            buf << getBoolStringRep("LineSmoothEnable", lnse->getValue());

            continue;
        }

        domGl_pipeline_settings::domLine_stipple_enableRef lnste = 
            states[i]->getLine_stipple_enable();

        if(lnste != NULL)
        {
            buf << getBoolStringRep("LineStippleEnable", lnste->getValue());

            continue;
        }

        domGl_pipeline_settings::domLogic_op_enableRef lope = 
            states[i]->getLogic_op_enable();

        if(lope != NULL)
        {
            buf << getBoolStringRep("LogicOpEnable", lope->getValue());

            continue;
        }

        domGl_pipeline_settings::domMultisample_enableRef mse = 
            states[i]->getMultisample_enable();

        if(mse != NULL)
        {
            buf << getBoolStringRep("MultisampleEnable", mse->getValue());
            continue;
        }

        domGl_pipeline_settings::domNormalize_enableRef nme = 
            states[i]->getNormalize_enable();

        if(nme != NULL)
        {
            buf << getBoolStringRep("NormalizeEnable", nme->getValue());
            continue;
        }

        domGl_pipeline_settings::domPoint_smooth_enableRef ptse = 
            states[i]->getPoint_smooth_enable();

        if(ptse != NULL)
        {
            buf << getBoolStringRep("PointSmoothEnable", ptse->getValue());

            continue;
        }

        domGl_pipeline_settings::domPolygon_offset_fill_enableRef pofe = 
            states[i]->getPolygon_offset_fill_enable();

        if(pofe != NULL)
        {
            buf << getBoolStringRep("PolygonOffsetFillEnable", 
                                    pofe->getValue());

            continue;
        }

        domGl_pipeline_settings::domPolygon_offset_line_enableRef pole = 
            states[i]->getPolygon_offset_line_enable();

        if(pole != NULL)
        {
            buf << getBoolStringRep("PolygonOffsetLineEnable", 
                                    pole->getValue());

            continue;
        }

        domGl_pipeline_settings::domPolygon_offset_point_enableRef pope = 
            states[i]->getPolygon_offset_point_enable();

        if(pope != NULL)
        {
            buf << getBoolStringRep("PolygonOffsetPointEnable", 
                                    pope->getValue());

            continue;
        }

        domGl_pipeline_settings::domPolygon_smooth_enableRef pse = 
            states[i]->getPolygon_smooth_enable();

        if(pse != NULL)
        {
            buf << getBoolStringRep("PolygonSmoothEnable", pse->getValue());

            continue;
        }

        domGl_pipeline_settings::domPolygon_stipple_enableRef pste = 
            states[i]->getPolygon_stipple_enable();

        if(pste != NULL)
        {
            buf << getBoolStringRep("PolygonStippleEnable", pste->getValue());

            continue;
        }

        domGl_pipeline_settings::domRescale_normal_enableRef rne  = 
            states[i]->getRescale_normal_enable();

        if(rne != NULL)
        {
            buf << getBoolStringRep("RescaleNormalEnable", rne->getValue());

            continue;
        }

        domGl_pipeline_settings::domSample_alpha_to_coverage_enableRef satce = 
            states[i]->getSample_alpha_to_coverage_enable();

        if(satce != NULL)
        {
            buf << getBoolStringRep("SampleAlphaToCoverageEnable", 
                                    satce->getValue());

            continue;
        }

        domGl_pipeline_settings::domSample_alpha_to_one_enableRef satoe = 
            states[i]->getSample_alpha_to_one_enable();

        if(satoe != NULL)
        {
            buf << getBoolStringRep("SampleAlphaToOneEnable", 
                                    satoe->getValue());

            continue;
        }

        domGl_pipeline_settings::domSample_coverage_enableRef sce = 
            states[i]->getSample_coverage_enable();

        if(sce != NULL)
        {
            buf << getBoolStringRep("SampleCoverageEnable", sce->getValue());

            continue;
        }

        domGl_pipeline_settings::domScissor_test_enableRef scte = 
            states[i]->getScissor_test_enable();

        if(scte != NULL)
        {
            buf << getBoolStringRep("ScissorTestEnable", scte->getValue());

            continue;
        }

        domGl_pipeline_settings::domStencil_test_enableRef stte  = 
            states[i]->getStencil_test_enable();

        if(stte != NULL)
        {
            buf << getBoolStringRep("StencilTestEnable", stte->getValue());

            continue;
        }

        domGl_pipeline_settings::domTexture1D_enableRef t1de  = 
            states[i]->getTexture1D_enable();

        if(t1de != NULL)
        {
            buf << getBoolStringRep("Texture1DEnable", 
                                    t1de->getIndex(),
                                    t1de->getValue());

            continue;
        }

        domGl_pipeline_settings::domTexture2D_enableRef t2de  = 
            states[i]->getTexture2D_enable();

        if(t2de != NULL)
        {
            buf << getBoolStringRep("Texture2DEnable", 
                                    t2de->getIndex(),
                                    t2de->getValue());

            continue;
        }

        domGl_pipeline_settings::domTexture3D_enableRef t3de = 
            states[i]->getTexture3D_enable();

        if(t3de != NULL)
        {
            buf << getBoolStringRep("Texture3DEnable", 
                                    t3de->getIndex(), 
                                    t3de->getValue());

            continue;
        }

        domGl_pipeline_settings::domTextureRECT_enableRef trde = 
            states[i]->getTextureRECT_enable();

        if(trde != NULL)
        {
            buf << getBoolStringRep("TextureRectangleEnable", 
                                    trde->getIndex(), 
                                    trde->getValue());

            continue;
        }

        domGl_pipeline_settings::domTextureCUBE_enableRef tcme  = 
            states[i]->getTextureCUBE_enable();

        if(tcme != NULL)
        {
            buf << getBoolStringRep("TextureCubeMapEnable", 
                                    tcme->getIndex(), 
                                    tcme->getValue());

            continue;
        }

        buf << std::endl;
    } // end for(states.getCount())

    return buf.str();
}


OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
