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

/*! Attempts to set option \a name to \a value for the ImageFileHandler that
    handles files with the given \a suffix.
    If successful \c true is returned, false otherwise.
    For the operation to succeed a \c boost::lexical_cast<> from the given type
    has to succeed, usually that means an appropriate overload of
    \c operator<< has to be available.
    
    \param[in] suffix File extension to choose the image type
                      this option applies to.
    \param[in] name Name of the option.
    \param[in] value Value of the option.
    \return Whether the value was set successfully.
 */
template <class ValueTypeT>
inline bool
    ImageFileHandlerBase::setOptionAs(
        const std::string &suffix,
        const std::string &name,
        const ValueTypeT  &value  )
{
    bool           retVal = false;
    ImageFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->setOptionAs<ValueTypeT>(name, value);
    }
    
    return retVal;
}

/*! Retrieves the option \a name from the ImageFileType that handles files
    with the given \a suffix and stores its value in \a value.
    Returns \c true if successful, \c false otherwise in which case \a value has
    an undefined value.
    
    \param[in] suffix File extension to choose the image type
                      this option applies to.
    \param[in] name Name of the option.
    \param[out] value Value the option.
    \return Whether the option is present for the given ImageFileType.
 */
template <class ValueTypeT>
inline bool 
    ImageFileHandlerBase::getOptionAs(
        const std::string &suffix,
        const std::string &name,
              ValueTypeT  &value  )
{
    bool           retVal = false;
    ImageFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->getOptionAs<ValueTypeT>(name, value);
    }
    
    return retVal;
}

OSG_END_NAMESPACE
