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


#ifndef _OSGPRUNEGRAPHOP_H_
#define _OSGPRUNEGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

class OSG_UTIL_DLLMAPPING PruneGraphOp : public GraphOp
{
public:
    enum Method {
        VOLUME,
        SUM_OF_DIMENSIONS,
    };

    static const char *getClassname(void) { return "PruneGraphOp"; };

    PruneGraphOp(
        float size = 1.0f,
        Method method = SUM_OF_DIMENSIONS,
        const char* name = "Prune");

    GraphOp* create();

    void setParams(const std::string params);
    
    std::string usage(void);

private:
    Action::ResultE traverseEnter(NodePtrConstArg node);
    Action::ResultE traverseLeave(NodePtrConstArg node, Action::ResultE res);

    bool isTooSmall(const NodePtr& node);
    float getSize(const NodePtr& node);

    float _size;
    Method _method;
};

OSG_END_NAMESPACE

#endif
