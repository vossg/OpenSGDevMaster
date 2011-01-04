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

/*! \brief Quantizer class.
          quantize reals into 8, 16, or 24 bit integers.
          round then left-reconstruct

    \ingroup GrpFileIOOSB
    \nohierarchy
*/

class Quantizer
{
    /*==========================  PUBLIC  =================================*/
  public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */
    
    Quantizer(Real32 inputMin, Real32 inputMax, UInt8 res);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Encode/Decode                               */
    /*! \{                                                                 */

    UInt32 encode(Real32 input       );
    Real32 decode(UInt32 encodedValue);

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
    
    Real32 normalizeInput(Real32 input, Real32 inputMin, Real32 inputScale);

    Real32 _inputMin;
    Real32 _inputMax;
    UInt32 _resolution;
    Real32 _intervalSize;
    Real32 _inputScale;
};

OSG_END_NAMESPACE

#endif /* _OSGNFIOQUANTIZER_H_ */
