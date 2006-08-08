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

#ifndef _OSGGEOEXPORTDEFINES_H_
#define _OSGGEOEXPORTDEFINES_H_

#include "OSGExportDefines.h"

#ifdef WIN32
#  ifdef OSG_WIN32_ICL
#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType CLASSNAME< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    "GeoVectorProperty",                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &CLASSNAME< T1 >::getClassType(void);    \
                                                              \
template DLLMAPPING                                           \
UInt32 CLASSNAME< T1 >::getClassTypeId(void);               \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &CLASSNAME< T1 >::getType(void);         \
template DLLMAPPING                                           \
const FieldContainerType &CLASSNAME< T1 >::getType(void) const
#  else // OSG_WIN32_ICL
#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType CLASSNAME< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    "GeoVectorProperty",                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template class DLLMAPPING TypedGeoVectorProperty< T1 >
#  endif // OSG_WIN32_ICL
#else // WIN32
#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType CLASSNAME< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    "GeoVectorProperty",                        \
    "GeoVectorProperty",                       \
    (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *))
#endif // WIN32


#ifdef WIN32

#define OSG_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,                         \
                                  OSG_TMPL_PARAM,                    \
                                  OSG_CLASS_PTR)                     \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)

#define OSG_GEO_PROP_TYPE_TMPL_DEF(OSG_CLASS,                         \
                                   OSG_TMPL_PARAM,                    \
                                   OSG_CLASS_PTR)                     \
    OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)

#else // WIN32

#define OSG_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,                         \
                                  OSG_TMPL_PARAM,                    \
                                  OSG_CLASS_PTR)

#define OSG_GEO_PROP_TYPE_TMPL_DEF(OSG_CLASS,                         \
                                   OSG_TMPL_PARAM,                    \
                                   OSG_CLASS_PTR)
#endif // WIN32


// New stuff


#ifdef WIN32

#  ifdef OSG_MICROSOFT_COMPILER_HACKS


#define OSG_GEO_PROP_DESC(OSG_BASE, OSG_DESC)                            \
FieldDescription *OSG_DESC::_desc[] =                                       \
{                                                                           \
    new FieldDescription(                                                   \
        MField<OSG_DESC::StoredType>::getClassType(),                       \
        "data",                                                             \
        OSG_FC_FIELD_IDM_DESC(OSG_BASE<OSG_DESC>::GeoPropDataField),     \
        false,                                                              \
        OSG_BASE<OSG_DESC>::getFPtrAccessMethod())                          \
}


#  else  // OSG_MICROSOFT_COMPILER_HACKS

#define OSG_GEO_PROP_DESC(OSG_BASE, OSG_DESC)                            \
FieldDescription *OSG_DESC::_desc[] =                                       \
{                                                                           \
    new FieldDescription(                                                   \
        MField<OSG_DESC::StoredType>::getClassType(),      \
        "data",                                                             \
        OSG_FC_FIELD_IDM_DESC(OSG_BASE<OSG_DESC>::GeoPropDataField),     \
        false,                                                              \
        (FieldAccessMethod) &OSG_BASE<OSG_DESC>::getFieldPtr)               \
}


#  endif  // OSG_MICROSOFT_COMPILER_HACKS

#else // WIN32

#define OSG_GEO_PROP_DESC(OSG_BASE, OSG_DESC)                            \
FieldDescription *OSG_DESC::_desc[] =                                       \
{                                                                           \
    new FieldDescription(                                                   \
        MField<OSG_DESC::StoredType>::getClassType(),      \
        "data",                                                             \
        OSG_FC_FIELD_IDM_DESC(OSG_BASE<OSG_DESC>::GeoPropDataField),     \
        false,                                                              \
        (FieldAccessMethod) &OSG_BASE<OSG_DESC>::getFieldPtr)               \
}


#endif // WIN32


#endif /* _OSGGEOEXPORTDEFINES_H_ */
