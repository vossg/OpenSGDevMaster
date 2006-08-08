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

#include <OSGGraphOpSeq.h>
#include <OSGGraphOpFactory.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GraphOpSeq
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

GraphOpSeq::GraphOpSeq(): _GraphOperators(), _excludeNames()
{
}

GraphOpSeq::GraphOpSeq(const std::string params): 
    _GraphOperators(), _excludeNames()
{
    setGraphOps(params);
}

GraphOpSeq::~GraphOpSeq()
{
}

bool GraphOpSeq::run(NodePtr &root)
{
    bool res=true;
    std::vector<GraphOp *>::iterator it=_GraphOperators.begin();
    std::vector<GraphOp *>::iterator en=_GraphOperators.end();

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
    <GraphOpName1>(<param1>,<param2>,...,<paramN>) <GraphOpName2>() ...
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

void GraphOpSeq::setGraphOps(const std::string params)
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
        
        GraphOp * go = GraphOpFactory::the().create(goname.c_str());
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
            _GraphOperators.push_back(go);
        }
    }
}

void GraphOpSeq::addGraphOp(GraphOp *op)
{
    _GraphOperators.push_back(op);
}

void GraphOpSeq::removeGraphOp(GraphOp *op)
{
    std::vector<GraphOp *>::iterator it=_GraphOperators.begin();
    for (; it!=_GraphOperators.end(); ++it)
        if (*it==op)
        {
            _GraphOperators.erase(it);
            break;
        }
}

void GraphOpSeq::clearGraphOps(void)
{
    _GraphOperators.clear();
}

UInt16 GraphOpSeq::getSize(void)
{
    return _GraphOperators.size();
}

GraphOp* GraphOpSeq::getGraphOp(UInt16 index)
{
    if (index<getSize())
        return _GraphOperators[index];
    else
        return NULL;
}

bool GraphOpSeq::setGraphOp(UInt16 index, GraphOp *op)
{
    if (index<getSize())
    {
        _GraphOperators[index]=op;
        return true;
    }
    else
        return false;
}

bool GraphOpSeq::removeGraphOp(UInt16 index)
{
    if (index<getSize())
    {
        _GraphOperators.erase(_GraphOperators.begin()+index);
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

UInt16 GraphOpSeq::extractStr(const std::string param, UInt16 spos, 
        char* delim, std::string& result)
{
    std::string::size_type pos = param.find(delim,spos);
    if (pos == std::string::npos) 
        pos = param.length();

    result=param.substr(spos,pos-spos);
    return pos+1;
}
