/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGTextMacBackend.h"
#include "OSGBaseTypes.h"


#if defined(__APPLE__) || defined(OSG_DO_DOC)


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

#include <ApplicationServices/ApplicationServices.h>

using namespace std;
OSG_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// MacOS X specific implementation of the TextVectorFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextMacVectorFace: public TextVectorFace
{
public:

    // Constructor
    TextMacVectorFace(ATSUStyle horiFontStyle);

    // Destructor
    virtual ~TextMacVectorFace();

    // Lays out one line of text
    virtual void layout(const wstring &text, const TextLayoutParam &param,
                        TextLayoutResult &layoutResult);

protected:

    // Creates a new Glyph object
    virtual auto_ptr<TextVectorGlyph> createGlyph(TextGlyph::Index glyphIndex);

private:

    // The style objects that define the font
    ATSUStyle _horiFontStyle;
    ATSUStyle _vertFontStyle;

    // The layout objects that handle the text layout
    ATSUTextLayout _horiTextLayout;
    ATSUTextLayout _vertTextLayout;
};


//----------------------------------------------------------------------
// MacOS X specific implementation of the TextVectorGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextMacVectorGlyph: public TextVectorGlyph
{
public:

    // Constructor
    TextMacVectorGlyph(Index glyphIndex, Real32 scale, ATSUStyle horiFontStyle, ATSUStyle vertFontStyle);

    // Destructor
    virtual ~TextMacVectorGlyph();
};


//----------------------------------------------------------------------
// MacOS X specific implementation of the TextPixmapFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextMacPixmapFace: public TextPixmapFace
{
public:

    // Constructor
    TextMacPixmapFace(ATSUStyle horiFontStyle);

    // Destructor
    virtual ~TextMacPixmapFace();

    // Lays out one line of text
    virtual void layout(const wstring &text, const TextLayoutParam &param,
                        TextLayoutResult &layoutResult);

protected:

    // Creates a new Glyph object
    virtual auto_ptr<TextPixmapGlyph> createGlyph(TextGlyph::Index glyphIndex);

private:

    const TextPixmapGlyph &getPixmapGlyph(const ATSLayoutRecord &layoutRecord, bool horizontal);

    // The style objects that define the font
    ATSUStyle _horiFontStyle;
    ATSUStyle _vertFontStyle;

    // The layout objects that handle the text layout
    ATSUTextLayout _horiTextLayout;
    ATSUTextLayout _vertTextLayout;
};


//----------------------------------------------------------------------
// MacOS X specific implementation of the TextPixmapGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextMacPixmapGlyph: public TextPixmapGlyph
{
public:

    // Constructor
    TextMacPixmapGlyph(Index glyphIndex, UInt32 width, UInt32 height,
        Real32 horiAdvance, Int32 horiBearingX, Int32 horiBearingY,
        Real32 vertAdvance, Int32 vertBearingX, Int32 vertBearingY,
        UInt8 *pixmap);

    // Destructor
    virtual ~TextMacPixmapGlyph();
};


//----------------------------------------------------------------------
// MacOS X specific implementation of the TextTXFFace class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextMacTXFFace: public TextTXFFace
{
public:

    // Constructor
    TextMacTXFFace(ATSUStyle horiFontStyle, const TextTXFParam &param);

    // Destructor
    virtual ~TextMacTXFFace();

private:

    void createGlyphs(ATSUStyle horiFontStyle, ATSUStyle vertFontStyle,
                      ATSUTextLayout horiTextLayout, ATSUTextLayout vertTextLayout,
                      const TextTXFParam &param);
};


//----------------------------------------------------------------------
// MacOS X specific implementation of the TextTXFGlyph class
// Author: pdaehne
//----------------------------------------------------------------------

/*! \nohierarchy 
 */

class TextMacTXFGlyph: public TextTXFGlyph
{
public:

    // Constructor
    TextMacTXFGlyph(Index glyphIndex, Real32 scale, const ATSGlyphScreenMetrics &horiMetrics, const ATSGlyphScreenMetrics &vertMetrics);

    // Destructor
    virtual ~TextMacTXFGlyph();
};


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacBackend::TextMacBackend(): TextBackend() {}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacBackend::~TextMacBackend() {}


//----------------------------------------------------------------------
// Returns the family name of a font
// Author: pdaehne
//----------------------------------------------------------------------
static string getFamilyName(ATSUFontID fontID)
{
    ItemCount fontNameIndex;
    OSStatus result = ATSUFindFontName(fontID, kFontFamilyName, kFontNoPlatformCode,
                                       kFontNoScriptCode, kFontNoLanguageCode,
                                       0, 0, 0, &fontNameIndex);
    if (result != noErr)
        return string();
    ByteCount actualNameLength;
    result = ATSUGetIndFontName(fontID, fontNameIndex, 0, 0, &actualNameLength,
                                0, 0, 0, 0);
    if ((result != noErr) || (actualNameLength == 0))
        return string();
    vector<char> name;
    name.resize(actualNameLength);
    FontPlatformCode fontNamePlatform;
    result = ATSUGetIndFontName(fontID, fontNameIndex, actualNameLength, &(name.front()), 0,
                                0, &fontNamePlatform, 0, 0);
    if ((result != noErr) || (actualNameLength == 0))
        return string();
    CFStringRef str = 0;
    switch (fontNamePlatform)
    {
        case kFontUnicodePlatform:
        case kFontMicrosoftPlatform: // ???
            str = CFStringCreateWithBytes(kCFAllocatorDefault, reinterpret_cast< ::UInt8*>(&(name.front())),
                                          actualNameLength, kCFStringEncodingUnicode, false);
            break;
        case kFontMacintoshPlatform:
            str = CFStringCreateWithBytes(kCFAllocatorDefault, reinterpret_cast< ::UInt8*>(&(name.front())),
                                          actualNameLength, kCFStringEncodingMacRoman, false);
            break;
        default:
            return string();
    }
    if (str == 0)
        return string();
    CFDataRef data = CFStringCreateExternalRepresentation(kCFAllocatorDefault, str, kCFStringEncodingUTF8, ' ');
    CFRelease(str);
    if (data == 0)
        return string();
    string familyName(reinterpret_cast<const char*>(CFDataGetBytePtr(data)),
                      static_cast<string::size_type>(CFDataGetLength(data)));
    CFRelease(data);
    return familyName;
}


//----------------------------------------------------------------------
// Tries to find a font
// Author: pdaehne
//----------------------------------------------------------------------
static ATSUStyle findFont(const string &family, TextFace::Style style, UInt32 size)
{
    // Handle generic family names
    string f;
    if (family == "SERIF")
        f = "Times New Roman";
    else if (family == "SANS")
        f = "Arial";
    else if (family == "TYPEWRITER")
        f = "Courier";
    else
        f = family;

    // Get the number of fonts installed
    ItemCount fontCount;
    OSStatus result = ATSUFontCount(&fontCount);
    if ((result != noErr) || (fontCount == 0))
        return 0;

    // Get the IDs of all fonts
    vector<ATSUFontID> fontIDs;
    fontIDs.resize(fontCount);
    result = ATSUGetFontIDs(&(fontIDs.front()), fontCount, &fontCount);
    if (result != noErr)
        return 0;

    // Try to find the font
    ItemCount i;
    for (i = 0; i < fontCount; ++i)
    {
        string familyName = getFamilyName(fontIDs[i]);
        if (familyName == f)
            break;
    }
    if (i >= fontCount)
        return 0;
    ATSUFontID fontID = fontIDs[i];

    FMFontFamily fontFamily;
    result = FMGetFontFamilyInstanceFromFont(fontID, &fontFamily, 0);
    if (result != noErr)
        return 0;
    FMFontStyle fStyle;
    switch (style)
    {
        default:
            FWARNING(("Invalid font style parameter.\n"));
            // intentionally fall through
        case TextFace::STYLE_PLAIN:      fStyle = normal;        break;
        case TextFace::STYLE_BOLD:       fStyle = bold;          break;
        case TextFace::STYLE_ITALIC:     fStyle = italic;        break;
        case TextFace::STYLE_BOLDITALIC: fStyle = bold | italic; break;
    }
    result = FMGetFontFromFontFamilyInstance(fontFamily, fStyle, &fontID, 0);
    if ((result != noErr) || (fontID == kATSUInvalidFontID))
        return 0;

    // Create style object
    ATSUStyle fontStyle;
    result = ATSUCreateStyle(&fontStyle);
    if (result != noErr)
        return 0;

    // Set style attributes
    //Boolean bold = ((style == TextFace::STYLE_BOLD) || (style == TextFace::STYLE_BOLDITALIC)) ? TRUE : FALSE;
    //Boolean italic = ((style == TextFace::STYLE_ITALIC) || (style == TextFace::STYLE_BOLDITALIC)) ? TRUE : FALSE;
    Fixed fontSize = IntToFixed(size);
    ATSUAttributeTag attributeTags[] = { kATSUFontTag, /*kATSUQDBoldfaceTag, kATSUQDItalicTag,*/ kATSUSizeTag };
    ByteCount attributeSizes[] = { sizeof(fontID), /*sizeof(bold), sizeof(italic),*/ sizeof(fontSize) };
    ATSUAttributeValuePtr attributeValues[] = { &fontID, /*&bold, &italic,*/ &fontSize };
    result = ATSUSetAttributes(fontStyle, /*4*/2, attributeTags, attributeSizes, attributeValues);
    if (result != noErr)
    {
        ATSUDisposeStyle(fontStyle);
        return 0;
    }

    return fontStyle;
}


//----------------------------------------------------------------------
// Creates a new vector face
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFaceTransitPtr TextMacBackend::createVectorFace(
    const string &family, TextFace::Style style)
{
    TextVectorFaceTransitPtr retVal;
    
    // Try to find the font
    ATSUStyle horiFontStyle = findFont(family, style, 1000);
    if (horiFontStyle != 0)
    {
        // Switch off hinting
        ATSStyleRenderingOptions styleRenderingOptions = kATSStyleNoHinting;
        ATSUAttributeTag attributeTag = kATSUStyleRenderingOptionsTag;
        ByteCount attributeSize = sizeof(styleRenderingOptions);
        ATSUAttributeValuePtr attributeValue = &styleRenderingOptions;
        OSStatus result = ATSUSetAttributes(horiFontStyle, 1, &attributeTag, &attributeSize, &attributeValue);
        // We don't care for errors - this is not really an important attribute
        
        // Create the new face object
        retVal = new TextMacVectorFace(horiFontStyle);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Creates a new pixmap face
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFaceTransitPtr TextMacBackend::createPixmapFace(
    const string &family, TextFace::Style style, UInt32 size)
{
    TextPixmapFaceTransitPtr retVal;
    
    // Try to find the font
    ATSUStyle horiFontStyle = findFont(family, style, size);
    if (horiFontStyle != 0)
    {
        retVal = new TextMacPixmapFace(horiFontStyle);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Creates a new TXF face
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFaceTransitPtr TextMacBackend::createTXFFace(
    const string &family, TextFace::Style style, const TextTXFParam &param)
{
    TextTXFFaceTransitPtr retVal;
    
    // Try to find the font
    ATSUStyle horiFontStyle = findFont(family, style, param.size);
    if (horiFontStyle != 0)
    {
        // Create the new face object
        retVal = new TextMacTXFFace(horiFontStyle, param);
    }
    
    return retVal;
}


//----------------------------------------------------------------------
// Returns the names of all font families available
// Author: pdaehne
//----------------------------------------------------------------------
void TextMacBackend::getFontFamilies(vector<string> &families)
{
    families.clear();

    // Get the number of fonts installed
    ItemCount fontCount;
    OSStatus result = ATSUFontCount(&fontCount);
    if ((result != noErr) || (fontCount == 0))
        return;

    // Get the IDs of all fonts
    vector<ATSUFontID> fontIDs;
    fontIDs.resize(fontCount);
    result = ATSUGetFontIDs(&(fontIDs.front()), fontCount, &fontCount);
    if (result != noErr)
        return;

    // Put all font families into the vector
    ItemCount i;
    set<string> familySet;
    for (i = 0; i < fontCount; ++i)
    {
        string familyName = getFamilyName(fontIDs[i]);
        if (familyName.empty() == false)
            familySet.insert(familyName);
    }
    families.assign(familySet.begin(), familySet.end());
}


//----------------------------------------------------------------------
// Tries to get information about the face
// Author: pdaehne
//----------------------------------------------------------------------
static void getFaceInfo(ATSUStyle horiFontStyle, ATSUStyle vertFontStyle, string &family, TextFace::Style &style,
    Real32 &horiAscent, Real32 &horiDescent,
    Real32 &vertAscent, Real32 &vertDescent)
{
    // Try to get the family name
    ATSUFontID fontID;
    OSStatus result = ATSUGetAttribute(horiFontStyle, kATSUFontTag, sizeof(fontID), &fontID, 0);
    if (((result == noErr) || (result == kATSUNotSetErr)) && (fontID != kATSUInvalidFontID))
        family = getFamilyName(fontID);
    else
        family.erase();

    // Try to get style
    Boolean bold;
    result = ATSUGetAttribute(horiFontStyle, kATSUQDBoldfaceTag, sizeof(bold), &bold, 0);
    if ((result != noErr) && (result != kATSUNotSetErr))
        bold = false;
    Boolean italic;
    result = ATSUGetAttribute(horiFontStyle, kATSUQDItalicTag, sizeof(italic), &italic, 0);
    if ((result != noErr) && (result != kATSUNotSetErr))
        italic = false;
    style = (bold == TRUE) ?
        (italic == TRUE ? TextFace::STYLE_BOLDITALIC : TextFace::STYLE_BOLD) :
        (italic == TRUE ? TextFace::STYLE_ITALIC : TextFace::STYLE_PLAIN);

    // Try to get ascent
    ATSUTextMeasurement measurement;
    result = ATSUGetAttribute(horiFontStyle, kATSUAscentTag, sizeof(measurement), &measurement, 0);
    horiAscent = ((result == noErr) || (result == kATSUNotSetErr)) ? FixedToFloat(measurement) : 0.f;
    result = ATSUGetAttribute(vertFontStyle, kATSUAscentTag, sizeof(measurement), &measurement, 0);
    vertAscent = ((result == noErr) || (result == kATSUNotSetErr)) ? -FixedToFloat(measurement) : 0.f;

    // Try to get descent
    result = ATSUGetAttribute(horiFontStyle, kATSUDescentTag, sizeof(measurement), &measurement, 0);
    horiDescent = ((result == noErr) || (result == kATSUNotSetErr)) ? -FixedToFloat(measurement) : 0.f;
    result = ATSUGetAttribute(vertFontStyle, kATSUDescentTag, sizeof(measurement), &measurement, 0);
    vertDescent = ((result == noErr) || (result == kATSUNotSetErr)) ? FixedToFloat(measurement) : 0.f;
}


//----------------------------------------------------------------------
// Creates all ATSU objects needed by a face
// Author: pdaehne
//----------------------------------------------------------------------
static void createATSUObjects(ATSUStyle horiFontStyle, ATSUStyle &vertFontStyle, ATSUTextLayout &horiTextLayout, ATSUTextLayout &vertTextLayout)
{
    // Create vertical style object
    OSStatus result = ATSUCreateAndCopyStyle(horiFontStyle, &vertFontStyle);
    if (result != noErr)
        vertFontStyle = 0;
    else
    {
        ATSUVerticalCharacterType verticalCharacterType = kATSUStronglyVertical;
        ATSUAttributeTag attributeTags[] = { kATSUVerticalCharacterTag };
        ByteCount attributeSizes[] = { sizeof(verticalCharacterType) };
        ATSUAttributeValuePtr attributeValues[] = { &verticalCharacterType };
        result = ATSUSetAttributes(vertFontStyle, 1, attributeTags, attributeSizes, attributeValues);
    }

    // Create the layout objects
    result = ATSUCreateTextLayout(&horiTextLayout);
    if (result != noErr)
        horiTextLayout = 0;
    result = ATSUCreateAndCopyTextLayout(horiTextLayout, &vertTextLayout);
    if (result != noErr)
        vertTextLayout = 0;
    else
    {
        Fixed lineRotation = IntToFixed(-90);
        ATSUAttributeTag layoutAttributeTags[] = { kATSULineRotationTag };
        ByteCount layoutAttributeSizes[] = { sizeof(lineRotation) };
        ATSUAttributeValuePtr layoutAttributeValues[] = { &lineRotation };
        result = ATSUSetLayoutControls(vertTextLayout, 1, layoutAttributeTags, layoutAttributeSizes, layoutAttributeValues);
    }
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacVectorFace::TextMacVectorFace(ATSUStyle horiFontStyle)
: TextVectorFace(), _horiFontStyle(horiFontStyle), _vertFontStyle(0), _horiTextLayout(0), _vertTextLayout(0)
{
    // Create all ATSU objects
    createATSUObjects(_horiFontStyle, _vertFontStyle, _horiTextLayout, _vertTextLayout);

    // Try to get information about the face
    getFaceInfo(_horiFontStyle, _vertFontStyle, _family, _style,
        _horiAscent, _horiDescent, _vertAscent, _vertDescent);

    // Determine the scale factor
    _scale = 1.f / (_horiAscent - _horiDescent);

    // Determine ascent
    _horiAscent *= _scale;
    _vertAscent = -0.5f;

    // Determine descent
    _horiDescent *= _scale;
    _vertDescent = 0.5f;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacVectorFace::~TextMacVectorFace()
{
    // Dispose the layout objects
    ATSUDisposeTextLayout(_horiTextLayout);
    ATSUDisposeTextLayout(_vertTextLayout);

    // Dispose style objects
    ATSUDisposeStyle(_horiFontStyle);
    ATSUDisposeStyle(_vertFontStyle);
}


//----------------------------------------------------------------------
// Converts a unicode string to utf16
// RFC2781: UTF-16, an encoding of ISO 10646
// Author: pdaehne
//----------------------------------------------------------------------
static void convertUnicodeToUTF16(const wstring &text, vector<UniChar> &utf16Text)
{
    UniCharCount i, textTotalLength = text.length();
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
void TextMacVectorFace::layout(const wstring &text, const TextLayoutParam &param,
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
    vector<UniChar> utf16Text;
    convertUnicodeToUTF16(text, utf16Text);
    if (utf16Text.empty() == true)
        return;

    // Check whether we have to use the horizontal or vertical ATSUI objects
    ATSUStyle fontStyle;
    ATSUTextLayout textLayout;
    if (param.horizontal == true)
    {
        fontStyle = _horiFontStyle;
        textLayout = _horiTextLayout;
    }
    else
    {
        fontStyle = _vertFontStyle;
        textLayout = _vertTextLayout;
    }

    // Set the length
    Real32 length = param.getLength(0);
    Fract justFactor = length <= 0.f ? kATSUNoJustification : kATSUFullJustification;
    ATSUTextMeasurement width = FloatToFixed(length <= 0.f ? 0.f : length / _scale);
    ATSUAttributeTag layoutAttributeTags[] = { kATSULineJustificationFactorTag, kATSULineWidthTag };
    ByteCount layoutAttributeSizes[] = { sizeof(justFactor), sizeof(width) };
    ATSUAttributeValuePtr layoutAttributeValues[] = { &justFactor, &width };
    ATSUSetLayoutControls(textLayout, 2, layoutAttributeTags, layoutAttributeSizes, layoutAttributeValues);

    // Set the text
    OSStatus result = ATSUSetTextPointerLocation(textLayout, &(utf16Text[0]), kATSUFromTextBeginning, kATSUToTextEnd, utf16Text.size());
    if (result != noErr)
        return;

    // Set the style object
    result = ATSUSetRunStyle(textLayout, fontStyle, kATSUFromTextBeginning, kATSUToTextEnd);
    if (result != noErr)
        return;

    // Get the layout records
    ATSLayoutRecord *layoutRecords;
    ItemCount numRecords;
    result = ATSUDirectGetLayoutDataArrayPtrFromTextLayout(textLayout, kATSUFromTextBeginning,
        kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords, &numRecords);
    if (result != noErr)
        return;
    Fixed *deltaYs;
    ItemCount numDeltaYs;
    result = ATSUDirectGetLayoutDataArrayPtrFromTextLayout(textLayout, kATSUFromTextBeginning,
        kATSUDirectDataBaselineDeltaFixedArray, (void**)&deltaYs, &numDeltaYs);
    if (result != noErr)
        deltaYs = 0;

    // Calculate the positions of the glyphs
    layoutResult.indices.reserve(numRecords);
    layoutResult.positions.reserve(numRecords);
    ItemCount j;
    Vec2f currPos;
    for (j = 0; j < numRecords; ++j)
    {
        ATSGlyphRef glyphID = layoutRecords[j].glyphID;
        currPos[0] = FixedToFloat(layoutRecords[j].realPos) * _scale;
        currPos[1] = (deltaYs != 0) && (j < numDeltaYs) ? -FixedToFloat(deltaYs[j]) * _scale: 0.f;
        const TextVectorGlyph &glyph = getVectorGlyph(glyphID);
        if (param.horizontal == true)
        {
            currPos[0] += glyph.getHoriBearingX();
            currPos[1] += glyph.getHoriBearingY();
        }
        else
        {
            float h = currPos.x();
            currPos[0] = currPos.y() + glyph.getVertBearingX();
            currPos[1] = -h + glyph.getVertBearingY();
        }
        if (glyphID != kATSDeletedGlyphcode)
        {
            layoutResult.indices.push_back(glyphID);
            layoutResult.positions.push_back(currPos);
        }
    }

    // Cleanup
    if (deltaYs != 0)
        ATSUDirectReleaseLayoutDataArrayPtr(0, kATSUDirectDataBaselineDeltaFixedArray, (void**)&deltaYs);
    ATSUDirectReleaseLayoutDataArrayPtr(0, kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords);

    // Adjust the origin depending on the major and the minor alignment
    adjustLineOrigin(param, currPos, layoutResult);

    // Determine text bounds / line bounds
    if (param.horizontal == true)
        layoutResult.textBounds[0] = osgAbs(currPos.x());
    else
        layoutResult.textBounds[1] = osgAbs(currPos.y());
    assert(layoutResult.lineBounds.empty() == false);
    layoutResult.lineBounds.front() = layoutResult.textBounds;
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
static OSStatus quadraticNewPathCallback(void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // We start a new contour
    userData->outline.push_back(TextVectorGlyph::Contour());

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// callback function that adds a line to the contour
// Author: pdaehne
//----------------------------------------------------------------------
static OSStatus quadraticLineCallback(const Float32Point *pt1, const Float32Point *pt2, void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // When this is the first segment, we have to put the first point into the contour
    if (userData->outline.back().empty() == true)
    {
        Vec2f p(pt1->x, -pt1->y);
        p *= userData->scale;
        p -= userData->offset;
        userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));
    }

    // We have a point on the line
    Vec2f p(pt2->x, -pt2->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// callback function that adds a quadratic Bezier spline to the contour
// Author: pdaehne
//----------------------------------------------------------------------
static OSStatus quadraticCurveCallback(const Float32Point *pt1, const Float32Point *controlPt, const Float32Point *pt2, void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // When this is the first segment, we have to put the first point into the contour
    if (userData->outline.back().empty() == true)
    {
        Vec2f p(pt1->x, -pt1->y);
        p *= userData->scale;
        p -= userData->offset;
        userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));
    }

    // We have a control point and a point on the line
    Vec2f p(controlPt->x, -controlPt->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_QUAD));
    p.setValues(pt2->x, -pt2->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// callback function that closes a contour
// Author: pdaehne
//----------------------------------------------------------------------
OSStatus quadraticClosePathCallback(void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // Check if the contour is valid, i.e. if it has more than three points.
    // When not, we simply delete the contour.
    if (userData->outline.back().size() < 3)
        userData->outline.erase(userData->outline.end() - 1);

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// callback function that starts a new contour
// Author: pdaehne
//----------------------------------------------------------------------
static OSStatus cubicMoveToCallback(const Float32Point *pt, void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // We start a new contour
    userData->outline.push_back(TextVectorGlyph::Contour());

    // We have a point on the line
    Vec2f p(pt->x, -pt->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// callback function that adds a line to the contour
// Author: pdaehne
//----------------------------------------------------------------------
static OSStatus cubicLineToCallback(const Float32Point *pt, void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // We have a point on the line
    Vec2f p(pt->x, -pt->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// callback function that adds a cubic Bezier spline to the contour
// Author: pdaehne
//----------------------------------------------------------------------
static OSStatus cubicCurveToCallback(const Float32Point *pt1, const Float32Point *pt2, const Float32Point *pt3, void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // We have two control points and a point on the line
    Vec2f p(pt1->x, -pt1->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_CUBIC));
    p.setValues(pt2->x, -pt2->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_CUBIC));
    p.setValues(pt3->x, -pt3->y);
    p *= userData->scale;
    p -= userData->offset;
    userData->outline.back().push_back(TextVectorGlyph::Point(p, TextVectorGlyph::Point::PT_ON));

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// callback function that closes a contour
// Author: pdaehne
//----------------------------------------------------------------------
static OSStatus cubicClosePathCallback(void *callBackDataPtr)
{
    UserData *userData = reinterpret_cast<UserData*>(callBackDataPtr);

    // Check if the contour is valid, i.e. if it has more than two points.
    // When not, we simply delete the contour.
    if (userData->outline.back().size() < 3)
        userData->outline.erase(userData->outline.end() - 1);

    // Continue
    return noErr;
}


//----------------------------------------------------------------------
// Creates a new Glyph object
// Author: pdaehne
//----------------------------------------------------------------------
auto_ptr<TextVectorGlyph> TextMacVectorFace::createGlyph(TextGlyph::Index glyphIndex)
{
    // We cannot create glyphs for invalid glyph indices
    if (glyphIndex == TextGlyph::INVALID_INDEX)
        return auto_ptr<TextVectorGlyph>();

    // Create and return the new glyph object
    return auto_ptr<TextVectorGlyph>(new TextMacVectorGlyph(glyphIndex, _scale, _horiFontStyle, _vertFontStyle));
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacVectorGlyph::TextMacVectorGlyph(Index glyphIndex, Real32 scale, ATSUStyle horiFontStyle, ATSUStyle vertFontStyle)
: TextVectorGlyph()
{
    _glyphIndex = glyphIndex;

    // Determine horizontal glyph metrics
    GlyphID glyphID = _glyphIndex;
    ATSGlyphScreenMetrics glyphScreenMetrics;
    OSStatus result = ATSUGlyphGetScreenMetrics(horiFontStyle, 1, &glyphID, 0, false, false, &glyphScreenMetrics);
    if (result == noErr)
    {
        _width = glyphScreenMetrics.width * scale;
        _height = glyphScreenMetrics.height * scale;
        _horiAdvance = glyphScreenMetrics.deviceAdvance.x * scale;
        _horiBearingX = glyphScreenMetrics.topLeft.x * scale;
        _horiBearingY = glyphScreenMetrics.topLeft.y * scale;
    }

    // Determine vertical glyph metrics
    result = ATSUGlyphGetScreenMetrics(vertFontStyle, 1, &glyphID, 0, false, false, &glyphScreenMetrics);
    if (result == noErr)
    {
        _width = glyphScreenMetrics.width * scale;
        _height = glyphScreenMetrics.height * scale;
        _vertAdvance = glyphScreenMetrics.deviceAdvance.y * scale;
        _vertBearingX = glyphScreenMetrics.topLeft.x * scale;
        _vertBearingY = glyphScreenMetrics.topLeft.y * scale;
    }

    // Get the outlines
    ATSCurveType curveType;
    result = ATSUGetNativeCurveType(horiFontStyle, &curveType);
    if (result != noErr)
        return;
    if (curveType == kATSQuadCurveType)
    {
        // This is quite ugly, we should do this only once for all glyphs.
        // But on MacOS X, this should be a NOP, anyway.
        ATSQuadraticNewPathUPP newPathProc = NewATSQuadraticNewPathUPP(&quadraticNewPathCallback);
        ATSQuadraticLineUPP lineProc = NewATSQuadraticLineUPP(&quadraticLineCallback);
        ATSQuadraticCurveUPP curveProc = NewATSQuadraticCurveUPP(&quadraticCurveCallback);
        ATSQuadraticClosePathUPP closePathProc = NewATSQuadraticClosePathUPP(&quadraticClosePathCallback);
        UserData userData(scale, Vec2f(_horiBearingX, _horiBearingY), _outline);
        OSStatus callbackResult;
        result = ATSUGlyphGetQuadraticPaths(horiFontStyle, glyphID, newPathProc, lineProc, curveProc, closePathProc, &userData, &callbackResult);
        DisposeATSQuadraticClosePathUPP(closePathProc);
        DisposeATSQuadraticCurveUPP(curveProc);
        DisposeATSQuadraticLineUPP(lineProc);
        DisposeATSQuadraticNewPathUPP(newPathProc);
    }
    else if (curveType == kATSCubicCurveType)
    {
        // This is quite ugly, we should do this only once for all glyphs.
        // But on MacOS X, this should be a NOP, anyway.
        ATSCubicMoveToUPP moveToProc = NewATSCubicMoveToUPP(&cubicMoveToCallback);
        ATSCubicLineToUPP lineToProc = NewATSCubicLineToUPP(&cubicLineToCallback);
        ATSCubicCurveToUPP curveToProc = NewATSCubicCurveToUPP(&cubicCurveToCallback);
        ATSCubicClosePathUPP closePathProc = NewATSCubicClosePathUPP(&cubicClosePathCallback);
        UserData userData(scale, Vec2f(_horiBearingX, _horiBearingY), _outline);
        OSStatus callbackResult;
        ATSUGlyphGetCubicPaths(horiFontStyle, glyphID, moveToProc, lineToProc, curveToProc, closePathProc, &userData, &callbackResult);
        DisposeATSCubicClosePathUPP(closePathProc);
        DisposeATSCubicCurveToUPP(curveToProc);
        DisposeATSCubicLineToUPP(lineToProc);
        DisposeATSCubicMoveToUPP(moveToProc);
    }
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacVectorGlyph::~TextMacVectorGlyph() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacPixmapFace::TextMacPixmapFace(ATSUStyle horiFontStyle)
: TextPixmapFace(), _horiFontStyle(horiFontStyle), _vertFontStyle(0), _horiTextLayout(0), _vertTextLayout(0)
{
    // Create all ATSU objects
    createATSUObjects(_horiFontStyle, _vertFontStyle, _horiTextLayout, _vertTextLayout);

    // Try to get information about the face
    getFaceInfo(_horiFontStyle, _vertFontStyle, _family, _style,
        _horiAscent, _horiDescent, _vertAscent, _vertDescent);

    // Determine the size
    Fixed size;
    OSStatus result = ATSUGetAttribute(_horiFontStyle, kATSUSizeTag, sizeof(size), &size, 0);
    _size = ((result == noErr) || (result == kATSUNotSetErr)) ? FixedToInt(size) : 0;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacPixmapFace::~TextMacPixmapFace()
{
    // Dispose the layout objects
    ATSUDisposeTextLayout(_horiTextLayout);
    ATSUDisposeTextLayout(_vertTextLayout);

    // Dispose style objects
    ATSUDisposeStyle(_horiFontStyle);
    ATSUDisposeStyle(_vertFontStyle);
}


//----------------------------------------------------------------------
// Lays out one line of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextMacPixmapFace::layout(const wstring &text, const TextLayoutParam &param,
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
    vector<UniChar> utf16Text;
    convertUnicodeToUTF16(text, utf16Text);
    if (utf16Text.empty() == true)
        return;

    // Check whether we have to use the horizontal or vertical ATSUI objects
    ATSUStyle fontStyle;
    ATSUTextLayout textLayout;
    if (param.horizontal == true)
    {
        fontStyle = _horiFontStyle;
        textLayout = _horiTextLayout;
    }
    else
    {
        fontStyle = _vertFontStyle;
        textLayout = _vertTextLayout;
    }

    // Set the length
    Real32 length = param.getLength(0);
    Fract justFactor = length <= 0.f ? kATSUNoJustification : kATSUFullJustification;
    ATSUTextMeasurement width = FloatToFixed(length <= 0.f ? 0.f : length);
    ATSUAttributeTag layoutAttributeTags[] = { kATSULineJustificationFactorTag, kATSULineWidthTag };
    ByteCount layoutAttributeSizes[] = { sizeof(justFactor), sizeof(width) };
    ATSUAttributeValuePtr layoutAttributeValues[] = { &justFactor, &width };
    ATSUSetLayoutControls(textLayout, 2, layoutAttributeTags, layoutAttributeSizes, layoutAttributeValues);

    // Set the text
    OSStatus result = ATSUSetTextPointerLocation(textLayout, &(utf16Text[0]), kATSUFromTextBeginning, kATSUToTextEnd, utf16Text.size());
    if (result != noErr)
        return;

    // Set the style object
    result = ATSUSetRunStyle(textLayout, fontStyle, kATSUFromTextBeginning, kATSUToTextEnd);
    if (result != noErr)
        return;

    // Get the layout records
    ATSLayoutRecord *layoutRecords;
    ItemCount numRecords;
    result = ATSUDirectGetLayoutDataArrayPtrFromTextLayout(textLayout, kATSUFromTextBeginning,
        kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords, &numRecords);
    if (result != noErr)
        return;
    Fixed *deltaYs;
    ItemCount numDeltaYs;
    result = ATSUDirectGetLayoutDataArrayPtrFromTextLayout(textLayout, kATSUFromTextBeginning,
        kATSUDirectDataBaselineDeltaFixedArray, (void**)&deltaYs, &numDeltaYs);
    if (result != noErr)
        deltaYs = 0;

    // Calculate the positions of the glyphs
    layoutResult.indices.reserve(numRecords);
    layoutResult.positions.reserve(numRecords);
    ItemCount j;
    Vec2f currPos;
    for (j = 0; j < numRecords; ++j)
    {
        ATSGlyphRef glyphID = layoutRecords[j].glyphID;
        currPos[0] = FixedToFloat(layoutRecords[j].realPos);
        currPos[1] = (deltaYs != 0) && (j < numDeltaYs) ? -FixedToFloat(deltaYs[j]) : 0.f;
        const TextPixmapGlyph &glyph = getPixmapGlyph(layoutRecords[j], param.horizontal);
        if (param.horizontal == true)
        {
            currPos[0] += glyph.getHoriBearingX();
            currPos[1] += glyph.getHoriBearingY();
        }
        else
        {
            float h = currPos.x();
            currPos[0] = currPos.y() + glyph.getVertBearingX();
            currPos[1] = -h + glyph.getVertBearingY();
        }
        if (glyphID != kATSDeletedGlyphcode)
        {
            layoutResult.indices.push_back(glyphID);
            layoutResult.positions.push_back(currPos);
        }
    }

    // Cleanup
    if (deltaYs != 0)
        ATSUDirectReleaseLayoutDataArrayPtr(0, kATSUDirectDataBaselineDeltaFixedArray, (void**)&deltaYs);
    ATSUDirectReleaseLayoutDataArrayPtr(0, kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords);

    // Adjust the origin depending on the major and the minor alignment
    adjustLineOrigin(param, currPos, layoutResult);

    // Determine text bounds / line bounds
    if (param.horizontal == true)
        layoutResult.textBounds[0] = osgAbs(currPos.x());
    else
        layoutResult.textBounds[1] = osgAbs(currPos.y());
    assert(layoutResult.lineBounds.empty() == false);
    layoutResult.lineBounds.front() = layoutResult.textBounds;
}


//----------------------------------------------------------------------
// Creates a new Glyph object
// Author: pdaehne
//----------------------------------------------------------------------
auto_ptr<TextPixmapGlyph> TextMacPixmapFace::createGlyph(TextGlyph::Index glyphIndex)
{
    return auto_ptr<TextPixmapGlyph>();
}


//----------------------------------------------------------------------
// Renders a glyph into a memory buffer
// Author: pdaehne
//----------------------------------------------------------------------
static void drawGlyph(ATSUTextLayout textLayout, const ATSLayoutRecord &layoutRecord,
                      ATSUTextMeasurement xPos, ATSUTextMeasurement yPos,
                      UInt32 width, UInt32 height, UInt8 *dst, UInt32 pitch)
{
    // No need to draw invisible glyphs
    if ((width == 0) || (height == 0))
        return;

    // Create offscreen GWorld
    GWorldPtr offscreenGWorld;
    Rect boundsRect;
    SetRect(&boundsRect, 0, 0, width, height);
    QDErr qdResult = NewGWorld(&offscreenGWorld, 32, &boundsRect, 0, 0, 0);
    if (qdResult != noErr)
        return;

    // Get the pixel buffer of the offscreen GWorld
    if (LockPixels(GetGWorldPixMap(offscreenGWorld)) == FALSE)
    {
        DisposeGWorld(offscreenGWorld);
        return;
    }
    Ptr src = GetPixBaseAddr(GetGWorldPixMap(offscreenGWorld));
    if (src == 0)
    {
        UnlockPixels(GetGWorldPixMap(offscreenGWorld));
        DisposeGWorld(offscreenGWorld);
        return;
    }

    // Initialize and activate the offscreen GWorld
    CGrafPtr port;
    GDHandle gdh;
    GetGWorld(&port, &gdh);
    SetGWorld(offscreenGWorld, 0);
    RGBColor gBlackColour = { 0x0000, 0x0000, 0x0000 };
    RGBBackColor(&gBlackColour);
    EraseRect(&boundsRect);
    RGBColor gWhiteColour = { 0xFFFF, 0xFFFF, 0xFFFF };
    RGBForeColor(&gWhiteColour);

    // Draw the text
    UniCharArrayOffset charOffset = layoutRecord.originalOffset >> 1;
    UniCharCount charCount = (layoutRecord.flags & kATSGlyphInfoByteSizeMask) >> 1;
    OSStatus result = ATSUDrawText(textLayout, charOffset, charCount, xPos, yPos);
    if (result == noErr)
    {
        long bpl = GetPixRowBytes(GetGWorldPixMap(offscreenGWorld));
        src += bpl * (height - 1);
        Ptr src2;
        UInt32 x, y;
        for (y = 0; y < height; ++y)
        {
            src2 = src + 1;
            for (x = 0; x < width; ++x)
            {
                *dst++ = *src2;
                src2+= 4;
            }
            src -= bpl;
            dst += pitch;
        }
    }

    // Deactivate and destroy the offscreen GWorld
    SetGWorld(port, gdh);
    UnlockPixels(GetGWorldPixMap(offscreenGWorld));
    DisposeGWorld(offscreenGWorld);
}


//----------------------------------------------------------------------
// Returns information about a glyph.
// Author: pdaehne
//----------------------------------------------------------------------
const TextPixmapGlyph &TextMacPixmapFace::getPixmapGlyph(const ATSLayoutRecord &layoutRecord, bool horizontal)
{
    ATSGlyphRef glyphID = layoutRecord.glyphID;
    if (glyphID == kATSDeletedGlyphcode)
        return _emptyGlyph;

    // Try to find the glyph in the map of glyphs
    GlyphMap::const_iterator it = _glyphMap.find(glyphID);
    if (it != _glyphMap.end())
    {
        assert(it->second != 0);
        return *(it->second);
    }

    // We did not find the glyph, so we have to create it
    ATSUTextMeasurement xPos = 0, yPos = 0;

    // Determine horizontal glyph metrics
    ATSGlyphScreenMetrics glyphScreenMetrics;
    OSStatus result = ATSUGlyphGetScreenMetrics(_horiFontStyle, 1, &glyphID, 0, true, true, &glyphScreenMetrics);
    if (result != noErr)
        return _emptyGlyph;
    Real32 horiAdvance = glyphScreenMetrics.deviceAdvance.x;
    UInt32 width = glyphScreenMetrics.width;
    UInt32 height = glyphScreenMetrics.height;
    Int32 horiBearingX = static_cast<Int32>(glyphScreenMetrics.topLeft.x);
    Int32 horiBearingY = static_cast<Int32>(glyphScreenMetrics.topLeft.y);
    if (horizontal == true)
    {
        xPos = FloatToFixed(-glyphScreenMetrics.topLeft.x) - (layoutRecord.realPos & 0xffff0000);
        yPos = FloatToFixed(glyphScreenMetrics.topLeft.y);
    }

    // Determine vertical glyph metrics
    result = ATSUGlyphGetScreenMetrics(_vertFontStyle, 1, &glyphID, 0, true, true, &glyphScreenMetrics);
    if (result != noErr)
        return _emptyGlyph;
    Real32 vertAdvance = glyphScreenMetrics.deviceAdvance.y;
    Int32 vertBearingX = static_cast<Int32>(glyphScreenMetrics.topLeft.x);
    Int32 vertBearingY = static_cast<Int32>(glyphScreenMetrics.topLeft.y);
    if (horizontal == false)
    {
        xPos = FloatToFixed(-glyphScreenMetrics.topLeft.x);
        yPos = FloatToFixed(glyphScreenMetrics.topLeft.y) - ((layoutRecord.realPos + fixed1) & 0xffff0000);
    }

    UInt8 *pixmap = 0;
    UInt32 size = width * height;
    if (size != 0)
    {
        // Create pixmap
        ATSUTextLayout textLayout = horizontal == true ? _horiTextLayout : _vertTextLayout;
        pixmap = new UInt8[size];
        drawGlyph(textLayout, layoutRecord, xPos, yPos, width, height, pixmap, 0);
    }

    auto_ptr<TextPixmapGlyph> glyph(new TextMacPixmapGlyph(glyphID, width, height, horiAdvance, horiBearingX, horiBearingY, vertAdvance, vertBearingX, vertBearingY, pixmap));

    // Put the glyph into the glyph cache
    _glyphMap.insert(GlyphMap::value_type(glyphID, glyph.get()));

    // Return the glyph
    return *(glyph.release());
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacPixmapGlyph::TextMacPixmapGlyph(Index glyphIndex, UInt32 width, UInt32 height,
    Real32 horiAdvance, Int32 horiBearingX, Int32 horiBearingY,
    Real32 vertAdvance, Int32 vertBearingX, Int32 vertBearingY,
    UInt8 *pixmap)
: TextPixmapGlyph()
{
    _glyphIndex = glyphIndex;
    _width = _pitch = width;
    _height = height;
    _pixmap = pixmap;

    // Determine horizontal glyph metrics
    _horiAdvance = horiAdvance;
    _horiBearingX = horiBearingX;
    _horiBearingY = horiBearingY;

    // Determine vertical glyph metrics
    _vertAdvance = vertAdvance;
    _vertBearingX = vertBearingX;
    _vertBearingY = vertBearingY;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacPixmapGlyph::~TextMacPixmapGlyph() {}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacTXFFace::TextMacTXFFace(ATSUStyle horiFontStyle, const TextTXFParam &param)
: TextTXFFace()
{
    // Create all ATSU objects
    ATSUStyle vertFontStyle;
    ATSUTextLayout horiTextLayout, vertTextLayout;
    createATSUObjects(horiFontStyle, vertFontStyle, horiTextLayout, vertTextLayout);

    // Try to get information about the face
    getFaceInfo(horiFontStyle, vertFontStyle, _family, _style,
                _horiAscent, _horiDescent, _vertAscent, _vertDescent);

    // Determine the scale factor
    _scale = 1.f / (_horiAscent - _horiDescent);

    // Determine ascent
    _horiAscent *= _scale;
    _vertAscent = -0.5f;

    // Determine descent
    _horiDescent *= _scale;
    _vertDescent = 0.5f;

    // Set the parameters
    _param = param;

    // Switch off all font features
    ATSUFontFeatureType featureType = kAllTypographicFeaturesType;
    ATSUFontFeatureSelector featureSelector = kAllTypeFeaturesOffSelector;
    ATSUSetFontFeatures(horiFontStyle, 1, &featureType, &featureSelector);
    ATSUSetFontFeatures(vertFontStyle, 1, &featureType, &featureSelector);

    // Create all glyphs and the texture
    createGlyphs(horiFontStyle, vertFontStyle, horiTextLayout, vertTextLayout, param);

    // Dispose the layout objects
    ATSUDisposeTextLayout(horiTextLayout);
    ATSUDisposeTextLayout(vertTextLayout);

    // Dispose style objects
    ATSUDisposeStyle(horiFontStyle);
    ATSUDisposeStyle(vertFontStyle);
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacTXFFace::~TextMacTXFFace() {}


//----------------------------------------------------------------------
// Creates all glyphs and the texture
// Author: pdaehne
//----------------------------------------------------------------------
void TextMacTXFFace::createGlyphs(ATSUStyle horiFontStyle, ATSUStyle vertFontStyle,
                                  ATSUTextLayout horiTextLayout, ATSUTextLayout vertTextLayout,
                                  const TextTXFParam &param)
{
    // Convert the unicode character string to utf16
    vector<UniChar> utf16Characters;
    convertUnicodeToUTF16(param.getCharacters(), utf16Characters);

    // Set the character string
    OSStatus result = ATSUSetTextPointerLocation(horiTextLayout, &(utf16Characters[0]), kATSUFromTextBeginning, kATSUToTextEnd, utf16Characters.size());
    if (result != noErr)
        return;

    // Set the style object
    result = ATSUSetRunStyle(horiTextLayout, horiFontStyle, kATSUFromTextBeginning, kATSUToTextEnd);
    if (result != noErr)
        return;

    // Get the layout records
    ATSLayoutRecord *layoutRecords;
    ItemCount numRecords;
    result = ATSUDirectGetLayoutDataArrayPtrFromTextLayout(horiTextLayout, kATSUFromTextBeginning,
                                                           kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords, &numRecords);
    if (result != noErr)
        return;

    // Determine horizontal glyph metrics
    vector<ATSGlyphScreenMetrics> horiMetrics;
    horiMetrics.resize(numRecords);
    result = ATSUGlyphGetScreenMetrics(horiFontStyle, numRecords, &(layoutRecords[0].glyphID), sizeof(ATSLayoutRecord), true, true, &(horiMetrics.front()));
    if (result != noErr)
    {
        ATSUDirectReleaseLayoutDataArrayPtr(0, kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords);
        return;
    }

    // Determine vertical glyph metrics
    vector<ATSGlyphScreenMetrics> vertMetrics;
    vertMetrics.resize(numRecords);
    result = ATSUGlyphGetScreenMetrics(vertFontStyle, numRecords, &(layoutRecords[0].glyphID), sizeof(ATSLayoutRecord), true, true, &(vertMetrics.front()));
    if (result != noErr)
    {
        ATSUDirectReleaseLayoutDataArrayPtr(0, kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords);
        return;
    }

    // Create all glyphs
    assert(numRecords == param.getCharacters().length() + 1);
    ItemCount j;
    for (j = 0; j < numRecords - 1; ++j)
    {
        ATSGlyphRef glyphID = layoutRecords[j].glyphID;
        wchar_t c = param.getCharacters()[j];
        _glyphMap.insert(GlyphMap::value_type(c, new TextMacTXFGlyph(c, _scale, horiMetrics[j], vertMetrics[j])));
    }

    // Calculate the positions of the glyphs on the texture
    prepareTexture(param);
    assert(_texture != NULL);
    assert(_texture->getSize() == static_cast<UInt32>(_texture->getWidth() * _texture->getHeight()));

    // Create the texture
    for (j = 0; j < numRecords - 1; ++j)
    {
        wchar_t c = param.getCharacters()[j];
        TextTXFGlyph *glyph = _glyphMap[c];

        // Create pixmap
        ATSUTextMeasurement xPos = FloatToFixed(-horiMetrics[j].topLeft.x) - (layoutRecords[j].realPos & 0xffff0000);
        ATSUTextMeasurement yPos = FloatToFixed(horiMetrics[j].topLeft.y);
        UInt32 width = glyph->getPixmapWidth();
        UInt32 height = glyph->getPixmapHeight();
        UInt8 *dst = _texture->editData() + glyph->getX() + glyph->getY() * _texture->getWidth();
        UInt32 pitch = _texture->getWidth() - width;
        drawGlyph(horiTextLayout, layoutRecords[j], xPos, yPos, width, height, dst, pitch);
    }

    // Cleanup
    ATSUDirectReleaseLayoutDataArrayPtr(0, kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void**)&layoutRecords);
}


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacTXFGlyph::TextMacTXFGlyph(Index glyphIndex, Real32 scale, const ATSGlyphScreenMetrics &horiMetrics, const ATSGlyphScreenMetrics &vertMetrics)
: TextTXFGlyph()
{
    _glyphIndex = glyphIndex;
    _scale = scale;
    _width = horiMetrics.width;
    _height = horiMetrics.height;

    // Determine horizontal glyph metrics
    _horiAdvance = horiMetrics.deviceAdvance.x * _scale;
    _horiBearingX = static_cast<int>(horiMetrics.topLeft.x);
    _horiBearingY = static_cast<int>(horiMetrics.topLeft.y);

    // Determine vertical glyph metrics
    _vertAdvance = vertMetrics.deviceAdvance.y * _scale;
    _vertBearingX = static_cast<int>(vertMetrics.topLeft.x);
    _vertBearingY = static_cast<int>(vertMetrics.topLeft.y);
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextMacTXFGlyph::~TextMacTXFGlyph() {}


OSG_END_NAMESPACE


#endif // __APPLE__
