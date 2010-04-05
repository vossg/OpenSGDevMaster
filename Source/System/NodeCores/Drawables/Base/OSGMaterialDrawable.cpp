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

#include "OSGConfig.h"

#include "OSGMaterialDrawable.h"

#include "OSGRenderAction.h"
#include "OSGPrimeMaterial.h"

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

Action::ResultE MaterialDrawable::renderActionEnterHandler(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);
    
    Material::DrawFunctor func;

    func = boost::bind(&MaterialDrawable::drawPrimitives, this, _1);

    Material      *m         = a->getMaterial();
    PrimeMaterial *pPrimeMat = NULL;

    if(m == NULL)
    {
        if(this->getMaterial() != NULL)
        {
            pPrimeMat = 
                this->getMaterial()->finalize(a->getRenderProperties(),
                                              a->getWindow()          );
        }
    }
    else
    {
        pPrimeMat = m->finalize(a->getRenderProperties(),
                                a->getWindow          ());
    }

    if(pPrimeMat == NULL)
    {
        pPrimeMat = getDefaultMaterial();
        
        FNOTICE(("MaterialDrawable::render: no Material!?!\n"));
    }

    UInt32 uiNPasses = pPrimeMat->getNPasses();
    
    for(UInt32 uiPass = 0; uiPass < uiNPasses; ++uiPass)
    {
        State *st = pPrimeMat->getState(uiPass);
        
        if(st != NULL)
        {
            a->dropFunctor(func, 
                           st, 
                           pPrimeMat->getSortKey() + uiPass);
        }
        else
        {
#ifndef WIN32
            FINFO(("%s: hit material with NULL state!\n", __func__));
#else
            FINFO(("Hit material with NULL state!\n"));
#endif
        }
    }

    if(a->pushVisibility())
    {
        if(a->selectVisibles() == 0)
        {
            a->popVisibility();
            return Action::Skip;
        }
    }
    
    return Action::Continue;
}

Action::ResultE MaterialDrawable::renderActionLeaveHandler(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);
    
    a->popVisibility();
    
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
void MaterialDrawable::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes
void MaterialDrawable::dump(      UInt32    , 
                            const BitVector ) const
{
    SLOG << "Dump MaterialDrawable NI" << std::endl;
}

