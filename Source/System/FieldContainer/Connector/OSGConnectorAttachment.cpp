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

#include <boost/bind.hpp>

#include <OSGConfig.h>

#include "OSGConnectorAttachment.h"
#include "OSGAttachmentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGConnectorAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGConnectorAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ConnectorAttachment::initMethod(InitPhase ePhase)
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

ConnectorAttachment::ConnectorAttachment(void) :
     Inherited   (), 
    _vConnections()
{
}

ConnectorAttachment::ConnectorAttachment(const ConnectorAttachment &source) :
     Inherited   (source), 
    _vConnections(      )
{
}

ConnectorAttachment::~ConnectorAttachment(void)
{
    for(UInt32 i = 0; i < _vConnections.size(); ++i)
    {
        delete _vConnections[i];
    }
}

/*----------------------------- class specific ----------------------------*/

void ConnectorAttachment::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ConnectorAttachment::dump(      UInt32    ,
                               const BitVector ) const
{
    SLOG << "Dump ConnectorAttachment NI" << std::endl;
}

void ConnectorAttachment::addConnection (BasicFieldConnector *pConnector)
{
    if(pConnector != NULL)
    {
        _vConnections.push_back(pConnector);
    }
}

void ConnectorAttachment::processChanged(FieldContainer      *pObj, 
                                         BitVector            whichField)
{
    ConnectionStore::const_iterator cIt  = _vConnections.begin();
    ConnectionStore::const_iterator cEnd = _vConnections.end  ();

    while(cIt != cEnd)
    {
        if((*cIt)->match(whichField) == true)
        {
            (*cIt)->process();
        }

        ++cIt;
    }
}

void addConnector(AttachmentContainer *pContainer,
                  BasicFieldConnector *pConn     )
{
    if(pContainer == NULL)
    {
        FFATAL(("addConnector: no container?!?"));
        return;
    }

    if(pConn == NULL)
    {
        FFATAL(("addConnector: no connector?!?"));
        return;
    }

    ConnectorAttachmentUnrecPtr pCA = NULL;

    Attachment          *att = pContainer->findAttachment(
        ConnectorAttachment::getClassType().getGroupId());

    if(att == NULL)
    {
        pCA = ConnectorAttachment::create();

        pContainer->addChangedFunctor(
            boost::bind(&ConnectorAttachment::processChanged, 
                        pCA.get(), 
                        _1, 
                        _2),
            "");

        pContainer->addAttachment(pCA);
    }
    else
    {
        pCA = dynamic_cast<ConnectorAttachment *>(att);

        if(pCA == NULL)
        {
            FFATAL(("setName: Attachment is not castable to Conn?!?"));
            return;
        }
    }

    pCA->addConnection(pConn);
}

OSG_END_NAMESPACE
