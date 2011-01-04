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
 * 2002/10/16: added transparency path. Thanks to Franck Sourdin             *
 *            (sourdin@ai.cluny.ensam.fr) for it!                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//-------------------------------
//  Includes
//-------------------------------

#include <cstdio>
#include <climits>

#include "OSGConfig.h"

#include "OSGGL.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "OSGLog.h"

#include "OSGNode.h"
#include "OSGGeometry.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGGeoFunctions.h"
#include "OSGSimpleTexturedMaterial.h"
#include "OSGImageFileHandler.h"
#include "OSGPathHandler.h"
#include "OSGGroup.h"
#include "OSGSceneFileHandler.h"
#include "OSGTriangleIterator.h"

#include "OSGOBJSceneFileType.h"

OSG_USING_NAMESPACE


/*! \class OSG::OBJSceneFileType
    \ingroup GrpSystemFileIO

 */

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:
const Char8 *OBJSceneFileType::_suffixA[] =  { "obj" };

OBJSceneFileType  OBJSceneFileType::_the(_suffixA,
                                          sizeof(_suffixA),
                                         false,
                                         10,
                                         (SceneFileType::OSG_READ_SUPPORTED |
                                          SceneFileType::OSG_WRITE_SUPPORTED));

/*****************************
 *    Classvariables
 *****************************/


/********************************
 *    Class methodes
 *******************************/


/*******************************
*public
*******************************/

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: Scene &image, const char *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: read the image from the given file
//SeeAlso:
//s:
//
//------------------------------
NodeTransitPtr OBJSceneFileType::read(      std::istream &is, 
                                      const Char8        *,
                                            Resolver        ) const
{
    NodeUnrecPtr rootPtr, nodePtr;
    std::string elem;
    std::map<std::string, DataElem>::const_iterator elemI;
    Vec3f vec3r;
    Pnt3f pnt3r;
    Vec2f vec2r;
    Real32 x,y,z;
    GeoPnt3fPropertyUnrecPtr coordPtr    = GeoPnt3fProperty::create();
    GeoVec2fPropertyUnrecPtr texCoordPtr = GeoVec2fProperty::create();
    GeoVec3fPropertyUnrecPtr normalPtr   = GeoVec3fProperty::create();
    GeometryUnrecPtr geoPtr;
    GeoIntegralPropertyUnrecPtr posIndexPtr, texIndexPtr, normalIndexPtr;
    GeoIntegralPropertyUnrecPtr lensPtr;
    GeoIntegralPropertyUnrecPtr typePtr;
    DataElem dataElem;
    Char8 strBuf[8192], *token, *nextToken;
    Int32 strBufSize = sizeof(strBuf)/sizeof(Char8);
    Int32 index, posIndex = 0, indexType;
    Int32 i,j,n,primCount[3];
    std::list<Mesh> meshList;
    std::map<std::string, SimpleTexturedMaterialUnrecPtr> mtlMap;
    std::map<std::string, SimpleTexturedMaterialUnrecPtr>::iterator mtlI;
    Mesh emptyMesh;
    Face emptyFace;
    TiePoint  emptyTie;
    Int32 indexMask, meshIndexMask;
    std::list<Face>::iterator faceI;
    std::list<Mesh>::iterator meshI;
    bool isSingleIndex;

    // create the first mesh entry
    meshList.push_back(emptyMesh);
    meshI = meshList.begin();

    if(is)
    {
        primCount[0] = 0;
        primCount[1] = 0;
        primCount[2] = 0;

        for(is >> elem; is.eof() == false; is >> elem)
        {
            if(elem[0] == '#' || elem[0] == '$')
            {
                is.ignore(INT_MAX, '\n');
            }
            else
            {
				SceneFileHandler::the()->updateReadProgress();

                elemI = _dataElemMap.find(elem);
                dataElem = ((elemI == _dataElemMap.end()) ?
                        UNKNOWN_DE : elemI->second );
                switch (dataElem)
                {
                    case OBJECT_DE:
                    case GROUP_DE:
                    case SMOOTHING_GROUP_DE:
                        is.ignore(INT_MAX, '\n');
                    break;
                    case VERTEX_DE:
                        primCount[0]++;
                        is >> x >> y >> z;
                        pnt3r.setValues(x,y,z);
                        coordPtr->addValue(pnt3r);
                    break;
                    case VERTEX_TEXTURECOORD_DE:
                        primCount[1]++;
                        is >> x >> y;
                        vec2r.setValues(x,y);
                        texCoordPtr->addValue(vec2r);
                    break;
                    case VERTEX_NORMAL_DE:
                        primCount[2]++;
                        is >> x >> y >> z;
                        vec3r.setValues(x,y,z);
                        normalPtr->addValue(vec3r);
                    break;
                    case LIB_MTL_DE:
                        is >> elem;
                        readMTL ( elem.c_str(), mtlMap );
                        is.ignore(INT_MAX, '\n');
                    break;
                    case USE_MTL_DE:
                        is >> elem;
                        if (meshI->faceList.empty() == false)
                        {
                            meshList.push_front(emptyMesh);
                            meshI = meshList.begin();
                        }
                        mtlI = mtlMap.find(elem);
                        if (mtlI == mtlMap.end())
                        {
                            FFATAL (("Unkown mtl %s\n", elem.c_str()));
                        }
                        else
                        {
                            meshI->mtlPtr = mtlI->second;
                        }
                    break;
                    case FACE_DE:
                        meshI->faceList.push_front(emptyFace);
                        faceI = meshI->faceList.begin();
                        is.get(strBuf,strBufSize);
                        token = strBuf;
                        indexType = 0;
                        while(token && *token)
                        {
                            for (; *token == '/'; token++)
                                indexType++;
                            for (; isspace(*token); token++)
                                indexType = 0;
                            index = strtol(token, &nextToken, 10);
                            if (token == nextToken)
                                break;
                            if (indexType == 0)
                                faceI->tieVec.push_back(emptyTie);
                            if (index >= 0)
                                index--;
                            else
                                index =  primCount[indexType] + index;
                            faceI->tieVec.back().index[indexType] = index;
                            token = nextToken;
                        }
                    break;
                    case UNKNOWN_DE:
                    default:
                        FWARNING (( "Unkown obj data elem: %s\n", elem.c_str()));
                        is.ignore(INT_MAX, '\n');
                    break;
                }
            }
        }

#if 0
        std::cerr << "------------------------------------------------" << std::endl;
        i = 0;
        for (meshI = meshList.begin(); meshI != meshList.end(); meshI++)
        {
            std::cerr << "Mesh " << i << " faceCount :"
                      << meshI->faceList.size() << std::endl;
            j = 0 ;
            for ( faceI = meshI->faceList.begin(); faceI != meshI->faceList.end();
                  faceI++)
            std::cerr << "MESH " <<  i << "face: " << j++ << "tie num: "
                      << faceI->tieVec.size() << std::endl;
            i++;
        }
        std::cerr << "------------------------------------------------" << std::endl;
#endif

        // create Geometry objects
        for (meshI = meshList.begin(); meshI != meshList.end(); meshI++)
        {
            geoPtr   = Geometry::create();
            posIndexPtr = NULL;
            texIndexPtr = NULL;
            normalIndexPtr = NULL;
            lensPtr  = GeoUInt32Property::create();
            typePtr  = GeoUInt8Property ::create();

            // create and check mesh index mask
            meshIndexMask = 0;
            isSingleIndex = true;
            if ( meshI->faceList.empty() == false)
            {
                for ( faceI = meshI->faceList.begin();
                  faceI != meshI->faceList.end(); faceI++)
                {
                    indexMask = 0;
                    n = faceI->tieVec.size();
                    for (i = 0; i < n; i++)
                    {
                        for (j = 0; j < 3; j++)
                        {
                            if ((index = (faceI->tieVec[i].index[j])) >= 0)
                            {
                                indexMask |= (1 << j);
                                if (j)
                                    isSingleIndex &= (posIndex == index);
                                else
                                    posIndex = index;
                            }
                        }
                    }
                    if (meshIndexMask == 0)
                    {
                        meshIndexMask = indexMask;
                    }
                    else if (meshIndexMask != indexMask)
                    {
                        // consider this real-world example:
                       // [...]
                       // f 1603//1747 1679//1744 1678//1743
                       // s 1
                       // f 9/1/10 5/2/9 1680/3/1748 1681/4/174
                       // [...]
                       // Some faces contain texture coords and others do not.
                       // The old version did just skip this geometry.
                       // This version should continue if there's at least
                       // the vertex index
                       // I've seen the change in the maskIndex only after a smooth group,
                       // so it's perhaps smarter to not ignore the smooth group further up in this code
                       if( !(indexMask & 1) )  
                       {
                         // if there are vertex indices there's no reason to get in here
                          FFATAL (( "IndexMask unmatch, can not create geo\n"));
                          meshIndexMask = 0;
                          break;
                       }
                       else
                       {
                         // consider the minimum similarities of mesh masks
                         meshIndexMask &= indexMask;
                       }
                    }
                }
            }
            else
            {
                FWARNING (("Mesh with empty faceList\n"));
            }

            // fill the geo properties
            if (meshIndexMask)
            {
                geoPtr->setPositions ( coordPtr );
                posIndexPtr = GeoUInt32Property::create();
                if(!isSingleIndex)
                    geoPtr->setIndex(posIndexPtr, Geometry::PositionsIndex);
                geoPtr->setLengths   ( lensPtr );
                geoPtr->setTypes     ( typePtr );

                if ( (meshIndexMask & 2) && texCoordPtr->size() > 0 )
                {
                    geoPtr->setTexCoords ( texCoordPtr );
                    texIndexPtr = GeoUInt32Property::create();
                    if(!isSingleIndex)
                        geoPtr->setIndex(texIndexPtr, Geometry::TexCoordsIndex);
                }
                else
                {
                    geoPtr->setTexCoords ( NULL );
                }

                if ( (meshIndexMask & 4) && normalPtr->size() > 0 )
                {
                    geoPtr->setNormals   ( normalPtr );
                    normalIndexPtr = GeoUInt32Property::create();
                    if(!isSingleIndex)
                        geoPtr->setIndex(normalIndexPtr, Geometry::NormalsIndex);
                }
                else
                {
                    geoPtr->setNormals   ( NULL );
                }

                if (meshI->mtlPtr == NULL)
                {
                    meshI->mtlPtr = SimpleTexturedMaterial::create();
                    meshI->mtlPtr->setDiffuse( Color3f( .8f, .8f, .8f ) );
                    meshI->mtlPtr->setSpecular( Color3f( 1.f, 1.f, 1.f ) );
                    meshI->mtlPtr->setShininess( 20.f );
                }
                geoPtr->setMaterial  ( meshI->mtlPtr );

                for ( faceI = meshI->faceList.begin();
                      faceI != meshI->faceList.end(); faceI++)
                {
                    n = faceI->tieVec.size();
    
                    // add the lens entry
                    lensPtr->push_back(n);
    
                    // add the type entry
                    typePtr->push_back(GL_POLYGON);
    
                    // create the index values
                    for (i = 0; i < n; i++)
                    {
                        if (isSingleIndex)
                        {
                            posIndexPtr->push_back(faceI->tieVec[i].index[0]);
                        }
                        else
                        {
                            posIndexPtr->push_back(faceI->tieVec[i].index[0]);
                            if(texIndexPtr != NULL)
                                texIndexPtr->push_back(faceI->tieVec[i].index[1]);
                            if(normalIndexPtr != NULL)
                                normalIndexPtr->push_back(faceI->tieVec[i].index[2]);
                        }
                    }
                }
    
                if(isSingleIndex)
				{
                    geoPtr->setIndex(posIndexPtr, Geometry::PositionsIndex);
                    geoPtr->setIndex(posIndexPtr, Geometry::NormalsIndex  );
                    geoPtr->setIndex(posIndexPtr, Geometry::TexCoordsIndex);
				}

                // need to port the geometry functions ...
                createSharedIndex( geoPtr );
    
                // check if we have normals
                // need to port the geometry functions ...

				if(geoPtr->getNormals() == NULL)
                    calcVertexNormals(geoPtr);

                // create and link the node
                nodePtr = Node::create();
                nodePtr->setCore( geoPtr );
    
                if (meshList.size() > 1)
                {
                    if (rootPtr == NULL)
                    {
                        rootPtr = Node::create();

                        GroupUnrecPtr tmpPtr = Group::create();

                        rootPtr->setCore ( tmpPtr );
                        rootPtr->addChild(nodePtr);
                    }
                    else
                    {
                        rootPtr->addChild(nodePtr);
                    }
                }
                else
                {
                    rootPtr = nodePtr;
                }
            }
        }
    }

    SceneFileHandler::the()->updateReadProgress(100);

    commitChanges();

    return NodeTransitPtr(rootPtr);
}

void OBJSceneFileType::write(Node * const  node,
                             std::ostream &os,
                             UInt32 &pIndex,
                             UInt32 &nIndex,
                             UInt32 &tIndex) const
{
	UInt32 i,pCount=0,nCount=0,tCount=0;
    Geometry *g = dynamic_cast<Geometry *>(node->getCore());
    if(g != NULL)
    {
        // HACK separate it in several geometry nodes.
        os << "g Geometry" << std::endl;
        os << "usemtl Geometry" << std::endl;
        Matrix mat = node->getToWorld();
        // write vertices
        if(g->getPositions())
        {
            pCount = g->getPositions()->getSize();
            for(i=0 ; i< pCount ; ++i)
            {
                Pnt3f v;
                g->getPositions()->getValue(v, i);
                mat.mult(v, v);
                os << "v " << v[0] << " " << v[1] << " " << v[2] << std::endl;
            }
        }
        // write normals
        if(g->getNormals())
        {
            nCount = g->getNormals()->getSize();
            for(i=0 ; i< nCount ; ++i)
            {
                Vec3f v;
                g->getNormals()->getValue(v, i);
                mat.mult(v, v);
                os << "vn " << v[0] << " " << v[1] << " " << v[2] << std::endl;
            }
        }
        // texture coords
        if(g->getTexCoords())
        {
            tCount = g->getTexCoords()->getSize();
            for(i=0 ; i< tCount ; ++i)
            {
                Vec2f v;
                g->getTexCoords()->getValue(v, i);
                os << "vt " << v[0] << " " << v[1] << std::endl;
            }
        }
        // write indices
        TriangleIterator f;
        for(f=g->beginTriangles() ; f!=g->endTriangles() ; ++f)
        {
            os << "f";
            for(i=0 ; i<3 ; ++i)
            {
                os << " " << f.getPositionIndex(i) + pIndex;
                if(nCount || tCount)
                {
                    os << "/";
                    if(tCount)
                        os << f.getTexCoordsIndex(i) + tIndex;
                    if(nCount)
                        os << "/" << f.getNormalIndex(i) + nIndex;
                }
            }
            os << std::endl;
        }
        pIndex += pCount;
        tIndex += tCount;
        nIndex += nCount;
    }
    for(MFUnrecChildNodePtr::const_iterator nI =node->getMFChildren()->begin();
                                            nI!=node->getMFChildren()->end();
                                          ++nI)
    {
        write((*nI),os,pIndex,nIndex,tIndex);
    }
}

bool OBJSceneFileType::write(Node * const node, std::ostream &os,
                             const Char8 *fileNameOrExtension) const
{
    UInt32 pIndex=1;
    UInt32 tIndex=1;
    UInt32 nIndex=1;
    
    write(node,os,pIndex,tIndex,nIndex);

    return true;
}

/******************************
*protected
******************************/


/******************************
*private
******************************/


/***************************
*instance methodes
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: OBJSceneFileType
//----------------------------
//
//Parameters:
//p: const char *suffixArray[], UInit16 suffixByteCount
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------

OBJSceneFileType::OBJSceneFileType(const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority,
                                         UInt32  flags) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority,
                  flags),
    _dataElemMap()

{
    initElemMap();
}

//----------------------------
// Function name: OBJSceneFileType
//----------------------------
//
//Parameters:
//p: const OBJSceneFileType &obj
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//------------------------------

OBJSceneFileType::OBJSceneFileType(const OBJSceneFileType &obj) :
    SceneFileType(obj)
{
    initElemMap();
}

//----------------------------
// Function name: ~OBJSceneFileType
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//------------------------------

OBJSceneFileType &OBJSceneFileType::the(void)
{
    return _the;
}

OBJSceneFileType::~OBJSceneFileType(void)
{
    return;
}

const Char8 *OBJSceneFileType::getName(void) const
{
    return "Wavefront Geometry";
}


/*------------access----------------*/

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/



/****************************
 *protected
 ****************************/


/****************************
 *private
 ****************************/


void OBJSceneFileType::initElemMap(void)
{
    if (_dataElemMap.empty())
    {
        _dataElemMap[""]        = UNKNOWN_DE;
        
        _dataElemMap["v"]       = VERTEX_DE;
        _dataElemMap["vt"]      = VERTEX_TEXTURECOORD_DE;
        _dataElemMap["vn"]      = VERTEX_NORMAL_DE;
        _dataElemMap["f"]       = FACE_DE;
        _dataElemMap["fo"]      = FACE_DE;
        _dataElemMap["mtllib"]  = LIB_MTL_DE;
        _dataElemMap["usemtl"]  = USE_MTL_DE;
        _dataElemMap["g"]       = GROUP_DE;
        _dataElemMap["s"]       = SMOOTHING_GROUP_DE;
        _dataElemMap["o"]       = OBJECT_DE;
    }

    if (_mtlElemMap.empty())
    {
        _mtlElemMap[""]        = UNKNOWN_ME;
        
        _mtlElemMap["newmtl"]  = NEW_MTL_ME;
        _mtlElemMap["Kd"]      = MTL_DIFFUSE_ME;
        _mtlElemMap["Ka"]      = MTL_AMBIENT_ME;
        _mtlElemMap["Ks"]      = MTL_SPECULAR_ME;
        _mtlElemMap["Ns"]      = MTL_SHININESS_ME;
        _mtlElemMap["Tr"]      = MTL_TRANSPARENCY_ME;
        _mtlElemMap["d"]       = MTL_DISSOLVE_ME;
        _mtlElemMap["map_Kd"]  = MTL_MAP_KD_ME;
        _mtlElemMap["map_Ka"]  = MTL_MAP_KA_ME;
        _mtlElemMap["map_Ks"]  = MTL_MAP_KS_ME;
        _mtlElemMap["illum"]   = MTL_ILLUM_ME;
        _mtlElemMap["refl"]    = MTL_REFL_ME;
    }
}

Int32 OBJSceneFileType::readMTL ( const Char8 *fileName,
                                  std::map<std::string, 
                                  SimpleTexturedMaterialUnrecPtr> & mtlMap )
  const
{
    if(fileName == NULL || strlen(fileName) == 0)
        return 0;

    Int32 mtlCount = 0;

	PathHandler *pathHandler = SceneFileHandler::the()->getPathHandler();
	std::string fullFilePath;

	if(pathHandler != NULL)
        fullFilePath = pathHandler->findFile(fileName);
    else
        fullFilePath = fileName;

    if(fullFilePath.empty())
    {
        FWARNING (("Couldn't open '%s'!\n", fileName));
        return 0;
    }

    std::ifstream in(fullFilePath.c_str());
    SimpleTexturedMaterialUnrecPtr mtlPtr = NULL;
    Real32 a,b,c;
    std::string elem;
    std::map<std::string, MaterialElem>::const_iterator elemI;
    MaterialElem mtlElem;
    std::map<std::string, OSG::ImageUnrecPtr> imageMap;
    std::map<std::string, OSG::ImageUnrecPtr>::iterator iI;
    ImageUnrecPtr image = NULL;
    bool constDiffuse = false, constAmbient = false, constSpecular = false;

    if (in)
    {
        for (in >> elem; in.eof() == false; in >> elem)
        {
            if (elem[0] == '#' || elem[0] == '$' )
            {
                in.ignore(INT_MAX, '\n');
            }
            else
            {
                elemI = _mtlElemMap.find(elem);
                mtlElem = ((elemI == _mtlElemMap.end()) ?
                     UNKNOWN_ME : elemI->second);
                if (mtlElem == NEW_MTL_ME)
                {
                    in >> elem;
                    mtlPtr = SimpleTexturedMaterial::create();
                    mtlPtr->setColorMaterial(GL_NONE);
                    mtlPtr->setEnvMode(GL_MODULATE);
                    mtlMap[elem] = mtlPtr;
                    mtlCount++;
                    constDiffuse  = false;
                    constAmbient  = false;
                    constSpecular = false;
                }
                else
                {
                    if (mtlPtr == NULL)
                    {
                        FFATAL (( "Invalid Mtl token: %s, newmtl expected in %s\n",
                                elem.c_str(), fileName ));
                        in.ignore(INT_MAX, '\n');
                    }
                    else
                    {
                        switch (mtlElem)
                        {
                            case MTL_DIFFUSE_ME:
                                in >> a >> b >> c;
                                if (!constDiffuse)
                                    mtlPtr->setDiffuse( Color3f( a,b,c ));
                            break;
                            case MTL_AMBIENT_ME:
                                in >> a >> b >> c;
                                if (!constAmbient)
                                    mtlPtr->setAmbient( Color3f( a,b,c ));
                            break;
                            case MTL_SPECULAR_ME:
                                in >> a >> b >> c;
                                if (!constSpecular)
                                    mtlPtr->setSpecular( Color3f( a,b,c ));
                            break;
                            case MTL_SHININESS_ME:
                                in >> a;
                                mtlPtr->setShininess(a);
                            break;
                            case MTL_ILLUM_ME:
                                ; // TODO: What to do with illum ?!?
                                in >> elem;
                                // FFATAL (("obj mtl illum not handled yet\n"));
                            break;
                            case MTL_REFL_ME:
                                mtlPtr->setEnvMap(true);
                            break;
                            case MTL_TRANSPARENCY_ME:
                                in >> a;
                                mtlPtr->setTransparency(a);
                            break;
                            case MTL_DISSOLVE_ME:
                                in >> a;
                                mtlPtr->setTransparency(1.f - a);
                                break;
                            case MTL_MAP_KD_ME:
                            case MTL_MAP_KA_ME:
                            case MTL_MAP_KS_ME:
                                image = NULL;
                                in >> elem;
                                iI = imageMap.find(elem);
                                if (iI == imageMap.end())
                                {
									std::string fullElemPath;
                                    if(pathHandler != NULL)
                                        fullElemPath = pathHandler->findFile(elem.c_str());
                                    else
                                        fullElemPath = elem.c_str();
                                    image = OSG::ImageFileHandler::the()->read(fullElemPath.c_str());

                                    if(image != NULL)
                                    {
                                        image->setForceAlphaBinary(
                                            image->calcIsAlphaBinary());

                                        imageMap[elem] = image;
                                    }
								}
                                else
                                {
                                    image = iI->second;
                                }
                                if (image != NULL)
                                {
                                    mtlPtr->setImage(image);
                                    switch (mtlElem)
                                    {
                                        case MTL_MAP_KD_ME:
                                            constDiffuse = true;
                                            mtlPtr->setDiffuse  ( Color3f( 1.f, 1.f, 1.f) );
                                        break;
                                        case MTL_MAP_KA_ME:
                                            constAmbient = true;
                                            mtlPtr->setAmbient  ( Color3f( 1.f, 1.f, 1.f) );
                                        break;
                                        case MTL_MAP_KS_ME:
                                            constSpecular = true;
                                            mtlPtr->setSpecular ( Color3f( 1.f, 1.f, 1.f) );
                                        break;
                                        default:
                                        break;
                                    }
                                }
                                else
                                {
                                    FFATAL (( "Can not find %s texture file in mtl %s \n",
                                            elem.c_str(), fileName ));
                                }
                            break;
                            default:
                                FWARNING (( "Invalid %s entry in %s\n",
                                            elem.c_str(), fileName ));
                                in.ignore(INT_MAX, '\n');
                        }
                    }
                }
            }
        }
    }
    return mtlCount;
}
