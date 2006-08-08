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

#ifndef _OSGNFIOGENERIC_H_
#define _OSGNFIOGENERIC_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNFIOBase.h"

OSG_BEGIN_NAMESPACE

/* \brief NFIOGeneric class.
          reads and writes a fieldcontainer.
*/

class NFIOGeneric : public NFIOBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    NFIOGeneric                     (void);
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~NFIOGeneric            (void);

    static const UInt8 FCPtrUnknown;
    static const UInt8 FCPtrFieldContainer;
    static const UInt8 FCPtrNode;
    static const UInt8 FCPtrNodeCore;
    static const UInt8 FCPtrAttachment;
    static const UInt8 FCPtrMaterial;
    static const UInt8 FCPtrStateChunk;

    static UInt8             getFCPtrType       (const FieldContainerPtr &fc);
    static FieldContainerPtr createFCReplacement(UInt8 fcPtrType            );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Read/Write                                */
    /*! \{                                                                 */

    virtual FieldContainerPtr readFC    (const std::string &typeName);
    virtual void              writeFC   (const FieldContainerPtr &fc);

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/
private:

    static NFIOGeneric _the;

};

OSG_END_NAMESPACE

#define OSGNFIOATEST_HEADER_CVSID "@(#)$Id: OSGNFIOGeneric.h,v 1.1.2.2 2005/09/21 16:19:23 a-m-z Exp $"

#endif /* _OSGNFIOGENERIC_H_ */
