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

#include "OSGReflexiveContainer.h"
#include "OSGFieldDescriptionBase.h"

OSG_USING_NAMESPACE


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldDescriptionBase::FieldDescriptionBase(
    const FieldType       &elementType,
    const Char8           *szName,
    const std::string      fieldDocumentation,
    const UInt32           uiFieldId,
    const BitVector        vFieldMask,
    const bool             bInternal,
    const UInt32           uiFieldFlags,
          FieldEditMethod  fEditMethod,
          FieldGetMethod   fGetMethod,
    const Char8           *defaultValue) :

    _szName            (szName      ),
    _documentation     (fieldDocumentation),

    _fieldType         (elementType ),
    _uiFieldId         (uiFieldId   ),
    _vFieldMask        (vFieldMask  ),

    _bInternal         (bInternal   ),
    _uiFieldFlags      (uiFieldFlags),

    _fEditMethod       (fEditMethod ),
    _fGetMethod        (fGetMethod  ),
    _fIndexedEditMethod(NULL        ),
    _fIndexedGetMethod (NULL        ),
    _defaultValue      (defaultValue)
{
}

FieldDescriptionBase::FieldDescriptionBase(
    const FieldType            &elementType,
    const Char8                *szName,
    const std::string           fieldDocumentation,
    const UInt32                uiFieldId,
    const BitVector             vFieldMask,
          FieldIndexEditMethod  fIndexedEditMethod,
          FieldIndexGetMethod   fIndexedGetMethod,
    const bool                  bInternal,
    const UInt32                uiFieldFlags,
    const Char8                *defaultValue      ) :

    _szName            (szName            ),
    _documentation     (fieldDocumentation),

    _fieldType         (elementType       ),
    _uiFieldId         (uiFieldId         ),
    _vFieldMask        (vFieldMask        ),

    _bInternal         (bInternal         ),
    _uiFieldFlags      (uiFieldFlags      ),

    _fEditMethod       (NULL              ),
    _fGetMethod        (NULL              ),
    _fIndexedEditMethod(fIndexedEditMethod),
    _fIndexedGetMethod (fIndexedGetMethod ),

    _defaultValue      (defaultValue      )
{
}

FieldDescriptionBase::FieldDescriptionBase(const FieldDescriptionBase &source):
    _szName            (source._szName            ),
    _documentation     (source._documentation     ),

    _fieldType         (source._fieldType         ),
    _uiFieldId         (source._uiFieldId         ),
    _vFieldMask        (source._vFieldMask        ),

    _bInternal         (source._bInternal         ),
    _uiFieldFlags      (source._uiFieldFlags      ),

    _fEditMethod       (source._fEditMethod       ),
    _fGetMethod        (source._fGetMethod        ),
    _fIndexedEditMethod(source._fIndexedEditMethod),
    _fIndexedGetMethod (source._fIndexedGetMethod ),

    _defaultValue      (source._defaultValue      )

{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldDescriptionBase::~FieldDescriptionBase(void)
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
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGFIELDDESCRIPTIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDDESCRIPTIONBASE_INLINE_CVSID;
}

