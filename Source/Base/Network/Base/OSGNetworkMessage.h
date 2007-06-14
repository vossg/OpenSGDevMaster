/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSG_NETWORK_MESSAGE_H_
#define _OSG_NETWORK_MESSAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

class OSG_BASE_DLLMAPPING NetworkMessage 
{
    /*==========================  PUBLIC  =================================*/
  public:
    
    /** \class Header
     *  \ingroup GrpBaseNetwork
     *  \brief Header of socket messages
     **/
    struct Header
    {
        UInt32 size;
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NetworkMessage(void);
    NetworkMessage(const NetworkMessage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~NetworkMessage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual UInt32        getSize   (void)=0;
    virtual MemoryHandle  getBuffer (void)=0;
            Header       &getHeader (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void setSize                (UInt32 size)=0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assignment                              */
    /*! \{                                                                 */

    NetworkMessage &operator =(const NetworkMessage &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef NetworkMessage *NetworkMessageP;

OSG_END_NAMESPACE

#endif /* _OSG_NETWORK_MESSAGE_H_ */
