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

#include "OSGGraphOpSeq.h"
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GraphOpSeq
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/



/*------------- constructors & destructors --------------------------------*/

GraphOpSeq::GraphOpSeq(void) :
    Inherited      (),
    _graphOperators(),
    _excludeNames  ()
{
}

GraphOpSeq::GraphOpSeq(const std::string &params) :
    Inherited      (),
    _graphOperators(),
    _excludeNames  ()
{
    setGraphOps(params);
}

GraphOpSeq::ObjTransitPtr GraphOpSeq::create(void)
{
    return ObjTransitPtr(new GraphOpSeq());
}

GraphOpSeq::ObjTransitPtr GraphOpSeq::create(const std::string &params)
{
    return ObjTransitPtr(new GraphOpSeq(params));
}

GraphOpSeq::~GraphOpSeq()
{
}

#ifndef OSG_DISABLE_DEPRECATED
/*! \deprecated Use GraphOpSeq::traverse instead.
 */
bool GraphOpSeq::run(Node *root)
{
    return traverse(root);
}
#endif

/*! Apply the sequence to the tree starting at \a root.
 */
bool GraphOpSeq::traverse(Node *root)
{
    bool res=true;
    std::vector<GraphOpRefPtr>::iterator it = _graphOperators.begin();
    std::vector<GraphOpRefPtr>::iterator en = _graphOperators.end();

    for ( ; it != en; ++it )
    {
        bool b = (*it)->traverse(root);
        res = res & b;
        if (!b)
            FWARNING(("GraphOpSeq: GraphOp %s could not traverse the scene correctly\n",(*it)->getName().c_str()));
    }

    return res;
}

/*!
    Creates the GraphOps automatically using a string.
    Every GraphOp has a special unique name.
    This name is how the GraphOp is recognized.   
    
    Format of the string:
    &lt;GraphOpName1&gt;(&lt;param1&lt;,&lt;param2&lt;,...,&lt;paramN&lt;) &lt;GraphOpName2&lt;() ...
    Basically you give a GraphOp name, then in brackets all
    parameters that should be passed to its setParams(...). 
    
    There are two special cases: Exclude and AddExclude
    The first one sets and the second one adds a new list of names.
    
    P.S. There is no error handling to keep things simple. Pass as 
    parameters only strings which can be processed correctly.
    Examples:
    
    Exclude(Me,You) Verify(true) AddExclude(Us,Them) Merge() Exclude(All) 
    Split(max_polygons=1500) Verify(repair=true) Exclude(Node1,Node2) 
    Merge() Stripe(stitch=true force=true)   
*/

void GraphOpSeq::setGraphOps(const std::string &params)
{
    UInt16 counter = 0;
    while (counter < params.length())
    {
        //eat all intervals
        while (params[counter]==' ') 
            counter++;
       
        std::string command;
        counter = extractStr(params, counter, ")", command) + 1;
        FDEBUG(("command: %s\n", command.c_str()));

        //extract the command from the substring
        std::string goname;
        UInt16 pos = extractStr(command, 0, "(", goname);
        FDEBUG(("GraphOpSeq::setGraphOps: goname: %s\n",goname.c_str()));
        
        GraphOpRefPtr go = GraphOpFactory::the()->create(goname.c_str());
        if (go == NULL)
        {
            if (goname=="Exclude" || goname=="AddExclude")
            {
                if (goname=="Exclude") 
                    _excludeNames.clear();
                    
                std::string cparams;
                extractStr(command, pos, ")", cparams);
                FDEBUG(("GraphOpSeq::setGraphOps: cparams: %s\n", cparams.c_str()));
                UInt16 i = 0;
                while(i < cparams.length())
                {
                    std::string ename;
                    i = extractStr(cparams, i, ",", ename);
                    _excludeNames.push_back(ename);
                    FDEBUG(("GraphOpSeq::setGraphOps: ename: %s\n",ename.c_str()));
                }
                
            }
            else
                FWARNING(("GraphOpSeq::setGraphOps: Invalid GraphOp name given: %s\n",goname.c_str()));
        }
        else
        {
            std::string goparams;
            extractStr(command, pos, ")", goparams);            
            FDEBUG(("GraphOpSeq::setGraphOps: goparams: %s\n", goparams.c_str()));
            go->setParams(goparams);
            std::list<std::string>::iterator it=_excludeNames.begin();
            for (; it!=_excludeNames.end(); ++it)
            {
                go->addToExcludeList(*it);
                FDEBUG(("GraphOpSeq::setGraphOps: Added to op: %s\n",(*it).c_str()));
            }
            
            _graphOperators.push_back(go);
        }
    }
}

void GraphOpSeq::addGraphOp(GraphOp *op)
{
    _graphOperators.push_back(op);
}

void GraphOpSeq::removeGraphOp(GraphOp *op)
{
    std::vector<GraphOpRefPtr>::iterator it = _graphOperators.begin();

    for(; it != _graphOperators.end(); ++it)
    {
        if(*it == op)
        {
            _graphOperators.erase(it);
            break;
        }
    }
}

void GraphOpSeq::clearGraphOps(void)
{
    _graphOperators.clear();
}

UInt16 GraphOpSeq::getSize(void)
{
    return _graphOperators.size();
}

GraphOp* GraphOpSeq::getGraphOp(UInt16 index)
{
    if(index < getSize())
        return _graphOperators[index];
    else
        return NULL;
}

bool GraphOpSeq::setGraphOp(UInt16 index, GraphOp *op)
{
    if(index < getSize())
    {
        _graphOperators[index]=op;
        return true;
    }
    else
        return false;
}

bool GraphOpSeq::removeGraphOp(UInt16 index)
{
    if (index<getSize())
    {
        _graphOperators.erase(_graphOperators.begin() + index);
        return true;
    }
    else
        return false;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

UInt16 GraphOpSeq::extractStr(const std::string  param, 
                                    UInt16       spos, 
                              const Char8       *delim, 
                                    std::string &result)
{
    std::string::size_type pos = param.find(delim,spos);
    if (pos == std::string::npos) 
        pos = param.length();

    result = param.substr(spos, pos - spos);
    return pos+1;
}
