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

#ifndef _OSGSYSMFIELDS_H_
#define _OSGSYSMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGSysFieldTraits.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldMulti
    \warning the getValue and operator[] functions may not return what
             you expect them to return. Descent STL implementation will 
             certainly not return 'bool &' nor 'const bool &'.
 */

typedef MField<bool, 2>   MFBool;

#if 0
#if ! defined(OSG_WIN32_CL)             || \
      defined(OSG_WITH_STLPORT)         || \
      defined(OSG_NEED_BOOL_MFIELD_SPEZ)
template <> inline
UInt32 MField<bool, 2>::getBinSize(void) const
{
    return sizeof(UInt32) + // num elements
           sizeof(UInt8) * _values.size();
}

template <> inline
void MField<bool, 2>::copyToBin(BinaryDataHandler &pMem) const
{
    UInt32 n = _values.size();

    pMem.putValue(n);

    for(UInt32 i = 0; i < n; ++i)
    {
        UInt8 bval = _values[i];

        pMem.putValue(bval);
    }
}

template <> inline
void MField<bool, 2>::copyFromBin(BinaryDataHandler &pMem)
{
    UInt32 n;
    
     pMem  .getValue(n);
    _values.clear ( );

#ifdef __hpux
    bool tmpVal;

    _values.resize(n, tmpVal);
#else
    _values.resize(n);
#endif

    UInt8 tmpBVal;

    for(UInt32 i = 0; i < n; ++i)
    {
        pMem.getValue(tmpBVal);

        _values[i] = (tmpBVal != 0);
    }
}
#endif
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Int8>   MFInt8;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<UInt8>  MFUInt8;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Int16>  MFInt16;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<UInt16> MFUInt16;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Int32>  MFInt32;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<UInt32> MFUInt32;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Int64>  MFInt64;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<UInt64> MFUInt64;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Real16> MFReal16;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Real32> MFReal32;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Fixed32> MFFixed32;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Real64> MFReal64;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<void *>   MFVoidP;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase  
    \warning the getValue and operator[] functions may not return what
             you expect them to return. Descent STL implementation will 
             certainly not return 'bool &' nor 'const bool &'.
 */
struct MFBool : public MField<bool, 2>   {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFInt8 : public MField<Int8>   {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFUInt8 : public MField<UInt8>  {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFInt16 : public MField<Int16>  {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFUInt16 : public MField<UInt16> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFInt32 : public MField<Int32>  {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFUInt32 : public MField<UInt32> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFInt64 : public MField<Int64>  {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFUInt64 : public MField<UInt64> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFReal16 : public MField<Real16> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFReal32 : public MField<Real32> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFFixed32 : public MField<Fixed32> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFReal64 : public MField<Real64> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVoidP : public MField<void *>   {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSYSMFIELDS_H_ */
