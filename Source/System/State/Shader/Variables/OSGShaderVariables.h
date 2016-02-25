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

#ifndef _OSGSHADERVARIABLES_H_
#define _OSGSHADERVARIABLES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderVariableBool.h"
#include "OSGShaderVariableInt.h"
#include "OSGShaderVariableUInt.h"
#include "OSGShaderVariableReal.h"

#include "OSGShaderVariableVec2f.h"
#include "OSGShaderVariableVec3f.h"
#include "OSGShaderVariableVec4f.h"

#include "OSGShaderVariablePnt2f.h"
#include "OSGShaderVariablePnt3f.h"

#include "OSGShaderVariableMatrix.h"

#include "OSGShaderVariableMInt.h"
#include "OSGShaderVariableMUInt.h"
#include "OSGShaderVariableMReal.h"

#include "OSGShaderVariableMVec2f.h"
#include "OSGShaderVariableMVec3f.h"
#include "OSGShaderVariableMVec4f.h"

#include "OSGShaderVariableMMatrix.h"

#include "OSGShaderVariableOSG.h"

#include "OSGShaderVariableUniformBlock.h"
#include "OSGShaderVariableShaderStorageBlock.h"

#include "OSGGLFuncProtos.h"
#include "OSGShaderProgram.h"

OSG_BEGIN_NAMESPACE

OSG_SYSTEM_DLLMAPPING
void osgUniformShaderVariableSwitch  (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableLocation(DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram  );

void osgUniformShaderVariableBool    (DrawEnv        *pEnv,   
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableInt     (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableUInt    (DrawEnv        *pEnv,
                                      ShaderVariable *pVar,
                                      Int32          &loc,
                                      UInt32          uiProgram,
                                      bool            warnUnknown);

void osgUniformShaderVariableReal    (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableVec2f   (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableVec3f   (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableVec4f   (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariablePnt2f   (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariablePnt3f   (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableMatrix  (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableMInt    (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableMUInt   (DrawEnv        *pEnv,
                                      ShaderVariable *pVar,
                                      Int32          &loc,
                                      UInt32          uiProgram,
                                      bool            warnUnknown);

void osgUniformShaderVariableMReal   (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableMVec2f  (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableMVec3f  (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableMVec4f  (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderVariableMMatrix (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,  
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderUniformBlockLocation
                                     (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram  );

void osgUniformShaderUniformBlockBinding
                                     (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,  
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

void osgUniformShaderStorageBlockLocation
                                     (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,       
                                      Int32          &loc,
                                      UInt32          uiProgram  );

void osgUniformShaderStorageBlockBinding
                                     (DrawEnv        *pEnv,      
                                      ShaderVariable *pVar,  
                                      Int32          &loc,
                                      UInt32          uiProgram, 
                                      bool            warnUnknown);

OSG_END_NAMESPACE

#include "OSGShaderVariables.inl"

#endif // _OSGSHADERVARIABLES_H_
