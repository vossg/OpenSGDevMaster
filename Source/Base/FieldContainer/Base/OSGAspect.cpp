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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGAspect.h"
#include "OSGFieldContainer.h"
#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"

OSG_BEGIN_NAMESPACE

namespace Aspect
{
    FieldContainer *initializeContainerFrom(FieldContainer *pSrc)
    {
        FieldContainer *returnValue = NULL;

        returnValue = convertToCurrent(pSrc);

        if(returnValue == NULL)
        {
            returnValue = pSrc->getType().createAspectCopy(pSrc,
                                                           pSrc->getId());


            returnValue->setupAspectStore(pSrc->getAspectStore());

            const FieldContainerType &fcType = pSrc->getType();

            UInt32 fCount = fcType.getNumFieldDescs();

            for(UInt32 i = 1; i <= fCount; ++i)
            {
                const FieldDescriptionBase *fDesc = fcType.getFieldDesc(i);

                if(fDesc->isInternal())
                    continue;

                GetFieldHandlePtr srcField = pSrc->getField(i);

                FieldContainerPtrSFieldBase::GetHandlePtr sfFCPtr = 
                    boost::dynamic_pointer_cast<
                              FieldContainerPtrSFieldBase::GetHandle>(srcField);

                FieldContainerPtrMFieldBase::GetHandlePtr mfFCPtr = 
                    boost::dynamic_pointer_cast<
                              FieldContainerPtrMFieldBase::GetHandle>(srcField);

                if(sfFCPtr != NULL && sfFCPtr->isValid() == true)
                {
                    fprintf(stderr, "initializing sfield %s, cnt: %s\n",
                            fDesc->getCName(),
                            (*sfFCPtr)->getValue()->getType().getCName());
                            
                    initializeContainerFrom((*sfFCPtr)->getValue());
                }
                else if(mfFCPtr != NULL && mfFCPtr->isValid() == true)
                {
                    SizeT mfSize = (*mfFCPtr)->size();
                    
                    for(SizeT i = 0; i < mfSize; i++)
                    {
                        fprintf(stderr, 
                                "initializing mfield[%"PRIUSize
                                "] %s, cnt: %s\n",
                                i,
                                fDesc->getCName(),
                                (**mfFCPtr)[i]->getType().getCName());

                        initializeContainerFrom((**mfFCPtr)[i]);
                    }
                }
            }

            AspectOffsetStore   oOffsets;
            BitVector           syncMode = 0;
            UInt32              srcAspect = 
                pSrc->getAspectStore()->getAspect(pSrc);

            UInt32              dstAspect = Thread::getCurrentAspect();

            UInt32              uiSInfo = (srcAspect << 24) | (dstAspect << 16);


            pSrc->getAspectStore()->fillOffsetArray(oOffsets, returnValue);

            returnValue->execSyncV(*pSrc,
                                    TypeTraits<BitVector>::BitsSet,
                                    oOffsets,
                                    syncMode,
                                    uiSInfo);
        }

        return returnValue;
    }
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
