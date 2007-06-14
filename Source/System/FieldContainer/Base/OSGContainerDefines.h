/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGCONTAINERDEFINES_H_
#define _OSGCONTAINERDEFINES_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/preprocessor/facilities/empty.hpp>

/*---------------------------- get type decl --------------------------------*/

#define OSG_RC_GET_TYPE_DECL                                                  \
    virtual       TypeObject &getType(void);                                  \
    virtual const TypeObject &getType(void) const

#define OSG_RC_GET_STATIC_TYPE_DECL                                           \
    static TypeObject &getClassType(void)           

#define OSG_RC_GET_STATIC_TYPE_ID_DECL                                        \
    static OSG::UInt32 getClassTypeId (void);                                 \
    static OSG::UInt32 getClassGroupId(void)

#define OSG_RC_TYPE_FUNCTIONS_DECL                                            \
    OSG_RC_GET_TYPE_DECL;                                                     \
    OSG_RC_GET_STATIC_TYPE_DECL;                                              \
    OSG_RC_GET_STATIC_TYPE_ID_DECL                     

/*---------------------------- get type def ---------------------------------*/

#define OSG_RC_GET_TYPE_DEF(OSG_CLASS)                                        \
    OSG_CLASS::TypeObject &OSG_CLASS::getType(void)                           \
    {                                                                         \
        return _type;                                                         \
    }                                                                         \
    const OSG_CLASS::TypeObject &OSG_CLASS::getType(void) const               \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_RC_GET_STATIC_TYPE_INL_DEF(OSG_CLASS)                             \
    inline                                                                    \
    OSG_CLASS::TypeObject &OSG_CLASS::getClassType(void)                      \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_RC_GET_STATIC_TYPE_ID_INL_DEF(OSG_CLASS)                          \
    inline                                                                    \
    OSG::UInt32 OSG_CLASS::getClassTypeId(void)                               \
    {                                                                         \
        return _type.getId();                                                 \
    }                                                                         \
    inline                                                                    \
    OSG::UInt32 OSG_CLASS::getClassGroupId(void)                              \
    {                                                                         \
        return _type.getGroupId();                                            \
    }

// -- Macros for defining the rc methods for template types -- //
#define OSG_RC_GET_STATIC_TYPE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, INLINE)    \
    template< class OSG_TMPL_PARAM >                                          \
    INLINE typename OSG_CLASS< OSG_TMPL_PARAM >::TypeObject &                 \
        OSG_CLASS< OSG_TMPL_PARAM >::getClassType(void)                       \
    {                                                                         \
        return Self::_type;                                                   \
    }
#define OSG_RC_GET_STATIC_TYPE_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)     \
        OSG_RC_GET_STATIC_TYPE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, BOOST_PP_EMPTY() )
#define OSG_RC_GET_STATIC_TYPE_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)        \
        OSG_RC_GET_STATIC_TYPE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, inline)

#define OSG_RC_GET_STATIC_TYPE_ID_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, INLINE) \
    template< class OSG_TMPL_PARAM >                                          \
    INLINE OSG::UInt32 OSG_CLASS< OSG_TMPL_PARAM >::getClassTypeId(void)      \
    {                                                                         \
        return Self::_type.getId();                                           \
    }                                                                         \
    template< class OSG_TMPL_PARAM >                                          \
    INLINE OSG::UInt32 OSG_CLASS< OSG_TMPL_PARAM >::getClassGroupId(void)     \
    {                                                                         \
        return Self::_type.getGroupId();                                      \
    }
#define OSG_RC_GET_STATIC_TYPE_ID_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)  \
        OSG_RC_GET_STATIC_TYPE_ID_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, BOOST_PP_EMPTY() )
#define OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)     \
        OSG_RC_GET_STATIC_TYPE_ID_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, inline)

#define OSG_RC_GET_TYPE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, INLINE)           \
    template< class OSG_TMPL_PARAM >                                          \
    INLINE typename OSG_CLASS< OSG_TMPL_PARAM >::TypeObject &                 \
        OSG_CLASS< OSG_TMPL_PARAM >::getType(void)                            \
    {                                                                         \
        return _type;                                                         \
    }                                                                         \
    template< class OSG_TMPL_PARAM >                                          \
    INLINE const typename OSG_CLASS< OSG_TMPL_PARAM >::TypeObject &           \
        OSG_CLASS< OSG_TMPL_PARAM >::getType(void) const                      \
    {                                                                         \
        return _type;                                                         \
    }
#define OSG_RC_GET_TYPE_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)            \
        OSG_RC_GET_TYPE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, BOOST_PP_EMPTY() )
#define OSG_RC_GET_TYPE_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)               \
        OSG_RC_GET_TYPE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, inline)


/** Macro for defining fully specialized version of the getType methods. */
#define OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(OSG_CLASS, TMPL_TYPE)            \
    template<> OSG_DLL_EXPORT                                                 \
    OSG_CLASS< TMPL_TYPE >::TypeObject &                                      \
        OSG_CLASS< TMPL_TYPE >::getType(void)                                 \
    {                                                                         \
        return _type;                                                         \
    }                                                                         \
    template<> OSG_DLL_EXPORT                                                 \
    const OSG_CLASS< TMPL_TYPE >::TypeObject &                                \
        OSG_CLASS< TMPL_TYPE >::getType(void) const                           \
    {                                                                         \
        return _type;                                                         \
    }                                                                         \
                                                                              \
    template <> OSG_DLL_EXPORT                                                \
    OSG_CLASS< TMPL_TYPE >::TypeObject &                                      \
       OSG_CLASS< TMPL_TYPE >::getClassType(void)                             \
    {                                                                         \
       return _type;                                                          \
    }


#define OSG_RC_TYPE_FUNCTIONS_DEF(OSG_CLASS)                                  \
    OSG_RC_GET_TYPE_DEF(OSG_CLASS)

#define OSG_RC_TYPE_FUNCTIONS_INL_DEF(OSG_CLASS)                              \
    OSG_RC_GET_STATIC_TYPE_INL_DEF   (OSG_CLASS)                              \
    OSG_RC_GET_STATIC_TYPE_ID_INL_DEF(OSG_CLASS)

#define OSG_RC_TYPE_FUNCTIONS_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)      \
    OSG_RC_GET_STATIC_TYPE_NONINL_TMPL_DEF   (OSG_CLASS, OSG_TMPL_PARAM)      \
    OSG_RC_GET_STATIC_TYPE_ID_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)      \
    OSG_RC_GET_TYPE_NONINL_TMPL_DEF          (OSG_CLASS, OSG_TMPL_PARAM)


/*---------------------------- create decl ----------------------------------*/

#define OSG_RC_CREATE_DECL                                                    \
    static ObjPtr create(void)

#define OSG_RC_CREATE_EMPTY_DECL                                              \
    static ObjPtr createEmpty(void)

#define OSG_RC_SHALLOWCOPY_DECL                                               \
    virtual OSG::FieldContainerPtr shallowCopy(void) const

#define OSG_RC_CREATE_FUNCTIONS_DECL                                          \
    OSG_RC_CREATE_DECL;                                                       \
    OSG_RC_CREATE_EMPTY_DECL;                                                 \
    OSG_RC_SHALLOWCOPY_DECL

/*---------------------------- create def -----------------------------------*/

#define OSG_RC_SHALLOWCOPY_DEF(OSG_CLASS)                                     \
    OSG::FieldContainerPtr OSG_CLASS::shallowCopy(void) const                 \
    {                                                                         \
        ObjPtr returnValue;                                                   \
                                                                              \
        newPtr<Self>(returnValue, this);                                      \
                                                                              \
        return returnValue;                                                   \
    } 

#define OSG_RC_SHALLOWCOPY_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, INLINE)    \
    template < class OSG_TMPL_PARAM > INLINE                                  \
    OSG::FieldContainerPtr                                                    \
        OSG_CLASS< OSG_TMPL_PARAM >::shallowCopy(void) const                  \
    {                                                                         \
        ObjPtr returnValue;                                                   \
                                                                              \
        Self::template newPtr<Self>(returnValue, this);                       \
                                                                              \
        return returnValue;                                                   \
    }
#define OSG_RC_SHALLOWCOPY_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)         \
        OSG_RC_SHALLOWCOPY_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, BOOST_PP_EMPTY() )
#define OSG_RC_SHALLOWCOPY_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)            \
        OSG_RC_SHALLOWCOPY_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, inline)


#define OSG_RC_CREATE_INL_DEF(OSG_CLASS)                                      \
    inline                                                                    \
    OSG_CLASS::ObjPtr OSG_CLASS::create(void)                                 \
    {                                                                         \
        ObjPtr fc;                                                            \
                                                                              \
        if(getClassType().getPrototype() != OSGNullFC)                        \
         fc = dynamic_cast<Self::ObjPtr>(                                     \
             getClassType().getPrototype()->shallowCopy());                   \
                                                                              \
        return fc;                                                            \
    }

#define OSG_RC_CREATE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, INLINE)             \
    template < class OSG_TMPL_PARAM > INLINE                                  \
    typename OSG_CLASS < OSG_TMPL_PARAM >::ObjPtr                             \
        OSG_CLASS< OSG_TMPL_PARAM >::create(void)                             \
    {                                                                         \
        ObjPtr fc;                                                            \
                                                                              \
        if(getClassType().getPrototype() != OSGNullFC)                        \
        {                                                                     \
         OSG::FieldContainerPtr temp_ptr = getClassType().getPrototype()->shallowCopy();  \
         fc = dynamic_cast<typename Self::ObjPtr>(temp_ptr);                  \
        }                                                                     \
                                                                              \
        return fc;                                                            \
    }
#define OSG_RC_CREATE_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)              \
        OSG_RC_CREATE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, BOOST_PP_EMPTY() )
#define OSG_RC_CREATE_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)                 \
        OSG_RC_CREATE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, inline)

#define OSG_RC_CREATE_SPECIALIZED_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)         \
    template <> OSG_DLL_EXPORT                                                \
    OSG_CLASS < OSG_TMPL_PARAM >::ObjPtr                                      \
        OSG_CLASS< OSG_TMPL_PARAM >::create(void)                             \
    {                                                                         \
        ObjPtr fc;                                                            \
                                                                              \
        if(getClassType().getPrototype() != OSGNullFC)                        \
        { \
         OSG::FieldContainerPtr temp_ptr = getClassType().getPrototype()->shallowCopy();  \
         fc = dynamic_cast<Self::ObjPtr>(temp_ptr);                           \
        }                                                                     \
                                                                              \
        return fc;                                                            \
    }

#define OSG_RC_CREATE_EMPTY_INL_DEF(OSG_CLASS)                                \
    inline                                                                    \
    OSG_CLASS::ObjPtr OSG_CLASS::createEmpty(void)                            \
    {                                                                         \
        ObjPtr returnValue;                                                   \
                                                                              \
        newPtr<Self>(returnValue);                                            \
                                                                              \
        return returnValue;                                                   \
    }

#define OSG_RC_CREATE_EMPTY_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, INLINE)       \
    template < class OSG_TMPL_PARAM > INLINE                                  \
    typename OSG_CLASS< OSG_TMPL_PARAM >::ObjPtr                              \
        OSG_CLASS< OSG_TMPL_PARAM >::createEmpty(void)                        \
    {                                                                         \
        ObjPtr returnValue;                                                   \
                                                                              \
        Self::template newPtr<Self>(returnValue);                             \
                                                                              \
        return returnValue;                                                   \
    }
#define OSG_RC_CREATE_EMPTY_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)        \
        OSG_RC_CREATE_EMPTY_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, BOOST_PP_EMPTY() )
#define OSG_RC_CREATE_EMPTY_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)           \
        OSG_RC_CREATE_EMPTY_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, inline)

#define OSG_RC_CREATE_EMPTY_SPECIALIZED_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)   \
    template < >                                                              \
    OSG_CLASS< OSG_TMPL_PARAM >::ObjPtr                                       \
        OSG_CLASS< OSG_TMPL_PARAM >::createEmpty(void)                        \
    {                                                                         \
        ObjPtr returnValue;                                                   \
                                                                              \
        Self::newPtr<Self>(returnValue);                                      \
                                                                              \
        return returnValue;                                                   \
    }

#define OSG_RC_CREATE_FUNCTIONS_DEF(OSG_CLASS)                                \
    OSG_RC_SHALLOWCOPY_DEF(OSG_CLASS)

#define OSG_RC_CREATE_FUNCTIONS_INL_DEF(OSG_CLASS)                            \
    OSG_RC_CREATE_INL_DEF      (OSG_CLASS)                                    \
    OSG_RC_CREATE_EMPTY_INL_DEF(OSG_CLASS)

#define OSG_RC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)       \
    OSG_RC_CREATE_INL_TMPL_DEF      (OSG_CLASS, OSG_TMPL_PARAM)               \
    OSG_RC_CREATE_EMPTY_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)

#define OSG_RC_CREATE_FUNCTIONS_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)    \
    OSG_RC_CREATE_NONINL_TMPL_DEF      (OSG_CLASS, OSG_TMPL_PARAM)            \
    OSG_RC_CREATE_EMPTY_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)


/*-------------------------- get size decl ----------------------------------*/

#define OSG_RC_GET_SIZE_DECL                                                  \
    virtual OSG::UInt32 getContainerSize(void) const

#define OSG_RC_SIZE_FUNCTIONS_DECL                                            \
    OSG_RC_GET_SIZE_DECL

/*-------------------------- get size def -----------------------------------*/

#define OSG_RC_GET_SIZE_DEF(OSG_CLASS)                                        \
    OSG::UInt32 OSG_CLASS::getContainerSize(void) const                       \
    {                                                                         \
        return sizeof(OSG_CLASS);                                             \
    }

#define OSG_RC_GET_SIZE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, INLINE)           \
    template < class OSG_TMPL_PARAM > INLINE                                  \
    OSG::UInt32 OSG_CLASS< OSG_TMPL_PARAM >::getContainerSize(void) const     \
    {                                                                         \
        return sizeof(OSG_CLASS< OSG_TMPL_PARAM >);                           \
    }
#define OSG_RC_GET_SIZE_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)            \
        OSG_RC_GET_SIZE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, BOOST_PP_EMPTY() )
#define OSG_RC_GET_SIZE_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)               \
        OSG_RC_GET_SIZE_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM, inline)

#define OSG_RC_SIZE_FUNCTIONS_DEF(OSG_CLASS)                                  \
    OSG_RC_GET_SIZE_DEF(OSG_CLASS)

#define OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)         \
    OSG_RC_GET_SIZE_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)
#define OSG_RC_SIZE_FUNCTIONS_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)      \
    OSG_RC_GET_SIZE_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)


/*------------------------ decl and def macros ------------------------------*/

#define OSG_FIELD_CONTAINER_DECL                                              \
    OSG_RC_TYPE_FUNCTIONS_DECL;                                               \
    OSG_RC_CREATE_FUNCTIONS_DECL;                                             \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_FIELD_CONTAINER_TMPL_DECL                                         \
    OSG_RC_TYPE_FUNCTIONS_DECL;                                               \
    OSG_RC_CREATE_FUNCTIONS_DECL;                                             \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_FIELD_CONTAINER_DEF(OSG_CLASS)                                    \
    OSG_RC_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                                    \
    OSG_RC_CREATE_FUNCTIONS_DEF(OSG_CLASS)                                    \
    OSG_RC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

#define OSG_FIELD_CONTAINER_INL_DEF(OSG_CLASS)                                \
    OSG_RC_TYPE_FUNCTIONS_INL_DEF  (OSG_CLASS)                                \
    OSG_RC_CREATE_FUNCTIONS_INL_DEF(OSG_CLASS)

#define OSG_FIELD_CONTAINER_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)           \
    OSG_RC_SHALLOWCOPY_INL_TMPL_DEF     (OSG_CLASS, OSG_TMPL_PARAM)           \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_CLASS, OSG_TMPL_PARAM)           \
    OSG_RC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)

#define OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)        \
    OSG_RC_SHALLOWCOPY_NONINL_TMPL_DEF     (OSG_CLASS, OSG_TMPL_PARAM)        \
    OSG_RC_SIZE_FUNCTIONS_NONINL_TMPL_DEF  (OSG_CLASS, OSG_TMPL_PARAM)        \
    OSG_RC_CREATE_FUNCTIONS_NONINL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)

// This method looks like a duplicate.  If the define works below, we should
// remove it and just use the one above.
/*
#define OSG_FIELD_CONTAINER_TMPL_NO_TYPE_DEF(OSG_CLASS, OSG_TMPL_PARAM)       \
    OSG_RC_SHALLOWCOPY_INL_TMPL_DEF     (OSG_CLASS, OSG_TMPL_PARAM)           \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_CLASS, OSG_TMPL_PARAM)           \
    OSG_RC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)
*/
#define OSG_FIELD_CONTAINER_TMPL_NO_TYPE_DEF(OSG_CLASS, OSG_TMPL_PARAM)       \
        OSG_FIELD_CONTAINER_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)

/*--------------------- abstr decl and def macros --------------------------*/

#define OSG_ABSTR_FIELD_CONTAINER_DECL                                        \
    OSG_RC_TYPE_FUNCTIONS_DECL;                                               \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_FIELD_CONTAINER_DEF(OSG_CLASS)                              \
    OSG_RC_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                                    \
    OSG_RC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

#define OSG_ABSTR_FIELD_CONTAINER_INL_DEF(OSG_CLASS)                          \
    OSG_RC_TYPE_FUNCTIONS_INL_DEF  (OSG_CLASS)

#define OSG_ABSTR_FIELD_CONTAINER_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)         \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF    (OSG_CLASS, OSG_TMPL_PARAM)           \


#ifndef WIN32
#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)
#else
#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)
#endif

#endif /* _OSGCONTAINERDEFINES_H_ */
