/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#include "OSGIOFileTypeBase.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* IOFileTypeBase::IOOption                                                */
/*-------------------------------------------------------------------------*/

    IOFileTypeBase::IOOption::IOOption(void)
    
    : optName (),
      optValue()
{
    // nothing to do
}

    IOFileTypeBase::IOOption::IOOption(IOOption const &other)
    
    : optName (other.optName ),
      optValue(other.optValue)
{
    // nothing to do
}

    IOFileTypeBase::IOOption::IOOption(
        const std::string &name, const std::string &value)
        
    : optName (name ),
      optValue(value)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* IOFileTypeBase                                                          */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Flags                                                                   */

UInt32
    IOFileTypeBase::getFlags(void) const
{
    return _flags;
}

/*-------------------------------------------------------------------------*/
/* Option Handling                                                         */

/*! Pushes the current options onto the option stack. If \c copyTop is \c true
    a copy of the current options is used as the new current options, otherwise
    an empty options set is used.
    
    \param[in] copyTop Whether to copy the current options.
 */
void
    IOFileTypeBase::pushOptions(bool copyTop)
{
    if(copyTop == true)
    {
        _optStack.push(_optStack.top());
    }
    else
    {
        _optStack.push(OptionSet());
    }
}

/*! Pops the next option set from the stack and makes it the current options.
 */
void
    IOFileTypeBase::popOptions(void)
{
    if(_optStack.size() > 1)
    {
        _optStack.pop();
    }
    else
    {
        FWARNING(("IOFileTypeBase::popOptions: Can not remove last element "
                  "from options stack.\n")); 
    }
}

/*! Sets the option \a name to \a value in \a optSet overwriting
    any previous value.

    \param[in] optSet OptionSet to modify.
    \param[in] name Name of the option.
    \param[in] value Value of the option.
 */
void
IOFileTypeBase::setOption(
    OptionSet &optSet, const std::string &name, const std::string &value)
{
    optSet[name] = IOOption(name, value);
}

/*! Removes the option \a name from \a optSet. If the option is not present
    \c false is returned, \c true otherwise.

    \param[in] optSet OptionSet to modify.
    \param[in] name   Name of the option.
    \return Whether the option was successfully removed.
 */
bool
IOFileTypeBase::unsetOption(OptionSet &optSet, const std::string &name)
{
    bool                retVal = false;
    OptionSet::iterator oIt    = optSet.find(name);
    
    if(oIt != optSet.end())
    {
        optSet.erase(oIt);
        retVal = true;
    }
    
    return retVal;
}

/*! Attempts to return the \a value associated with option \a name
    in \a optSet. If the option is not present \c false is returned,
    \c true otherwise and only in this case value is being set.
    
    \param[in] optSet OptionSet to read.
    \param[in] name   Name of the option.
    \param[out] value Value of option.
    \return Whether the option is present.
 */
bool
IOFileTypeBase::getOption(
    const OptionSet &optSet, std::string const &name, std::string &value)
{
    bool                      retVal = false;
    OptionSet::const_iterator oIt    = optSet.find(name);
    
    if(oIt != optSet.end())
    {
        value  = oIt->second.optValue;
        retVal = true;
    }
    
    return retVal;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */


    IOFileTypeBase::IOFileTypeBase(UInt32 const flags)
    
    : _flags   (flags),
      _optStack(     )
{
    _optStack.push(OptionSet());
}

    IOFileTypeBase::IOFileTypeBase(Self const &other)
    
    : _flags   (other._flags   ),
      _optStack(other._optStack)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

    IOFileTypeBase::~IOFileTypeBase(void)
{
    // nothing to do
}

OSG_END_NAMESPACE
