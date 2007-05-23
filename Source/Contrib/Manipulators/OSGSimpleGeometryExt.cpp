/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include "OSGSimpleGeometryExt.h"

#include <OSGSimpleMaterial.h>
#include <OSGLineChunk.h>
#include <OSGGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGFaceIterator.h>
#include <OSGComponentTransform.h>

using namespace std;

OSG_BEGIN_NAMESPACE

GeometryPtr makeGridGeo(const Real32   width,
                        const Real32   depth,
                        const Real32   hCellWidth,
                        const Color3f &color     )
{
    Int32       nCols, nRows;
    Real32      x, z;

    const Color3f darkerColor =
        Color3f(color[0] - 0.4, color[1] - 0.4, color[2] - 0.4);

    GeometryPtr        geo     = Geometry::create();
    GeoPositions3fPtr  pnts    = GeoPositions3f::create();
    GeoPLengthsUI32Ptr lens    = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr    types   = GeoPTypesUI8::create();
    GeoColors3fPtr     colors  = GeoColors3f::create();
//    GeoIndicesUI32Ptr  indices = GeoIndicesUI32::create();
    SimpleMaterialPtr  mat     = SimpleMaterial::create();

    Real32 height   (0.0        );
    Real32 widthHalf(width / 2.0);
    Real32 depthHalf(depth / 2.0);
//    hCellWidth     = 1;
    Real32 vCellWidth(hCellWidth);
    nCols        = Int32(width / hCellWidth);
    nRows        = Int32(depth / vCellWidth);

    /*
    SLOG << "creating Grid: width=" << width
         << ", depth=" << depth
         << ", hCellWidth=" << hCellWidth
         << ", vCellWidth=" << vCellWidth
         << ", nCols=" << nCols
         << ", nRows=" << nRows << endl;
    */
    Int32 pntCnt(0);

    // horizontal lines
    for( Real32 d = -nRows / 2; d <= nRows / 2; ++d )
    {
        z = d * vCellWidth;
        pnts->addValue(Pnt3f(-widthHalf, height, z));
        pnts->addValue(Pnt3f( widthHalf, height, z));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(color);
        colors->addValue(color);
    }

    // vertical lines
    for( Real32 w = -nCols/2; w <= nCols/2; ++w )
    {
        x = w * hCellWidth;
        pnts->addValue(Pnt3f(x, height, -depthHalf));
        pnts->addValue(Pnt3f(x, height,  depthHalf));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(color);
        colors->addValue(color);
    }

    /*
    // horizontal & vertical mid lines in different color
    pnts->addValue(Pnt3f(-widthHalf, height, 0));
    pnts->addValue(Pnt3f( widthHalf, height, 0));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);

    pnts->addValue(Pnt3f(0, height, -depthHalf));
    pnts->addValue(Pnt3f(0, height,  depthHalf));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);
    */

    //SLOG << "Grid has " << pntCnt << " points.\n" << endl;

    types->addValue(GL_LINES);
    lens->addValue (pntCnt  );

    // set the color for the grid
    mat->setAmbient(color);
    mat->setDiffuse(color);
    mat->setLit    (false);

    geo->setPositions(pnts   );
//    geo->setIndices  (indices);
    geo->setColors   (colors );
    geo->setTypes    (types  );
    geo->setLengths  (lens   );
    geo->setMaterial (mat    );

    commitChanges();

    return geo;
}

GeometryPtr makeGridBorderGeo(const Real32   width,
                              const Real32   depth,
                              const Color3f &color)
{
    const Color3f darkerColor =
        Color3f( color[0]-0.4, color[1]-0.4, color[2]-0.4 );

    GeometryPtr        geo       = Geometry::create();
    GeoPositions3fPtr  pnts      = GeoPositions3f::create();
    GeoPLengthsUI32Ptr lens      = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr    types     = GeoPTypesUI8::create();
    GeoColors3fPtr     colors    = GeoColors3f::create();
//    GeoIndicesUI32Ptr  indices   = GeoIndicesUI32::create();
    SimpleMaterialPtr  mat       = SimpleMaterial::create();
    LineChunkPtr       lineChunk = LineChunk::create();

    Real32 height   (0.0        );
    Real32 widthHalf(width / 2.0);
    Real32 depthHalf(depth / 2.0);

    Int32 pntCnt(0);

    // horizontal & vertical mid lines in different color
    pnts->addValue(Pnt3f(-widthHalf, height, 0));
    pnts->addValue(Pnt3f( widthHalf, height, 0));
    pntCnt++; pntCnt++;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);

    pnts->addValue(Pnt3f(0, height, -depthHalf));
    pnts->addValue(Pnt3f(0, height,  depthHalf));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);

    // the border
    pnts->addValue(Pnt3f(-widthHalf, 0, depthHalf));
    pnts->addValue(Pnt3f( widthHalf, 0, depthHalf));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);

    pnts->addValue(Pnt3f(widthHalf, 0,  depthHalf));
    pnts->addValue(Pnt3f(widthHalf, 0, -depthHalf));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);

    pnts->addValue(Pnt3f( widthHalf, 0, -depthHalf));
    pnts->addValue(Pnt3f(-widthHalf, 0, -depthHalf));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);

    pnts->addValue(Pnt3f(-widthHalf, 0, -depthHalf));
    pnts->addValue(Pnt3f(-widthHalf, 0,  depthHalf));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(darkerColor);
    colors->addValue(darkerColor);

    lineChunk->setWidth (1   );
    lineChunk->setSmooth(true);

    types->addValue(GL_LINES);
    lens->addValue (pntCnt  );

    // set the color for the grid
    mat->setLit  (false    );
    mat->addChunk(lineChunk);

    geo->setPositions(pnts   );
//    geo->setIndices  (indices);
    geo->setColors   (colors );
    geo->setTypes    (types  );
    geo->setLengths  (lens   );
    geo->setMaterial (mat    );

    commitChanges();

    return geo;
}

/*! \brief create a grid
 *  \ingroup SimpleGeometryExt
 *
 * Creates a grid with the specified <i>width</i> and <i>height</i>.
 * The grid has the base color <i>color</i>.
 */
NodePtr makeGrid(const Real32   width,
                 const Real32   depth,
                 const Real32   hCellWidth,
                 const Color3f &color     )
{
    NodePtr  grpNode    = Node::create();
    GroupPtr grpCore    = Group::create();
    NodePtr  gridNode   = Node::create();
    NodePtr  borderNode = Node::create();

    gridNode->setCore  (makeGridGeo(width, depth, hCellWidth, color));
    borderNode->setCore(makeGridBorderGeo(width, depth, color)      );

    grpNode->setCore (grpCore   );
    grpNode->addChild(gridNode  );
    grpNode->addChild(borderNode);

    commitChanges();

    return grpNode;
}


NodePtr makeSelection(NodePtr geoN)
{
    NodePtr               transN = Node::create();
    NodePtr               node   = Node::create();
    ComponentTransformPtr transC = ComponentTransform::create();

    node->setCore(makeSelectionGeo(geoN));

    transN->setCore (transC);
    transN->addChild(node  );

    addRef(transN);

    commitChanges();

    return transN;
}

GeometryPtr makeSelectionGeo(NodePtr geoN)
{
    Pnt3f min, max;
    geoN->getVolume().getBounds(min, max);

    GeometryPtr        geo       = Geometry::create();
    GeoPositions3fPtr  newPnts   = GeoPositions3f::create();
    GeoPLengthsUI32Ptr lens      = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr    types     = GeoPTypesUI8::create();
    GeoColors3fPtr     colors    = GeoColors3f::create();

//    GeoIndicesUI32Ptr  indices   = GeoIndicesUI32::create();
    SimpleMaterialPtr  mat       = SimpleMaterial::create();

    LineChunkPtr       lineChunk = LineChunk::create();

    GeometryPtr selGeoC = cast_dynamic<GeometryPtr>(geoN->getCore());
    if( selGeoC != NullFC )
    {
        GeoPositions3fPtr pnts = cast_dynamic<GeoPositions3fPtr>(selGeoC->getPositions());
//        GeoPositions3f::StoredFieldType     *p = pnts->getFieldPtr();

//        GeoPositions3f::StoredFieldType::iterator it;
        FaceIterator fi;

        for(fi=selGeoC->beginFaces(); fi!=selGeoC->endFaces(); ++fi)
        {
            newPnts->addValue(fi.getPosition(0));
            newPnts->addValue(fi.getPosition(1));
            newPnts->addValue(fi.getPosition(2));

            colors->addValue(Color3f(1, 1, 1));
            colors->addValue(Color3f(1, 1, 1));
            colors->addValue(Color3f(1, 1, 1));

            types->addValue(GL_LINE_STRIP);
            lens->addValue (3            );
        }
    }

    lineChunk->setWidth (1    );
    lineChunk->setSmooth(false);

    // set the color for the grid
    mat->setLit  (false    );
    mat->addChunk(lineChunk);

    geo->setPositions(newPnts);
//    geo->setIndices  (indices);
//    geo->setColors   (colors );
    geo->setTypes    (types  );
    geo->setLengths  (lens   );
    geo->setMaterial (mat    );

    commitChanges();

    return geo;
}

GeometryPtr makeCoordAxisGeo(const Real32 length,
                             const Real32 lineWidth,
                             const bool   showAxisName)
{
    GeometryPtr        geo       = Geometry::create();
    GeoPositions3fPtr  pnts      = GeoPositions3f::create();
    GeoPLengthsUI32Ptr lens      = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr    types     = GeoPTypesUI8::create();
    GeoColors3fPtr     colors    = GeoColors3f::create();
//    GeoIndicesUI32Ptr  indices   = GeoIndicesUI32::create();
    SimpleMaterialPtr  mat       = SimpleMaterial::create();
    LineChunkPtr       lineChunk = LineChunk::create();

    Int32 pntCnt(0);
    // the x-axis coords and colors
    pnts->addValue(Pnt3f(0     , 0, 0));
    pnts->addValue(Pnt3f(length, 0, 0));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(Color3f(1, 0, 0));
    colors->addValue(Color3f(1, 0, 0));

    // the y-axis coords and colors
    pnts->addValue(Pnt3f(0, 0,      0));
    pnts->addValue(Pnt3f(0, length, 0));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(Color3f(0, 1, 0));
    colors->addValue(Color3f(0, 1, 0));

    // the z-axis coords and colors
    pnts->addValue(Pnt3f(0, 0, 0     ));
    pnts->addValue(Pnt3f(0, 0, length));
    ++pntCnt;
    ++pntCnt;
    colors->addValue(Color3f(0, 0, 1));
    colors->addValue(Color3f(0, 0, 1));

    if( showAxisName )
    {
        // the x text (drawn with lines)
        pnts->addValue(Pnt3f(length      ,   0.125, 0));
        pnts->addValue(Pnt3f(length + 0.25, -0.125, 0));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(Color3f(1, 0, 0)               );
        colors->addValue(Color3f(1, 0, 0)               );
        pnts->addValue  (Pnt3f(length       , -0.125, 0));
        pnts->addValue  (Pnt3f(length + 0.25,  0.125, 0));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 0, 0));

        // the y text (drawn with lines)
        pnts->addValue(Pnt3f(-0.125, length       , 0));
        pnts->addValue(Pnt3f( 0.125, length + 0.25, 0));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(Color3f(0, 1, 0)                );
        colors->addValue(Color3f(0, 1, 0)                );
        pnts->addValue  (Pnt3f(-0.125, length + 0.25 , 0));
        pnts->addValue  (Pnt3f( 0.000, length + 0.125, 0));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(Color3f(0, 1, 0));
        colors->addValue(Color3f(0, 1, 0));

        // the z text (drawn with lines)
        pnts->addValue(Pnt3f(-0.125, 0, length));
        pnts->addValue(Pnt3f( 0.125, 0, length));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(Color3f(0, 0, 1)               );
        colors->addValue(Color3f(0, 0, 1)               );
        pnts->addValue  (Pnt3f( 0.125, 0, length       ));
        pnts->addValue  (Pnt3f(-0.125, 0, length + 0.25));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(Color3f(0, 0, 1)               );
        colors->addValue(Color3f(0, 0, 1)               );
        pnts->addValue  (Pnt3f(-0.125, 0, length + 0.25));
        pnts->addValue  (Pnt3f( 0.125, 0, length + 0.25));
        ++pntCnt;
        ++pntCnt;
        colors->addValue(Color3f(0, 0, 1));
        colors->addValue(Color3f(0, 0, 1));
    }

    //SLOG << "CoordAxis has " << pntCnt << " points.\n" << endl;

    types->addValue(GL_LINES);
    lens->addValue (pntCnt);

    lineChunk->setWidth(lineWidth);

    /*
    mat->setAmbient(Color3f(1, 1, 1));
    mat->setDiffuse(Color3f(1, 1, 1));
    */
    mat->addChunk  (lineChunk       );
    mat->setLit    (false           );

    geo->setPositions(pnts   );
    geo->setColors   (colors );
//    geo->setIndices  (indices);
    geo->setTypes    (types  );
    geo->setLengths  (lens   );
    geo->setMaterial (mat    );

    commitChanges();

    return geo;
}

NodePtr makeCoordAxis(const Real32 length,
                      const Real32 lineWidth,
                      const bool   showAxisName)
{
    NodePtr node = Node::create();
    node->setCore(makeCoordAxisGeo(length, lineWidth, showAxisName));
    commitChanges();

    return node;
}

PolygonChunkPtr _gayaPolygonChunk;

PolygonChunkPtr getPolygonChunk(const UInt16 faces,
                                const UInt16 mode )
{
    if( _gayaPolygonChunk == NullFC )
    {
        _gayaPolygonChunk = PolygonChunk::create();

        addRef(_gayaPolygonChunk);

        _gayaPolygonChunk->setCullFace(faces);
        _gayaPolygonChunk->setFrontMode(mode);
        _gayaPolygonChunk->setSmooth(true);
        _gayaPolygonChunk->setOffsetLine(true);
        _gayaPolygonChunk->setOffsetFill(false);
        _gayaPolygonChunk->setOffsetFactor(-1);
//        _gayaPolygonChunk->setOffsetBias(1);

        commitChanges();
    }
    return _gayaPolygonChunk;
}

MaterialChunkPtr _gayaMaterialChunk;

MaterialChunkPtr getMaterialChunk(const Color4f &ambientColor,
                                  const Color4f &diffuseColor,
                                  const Color4f &specularColor,
                                  const bool     lit          )
{
    if( _gayaMaterialChunk == NullFC )
    {
        _gayaMaterialChunk = MaterialChunk::create();

        addRef(_gayaMaterialChunk);

        _gayaMaterialChunk->setDiffuse(diffuseColor);
        _gayaMaterialChunk->setAmbient(ambientColor);
        _gayaMaterialChunk->setSpecular(specularColor);
        _gayaMaterialChunk->setLit(lit);

        commitChanges();
    }
    return _gayaMaterialChunk;
}

ChunkMaterialPtr _gayaSelectionMaterial;

ChunkMaterialPtr getSelectionMaterial()
{
    if( _gayaSelectionMaterial == NullFC )
    {
        _gayaSelectionMaterial = ChunkMaterial::create();

        addRef(_gayaSelectionMaterial);

        _gayaSelectionMaterial->addChunk(getPolygonChunk());
        _gayaSelectionMaterial->addChunk(getMaterialChunk(Color4f(1,1,1,0),
                                                          Color4f(1,1,1,0)));

        commitChanges();
    }
    return _gayaSelectionMaterial;
}


OSG_END_NAMESPACE
