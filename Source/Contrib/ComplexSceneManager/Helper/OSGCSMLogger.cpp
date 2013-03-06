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

#include "OSGCSMLogger.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMLoggerBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMLogger.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMLogger::initMethod(InitPhase ePhase)
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

CSMLogger::CSMLogger(void) :
    Inherited()
{
}

CSMLogger::CSMLogger(const CSMLogger &source) :
    Inherited(source)
{
}

CSMLogger::~CSMLogger(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CSMLogger::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & (ContainersFieldMask | FieldsFieldMask)))
    {
    }
}

void CSMLogger::dump(      UInt32    ,
                     const BitVector ) const
{
    SLOG << "Dump CSMLogger NI" << std::endl;
}

void CSMLogger::postOSGLoading(FileContextAttachment * const pContext)
{
        MFContainersType::const_iterator cIt  = _mfContainers.begin();
        MFContainersType::const_iterator cEnd = _mfContainers.end  ();

        MFString        ::const_iterator fIt  = _mfFields.begin    ();
        MFString        ::const_iterator fEnd = _mfFields.end      ();

        for(; cIt != cEnd && fIt != fEnd; ++cIt, ++fIt)
        {
            fprintf(stderr, "log : %p (%s).%s\n",
                    *cIt,
                    (*cIt) != NULL ? (*cIt)->getType().getCName() : "---",
                    fIt->c_str()                                         );

            const FieldDescriptionBase *pDesc = 
                (*cIt)->getFieldDescription(fIt->c_str());

            if(pDesc != NULL)
            {
                ChangedFunctor logCB = 
                    boost::bind(&CSMLogger::doLog, 
                                this,
                                _1, 
                                _2, 
                                _3,
                                pDesc->getFieldId(),
                                pDesc->getFieldMask());

                (*cIt)->addChangedFunctor(logCB, "");
            }
        }
}

void CSMLogger::doLog(FieldContainer *pContainer, 
                      BitVector       bvFlags   ,
                      UInt32          origin    ,
                      UInt32          uiRefFieldId,
                      BitVector       uiRefFieldMask)
{
    if(0x0000 != (bvFlags & uiRefFieldMask) && _sfEnabled.getValue() == true)
    {
        GetFieldHandlePtr pFH = pContainer->getField(uiRefFieldId);

        if(pFH && pFH->isValid() == true)
        {
            static CErrOutStream cerrStream;

            const FieldDescriptionBase *pDesc = 
                pContainer->getFieldDescription(uiRefFieldId);

            AttachmentContainer *pAtt = 
                dynamic_cast<AttachmentContainer *>(pContainer);

            if(pAtt != NULL)
            {
                const Char8 *szName = getName(pAtt);

                if(szName != NULL)
                {
                    cerrStream << "[" << szName << "]:";
                }
            }

            cerrStream << pContainer->getType().getName() 
                       << "."
                       << pDesc->getName()
                       << " : ";
            
            pFH->pushValueToStream(cerrStream);

            cerrStream << std::endl;
        }
    }
}

OSG_END_NAMESPACE
