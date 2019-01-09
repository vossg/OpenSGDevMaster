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

#include "OSGTextWIN32Backend.h"
#include "OSGBaseTypes.h"


#if defined(_WIN32) || defined(OSG_DO_DOC)


#ifdef _MSC_VER
# pragma warning (disable: 4786)
#endif

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


using namespace std;
OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// WIN32 specific implementation of the TextVectorFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextWIN32VectorFace: public TextVectorFace
{
public:

    // Constructor
    TextWIN32VectorFace(TextWIN32Backend *backend, HFONT hHoriFont, HFONT hVertFont);

    // Destructor
    virtual ~TextWIN32VectorFace();

    // Lays out one line of text
    virtual void layout(const wstring &text, const TextLayoutParam &param,
                        TextLayoutResult &layoutResult);

protected:

    // Creates a new Glyph object
    virtual unique_ptr<TextVectorGlyph> createGlyph(TextGlyph::Index glyphIndex);

private:

    // The backend that created the face
    TextWIN32Backend *_backend;

    // Font handle for horizontal layout
    HFONT _hHoriFont;

    // Font handle for vertical layout
    HFONT _hVertFont;
};


//----------------------------------------------------------------------
// WIN32 specific implementation of the TextVectorGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextWIN32VectorGlyph: public TextVectorGlyph
{
public:

    // Constructor
    TextWIN32VectorGlyph(Index glyphIndex, Real32 scale,
                         const GLYPHMETRICS &hpgm, const GLYPHMETRICS &vhpgm,
                         LPTTPOLYGONHEADER lpHeader, DWORD size);

    // Destructor
    virtual ~TextWIN32VectorGlyph();
};


//----------------------------------------------------------------------
// WIN32 specific implementation of the TextPixmapFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextWIN32PixmapFace: public TextPixmapFace
{
public:

    // Constructor
    TextWIN32PixmapFace(TextWIN32Backend *backend, HFONT hHoriFont, HFONT hVertFont, UInt32 size);

    // Destructor
    virtual ~TextWIN32PixmapFace();

    // Lays out one line of text
    virtual void layout(const wstring &text, const TextLayoutParam &param,
                        TextLayoutResult &layoutResult);

protected:

    // Creates a new Glyph object
    virtual unique_ptr<TextPixmapGlyph> createGlyph(TextGlyph::Index glyphIndex);

private:

    // The backend that created the face
    TextWIN32Backend *_backend;

    // Font handle for horizontal layout
    HFONT _hHoriFont;

    // Font handle for vertical layout
    HFONT _hVertFont;
};


//----------------------------------------------------------------------
// WIN32 specific implementation of the TextPixmapGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextWIN32PixmapGlyph: public TextPixmapGlyph
{
public:

    // Constructor
    TextWIN32PixmapGlyph(Index glyphIndex, const GLYPHMETRICS &hpgm,
                         const GLYPHMETRICS &vpgm, UInt8 *pixmap);

    // Destructor
    virtual ~TextWIN32PixmapGlyph();
};


//----------------------------------------------------------------------
// WIN32 specific implementation of the TextTXFFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextWIN32TXFFace: public TextTXFFace
{
public:

    // Constructor
    TextWIN32TXFFace(const TextWIN32Backend *backend, HFONT hHoriFont, HFONT hVertFont,
                     const TextTXFParam &param);

    // Destructor
    virtual ~TextWIN32TXFFace();
};


//----------------------------------------------------------------------
// WIN32 specific implementation of the TextTXFGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextWIN32TXFGlyph: public TextTXFGlyph
{
public:

    // Constructor
    TextWIN32TXFGlyph(Index glyphIndex, TextWIN32TXFFace *face, Real32 scale,
                      const GLYPHMETRICS &hpgm, const GLYPHMETRICS &vpgm);

    // Destructor
    virtual ~TextWIN32TXFGlyph();
};


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32Backend::TextWIN32Backend()
    : TextBackend(), _hDC(0)
{
    // Create device context
    _hDC = CreateDC("DISPLAY", 0, 0, 0);
    if (_hDC == 0)
    {
        SWARNING << "TextWIN32Backend: Failed to create device context."
                 << std::endl;
        return;
    }

    SetGraphicsMode(_hDC, GM_ADVANCED);
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32Backend::~TextWIN32Backend()
{
    // Destroy device context
    DeleteDC(_hDC);
}


//----------------------------------------------------------------------
// Helper struct used by enumFamCallBack
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class EnumData
{
public:
    string fullname;
    UINT emSize;
};


//----------------------------------------------------------------------
// Callback that gets called by Windows to enumerate fonts
// Author: pdaehne
//----------------------------------------------------------------------
static int CALLBACK enumFamCallBack(ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm,
                                    DWORD fontType, LPARAM lParam)
{
    // We are not interested in raster fonts
    if ((fontType & RASTER_FONTTYPE) != 0)
        return 1;

    // Fill enumData structure
    EnumData *enumData = reinterpret_cast<EnumData*>(lParam);
    enumData->fullname = (const char *)lpelf->elfFullName;
    enumData->emSize = lpntm->ntmSizeEM;

    // Quit enumeration
    return 0;
}


//----------------------------------------------------------------------
// Creates horizontal and vertical fonts from given fontname,
// size and style
// Author: pdaehne
//----------------------------------------------------------------------
void TextWIN32Backend::createFonts(const string &family, UInt32 size, TextFace::Style style,
                                   HFONT &hHoriFont, HFONT &hVertFont)
{
    // Initialization
    hHoriFont = hVertFont = 0;

    // Handle generic family names
    string f;
    if (family == "SERIF")
        f = "Times New Roman";
    else if (family == "SANS")
        f = "Arial";
    else if (family == "TYPEWRITER")
        f = "Courier New";
    else
        f = family;

    if (size == 0)
    {
        // Grrr - this is only necessary to get the EM size -pdaehne
        EnumData enumData;
        EnumFontFamilies(_hDC, (LPCTSTR)(f.c_str()), (FONTENUMPROC)enumFamCallBack,
                         (LPARAM)&enumData);
        if (enumData.fullname.empty() == true)
            return;
        size = -enumData.emSize;
    }

    // Handle style
    BYTE italic;
    LONG weight;
    switch (style)
    {
        default:
            FWARNING(("Invalid font style parameter.\n"));
            // intentionally fall through
        case TextFace::STYLE_PLAIN:
            italic = FALSE;
            weight = FW_NORMAL;
            break;
        case TextFace::STYLE_BOLD:
            italic = FALSE;
            weight = FW_BOLD;
            break;
        case TextFace::STYLE_ITALIC:
            italic = TRUE;
            weight = FW_NORMAL;
            break;
        case TextFace::STYLE_BOLDITALIC:
            italic = TRUE;
            weight = FW_BOLD;
            break;
    }

    // Create the the horizontal font
    hHoriFont = CreateFont(size, 0, 0, 0, weight, italic, FALSE, FALSE,
                           DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
                           ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                           f.c_str());

    // Create the the vertical font
    hVertFont = CreateFont(size, 0, -900, 0, weight, italic, FALSE, FALSE,
                           DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
                           ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                           f.c_str());
}


//----------------------------------------------------------------------
// Creates a new vector face
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFaceTransitPtr TextWIN32Backend::createVectorFace(
    const string &family, TextFace::Style style)
{
    TextVectorFaceTransitPtr retVal;
    
    // Try to create the font handles
    HFONT hHoriFont, hVertFont;
    createFonts(family, 0, style, hHoriFont, hVertFont);
    if (hHoriFont != 0)
    {
        // Create the new face object
        retVal = new TextWIN32VectorFace(this, hHoriFont, hVertFont);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Creates a new pixmap face
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFaceTransitPtr TextWIN32Backend::createPixmapFace(
    const string &family, TextFace::Style style, UInt32 size)
{
    TextPixmapFaceTransitPtr retVal;
    
    // Try to create the font handles
    HFONT hHoriFont, hVertFont;
    createFonts(family, size, style, hHoriFont, hVertFont);
    if (hHoriFont != 0)
    {
        // Create the new face object
        retVal = new TextWIN32PixmapFace(this, hHoriFont, hVertFont, size);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Creates a new TXF face
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFaceTransitPtr TextWIN32Backend::createTXFFace(
    const string &family, TextFace::Style style, const TextTXFParam &param)
{
    TextTXFFaceTransitPtr retVal;
    
    // Try to create the font handles
    HFONT hHoriFont, hVertFont;
    createFonts(family, param.size, style, hHoriFont, hVertFont);
    if (hHoriFont != 0)
    {
        // Create the new face object
        retVal = new TextWIN32TXFFace(this, hHoriFont, hVertFont, param);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Callback that gets called by Windows to enumerate fonts
// Author: pdaehne
//----------------------------------------------------------------------
static int CALLBACK enumFamCallBack2(ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm,
                                    DWORD fontType, LPARAM lParam)
{
    // We are not interested in raster fonts
    if ((fontType & RASTER_FONTTYPE) != 0)
        return 1;

    // Fill enumData structure
    set<string> *familySet = reinterpret_cast<set<string>*>(lParam);
    familySet->insert(lpelf->elfLogFont.lfFaceName);

    // Continue enumeration
    return 1;
}


//----------------------------------------------------------------------
// Returns the names of all font families available
// Author: pdaehne
//----------------------------------------------------------------------
void TextWIN32Backend::getFontFamilies(vector<string> &families)
{
    families.clear();

    set<string> familySet;
    EnumFontFamilies(_hDC, 0, (FONTENUMPROC)enumFamCallBack2, (LPARAM)&familySet);
    // GRRRR, this does not work on WIN32...
    //families.assign(familySet.begin(), familySet.end());
    families.resize(familySet.size());
    copy(familySet.begin(), familySet.end(), families.begin());
}


//----------------------------------------------------------------------
// Returns information about a given font
// Author: pdaehne
//----------------------------------------------------------------------
static void getFontInfo(HDC hDC, HFONT hFont, string &family,
                        TextFace::Style &style, Real32 &ascent, Real32 &descent)
{
    // Select the font into the device context
    HGDIOBJ oldFont = SelectObject(hDC, hFont);

    // Get the name of the font
    int nameLength = GetTextFace(hDC, 0, 0);
    family.resize(nameLength);
    GetTextFace(hDC, nameLength, &(family[0]));
    // GetTextFace also puts a trailing '\0' into the string, so we have to remove it
    family.resize(nameLength - 1);

    // Get metrics of the font
    TEXTMETRIC tm;
    BOOL result = GetTextMetrics(hDC, &tm);
    SelectObject(hDC, oldFont);
    if (result == FALSE)
        return;

    // Determine the style
    if (tm.tmWeight > (FW_NORMAL + FW_BOLD) / 2)
        style = tm.tmItalic != 0 ? TextFace::STYLE_BOLDITALIC : TextFace::STYLE_BOLD;
    else
        style = tm.tmItalic != 0 ? TextFace::STYLE_ITALIC : TextFace::STYLE_PLAIN;

    // Determine ascent
    ascent = static_cast<Real32>(tm.tmAscent);

    // Determine descent
    descent = static_cast<Real32>(-tm.tmDescent);
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32VectorFace::TextWIN32VectorFace(TextWIN32Backend *backend,
                                         HFONT hHoriFont, HFONT hVertFont)
: TextVectorFace(), _backend(backend), _hHoriFont(hHoriFont), _hVertFont(hVertFont)
{
    // Get information about the font
    getFontInfo(_backend->_hDC, _hHoriFont, _family, _style,
        _horiAscent, _horiDescent);

    // Determine the scale factor and adjust ascent and descent
    _scale = 1.f / (_horiAscent - _horiDescent);
    _horiAscent *= _scale;
    _horiDescent *= _scale;

    // Determine vertical ascent and descent
    _vertAscent = -0.5f;
    _vertDescent = 0.5f;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32VectorFace::~TextWIN32VectorFace()
{
    // Destroy the font objects
    DeleteObject(_hHoriFont);
    DeleteObject(_hVertFont);
}


//----------------------------------------------------------------------
// Converts a unicode string to utf16
// RFC2781: UTF-16, an encoding of ISO 10646
// Author: pdaehne
//----------------------------------------------------------------------
static void convertUnicodeToUTF16(const wstring &text, vector<WCHAR> &utf16Text)
{
    wstring::size_type i, textTotalLength = text.length();
    utf16Text.clear();
    utf16Text.reserve(textTotalLength);
    for (i = 0; i < textTotalLength; ++i)
    {
        wchar_t unicode = text[i];
        if (unicode < 0x10000)
            utf16Text.push_back(unicode);
        else if (unicode < 0x110000)
        {
            unsigned long u = unicode - 0x10000;
            utf16Text.push_back(0xd800 | (u >> 10));
            utf16Text.push_back(0xdc00 | (u & 0x3ff));
        }
    }
}


//----------------------------------------------------------------------
// Lays out one line of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextWIN32VectorFace::layout(const wstring &text, const TextLayoutParam &param,
                                 TextLayoutResult &layoutResult)
{
    // Initialize return values
    layoutResult.clear();
    if (param.horizontal == true)
        layoutResult.textBounds[1] = _horiAscent - _horiDescent;
    else
        layoutResult.textBounds[0] = _vertDescent - _vertAscent;
    layoutResult.lineBounds.push_back(layoutResult.textBounds);

    // Convert the unicode string to utf16
    vector<WCHAR> utf16Text;
    convertUnicodeToUTF16(text, utf16Text);
    vector<WCHAR>::size_type len = utf16Text.size();
    if (len == 0)
        return;

    // Select the font into the device context
    HGDIOBJ oldFont;
    if (param.horizontal == true)
        oldFont = SelectObject(_backend->_hDC, _hHoriFont);
    else
        oldFont = SelectObject(_backend->_hDC, _hVertFont);

    GCP_RESULTSW results;
    ZeroMemory(&results, sizeof(results));
    results.lStructSize = sizeof(results);
    results.lpDx = new int[len];
    results.lpGlyphs = new WCHAR[len];
    results.lpGlyphs[0] = 0; // needed by GCP_LIGATE
    results.nGlyphs = UInt32(len);
    DWORD dwFlags = GCP_GLYPHSHAPE | GCP_LIGATE | GCP_REORDER | GCP_USEKERNING;
    int nMaxExtent = 0;
    Real32 length = param.getLength(0);
    if (length > 0)
    {
        dwFlags |= GCP_JUSTIFY | GCP_KASHIDA | GCP_MAXEXTENT;
        nMaxExtent = length / _scale;
    }
    DWORD result = GetCharacterPlacementW(_backend->_hDC, &(utf16Text[0]), UInt32(len), nMaxExtent, &results, dwFlags);
    if (result != 0)
    {
        layoutResult.indices.reserve(results.nGlyphs);
        layoutResult.positions.reserve(results.nGlyphs);
        UINT j;
        Vec2f currPos;
        for (j = 0; j < results.nGlyphs; ++j)
        {
            // Get glyph
            const TextGlyph &glyph = getGlyph(results.lpGlyphs[j]);

            // Calculate position
            Vec2f pos;
            if (param.horizontal == true)
            {
                pos = currPos;
                pos[0] += glyph.getHoriBearingX();
                pos[1] += glyph.getHoriBearingY();
                currPos[0] += results.lpDx[j] * _scale;
            }
            else
            {
                pos = currPos;
                pos[0] += glyph.getVertBearingX();
                pos[1] += glyph.getVertBearingY();
                currPos[1] -= results.lpDx[j] * _scale;
            }
            layoutResult.indices.push_back(results.lpGlyphs[j]);
            layoutResult.positions.push_back(pos);
        }

        // Adjust the origin depending on the major and the minor alignment
        adjustLineOrigin(param, currPos, layoutResult);

        // Determine text bounds / line bounds
        if (param.horizontal == true)
            layoutResult.textBounds[0] = osgAbs(currPos.x());
        else
            layoutResult.textBounds[1] = osgAbs(currPos.y());
        OSG_ASSERT(layoutResult.lineBounds.empty() == false);
        layoutResult.lineBounds.front() = layoutResult.textBounds;
    }
    delete [] results.lpDx;
    delete [] results.lpGlyphs;

    // Unselect the font
    SelectObject(_backend->_hDC, oldFont);
}


//----------------------------------------------------------------------
// Creates a new Glyph object
// Author: pdaehne
//----------------------------------------------------------------------
unique_ptr<TextVectorGlyph> TextWIN32VectorFace::createGlyph(TextGlyph::Index glyphIndex)
{
    // We cannot create glyphs for invalid glyph indices
    if (glyphIndex == TextGlyph::INVALID_INDEX)
        return unique_ptr<TextVectorGlyph>();

    // Select the vertical font into the device context
    HGDIOBJ oldFont = SelectObject(_backend->_hDC, _hVertFont);

    // Get the vertical metrics
    GLYPHMETRICS vpgm;
    MAT2 mat2 = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
    DWORD size = GetGlyphOutlineW(_backend->_hDC, glyphIndex, GGO_METRICS | GGO_GLYPH_INDEX,
                                  &vpgm, 0, 0, &mat2);
    if (size == GDI_ERROR)
    {
        SelectObject(_backend->_hDC, oldFont);
        return unique_ptr<TextVectorGlyph>();
    }

    // Select the horizontal font into the device context
    SelectObject(_backend->_hDC, _hHoriFont);

    // Get glyph outline
    GLYPHMETRICS hpgm;
    size = GetGlyphOutlineW(_backend->_hDC, glyphIndex, GGO_NATIVE | GGO_GLYPH_INDEX, &hpgm, 0, 0, &mat2);
    if (size == GDI_ERROR)
    {
        SelectObject(_backend->_hDC, oldFont);
        return unique_ptr<TextVectorGlyph>();
    }
    LPTTPOLYGONHEADER lpHeader = (LPTTPOLYGONHEADER) new char[size];
    size = GetGlyphOutlineW(_backend->_hDC, glyphIndex, GGO_NATIVE | GGO_GLYPH_INDEX, &hpgm, size, lpHeader, &mat2);

    // Unselect the font
    SelectObject(_backend->_hDC, oldFont);

    if (size == GDI_ERROR)
    {
        delete [] lpHeader;
        return unique_ptr<TextVectorGlyph>();
    }

    // Create and return the new glyph object
    unique_ptr<TextVectorGlyph> glyph(new TextWIN32VectorGlyph(glyphIndex, _scale,
                                                             hpgm, vpgm, lpHeader, size));
    delete [] lpHeader;
    return glyph;
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32VectorGlyph::TextWIN32VectorGlyph(Index glyphIndex, Real32 scale,
                                           const GLYPHMETRICS &hpgm,
                                           const GLYPHMETRICS &vpgm,
                                           LPTTPOLYGONHEADER lpHeader,
                                           DWORD size)
: TextVectorGlyph()
{
    _glyphIndex = glyphIndex;
    _width = static_cast<Real32>(hpgm.gmBlackBoxX) * scale;
    _height = static_cast<Real32>(hpgm.gmBlackBoxY) * scale;

    // Determine horizontal glyph metrics
    _horiAdvance = static_cast<Real32>(hpgm.gmCellIncX) * scale;
    _horiBearingX = static_cast<Real32>(hpgm.gmptGlyphOrigin.x) * scale;
    _horiBearingY = static_cast<Real32>(hpgm.gmptGlyphOrigin.y) * scale;

    // Determine vertical glyph metrics
    // Hmmm, there is no useful information here for vertical layout -
    // the values provided are just the same as for horizontal layout.
    // So we have to guess resonable values -pdaehne
    //_vertAdvance = static_cast<Real32>(vpgm.gmCellIncY) * scale;
    //_vertBearingX = static_cast<Real32>(vpgm.gmptGlyphOrigin.x) * scale;
    //_vertBearingY = static_cast<Real32>(vpgm.gmptGlyphOrigin.y) * scale;
    _vertAdvance = -_height;
    _vertBearingX = -_width / 2.f;
    _vertBearingY = 0.f;

    Vec2f offset(_horiBearingX, _horiBearingY), p;

    // The following algorithm has been taken from MSDN article Q243285
    // "HOWTO: Draw TrueType Glyph Outlines" - pdaehne

    WORD                i;
    LPTTPOLYGONHEADER   lpStart;    // the start of the buffer
    LPTTPOLYCURVE       lpCurve;    // the current curve of a contour
    POINTFX *endPoint = 0;

    lpStart = lpHeader;

    // Loop until we have processed the entire buffer of contours.
    // The buffer may contain one or more contours that begin with
    // a TTPOLYGONHEADER. We have them all when we the end of the buffer.
    while ((DWORD)lpHeader < (DWORD)(((LPSTR)lpStart) + size))
    {
        if (lpHeader->dwType == TT_POLYGON_TYPE)
        // Draw each coutour, currently this is the only valid
        // type of contour.
        {
            _outline.push_back(TextVectorGlyph::Contour());

            // Convert the starting point. It is an on curve point.
            // All other points are continuous from the "last"
            // point of the contour. Thus the start point the next
            // bezier is always pt[cTotal-1] - the last point of the
            // previous bezier. See PolyBezier.
            POINTFX &startPoint = lpHeader->pfxStart;
            p.setValues(startPoint.x.value, startPoint.y.value);
            p *= scale;
            p -= offset;
            _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

            // Get to first curve of contour -
            // it starts at the next byte beyond header
            lpCurve = (LPTTPOLYCURVE) (lpHeader + 1);

            // Walk this contour and process each curve (or line) segment
            // and add it to the Beziers
            while ((DWORD)lpCurve < (DWORD)(((LPSTR)lpHeader) + lpHeader->cb))
            {
                //**********************************************
                // Format assumption:
                //   The bytes immediately preceding a POLYCURVE
                //   structure contain a valid POINTFX.
                //
                //   If this is first curve, this points to the
                //      pfxStart of the POLYGONHEADER.
                //   Otherwise, this points to the last point of
                //      the previous POLYCURVE.
                //
                //   In either case, this is representative of the
                //      previous curve's last point.
                //**********************************************

                if (lpCurve->wType == TT_PRIM_LINE)
                {
                    // All point are on the curve
                    for (i = 0; i < lpCurve->cpfx; ++i)
                    {
                        p.setValues(lpCurve->apfx[i].x.value, lpCurve->apfx[i].y.value);
                        p *= scale;
                        p -= offset;
                        _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));
                    }
                }
                else if (lpCurve->wType == TT_PRIM_QSPLINE)
                {
                    // All points apart from the last point of off the curve quadratric
                    // Bezier spline control points. The last point is on the curve.
                    // Between two consecutive control points, we have to insert a point
                    // that is on the curve. This point lies directly between the two control
                    // points.
                    short x1, x2, y1, y2;
                    for (i = 0; i < lpCurve->cpfx; ++i)
                    {
                        x2 = lpCurve->apfx[i].x.value;
                        y2 = lpCurve->apfx[i].y.value;
                        if (i >= lpCurve->cpfx - 1)
                        {
                            p.setValues(x2, y2);
                            p *= scale;
                            p -= offset;
                            _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));
                            break;
                        }
                        if (i > 0)
                        {
                            x1 = (x1 + x2) >> 1;
                            y1 = (y1 + y2) >> 1;
                            p.setValues(x1, y1);
                            p *= scale;
                            p -= offset;
                            _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));
                        }
                        p.setValues(x2, y2);
                        p *= scale;
                        p -= offset;
                        _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_QUAD));
                        x1 = x2;
                        y1 = y2;
                    }
                }
                else if (lpCurve->wType == TT_PRIM_CSPLINE)
                {
                    // TODO: Did not find any font until now that contains cubic
                    // splines, so this code is untested -pdaehne
                    for (i = 0; i < lpCurve->cpfx; ++i)
                    {
                        p.setValues(lpCurve->apfx[i].x.value, lpCurve->apfx[i].y.value);
                        p *= scale;
                        p -= offset;
                        if (i >= lpCurve->cpfx - 1)
                            _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));
                        else
                            _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_CUBIC));
                    }
                }
                else
                    // Oops! A POLYCURVE format we don't understand.
                    ; // error, error, error

                // Keep the end point
                endPoint = &(lpCurve->apfx[lpCurve->cpfx - 1]);

                // Move on to next curve in the contour.
                lpCurve = (LPTTPOLYCURVE)&(lpCurve->apfx[lpCurve->cpfx]);
            }

            // Check if the contour is valid, i.e. if it has more than two points.
            // When not, we simply delete the contour.
            if (_outline.back().size() < 3)
                _outline.erase(_outline.end() - 1);
            else
                // Add points to close the contour.
                // All contours are implied closed by TrueType definition.
                // Depending on the specific font and glyph being used, these
                // may not always be needed.
                if ((startPoint.x.value != endPoint->x.value) || (startPoint.y.value != endPoint->y.value))
                {
                    p.setValues(startPoint.x.value, startPoint.y.value);
                    p *= scale;
                    p -= offset;
                    _outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));
                }
        }
        else
            // Bad, bail, must have a bogus buffer.
            break; // error, error, error

        // Move on to next Contour.
        // Its header starts immediate after this contour
        lpHeader = (LPTTPOLYGONHEADER)(((LPSTR)lpHeader) + lpHeader->cb);
    }
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32VectorGlyph::~TextWIN32VectorGlyph() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32PixmapFace::TextWIN32PixmapFace(TextWIN32Backend *backend, HFONT hHoriFont, HFONT hVertFont, UInt32 size)
: TextPixmapFace(), _backend(backend), _hHoriFont(hHoriFont), _hVertFont(hVertFont)
{
    // Get information about the font
    getFontInfo(_backend->_hDC, _hHoriFont, _family, _style,
        _horiAscent, _horiDescent);

    // Set the size
    _size = size;

    // Determine vertical ascent and descent
    _vertAscent = -static_cast<Real32>(_size) / 2.f;
    _vertDescent = static_cast<Real32>(_size) / 2.f;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32PixmapFace::~TextWIN32PixmapFace()
{
    // Destroy the font objects
    DeleteObject(_hHoriFont);
    DeleteObject(_hVertFont);
}


//----------------------------------------------------------------------
// Lays out one line of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextWIN32PixmapFace::layout(const wstring &text, const TextLayoutParam &param,
                                 TextLayoutResult &layoutResult)
{
    // Initialize return values
    layoutResult.clear();
    if (param.horizontal == true)
        layoutResult.textBounds[1] = _horiAscent - _horiDescent;
    else
        layoutResult.textBounds[0] = _vertDescent - _vertAscent;
    layoutResult.lineBounds.push_back(layoutResult.textBounds);

    // Convert the unicode string to utf16
    vector<WCHAR> utf16Text;
    convertUnicodeToUTF16(text, utf16Text);
    vector<WCHAR>::size_type len = utf16Text.size();
    if (len == 0)
        return;

    // Select the font into the device context
    HGDIOBJ oldFont;
    if (param.horizontal == true)
        oldFont = SelectObject(_backend->_hDC, _hHoriFont);
    else
        oldFont = SelectObject(_backend->_hDC, _hVertFont);

    GCP_RESULTSW results;
    ZeroMemory(&results, sizeof(results));
    results.lStructSize = sizeof(results);
    results.lpDx = new int[len];
    results.lpGlyphs = new WCHAR[len];
    results.lpGlyphs[0] = 0; // needed by GCP_LIGATE
    results.nGlyphs = UInt32(len);
    DWORD dwFlags = GCP_GLYPHSHAPE | GCP_LIGATE | GCP_REORDER | GCP_USEKERNING;
    int nMaxExtent = 0;
    Real32 length = param.getLength(0);
    if (length > 0)
    {
        dwFlags |= GCP_JUSTIFY | GCP_KASHIDA | GCP_MAXEXTENT;
        nMaxExtent = length;
    }
    DWORD result = GetCharacterPlacementW(_backend->_hDC, &(utf16Text[0]), UInt32(len), nMaxExtent, &results, dwFlags);
    if (result != 0)
    {
        layoutResult.indices.reserve(results.nGlyphs);
        layoutResult.positions.reserve(results.nGlyphs);
        UINT j;
        Vec2f currPos;
        for (j = 0; j < results.nGlyphs; ++j)
        {
            // Get glyph
            const TextGlyph &glyph = getGlyph(results.lpGlyphs[j]);

            // Calculate position
            Vec2f pos;
            if (param.horizontal == true)
            {
                pos[0] = currPos.x() + glyph.getHoriBearingX();
                pos[1] = currPos.y() + glyph.getHoriBearingY();
                currPos[0] += results.lpDx[j];
            }
            else
            {
                pos[0] = currPos.x() + glyph.getVertBearingX();
                pos[1] = currPos.y() + glyph.getVertBearingY();
                currPos[1] -= results.lpDx[j];
            }
            layoutResult.indices.push_back(results.lpGlyphs[j]);
            layoutResult.positions.push_back(pos);
        }

        // Adjust the origin depending on the major and the minor alignment
        adjustLineOrigin(param, currPos, layoutResult);

        // Determine text bounds / line bounds
        if (param.horizontal == true)
            layoutResult.textBounds[0] = osgAbs(currPos.x());
        else
            layoutResult.textBounds[1] = osgAbs(currPos.y());
        OSG_ASSERT(layoutResult.lineBounds.empty() == false);
        layoutResult.lineBounds.front() = layoutResult.textBounds;
    }
    delete [] results.lpDx;
    delete [] results.lpGlyphs;

    // Unselect the font
    SelectObject(_backend->_hDC, oldFont);
}


//----------------------------------------------------------------------
// Creates a new Glyph object
// Author: pdaehne
//----------------------------------------------------------------------
unique_ptr<TextPixmapGlyph> TextWIN32PixmapFace::createGlyph(TextGlyph::Index glyphIndex)
{
    // We cannot create glyphs for invalid glyph indices
    if (glyphIndex == TextGlyph::INVALID_INDEX)
        return unique_ptr<TextPixmapGlyph>();

    // Select the vertical font into the device context
    HGDIOBJ oldFont = SelectObject(_backend->_hDC, _hVertFont);

    // Get the vertical metrics
    GLYPHMETRICS vpgm;
    MAT2 mat2 = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
    DWORD size = GetGlyphOutlineW(_backend->_hDC, glyphIndex, GGO_METRICS | GGO_GLYPH_INDEX,
                                  &vpgm, 0, 0, &mat2);
    if (size == GDI_ERROR)
    {
        SelectObject(_backend->_hDC, oldFont);
        return unique_ptr<TextPixmapGlyph>();
    }

    // Select the horizontal font into the device context
    SelectObject(_backend->_hDC, _hHoriFont);

    GLYPHMETRICS hpgm;
    size = GetGlyphOutlineW(_backend->_hDC, glyphIndex, GGO_GRAY8_BITMAP | GGO_GLYPH_INDEX,
                                  &hpgm, 0, 0, &mat2);
    if (size == GDI_ERROR)
    {
        SelectObject(_backend->_hDC, oldFont);
        return unique_ptr<TextPixmapGlyph>();
    }
    UInt8 *buffer;
    if (size == 0)
        buffer = 0;
    else
    {
        // Get the pixmap
        buffer = new UInt8[size];
        size = GetGlyphOutlineW(_backend->_hDC, glyphIndex, GGO_GRAY8_BITMAP | GGO_GLYPH_INDEX,
                                &hpgm, size, buffer, &mat2);
        if (size == GDI_ERROR)
        {
            delete [] buffer;
            SelectObject(_backend->_hDC, oldFont);
            return unique_ptr<TextPixmapGlyph>();
        }

        // The gray values in the buffer are between 0 and 64, inclusively.
        // So we have to scale them
        DWORD i;
        UInt8 *ptr = buffer;
        for (i = size; i > 0; --i)
        {
            *ptr = *ptr >= 64 ? 255 : *ptr << 2;
            ++ptr;
        }
    }
    SelectObject(_backend->_hDC, oldFont);

    // Create and return the new glyph object
    return unique_ptr<TextPixmapGlyph>(new TextWIN32PixmapGlyph(glyphIndex, hpgm, vpgm, buffer));
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32PixmapGlyph::TextWIN32PixmapGlyph(Index glyphIndex, const GLYPHMETRICS &hpgm,
                                           const GLYPHMETRICS &vpgm, UInt8 *pixmap)
: TextPixmapGlyph()
{
    _glyphIndex = glyphIndex;
    _width = hpgm.gmBlackBoxX;
    _pitch = (hpgm.gmBlackBoxX + 3) & ~3;
    _height = hpgm.gmBlackBoxY;
    _pixmap = pixmap;
    flipPixmap();

    // Determine horizontal glyph metrics
    _horiAdvance = hpgm.gmCellIncX;
    _horiBearingX = hpgm.gmptGlyphOrigin.x;
    _horiBearingY = hpgm.gmptGlyphOrigin.y;

    // Determine vertical glyph metrics
    // Hmmm, there is no useful information here for vertical layout -
    // the values provided are just the same as for horizontal layout.
    // So we have to guess resonable values -pdaehne
    //_vertAdvance = vpgm.gmCellIncY;
    //_vertBearingX = vpgm.gmptGlyphOrigin.x;
    //_vertBearingY = vpgm.gmptGlyphOrigin.y;
    _vertAdvance = -static_cast<Int32>(_height);
    _vertBearingX = -static_cast<Int32>(_width >> 1);
    _vertBearingY = 0;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32PixmapGlyph::~TextWIN32PixmapGlyph() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32TXFFace::TextWIN32TXFFace(const TextWIN32Backend *backend, HFONT hHoriFont, HFONT hVertFont, const TextTXFParam &param)
: TextTXFFace()
{
    // Get information about the font
    getFontInfo(backend->_hDC, hHoriFont, _family, _style,
        _horiAscent, _horiDescent);

    // Set the parameters
    _param = param;

    // Determine the scale factor & adjust ascent and descent
    _scale = 1.f / (_horiAscent - _horiDescent);
    _horiAscent *= _scale;
    _horiDescent *= _scale;

    // Determine vertical ascent and descent
    _vertAscent = -0.5f;
    _vertDescent = 0.5f;

    // Convert the unicode string to utf16
    vector<WCHAR> utf16Text;
    convertUnicodeToUTF16(param.getCharacters(), utf16Text);
    vector<WCHAR>::size_type len = utf16Text.size();
    if (len == 0)
    {
        DeleteObject(hHoriFont);
        DeleteObject(hVertFont);
        return;
    }

    // Select the font into the device context
    HGDIOBJ oldFont = SelectObject(backend->_hDC, hHoriFont);

    GCP_RESULTSW results;
    ZeroMemory(&results, sizeof(results));
    results.lStructSize = sizeof(results);
    results.lpGlyphs = new WCHAR[len];
    results.nGlyphs = UInt32(len);
    DWORD result = GetCharacterPlacementW(backend->_hDC, &(utf16Text[0]), UInt32(len), 0, &results, 0);
    if (result == 0)
    {
        delete [] results.lpGlyphs;
        SelectObject(backend->_hDC, oldFont);
        DeleteObject(hHoriFont);
        DeleteObject(hVertFont);
        return;
    }

    // Create all glyphs
    OSG_ASSERT(results.nGlyphs == param.getCharacters().length());
    UINT j;
    for (j = 0; j < results.nGlyphs; ++j)
    {
        // Select the vertical font into the device context
        SelectObject(backend->_hDC, hVertFont);

        // Get the vertical metrics
        GLYPHMETRICS vpgm;
        MAT2 mat2 = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
        DWORD size = GetGlyphOutlineW(backend->_hDC, results.lpGlyphs[j], GGO_METRICS | GGO_GLYPH_INDEX,
                                  &vpgm, 0, 0, &mat2);
        if (size == GDI_ERROR)
            continue;

        // Select the horizontal font into the device context
        SelectObject(backend->_hDC, hHoriFont);

        // Get the horizontal metrics
        GLYPHMETRICS hpgm;
        // Using GGO_METRICS gives a to small value for the width of the glyph...
        size = GetGlyphOutlineW(backend->_hDC, results.lpGlyphs[j], /*GGO_METRICS*/GGO_GRAY8_BITMAP | GGO_GLYPH_INDEX,
                             &hpgm, 0, 0, &mat2);
        if (size == GDI_ERROR)
            continue;

        _glyphMap.insert(GlyphMap::value_type(param.getCharacters()[j], new TextWIN32TXFGlyph(param.getCharacters()[j], this, _scale, hpgm, vpgm)));
    }

    // Calculate the positions of the glyphs on the texture
    prepareTexture(param);
    OSG_ASSERT(_texture != NULL);
    OSG_ASSERT(_texture->getSize() == static_cast<UInt32>(_texture->getWidth() * _texture->getHeight()));

    // Create the texture
    SelectObject(backend->_hDC, hHoriFont);
    vector<unsigned char> buffer;

    for (j = 0; j < results.nGlyphs; ++j)
    {
        // Get the pixmap
        GLYPHMETRICS hpgm;
        MAT2 mat2 = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
        DWORD size = GetGlyphOutlineW(backend->_hDC, results.lpGlyphs[j], GGO_GRAY8_BITMAP | GGO_GLYPH_INDEX,
                                  &hpgm, 0, 0, &mat2);
        if ((size == GDI_ERROR) || (size == 0))
            continue;
        buffer.resize(size);
        size = GetGlyphOutlineW(backend->_hDC, results.lpGlyphs[j], GGO_GRAY8_BITMAP | GGO_GLYPH_INDEX,
                                &hpgm, size, &(buffer[0]), &mat2);
        if (size == GDI_ERROR)
            continue;

        // Try to find the glyph in the glyphmap
        GlyphMap::iterator gIt = _glyphMap.find(param.getCharacters()[j]);
        if (gIt == _glyphMap.end())
            continue;
        OSG_ASSERT(gIt->second != 0);
        TextTXFGlyph *glyph = gIt->second;

        // Put the glyph pixmap into the texture
        unsigned char *src = &(buffer[0]);
        int bpl = (hpgm.gmBlackBoxX + 3) & ~3;
        src += bpl * (hpgm.gmBlackBoxY - 1);
        unsigned char *src2;
        UInt8 *dst = _texture->editData() + glyph->getX() + glyph->getY() * _texture->getWidth();
        UInt32 dstPitch = _texture->getWidth() - glyph->getPixmapWidth();
        UInt32 x, y;
        for (y = 0; y < glyph->getPixmapHeight(); ++y)
        {
            src2 = src;
            for (x = 0; x < glyph->getPixmapWidth(); ++x)
            {
                // The gray values in the buffer are between 0 and 64, inclusively.
                // So we have to scale them
                *dst++ = *src2 >= 64 ? 255 : *src2 << 2;
                ++src2;
            }
            src -= bpl;
            dst += dstPitch;
        }
    }


    delete [] results.lpGlyphs;

    // Unselect the font
    SelectObject(backend->_hDC, oldFont);

    // Cleanup
    DeleteObject(hHoriFont);
    DeleteObject(hVertFont);
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32TXFFace::~TextWIN32TXFFace() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextWIN32TXFGlyph::TextWIN32TXFGlyph(Index glyphIndex, TextWIN32TXFFace *face, Real32 scale,
                                     const GLYPHMETRICS &hpgm, const GLYPHMETRICS &vpgm)
: TextTXFGlyph()
{
    _glyphIndex = glyphIndex;
    _scale = scale;
    _width = hpgm.gmBlackBoxX;
    _height = hpgm.gmBlackBoxY;

    // Determine horizontal glyph metrics
    _horiAdvance = static_cast<Real32>(hpgm.gmCellIncX) * _scale;
    _horiBearingX = hpgm.gmptGlyphOrigin.x;
    _horiBearingY = hpgm.gmptGlyphOrigin.y;

    // Determine vertical glyph metrics
    // Hmmm, there is no useful information here for vertical layout -
    // the values provided are just the same as for horizontal layout.
    // So we have to guess resonable values -pdaehne
    //_vertAdvance = static_cast<Real32>(vpgm.gmCellIncY) * _scale;
    //_vertBearingX = vpgm.gmptGlyphOrigin.x;
    //_vertBearingY = vpgm.gmptGlyphOrigin.y;
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
TextWIN32TXFGlyph::~TextWIN32TXFGlyph() {}


OSG_END_NAMESPACE


#endif // _WIN32
