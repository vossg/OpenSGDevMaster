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

#ifndef _OSGEXPORTDEFINES_H_
#define _OSGEXPORTDEFINES_H_

#ifdef WIN32
#define OSG_DLL_EXPORT __declspec(dllexport)
#else
#define OSG_DLL_EXPORT
#endif

/*---------------------------------------------------------------------------*\
 *                               Field                                       *
\*---------------------------------------------------------------------------*/

#if 0
#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION)

#if defined(WIN32X) && defined(OSG_COMPILEBASELIB)
# define OSG_FIELD_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                \
                                                                             \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME< T1 >::getClassType(void)

# define OSG_FIELD_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)            \
                                                                             \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME< T1, T2 >::getClassType(void)

# define OSG_FIELD_DLLEXPORT_DECL3(CLASSNAME, T1, T2, T3, DLLMAPPING)        \
                                                                             \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME< T1, T2, T3 >::getClassType(void)
#else
# define OSG_FIELD_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)
# define OSG_FIELD_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)
# define OSG_FIELD_DLLEXPORT_DECL3(CLASSNAME, T1, T2, T3, DLLMAPPING)
#endif


#if 0
# define OSG_FIELD_DLLEXPORT_DEF1(CLASSNAME, T1)                             \
                                                                             \
    template OSG_DLL_EXPORT                                                  \
        const FieldType &CLASSNAME< T1 >::getClassType(void)

# define OSG_FIELD_DLLEXPORT_DEF2(CLASSNAME, T1, T2)                         \
                                                                             \
    template OSG_DLL_EXPORT                                                  \
        const FieldType &CLASSNAME< T1, T2 >::getClassType(void)

# define OSG_FIELD_DLLEXPORT_DEF3(CLASSNAME, T1, T2, T3)                     \
                                                                             \
    template OSG_DLL_EXPORT                                                  \
        const FieldType &CLASSNAME< T1, T2, T3 >::getClassType(void)
#else
# define OSG_FIELD_DLLEXPORT_DEF1(CLASSNAME, T1)                             \
                                                                             \
template <> OSG_DLL_EXPORT                                                   \
const FieldType &CLASSNAME< T1 >::getClassType(void)                         \
{                                                                            \
    return _fieldType;                                                       \
}

# define OSG_FIELD_DLLEXPORT_DEF2(CLASSNAME, T1, T2)                         \
                                                                             \
template <> OSG_DLL_EXPORT                                                   \
const FieldType &CLASSNAME< T1, T2 >::getClassType(void)                     \
{                                                                            \
    return _fieldType;                                                       \
}

# define OSG_FIELD_DLLEXPORT_DEF3(CLASSNAME, T1, T2, T3)                     \
                                                                             \
template <> OSG_DLL_EXPORT                                                   \
const FieldType &CLASSNAME< T1, T2, T3 >::getClassType(void)                 \
{                                                                            \
    return _fieldType;                                                       \
}
#endif

#elif defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION)

# define OSG_FIELD_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPTING)               \
                                                                             \
    extern template class DLLMAPPING CLASSNAME< T1 >

# define OSG_FIELD_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPTING)           \
                                                                             \
    extern template class DLLMAPPING CLASSNAME< T1, T2 >

# define OSG_FIELD_DLLEXPORT_DECL3(CLASSNAME, T1, T2, T3, DLLMAPPTING)       \
                                                                             \
    extern template class DLLMAPPING CLASSNAME< T1, T2, T3 >


#  define OSG_FIELD_DLLEXPORT_DEF1(CLASSNAME, T1)                            \
                                                                             \
    template class OSG_DLL_EXPORT CLASSNAME< T1 >;

#  define OSG_FIELD_DLLEXPORT_DEF2(CLASSNAME, T1, T2)                        \
                                                                             \
    template class OSG_DLL_EXPORT CLASSNAME< T1, T2 >;

#  define OSG_FIELD_DLLEXPORT_DEF3(CLASSNAME, T1, T2, T3)                    \
                                                                             \
    template class OSG_DLL_EXPORT CLASSNAME< T1, T2, T3 >;
   
#else

# define OSG_FIELD_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING) 

# define OSG_FIELD_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING) 

# define OSG_FIELD_DLLEXPORT_DECL3(CLASSNAME, T1, T2, T3, DLLMAPPING) 

# if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)

#  define OSG_FIELD_DLLEXPORT_DEF1(CLASSNAME, T1)                            \
                                                                             \
    template const FieldType &CLASSNAME< T1 >::fieldTypeExportHelper(void)

#  define OSG_FIELD_DLLEXPORT_DEF2(CLASSNAME, T1, T2)                        \
                                                                             \
    template const FieldType &CLASSNAME< T1, T2 >::fieldTypeExportHelper(void)

#  define OSG_FIELD_DLLEXPORT_DEF3(CLASSNAME, T1, T2, T3)                    \
                                                                             \
    template const FieldType &CLASSNAME< T1,                                 \
                                         T2,                                 \
                                         T3 >::fieldTypeExportHelper(void)

# else

#  define OSG_FIELD_DLLEXPORT_DEF1(CLASSNAME, T1)                            \
                                                                             \
    template FieldType CLASSNAME< T1 >::_fieldType

#  define OSG_FIELD_DLLEXPORT_DEF2(CLASSNAME, T1, T2)                        \
                                                                             \
    template FieldType CLASSNAME< T1, T2 >::_fieldType

#  define OSG_FIELD_DLLEXPORT_DEF3(CLASSNAME, T1, T2, T3)                    \
                                                                             \
    template FieldType CLASSNAME< T1, T2, T3 >::_fieldType

# endif

#endif
#endif

# define OSG_FIELD_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)
# define OSG_FIELD_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)
# define OSG_FIELD_DLLEXPORT_DECL3(CLASSNAME, T1, T2, T3, DLLMAPPING)

# define OSG_FIELD_DLLEXPORT_DEF1(CLASSNAME, T1)                             \
                                                                             \
template <> OSG_DLL_EXPORT                                                   \
const FieldType &CLASSNAME< T1 >::getClassType(void)                         \
{                                                                            \
    return _fieldType;                                                       \
}

# define OSG_FIELD_DLLEXPORT_DEF2(CLASSNAME, T1, T2)                         \
                                                                             \
template <> OSG_DLL_EXPORT                                                   \
const FieldType &CLASSNAME< T1, T2 >::getClassType(void)                     \
{                                                                            \
    return _fieldType;                                                       \
}

# define OSG_FIELD_DLLEXPORT_DEF3(CLASSNAME, T1, T2, T3)                     \
                                                                             \
template <> OSG_DLL_EXPORT                                                   \
const FieldType &CLASSNAME< T1, T2, T3 >::getClassType(void)                 \
{                                                                            \
    return _fieldType;                                                       \
}

#define OSG_FIELDTRAITS_GETTYPE(CLASSNAME)        \
DataType &FieldTraits< CLASSNAME >::getType(void) \
{                                                 \
    return _type;                                 \
}

#define OSG_FIELDTRAITS_GETTYPE_NS(CLASSNAME, NAMESPACE)     \
DataType &FieldTraits< CLASSNAME, NAMESPACE >::getType(void) \
{                                                            \
    return _type;                                            \
}

#endif /* _OSGEXPORTDEFINES_H_ */

