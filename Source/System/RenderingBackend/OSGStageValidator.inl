/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

inline
void StageValidator::incEventCounter(void)
{
    ++_uiEventCounter;
}

inline
StageValidator::ValidationStatus StageValidator::validate(Int32 iStageId)
{
    if(iStageId < 0)
        return Self::Unknown;

    if(_vStatusStore.size() <= static_cast<UInt32>(iStageId))
    {
        StageStatus tmpStat;
        
        tmpStat._uiLastEvent = 0;
        tmpStat._eStatus     = Self::Unknown;

        _vStatusStore.resize(iStageId + 1, tmpStat);
    }

    StageStatus            &oStat       = _vStatusStore[iStageId];
    Self::ValidationStatus  returnValue = Self::Finished;

    if(oStat._uiLastEvent < _uiEventCounter)
    {
        oStat._uiLastEvent = _uiEventCounter;
        oStat._eStatus     = Self::Running;

        returnValue = Self::Run;
    }
    else
    {
        if(oStat._uiLastEvent == _uiEventCounter)
        {
            if(oStat._eStatus == StageValidator::Running)
            {
                oStat._eStatus = StageValidator::Finished;
                
                returnValue = Self::Run;
            }
        }
    }

    return returnValue;
}

inline
StageValidator::ValidationStatus StageValidator::checkRunRequest(Int32 iStageId)
{
    if(iStageId < 0)
        return Self::Unknown;

    if(_vStatusStore.size() <= static_cast<UInt32>(iStageId))
    {
        StageStatus tmpStat;
        
        tmpStat._uiLastEvent = 0;
        tmpStat._eStatus     = Self::Unknown;

        _vStatusStore.resize(iStageId + 1, tmpStat);
    }

    StageStatus            &oStat       = _vStatusStore[iStageId];
    Self::ValidationStatus  returnValue = Self::Inactive;

    if(oStat._uiLastEvent == 0)
    {
        oStat._uiLastEvent = _uiEventCounter;
        oStat._eStatus     = Self::Running;

        returnValue = Self::Run;
    }
    else
    {
        if(oStat._uiLastEvent == _uiEventCounter)
        {
            if(oStat._eStatus == StageValidator::Running)
            {
                oStat._eStatus = StageValidator::Finished;
                
                returnValue = Self::Run;
            }
        }
    }

    return returnValue;
}

inline
void StageValidator::requestRun(Int32 iStageId)
{
    if(iStageId < 0)
        return;

    if(_vStatusStore.size() <= static_cast<UInt32>(iStageId))
    {
        StageStatus tmpStat;
        
        tmpStat._uiLastEvent = 0;
        tmpStat._eStatus     = Self::Unknown;

        _vStatusStore.resize(iStageId + 1, tmpStat);
    }

    _vStatusStore[iStageId]._uiLastEvent = 0;
}

OSG_END_NAMESPACE
