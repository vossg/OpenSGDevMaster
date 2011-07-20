/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGOFDATABASE_H_
#define _OSGOFDATABASE_H_

#include <istream>

#include "OSGFileIODef.h"
#include "OSGContainerForwards.h"

#include "OSGOFRecords.h"
#include "OSGOFPalettes.h"
#include "OSGOFPrimaryRecords.h"

#include <stack>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_FILEIO_DLLMAPPING OFDatabase
{
  public:

    enum VertexUnits
    {
        VU_Meters        = 0,
        VU_Kilometers    = 1,
        VU_Feet          = 4,
        VU_Inches        = 5,
        VU_NauticalMiles = 8
    };

    /*---------------------------------------------------------------------*/

     OFDatabase(void);
    ~OFDatabase(void);

    /*---------------------------------------------------------------------*/

    bool           read   (std::istream &is);
    NodeTransitPtr convert(void            );

    /*---------------------------------------------------------------------*/

    void pushLevel(void);
    void popLevel (void);

    /*---------------------------------------------------------------------*/

    VertexUnits getTargetUnits(void             ) const;
    void        setTargetUnits(VertexUnits units);

    Real32      getUnitScale  (void             ) const;
    void        setUnitScale  (Real32      scale);

    /*---------------------------------------------------------------------*/

    const OFColorPaletteRecord    *getColorPalette (void        );
    const OFVertexPaletteRecord   *getVertexPalette(void        );

    const OFTexturePaletteRecord  *getTexRecord    (UInt32 uiIdx);
    const OFMaterialPaletteRecord *getMatRecord    (UInt32 uiIdx);

    void addColorPaletteRecord   (OFColorPaletteRecord    *colPal );
    void addVertexPaletteRecord  (OFVertexPaletteRecord   *vertPal);
    void addTexturePaletteRecord (OFTexturePaletteRecord  *texPal );
    void addMaterialPaletteRecord(OFMaterialPaletteRecord *matPal );

    /*---------------------------------------------------------------------*/
  protected:

    OFHeaderRecordRCPtr     _pHeader;
    std::stack<OFRecord *>  _sRecords;

    OFRecordRCPtr           _pCurr;
    OFRecordRCPtr           _pCurrPrimary;

    OFColorPaletteRCPtr     _pColorPalette;
    OFVertexPaletteRCPtr    _pVertexPalette;
    OFTexturePaletteRCPtr   _pTexturePalette;
    OFMaterialPaletteRCPtr  _pMaterialPalette;

    VertexUnits             _targetUnits;
    Real32                  _unitScale;

    // OpCode without object

    static const UInt16 OFContinuationOC = 23;
};

OSG_END_NAMESPACE

#endif // _OSGOFDATABASE_H
