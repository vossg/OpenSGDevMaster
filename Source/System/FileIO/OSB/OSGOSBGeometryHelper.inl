/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2006 by the OpenSG Forum                  *
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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBGeometryHelper                                                      */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Reading Helper Functions                                                */

template <class GeoPropPtrTypeT>
void
OSBGeometryHelper::readPackedIntegralProperty(
          BinaryReadHandler *rh,
    const GeoPropPtrTypeT    prop,
    const UInt32             maxValue,
    const UInt32             propSize,
    const UInt32             byteSize )
{
    OSG_OSB_LOG(("OSBGeometryHelper::readPackedIntegralProperty<>:\n"));

    typedef          GeoPropPtrTypeT              GeoPropPtrType;
    typedef typename GeoPropPtrType::Object       GeoPropType;
    typedef typename GeoPropType::StoredFieldType GeoPropFieldType;
    typedef typename GeoPropFieldType::StoredType IntegralType;

    // read packed values into a buffer
    BitUnpacker::BufferType buffer;
    buffer.resize(byteSize);
    rh->getValues(static_cast<UInt8*>(&buffer.front()), byteSize);

    GeoPropFieldType *propField = prop->editFieldPtr();

    propField->reserve(propSize);
    BitUnpacker unpacker(buffer, maxValue);

    for(UInt32 i = 0; i < propSize; ++i)
    {
        propField->push_back(static_cast<IntegralType>(unpacker.unpack()));
    }

    OSG_OSB_LOG(("OSBGeometryHelper::readPackedIntegralProperty<>: "
            "Inflated [%u] bytes to [%u] values. Size ratio [%f] %%\n",
            byteSize, propSize,
            100.0 * (propSize * sizeof(IntegralType)) / byteSize));
}

template <class GeoPropPtrTypeT>
void
OSBGeometryHelper::readQuantizedVectorProperty(
          BinaryReadHandler *rh,
    const GeoPropPtrTypeT    prop,
    const UInt32             fieldSize,
    const UInt8              resolution,
    const Real32             minValue,
    const Real32             maxValue,
    const UInt32             propSize   )
{
    OSG_OSB_LOG(("OSBGeometryHelper::readQuantizedVectorProperty<>:\n"));

    typedef          GeoPropPtrTypeT                     GeoPropPtrType;
    typedef typename GeoPropPtrType::Object              GeoPropType;
    typedef typename GeoPropType::StoredFieldType        GeoPropFieldType;
    typedef typename GeoPropFieldType::StoredType        VectorType;
    typedef typename VectorType::ValueType               ElementType;

    UInt32            propDim   = prop->getDimension();
    GeoPropFieldType *propField = prop->editFieldPtr();

    // allocate space
    propField->reserve(propSize);

    if(resolution == Quantizer::QRES_8BIT)
    {
        Quantizer quan(minValue, maxValue, resolution);

        UInt8      qv;
        VectorType v;
        for(UInt32 i = 0; i < propSize; ++i)
        {
            for(UInt32 j = 0; j < propDim; ++j)
            {
                rh->getValue(qv);
                v[j] = static_cast<ElementType>(quan.decode(qv));
            }

            propField->push_back(v);
        }
    }
    else if(resolution == Quantizer::QRES_16BIT)
    {
        Quantizer quan(minValue, maxValue, resolution);

        UInt16     qv;
        VectorType v;
        for(UInt32 i = 0; i < propSize; ++i)
        {
            for(UInt32 j = 0; j < propDim; ++j)
            {
                rh->getValue(qv);
                v[j] = static_cast<ElementType>(quan.decode(qv));
            }

            propField->push_back(v);
        }
    }
    else if(resolution == Quantizer::QRES_24BIT)
    {
        Quantizer quan(minValue, maxValue, resolution);

        UInt32     qv;
        UInt16     qvl;
        UInt8      qvh;
        VectorType v;
        for(UInt32 i = 0; i < propSize; ++i)
        {
            for(UInt32 j = 0; j < propDim; ++j)
            {
                rh->getValue(qvl);
                rh->getValue(qvh);
                qv = (((static_cast<UInt32>(qvh) << 16) |
                        static_cast<UInt32>(qvl)         ) & 0x00FFFFFF);
                v[j] = static_cast<ElementType>(quan.decode(qv));
            }

            propField->push_back(v);
        }
    }
    else
    {
        FFATAL(("OSBGeometryHelper::readQuantizedVectorProperty<>: "
                "Unknown quantization resolution, can not decode data.\n"));

        // skip remaining part of field
        rh->skip(fieldSize - sizeof(UInt8) - sizeof(Real32)
                           - sizeof(Real32) - sizeof(UInt32));
    }

    OSG_OSB_LOG(("OSBGeometryHelper::readQuantizedVectorProperty<>: "
            "Inflated [%u] bytes to [%u] values. Size ratio [%f] %%\n",
            fieldSize, propSize,
            100.0 * (propSize * sizeof(VectorType)) / fieldSize));
}

/*-------------------------------------------------------------------------*/
/* Conversion Helper Functions                                             */

template <class OutIndexPtrTypeT, class InIndexPtrTypeT>
void
OSBGeometryHelper::splitMultiIndex(
    const std::vector<UInt16> &indexMapping,
    const InIndexPtrTypeT      inIndex,
          Geometry            * const geo          )
{
    typedef typename PtrStripper<OutIndexPtrTypeT>::Object OutIndexType;
    typedef typename OutIndexType::ObjUnrecPtr             OutIndexUnrecPtrType;
    typedef typename OutIndexType::StoredFieldType         OutIndexFieldType;

    UInt32 indexMappingSize = UInt32(indexMapping.size());
    UInt32 inIndexSize      = inIndex->size32();

    std::vector<OutIndexUnrecPtrType  > outIndices;
    std::vector<OutIndexFieldType    *> outFields;

    // create the index properties
    for(UInt32 i = 0; i < indexMappingSize; ++i)
    {
        OutIndexUnrecPtrType  index = OutIndexType::create();
        OutIndexFieldType    *field = index->editFieldPtr();

        outIndices.push_back(index);
        outFields .push_back(field);
    }

    // split the multi-index into single indices
    for(UInt32 i = 0; i < inIndexSize; i += indexMappingSize)
    {
        for(UInt32 j = 0; j < indexMappingSize; ++j)
        {
            outFields[j]->push_back(inIndex->getValue(i + j));
        }
    }

    // remove the old indices.
    geo->setIndices(NULL);
    geo->resizePropIndices(0);

    for(UInt32 i = 0; i < indexMappingSize; ++i)
    {
        if(indexMapping[i] & OSBGeometryElement::MapPosition)
            geo->setIndex(outIndices[i], Geometry::PositionsIndex);
        if(indexMapping[i] & OSBGeometryElement::MapNormal)
            geo->setIndex(outIndices[i], Geometry::NormalsIndex);
        if(indexMapping[i] & OSBGeometryElement::MapColor)
            geo->setIndex(outIndices[i], Geometry::ColorsIndex);
        if(indexMapping[i] & OSBGeometryElement::MapSecondaryColor)
            geo->setIndex(outIndices[i], Geometry::SecondaryColorsIndex);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords)
            geo->setIndex(outIndices[i], Geometry::TexCoordsIndex);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords1)
            geo->setIndex(outIndices[i], Geometry::TexCoords1Index);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords2)
            geo->setIndex(outIndices[i], Geometry::TexCoords2Index);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords3)
            geo->setIndex(outIndices[i], Geometry::TexCoords3Index);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords4)
            geo->setIndex(outIndices[i], Geometry::TexCoords4Index);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords5)
            geo->setIndex(outIndices[i], Geometry::TexCoords5Index);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords6)
            geo->setIndex(outIndices[i], Geometry::TexCoords6Index);
        if(indexMapping[i] & OSBGeometryElement::MapTexCoords7)
            geo->setIndex(outIndices[i], Geometry::TexCoords7Index);
    }
}


OSG_END_NAMESPACE
