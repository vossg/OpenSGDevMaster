/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifndef _OSGTRANSITPTR_H_
#define _OSGTRANSITPTR_H_

#if 0

#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGTransitPtr.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

template<class ContainerPtr>
class RefPtr;

template<class ContainerPtr>
class TransitPtr
{
    /*==========================  PUBLIC  =================================*/

  public:
  
    typedef ContainerPtr Ref;

    typedef RefPtr<ContainerPtr> SelfRefPtr;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    TransitPtr(TransitPtr &other);
    TransitPtr(SelfRefPtr &other);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~TransitPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    TransitPtr &operator =(const TransitPtr  &other);
    TransitPtr &operator =(const SelfRefPtr  &other);

    void swap(TransitPtr  &other);    
    void swap(SelfRefPtr  &other);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    SelfRefPtr &debugFoo(void) { return _pRef; }

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
    
    
    SelfRefPtr _pRef;
};

typedef TransitPtr<FieldContainerPtr> FieldContainerTransitPtr;

OSG_END_NAMESPACE

#include "OSGTransitPtr.inl"

#else

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

template<class ContainerPtr>
class TransitPtr;

OSG_END_NAMESPACE

#endif

#endif /* _OSGCOREDNODEPTR_H_ */
