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

#ifndef _OSGHARDWARECONTEXTDATA_H_
#define _OSGHARDWARECONTEXTDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMemoryObject.h"

OSG_BEGIN_NAMESPACE

class HardwareContext;

/*! \class HardwareContextData 
    Memory, simple reference counted memory object. Parent of
    everything that should be shared, but must not be thread safe.
    \ingroup GrpBaseMemoryObjectsBase
    \ingroup GrpBaseHardwareContext
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING HardwareContextData : public MemoryObject
{

    /*==========================  PUBLIC  =================================*/

    typedef MemoryObject Inherited;

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                                                              */
    /*! \{                                                                 */

    virtual void releaseResources(HardwareContext *pContext);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    HardwareContextData(void);
    HardwareContextData(const  HardwareContextData &source);

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~HardwareContextData(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const HardwareContextData &source);
};
 
OSG_END_NAMESPACE

#include "OSGHardwareContextData.inl"

#endif /* _OSGHARDWARECONTEXTDATA_H_ */
