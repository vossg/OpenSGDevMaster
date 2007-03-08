/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#include "OSGOSBGeoVectorPropertyElement.h"

#include "OSGNFIOQuantizer.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBGeoVectorPropertyElement                                             */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBGeoVectorPropertyElement::OSBGeoVectorPropertyElement(
    OSBRootElement *root, UInt16 version)
    : Inherited          (root, version      ),
      _quantizeResolution(Quantizer::QRES_OFF)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBGeoVectorPropertyElement::~OSBGeoVectorPropertyElement(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBGeoVectorPropertyElement::setQuantizeResolution(UInt8 res)
{
    _quantizeResolution = res;
}

UInt8
OSBGeoVectorPropertyElement::getQuantizeResolution(void) const
{
    return _quantizeResolution;
}
