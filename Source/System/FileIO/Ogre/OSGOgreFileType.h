/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#ifndef _OSGOGREFILETYPE_H_
#define _OSGOGREFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGOgreFileType.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING OgreFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef SceneFileType  Inherited;
    typedef OgreFileType   Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Name                                                         */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    virtual NodeTransitPtr
        read(      std::istream &is,
             const Char8        *fileNameOrExtension,
                   Resolver      resolver            = NULL) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

    OgreFileType(const Char8  *suffixArray[],
                       UInt16  suffixByteCount,
                       bool    override,
                       UInt32  overridePriority,
                       UInt32  flags);

    virtual ~OgreFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static const Char8        *_suffixA[];
    static       OgreFileType  _the;
};

OSG_END_NAMESPACE

#endif // _OSGOGREFILETYPE_H_
