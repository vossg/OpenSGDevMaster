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

#ifndef _OSGIDSTRING_H_
#define _OSGIDSTRING_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include <cstring>
#include <vector>
#include <iostream>

OSG_BEGIN_NAMESPACE

/*!
* An id in the system.
*
* This is a helper class that provides an interface to help in the handling
* and use of string identifiers.
*
* \ingroup GrpBaseBase
*/

class OSG_BASE_DLLMAPPING IDString
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum MemType
    {
        COPY,
        LINK
    };

    typedef std::vector<IDString  > StringVec;
    typedef std::vector<IDString *> StringPVec;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    explicit IDString(      UInt32    size    = 0   );

    explicit IDString(const Char8    *str,
                            MemType   memType = COPY);
             IDString(const IDString &obj,
                            MemType   memType = COPY);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~IDString(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    const Char8 *str      (      void                      ) const;

          bool   isEmpty  (      void                      ) const;


          void   set      (const Char8 *str,
                                 MemType     memType = COPY);

          void   toUpper  (      void                      );
          void   toLower  (      void                      );

          UInt32 getLength(      void                      ) const;
          void   setLength(      UInt32      length        );

          void   tokenize (      StringVec  &v             );
          void   tokenize (      StringPVec &v             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    const IDString & operator =(const IDString &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Comparison                                  */
    /*! \{                                                                 */

    bool operator ==(const IDString &obj) const;
    bool operator !=(const IDString &obj) const;

    bool operator < (const IDString &obj) const;
    bool operator > (const IDString &obj) const;

    bool operator >=(const IDString &obj) const;
    bool operator <=(const IDString &obj) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    Char8   *_str;
    MemType  _memType;

    private:

    friend OSG_BASE_DLLMAPPING
    std::ostream &operator <<(      std::ostream  &os,
                              const IDString      &obj);

};


OSG_BASE_DLLMAPPING
std::ostream &operator <<(      std::ostream  &os,
                          const IDString      &obj);

OSG_BASE_DLLMAPPING
OutStream &operator <<(      OutStream  &os,
                       const IDString   &obj);

OSG_END_NAMESPACE

#include "OSGIDString.inl"
#include "OSGIDStringLink.h"

#endif /* _OSGSTRING_H_ */



