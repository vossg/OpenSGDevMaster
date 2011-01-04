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

//-------------------------------
//  Includes
//-------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGNode.h"
#include "OSGGeometry.h"
#include "OSGSimpleMaterial.h"
#include "OSGTypedGeoIntegralProperty.h"

#include "OSGSTLSceneFileType.h"

OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


/*! \class OSG::STLSceneFileType
    \ingroup GrpSystemFileIO

*/

/*****************************
*   Types
*****************************/
// Static Class Varible implementations:

const Char8            *STLSceneFileType::_suffixA[] = {"stl", "stla", "stlb"};


STLSceneFileType  STLSceneFileType::_the(_suffixA,
                                        sizeof(_suffixA),
                                        false,
                                        10,
                                        SceneFileType::OSG_READ_SUPPORTED);

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

#ifdef __sgi
#pragma set woff 1209
#endif

NodeTransitPtr STLSceneFileType::read(      std::istream &is,
                                    const Char8        *fileNameOrExtension,
                                            Resolver        ) const
{

    NodeTransitPtr              root;
    GeometryUnrecPtr            geo;
    GeoPnt3fPropertyUnrecPtr    points;
    GeoVec3fPropertyUnrecPtr    normals;
    GeoIntegralPropertyUnrecPtr index;
    GeoIntegralPropertyUnrecPtr lens;
    GeoIntegralPropertyUnrecPtr type;

    STLFaceList theFaces;
    std::string theName;
    bool        isAscii = isASCII(is, fileNameOrExtension);

    if(isAscii)
    {
        if(!readASCII(is, theFaces, theName))
            return root;
    }
    else
    {
        if(!readBinary(is, theFaces, theName))
            return root;
    }
    if(!theFaces.empty())
    {
        geo = Geometry::create();
        
        points = GeoPnt3fProperty::create();
        geo->setPositions(points);
        normals = GeoVec3fProperty::create();
        geo->setNormals(normals);
        lens = GeoUInt32Property::create();
        geo->setLengths(lens);
        lens->push_back(theFaces.size()*3);
        type = GeoUInt8Property::create();
        geo->setTypes(type);
        type->push_back(GL_TRIANGLES);

        root = Node::create();
        //setName(root, theName.c_str());

        GeoPnt3fProperty::StoredFieldType *fPos  = points ->editFieldPtr();
        GeoVec3fProperty::StoredFieldType *fNorm = normals->editFieldPtr();

        STLFaceListIterator actIt, endIt;
        actIt = theFaces.begin();
        endIt = theFaces.end();

        while(actIt != endIt)
        {
            fPos ->push_back(Pnt3f(actIt->v1x, actIt->v1y, actIt->v1z));
            fPos ->push_back(Pnt3f(actIt->v2x, actIt->v2y, actIt->v2z));
            fPos ->push_back(Pnt3f(actIt->v3x, actIt->v3y, actIt->v3z));

            fNorm->push_back(Vec3f(actIt->nx,  actIt->ny,  actIt->nz));
            fNorm->push_back(Vec3f(actIt->nx,  actIt->ny,  actIt->nz));
            fNorm->push_back(Vec3f(actIt->nx,  actIt->ny,  actIt->nz));

            ++actIt;
        }

        geo->setTypes    (type);
        geo->setLengths  (lens);
        geo->setPositions(points);
        geo->setNormals  (normals);

        geo->setMaterial(getDefaultMaterial());

        root->setCore(geo);
    }

    commitChanges();

    return root;
}

bool STLSceneFileType::isASCII(std::istream &is, const Char8* fileNameOrExtension) const
{
    std::string theAbsName = fileNameOrExtension;
    std::string theExtension;
    int nameLength = theAbsName.length();
    int separator  = theAbsName.rfind(".", nameLength);
    theExtension = theAbsName.substr(separator+1, nameLength-separator-1);

    for (UInt32 i = 0; i < theExtension.length(); i++)
        theExtension[i] = tolower(theExtension[i]);

    if (theExtension.compare("stla") == 0)
        return true;
    else if (theExtension.compare("stlb") == 0)
        return false;
    else
    {
        // we have to check if our file start with "solid"
        std::string theCheck;
        is >> theCheck;
        for (UInt32 i = 0; i< theCheck.length(); i++)
                theCheck[i] = tolower(theCheck[i]);

        is.seekg( 0, std::ios_base::beg );

        return (theCheck.compare("solid") == 0);
    }
}

bool STLSceneFileType::readASCII(std::istream &is, STLFaceList& theFaces, std::string& theName) const
{
    FDEBUG(("STLSceneFileType::readASCII:\n"));
    
    char token[9];
    int finished = 0;
    UInt32 i;

    if(!is)
    return false;

    while ((finished == 0) && (! (is.eof())))
    {
        //SceneFileHandler::the().updateReadProgress();
        memset(token, ' ', 9);
        is >> token;
        for (i = 0; i < strlen(token); i++)
        {
            token[i] = tolower(token[i]);
        }
        if (strcmp(token, "solid") == 0)
        {
            char tmp = is.get();
            if (tmp == ' ')
            is >> theName;
        }
        else if (strcmp(token, "facet") == 0)
        {
            STLFace tmpFace;
            is >> token >> tmpFace.nx >> tmpFace.ny >> tmpFace.nz;
            is >> token >> token;// skip "outer loop"
            is >> token >> tmpFace.v1x >> tmpFace.v1y >> tmpFace.v1z;
            is >> token >> tmpFace.v2x >> tmpFace.v2y >> tmpFace.v2z;
            is >> token >> tmpFace.v3x >> tmpFace.v3y >> tmpFace.v3z;
            is >> token;// skip "endloop"
            is >> token;// skip "endfacet"
            theFaces.push_back(tmpFace);
        }
        else if (strcmp(token, "endsolid") == 0)
        {
            finished = 1;
            return true;
        }
    }
    return false;
}

bool STLSceneFileType::readBinary(std::istream &is, STLFaceList& theFaces, std::string& theName) const
{
    FDEBUG(("STLSceneFileType::readBinary:\n"));
    
    if(!is)
        return false;

    bool   bigEndian  = osgIsBigEndian();
    char   name[80]   = "";
    UInt32 facetCount = 0;
    UInt32 facet      = 0;

    is.read(&name[0], 80);  // read the header
    theName = name;
    facetCount = readUInt32(is, bigEndian);

    for(; facet < facetCount && !is.eof(); ++facet)
    {
        //SceneFileHandler::the().updateReadProgress();
        // a binary facet block has 50 bytes
        STLFace tmpFace;

        tmpFace.nx = readFloat(is, bigEndian);
        tmpFace.ny = readFloat(is, bigEndian);
        tmpFace.nz = readFloat(is, bigEndian);

        tmpFace.v1x = readFloat(is, bigEndian);
        tmpFace.v1y = readFloat(is, bigEndian);
        tmpFace.v1z = readFloat(is, bigEndian);

        tmpFace.v2x = readFloat(is, bigEndian);
        tmpFace.v2y = readFloat(is, bigEndian);
        tmpFace.v2z = readFloat(is, bigEndian);

        tmpFace.v3x = readFloat(is, bigEndian);
        tmpFace.v3y = readFloat(is, bigEndian);
        tmpFace.v3z = readFloat(is, bigEndian);

        theFaces.push_back(tmpFace);
        char buffer[2]; // offset filler
        is.read (&buffer[0], 2);
    }

    if(facet < facetCount)
    {
        SWARNING << "STLSceneFileType::readBinary: Encountered EOF after "
                 << "reading [" << facet << "] facets, was expecting ["
                 << facetCount << "]."
                 << std::endl;
    }

    return true;
}

Real32 STLSceneFileType::readFloat(std::istream& is, bool bigEndian) const
{
    Real32 result = 0.f;

    if(bigEndian)
    {
        UInt32 buffer;

        is.read(reinterpret_cast<char *>(&buffer), sizeof(Real32));
        result = osgNetToHostFP(buffer);
    }
    else
    {
        is.read(reinterpret_cast<char *>(&result), sizeof(Real32));
    }

    return result;
}

UInt32 STLSceneFileType::readUInt32(std::istream &is, bool bigEndian) const
{
    UInt32 result = 0;
    char   buffer[4];

    is.read(&buffer[0], 4);
    std::memcpy(reinterpret_cast<char *>(&result), buffer, 4);

    if(bigEndian)
        result = osgNetToHost(result);

    return result;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

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


STLSceneFileType::STLSceneFileType(const Char8  *suffixArray[],
                                        UInt16  suffixByteCount,
                                        bool    override,
                                        UInt32  overridePriority,
                                        UInt32  flags) :
    SceneFileType(suffixArray,
                suffixByteCount,
                override,
                overridePriority,
                flags)
{
}

STLSceneFileType &STLSceneFileType::the(void)
{
    return _the;
}

const Char8 *STLSceneFileType::getName(void) const
{
    return "Stereolithography Geometry";
}


STLSceneFileType::~STLSceneFileType (void )
{
    return;
}


