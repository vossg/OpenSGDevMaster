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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGMPBase.h"
#include "OSGTypeFactory.h"
#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::MPType
 */

MPType::MPType(const Char8  *szName, 
               const Char8  *szParentName,
               const UInt32  uiNamespace ) :
    Inherited(szName, 
              szParentName, 
              uiNamespace )
{
}


MPType::~MPType(void)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::MPThreadType
 */

UInt32 MPThreadType::_uiThreadCount = 0;


MPThreadType::MPThreadType(const Char8          *szName, 
                           const Char8          *szParentName,
                                 CreateThreadF   fCreateThread,
                                 InitThreadingF  fInitThreading,
                           const UInt32          uiNamespace   ) :
     Inherited    (szName, szParentName, uiNamespace),
    _fCreateThread(fCreateThread                    )
{
    ThreadManager::the()->registerThreadType(this);

    if(fInitThreading != NULL)
        fInitThreading();
}


MPThreadType::~MPThreadType(void)
{
}


BaseThread *MPThreadType::create(const Char8 *szName)
{
    Char8      *szTmp;
    UInt32      uiNewId     = _uiThreadCount++;
    BaseThread *returnValue = NULL;

    if(szName == NULL)
    {
        szTmp = new Char8[16];
        sprintf(szTmp, "OSGThread_%u", uiNewId);
    }
    else
    {
        szTmp = const_cast<Char8 *>(szName);
    }

    if(_fCreateThread != NULL)
        returnValue =  _fCreateThread(szTmp, uiNewId);

    if(szTmp != szName)
        delete [] szTmp;

    return returnValue;
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::MPCondVarType
 */

UInt32 MPCondVarType::_uiCondVarCount = 0;


MPCondVarType::MPCondVarType(const Char8       *szName, 
                             const Char8       *szParentName,
                             CreateCondVarF     fCreateCondVar,
                             const UInt32       uiNamespace ) :
     Inherited  (szName, szParentName, uiNamespace),
    _fCreateCondVar(fCreateCondVar                      )
{
    ThreadManager::the()->registerCondVarType(this);
}


MPCondVarType::~MPCondVarType(void)
{
}


CondVar *MPCondVarType::create(const Char8 *szName)
{
    Char8   *szTmp;
    UInt32   uiNewId     = _uiCondVarCount++;
    CondVar *returnValue = NULL;

    if(szName == NULL)
    {
        szTmp = new Char8[16];
        sprintf(szTmp, "OSGCondVar_%u", uiNewId);
    }
    else
    {
        szTmp = const_cast<Char8 *>(szName);
    }

    if(_fCreateCondVar != NULL)
        returnValue = _fCreateCondVar(szTmp, uiNewId);

    if(szTmp != szName)
        delete [] szTmp;

    return returnValue;
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::MPBarrierType
 */

UInt32 MPBarrierType::_uiBarrierCount = 0;


MPBarrierType::MPBarrierType(const Char8          *szName, 
                             const Char8          *szParentName,
                                   CreateBarrierF  fCreateBarrier,
                             const UInt32          uiNamespace   ) :
     Inherited     (szName, szParentName, uiNamespace),
    _fCreateBarrier(fCreateBarrier                   )
{
    ThreadManager::the()->registerBarrierType(this);
}


MPBarrierType::~MPBarrierType(void)
{
}


Barrier *MPBarrierType::create(const Char8 *szName)
{
    Char8   *szTmp;
    UInt32   uiNewId     = _uiBarrierCount++;
    Barrier *returnValue = NULL;

    if(szName == NULL)
    {
        szTmp = new Char8[16];
        sprintf(szTmp, "OSGBarrier_%u", uiNewId);
    }
    else
    {
        szTmp = const_cast<Char8 *>(szName);
    }

    if(_fCreateBarrier != NULL)
        returnValue =  _fCreateBarrier(szTmp, uiNewId);

    if(szTmp != szName)
        delete [] szTmp;

    return returnValue;
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::MPLockType
 */

UInt32 MPLockType::_uiLockCount = 0;


MPLockType::MPLockType(const Char8       *szName, 
                       const Char8       *szParentName,
                             CreateLockF  fCreateLock,
                       const UInt32       uiNamespace ) :
     Inherited  (szName, szParentName, uiNamespace),
    _fCreateLock(fCreateLock                      )
{
    ThreadManager::the()->registerLockType(this);
}


MPLockType::~MPLockType(void)
{
}


Lock *MPLockType::create(const Char8 *szName)
{
    Char8   *szTmp;
    UInt32  uiNewId     = _uiLockCount++;
    Lock   *returnValue = NULL;

    if(szName == NULL)
    {
        szTmp = new Char8[16];
        sprintf(szTmp, "OSGLock_%u", uiNewId);
    }
    else
    {
        szTmp = const_cast<Char8 *>(szName);
    }

    if(_fCreateLock != NULL)
        returnValue = _fCreateLock(szTmp, uiNewId);

    if(szTmp != szName)
        delete [] szTmp;

    return returnValue;
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::MPLockPoolType
 */

UInt32 MPLockPoolType::_uiLockPoolCount = 0;


MPLockPoolType::MPLockPoolType(
    const Char8           *szName, 
    const Char8           *szParentName,
          CreateLockPoolF  fCreateLockPool,
    const UInt32           uiNamespace    ) :

     Inherited      (szName, szParentName, uiNamespace),
    _fCreateLockPool(fCreateLockPool                  )
{
    ThreadManager::the()->registerLockPoolType(this);
}


MPLockPoolType::~MPLockPoolType(void)
{
}


LockPool *MPLockPoolType::create(const Char8 *szName)
{
    Char8    *szTmp;
    UInt32    uiNewId     = _uiLockPoolCount++;
    LockPool *returnValue = NULL;

    if(szName == NULL)
    {
        szTmp = new Char8[16];
        sprintf(szTmp, "OSGThread_%u", uiNewId);
    }
    else
    {
        szTmp = const_cast<Char8 *>(szName);
    }

    if(_fCreateLockPool != NULL)
        returnValue =  _fCreateLockPool(szTmp, uiNewId);

    if(szTmp != szName)
        delete [] szTmp;

    return returnValue;
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::MPBase
 */

MPType MPBase::_type("OSGMPBase", NULL);


const MPType &MPBase::getStaticType(void)
{
    return _type;
}


UInt32 MPBase::getStaticTypeId(void)
{
    return 0;
}


MPType &MPBase::getType(void)
{
    return _type;
}


const MPType &MPBase::getType(void) const
{
    return _type;
}


UInt32 MPBase::getTypeId(void)
{
    return getType().getId();
}


const Char8 *MPBase::getCName(void) const
{
    return _szName;
}


MPBase::MPBase(const Char8 *szName) :
     Inherited(    ),
    
    _szName   (NULL)
{
    osgStringDup(szName, _szName);
}


MPBase::~MPBase(void)
{
    delete [] _szName;
}

