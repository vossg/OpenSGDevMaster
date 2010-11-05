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
//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGImage.h"

#include "OSGViewport.h"

#include "OSGSimpleStatisticsForeground.h"
#include "OSGStatisticsDefaultFont.h"

#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextTXFGlyph.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSimpleStatisticsForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleStatisticsForeground.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

SimpleStatisticsForeground::SimpleStatisticsForeground(void) :
    Inherited(), _face(0), _texchunk(NULL), _texenvchunk(NULL)
{
    _texenvchunk = TextureEnvChunk::createLocal();
    _texenvchunk->setEnvMode(GL_MODULATE);
}

/* */
SimpleStatisticsForeground::SimpleStatisticsForeground(
    const SimpleStatisticsForeground &source) :

    Inherited   (source),
    _face       (source._face),
    _texchunk   (source._texchunk),
    _texenvchunk(source._texenvchunk)
{
}

/* */
SimpleStatisticsForeground::~SimpleStatisticsForeground(void)
{
}

void SimpleStatisticsForeground::resolveLinks(void)
{
    Inherited::resolveLinks();
    
    _texchunk    = NULL;
    _texenvchunk = NULL;
    _face        = NULL;
}


/*----------------------------- class specific ----------------------------*/

void SimpleStatisticsForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/* */
void SimpleStatisticsForeground::changed(ConstFieldMaskArg whichField,
                                         UInt32            origin,
                                         BitVector         details    )
{
    Inherited::changed(whichField, origin, details);
}

/* */
void SimpleStatisticsForeground::dump(UInt32, const BitVector) const
{
    SLOG << "Dump SimpleStatisticsForeground NI" << std::endl;
}

/*! Convenience function to add an element and format.
*/
void SimpleStatisticsForeground::addElement(StatElemDescBase &desc,
                                            const char *format)
{
    editMFElementIDs()->push_back(desc.getID());
    editMFFormats   ()->push_back(format ? format : "");
}

/*! Convenience function to add an element and format.
*/
void SimpleStatisticsForeground::addElement(Int32 id, const char *format)
{
    editMFElementIDs()->push_back(id);
    editMFFormats   ()->push_back(format ? format : "");
}

/*! Convenience function to add a line of text.
*/
void SimpleStatisticsForeground::addText(const char *text)
{
    addElement( -1, text );
}

/*! Convenience function to clear all elements.
*/
void SimpleStatisticsForeground::clearElems(void)
{
    editMFElementIDs()->clear();
    editMFFormats   ()->clear();

    if(getCollector() != NULL)
    {
        getCollector()->clearElems();
    }
}

/*! Initialize the text used. It is compiled into the library as
    StatisticsDefaultFontData and used as a TXF font.
*/
void SimpleStatisticsForeground::initText(const std::string &family, Real32 size)
{
    // Cleanup
    _face     = NULL;
    _texchunk = NULL;

    // Create the font
    if (family.empty() == false)
    {
        TextTXFParam param;
        param.size = static_cast<UInt32>(size);
        _face = TextTXFFace::create(family, TextFace::STYLE_PLAIN, param);
        if (_face != 0)
        {
            _texchunk = TextureObjChunk::createLocal();
            ImageUnrecPtr texture = _face->getTexture();
            _texchunk->setImage(texture);
            _texchunk->setWrapS(GL_CLAMP);
            _texchunk->setWrapT(GL_CLAMP);
            _texchunk->setMinFilter(GL_NEAREST);
            _texchunk->setMagFilter(GL_NEAREST);
        }
    }

    // We failed to create the font - fallback to the default font
    if (_face == 0)
    {
        _face     = StatisticsDefaultFont::the()->getFace();
        _texchunk = StatisticsDefaultFont::the()->getTexture();
    }
}

/*! Draw the statistics lines.
*/
void SimpleStatisticsForeground::draw(DrawEnv *pEnv)
{
    if(getActive() == false)
        return;

    if(_face == 0)
        initText(getFamily(), getSize());

    if ((getCollector() == NULL) || 
        (!getCollector()->getNumOfElems() && !getMFElementIDs()->size()))
        return; // nothing to do

    Real32  pw = Real32(pEnv->getPixelWidth ());
    Real32  ph = Real32(pEnv->getPixelHeight());

    if(pw < 1 || ph < 1)
        return;

    glPushAttrib(GL_LIGHTING_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Set viewport. We want to map one unit to one pixel on the
    // screen. Some sources in the internet say that we should
    // add an offset of -0.375 to prevent rounding errors. Don't
    // know if that is true, but it seems to work.
    glOrtho(0 - 0.375, pw - 0.375, 0 - 0.375, ph - 0.375, 0, 1);

    // retrieve text
    std::vector < std::string > stat;

    StatCollector *col = this->getCollector();
    StatElem      *el;

    if(getMFElementIDs()->size() != 0)
    {
        for(UInt32 i = 0; i < getMFElementIDs()->size(); ++i)
        {
            Int32 id(getElementIDs(i));
            el = ((id >= 0) ? col->getElem(id) : 0);

            stat.resize(stat.size() + 1);
            std::vector < std::string >::iterator str = stat.end() - 1;

            const char  *format = NULL;
            if(i < getMFFormats()->size() && getFormats(i).length())
            {
                format = getFormats(i).c_str();
            }

            if (el)
                el->putToString(*str, format);
            else
                *str = format;
        }
    }
    else    // fallback, show all elements
    {
        for(UInt32 i = 0; i < col->getNumOfElems(); ++i)
        {
            el = col->getElem(i, false);
            if(el)
            {
                std::string desc(el->getDesc()->getName()), eltext;

                el->putToString(eltext);
                desc = desc + " : " + eltext;

                stat.resize(stat.size() + 1);
                std::vector < std::string >::iterator str = stat.end() - 1;
                *str = desc;
            }
        }
    }

    TextLayoutParam layoutParam;
    layoutParam.spacing = 1.1f;
    layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
    layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;

    TextLayoutResult layoutResult;
    _face->layout(stat, layoutParam, layoutResult);

    Real32 scale = 1 / _face->getScale();
    Real32 size = _face->getParam().size;
    Real32 textWidth = layoutResult.textBounds.x() * scale + size + getTextMargin().x() * 2.0f;
    Real32 textHeight = layoutResult.textBounds.y() * scale + size + getTextMargin().y() * 2.0f;

    // Let's do some simple form of layout management
    Real32 orthoX = 0, orthoY = ph;

    switch ( getHorizontalAlign() )
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

    switch ( getVerticalAlign() )
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
        glVertex2f(0, -textHeight);
        glVertex2f(textWidth, -textHeight);
        glVertex2f(textWidth, 0);
        glVertex2f(0, 0);
    glEnd();

    // draw border
    if(getBorderColor().alpha() >= 0.0f)
    {
        glColor4fv(
            static_cast<const GLfloat *>(getBorderColor().getValuesRGBA()));

        glBegin(GL_LINE_LOOP);
            glVertex2f(getBorderOffset().x(), 
                       -textHeight + 1 + getBorderOffset().y());
            glVertex2f(textWidth - 1 - getBorderOffset().x(), 
                       -textHeight + 1 + getBorderOffset().y());
            glVertex2f(textWidth - 1 - getBorderOffset().x(), 
                       -1 - getBorderOffset().y());
            glVertex2f(getBorderOffset().x(), -1 - getBorderOffset().y());
        glEnd();
    }

    glTranslatef( 0.5 * size + getTextMargin().x(), 
                 -0.5 * size - getTextMargin().y(), 
                  0.0);

    _texchunk   ->activate(pEnv);
    _texenvchunk->activate(pEnv);

    // draw text shadow
    glColor4fv(static_cast<const GLfloat *>(getShadowColor().getValuesRGBA()));
    glPushMatrix();
    glTranslatef(getShadowOffset().x(), getShadowOffset().y(), 0);
    glScalef(scale, scale, 1);
    _face->drawCharacters(layoutResult);

    // draw text
    glColor4fv(static_cast<const GLfloat *>(getColor().getValuesRGBA()));
    glPopMatrix();
    glScalef(scale, scale, 1);
    _face->drawCharacters(layoutResult);

    _texchunk   ->deactivate(pEnv);
    _texenvchunk->deactivate(pEnv);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}
