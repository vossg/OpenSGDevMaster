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

#ifndef _OSGOSBGEOMETRYELEMENT_H_
#define _OSGOSBGEOMETRYELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGGeoIntegralProperty.h"

#include "OSGOSBCommonElement.h"
#include "OSGOSBElementFactoryHelper.h"

#include <vector>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBGeometryElement : public OSBCommonElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OSBCommonElement   Inherited;
    typedef OSBGeometryElement Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */

    static const UInt16 MapPosition;
    static const UInt16 MapNormal;
    static const UInt16 MapColor;
    static const UInt16 MapSecondaryColor;
    static const UInt16 MapTexCoords;
    static const UInt16 MapTexCoords1;
    static const UInt16 MapTexCoords2;
    static const UInt16 MapTexCoords3;
    static const UInt16 MapTexCoords4;
    static const UInt16 MapTexCoords5;
    static const UInt16 MapTexCoords6;
    static const UInt16 MapTexCoords7;
    static const UInt16 MapEmpty;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBGeometryElement(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBGeometryElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read    (const std::string &typeName);
    virtual void postRead(      void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing                                                      */
    /*! \{                                                                 */

    virtual void preWrite(FieldContainer * const fc);
    virtual void write   (void                     );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*!\brief prohibit default function (move to 'public' if needed)       */
    OSBGeometryElement(const OSBGeometryElement &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const OSBGeometryElement &source);

    /*---------------------------------------------------------------------*/
    /*! \name Reading Helper Functions                                     */
    /*! \{                                                                 */

    void readV100    (void);
    void postReadV100(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static OSBElementRegistrationHelper<OSBGeometryElement> _regHelper;

    std::vector<UInt16>         _indexMapping;
    UInt32                      _indicesId;
    GeoIntegralPropertyUnrecPtr _indices;
    bool                        _indices16Bit;
    bool                        _indicesPacked;

    UInt16                      _version;
};

OSG_END_NAMESPACE

#endif /* _OSGOSBGEOMETRYELEMENT_H_ */
