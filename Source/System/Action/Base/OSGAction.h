/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGACTION_H_
#define _OSGACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>
#include <stack>

#include <boost/function.hpp>

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldContainerType.h"
#include "OSGContainerForwards.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGActionBase.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class Node;
class Action;
class MultiCore;

template <class ParentT>
class StageHandlerMixin;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief Action base class
    \ingroup GrpSystemActionBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING Action : public ActionBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    typedef boost::function<ResultE(NodeCore * const, 
                                    Action   *      )> Functor;
    typedef boost::function<ResultE(Node     * const,   
                                    Action   *      )> NodeFunctor; 

    typedef std::vector<Functor>                       FunctorStore;
    typedef FunctorStore::iterator                     FunctorStoreIt;
    typedef FunctorStore::const_iterator               FunctorStoreConstIt;

    typedef ActionBase::ResultE (NodeCore::*Callback)(Action *);


    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    // create a new action by cloning the prototype
    static Action *create(void);
    
    // prototype access
    // after setting the prototype all new actions are clones of it

    static void    setPrototype(Action *proto);
    static Action *getPrototype(void         );
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~Action(void);

    /*------------------------- your_category -------------------------------*/
    
    // default registration. static, so it can be called during static init
    
    static void registerEnterDefault (const FieldContainerType &type, 
                                      const Functor            &func);
    
    static void registerLeaveDefault (const FieldContainerType &type, 
                                      const Functor            &func);

    // instance registration
    
           void registerEnterFunction(const FieldContainerType &type, 
                                      const Functor            &func);
    
           void registerLeaveFunction(const FieldContainerType &type, 
                                      const Functor            &func);

    /*------------------------- your_category -------------------------------*/

    // application

    virtual ResultE apply(std::vector<Node *>::iterator begin, 
                          std::vector<Node *>::iterator end  );

    virtual ResultE apply(Node * const                   node);

    /*------------------------- your_category -------------------------------*/
    
    // the node being traversed. Might be needed by the traversed core
    
    inline Node           *getActNode  (void);
    inline FieldContainer *getActParent(void);

    // the node being traversed. Might be needed by the traversed core
    // needs to be set by the RenderAction, as the draw tree is traversed 
    // after the graph traversal
    
    void setActNode(Node * const node);

    /*------------------------- your_category -------------------------------*/

    // Node access: 
    // the number of active nodes 
    
    UInt32       getNNodes  (void                 ) const;
    
    // you can access a single node by getNode
    
    Node        *getNode    (int             index);
    
    // per default all child nodes are traversed. If addNode is called, 
    // only the added nodes will be traversed.
    
    void         addNode    (Node * const node);

    // Common case: going through the children list and picking up some of 
    // them, but it's not clear if any at all. Call useNodeList() and then
    // addNode() for every node to traverse, or not at all. 

    void         useNodeList(bool bVal = true    ); 
   
    /*------------------------- assignment ----------------------------------*/

    UInt32 getTravMask (void      ) const;
    void   setTravMask (UInt32 val);

    void   andTravMask (UInt32 val);
    void   orTravMask  (UInt32 val);
    
    /*------------------------- comparison ----------------------------------*/

    void pushTravMask(void);
    void popTravMask (void);

    /*------------------------- comparison ----------------------------------*/

    bool operator <  (const Action &other);
    
    bool operator == (const Action &other);
    bool operator != (const Action &other);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // protected to allow derived access
    Action(void);
    Action(const Action &source);

    // call the single node. used for cascading actions
    
    inline ResultE callEnter(NodeCore * const core);   
    inline ResultE callLeave(NodeCore * const core);

    // start/stop functions for the action.
    // called at the very beginning/end, can return a list of nodes
    // via addNode() which is traversed before/after the traversal is done
    // main use: collecting actions use stop() to emit their collection
    
    virtual ResultE start(void       );  
    virtual ResultE stop (ResultE res); // res is the exit code of the action
    
    // recurse through the node
    ResultE recurse             (Node      * const node );
    ResultE recurseNoCallback   (Node      * const node );
    ResultE recurseMultiCoreFrom(Node      * const node,
                                 MultiCore * const core,
                                 NodeCore  * const from );
   
    // call the _newList list of nodes
    
    ResultE callNewList(void);

    void setActParent(FieldContainer * const parent);

    // access default functors

    virtual FunctorStore* getDefaultEnterFunctors(void);
    virtual FunctorStore* getDefaultLeaveFunctors(void);

    // default function
    
    static ResultE _defaultEnterFunction(NodeCore * const node, 
                                         Action   *       action);
    static ResultE _defaultLeaveFunction(NodeCore * const node, 
                                         Action   *       action);

    // functors
    // just protected, so that derived actions can access them
    
    FunctorStore _enterFunctors;
    FunctorStore _leaveFunctors;
   
    
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Node                 *_actNode;   // the node being traversed right now
    FieldContainer       *_actParent;

    std::vector<Node  *> *_actList;  // list of active objects for this level
                                     // if empty, use the actNode's children

    bool                  _useNewList;// set by clearNodeList
    std::vector<Node  *>  _newList;   // list of active object for this level

    UInt32                _travMask;
    std::stack<UInt32>    _sTravMask;

    NodeFunctor           _nodeEnterCB;
    NodeFunctor           _nodeLeaveCB;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    template <class ParentT>
    friend class StageHandlerMixin;

    friend class MultiCore;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    // the prototype which is copied to create new actions
    static Action       *_prototype;
    
    // default functors for instantiation
    static FunctorStore *_defaultEnterFunctors;
    static FunctorStore *_defaultLeaveFunctors;
    
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------
       
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
    
    // helper functions for start/stop, that also call the results of 
    // start/stop
    
    ResultE callStart(void       );
    ResultE callStop (ResultE res);

    Action& operator =(const Action &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef Action *ActionP;

/*---------------------------------------------------------------------*/
/*! \name                    Traversal Functions                       */
/*! \{                                                                 */

/*! \ingroup GrpSystemActionFuncs
 */

typedef boost::function<
          Action::ResultE (Node * const   )> TraverseEnterFunctor;

/*! \ingroup GrpSystemActionFuncs
 */

typedef boost::function<
          Action::ResultE (Node * const, 
                           Action::ResultE)> TraverseLeaveFunctor;

/*! \ingroup GrpSystemActionFuncs
 */

typedef boost::function<ActionBase::ResultE (Action *)> RenderActionFunctor;

/*
typedef ArgsCollector<ActionBase::ResultE> ArgsT;

typedef TypedFunctor1Base<Action::ResultE, 
                          CPtrRefCallArg<NodePtr> > TraverseEnterFunctor;
typedef TypedFunctor2Base<Action::ResultE, 
                          CPtrRefCallArg<NodePtr>, 
                          ArgsT                   > TraverseLeaveFunctor;
 */

/*! \ingroup GrpSystemActionFuncs
 */

OSG_SYSTEM_DLLMAPPING
ActionBase::ResultE traverse(      Node * const          root, 
                                   TraverseEnterFunctor  func);

/*! \ingroup GrpSystemActionFuncs
 */

OSG_SYSTEM_DLLMAPPING
ActionBase::ResultE traverse(const std::vector<Node *> &nodeList, 
                                   TraverseEnterFunctor  func);

/*! \ingroup GrpSystemActionFuncs
 */

OSG_SYSTEM_DLLMAPPING
ActionBase::ResultE traverse(const MFUnrecChildNodePtr  &nodeList, 
                                   TraverseEnterFunctor  func);
                            
/*! \ingroup GrpSystemActionFuncs
 */

OSG_SYSTEM_DLLMAPPING
ActionBase::ResultE traverse(      Node * const          root, 
                                   TraverseEnterFunctor  enter, 
                                   TraverseLeaveFunctor  leave);
/*! \ingroup GrpSystemActionFuncs
 */

OSG_SYSTEM_DLLMAPPING
ActionBase::ResultE traverse(const std::vector<Node *>  &nodeList, 
                                   TraverseEnterFunctor  enter, 
                                   TraverseLeaveFunctor  leave);

/*! \ingroup GrpSystemActionFuncs
 */

OSG_SYSTEM_DLLMAPPING
ActionBase::ResultE traverse(const MFUnrecChildNodePtr  &nodeList, 
                                   TraverseEnterFunctor  enter, 
                                   TraverseLeaveFunctor  leave);
                            
/*! \}                                                                 */

OSG_END_NAMESPACE

#include "OSGAction.inl"

#endif /* _OSGACTION_H_ */


