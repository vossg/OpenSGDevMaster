/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

OSG_BEGIN_NAMESPACE

inline ColladaEffectTransitPtr ColladaEffect::create(
    domEffect *effect, ColladaGlobal *global)
{
    return ColladaEffectTransitPtr(new ColladaEffect(effect, global));
}

inline ChunkMaterial *ColladaEffect::getMaterial(void)
{
    return _material;
}

inline void ColladaEffect::setTexCoordMapping(
    UInt32 texCoord, const std::string &mappedTC)
{
    if(texCoord >= _texCoordMapping.size())
    {
        _texCoordMapping.resize(texCoord + 1);
    }
    
    _texCoordMapping[texCoord] = mappedTC;
}

/*! Computes a luminance value from the red, green and blue component of a
    color per the Collada Spec.
 */
inline Real32 ColladaEffect::computeLuminance(
    Real32 colR, Real32 colG, Real32 colB)
{
    return colR * 0.212671 + colG * 0.71516 + colB * 0.072169;
}

inline void ColladaEffect::fillElements(
    domCommon_color_or_texture_type                *colTexIn,
    domCommon_color_or_texture_type::domColorRef   &colOut,
    domCommon_color_or_texture_type::domTextureRef &texOut   )
{
    if(colTexIn != NULL)
    {
        colOut = colTexIn->getColor  ();
        texOut = colTexIn->getTexture();
    }
}

inline void ColladaEffect::fillElements(
    domCommon_transparent_type                     *colTexIn,
    domCommon_color_or_texture_type::domColorRef   &colOut,
    domCommon_color_or_texture_type::domTextureRef &texOut   )
{
    if(colTexIn != NULL)
    {
        colOut = colTexIn->getColor  ();
        texOut = colTexIn->getTexture();
    }
}

OSG_END_NAMESPACE
