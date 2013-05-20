/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGRENDERPROPERTIESPOOL_H_
#define _OSGRENDERPROPERTIESPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGTaggedSingletonHolder.h"
#include "OSGNamedSplitFinitePool.h"

OSG_BEGIN_NAMESPACE

struct RenderPropertiesPoolTag;

/*! \nohierarchy
 */

struct RenderPropertiesSplitInfo
{
    // Unique lower Splitpoint bits / store 1

    static const UInt32 NumBits    = RenderPropertyBits;
    static const UInt32 SplitPoint = RenderPropertyUniqueBits;

    template<UInt32 SplitPoint>
    struct SplitMaskImpl;

    typedef SplitMaskImpl<SplitPoint> SplitMask;

    static void dump(void)
    {
        fprintf(stderr, "num bits    : %d\n", NumBits);
        fprintf(stderr, "split point : %d\n", SplitPoint);
    }
};

template<>
struct RenderPropertiesSplitInfo::SplitMaskImpl<8>
{
    static const RenderPropBitVector Lower = 0x00000000000000FF;
    static const RenderPropBitVector Upper = 0xFFFFFFFFFFFFFF00;
};

template<>
struct RenderPropertiesSplitInfo::SplitMaskImpl<16>
{
    static const RenderPropBitVector Lower = 0x000000000000FFFF;
    static const RenderPropBitVector Upper = 0xFFFFFFFFFFFF0000;
};

template<>
struct RenderPropertiesSplitInfo::SplitMaskImpl<24>
{
    static const RenderPropBitVector Lower = 0x0000000000FFFFFF;
    static const RenderPropBitVector Upper = 0xFFFFFFFFFF000000;
};

template<>
struct RenderPropertiesSplitInfo::SplitMaskImpl<32>
{
    static const RenderPropBitVector Lower  = 0x00000000FFFFFFFF;
    static const RenderPropBitVector Uppper = 0xFFFFFFFF00000000;
};
    


/*! \ingroup GrpSystemRenderingBackendPools
 */

typedef NamedSplitFinitePool<RenderPropBitVector, 
                             RenderPropertiesSplitInfo,
                             RenderPropertiesPoolTag, 
                             SingleLockPolicy> RenderPropertiesPoolBase;


/*! \ingroup GrpSystemRenderingBackendPools
 */

typedef TaggedSingletonHolder<RenderPropertiesPoolBase, 
                              RenderPropertiesPoolTag> RenderPropertiesPool;


struct RenderPropertiesStruct
{
    const BitVector ColorBuffer;
    const BitVector DepthBuffer;

    const BitVector GBuffer;

    const BitVector ShadowFactor;

    RenderPropertiesStruct(void);
};

extern OSG_SYSTEM_DLLMAPPING RenderPropertiesStruct SystemRenderProperties;

OSG_END_NAMESPACE

#endif /* _OSGDATASLOTPOOL_H_ */
