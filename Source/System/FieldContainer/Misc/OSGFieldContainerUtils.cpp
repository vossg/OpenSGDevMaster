/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#include "OSGFieldContainerUtils.h"
#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"
#include "OSGAttachment.h"
#include "OSGAttachmentMapSFields.h"

OSG_BEGIN_NAMESPACE

namespace
{
    // anonymous namespace for implementation details of the compareContainer
    // function.

/*! Compares two PointerFields \a lhsField and \a rhsField by recursively
    comparing the pointed-to containers.
    This function is only used in \c compareContainer below.
 */
bool comparePointerFields(
    GetFieldHandlePtr lhsField, GetFieldHandlePtr rhsField,
    bool              ignoreAttachments,
    bool              compareIdentity                      )
{
    bool returnValue = true;
    
    SFAttachmentPtrMap::GetHandlePtr  lhsAMHandle =
        boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
            lhsField);
    SFAttachmentPtrMap::GetHandlePtr  rhsAMHandle =
        boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
            rhsField);
    
    FieldContainerPtrSFieldBase::GetHandlePtr lhsSFHandle =
        boost::dynamic_pointer_cast<
            FieldContainerPtrSFieldBase::GetHandle>(lhsField);
    FieldContainerPtrSFieldBase::GetHandlePtr rhsSFHandle =
        boost::dynamic_pointer_cast<
            FieldContainerPtrSFieldBase::GetHandle>(rhsField);
    
    FieldContainerPtrMFieldBase::GetHandlePtr lhsMFHandle =
        boost::dynamic_pointer_cast<
            FieldContainerPtrMFieldBase::GetHandle>(lhsField);
    FieldContainerPtrMFieldBase::GetHandlePtr rhsMFHandle =
        boost::dynamic_pointer_cast<
            FieldContainerPtrMFieldBase::GetHandle>(rhsField);
    
    if(lhsAMHandle != NULL && lhsAMHandle->isValid() &&
       rhsAMHandle != NULL && rhsAMHandle->isValid()   )
    {
        const AttachmentMap &lhsAM = (*lhsAMHandle)->getValue();
        const AttachmentMap &rhsAM = (*rhsAMHandle)->getValue();
        
        if(lhsAM.size() != rhsAM.size())
        {
            returnValue = false;
        }
        else
        {
            AttachmentMap::const_iterator lhsAMIt  = lhsAM.begin();
            AttachmentMap::const_iterator lhsAMEnd = lhsAM.end  ();
            
            AttachmentMap::const_iterator rhsAMIt  = rhsAM.begin();
            AttachmentMap::const_iterator rhsAMEnd = rhsAM.end  ();
            
            for(; lhsAMIt != lhsAMEnd && returnValue == true; ++lhsAMIt, ++rhsAMIt)
            {
                returnValue = compareContainerEqual(
                    lhsAMIt->second, rhsAMIt->second,
                    ignoreAttachments, compareIdentity);
            }
        }
    }
    else if(lhsSFHandle != NULL && lhsSFHandle->isValid() &&
            rhsSFHandle != NULL && rhsSFHandle->isValid()   )
    {
        returnValue = compareContainerEqual(
            lhsSFHandle->get(), rhsSFHandle->get(),
            ignoreAttachments, compareIdentity     );
    }
    else if(lhsMFHandle != NULL && lhsMFHandle->isValid() &&
            rhsMFHandle != NULL && rhsMFHandle->isValid()   )
    {
        if(lhsMFHandle->size() != rhsMFHandle->size())
        {
            returnValue = false;
        }
        else
        {
            for(UInt32 i = 0; i < lhsMFHandle->size() && returnValue == true;
                ++i)
            {
                returnValue = compareContainerEqual(
                    lhsMFHandle->get(i), rhsMFHandle->get(i),
                    ignoreAttachments, compareIdentity       );
            }
        }
    }
    
    return returnValue;
}

} // namespace

/*! Compares two FieldContainer \a lhs and \a rhs for equivalence. The meaning
    of this comparison can be tweaked with the additional arguments.
    If \a ignoreAttachments is \c true, Attachments are excluded from the
    comparison.
    If \a compareIdentity is \c true, pointers are compared by
    address otherwise the pointed-to objects are compared for equivalence.
 */
bool compareContainerEqual(
    const FieldContainer *lhs,
    const FieldContainer *rhs,
          bool            ignoreAttachments,
          bool            compareIdentity   )
{
    // compare pointers
    if(lhs == rhs)
        return true;
    
    if(lhs == NULL || rhs == NULL)
        return false;
    
    // different types ?
    if(lhs->getType() != rhs->getType())
        return false;
    
    UInt32 lhsFCount = lhs->getType().getNumFieldDescs();
    UInt32 rhsFCount = rhs->getType().getNumFieldDescs();
    
    // different number of (dynamic) fields ?
    if(lhsFCount != rhsFCount)
        return false;
    
    bool returnValue = true;
    
    for(UInt32 i = 1; i <= lhsFCount && returnValue == true; ++i)
    {
        GetFieldHandlePtr lhsField = lhs->getField(i);
        GetFieldHandlePtr rhsField = rhs->getField(i);
        
        // valid handles ?
        if(lhsField == NULL || lhsField->isValid() == false ||
           rhsField == NULL || rhsField->isValid() == false   )
            continue;
        
        if(lhsField->getType() != rhsField->getType())
        {
            returnValue = false;
            continue;
        }
        
        // skip internal and parent fields
        if(lhsField->isInternal()            == true                      ||
           lhsField->getType   ().getClass() == FieldType::ParentPtrField   )
            continue;
        
        // skip attachments, if the option is set
        if(ignoreAttachments && lhsField->getName() == "attachments")
            continue;
        
        if(compareIdentity == true)
        {
            if(lhsField->equal(rhsField) == false)
                returnValue = false;
        }
        else
        {
            if(lhsField->isPointerField() == true)
            {
                returnValue = comparePointerFields(
                    lhsField, rhsField, ignoreAttachments, compareIdentity);
            }
            else
            {
                if(lhsField->equal(rhsField) == false)
                    returnValue = false;
            }
        }
    }
    
    return returnValue;
}

OSG_END_NAMESPACE
