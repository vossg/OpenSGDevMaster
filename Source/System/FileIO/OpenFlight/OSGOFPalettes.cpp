/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGOFPalettes.h"

#include "OSGOFAncillaryRecords.h"
#include "OSGOpenFlightLog.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------
// OFVertexPalette
//---------------------------------------------------------------------

OFVertexPalette::OFVertexPalette(void) :
     Inherited     (    ),
    _pVertexPalette(NULL)
{
}

OFVertexPalette::~OFVertexPalette(void)
{
    _pVertexPalette = NULL;
}

void OFVertexPalette::addRecord(OFVertexPaletteRecord *pVertexPal)
{
    if(_pVertexPalette == NULL)
    {
        _pVertexPalette = pVertexPal;
    }
    else
    {
        FFATAL(("OFVertexPalette::addRecord: VertexPaletteRecord "
                "already present\n"));
    }
}

const OFVertexPaletteRecord *OFVertexPalette::getRecord(void)
{
    return _pVertexPalette;
}

void OFVertexPalette::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "VertexPalette : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    if(_pVertexPalette != NULL)
        _pVertexPalette->dump(uiIndent);

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

//---------------------------------------------------------------------
// OFTexturePalette
//---------------------------------------------------------------------

OFTexturePalette::OFTexturePalette(void) :
    _mTextures()
{
}

OFTexturePalette::~OFTexturePalette(void)
{
    TextureStoreIt tIt  = _mTextures.begin();
    TextureStoreIt tEnd = _mTextures.end  ();

    while(tIt != tEnd)
    {
        tIt->second = NULL;

        ++tIt;
    }

    _mTextures.clear();
}

void OFTexturePalette::addRecord(OFTexturePaletteRecord *pTex)
{
    if(pTex != NULL)
    {
        TextureStoreIt tIt = _mTextures.find(pTex->getPatternIdx());

        if(tIt == _mTextures.end())
        {
            _mTextures[pTex->getPatternIdx()] = pTex;
        }
        else
        {
            FFATAL(("OFTexturePalette::addRecord: Texture with idx [%d] "
                    "already present.\n", pTex->getPatternIdx()));
        }
    }
}

const OFTexturePaletteRecord *OFTexturePalette::getRecord(Int32 uiId)
{
    const OFTexturePaletteRecord *returnValue = NULL;

    TextureStoreIt tIt = _mTextures.find(uiId);

    if(tIt != _mTextures.end())
    {
        returnValue = tIt->second;
    }

    return returnValue;
}

void OFTexturePalette::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "TexturePalette : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    TextureStoreIt tIt  = _mTextures.begin();
    TextureStoreIt tEnd = _mTextures.end  ();

    for(; tIt != tEnd; ++tIt)
    {
        tIt->second->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

//---------------------------------------------------------------------
// OFMaterialPalette
//---------------------------------------------------------------------

OFMaterialPalette::~OFMaterialPalette(void)
{
    // nothing to do
}

OFMaterialPalette::OFMaterialPalette(void) :
    Inherited  (),
    _mMaterials()
{
    // nothing to do
}

void OFMaterialPalette::addRecord(OFMaterialPaletteRecord *pMat)
{
    if(pMat != NULL)
    {
        MaterialStoreIt mIt = _mMaterials.find(pMat->getMaterialIdx());

        if(mIt == _mMaterials.end())
        {
            _mMaterials[pMat->getMaterialIdx()] = pMat;
        }
        else
        {
            FFATAL(("OFMaterialPalette::addRecord: Material with idx [%d] "
                    "already present.\n", pMat->getMaterialIdx()));
        }
    }
}

const OFMaterialPaletteRecord *OFMaterialPalette::getRecord(Int32 uiId)
{
    const OFMaterialPaletteRecord *returnValue = NULL;

    MaterialStoreIt mIt = _mMaterials.find(uiId);

    if(mIt != _mMaterials.end())
    {
        returnValue = mIt->second;
    }

    return returnValue;
}

void OFMaterialPalette::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "MaterialPalette : " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    uiIndent += 2;

    MaterialStoreIt mIt  = _mMaterials.begin();
    MaterialStoreIt mEnd = _mMaterials.end  ();

    for(; mIt != mEnd; ++mIt)
        mIt->second->dump(uiIndent);

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

OSG_END_NAMESPACE
