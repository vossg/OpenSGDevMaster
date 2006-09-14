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

#ifndef _OSGCOMPILETIMEFUNCTIONS_H_
#define _OSGCOMPILETIMEFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*                   Ccompile Time Functions                           */

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCMax compile time max
    \ingroup GrpBaseBaseCmpTimeFn                                      
 */

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCMax
    \hideinhierarchy
 */

template <Int32 uiValue1, Int32 uiValue2>
struct osgStaticMax
{
    enum _iMax { iMax = uiValue1 < uiValue2 ? uiValue2 : uiValue1 };
};


#if defined(OSG_COMPILER_PART_SPEZ)

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCIFTBased compile time if, type based
    \ingroup GrpBaseBaseCmpTimeFn                                      
 */

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

struct TrueType  {};

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

struct FalseType {};

/*! Compile time if, true case, type based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

template<class IConditionV, class IThenT, class IElseT>
struct osgTypeIF
{
    typedef IThenT _IRet;
    typedef IElseT _IDummyRef;
};

/*! Compile time if, false case, type based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

template<class IThenT, class IElseT>
struct osgTypeIF<FalseType, IThenT, IElseT>
{
    typedef IElseT _IRet;
    typedef IThenT _IDummyRef;
};

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCIFBBased compile time if, bool based
    \ingroup GrpBaseBaseCmpTimeFn                                      
 */

/*! Compile time if, true case, bool based
    \ingroup GrpBaseBaseCmpTimeFn                  
    \ingroup GrpCIFBBased                                      
    \hideinhierarchy
 */

template<bool IConditionV, class IThenT, class IElseT>
struct osgIF
{
    typedef IThenT _IRet;
    typedef IElseT _IDummyRef;
};

/*! Compile time if, false case, bool based
    \ingroup GrpBaseBaseCmpTimeFn                  
    \ingroup GrpCIFBBased
    \hideinhierarchy
 */

template<class IThenT, class IElseT>
struct osgIF<false, IThenT, IElseT>
{
    typedef IElseT _IRet;
    typedef IThenT _IDummyRef;
};

/*---------------------------------------------------------------------*/

#else

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCIFBBased compile time if, bool based
    \ingroup GrpBaseBaseCmpTimeFn                                      
 */

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
 */

template <bool IConditionV>
struct osgIFGen
{
    template<class IThenT, class IElseT>
    struct osgIFSwitch
    {
        typedef IThenT _IRet;
        typedef IElseT _IDummyRef;
    };
};

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
 */

template <>
struct osgIFGen<false>
{
    template<class IThenT, class IElseT>
    struct osgIFSwitch
    {
        typedef IElseT _IRet;
        typedef IThenT _IDummyRef;
    };
};

/*! Compile time if, bool based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
 */

template<bool IConditionV, class IThenT, class IElseT>
struct osgIF
{
    typedef typename osgIFGen<IConditionV>::osgIFSwitch<IThenT, 
                                                        IElseT>::_IRet _IRet;
};

#endif

template <class T>
struct isPtr
{
    static const bool result = false;
};

template <class T>
struct isPtr<T *>
{
    static const bool result = true;
};

OSG_END_NAMESPACE

#define OSGCOMPILETIMEFUNCTIONS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGCOMPILETIMEFUNCTIONS_H_ */
