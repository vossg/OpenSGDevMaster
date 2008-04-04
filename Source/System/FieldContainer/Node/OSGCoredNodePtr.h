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

#ifndef _OSGCOREDNODEPTR_H_
#define _OSGCOREDNODEPTR_H_
#ifdef __sgi
#pragma once
#endif

#if 0

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGCoredNodePtr.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEM_DLLMAPPING CoredNodePtrBase
{
    /*==========================  PUBLIC  =================================*/

  public: 

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    CoredNodePtrBase(void);
  
    CoredNodePtrBase(NodePtr pNode);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~CoredNodePtrBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    NodePtr node(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
  
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    virtual NodeCorePtr getCoreV(      void                        ) const = 0;
    
    void        setNode (      NodePtrConstArg       pNode);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    
    NodePtr _pNode;
};

/*! \ingroup GrpSystemFieldContainer
 */

template <class Core>
class CoredNodePtr : public CoredNodePtrBase
{
    /*==========================  PUBLIC  =================================*/
  public:
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    CoredNodePtr(void);
    CoredNodePtr(const CoredNodePtr<Core> &pCore);
    
    // make them explicit to prevent unexpected construction/cast paths
    
    explicit CoredNodePtr(const          NodePtr      &pNode);
    explicit CoredNodePtr(const          NodeCorePtr  &pCore);
    explicit CoredNodePtr(const typename Core::ObjPtr &pCore);
     
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Create                                  */
    /*! \{                                                                 */

    static CoredNodePtr<Core> create(void);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~CoredNodePtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    void coreChanged(void);
  
    typename Core::ObjPtr core       (void) const;

    typename Core::ObjPtr &operator->(void);
    
    /* Note: these only work for a RHS */
    operator NodePtr(void);

    operator typename Core::ObjPtr(void);

    /* Assignment. Create a new CNP if necessary */
    
    CoredNodePtr<Core> &operator =(const          NodePtr            &pNode);

    CoredNodePtr<Core> &operator =(const typename Core::ObjPtr       &pCore);

    CoredNodePtr<Core> &operator =(const          CoredNodePtr<Core> &pCNP );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/ 

  protected:
  
    typedef          CoredNodePtrBase Inherited;

    typedef typename Core::ObjPtr      CorePtr;

    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    NodeCorePtr getCoreV  (               void                        ) const;
    
    void        setCore   (const          NodeCorePtr           &pCore);
    void        setCore   (const typename Core::ObjPtr          &pCore);

    void        updateNode(               void                        );
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
  
    typename Core::ObjPtr _pCore;
};

OSG_END_NAMESPACE

#include "OSGCoredNodePtr.inl"

#else

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

template<class Core>
class CoredNodePtr;

OSG_END_NAMESPACE

#endif

#endif /* _OSGCOREDNODEPTR_H_ */
