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

#include "OSGSystemDef.h"
#include "OSGAction.h"
#include "OSGGraphOp.h"
#include "OSGSingletonHolder.h"

OSG_BEGIN_NAMESPACE

/*! \brief GraphOpFactory class
    \ingroup GrpSystemGraphOp
    \ingroup GrpSystemMemoryObjects
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING GraphOpFactoryBase
{
  public:
    typedef std::map<std::string, GraphOpRefPtr> TypeMap;
    typedef TypeMap::iterator                    TypeMapIt;
    typedef TypeMap::const_iterator              TypeMapConstIt;
    
    void registerOp  (      GraphOp* prototype);
    void unRegisterOp(      GraphOp* prototype);
    void unRegisterOp(const char*    name     );
        
    GraphOpTransitPtr create(const char* name);

    TypeMapConstIt begin(void) const;
    TypeMapConstIt end  (void) const;
    
  private:

    template <class SingletonT>
    friend class SingletonHolder;

    GraphOpFactoryBase(void);
    ~GraphOpFactoryBase(void);

    TypeMap _typeMap;
};

/*! \typedef OSG::SingletonHolder<OSG::GraphOpFactoryBase> GraphOpFactory;
    \ingroup GrpSystemGraphOp
    \relatesalso OSG::GraphOpFactoryBase
 */

typedef SingletonHolder<GraphOpFactoryBase> GraphOpFactory;

typedef GraphOpFactory *GraphOpFactoryP;

OSG_END_NAMESPACE

#endif /* _OSGGRAPHOPSEQ_H_ */

