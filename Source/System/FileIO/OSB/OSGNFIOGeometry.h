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

#ifndef _OSGNFIOGEOMETRY_H_
#define _OSGNFIOGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeometry.h"

#include "OSGNFIOBase.h"

OSG_BEGIN_NAMESPACE

/* \brief NFIOGeometry class.
          reads and writes a geometry node.
*/

class NFIOGeometry : public NFIOBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    NFIOGeometry                     (void);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~NFIOGeometry            (void);
  
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Init                                      */
    /*! \{                                                                 */
        
    virtual void                initialise    (void);
    virtual void                terminate    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Read/Write                                */
    /*! \{                                                                 */
    
    virtual FieldContainerPtr   readFC  (const std::string &typeName);
    virtual void                writeFC (const FieldContainerPtr &fc);
    virtual void                postProcessFC(const FieldContainerPtr &fc);

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/
private:
    
    void readQuantizedPositions (GeometryPtr &geo      );
    void readQuantizedNormals   (GeometryPtr &geo      );
    void readQuantizedTexCoords (GeometryPtr &geo      );
    void readPackedIndices      (GeometryPtr &geo, UInt32 size = 0);
    template<class VecType, class GeoPropType> 
    void readQuantizedVectors(const GeoPropType &prop  );
    
    void writeQuantizedPositions(const GeometryPtr &geo, UInt8 res);
    void writeQuantizedNormals  (const GeometryPtr &geo, UInt8 res);
    void writeQuantizedTexCoords(const GeometryPtr &geo, UInt8 res);
    void writePackedIndices     (const GeometryPtr &geo                     );
    template<class VecType, class GeoPropType>
    void writeQuantizedVectors  (const GeoPropType &prop,
                                 const std::string &fieldName,
                                 const std::string &fieldType,
                                 UInt8 res);

    bool _conversion;
    
    typedef std::map<GeometryPtr, std::vector<UInt16> > geosIndexMappingMap;
    geosIndexMappingMap _geos_index_mapping;

    static const UInt16 MapPosition;
    static const UInt16 MapNormal;
    static const UInt16 MapColor;
    static const UInt16 MapSecondaryColor;
    static const UInt16 MapTexCoords;
    static const UInt16 MapTexCoords1;
    static const UInt16 MapTexCoords2;
    static const UInt16 MapTexCoords3;
    static const UInt16 MapEmpty;
    
    static NFIOGeometry _the;
};

OSG_END_NAMESPACE

#define OSGNFIOGEOMETRY_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGNFIOGEOMETRY_H_ */
