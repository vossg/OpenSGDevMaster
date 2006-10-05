/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2003 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGTypeBase.h"
#include "OSGTypeFactory.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

TypeBase::TypeBase(const TypeBase &source) :
    _uiTypeId    (source._uiTypeId    ),
    //_uiTypeRootId(source._uiTypeRootId),
    _uiNameSpace (source._uiNameSpace ),

    _pParentType (source._pParentType ),

    _szName      (source._szName      ),
    _szParentName(source._szParentName),

    _bInitialized(source._bInitialized)
{
}

bool TypeBase::initialize(void)
{
    if(_bInitialized == true)
        return _bInitialized;

    if(_szParentName.isEmpty() == false)
    {
        _pParentType =
            TypeFactory::the()->findType(_szParentName.str(), _uiNameSpace);

        if(_pParentType == NULL)
        {
            _pParentType =
                TypeFactory::the()->findType(_szParentName.str(),
                                              GlobalNamespace);
        }

        if(_pParentType == NULL)
        {
            SWARNING << "ERROR: could not find parent type named "
                     << _szParentName.str()
                     << " in "
                     << _szName.str()
                     << std::endl;
        }
        else
        {
            _bInitialized = _pParentType->initialize();
        }
    }
    else
    {
        _bInitialized = true;
    }

    PNOTICE << "Initialized Type "
            << _szName.str()
            << " | "
            << _bInitialized
            << std::endl;

    return _bInitialized;
}

void TypeBase::terminate (void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

TypeBase::TypeBase(const Char8 *szName,
                   const Char8 *szParentName,
                   const UInt32 uiNameSpace) :
    _uiTypeId    (           0),
    //_uiTypeRootId(           0),
    _uiNameSpace (uiNameSpace ),

    _pParentType (NULL        ),

    _szName      (szName      ),
    _szParentName(szParentName),

    _bInitialized(false       )
{
    _uiTypeId = TypeFactory::the()->registerType(this);
}

TypeBase::~TypeBase(void)
{
}


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief Get method for attribute Id
 */

UInt32 TypeBase::getId(void) const
{
    return _uiTypeId;
}

/** \brief Get method for attribute name
 */

const IDString &TypeBase::getName(void) const
{
    return _szName;
}

/** \brief Get method for name as c string
 */

const Char8 *TypeBase::getCName(void) const
{
    return _szName.str();
}

const TypeBase &TypeBase::getParent(void) const
{
   return (*_pParentType);
}
const IDString &TypeBase::getParentName (void) const
{
    return _szParentName;
}

const Char8 *TypeBase::getCParentName(void) const
{
    return _szParentName.str();
}

UInt32 TypeBase::getNameSpace(void) const
{
    return _uiNameSpace;
}

/*-------------------------- inheriteance ---------------------------------*/

bool TypeBase::isInitialized(void) const
{
    return _bInitialized;
}

bool TypeBase::isDerivedFrom(const TypeBase &other) const
{
    bool      returnValue = false;
    TypeBase *pCurrType   = _pParentType;

    if(_uiTypeId == other._uiTypeId)
    {
        returnValue = true;
    }
    else
    {
        while(pCurrType != NULL && returnValue == false)
        {
            if(other._uiTypeId == pCurrType->_uiTypeId)
            {
                returnValue = true;
            }
            else
            {
                pCurrType = pCurrType->_pParentType;
            }
        }
    }

    return returnValue;
}

/*-------------------------- comparison -----------------------------------*/

bool TypeBase::operator ==(const TypeBase &other) const
{
    return _uiTypeId == other._uiTypeId;
}

bool TypeBase::operator !=(const TypeBase &other) const
{
    return ! (*this == other);
}

/*------------------------- comparison ----------------------------------*/

void TypeBase::dump(      UInt32    uiIndent,
                    const BitVector         ) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "TypeBase : " << getId() << " | " << getCName() << std::endl;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif


namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGTYPEBASE_HEADER_CVSID;
}
