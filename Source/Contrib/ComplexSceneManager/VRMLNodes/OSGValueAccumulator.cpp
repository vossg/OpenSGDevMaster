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

#include "OSGValueAccumulator.h"

OSG_BEGIN_NAMESPACE

#define OSGSVALUEACCUMULATOR_IMPL(DESC)                                 \
                                                                        \
template<>                                                              \
void SValueAccumulator<DESC>::classDescInserter(TypeObject &oType)      \
{                                                                       \
    FieldDescriptionBase *pDesc = NULL;                                 \
                                                                        \
                                                                        \
    pDesc = new SFValueType::Description(                               \
        SFValueType::getClassType(),                                    \
        "value",                                                        \
        "",                                                             \
        ValueFieldId, ValueFieldMask,                                   \
        true,                                                           \
        (Field::FThreadLocal),                                          \
        static_cast<FieldEditMethodSig>(&Self::editHandleValue),        \
        static_cast<FieldGetMethodSig >(&Self::getHandleValue));        \
                                                                        \
    oType.addInitialDesc(pDesc);                                        \
                                                                        \
    pDesc = new SFValueType::Description(                               \
        SFValueType::getClassType(),                                    \
        "rhs",                                                          \
        "",                                                             \
        RhsFieldId, RhsFieldMask,                                       \
        true,                                                           \
        (Field::FThreadLocal),                                          \
        static_cast<FieldEditMethodSig>(&Self::editHandleRhs),          \
        static_cast<FieldGetMethodSig >(&Self::getHandleRhs));          \
                                                                        \
    oType.addInitialDesc(pDesc);                                        \
                                                                        \
}                                                                       \
                                                                        \
                                                                        \
template<>                                                              \
SValueAccumulator<DESC>::TypeObject                                     \
    SValueAccumulator<DESC>::_type(                                     \
        Self::getClassname(),                                           \
        Inherited::getClassname(),                                      \
        "NULL",                                                         \
        0,                                                              \
        reinterpret_cast<PrototypeCreateF>(&Self::createEmptyLocal),    \
        Self::initMethod,                                               \
        Self::exitMethod,                                               \
        reinterpret_cast<InitalInsertDescFunc>(                         \
            reinterpret_cast<void *>(&Self::classDescInserter)),        \
        false,                                                          \
        (Self::ValueFieldMask         |                                 \
         Self::RhsFieldMask           ),                                \
        "",                                                             \
        ""                                                              \
                            );                                          \
                                                                        \
                                                                        \
template<>                                                              \
FieldContainerType &SValueAccumulator<DESC>::getClassType(void)         \
{                                                                       \
    return _type;                                                       \
}                                                                       \
                                                                        \
template<>                                                              \
UInt32 SValueAccumulator<DESC>::getClassTypeId(void)                    \
{                                                                       \
    return _type.getId();                                               \
}                                                                       \
                                                                        \
template<>                                                              \
UInt16 SValueAccumulator<DESC>::getClassGroupId(void)                   \
{                                                                       \
    return _type.getGroupId();                                          \
}                                                                       \
                                                                        \
template<>                                                              \
FieldContainerType &SValueAccumulator<DESC>::getType(void)              \
{                                                                       \
    return _type;                                                       \
}                                                                       \
                                                                        \
                                                                        \
template<>                                                              \
const FieldContainerType &SValueAccumulator<DESC>::getType(void) const  \
{                                                                       \
    return _type;                                                       \
}

//OSGSVALUEEMITTER_IMPL(Int32EmitterDesc )
OSGSVALUEACCUMULATOR_IMPL(Real32AccumulatorDesc)
OSGSVALUEACCUMULATOR_IMPL(Vec2fAccumulatorDesc)
OSGSVALUEACCUMULATOR_IMPL(MatrixAccumulatorDesc)

OSG_END_NAMESPACE
