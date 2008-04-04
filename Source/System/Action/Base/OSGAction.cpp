/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGNodeCore.h>
#include "OSGAction.h"

//#define BOOST_MEM_FN_ENABLE_CDECL
#include <boost/bind.hpp>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Action
    \ingroup GrpSystemAction

The action base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


Action *Action::_prototype = NULL;

std::vector<Action::Functor> *Action::_defaultEnterFunctors = NULL;
std::vector<Action::Functor> *Action::_defaultLeaveFunctors = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void Action::registerEnterDefault(const FieldContainerType &type, 
                                  const Action::Functor    &func)
{
    if(_defaultEnterFunctors == NULL)
        _defaultEnterFunctors = new std::vector<Action::Functor>;

#ifndef OSG_WINCE
    while(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->push_back(&Action::_defaultEnterFunction);
    }
#else
    while(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->push_back(&NodeCore::defaultEnter);
    }
#endif
    
    (*_defaultEnterFunctors)[type.getId()] = func;
}

void Action::registerLeaveDefault(const FieldContainerType &type, 
                                  const Action::Functor    &func)
{
    if(_defaultLeaveFunctors == NULL)
        _defaultLeaveFunctors = new std::vector<Action::Functor>;

#ifndef OSG_WINCE
    while(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->push_back(&Action::_defaultLeaveFunction);
    }
#else
    while(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->push_back(&NodeCore::defaultLeave);
    }
#endif
    
    (*_defaultLeaveFunctors)[type.getId()] = func;
}

void Action::setPrototype(Action *proto)
{
    _prototype = proto;
}

Action *Action::getPrototype(void)
{
    return _prototype;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Action::Action(void) : 
    _enterFunctors(                            ),
    _leaveFunctors(                            ),
    _actNode      (OSGNullFC                   ),
    _actList      (NULL                        ),
    _useNewList   (false                       ),
    _travMask     (TypeTraits<UInt32>::getMax()),
    _nodeEnterCB  (                            ),
    _nodeLeaveCB  (                            )
{
    if(_defaultEnterFunctors)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors)
        _leaveFunctors = *_defaultLeaveFunctors;
}

/** \brief Copy-Constructor
 */

Action::Action(const Action & source) :
    _enterFunctors(source._enterFunctors       ),
    _leaveFunctors(source._leaveFunctors       ),
    _actNode      (OSGNullFC                   ),
    _actList      (NULL                        ),
    _useNewList   (false                       ),
    _travMask     (source._travMask            ),
    _nodeEnterCB  (source._nodeEnterCB         ),
    _nodeLeaveCB  (source._nodeLeaveCB         )
{
}


/** \brief create a new action
 */

Action *Action::create(void)
{
    Action *act;
    
    if(_prototype)
    {
        act = new Action(*_prototype);
    }
    else
    {
        act = new Action();
    }

    return act;
}

/** \brief Destructor
 */

Action::~Action(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void Action::registerEnterFunction(const FieldContainerType &type, 
                                   const Action::Functor    &func)
{
#ifndef OSG_WINCE
    while(type.getId() >= _enterFunctors.size())
    {
        _enterFunctors.push_back(&Action::_defaultEnterFunction);
    }
#else
    while(type.getId() >= _enterFunctors.size())
    {
        _enterFunctors.push_back(&NodeCore::defaultEnter);
    }
#endif
    
    _enterFunctors[type.getId()] = func;
}

void Action::registerLeaveFunction(const FieldContainerType &type, 
                                   const Action::Functor    &func)
{
#ifndef OSG_WINCE
    while(type.getId() >= _leaveFunctors.size())
    {
        _leaveFunctors.push_back(&Action::_defaultLeaveFunction);
    }
#else
    while(type.getId() >= _leaveFunctors.size())
    {
        _leaveFunctors.push_back(&NodeCore::defaultLeave);
    }
#endif
    
    _leaveFunctors[type.getId()] = func;
}



// application entry points

ActionBase::ResultE Action::apply(std::vector<NodePtr>::iterator begin,
                                  std::vector<NodePtr>::iterator end)
{
    Action::ResultE res = Continue;
    
    // call the start function and its' returns

    if((res = callStart()) != Continue)
        return res;     
    
    // call the given nodes
    
    for(; begin != end; ++begin)
    {
        if(*begin == NullFC)
        {
            SWARNING << "apply: encountered NullNode!" << std::endl;
            return Quit;            
        }
        else
        {
            res = recurse(*begin);
            
            if(res != Continue)
                break;
        }
    }
        
    // call the stop function and its' returns
    res = callStop(res);  
    
    return res;
}

ActionBase::ResultE Action::apply(NodePtrConstArg node)
{
    if(node == NullFC)
    {
        SWARNING << "apply: node is Null!" << std::endl;
        return Quit;            
    }

    std::vector<NodePtr> nodeList;

    nodeList.push_back(node);

    return apply(nodeList.begin(), nodeList.end());
}




// recursion calling

ActionBase::ResultE Action::recurse(NodePtrConstArg node)
{
    if(node == NullFC)
        return Continue;

    if((node->getTravMask() & getTravMask()) == 0)
        return Continue;

#if OSG_1_COMPAT
    if(node->getOcclusionMask() & 1)
        return Continue;
#endif

    NodeCorePtr core = node->getCore();
    
    if(core == NullFC)
    {
        SWARNING << "recurse: core is Null,  don't know what to do!" 
                 << std::endl;
        return Quit;                    
    }
    
    Action::ResultE result = Continue;

    _actList = NULL;
    _actNode = node;

    _newList.clear();

    _useNewList = false;

    if(_nodeEnterCB != NULL)
        result = _nodeEnterCB(node, this);

    if(result != Continue)
    {
        if(result == Skip)
            return Continue;
    
        return result;
    }

    result = callEnter(node->getCore());

    if(result != Continue)
    {
        if(result == Skip)
            return Continue;
    
        return result;
    }
    
    if(! _newList.empty())
    {
        result = callNewList();
    }
    else if(! _useNewList) // new list is empty, but not used?
    {
        MFUnrecNodePtr::const_iterator it;

        for(  it  = node->getMFChildren()->begin(); 
              it != node->getMFChildren()->end(); 
            ++it)
        {
            result = recurse(*it);
            
            if(result != Continue)
                break;
        }
    }   
    
    _actNode = node;

    if(result == Continue)
    {
        result = callLeave(node->getCore());
    }
    else
    {
        callLeave(node->getCore());
    }

    if(_nodeLeaveCB != NULL)
        _nodeLeaveCB(node, this);

    if(result == Skip)
        return Continue;
        
    return result;
}

// call the _newList objects
ActionBase::ResultE Action::callNewList(void)
{
    ResultE result = Continue;

    // need to make a copy, because the one in the action is cleared

    std::vector<NodePtr> nodeList;

    nodeList.swap(_newList);

    std::vector<NodePtr>::iterator it;

    _actList = &nodeList;

    for(it = nodeList.begin(); it != nodeList.end(); ++it)
    {
        result = recurse(*it);

        if(result != Continue)
            break;
    }
    
    return result;
}


// call the start function and its results

ActionBase::ResultE Action::callStart(void)
{
    ResultE res = Continue;
    
    // call the start and see if it returns some nodes
    
    _newList.clear();

    if((res = start()) != Continue)
        return res;     
    
    // got some nodes? call them
    
    if(! _newList.empty())
        res = callNewList();
    
    // return the result

    return res;
}

// call the stop function and its results

ActionBase::ResultE Action::callStop(ResultE res)
{
    // call the start and see if it returns some nodes
    
    _newList.clear();

    if((res = stop(res)) != Continue)
        return res;     
            
    if(! _newList.empty())
        res = callNewList();

    return res;
}

// default start/stop, does nothing

ActionBase::ResultE Action::start(void)
{
    return Continue;
}

ActionBase::ResultE Action::stop(ResultE res)
{
    return res;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

Action& Action::operator = (const Action &source)
{
    if (this == &source)
        return *this;

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

bool Action::operator < (const Action &other)
{
    return this < &other;
}

/** \brief equal
 */

bool Action::operator == (const Action &OSG_CHECK_ARG(other))
{
    return false;
}

/** \brief unequal
 */

bool Action::operator != (const Action &other)
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

std::vector<Action::Functor>* Action::getDefaultEnterFunctors(void)
{
    return _defaultEnterFunctors;
}

std::vector<Action::Functor>* Action::getDefaultLeaveFunctors(void)
{
    return _defaultLeaveFunctors;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

// default Action function: just call all kids

ActionBase::ResultE Action::_defaultEnterFunction(NodeCorePtrConstArg  , 
                                                  Action          *)
{
    return Continue;
}

ActionBase::ResultE Action::_defaultLeaveFunction(NodeCorePtrConstArg  , 
                                                  Action          *)
{
    return Continue;
}

/*************** Functions ******************/

OSG_BEGIN_NAMESPACE

/*
inline
ActionBase::ResultE doCallEnter(NodePtrConstArg       node, 
                                TraverseEnterFunctor &func)
{
    return func.call(node);
}

inline
ActionBase::ResultE doCallLeave(NodePtrConstArg       node, 
                                ActionBase::ResultE   res,
                                TraverseLeaveFunctor &func)
{
    return func.call(node, res);
}
*/

/*! Simple tree traversal function. Calls func for every node encountered
 */

ActionBase::ResultE traverse(const std::vector<NodePtr> &nodeList, 
                                   TraverseEnterFunctor  func    )
{
    ActionBase::ResultE res = ActionBase::Continue;

    std::vector<NodePtr>::const_iterator it = nodeList.begin();
    std::vector<NodePtr>::const_iterator en = nodeList.end  ();
    
    for(; it != en; ++it)
    {
        res = traverse((*it), func);
        
        if(res == ActionBase::Quit)
            break;
    }
        
    return res;
}

ActionBase::ResultE traverse(const MFUnrecNodePtr       &nodeList, 
                                   TraverseEnterFunctor  func    )
{
    ActionBase::ResultE res = ActionBase::Continue;

    MFUnrecNodePtr::const_iterator it = nodeList.begin();
    MFUnrecNodePtr::const_iterator en = nodeList.end  ();
    
    for(; it != en; ++it)
    {
        res = traverse((*it), func);
        
        if(res == ActionBase::Quit)
            break;
    }
        
    return res;
}

/*! Simple tree traversal function. Calls func for every node encountered
 */

ActionBase::ResultE traverse(NodePtrConstArg      node, 
                             TraverseEnterFunctor func )
{
    ActionBase::ResultE res = ActionBase::Continue;
    
    res = func(node);
    
    switch(res)
    {
        case ActionBase::Skip:      
            return Action::Continue;

        case ActionBase::Continue:  
            return traverse(*(node->getMFChildren()), 
                            func                    );

        default:                
            break;
    }
                 
    return res;
}
                            
/*! Simple tree traversal function. Calls enter before entering a node,
    leave after leaving.
 */

ActionBase::ResultE traverse(const std::vector<NodePtr> &nodeList, 
                                   TraverseEnterFunctor  enter, 
                                   TraverseLeaveFunctor  leave )
{
    ActionBase::ResultE res = ActionBase::Continue;

    std::vector<NodePtr>::const_iterator it = nodeList.begin();
    std::vector<NodePtr>::const_iterator en = nodeList.end  ();
    
    for(; it != en; ++it)
    {
        res = traverse((*it), enter, leave);
        
        if(res == Action::Quit)
            break;
    }
        
    return res;
}

ActionBase::ResultE traverse(const MFUnrecNodePtr       &nodeList, 
                                   TraverseEnterFunctor  enter, 
                                   TraverseLeaveFunctor  leave )
{
    ActionBase::ResultE res = ActionBase::Continue;

    MFUnrecNodePtr::const_iterator it = nodeList.begin();
    MFUnrecNodePtr::const_iterator en = nodeList.end  ();
    
    for(; it != en; ++it)
    {
        res = traverse((*it), enter, leave);
        
        if(res == Action::Quit)
            break;
    }
        
    return res;
}

                            
/*! Simple tree traversal function. Calls enter before entering a node,
    leave after leaving.
 */

ActionBase::ResultE traverse(NodePtrConstArg      node, 
                             TraverseEnterFunctor enter, 
                             TraverseLeaveFunctor leave )
{
    ActionBase::ResultE res = ActionBase::Continue;
    
    res = enter(node);
    
    switch(res)
    {
        case ActionBase::Skip:      
            res = Action::Continue;
            break;

        case ActionBase::Continue:  
            res = traverse(*(node->getMFChildren()), 
                           enter, 
                           leave                   );

        default:                
            break;
    }
     
    res = leave(node, res);
                
    return res;
}

OSG_END_NAMESPACE
