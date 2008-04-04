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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGTiledQuadTreeTerrain.h"
#include "OSGQuadTreeTerrain.h"
#include "OSGRenderAction.h"
#include "OSGImage.h"
#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTiledQuadTreeTerrainBase.cpp file.
// To modify it, please change the .fcd file (OSGTiledQuadTreeTerrain.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TiledQuadTreeTerrain::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    RenderAction::registerEnterDefault(
        TiledQuadTreeTerrain::getClassType(), 
        reinterpret_cast<Action::Callback>(&TiledQuadTreeTerrain::renderEnter));
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TiledQuadTreeTerrain::TiledQuadTreeTerrain(void) :
    Inherited()
{
}

TiledQuadTreeTerrain::TiledQuadTreeTerrain(
    const TiledQuadTreeTerrain &source) :
    
    Inherited(source)
{
}

TiledQuadTreeTerrain::~TiledQuadTreeTerrain(void)
{
}

/*----------------------------- class specific ----------------------------*/

inline MaterialTransitPtr cloneMaterial(const MaterialPtr &mat)
{
#if 0

    for(MFStateChunkPtr::const_iterator it =  m->getChunks().begin();
                                        it != m->getChunks().end();
                                      ++it)
    {
        clone->addChunk(*it);
    }
#endif

    ChunkMaterialPtr        m     = dynamic_cast<ChunkMaterialPtr>(mat);
    ChunkMaterialTransitPtr clone(NULL);

    if(m != NULL)
    {
        clone = dynamic_pointer_cast<ChunkMaterial>(m->shallowCopy());
    }

    return MaterialTransitPtr(clone);
}


void TiledQuadTreeTerrain::changed(ConstFieldMaskArg whichField, 
                                   UInt32            origin,
                                   BitVector         details)
{
    // GeoMorphing is copied into each terrain node here
    // EyePointValid is set true here
    // EyePoint is calculated in ::renderEnter and copied into each terrain 
    // node PerPixelLighting is copied into each terrain node here
    // UpdateTerrain is copied into each terrain node in ::renderEnter
    // Detail is copied into each terrain node here
    // BorderDetail is set to 1 here

    // changed HeightData
    // * update HeightError and HeightQuad
    if((whichField & HeightTilesFieldMask) && getMFHeightTiles()->size() > 0) 
    {
        if(getParents().size() > 0 && getParents()[0] != NullFC)
        { // parent must be set!
            NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);

            while(pParent->getNChildren() > 0) 
            {
                pParent->subChild(0u);
            }

            Real32 step   = 
                (getHeightTiles(0)->getWidth()-1)*getVertexSpacing();

            Real32 tstepx = 1.0f/getSizeX();
            Real32 tstepy = 1.0f/getSizeY();

            UInt32 i, j;

            const UInt32 roi = getSizeROI()+getSizeROI()+1;
            // mention: order of loops!

            for(j=0; j<roi; ++j) 
            {
                for(i=0; i<roi; ++i) 
                {
                    QuadTreeTerrainUnrecPtr terrain = QuadTreeTerrain::create();

                    terrain->setVertexSpacing(getVertexSpacing());
                    terrain->setHeightScale  (getHeightScale());
                    terrain->setGeoMorphing  (getGeoMorphing());
                    terrain->setDetail       (getDetail());
                    terrain->setBorderDetail (1);
                    terrain->setEyePointValid(true);
                    terrain->setUpdateTerrain(getUpdateTerrain());
                    terrain->setPerPixelLighting(getPerPixelLighting());

                    NodeUnrecPtr node = Node::create();
                    
//                    addRefX(node);

                    node->setCore(terrain);
                    // activate the roi*roi tiles for current point
                    // (getCurrentX()=getSizeROI(),getCurrentY()=getSizeROI())

                    if (i < getSizeX() && j < getSizeY()) 
                    {
                        terrain->setHeightData(getHeightTiles(j*getSizeX()+i));
                        terrain->setOriginX(i*step);
                        terrain->setOriginY(j*step);
                        node->setTravMask(TypeTraits<UInt32>::BitsSet);
                    } 
                    else 
                    {
                        node->setTravMask(0);
                    }

                    pParent->addChild(node);
                }
            }
        }
        setCurrentX(getSizeROI());
        setCurrentY(getSizeROI());
    }

    if(((whichField & MaterialFieldMask) || 
        (whichField & PerPixelLightingFieldMask))) 
    {
        if(getParents().size() > 0 && getParents()[0] != NullFC)
        { // parent must be set!
            Real32 tstepx = 1.0f/getSizeX();
            Real32 tstepy = 1.0f/getSizeY();
            UInt32 i, j;
            const UInt32 roi = getSizeROI()+getSizeROI()+1;
            for(j=0; j<roi; ++j) 
            {
                for(i=0; i<roi; ++i) 
                {
                    NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
                    
                    NodePtr node = pParent->getChild(j*roi+i);
                    
                    QuadTreeTerrainPtr terrain = 
                        dynamic_cast<QuadTreeTerrainPtr>(node->getCore());
                    
                    if (terrain == NullFC) 
                    {
                        continue;
                    }
                    
                    if(getMaterial() == NullFC) 
                    { // use material of MFHeightTextures
                        if(getHeightTextures().size() > j*getSizeX()+i && 
                           i < getSizeX() && j < getSizeY())
                        {	      
                            terrain->setMaterial(
                                getHeightTextures(j*getSizeX()+i));
                        }
                    } 
                    else 
                    { // use material of this MaterialGroup
                        MaterialUnrecPtr mat = cloneMaterial(getMaterial());
                        terrain->setMaterial(mat);
                        terrain->setOriginTexX(i*tstepx);
                        terrain->setOriginTexY(j*tstepy);
                        terrain->setTexSpacing (tstepx);
                        terrain->setTexYSpacing(tstepy);
                    }
                    
                    terrain->setPerPixelLighting(getPerPixelLighting());
                }
            }
        }
    }

    if((whichField & GeoMorphingFieldMask)) 
    {
        if(getParents().size() > 0 && getParents()[0] != NullFC)
        { // parent must be set!
            const UInt32 roi  = getSizeROI()+getSizeROI()+1;
            const UInt32 roi2 = roi*roi;
            
            for(UInt32 i=0; i<roi2; ++i) 
            {
                NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
                
                NodePtr node = pParent->getChild(i);
                
                QuadTreeTerrainPtr terrain = 
                    dynamic_cast<QuadTreeTerrainPtr>(node->getCore());
                
                if(terrain == NullFC) 
                {
                    continue;
                }
                
                terrain->setGeoMorphing(getGeoMorphing());
            }
        }
    }

    if((whichField & DetailFieldMask)) 
    {
        if(getParents().size() > 0 && getParents()[0] != NullFC)
        { // parent must be set!
            const UInt32 roi  = getSizeROI()+getSizeROI()+1;
            const UInt32 roi2 = roi*roi;

            for (UInt32 i=0; i<roi2; ++i) 
            {
                NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
                
                NodePtr    node = pParent->getChild(i);
                
                QuadTreeTerrainPtr terrain = 
                    dynamic_cast<QuadTreeTerrainPtr>(node->getCore());
                
                if(terrain == NullFC) 
                {
                    continue;
                }
                
                terrain->setDetail(getDetail());
            }
        }
    }
    Inherited::changed(whichField, origin, details);
}

inline void reorderChilds (const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num;

   for(Int32 i=0; i<num2; ++i) 
   {
       parent->addChild(order[i]);
   }
}
inline void subAllChilds (const NodePtr& parent, NodePtr order[], Int32 num)
{
   //Int32 num2 = num*num;
    while (parent->getNChildren() > 0) 
    {
        parent->subChild(0u);
    }
}

inline void caseChilds_n1n1(const NodePtr& parent, NodePtr order[], Int32 num)
{
   Int32 num2 = num*num-num;
   Int32 i, j, k;
   
   for (i=0, k=0; i<num; ++i, ++k) 
   {
       order[k] = parent->getChild(num2+i);
   }
   for(i=0; i<num-1; ++i) 
   {
       order[k] = parent->getChild(i*num+num-1);

       for(j=0, ++k; j<num-1; ++j, ++k) 
       {
           order[k] = parent->getChild(i*num+j);
       }
   }
   subAllChilds(parent, order, num);
}

inline void caseChilds_n10 (const NodePtr& parent, NodePtr order[], Int32 num)
{
    Int32 num2 = num*num-num;
    Int32 i, j, k;

    for(i=0, k=0; i<num; ++i) 
    {
        order[k] = parent->getChild(i*num+num-1);

        for(j=0, ++k; j<num-1; ++j, ++k) 
        {
            order[k] = parent->getChild(i*num+j);
        }
    }
    subAllChilds(parent, order, num);
}

inline void caseChilds_n1p1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
    Int32 num2 = num*num-num;
    Int32 i, j, k;

    for(i=1, k=0; i<num; ++i) 
    {
        order[k] = parent->getChild(i*num+num-1);

        for(j=0, ++k; j<num-1; ++j, ++k) 
        {
            order[k] = parent->getChild(i*num+j);
        }
    }

    for(i=0; i<num; ++i, ++k) 
    {
        order[k] = parent->getChild(i);
    }
    subAllChilds(parent, order, num);
}

inline void caseChilds_0n1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
    Int32 num2 = num*num-num;
    Int32 i, j, k;
    
    for(i=0, k=0; i<num; ++i, ++k) 
    {
        order[k] = parent->getChild(num2+i);
    }

    for(i=0; i<num-1; ++i) 
    {
        for(j=0; j<num; ++j, ++k) 
        {
            order[k] = parent->getChild(i*num+j);
        }
    }
    subAllChilds(parent, order, num);
}

inline void caseChilds_0p1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
    Int32 num2 = num*num-num;
    Int32 i, j, k;

    for(i=1, k=0; i<num; ++i) 
    {
        for(j=0; j<num; ++j, ++k) 
        {
            order[k] = parent->getChild(i*num+j);
        }
    }

    for(i=0; i<num; ++i, ++k) 
    {
        order[k] = parent->getChild(i);
    }

    subAllChilds(parent, order, num);
}

inline void caseChilds_p1n1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
    Int32 num2 = num*num-num;
    Int32 i, j, k;

    for(i=0, k=0; i<num; ++i, ++k) 
    {
        order[k] = parent->getChild(num2+i);
    }

    for(i=0; i<num-1; ++i, ++k) 
    {
        for(j=1; j<num; ++j, ++k) 
        {
            order[k] = parent->getChild(i*num+j);
        }
        order[k] = parent->getChild(i*num);
    }
    subAllChilds(parent, order, num);
}
inline void caseChilds_p10 (const NodePtr& parent, NodePtr order[], Int32 num)
{
    Int32 num2 = num*num-num;
    Int32 i, j, k;

    for(i=0, k=0; i<num; ++i, ++k) 
    {
        for(j=1; j<num; ++j, ++k) 
        {
            order[k] = parent->getChild(i*num+j);
        }
        order[k] = parent->getChild(i*num);
    }
   subAllChilds(parent, order, num);
}
inline void caseChilds_p1p1 (const NodePtr& parent, NodePtr order[], Int32 num)
{
    Int32 num2 = num*num-num;
    Int32 i, j, k;

    for(i=1, k=0; i<num; ++i, ++k) 
    {
        for(j=1; j<num; ++j, ++k) 
        {
            order[k] = parent->getChild(i*num+j);
        }
        order[k] = parent->getChild(i*num);
    }

    for(i=0; i<num; ++i, ++k) 
    {
        order[k] = parent->getChild(i);
    }
    subAllChilds(parent, order, num);
}

#ifdef OSG_OLD_RENDER_ACTION
Action::ResultE TiledQuadTreeTerrain::renderEnter (Action* action)
{  
   NodePtr            node;
   QuadTreeTerrainPtr core;

   RenderAction* da = dynamic_cast<RenderAction*>(action);

   if(da != NULL && getUpdate() && getSizeX() > 0 && getSizeY() > 0) 
   { // dynamic tesselation
       const FrustumVolume& frustum = da->getFrustum();

       Matrix camera  = da->getCameraToWorld();
       Matrix toworld = da->top_matrix();
       //action->getActNode()->getToWorld(toworld);
       toworld.invert();
       camera.multLeft(toworld);

      // choose tile
      Real32 step   = (getHeightTiles(0)->getWidth()-1)*getVertexSpacing();
      Real32 tstepx = 1.0f/getSizeX();
      Real32 tstepy = 1.0f/getSizeY();
      // tiling cs is [0, getSizeX()*getWidth()]*[0, getSizeY()*getWidth()]

      Pnt3f eyePoint(camera[3][0], camera[3][1], camera[3][2]);
      // set eye point for all terrain child nodes

      const Int32 roi  = getSizeROI()+getSizeROI()+1;
      const Int32 roi2 = roi*roi;
      
      for(UInt32 i=0; i<roi2; ++i) 
      {
          NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
          node = pParent->getChild(i);

          core = dynamic_cast<QuadTreeTerrainPtr>(node->getCore());

          core->setEyePoint(eyePoint);
          core->setUpdateTerrain(getUpdateTerrain());
      }

      // find tile (x, y) for current eye point
      Int32 x = Int32((eyePoint[0])/step);
      Int32 y = Int32((eyePoint[2])/step);

      x = osgMax(x, 0);
      x = osgMin(x, Int32(getSizeX()-1));
      y = osgMax(y, 0);
      y = osgMin(y, Int32(getSizeY()-1));

      // change tiling to tile (x, y)
      if(x != getCurrentX() || y != getCurrentY()) 
      {
          if(x < getCurrentX()-1) 
          {
              x = getCurrentX()-1;
          } 
          else if(x > getCurrentX()+1) 
          {
              x = getCurrentX()+1;
          }

          if(y < getCurrentY()-1) 
          {
              y = getCurrentY()-1;
          } 
          else if (y > getCurrentY()+1) 
          {
              y = getCurrentY()+1;
          }
          SNOTICE << "current (" 
                  << getCurrentX() << "," 
                  << getCurrentY() << ")->(" 
                  << x << "," 
                  << y << ")" 
                  << std::endl;
          
          Int32 i, j;

          NodePtr order[49];

          assert(roi*roi <= 49);

          switch (x - getCurrentX()) 
          {
              case -1:
                  switch (y - getCurrentY()) 
                  {
                      case -1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_n1n1(pParent, order, roi);
                          
                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[i+getSizeROI()];
                              if(y-getSizeROI() >= 0 && 
                                 x+i >= 0 && 
                                 x+i < getSizeX()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y-getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y-getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y-getSizeROI())*
                                                          tstepy);
                                  }
                                  
                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y-getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(i=-getSizeROI()+1; i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi];

                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     (x-getSizeROI())));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x-getSizeROI()));
                                  } 
                                  else
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);

                                      core->setOriginTexY((y+i)*tstepy);
                                  }
                                  
                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 0: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_n10(pParent, order, roi);

                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi];

                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     x-getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x-getSizeROI()));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }

                      case 1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_n1p1(pParent, order, roi);

                          for(i=-getSizeROI(); i<getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi];

                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     x-getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x-getSizeROI()));
                                  }
                                  else 
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              }
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(j=-getSizeROI(); j<=getSizeROI(); ++j) 
                          {
                              node = order[roi2-roi+j+getSizeROI()];

                              if(x+j >= 0 && 
                                 x+j < getSizeX() && 
                                 y+getSizeROI() < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y+getSizeROI())*
                                                     getSizeX() + 
                                                     x+j));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+
                                                             getSizeROI())*
                                                            getSizeX() + x+j));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+j)*tstepx);
                                      core->setOriginTexY((y+getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+j)*step);
                                  core->setOriginY((y+getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                  }
                  break;

              case 0:
                  switch (y - getCurrentY()) 
                  {
                      case -1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_0n1(pParent, order, roi);

                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[i+getSizeROI()];

                              if (x+i >= 0 && 
                                  x+i < getSizeX() && 
                                  y-getSizeROI() >= 0) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y-getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y-getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y-getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y-getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_0p1(pParent, order, roi);
                          
                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[roi2-roi+(i+getSizeROI())];
                              if(x+i >= 0 && 
                                 x+i < getSizeX() && 
                                 y+getSizeROI() < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y+getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y+getSizeROI())*
                                                          tstepy);
                                  }
                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y+getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                  }
                  break;
              case +1:
                  switch (y - getCurrentY()) 
                  {
                      case -1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_p1n1(pParent, order, roi);
                          
                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[i+getSizeROI()];

                              if(x+i >= 0 && 
                                 x+i < getSizeX() && 
                                 y-getSizeROI() >= 0) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y-getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y-getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y-getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y-getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(i=-getSizeROI()+1; i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi+(roi-1)];
                              
                              if(x+getSizeROI() < getSizeX() && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*getSizeX() + 
                                                     (x+getSizeROI())));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x+getSizeROI()));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x+getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 0: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_p10(pParent, order, roi);

                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi+roi-1];
                              
                              if(x+getSizeROI() < getSizeX() && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     x+getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x+getSizeROI()));
                                  } 
                                  else
                                  {
                                      core->setOriginTexX((x+getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x+getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_p1p1(pParent, order, roi);

                          for(i=-getSizeROI(); i<getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi+roi-1];
                              
                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*getSizeX() + 
                                                     x-getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() +
                                                            x-getSizeROI()));
                                  } 
                                  else
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                                  
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(j=-getSizeROI(); j<=getSizeROI(); ++j) 
                          {
                              node = order[roi2-roi+(j+getSizeROI())];
                              
                              if(y+getSizeROI() < getSizeY() && 
                                 x+j >= 0 && 
                                 x+j < getSizeX()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+getSizeROI())*
                                                     getSizeX() + x+j));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+getSizeROI())*
                                                            getSizeX() + x+j));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+j)*tstepx);
                                      core->setOriginTexY((y+getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+j)*step);
                                  core->setOriginY((y+getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);

                          break;
                      }
                  }
                  break;
          }


          setCurrentX(x); 
          setCurrentY(y); 
          
#ifdef OSG_DEBUG
          UInt32 dup;
          for (UInt32 i=0; i<roi2; ++i) 
          {
              NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
              node = pParent->getChild(i);

              core = dynamic_cast<QuadTreeTerrainPtr>(node->getCore());

              if(node->getTravMask()) 
              {
                  std::cout << "tile " << i << "(" 
                            << core->getOriginX() << "," 
                            << core->getOriginY() << "):";
                  dup = 0;

                  for(UInt32 j=0; j<roi2; ++j) 
                  {
                      NodePtr            pParent2 = 
                          dynamic_cast<NodePtr>(getParents()[0]);
                      NodePtr            node2 = pParent2->getChild(j);
                      QuadTreeTerrainPtr core2 = 
                          dynamic_cast<QuadTreeTerrainPtr>(node2->getCore());

                      if (node2->getTravMask() && 
                          core->getOriginX() == core2->getOriginX() && 
                          core->getOriginY() == core2->getOriginY()) 
                      {
                          std::cout << " " << j; 
                          ++dup;
                      }
                  }

                  std::cout << std::endl;
                  
                  if(dup > 1) 
                  {
                      SFATAL << "tile has " << dup-1 
                             << " duplicates!" << std::endl;
                  }
              }
          }
#endif
      }
   }
   
   UInt32 numIndis = 0;
   UInt32 numFans = 0;
   NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
              
   for(UInt32 i=0; i<pParent->getNChildren(); ++i) 
   {
       node = pParent->getChild(i);
       
       if (node != NullFC) 
       {
           core = dynamic_cast<QuadTreeTerrainPtr>(node->getCore());

           if(core != NullFC && core->getIndices() != NullFC) 
           {
               numIndis += core->getIndices()->size();
               numFans  += core->getTypes()->size();
           }
       }
   }
   SNOTICE << numIndis/3 << " triangles in " 
           << numFans << " fans" << std::endl; 

   return Action::Continue;
}
#endif

Action::ResultE TiledQuadTreeTerrain::renderEnter (Action* action)
{
    RenderAction* da = 
        dynamic_cast<RenderAction*>(action);

    Action::ResultE returnValue =
        this->doRenderEnter(da->getFrustum(),
                            da->getActivePartition()->getCameraToWorld(),
                            da->getActivePartition()->topMatrix());
    
    
    return returnValue;
}

Action::ResultE TiledQuadTreeTerrain::doRenderEnter(
    const FrustumVolume &frustum,
    Matrix         camera,
    Matrix         toworld)
{  
   NodePtr            node;
   QuadTreeTerrainPtr core;

//   RenderAction* da = dynamic_cast<RenderAction*>(action);

   if(getUpdate() && getSizeX() > 0 && getSizeY() > 0) 
   { // dynamic tesselation
//       const FrustumVolume& frustum = da->getFrustum();

//       Matrix camera  = da->getCameraToWorld();
//       Matrix toworld = da->top_matrix();
       //action->getActNode()->getToWorld(toworld);
       toworld.invert();
       camera.multLeft(toworld);

      // choose tile
      Real32 step   = (getHeightTiles(0)->getWidth()-1)*getVertexSpacing();
      Real32 tstepx = 1.0f/getSizeX();
      Real32 tstepy = 1.0f/getSizeY();
      // tiling cs is [0, getSizeX()*getWidth()]*[0, getSizeY()*getWidth()]

      Pnt3f eyePoint(camera[3][0], camera[3][1], camera[3][2]);
      // set eye point for all terrain child nodes

      const Int32 roi  = getSizeROI()+getSizeROI()+1;
      const Int32 roi2 = roi*roi;
      
      for(UInt32 i=0; i<roi2; ++i) 
      {
          NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
          node = pParent->getChild(i);

          core = dynamic_cast<QuadTreeTerrainPtr>(node->getCore());

          core->setEyePoint(eyePoint);
          core->setUpdateTerrain(getUpdateTerrain());
      }

      // find tile (x, y) for current eye point
      Int32 x = Int32((eyePoint[0])/step);
      Int32 y = Int32((eyePoint[2])/step);

      x = osgMax(x, 0);
      x = osgMin(x, Int32(getSizeX()-1));
      y = osgMax(y, 0);
      y = osgMin(y, Int32(getSizeY()-1));

      // change tiling to tile (x, y)
      if(x != getCurrentX() || y != getCurrentY()) 
      {
          if(x < getCurrentX()-1) 
          {
              x = getCurrentX()-1;
          } 
          else if(x > getCurrentX()+1) 
          {
              x = getCurrentX()+1;
          }

          if(y < getCurrentY()-1) 
          {
              y = getCurrentY()-1;
          } 
          else if (y > getCurrentY()+1) 
          {
              y = getCurrentY()+1;
          }
          SNOTICE << "current (" 
                  << getCurrentX() << "," 
                  << getCurrentY() << ")->(" 
                  << x << "," 
                  << y << ")" 
                  << std::endl;
          
          Int32 i, j;

          NodePtr order[49];

          assert(roi*roi <= 49);

          switch (x - getCurrentX()) 
          {
              case -1:
                  switch (y - getCurrentY()) 
                  {
                      case -1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_n1n1(pParent, order, roi);
                          
                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[i+getSizeROI()];
                              if(y-getSizeROI() >= 0 && 
                                 x+i >= 0 && 
                                 x+i < getSizeX()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y-getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y-getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y-getSizeROI())*
                                                          tstepy);
                                  }
                                  
                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y-getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(i=-getSizeROI()+1; i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi];

                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     (x-getSizeROI())));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x-getSizeROI()));
                                  } 
                                  else
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);

                                      core->setOriginTexY((y+i)*tstepy);
                                  }
                                  
                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 0: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_n10(pParent, order, roi);

                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi];

                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     x-getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x-getSizeROI()));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }

                      case 1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_n1p1(pParent, order, roi);

                          for(i=-getSizeROI(); i<getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi];

                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     x-getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x-getSizeROI()));
                                  }
                                  else 
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              }
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(j=-getSizeROI(); j<=getSizeROI(); ++j) 
                          {
                              node = order[roi2-roi+j+getSizeROI()];

                              if(x+j >= 0 && 
                                 x+j < getSizeX() && 
                                 y+getSizeROI() < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y+getSizeROI())*
                                                     getSizeX() + 
                                                     x+j));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+
                                                             getSizeROI())*
                                                            getSizeX() + x+j));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+j)*tstepx);
                                      core->setOriginTexY((y+getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+j)*step);
                                  core->setOriginY((y+getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                  }
                  break;

              case 0:
                  switch (y - getCurrentY()) 
                  {
                      case -1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_0n1(pParent, order, roi);

                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[i+getSizeROI()];

                              if (x+i >= 0 && 
                                  x+i < getSizeX() && 
                                  y-getSizeROI() >= 0) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y-getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y-getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y-getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y-getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_0p1(pParent, order, roi);
                          
                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[roi2-roi+(i+getSizeROI())];
                              if(x+i >= 0 && 
                                 x+i < getSizeX() && 
                                 y+getSizeROI() < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());

                                  core->setHeightData(
                                      getHeightTiles((y+getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y+getSizeROI())*
                                                          tstepy);
                                  }
                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y+getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                  }
                  break;
              case +1:
                  switch (y - getCurrentY()) 
                  {
                      case -1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_p1n1(pParent, order, roi);
                          
                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[i+getSizeROI()];

                              if(x+i >= 0 && 
                                 x+i < getSizeX() && 
                                 y-getSizeROI() >= 0) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y-getSizeROI())*
                                                     getSizeX() + x+i));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y-getSizeROI())*
                                                            getSizeX() + x+i));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+i)*tstepx);
                                      core->setOriginTexY((y-getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+i)*step);
                                  core->setOriginY((y-getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(i=-getSizeROI()+1; i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi+(roi-1)];
                              
                              if(x+getSizeROI() < getSizeX() && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*getSizeX() + 
                                                     (x+getSizeROI())));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x+getSizeROI()));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x+getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 0: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_p10(pParent, order, roi);

                          for(i=-getSizeROI(); i<=getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi+roi-1];
                              
                              if(x+getSizeROI() < getSizeX() && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*
                                                     getSizeX() + 
                                                     x+getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() + 
                                                            x+getSizeROI()));
                                  } 
                                  else
                                  {
                                      core->setOriginTexX((x+getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x+getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);
                          break;
                      }
                      case 1: 
                      {
                          NodePtr pParent = 
                              dynamic_cast<NodePtr>(getParents()[0]);

                          caseChilds_p1p1(pParent, order, roi);

                          for(i=-getSizeROI(); i<getSizeROI(); ++i) 
                          {
                              node = order[(i+getSizeROI())*roi+roi-1];
                              
                              if(x-getSizeROI() >= 0 && 
                                 y+i >= 0 && 
                                 y+i < getSizeY()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+i)*getSizeX() + 
                                                     x-getSizeROI()));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+i)*
                                                            getSizeX() +
                                                            x-getSizeROI()));
                                  } 
                                  else
                                  {
                                      core->setOriginTexX((x-getSizeROI())*
                                                          tstepx);
                                      core->setOriginTexY((y+i)*tstepy);
                                  }

                                  core->setOriginX((x-getSizeROI())*step);
                                  core->setOriginY((y+i)*step);
                                  
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }

                          for(j=-getSizeROI(); j<=getSizeROI(); ++j) 
                          {
                              node = order[roi2-roi+(j+getSizeROI())];
                              
                              if(y+getSizeROI() < getSizeY() && 
                                 x+j >= 0 && 
                                 x+j < getSizeX()) 
                              {
                                  node->setTravMask(
                                      TypeTraits<UInt32>::BitsSet);
                                  core = 
                                      dynamic_cast<QuadTreeTerrainPtr>(
                                          node->getCore());
                                  
                                  core->setHeightData(
                                      getHeightTiles((y+getSizeROI())*
                                                     getSizeX() + x+j));

                                  if(getMaterial() == NullFC) 
                                  {
                                      core->setMaterial(
                                          getHeightTextures((y+getSizeROI())*
                                                            getSizeX() + x+j));
                                  } 
                                  else 
                                  {
                                      core->setOriginTexX((x+j)*tstepx);
                                      core->setOriginTexY((y+getSizeROI())*
                                                          tstepy);
                                  }

                                  core->setOriginX((x+j)*step);
                                  core->setOriginY((y+getSizeROI())*step);
                              } 
                              else 
                              {
                                  node->setTravMask(0);
                              }
                          }
                          reorderChilds(pParent, order, roi);

                          break;
                      }
                  }
                  break;
          }


          setCurrentX(x); 
          setCurrentY(y); 
          
#ifdef OSG_DEBUG
          UInt32 dup;
          for (UInt32 i=0; i<roi2; ++i) 
          {
              NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
              node = pParent->getChild(i);

              core = dynamic_cast<QuadTreeTerrainPtr>(node->getCore());

              if(node->getTravMask()) 
              {
                  std::cout << "tile " << i << "(" 
                            << core->getOriginX() << "," 
                            << core->getOriginY() << "):";
                  dup = 0;

                  for(UInt32 j=0; j<roi2; ++j) 
                  {
                      NodePtr            pParent2 = 
                          dynamic_cast<NodePtr>(getParents()[0]);
                      NodePtr            node2 = pParent2->getChild(j);
                      QuadTreeTerrainPtr core2 = 
                          dynamic_cast<QuadTreeTerrainPtr>(node2->getCore());

                      if (node2->getTravMask() && 
                          core->getOriginX() == core2->getOriginX() && 
                          core->getOriginY() == core2->getOriginY()) 
                      {
                          std::cout << " " << j; 
                          ++dup;
                      }
                  }

                  std::cout << std::endl;
                  
                  if(dup > 1) 
                  {
                      SFATAL << "tile has " << dup-1 
                             << " duplicates!" << std::endl;
                  }
              }
          }
#endif
      }
   }
   
   UInt32 numIndis = 0;
   UInt32 numFans = 0;
   NodePtr pParent = dynamic_cast<NodePtr>(getParents()[0]);
              
   for(UInt32 i=0; i<pParent->getNChildren(); ++i) 
   {
       node = pParent->getChild(i);
       
       if (node != NullFC) 
       {
           core = dynamic_cast<QuadTreeTerrainPtr>(node->getCore());

           if(core != NullFC && core->getIndices() != NullFC) 
           {
               numIndis += core->getIndices()->size();
               numFans  += core->getTypes()->size();
           }
       }
   }
   SNOTICE << numIndis/3 << " triangles in " 
           << numFans << " fans" << std::endl; 

   return Action::Continue;
}

void TiledQuadTreeTerrain::dump(      UInt32    , 
                                      const BitVector ) const
{
    SLOG << "Dump TiledTerrain NI" << std::endl;
}

