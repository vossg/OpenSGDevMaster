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

#include <OSGBaseTypes.h>
#include <OSGGeoTypeGraphOp.h>
#include <OSGLog.h>
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

namespace
{

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpFactory::the()->registerOp(new GeoTypeGraphOp);
    return true;
}

static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace

GeoTypeGraphOp::GeoTypeGraphOp(const char* name)
    : Inherited(name),
      _filter  (TypeTraits<OSG::BitVector>::getMax())
{
}

GeoTypeGraphOp::~GeoTypeGraphOp(void)
{
}

GraphOpTransitPtr GeoTypeGraphOp::create(void)
{
    return GraphOpTransitPtr(new GeoTypeGraphOp());
}


bool GeoTypeGraphOp::travNodeEnter(Node *node)
{
    Geometry *geo = dynamic_cast<Geometry *>(node->getCore());

    if(geo == NULL)
    {
        return true;
    }

    GeoVectorProperty *positions = geo->getPositions();

    // amz
#if 0

#if !defined(__sun) && !defined(OSG_NO_INT8_PNT)
    // normals
    if(_filter & Geometry::NormalsFieldMask)
    {
        GeoNormalsPtr   normals   = geo->getNormals();
        GeoNormals3fPtr normals3f = GeoNormals3fPtr::dcast(normals);
        if (normals3f != NullFC)
        {
            MFVec3f &src = normals3f->getField();
            
            GeoNormals3bPtr normals3b = GeoNormals3b::create();
            MFVec3b &dst = normals3b->getField();
            dst.reserve(src.size());
            beginEditCP(normals3b);
                for (UInt32 i = 0; i < src.size(); ++i)
                {
                    Vec3f vec = src[i];
                    vec *= (0.9f / vec.length());
                    normals3b->push_back(vec);
                }
            endEditCP(normals3b);
    
            beginEditCP(geo, Geometry::NormalsFieldMask);
                geo->setNormals(normals3b);
            endEditCP(geo, Geometry::NormalsFieldMask);
        }
    }
#endif

    GeoColorsPtr    colors    = geo->getColors();
    GeoColorsPtr    scolors   = geo->getSecondaryColors();

    if(_filter & Geometry::LengthsFieldMask)
    {
        // lengths
        GeoPLengthsUI32Ptr lengthsUI32 = GeoPLengthsUI32Ptr::dcast(geo->getLengths());
        if(lengthsUI32 != NullFC)
        {
            MFUInt32 &src = lengthsUI32->getField();
    
            // now check if maximum length is greater than 65535
            UInt32 max_length = UInt32(TypeTraits<UInt16>::getMax());
            bool max_length_ok = true;
            for(UInt32 i=0;i<src.size();++i)
            {
                if(src[i] > max_length)
                {
                    max_length_ok = false;
                    break;
                }
            }
    
            if(max_length_ok)
            {
                GeoPLengthsUI16Ptr lengthsUI16 = GeoPLengthsUI16::create();
                MFUInt16 &dst = lengthsUI16->getField();
                dst.reserve(src.size());
                beginEditCP(lengthsUI16);
                    for (UInt32 i = 0; i < src.size(); ++i)
                        dst.push_back(UInt16(src[i]));
                endEditCP(lengthsUI16);
        
                beginEditCP(geo, Geometry::LengthsFieldMask);
                    geo->setLengths(lengthsUI16);
                endEditCP(geo, Geometry::LengthsFieldMask);
            }
        }
    }

    // indices
    if(_filter & Geometry::IndicesFieldMask)
    {
        GeoIndicesUI32Ptr indicesUI32 = GeoIndicesUI32Ptr::dcast(geo->getIndices());
        if(indicesUI32 != NullFC)
        {
            MFUInt32 &src = indicesUI32->getField();
    
            // now check if maximum index is greater than 65535
            UInt32 max_index = UInt32(TypeTraits<UInt16>::getMax());
            bool max_index_ok = true;
            for(UInt32 i=0;i<src.size();++i)
            {
                if(src[i] > max_index)
                {
                    max_index_ok = false;
                    break;
                }
            }
    
            if(max_index_ok)
            {
                GeoIndicesUI16Ptr indicesUI16 = GeoIndicesUI16::create();
                MFUInt16 &dst = indicesUI16->getField();
                dst.reserve(src.size());
                beginEditCP(indicesUI16);
                    for (UInt32 i = 0; i < src.size(); ++i)
                        dst.push_back(src[i]);
                endEditCP(indicesUI16);
        
                beginEditCP(geo, Geometry::IndicesFieldMask);
                    geo->setIndices(indicesUI16);
                endEditCP(geo, Geometry::IndicesFieldMask);
            }
        }
    }

#endif

    return true;
}


bool GeoTypeGraphOp::travNodeLeave(Node *)
{
    return true;
}

void GeoTypeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    std::string filter;

    // amz
#if 0
    if(ps("filter", filter))
    {
        _filter = 0;
        if(filter.find("Nor") != std::string::npos ||
           filter.find("nor") != std::string::npos)
        {
            _filter |= Geometry::NormalsFieldMask;
        }
        if(filter.find("Ind") != std::string::npos ||
           filter.find("ind") != std::string::npos)
        {
            _filter |= Geometry::IndicesFieldMask;
        }
        if(filter.find("Len") != std::string::npos ||
           filter.find("len") != std::string::npos)
        {
            _filter |= Geometry::LengthsFieldMask;
        }
    }
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("GeoTypeGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
#endif
}

std::string GeoTypeGraphOp::usage(void)
{
    return 
    "GeoType: convert the types of a Geometry's attributes\n"
    "  Tries to convert the attributes of a Geometry to smaller/faster\n"
    "  types. By default only the lengths are changed to 16 bit.\n"
    "Params: name (type, default)\n"
    "  filter  (string, \"\"): fields to convert, can be a combination of\n"
    "                        Normals, Indices and Lengths, connected by +.\n"
    ;
}

void GeoTypeGraphOp::setFilter(const OSG::BitVector &filter)
{
    _filter = filter;
}
