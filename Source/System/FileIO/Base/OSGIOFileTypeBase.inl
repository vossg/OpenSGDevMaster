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

/*! Returns whether an option with the given \a name is present in \a optSet.

    \param[in] optSet OptionSet to check.
    \param[in] name   Name of the option.
    \return Whether the option is present.
 */
inline bool
IOFileTypeBase::hasOption(const OptionSet &optSet, const std::string &name)
{
    return (optSet.find(name) != optSet.end());
}

/*! Attempts to set option \a name to \a value in \a optSet.
    If successful \c true is returned, false otherwise.
    For the operation to succeed a \c boost::lexical_cast<> from the given type
    has to succeed, usually that means an appropriate overload of
    \c operator<< has to be available.
    
    \param[in] optSet OptionSet to modify.
    \param[in] name Name of the option.
    \param[in] value Value of the option.
    \return Whether the value was set successfully.
 */
template <class ValueTypeT>
inline bool
IOFileTypeBase::setOptionAs(
    OptionSet &optSet, const std::string &name, const ValueTypeT &value)
{
    bool retVal = false;

    try
    {
        setOption(optSet, name, boost::lexical_cast<std::string>(value));
        retVal = true;
    }
    catch(boost::bad_lexical_cast &blc)
    {
        SWARNING << "IOFileTypeBase::setOptionAs: Failed to store value "
                 << "for option [" << name << "] : "
                 << blc.what() << std::endl;
    }

    return retVal;
}

/*! Attempts to return the \a value associated with option \a name in \a optSet
    as the requested type.
    If the option is not present \c false is returned, \c true otherwise and
    only in this case value is being set.
    For the operation to succeed a \c boost::lexical_cast<> to the requested
    type has to succeed, usually that means an appropriate overload of
    \c operator>> has to be available.

    \param[in]  optSet OptionSet to read.
    \param[in]  name Name of the option.
    \param[out] value Value of option.
    \return Whether the option is present.
 */
template <class ValueTypeT>
inline bool
IOFileTypeBase::getOptionAs(
    const OptionSet &optSet, const std::string &name, ValueTypeT &value)
{
    bool        retVal   = false;
    std::string valueStr;

    if(getOption(optSet, name, valueStr) == true)
    {
        try
        {
            value  = boost::lexical_cast<ValueTypeT>(valueStr);
            retVal = true;
        }
        catch(boost::bad_lexical_cast &blc)
        {
            SWARNING << "IOFileTypeBase::getOptionAs: Failed to extract "
                     << "value of option [" << name << "] from string ["
                     << valueStr << "] : "
                     << blc.what() << std::endl;
        }
    }

    return retVal;
}


/*! Returns the currently active option set, i.e. the top of the options stack.
 */
inline IOFileTypeBase::OptionSet const  &
    IOFileTypeBase::getOptions(void) const
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
    return hasOption(_optStack.top(), name);
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
    return setOptionAs(_optStack.top(), name, value);
}

/*! Sets the option \a name to \a value overwriting any previous value.

    \param[in] name Name of the option.
    \param[in] value Value of the option.
 */
inline void
IOFileTypeBase::setOption(const std::string &name, const std::string &value)
{
    setOption(_optStack.top(), name, value);
}

/*! Removes the option \a name. If the option is not present
    \c false is returned, \c true otherwise.

    \param[in] name   Name of the option.
    \return Whether the option was successfully removed.
 */
inline bool
IOFileTypeBase::unsetOption(const std::string &name)
{
    return unsetOption(_optStack.top(), name);
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
    return getOptionAs(_optStack.top(), name, value);
}

/*! Attempts to return the \a value associated with option \a name.
    If the option is not present \c false is returned,
    \c true otherwise and only in this case value is being set.
    
    \param[in]  name   Name of the option.
    \param[out] value  Value of option.
    \return Whether the option is present.
 */
inline bool
IOFileTypeBase::getOption(const std::string &name, std::string &value) const
{
    return getOption(_optStack.top(), name, value);
}

OSG_END_NAMESPACE
