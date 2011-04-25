/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline
void DisplayFilterStageData::setColFilter(ColorDisplayFilter *pFilt)
{
    _pColFilter = pFilt;
}

inline
ColorDisplayFilter *DisplayFilterStageData::getColFilter(void)
{
    return _pColFilter;
}

inline
void DisplayFilterStageData::setDistFilter(DistortionDisplayFilter *pFilt)
{
    _pDistFilter = pFilt;
}

inline
DistortionDisplayFilter *DisplayFilterStageData::getDistFilter(void)
{
    return _pDistFilter;
}

inline
void DisplayFilterStageData::setCalibFilter(CalibrationPatternFilter *pFilt)
{
    _pCalibFilter = pFilt;
}

inline
CalibrationPatternFilter *DisplayFilterStageData::getCalibFilter(void)
{
    return _pCalibFilter;
}

inline
void DisplayFilterStageData::setInitColTableFrom(ColorDisplayFilter *pFilter)
{
    _pInitColTableFrom = pFilter;
}

inline
ColorDisplayFilter *DisplayFilterStageData::getInitColTableFrom(void)
{
    return _pInitColTableFrom;
}

OSG_END_NAMESPACE
