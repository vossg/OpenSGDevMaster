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


#ifndef _OSGPARENTCONTAINER_H_
#define _OSGPARENTCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

template <class Object, class Ptr>
struct PtrWrapper
{
    typedef PtrWrapper<Object, Ptr> Self;
    typedef Ptr                     Pointer;
    typedef Object                  StoredObject;

    Ptr    _ptr;

    UInt16 _parentFPos;

    PtrWrapper(void) : 
        _ptr       (NULL),
        _parentFPos(0xFFFF)
      
    {
    }
    
    PtrWrapper(Ptr ptr) :
        _ptr(ptr),
        _parentFPos(0xFFFF)
    {
    } 

    ~PtrWrapper(void) 
    {
    }

    void setParentFieldPos(UInt16 parentFPos)
    {
        _parentFPos = parentFPos;
    }

    UInt16 getParentFieldPos(void)
    {
        return _parentFPos;
    }

    Ptr getCPtr(void)
    {
        return _ptr;
    }
    
    void addReference(void) const
    {
        _ptr->addReference();
    }

    void subReference(void) const
    {
        _ptr->subReference();
    }

    operator Ptr(void) const
    {
        return _ptr;
    }

    Object &operator *(void)
    {
        return *_ptr;
    }

    Object &operator *(void) const
    {
        return *_ptr;
    }

    Ptr operator->(void)
    {
        return _ptr;
    }

    Ptr operator->(void) const 
    {
        return _ptr;
    }

    bool operator ==(const Self &other) const
    {
        return _ptr == other._ptr;
    }

    bool operator ==(const Ptr other) const
    {
        return _ptr == other;
    }

/*
    bool operator ==(const int other) const
    {
        return _ptr == NULL;
    }

    bool operator !=(const int other) const
    {
        return _ptr != NULL;
    }
 */
};

typedef PtrWrapper<FieldContainer,
                   FieldContainerPtr>        ParentFieldContainerPtr;

typedef PtrWrapper<FieldContainer,
                   FieldContainerPtr> const &ParentFieldContainerPtrConstArg;

typedef PtrWrapper<FieldContainer,
                   FieldContainerPtr> const  ParentFieldContainerPtrConst;

typedef PtrWrapper<Node,
                   NodePtr          >        ParentNodePtr;

typedef PtrWrapper<FieldBundle,
                   FieldBundleP>             ParentFieldBundleP;

typedef PtrWrapper<FieldBundle,
                   FieldBundleP> const      &ParentFieldBundlePConstArg;

typedef PtrWrapper<FieldBundle,
                   FieldBundleP> const       ParentFieldBundlePConst;

OSG_END_NAMESPACE

#endif /* _OSGPARENTCONTAINER_H_ */
