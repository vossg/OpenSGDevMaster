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

#ifndef _OSGINTERSECTKDTREENODEFIELDS_H_
#define _OSGINTERSECTKDTREENODEFIELDS_H_

#include "OSGConfig.h"
#include "OSGDrawableDef.h"
#include "OSGFieldTraits.h"
#include "OSGIntersectKDTreeNode.h"
#include "OSGMField.h"
#include "OSGSField.h"

OSG_BEGIN_NAMESPACE

template <>
struct OSG_DRAWABLE_DLLMAPPING FieldTraits<IntersectKDTreeNode> :
    public FieldTraitsTemplateBase<IntersectKDTreeNode>
{
    typedef FieldTraitsTemplateBase<IntersectKDTreeNode>  Inherited;
    typedef FieldTraits<IntersectKDTreeNode>              Self;

    static  DataType _type;

    enum { Convertible = Self::NotConvertible };

    static       DataType &getType (void);

    static const Char8    *getSName(void);
    static const Char8    *getMName(void);

    static SizeT  getBinSize(const IntersectKDTreeNode &oObject     );
    static SizeT  getBinSize(const IntersectKDTreeNode *pObjectStore,
                                   SizeT                uiNumObjects);

    static void copyToBin(      BinaryDataHandler   &pMem,
                          const IntersectKDTreeNode &oObject      );
    static void copyToBin(      BinaryDataHandler   &pMem,
                          const IntersectKDTreeNode *pObjectStore,
                                SizeT                uiNumObjects );

    static void copyFromBin(BinaryDataHandler   &pMem,
                            IntersectKDTreeNode &oObject      );
    static void copyFromBin(BinaryDataHandler   &pMem,
                            IntersectKDTreeNode *pObjectStore,
                            SizeT                uiNumObjects );
};

typedef MField<IntersectKDTreeNode> MFIntersectKDTreeNode;
typedef SField<IntersectKDTreeNode> SFIntersectKDTreeNode;

OSG_END_NAMESPACE

#include "OSGIntersectKDTreeNodeFields.inl"

#endif /* _OSGINTERSECTKDTREENODEFIELDS_H_ */
