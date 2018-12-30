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

#ifdef _MSC_VER
# pragma warning (disable: 4786)
#endif

#if __GNUC__ > 4 || (__GNUC__ >= 4 && __GNUC_MINOR__ >=8)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include "OSGTextFT2Backend.h"
#include "OSGBaseTypes.h"


#if defined(OSG_WITH_FT2) || defined(OSG_DO_DOC)


#include "OSGTextPixmapFace.h"
#include "OSGTextPixmapGlyph.h"
#include "OSGTextVectorFace.h"
#include "OSGTextVectorGlyph.h"
#include "OSGTextTXFFace.h"
#include "OSGTextTXFGlyph.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"

#include <iostream>
#include <algorithm>
#include <set>
#ifdef OSG_WITH_FONTCONFIG
# include <fontconfig/fontconfig.h>
#else
# ifdef _WIN32
#  include <windows.h>
# else
#  include <dirent.h>
# endif
#endif

// ?????
#ifdef _MSC_VER
# include <freetype/ftoutln.h>
#else
# include FT_OUTLINE_H
#endif

using namespace std;
OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Freetype2 specific implementation of the TextVectorFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextFT2VectorFace: public TextVectorFace
{
  public:

    // Constructor
    TextFT2VectorFace(FT_Face face);

    // Destructor
    virtual ~TextFT2VectorFace();

    // Lays out one line of text
    virtual void layout(const wstring &text, const TextLayoutParam &param,
                        TextLayoutResult &layoutResult);

  protected:

    // Creates a new Glyph object
    virtual unique_ptr<TextVectorGlyph> createGlyph(TextGlyph::Index glyphIndex);

  private:

    // Freetype face object
    FT_Face _face;

    TextFT2VectorFace(const TextFT2VectorFace &other);
    void operator =(const TextFT2VectorFace &rhs);
};


//----------------------------------------------------------------------
// Freetype2 specific implementation of the TextVectorGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextFT2VectorGlyph: public TextVectorGlyph
{
public:

    // Constructor
    TextFT2VectorGlyph(Index glyphIndex, Real32 scale, FT_GlyphSlot glyphSlot);

    // Destructor
    virtual ~TextFT2VectorGlyph();
};


//----------------------------------------------------------------------
// Freetype2 specific implementation of the TextPixmapFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextFT2PixmapFace: public TextPixmapFace
{
  public:

    // Constructor
    TextFT2PixmapFace(FT_Face face, UInt32 size);

    // Destructor
    virtual ~TextFT2PixmapFace();

    // Lays out one line of text
    virtual void layout(const wstring &text, const TextLayoutParam &param,
                        TextLayoutResult &layoutResult);

  protected:

    // Creates a new Glyph object
    virtual unique_ptr<TextPixmapGlyph> createGlyph(TextGlyph::Index glyphIndex);

  private:
    
    // Freetype face object
    FT_Face _face;

    TextFT2PixmapFace(const TextFT2PixmapFace &other);
    void operator =(const TextFT2PixmapFace &rhs);
};


//----------------------------------------------------------------------
// Freetype2 specific implementation of the TextPixmapGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextFT2PixmapGlyph: public TextPixmapGlyph
{
public:

    // Constructor
    TextFT2PixmapGlyph(Index glyphIndex, TextFT2PixmapFace *face, FT_GlyphSlot glyphSlot);

    // Destructor
    virtual ~TextFT2PixmapGlyph();
};


//----------------------------------------------------------------------
// Freetype2 specific implementation of the TextTXFFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextFT2TXFFace: public TextTXFFace
{
public:

    // Constructor
    TextFT2TXFFace(FT_Face face, const TextTXFParam &param);

    // Destructor
    virtual ~TextFT2TXFFace();
};


//----------------------------------------------------------------------
// Freetype2 specific implementation of the TextTXFGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextFT2TXFGlyph: public TextTXFGlyph
{
public:

    // Constructor
    TextFT2TXFGlyph(Index glyphIndex, TextFT2TXFFace *face,
                    Real32 scale, FT_GlyphSlot glyphSlot);

    // Destructor
    virtual ~TextFT2TXFGlyph();
};


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2Backend::TextFT2Backend()
    : TextBackend(),
      _library  (0)
#ifndef OSG_WITH_FONTCONFIG
  ,
# ifdef FONT_SEARCHPATH
      _pathList(FONT_SEARCHPATH),
#else
      _pathList(),
#endif
      _scanForFonts(true),
      _fontMap()
#endif
{
    // Initialize Freetype library
    FT_Error error = FT_Init_FreeType(&_library);
    if (error)
    {
        // There is not much we can do here when we cannot initialize
        // the library - we simply will not be able to create any font
        SWARNING << "TextFT2Backend: Failed to initialize freetype library."
                 << std::endl;

        _library = 0;
    }

#ifdef OSG_WITH_FONTCONFIG

    // Initialize FontConfig library
    FcBool fcSuccess = FcInit();

    if(fcSuccess != FcTrue)
    {
        // Same as above, not much we can do
        SWARNING << "TextFT2Backend: Failed to initialize fontconfig library."
                 << std::endl;
    }

#endif // OSG_WITH_FONTCONFIG

}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2Backend::~TextFT2Backend()
{
    // Deinitialize Freetype library
    if (_library != 0)
        FT_Done_FreeType(_library);

#ifdef OSG_WITH_FONTCONFIG

    // Deinitialize FontConfig library
    // Hmmm, this is mentioned in the documentation, but nowhere
    // defined in the header files (at least for my version of the
    // library)
    //FcFini();

#endif // OSG_WITH_FONTCONFIG
}


//----------------------------------------------------------------------
// Tries to find the path and the index of a font
// Author: pdaehne
//----------------------------------------------------------------------
bool TextFT2Backend::findPath(const string &family, TextFace::Style style,
                              string &path, int &index)
{
    // Initialize result values
    path.erase();
    index = -1;

#ifdef OSG_WITH_FONTCONFIG

    // Handle generic family names
    string f;
    if (family == "SERIF")
        f = "serif";
    else if (family == "SANS")
        f = "sans-serif";
    else if (family == "TYPEWRITER")
        f = "monospace";
    else
        f = family;

    // Create FontConfig search pattern
    FcPattern *pattern = FcPatternCreate();
    if (pattern == 0)
        return false;

    // We are only interested in outline fonts
    if (FcPatternAddBool(pattern, FC_OUTLINE, FcTrue) == FcFalse)
    {
        FcPatternDestroy(pattern);
        return false;
    }

    // Set font family
    if (FcPatternAddString(pattern, 
                           FC_FAMILY, 
                           reinterpret_cast<
                               const FcChar8*>(f.c_str())) == FcFalse)
    {
        FcPatternDestroy(pattern);
        return false;
    }

    // Set style
    int slant;
    int weight;
    switch (style)
    {
    default:
        FWARNING(("Invalid font style parameter.\n"));
        // intentionally fall through
    case TextFace::STYLE_PLAIN:
        slant = FC_SLANT_ROMAN;
        weight = FC_WEIGHT_MEDIUM;
        break;
    case TextFace::STYLE_BOLD:
        slant = FC_SLANT_ROMAN;
        weight = FC_WEIGHT_BOLD;
        break;
    case TextFace::STYLE_ITALIC:
        slant = FC_SLANT_ITALIC;
        weight = FC_WEIGHT_MEDIUM;
        break;
    case TextFace::STYLE_BOLDITALIC:
        slant = FC_SLANT_ITALIC;
        weight = FC_WEIGHT_BOLD;
        break;
    }
    if (FcPatternAddInteger(pattern, FC_SLANT, slant) == FcFalse)
    {
        FcPatternDestroy(pattern);
        return false;
    }
    if (FcPatternAddInteger(pattern, FC_WEIGHT, weight) == FcFalse)
    {
        FcPatternDestroy(pattern);
        return false;
    }

    // Do some magic stuff... Taken from FontConfig example programs
    if (FcConfigSubstitute(0, pattern, FcMatchPattern) == FcFalse)
    {
        FcPatternDestroy(pattern);
        return false;
    }
    FcDefaultSubstitute(pattern);

    // Search for a matching font
    FcResult result;
    FcPattern *match = FcFontMatch(0, pattern, &result);
    // We do not need the search pattern any more
    FcPatternDestroy(pattern);
    if (match == 0)
        return false;

    // Get path to font file
    FcChar8 *pathPtr;
    if (FcPatternGetString(match, FC_FILE, 0, &pathPtr) != FcResultMatch)
    {
        FcPatternDestroy(match);
        return false;
    }
    path = reinterpret_cast<const char *>(pathPtr);

    // Get index of face in the font file
    if (FcPatternGetInteger(match, FC_INDEX, 0, &index) != FcResultMatch)
    {
        FcPatternDestroy(match);
        return false;
    }

    // Destroy the match pattern
    FcPatternDestroy(match);

#else // !OSG_WITH_FONTCONFIG

    // Scan the font search path for fonts
    scanForFonts();

    // Try to find a matching font
    FontMap::const_iterator it, bestMatchIt = _fontMap.end();
    pair<FontMap::const_iterator, FontMap::const_iterator> range;
    //string f = family;
    //transform(f.begin(), f.end(), f.begin(), ::tolower);
    range = _fontMap.equal_range(/*f*/family);
    for (it = range.first; it != range.second; ++it)
    {
        if (it->second.style == style)
        {
            bestMatchIt = it;
            break;
        }
    }
    if (bestMatchIt == _fontMap.end())
        return false;
    path = bestMatchIt->second.path;
    index = bestMatchIt->second.index;

#endif // !OSG_WITH_FONTCONFIG

    return true;
}


//----------------------------------------------------------------------
// Tries to create a freetype2 face
// Author: pdaehne
//----------------------------------------------------------------------
FT_Face TextFT2Backend::createFace(const string &family, TextFace::Style style, FT_UInt size)
{
    // Check if we have a valid freetype2 library handle
    if (_library == 0)
        return 0;

    // Try to find the path and the index of a font
    string path;
    int index;
    if (findPath(family, style, path, index) == false)
        return 0;

    // Try to open the font file
    FT_Face face;
    FT_Error error = FT_New_Face(_library, path.c_str(), index, &face);
    if (error)
        return 0;

    // Does this Face have a family name?
    // If not, just use the family name used to find it.
    if(face->family_name == NULL)
        face->family_name = strdup(family.c_str());
        
    // Select unicode character map
    // Freetype should do this automatically, but in fact it
    // does not do it for Type1 fonts -pdaehne
    error = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
    // Don't care if this went wrong, maybe we still get correct results

    // Set the size
    if (size > 0)
        error = FT_Set_Pixel_Sizes(face, 0, size);
        // Again, we deliberately do not care for errors

    // For Type1 fonts, attach metric file
    string::size_type pos = path.rfind('.');
    if (pos != string::npos)
    {
        string suffix = path.substr(pos + 1);
        transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
        if ((suffix == "pfb") || (suffix == "pfa"))
        {
            string addPath = path.substr(0, pos + 1);
            addPath.append("afm");
            error = FT_Attach_File(face, addPath.c_str());
            // Don't care if this went wrong, the face will still work
        }
    }

    return face;
}


//----------------------------------------------------------------------
// Creates a new vector face
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFaceTransitPtr
TextFT2Backend::createVectorFace(const string &family, TextFace::Style style)
{
    TextVectorFaceTransitPtr retVal;
    
    // Try to create the freetype2 face
    FT_Face face = createFace(family, style, 0);
    
    if(face != 0)
    {
        // Create the new face object
        retVal = new TextFT2VectorFace(face);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Creates a new pixmap face
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFaceTransitPtr
TextFT2Backend::createPixmapFace(const string &family, TextFace::Style style, UInt32 size)
{
    TextPixmapFaceTransitPtr retVal;
    
    // Try to create the freetype2 face
    FT_Face face = createFace(family, style, size);
    if (face != 0)
    {
        // Create the new face object
        retVal = new TextFT2PixmapFace(face, size);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Creates a new TXF face
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFaceTransitPtr
TextFT2Backend::createTXFFace(const string &family, TextFace::Style style, const TextTXFParam &param)
{
    TextTXFFaceTransitPtr retVal;
    
    // Try to create the freetype2 face
    FT_Face face = createFace(family, style, param.size);
    if (face != 0)
    {
        // Create and return the new face object
        retVal = new TextFT2TXFFace(face, param);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Returns the names of all font families available
// Author: pdaehne
//----------------------------------------------------------------------
void TextFT2Backend::getFontFamilies(vector<string> &families)
{
    // Initialize the result vector
    families.clear();

#ifdef OSG_WITH_FONTCONFIG

    // Create a pattern that matches all fonts
    FcPattern *pattern = FcPatternCreate();
    if (pattern == 0)
        return;

    // We are only interested in the names of the font families
    FcObjectSet *objectSet = FcObjectSetBuild(FC_FAMILY, NULL);
    if (objectSet == 0)
    {
        FcPatternDestroy(pattern);
        return;
    }

    // Get all available fonts and put their names into the vector
    FcFontSet *fontSet = FcFontList(0, pattern, objectSet);
    if (fontSet != 0)
    {
        int    i;
        set<string> familySet;
        for (i = 0; i < fontSet->nfont; ++i)
        {
            FcChar8 *family;
            if (FcPatternGetString(fontSet->fonts[i], FC_FAMILY, 0, &family) == FcResultMatch)
                familySet.insert(reinterpret_cast<char*>(family));
        }
        // GRRRR, this does not work on WIN32...
        //families.assign(familySet.begin(), familySet.end());
        families.resize(familySet.size());
        copy(familySet.begin(), familySet.end(), families.begin());
        FcFontSetDestroy(fontSet);
    }

    // Cleanup
    FcObjectSetDestroy(objectSet);
    FcPatternDestroy(pattern);

#else // !OSG_WITH_FONTCONFIG

    // Scan the font search path for fonts
    scanForFonts();

    // Put the available fonts into the vector
    families.reserve(_fontMap.size());
    FontMap::const_iterator it;
    for (it = _fontMap.begin(); it != _fontMap.end(); ++it)
        families.push_back(it->first);
    unique(families.begin(), families.end());

#endif // !OSG_WITH_FONTCONFIG
}


//----------------------------------------------------------------------
// Scans the font search path for fonts
// Author: pdaehne
//----------------------------------------------------------------------
#ifndef OSG_WITH_FONTCONFIG
void TextFT2Backend::scanForFonts(void)
{
    // We scan the font directory only once
    if (_scanForFonts == true)
    {
        _scanForFonts = false;

        // Split the path list into its components
        string::size_type start = 0;
        while (true)
        {
#ifdef _WIN32
            string::size_type end = _pathList.find(';', start);
#else
            string::size_type end = _pathList.find(':', start);
#endif
            string path = end == string::npos ? _pathList.substr(start) : _pathList.substr(start, end - start);

            // Remove whitespace
            string::size_type wsPos = path.find_first_not_of(" \t\r\n");
            if (wsPos != string::npos)
            {
                path.erase(0, wsPos);
                wsPos = path.find_last_not_of(" \t\r\n");
                path.erase(wsPos + 1);

                // Scan the directory for fonts
                scanDir(path);
            }

            if (end == string::npos)
                break;
            start = end + 1;
        }
    }
}
#endif // !OSG_WITH_FONTCONFIG


//----------------------------------------------------------------------
// Scans a directory and its subdirectories for fonts
// Author: pdaehne
//----------------------------------------------------------------------
#ifndef OSG_WITH_FONTCONFIG
void TextFT2Backend::scanDir(const string &path)
{
#ifdef _WIN32

    // Append a slash to the end of the path if necessary
    string p = path;
    if ((p.length() < 1) || ((p[p.length() - 1] != '/') && (p[p.length() - 1] != '\\')))
        p.append(1, '\\');

    // Try to find the first directory entry
    string pattern = p;
    pattern.append(1, '*');
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(pattern.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    while (true)
    {
        // Create the full path of the directory entry
        string name = findFileData.cFileName;
        string fullname = p;
        fullname.append(name);

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // Recursively scan subdirectories
            if ((name != ".") && (name != ".."))
                scanDir(fullname);
        }
        else
            // Try to open the file as a font
            checkFile(fullname);

        // Try to find the next directory entry
        if (FindNextFile(hFind, &findFileData) == FALSE)
            break;
    }

    // Finished
    FindClose(hFind);

#else // !_WIN32

    // Open the directory
    DIR *dir = opendir(path.c_str());
    if (dir == 0)
        return;

    // Append a slash to the end of the path if necessary
    string p = path;
    if ((p.length() < 1) || (p[p.length() - 1] != '/'))
        p.append(1, '/');

    struct dirent entry, *result;
    while (true)
    {
        // Try to get the next directory entry
        if (readdir_r(dir, &entry, &result) != 0)
            return;
        if (result == 0)
            break;

        // Create the full path of the directory entry
        string name = entry.d_name;
        string fullname = p;
        fullname.append(name);
        switch (entry.d_type)
        {
            case DT_DIR:
                // Recursively scan subdirectories
                if ((name != ".") && (name != ".."))
                    scanDir(fullname);
                break;
            case DT_REG:
                // Try to open the file as a font
                checkFile(fullname);
                break;
            default:
                break;
        }
    }

    // Finished
    closedir(dir);

#endif // !_WIN32

}
#endif // !OSG_WITH_FONTCONFIG


//----------------------------------------------------------------------
// Checks if a file is a font file
// Author: pdaehne
//----------------------------------------------------------------------
#ifndef OSG_WITH_FONTCONFIG
void TextFT2Backend::checkFile(const string &fullname)
{
    // Try to open the file as a font
    FT_Long index = 0;
    FT_Long numFaces = 1;
    while (index < numFaces)
    {
        FT_Face face;
        FT_Error error = FT_New_Face(_library, fullname.c_str(), index, &face);
        if (error)
            break;

        // We got a font - put it into the map of fonts
        numFaces = face->num_faces;
        FontInfo fontInfo;
        fontInfo.path = fullname;
        fontInfo.index = index;
        if (face->style_flags & FT_STYLE_FLAG_BOLD)
            fontInfo.style = face->style_flags & FT_STYLE_FLAG_ITALIC ? TextFace::STYLE_BOLDITALIC : TextFace::STYLE_BOLD;
        else
            fontInfo.style = face->style_flags & FT_STYLE_FLAG_ITALIC ? TextFace::STYLE_ITALIC : TextFace::STYLE_PLAIN;
        string family = face->family_name;
        //transform(family.begin(), family.end(), family.begin(), ::tolower);
        _fontMap.insert(FontMap::value_type(family, fontInfo));
        FT_Done_Face(face);

        ++index;
    }
}
#endif // !OSG_WITH_FONTCONFIG


//----------------------------------------------------------------------
// Returns information about a face
// Author: pdaehne
//----------------------------------------------------------------------
static void getFaceInfo(FT_Face face, string &family, TextFace::Style &style)
{
    // Determine the family name
    family = face->family_name;

    // Determine the style
    if (face->style_flags & FT_STYLE_FLAG_BOLD)
        style = face->style_flags & FT_STYLE_FLAG_ITALIC ? TextFace::STYLE_BOLDITALIC : TextFace::STYLE_BOLD;
    else
        style = face->style_flags & FT_STYLE_FLAG_ITALIC ? TextFace::STYLE_ITALIC : TextFace::STYLE_PLAIN;
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2VectorFace::TextFT2VectorFace(FT_Face face)
    : TextVectorFace(),
      _face(face)
{
    // Get information about the face
    getFaceInfo(_face, _family, _style);

    // Determine the scale factor
    _scale = 1.f / static_cast<Real32>(_face->ascender - _face->descender);

    // Determine ascent
    _horiAscent = static_cast<Real32>(_face->ascender) * _scale;
    _vertAscent = -0.5f;

    // Determine descent
    _horiDescent = static_cast<Real32>(_face->descender) * _scale;
    _vertDescent = 0.5f;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2VectorFace::~TextFT2VectorFace(void)
{
    // Close the font file
    FT_Done_Face(_face);
}


//----------------------------------------------------------------------
// Lays out one line of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextFT2VectorFace::layout(const wstring &text, const TextLayoutParam &param,
                               TextLayoutResult &layoutResult)
{
    // Initialize return values
    layoutResult.clear();

    // Do the layout depending on the direction
    FT_UInt previousGlyphIndex = 0;
    Vec2f currPos;
    size_t i, len = text.length();
    layoutResult.indices.reserve(len);
    layoutResult.positions.reserve(len);
    vector<UInt32> spaceIndices;
    bool justify = param.getLength(0) > 0.f;
    for (i = 0; i < len; ++i)
    {
        // Get glyph
        FT_UInt glyphIndex = FT_Get_Char_Index(_face, text[i]);
        const TextGlyph &glyph = getGlyph(glyphIndex);
        if ((justify == true) && (text[i] == ' '))
            spaceIndices.push_back(layoutResult.indices.size());

        // Calculate position
        Vec2f pos;
        if (param.horizontal == true)
        {
            if (param.leftToRight == true)
            {
                FT_Vector kerning;
                FT_Get_Kerning(_face, previousGlyphIndex, glyphIndex, ft_kerning_unscaled/*FT_KERNING_UNSCALED*/, &kerning);
                currPos[0] += static_cast<float>(kerning.x) * _scale;
                pos = currPos;
                pos[0] += glyph.getHoriBearingX();
                pos[1] += glyph.getHoriBearingY();
                currPos[0] += glyph.getHoriAdvance();
            }
            else // leftToRight == false
            {
                FT_Vector kerning;
                FT_Get_Kerning(_face, glyphIndex, previousGlyphIndex, ft_kerning_unscaled/*FT_KERNING_UNSCALED*/, &kerning);
                currPos[0] -= static_cast<float>(kerning.x) * _scale + glyph.getHoriAdvance();
                pos = currPos;
                pos[0] += glyph.getHoriBearingX();
                pos[1] += glyph.getHoriBearingY();
            }
            previousGlyphIndex = glyphIndex;
        }
        else // horizontal == false
        {
            if (param.topToBottom == true)
            {
                pos = currPos;
                pos[0] += glyph.getVertBearingX();
                pos[1] += glyph.getVertBearingY();
                currPos[1] += glyph.getVertAdvance();
            }
            else // topToBottom == false
            {
                currPos[1] -= glyph.getVertAdvance();
                pos = currPos;
                pos[0] += glyph.getVertBearingX();
                pos[1] += glyph.getVertBearingY();
            }
        }

        layoutResult.indices.push_back(glyphIndex);
        layoutResult.positions.push_back(pos);
    }

    // Justify the line
    if (justify == true)
        justifyLine(param, spaceIndices, currPos, layoutResult);

    // Adjust the origin depending on the major and the minor alignment
    adjustLineOrigin(param, currPos, layoutResult);

    // Determine text bounds / line bounds
    if (param.horizontal == true)
        layoutResult.textBounds.setValues(osgAbs(currPos.x()), _horiAscent - _horiDescent);
    else
        layoutResult.textBounds.setValues(_vertDescent - _vertAscent, osgAbs(currPos.y()));
    layoutResult.lineBounds.push_back(layoutResult.textBounds);
}


//----------------------------------------------------------------------
// Helper object used by the decompose callback functions
// Author: pdaehne
//----------------------------------------------------------------------
typedef struct UserData
{
    Real32 scale;
    Vec2f offset;
    TextVectorGlyph::Outline &outline;
    inline UserData(Real32 s, const Vec2f &off, TextVectorGlyph::Outline &o)
    : scale(s), offset(off), outline(o)
    {}
}
UserData;


//----------------------------------------------------------------------
// callback function that starts a new contour
// Author: pdaehne
//----------------------------------------------------------------------
#if ((FREETYPE_MAJOR == 2) && (FREETYPE_MINOR < 2))
static int moveToFunc(FT_Vector *to, void *user)
#else
static int moveToFunc(const FT_Vector *to, void *user)
#endif
{
    UserData *userData = reinterpret_cast<UserData*>(user);

    // Check if the previous contour is valid, i.e. if it has more than two points.
    // When not, we simply delete the contour.
    if (userData->outline.empty() == false)
        if (userData->outline.back().size() < 3)
            userData->outline.erase(userData->outline.end() - 1);

    // We start a new contour
    userData->outline.push_back(TextVectorGlyph::Contour());

    // We have a point on the line
    Vec2f p(to->x, to->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return 0;
}


//----------------------------------------------------------------------
// callback function that adds a line to the contour
// Author: pdaehne
//----------------------------------------------------------------------
#if ((FREETYPE_MAJOR == 2) && (FREETYPE_MINOR < 2))
static int lineToFunc(FT_Vector *to, void *user)
#else
static int lineToFunc(const FT_Vector *to, void *user)
#endif
{
    UserData *userData = reinterpret_cast<UserData*>(user);

    // We have a point on the line
    Vec2f p(to->x, to->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return 0;
}


//----------------------------------------------------------------------
// callback function that adds a quadratic Bezier spline to the contour
// Author: pdaehne
//----------------------------------------------------------------------
#if ((FREETYPE_MAJOR == 2) && (FREETYPE_MINOR < 2))
static int conicToFunc(FT_Vector *control, FT_Vector *to, void *user)
#else
static int conicToFunc(const FT_Vector *control, const FT_Vector *to, void *user)
#endif
{
    UserData *userData = reinterpret_cast<UserData*>(user);

    // We have a control point and a point on the line
    Vec2f p(control->x, control->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_QUAD));
    p.setValues(to->x, to->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return 0;
}


//----------------------------------------------------------------------
// callback function that adds a cubic Bezier spline to the contour
// Author: pdaehne
//----------------------------------------------------------------------
#if ((FREETYPE_MAJOR == 2) && (FREETYPE_MINOR < 2))
static int cubicToFunc(FT_Vector *control1, FT_Vector *control2, FT_Vector *to, void *user)
#else
static int cubicToFunc(const FT_Vector *control1, const FT_Vector *control2, const FT_Vector *to, void *user)
#endif
{
    UserData *userData = reinterpret_cast<UserData*>(user);

    // We have two control points and a point on the line
    Vec2f p(control1->x, control1->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_CUBIC));
    p.setValues(control2->x, control2->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_CUBIC));
    p.setValues(to->x, to->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return 0;
}


//----------------------------------------------------------------------
// Creates a new Glyph object
// Author: pdaehne
//----------------------------------------------------------------------
unique_ptr<TextVectorGlyph> TextFT2VectorFace::createGlyph(TextGlyph::Index glyphIndex)
{
    // We cannot create glyphs for invalid glyph indices
    if (glyphIndex == TextGlyph::INVALID_INDEX)
        return unique_ptr<TextVectorGlyph>();

    // Try to get the glyph
    FT_Error error = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_NO_SCALE);
    if (error)
        return unique_ptr<TextVectorGlyph>();

    // We are only interested in outlines
    FT_GlyphSlot glyphSlot = _face->glyph;
    if (glyphSlot->format != ft_glyph_format_outline/*FT_GLYPH_FORMAT_OUTLINE*/)
        return unique_ptr<TextVectorGlyph>();

    // Create and return the new glyph object
    return unique_ptr<TextVectorGlyph>(new TextFT2VectorGlyph(glyphIndex, _scale, glyphSlot));
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2VectorGlyph::TextFT2VectorGlyph(Index glyphIndex, float scale, FT_GlyphSlot glyphSlot)
: TextVectorGlyph()
{
    _glyphIndex = glyphIndex;
    _width = static_cast<Real32>(glyphSlot->metrics.width) * scale;
    _height = static_cast<Real32>(glyphSlot->metrics.height) * scale;

    // Determine horizontal glyph metrics
    _horiAdvance = static_cast<Real32>(glyphSlot->metrics.horiAdvance) * scale;
    _horiBearingX = static_cast<Real32>(glyphSlot->metrics.horiBearingX) * scale;
    _horiBearingY = static_cast<Real32>(glyphSlot->metrics.horiBearingY) * scale;

    // Determine vertical glyph metrics
    // Hmmm, there is no useful information here for vertical layout.
    // So we have to guess resonable values -pdaehne
    //_vertAdvance = -static_cast<Real32>(glyphSlot->metrics.vertAdvance) * scale;
    //_vertBearingX = static_cast<Real32>(glyphSlot->metrics.vertBearingX) * scale;
    //_vertBearingY = -static_cast<Real32>(glyphSlot->metrics.vertBearingY) * scale;
    _vertAdvance = -_height - 1.f / 10.f;
    _vertBearingX = -_width / 2.f;
    _vertBearingY = -1.f / 20.f;

    // Add the outlines to the glyph object
    FT_Outline_Funcs func_interface =
    {
        moveToFunc,
        lineToFunc,
        conicToFunc,
        cubicToFunc,
        0,
        0
    };
    UserData userData(scale, Vec2f(_horiBearingX, _horiBearingY), _outline);
    FT_Outline_Decompose(&(glyphSlot->outline), &func_interface, &userData);

    // Check if the last contour is valid, i.e. if it has more than two points.
    // When not, we simply delete the contour.
    if (_outline.empty() == false)
        if (_outline.back().size() < 3)
            _outline.erase(_outline.end() - 1);
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2VectorGlyph::~TextFT2VectorGlyph() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2PixmapFace::TextFT2PixmapFace(FT_Face face, UInt32 size)
: TextPixmapFace(), _face(face)
{
    // Get information about the face
    getFaceInfo(_face, _family, _style);

    // Set the size
    _size = size;

    // Determine ascent
    _horiAscent = static_cast<Real32>(_face->size->metrics.ascender) / 64.f;
    _vertAscent = -static_cast<Real32>(_size) / 2.f;

    // Determine descent
    _horiDescent = static_cast<Real32>(_face->size->metrics.descender) / 64.f;
    _vertDescent = static_cast<Real32>(_size) / 2.f;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2PixmapFace::~TextFT2PixmapFace()
{
    // Close the font file
    FT_Done_Face(_face);
}


//----------------------------------------------------------------------
// Lays out one line of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextFT2PixmapFace::layout(const wstring &text, const TextLayoutParam &param,
                               TextLayoutResult &layoutResult)
{
    // Initialize return values
    layoutResult.clear();

    // Do the layout depending on the direction
    FT_UInt previousGlyphIndex = 0;
    Vec2f currPos;
    size_t i, len = text.length();
    layoutResult.indices.reserve(len);
    layoutResult.positions.reserve(len);
    vector<UInt32> spaceIndices;
    bool justify = param.getLength(0) > 0.f;
    for (i = 0; i < len; ++i)
    {
        // Get glyph
        FT_UInt glyphIndex = FT_Get_Char_Index(_face, text[i]);
        const TextGlyph &glyph = getGlyph(glyphIndex);
        if ((justify == true) && (text[i] == ' '))
            spaceIndices.push_back(layoutResult.indices.size());

        // Calculate position
        Vec2f pos;
        if (param.horizontal == true)
        {
            if (param.leftToRight == true)
            {
                FT_Vector kerning;
                FT_Get_Kerning(_face, previousGlyphIndex, glyphIndex, ft_kerning_default/*FT_KERNING_DEFAULT*/, &kerning);
                currPos[0] += static_cast<float>(kerning.x) / 64.f;
                pos[0] = currPos.x() + glyph.getHoriBearingX();
                pos[1] = currPos.y() + glyph.getHoriBearingY();
                currPos[0] += glyph.getHoriAdvance();
            }
            else // leftToRight == false
            {
                FT_Vector kerning;
                FT_Get_Kerning(_face, glyphIndex, previousGlyphIndex, ft_kerning_default/*FT_KERNING_DEFAULT*/, &kerning);
                currPos[0] -= static_cast<float>(kerning.x) / 64.f + glyph.getHoriAdvance();
                pos[0] = currPos[0] + glyph.getHoriBearingX();
                pos[1] = currPos[1] + glyph.getHoriBearingY();
            }
            previousGlyphIndex = glyphIndex;
        }
        else // horizontal == false
        {
            if (param.topToBottom == true)
            {
                pos[0] = currPos.x() + glyph.getVertBearingX();
                pos[1] = currPos.y() + glyph.getVertBearingY();
                currPos[1] += glyph.getVertAdvance();
            }
            else // topToBottom == false
            {
                currPos[1] -= glyph.getVertAdvance();
                pos[0] = currPos.x() + glyph.getVertBearingX();
                pos[1] = currPos.y() + glyph.getVertBearingY();
            }
        }

        layoutResult.indices.push_back(glyphIndex);
        layoutResult.positions.push_back(pos);
    }

    // Justify the line
    if (justify == true)
        justifyLine(param, spaceIndices, currPos, layoutResult);

    // Adjust the origin depending on the major and the minor alignment
    adjustLineOrigin(param, currPos, layoutResult);

    // Determine text bounds / line bounds
    if (param.horizontal == true)
        layoutResult.textBounds.setValues(osgAbs(currPos.x()), _horiAscent - _horiDescent);
    else
        layoutResult.textBounds.setValues(_vertDescent - _vertAscent, osgAbs(currPos.y()));
    layoutResult.lineBounds.push_back(layoutResult.textBounds);
}


//----------------------------------------------------------------------
// Creates a new Glyph object
// Author: pdaehne
//----------------------------------------------------------------------
unique_ptr<TextPixmapGlyph> TextFT2PixmapFace::createGlyph(TextGlyph::Index glyphIndex)
{
    // We cannot create glyphs for invalid glyph indices
    if (glyphIndex == TextGlyph::INVALID_INDEX)
        return unique_ptr<TextPixmapGlyph>();

    // Try to get the glyph
    FT_Error error = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_DEFAULT);
    if (error)
        return unique_ptr<TextPixmapGlyph>();

    // We are only interested in outlines
    FT_GlyphSlot glyphSlot = _face->glyph;
    if (glyphSlot->format != ft_glyph_format_bitmap/*FT_GLYPH_FORMAT_BITMAP*/)
    {
        error = FT_Render_Glyph(glyphSlot, ft_render_mode_normal/*FT_RENDER_MODE_NORMAL*/);
        if (error)
            return unique_ptr<TextPixmapGlyph>();
    }

    // Create and return the new glyph object
    return unique_ptr<TextPixmapGlyph>(new TextFT2PixmapGlyph(glyphIndex, this, glyphSlot));
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2PixmapGlyph::TextFT2PixmapGlyph(Index glyphIndex, TextFT2PixmapFace *face, FT_GlyphSlot glyphSlot)
: TextPixmapGlyph()
{
    _glyphIndex = glyphIndex;
    _width = glyphSlot->bitmap.width;
    _pitch = glyphSlot->bitmap.pitch;
    _height = glyphSlot->bitmap.rows;

    // Determine horizontal glyph metrics
    _horiAdvance = static_cast<Real32>(glyphSlot->metrics.horiAdvance) / 64.f;
    _horiBearingX = glyphSlot->bitmap_left;
    _horiBearingY = glyphSlot->bitmap_top;

    // Determine vertical glyph metrics
    // Hmmm, there is no useful information here for vertical layout.
    // So we have to guess resonable values -pdaehne
    //_vertAdvance = -static_cast<Real32>(glyphSlot->metrics.vertAdvance) / 64.f;
    //_vertBearingX = static_cast<int>(static_cast<float>(glyphSlot->metrics.vertBearingX) / 64.f);
    //_vertBearingY = static_cast<int>(-static_cast<float>(glyphSlot->metrics.vertBearingY) / 64.f);
    _vertBearingX = -static_cast<Int32>(_width >> 1);
    _vertBearingY = static_cast<Int32>(-(face->getHoriAscent() - face->getHoriDescent()) / 20.f);
    if (_vertBearingY > -1)
        _vertBearingY = -1;
    Int32 vertAdvanceOffset = _vertBearingY << 1;
    _vertAdvance = -static_cast<Int32>(_height) + vertAdvanceOffset;

    unsigned int size = glyphSlot->bitmap.pitch * glyphSlot->bitmap.rows;
    if ((size == 0) || (glyphSlot->bitmap.buffer == 0))
        _pixmap = 0;
    else
    {
        _pixmap = new unsigned char[size];
        memcpy(_pixmap, glyphSlot->bitmap.buffer, size);
        flipPixmap();
    }
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2PixmapGlyph::~TextFT2PixmapGlyph() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2TXFFace::TextFT2TXFFace(FT_Face face, const TextTXFParam &param)
{
    // Get information about the face
    getFaceInfo(face, _family, _style);

    // Set the size
    _param = param;

    // Determine ascent
    _horiAscent = static_cast<Real32>(face->size->metrics.ascender) / 64.f;
    _vertAscent = -0.5f;

    // Determine descent
    _horiDescent = static_cast<Real32>(face->size->metrics.descender) / 64.f;
    _vertDescent = 0.5f;

    // Determine the scale factor & adjust ascent and descent
    _scale = 1.f / (_horiAscent - _horiDescent);
    _horiAscent *= _scale;
    _horiDescent *= _scale;

    // Create all glyphs
    wstring::const_iterator it;
    for (it = param.getCharacters().begin(); it != param.getCharacters().end(); ++it)
    {
        FT_UInt glyphIndex = FT_Get_Char_Index(face, *it);
        if (glyphIndex == 0)
            continue;
        FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
        if (error)
            continue;
        FT_GlyphSlot glyphSlot = face->glyph;
        if (glyphSlot->format != ft_glyph_format_bitmap/*FT_GLYPH_FORMAT_BITMAP*/)
        {
            error = FT_Render_Glyph(glyphSlot, ft_render_mode_normal/*FT_RENDER_MODE_NORMAL*/);
            if (error)
                continue;
        }
        _glyphMap.insert(GlyphMap::value_type(*it, new TextFT2TXFGlyph(*it, this, _scale, face->glyph)));
    }

    // Calculate the positions of the glyphs on the texture
    prepareTexture(param);
    OSG_ASSERT(_texture != NULL);
    OSG_ASSERT(_texture->getSize() == static_cast<UInt32>(_texture->getWidth() * _texture->getHeight()));

    // Create the texture
    for (it = param.getCharacters().begin(); it != param.getCharacters().end(); ++it)
    {
        GlyphMap::iterator gIt = _glyphMap.find(*it);
        if (gIt == _glyphMap.end())
            continue;
        OSG_ASSERT(gIt->second != 0);
        TextTXFGlyph *glyph = gIt->second;
        FT_UInt glyphIndex = FT_Get_Char_Index(face, *it);
        if (glyphIndex == 0)
            continue;
        FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
        if (error)
            continue;
        FT_GlyphSlot glyphSlot = face->glyph;
        if (glyphSlot->format != ft_glyph_format_bitmap/*FT_GLYPH_FORMAT_BITMAP*/)
        {
            error = FT_Render_Glyph(glyphSlot, ft_render_mode_normal/*FT_RENDER_MODE_NORMAL*/);
            if (error)
                continue;
        }
        unsigned char *src = glyphSlot->bitmap.buffer;
        if (src == 0)
            continue;
        int bpl = glyphSlot->bitmap.pitch;
        src += bpl * (glyph->getPixmapHeight() - 1);
        unsigned char *src2;
        UInt8 *dst = _texture->editData() + glyph->getX() + glyph->getY() * _texture->getWidth();
        UInt32 dstPitch = _texture->getWidth() - glyph->getPixmapWidth();
        UInt32 x, y;
        for (y = 0; y < glyph->getPixmapHeight(); ++y)
        {
            src2 = src;
            for (x = 0; x < glyph->getPixmapWidth(); ++x)
                *dst++ = *src2++;
            src -= bpl;
            dst += dstPitch;
        }
    }

    // Close the font file
    FT_Done_Face(face);
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2TXFFace::~TextFT2TXFFace() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2TXFGlyph::TextFT2TXFGlyph(Index glyphIndex, TextFT2TXFFace *face,
                                 Real32 scale, FT_GlyphSlot glyphSlot)
: TextTXFGlyph()
{
    _glyphIndex = glyphIndex;
    _scale = scale;
    _width = glyphSlot->bitmap.width;
    _height = glyphSlot->bitmap.rows;

    // Determine horizontal glyph metrics
    _horiAdvance = static_cast<Real32>(glyphSlot->metrics.horiAdvance) / 64.f * _scale;
    _horiBearingX = glyphSlot->bitmap_left;
    _horiBearingY = glyphSlot->bitmap_top;

    // Determine vertical glyph metrics
    // Hmmm, there is no useful information here for vertical layout.
    // So we have to guess resonable values -pdaehne
    //_vertAdvance = -static_cast<Real32>(glyphSlot->metrics.vertAdvance) / 64.f * _scale;
    //_vertBearingX = static_cast<int>(static_cast<float>(glyphSlot->metrics.vertBearingX) / 64.f);
    //_vertBearingY = static_cast<int>(-static_cast<float>(glyphSlot->metrics.vertBearingY) / 64.f);
    _vertBearingX = -static_cast<Int32>(_width >> 1);
    if (glyphIndex == 32)
    {
        _vertBearingY = -_horiBearingX;
        _vertAdvance = -_horiAdvance;
    }
    else
    {
        _vertBearingY = static_cast<Int32>(-(face->getHoriAscent() - face->getHoriDescent()) / _scale / 20.f);
        if (_vertBearingY > -1)
            _vertBearingY = -1;
        Real32 vertAdvanceOffset = static_cast<Real32>(_vertBearingY) * 2.f * _scale;
        _vertAdvance = -static_cast<Real32>(_height) * _scale + vertAdvanceOffset;
    }
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFT2TXFGlyph::~TextFT2TXFGlyph() {}


OSG_END_NAMESPACE


#endif // OSG_WITH_FT2

