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

#include <OSGFieldContainer.h>
#include <OSGAttachmentMapSFields.h>
#include <OSGFieldContainerAttachment.h>
#include <OSGAttachmentContainer.h>
#include <OSGContainerPtrFuncs.h>

OSG_BEGIN_NAMESPACE

template<> 
void FieldDescription<SFFieldContainerAttachmentPtrMap::SFieldTraits, 
                      SingleField                           >::cloneValues(
    const Field                     *pSrc,
          ConstFieldMaskArg          whichField,
    const StringVector              &share,
          FieldContainerPtrConstArg  pDst) const
{
    const SFFieldContainerAttachmentPtrMap *pAttMap = 
        static_cast<const SFFieldContainerAttachmentPtrMap *>(pSrc);
            
    FieldContainerAttachmentMap::const_iterator mapIt  = 
        pAttMap->getValue().begin();

    FieldContainerAttachmentMap::const_iterator mapEnd = 
        pAttMap->getValue().end();
    
    AttachmentContainerPtr pDstAC = cast_dynamic<AttachmentContainerPtr>(pDst);

    while(mapIt != mapEnd)
    {
        FieldContainerAttachmentPtr fc = mapIt->second;
        UInt16                      uiBinding = UInt16(mapIt->first & 
                                                       0x0000FFFF   );

        bool shareit = false;

        for(UInt32 k = 0;k < share.size(); ++k)
        {
            FieldContainerType *fct = 
                FieldContainerFactory::the()->findType(share[k].c_str());

            if(fc  != NullFC && 
               fct != NULL   &&
               fc->getType().isDerivedFrom(*fct))
            {
                shareit = true;
                break;
            }
        }
        
        if(!shareit)
        {
            fc = cast_dynamic<FieldContainerAttachmentPtr>(
                OSG::deepClone(fc, share));
        }

        
        pDstAC->addAttachment(fc, uiBinding);
        
        ++mapIt;
    }
}

OSG_END_NAMESPACE
