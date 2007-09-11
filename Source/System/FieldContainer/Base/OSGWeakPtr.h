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

#ifndef _OSGWEAKPTR_H_
#define _OSGWEAKPTR_H_

#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPtr.h
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
class WeakPtr
{
    /*==========================  PUBLIC  =================================*/

  public:
  
    typedef ContainerPtr Ref;
    typedef const Ref WeakPtr::*unspecified_bool_type;

    typedef RefPtr<ContainerPtr> SelfRefPtr;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    WeakPtr(void);
    WeakPtr(const WeakPtr &weakPtr);
    
    // make it explicit to prevent unexpected construction/cast paths
    
    explicit WeakPtr(const SelfRefPtr &refPtr);
    explicit WeakPtr(const Ref        &pContainer);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~WeakPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    operator SelfRefPtr(void) const;
    
    SelfRefPtr get(void) const;
    
    WeakPtr &operator =(const Ref                   &pContainer);
    WeakPtr &operator =(const WeakPtr               &weakPtr   );
    WeakPtr &operator =(const SelfRefPtr            &refPtr   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator <  (const FieldContainerPtr    &other) const;
    bool operator == (const FieldContainerPtr    &other) const;
    bool operator != (const FieldContainerPtr    &other) const;

    bool operator <  (const WeakPtr<ContainerPtr> &other) const;
    bool operator == (const WeakPtr<ContainerPtr> &other) const;
    bool operator != (const WeakPtr<ContainerPtr> &other) const;

    bool operator !  (void                              ) const;
 
    operator unspecified_bool_type() const;
  
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
  
    void setRef(const Ref &pContainer);
    
    Ref _pRef;
};

typedef WeakPtr<FieldContainerPtr> FieldContainerWeakPtr;

OSG_END_NAMESPACE

#include "OSGWeakPtr.inl"

#endif /* _OSGCOREDNODEPTR_H_ */
