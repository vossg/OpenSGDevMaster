/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *                     contact: danielg@iastate.edu                          *
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

#ifndef _OSG_RADIXSORT_H_
#define _OSG_RADIXSORT_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGBaseTypes.h"
#include "OSGSysFields.h"

OSG_BEGIN_NAMESPACE
/**
*   Sorts a vector of floating point values.  After the sort is finished, the 
*   sorted order of indices will be in the indices vector.
*
*   @param size     Number of elements to sort
*   @param floats   Vector of 32-bit floating point numbers to sort
*   @param indices  Vector which will contain the sorted indices, such that 
*                       indices[0] will be the index of the smallest value in floats
*
*/

OSG_UTIL_DLLMAPPING 
void RadixSort(UInt32 size, const MFReal32 &floats, MFUInt32 &indices);

OSG_END_NAMESPACE

#endif //_OSG_RADIXSORT_H_
