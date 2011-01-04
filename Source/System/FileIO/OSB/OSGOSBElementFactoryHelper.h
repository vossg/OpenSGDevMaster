/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2006 by the OpenSG Forum                  *
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

#ifndef _OSGOSBELEMENTFACTORYHELPER_H_
#define _OSGOSBELEMENTFACTORYHELPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGOSBElementFactory.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

template <class ElementTypeT>
struct OSBElementRegistrationHelper
{
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ElementTypeT ElementType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    explicit OSBElementRegistrationHelper(const std::string &typeName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

template <class ElementTypeT>
struct OSBDefaultElementRegistrationHelper
{
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ElementTypeT ElementType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    explicit OSBDefaultElementRegistrationHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

#include "OSGOSBElementFactoryHelper.inl"

#endif /* _OSGOSBELEMENTFACTORYHELPER_H_ */
