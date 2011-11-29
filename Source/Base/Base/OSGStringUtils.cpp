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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include <string>
#include "OSGStringUtils.h"
#include "OSGGLDefineMapper.h"

#include "OSGFieldContainerType.h"
#include "OSGNode.h"
#include "OSGNameAttachment.h"

#include <boost/xpressive/xpressive.hpp>

OSG_BEGIN_NAMESPACE

/*! \class string_token_iterator

    \brief Iterator over tokens in a std::string, separated by a specifiable
    set of separator characters.

    Provides an STL iterator like interface to access parts of a std::string.
    The individual parts are separated by at least one character from the set
    of separator characters.

    \note Based on code by Daniel Andersson
    from http://www.codeproject.com/string/stringsplitter.asp

    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn 
 */

/*! Default constructs a new iterator that has no string and no separators.
    This constructor exists only to make this type default constructible, but
    since there is no way to later set the string or the separators it's quite
    useless.
 */
string_token_iterator::string_token_iterator() : 
    _separator(0),
    _str      (0), 
    _start    (0), 
    _end      (0) 
{
}

/*! Creates a new iterator that operates on the string \a str and splits it
    at the separators given in the C string \a separator.

    \param[in] str String to iterator over.
    \param[in] separator Characters at which the string is split.

    \warning The strings \a str and \a separator are not copied, be sure not to
    delete them before you are done with this iterator.
 */
string_token_iterator::string_token_iterator(const std::string &str, 
                                             const char        *separator) :
    _separator( separator),
    _str      (&str      ),
    _start    ( 0        ),
    _end      ( 0        )
{
    find_next();
}

/*! Creates a new iterator with the internal state of \a rhs, i.e. the new
    iterator operates on the same string with the same separators as \a rhs and
    operator*() will return the same substring on its next call for both
    iterators.

    \param[in] rhs Iterator to copy.

    \warning The string and separator are not copied, be sure not to delete them
    before you are done with this iterator.
 */
string_token_iterator::string_token_iterator(
    const string_token_iterator & rhs) :

    _separator(rhs._separator),
    _str      (rhs._str      ),
    _start    (rhs._start    ),
    _end      (rhs._end      )
{
}

/*! Advances to the next token.

    \return The iterator after it was advanced.
 */
string_token_iterator & string_token_iterator::operator++()
{
    find_next();

    return *this;
}

/*! Advances to the next token and returns a copy of \c this from before it was
    advanced.

    \return A copy of this iterator before it was advanced.
 */
string_token_iterator string_token_iterator::operator++(int)
{
    string_token_iterator temp(*this);

    ++(*this);

    return temp;
}

/*! Returns the next token from the string or an empty string if there are no
    further tokens.

    \return Next token from the string.
 */
std::string string_token_iterator::operator*() const
{
    std::string returnValue;

    if(_end == std::string::npos)
    {
        returnValue = _str->substr(_start);
    }
    else
    {
        returnValue = _str->substr(_start, _end - _start);
    }

    return returnValue;
}

/*! Compares \c this to another string_token_iterator \a rhs for equality. They
    are considered equal if they operator on the same string and will return
    the same token on the next call to operator*().

    \param[in] rhs Iterator to compare \c this with.
    \return \c true if the iterators are equal, false otherwise.
 */
bool string_token_iterator::operator==(const string_token_iterator & rhs) const
{
    return (rhs._str == _str && rhs._start == _start && rhs._end == _end);
}

/*! Compares \c this to another string_token_iterator \a rhs for inequality.
    They are considered not equal, if a comparison for equality would return
    \c false.

    \param[in] rhs Iterator to compare \c this with.
    \return \c true if the iterators are not equal, false otherwise.
 */
bool string_token_iterator::operator!=(const string_token_iterator & rhs) const
{
    return !(rhs == *this);
}

/*! Advances the internal state to the next token.
 */
void string_token_iterator::find_next(void)
{
    _start = _str->find_first_not_of(_separator, _end);

    // Apparently some STL implementations don't do npos !?!
    if(_start == std::string::npos || _start >= _str->length())
    {
        _start = _end = 0;
        _str   = 0;
        return;
    }

    _end = _str->find_first_of(_separator, _start);
}



/*---------------------------------------------------------------------*/
/* String Utils, from OpenSGToolbox,  Author: David Kabala             */

std::string addStringBetweenUpperCaseChange(const std::string &szSource, 
                                            const std::string &szPad)
{
    std::string szResult = szSource;
    
    for(UInt32 i = 0; i < szResult.size() - 2; ++i)
    {
        if((97 <= szResult[i    ] && szResult[i    ] <= 122) && 
           (65 <= szResult[i + 1] && szResult[i + 1] <= 90 )  )
        {
            szResult.insert(i + 1, szPad);
        }
    }
    
    return szResult;
}

void getLine(const std::string &szText, 
                   UInt32       uiTextPos, 
                   Int32       &iLineNumber, 
                   Int32       &iLineStartPos)
{
    std::istringstream inStream(szText);

    std::string szLine;

    iLineNumber   = 1;
    iLineStartPos = 0;

    while(std::getline(inStream, szLine) && 
          uiTextPos > iLineStartPos + szLine.size())
    {
        iLineStartPos += szLine.size() + 1;

        ++iLineNumber;
    }
}


std::string lexical_cast(const boost::any &oSource)
{
    if(oSource.type() == typeid(std::string))              // String
    {
        return boost::any_cast<std::string>(oSource);
    }
    else if(oSource.type() == typeid(Char8*))              // Char8 *
    {
        return std::string(boost::any_cast<Char8 *>(oSource));
    }
    //Numbers
    else if(oSource.type() == typeid(UInt8))               // UInt8
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<UInt8>(oSource));
    }
    else if(oSource.type() == typeid(UInt16))              // UInt16
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<UInt16>(oSource));
    }
    else if(oSource.type() == typeid(UInt32))              // UInt32
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<UInt32>(oSource));
    }
    else if(oSource.type() == typeid(UInt64))              // UInt64
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<UInt64>(oSource));
    }
    else if(oSource.type() == typeid(Int8))                // Int8
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Int8>(oSource));
    }
    else if(oSource.type() == typeid(Int16))               // Int16
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Int16>(oSource));
    }
    else if(oSource.type() == typeid(Int32))               // Int32
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Int32>(oSource));
    }
    else if(oSource.type() == typeid(Int64))               // Int64
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Int64>(oSource));
    }
    else if(oSource.type() == typeid(Real16))              // Real16
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Real16>(oSource));
    }
    else if(oSource.type() == typeid(Real32))              // Real32
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Real32>(oSource));
    }
    else if(oSource.type() == typeid(Real64))              // Real64
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Real64>(oSource));
    }
    else if(oSource.type() == typeid(Real128))             // Real128
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Real128>(oSource));
    }
    else if(oSource.type() == typeid(Fixed32))             // Fixed32
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Fixed32>(oSource));
    }
    else if(oSource.type() == typeid(Char8))               // Char8
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<Char8>(oSource));
    }
    else if(oSource.type() == typeid(UChar8))              // UChar8
    {
        return boost::lexical_cast<
                  std::string>(boost::any_cast<UChar8>(oSource));
    }
    else if(oSource.type() == typeid(SChar8))              // SChar8
    {
        return boost::lexical_cast<std::string>(
            boost::any_cast<SChar8>(oSource));
    }
    else if(oSource.type() == typeid(GLenum))              // GLenum
    {
        return GLDefineMapper::the()->toString(
            boost::any_cast<GLenum>(oSource));
    }
    else if(oSource.type() == typeid(BoostPath))           // File Path
    {
        return OSGBP2STR(boost::any_cast<BoostPath>(oSource).filename());
    }
    else if(oSource.type() == typeid(FieldContainerType *)) // FCType
    {
        return std::string(
            boost::any_cast<FieldContainerType *>(oSource)->getCName());
    }
    else
    {
        try
        {
            AttachmentContainer *pContainer = 
                boost::any_cast<Node *>(oSource);

            if(pContainer != NULL)
            {
                const Char8 *szContainerName = getName(pContainer);

                if(szContainerName != NULL)
                {
                    return std::string(szContainerName);
                }
                else
                {
                    return std::string("Empty Name");
                }
            }
        }
        catch(boost::bad_any_cast &)
        {
        }
        throw boost::bad_lexical_cast(oSource.type(), typeid(std::string));
    }

    return std::string("");
}

bool isAlphabetChar(UChar8 c)
{
    if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return true;
    }
    return false;
}

bool isNumericChar(UChar8 c)
{
    if(c >= 48 && c <= 57)
    {
        return true;
    }

    return false;
}

bool isWordChar(UChar8 c)
{
    if(isAlphabetChar(c) || 
       isNumericChar (c) ||
       c == '_'           )
    {
        return true;
    }

    return false;
}

bool isPunctuationChar(UChar8 c)
{
    switch(c)
    {
        case '!': 
        case '~':
        case '`':
        case '@':
        case '#':
        case '$':
        case '%':
        case '^':
        case '&':
        case '*':
        case '(':
        case ')':
        case '-':
        case '_':
        case '+':
        case '=':
        case ':':
        case ';':
        case '\"':
        case '\'':
        case '[':
        case '{':
        case ']':
        case '}':
        case '|':
        case '\\':
        case '<':
        case '>':
        case '.':
        case '/':
        case ',':
        case '?':
            return true;
            
    }

    return false;
}

bool isWhitespaceChar(UChar8 c)
{
    switch(c)
    {
        case ' ': 
        case '\t':
        case '\n':
            return true;
    }

    return false;
}

bool isPrintableChar(UChar8 c)
{
    return (isAlphabetChar   (c) ||
            isNumericChar    (c) ||
            isPunctuationChar(c)  );
}

std::string doxygenToPlainFormatting(const std::string &szDoc)
{
    std::string szResult = szDoc;

    using boost::xpressive::_;
    using boost::xpressive::_ln;
    using boost::xpressive::s1;
    using boost::xpressive::as_xpr;

    //Remove all newlines that do not have another newline directly afterward
    boost::xpressive::sregex srSingleNewlineRegex = _ln >> (s1 = ~_ln);
    std::string              szSingleNewlineReplace(" $1");

    szResult = regex_replace(szResult, 
                             srSingleNewlineRegex, 
                             szSingleNewlineReplace);

    //Generate a vector of tags that define internal sections
    typedef std::pair  <std::string, std::string> StringPair;
    typedef std::vector<StringPair              > StringPairVector;
 
    StringPairVector spTagsToRemove;

    spTagsToRemove.push_back(std::pair<std::string, std::string>("ext",
                                                                 "endext"));
    spTagsToRemove.push_back(std::pair<std::string, std::string>("dev",
                                                                 "enddev"));

    //Remove the tagged sections from the string
    StringPairVector::const_iterator it = spTagsToRemove.begin();

    for(; it != spTagsToRemove.end(); ++it)
    {
        boost::xpressive::sregex srRemoveRegex = 
            as_xpr('\\') >> it->first >> -*_ >> '\\' >> it->second;

        szResult = regex_replace(szResult, srRemoveRegex, "");
    }

    /*!\todo Replace some of the embedded html tags, like <br>*/
    /*!\todo Convert common doxygen tags*/

    return szResult;
}


/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
