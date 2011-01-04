/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2007 by the OpenSG Forum                    *
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

#ifndef _OSGOSBDRIVER_H_
#define _OSGOSBDRIVER_H_

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGIOFileTypeBase.h"
#include "OSGNode.h"

#include <iostream>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBDriver
{
  public:
    static NodeTransitPtr read (      std::istream              &inStream,
                                const IOFileTypeBase::OptionSet &options   );

    static bool           write(      Node              * const  node,
                                      std::ostream              &outStream,
                                const IOFileTypeBase::OptionSet &options   );

    static FieldContainerTransitPtr
        readFC (      std::istream              &inStream,
                const IOFileTypeBase::OptionSet &options   );

    static bool
        writeFC(      FieldContainer * const     fc,
                      std::ostream              &outStream,
                const IOFileTypeBase::OptionSet &options   );
};

OSG_END_NAMESPACE

#endif /* _OSGOSBDRIVER_H_ */
