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

#ifndef _OSGVECFIELDTRAITS_H_
#define _OSGVECFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGVecFieldTraits.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/
#endif


#undef defineTrait
#undef doDefineTrait

#define doDefineTrait(base, dim, type)                                      \
template <>                                                                 \
struct FieldTraits<base##dim##type> :                                       \
    public FieldTraitsVec##dim##TemplateBase<base##dim##type>               \
{                                                                           \
  private:                                                                  \
                                                                            \
    static  DataType            _type;                                      \
                                                                            \
  public:                                                                   \
                                                                            \
    typedef FieldTraits<base##dim##type>  Self;                             \
                                                                            \
                                                                            \
    enum             { Convertible = (Self::ToStreamConvertible  |          \
                                      Self::FromStringConvertible)     };   \
                                                                            \
    enum             { bHasParent        = 0x01                        };   \
                                                                            \
    static OSG_BASE_DLLMAPPING                                              \
           DataType &getType      (void);                                   \
                                                                            \
    static Char8    *getSName     (void) { return "SF"#base #dim #type; }   \
    static Char8    *getMName     (void) { return "MF"#base #dim #type; }   \
                                                                            \
    static base##dim##type getDefault (void) { return base##dim##type();}   \
}





/*! \ingroup GrpBaseFieldTraits
 */

#if !defined(OSG_DOC_DEV_TRAITS)

#define defineTrait(base, dim, type)                        \
/*! \hideinhierarchy */                                     \
doDefineTrait(base, dim, type);                             \
/*! \class  FieldTraitsTemplateBase<base##dim##type> */     \
/*! \hideinhierarchy                        */

#else

#define defineTrait(base, dim, type) \
doDefineTrait(base, dim, type)

#endif

// Filler Macros
#undef  defineBTrait
#define defineBTrait(dim, type)         \
defineTrait(Vec, dim, type)             \
defineTrait(Pnt, dim, type)

#undef  defineDTrait
#define defineDTrait(type)              \
defineBTrait(1, type)                   \
defineBTrait(2, type)                   \
defineBTrait(3, type)                   \
defineBTrait(4, type)


// Actual Instantiations

defineDTrait(ub)
#ifndef OSG_NO_INT8_PNT
defineDTrait( b)
#endif
defineDTrait(us)
defineDTrait( s)
defineDTrait( f)
defineDTrait( d)
defineDTrait(ld)

defineDTrait(fx) 

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGVECFIELDTRAITS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGVECFIELDTRAITS_H_ */
