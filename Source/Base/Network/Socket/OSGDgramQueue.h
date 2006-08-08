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

#ifndef _DGRAMQUEUE_H_
#define _DGRAMQUEUE_H_
#ifdef __sgi
#pragma once
#endif

#include <list>

#include "OSGBaseTypes.h"
#include "OSGTime.h"
#include "OSGBaseDef.h"
#include "OSGConnection.h"
#include "OSGDgramSocket.h"
#include "OSGSocketAddress.h"
#include "OSGConnectionType.h"
#include "OSGDgram.h"

OSG_BEGIN_NAMESPACE

class BaseThread;

class OSG_BASE_DLLMAPPING DgramQueue 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef std::list<Dgram*>          QueueT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    DgramQueue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DgramQueue(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               data put,get                                   */
    /*! \{                                                                 */

    void   put    (Dgram *dgram);
    Dgram *get    (Lock  *lock );
    bool   empty  (void        );
    void   wait   (Lock  *lock );
    bool   waiting(void        );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
  
    /*---------------------------------------------------------------------*/
    /*! \name               member                                         */
    /*! \{                                                                 */

    Barrier   *_barrier;
    QueueT     _queue;
    bool       _waiting;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

	/*!\brief prohibit default function (move to 'public' if needed) */
    DgramQueue(const DgramQueue &source);
    void operator =(const DgramQueue &source);
};

// class pointer
typedef DgramQueue *DgramQueueP;

OSG_END_NAMESPACE

#define OSG_DGRAMQUEUEHEADER_CVSID "@(#)$Id:$"

#endif /* _DGRAMQUEUE_H_ */
