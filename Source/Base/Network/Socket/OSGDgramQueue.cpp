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

#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <algorithm>
#include <set>

#include "OSGConfig.h"
#include "OSGBaseThread.h"
#include "OSGThreadManager.h"
#include "OSGSocketSelection.h"
#include "OSGDgramQueue.h"

OSG_USING_NAMESPACE

/** \class osg::DgramQueue
 *  \ingroup GrpBaseNetwork
 *  \brief Stream socket connection
 *
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 *  size must be 2^x
 */

DgramQueue::DgramQueue():
    _queue(),
    _waiting(false)
{
    char barrierName[256];
    sprintf(barrierName,"DgramQueue%p",this);

    // create barrier
    _barrier = Barrier::get(barrierName);
}

/*! Destructor
 */
DgramQueue::~DgramQueue()
{
}

/*-------------------------------------------------------------------------*/
/*                           put / get                                     */

/*! put a dgram to the queue. 
 */
void DgramQueue::put( Dgram *dgram )
{
    _queue.push_back(dgram);
    if(_waiting)
    {
        _waiting = false;
        _barrier->enter(2);
    }
}

/*! get a dgram from the queue. Block if queue is empty
 */
Dgram *DgramQueue::get( Lock *lock )
{
    Dgram *result;

    if(_queue.empty())
    {
        _waiting = true;
        lock->release();
        _barrier->enter(2);
        lock->acquire();
    }
    result = _queue.front();
    _queue.pop_front();

    return result;
}

/*! wait for a dgram but dont read
 */
void DgramQueue::wait( Lock *lock )
{
    if(_queue.empty())
    {
        _waiting = true;
        lock->release();
        _barrier->enter(2);
        lock->acquire();
    }
}

/*! true, if reader is waiting
 */
bool DgramQueue::waiting(void)
{
    return _waiting;
}

bool DgramQueue::empty(void)
{
    return _queue.empty();
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id:$";
    static Char8 cvsid_hpp[] = OSG_DGRAMQUEUEHEADER_CVSID;
}
