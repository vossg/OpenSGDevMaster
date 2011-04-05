/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
void ShaderVariableFunctor::setFunctor(ProcVarFunctor pFunc)
{
    _pFunc = pFunc;

#ifdef OSG_1_COMPAT
    _uiFuncMode = 0;
#endif
}

inline
void ShaderVariableFunctor::setFunctor(ProcVarNodeFunctor pFunc)
{
    _pNodeFunc = pFunc;

#ifdef OSG_1_COMPAT
    _uiFuncMode = 0;
#endif
}


#ifdef OSG_1_COMPAT
inline
void ShaderVariableFunctor::setFunctor(ParamFunctor pPFunc)
{
    _pPFunc = pPFunc;
    
    _uiFuncMode = 1;
}

inline
void ShaderVariableFunctor::setFunctor (OSGParamFunctor pOSGPFunc)
{
    _pOSGPFunc = pOSGPFunc;

    _uiFuncMode = 2;
}

inline
UInt32 ShaderVariableFunctor::getFuncMode(void)
{
    return _uiFuncMode;
}
#endif

inline
void ShaderVariableFunctor::evaluate(DrawEnv *pEnv,
                                     Int32   &iLocation)
{
    if(_pFunc)
    {
        _pFunc(pEnv, iLocation);
    }

    if(_pNodeFunc)
    {
        _pNodeFunc(pEnv, iLocation, pEnv->getSGNode());
    }
}

#ifdef OSG_1_COMPAT
inline
void ShaderVariableFunctor::evaluate(GetUniformLocProc  getULoc,
                                     DrawEnv           *pEnv,
                                     UInt32             uiProg )
{
    if(_pPFunc)
    {
        _pPFunc(getULoc, pEnv, uiProg);
    }
}

inline
void ShaderVariableFunctor::evaluate(ShaderVariable    *pVar,
                                     DrawEnv           *pEnv,
                                     UInt32             uiProg)
{
    if(_pOSGPFunc)
    {
        _pOSGPFunc(pVar, pEnv, uiProg);
    }
}
#endif

OSG_END_NAMESPACE
