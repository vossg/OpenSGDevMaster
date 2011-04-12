/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#ifndef _OSGOGREOPTIONS_H_
#define _OSGOGREOPTIONS_H_

/*! \file OSGOgreOptions.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGIOFileTypeBase.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING OgreOptions
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OgreOptions                Self;
    typedef IOFileTypeBase::OptionSet  OptionSet;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor/Destructor                                       */
    /*! \{                                                                 */

    explicit  OgreOptions(      void             );
    explicit  OgreOptions(const OptionSet &optSet);
             ~OgreOptions(      void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Options                                                      */
    /*! \{                                                                 */

    void parseOptions(const OptionSet &optSet);

    bool getLoadAnimations(void      ) const;
    void setLoadAnimations(bool value);

    bool getLoadSkeleton  (void      ) const;
    void setLoadSkeleton  (bool value);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    bool _loadAnimations;
    bool _loadSkeleton;
};

OSG_END_NAMESPACE

#endif // _OSGOGREOPTIONS_H_
