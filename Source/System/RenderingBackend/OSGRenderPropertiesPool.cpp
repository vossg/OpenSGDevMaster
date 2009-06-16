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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGBaseInitFunctions.h"
#include "OSGRenderPropertiesPool.h"
#include "OSGTaggedSingletonHolder.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

OSG_TAGGEDSINGLETON_INST(RenderPropertiesPoolBase, 
                         RenderPropertiesPoolTag )

template class TaggedSingletonHolder<RenderPropertiesPoolBase, 
                                     RenderPropertiesPoolTag>;

template<>
void NamedSplitFinitePool<RenderPropBitVector, 
                          RenderPropertiesSplitInfo,
                          RenderPropertiesPoolTag, 
                          SingleLockPolicy         >::initialize(void)
{
    for(UInt32 i = 0; i < RenderPropertiesSplitInfo::SplitPoint; ++i)
    {
        RenderPropBitVector tmpVal = RenderPropBitVector(0x0001) << i;

        _vElementStore1.push_back(tmpVal);
    }

    std::reverse(_vElementStore1.begin(),
                 _vElementStore1.end  ());

    for(UInt32 i = RenderPropertiesSplitInfo::SplitPoint; 
               i < RenderPropertiesSplitInfo::NumBits; 
             ++i)
    {
        RenderPropBitVector tmpVal = RenderPropBitVector(0x0001) << i;

        _vElementStore2.push_back(tmpVal);
    }

    std::reverse(_vElementStore2.begin(),
                 _vElementStore2.end  ());

    _oDefaultElement = RenderPropBitVector(0x0000);

    std::string szFallback("fallback");

    _mNameValueMap[ szFallback     ] = _oDefaultElement;
    _mValueNameMap[_oDefaultElement] =  szFallback;
}

template<>
void NamedSplitFinitePool<RenderPropBitVector, 
                          RenderPropertiesSplitInfo,
                          RenderPropertiesPoolTag, 
                          SingleLockPolicy         >::keyToStringList(
                              const StoredType               &val,
                                    std::vector<std::string> &result)
{
    const RenderPropBitVector zeroVec = 0x0000;

    const RenderPropBitVector splitVal = 
        RenderPropBitVector(0x0001) << RenderPropertiesSplitInfo::SplitPoint;

    for(UInt32 i = 0; i < RenderPropertiesSplitInfo::NumBits; ++i)
    {
        RenderPropBitVector tmpVal = RenderPropBitVector(0x0001) << i;

        if(zeroVec != (val & tmpVal))
        {
            std::string tmpRes = this->findName(tmpVal);

            if(tmpVal < splitVal)
            {
                tmpRes.append("@");
            }
            else
            {
                tmpRes.append("$");
            }

            result.push_back(tmpRes);
        }
    }

}

OSG_END_NAMESPACE
