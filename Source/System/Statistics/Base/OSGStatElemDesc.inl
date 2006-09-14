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
bool StatElemDescBase::isValidID(Int32 id)
{ 
    return (_descVec && (id >= 0) && (id < Int32(_descVec->size()))); 
}

/*-------------------------------------------------------------------------*/

inline
StatElemDescBase *StatElemDescBase::getDesc(Int32 id)
{ 
    return (*_descVec)[id]; 
}

/*-------------------------------------------------------------------------*/

inline
Int32 StatElemDescBase::getNumOfDescs(void)
{ 
    return _descVec ? _descVec->size() : 0; 
}

/*-------------------------------------------------------------------------*/

inline
Int32 StatElemDescBase::getID(void) 
{ 
    return _id; 
}

/*-------------------------------------------------------------------------*/

inline  
const IDString &StatElemDescBase::getName(void) 
{ 
    return _name; 
}

/*-------------------------------------------------------------------------*/

inline
const IDString &StatElemDescBase::getDescription(void) 
{ 
    return _description; 
}



// The templated StatElemDesc

template <class T> inline
StatElemDesc<T>::StatElemDesc(const Char8 *name, 
                              const Char8 *description) :
    StatElemDescBase(name, description)
{
}


template <class T> inline
StatElemDesc<T>::~StatElemDesc()
{
}


template <class T> inline
StatElem *StatElemDesc<T>::createElem(void)
{
    return T::create(this);
}


OSG_END_NAMESPACE

#define OSGSTATELEMDESC_INLINE_CVSID "@(#)$Id$"
