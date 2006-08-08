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

#ifndef _OSGNFIOQUANTIZER_H_
#define _OSGNFIOQUANTIZER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/* \brief Quantizer class.
          quantize reals into 8, 16, or 24 bit integers.
          round then left-reconstruct
*/

class Quantizer
{
    /*==========================  PUBLIC  =================================*/
public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */
    
    Quantizer(Real32 input_min, Real32 input_max, UInt8 res);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Encode/Decode                               */
    /*! \{                                                                 */

    UInt32 encode(Real32 input);
    Real32 decode(UInt32 encoded_value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Constants                                 */
    /*! \{                                                                 */

    static const UInt8 QRES_OFF;
    static const UInt8 QRES_8BIT;
    static const UInt8 QRES_16BIT;
    static const UInt8 QRES_24BIT;

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/

private:
    
    Real32 normalize_input(Real32 input, Real32 input_min,
                           Real32 input_scale);

    Real32 _input_min, _input_max;
    UInt32 _resolution;
    Real32 _interval_size;
    Real32 _input_scale;
};

OSG_END_NAMESPACE

#define OSGNFIOQUANTIZER_HEADER_CVSID "@(#)$Id: OSGNFIOQuantizer.h,v 1.1.2.2 2005/10/04 08:40:21 vossg Exp $"

#endif /* _OSGNFIOQUANTIZER_H_ */
