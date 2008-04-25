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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGTypeBase.h"
#include "OSGTypeFactory.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class TypeBase
    \ingroup GrpBaseBaseTypeSystem
    \ingroup GrpBaseBase

    Base for all types in the type system.

    A type is uniquely defined by:
     - Name: The name of our type,
     - Namespace id: The namespace we belong to.

    The TypeBase object also tracks the name of the parent type, but this
    does not influence the unique identity of a type.
    This class uses the TypeFactory to register types with the running system,
    which assigns a unique id to every registered type.

    The creation/initialization of TypeBase (or derived classes) objects is
    split into two steps: First the constructor registers the type with the
    TypeFactory, but leaves some dependent members uninitialized. Second,
    when initialize is called these members are set (often with values obtained
    from the TypeFactory). This decouples the creation/initialization order from
    the inheritance hierarchy of the types.

    \see TypeFactory
 */

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

/*! Copy constructor, initializes all members with their respective value
    from \a source.

    \param[in] source Object to copy from.
 */
TypeBase::TypeBase(const TypeBase &source) :
    _uiTypeId    (source._uiTypeId    ),
    //_uiTypeRootId(source._uiTypeRootId),
    _uiNameSpace (source._uiNameSpace ),

    _pParentType (source._pParentType ),

    _szName      (source._szName      ),
    _szParentName(source._szParentName),

    _bInitialized(false               )
{
}

/*! Initialize this object and set dependent members.

    \return true if the initialization succeeded, false otherwise.
 */
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
                     << endLog;
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

    FDEBUG(("Initialized Type %s | %d\n",_szName.str(), _bInitialized));

    return _bInitialized;
}

/*! Perform cleanup operations for this object, does nothing for this class.
    Override in a derived class.
 */
void TypeBase::terminate (void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*! Constructor. The type described by this is registered with the TypeFactory
    and its name and parents name are set to the given values.

    \param[in] szName Name of the described type.
    \param[in] szParentName Name of the parent type.
    \param[in] uiNameSpace Namespace the described type belongs to.

    \note Some members only have valid values after initialize was called.
 */
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

/*! Destructor.
 */
TypeBase::~TypeBase(void)
{
}


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*! \brief Get method for attribute Id.

    \return The type id.
 */
UInt32 TypeBase::getId(void) const
{
    return _uiTypeId;
}

/*! \brief Get method for attribute name.

    \return The types name.
 */
const IDString &TypeBase::getName(void) const
{
    return _szName;
}

/*! \brief Get method for name as C string.

    \return The types name as a C string.
 */
const Char8 *TypeBase::getCName(void) const
{
    return _szName.str();
}

/*! Returns an object describing the parent of the type described by this.

    \return TypeBase instance describing the parent.

    \note This method can only be used after initialize has been called.
 */
const TypeBase &TypeBase::getParent(void) const
{
   return (*_pParentType);
}

/*! Returns the parent types name.

    \return Name of the parent type.
 */
const IDString &TypeBase::getParentName (void) const
{
    return _szParentName;
}

/*! Returns the parent types name as a C string.

    \return Name of the parent type as a C string.
 */
const Char8 *TypeBase::getCParentName(void) const
{
    return _szParentName.str();
}

/*! Returns the namespace the descibed type belongs to.

    \return Namespace of the type.
 */
UInt32 TypeBase::getNameSpace(void) const
{
    return _uiNameSpace;
}

/*-------------------------- inheriteance ---------------------------------*/

/*! Returns whether this was initialized.

    \return true if this was initialized, false otherwise.
 */
bool TypeBase::isInitialized(void) const
{
    return _bInitialized;
}

/*! Returns whether this type is derived from the type described by \a other.

    \param[in] other Type to test if it is a parent of this type.
    \return true if \a other is a parent of this type, false otherwise.

    \note This method can only be used after initialize has been called.
 */
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

/*! Compare two TypeBase objects for equality. They are equal, iff they
    describe the same type as determined by comparing the stored type ids.

    \param[in] other TypeBase instance to compare this with.
    \return true if this and \a other refer to the same type, false otherwise.
 */
bool TypeBase::operator ==(const TypeBase &other) const
{
    return _uiTypeId == other._uiTypeId;
}

/*! Compare two TypeBase objects for inequality. They are not equal if
    equality comparison returns false, i.e. they refer to different types.

    \param[in] other TypeBase instance to compare this with.
    \return true if this and \a other refer to different types, false otherwise.
 */
bool TypeBase::operator !=(const TypeBase &other) const
{
    return ! (*this == other);
}

/*------------------------- comparison ----------------------------------*/

/*! Print information about this object for debugging purposes.

    \param[in] uiIndent Number of spaces to indent output.
    \param[in] bvFlags Not used
 */
void TypeBase::dump(      UInt32    uiIndent,
                    const BitVector         ) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "TypeBase : " << getId() << " | " << getCName() << endLog;
}

OSG_END_NAMESPACE
