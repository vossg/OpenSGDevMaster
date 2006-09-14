/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

OSG_BEGIN_NAMESPACE

template <class ParentT>
RefCountMixin<ParentT>::RefCountMixin(void) :
     Inherited( ),
    _iRefCount(0)
{
}

template <class ParentT>
RefCountMixin<ParentT>::RefCountMixin(const RefCountMixin &source) :
     Inherited(source),
    _iRefCount(     0)
{
}

template <class ParentT>
RefCountMixin<ParentT>::~RefCountMixin(void)
{
}

template <class ParentT>
void RefCountMixin<ParentT>::addReference(void)
{
    ++_iRefCount;
    
    Thread::getCurrentChangeList()->addAddRefd(Inherited::getId());

}

template <class ParentT>
void RefCountMixin<ParentT>::subReference(void)
{
    Thread::getCurrentChangeList()->addSubRefd(Inherited::getId());

    --_iRefCount;

    if(_iRefCount <= 0)
    {
        this->onDestroy   (Inherited::getId());
        this->resolveLinks(                  );

        delete this;
    }
}

OSG_END_NAMESPACE

#define OSGREFCOUNTMIXIN_INLINE_CVSID "@(#)$Id$"

