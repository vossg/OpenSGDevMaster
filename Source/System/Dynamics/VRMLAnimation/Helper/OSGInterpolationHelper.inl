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
                             const KeyFieldT      &,
                             const KeyValueFieldT &mfKeyValues,
                                   ValueFieldT    &fValue     )
{
    fValue.setValue(mfKeyValues.front());
}

template<class KeyFieldT, class KeyValueFieldT, class ValueFieldT> inline
void InterpolationHelper<KeyFieldT,
                         KeyValueFieldT,
                         ValueFieldT>::copyLastValue (
                             const KeyFieldT      &,
                             const KeyValueFieldT &mfKeyValues,
                                   ValueFieldT    &fValue     )
{
    fValue.setValue(mfKeyValues.back());
}

// Orientation

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
    if(osgAbs(mfKeys[uiStopIndex] - mfKeys[uiStartIndex]) <
       TypeTraits<Real32>::getDefaultEps()                  )
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

// Position

template<> inline
void InterpolationHelper<MFReal32, 
                         MFVec3f, 
                         SFVec3f>::lerp( 
                             const UInt32    uiStopIndex,
                             const UInt32    uiStartIndex,
                             const Real32    rFraction,
                             const MFReal32 &mfKeys,
                             const MFVec3f  &mfKeyValues,
                                   SFVec3f  &fValue  )
{
    if(osgAbs(mfKeys[uiStopIndex] - mfKeys[uiStartIndex]) <
       TypeTraits<Real32>::getDefaultEps()                  )
    {
        return;
    }
    else
    {
        Vec3f vResult;

        Real32 t =
            (rFraction           - mfKeys[uiStartIndex]) /
            (mfKeys[uiStopIndex] - mfKeys[uiStartIndex]);
        
        vResult  = mfKeyValues[uiStopIndex ];
        vResult -= mfKeyValues[uiStartIndex];
        vResult *= t;

        vResult += mfKeyValues[uiStartIndex];

        fValue.setValue(vResult);
    }
}


// Coordinate

template<> inline
void InterpolationHelper<MFReal32, 
                         MFPnt3f, 
                         MFPnt3f>::copyFirstValue(
                             const MFReal32 &mfKeys,
                             const MFPnt3f  &mfKeyValues,
                                   MFPnt3f  &fValue     )
{
    UInt32 uiNumPoints = UInt32(mfKeyValues.size() / mfKeys.size());

    MFPnt3f::const_iterator startIt = mfKeyValues.begin();
    MFPnt3f::const_iterator stopIt  = startIt + uiNumPoints;
    
    fValue.clear();
    fValue.insert(fValue.begin(), startIt, stopIt);
}

template<> inline
void InterpolationHelper<MFReal32, 
                         MFPnt3f, 
                         MFPnt3f>::copyLastValue (
                             const MFReal32 &mfKeys,
                             const MFPnt3f  &mfKeyValues,
                                   MFPnt3f  &fValue     )
{
    UInt32 uiNumPoints = UInt32(mfKeyValues.size() / mfKeys.size());

    MFPnt3f::const_iterator stopIt  = mfKeyValues.end();
    MFPnt3f::const_iterator startIt = stopIt - uiNumPoints;
    
    fValue.clear();
    fValue.insert(fValue.begin(), startIt, stopIt);
}

template<> inline
void InterpolationHelper<MFReal32, 
                         MFPnt3f, 
                         MFPnt3f>::lerp( 
                             const UInt32    uiStopIndex,
                             const UInt32    uiStartIndex,
                             const Real32    rFraction,
                             const MFReal32 &mfKeys,
                             const MFPnt3f  &mfKeyValues,
                                   MFPnt3f  &fValue  )
{
    if(osgAbs(mfKeys[uiStopIndex] - mfKeys[uiStartIndex]) <
       TypeTraits<Real32>::getDefaultEps()                  )
    {
        return;
    }
    else
    {
        Pnt3f vResult;

        UInt32 uiNumPoints = UInt32(mfKeyValues.size() / mfKeys.size());

        Real32 t =
            (rFraction           - mfKeys[uiStartIndex]) /
            (mfKeys[uiStopIndex] - mfKeys[uiStartIndex]);

        UInt32 uiIndex1    = uiStartIndex * uiNumPoints;
        UInt32 uiIndex2    = uiStopIndex  * uiNumPoints;
        
        fValue.clear();

        for(UInt32 i = 0; i < uiNumPoints; i++)
        {
            vResult  = mfKeyValues[uiIndex2];
            vResult -= mfKeyValues[uiIndex1].subZero();
            vResult *= t;
            
            vResult += mfKeyValues[uiIndex1].subZero();
                
            fValue.push_back(vResult);
            
            ++uiIndex1;
            ++uiIndex2;
        }
    }
}


// Normal

template<> inline
void InterpolationHelper<MFReal32, 
                         MFVec3f, 
                         MFVec3f>::copyFirstValue(
                             const MFReal32 &mfKeys,
                             const MFVec3f  &mfKeyValues,
                                   MFVec3f  &fValue     )
{
    UInt32 uiNumPoints = UInt32(mfKeyValues.size() / mfKeys.size());

    MFVec3f::const_iterator startIt = mfKeyValues.begin();
    MFVec3f::const_iterator stopIt  = startIt + uiNumPoints;
    
    fValue.clear();
    fValue.insert(fValue.begin(), startIt, stopIt);
}

template<> inline
void InterpolationHelper<MFReal32, 
                         MFVec3f, 
                         MFVec3f>::copyLastValue (
                             const MFReal32 &mfKeys,
                             const MFVec3f  &mfKeyValues,
                                   MFVec3f  &fValue     )
{
    UInt32 uiNumPoints = UInt32(mfKeyValues.size() / mfKeys.size());

    MFVec3f::const_iterator stopIt  = mfKeyValues.end();
    MFVec3f::const_iterator startIt = stopIt - uiNumPoints;
    
    fValue.clear();
    fValue.insert(fValue.begin(), startIt, stopIt);
}

template<> inline
void InterpolationHelper<MFReal32, 
                         MFVec3f, 
                         MFVec3f>::lerp( 
                             const UInt32    uiStopIndex,
                             const UInt32    uiStartIndex,
                             const Real32    rFraction,
                             const MFReal32 &mfKeys,
                             const MFVec3f  &mfKeyValues,
                                   MFVec3f  &fValue  )
{
    if(osgAbs(mfKeys[uiStopIndex] - mfKeys[uiStartIndex]) <
       TypeTraits<Real32>::getDefaultEps()                  )
    {
        return;
    }
    else
    {
        Vec3f vResult;

        UInt32 uiNumPoints = UInt32(mfKeyValues.size() / mfKeys.size());

        Real32 t =
            (rFraction           - mfKeys[uiStartIndex]) /
            (mfKeys[uiStopIndex] - mfKeys[uiStartIndex]);

        UInt32 uiIndex1    = uiStartIndex * uiNumPoints;
        UInt32 uiIndex2    = uiStopIndex  * uiNumPoints;
        
        fValue.clear();

        for(UInt32 i = 0; i < uiNumPoints; i++)
        {
            vResult  = mfKeyValues[uiIndex2];
            vResult -= mfKeyValues[uiIndex1].subZero();
            vResult *= t;
            
            vResult += mfKeyValues[uiIndex1].subZero();
                
            fValue.push_back(vResult);
            
            ++uiIndex1;
            ++uiIndex2;
        }
    }
}


// Scalar

template<> inline
void InterpolationHelper<MFReal32, 
                         MFReal32, 
                         SFReal32>::lerp( 
                             const UInt32    uiStopIndex,
                             const UInt32    uiStartIndex,
                             const Real32    rFraction,
                             const MFReal32 &mfKeys,
                             const MFReal32 &mfKeyValues,
                                   SFReal32 &fValue  )
{
    if(osgAbs(mfKeys[uiStopIndex] - mfKeys[uiStartIndex]) <
       TypeTraits<Real32>::getDefaultEps()                  )
    {
        return;
    }
    else
    {
        Real32 vResult;

        Real32 t =
            (rFraction           - mfKeys[uiStartIndex]) /
            (mfKeys[uiStopIndex] - mfKeys[uiStartIndex]);
        
        vResult  = mfKeyValues[uiStopIndex ];
        vResult -= mfKeyValues[uiStartIndex];
        vResult *= t;

        vResult += mfKeyValues[uiStartIndex];

        fValue.setValue(vResult);
    }
}


// Interpolate

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

    if(mfKeys.size() == 0 || mfKeyValues.size() == 0)
    {
        return;
    }

    keyIt = lower_bound(mfKeys.begin(), 
                        mfKeys.end  (),
                        rFraction);

    if(keyIt != mfKeys.end())
    {
        if(keyIt == mfKeys.begin())
        {
            copyFirstValue(mfKeys, mfKeyValues, fValue);
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
        copyLastValue(mfKeys, mfKeyValues, fValue);
    }
}

template<class KeyFieldT, class KeyValueFieldT, class ValueFieldT> 
template<class ResortIndexTypeT> inline
void InterpolationHelper<KeyFieldT,
                         KeyValueFieldT,
                         ValueFieldT>::resortKeyValues(      
                                   UInt32            uiNumKeys,
                                   UInt32            uiValuesPerKey,
                                   KeyValueFieldT   &mfKeyValues,
                             const ResortIndexTypeT &mfResortIndex)
{
    KeyValueFieldT tmpKeyValues;

    tmpKeyValues.resize(mfKeyValues.size());

    UInt32 uiGlobalIdx = 0;
        
    for(UInt32 i = 0; i < uiNumKeys; ++i)
    {
        UInt32 uiGlobalBase = i * uiValuesPerKey;
                
        for(UInt32 j = 0; j < uiValuesPerKey; ++j, ++uiGlobalIdx)
        {
            tmpKeyValues[uiGlobalIdx] = 
                mfKeyValues[uiGlobalBase + mfResortIndex[j]];
        }
    }

    mfKeyValues = tmpKeyValues;
}

OSG_END_NAMESPACE
