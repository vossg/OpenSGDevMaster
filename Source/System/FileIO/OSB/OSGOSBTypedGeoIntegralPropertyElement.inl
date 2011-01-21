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
/* OSBTypedGeoIntegralPropertyElement                                     */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

template <class GeoPropertyTypeT>
OSBTypedGeoIntegralPropertyElement<GeoPropertyTypeT>::
    OSBTypedGeoIntegralPropertyElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class GeoPropertyTypeT>
OSBTypedGeoIntegralPropertyElement<GeoPropertyTypeT>::
    ~OSBTypedGeoIntegralPropertyElement(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

template <class GeoPropertyTypeT>
void
OSBTypedGeoIntegralPropertyElement<GeoPropertyTypeT>::read(
    const std::string &typeName)
{
    OSG_OSB_LOG(("OSBTypedGeoIntegralPropertyElement<>::read\n"));

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
            FINFO(("OSBTypedGeoIntegralPropertyElement<>::read: "
                   "Unknown version, trying to read as latest.\n"));
        }
    }
    else
    {
        FFATAL(("OSBTypedGeoIntegralPropertyElement<>::read: "
                "Can not read pre-OpenSG 2 GeoProperty data.\n"));
        return;
    }

    rh->getValue(flags);

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
            OSG_OSB_LOG(("OSBTypedGeoIntegralPropertyElement<>::read: "
                    "Reading stopped at field: [%s].\n", fieldName.c_str()));
            break;
        }

        if(fieldName == "values")
        {
            // "values" can be packed and require special handling
            if((flags & FlagPackedMask) == FlagPacked)
            {
                OSBGeometryHelper gh;
                UInt32             maxValue;
                UInt32             propSize;
                UInt32             byteSize;

                gh.readPackedIntegralPropertyHeader(
                    rh, maxValue, propSize, byteSize);

                gh.readPackedIntegralProperty(
                    rh, prop, maxValue, propSize, byteSize);
            }
            else
            {
                readFieldContent(fieldName, fieldTypeName,
                                 fieldSize, "", ptrFieldIt);
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
OSBTypedGeoIntegralPropertyElement<GeoPropertyTypeT>::postRead(void)
{
    OSG_OSB_LOG(("OSBTypedGeoIntegralPropertyElement<>::postRead\n"));
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

template <class GeoPropertyTypeT>
void
OSBTypedGeoIntegralPropertyElement<GeoPropertyTypeT>::preWrite(
    FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBTypedGeoIntegralPropertyElement<>::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

template <class GeoPropertyTypeT>
void
OSBTypedGeoIntegralPropertyElement<GeoPropertyTypeT>::write(void)
{
    OSG_OSB_LOG(("OSBTypedGeoIntegralPropertyElement<>::write\n"));

    BinaryWriteHandler    *wh    = editRoot()->getWriteHandler();
    UInt8                  flags = 0;
    GeoPropertyPtrType     prop  =
        dynamic_cast<GeoPropertyPtrType>(getContainer());

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    if(getPackData() == true)
    {
        flags |= FlagPacked;
    }
    else
    {
        flags &= ~FlagPackedMask;
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

    if(getPackData() == true)
    {
        UInt32 propSize = prop->getSize();

        if(propSize > 0)
        {
            IntegralType                maxValue;
            const GeoPropertyFieldType &propField = *(prop->getFieldPtr());

            // propField is not empty, so there is a max -> we do not deref end()
            maxValue = *(std::max_element(propField.begin(), propField.end()));

            // pack values
            BitPacker packer(propSize, maxValue);
            for(UInt32 i = 0; i < propSize; ++i)
                packer.pack(propField[i]);

            const BitPacker::BufferType &buffer   = packer.getBuffer();
            UInt32                       byteSize = buffer.size();

            // fieldSize: flags + maxValue + propSize + byteSize
            UInt32 fieldSize = sizeof(UInt8) + sizeof(IntegralType)
                + sizeof(UInt32) + sizeof(UInt8) * byteSize;

            // write everything
            writeFieldHeader(fieldName, fieldTypeName, fieldSize);
            wh->putValue(maxValue);
            wh->putValue(propSize);
            wh->putValue(byteSize);
            wh->putValues(&buffer.front(), byteSize);
        }
        else
        {
            UInt32 fieldSize = sizeof(IntegralType) + 2 * sizeof(UInt32);

            writeFieldHeader(fieldName, fieldTypeName, fieldSize);
            wh->putValue(static_cast<IntegralType>(0));  // maxValue
            wh->putValue(static_cast<UInt32>      (0));  // propSize
            wh->putValue(static_cast<UInt32>      (0));  // byteSize
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
