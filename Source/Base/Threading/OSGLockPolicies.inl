/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
NoLockPolicy::NoLockPolicy(void)
{
}


inline
NoLockPolicy::~NoLockPolicy(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Reference Counting                               */

inline
void NoLockPolicy::acquire(void)
{
}

inline
void NoLockPolicy::release(void)
{
}

inline
bool NoLockPolicy::request(void)
{
    return true;
}



/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


inline
SingleLockPolicy::SingleLockPolicy(void) :
    _pLock(NULL)
{
    _pLock = Lock::create();
}


inline
SingleLockPolicy::~SingleLockPolicy(void)
{
    _pLock = NULL;
}

inline
void SingleLockPolicy::acquire(void)
{
    _pLock->acquire();
}

inline
void SingleLockPolicy::release(void)
{
    _pLock->release();
}

inline
bool SingleLockPolicy::request(void)
{
    return _pLock->request();
}



/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


inline
SingleStaticInitLockPolicy::SingleStaticInitLockPolicy(void) :
    _pLock(NULL)
{
    addPreFactoryInitFunction(
        boost::bind(&SingleStaticInitLockPolicy::init, this));

    addPreMPExitFunction(
        boost::bind(&SingleStaticInitLockPolicy::shutdown, this));
}


inline
SingleStaticInitLockPolicy::~SingleStaticInitLockPolicy(void)
{
}

inline
bool SingleStaticInitLockPolicy::init(void)
{
    _pLock = Lock::create();

    return true;
}

inline
bool SingleStaticInitLockPolicy::shutdown(void)
{
    _pLock = NULL;

    return true;
}

inline
void SingleStaticInitLockPolicy::acquire(void)
{
    _pLock->acquire();
}

inline
void SingleStaticInitLockPolicy::release(void)
{
    _pLock->release();
}

inline
bool SingleStaticInitLockPolicy::request(void)
{
    return _pLock->request();
}

OSG_END_NAMESPACE


