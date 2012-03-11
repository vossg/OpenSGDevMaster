/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <OSGConfig.h>

#include "OSGStackedTransform.h"
#include "OSGTransformationElement.h"
#include "OSGIntersectAction.h"

#include "OSGRenderAction.h"
#include "OSGNameAttachment.h"

#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStackedTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGStackedTransform.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::string StackedTransform::TranslateName = std::string("translate");
std::string StackedTransform::RotateXName   = std::string("rotateX"  );
std::string StackedTransform::RotateYName   = std::string("rotateY"  );
std::string StackedTransform::RotateZName   = std::string("rotateZ"  );
std::string StackedTransform::ScaleName     = std::string("scale"    );

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StackedTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            StackedTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &StackedTransform::renderEnter));
        
        RenderAction::registerLeaveDefault(
            StackedTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &StackedTransform::renderLeave));
        
        
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &StackedTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &StackedTransform::intersectLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void StackedTransform::updateTransform(void)
{
    _mTransformation.setIdentity();

    for(UInt32 i =0; i < getMFTransformElements()->size(); ++i)
    {
        getTransformElements(i)->accumulateMatrix(_mTransformation);
    }
        
    invalidateVolume();
}

void StackedTransform::accumulateMatrix(Matrix &result)
{
    result.mult(_mTransformation);
}

void StackedTransform::adjustVolume(Volume &volume)
{
    volume.transform(_mTransformation);
}

TransformationElement *StackedTransform::getElement(
    const std::string &szName) const
{
    const Char8 *szElemName = NULL;

    for(UInt32 i = 0; i < getMFTransformElements()->size(); ++i)
    {
        szElemName = getName(getTransformElements(i));

        if(szElemName != NULL && szName.compare(szElemName) == 0)
        {
            return getTransformElements(i);
        }
    }

    return NULL;
}

void StackedTransform::pushToNamedTransformElements(
    TransformationElement       * const pValue,
    std::string           const &       szName)
{
    setName(pValue, szName.c_str());

    Inherited::pushToTransformElements(pValue);
}

void StackedTransform::insertIntoNamedTransformElements(
    UInt32                              uiIndex,
    TransformationElement       * const pValue,
    std::string           const &       szName)
{
    setName(pValue, szName.c_str());

    Inherited::insertIntoTransformElements(uiIndex, pValue);
}

void StackedTransform::replaceInNamedTransformElements(
    UInt32                              uiIndex,
    TransformationElement       * const pValue,
    std::string           const &       szName)
{
    setName(pValue, szName.c_str());

    Inherited::replaceInTransformElements(uiIndex, pValue);
}

void StackedTransform::replaceObjInNamedTransformElements(
    TransformationElement       * const pOldElem,
    TransformationElement       * const pNewElem,
    std::string           const &       szName  )
{
    setName(pNewElem, szName.c_str());

    Inherited::replaceObjInTransformElements(pOldElem, pNewElem);
}

void StackedTransform::removeFromNamedTransformElements(
    const std::string &szName)
{
    const Char8 *szElemName = NULL;

    for(UInt32 i = 0; i < getMFTransformElements()->size(); ++i)
    {
        szElemName = getName(getTransformElements(i));

        if(szElemName != NULL && szName.compare(szElemName) == 0)
        {
            Inherited::removeFromTransformElements(i);

            return;
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE StackedTransform::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pushVisibility();

    pAction->pushMatrix(this->_mTransformation);

    return Action::Continue;
}

Action::ResultE StackedTransform::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

Action::ResultE StackedTransform::intersectEnter(Action *action)
{
    // Use parent class for trivial reject
    if(Inherited::intersectEnter(action) == Action::Skip)
        return Action::Skip;
    
    // Need to check children
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->_mTransformation;

    m.invert();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    Real32 length = dir.length();

    if(length < TypeTraits<Real32>::getDefaultEps())
        SWARNING << "StackedTransform::intersectEnter: Near-zero scale!" 
                 << std::endl;

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale  (length                          );
    
    return Action::Continue; 
}

Action::ResultE StackedTransform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->_mTransformation;
    
    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StackedTransform::StackedTransform(void) :
     Inherited      (),
    _mTransformation()
{
    _mTransformation.setIdentity();
}

StackedTransform::StackedTransform(const StackedTransform &source) :
     Inherited      (source                 ),
    _mTransformation(source._mTransformation)
{
}

StackedTransform::~StackedTransform(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StackedTransform::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & TransformElementsFieldMask))
    {
        updateTransform();
    }
}

void StackedTransform::dump(      UInt32    ,
                            const BitVector ) const
{
    SLOG << "Dump StackedTransform NI" << std::endl;
}

OSG_END_NAMESPACE
