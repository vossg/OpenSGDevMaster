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

#ifndef _SELECTION_H_
#define _SELECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#ifdef WIN32
#include <windows.h>
#else
#include <sys/types.h>
#endif

#include <string>
#include "OSGBaseDef.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------
class Socket;

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
*/

class OSG_BASE_DLLMAPPING SocketSelection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SocketSelection();
    SocketSelection(const SocketSelection &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~SocketSelection();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   SocketSelection functions                  */
    /*! \{                                                                 */

    void clear     (void                                );
    void clearRead (const Socket &soc                   );
    void clearWrite(const Socket &soc                   );
    void setRead   (const Socket &soc                   );
    void setWrite  (const Socket &soc                   );
    bool isSetRead (const Socket &soc                   );
    bool isSetWrite(const Socket &soc                   );
    int  select    (double time                         );
    int  select    (double time,SocketSelection &result ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   assignment                                 */
    /*! \{                                                                 */

	const SocketSelection & operator =(const SocketSelection &source);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

#ifdef WIN32
    struct fd_set *_fdSetRead;
    struct fd_set *_fdSetWrite;
#else
    fd_set *_fdSetRead;
    fd_set *_fdSetWrite;
#endif

    /*==========================  PRIVATE  ================================*/
};

OSG_END_NAMESPACE

#endif

