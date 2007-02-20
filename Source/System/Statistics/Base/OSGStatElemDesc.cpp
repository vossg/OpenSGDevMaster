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
 * by the Free Software Foundation, version 2.             
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

#include "OSGStatElemDesc.h"

#include "OSGLog.h"
#include "OSGBaseInitFunctions.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StatElemDescBase::DescStorage *StatElemDescBase::_descVec = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! Returns the descriptor with the given \a name, or NULL if no such
    descriptor is found.

    \param[i] name Name of the descriptor to return.
    \return Descriptor with the given name, or NULL if it is not found.
 */
StatElemDescBase *StatElemDescBase::findDescByName(const Char8 *name)
{
    Int32             n    = _descVec ? _descVec->size() : 0;
    StatElemDescBase *desc = 0;
    
    if(name && *name && n)
    {
        for(Int32 i = 0; i < n; ++i)
        {
            if (!osgStringCmp(name, (*_descVec)[i]->_name.str()))
            {
                desc = (*_descVec)[i];
                break;
            }
        }
    }

    return desc;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*! \brief Constructor.
    Creates a descriptor with the given name and description. The descriptor
    is assigned a unique id, that can be obtained with getId().
    It is an error to create two descriptors with the same name.

    \param[in] name Name for the descriptor; must be unique.
    \param[in] description Description of the purpose of the StatElem, this
        descriptor belongs to.
 */
StatElemDescBase::StatElemDescBase(const Char8 *name, 
                                   const Char8 *description,
                                   ResetMode    reset) :
    _id         (         -1),
    _name       (       name),
    _description(description),
    _resetMode  (reset)
{
    StatElemDescBase *desc = 0;
    
    if(_descVec) 
    {
        desc = findDescByName(name);
    }
    else
    {
        _descVec = new DescStorage;

        addPostFactoryExitFunction(&StatElemDescBase::terminate);
    }

    if(desc) 
    {
        FFATAL(("Attempt to register the StatElemDescBase name %s a second "
                "time\n", name));
    }
    else 
    {
        _id = _descVec->size();
        _descVec->push_back(this);
    }
}

/*! \brief Destructor.
    It destroys the descriptor object, but the name and id are still reserved,
    so you still can not create a new descriptor with the same name.
 */
StatElemDescBase::~StatElemDescBase(void)
{
}

/*! Prints information about all registered descriptors, by calling their
    print() method.
 */
void StatElemDescBase::printAll(void)
{
    Int32 n = _descVec ? _descVec->size() : 0;
    
    for(Int32 i = 0; i < n; i++)
        (*_descVec)[i]->print();
}

/*! Print information about this descriptor, i.e. its id, name and description.
 */
void StatElemDescBase::print(void)
{
    FLOG(( "StatElemDescBase: ID/Name/Description: %d/%s/%s\n",
           _id, 
           _name.str(), 
           _description.str()));
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*! Destroys the storage for the registered descriptors.
    \warning This is and should only be called during system shutdown.
 */
bool StatElemDescBase::terminate(void)
{
    delete _descVec;

    return true;
}

/*-------------------------- assignment -----------------------------------*/

/*! \brief Assignment.
    This is a no-op.
 */
StatElemDescBase& StatElemDescBase::operator = (const StatElemDescBase &source)
{
    if (this == &source)
        return *this;

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*! \brief Less comparison.
    Compares the address of this agains \a other.
 */
bool StatElemDescBase::operator < (const StatElemDescBase &other) const
{
    return this < &other;
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
    static Char8 cvsid_hpp[] = OSGSTATELEMDESC_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATELEMDESC_INLINE_CVSID;
}
