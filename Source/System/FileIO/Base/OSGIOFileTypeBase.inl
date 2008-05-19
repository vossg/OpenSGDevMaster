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

OSG_BEGIN_NAMESPACE

/*! Returns the currently active option set, i.e. the top of the options stack.
 */
inline IOFileTypeBase::OptionSet const  &
    IOFileTypeBase::getOptions (void) const
{
    return _optStack.top();
}

/*! Returns the currently active option set, i.e. the top of the options stack.
 */
inline IOFileTypeBase::OptionSet &
    IOFileTypeBase::editOptions(void)
{
    return _optStack.top();
}

/*! Returns whether an option with the given \a name is present.

    \param[in] name Name of the option.
    \return Whether the option is present.
 */
inline bool
    IOFileTypeBase::hasOption(std::string const &name) const
{
    return (_optStack.top().find(name) != _optStack.top().end());
}

/*! Attempts to set option \a name to \a value.
    If successful \c true is returned, false otherwise.
    For the operation to succeed a \c boost::lexical_cast<> from the given type
    has to succeed, usually that means an appropriate overload of
    \c operator<< has to be available.
    
    \param[in] name Name of the option.
    \param[in] value Value of the option.
    \return Whether the value was set successfully.
 */
template <class ValueTypeT>
inline bool
    IOFileTypeBase::setOptionAs(
        const std::string &name, const ValueTypeT &value)
{
    bool retVal = false;
    
    try
    {
        _optStack.top()[name] =
            IOOption(name, boost::lexical_cast<std::string>(value));
        retVal = true;
    }
    catch(boost::bad_lexical_cast &)
    {
        FWARNING(("IOFileTypeBase::setOptionAs: Failed to store value "
                  "for option [%s].\n", name.c_str()));
    }
    
    return retVal;
}

/*! Attempts to return the value associated with option \a name in \a value
    as the requested type.
    If the option is not present \c false is returned, \c true otherwise and
    only in this case value is being set.
    For the operation to succeed a \c boost::lexical_cast<> to the requested
    type has to succeed, usually that means an appropriate overload of
    \c operator>> has to be available.
    
    \param[in]  name Name of the option.
    \param[out] value Value of option.
    \return Whether the option is present.
 */
template <class ValueTypeT>
inline bool
    IOFileTypeBase::getOptionAs(
        const std::string &name, ValueTypeT &value) const
{
    bool                      retVal = false;
    OptionSet::const_iterator oIt    = _optStack.top().find(name);
    
    if(oIt != _optStack.top().end())
    {
        try
        {
            value  = boost::lexical_cast<ValueTypeT>(oIt->second.optValue);
            retVal = true;
        }
        catch(boost::bad_lexical_cast &)
        {
            FWARNING(("IOFileTypeBase::getOptionAs: Failed to extract value "
                      "of option [%s].\n", name.c_str()));
        }
    }
    
    return retVal;
}

OSG_END_NAMESPACE
