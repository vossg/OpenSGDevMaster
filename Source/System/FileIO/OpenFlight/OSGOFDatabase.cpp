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

#include "OSGOFDatabase.h"

#include "OSGNode.h"
#include "OSGOFPrimaryRecords.h"
#include "OSGOpenFlightLog.h"

OSG_BEGIN_NAMESPACE

OFDatabase::OFDatabase(void) :
    _pHeader         (NULL),
    _sRecords        (    ),
    _pCurr           (NULL),
    _pCurrPrimary    (NULL),
    _pColorPalette   (NULL),
    _pVertexPalette  (NULL),
    _pTexturePalette (NULL),
    _pMaterialPalette(NULL),
    _targetUnits     (VU_Meters),
    _unitScale       (1.f)
{
}

OFDatabase::~OFDatabase(void)
{
    _pHeader          = NULL;
    _pColorPalette    = NULL;
    _pVertexPalette   = NULL;
    _pTexturePalette  = NULL;
    _pMaterialPalette = NULL;
}

bool OFDatabase::read(std::istream &is)
{
    bool returnValue = true;

    OFRecordHeader  oRHeader;

    returnValue = oRHeader.read(is);

    if(returnValue == false)
        return returnValue;

    _pHeader = dynamic_pointer_cast<OFHeaderRecord>(
        OFHeaderRecord::create(oRHeader, *this));

    returnValue = _pHeader->read(is);

    if(returnValue == false)
        return returnValue;

    _sRecords.push(_pHeader);

    _pCurr        = _pHeader;
    _pCurrPrimary = _pHeader;

    while(returnValue == true)
    {
        returnValue = oRHeader.read(is);

        if(returnValue == false)
            break;

        if(oRHeader.sOpCode == OFContinuationOC)
        {
            if(_pCurr != NULL)
            {
                _pCurr->readContinue(is, oRHeader.sLength - 4);
            }
            else
            {
                FWARNING(("OFDatabase::read: Found ContinuationRecord, "
                          "without preceding record.\n"));
            }
        }
        else
        {
            _pCurr = OFRecordFactory::the()->createRecord(oRHeader, *this);

            if(_pCurr != NULL)
            {
                returnValue = _pCurr->read(is);

                if(_pCurr->getCategory() == OFRecord::RC_Primary)
                {
                    _sRecords.top()->addChild(_pCurr);
                    _pCurrPrimary = _pCurr;
                }
                else if(_pCurr->getCategory() == OFRecord::RC_Ancillary)
                {
                    _pCurrPrimary->addChild(_pCurr);
                }
            }
            else
            {
                FFATAL(("OFDatabase::read: Failed to create record for "
                        "[%u][%s].\n",
                        oRHeader.sOpCode,
                        OFRecord::getOpCodeString(oRHeader.sOpCode)));
            }
        }
    }

    _pCurr        = NULL;
    _pCurrPrimary = NULL;

    _sRecords.pop();

    if(_sRecords.empty() != true)
    {
        FWARNING(("OFDatabase::read: Record stack inconsistent.\n"));
    }

    return true;
}

NodeTransitPtr OFDatabase::convert(void)
{
    NodeTransitPtr returnValue(NULL);

    if(_pHeader == NULL)
        return returnValue;

#ifndef OSG_OPENFLIGHT_SILENT
    _pHeader->dump(0);
#endif

    returnValue = _pHeader->convertToNode();

    return returnValue;
}

void OFDatabase::pushLevel(void)
{
    _sRecords.push(_pCurrPrimary);
}

void OFDatabase::popLevel(void)
{
    _sRecords.pop();

    _pCurrPrimary = _sRecords.top();
}

OFDatabase::VertexUnits OFDatabase::getTargetUnits(void) const
{
    return _targetUnits;
}

void OFDatabase::setTargetUnits(VertexUnits units)
{
    _targetUnits = units;
}

Real32 OFDatabase::getUnitScale(void) const
{
    return _unitScale;
}

void OFDatabase::setUnitScale(Real32 scale)
{
    _unitScale = scale;
}

const OFColorPaletteRecord *OFDatabase::getColorPalette(void)
{
    if(_pColorPalette == NULL)
        return NULL;

    return _pColorPalette->getRecord();
}

const OFVertexPaletteRecord *OFDatabase::getVertexPalette(void)
{
    if(_pVertexPalette == NULL)
        return NULL;

    return _pVertexPalette->getRecord();
}

const OFTexturePaletteRecord *OFDatabase::getTexRecord(UInt32 uiIdx)
{
    if(_pTexturePalette == NULL)
        return NULL;

    return _pTexturePalette->getRecord(uiIdx);
}

const OFMaterialPaletteRecord *OFDatabase::getMatRecord(UInt32 uiIdx)
{
    if(_pMaterialPalette == NULL)
        return NULL;

    return _pMaterialPalette->getRecord(uiIdx);
}

void OFDatabase::addColorPaletteRecord(OFColorPaletteRecord *pColPal)
{
    if(_pColorPalette == NULL)
        _pColorPalette = new OFColorPalette;

    _pColorPalette->addRecord(pColPal);
}

void OFDatabase::addVertexPaletteRecord(OFVertexPaletteRecord *pVertPal)
{
    if(_pVertexPalette == NULL)
        _pVertexPalette = new OFVertexPalette;

    _pVertexPalette->addRecord(pVertPal);
}

void OFDatabase::addTexturePaletteRecord(OFTexturePaletteRecord *pTexPal)
{
    if(_pTexturePalette == NULL)
        _pTexturePalette = new OFTexturePalette;

    _pTexturePalette->addRecord(pTexPal);
}

void OFDatabase::addMaterialPaletteRecord(OFMaterialPaletteRecord *pMatPal)
{
    if(_pMaterialPalette == NULL)
        _pMaterialPalette = new OFMaterialPalette;

    _pMaterialPalette->addRecord(pMatPal);
}

OSG_END_NAMESPACE
