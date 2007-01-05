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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include <OSGConfig.h>

#include "OSGMaterialDrawable.h"

#include <OSGRenderAction.h>

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGMaterialDrawableBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialDrawable.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
MaterialDrawable::MaterialDrawable(void) :
    Inherited()
{
}

//! Copy Constructor
MaterialDrawable::MaterialDrawable(const MaterialDrawable &source) :
    Inherited(source)
{
}

//! Destructor
MaterialDrawable::~MaterialDrawable(void)
{
}

/*----------------------------- class specific ----------------------------*/

Action::ResultE MaterialDrawable::renderActionHandler(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Material::DrawFunctor func;

    func = boost::bind(&MaterialDrawable::drawPrimitives, this, _1);

    Material *m = a->getMaterial();

    if(m == NULL)
    {
        if(getMaterial() != NullFC)
        {
            m = getCPtr(getMaterial());
        }
        else
        {
            m = getCPtr(getDefaultMaterial());

            FNOTICE(("MaterialDrawable::render: no Material!?!\n"));
        }
    }

    a->dropFunctor(func, m);

    return Action::Continue;
}

//! initialize the static features of the class, e.g. action callbacks
Action::ResultE MaterialDrawable::drawPrimitives(DrawEnv *)
{
    FWARNING (("You should overload drawPrimitives in your code\n"));

    return Action::Continue;
}

void MaterialDrawable::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes
void MaterialDrawable::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void MaterialDrawable::dump(      UInt32    , 
                            const BitVector ) const
{
    SLOG << "Dump MaterialDrawable NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGMATERIALDRAWABLEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMATERIALDRAWABLEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMATERIALDRAWABLEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

