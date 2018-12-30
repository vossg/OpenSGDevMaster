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

#include "OSGCounters.h"

OSG_BEGIN_NAMESPACE

#define OSGCOUNTER_IMPL(DESC)                                           \
                                                                        \
template<>                                                              \
void CounterImpl<DESC>::classDescInserter(TypeObject &oType)            \
{                                                                       \
    FieldDescriptionBase *pDesc = NULL;                                 \
                                                                        \
                                                                        \
    pDesc = new SFValueType::Description(                               \
        SFValueType::getClassType(),                                    \
        "step",                                                         \
        "",                                                             \
        StepFieldId, StepFieldMask,                                     \
        true,                                                           \
        (Field::FThreadLocal),                                          \
        static_cast<FieldEditMethodSig>(&Self::editHandleStep),         \
        static_cast<FieldGetMethodSig >(&Self::getHandleStep));         \
                                                                        \
    oType.addInitialDesc(pDesc);                                        \
                                                                        \
    pDesc = new SFValueType::Description(                               \
        SFValueType::getClassType(),                                    \
        "resetValue",                                                   \
        "",                                                             \
        ResetValueFieldId, ResetValueFieldMask,                         \
        false,                                                          \
        (Field::FThreadLocal),                                          \
        static_cast<FieldEditMethodSig>(&Self::editHandleResetValue),   \
        static_cast<FieldGetMethodSig >(&Self::getHandleResetValue));   \
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
}                                                                       \
                                                                        \
                                                                        \
template<>                                                              \
CounterImpl<DESC>::TypeObject                                           \
    CounterImpl<DESC>::_type(                                           \
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
        (ValueFieldMask),                                               \
        "",                                                             \
        ""                                                              \
                            );                                          \
                                                                        \
                                                                        \
template<>                                                              \
FieldContainerType &CounterImpl<DESC>::getClassType(void)               \
{                                                                       \
    return _type;                                                       \
}                                                                       \
                                                                        \
template<>                                                              \
UInt32 CounterImpl<DESC>::getClassTypeId(void)                          \
{                                                                       \
    return _type.getId();                                               \
}                                                                       \
                                                                        \
template<>                                                              \
UInt16 CounterImpl<DESC>::getClassGroupId(void)                         \
{                                                                       \
    return _type.getGroupId();                                          \
}                                                                       \
                                                                        \
template<>                                                              \
FieldContainerType &CounterImpl<DESC>::getType(void)                    \
{                                                                       \
    return _type;                                                       \
}                                                                       \
                                                                        \
                                                                        \
template<>                                                              \
const FieldContainerType &CounterImpl<DESC>::getType(void) const        \
{                                                                       \
    return _type;                                                       \
}

template<> inline
void CounterImpl<UInt32CounterDesc>::changed(ConstFieldMaskArg whichField, 
                                             UInt32            origin,
                                             BitVector         details)
{
    if((IncTriggerFieldMask | DecTriggerFieldMask) !=
       (whichField & (IncTriggerFieldMask | DecTriggerFieldMask)))
    {

        if(0x0000 != (whichField & IncTriggerFieldMask))
        {
            setValue(getValue() + getStep());
        }
        
        if(0x0000 != (whichField & DecTriggerFieldMask))
        {
            if(getStep() <= getValue())
            {
                setValue(getValue() - getStep());
            }
            else
            {
                setValue(TypeTraits<ValueType>::getZeroElement());
            }
        }
    }

    Inherited::changed(whichField, origin, details);
}



Vec2f Vec2fCounterDesc::getZeroElement(void)
{
    return Vec2f(0.f, 0.f);
}

Vec2f Vec2fCounterDesc::getOneElement(void)
{
    return Vec2f(1.f, 1.f);
}


Vec3f Vec3fCounterDesc::getZeroElement(void)
{
    return Vec3f(0.f, 0.f, 0.f);
}

Vec3f Vec3fCounterDesc::getOneElement(void)
{
    return Vec3f(1.f, 1.f, 1.f);
}


Vec4f Vec4fCounterDesc::getZeroElement(void)
{
    return Vec4f(0.f, 0.f, 0.f);
}

Vec4f Vec4fCounterDesc::getOneElement(void)
{
    return Vec4f(1.f, 1.f, 1.f);
}


OSGCOUNTER_IMPL(Int32CounterDesc )
OSGCOUNTER_IMPL(UInt32CounterDesc)
OSGCOUNTER_IMPL(Real32CounterDesc)
OSGCOUNTER_IMPL(Vec2fCounterDesc)
OSGCOUNTER_IMPL(Vec3fCounterDesc)
OSGCOUNTER_IMPL(Vec4fCounterDesc)

OSG_END_NAMESPACE
