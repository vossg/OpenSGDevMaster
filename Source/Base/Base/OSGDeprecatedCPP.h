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

#ifndef _OSGDEPRECATEDCPP_H_
#define _OSGDEPRECATEDCPP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifdef __GNUC__

//#  if __GNUC__ >= 4 || __GNUC_MINOR__ >= 3
//#    include "unordered_set"
//#    define OSG_HASH_SET(TYPE) ::unordered_set< TYPE >
//#  else
#    ifdef OSG_STL_HAS_HASH_MAP
#      ifdef OSG_HASH_MAP_AS_EXT
#        ifdef  __DEPRECATED
#          undef  __DEPRECATED
#          define OSG_DEPRECATED_ACTIVE
#        endif
#        include <ext/hash_set>
#        include <ext/hash_map>
#        ifdef OSG_DEPRECATE_ACTIVE
#          define __DEPRECATED
#          undef OSG_DEPRECATE_ACTIVE
#        endif
#      else
#        include <hash_set>
#        include <hash_map>
#      endif
#      define OSG_HASH_SET(TYPE) OSG_STDEXTENSION_NAMESPACE::hash_set< TYPE >
#      define OSG_HASH_MAP(TYPE_K, TYPE_V)                                   \
                        OSG_STDEXTENSION_NAMESPACE::hash_map< TYPE_K, TYPE_V >
#      define OSG_HASH_MAP_CMP(TYPE_K, TYPE_V, CMP)                          \
                   OSG_STDEXTENSION_NAMESPACE::hash_map< TYPE_K, TYPE_V, CMP >
#    else
#      include <set>
#      include <map>
#      define OSG_HASH_SET(TYPE)           std::set< TYPE >
#      define OSG_HASH_MAP(TYPE_K, TYPE_V) std::map< TYPE_K, TYPE_V >
#      define OSG_HASH_MAP_CMP(TYPE_K, TYPE_V, CMP)                     \
                                          std::map< TYPE_K, TYPE_V, CMP >
#    endif
//#  endif

#else

#  ifdef OSG_STL_HAS_HASH_MAP
#    ifdef OSG_HASH_MAP_AS_EXT
#      include <ext/hash_set>
#      include <ext/hash_map>
#    else
#      include <hash_set>
#      include <hash_map>
#    endif
#    define OSG_HASH_SET(TYPE) OSG_STDEXTENSION_NAMESPACE::hash_set< TYPE >
#    define OSG_HASH_MAP(TYPE_K, TYPE_V)                                     \
                   OSG_STDEXTENSION_NAMESPACE::hash_map< TYPE_K, TYPE_V >
#    define OSG_HASH_MAP_CMP(TYPE_K, TYPE_V, CMP)                            \
                   OSG_STDEXTENSION_NAMESPACE::hash_map< TYPE_K, TYPE_V, CMP >
#  else
#    include <set>
#    include <map>
#    define OSG_HASH_SET(TYPE)           std::set< TYPE >
#    define OSG_HASH_MAP(TYPE_K, TYPE_V) std::map< TYPE_K, TYPE_V >
#    define OSG_HASH_MAP_CMP(TYPE_K, TYPE_V, CMP) \
                                          std::map< TYPE_K, TYPE_V, CMP >
#  endif

#endif

#endif


