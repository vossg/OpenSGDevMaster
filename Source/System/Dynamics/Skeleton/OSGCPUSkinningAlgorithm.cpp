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

#include "OSGCPUSkinningAlgorithm.h"
#include "OSGCPUSkinningDataAttachment.h"
#include "OSGGeoPumpGroup.h"
#include "OSGIntersectAction.h"
#include "OSGPrimeMaterial.h"
#include "OSGTriangleIterator.h"
#include "OSGTypedGeoIntegralProperty.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCPUSkinningAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGCPUSkinningAlgorithm.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

namespace
{
    template <class PropertyTypeT>
    void xformObjectSpaceProperty(
        const MFMatrix            *mfJointMat,
        const GeoVec4fProperty    *jointIdxProp,
        const GeoVec4fProperty    *jointWeightProp,
        const GeoVectorProperty   *origProp,
              GeoVectorProperty   *prop      )
    {
        const PropertyTypeT                 *typedOrigProp =
            boost::polymorphic_downcast<const PropertyTypeT *>(origProp);
        PropertyTypeT                       *typedProp     =
            boost::polymorphic_downcast<PropertyTypeT *>(prop);

        const typename PropertyTypeT::StoredFieldType *origPnt  =
            typedOrigProp->getFieldPtr();
        typename PropertyTypeT::StoredFieldType       *xformPnt =
            typedProp    ->editFieldPtr();

        for(UInt32 i = 0; i < origPnt->size(); ++i)
        {
            typename PropertyTypeT::StoredType outPnt;
            Real32                             sumWeights = 0.f;

            for(UInt16 j = 0; j < 4; ++j)
            {
                Int32 jIdx = static_cast<Int32>((*jointIdxProp)[i][j]);

                if(jIdx >= 0)
                {
                    typename PropertyTypeT::StoredType tmpPnt;
                    (*mfJointMat)[jIdx].mult((*origPnt)[i], tmpPnt);

                    outPnt     += ((*jointWeightProp)[i][j] * tmpPnt).subZero();
                    sumWeights +=  (*jointWeightProp)[i][j];
                }
                else
                {
                    break;
                }
            }

            (*xformPnt)[i] = (1.f / sumWeights) * outPnt;
        }
    }

    template <class PropertyTypeT, class PropIndexTypeT>
    void xformIndexedObjectSpaceProperty(
        const MFMatrix            *mfJointMat,
        const GeoVec4fProperty    *jointIdxProp,
        const GeoVec4fProperty    *jointWeightProp,
        const GeoIntegralProperty *origPropIdx,
        const GeoVectorProperty   *origProp,
              GeoVectorProperty   *prop      )
    {
        const PropertyTypeT                 *typedOrigProp    =
            boost::polymorphic_downcast<const PropertyTypeT *>(origProp);
        const PropIndexTypeT                *typedOrigPropIdx =
            boost::polymorphic_downcast<const PropIndexTypeT *>(origPropIdx);
        PropertyTypeT                       *typedProp        =
            boost::polymorphic_downcast<PropertyTypeT *>(prop);

        const typename PropertyTypeT::StoredFieldType  *origPnt  =
            typedOrigProp->getFieldPtr();
        const typename PropIndexTypeT::StoredFieldType *origI    =
            typedOrigPropIdx->getFieldPtr();
        typename PropertyTypeT::StoredFieldType        *xformPnt =
            typedProp->editFieldPtr();

        for(UInt32 i = 0; i < origI->size(); ++i)
        {
            typename PropIndexTypeT::StoredType vIdx = (*origI)[i];
            typename PropertyTypeT::StoredType  outPnt;
            Real32                              sumWeights = 0.f;

            for(UInt16 j = 0; j < 4; ++j)
            {
                Int32 jIdx = static_cast<Int32>((*jointIdxProp)[vIdx][j]);

                if(jIdx >= 0)
                {
                    typename PropertyTypeT::StoredType tmpPnt;
                    (*mfJointMat)[jIdx].mult((*origPnt)[vIdx], tmpPnt);

                    outPnt     += ((*jointWeightProp)[vIdx][j] * tmpPnt).subZero();
                    sumWeights +=  (*jointWeightProp)[vIdx][j];
                }
                else
                {
                    break;
                }
            }

            (*xformPnt)[vIdx] = (1.f / sumWeights) * outPnt;
        }
    }

    template <class PropertyTypeT>
    void xformTangentSpaceProperty(
        const MFMatrix            *mfJointMat,
        const GeoVec4fProperty    *jointIdxProp,
        const GeoVec4fProperty    *jointWeightProp,
        const GeoVectorProperty   *origProp,
              GeoVectorProperty   *prop      )
    {
        const PropertyTypeT *typedOrigProp =
            boost::polymorphic_downcast<const PropertyTypeT *>(origProp);
        PropertyTypeT       *typedProp     =
            boost::polymorphic_downcast<PropertyTypeT *>(prop);

        const typename PropertyTypeT::StoredFieldType *origVec  =
            typedOrigProp->getFieldPtr();
        typename PropertyTypeT::StoredFieldType       *xformVec =
            typedProp    ->editFieldPtr();

        for(UInt32 i = 0; i < origVec->size(); ++i)
        {
            typename PropertyTypeT::StoredType outVec;
            Real32                             sumWeights = 0.f;

            for(UInt16 j = 0; j < 4; ++j)
            {
                Int32 jIdx = static_cast<Int32>((*jointIdxProp)[i][j]);

                if(jIdx >= 0)
                {
                    typename PropertyTypeT::StoredType tmpVec;

                    (*mfJointMat)[jIdx].mult((*origVec)[i], tmpVec);

                    outVec     += (*jointWeightProp)[i][j] * tmpVec;
                    sumWeights += (*jointWeightProp)[i][j];
                }
                else
                {
                    break;
                }
            }

            (*xformVec)[i] = (1.f / sumWeights) * outVec;
        }
    }

    
    template <class PropertyTypeT, class PropIndexTypeT>
    void xformIndexedTangentSpaceProperty(
        const MFMatrix            *mfJointMat,
        const GeoVec4fProperty    *jointIdxProp,
        const GeoVec4fProperty    *jointWeightProp,
        const GeoIntegralProperty *origPropIdx,
        const GeoVectorProperty   *origProp,
              GeoVectorProperty   *prop      )
    {
        const PropertyTypeT  *typedOrigProp    =
            boost::polymorphic_downcast<const PropertyTypeT *>(origProp);
        const PropIndexTypeT *typedOrigPropIdx =
            boost::polymorphic_downcast<const PropIndexTypeT *>(origPropIdx);
        PropertyTypeT        *typedProp        =
            boost::polymorphic_downcast<PropertyTypeT *>(prop);

        const typename PropertyTypeT::StoredFieldType  *origVec  =
            typedOrigProp->getFieldPtr();
        const typename PropIndexTypeT::StoredFieldType *origI    =
            typedOrigPropIdx->getFieldPtr();
        typename PropertyTypeT::StoredFieldType        *xformVec =
            typedProp->editFieldPtr();

        for(UInt32 i = 0; i < origI->size(); ++i)
        {
            typename PropIndexTypeT::StoredType vIdx = (*origI)[i];
            typename PropertyTypeT::StoredType  outVec;
            Real32                              sumWeights = 0.f;

            for(UInt16 j = 0; j < 4; ++j)
            {
                Int32 jIdx = static_cast<Int32>((*jointIdxProp)[vIdx][j]);

                if(jIdx >= 0)
                {
                    typename PropertyTypeT::StoredType tmpVec;

                    (*mfJointMat)[jIdx].mult((*origVec)[vIdx], tmpVec);

                    outVec     += (*jointWeightProp)[vIdx][j] * tmpVec;
                    sumWeights += (*jointWeightProp)[vIdx][j];
                }
                else
                {
                    break;
                }
            }

            (*xformVec)[vIdx] = (1.f / sumWeights) * outVec;
        }
    }

} // namespace

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CPUSkinningAlgorithm::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CPUSkinningAlgorithm::CPUSkinningAlgorithm(void) :
    Inherited()
{
}

CPUSkinningAlgorithm::CPUSkinningAlgorithm(const CPUSkinningAlgorithm &source) :
    Inherited(source)
{
}

CPUSkinningAlgorithm::~CPUSkinningAlgorithm(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CPUSkinningAlgorithm::adjustVolume(Volume &volume)
{
    SkinnedGeometry *skinGeo = getSkin();

    if(skinGeo != NULL)
    {
        skinGeo->Inherited::adjustVolume(volume);
    }
}

ActionBase::ResultE
CPUSkinningAlgorithm::renderEnter(Action *action)
{
    Action::ResultE  res     = Action::Continue;
    SkinnedGeometry *skinGeo = getSkin    ();
    Skeleton        *skel    = getSkeleton();
    RenderAction    *ract    =
        boost::polymorphic_downcast<RenderAction *>(action); 

    OSG_ASSERT(skinGeo != NULL);
    OSG_ASSERT(skel    != NULL);

    CPUSkinningDataAttachmentUnrecPtr data = getCPUSkinningData(skinGeo);

    if(data == NULL)
    {
        data = CPUSkinningDataAttachment::create();
        skinGeo->addAttachment(data);
    }

    skel->renderEnter(action, skinGeo);

    if(data->getDataValid() == false)
    {
        transformGeometry(skinGeo, skel, data);

        data->setDataValid(true);
    }

    renderGeometry(ract, skinGeo, data);

    return res;
}

ActionBase::ResultE
CPUSkinningAlgorithm::renderLeave(Action *action)
{
    return Action::Continue;
}

ActionBase::ResultE
CPUSkinningAlgorithm::intersectEnter(Action *action)
{
    Action::ResultE  res     = Action::Continue;
    SkinnedGeometry *skinGeo = getSkin    ();
    Skeleton        *skel    = getSkeleton();
    IntersectAction *iact    =
        boost::polymorphic_downcast<IntersectAction *>(action);

    CPUSkinningDataAttachmentUnrecPtr data = getCPUSkinningData(skinGeo);

    if(data == NULL)
    {
        data = CPUSkinningDataAttachment::create();
        skinGeo->addAttachment(data);
    }

    skel->intersectEnter(action, skinGeo);

    if(data->getDataValid() == false)
    {
        transformGeometry(skinGeo, skel, data);

        data->setDataValid(true);
    }

    intersectGeometry(iact, skinGeo, data);

    return res;
}

CPUSkinningAlgorithm::RenderModeE
CPUSkinningAlgorithm::getRenderMode(void) const
{
    return SkinnedGeometry::RMSkinnedCPU;
}

void CPUSkinningAlgorithm::changed(ConstFieldMaskArg whichField, 
                                   UInt32            origin,
                                   BitVector         details)
{
    if((SkeletonFieldMask & whichField) != 0    &&
       _sfSkeleton.getValue()           != NULL   )
    {
        if(_sfSkeleton.getValue()->hasChangedFunctor(boost::bind(
               &CPUSkinningAlgorithm::skeletonChanged,
               this, _1, _2                                )) == false)
        {
            _sfSkeleton.getValue()->addChangedFunctor(boost::bind(
                &CPUSkinningAlgorithm::skeletonChanged,
                this, _1, _2                                ),
                "CPUSkinningAlgorithm::skeletonChanged"  );
        }
    }

    Inherited::changed(whichField, origin, details);
}

void CPUSkinningAlgorithm::dump(      UInt32    ,
                                      const BitVector ) const
{
    SLOG << "Dump CPUSkinningAlgorithm NI" << std::endl;
}

void CPUSkinningAlgorithm::transformGeometry(
    SkinnedGeometry           *skinGeo,
    Skeleton                  *skel,
    CPUSkinningDataAttachment *data)
{
    const SkinnedGeometry::MFPropIndicesType *mfOrigIdx   =
        skinGeo->getMFPropIndices();
    const SkinnedGeometry::MFPropertiesType  *mfOrigProps =
        skinGeo->getMFProperties();
    SkinnedGeometry::MFPropertiesType        *mfProps     =
        data->editMFProperties();

    const GeoVec4fProperty *jointIdxProp    =
        dynamic_cast<const GeoVec4fProperty *>(
            (*mfOrigProps)[skinGeo->getJointIndexProperty()]);
    const GeoVec4fProperty *jointWeightProp =
        dynamic_cast<const GeoVec4fProperty *>(
            (*mfOrigProps)[skinGeo->getJointWeightProperty()]);

    if(skinGeo->getIndex(skinGeo->getJointIndexProperty ()) !=
       skinGeo->getIndex(skinGeo->getJointWeightProperty())   )
    {
        SWARNING << "CPUSkinningAlgorithm::transformGeometry: "
                 << "Multi indexed geometry not supported!"
                 << std::endl;
        return;
    }

    mfProps->resize(mfOrigProps->size(), NULL);

    const MFMatrix *mfJointMat       = NULL;
    const MFMatrix *mfJointNormalMat = NULL;

    // if the geometry has a non-identity bind shape matrix
    // premultiply joint matrices with bind shape matrix and store in data
    // attachment
    if(skinGeo->getBindShapeMatrix().equals(Matrix::identity(), Eps) == false)
    {
        mfJointMat               = skel->getMFJointMatrices ();
        MFMatrix *mfJointBindMat = data->editMFJointMatrices();

        mfJointBindMat->resize(mfJointMat->size());

        for(UInt32 i = 0; i < mfJointMat->size(); ++i)
        {
            (*mfJointBindMat)[i] = (*mfJointMat)[i];
            (*mfJointBindMat)[i].mult(skinGeo->getBindShapeMatrix());
        }

        mfJointMat = data->getMFJointMatrices();

        if(skel->getCalcNormalMatrices() == true)
        {
            mfJointNormalMat               = skel->getMFJointNormalMatrices ();
            MFMatrix *mfJointNormalBindMat = data->editMFJointNormalMatrices();

            mfJointNormalBindMat->resize(mfJointNormalMat->size());

            for(UInt32 i = 0; i < mfJointNormalMat->size(); ++i)
            {
                (*mfJointNormalBindMat)[i] = (*mfJointNormalMat)[i];
                (*mfJointNormalBindMat)[i].mult(skinGeo->getBindShapeMatrix());
            }

            mfJointNormalMat = data->getMFJointNormalMatrices();
        }
        else
        {
            mfJointNormalMat = data->getMFJointMatrices();
        }
    }
    else
    {
        mfJointMat = skel->getMFJointMatrices();

        if(skel->getCalcNormalMatrices() == true)
        {
            mfJointNormalMat = skel->getMFJointNormalMatrices();
        }
        else
        {
            mfJointNormalMat = skel->getMFJointMatrices();
        }
    }

    // transform all properties

    for(UInt16 i = 0; i < mfProps->size(); ++i)
    {
        // do not transform the vertex joint indices/weights
        if(i == skinGeo->getJointIndexProperty () ||
           i == skinGeo->getJointWeightProperty()   )
        {
            continue;
        }

        GeoIntegralProperty *origPropIdx = (*mfOrigIdx  )[i];
        GeoVectorProperty   *origProp    = (*mfOrigProps)[i];
        GeoVectorProperty   *prop        = (*mfProps    )[i];

        if(origProp == NULL)
            continue;

        if(prop == NULL)
        {
            GeoVectorPropertyUnrecPtr newProp =
                dynamic_pointer_cast<GeoVectorProperty>(origProp->clone());

            mfProps->replace(i, newProp);
            prop = newProp;
        }
        else if(prop->size() != origProp->size())
        {
            prop->resize(origProp->size());
        }

        switch(origProp->getUsage() & GeoProperty::UsageSpaceMask)
        {
        case GeoProperty::UsageObjectSpace:
        {
             transformObjectSpaceProperty(
                 mfJointMat,
                 jointIdxProp, jointWeightProp,
                 origPropIdx, origProp, prop);
        }
        break;

        case GeoProperty::UsageTangentSpace:
        {
            transformTangentSpaceProperty(
                mfJointNormalMat,
                jointIdxProp, jointWeightProp,
                origPropIdx, origProp, prop);
        }
        break;

        default:
            // only need to transform object/tangent space properties
            break;
        }
    }
}

/*! Transforms a property that contains object space values (positions).
 */
void CPUSkinningAlgorithm::transformObjectSpaceProperty(
    const MFMatrix            *mfJointMat,
    const GeoVec4fProperty    *jointIdxProp,
    const GeoVec4fProperty    *jointWeightProp,
    const GeoIntegralProperty *origPropIdx,
    const GeoVectorProperty   *origProp,
          GeoVectorProperty   *prop     )
{
    if(origPropIdx              != NULL              &&
       origPropIdx->getFormat() == GL_UNSIGNED_SHORT   )
    {
        // handle most common Pnt3f/Pnt4f cases
        if(origProp->getVectorType() == GeoProperty::VectorTypePoint &&
           origProp->getDimension () == 3                            &&
           origProp->getFormat    () == GL_FLOAT                       )
        {
            xformIndexedObjectSpaceProperty<
                GeoPnt3fProperty,
                GeoUInt16Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx,  origProp, prop);
        }
        else if(origProp->getVectorType() == GeoProperty::VectorTypePoint &&
                origProp->getDimension () == 4                            &&
                origProp->getFormat    () == GL_FLOAT                       )
        {
            xformIndexedObjectSpaceProperty<
                GeoPnt4fProperty,
                GeoUInt16Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx, origProp, prop);
        }
        else
        {
            SWARNING << "CPUSkinningAlgorithm::transformObjectSpaceProperty: "
                     << "generic transform NIY" << std::endl;
        }
    }
    else if(origPropIdx              != NULL            &&
            origPropIdx->getFormat() == GL_UNSIGNED_INT   )
    {
        // handle most common Pnt3f/Pnt4f cases
        if(origProp->getVectorType() == GeoProperty::VectorTypePoint &&
           origProp->getDimension () == 3                            &&
           origProp->getFormat    () == GL_FLOAT                       )
        {
            xformIndexedObjectSpaceProperty<
                GeoPnt3fProperty,
                GeoUInt32Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx, origProp, prop);
        }
        else if(origProp->getVectorType() == GeoProperty::VectorTypePoint &&
                origProp->getDimension () == 4                            &&
                origProp->getFormat    () == GL_FLOAT                       )
        {
            xformIndexedObjectSpaceProperty<
                GeoPnt4fProperty,
                GeoUInt32Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx, origProp, prop);
        }
        else
        {
            SWARNING << "CPUSkinningAlgorithm::transformObjectSpaceProperty: "
                     << "generic transform NIY" << std::endl;
        }
    }
    else if(origPropIdx == NULL)
    {
        // handle most common Pnt3f/Pnt4f cases
        if(origProp->getVectorType() == GeoProperty::VectorTypePoint &&
           origProp->getDimension () == 3                            &&
           origProp->getFormat    () == GL_FLOAT                       )
        {
            xformObjectSpaceProperty<
                GeoPnt3fProperty>(mfJointMat,
                                  jointIdxProp, jointWeightProp,
                                  origProp, prop);
        }
        else if(origProp->getVectorType() == GeoProperty::VectorTypePoint &&
                origProp->getDimension () == 4                            &&
                origProp->getFormat    () == GL_FLOAT                       )
        {
            xformObjectSpaceProperty<
                GeoPnt4fProperty>(mfJointMat,
                                  jointIdxProp, jointWeightProp,
                                  origProp, prop);
        }
        else
        {
            SWARNING << "CPUSkinningAlgorithm::transformObjectSpaceProperty: "
                     << "generic transform NIY" << std::endl;
        }
    }
    else
    {
        SWARNING << "CPUSkinningAlgorithm::transformObjectSpaceProperty: "
                 << "Unknown index format." << std::endl;
    }
}

/*! Transforms a property that contains tangent space values (normals,
    tangents, bitangents).
 */
void CPUSkinningAlgorithm::transformTangentSpaceProperty(
    const MFMatrix            *mfJointMat,
    const GeoVec4fProperty    *jointIdxProp,
    const GeoVec4fProperty    *jointWeightProp,
    const GeoIntegralProperty *origPropIdx,
    const GeoVectorProperty   *origProp,
          GeoVectorProperty   *prop     )
{
    if(origPropIdx              != NULL              &&
       origPropIdx->getFormat() == GL_UNSIGNED_SHORT   )
    {
        // handle most common Vec3f/Vec4f cases
        if(origProp->getVectorType() == GeoProperty::VectorTypeVector &&
           origProp->getDimension () == 3                             &&
           origProp->getFormat    () == GL_FLOAT                        )
        {
            xformIndexedTangentSpaceProperty<
                GeoVec3fProperty,
                GeoUInt16Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx, origProp, prop);
        }
        else if(origProp->getVectorType() == GeoProperty::VectorTypeVector &&
                origProp->getDimension () == 4                             &&
                origProp->getFormat    () == GL_FLOAT                        )
        {
            xformIndexedTangentSpaceProperty<
                GeoVec4fProperty,
                GeoUInt16Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx, origProp, prop);
        }
        else
        {
            SWARNING << "CPUSkinningAlgorithm::transformTangentSpaceProperty: "
                     << "generic transform NIY" << std::endl;
        }
    }
    else if(origPropIdx              != NULL            &&
            origPropIdx->getFormat() == GL_UNSIGNED_INT   )
    {
        // handle most common Vec3f/Vec4f cases
        if(origProp->getVectorType() == GeoProperty::VectorTypeVector &&
           origProp->getDimension () == 3                             &&
           origProp->getFormat    () == GL_FLOAT                        )
        {
            xformIndexedTangentSpaceProperty<
                GeoVec3fProperty,
                GeoUInt32Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx, origProp, prop);
        }
        else if(origProp->getVectorType() == GeoProperty::VectorTypeVector &&
                origProp->getDimension () == 4                             &&
                origProp->getFormat    () == GL_FLOAT                        )
        {
            xformIndexedTangentSpaceProperty<
                GeoVec4fProperty,
                GeoUInt32Property>(mfJointMat,
                                   jointIdxProp, jointWeightProp,
                                   origPropIdx, origProp, prop);
        }
        else
        {
            SWARNING << "CPUSkinningAlgorithm::transformTangentSpaceProperty: "
                     << "generic transform NIY" << std::endl;
        }
    }
    else if(origPropIdx == NULL)
    {
        // handle most common Vec3f/Vec4f cases
        if(origProp->getVectorType() == GeoProperty::VectorTypeVector &&
           origProp->getDimension () == 3                             &&
           origProp->getFormat    () == GL_FLOAT                        )
        {
            xformTangentSpaceProperty<
                GeoVec3fProperty>(mfJointMat,
                                  jointIdxProp, jointWeightProp,
                                  origProp, prop);
        }
        else if(origProp->getVectorType() == GeoProperty::VectorTypeVector &&
                origProp->getDimension () == 4                             &&
                origProp->getFormat    () == GL_FLOAT                        )
        {
            xformTangentSpaceProperty<
                GeoVec4fProperty>(mfJointMat,
                                  jointIdxProp, jointWeightProp,
                                  origProp, prop);
        }
        else
        {
            SWARNING << "CPUSkinningAlgorithm::transformTangentSpaceProperty: "
                     << "generic transform NIY" << std::endl;
        }
    }
    else
    {
        SWARNING << "CPUSkinningAlgorithm::transformTangentSpaceProperty: "
                 << "Unknown index format." << std::endl;
    }
}

void CPUSkinningAlgorithm::renderGeometry(
    RenderAction              *ract,
    SkinnedGeometry           *skinGeo,
    CPUSkinningDataAttachment *data   )
{
    Material      *pMat      = ract->getMaterial();
    PrimeMaterial *pPrimeMat = NULL;

    if(pMat == NULL)
    {
        if(skinGeo->getMaterial() != NULL)
        {
            pPrimeMat = skinGeo->getMaterial()->finalize(
                ract->getRenderProperties(), ract->getWindow());
        }
    }
    else
    {
        pPrimeMat = pMat->finalize(
            ract->getRenderProperties(), ract->getWindow());
    }

    if(pPrimeMat == NULL)
    {
        SNOTICE << "CPUSkinningAlgorithm::preDrawPrimitives: No Material "
                << "for SkinnedGeometry " << skinGeo
                << std::endl;

        pPrimeMat = getDefaultMaterial();
    }

    DrawEnv::DrawFunctor drawFunc  = boost::bind(
        &CPUSkinningAlgorithm::drawPrimitives, this, skinGeo, data, _1);
    UInt32               uiNPasses = pPrimeMat->getNPasses();
    
    for(UInt32 uiPass = 0; uiPass < uiNPasses; ++uiPass)
    {
        State *st = pPrimeMat->getState(uiPass);
        
        if(st != NULL)
        {
            ract->dropFunctor(drawFunc,
                              st, 
                              pPrimeMat->getSortKey() + uiPass);
        }
        else
        {
            FINFO(("%s: Material %p has NULL state for pass %d\n",
                   OSG_FUNCNAME_MACRO, pPrimeMat, uiPass));
        }
    }
}

void CPUSkinningAlgorithm::drawPrimitives(
    SkinnedGeometry *skinGeo, CPUSkinningDataAttachment* data, DrawEnv *pEnv)
{
    // store glColor.
    Color4f color;

    if(skinGeo->getColors() != NULL)
        glGetFloatv(GL_CURRENT_COLOR, color.getValuesRGBA());

    GeoPumpGroup::PropertyCharacteristics prop =
        GeoPumpGroup::characterizeGeometry(skinGeo);

    GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, prop);

    if(pump != NULL)
    {
        pump(pEnv,
             skinGeo->getLengths(),      skinGeo->getTypes(),
             data   ->getMFProperties(), skinGeo->getMFPropIndices());
    }
    else
    {
        SWARNING << "CPUSkinningAlgorithm::drawPrimitives: no GeoPump found "
                 << "for SkinnedGeometry " << skinGeo
                 << std::endl;
    }

    // restore glColor.
    if(skinGeo->getColors() != NULL)
        glColor4fv(color.getValuesRGBA());
}

void CPUSkinningAlgorithm::intersectGeometry(IntersectAction           *iact,
                                             SkinnedGeometry           *skinGeo,
                                             CPUSkinningDataAttachment *data    )
{
    const GeoVectorProperty *pos    =
        data->getProperties(Geometry::PositionsIndex);
    TriangleIterator         triIt  = skinGeo->beginTriangles();
    TriangleIterator         triEnd = skinGeo->endTriangles  ();

    const Line              &line   = iact->getLine();
    Real32                   hitT   = 0.f;
    Vec3f                    hitNorm;

    for(; triIt != triEnd; ++triIt)
    {
        if(line.intersect(
               pos->getValue<Pnt3f>(triIt.getPositionIndex(0)),
               pos->getValue<Pnt3f>(triIt.getPositionIndex(1)),
               pos->getValue<Pnt3f>(triIt.getPositionIndex(2)), hitT, &hitNorm))
        {
            iact->setHit(hitT, iact->getActNode(),
                         triIt.getIndex(), hitNorm, -1);
        }
    }
}

void CPUSkinningAlgorithm::skeletonChanged(FieldContainer    *fc,
                                           ConstFieldMaskArg  whichField)
{
    if(((Skeleton::JointMatricesFieldMask      |
         Skeleton::JointNormalMatricesFieldMask) & whichField) != 0)
    {
        OSG_ASSERT(fc == _sfSkeleton.getValue());

        CPUSkinningDataAttachment *data =
            getCPUSkinningData(_sfSkin.getValue());

        if(data != NULL)
            data->setDataValid(false);
    }
}

void CPUSkinningAlgorithm::resolveLinks(void)
{
    if(_sfSkeleton.getValue() != NULL)
    {
        _sfSkeleton.getValue()->subChangedFunctor(boost::bind(
            &CPUSkinningAlgorithm::skeletonChanged,
            this, _1, _2                           ));
    }

    Inherited::resolveLinks();
}

OSG_END_NAMESPACE
