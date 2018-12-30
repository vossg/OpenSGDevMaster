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

#include "OSGValueEmitter.h"

OSG_BEGIN_NAMESPACE

#define OSGSVALUEEMITTER_IMPL(DESC)                                     \
                                                                        \
template<>                                                              \
void SValueEmitter<DESC>::classDescInserter(TypeObject &oType)          \
{                                                                       \
    FieldDescriptionBase *pDesc = NULL;                                 \
                                                                        \
                                                                        \
    pDesc = new SFOSGAny::Description(                                  \
        SFOSGAny::getClassType(),                                       \
        "trigger",                                                      \
        "",                                                             \
        TriggerFieldId, TriggerFieldMask,                               \
        true,                                                           \
        (Field::FThreadLocal),                                          \
        static_cast<FieldEditMethodSig>(&Self::editHandleTrigger),      \
        static_cast<FieldGetMethodSig >(&Self::getHandleTrigger));      \
                                                                        \
    oType.addInitialDesc(pDesc);                                        \
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
    pDesc = new SFBool::Description(                                    \
        SFBool::getClassType(),                                         \
        "ignoreNextChange",                                             \
        "",                                                             \
        IgnoreNextChangeFieldId, IgnoreNextChangeFieldMask,             \
        true,                                                           \
        (Field::FThreadLocal),                                          \
        static_cast<FieldEditMethodSig>(                                \
            &Self::editHandleIgnoreNextChange),                         \
        static_cast<FieldGetMethodSig >(                                \
            &Self::getHandleIgnoreNextChange));                         \
                                                                        \
    oType.addInitialDesc(pDesc);                                        \
}                                                                       \
                                                                        \
                                                                        \
template<>                                                              \
SValueEmitter<DESC>::TypeObject                                         \
    SValueEmitter<DESC>::_type(                                         \
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
        (Self::TriggerFieldMask         |                               \
         Self::ValueFieldMask           |                               \
         Self::IgnoreNextChangeFieldMask),                              \
        "",                                                             \
        ""                                                              \
                            );                                          \
                                                                        \
                                                                        \
template<>                                                              \
FieldContainerType &SValueEmitter<DESC>::getClassType(void)             \
{                                                                       \
    return _type;                                                       \
}                                                                       \
                                                                        \
template<>                                                              \
UInt32 SValueEmitter<DESC>::getClassTypeId(void)                        \
{                                                                       \
    return _type.getId();                                               \
}                                                                       \
                                                                        \
template<>                                                              \
UInt16 SValueEmitter<DESC>::getClassGroupId(void)                       \
{                                                                       \
    return _type.getGroupId();                                          \
}                                                                       \
                                                                        \
template<>                                                              \
FieldContainerType &SValueEmitter<DESC>::getType(void)                  \
{                                                                       \
    return _type;                                                       \
}                                                                       \
                                                                        \
                                                                        \
template<>                                                              \
const FieldContainerType &SValueEmitter<DESC>::getType(void) const      \
{                                                                       \
    return _type;                                                       \
}

OSGSVALUEEMITTER_IMPL(BoolEmitterDesc  )
OSGSVALUEEMITTER_IMPL(Int32EmitterDesc )
OSGSVALUEEMITTER_IMPL(UInt32EmitterDesc)
OSGSVALUEEMITTER_IMPL(Real32EmitterDesc)
OSGSVALUEEMITTER_IMPL(TimeEmitterDesc  )
OSGSVALUEEMITTER_IMPL(Vec2fEmitterDesc )
OSGSVALUEEMITTER_IMPL(Vec3fEmitterDesc )
OSGSVALUEEMITTER_IMPL(StringEmitterDesc)
OSGSVALUEEMITTER_IMPL(MatrixEmitterDesc)

OSG_END_NAMESPACE
