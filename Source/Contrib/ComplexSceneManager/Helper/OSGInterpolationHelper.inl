/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

template<class KeyFieldT, class KeyValueFieldT, class ValueFieldT> inline
void InterpolationHelper<KeyFieldT,
                         KeyValueFieldT,
                         ValueFieldT>::copyFirstValue(
                             const KeyValueFieldT &mfKeyValues,
                                   ValueFieldT    &fValue     )
{
    fValue.setValue(mfKeyValues.front());
}

template<class KeyFieldT, class KeyValueFieldT, class ValueFieldT> inline
void InterpolationHelper<KeyFieldT,
                         KeyValueFieldT,
                         ValueFieldT>::copyLastValue (
                             const KeyValueFieldT &mfKeyValues,
                                   ValueFieldT    &fValue     )
{
    fValue.setValue(mfKeyValues.back());
}


template<> inline
void InterpolationHelper<MFReal32, 
                         MFQuaternion, 
                         SFQuaternion>::lerp( 
                             const UInt32        uiStopIndex,
                             const UInt32        uiStartIndex,
                             const Real32        rFraction,
                             const MFReal32     &mfKeys,
                             const MFQuaternion &mfKeyValues,
                                   SFQuaternion &fValue  )
{
    if(osgAbs(mfKeys[uiStopIndex] - mfKeys[uiStartIndex]) < Eps)
    {
        return;
    }
    else
    {
        Quaternion result;

        Real32 t =
            (rFraction           - mfKeys[uiStartIndex]) /
            (mfKeys[uiStopIndex] - mfKeys[uiStartIndex]);
        
        result.slerpThis(mfKeyValues[uiStartIndex], 
                         mfKeyValues[uiStopIndex],
                         t);

        fValue.setValue(result);
    }
}





template<class KeyFieldT, class KeyValueFieldT, class ValueFieldT> inline
void InterpolationHelper<KeyFieldT,
                         KeyValueFieldT,
                         ValueFieldT>::interpolate(
                             const Real32          rFraction,
                             const KeyFieldT      &mfKeys,
                             const KeyValueFieldT &mfKeyValues,
                                   ValueFieldT    &fValue     )
{
    typename KeyFieldT::const_iterator keyIt;

    keyIt = lower_bound(mfKeys.begin(), 
                        mfKeys.end  (),
                        rFraction);

    if(keyIt != mfKeys.end())
    {
        if(keyIt == mfKeys.begin())
        {
            copyFirstValue(mfKeyValues, fValue);
        }
        else
        {
            UInt32 uiStopIndex  = keyIt - mfKeys.begin();
            UInt32 uiStartIndex = uiStopIndex - 1;
            
            lerp(uiStartIndex, 
                 uiStopIndex, 
                 rFraction,
                 mfKeys,
                 mfKeyValues, 
                 fValue     );
        }
    }
    else
    {
        copyLastValue(mfKeyValues, fValue);
    }
}

OSG_END_NAMESPACE
