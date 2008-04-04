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

#ifndef _OSGREFPTR_H_
#define _OSGREFPTR_H_

#if 0

#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGRefPtr.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

template<class ContainerPtr>
class TransitPtr;

/*! \ingroup GrpSystemFieldContainer
 */

template<class ContainerPtr>
class RefPtr
{
    /*==========================  PUBLIC  =================================*/

  public:
  
    typedef ContainerPtr Ref;
    typedef TransitPtr<ContainerPtr> SelfTransitPtr;
    // typedef const Ref RefPtr::*unspecified_bool_type;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    RefPtr(void);
    RefPtr(const RefPtr &refPtr);
    
    // make it explicit to prevent unexpected construction/cast paths
    
    explicit RefPtr(const Ref         &pContainer);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    ~RefPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    operator Ref(void) const;
    
    typename PtrStripper<ContainerPtr>::Object* operator->(void) const;
    
    Ref get(void) const;
    
    RefPtr &operator =(const Ref                  &pContainer);
    RefPtr &operator =(const RefPtr               &refPtr    );
    RefPtr &operator =(      SelfTransitPtr       &transPtr  );

    void swap(RefPtr         &other);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

//    bool operator <  (const FieldContainerPtr    &other) const;
//    bool operator == (const FieldContainerPtr    &other) const;
//    bool operator != (const FieldContainerPtr    &other) const;

    bool operator <  (const RefPtr<ContainerPtr> &other) const;
    bool operator == (const RefPtr<ContainerPtr> &other) const;
    bool operator != (const RefPtr<ContainerPtr> &other) const;

    bool operator !  (void                              ) const;
 
//    operator unspecified_bool_type() const;
  
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
  
    void setRef(const Ref &pContainer);
    
    Ref _pRef;
};

typedef RefPtr<FieldContainerPtr> FieldContainerRefPtr;

OSG_END_NAMESPACE

#include "OSGRefPtr.inl"

#else

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

template<class ContainerPtr>
class RefPtr;

OSG_END_NAMESPACE

#endif

#endif /* _OSGCOREDNODEPTR_H_ */
