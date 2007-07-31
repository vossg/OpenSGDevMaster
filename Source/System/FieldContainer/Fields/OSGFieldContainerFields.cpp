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

#include <OSGFieldContainerSFields.h>
#include <OSGFieldContainerMFields.h>

#include <OSGTypeBasePredicates.h>
#include <OSGReflexiveContainerTypePredicates.h>

OSG_BEGIN_NAMESPACE
#if 0
template<>
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 SingleField                  >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FieldContainerPtr fc =
        static_cast<const SFFieldContainerPtr*>(pSrc)->getValue();

    if(fc != NullFC)
    {
        const FieldContainerType& fcType = fc->getType();

        // test if fc type should NOT be ignored
        if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                            ignoreGroupIds.end(), fcType) &&
           !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                            ignoreTypes.end(),    fcType)   )
        {
            // test if fc should NOT be shared
            if(!TypePredicates::typeInGroupIds (shareGroupIds.begin(),
                                                shareGroupIds.end(), fcType) &&
               !TypePredicates::typeDerivedFrom(shareTypes.begin(),
                                                shareTypes.end(),    fcType)   )
            {
                fc = OSG::deepClone(fc, shareTypes,    ignoreTypes,
                                        shareGroupIds, ignoreGroupIds);
            }
        }
        else
        {
            fc = NullFC;
        }
    }

    pDst->pushToField(fc, fieldId);
}

template<>
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 MultiField                   >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    const MFFieldContainerPtr *pFCField =
        static_cast<const MFFieldContainerPtr *>(pSrc);
    MFFieldContainerPtr::const_iterator fieldIter = pFCField->begin();
    MFFieldContainerPtr::const_iterator fieldEnd  = pFCField->end();

    // TODO: Could this be optimized by checking ignore/share just once ?
    for(; fieldIter != fieldEnd; ++fieldIter)
    {
        FieldContainerPtr fc = *fieldIter;

        if(fc != NullFC)
        {
            const FieldContainerType& fcType = fc->getType();

            // test if fc type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                                ignoreGroupIds.end(),
                                                fcType                 ) &&
               !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                                ignoreTypes.end(),
                                                fcType                 )   )
            {
                // test if fc should NOT be shared
                if(!TypePredicates::typeInGroupIds (shareGroupIds.begin(),
                                                    shareGroupIds.end(),
                                                    fcType                ) &&
                   !TypePredicates::typeDerivedFrom(shareTypes.begin(),
                                                    shareTypes.end(),
                                                    fcType                )   )
                {
                    fc = OSG::deepClone(fc, shareTypes,    ignoreTypes,
                                            shareGroupIds, ignoreGroupIds);
                }
            }
        }

        pDst->pushToField(fc, fieldId);
    }
}

template <>
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 SingleField                  >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FieldContainerPtr fc =
        static_cast<const SFFieldContainerPtr*>(pSrc)->getValue();

    if(fc != NullFC)
    {
        const FieldContainerType& fcType = fc->getType();

        // test if att type should NOT be ignored
        if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                            ignoreGroupIds.end(), fcType) &&
           !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                            ignoreTypes.end(),    fcType)   )
        {
            // test if att should cloned
            if(TypePredicates::typeInGroupIds (cloneGroupIds.begin(),
                                               cloneGroupIds.end(), fcType) ||
               TypePredicates::typeDerivedFrom(cloneTypes.begin(),
                                               cloneTypes.end(),    fcType)   )
            {
                fc = OSG::deepClone(fc, cloneTypes,    ignoreTypes,
                                        cloneGroupIds, ignoreGroupIds);
            }
        }
        else
        {
            fc = NullFC;
        }
    }

    pDst->pushToField(fc, fieldId);
}

template <>
void
FieldDescription<FieldTraits<FieldContainerPtr>,
                 MultiField                   >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    const MFFieldContainerPtr *pFCField =
        static_cast<const MFFieldContainerPtr *>(pSrc);
    MFFieldContainerPtr::const_iterator fieldIter = pFCField->begin();
    MFFieldContainerPtr::const_iterator fieldEnd  = pFCField->end();

    // TODO: Could this be optimized by checking ignore/clone just once ?
    for(; fieldIter != fieldEnd; ++fieldIter)
    {
        FieldContainerPtr fc = *fieldIter;

        if(fc != NullFC)
        {
            const FieldContainerType& fcType = fc->getType();

            // test if att type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                                ignoreGroupIds.end(),
                                                fcType                 ) &&
                !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                                 ignoreTypes.end(),
                                                 fcType                )   )
            {
                // test if att should cloned
                if(TypePredicates::typeInGroupIds (cloneGroupIds.begin(),
                                                   cloneGroupIds.end(),
                                                   fcType                ) ||
                   TypePredicates::typeDerivedFrom(cloneTypes.begin(),
                                                   cloneTypes.end(),
                                                   fcType                )   )
                {
                    fc = OSG::deepClone(fc, cloneTypes,    ignoreTypes,
                                            cloneGroupIds, ignoreGroupIds);
                }
            }
        }

        pDst->pushToField(fc, fieldId);
    }
}
#endif

OSG_END_NAMESPACE
