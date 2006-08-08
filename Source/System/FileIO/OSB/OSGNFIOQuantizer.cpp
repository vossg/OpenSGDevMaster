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

#include <OSGConfig.h>
#include "OSGNFIOQuantizer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Quantizer
           quantize reals into 8, 16, or 24 bit integers.
           round then left-reconstruct
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt8 Quantizer::QRES_OFF = 0;
const UInt8 Quantizer::QRES_8BIT = 1;
const UInt8 Quantizer::QRES_16BIT = 2;
const UInt8 Quantizer::QRES_24BIT = 3;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

Quantizer::Quantizer(Real32 input_min, Real32 input_max, UInt8 res)
{
    _input_min = input_min;
    _input_max = input_max;

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
    _input_scale = 1.0f / (_input_max - _input_min);
    _interval_size = 1.0f / (Real32)(_resolution - 1);
#else
    // TC
    _input_scale = 1.0f / (_input_max - _input_min);
    _interval_size = 1.0f / (Real32)(_resolution);
#endif
}

UInt32 Quantizer::encode(Real32 input)
{
#if 1
    // RL
    Real32 normalized = normalize_input(input, _input_min, _input_scale);
    UInt32 result = (UInt32)((normalized * (_resolution - 1)) + 0.5f);
    if(result > _resolution - 1)
        result = _resolution - 1;
#else
    // TC
    Real32 normalized = normalize_input(input, _input_min, _input_scale);
    int result = (UInt32)(normalized * _resolution);
    if (result > _resolution - 1)
        result = _resolution - 1;
#endif
    return result;
}

Real32 Quantizer::decode(UInt32 encoded)
{
#if 1
    // RL
    Real32 normalized = encoded * _interval_size;
    return normalized * (_input_max - _input_min) + _input_min;
#else
    // TC
    Real32 normalized = (encoded + 0.5f) * _interval_size;
    return normalized * (_input_max - _input_min) + _input_min;
#endif
}

Real32 Quantizer::normalize_input(Real32 input, Real32 input_min, Real32 input_scale)
{
    Real32 normalized = (input - input_min) * input_scale;
    if (normalized < 0)
        normalized = 0;

    return normalized;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNFIOQuantizer.cpp,v 1.1.2.1 2005/08/16 16:18:10 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGNFIOQUANTIZER_HEADER_CVSID;
}
