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
#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#ifdef OSG_HAS_SSTREAM
#include <sstream>
#else
#include <strstream>
#endif

#include <OSGImage.h>

#include <OSGViewport.h>

#include "OSGSimpleStatisticsForeground.h"
#include "OSGStatisticsDefaultFont.h"

#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextTXFGlyph.h"

OSG_USING_NAMESPACE

/*! \class OSG::SimpleStatisticsForeground
    \ingroup GrpSystemWindowForegroundsStatistics

SimpleStatisticsForeground displays the Statistics info as simple text lines.
See \ref PageSystemWindowForegroundStatisticsSimple for a description.

The format string for the given elements are stored in the _mfFormats Field,
the size and color used for all lines in _sfSize and _sfColor.
*/
/* static vars */
TextTXFFace *SimpleStatisticsForeground::       _face = 0;

TextureChunkPtr SimpleStatisticsForeground::    _texchunk;

/*----------------------- constructors & destructors ----------------------*/

SimpleStatisticsForeground::SimpleStatisticsForeground(void) :
    Inherited()
{
}

/* */
SimpleStatisticsForeground::SimpleStatisticsForeground(
    const SimpleStatisticsForeground &source) :
    
    Inherited(source)
{
}

/* */
SimpleStatisticsForeground::~SimpleStatisticsForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SimpleStatisticsForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/* */
void SimpleStatisticsForeground::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin    )
{
    Inherited::changed(whichField, origin);
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
    editElementIDs().push_back(desc.getID());
    editFormats().push_back(format ? format : "");
}

/*! Convenience function to add an element and format.
*/
void SimpleStatisticsForeground::addElement(Int32 id, const char *format)
{
    editElementIDs().push_back(id);
    editFormats().push_back(format ? format : "");
}

/*! Initialize the text used. It is compiled into the library as
    StatisticsDefaultFontData and used as a TXF font.
*/


void SimpleStatisticsForeground::initText(void)
{
    // create the text needed
#ifdef OSG_HAS_SSTREAM
    std::istringstream stream(StatisticsDefaultFontString,
                              std::istringstream::in |
                              std::istringstream::out);
#else
    std::istrstream stream((char *) StatisticsDefaultFontData,
                           StatisticsDefaultFontDataSize);
#endif
    _face = TextTXFFace::createFromStream(stream);
    addRefP(_face);

    ImagePtr texture = _face->getTexture();
    _texchunk = TextureChunk::create();

    _texchunk->setImage(texture);
    _texchunk->setWrapS(GL_CLAMP);
    _texchunk->setWrapT(GL_CLAMP);
    _texchunk->setEnvMode(GL_MODULATE);
}

/*! Draw the statistics lines.
*/
void SimpleStatisticsForeground::draw(DrawEnv *pEnv, Viewport *pPort)
{
    if (_face == 0)
        initText();

    Real32  pw = Real32(pPort->getPixelWidth ());
    Real32  ph = Real32(pPort->getPixelHeight());

    if(pw < 1 || ph < 1)
        return;

    GLboolean    light = glIsEnabled(GL_LIGHTING);

    GLint   fill[2];
    glGetIntegerv(GL_POLYGON_MODE, fill);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLboolean    depth = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    GLboolean    colmat = glIsEnabled(GL_COLOR_MATERIAL);
    glDisable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    Real32  aspect = pw / ph;
    Real32  size = getSize();

    glOrtho(-0.5, -0.5 + ph / size * aspect, 0.5 - ph / size, 0.5, 0, 1);

    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // draw text
    std::vector < std::string > stat;

    StatCollector *col = &(this->editCollector());
    StatElem      *el;

    if(getElementIDs().size() != 0)
    {
        for(UInt32 i = 0; i < getElementIDs().size(); ++i)
        {
            Int32 id(getElementIDs()[i]);
            el = ((id >= 0) ? col->getElem(id) : 0);

            stat.resize(stat.size() + 1);
            std::vector < std::string >::iterator str = stat.end() - 1;

            const char  *format = NULL;
            if(i < getFormats().size() && getFormats()[i].length())
            {
              format = getFormats()[i].c_str();
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
                std::string desc(el->getDesc()->getName().str()), eltext;
                
                el->putToString(eltext);
                desc = desc + " : " + eltext;
                
                stat.resize(stat.size() + 1);
                std::vector < std::string >::iterator str = stat.end() - 1;
                *str = desc;
            }
        }
    }

    TextLayoutParam layoutParam;
    layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
    layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;
    TextLayoutResult layoutResult;
    _face->layout(stat, layoutParam, layoutResult);

    _texchunk->activate(pEnv);

    glColor4fv((GLfloat *) getColor().getValuesRGBA());

    glBegin(GL_QUADS);
    UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    for(i = 0; i < numGlyphs; ++i)
    {
        const TextTXFGlyph &glyph = _face->getTXFGlyph(layoutResult.indices[i]);
        Real32 width = glyph.getWidth();
        Real32 height = glyph.getHeight();
        // No need to draw invisible glyphs
        if ((width <= 0.f) || (height <= 0.f))
            continue;

        // Calculate coordinates
        const Vec2f &pos = layoutResult.positions[i];
        Real32 posLeft = pos.x();
        Real32 posTop = pos.y();
        Real32 posRight = pos.x() + width;
        Real32 posBottom = pos.y() - height;
        Real32 texCoordLeft = glyph.getTexCoord(TextTXFGlyph::COORD_LEFT);
        Real32 texCoordTop = glyph.getTexCoord(TextTXFGlyph::COORD_TOP);
        Real32 texCoordRight = glyph.getTexCoord(TextTXFGlyph::COORD_RIGHT);
        Real32 texCoordBottom = glyph.getTexCoord(TextTXFGlyph::COORD_BOTTOM);

        // lower left corner
        glTexCoord2f(texCoordLeft, texCoordBottom);
        glVertex2f(posLeft, posBottom);

        // lower right corner
        glTexCoord2f(texCoordRight, texCoordBottom);
        glVertex2f(posRight, posBottom);

        // upper right corner
        glTexCoord2f(texCoordRight, texCoordTop);
        glVertex2f(posRight, posTop);

        // upper left corner
        glTexCoord2f(texCoordLeft, texCoordTop);
        glVertex2f(posLeft, posTop);
    }
    glEnd();

    _texchunk->deactivate(pEnv);

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if(depth == GL_TRUE)
        glEnable(GL_DEPTH_TEST);
    if(light == GL_TRUE)
        glEnable(GL_LIGHTING);
    if(colmat == GL_TRUE)
        glEnable(GL_COLOR_MATERIAL);

    glPolygonMode(GL_FRONT_AND_BACK, fill[0]);
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */
#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif
namespace
{
static char cvsid_cpp[] = "@(#)$Id: OSGSimpleStatisticsForeground.cpp,v 1.1.2.1 2006/05/08 06:01:14 vossg Exp $";
static char cvsid_hpp[] = OSGSIMPLESTATISTICSFOREGROUND_HEADER_CVSID;
static char cvsid_inl[] = OSGSIMPLESTATISTICSFOREGROUND_INLINE_CVSID;
}
