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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/*! \var osg::FieldType::_contentType
    Type stored within fields of this type
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldType::FieldType(const Char8             *szName,
                     const Char8             *szParentName,
                     const DataType          &contentType,
                           Cardinality        cardinality,
                     const UInt32             uiNameSpace) :
     Inherited   (szName, 
                  szParentName, 
                  uiNameSpace ),
    _cardinality (cardinality ),
    _contentType (contentType ),
    _pScanAsType (NULL        )
{
}

FieldType::FieldType(const Char8              *szName,
                     const Char8              *szParentName,
                     const DataType           &contentType,
                           Cardinality         cardinality,
                     const FieldType          &pScanAsType,
                     const UInt32             uiNameSpace ) :
     Inherited   ( szName, 
                   szParentName,
                   uiNameSpace ),
    _cardinality ( cardinality ),
    _contentType ( contentType ),
    _pScanAsType (&pScanAsType )
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldType::~FieldType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

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
    static Char8 cvsid_hpp[] = OSGFIELDTYPE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDTYPE_INLINE_CVSID;
}
