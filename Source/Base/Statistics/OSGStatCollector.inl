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

/*! Returns the number StatElems this collector can currently store.
    Normally this corresponds to the number of registered StatElems in the
    system, only if new ones were registered after this collector instance was
    created the numbers can differ.

    \warning This is not the number of StatElems actually stored in this
    collector.

    \return Number of StatElems this collector can currently store.
 */

inline
UInt32 StatCollector::getNumOfElems(void) const
{
    return _elemVec.size();
}

/*-------------------------------------------------------------------------*/

/*! Tests if the given \a id is valid for this collector, i.e. if it can be
    used to refer to a StatElem in it.

    \warning It does not test if there actually is a StatElem with this id in
    this collector, only if there can be one.
 */

inline
bool StatCollector::isValidID(Int32 elemId) const
{
    return (elemId >= 0) && (elemId < static_cast<Int32>(_elemVec.size()));
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
StatElem *StatCollector::getElem(Int32 elemId, bool create)
{
    if(create == true)
    {
        // This only happens when dynamically adding StatElems
        // but it's really nasty if it happens.

        if(elemId >= static_cast<Int32>(_elemVec.size()))
            refitElemNum();

        StatElem *elem = _elemVec[elemId];

        if(elem == NULL)
        {
            StatElemDescBase    *desc = StatElemDescBase::getDesc(elemId);
            elem = _elemVec[elemId] = desc->createElem();
        }

        return elem;
    }

    return isValidID(elemId) ? _elemVec[elemId] : NULL;
}


/*! Return a pointer to the StatElem for the id.
    It will return NULL if the element doesn't exist yet.

    \param[in] elemId Id of the StatElem to return.
    \return StatElem with given id, or NULL if it does not exist.
*/

inline StatElem *StatCollector::getElem(Int32 elemId) const
{
    return isValidID(elemId) ? _elemVec[elemId] : NULL;
}

/*-------------------------------------------------------------------------*/

/*! Return the StatElem for the given descriptor \a desc. If the StatElem
    does not yet exist in this collector and \a create is true, it will be
    created. If \a create is false only existing StatElems will be returned and
    NULL for those that do not exist yet.

    \param[in] desc Descriptor for the StatElem to return.
    \param[in] create If true, not existing StatElem will be created.
    \return StatElem for the given descriptor, or NULL if it does not exist.
 */

inline
StatElem *StatCollector::getElem(StatElemDescBase &desc, bool create)
{
    return getElem(desc.getID(), create);
}

/*-------------------------------------------------------------------------*/

/*! Return a typed StatElem for the given descriptor \a desc. If the StatElem
    does not yet exist in this collector and \a create is true, it will be
    created. If \a create is false only existing StatElems will be returned and
    NULL for those that do not exist yet.
    The return value will be a pointer to a subclass of StatElem, the exact type
    depends on the type of \a desc.

    \param[in] desc Descriptor for the StatElem to return.
    \param[in] create If true, not existing StatElem will be created.
    \return StatElem for the given descriptor, or NULL if it does not exist.
 */

template<class T> inline
T *StatCollector::getElem(StatElemDesc<T> &desc, bool create)
{
    return reinterpret_cast<T*>(getElem(desc.getID(), create));
}

OSG_END_NAMESPACE
