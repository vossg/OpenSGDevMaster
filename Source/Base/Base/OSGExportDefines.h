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

#ifdef OSG_1_COMPAT
# define OSG_FIELD_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)
# define OSG_FIELD_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)
# define OSG_FIELD_DLLEXPORT_DECL3(CLASSNAME, T1, T2, T3, DLLMAPPING)
#endif

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

# define OSG_FIELD_SPEZ_DLLEXPORT_DEF1(CLASSNAME, T1)                        \
                                                                             \
OSG_DLL_EXPORT                                                               \
const FieldType &CLASSNAME< T1 >::getClassType(void)                         \
{                                                                            \
    return _fieldType;                                                       \
}

# define OSG_FIELD_SPEZ_DLLEXPORT_DEF2(CLASSNAME, T1, T2)                    \
                                                                             \
OSG_DLL_EXPORT                                                               \
const FieldType &CLASSNAME< T1, T2 >::getClassType(void)                     \
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


#if defined(OSG_STATIC_MEMEBER_NEEDS_COPY_ASIGN_INIT)

#define OSG_SFIELDTYPE_SPEZ_INST(T1, T2)                 \
FieldType SField< T1 , T2 >::_fieldType = FieldType(     \
    SFieldTraits::getSName(),                            \
    SFieldTraits::getSPName(),                           \
    SFieldTraits::getType (),                            \
    FieldType::SINGLE_FIELD)

#define OSG_MFIELDTYPE_SPEZ_INST(T1, T2)                 \
FieldType MField< T1, T2 >::_fieldType = FieldType(      \
    MFieldTraits::getMName(),                            \
    MFieldTraits::getMPName(),                           \
    MFieldTraits::getType (),                            \
    FieldType::MULTI_FIELD)

#define OSG_SFIELDTYPE_INST(CLASSNAME, T1, T2, T3)           \
template<>                                                   \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType = FieldType(  \
    SFieldTraits::getSName(),                                \
    SFieldTraits::getSPName(),                               \
    SFieldTraits::getType (),                                \
    FieldType::SINGLE_FIELD)

#define OSG_SFIELDTYPE_INST_X(CLASSNAME, T1, T2, T3)        \
template<>                                                  \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType = FieldType( \
    SFieldTraits::getSName< T2 >(),                         \
    SFieldTraits::getSPName(),                              \
    SFieldTraits::getType (),                               \
    FieldType::SINGLE_FIELD)

#define OSG_MFIELDTYPE_INST(CLASSNAME, T1, T2, T3)          \
template<>                                                  \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType = FieldType( \
    MFieldTraits::getMName(),                               \
    MFieldTraits::getMPName(),                              \
    MFieldTraits::getType (),                               \
    FieldType::MULTI_FIELD)

#define OSG_MFIELDTYPE_INST_X(CLASSNAME, T1, T2, T3)        \
template<>                                                  \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType = FieldType( \
    MFieldTraits::getMName< T2 >(),                         \
    MFieldTraits::getMPName(),                              \
    MFieldTraits::getType (),                               \
    FieldType::MULTI_FIELD)

#else

#define OSG_SFIELDTYPE_SPEZ_INST(T1, T2)                 \
FieldType SField< T1 , T2 >::_fieldType(                 \
    SFieldTraits::getSName(),                            \
    SFieldTraits::getSPName(),                           \
    SFieldTraits::getType (),                            \
    FieldType::SINGLE_FIELD)

#define OSG_MFIELDTYPE_SPEZ_INST(T1, T2)                 \
FieldType MField< T1 , T2 >::_fieldType(                 \
    MFieldTraits::getMName(),                            \
    MFieldTraits::getMPName(),                           \
    MFieldTraits::getType (),                            \
    FieldType::MULTI_FIELD)

#define OSG_SFIELDTYPE_INST(CLASSNAME, T1, T2, T3)       \
template<>                                               \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType(          \
    SFieldTraits::getSName(),                            \
    SFieldTraits::getSPName(),                           \
    SFieldTraits::getType (),                            \
    FieldType::SINGLE_FIELD)

#define OSG_SFIELDTYPE_INST_X(CLASSNAME, T1, T2, T3)     \
template<>                                               \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType(          \
    SFieldTraits::getSName< T2 >(),                      \
    SFieldTraits::getSPName(),                           \
    SFieldTraits::getType (),                            \
    FieldType::SINGLE_FIELD)


#define OSG_MFIELDTYPE_INST(CLASSNAME, T1, T2, T3)       \
template<>                                               \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType(          \
    MFieldTraits::getMName(),                            \
    MFieldTraits::getMPName(),                           \
    MFieldTraits::getType (),                            \
    FieldType::MULTI_FIELD)

#define OSG_MFIELDTYPE_INST_X(CLASSNAME, T1, T2, T3)     \
template<>                                               \
FieldType CLASSNAME< T1 , T2, T3 >::_fieldType(          \
    MFieldTraits::getMName< T2 >(),                      \
    MFieldTraits::getMPName(),                           \
    MFieldTraits::getType (),                            \
    FieldType::MULTI_FIELD)

#endif


#define OSG_EXPORT_PTR_SFIELD(CLASS, T1, T2, T3) \
    OSG_SFIELDTYPE_INST_X(CLASS, T1, T2, T3);    \
    OSG_FIELD_DLLEXPORT_DEF3(CLASS, T1, T2, T3)  

#define OSG_EXPORT_PTR_MFIELD(CLASS, T1, T2, T3) \
    OSG_MFIELDTYPE_INST_X(CLASS, T1, T2, T3);    \
    OSG_FIELD_DLLEXPORT_DEF3(CLASS, T1, T2, T3)  

#define OSG_EXPORT_PTR_SFIELD_FULL(CLASS, T1, T3)                   \
    OSG_EXPORT_PTR_SFIELD(CLASS, T1, RecordedRefCountPolicy,   T3); \
    OSG_EXPORT_PTR_SFIELD(CLASS, T1, UnrecordedRefCountPolicy, T3); \
    OSG_EXPORT_PTR_SFIELD(CLASS, T1, WeakRefCountPolicy,       T3); \
    OSG_EXPORT_PTR_SFIELD(CLASS, T1, NoRefCountPolicy,         T3);

#define OSG_EXPORT_PTR_MFIELD_FULL(CLASS, T1, T3)                   \
    OSG_EXPORT_PTR_MFIELD(CLASS, T1, RecordedRefCountPolicy,   T3); \
    OSG_EXPORT_PTR_MFIELD(CLASS, T1, UnrecordedRefCountPolicy, T3); \
    OSG_EXPORT_PTR_MFIELD(CLASS, T1, WeakRefCountPolicy,       T3); \
    OSG_EXPORT_PTR_MFIELD(CLASS, T1, NoRefCountPolicy,         T3);


#define OSG_FIELD_TRAITS_NAME_INST(PTRCLASS)               \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getSName<RecordedRefCountPolicy>(void)   \
{                                                          \
    return "SFRec"#PTRCLASS;                               \
}                                                          \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getSName<UnrecordedRefCountPolicy>(void) \
{                                                          \
    return "SFUnrec"#PTRCLASS;                             \
}                                                          \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getSName<WeakRefCountPolicy>(void)       \
{                                                          \
    return "SFWeak"#PTRCLASS;                              \
}                                                          \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getSName<NoRefCountPolicy>(void)         \
{                                                          \
    return "SFUnrefd"#PTRCLASS;                            \
}                                                          \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getMName<RecordedRefCountPolicy>(void)   \
{                                                          \
    return "MFRec"#PTRCLASS;                               \
}                                                          \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getMName<UnrecordedRefCountPolicy>(void) \
{                                                          \
    return "MFUnrec"#PTRCLASS;                             \
}                                                          \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getMName<WeakRefCountPolicy>(void)       \
{                                                          \
    return "MFWeak"#PTRCLASS;                              \
}                                                          \
                                                           \
template<> inline                                          \
const Char8 *FieldTraits<                                  \
    PTRCLASS, 0>::getMName<NoRefCountPolicy>(void)         \
{                                                          \
    return "MFUnrefd"#PTRCLASS;                            \
}


#define OSG_FIELDCONTAINER_FIELDS_INST(PTRCLASS)                           \
                                                                           \
typedef                                                                    \
  FieldContainerPtrMField<PTRCLASS,                                        \
                          RecordedRefCountPolicy  > MFRec##PTRCLASS;       \
                                                                           \
typedef                                                                    \
  FieldContainerPtrMField<PTRCLASS,                                        \
                          UnrecordedRefCountPolicy> MFUnrec##PTRCLASS;     \
                                                                           \
typedef                                                                    \
  FieldContainerPtrMField<PTRCLASS,                                        \
                          WeakRefCountPolicy      > MFWeak##PTRCLASS;      \
                                                                           \
typedef                                                                    \
  FieldContainerPtrMField<PTRCLASS,                                        \
                          NoRefCountPolicy        > MFUncounted##PTRCLASS; \
                                                                           \
typedef                                                                    \
  FieldContainerPtrSField<PTRCLASS,                                        \
                          RecordedRefCountPolicy  > SFRec##PTRCLASS;       \
                                                                           \
typedef                                                                    \
  FieldContainerPtrSField<PTRCLASS,                                        \
                          UnrecordedRefCountPolicy> SFUnrec##PTRCLASS;     \
                                                                           \
typedef                                                                    \
  FieldContainerPtrSField<PTRCLASS,                                        \
                          WeakRefCountPolicy      > SFWeak##PTRCLASS;      \
                                                                           \
typedef                                                                    \
  FieldContainerPtrSField<PTRCLASS,                                        \
                          NoRefCountPolicy        > SFUncounted##PTRCLASS


#endif /* _OSGEXPORTDEFINES_H_ */

