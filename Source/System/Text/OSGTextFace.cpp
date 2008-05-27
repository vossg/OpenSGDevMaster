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

#include "OSGTextFace.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#ifdef __sgi
# include <cassert>
# include <cfloat>
#else
# include <cassert>
# include <cfloat>
#endif


using namespace std;


OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFace::~TextFace() {}


//----------------------------------------------------------------------
// Lays out one line of text.
// Author: pdaehne
//----------------------------------------------------------------------
void TextFace::layout(const string &utf8Text,
                      const TextLayoutParam &param,
                      TextLayoutResult &result)
{
    // Convert the UTF8 string to a unicode string
    wstring text;
    convertUTF8ToUnicode(utf8Text, text);

    // Call the unicode layout method
    layout(text, param, result);
}


//----------------------------------------------------------------------
// Lays out multiple lines of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextFace::layout(const vector<string> &lines,
                      const TextLayoutParam &param,
                      TextLayoutResult &result)
{
    // Convert the UTF8 strings to unicode strings
    vector<wstring> unicodeLines(lines.size());
    vector<wstring>::iterator unicodeLineIt;
    vector<string>::const_iterator lineIt;
    for (lineIt = lines.begin(), unicodeLineIt = unicodeLines.begin();
         lineIt != lines.end(); ++lineIt, ++unicodeLineIt)
        convertUTF8ToUnicode(*lineIt, *unicodeLineIt);

    // Call the unicode layout method
    layout(unicodeLines, param, result);
}


//----------------------------------------------------------------------
// Lays out multiple lines of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextFace::layout(const vector<wstring> &lines,
                      const TextLayoutParam &param,
                      TextLayoutResult &result)
{
    // Initialize return values
    result.clear();

    TextLayoutParam lineParam = param;
    Vec2f offset, lineOffset;
    if (param.horizontal == true)
    {
        Real32 lineHeight = _horiAscent - _horiDescent;
        Real32 spacing = param.spacing * lineHeight;
        Real32 leading = spacing - lineHeight;
        Real32 fullHeight = spacing * lines.size() - leading;
        result.textBounds[1] = fullHeight;
        lineParam.minorAlignment = TextLayoutParam::ALIGN_FIRST;
        if (param.topToBottom == true)
        {
            lineOffset[1] = -spacing;
            switch (param.minorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                    break;
                case TextLayoutParam::ALIGN_BEGIN:
                    offset[1] = -_horiAscent;
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[1] = -_horiAscent + fullHeight / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    offset[1] = -_horiAscent + fullHeight;
                    break;
            }
        }
        else // topToBottom == false
        {
            lineOffset[1] = spacing;
            switch (param.minorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                    break;
                case TextLayoutParam::ALIGN_BEGIN:
                    offset[1] = -_horiDescent;
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[1] = -_horiDescent - fullHeight / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    offset[1] = -_horiDescent - fullHeight;
                    break;
            }
        }
    }
    else // horizontal == false
    {
        Real32 lineHeight = _vertDescent - _vertAscent;
        Real32 spacing = param.spacing * lineHeight;
        Real32 leading = spacing - lineHeight;
        Real32 fullHeight = spacing * lines.size() - leading;
        result.textBounds[0] = fullHeight;
        lineParam.minorAlignment = TextLayoutParam::ALIGN_FIRST;
        if (param.leftToRight == true)
        {
            lineOffset[0] = spacing;
            switch (param.minorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                    break;
                case TextLayoutParam::ALIGN_BEGIN:
                    offset[0] = -_vertAscent;
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[0] = -_vertAscent - fullHeight / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    offset[0] = -_vertAscent - fullHeight;
                    break;
            }
        }
        else // leftToRight == false
        {
            lineOffset[0] = -spacing;
            switch (param.minorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                    break;
                case TextLayoutParam::ALIGN_BEGIN:
                    offset[0] = -_vertDescent;
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[0] = -_vertDescent + fullHeight / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    offset[0] = -_vertDescent + fullHeight;
                    break;
            }
        }
    }

    result.lineBounds.reserve(lines.size());
    TextLayoutResult lineResult;
    Real32 maxExtend = 0.f;
    UInt32 lineIndex;
    for (lineIndex = 0; lineIndex < lines.size(); ++lineIndex)
    {
        lineParam.setLength(param.getLength(lineIndex));
        layout(lines[lineIndex], lineParam, lineResult);
        UInt32 i, numGlyphs = lineResult.getNumGlyphs();
        for (i = 0; i < numGlyphs; ++i)
        {
            result.indices.push_back(lineResult.indices[i]);
            result.positions.push_back(lineResult.positions[i] + offset);
        }
        assert(lineResult.lineBounds.empty() == false);
        result.lineBounds.push_back(lineResult.lineBounds.front());
        Real32 extend = lineResult.lineBounds.front()[param.horizontal == true ? 0 : 1];
        if (extend > maxExtend)
            maxExtend = extend;
        offset += lineOffset;
    }
    result.textBounds[param.horizontal == true ? 0 : 1] = maxExtend;
}


//----------------------------------------------------------------------
// Calculates the bounding box of a text after layout
// Author: pdaehne
//----------------------------------------------------------------------
void TextFace::calculateBoundingBox(const TextLayoutResult &layoutResult, Vec2f &lowerLeft, Vec2f &upperRight)
{
    // Initialize bounding box
    lowerLeft.setValues(FLT_MAX, FLT_MAX);
    upperRight.setValues(-FLT_MAX, -FLT_MAX);

    UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    for (i = 0; i < numGlyphs; ++i)
    {
        const TextGlyph &glyph = getGlyph(layoutResult.indices[i]);
        Real32 width = glyph.getWidth();
        Real32 height = glyph.getHeight();
        // Don't handle invisible glyphs
        if ((width <= 0.f) || (height <= 0.f))
            continue;

        // Calculate coodinates
        const Vec2f &pos = layoutResult.positions[i];
        Real32 left = pos.x();
        Real32 right = left + glyph.getWidth();
        Real32 top = pos.y();
        Real32 bottom = top - glyph.getHeight();

        // Adjust bounding box
        if (lowerLeft[0] > left)
            lowerLeft[0] = left;
        if (upperRight[0] < right)
            upperRight[0] = right;
        if (upperRight[1] < top)
            upperRight[1] = top;
        if (lowerLeft[1] > bottom)
            lowerLeft[1] = bottom;
    }
}


//----------------------------------------------------------------------
// Converts a UTF8 sequence to unicode
// Author: pdaehne
//----------------------------------------------------------------------
static wchar_t utf8Char2Unicode(const char *&str)
{
    char c = *str++;
    if ((c & 0x80) == 0)
        return c;
    if (((c & 0xc0) == 0x80) || ((c & 0xfe) == 0xfe)) // should never happen
        return static_cast<unsigned char>(c);
    char mask = 0xe0, value = 0xc0;
    int i;
    for (i = 1; i < 6; ++i)
    {
        if ((c & mask) == value)
            break;
        value = mask;
        mask >>= 1;
    }
    wchar_t result = c & ~mask;
    for (; i > 0; --i)
    {
        c = *str++;
        if ((c & 0xc0) != 0x80) // should never happen
            ; // TODO
        result <<= 6;
        result |= c & 0x3f;
    }
    return result;
}


//----------------------------------------------------------------------
// Converts a UTF8 encoded string to a unicode string
// See the following document for more information:
// RFC2279: UTF-8, a transformation format of ISO 10646
// Author: pdaehne
//----------------------------------------------------------------------
void TextFace::convertUTF8ToUnicode(const string &utf8Text, wstring &text)
{
    // Clear and prepare the result string
    text.erase();
    text.reserve(utf8Text.length());

    // Transform UTF8 sequences to UTF16 sequences
    const char *pos = utf8Text.c_str();
    while (*pos != '\0')
        text.append(1, utf8Char2Unicode(pos));
}


//----------------------------------------------------------------------
// Justifies one line of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextFace::justifyLine(const TextLayoutParam &param,
                           const vector<UInt32> &spaceIndices,
                           Vec2f &currPos, TextLayoutResult &layoutResult) const
{
    // We need at least two glyphs for justification
    UInt32 numGlyphs = layoutResult.positions.size();
    if (numGlyphs < 2)
        return;

    // Determine how much additional white space we have
    Real32 actualLength = osgAbs(param.horizontal == true ? currPos.x() : currPos.y());
    Real32 delta = param.getLength(0) - actualLength;

    // Determine the amount of space that is added between glyphs and words
    UInt32 numSpaces = spaceIndices.size();
    numGlyphs -= 1 + numSpaces;
    // Space added between glyphs is by this factor smaller than space added between words
    Real32 factor = 0.5;
    Real32 spaceDelta = delta / (static_cast<Real32>(numSpaces) + static_cast<Real32>(numGlyphs) * factor);
    Real32 glyphDelta = spaceDelta * factor;
    Vec2f spaceOffset, glyphOffset;
    if (param.horizontal == true)
        if (param.leftToRight == true)
        {
            spaceOffset.setValues(spaceDelta, 0.f);
            glyphOffset.setValues(glyphDelta, 0.f);
        }
        else
        {
            spaceOffset.setValues(-spaceDelta, 0.f);
            glyphOffset.setValues(-glyphDelta, 0.f);
        }
    else
        if (param.topToBottom == true)
        {
            spaceOffset.setValues(0.f, -spaceDelta);
            glyphOffset.setValues(0.f, -glyphDelta);
        }
        else
        {
            spaceOffset.setValues(0.f, spaceDelta);
            glyphOffset.setValues(0.f, glyphDelta);
        }

    // Adjust the positions of the glyphs
    Vec2f offset;
    vector<UInt32>::const_iterator it = spaceIndices.begin();
    UInt32 i;
    for (i = 1; i < layoutResult.positions.size(); ++i)
    {
        if ((it == spaceIndices.end()) || (i < *it))
            offset += glyphOffset;
        else
        {
            offset += spaceOffset;
            ++it;
        }
        layoutResult.positions[i] += offset;
    }
    currPos += offset;
}


//----------------------------------------------------------------------
// Adjusts the positions of glyphs, depending on the alignment
// Author: pdaehne
//----------------------------------------------------------------------
void TextFace::adjustLineOrigin(const TextLayoutParam &param,
                                const Vec2f &currPos,
                                TextLayoutResult &layoutResult) const
{
    Vec2f offset;
    if (param.horizontal == true)
    {
        switch (param.minorAlignment)
        {
            default:
            case TextLayoutParam::ALIGN_FIRST:  offset[1] = 0.f; break;
            case TextLayoutParam::ALIGN_BEGIN:  offset[1] = -_horiAscent; break;
            case TextLayoutParam::ALIGN_MIDDLE: offset[1] = -(_horiAscent + _horiDescent) / 2.f; break;
            case TextLayoutParam::ALIGN_END:    offset[1] = -_horiDescent; break;
        }
        if (param.leftToRight == true)
        {
            switch (param.majorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                case TextLayoutParam::ALIGN_BEGIN:
                    if (currPos.x() < 0)
                        offset[0] = -currPos.x();
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[0] = -currPos.x() / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    if (currPos.x() > 0)
                        offset[0] = -currPos.x();
                    break;
            }
        }
        else // leftToRight == false
        {
            switch (param.majorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                case TextLayoutParam::ALIGN_BEGIN:
                    if (currPos.x() > 0)
                        offset[0] = -currPos.x();
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[0] = -currPos.x() / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    if (currPos.x() < 0)
                        offset[0] = -currPos.x();
                    break;
            }
        }
    }
    else // param.horizontal == false
    {
        switch (param.minorAlignment)
        {
            default:
            case TextLayoutParam::ALIGN_FIRST:  offset[0] = 0.f; break;
            case TextLayoutParam::ALIGN_BEGIN:  offset[0] = -_vertAscent; break;
            case TextLayoutParam::ALIGN_MIDDLE: offset[0] = -(_vertAscent + _vertDescent) / 2.f; break;
            case TextLayoutParam::ALIGN_END:    offset[0] = -_vertDescent; break;
        }
        if (param.topToBottom == true)
        {
            switch (param.majorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                case TextLayoutParam::ALIGN_BEGIN:
                    if (currPos.y() > 0)
                        offset[1] = -currPos.y();
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[1] = -currPos.y() / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    if (currPos.y() < 0)
                        offset[1] = -currPos.y();
                    break;
            }
        }
        else // TopToBottom == false
        {
            switch (param.majorAlignment)
            {
                default:
                case TextLayoutParam::ALIGN_FIRST:
                case TextLayoutParam::ALIGN_BEGIN:
                    if (currPos.y() < 0)
                        offset[1] = -currPos.y();
                    break;
                case TextLayoutParam::ALIGN_MIDDLE:
                    offset[1] = -currPos.y() / 2.f;
                    break;
                case TextLayoutParam::ALIGN_END:
                    if (currPos.y() > 0)
                        offset[1] = -currPos.y();
                    break;
            }
        }
    }

    // Adjust all glyph positions
    if ((offset.x() != 0.f) || (offset.y() != 0.f))
    {
        vector<Vec2f>::iterator it;
        for (it = layoutResult.positions.begin(); it != layoutResult.positions.end(); ++it)
            *it += offset;
    }
}


OSG_END_NAMESPACE
