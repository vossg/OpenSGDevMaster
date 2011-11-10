/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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
TextureObjChunk *PostShaderStage::RenderPassData::getOutputTexture(void) const
{
    return _pOutputTexture;
}

inline
bool PostShaderStage::RenderPassData::getIsLastPass(void) const
{
    return _bIsLassPass;
}

inline
SimpleSHLChunk *PostShaderStage::RenderPassData::getShader(void) const
{
    return _pShader;
}

inline
std::string PostShaderStage::RenderPassData::getOutputTextureName(void) const
{
    return (PostShaderStage::PrePassXName              +
            boost::lexical_cast<std::string>(_uiIndex) +
            PostShaderStage::PostPassXColorTexName     ); 
}

inline
std::string PostShaderStage::RenderPassData::getWidthName(void) const
{
    return (PostShaderStage::PrePassXName              +
            boost::lexical_cast<std::string>(_uiIndex) +
            PostShaderStage::PostPassXColorWidthName   );
}

inline
std::string PostShaderStage::RenderPassData::getHeightName(void) const
{
    return (PostShaderStage::PrePassXName              +
            boost::lexical_cast<std::string>(_uiIndex) +
            PostShaderStage::PostPassXColorHeightName);
}

inline
UInt32 PostShaderStage::RenderPassData::getIndex(void) const
{
    return _uiIndex;
}

inline
UInt32 PostShaderStage::getNumPasses(void) const
{
    return getMFVertexShaders()->size();
}

inline
void PostShaderStage::insertPass(      UInt32       uiIndex,
                                 const std::string &szVertexProgram,
                                 const std::string &szFragmentProgram,
                                       Vec2f        vSize            )
{
    editMFVertexShaders  ()->insert(uiIndex, szVertexProgram  );
    editMFFragmentShaders()->insert(uiIndex, szFragmentProgram);

    editMFPassSizes      ()->push_back(vSize);
}

inline
void PostShaderStage::addPass(const std::string &szVertexProgram,
                              const std::string &szFragmentProgram,
                                    Vec2f        vSize)
{
    editMFVertexShaders  ()->push_back(szVertexProgram  );
    editMFFragmentShaders()->push_back(szFragmentProgram);

    editMFPassSizes      ()->push_back(vSize);
}

inline
void PostShaderStage::clearPasses(void)
{
    editMFVertexShaders  ()->clear();
    editMFFragmentShaders()->clear();
    editMFPassSizes      ()->clear();
}

inline
void PostShaderStage::erasePass(UInt32 Index)
{
    editMFVertexShaders  ()->erase(Index);
    editMFFragmentShaders()->erase(Index);
    editMFPassSizes      ()->erase(Index);
}

inline
SimpleSHLChunk *PostShaderStage::getPassShader(UInt32 Index) const
{
    return _vPostProcessPasses[Index]->getShader();
}

OSG_END_NAMESPACE
