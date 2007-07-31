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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGFieldBundle.h"

OSG_USING_NAMESPACE

void FieldBundle::classDescInserter(TypeObject &)
{
}

FieldBundle::TypeObject FieldBundle::_type(
    FieldBundle::getClassname(),
    "ReflexiveContainer",
    "FieldBundle",
    0,
    NULL,
    NULL,
    NULL,
    false,
    0);

FieldBundle::TypeObject &FieldBundle::getType(void)
{
    return _type;
}
    
const FieldBundle::TypeObject &FieldBundle::getType(void) const
{
    return _type;
}

#if 0
void FieldBundle::pushToField(      FieldBundlePConstArg pNewElement,
                              const UInt32               uiFieldId  )
{
}

void FieldBundle::insertIntoMField(const UInt32               uiIndex,
                                         FieldBundlePConstArg pNewElement,
                                   const UInt32               uiFieldId  )
{
}

void FieldBundle::replaceInMField(const UInt32               uiIndex,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  )
{
}

void FieldBundle::replaceInMField(      FieldBundlePConstArg pOldElement,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  )
{
}

void FieldBundle::removeFromMField(const UInt32 uiIndex,
                                   const UInt32 uiFieldId)
{
}

void FieldBundle::removeFromMField(      FieldBundlePConstArg pElement,
                                   const UInt32               uiFieldId  )
{
}

void FieldBundle::clearField(const UInt32 uiFieldId)
{
}
#endif

bool FieldBundle::deregister(UInt32 uiBundleId)
{
    return false;
}

void FieldBundle::registerChangedContainerV(void)
{
}
