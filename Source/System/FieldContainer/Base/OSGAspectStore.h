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

#ifndef _OSGASPECTSTORE_H_
#define _OSGASPECTSTORE_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_MT_CPTR_ASPECT

#include "OSGBaseTypes.h"
#include "OSGThread.h"
#include "OSGThreadManager.h"

#include <vector>

OSG_BEGIN_NAMESPACE

class FieldContainer;

/*! Memory, simple reference counted memory object. Parent of
    everything that should be shared, but must not be thread safe.
    \ingroup GrpBaseBase
 */

class OSG_SYSTEM_DLLMAPPING AspectStore
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    AspectStore(void);
    AspectStore(const  AspectStore &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    FieldContainer *getPtr            (void                        );
    FieldContainer *getPtr            (UInt32            uiAspect  );
    void            setPtrForAspect   (FieldContainerPtr pContainer, 
                                       UInt32            uiAspect  );
    void            removePtrForAspect(UInt32            uiAspect  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void  addRef     (void);
    void  subRef     (void);    
    Int32 getRefCount(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void fillOffsetArray(AspectOffsetStore &oStore,
                         FieldContainerPtr  pRef  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::vector<FieldContainer *> FieldContainerStore;

    FieldContainerStore _vAspects;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
 
    ~AspectStore(void); 

    /*! \}                                                                 */
   /*==========================  PRIVATE  ================================*/

  private:

    Int32 _refCount;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const AspectStore &source);
};

typedef AspectStore *AspectStoreP;

inline 
void addRef(const AspectStoreP pObject);

inline
void subRef(const AspectStoreP pObject);

OSG_END_NAMESPACE

#include "OSGAspectStore.inl"

#define OSGASPECTSTORE_HEADER_CVSID "@(#)$Id$"

#endif

#endif /* _OSGASPECTSTORE_H_ */
