/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include "OSGConfig.h"
#include "OSGNFIOQuantizer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Quantizer
           quantize reals into 8, 16, or 24 bit integers.
           round then left-reconstruct
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt8 Quantizer::QRES_OFF   = 0;
const UInt8 Quantizer::QRES_8BIT  = 1;
const UInt8 Quantizer::QRES_16BIT = 2;
const UInt8 Quantizer::QRES_24BIT = 3;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

Quantizer::Quantizer(Real32 inputMin, Real32 inputMax, UInt8 res)
{
    _inputMin = inputMin;
    _inputMax = inputMax;

    switch(res)
    {
        case Quantizer::QRES_8BIT:
            _resolution = 0x100;
        break;
        case Quantizer::QRES_16BIT:
            _resolution = 0x10000;
        break;
        case Quantizer::QRES_24BIT:
            _resolution = 0x1000000;
        break;
    }

#if 1
    // RL
    _inputScale   = 1.0f / (_inputMax - _inputMin);
    _intervalSize = 1.0f / Real32(_resolution - 1);
#else
    // TC
    _inputScale   = 1.0f / (_inputMax - _inputMin);
    _intervalSize = 1.0f / Real32(_resolution);
#endif
}

UInt32 Quantizer::encode(Real32 input)
{
#if 1
    // RL
    Real32 normalized = normalizeInput(input, _inputMin, _inputScale);
    UInt32 result     = static_cast<UInt32>((normalized * (_resolution - 1)) + 0.5f);
    if(result > _resolution - 1)
        result = _resolution - 1;
#else
    // TC
    Real32 normalized = normalizeInput(input, _inputMin, _inputScale);
    UInt32 result     = static_cast<UInt32>(normalized * _resolution);
    if (result > _resolution - 1)
        result = _resolution - 1;
#endif
    return result;
}

Real32 Quantizer::decode(UInt32 encodedValue)
{
#if 1
    // RL
    Real32 normalized = encodedValue * _intervalSize;
    return normalized * (_inputMax - _inputMin) + _inputMin;
#else
    // TC
    Real32 normalized = (encodedValue + 0.5f) * _intervalSize;
    return normalized * (_inputMax - _inputMin) + _inputMin;
#endif
}

Real32 Quantizer::normalizeInput(Real32 input, Real32 inputMin, Real32 inputScale)
{
    Real32 normalized = (input - inputMin) * inputScale;
    if (normalized < 0)
        normalized = 0;

    return normalized;
}

