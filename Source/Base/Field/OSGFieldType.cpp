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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGFieldDescFactory.h"

OSG_USING_NAMESPACE

/*! \var OSG::FieldType::_contentType
    Type stored within fields of this type
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldType::FieldType(const Char8                   *szName,
                     const Char8                   *szParentName,
                     const DataType                &contentType,
                           Cardinality              cardinality,
                           Class                    fieldClass,
                           FieldDescCreator         fCreator,
                           IndexedFieldDescCreator  fIdxCreator,
                     const UInt32                   uiNameSpace) :
     Inherited   (szName, 
                  szParentName, 
                  uiNameSpace ),
    _cardinality (cardinality ),
    _fieldClass  (fieldClass  ),
    _contentType (contentType ),
    _pScanAsType (NULL        )
{
    FieldDescFactory::the()->registerDescription( szName,
                                                 _uiTypeId,
                                                  fCreator,
                                                  fIdxCreator);
}

FieldType::FieldType(const Char8                   *szName,
                     const Char8                   *szParentName,
                     const DataType                &contentType,
                           Cardinality              cardinality,
                           Class                    fieldClass,
                     const FieldType               &pScanAsType,
                           FieldDescCreator         fCreator,
                           IndexedFieldDescCreator  fIdxCreator,
                     const UInt32                   uiNameSpace ) :
     Inherited   ( szName, 
                   szParentName,
                   uiNameSpace ),
    _cardinality ( cardinality ),
    _fieldClass  ( fieldClass  ),
    _contentType ( contentType ),
    _pScanAsType (&pScanAsType )
{
    FieldDescFactory::the()->registerDescription( szName,
                                                 _uiTypeId,
                                                  fCreator,
                                                  fIdxCreator);
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldType::~FieldType(void) 
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

