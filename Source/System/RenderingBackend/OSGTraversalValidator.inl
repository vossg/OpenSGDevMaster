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
void TraversalValidator::incEventCounter(void)
{
    ++_uiEventCounter;
}

inline
TraversalValidator::ValidationStatus 
    TraversalValidator::validate(Int32 iElementId,
                                 UInt16 uiCurrentTrav)
{
    if(iElementId < 0)
        return Self::Unknown;

    if(_vStatusStore.size() <= static_cast<UInt32>(iElementId))
    {
        TraversalStatus tmpStat;
        
        tmpStat._uiLastEvent      = 0;
        tmpStat._eStatus          = Self::Unknown;
        tmpStat._uiFinishedInTrav = 0;

        _vStatusStore.resize(iElementId + 1, tmpStat);
    }

    TraversalStatus        &oStat       = _vStatusStore[iElementId];
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
            if(oStat._eStatus == TraversalValidator::Running)
            {
                oStat._eStatus          = TraversalValidator::Finished;
                oStat._uiFinishedInTrav = uiCurrentTrav;

                returnValue = Self::Run;
            }
            else if(oStat._eStatus == TraversalValidator::Finished)
            {
                if(oStat._uiFinishedInTrav != uiCurrentTrav)
                {
                    returnValue = TraversalValidator::Inactive;
                }
            }
        }
    }

    return returnValue;
}

inline
TraversalValidator::ValidationStatus 
    TraversalValidator::checkRunRequest(Int32 iElementId)
{
    if(iElementId < 0)
        return Self::Unknown;

    if(_vStatusStore.size() <= static_cast<UInt32>(iElementId))
    {
        TraversalStatus tmpStat;
        
        tmpStat._uiLastEvent = 0;
        tmpStat._eStatus     = Self::Unknown;

        _vStatusStore.resize(iElementId + 1, tmpStat);
    }

    TraversalStatus        &oStat       = _vStatusStore[iElementId];
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
            if(oStat._eStatus == TraversalValidator::Running)
            {
                oStat._eStatus = TraversalValidator::Finished;
                
                returnValue = Self::Run;
            }
        }
    }

    return returnValue;
}

inline
void TraversalValidator::requestRun(Int32 iElementId)
{
    if(iElementId < 0)
        return;

    if(_vStatusStore.size() <= static_cast<UInt32>(iElementId))
    {
        TraversalStatus tmpStat;
        
        tmpStat._uiLastEvent = 0;
        tmpStat._eStatus     = Self::Unknown;

        _vStatusStore.resize(iElementId + 1, tmpStat);
    }

    _vStatusStore[iElementId]._uiLastEvent = 0;
}

OSG_END_NAMESPACE
