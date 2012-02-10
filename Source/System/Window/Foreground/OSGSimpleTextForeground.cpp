/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGSimpleTextForeground.h"

#include "OSGImage.h"

#include "OSGViewport.h"

#include "OSGDefaultFont.h"

#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextTXFGlyph.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"

#include <boost/xpressive/xpressive.hpp>
#include <boost/xpressive/regex_actions.hpp>

using namespace boost::xpressive;

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSimpleTextForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleTextForeground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SimpleTextForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SimpleTextForeground::initText(const std::string &szFamily, Real32 fSize)
{
    // Cleanup
    _pFace     = NULL;
    _pTexChunk = NULL;

    // Create the font
    if(szFamily.empty() == false)
    {
        TextTXFParam param;

        param.size = static_cast<UInt32>(fSize);

        _pFace = TextTXFFace::create(szFamily, TextFace::STYLE_PLAIN, param);

        if(_pFace != NULL)
        {
            _pTexChunk = TextureObjChunk::createLocal();

            ImageUnrecPtr pTexture = _pFace->getTexture();

            _pTexChunk->setImage    (pTexture        );
            _pTexChunk->setWrapS    (GL_CLAMP_TO_EDGE);
            _pTexChunk->setWrapT    (GL_CLAMP_TO_EDGE);
            _pTexChunk->setMinFilter(GL_NEAREST      );
            _pTexChunk->setMagFilter(GL_NEAREST      );
        }
    }

    // We failed to create the font - fallback to the default font
    if(_pFace == NULL)
    {
        _pFace     = DefaultFont::the()->getFace   ();
        _pTexChunk = DefaultFont::the()->getTexture();
    }
}

void SimpleTextForeground::draw(DrawEnv *pEnv)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(!getActive())
    {
        return;
    }

    if(_pFace == NULL)
    {
        initText(getFamily(), getSize());
    }

    //Setup the orthographic projection
    UInt32 fullWidth;
    UInt32 fullHeight;

    beginOrthoRender(pEnv, fullWidth, fullHeight);

    glPushAttrib(GL_LIGHTING_BIT     | GL_POLYGON_BIT     | 
                 GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_DEPTH_TEST    );
    glDisable(GL_COLOR_MATERIAL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);

    //Layout the text
    TextLayoutParam layoutParam;

    layoutParam.spacing = 1.1f;
    layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
    layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;

    TextLayoutResult layoutResult;

    _pFace->layout(_vPlainTextLines, layoutParam, layoutResult);

    Real32 scale      = 1.f / _pFace->getScale();
    Real32 size       =       _pFace->getParam().size;
    Real32 textWidth  = 
        layoutResult.textBounds.x() * scale + size + getTextMargin().x() * 2.0f;
    Real32 textHeight = 
        layoutResult.textBounds.y() * scale + size + getTextMargin().y() * 2.0f;

    // Let's do some simple form of layout management
    Real32  pw = Real32(pEnv->getPixelWidth ());
    Real32  ph = Real32(pEnv->getPixelHeight());

    if(pw < 1.f || ph < 1.f)
    {
        return;
    }

    Real32 orthoX = 0.f, orthoY = ph;

    switch(getHorizontalAlign())
    {
        case Right:
            orthoX = pw - textWidth;
            break;
        case Middle:
            orthoX = (pw - textWidth) * 0.5;
            break;
        case Left:
        default:
            break;
    }

    switch(getVerticalAlign())
    {
        case Bottom:
            orthoY = textHeight;
            break;
        case Center:
            orthoY = (ph - textHeight) * 0.5 + textHeight;
            break;
        case Top:
        default:
            break;
    }

    glTranslatef(orthoX, orthoY, 0.0);

    // draw background
    glColor4fv(static_cast<const GLfloat *>(getBgColor().getValuesRGBA()));

    glBegin(GL_QUADS);
        glVertex2f(0.f,       -textHeight);
        glVertex2f(textWidth, -textHeight);
        glVertex2f(textWidth,  0.f       );
        glVertex2f(0.f,        0.f       );
    glEnd();

    // draw border
    if(getBorderColor().alpha() >= 0.0f)
    {
        glColor4fv(
            static_cast<const GLfloat *>(getBorderColor().getValuesRGBA()));

        glBegin(GL_LINE_LOOP);
            glVertex2f(                  getBorderOffset().x(), 
                       -textHeight + 1 + getBorderOffset().y());

            glVertex2f( textWidth  - 1 - getBorderOffset().x(), 
                       -textHeight + 1 + getBorderOffset().y());

            glVertex2f( textWidth  - 1 - getBorderOffset().x(), 
                                   - 1 - getBorderOffset().y());

            glVertex2f(                  getBorderOffset().x(), 
                                   - 1 - getBorderOffset().y());
        glEnd();
    }

    glTranslatef( 0.5f * size + getTextMargin().x(), 
                 -0.5f * size - getTextMargin().y(), 
                  0.0f);

    _pTexChunk   ->activate(pEnv);
    _pTexEnvChunk->activate(pEnv);

    // draw text shadow
    glColor4fv(static_cast<const GLfloat *>(getShadowColor().getValuesRGBA()));

    glPushMatrix();
    glTranslatef(getShadowOffset().x(), getShadowOffset().y(), 0);
    glScalef(scale, scale, 1);

    drawCharacters(_pFace, layoutResult, false);

    // draw text
    glPopMatrix();
    glScalef(scale, scale, 1);

    drawCharacters(_pFace, layoutResult, true);

    _pTexChunk   ->deactivate(pEnv);
    _pTexEnvChunk->deactivate(pEnv);

    glPopAttrib();

    //reset the matrices
    endOrthoRender(pEnv);
#endif
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
/*! Sets up an ortho projection for rendering. It handles tiling
    when a TileCameraDecorator is in use. When done you need to call
    endOrthoRender to clean up changes to the OpenGL matrix stacks.

    \param pEnv DrawEnv being used for rendering
    \param normX Wether x coordinates are going to be normalized.
    \param normY Wether y coordinates are going to be normalized.
    \param[out] fullWidth width of the viewport
    \param[out] fullHeight height of the viewport

    \note When the TileCameraDecorator is in use, the width and height of the
          viewport (fullWidth, fullHeight) are defined by the
          TileCameraDecorator. 
 */
void SimpleTextForeground::beginOrthoRender(DrawEnv *pEnv,
                                            UInt32  &fullWidth,
                                            UInt32  &fullHeight)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    UInt32 width   = pEnv->getPixelWidth ();
    UInt32 height  = pEnv->getPixelHeight();

    fullWidth  = pEnv->getTileFullSize()[0];
    fullHeight = pEnv->getTileFullSize()[1];

    if(fullWidth == 0 || getTile())
    {
        fullWidth  = width;
        fullHeight = height;
    }
    else if(!getTile())
    {
        /*! \warning: Hack! */
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(0.0f, fullHeight - height,0.0f);
        //End Hack

        glMatrixMode(GL_PROJECTION);
        Matrix sm = pEnv->calcTileDecorationMatrix();

        glLoadMatrixf(sm.getValues());

    }

    glOrtho(- 0.375f,
            static_cast<Real32>(fullWidth) - 0.375f,
            - 0.375f,
            static_cast<Real32>(fullHeight) - 0.375f,
            -1.0f,
            1.0f);

    glMatrixMode(GL_MODELVIEW);
#endif
}

/*! Clean up changes to the OpenGL matrix stacks done by beginOrthoRender
 */
void SimpleTextForeground::endOrthoRender(DrawEnv *pEnv)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
}

void SimpleTextForeground::resolveLinks(void)
{
    Inherited::resolveLinks();
    
    _pTexChunk    = NULL;
    _pTexEnvChunk = NULL;
    _pFace        = NULL;
}

template <typename ElemT>
struct HexTo 
{
    ElemT value;
    operator ElemT() const { return value; }

    friend std::istream& operator>>(std::istream& in, HexTo& out) 
    {
        in >> std::hex >> out.value;
        return in;
    }
};

bool SimpleTextForeground::isColoredRange(UInt32 uiPosition) const
{
    for(UInt32 i = 0; i < _vColorRanges.size(); ++i)
    {
        if(_vColorRanges[i].isBounded(uiPosition))
        {
            return true;
        }
    }

    return false;
}

Color4f SimpleTextForeground::getColorRange(UInt32 uiPosition) const
{
    for(UInt32 i = 0; i < _vColorRanges.size(); ++i)
    {
        if(_vColorRanges[i].isBounded(uiPosition))
        {
            return _vColorRanges[i].getColor();
        }
    }

    return Color4f();
}

void SimpleTextForeground::updateFormatting(void)
{
    //Clear the formatted lines
    _vPlainTextLines.clear();
    _vColorRanges   .clear();

    UInt32 uiIndexOffset = 0;

    for(UInt32 i = 0; i < getMFLines()->size() ; ++i)
    {
        std::string szResult = getLines(i);

        //Remove all newlines that do not have another newline directly
        //afterward 

        mark_tag redTag  (1),
                 greenTag(2),
                 blueTag (3),
                 alphaTag(4),
                 textTag (5);

        //Matches a string similar to \color=AA00FF11
        //sregex ColorRegex =
            //"\\color"
            //>> *space
            //>> '='
            //>> *space
            //>> (redTag = repeat<2>(alnum))
            //>> (greenTag = repeat<2>(alnum))
            //>> (blueTag = repeat<2>(alnum))
            //>> !(alphaTag = repeat<2>(alnum));

        //Matches a string similar to \{\color=AA00FF11 Some text}
        sregex srTaggedColorRegex =
            as_xpr('\\') >> '{'
                         >> *space
                         >> "\\color"
                         >> *space
                         >> '='
                         >> *space
                         >> (redTag    = repeat<2>(alnum))
                         >> (greenTag  = repeat<2>(alnum))
                         >> (blueTag   = repeat<2>(alnum))
                         >> !(alphaTag = repeat<2>(alnum))
                         >> *space
                         >> (textTag = -*_) >> '}';

        //Get the color
        smatch what;

        while(regex_search(szResult, what, srTaggedColorRegex))
        {
            Real32 Red(0.0f), Green(0.0f), Blue(0.0f), Alpha(1.0f);

            try
            {
                 Red = static_cast<Real32>(
                     boost::lexical_cast< HexTo<UInt16> >(
                         std::string("0x") + what[redTag])) /
                             TypeTraits<UInt8>::getMax();
            }
            catch(boost::bad_lexical_cast &)
            {
                SWARNING << "Could not convert hex value "
                         << what[redTag]
                         << " into a 8-bit unsigned integer for the red "
                         << "color component." 
                         << std::endl;
            }

            try
            {
                 Green = static_cast<Real32>(
                     boost::lexical_cast< HexTo<UInt16> >(
                         std::string("0x") + what[greenTag])) /
                             TypeTraits<UInt8>::getMax();

            }
            catch(boost::bad_lexical_cast &)
            {
                SWARNING << "Could not convert hex value "
                         << what[greenTag]
                         << " into a 8-bit unsigned integer for the "
                         << "green color component."
                         << std::endl;
            }

            try
            {
                 Blue = static_cast<Real32>(
                     boost::lexical_cast< HexTo<UInt16> >(
                         std::string("0x") + what[blueTag])) /
                             TypeTraits<UInt8>::getMax();

            }
            catch(boost::bad_lexical_cast &)
            {
                SWARNING << "Could not convert hex value "
                         << what[blueTag]
                         << " into a 8-bit unsigned integer for the "
                         << "blue color component."
                         << std::endl;
            }
            
            try
            {
                 Alpha = static_cast<Real32>(
                     boost::lexical_cast<HexTo <UInt16> >(
                         std::string("0x") + what[alphaTag])) /
                             TypeTraits<UInt8>::getMax();

            }
            catch(boost::bad_lexical_cast &)
            {
                SWARNING << "Could not convert hex value "
                         << what[alphaTag]
                         << " into a 8-bit unsigned integer for the "
                         << "alpha color component."
                         << std::endl;
            }

            TextColoredRange oColorRange(
                uiIndexOffset + what.position(),
                uiIndexOffset + what.position() + what[textTag].length() - 1,
                Color4f(Red, Green, Blue, Alpha));

            _vColorRanges.push_back(oColorRange);

            //Remove the tag from the plain text
            szResult = regex_replace(szResult,
                                     srTaggedColorRegex,
                                     "" + textTag,
                                     regex_constants::match_default | 
                                     regex_constants::format_first_only);
        }

        //Push the plain text line to the lines vector
        _vPlainTextLines.push_back(szResult);

        uiIndexOffset += UInt32(szResult.size());
    }
}

// Render the text using the layout
void SimpleTextForeground::drawCharacters(
          TextTXFFace      * const pTextFace,
    const TextLayoutResult &       oLayoutResult,
          bool                     bWithColoring)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    Color4f cCurrentColor = getColor();
    Color4f cNewColor;

    glBegin(GL_QUADS);

    if(bWithColoring)
    {
        glColor4fv(cCurrentColor.getValues());
    }

    UInt32 i, numGlyphs = oLayoutResult.getNumGlyphs();

    for(i = 0; i < numGlyphs; ++i)
    {
        //Does the text color need to change
        if(bWithColoring)
        {
            if(isColoredRange(i))
            {
                cNewColor = getColorRange(i);
            }
            else
            {
                cNewColor = getColor();
            }

            if(cCurrentColor != cNewColor)
            {
                cCurrentColor = cNewColor;
                glColor4fv(cCurrentColor.getValues());
            }
        }

        const TextTXFGlyph &glyph = 
            pTextFace->getTXFGlyph(oLayoutResult.indices[i]);

        Real32 width  = glyph.getWidth ();
        Real32 height = glyph.getHeight();

        // No need to draw invisible glyphs
        if((width <= 0.f) || (height <= 0.f))
            continue;

        // Calculate coordinates
        Vec2f  const &pos       = oLayoutResult.positions[i];
        Real32        posLeft   = pos.x();
        Real32        posTop    = pos.y();
        Real32        posRight  = pos.x() + width;
        Real32        posBottom = pos.y() - height;

        Real32 texCoordLeft   = glyph.getTexCoord(TextTXFGlyph::COORD_LEFT  );
        Real32 texCoordTop    = glyph.getTexCoord(TextTXFGlyph::COORD_TOP   );
        Real32 texCoordRight  = glyph.getTexCoord(TextTXFGlyph::COORD_RIGHT );
        Real32 texCoordBottom = glyph.getTexCoord(TextTXFGlyph::COORD_BOTTOM);

        // lower left corner
        glTexCoord2f(texCoordLeft, texCoordBottom);
        glVertex2f  (posLeft,      posBottom     );

        // lower right corner
        glTexCoord2f(texCoordRight, texCoordBottom);
        glVertex2f  (posRight,      posBottom     );

        // upper right corner
        glTexCoord2f(texCoordRight, texCoordTop);
        glVertex2f  (posRight,      posTop     );

        // upper left corner
        glTexCoord2f(texCoordLeft, texCoordTop);
        glVertex2f  (posLeft,      posTop     );
    }

    glEnd();
#endif
}

/*----------------------- constructors & destructors ----------------------*/

SimpleTextForeground::SimpleTextForeground(void) :
     Inherited      (    ),
    _pFace          (NULL),
    _pTexChunk      (NULL),
    _pTexEnvChunk   (NULL),
    _vPlainTextLines(    ),
    _vColorRanges   (    )
   
{
    _pTexEnvChunk = TextureEnvChunk::createLocal();
    _pTexEnvChunk->setEnvMode(GL_MODULATE);
}

SimpleTextForeground::SimpleTextForeground(const SimpleTextForeground &source) :
     Inherited      (source                 ),
    _pFace          (source._pFace          ),
    _pTexChunk      (source._pTexChunk      ),
    _pTexEnvChunk   (source._pTexEnvChunk   ),
    _vPlainTextLines(source._vPlainTextLines),
    _vColorRanges   (source._vColorRanges   )
{
}

SimpleTextForeground::~SimpleTextForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SimpleTextForeground::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & LinesFieldMask)
    {
        updateFormatting();
    }

    if((whichField & SizeFieldMask) ||
       (whichField & FamilyFieldMask))
    {
        _pFace = NULL;
    }
}

void SimpleTextForeground::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SimpleTextForeground NI" << std::endl;
}

/*---------------------------- internal classes ---------------------------*/
//SimpleTextForeground::TextElement::TextElement(const std::string& Text,
                                               //bool        IsColored,
                                               //const Color4f&     Color) :
                    //_Text(Text),
                    //_IsColored(IsColored),
                    //_Color(Color)
//{
//}

OSG_END_NAMESPACE
