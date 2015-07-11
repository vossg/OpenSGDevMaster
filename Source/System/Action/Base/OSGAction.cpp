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

#include "OSGLog.h"
#include "OSGFieldContainer.h"
#include "OSGMultiCore.h"
#include "OSGNodeCore.h"
#include "OSGAction.h"
#include "OSGRootGroup.h"

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


Action               *Action::_prototype            = NULL;

Action::FunctorStore *Action::_defaultEnterFunctors = NULL;
Action::FunctorStore *Action::_defaultLeaveFunctors = NULL;

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
        _defaultEnterFunctors = new FunctorStore;

    while(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->push_back(&Action::_defaultEnterFunction);
    }

    (*_defaultEnterFunctors)[type.getId()] = func;
}

void Action::registerLeaveDefault(const FieldContainerType &type,
                                  const Action::Functor    &func)
{
    if(_defaultLeaveFunctors == NULL)
        _defaultLeaveFunctors = new FunctorStore;

    while(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->push_back(&Action::_defaultLeaveFunction);
    }

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
     Inherited    (                           ),
    _enterFunctors(                           ),
    _leaveFunctors(                           ),
    _actNode      (NULL                       ),
    _actParent    (NULL                       ),
    _actList      (NULL                       ),
    _useNewList   (false                      ),
    _newList      (                           ),
    _travMask     (TypeTraits<UInt32>::BitsSet),
    _sTravMask    (                           ),
    _nodeEnterCB  (                           ),
    _nodeLeaveCB  (                           )
{
    if(_defaultEnterFunctors)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors)
        _leaveFunctors = *_defaultLeaveFunctors;
}

/** \brief Copy-Constructor
 */

Action::Action(const Action &source) :
     Inherited    (source                      ),
    _enterFunctors(source._enterFunctors       ),
    _leaveFunctors(source._leaveFunctors       ),
    _actNode      (NULL                        ),
    _actParent    (NULL                        ),
    _actList      (NULL                        ),
    _useNewList   (false                       ),
    _newList      (                            ),
    _travMask     (source._travMask            ),
    _sTravMask    (                            ),
    _nodeEnterCB  (source._nodeEnterCB         ),
    _nodeLeaveCB  (source._nodeLeaveCB         )
{
}


/** \brief create a new action
 */

Action::ObjTransitPtr Action::create(void)
{
    ObjTransitPtr act(NULL);

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
    while(type.getId() >= _enterFunctors.size())
    {
        _enterFunctors.push_back(&Action::_defaultEnterFunction);
    }

    _enterFunctors[type.getId()] = func;
}

void Action::registerLeaveFunction(const FieldContainerType &type,
                                   const Action::Functor    &func)
{
    while(type.getId() >= _leaveFunctors.size())
    {
        _leaveFunctors.push_back(&Action::_defaultLeaveFunction);
    }

    _leaveFunctors[type.getId()] = func;
}



// application entry points

Action::ResultE Action::apply(std::vector<Node *>::iterator begin,
                              std::vector<Node *>::iterator end)
{
    Action::ResultE res = Continue;

    // call the start function and its' returns

    if((res = callStart()) != Continue)
        return res;

    // call the given nodes

    for(; begin != end; ++begin)
    {
        if(*begin == NULL)
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

Action::ResultE Action::apply(Node * const node)
{
    if(node == NULL)
    {
        SWARNING << "apply: node is Null!" << std::endl;
        return Quit;
    }

    std::vector<Node *> nodeList;

    nodeList.push_back(node);

    return apply(nodeList.begin(), nodeList.end());
}




// recursion calling

Action::ResultE Action::recurse(Node * const node)
{
    if(node == NULL)
        return Continue;

    if((node->getTravMask() & getTravMask()) == 0x0000)
    {
        return Continue;
    }

#if OSG_1_COMPAT
    if(node->getOcclusionMask() & 1)
        return Continue;
#endif

    NodeCore *core = node->getCore();

    if(core == NULL)
    {
        SWARNING << "Action::recurse: core is NULL, "
                 << "aborting traversal." << std::endl;
        return Quit;
    }

    Action::ResultE result = Continue;

    _actList   = NULL;
    _actNode   = node;
    _actParent = node;

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

    _actNode   = node;
    _actParent = node;

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
        Node::MFChildrenType::const_iterator cIt =
            node->getMFChildren()->begin();
        Node::MFChildrenType::const_iterator cEnd =
            node->getMFChildren()->end  ();

        for(; cIt != cEnd; ++cIt)
        {
            result = recurse(*cIt);

            if(result != Continue)
                break;
        }
    }

    _actNode   = node;
    _actParent = node;

    if(result == Continue)
    {
        result = callLeave(node->getCore());
    }
    else
    {
        callLeave(node->getCore());
    }

    _actNode   = node;
    _actParent = node;

    if(_nodeLeaveCB != NULL)
        _nodeLeaveCB(node, this);

    if(result == Skip)
        return Continue;

    return result;
}

Action::ResultE Action::recurseNoCallback(Node * const node)
{
    if(node == NULL)
        return Continue;

    if((node->getTravMask() & getTravMask()) == 0x0000)
    {
        return Continue;
    }

    NodeCore *core = node->getCore();

    if(core == NULL)
    {
        SWARNING << "Action::recurseNoCallback: core is NULL, "
                 << "aborting traversal." << std::endl;
        return Quit;
    }

    Action::ResultE result = Action::Continue;

    _actList   = NULL;
    _actNode   = node;
    _actParent = node;

    if(! _newList.empty())
    {
        result = callNewList();
    }
    else if(! _useNewList) // new list is empty, but not used?
    {
        Node::MFChildrenType::const_iterator cIt =
            node->getMFChildren()->begin();

        Node::MFChildrenType::const_iterator cEnd =
            node->getMFChildren()->end  ();

        for( ; cIt != cEnd; ++cIt)
        {
            result = recurse(*cIt);

            if(result != Continue)
                break;
        }
    }

    _actNode   = node;
    _actParent = node;

    if(result == Skip)
        return Continue;

    return result;
}

Action::ResultE Action::recurseMultiCoreFrom(Node      * const node,
                                             MultiCore * const mcore,
                                             NodeCore  * const from )
{
    if(node == NULL)
        return Continue;

    if((node->getTravMask() & getTravMask()) == 0x0000)
    {
        return Continue;
    }

    OSG_ASSERT(node->getCore() == mcore);

    Action::ResultE result = Continue;

    _actList   = NULL;
    _actNode   = node;
    _actParent = node;

    result = mcore->actionEnterFrom(this, from);

    _actNode   = node;
    _actParent = node;

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
        Node::MFChildrenType::const_iterator it =
            node->getMFChildren()->begin();
        Node::MFChildrenType::const_iterator en =
            node->getMFChildren()->end  ();

        for(; it != en; ++it)
        {
            result = recurse(*it);

            if(result != Continue)
                break;
        }
    }

    _actNode   = node;
    _actParent = node;

    if(result == Continue)
    {
        result = mcore->actionLeaveFrom(this, from);
    }
    else
    {
        mcore->actionLeaveFrom(this, from);
    }

    _actNode   = node;
    _actParent = node;

    if(result == Skip)
        return Continue;

    return result;
}


// call the _newList objects
Action::ResultE Action::callNewList(void)
{
    ResultE result = Continue;

    // need to make a copy, because the one in the action is cleared

    std::vector<Node *> nodeList;

    nodeList.swap(_newList);

    std::vector<Node *>::iterator it = nodeList.begin();
    std::vector<Node *>::iterator en = nodeList.end();

    _actList = &nodeList;

    for(; it != en; ++it)
    {
        result = recurse(*it);

        if(result != Continue)
            break;
    }

    _actList = NULL;

    return result;
}


// call the start function and its results

Action::ResultE Action::callStart(void)
{
    ResultE       res          = Continue;
    FunctorStore *defaultEnter = getDefaultEnterFunctors();
    FunctorStore *defaultLeave = getDefaultLeaveFunctors();

    // new default enter functor registered since this action was created
    if(defaultEnter          != NULL &&
       _enterFunctors.size() <  defaultEnter->size())
    {
        _enterFunctors.reserve(defaultEnter->size());

        FunctorStoreConstIt fIt  = defaultEnter->begin() + _enterFunctors.size();
        FunctorStoreConstIt fEnd = defaultEnter->end  ();

        for(; fIt != fEnd; ++fIt)
        {
            _enterFunctors.push_back(*fIt);
        }
    }

    // new default leave functor registered since this action was created
    if(defaultLeave          != NULL &&
       _leaveFunctors.size() <  defaultLeave->size())
    {
        _leaveFunctors.reserve(defaultLeave->size());

        FunctorStoreConstIt fIt  = defaultLeave->begin() + _leaveFunctors.size();
        FunctorStoreConstIt fEnd = defaultLeave->end  ();

        for(; fIt != fEnd; ++fIt)
        {
            _leaveFunctors.push_back(*fIt);
        }
    }

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

Action::ResultE Action::callStop(ResultE res)
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

Action::ResultE Action::start(void)
{
    while(_sTravMask.empty() == false)
        _sTravMask.pop();

    return Continue;
}

Action::ResultE Action::stop(ResultE res)
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

Action::FunctorStore *Action::getDefaultEnterFunctors(void)
{
    return _defaultEnterFunctors;
}

Action::FunctorStore *Action::getDefaultLeaveFunctors(void)
{
    return _defaultLeaveFunctors;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

// default Action function: just call all kids

Action::ResultE Action::_defaultEnterFunction(NodeCore * const,
                                              Action   *      )
{
    return Continue;
}

Action::ResultE Action::_defaultLeaveFunction(NodeCore * const,
                                              Action   *      )
{
    return Continue;
}

/*************** Functions ******************/

OSG_BEGIN_NAMESPACE

/*! Simple tree traversal function. Calls func for every node encountered
 */

Action::ResultE traverse(const std::vector<Node *>  &nodeList,
                               TraverseEnterFunctor  func    )
{
    Action::ResultE res = Action::Continue;

    std::vector<Node *>::const_iterator it = nodeList.begin();
    std::vector<Node *>::const_iterator en = nodeList.end  ();

    for(; it != en; ++it)
    {
        res = traverse((*it), func);

        if(res == ActionBase::Quit)
            break;
    }

    return res;
}

Action::ResultE traverse(const MFUnrecChildNodePtr  &nodeList,
                               TraverseEnterFunctor  func    )
{
    Action::ResultE res = Action::Continue;

    MFUnrecChildNodePtr::const_iterator it = nodeList.begin();
    MFUnrecChildNodePtr::const_iterator en = nodeList.end  ();

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

Action::ResultE traverse(Node                 * const node,
                         TraverseEnterFunctor         func )
{
    Action::ResultE res = Action::Continue;

    res = func(node);

    if(node == NULL)
        return Action::Continue;

    RootGroup *pRGroup = dynamic_cast<RootGroup *>(node->getCore());

    switch(res)
    {
        case Action::Skip:
            return Action::Continue;

        case Action::Continue:
        {
            if(pRGroup != NULL && pRGroup->getRoot() != NULL)
            {
                return traverse(pRGroup->getRoot(), func);
            }
            else
            {
                return traverse(*(node->getMFChildren()),
                                func                    );
            }
        }
        break;

        default:
            break;
    }

    return res;
}

/*! Simple tree traversal function. Calls enter before entering a node,
    leave after leaving.
 */

Action::ResultE traverse(const std::vector<Node *> &nodeList,
                               TraverseEnterFunctor  enter,
                               TraverseLeaveFunctor  leave )
{
    Action::ResultE res = Action::Continue;

    std::vector<Node *>::const_iterator it = nodeList.begin();
    std::vector<Node *>::const_iterator en = nodeList.end  ();

    for(; it != en; ++it)
    {
        res = traverse((*it), enter, leave);

        if(res == Action::Quit)
            break;
    }

    return res;
}

Action::ResultE traverse(const MFUnrecChildNodePtr  &nodeList,
                               TraverseEnterFunctor  enter,
                               TraverseLeaveFunctor  leave )
{
    Action::ResultE res = Action::Continue;

    MFUnrecChildNodePtr::const_iterator it = nodeList.begin();
    MFUnrecChildNodePtr::const_iterator en = nodeList.end  ();

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

Action::ResultE traverse(Node                 * const node,
                         TraverseEnterFunctor         enter,
                         TraverseLeaveFunctor         leave)
{
    Action::ResultE res = Action::Continue;

    res = enter(node);

    RootGroup *pRGroup = dynamic_cast<RootGroup *>(node->getCore());

    switch(res)
    {
        case Action::Skip:
            res = Action::Continue;
            break;

        case Action::Continue:
        {
            if(pRGroup != NULL && pRGroup->getRoot() != NULL)
            {
                res = traverse(pRGroup->getRoot(), enter, leave);
            }
            else
            {
                res = traverse(*(node->getMFChildren()),
                               enter,
                               leave                   );
            }
        }
        break;
        default:
            break;
    }

    res = leave(node, res);

    return res;
}

OSG_END_NAMESPACE
