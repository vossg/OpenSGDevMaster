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

#include "OSGConfig.h"
#include "OSGSkinnedGeometry.h"
#include "OSGHardwareSkinningAlgorithm.h"
#include "OSGSkeletonSkinningAlgorithm.h"
#include "OSGUnskinnedSkinningAlgorithm.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkinnedGeometryBase.cpp file.
// To modify it, please change the .fcd file (OSGSkinnedGeometry.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkinnedGeometry::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            SkinnedGeometry::getClassType(),
            reinterpret_cast<Action::Callback>(&SkinnedGeometry::renderEnter));
        RenderAction::registerLeaveDefault(
            SkinnedGeometry::getClassType(),
            reinterpret_cast<Action::Callback>(&SkinnedGeometry::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkinnedGeometry::SkinnedGeometry(void) :
    Inherited()
{
}

SkinnedGeometry::SkinnedGeometry(const SkinnedGeometry &source) :
    Inherited(source)
{
}

SkinnedGeometry::~SkinnedGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkinnedGeometry::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    if((RenderModeFieldMask & whichField) != 0)
    {
        switch(_sfRenderMode.getValue())
        {
        case RMUnskinned:
        {
            UnskinnedSkinningAlgorithmUnrecPtr algo =
                UnskinnedSkinningAlgorithm::create();
            setSkinningAlgorithm(algo);

            if(_sfSkeleton.getValue() != NULL)
                algo->setSkeleton(_sfSkeleton.getValue());
        }
        break;

        case RMSkeleton:
        {
            SkeletonSkinningAlgorithmUnrecPtr algo =
                SkeletonSkinningAlgorithm::create();
            setSkinningAlgorithm(algo);

            if(_sfSkeleton.getValue() != NULL)
            {
                algo->setSkeleton(_sfSkeleton.getValue());
                _sfSkeleton.getValue()->setUseInvBindMatrix(false);
            }
        }
        break;

        case RMSkinnedHardware:
        {
            HardwareSkinningAlgorithmUnrecPtr algo =
                HardwareSkinningAlgorithm::create();
            setSkinningAlgorithm(algo);

            if(_sfSkeleton.getValue() != NULL)
            {
                algo->setSkeleton(_sfSkeleton.getValue());
                _sfSkeleton.getValue()->setUseInvBindMatrix(true);
            }
        }
        break;

        case RMSkinnedSoftware:
        {
            setSkinningAlgorithm(NULL);
        }
        break;
        }

        invalidateVolume();
    }
    
    if((SkeletonFieldMask & whichField) != 0)
    {
        if(_sfSkinningAlgorithm.getValue() != NULL)
        {
            _sfSkinningAlgorithm.getValue()->setSkeleton(
                _sfSkeleton.getValue());
        }
    }

    Inherited::changed(whichField, origin, details);
}

const Matrix &
SkinnedGeometry::getBindShapeMatrix(void) const
{
    return Inherited::getBindShapeMatrix();
}

void
SkinnedGeometry::setBindShapeMatrix(const Matrix &value)
{
#if 0
    bool   needTransform  = false;
    Matrix objSpaceMatrix;
    Matrix tangSpaceMatrix;

    if(_sfBindShapeMatrix.getValue() != Matrix::identity())
    {
        needTransform = true;

        objSpaceMatrix = _sfBindShapeMatrix.getValue();
        objSpaceMatrix.invert();

        tangSpaceMatrix = _sfBindShapeMatrix.getValue();
        tangSpaceMatrix.transpose();
    }

    if(value != Matrix::identity())
    {
        needTransform = true;

        objSpaceMatrix.multLeft(value);
    
        Matrix valueInvT(value);
        valueInvT.invert   ();
        valueInvT.transpose();

        tangSpaceMatrix.multLeft(valueInvT);
    }

    if(needTransform == true)
    {
        // transform properties
        MFPropertiesType::const_iterator pIt  = getMFProperties()->begin();
        MFPropertiesType::const_iterator pEnd = getMFProperties()->end  ();

        for(UInt32 i = 0; pIt != pEnd; ++pIt, ++i)
        {
            if(*pIt == NULL)
                continue;

            UInt32 propSpace = (*pIt)->getUsage() & GeoProperty::UsageSpaceMask;

            if(propSpace == GeoProperty::UsageObjectSpace)
            {
                SLOG << "SkinnedGeometry::setBindShapeMatrix: transforming prop "
                     << i << " with objSpaceMatrix" << std::endl;

                transformProperty<Pnt4f>(*pIt, objSpaceMatrix);
            }
            else if(propSpace == GeoProperty::UsageTangentSpace)
            {
                SLOG << "SkinnedGeometry::setBindShapeMatrix: transforming prop "
                     << i << " with tangSpaceMatrix" << std::endl;

                transformProperty<Vec4f>(*pIt, tangSpaceMatrix);
            }
        }
    }
#endif

    Inherited::setBindShapeMatrix(value);
}

Action::ResultE
SkinnedGeometry::renderEnter(Action *action)
{
    if(_sfSkeleton.getValue() == NULL)
    {
        SWARNING << "SkinnedGeometry::renderEnter: No skeleton." << std::endl;

        return Action::Continue;
    }

    if(_sfSkinningAlgorithm.getValue() == NULL)
    {
        SWARNING << "SkinnedGeometry::renderEnter: No SkinningAlgorithm."
                 << std::endl;
        return Action::Continue;
    }

    return _sfSkinningAlgorithm.getValue()->renderEnter(action);
}

Action::ResultE
SkinnedGeometry::renderLeave(Action *action)
{
    if(_sfSkeleton.getValue() == NULL)
    {
        SWARNING << "SkinnedGeometry::renderLeave: No skeleton." << std::endl;

        return Action::Continue;
    }

    if(_sfSkinningAlgorithm.getValue() == NULL)
    {
        SWARNING << "SkinnedGeometry::renderLeave: No SkinningAlgorithm."
                 << std::endl;
        return Action::Continue;
    }

    return _sfSkinningAlgorithm.getValue()->renderLeave(action);
}

void
SkinnedGeometry::fill(DrawableStatsAttachment *drawStats)
{
    Inherited::fill(drawStats);
}

void SkinnedGeometry::adjustVolume(Volume &volume)
{
    if(_sfSkinningAlgorithm.getValue() != NULL)
    {
        _sfSkinningAlgorithm.getValue()->adjustVolume(volume);
    }
    else
    {
        Inherited::adjustVolume(volume                       );
        volume.transform       (_sfBindShapeMatrix.getValue());

        SLOG << "SkinnedGeometry::adjustVolume: Using Mesh vol "
             << std::endl;
    }
}

void SkinnedGeometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkinnedGeometry NI" << std::endl;
}

OSG_END_NAMESPACE
