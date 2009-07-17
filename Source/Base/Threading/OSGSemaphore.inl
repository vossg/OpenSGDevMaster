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

#if defined (OSG_USE_PTHREADS)

/*------------------------------- Semaphore --------------------------------*/

inline
void PThreadSemaphoreBase::wait(void)
{
    sem_wait(&(_pLowLevelSemaphore));
}

inline
void PThreadSemaphoreBase::post(void)
{
    sem_post(&(_pLowLevelSemaphore));
}

#endif /* OSG_USE_PTHREADS */


#if defined (OSG_USE_SPROC)

/*----------------------------- Semaphore-----------------------------------*/

inline
void SprocSemaphoreBase::wait(void)
{
    if(_pLowLevelSema != NULL)
        uspsema(_pLowLevelSema);
}

inline
void SprocSemaphoreBase::post(void)
{
    if(_pLowLevelSema != NULL)
        usvsema(_pLowLevelSema);
}

#endif /* OSG_USE_SPROC */


#if defined (OSG_USE_WINTHREADS)

/*------------------------------- Semaphore --------------------------------*/

inline
void WinThreadSemaphoreBase::wait(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "Semaphore::acquire %p\n", this);
#endif

    WaitForSingleObject(_pSemaphore, INFINITE);
}

inline
void WinThreadSemaphoreBase::post(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "Semaphore::release %p\n", this);
#endif

    ReleaseSemaphore(_pSemaphore, 1, NULL);
}

#endif /* OSG_USE_WINTHREADS */




inline
Semaphore *Semaphore::create(void)
{
    return Semaphore::get(NULL);
}

inline
const MPSemaphoreType &Semaphore::getClassType(void)
{
    return _type;
}

/*----------------------------- Semaphore ----------------------------------*/

inline
void Semaphore::wait(void)
{
    Inherited::wait();
}

inline
void Semaphore::post(void)
{
    Inherited::post();
}

OSG_END_NAMESPACE
