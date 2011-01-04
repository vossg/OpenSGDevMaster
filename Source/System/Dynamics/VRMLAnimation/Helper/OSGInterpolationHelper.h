/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifndef _OSGINTERPOLATIONHELPER_H_
#define _OSGINTERPOLATIONHELPER_H_

#include "OSGBaseTypes.h"
#include "OSGMathFields.h"
#include "OSGVecFields.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpDynamicsVRMLAnimationObj
    \nohierarchy
 */

template<class KeyFieldT, class KeyValueFieldT, class ValueFieldT>
struct InterpolationHelper
{
  public:


    static void copyFirstValue(const KeyFieldT      &mfKeys,
                               const KeyValueFieldT &mfKeyValues,
                                     ValueFieldT    &fValue     );

    static void copyLastValue (const KeyFieldT      &mfKeys,
                               const KeyValueFieldT &mfKeyValues,
                                     ValueFieldT    &fValue     );

    static void lerp          (const UInt32          uiStopIndex,
                               const UInt32          uiStartIndex,
                               const Real32          rFraction,
                               const KeyFieldT      &mfKeys,
                               const KeyValueFieldT &mfKeyValues,
                                     ValueFieldT    &fValue     );

    static void interpolate   (const Real32          rFraction,
                               const KeyFieldT      &mfKeys,
                               const KeyValueFieldT &mfKeyValues,
                                     ValueFieldT    &fValue     );
     


    template<class ResortIndexTypeT> 
    static void resortKeyValues(      UInt32            uiNumKeys,
                                      UInt32            uiValuesPerKey,
                                      KeyValueFieldT   &mfKeyValues,
                                const ResortIndexTypeT &mfResortIndex);
};


OSG_END_NAMESPACE

#include "OSGInterpolationHelper.inl"

#endif
