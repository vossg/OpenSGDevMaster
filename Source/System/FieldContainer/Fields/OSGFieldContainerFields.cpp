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

#include<OSGFieldContainerSFields.h>
#include<OSGFieldContainerMFields.h>

OSG_BEGIN_NAMESPACE

template<> 
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<FieldContainerPtr>, 
                      SingleField                   >::cloneValues(
    const Field                     *pSrc,
          ConstFieldMaskArg          whichField,
    const StringVector              &share,
          FieldContainerPtrConstArg  pDst) const

{
    FieldContainerPtr fc = 
        ((const SFFieldContainerPtr *) pSrc)->getValue();
    
    bool shareit = false;

    for(UInt32 k = 0; k < share.size(); ++k)
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
        fc = OSG::deepClone(fc, share);
    }

    pDst->pushToField(fc, whichField);
}

template<>
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<FieldContainerPtr>, 
                      MultiField                   >::cloneValues(
    const Field                     *pSrc,
          ConstFieldMaskArg          whichField,
    const StringVector              &share,
          FieldContainerPtrConstArg  pDst) const
{

    const MFFieldContainerPtr *pFCField = 
        static_cast<const MFFieldContainerPtr *>(pSrc);

    for(UInt32 j = 0;j < pFCField->size();++j)
    {
        FieldContainerPtr fc = (*pFCField)[j];
        
        bool shareit = false;

        for(UInt32 k = 0; k < share.size(); ++k)
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
            fc = OSG::deepClone(fc, share);
        }

        pDst->pushToField(fc, whichField);
    }
}


template<> 
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<FieldContainerPtr>, 
                      SingleField                   >::shareValues(
    const Field                     *pSrc,
          ConstFieldMaskArg          whichField,
          FieldContainerPtrConstArg  pDst) const

{
    FieldContainerPtr fc = 
        ((const SFFieldContainerPtr *) pSrc)->getValue();
    
    pDst->pushToField(fc, whichField);
}

template<>
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<FieldContainerPtr>, 
                      MultiField                   >::shareValues(
    const Field                     *pSrc,
          ConstFieldMaskArg          whichField,
          FieldContainerPtrConstArg  pDst) const
{

    const MFFieldContainerPtr *pFCField = 
        static_cast<const MFFieldContainerPtr *>(pSrc);

    for(UInt32 j = 0;j < pFCField->size();++j)
    {
        FieldContainerPtr fc = (*pFCField)[j];
        
        pDst->pushToField(fc, whichField);
    }
}

OSG_END_NAMESPACE
