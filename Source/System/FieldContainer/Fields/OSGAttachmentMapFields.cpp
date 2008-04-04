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

#define OSG_COMPILEATTACHMENTMAPFIELDINST

#include <OSGFieldContainer.h>
#include <OSGAttachmentMapSFields.h>
#include <OSGFieldContainerAttachment.h>
#include <OSGAttachmentContainer.h>
#include <OSGContainerPtrFuncs.h>

#include <OSGTypeBasePredicates.h>
#include <OSGReflexiveContainerTypePredicates.h>

#include <OSGSField.ins>

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include <OSGSFieldFuncs.ins>

#endif

//#include <OSGSFieldAdaptor.ins>


OSG_BEGIN_NAMESPACE
#if 0
template <>
void
FieldDescription<SFFieldContainerAttachmentPtrMap::SFieldTraits,
                 SingleField                                    >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    const SFFieldContainerAttachmentPtrMap *pAttMap =
        static_cast<const SFFieldContainerAttachmentPtrMap *>(pSrc);
    FieldContainerAttachmentMap::const_iterator mapIt  =
        pAttMap->getValue().begin();
    FieldContainerAttachmentMap::const_iterator mapEnd =
        pAttMap->getValue().end();
    AttachmentContainerPtr pDstAC = dynamic_cast<AttachmentContainerPtr>(pDst);

    for(; mapIt != mapEnd; ++mapIt)
    {
        FieldContainerAttachmentPtr att       = mapIt->second;
        UInt16                      uiBinding = UInt16(mapIt->first &
                                                       0x0000FFFF    );

        if(att != NullFC)
        {
            const FieldContainerType &attType = att->getType();

            // test if fc type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                                ignoreGroupIds.end(),
                                                attType                ) &&
               !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                                ignoreTypes.end(),
                                                attType                )   )
            {
                // test if fc should NOT be shared
                if(!TypePredicates::typeInGroupIds (shareGroupIds.begin(),
                                                    shareGroupIds.end(),
                                                    attType               ) &&
                   !TypePredicates::typeDerivedFrom(shareTypes.begin(),
                                                    shareTypes.end(),
                                                    attType               )   )
                {
                    att = dynamic_cast<FieldContainerAttachmentPtr>(
                        OSG::deepClone(att, shareTypes,    ignoreTypes,
                                            shareGroupIds, ignoreGroupIds));
                }
            }
        }

        pDstAC->addAttachment(att, uiBinding);
    }
}

template <>
void
FieldDescription<SFFieldContainerAttachmentPtrMap::SFieldTraits,
                 SingleField                                    >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    const SFFieldContainerAttachmentPtrMap *pAttMap =
        static_cast<const SFFieldContainerAttachmentPtrMap *>(pSrc);
    FieldContainerAttachmentMap::const_iterator mapIt  =
        pAttMap->getValue().begin();
    FieldContainerAttachmentMap::const_iterator mapEnd =
        pAttMap->getValue().end();
    AttachmentContainerPtr pDstAC = dynamic_cast<AttachmentContainerPtr>(pDst);

    for(; mapIt != mapEnd; ++mapIt)
    {
        FieldContainerAttachmentPtr att       = mapIt->second;
        UInt16                      uiBinding = UInt16(mapIt->first &
                                                       0x0000FFFF    );

        if(att != NullFC)
        {
            const FieldContainerType &attType = att->getType();

            // test if att type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                                ignoreGroupIds.end(),
                                                attType                ) &&
               !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                                ignoreTypes.end(),
                                                attType                )   )
            {
                // test if att should cloned
                if(TypePredicates::typeInGroupIds (cloneGroupIds.begin(),
                                                   cloneGroupIds.end(),
                                                   attType               ) ||
                   TypePredicates::typeDerivedFrom(cloneTypes.begin(),
                                                   cloneTypes.end(),
                                                   attType               )   )
                {
                    att = dynamic_cast<FieldContainerAttachmentPtr>(
                        OSG::deepClone(att, cloneTypes,    ignoreTypes,
                                            cloneGroupIds, ignoreGroupIds));
                }
            }
        }

        pDstAC->addAttachment(att, uiBinding);
    }
}
#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<FieldContainerAttachmentMap>::_type(
    "FieldContainerAttachmentMap",
    NULL);

OSG_FIELDTRAITS_GETTYPE(FieldContainerAttachmentMap)

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_FIELD_DLLEXPORT_DEF1(SField, FieldContainerAttachmentMap);

OSG_END_NAMESPACE
