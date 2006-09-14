/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include <OSGConfig.h>

#include <ctype.h>
#include <string>
#include <sstream>

#include "OSGNFIOOptions.h"
#include "OSGNFIOQuantizer.h"

#include "OSGLog.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NFIOOptions
           parses the reader/writer options.
 */

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOOptions::NFIOOptions(void) :
_inlineTextures(true),
_compressTextures(false),
_texturesCompressionQuality(75),
_quantizePositions(Quantizer::QRES_OFF),
_quantizeNormals(Quantizer::QRES_OFF),
_quantizeTexCoords(Quantizer::QRES_OFF),
_packIndices(false),
_unpack16BitIndices(true)
{
}

/*------------------------------ destructor -------------------------------*/

NFIOOptions::~NFIOOptions(void)
{
}

/*------------------------------ init------ -------------------------------*/

void NFIOOptions::init(const std::string &options)
{
    // init default parameters
    _inlineTextures = true;
    _compressTextures = false;
    _texturesCompressionQuality = 75;
    _quantizePositions = Quantizer::QRES_OFF;
    _quantizeNormals = Quantizer::QRES_OFF;
    _quantizeTexCoords = Quantizer::QRES_OFF;
    _packIndices = false;
    _unpack16BitIndices = false;
    
    std::string option;
    std::string::size_type i = 0;

    // parse options
    if(options.find("inlineTextures=true") != std::string::npos)
        _inlineTextures = true;
    if(options.find("inlineTextures=false") != std::string::npos)
        _inlineTextures = false;
    
    if(options.find("compressTextures=true") != std::string::npos)
        _compressTextures = true;
    if(options.find("compressTextures=false") != std::string::npos)
        _compressTextures = false;
    
    option = "texturesCompressionQuality=";
    if((i=options.find(option)) != std::string::npos)
        _texturesCompressionQuality = getInteger(options.substr(i+option.size()));
    
    if(options.find("quantizePositions=0") != std::string::npos)
        _quantizePositions = Quantizer::QRES_OFF;
    if(options.find("quantizePositions=8") != std::string::npos)
        _quantizePositions = Quantizer::QRES_8BIT;
    if(options.find("quantizePositions=16") != std::string::npos)
        _quantizePositions = Quantizer::QRES_16BIT;
    if(options.find("quantizePositions=24") != std::string::npos)
        _quantizePositions = Quantizer::QRES_24BIT;
    
    if(options.find("quantizeNormals=0") != std::string::npos)
        _quantizeNormals = Quantizer::QRES_OFF;
    if(options.find("quantizeNormals=8") != std::string::npos)
        _quantizeNormals = Quantizer::QRES_8BIT;
    if(options.find("quantizeNormals=16") != std::string::npos)
        _quantizeNormals = Quantizer::QRES_16BIT;
    if(options.find("quantizeNormals=24") != std::string::npos)
        _quantizeNormals = Quantizer::QRES_24BIT;
    
    if(options.find("quantizeTexCoords=0") != std::string::npos)
        _quantizeTexCoords = Quantizer::QRES_OFF;
    if(options.find("quantizeTexCoords=8") != std::string::npos)
        _quantizeTexCoords = Quantizer::QRES_8BIT;
    if(options.find("quantizeTexCoords=16") != std::string::npos)
        _quantizeTexCoords = Quantizer::QRES_16BIT;
    if(options.find("quantizeTexCoords=24") != std::string::npos)
        _quantizeTexCoords = Quantizer::QRES_24BIT;
    
    if(options.find("packIndices=true") != std::string::npos)
        _packIndices = true;
    if(options.find("packIndices=false") != std::string::npos)
        _packIndices = false;

    if(options.find("unpack16BitIndices=true") != std::string::npos)
        _unpack16BitIndices = true;
    if(options.find("unpack16BitIndices=false") != std::string::npos)
        _unpack16BitIndices = false;
}

/*------------------------------ options--- -------------------------------*/

bool NFIOOptions::inlineTextures(void) const
{
    return _inlineTextures;
}

bool NFIOOptions::compressTextures(void) const
{
    return _compressTextures;
}

UInt32 NFIOOptions::texturesCompressionQuality(void) const
{
    return _texturesCompressionQuality;
}

UInt8 NFIOOptions::quantizePositions(void) const
{
    return _quantizePositions;
}

UInt8 NFIOOptions::quantizeNormals(void) const
{
    return _quantizeNormals;
}

UInt8 NFIOOptions::quantizeTexCoords(void) const
{
    return _quantizeTexCoords;
}

bool NFIOOptions::packIndices(void) const
{
    return _packIndices;
}

bool NFIOOptions::unpack16BitIndices(void) const
{
    return _unpack16BitIndices;
}

/*------------------------ helper functions ------------------------------*/

Int32 NFIOOptions::getInteger(const std::string &str)
{
    std::stringstream ss;
    UInt32 i = 0;
    while(i < str.length() && str[i] != ',' &&
          (isdigit(str[i]) || str[i] == '-'))
    {
        ss << str[i++];
    }
    Int32 r;
    ss >> r;
    return r;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGNFIOOPTIONS_HEADER_CVSID;
}
