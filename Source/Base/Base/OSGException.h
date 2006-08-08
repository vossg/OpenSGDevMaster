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

#ifndef _OSGEXCEPTION_H_
#define _OSGEXCEPTION_H_
#ifdef __sgi
#pragma once
#endif

#include <exception>
#include <string>
#include <iostream>

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

class Exception;

OSG_BASE_DLLMAPPING 
std::ostream &operator <<(      std::ostream &os,
                          const Exception    &obj);

/*! \ingroup GrpBaseBase
 */

class OSG_BASE_DLLMAPPING Exception : 
    public OSG_STDEXCEPTION_NAMESPACE::exception
{
    /*==========================  PUBLIC  =================================*/

  public:

     /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Exception(      void             );
    Exception(const Exception &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Exception(void) OSG_THROW_NOTHING();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Info                                      */
    /*! \{                                                                 */

    virtual const Char8 *what(void) const OSG_THROW_NOTHING();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    Exception &operator =(const Exception &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef OSG_STDEXCEPTION_NAMESPACE::exception Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */

    std::string _what;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend OSG_BASE_DLLMAPPING
    std::ostream &operator <<(      std::ostream &os,
                              const Exception    &obj);

};

OSG_END_NAMESPACE

#define OSGEXCEPTION_HEADER_CVSID "@(#)$Id: $"

#endif /* _EXCEPTION_H_ */
