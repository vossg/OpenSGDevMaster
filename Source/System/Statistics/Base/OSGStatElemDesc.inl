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
bool StatElemDescBase::isValidID(Int32 descId)
{ 
    return (_descVec && (descId >= 0) && (descId < static_cast<Int32>(_descVec->size())));
}

/*-------------------------------------------------------------------------*/

inline
StatElemDescBase *StatElemDescBase::getDesc(Int32 descId)
{ 
    return (*_descVec)[descId];
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

/*-------------------------------------------------------------------------*/

inline
StatElemDescBase::ResetMode StatElemDescBase::getResetMode(void) const
{ 
    return _resetMode; 
}


// The templated StatElemDesc

template <class T> inline
StatElemDesc<T>::StatElemDesc(const Char8 *name, 
                              const Char8 *description,
                              ResetMode reset) :
    StatElemDescBase(name, description, reset)
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
