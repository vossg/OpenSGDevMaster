/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline 
NodePtr Action::getActNode(void)
{
    return _actNode;
}

    
inline 
void Action::setActNode(const NodePtr node)
{
    _actNode = node;
}

inline
NodePtr Action::getNode(int index)
{
    if(_actList == NULL)
    {
        return _actNode->getChild(index);
    }
    else
    {
        return (*_actList)[index];
    }
}

inline
void Action::addNode(const NodePtr node)
{
    _newList.push_back(node);
}

inline
void Action::useNodeList(bool bVal)
{
    _useNewList = bVal;
}

inline
UInt32 Action::getNNodes(void) const
{
    if(_actList == NULL)
    {
        return _actNode->getNChildren();
    }
    else
    {
        return (*_actList).size();
    }
}


inline
UInt32 Action::getTravMask(void) const
{
    return _travMask;
}

inline
void Action::setTravMask(UInt32 val)
{
    _travMask = val;
}

/*-------------------------- your_category---------------------------------*/

// callEnter/callLeave: call the right functor. If the type is unknown and new
// (i.e. its index is larger than the vector) try to find the function in the
// default list.

inline
ActionBase::ResultE Action::callEnter(const NodeCorePtr core)
{
    ResultE result;

    UInt32 uiFunctorIndex = core->getType().getId();

    if(uiFunctorIndex < _enterFunctors.size())
    {
        result = _enterFunctors[uiFunctorIndex](core, this);
    }
    else if(getDefaultEnterFunctors() &&
            uiFunctorIndex < getDefaultEnterFunctors()->size())
    {
        // field container registered method after this action was instantiated
        // copy the new functors from default vector

        std::vector<Functor> *defaultEnter = getDefaultEnterFunctors();

        while(defaultEnter->size() > _enterFunctors.size())
        {
            _enterFunctors.push_back((*defaultEnter)[_enterFunctors.size()]);
        }

        result = _enterFunctors[uiFunctorIndex](core, this);
    }
    else // unknown field container
    {
        result = _defaultEnterFunction(core, this);
    }

    return result;
}

inline
ActionBase::ResultE Action::callLeave(const NodeCorePtr core)
{
    ResultE result;

    UInt32 uiFunctorIndex = core->getType().getId();

    if(uiFunctorIndex < _leaveFunctors.size())
    {
        result = _leaveFunctors[uiFunctorIndex](core, this);
    }
    else if(getDefaultLeaveFunctors() &&
            uiFunctorIndex < getDefaultLeaveFunctors()->size())
    {
        // field container registered method after this action was instantiated
        // copy the new functors from default vector

        std::vector<Functor> *defaultLeave = getDefaultLeaveFunctors();

        while(defaultLeave->size() > _leaveFunctors.size())
        {
            _leaveFunctors.push_back((*defaultLeave)[_leaveFunctors.size()]);
        }

        result = _leaveFunctors[uiFunctorIndex](core, this);
    }
    else // unknown field container
    {
        result = _defaultLeaveFunction(core, this);
    }

    return result;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */


/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */


/** \brief equal
 */


/** \brief unequal
 */



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
