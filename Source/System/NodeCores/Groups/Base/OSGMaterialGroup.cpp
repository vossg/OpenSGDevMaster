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

#include <OSGConfig.h>

#include "OSGMaterialGroup.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGMaterialGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialGroup.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void MaterialGroup::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void MaterialGroup::dump(      UInt32    uiIndent,
                         const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MaterialGroup::MaterialGroup(void) :
    Inherited()
{
}

MaterialGroup::MaterialGroup(const MaterialGroup &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MaterialGroup::~MaterialGroup(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Render                                    */

ActionBase::ResultE MaterialGroup::renderEnter(Action *action)
{
    RenderAction *da = dynamic_cast<RenderAction *>(action);

    if( da                    != NULL &&
       _sfMaterial.getValue() != NullFC &&
        da->getMaterial()     == NULL)
    {
        da->setMaterial(&(*(_sfMaterial.getValue())), da->getActNode());
    }

    return Group::renderEnter(action);
}

ActionBase::ResultE MaterialGroup::renderLeave(Action *action)
{
    RenderAction *da = dynamic_cast<RenderAction *>(action);

    if(da != NULL && da->getMaterialNode() == action->getActNode())
    {
        da->setMaterial(NULL, NullFC);
    }

    return Group::renderLeave(action);
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void MaterialGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MaterialGroup::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MaterialGroup::renderLeave));
    }
}


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
    static Char8 cvsid_hpp[] = OSGMATERIALGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGMATERIALGROUP_INLINE_CVSID;
}
