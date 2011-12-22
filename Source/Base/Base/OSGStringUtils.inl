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

/*---------------------------------------------------------------------*/
/*! \name C strings                                                    */
/*! \{                                                                 */

/*! Creates a copy of the C string \a szInput and stores a pointer to the copy
    in \a szOutput. The memory for the copy is allocated using \c new[], while
    any memory already pointed to by \a szOutput is deallocated
    with \c delete[].

    \param[in] szInput The C string to copy.
    \param[out] szOutput Set to point to the copy.

    \ingroup GrpBaseBaseStringFn
 */
inline
void osgStringDup(const OSG::TChar *szInput, OSG::TChar *&szOutput)
{
    delete [] szOutput;

    szOutput = NULL;

    if(szInput != NULL)
    {
#if defined(WIN32)
        szOutput = new TChar[::_tcslen(szInput) + 1];
        ::_tcscpy(szOutput, szInput);
#else
        szOutput = new TChar[::strlen(szInput) + 1];
        ::strcpy(szOutput, szInput);
#endif
    }
}

#ifdef OSG_1_COMPAT
/*! Creates a copy of the C string \a szInput and stores a pointer to the copy
    in \a szOutput. The memory for the copy is allocated using \c new[], while
    any memory already pointed to by \a szOutput is deallocated
    with \c delete[].

    \param[in] szInput The C string to copy.
    \param[out] szOutput Set to point to the copy.

    \deprecated use osgStringDup instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
void stringDup(const OSG::TChar *szInput, OSG::TChar *&szOutput)
{
    OSG::osgStringDup(szInput, szOutput);
}
#endif // OSG_1_COMPAT

/*! Creates a copy of the C string \a szInput at the position pointed to by
    \a szOutput. This function does not allocate memory, so \a szOutput must
    point to a buffer that is large enough.

    \param[in] szInput The C string to copy.
    \param[out] szOutput Pointer to a buffer where the copy is stored.

    \warning This function does not check the size of the destination buffer,
    hence it could overwrite other data if the buffer is not large enough !

    \ingroup GrpBaseBaseStringFn
 */
inline
void  osgStringCopy(const OSG::Char8 *szInput, OSG::Char8 *szOutput)
{
    if(szInput != NULL && szOutput != NULL)
    {
        ::strcpy(szOutput, szInput);
    }
}

#ifdef OSG_1_COMPAT
/*! Creates a copy of the C string \a szInput at the position pointed to by
    \a szOutput. This function does not allocate memory, so \a szOutput must
    point to a buffer that is large enough.

    \param[in] szInput The C string to copy.
    \param[out] szOutput Pointer to a buffer where the copy is stored.

    \warning This function does not check the size of the destination buffer,
    hence it could overwrite other data if the buffer is not large enough !

    \deprecated use osgStringCopy instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
void  stringcpy(const OSG::Char8 *szInput, OSG::Char8 *szOutput)
{
    OSG::osgStringCopy(szInput, szOutput);
}
#endif // OSG_1_COMPAT

/*! Compares two C strings, but considers at most the first \a count characters.
    The return value has the same sign as the difference of the first differing
    pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \param[in] count Maximal number of charaters to compare
    \return 0 if the first \a count characters of both strings are equal,
    -1 if \a string1 is less than \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::Int32 osgStringNCmp(const OSG::Char8 *string1, 
                         const OSG::Char8 *string2, 
                               size_t      count)
{
    return ::strncmp(string1, string2, count);
}

#ifdef OSG_1_COMPAT
/*! Compares two C strings, but considers at most the first \a count characters.
    The return value has the same sign as the difference of the first differing
    pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \param[in] count Maximal number of charaters to compare
    \return 0 if the first \a count characters of both strings are equal,
    -1 if \a string1 is less than \a string2 and 1 otherwise.

    \deprecated use osgStringNCmp instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::Int32 stringncmp(const OSG::Char8  *string1, 
                      const OSG::Char8  *string2, 
                            size_t       count  )
{
    return OSG::osgStringNCmp(string1, string2, count);
}
#endif // OSG_1_COMPAT

/*! Returns the length of a C string, i.e. the number of characters from the
    given pointer, to the first zero character.

    \param[in] string1 String whose length is determined.
    \return Length of the string.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::SizeT osgStringLen(const OSG::Char8 *string1)
{
    return ::strlen(string1);
}

#ifdef OSG_1_COMPAT
/*! Returns the length of a C string, i.e. the number of characters from the
    given pointer, to the first zero character.

    \param[in] string1 String whose length is determined.
    \return Length of the string.

    \deprecated use osgStringLen instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::SizeT stringlen(const OSG::Char8 *string1)
{
    return OSG::osgStringLen(string1);
}
#endif // OSG_1_COMPAT

/*! Compares two C strings. The return value has the same sign as the
    difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::Int32 osgStringCmp(const OSG::Char8 *string1, const OSG::Char8 *string2)
{
    return ::strcmp(string1, string2);
}

#ifdef OSG_1_COMPAT
/*! Compares two C strings. The return value has the same sign as the
    difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \deprecated use osgStringCmp instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::Int32 stringcmp(const OSG::Char8 *string1, const OSG::Char8 *string2)
{
    return OSG::osgStringCmp(string1, string2);
}
#endif // OSG_1_COMPAT

/*! Compare two C strings ignoring differences in case. The return value has
    the same sign as the difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::Int32 osgStringCaseCmp(const OSG::Char8 *string1,
                            const OSG::Char8 *string2)
{
#if !defined(WIN32)
    return ::strcasecmp(string1, string2);
#else
    return _stricmp  (string1, string2);
#endif
}

/*! Compare two C strings ignoring differences in case, but considers at most
    the first \a count characters. The return value has
    the same sign as the difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \param[in] count   number of characters to compare
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::Int32 osgStringNCaseCmp(const OSG::Char8  *string1,
                             const OSG::Char8  *string2,
                                   size_t       count)
{
#if !defined(WIN32)
    return ::strncasecmp(string1, string2, count);
#else
    return _strnicmp  (string1, string2, count);
#endif
}

#ifdef OSG_1_COMPAT
/*! Compare two C strings ignoring differences in case. The return value has
    the same sign as the difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \deprecated use osgStringCaseCmp instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
OSG::Int32 stringcasecmp(const OSG::Char8 *string1,
                         const OSG::Char8 *string2)
{
    return OSG::osgStringCaseCmp(string1, string2);
}
#endif // OSG_1_COMPAT

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

