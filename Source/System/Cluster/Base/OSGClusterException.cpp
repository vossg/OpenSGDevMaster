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

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGClusterException.h"

OSG_USING_NAMESPACE

/** \class ClusterException
 *  \ingroup GrpSystemCluster
 *  \brief Indicate cluster exceptions
 **/

/*! Constructor. Add ClusterLib to the error text
 */

ClusterException::ClusterException(void) : Exception()
{
    _what += "ClusterLib: ";
}

/** \class ConnectionClosed
 *  \ingroup GrpSystemCluster
 *  \brief Indicate close of connecitons
 **/

/*! Constructor. Add error text.
 */
ConnectionClosed::ConnectionClosed(void) : ClusterException()
{
    _what += "Connection closed by endpoint. ";
}

/** \class RemoteSyncError
 *  \ingroup GrpSystemCluster
 *  \brief Indicate error in sync data stream
 **/

/*! Constructor. Add error text.
 */
RemoteSyncError::RemoteSyncError(void) : ClusterException()
{
    _what += "Error in synchronisation data stream. ";
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id:$";
    static Char8 cvsid_hpp[] = OSGCLUSTEREXCEPTION_HEADER_CVSID;
}
