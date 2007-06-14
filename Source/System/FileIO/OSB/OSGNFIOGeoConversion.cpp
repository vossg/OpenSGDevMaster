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

#include "OSGConfig.h"

#include "OSGNFIOFactory.h"
#include "OSGNFIOGeneric.h"
#include "OSGGeometry.h"
#include "OSGLog.h"
#include "OSGImageFileHandler.h"
#include "OSGNameAttachment.h"

#include "OSGTypedGeoIntegralProperty.h"

#include "OSGNFIOBase.h"

OSG_USING_NAMESPACE


template<class PropType>
class NFIOGeoConversion : public NFIOBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    NFIOGeoConversion(const char *name) :
        NFIOBase(name)
    {
        _version = 100;
    }
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~NFIOGeoConversion(void)
    {
    }
  
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Read/Write                                */
    /*! \{                                                                 */

    virtual FieldContainerPtr readFC(const std::string &/*typeName*/)
    {
        FDEBUG(("NFIOGeoConversion::readFC\n"));

        UInt8 fcPtrType;
        _in->getValue(fcPtrType);

        UInt16 version = 0;
        _in->getValue(version);
    
        //printf("NFIOGeoConversion::readFC : got type %d version %d\n", fcPtrType, version);
    
        std::string fieldName;
        std::string fieldType;
        UInt32 size;
    
        // internal field.
        _in->getValue(fieldName);
        _in->getValue(fieldType);
        _in->getValue(size);
        _in->skip(size);
    
        // positions field.
        _in->getValue(fieldName);
        _in->getValue(fieldType);
        _in->getValue(size);
    
        //printf("NFIOGeoConversion::readFC : got field '%s' type '%s'\n", fieldName.c_str(), fieldType.c_str());

        typename PropType::ObjPtr pnts = PropType::create();
        typename PropType::StoredFieldType *p = pnts->editFieldPtr();
    
        p->copyFromBin(*_in);
        
        // read end marker.
        _in->getValue(fieldName);
        
        //printf("NFIOGeoConversion::readFC : reading %u elements.\n", p->size());
    
        return pnts;
    }

    virtual void writeFC(const FieldContainerPtr &/*fc*/)
    {
        FDEBUG(("NFIOGeoConversion::witeFC\n"));

        // GeoPositions is not yet supported so just write a empty dummy out.
        _out->putValue(_version);

        writeEndMarker();
    }
    
    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/
private:

};

static NFIOGeoConversion<GeoPnt2sProperty> geoPositions2s("GeoPositions2s");
static NFIOGeoConversion<GeoPnt3sProperty> geoPositions3s("GeoPositions3s");
static NFIOGeoConversion<GeoPnt4sProperty> geoPositions4s("GeoPositions4s");

static NFIOGeoConversion<GeoPnt2fProperty> geoPositions2f("GeoPositions2f");
static NFIOGeoConversion<GeoPnt3fProperty> geoPositions3f("GeoPositions3f");
static NFIOGeoConversion<GeoPnt4fProperty> geoPositions4f("GeoPositions4f");

static NFIOGeoConversion<GeoPnt2dProperty> geoPositions2d("GeoPositions2d");
static NFIOGeoConversion<GeoPnt3dProperty> geoPositions3d("GeoPositions3d");
static NFIOGeoConversion<GeoPnt4dProperty> geoPositions4d("GeoPositions4d");

static NFIOGeoConversion<GeoVec3fProperty> geoNormals3f("GeoNormals3f");
static NFIOGeoConversion<GeoVec3sProperty> geoNormals3s("GeoNormals3s");
static NFIOGeoConversion<GeoVec3bProperty> geoNormals3b("GeoNormals3b");

static NFIOGeoConversion<GeoColor3fProperty> geoColors3f("GeoColors3f");
static NFIOGeoConversion<GeoColor4fProperty> geoColors4f("GeoColors4f");

static NFIOGeoConversion<GeoColor3ubProperty> geoColors3ub("GeoColors3ub");
static NFIOGeoConversion<GeoColor4ubProperty> geoColors4ub("GeoColors4ub");

static NFIOGeoConversion<GeoVec1fProperty> geoTexCoords1f("GeoTexCoords1f");
static NFIOGeoConversion<GeoVec2fProperty> geoTexCoords2f("GeoTexCoords2f");
static NFIOGeoConversion<GeoVec3fProperty> geoTexCoords3f("GeoTexCoords3f");
static NFIOGeoConversion<GeoVec4fProperty> geoTexCoords4f("GeoTexCoords4f");

static NFIOGeoConversion<GeoVec1dProperty> geoTexCoords1d("GeoTexCoords1d");
static NFIOGeoConversion<GeoVec2dProperty> geoTexCoords2d("GeoTexCoords2d");
static NFIOGeoConversion<GeoVec3dProperty> geoTexCoords3d("GeoTexCoords3d");
static NFIOGeoConversion<GeoVec4dProperty> geoTexCoords4d("GeoTexCoords4d");

static NFIOGeoConversion<GeoUInt8Property> geoPTypesUI8("GeoPTypesUI8");
static NFIOGeoConversion<GeoUInt16Property> geoPTypesUI16("GeoPTypesUI16");
static NFIOGeoConversion<GeoUInt32Property> geoPTypesUI32("GeoPTypesUI32");

static NFIOGeoConversion<GeoUInt8Property> geoPLengthsUI8("GeoPLengthsUI8");
static NFIOGeoConversion<GeoUInt16Property> geoPLengthsUI16("GeoPLengthsUI16");
static NFIOGeoConversion<GeoUInt32Property> geoPLengthsUI32("GeoPLengthsUI32");

static NFIOGeoConversion<GeoUInt8Property> geoIndicesUI8("GeoIndicesUI8");
static NFIOGeoConversion<GeoUInt16Property> geoIndicesUI16("GeoIndicesUI16");
static NFIOGeoConversion<GeoUInt32Property> geoIndicesUI32("GeoIndicesUI32");
