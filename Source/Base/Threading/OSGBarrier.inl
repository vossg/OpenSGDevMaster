/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

OSG_BEGIN_NAMESPACE

inline
void BarrierCommonBase::setNumWaitFor(UInt32 uiNumWaitFor)
{
    _uiNumWaitFor = uiNumWaitFor;
}


#if defined (OSG_USE_PTHREADS)

/*------------------------------- Enter -----------------------------------*/

inline
void PThreadBarrierBase::enter(void)
{
    if(_uiNumWaitFor <= 1)
        return;

    pthread_mutex_lock(&(_pLockOne));

    _uiCount++;

    if(_uiCount < _uiNumWaitFor)
    {
        /* not enough threads are waiting => wait */

        pthread_cond_wait(&(_pWakeupCondition[_uiCurrentCond]), &(_pLockOne));
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads
        */

        pthread_cond_broadcast(&(_pWakeupCondition[_uiCurrentCond]));

        _uiCount       = 0;
        _uiCurrentCond = 1 - _uiCurrentCond;
    }

    pthread_mutex_unlock(&(_pLockOne));
}

inline
void PThreadBarrierBase::enter(UInt32 uiNumWaitFor)
{
    _uiNumWaitFor = uiNumWaitFor;

    enter();
}

#endif /* OSG_USE_PTHREADS */



#if defined (OSG_USE_SPROC)

/*------------------------------ Enter ------------------------------------*/

inline
void SprocBarrierBase::enter(void)
{
    if(_pBarrier != NULL)
        barrier(_pBarrier, _uiNumWaitFor);
}

inline
void SprocBarrierBase::enter(UInt32 uiNumWaitFor)
{
    _uiNumWaitFor = uiNumWaitFor;

    enter();
}

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

/*------------------------------ Enter ------------------------------------*/

inline
void WinThreadBarrierBase::enter(void)
{
	WaitForSingleObject(_pMutex1, INFINITE);

	++_uiNumWaiters;

	if(_uiNumWaiters == _uiNumWaitFor) 
	{
		--_uiNumWaiters;

		ReleaseMutex(_pMutex1);

		ReleaseSemaphore(_pBarrierSema, _uiNumWaitFor - 1, NULL);

		return;
	}
	else
	{
		ReleaseMutex(_pMutex1);

		WaitForSingleObject(_pBarrierSema, INFINITE);
		
		WaitForSingleObject(_pMutex1, INFINITE);

		--_uiNumWaiters;

		ReleaseMutex(_pMutex1);
	}
}

inline
void WinThreadBarrierBase::enter(UInt32 uiNumWaitFor)
{
    _uiNumWaitFor = uiNumWaitFor;

    enter();
}

#endif /* OSG_USE_WINTHREADS */

inline
Barrier *Barrier::create(void)
{
    return Barrier::get(NULL);
}

inline
const MPBarrierType &Barrier::getClassType(void)
{
    return _type;
}

/*------------------------------- Enter -----------------------------------*/


inline
void Barrier::setNumWaitFor(UInt32 uiNumWaitFor)
{
    Inherited::setNumWaitFor(uiNumWaitFor);
}


inline
void Barrier::enter(void)
{
    Inherited::enter();
}

inline
void Barrier::enter(UInt32 uiNumWaitFor)
{
    Inherited::enter(uiNumWaitFor);
}


OSG_END_NAMESPACE
