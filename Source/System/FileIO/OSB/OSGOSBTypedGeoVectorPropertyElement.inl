/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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
/* OSBTypedGeoVectorPropertyElement                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

template <class GeoPropertyTypeT>
OSBTypedGeoVectorPropertyElement<GeoPropertyTypeT>::
    OSBTypedGeoVectorPropertyElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class GeoPropertyTypeT>
OSBTypedGeoVectorPropertyElement<GeoPropertyTypeT>::
    ~OSBTypedGeoVectorPropertyElement(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

template <class GeoPropertyTypeT>
void
OSBTypedGeoVectorPropertyElement<GeoPropertyTypeT>::read(
    const std::string &typeName)
{
    OSG_OSB_LOG(("OSBTypedGeoVectorPropertyElement<>::read\n"));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    UInt8  ptrTypeId;
    UInt16 version;
    UInt8  flags;

    rh->getValue(ptrTypeId);
    rh->getValue(version  );

    if(version >= OSGOSBHeaderVersion200)
    {
        if(version > OSGOSBHeaderVersion200)
        {
            FINFO(("OSBTypedGeoVectorPropertyElement<>::read: "
                   "Unknown version, trying to read as latest.\n"));
        }
    }
    else
    {
        FFATAL(("OSBTypedGeoVectorPropertyElement<>::read: "
                "Can not read pre-OpenSG 2 GeoProperty data.\n"));
        return;
    }

    rh->getValue(flags);
    UInt8 quanRes = flags & FlagQuantizeResolutionMask;

    GeoPropertyUnrecPtrType prop = GeoPropertyType::create();
    setContainer(prop);

    while(true)
    {
        std::string    fieldName;
        std::string    fieldTypeName;
        UInt32         fieldSize;
        PtrFieldListIt ptrFieldIt;

        if(!readFieldHeader("", fieldName, fieldTypeName, fieldSize))
        {
            OSG_OSB_LOG(("OSBGeoIntegralPropertyElement<>::read: "
                    "Reading stopped at field: [%s].\n", fieldName.c_str()));
            break;
        }

        if(fieldName == "values")
        {
            // "values" can be quantized and require special handling
            if(quanRes == Quantizer::QRES_OFF)
            {
                readFieldContent(fieldName, fieldTypeName,
                                 fieldSize, "", ptrFieldIt);
            }
            else
            {
                OSBGeometryHelper gh;
                Real32 minValue;
                Real32 maxValue;
                UInt32 propSize;

                rh->getValue(minValue);
                rh->getValue(maxValue);
                rh->getValue(propSize);

                gh.readQuantizedVectorProperty(rh, prop, fieldSize, quanRes,
                                               minValue, maxValue, propSize );
            }
        }
        else
        {
            // all other fields can be read normally
            readFieldContent(fieldName, fieldTypeName,
                             fieldSize, "", ptrFieldIt);
        }
    }
}

template <class GeoPropertyTypeT>
void
OSBTypedGeoVectorPropertyElement<GeoPropertyTypeT>::postRead(void)
{
    OSG_OSB_LOG(("OSBTypedGeoVectorPropertyElement<>::postRead\n"));
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

template <class GeoPropertyTypeT>
void
OSBTypedGeoVectorPropertyElement<GeoPropertyTypeT>::preWrite(
    FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBTypedGeoVectorPropertyElement<>::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

template <class GeoPropertyTypeT>
void
OSBTypedGeoVectorPropertyElement<GeoPropertyTypeT>::write(void)
{
    OSG_OSB_LOG(("OSBTypedGeoVectorPropertyElement<>::write\n"));

    BinaryWriteHandler   *wh      = editRoot()->getWriteHandler();
    const OSBRootElement *root    = getRoot();
    UInt8                 quanRes = getQuantizeResolution();
    UInt8                 flags   = 0;
    GeoPropertyPtrType    prop    =
        dynamic_cast<GeoPropertyPtrType>(getContainer());

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    if((quanRes != Quantizer::QRES_OFF) && (prop->getFormat() == GL_FLOAT))
    {
        flags |= root->getOptions().quantizePositions();
    }
    else
    {
        flags &= ~FlagQuantizeResolutionMask;
    }

    wh->putValue(flags);

    std::string excludedFields("'values'");

    // write all other fields
    writeFields(excludedFields, false);

    // get info to write "values" field
    const FieldDescriptionBase *fieldDesc     =
        getContainer()->getFieldDescription("values");
    UInt32                      fieldId       = fieldDesc->getFieldId  ();
    const FieldType            &fieldType     = fieldDesc->getFieldType();
    const std::string          &fieldName     = fieldDesc->getName     ();
    const std::string          &fieldTypeName = fieldType .getName     ();
    BitVector                   fieldMask     = fieldDesc->getFieldMask();

    if((quanRes != Quantizer::QRES_OFF) && (prop->getFormat() == GL_FLOAT))
    {
        UInt32                      propSize  = prop->getSize();
        UInt32                      propDim   = prop->getDimension();
        const GeoPropertyFieldType &propField = *(prop->getFieldPtr());

        if(propSize > 0)
        {
            VectorType  vec;
            ElementType minValue = TypeTraits<ElementType>::getMax();
            ElementType maxValue = TypeTraits<ElementType>::getMin();

            for(UInt32 i = 0; i < propSize; ++i)
            {
                vec = propField[i];
                for(UInt32 d = 0; d < propDim; ++d)
                {
                    if(vec[d] < minValue)
                        minValue = vec[d];
                    if(vec[d] > maxValue)
                        maxValue = vec[d];
                }
            }

            UInt32 fieldSize = 0;
            if(quanRes == Quantizer::QRES_8BIT)
            {
                fieldSize = sizeof(UInt8) * propDim * propSize +
                    2 * sizeof(ElementType) + sizeof(UInt32);
            }
            else if(quanRes == Quantizer::QRES_16BIT)
            {
                fieldSize = sizeof(UInt16) * propDim * propSize +
                    2 * sizeof(ElementType) + sizeof(UInt32);
            }
            else if(quanRes == Quantizer::QRES_24BIT)
            {
                fieldSize =
                    (sizeof(UInt16) + sizeof(UInt8)) * propDim * propSize +
                    2 * sizeof(ElementType) + sizeof(UInt32);
            }

            // write header
            writeFieldHeader(fieldName, fieldTypeName, fieldSize);
            wh->putValue(minValue);
            wh->putValue(maxValue);
            wh->putValue(propSize);

            if(quanRes == Quantizer::QRES_8BIT)
            {
                Quantizer quantizer(minValue, maxValue, quanRes);
                UInt8     qv;
                for(UInt32 i = 0; i < propSize; ++i)
                {
                    vec = propField[i];
                    for(UInt32 d = 0; d < propDim; ++d)
                    {
                        qv = quantizer.encode(vec[d]);
                        wh->putValue(qv);
                    }
                }
            }
            else if(quanRes == Quantizer::QRES_16BIT)
            {
                Quantizer quantizer(minValue, maxValue, quanRes);
                UInt16     qv;
                for(UInt32 i = 0; i < propSize; ++i)
                {
                    vec = propField[i];
                    for(UInt32 d = 0; d < propDim; ++d)
                    {
                        qv = quantizer.encode(vec[d]);
                        wh->putValue(qv);
                    }
                }
            }
            else if(quanRes == Quantizer::QRES_24BIT)
            {
                Quantizer quantizer(minValue, maxValue, quanRes);
                UInt32    qv;
                UInt16    qvl;
                UInt8     qvh;
                for(UInt32 i = 0; i < propSize; ++i)
                {
                    vec = propField[i];
                    for(UInt32 d = 0; d < propDim; ++d)
                    {
                        qv  = quantizer.encode(vec[d]);
                        qvl = qv & 0x0000FFFF;
                        qvh = (qv >> 16) & 0x000000FF;
                        wh->putValue(qvl);
                        wh->putValue(qvh);
                    }
                }
            }
        }
        else
        {
            UInt32 fieldSize = 2 * sizeof(ElementType) + sizeof(UInt32);

            writeFieldHeader(fieldName, fieldTypeName, fieldSize);
            wh->putValue(ElementType(0));
            wh->putValue(ElementType(0));
            wh->putValue(UInt32(0));
        }
    }
    else
    {
        UInt32 fieldSize = getContainer()->getBinSize(fieldMask);

        writeFieldHeader (fieldName, fieldTypeName, fieldSize);
        writeFieldContent(fieldId);
    }

    writeEndMarker();
}

OSG_END_NAMESPACE
