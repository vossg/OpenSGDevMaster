/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include <vector>

#include "OSGConfig.h"

#include "OSGGeoProperties.h"

#include "OSGNFIOGeometry.h"
#include "OSGNFIOFactory.h"

#include "OSGNFIOQuantizer.h"
#include "OSGNFIOBitPacker.h"

#include <OSGLog.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NFIOGeometry
           reads and writes a geometry node.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt16 NFIOGeometry::MapPosition       = 1;
const UInt16 NFIOGeometry::MapNormal         = NFIOGeometry::MapPosition << 1;
const UInt16 NFIOGeometry::MapColor          = NFIOGeometry::MapNormal << 1;
const UInt16 NFIOGeometry::MapSecondaryColor = NFIOGeometry::MapColor << 1;
const UInt16 NFIOGeometry::MapTexCoords      = NFIOGeometry::MapSecondaryColor << 1;
const UInt16 NFIOGeometry::MapTexCoords1     = NFIOGeometry::MapTexCoords << 1;
const UInt16 NFIOGeometry::MapTexCoords2     = NFIOGeometry::MapTexCoords1 << 1;
const UInt16 NFIOGeometry::MapTexCoords3     = NFIOGeometry::MapTexCoords2 << 1;
const UInt16 NFIOGeometry::MapTexCoords4     = NFIOGeometry::MapTexCoords3 << 1;
const UInt16 NFIOGeometry::MapTexCoords5     = NFIOGeometry::MapTexCoords4 << 1;
const UInt16 NFIOGeometry::MapTexCoords6     = NFIOGeometry::MapTexCoords5 << 1;
const UInt16 NFIOGeometry::MapTexCoords7     = NFIOGeometry::MapTexCoords6 << 1;
const UInt16 NFIOGeometry::MapEmpty          = NFIOGeometry::MapTexCoords7 << 1;

NFIOGeometry NFIOGeometry::_the;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOGeometry::NFIOGeometry(void) :
    NFIOBase("Geometry"),
    _conversion(false),
    _geos_index_mapping()
{
    _version = 200;
}

/*------------------------------ destructor -------------------------------*/

NFIOGeometry::~NFIOGeometry(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void NFIOGeometry::initialise(void)
{
    _geos_index_mapping.clear();
}

void NFIOGeometry::terminate(void)
{
    _geos_index_mapping.clear();
}

FieldContainerPtr NFIOGeometry::readFC(const std::string &/*typeName*/)
{
    FDEBUG(("NFIOGeometry::readFC\n"));
    
    GeometryPtr geo = Geometry::create();
    
    UInt16 version;
    _in->getValue(version);
    
    if(version == 100 && _version == 200)
    {
        FINFO(("NFIOGeometry::readFC : Converting 1.00 Geometry.\n"));
     
        _conversion = true;
   
        std::vector<UInt16> index_mapping;

        GetFieldHandlePtr prop_field = geo->getField("properties");
        FieldDescriptionBase *fDesc = geo->getFieldDescription("properties");
        UInt32 prop_fieldId = fDesc->getFieldId();

        // ok now add the property ids.
        _fieldList.push_back(fcInfo(geo, prop_fieldId, prop_field));
        fcInfo &prop_info = _fieldList.back();
        prop_info._ids.resize(16);
        for(UInt32 i=0;i<16;++i)
            prop_info._ids[0] = 0;

        std::string fieldName;
        while(true)
        {
            _in->getValue(fieldName);
            if(fieldName.empty())
                break;

            std::string fieldType;
            _in->getValue(fieldType);
            UInt32 size = 0;
            _in->getValue(size);
            
            
            if(fieldName == "types" ||
               fieldName == "lengths")
            {
                UInt32 id = 0;
                _in->getValue(id);
                
                if(id != 0)
                {
                    //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
                
                    GetFieldHandlePtr field = geo->getField(fieldName.c_str());
                    FieldDescriptionBase *fDesc = geo->getFieldDescription(fieldName.c_str());
                    UInt32 fieldId = fDesc->getFieldId();
                
                    _fieldList.push_back(fcInfo(geo, fieldId, id, field));
                }
            }
            else if(fieldName == "indexMapping")
            {
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s'\n", fieldName.c_str(), size, fieldType.c_str());

                MField<UInt16> im;
                im.copyFromBin(*_in);
                for(UInt32 i=0;i<im.size();++i)
                    index_mapping.push_back(im[i]);
                //printf("NFIOGeometry::readFC : got %u index maps\n", index_mapping.size());
            }
            else if(fieldName == "indices")
            {
                UInt32 id = 0;
                _in->getValue(id);
           
                if(id != 0)
                {
                    //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
                    
                    GetFieldHandlePtr field = geo->getField("propIndices");
                    FieldDescriptionBase *fDesc = geo->getFieldDescription("propIndices");
                    UInt32 fieldId = fDesc->getFieldId();
                    
                    _fieldList.push_back(fcInfo(geo, fieldId, field));
                    fcInfo &info = _fieldList.back();
                    info._ids.push_back(id);
                }
            }
            // property field
            else if(fieldName == "positions")
            {    
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::PositionsIndex] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "normals")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::NormalsIndex] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "colors")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::ColorsIndex] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "secondaryColors")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::SecondaryColorsIndex] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoordsIndex] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords1")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoords1Index] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords2")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoords2Index] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords3")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoords3Index] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords4")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoords4Index] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords5")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoords5Index] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords6")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoords6Index] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            else if(fieldName == "texCoords7")
            {
                UInt32 id = 0;
                _in->getValue(id);
                prop_info._ids[Geometry::TexCoords7Index] = id;
                //printf("NFIOGeometry::readFC : reading %s size: %u  type: '%s' id: %u\n", fieldName.c_str(), size, fieldType.c_str(), id);
            }
            // packed stuff
            else if(fieldName == "pindices")
            {
                //printf("NFIOGeometry::readFC : reading packed indices.\n");
                readPackedIndices(geo, size);
            }
            else
            {
                // ok handle the compatible fields.
                GetFieldHandlePtr field = geo->getField(fieldName.c_str());
                FieldDescriptionBase *fDesc = geo->getFieldDescription(fieldName.c_str());
        
                BitVector mask;
                UInt32 fieldId = 0;
                if(fDesc != NULL)
                {
                    mask = fDesc->getFieldMask();
                    fieldId = fDesc->getFieldId();
                }
                else
                {
                    FWARNING(("NFIOBase::readFCPtr: skipping unknown field '%s' with "
                              "type '%s'!\n", fieldName.c_str(),
                              fieldType.c_str()));
                    _in->skip(size);
                    continue;
                }

                FieldContainerPtrSFieldBase::GetHandlePtr sfPtrHandle =
                    boost::dynamic_pointer_cast<
                        FieldContainerPtrSFieldBase::GetHandle>(field);

                FieldContainerPtrMFieldBase::GetHandlePtr mfPtrHandle =
                    boost::dynamic_pointer_cast<
                        FieldContainerPtrMFieldBase::GetHandle>(field);

        
//                if(strstr(fieldType.c_str(), "Ptr") != NULL)
                if(sfPtrHandle != NULL || mfPtrHandle != NULL)
                {
//                    if(fieldType[0] == 'S' && fieldType[1] == 'F') 
                    if(sfPtrHandle != NULL && sfPtrHandle->isValid() == true)
                    {
                        readSFFieldContainerPtr(geo, fieldId, field);
                    }
//                    else if(fieldType[0] == 'M' && fieldType[1] == 'F') 
                    else if(mfPtrHandle            != NULL && 
                            mfPtrHandle->isValid() == true)
                    {
                        readMFFieldContainerPtr(geo, fieldId, field);
                    }
                }
                else if(!strcmp(fieldName.c_str(), "attachments"))
                {
                    readMFFieldContainerPtr(geo, fieldId, field);
                }
                else
                {
                    geo->copyFromBin(*_in, mask);
                }
            }
        }

        _geos_index_mapping.insert(std::make_pair(geo, index_mapping));
    }
    else
    {
        std::string fieldName;
    
        fieldName = readFCFields(geo, "", "'qpositions' 'qnormals'"
                                      " 'qtexCoords' 'pindices'");
    
        if(fieldName.empty())
            return geo;

        // qpositions
        if(fieldName == "qpositions")
        {
            readQuantizedPositions(geo);
            _in->getValue(fieldName);
            if(fieldName.empty())
                return geo;
        }
    
        // qnormals
        if(fieldName == "qnormals")
        {
            readQuantizedNormals(geo);
            _in->getValue(fieldName);
            if(fieldName.empty())
                return geo;
        }
    
        // qtexCoords
        if(fieldName == "qtexCoords")
        {
            readQuantizedTexCoords(geo);
            _in->getValue(fieldName);
            if(fieldName.empty())
                return geo;
        }
    
        // indices
        if(fieldName == "pindices")
        {
            readPackedIndices(geo);
            _in->getValue(fieldName);
            if(fieldName.empty())
                return geo;
        }
    }

    return geo;
}

void NFIOGeometry::readQuantizedPositions(GeometryPtr &geo)
{
    // read quantized normals.
    
    std::string fieldType;
    _in->getValue(fieldType);
    
    GeoPnt3fPropertyPtr positions = GeoPnt3fProperty::create();
    readQuantizedVectors<Pnt3f>(positions);
    
    geo->setPositions(positions);
}

void NFIOGeometry::readQuantizedNormals(GeometryPtr &geo)
{
    // read quantized normals.
    
    std::string fieldType;
    _in->getValue(fieldType);
    
    GeoVec3fPropertyPtr normals = GeoVec3fProperty::create();
    readQuantizedVectors<Vec3f>(normals);
    
    geo->setNormals(normals);
}

void NFIOGeometry::readQuantizedTexCoords(GeometryPtr &geo)
{
    // read quantized texcoords.
    
    std::string fieldType;
    _in->getValue(fieldType);
    
    GeoVec2fPropertyPtr texcoords = GeoVec2fProperty::create();
    readQuantizedVectors<Vec2f>(texcoords);
    
    geo->setTexCoords(texcoords);
}

void NFIOGeometry::readPackedIndices(GeometryPtr &geo, UInt32 size)
{
    // read packed indices.
  
    // when size > 0 we skip the fieldType and size reading!

    if(size == 0)
    {
        std::string fieldType;
        _in->getValue(fieldType);
    }

    UInt32 max = 0;
    UInt32 indices_size = 0;
    UInt32 noe = 0;
    
    if(size == 0)
        _in->getValue(size);
    _in->getValue(max);
    _in->getValue(indices_size);
    _in->getValue(noe);
    
    GeoIntegralPropertyPtr indices = NullFC;
    bool using_16bit = false;
    if(getOptions().unpack16BitIndices())
    {
        // auto create 16 bit indices?
        if(max > TypeTraits<UInt16>::getMax())
        {
            indices = GeoUInt32Property::create();
        }
        else
        {
            using_16bit = true;
            indices = GeoUInt16Property::create();
        }
    }
    else
    {
        indices = GeoUInt32Property::create();
    }

    std::vector<UInt8> buffer;
    buffer.reserve(noe);
    UInt8 v;
    for(UInt32 i=0;i<noe;++i)
    {
        _in->getValue(v);
        buffer.push_back(v);
    }
    
    if(using_16bit)
    {
        MFUInt16 *ind = dynamic_cast<GeoUInt16PropertyPtr>(indices)->editFieldPtr();
        ind->reserve(indices_size);
        BitUnpacker unpacker(buffer, max);
        for(UInt32 i=0;i<indices_size;++i)
            ind->push_back(UInt16(unpacker.unpack()));
    }
    else
    {
        MFUInt32 *ind = dynamic_cast<GeoUInt32PropertyPtr>(indices)->editFieldPtr();
        ind->reserve(indices_size);
        BitUnpacker unpacker(buffer, max);
        for(UInt32 i=0;i<indices_size;++i)
            ind->push_back(unpacker.unpack());
    }

    geo->setIndices(indices);
}

template<class VecType, class GeoPropType> 
void NFIOGeometry::readQuantizedVectors(const GeoPropType &prop)
{
    UInt32 size = 0;
    UInt8 res = 0;
    Real32 min = 0;
    Real32 max = 0;
    UInt32 d = prop->getDimension();
    UInt32 noe = 0;
    
    _in->getValue(size); // size
    _in->getValue(res);
    _in->getValue(min);
    _in->getValue(max);
    _in->getValue(noe);
    
    prop->editFieldPtr()->reserve(noe);

    VecType t;
    
    if(res == Quantizer::QRES_8BIT)
    {
        Quantizer quantizer(min, max, res);
        UInt8 qv;
        for(UInt32 i=0;i<noe;++i)
        {
            for(UInt32 j=0;j<d;++j)
            {
                _in->getValue(qv);
                t[j] = quantizer.decode(qv);
            }
            prop->addValue(t);
        }
    }
    else if(res == Quantizer::QRES_16BIT)
    {
        Quantizer quantizer(min, max, res);
        UInt16 qv;
        for(UInt32 i=0;i<noe;++i)
        {
            for(UInt32 j=0;j<d;++j)
            {
                _in->getValue(qv);
                t[j] = quantizer.decode(qv);
            }
            prop->addValue(t);
        }
    }
    else if (res == Quantizer::QRES_24BIT)
    {
        Quantizer quantizer(min, max, res);
        UInt32 qv;
        UInt16 qvl;
        UInt8  qvh;
        for(UInt32 i=0;i<noe;++i)
        {
            for(UInt32 j=0;j<d;++j)
            {
                _in->getValue(qvl);
                _in->getValue(qvh);
                qv = ((qvl | (qvh << 16)) & 0x00ffffff);
                t[j] = quantizer.decode(qv);
            }
            prop->addValue(t);
        }
    }
}

// ------------------------ writer ----------------------------

void NFIOGeometry::writeFC(const FieldContainerPtr &fc)
{
    FDEBUG(("NFIOGeometry::witeFC\n"));
    
    GeometryPtr geo = dynamic_cast<GeometryPtr>(fc);
    
    _out->putValue(_version);

    std::string exclude = "";
    
    if(getOptions().quantizePositions() != 0)
        exclude += "'positions'";
    if(getOptions().quantizeNormals() != 0)
        exclude += "'normals'";
    if(getOptions().quantizeTexCoords() != 0)
        exclude += "'texCoords'";
    if(getOptions().packIndices())
        exclude += "'indices'";
    
    writeFCFields(geo, exclude, false);
    
    if(getOptions().quantizePositions() != Quantizer::QRES_OFF)
        writeQuantizedPositions(geo, getOptions().quantizePositions());
    
    if(getOptions().quantizeNormals() != Quantizer::QRES_OFF)
        writeQuantizedNormals(geo, getOptions().quantizeNormals());
    
    if(getOptions().quantizeTexCoords() != Quantizer::QRES_OFF)
        writeQuantizedTexCoords(geo, getOptions().quantizeTexCoords());
    
    if(getOptions().packIndices())
        writePackedIndices(geo);

    writeEndMarker();
}

void NFIOGeometry::writeQuantizedPositions(const GeometryPtr &geo, UInt8 res)
{
    GeoPnt3fPropertyPtr positions = dynamic_cast<GeoPnt3fPropertyPtr>(geo->getPositions());
    
    if(positions != NullFC)
    {
        writeQuantizedVectors<Pnt3f>(positions, "qpositions", "QMFUInt83f", res);
    }
}


void NFIOGeometry::writeQuantizedNormals(const GeometryPtr &geo, UInt8 res)
{
    GeoVec3fPropertyPtr normals = dynamic_cast<GeoVec3fPropertyPtr>(geo->getNormals());
    
    if(normals != NullFC)
    {
        writeQuantizedVectors<Vec3f>(normals, "qnormals", "QMFUInt83f", res);
    }
}

void NFIOGeometry::writeQuantizedTexCoords(const GeometryPtr &geo, UInt8 res)
{
    GeoVec2fPropertyPtr texcoords = dynamic_cast<GeoVec2fPropertyPtr>(geo->getTexCoords());
    
    if(texcoords != NullFC)
    {
        writeQuantizedVectors<Vec2f>(texcoords, "qtexCoords", "QMFUInt82f", res);
    }
}

void NFIOGeometry::writePackedIndices(const GeometryPtr &geo)
{
    // write packed indices.

    GeoIntegralPropertyPtr indices = geo->getIndices();
    
    if(indices != NullFC)
    {
        _out->putValue(std::string("pindices"));
        _out->putValue(std::string("PMFUInt8"));
        
        // get max index.
        UInt32 max = 0;
        UInt32 indices_size = indices->getSize();
        for(UInt32 i=0;i<indices_size;++i)
        {
            UInt32 v = indices->getValue(i);
            if(v > max)
                max = v;
        }
        
        BitPacker packer(indices_size, max);
        for(UInt32 i=0;i<indices_size;++i)
            packer.pack(indices->getValue(i));
        
        std::vector<UInt8> &buffer = packer.getBuffer();
       
        UInt32 noe = buffer.size();
        UInt32 size = sizeof(UInt32) + sizeof(UInt32) + sizeof(UInt8) * noe;
        _out->putValue(size);
        _out->putValue(max);
        _out->putValue(indices_size);
        _out->putValue(noe);
        for(UInt32 i=0;i<noe;++i)
            _out->putValue(buffer[i]);
    }
}

template<class VecType, class GeoPropType>
void NFIOGeometry::writeQuantizedVectors(const GeoPropType &prop,
                                         const std::string &fieldName,
                                         const std::string &fieldType,
                                         UInt8 res)
{
    UInt32 noe = prop->getSize();
        
    if(noe > 0)
    {
        UInt32 d = prop->getDimension();
        Real32 min = FLT_MAX;
        Real32 max = -FLT_MAX;
        VecType v;
        
        for(UInt32 i=0;i<noe;++i)
        {
            v = prop->getValue(i);
            for(UInt32 j=0;j<d;++j)
            {
                if(v[j] < min)
                    min = v[j];
                if(v[j] > max)
                    max = v[j];
            }
        }
        
        _out->putValue(fieldName);
        _out->putValue(fieldType);
        
        UInt32 size;
        if(res == Quantizer::QRES_8BIT)
        {
            size = sizeof(UInt8) * d * noe + sizeof(UInt8) +
                   sizeof(Real32) + sizeof(Real32) + sizeof(UInt32);
        }
        else if(res == Quantizer::QRES_16BIT)
        {
            size = sizeof(UInt16) * d * noe + sizeof(UInt8) +
                   sizeof(Real32) + sizeof(Real32) + sizeof(UInt32);
        }
        else if(res == Quantizer::QRES_24BIT)
        {
            size = (sizeof(UInt16) + sizeof(UInt8)) * d * noe + sizeof(UInt8) +
                    sizeof(Real32) + sizeof(Real32) + sizeof(UInt32);
        }
        
        _out->putValue(size); // size
        _out->putValue(res);
        _out->putValue(min);
        _out->putValue(max);
        _out->putValue(noe);
        
        if(res == Quantizer::QRES_8BIT)
        {
            Quantizer quantizer(min, max, res);
            UInt8 qv;
            for(UInt32 i=0;i<noe;++i)
            {
                v = prop->getValue(i);
                for(UInt32 j=0;j<d;++j)
                {
                    qv = quantizer.encode(v[j]);
                    _out->putValue(qv);
                }
            }
        }
        else if(res == Quantizer::QRES_16BIT)
        {
            Quantizer quantizer(min, max, res);
            UInt16 qv;
            for(UInt32 i=0;i<noe;++i)
            {
                v = prop->getValue(i);
                for(UInt32 j=0;j<d;++j)
                {
                    qv = quantizer.encode(v[j]);
                    _out->putValue(qv);
                }
            }
        }
        else if(res == Quantizer::QRES_24BIT)
        {
            Quantizer quantizer(min, max, res);
            UInt32 qv;
            UInt16 qvl;
            UInt8  qvh;
            for(UInt32 i=0;i<noe;++i)
            {
                v = prop->getValue(i);
                for(UInt32 j=0;j<d;++j)
                {
                    qv = quantizer.encode(v[j]);
                    qvl = (qv & 0x0000ffff);
                    qvh = ((qv >> 16) & 0x000000ff);
                    _out->putValue(qvl);
                    _out->putValue(qvh);
                }
            }
        }
    }
}

void NFIOGeometry::postProcessFC(const FieldContainerPtr &fc)
{
    if(!_conversion)
        return;

    GeometryPtr geo = dynamic_cast<GeometryPtr>(fc);
    
    if(geo == NullFC)
        return;

    geosIndexMappingMap::iterator it = _geos_index_mapping.find(geo);
    
    if(it == _geos_index_mapping.end())
        return;
    
    //printf("NFIOGeometry::postProcessFC\n");

    // convert interleaved indices
        
    std::vector<UInt16> index_mapping = (*it).second;
    UInt32 size = index_mapping.size();
    
    if(size == 0)
        return;

    GeoIntegralPropertyPtr interleaved_indices = geo->getIndices();

    if(geo == NullFC)
        return;

    if(size == 1)
    {
        // single indexed.
        geo->setIndices(interleaved_indices);
    }
    else
    {
        // multi indexed.
        std::vector<GeoUInt32PropertyPtr> indices_list;
        std::vector<GeoUInt32Property::StoredFieldType *> indicesp_list;
        for(UInt32 i=0;i<size;++i)
        {
            GeoUInt32PropertyPtr indices = GeoUInt32Property::create();
            GeoUInt32Property::StoredFieldType *indicesp = indices->editFieldPtr();
            indices_list.push_back(indices);
            indicesp_list.push_back(indicesp);
        }

        // split indices
        for(UInt32 i=0;i<interleaved_indices->size();i+=size)
        {
            for(UInt32 j=0;j<size;++j)
            {
                indicesp_list[j]->push_back(
                    interleaved_indices->getValue(i+j));
            }
        }

        // remove the old interleaved indices.
        geo->setIndices(NullFC);
        geo->resizePropIndices(0);

        for(UInt32 i=0;i<size;++i)
        {
            if(index_mapping[i] & NFIOGeometry::MapPosition)
                geo->setIndex(indices_list[i], Geometry::PositionsIndex);
            if(index_mapping[i] & NFIOGeometry::MapNormal)
                geo->setIndex(indices_list[i], Geometry::NormalsIndex);
            if(index_mapping[i] & NFIOGeometry::MapColor)
                geo->setIndex(indices_list[i], Geometry::ColorsIndex);
            if(index_mapping[i] & NFIOGeometry::MapSecondaryColor)
                geo->setIndex(indices_list[i], Geometry::SecondaryColorsIndex);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords)
                geo->setIndex(indices_list[i], Geometry::TexCoordsIndex);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords1)
                geo->setIndex(indices_list[i], Geometry::TexCoords1Index);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords2)
                geo->setIndex(indices_list[i], Geometry::TexCoords2Index);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords3)
                geo->setIndex(indices_list[i], Geometry::TexCoords3Index);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords4)
                geo->setIndex(indices_list[i], Geometry::TexCoords4Index);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords5)
                geo->setIndex(indices_list[i], Geometry::TexCoords5Index);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords6)
                geo->setIndex(indices_list[i], Geometry::TexCoords6Index);
            if(index_mapping[i] & NFIOGeometry::MapTexCoords7)
                geo->setIndex(indices_list[i], Geometry::TexCoords7Index);
        }
    }
}
