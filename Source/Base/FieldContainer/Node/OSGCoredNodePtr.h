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

#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerNodes
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class CoreT>
class CoredNodeRefPtr
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
  
    typedef CoreT                         Core;
    typedef CoredNodeRefPtr               Self;
    
    typedef          Core                *CorePtr;
    typedef typename Core::ObjRecPtr      CoreRefPtr;
    typedef typename Core::ObjTransitPtr  CoreTransitPtr;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
             CoredNodeRefPtr(void                    );
             CoredNodeRefPtr(Self        const &pCore);
    explicit CoredNodeRefPtr(Node              *pNode);
    explicit CoredNodeRefPtr(NodeCore          *pCore);
    explicit CoredNodeRefPtr(CorePtr            pCore);
    explicit CoredNodeRefPtr(CoreTransitPtr     pCore);
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Create                                  */
    /*! \{                                                                 */

    static CoredNodeRefPtr<Core> create(void);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~CoredNodeRefPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    void coreChanged(void);
  
    Node   *node      (void) const;
    CorePtr core      (void) const;
    
    CorePtr operator->(void) const;
    
    /* Note: these only work for a RHS */
    operator Node    *(void);
    operator CorePtr  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */
    
    Self &operator =(Node           *pNode);
    Self &operator =(NodeTransitPtr  pNode);
    Self &operator =(CorePtr         pCore);
    Self &operator =(CoreTransitPtr  pCore);
    Self &operator =(Self    const  &pCNRP);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/ 
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    void setNode   (Node           * const pNode);
    void setNode   (NodeTransitPtr         pNode);

    void setCore   (NodeCore       * const pCore);
    void setCore   (CorePtr                pCore);

    void updateNode(void                        );
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    NodeRecPtr _pNode;
    CoreRefPtr _pCore;
};

/*! \ingroup GrpBaseFieldContainerNodes
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class CoreT>
class CoredNodeMTRefPtr
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
  
    typedef CoreT                         Core;
    typedef CoredNodeMTRefPtr             Self;
    
    typedef          Core                *CorePtr;
    typedef typename Core::ObjMTRecPtr    CoreMTRefPtr;
    typedef typename Core::ObjTransitPtr  CoreTransitPtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
             CoredNodeMTRefPtr(void                    );
             CoredNodeMTRefPtr(Self        const &pCore);
    explicit CoredNodeMTRefPtr(Node              *pNode);
    explicit CoredNodeMTRefPtr(NodeCore          *pCore);
    explicit CoredNodeMTRefPtr(CorePtr            pCore);
    explicit CoredNodeMTRefPtr(CoreTransitPtr     pCore);
 
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Create                                  */
    /*! \{                                                                 */

    static CoredNodeMTRefPtr<Core> create(void);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~CoredNodeMTRefPtr(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    void coreChanged(void);
  
    Node    *node      (void) const;
    CorePtr  core      (void) const;
    
    CorePtr operator->(void) const;
    
    /* Note: these only work for a RHS */
    operator Node    *(void);
    operator CorePtr  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */
    
    Self &operator =(Node          *pNode);
    Self &operator =(CorePtr        pCore);
    Self &operator =(CoreTransitPtr pCore);
    Self &operator =(Self    const &pCNRP);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/ 
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    void setNode   (Node     * const pNode);
    
    void setCore   (NodeCore * const pCore);
    void setCore   (CorePtr          pCore);

    void updateNode(void                  );
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    NodeMTRecPtr  _pNode;
    CoreMTRefPtr  _pCore;
};

OSG_END_NAMESPACE

#include "OSGCoredNodePtr.inl"

#endif /* _OSGCOREDNODEPTR_H_ */
