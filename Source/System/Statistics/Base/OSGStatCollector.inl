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
OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/

inline 
UInt32 StatCollector::getNumOfElems(void) const
{
    return _elemVec.size();
}

/*-------------------------------------------------------------------------*/

inline 
bool StatCollector::isValidID(Int32 id) const
{
    return (id >= 0) && (id < Int32(_elemVec.size()));
}

/*-------------------------------------------------------------------------*/

/*! Return a pointer to the StatElem for the id. 
    This function has two modes. By default it's careful and sets
    the create argument to true. In this case it checks whether the 
    Collector already contains a StatElem for the given id and creates
    it if necessary. If you know that your Collector already contains that
    element (because you explicitly created it outside the testing loop)
    you can set it to false and speed up the whole function a bit.
*/

inline 
StatElem *StatCollector::getElem(Int32 id, bool create)
{
    if(create == true)
    {
        // This only happens when dynamically adding StatElems
        // but it's really nasty if it happens.

        if(id >= int(_elemVec.size())) 
            refitElemNum();
        
        StatElem *elem = _elemVec[id];

        if(elem == NULL)
        {
            StatElemDescBase    *desc = StatElemDescBase::getDesc(id);
            elem = _elemVec[id] = desc->createElem();
        }

        return elem;
    }

    return _elemVec[id];
}


/*! Return a pointer to the StatElem for the id. 
    It will returnn NULL if the element doesn't exist yet.
*/

inline StatElem *StatCollector::getElem(Int32 id) const
{
    return _elemVec[id];
}

/*-------------------------------------------------------------------------*/

inline 
StatElem *StatCollector::getElem(StatElemDescBase &desc, bool create)
{
    return getElem(desc.getID(), create);
}

/*-------------------------------------------------------------------------*/

template<class T> inline
T *StatCollector::getElem(StatElemDesc<T> &desc, bool create)
{
    return reinterpret_cast < T * > (getElem(desc.getID(), create));
}

OSG_END_NAMESPACE

#define OSGSTATCOLLECTOR_INLINE_CVSID "@(#)$Id: $"
