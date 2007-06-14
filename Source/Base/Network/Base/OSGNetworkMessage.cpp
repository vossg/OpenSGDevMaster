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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGNetworkMessage.h"

OSG_USING_NAMESPACE

/** \class OSG::NetworkMessage
 *  \ingroup GrpBaseNetwork
 *  \brief Abstract socket message buffer
 *
 * This is the base class for socket messages. It provides an Interface
 * for transmission of data buffers.
 * 
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 */
NetworkMessage::NetworkMessage(void)
{
}

/*! copy Constructor
 */
NetworkMessage::NetworkMessage(const NetworkMessage &)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor
 */
NetworkMessage::~NetworkMessage(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
NetworkMessage& NetworkMessage::operator = (const NetworkMessage &)
{
    return *this;
}

/*! Get message header. A pointer to the first byte of the message is
    returned
 */
NetworkMessage::Header &NetworkMessage::getHeader (void)
{
    return *((Header*)(getBuffer()));
}

