/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGFieldContainerAttachment.h"

OSG_USING_NAMESPACE

void FieldContainerAttachment::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);
}

Char8 *FieldContainerAttachment::getClassname(void)
{
    return "FieldContainerAttachment";
}

FieldContainerAttachment::TypeObject FieldContainerAttachment::_type(true,
    FieldContainerAttachment::getClassname(),
    Inherited               ::getClassname(),
    "FieldContainer",
    0,
    NULL,
    NULL,
    (InitalInsertDescFunc) &FieldContainerAttachment::classDescInserter,
    false);

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerAttachment::FieldContainerAttachment(void) :
    Inherited()
{
}

FieldContainerAttachment::FieldContainerAttachment(
    const FieldContainerAttachment &source) :

    Inherited(source)
{
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerAttachment::~FieldContainerAttachment(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINERATTACHMENT_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINERATTACHMENT_INLINE_CVSID;
}

