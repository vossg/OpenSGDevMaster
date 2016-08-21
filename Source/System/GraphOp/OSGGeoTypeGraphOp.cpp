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

#include "OSGBaseTypes.h"
#include "OSGGeoTypeGraphOp.h"
#include "OSGLog.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

namespace
{

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpRefPtr newOp = GeoTypeGraphOp::create();

    GraphOpFactory::the()->registerOp(newOp);
    return true;
}

static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace


GeoTypeGraphOpTransitPtr GeoTypeGraphOp::create(void)
{
    return GeoTypeGraphOpTransitPtr(new GeoTypeGraphOp);
}

GraphOpTransitPtr GeoTypeGraphOp::clone(void)
{
    return GraphOpTransitPtr(new GeoTypeGraphOp);
}

GeoTypeGraphOp::GeoTypeGraphOp(const char* name)
    : Inherited(name),
      _filter  (TypeTraits<OSG::BitVector>::getMax())
{
}

GeoTypeGraphOp::~GeoTypeGraphOp(void)
{
}

bool GeoTypeGraphOp::travNodeEnter(Node *node)
{
    return true;
}

bool GeoTypeGraphOp::travNodeLeave(Node *node)
{
    Geometry *geo = dynamic_cast<Geometry *>(node->getCore());
    
    if(geo == NULL)
        return true;
    
    if(_filter & FilterNormals)
        processNormals(geo);
    
    if(_filter & FilterIndices)
        processIndices(geo);
    
    if(_filter & FilterLengths)
        processLengths(geo);
    
    return true;
}

void GeoTypeGraphOp::processNormals(Geometry *geo)
{
    GeoVectorProperty *norm   = geo->getProperty(Geometry::NormalsIndex);
    GeoVec3fProperty  *norm3f = dynamic_cast<GeoVec3fProperty *>(norm);
        
    if(norm3f != NULL)
    {
        GeoVec3NbPropertyUnrecPtr norm3b = GeoVec3NbProperty::create();
        
        const GeoVec3fProperty::StoredFieldType *srcF = norm3f->getFieldPtr();
        
        norm3b->resize(srcF->size());
        
        for(UInt32 i = 0; i < srcF->size(); ++i)
        {
            Vec3f n = (*srcF)[i];
            n.normalize();

            norm3b->setValue(n, i);
        }
        
        geo->setProperty(norm3b, Geometry::NormalsIndex);
    }
}

void GeoTypeGraphOp::processIndices(Geometry *geo)
{
    Geometry::IndexBag ibag = geo->getUniqueIndexBag();
        
    for(UInt32 i = 0; i < ibag.size(); ++i)
    {
        GeoIntegralProperty *ind   = ibag[i].first;
        GeoUInt32Property   *ind32 = dynamic_cast<GeoUInt32Property *>(ind);
        
        if(ind32 != NULL)
        {
            const GeoUInt32Property::StoredFieldType *srcF = ind32->getFieldPtr();
            
            UInt32 maxIndex     = TypeTraits<UInt16>::getMax();
            bool   allowConvert = true;
            
            for(UInt32 j = 0; j < srcF->size(); ++j)
            {
                if((*srcF)[j] > maxIndex)
                {
                    allowConvert = false;
                    break;
                }
            }
            
            if(allowConvert)
            {
                GeoUInt16PropertyUnrecPtr           ind16 =
                        GeoUInt16Property::create();
                GeoUInt16Property::StoredFieldType *dstF  =
                        ind16->editFieldPtr();
                
                dstF->reserve(srcF->size());
                
                for(UInt32 j = 0; j < srcF->size(); ++j)
                {
                    UInt32 k = (*srcF)[j];
                    dstF->push_back(k);
                }
                
                // set index for all properties that use it
                for(UInt32 j = 0; j < ibag[i].second.size(); ++j)
                    geo->setIndex(ind16, ibag[i].second[j]);
            }
        }
    }
}

void GeoTypeGraphOp::processLengths(Geometry *geo)
{
    GeoIntegralProperty *len   = geo->getLengths();
    GeoUInt32Property   *len32 = dynamic_cast<GeoUInt32Property *>(len);
        
    if(len32 != NULL)
    {
        const GeoUInt32Property::StoredFieldType *srcF = len32->getFieldPtr();
            
        UInt32 maxLength    = TypeTraits<UInt16>::getMax();
        bool   allowConvert = true;
            
        for(UInt32 i = 0; i < srcF->size(); ++i)
        {
            if((*srcF)[i] > maxLength)
            {
                allowConvert = false;
                break;
            }
        }
            
        if(allowConvert)
        {
            GeoUInt16PropertyUnrecPtr           len16 =
                    GeoUInt16Property::create();
            GeoUInt16Property::StoredFieldType *dstF  =
                    len16->editFieldPtr();
                
            dstF->reserve(srcF->size());
                
            for(UInt32 j = 0; j < srcF->size(); ++j)
            {
                UInt32 i = (*srcF)[j];
                dstF->push_back(i);
            }
            
            geo->setLengths(len16);
        }
    }
}

void GeoTypeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);
    std::string filter;

    if(ps("filter", filter))
    {
        _filter = TypeTraits<BitVector>::BitsClear;
        
        if(filter.find("Nor") != std::string::npos ||
           filter.find("nor") != std::string::npos   )
        {
            _filter |= FilterNormals;
        }
        
        if(filter.find("Ind") != std::string::npos ||
           filter.find("ind") != std::string::npos   )
        {
            _filter |= FilterIndices;
        }
        
        if(filter.find("Len") != std::string::npos ||
           filter.find("len") != std::string::npos   )
        {
            _filter |= FilterLengths;
        }
    }

    std::string out = ps.getUnusedParams();
    
    if(out.length())
    {
        FWARNING(("GeoTypeGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
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
