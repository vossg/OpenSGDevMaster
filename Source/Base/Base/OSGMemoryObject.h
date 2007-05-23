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

#ifndef _OSGMEMORYOBJECT_H_
#define _OSGMEMORYOBJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*! Memory, simple reference counted memory object. Parent of
    everything that should be shared, but must not be thread safe.
    \ingroup GrpBaseBase
 */

class OSG_BASE_DLLMAPPING MemoryObject
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MemoryObject(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void  addRef     (void);
    void  subRef     (void);    
    Int32 getRefCount(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    MemoryObject(void);
    MemoryObject(const  MemoryObject &source);

    /*! \}                                                                 */
   /*==========================  PRIVATE  ================================*/

  private:

    Int32 _refCount;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MemoryObject &source);
};

typedef MemoryObject *       MemoryObjectP;
typedef MemoryObject * const MemoryObjectPConst;

inline 
void addRef(MemoryObjectPConst pObject);

inline
void subRef(MemoryObjectPConst pObject);

template <class T> inline
void setRefd(T *&pObject, T * const pNewObject);

template <class T> inline
void clearRef(T *&pObject);
 
#ifdef OSG_1_COMPAT
inline
void subRefP(MemoryObjectPConst pObject)
{
    subRef(pObject);
}
inline
void addRefP(MemoryObjectPConst pObject)
{
    addRef(pObject);
}
#endif

OSG_END_NAMESPACE

#include "OSGMemoryObject.inl"

#endif /* _OSGMEMORYOBJECT_H_ */
