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

#ifndef _OSGPOINTERTYPE_H_
#define _OSGPOINTERTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <typeinfo>
#include "OSGDataType.h"
#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseField
    \ingroup GrpLibOSGBase 
 */

class OSG_BASE_DLLMAPPING PointerType : public DataType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PointerType(const Char8                   *szName, 
                const Char8                   *szParentName,
                const DataType                &contentType,
                const UInt32                   uiNameSpace = GlobalNamespace);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PointerType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Is                                      */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const DataType    &getContentType(void) const;

    /*! \}                                                                 */

#if defined(OSG_STATIC_MEMEBER_NEEDS_COPY_ASIGN_INIT)
    /*!\brief prohibit default function (move to 'public' if needed) */
    PointerType(const PointerType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    PointerType &operator =(const PointerType &obj);
#endif

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef DataType Inherited;

    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

    const DataType &_contentType;

    /*==========================  PRIVATE  ================================*/

  private:

#if !defined(OSG_STATIC_MEMEBER_NEEDS_COPY_ASIGN_INIT)
    /*!\brief prohibit default function (move to 'public' if needed) */
    PointerType(const PointerType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    PointerType &operator =(const PointerType &obj);
#endif
};

OSG_END_NAMESPACE

#include "OSGPointerType.inl"

#endif /* _OSGPOINTERTYPE_H_ */



