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

#ifndef _OSGOSBGEOMETRYHELPER_H_
#define _OSGOSBGEOMETRYHELPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"

#include "OSGOSBElementBase.h"
#include "OSGGeometry.h"

#include "OSGNFIOBitPacker.h"
#include "OSGNFIOQuantizer.h"
#include "OSGOSBGeometryElement.h"

#include <vector>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBGeometryHelper
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OSBElementBase::BinaryReadHandler  BinaryReadHandler;
    typedef OSBElementBase::BinaryWriteHandler BinaryWriteHandler;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading Helper Functions                                     */
    /*! \{                                                                 */

    void readPackedIntegralPropertyHeader(BinaryReadHandler *rh,
                                          UInt32            &maxValue,
                                          UInt32            &propSize,
                                          UInt32            &byteSize  );

    template <class GeoPropPtrTypeT>
    void readPackedIntegralProperty   (      BinaryReadHandler *rh,
                                       const GeoPropPtrTypeT    prop,
                                       const UInt32             maxValue,
                                       const UInt32             propSize,
                                       const UInt32             byteSize );

    void readQuantizedVectorPropertyHeader(BinaryReadHandler *rh,
                                           UInt8             &resolution,
                                           Real32            &minValue,
                                           Real32            &maxValue,
                                           UInt32            &propSize   );

    template <class GeoPropPtrTypeT>
    void readQuantizedVectorProperty(      BinaryReadHandler *rh,
                                     const GeoPropPtrTypeT    prop,
                                     const UInt32             fieldSize,
                                     const UInt8              resolution,
                                     const Real32             minValue,
                                     const Real32             maxValue,
                                     const UInt32             propSize   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Conversion Helper Functions                                  */
    /*! \{                                                                 */

    template <class OutIndexPtrTypeT, class InIndexPtrTypeT>
    void splitMultiIndex(const std::vector<UInt16>           &indexMapping,
                         const InIndexPtrTypeT                inIndex,
                               Geometry                      * const geo  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

#include "OSGOSBGeometryHelper.inl"

#endif /* _OSGOSBGEOMETRYHELPER_H_ */
