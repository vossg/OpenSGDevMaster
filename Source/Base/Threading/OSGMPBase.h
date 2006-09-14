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

#ifndef _OSGMPBASE_H_
#define _OSGMPBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTypeBase.h"
#include "OSGMemoryObject.h"

OSG_BEGIN_NAMESPACE

class MPBase;
class BaseThread;
class Barrier;
class Lock;
class LockPool;

typedef BaseThread *(*CreateThreadF  )(const Char8  *szName,
                                             UInt32  uiId);
typedef Barrier    *(*CreateBarrierF )(const Char8  *szName,
                                             UInt32  uiId);
typedef Lock       *(*CreateLockF    )(const Char8  *szName,
                                             UInt32  uiId);
typedef LockPool   *(*CreateLockPoolF)(const Char8  *szName,
                                             UInt32  uiId);
typedef void        (*InitThreadingF) (void);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING MPType : public TypeBase
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPType(const Char8  *szName, 
           const Char8  *szParentName,
           const UInt32  uiNamespace = GlobalNamespace);
                 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
             
    virtual ~MPType(void); 
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    typedef TypeBase Inherited;

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MPType(const MPType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MPType &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING MPThreadType : public MPType
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPThreadType(const Char8         *szName, 
                 const Char8         *szParentName,
                       CreateThreadF  fCreateThread,
                       InitThreadingF fInitThreading,
                 const UInt32         uiNamespace   = GlobalNamespace);
                       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MPThreadType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    BaseThread *create(const Char8 *szName);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPType Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
 
    static UInt32        _uiThreadCount;
           CreateThreadF _fCreateThread;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MPThreadType(const MPThreadType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MPThreadType &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING MPBarrierType : public MPType
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPBarrierType(const Char8          *szName, 
                  const Char8          *szParentName,
                        CreateBarrierF  fCreateBarrier,
                  const UInt32          uiNamespace   = GlobalNamespace);
                        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
                    
    virtual ~MPBarrierType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    Barrier *create(const Char8 *szName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPType Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                       Class Specific                         */
    /*! \{                                                                 */

    static UInt32         _uiBarrierCount;
           CreateBarrierF _fCreateBarrier;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MPBarrierType(const MPBarrierType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MPBarrierType &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING MPLockType : public MPType
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPLockType(const Char8       *szName, 
               const Char8       *szParentName,
                     CreateLockF  fCreateLock,
               const UInt32       uiNamespace = GlobalNamespace);
                     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
                 
    virtual ~MPLockType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    Lock *create(const Char8 *szName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef MPType Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                  Class Specific                              */
    /*! \{                                                                 */

    static UInt32       _uiLockCount;
           CreateLockF  _fCreateLock;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MPLockType(const MPLockType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MPLockType &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! \ingroup GrpBaseBaseMultiThreading

class OSG_BASE_DLLMAPPING MPLockPoolType : public MPType
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPLockPoolType(const Char8           *szName, 
                   const Char8           *szParentName,
                         CreateLockPoolF  fCreateLockPool,
                   const UInt32           uiNamespace    = GlobalNamespace);
                         
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MPLockPoolType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Construction                              */
    /*! \{                                                                 */

    LockPool *create(const Char8 *szName);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPType Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static  UInt32          _uiLockPoolCount;
            CreateLockPoolF _fCreateLockPool;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MPLockPoolType(const MPLockPoolType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MPLockPoolType &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! \ingroup GrpBaseBaseMultiThreading

class OSG_BASE_DLLMAPPING MPBase : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const MPType &getStaticType  (void);
    static       UInt32  getStaticTypeId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    virtual       MPType &getType  (void);
    virtual const MPType &getType  (void) const;
                  UInt32  getTypeId(void);
            const Char8  *getCName (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static  MPType  _type;
            Char8  *_szName;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPBase(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MPBase(void); 

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MPBase(const MPBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MPBase &source);
};

typedef MPBase *MPBaseP;

inline 
void addRef(const MPBaseP objectP);

inline
void subRef(const MPBaseP objectP);

OSG_END_NAMESPACE

#include "OSGMPBase.inl"

#define OSGMPBASE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGMPBASE_H_ */
