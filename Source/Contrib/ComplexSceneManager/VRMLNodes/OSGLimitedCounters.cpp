/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include "OSGLimitedCounters.h"

OSG_BEGIN_NAMESPACE

#define OSGLIMCOUNTER_IMPL(DESC)                                       \
                                                                       \
template<>                                                             \
void LimitedCounterImpl<DESC>::classDescInserter(                      \
    TypeObject &oType)                                                 \
{                                                                      \
    FieldDescriptionBase *pDesc = NULL;                                \
                                                                       \
                                                                       \
    pDesc = new SFLimitType::Description(                              \
        SFLimitType::getClassType(),                                   \
        "upperLimit",                                                  \
        "",                                                            \
        UpperLimitFieldId, UpperLimitFieldMask,                        \
        true,                                                          \
        (Field::FThreadLocal),                                         \
        static_cast<FieldEditMethodSig>(&Self::editHandleUpperLimit),  \
        static_cast<FieldGetMethodSig >(&Self::getHandleUpperLimit));  \
                                                                       \
    oType.addInitialDesc(pDesc);                                       \
                                                                       \
    pDesc = new SFLimitType::Description(                              \
        SFLimitType::getClassType(),                                   \
        "lowerLimit",                                                  \
        "",                                                            \
        LowerLimitFieldId, LowerLimitFieldMask,                        \
        false,                                                         \
        (Field::FThreadLocal),                                         \
        static_cast<FieldEditMethodSig>(&Self::editHandleLowerLimit),  \
        static_cast<FieldGetMethodSig >(&Self::getHandleLowerLimit));  \
                                                                       \
    oType.addInitialDesc(pDesc);                                       \
                                                                       \
    pDesc = new SFBool::Description(                                   \
        SFBool::getClassType(),                                        \
        "loop",                                                        \
        "",                                                            \
        LoopFieldId, LoopFieldMask,                                    \
        true,                                                          \
        (Field::FThreadLocal),                                         \
        static_cast<FieldEditMethodSig>(&Self::editHandleLoop),        \
        static_cast<FieldGetMethodSig >(&Self::getHandleLoop));        \
                                                                       \
    oType.addInitialDesc(pDesc);                                       \
}                                                                      \
                                                                       \
                                                                       \
template<>                                                             \
LimitedCounterImpl<DESC>::TypeObject                                   \
    LimitedCounterImpl<DESC>::_type(                                   \
        Self::getClassname(),                                          \
        Inherited::getClassname(),                                     \
        "NULL",                                                        \
        0,                                                             \
        reinterpret_cast<PrototypeCreateF>(&Self::createEmptyLocal),   \
        Self::initMethod,                                              \
        Self::exitMethod,                                              \
        reinterpret_cast<InitalInsertDescFunc>(                        \
            reinterpret_cast<void *>(&Self::classDescInserter)),       \
        false,                                                         \
        0,                                                             \
        "",                                                            \
        ""                                                             \
                                   );                                  \
                                                                       \
                                                                       \
                                                                       \
template<>                                                             \
FieldContainerType &LimitedCounterImpl<DESC>::getClassType(void)       \
{                                                                      \
    return _type;                                                      \
}                                                                      \
                                                                       \
template<>                                                             \
UInt32 LimitedCounterImpl<DESC>::getClassTypeId(void)                  \
{                                                                      \
    return _type.getId();                                              \
}                                                                      \
                                                                       \
template<>                                                             \
UInt16 LimitedCounterImpl<DESC>::getClassGroupId(void)                 \
{                                                                      \
    return _type.getGroupId();                                         \
}                                                                      \
                                                                       \
                                                                       \
template<>                                                             \
FieldContainerType &LimitedCounterImpl<DESC>::getType(void)            \
{                                                                      \
    return _type;                                                      \
}                                                                      \
                                                                       \
template<>                                                             \
const FieldContainerType &                                             \
    LimitedCounterImpl<DESC>::getType(void) const                      \
{                                                                      \
    return _type;                                                      \
}

OSGLIMCOUNTER_IMPL(LimitedInt32CounterDesc )
OSGLIMCOUNTER_IMPL(LimitedUInt32CounterDesc)
OSGLIMCOUNTER_IMPL(LimitedReal32CounterDesc)

OSG_END_NAMESPACE
