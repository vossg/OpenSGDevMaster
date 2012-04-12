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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include <cstring>
#include <boost/bind.hpp>

#include "OSGGraphOp.h"
#include "OSGNameAttachment.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

Parameters are generally passed using the setParams() method (or indirectly
from constructing a GraphOpSeq via string) and follow the following 
conventions:

- Parameters are a key=value pair (e.g. max_polygons=1000). Note that
  there can be no spaces around the =, and that parameter values cannot
  contain spaces or ')' either right now.
- Special case: boolean parameters. If just the name is given, this is
  considered equivalent to True.
- Multiple parameters are separated by spaces.

Calling usage() gives a short textual desription of the purpose and
parameters of a GraphOp.
*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

GraphOp::GraphOp(const char* name): 
    Inherited(),
    _excludeListNodes(), 
    _excludeListNames(),
    _name(name)
{
}

GraphOp::~GraphOp(void)
{
}

bool GraphOp::traverse(Node *node)
{
    Action::ResultE res;
    /*
    res = ::traverse(node,
          osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE,
          GraphOp,
          NodePtr>(this,&GraphOp::traverseEnter),
          osgTypedMethodFunctor2ObjPtrCPtrRef<Action::ResultE,
          GraphOp,
          NodePtr,
          Action::ResultE>(this,&GraphOp::traverseLeave));
    */
    res = ::traverse(node, 
                     boost::bind(&GraphOp::traverseEnter, this, _1    ),
                     boost::bind(&GraphOp::traverseLeave, this, _1, _2) );

    if (res == Action::Continue) 
        return true;
    else 
        return false;
}

const std::string & GraphOp::getName(void)
{
    return _name;
};

void GraphOp::setName(const char *name)
{
    _name = name;
};

/*--------------------------- Exclude List --------------------------------*/

void GraphOp::addToExcludeList(Node * const node)
{
    if (!isInExcludeListNodes(node))
        _excludeListNodes.push_back(node);
}

void GraphOp::addToExcludeList(const std::string &name)
{
    if (!isInExcludeListNames(name))
        _excludeListNames.push_back(name);
}

void GraphOp::removeFromExcludeList(Node * const node)
{
    _excludeListNodes.remove(node);
}

void GraphOp::removeFromExcludeList(const std::string &name)
{
    _excludeListNames.remove(name);
}

void GraphOp::clearExcludeList(void)
{
    _excludeListNames.clear();
    _excludeListNodes.clear();
}

bool GraphOp::isInExcludeListNodes(Node * const node) const
{
    NodeListType::const_iterator nodeIt;
    nodeIt = std::find(_excludeListNodes.begin(),
                       _excludeListNodes.end  (), node);

    if(nodeIt == _excludeListNodes.end())
        return false;
    else
        return true;
}

bool GraphOp::isInExcludeListNames(const std::string &name) const
{
    NameListType::const_iterator nameIt;
    nameIt = std::find(_excludeListNames.begin(),
                       _excludeListNames.end  (), name);

    if(nameIt == _excludeListNames.end())
        return false;
    else
        return true;
}

bool GraphOp::isInExcludeList(Node * const node) const
{
    if(isInExcludeListNodes(node) ||
       (OSG::getName(node) != NULL && isInExcludeListNames(OSG::getName(node))))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GraphOp::addToPreserveList(Node * const node)
{
    if(!isInPreserveListNodes(node))
        _preserveListNodes.push_back(node);
}

void GraphOp::addToPreserveList(const std::string &name)
{
    if(!isInPreserveListNames(name))
        _preserveListNames.push_back(name);
}

void GraphOp::removeFromPreserveList(Node * const node)
{
    _preserveListNodes.remove(node);
}

void GraphOp::removeFromPreserveList(const std::string &name)
{
    _preserveListNames.remove(name);
}

void GraphOp::clearPreserveList(void)
{
    _preserveListNodes.clear();
    _preserveListNames.clear();
}

bool GraphOp::isInPreserveListNodes(Node * const node) const
{
    NodeListType::const_iterator nodeIt;
    nodeIt = std::find(_preserveListNodes.begin(),
                       _preserveListNodes.end  (), node);

    if(nodeIt == _preserveListNodes.end())
        return false;
    else
        return true;
}

bool GraphOp::isInPreserveListNames(const std::string &name) const
{
    NameListType::const_iterator nameIt;
    nameIt = std::find(_preserveListNames.begin(),
                       _preserveListNames.end  (), name);

    if(nameIt == _preserveListNames.end())
        return false;
    else
        return true;
}

bool GraphOp::isInPreserveList(Node * const node) const
{
    if(isInPreserveListNodes(node) ||
       (OSG::getName(node) != NULL && isInPreserveListNames(OSG::getName(node))))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Parameter Helpers

GraphOp::ParamSet::ParamSet(const std::string &params) :
    _values(),
    _used()
{
    std::string::const_iterator it = params.begin(), end = params.end();
    
    std::string key, value;
    
    while(it != end)
    {
        char c = 0;
        
        key = "";
        value = "";
        
        // Read key
        while(it != end)
        {
            c = *it++;
            
            if(c == ' ' || c == '=')
                break;
            
            key += tolower(c);
        }
        
        // Do we have a value? Read it
        if (it != end && c == '=')
        {
            while(it != end)
            {
                c = *it++;

                if(c == ' ')
                    break;

                value += c;
            }           
        }

        // Add key, value pair
        
        FDEBUG(("GraphOp::ParamSet: key='%s', value='%s'\n", key.c_str(),
                                                             value.c_str()));

        _values.insert(valuesT::value_type(key, value));

        // Skip to next param

        while(it != end && (*it == ' ')) ;
   }
}

bool GraphOp::ParamSet::operator()(const char *name, std::string &val)
{
    valuesT::iterator it = _values.find(name);
    
    if(it != _values.end())
    {
        val = (*it).second;
        
        _used[name] = true;
        
        return true;
    }
    return false;
}
 
bool GraphOp::ParamSet::operator()(const char *name, Real32 &val)
{
    valuesT::iterator it = _values.find(name);
    
    if(it != _values.end())
    {
        const Char8* c = (*it).second.c_str();
        val = TypeTraits<Real32>::getFromCString(c);
        
        _used[name] = true;
        return true;
    }
    return false;
}

bool GraphOp::ParamSet::operator()(const char *name, UInt16 &val)
{
    valuesT::iterator it = _values.find(name);
    
    if(it != _values.end())
    {
        const Char8* c = (*it).second.c_str();
        val = TypeTraits<UInt16>::getFromCString(c);
        
        _used[name] = true;
        return true;
    }
    return false;
}

bool GraphOp::ParamSet::operator()(const char *name, UInt32 &val)
{
    valuesT::iterator it = _values.find(name);
    
    if(it != _values.end())
    {
        const Char8* c = (*it).second.c_str();
        val = TypeTraits<UInt32>::getFromCString(c);
        
        _used[name] = true;
        return true;
    }
    return false;
}

bool GraphOp::ParamSet::operator()(const char *name, Int32 &val)
{
    valuesT::iterator it = _values.find(name);
    
    if(it != _values.end())
    {
        const Char8* c = (*it).second.c_str();
        val = TypeTraits<Int32>::getFromCString(c);
        
        _used[name] = true;
        return true;
    }
    return false;
}

bool GraphOp::ParamSet::operator()(const char *name, bool &val)
{
    valuesT::iterator it = _values.find(name);
    
    if(it != _values.end())
    {
        if((*it).second.length() == 0)
        {
            val = true;
        }
        else
        {
            const Char8* c = (*it).second.c_str();
            val = TypeTraits<bool>::getFromCString(c);
        }
        
        _used[name] = true;
        return true;
    }
    return false;
}

void GraphOp::ParamSet::markUsed(const char *name)
{
    _used[name] = true;
}

std::string GraphOp::ParamSet::getUnusedParams(void)
{
    std::string out;
    
    for (valuesT::iterator it = _values.begin(); it != _values.end(); ++it)
    {
        usedT::iterator uit = _used.find((*it).first);
        
        if(uit == _used.end())
        {
            if(out.length())
                out += " ";
                
            out += (*it).first;
        }
    }
 
    return out;   
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/
