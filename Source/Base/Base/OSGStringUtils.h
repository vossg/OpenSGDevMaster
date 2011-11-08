/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGSTRINGUTILS_H_
#define _OSGSTRINGUTILS_H_

#include "OSGBaseFunctions.h"

#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*                   Case String Runtime Functions                     */

inline
void  osgStringDup     (const OSG::TChar  *szInput,       
                              OSG::TChar  *&szOutput);

#ifdef OSG_1_COMPAT
inline
void  stringDup        (const OSG::TChar  *szInput,       
                              OSG::TChar  *&szOutput);
#endif


inline
void  osgStringCopy    (const OSG::Char8  *szInput,       
                              OSG::Char8  *szOutput);

#ifdef OSG_1_COMPAT
inline
void  stringcpy        (const OSG::Char8  *szInput,       
                              OSG::Char8  *szOutput);
#endif


inline
Int32 osgStringNCmp    (const OSG::Char8  *string1, 
                        const OSG::Char8  *string2, 
                              size_t       count   );

#ifdef OSG_1_COMPAT
inline
Int32 stringncmp       (const OSG::Char8  *string1, 
                        const OSG::Char8  *string2, 
                              size_t       count  );
#endif


inline
Int32 osgStringLen     (const OSG::Char8  *string1);

#ifdef OSG_1_COMPAT
inline
Int32 stringlen        (const OSG::Char8  *string1);
#endif


inline
Int32 osgStringCmp     (const OSG::Char8 *string1, 
                        const OSG::Char8 *string2 );

#ifdef OSG_1_COMPAT
inline
Int32 stringcmp        (const OSG::Char8 *string1, 
                        const OSG::Char8 *string2 );
#endif


inline
Int32 osgStringCaseCmp (const OSG::Char8 *string1, 
                        const OSG::Char8 *string2 );

inline
Int32 osgStringNCaseCmp(const OSG::Char8  *string1, 
                        const OSG::Char8  *string2, 
                              size_t       count  );

#ifdef OSG_1_COMPAT
inline
Int32 stringcasecmp    (const OSG::Char8 *string1, 
                        const OSG::Char8 *string2);
#endif

/*---------------------------------------------------------------------*/
/* String Utils, from OpenSGToolbox,  Author: David Kabala             */

OSG_BASE_DLLMAPPING 
std::string addStringBetweenUpperCaseChange(const std::string &szSource, 
                                            const std::string &szPad        );

OSG_BASE_DLLMAPPING
std::string lexical_cast                   (const boost::any  &oSource      );

OSG_BASE_DLLMAPPING 
void        getLine                        (const std::string &szText, 
                                                  UInt32       uiTextPos, 
                                                  Int32       &iLineNumber, 
                                                  Int32       &iLineStartPos);

OSG_BASE_DLLMAPPING
bool  isPrintableChar (UChar8 c);

OSG_BASE_DLLMAPPING 
bool isAlphabetChar   (UChar8 c);

OSG_BASE_DLLMAPPING 
bool isNumericChar    (UChar8 c);

OSG_BASE_DLLMAPPING 
bool isWordChar       (UChar8 c);

OSG_BASE_DLLMAPPING 
bool isPunctuationChar(UChar8 c);

OSG_BASE_DLLMAPPING 
bool isWhitespaceChar (UChar8 c);

/*!\fn std::string doxygenToPlainFormatting(const std::string &Doc)
 * \brief Get a plain string formatting of a string using doxygen documentation
 *
 * \param[in] Doc The string using doxygen formatting
 *
 * \returns A plain string formatting
 */

OSG_BASE_DLLMAPPING 
std::string doxygenToPlainFormatting(const std::string &szDoc);


/*---------------------------------------------------------------------*/

/*! String less than compare functor used for a STL weak ordering
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct LTString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) < 0;
    }
};

/*! String equal compare functor
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct EQString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) == 0;
    }
};


#ifdef OSG_USE_HASH_COMPARE
/*! String hash functor
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct HashCmpString : 
    public OSG_STDEXTENSION_NAMESPACE::hash_compare<const Char8 *, LTString>
{
    typedef       std::hash_compare<const Char8 *, LTString>   Inherited;
    typedef const Char8                                      *_Kty;

    HashCmpString(void) : Inherited() 
    {
    }

    size_t operator()(const _Kty& _Keyval) const
	{
        return OSG_STDEXTENSION_NAMESPACE::hash_value<const Char8 *>(_Keyval);
    }

    bool operator()(const _Kty& _Keyval1, const _Kty& _Keyval2) const
    {
        return Inherited::operator()(_Keyval1, _Keyval2);
    }
};
#endif

/*! String Tokenizer
    \ingroup GrpBaseBaseStringFn
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING string_token_iterator :
#if defined(OSG_HAS_INPUT_ITERATOR)
    public std::input_iterator<std::string, std::ptrdiff_t>
#else
    public std::iterator<std::input_iterator_tag, std::string>
#endif
{
  public:
    string_token_iterator();

    string_token_iterator(const std::string & str_,
                          const char        * separator_ = " ");

    string_token_iterator(const string_token_iterator & rhs);

    string_token_iterator & operator++();

    string_token_iterator operator++(int);

    std::string operator*() const;

    bool operator==(const string_token_iterator & rhs) const;

    bool operator!=(const string_token_iterator & rhs) const;

  private:

    void find_next(void);

    const char                   * _separator;
    const std::string            * _str;
          std::string::size_type   _start;
          std::string::size_type   _end;
};

OSG_END_NAMESPACE

#include "OSGStringUtils.inl"

#endif /* OSGBASEFUNCTIONS_H */
