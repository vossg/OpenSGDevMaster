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


#ifndef _OSGGRAPHOPFACTORY_H_
#define _OSGGRAPHOPFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAction.h"
#include "OSGGraphOp.h"
#include "OSGSingletonHolder.h"

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! GraphOpSeq class

class OSG_SYSTEM_DLLMAPPING GraphOpFactoryBase
{
  public:
        
    void registerOp(GraphOp* prototype);
    void unRegisterOp(GraphOp* prototype);
    void unRegisterOp(const char* name);
        
    GraphOp *create(const char* name);

    
    /* map access */
    typedef std::map<std::string, GraphOp*>::const_iterator iterator;
    
    iterator begin(void);
    iterator end();  
    
  private:

    template <class SingletonT>
    friend class SingletonHolder;

    typedef std::map<std::string, GraphOp*>::iterator MapIt;

    typedef std::pair <std::string, GraphOp*> GraphOpPair;
        
    GraphOpFactoryBase(void);
    ~GraphOpFactoryBase(void);

    std::map<std::string, GraphOp*> _typeMap;
};

typedef SingletonHolder<GraphOpFactoryBase> GraphOpFactory;

typedef GraphOpFactory *GraphOpFactoryP;

OSG_END_NAMESPACE

#endif /* _OSGGRAPHOPSEQ_H_ */

