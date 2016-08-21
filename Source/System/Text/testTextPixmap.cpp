#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGBaseFunctions.h"
#include "OSGTransform.h"
#include "OSGGroup.h"
#include "OSGImage.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGSimpleStatisticsForeground.h"
#include "OSGSolidBackground.h"
#include "OSGGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"

#include "OSGTextPixmapFace.h"
#include "OSGTextPixmapGlyph.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextFaceFactory.h"

// Activate the OpenSG namespace
using namespace std;

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManagerRefPtr mgr;

OSG::NodeRecPtr scene;

OSG::SimpleStatisticsForegroundRecPtr statfg;
OSG::StatElemDesc<OSG::StatStringElem> familyDesc("family", "The font family");
OSG::StatElemDesc<OSG::StatStringElem> styleDesc("style", "The font style");
OSG::StatElemDesc<OSG::StatStringElem> majorAlignDesc("majorAlignment", "The major alignment");
OSG::StatElemDesc<OSG::StatStringElem> minorAlignDesc("minorAlignment", "The minor alignment");
OSG::StatElemDesc<OSG::StatStringElem> dirDesc("direction", "The direction (horizontal or vertical)");
OSG::StatElemDesc<OSG::StatStringElem> horiDirDesc("horizontal direction", "The horizontal direction (left-to-right or right-to-left)");
OSG::StatElemDesc<OSG::StatStringElem> vertDirDesc("vertical direction", "The vertical direction (top-to-bottom or bottom-to-top)");

OSG::TextPixmapFaceRefPtr pFace;
string family = "SANS";
vector<string> families;
OSG::TextFace::Style style = OSG::TextFace::STYLE_PLAIN;
OSG::TextLayoutParam oLayoutParam;
vector<string> lines;

int mainMenuID;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Create the coordinate cross
OSG::NodeTransitPtr createCoordinateCross()
{
    OSG::GeometryUnrecPtr geoPtr = OSG::Geometry::create();

    OSG::GeoUInt8PropertyUnrecPtr typesPtr = OSG::GeoUInt8Property::create();
    typesPtr->push_back(GL_LINES);
    geoPtr->setTypes(typesPtr);

    OSG::GeoUInt32PropertyUnrecPtr lensPtr = OSG::GeoUInt32Property::create();
    lensPtr->push_back(6);
    geoPtr->setLengths(lensPtr);

    OSG::GeoPnt3fPropertyUnrecPtr posPtr = OSG::GeoPnt3fProperty::create();
    posPtr->push_back(OSG::Vec3f(-0.1f, 0.f, 0.f));
    posPtr->push_back(OSG::Vec3f(1.f, 0.f, 0.f));
    posPtr->push_back(OSG::Vec3f(0.f, -0.1f, 0.f));
    posPtr->push_back(OSG::Vec3f(0.f, 1.f, 0.f));
    posPtr->push_back(OSG::Vec3f(0.f, 0.f, -0.1f));
    posPtr->push_back(OSG::Vec3f(0.f, 0.f, 1.f));
    geoPtr->setPositions(posPtr);

    OSG::GeoColor3fPropertyUnrecPtr colorsPtr = OSG::GeoColor3fProperty::create();
    colorsPtr->push_back(OSG::Color3f(1.f, 0.f, 0.f));
    colorsPtr->push_back(OSG::Color3f(0.f, 1.f, 0.f));
    colorsPtr->push_back(OSG::Color3f(0.f, 0.f, 1.f));
    geoPtr->setColors(colorsPtr);

    OSG::GeoUInt32PropertyUnrecPtr posIndicesPtr = OSG::GeoUInt32Property::create();
    OSG::GeoUInt32PropertyUnrecPtr colIndicesPtr = OSG::GeoUInt32Property::create();
    // X Axis
    posIndicesPtr->push_back(0);
    colIndicesPtr->push_back(0);
    posIndicesPtr->push_back(1);
    colIndicesPtr->push_back(0);
    // Y Axis
    posIndicesPtr->push_back(2);
    colIndicesPtr->push_back(1);
    posIndicesPtr->push_back(3);
    colIndicesPtr->push_back(1);
    // Z Axis
    posIndicesPtr->push_back(4);
    colIndicesPtr->push_back(2);
    posIndicesPtr->push_back(5);
    colIndicesPtr->push_back(2);
    geoPtr->setIndex(posIndicesPtr, OSG::Geometry::PositionsIndex);
    geoPtr->setIndex(colIndicesPtr, OSG::Geometry::ColorsIndex);

    OSG::SimpleMaterialUnrecPtr matPtr = OSG::SimpleMaterial::create();
    geoPtr->setMaterial(matPtr);

    OSG::NodeTransitPtr nodePtr = OSG::Node::create();
    nodePtr->setCore(geoPtr);

    return nodePtr;
}

// Create the metrics
OSG::NodeTransitPtr createMetrics(OSG::TextFace *face, OSG::Real32 scale, const OSG::TextLayoutParam &layoutParam,
                      const OSG::TextLayoutResult &layoutResult)
{
    OSG::GeometryUnrecPtr geoPtr = OSG::Geometry::create();

    OSG::GeoUInt8PropertyUnrecPtr typesPtr = OSG::GeoUInt8Property::create();
    geoPtr->setTypes(typesPtr);

    OSG::GeoUInt32PropertyUnrecPtr lensPtr = OSG::GeoUInt32Property::create();
    geoPtr->setLengths(lensPtr);

    OSG::GeoPnt3fPropertyUnrecPtr posPtr = OSG::GeoPnt3fProperty::create();
    geoPtr->setPositions(posPtr);

    OSG::GeoColor3fPropertyUnrecPtr colorsPtr = OSG::GeoColor3fProperty::create();
    colorsPtr->push_back(OSG::Color3f(0.f, 0.f, 1.f));
    colorsPtr->push_back(OSG::Color3f(1.f, 0.f, 0.f));
    colorsPtr->push_back(OSG::Color3f(0.f, 1.f, 0.f));
    colorsPtr->push_back(OSG::Color3f(1.f, 1.f, 0.f));
    geoPtr->setColors(colorsPtr);

    OSG::GeoUInt32PropertyUnrecPtr posIndicesPtr = OSG::GeoUInt32Property::create();
    geoPtr->setIndex(posIndicesPtr, OSG::Geometry::PositionsIndex);
    OSG::GeoUInt32PropertyUnrecPtr colIndicesPtr = OSG::GeoUInt32Property::create();
    geoPtr->setIndex(colIndicesPtr, OSG::Geometry::ColorsIndex);

    OSG::UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    for (i = 0; i < numGlyphs; ++i)
    {
        const OSG::TextGlyph &glyph = face->getGlyph(layoutResult.indices[i]);
        typesPtr->push_back(GL_LINE_LOOP);
        lensPtr->push_back(4);
        const OSG::Vec2f &pos = layoutResult.positions[i];
        OSG::Real32 left = pos.x() * scale;
        OSG::Real32 right = (pos.x() + glyph.getWidth()) * scale;
        OSG::Real32 top = pos.y() * scale;
        OSG::Real32 bottom = (pos.y() - glyph.getHeight()) * scale;
        OSG::UInt32 posOffset = posPtr->size();
        posPtr->push_back(OSG::Vec3f(left, bottom, 0.f));
        posPtr->push_back(OSG::Vec3f(right, bottom, 0.f));
        posPtr->push_back(OSG::Vec3f(right, top, 0.f));
        posPtr->push_back(OSG::Vec3f(left, top, 0.f));
        posIndicesPtr->push_back(posOffset);
        colIndicesPtr->push_back(0);
        posIndicesPtr->push_back(posOffset + 1);
        colIndicesPtr->push_back(0);
        posIndicesPtr->push_back(posOffset + 2);
        colIndicesPtr->push_back(0);
        posIndicesPtr->push_back(posOffset + 3);
        colIndicesPtr->push_back(0);
    }

    // Bounding box
    OSG::Vec2f lowerLeft, upperRight;
    face->calculateBoundingBox(layoutResult, lowerLeft, upperRight);
    typesPtr->push_back(GL_LINE_LOOP);
    lensPtr->push_back(4);
    OSG::Real32 left = lowerLeft.x() * scale;
    OSG::Real32 right = upperRight.x() * scale;
    OSG::Real32 top = upperRight.y() * scale;
    OSG::Real32 bottom = lowerLeft.y() * scale;
    OSG::UInt32 posOffset = posPtr->size();
    posPtr->push_back(OSG::Vec3f(left, bottom, 0.f));
    posPtr->push_back(OSG::Vec3f(right, bottom, 0.f));
    posPtr->push_back(OSG::Vec3f(right, top, 0.f));
    posPtr->push_back(OSG::Vec3f(left, top, 0.f));
    posIndicesPtr->push_back(posOffset);
    colIndicesPtr->push_back(1);
    posIndicesPtr->push_back(posOffset + 1);
    colIndicesPtr->push_back(1);
    posIndicesPtr->push_back(posOffset + 2);
    colIndicesPtr->push_back(1);
    posIndicesPtr->push_back(posOffset + 3);
    colIndicesPtr->push_back(1);

    // Text bounds & Line bounds
    OSG::Vec2f pos, textPos, offset;
    if (layoutParam.horizontal == true)
    {
        OSG::Real32 lineHeight = face->getHoriAscent() - face->getHoriDescent();
        OSG::Real32 spacing = layoutParam.spacing * lineHeight;
        if (layoutParam.topToBottom == true)
        {
            switch (layoutParam.minorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                    break;
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    pos[1] = textPos[1] = face->getHoriAscent();
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    pos[1] = textPos[1] = (spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    pos[1] = textPos[1] = spacing * (layoutResult.lineBounds.size() - 1) + lineHeight;
                    break;
            }
            offset.setValues(0.f, -spacing);
        }
        else
        {
            switch (layoutParam.minorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                    pos[1] = lineHeight;
                    textPos[1] = spacing * (layoutResult.lineBounds.size() - 1) + lineHeight;
                    break;
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    pos[1] = face->getHoriAscent();
                    textPos[1] = spacing * (layoutResult.lineBounds.size() - 1) + face->getHoriAscent();
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    pos[1] = -(spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f + lineHeight;
                    textPos[1] = (spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    pos[1] = -spacing * (layoutResult.lineBounds.size() - 1);
                    break;
            }
            offset.setValues(0.f, spacing);
        }
    }
    else
    {
        OSG::Real32 lineHeight = face->getVertDescent() - face->getVertAscent();
        OSG::Real32 spacing = layoutParam.spacing * lineHeight;
        if (layoutParam.leftToRight == true)
        {
            switch (layoutParam.minorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                    break;
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    pos[0] = textPos[0] = face->getVertAscent();
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    pos[0] = textPos[0] = -(spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    pos[0] = textPos[0] = -spacing * (layoutResult.lineBounds.size() - 1) - lineHeight;
                    break;
            }
            offset.setValues(spacing, 0.f);
        }
        else
        {
            switch (layoutParam.minorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                    pos[0] = -lineHeight;
                    textPos[0] = -spacing * (layoutResult.lineBounds.size() - 1) - lineHeight;
                    break;
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    pos[0] = -face->getVertDescent();
                    textPos[0] = -spacing * (layoutResult.lineBounds.size() - 1) -face->getVertDescent();
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    pos[0] = (spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f - lineHeight;
                    textPos[0] = -(spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    pos[0] = spacing * (layoutResult.lineBounds.size() - 1);
                    break;
            }
            offset.setValues(-spacing, 0.f);
        }
    }

    typesPtr->push_back(GL_LINE_LOOP);
    lensPtr->push_back(4);
    left = textPos.x();
    top = textPos.y();
    if (layoutParam.horizontal == true)
        if (layoutParam.leftToRight == true)
            switch (layoutParam.majorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    left -= layoutResult.textBounds.x() / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    left -= layoutResult.textBounds.x();
                    break;
            }
        else
            switch (layoutParam.majorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    left -= layoutResult.textBounds.x();
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    left -= layoutResult.textBounds.x() / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    break;
            }
    else
        if (layoutParam.topToBottom == true)
            switch (layoutParam.majorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    top += layoutResult.textBounds.y() / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    top += layoutResult.textBounds.y();
                    break;
            }
        else
            switch (layoutParam.majorAlignment)
            {
                case OSG::TextLayoutParam::ALIGN_BEGIN:
                case OSG::TextLayoutParam::ALIGN_FIRST:
                    top += layoutResult.textBounds.y();
                    break;
                case OSG::TextLayoutParam::ALIGN_MIDDLE:
                    top += layoutResult.textBounds.y() / 2.f;
                    break;
                case OSG::TextLayoutParam::ALIGN_END:
                    break;
            }
    left *= scale;
    right = left + layoutResult.textBounds.x() * scale;
    top *= scale;
    bottom = top - layoutResult.textBounds.y() * scale;
    posOffset = posPtr->size();
    posPtr->push_back(OSG::Vec3f(left, bottom, 0.f));
    posPtr->push_back(OSG::Vec3f(right, bottom, 0.f));
    posPtr->push_back(OSG::Vec3f(right, top, 0.f));
    posPtr->push_back(OSG::Vec3f(left, top, 0.f));
    posIndicesPtr->push_back(posOffset);
    colIndicesPtr->push_back(3);
    posIndicesPtr->push_back(posOffset + 1);
    colIndicesPtr->push_back(3);
    posIndicesPtr->push_back(posOffset + 2);
    colIndicesPtr->push_back(3);
    posIndicesPtr->push_back(posOffset + 3);
    colIndicesPtr->push_back(3);

    vector<OSG::Vec2f>::const_iterator lbIt;
    for (lbIt = layoutResult.lineBounds.begin(); lbIt != layoutResult.lineBounds.end(); ++lbIt)
    {
        typesPtr->push_back(GL_LINE_LOOP);
        lensPtr->push_back(4);
        left = pos.x();
        top = pos.y();
        if (layoutParam.horizontal == true)
            if (layoutParam.leftToRight == true)
                switch (layoutParam.majorAlignment)
                {
                    case OSG::TextLayoutParam::ALIGN_BEGIN:
                    case OSG::TextLayoutParam::ALIGN_FIRST:
                        break;
                    case OSG::TextLayoutParam::ALIGN_MIDDLE:
                        left -= lbIt->x() / 2.f;
                        break;
                    case OSG::TextLayoutParam::ALIGN_END:
                        left -= lbIt->x();
                        break;
                }
            else
                switch (layoutParam.majorAlignment)
                {
                    case OSG::TextLayoutParam::ALIGN_BEGIN:
                    case OSG::TextLayoutParam::ALIGN_FIRST:
                        left -= lbIt->x();
                        break;
                    case OSG::TextLayoutParam::ALIGN_MIDDLE:
                        left -= lbIt->x() / 2.f;
                        break;
                    case OSG::TextLayoutParam::ALIGN_END:
                        break;
                }
        else
            if (layoutParam.topToBottom == true)
                switch (layoutParam.majorAlignment)
                {
                    case OSG::TextLayoutParam::ALIGN_BEGIN:
                    case OSG::TextLayoutParam::ALIGN_FIRST:
                        break;
                    case OSG::TextLayoutParam::ALIGN_MIDDLE:
                        top += lbIt->y() / 2.f;
                        break;
                    case OSG::TextLayoutParam::ALIGN_END:
                        top += lbIt->y();
                        break;
                }
            else
                switch (layoutParam.majorAlignment)
                {
                    case OSG::TextLayoutParam::ALIGN_BEGIN:
                    case OSG::TextLayoutParam::ALIGN_FIRST:
                        top += lbIt->y();
                        break;
                    case OSG::TextLayoutParam::ALIGN_MIDDLE:
                        top += lbIt->y() / 2.f;
                        break;
                    case OSG::TextLayoutParam::ALIGN_END:
                        break;
                }
        left *= scale;
        right = left + lbIt->x() * scale;
        top *= scale;
        bottom = top - lbIt->y() * scale;
        posOffset = posPtr->size();
        posPtr->push_back(OSG::Vec3f(left, bottom, 0.f));
        posPtr->push_back(OSG::Vec3f(right, bottom, 0.f));
        posPtr->push_back(OSG::Vec3f(right, top, 0.f));
        posPtr->push_back(OSG::Vec3f(left, top, 0.f));
        posIndicesPtr->push_back(posOffset);
        colIndicesPtr->push_back(2);
        posIndicesPtr->push_back(posOffset + 1);
        colIndicesPtr->push_back(2);
        posIndicesPtr->push_back(posOffset + 2);
        colIndicesPtr->push_back(2);
        posIndicesPtr->push_back(posOffset + 3);
        colIndicesPtr->push_back(2);

        typesPtr->push_back(GL_LINE_STRIP);
        lensPtr->push_back(2);
        posOffset = posPtr->size();
        if (layoutParam.horizontal == true)
        {
            OSG::Real32 base = top - face->getHoriAscent() * scale;
            posPtr->push_back(OSG::Vec3f(left, base, 0.f));
            posPtr->push_back(OSG::Vec3f(right, base, 0.f));
        }
        else
        {
            OSG::Real32 base = left - face->getVertAscent() * scale;
            posPtr->push_back(OSG::Vec3f(base, top, 0.f));
            posPtr->push_back(OSG::Vec3f(base, bottom, 0.f));
        }
        posIndicesPtr->push_back(posOffset);
        colIndicesPtr->push_back(2);
        posIndicesPtr->push_back(posOffset + 1);
        colIndicesPtr->push_back(2);
        pos += offset;
    }

    OSG::SimpleMaterialUnrecPtr matPtr = OSG::SimpleMaterial::create();
    geoPtr->setMaterial(matPtr);

    OSG::NodeTransitPtr nodePtr = OSG::Node::create();
    nodePtr->setCore(geoPtr);

    return nodePtr;
}

void updateFace(void)
{
    // Try to create new face
    OSG::TextPixmapFaceRefPtr newFace = OSG::TextPixmapFace::create(family, style, 78);
    if (newFace == 0)
        return;
    pFace = newFace;

    // Update information on the screen
    family = pFace->getFamily();

    if(statfg->getCollector() != NULL)
    {
        statfg->getCollector()->getElem(familyDesc)->set(family);
        style = pFace->getStyle();
        OSG::StatStringElem *statElem = statfg->getCollector()->getElem(styleDesc);
        switch (style)
        {
            case OSG::TextFace::STYLE_PLAIN:
                statElem->set("Plain");
                break;
            case OSG::TextFace::STYLE_BOLD:
                statElem->set("Bold");
                break;
            case OSG::TextFace::STYLE_ITALIC:
                statElem->set("Italic");
                break;
            case OSG::TextFace::STYLE_BOLDITALIC:
                statElem->set("Bold & Italic");
                break;
        }
    }
}

const char *alignmentToString(OSG::TextLayoutParam::Alignment alignment)
{
    switch (alignment)
    {
        case OSG::TextLayoutParam::ALIGN_FIRST:
            return "First";
        case OSG::TextLayoutParam::ALIGN_BEGIN:
            return "Begin";
        case OSG::TextLayoutParam::ALIGN_MIDDLE:
            return "Middle";
        case OSG::TextLayoutParam::ALIGN_END:
            return "End";
        default:
            return "???";
    }
}

void updateScene(void)
{
    if(statfg->getCollector() != NULL)
    {
        statfg->getCollector()->getElem(majorAlignDesc)->set(alignmentToString(oLayoutParam.majorAlignment));
        statfg->getCollector()->getElem(minorAlignDesc)->set(alignmentToString(oLayoutParam.minorAlignment));
        statfg->getCollector()->getElem(dirDesc)->set(oLayoutParam.horizontal ? "Horizontal" : "Vertical");
        statfg->getCollector()->getElem(horiDirDesc)->set(oLayoutParam.leftToRight ? "Left to right" : "Right to left");
        statfg->getCollector()->getElem(vertDirDesc)->set(oLayoutParam.topToBottom ? "Top to bottom" : "Bottom to top");
    }

    if(pFace == NULL)
        return;

    OSG::TextLayoutResult layoutResult;
    pFace->layout(lines, oLayoutParam, layoutResult);
    OSG::Vec2f offset;
    OSG::ImageUnrecPtr imagePtr = pFace->makeImage(layoutResult, offset);
    OSG::Real32 width = imagePtr->getWidth();
    OSG::Real32 height = imagePtr->getHeight();
    OSG::Real32 scale = 2.f / (pFace->getHoriAscent() - pFace->getHoriDescent());

    // Put it all together into a Geometry NodeCore.
    OSG::GeometryUnrecPtr geo = OSG::makePlaneGeo(width * scale, height * scale, 1, 1);
    OSG::NodeUnrecPtr textNode = OSG::Node::create();
    textNode->setCore(geo);
    OSG::NodeUnrecPtr transNodePtr = OSG::Node::create();
    OSG::TransformUnrecPtr transPtr = OSG::Transform::create();
    OSG::Matrix transMatrix;
    transMatrix.setTranslate((offset.x() + width / 2.f) * scale, (offset.y() - height / 2.f) * scale, -0.03f);
    transPtr->setMatrix(transMatrix);
    transNodePtr->setCore(transPtr);
    transNodePtr->addChild(textNode);

    OSG::TextureObjChunkUnrecPtr texObjChunk = OSG::TextureObjChunk::create();
    texObjChunk->setImage(imagePtr);
    texObjChunk->setScale(false);
    texObjChunk->setWrapS(GL_CLAMP);
    texObjChunk->setWrapT(GL_CLAMP);
    texObjChunk->setMagFilter(GL_NEAREST);
    texObjChunk->setMinFilter(GL_NEAREST);

    OSG::TextureEnvChunkUnrecPtr texEnvChunk = OSG::TextureEnvChunk::create();
    texEnvChunk->setEnvMode(GL_MODULATE);

    OSG::TextureTransformChunkUnrecPtr texTransChunk = OSG::TextureTransformChunk::create();
    OSG::Real32 textureWidth = OSG::osgNextPower2(static_cast<OSG::UInt32>(width));
    OSG::Real32 textureHeight = OSG::osgNextPower2(static_cast<OSG::UInt32>(height));
    OSG::Matrix matrix;
    matrix.setScale(width / textureWidth, height / textureHeight, 1.f);
    texTransChunk->setMatrix(matrix);

    OSG::MaterialChunkUnrecPtr matChunk = OSG::MaterialChunk::create();
    matChunk->setAmbient(OSG::Color4f(1.f, 1.f, 1.f, 1.f));
    matChunk->setDiffuse(OSG::Color4f(1.f, 1.f, 1.f, 1.f));
    matChunk->setEmission(OSG::Color4f(0.f, 0.f, 0.f, 1.f));
    matChunk->setSpecular(OSG::Color4f(0.f, 0.f, 0.f, 1.f));
    matChunk->setShininess(0);

    OSG::BlendChunkUnrecPtr blendChunk = OSG::BlendChunk::create();
    blendChunk->setSrcFactor(GL_SRC_ALPHA);
    blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    OSG::ChunkMaterialUnrecPtr m = OSG::ChunkMaterial::create();
    m->addChunk(texObjChunk);
    m->addChunk(texEnvChunk);
    m->addChunk(texTransChunk);
    m->addChunk(matChunk);
    m->addChunk(blendChunk);

    geo->setMaterial(m);

    scene->clearChildren();
    scene->addChild(createCoordinateCross());
    scene->addChild(createMetrics(pFace, scale, oLayoutParam, layoutResult));
    scene->addChild(transNodePtr);
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        lines.push_back(argc >= 2 ? argv[1] : "Hello World!");
        lines.push_back("Powered by OpenSG");
        lines.push_back("3rd line");
        oLayoutParam.spacing = 1.5f;
        //oLayoutParam.length.push_back(10.f * 78.f);
        //oLayoutParam.length.push_back(7.f * 78.f);
        //oLayoutParam.length.push_back(-1.f * 78.f);
    
        // put the geometry core into a node
        scene = OSG::Node::create();
        OSG::GroupUnrecPtr groupPtr = OSG::Group::create();
        scene->setCore(groupPtr);
    
        statfg = OSG::SimpleStatisticsForeground::create();
        statfg->setSize(25);
        statfg->setColor(OSG::Color4f(0,1,0,0.9f));
        statfg->addElement(familyDesc, "Family: %s");
        statfg->addElement(styleDesc, "Style: %s");
        statfg->addElement(majorAlignDesc, "Major Alignment: %s");
        statfg->addElement(minorAlignDesc, "Minor Alignment: %s");
        statfg->addElement(dirDesc, "%s");
        statfg->addElement(horiDirDesc, "%s");
        statfg->addElement(vertDirDesc, "%s");
    
        // Create the background
        OSG::SolidBackgroundUnrecPtr bg = OSG::SolidBackground::create();
        bg->setColor(OSG::Color3f(0.1f, 0.1f, 0.5f));
    
        updateFace();
        updateScene();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
    
        // show the whole scene
        mgr->showAll();
    
        // add the statistics forground and the background
        gwin->getPort(0)->addForeground(statfg);
        gwin->getPort(0)->setBackground(bg);
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display( void )
{
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        {
            mgr    = NULL;
            pFace  = NULL;
            scene  = NULL;
            statfg = NULL;

            OSG::osgExit();
            exit(0);
        }
        break;
    }
}

#define COMMAND_FAMILY_SANS 701
#define COMMAND_FAMILY_SERIF 702
#define COMMAND_FAMILY_TYPEWRITER 703
#define COMMAND_FAMILY_BASE 704
#define COMMAND_STYLE_PLAIN 301
#define COMMAND_STYLE_BOLD 302
#define COMMAND_STYLE_ITALIC 303
#define COMMAND_STYLE_BOLDITALIC 304
#define COMMAND_MAJORALIGNMENT_FIRST 101
#define COMMAND_MAJORALIGNMENT_BEGIN 102
#define COMMAND_MAJORALIGNMENT_MIDDLE 103
#define COMMAND_MAJORALIGNMENT_END 104
#define COMMAND_MINORALIGNMENT_FIRST 201
#define COMMAND_MINORALIGNMENT_BEGIN 202
#define COMMAND_MINORALIGNMENT_MIDDLE 203
#define COMMAND_MINORALIGNMENT_END 204
#define COMMAND_HORIZONTAL 401
#define COMMAND_VERTICAL 402
#define COMMAND_LEFTTORIGHT 501
#define COMMAND_RIGHTTOLEFT 502
#define COMMAND_TOPTOBOTTOM 601
#define COMMAND_BOTTOMTOTOP 602

void menu(int command)
{
    switch (command)
    {
        case COMMAND_FAMILY_SANS:
            family = "SANS";
            updateFace();
            break;
        case COMMAND_FAMILY_SERIF:
            family = "SERIF";
            updateFace();
            break;
        case COMMAND_FAMILY_TYPEWRITER:
            family = "TYPEWRITER";
            updateFace();
            break;
        case COMMAND_STYLE_PLAIN:
            style = OSG::TextFace::STYLE_PLAIN;
            updateFace();
            break;
        case COMMAND_STYLE_BOLD:
            style = OSG::TextFace::STYLE_BOLD;
            updateFace();
            break;
        case COMMAND_STYLE_ITALIC:
            style = OSG::TextFace::STYLE_ITALIC;
            updateFace();
            break;
        case COMMAND_STYLE_BOLDITALIC:
            style = OSG::TextFace::STYLE_BOLDITALIC;
            updateFace();
            break;
        case COMMAND_MAJORALIGNMENT_FIRST:
            oLayoutParam.majorAlignment = OSG::TextLayoutParam::ALIGN_FIRST;
            break;
        case COMMAND_MAJORALIGNMENT_BEGIN:
            oLayoutParam.majorAlignment = OSG::TextLayoutParam::ALIGN_BEGIN;
            break;
        case COMMAND_MAJORALIGNMENT_MIDDLE:
            oLayoutParam.majorAlignment = OSG::TextLayoutParam::ALIGN_MIDDLE;
            break;
        case COMMAND_MAJORALIGNMENT_END:
            oLayoutParam.majorAlignment = OSG::TextLayoutParam::ALIGN_END;
            break;
        case COMMAND_MINORALIGNMENT_FIRST:
            oLayoutParam.minorAlignment = OSG::TextLayoutParam::ALIGN_FIRST;
            break;
        case COMMAND_MINORALIGNMENT_BEGIN:
            oLayoutParam.minorAlignment = OSG::TextLayoutParam::ALIGN_BEGIN;
            break;
        case COMMAND_MINORALIGNMENT_MIDDLE:
            oLayoutParam.minorAlignment = OSG::TextLayoutParam::ALIGN_MIDDLE;
            break;
        case COMMAND_MINORALIGNMENT_END:
            oLayoutParam.minorAlignment = OSG::TextLayoutParam::ALIGN_END;
            break;
        case COMMAND_HORIZONTAL:
            oLayoutParam.horizontal = true;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(5, "Vertical", COMMAND_VERTICAL);
            break;
        case COMMAND_VERTICAL:
            oLayoutParam.horizontal = false;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(5, "Horizontal", COMMAND_HORIZONTAL);
            break;
        case COMMAND_LEFTTORIGHT:
            oLayoutParam.leftToRight = true;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(6, "Right to left", COMMAND_RIGHTTOLEFT);
            break;
        case COMMAND_RIGHTTOLEFT:
            oLayoutParam.leftToRight = false;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(6, "Left to right", COMMAND_LEFTTORIGHT);
            break;
        case COMMAND_TOPTOBOTTOM:
            oLayoutParam.topToBottom = true;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(7, "Bottom to top", COMMAND_BOTTOMTOTOP);
            break;
        case COMMAND_BOTTOMTOTOP:
            oLayoutParam.topToBottom = false;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(7, "Top to bottom", COMMAND_TOPTOBOTTOM);
            break;
        default:
            if (command < COMMAND_FAMILY_BASE)
                return;
            family = families[command - COMMAND_FAMILY_BASE];
            updateFace();
    }
    updateScene();
    mgr->showAll();
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    int familyMenuID = glutCreateMenu(menu);
    glutSetMenu(familyMenuID);
    glutAddMenuEntry("SANS", COMMAND_FAMILY_SANS);
    glutAddMenuEntry("SERIF", COMMAND_FAMILY_SERIF);
    glutAddMenuEntry("TYPEWRITER", COMMAND_FAMILY_TYPEWRITER);
    OSG::TextFaceFactory::the()->getFontFamilies(families);
    OSG::UInt32 i;
    for (i = 0; i < families.size(); ++i)
        glutAddMenuEntry(families[i].c_str(), COMMAND_FAMILY_BASE + i);
    int styleMenuID = glutCreateMenu(menu);
    glutSetMenu(styleMenuID);
    glutAddMenuEntry("Plain", COMMAND_STYLE_PLAIN);
    glutAddMenuEntry("Bold", COMMAND_STYLE_BOLD);
    glutAddMenuEntry("Italic", COMMAND_STYLE_ITALIC);
    glutAddMenuEntry("Bold + Italic", COMMAND_STYLE_BOLDITALIC);
    int majorAlignmentMenuID = glutCreateMenu(menu);
    glutSetMenu(majorAlignmentMenuID);
    glutAddMenuEntry("First", COMMAND_MAJORALIGNMENT_FIRST);
    glutAddMenuEntry("Begin", COMMAND_MAJORALIGNMENT_BEGIN);
    glutAddMenuEntry("Middle", COMMAND_MAJORALIGNMENT_MIDDLE);
    glutAddMenuEntry("End", COMMAND_MAJORALIGNMENT_END);
    int minorAlignmentMenuID = glutCreateMenu(menu);
    glutSetMenu(minorAlignmentMenuID);
    glutAddMenuEntry("First", COMMAND_MINORALIGNMENT_FIRST);
    glutAddMenuEntry("Begin", COMMAND_MINORALIGNMENT_BEGIN);
    glutAddMenuEntry("Middle", COMMAND_MINORALIGNMENT_MIDDLE);
    glutAddMenuEntry("End", COMMAND_MINORALIGNMENT_END);
    mainMenuID = glutCreateMenu(menu);
    glutSetMenu(mainMenuID);
    glutAddSubMenu("Family", familyMenuID);
    glutAddSubMenu("Style", styleMenuID);
    glutAddSubMenu("Major Alignment", majorAlignmentMenuID);
    glutAddSubMenu("Minor Alignment", minorAlignmentMenuID);
    glutAddMenuEntry("Vertical", COMMAND_VERTICAL);
    glutAddMenuEntry("Right to left", COMMAND_RIGHTTOLEFT);
    glutAddMenuEntry("Bottom to top", COMMAND_BOTTOMTOTOP);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    return winid;
}
