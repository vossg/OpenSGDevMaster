/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"
#include "OSGFieldConnectorFactory.h"
#include "OSGFieldContainer.h"

#include "OSGVecSFields.h"

OSG_BEGIN_NAMESPACE

template <>
void SFieldConnector<SFVec3f, SFPnt3f>::process(void)
{
    _pDst->editSField(_bDstMask);

    _pDstField->setValue(_pSrcField->getValue().addToZero());
}

template <>
void SFieldConnector<SFPnt3f, SFVec3f>::process(void)
{
    _pDst->editSField(_bDstMask);

    _pDstField->setValue(_pSrcField->getValue().subZero());
}

OSG_END_NAMESPACE

namespace 
{
    bool registerConversionConnectors(void)
    {
        fprintf(stderr, "registerConversionConnectors\n");

        OSG::FieldConnectorFactory::the()->registerConnector(
            OSG::SFVec3f::getClassType(),
            OSG::SFPnt3f::getClassType(),

            new OSG::SFieldConnector<OSG::SFVec3f, OSG::SFPnt3f>(NULL, 0, 
                                                                 NULL, 0),
            new OSG::SFieldConnector<OSG::SFPnt3f, OSG::SFVec3f>(NULL, 0, 
                                                                 NULL, 0));

        return true;
    }

    bool registerConversionConnectorsInit(void)
    {
        OSG::addPostFactoryInitFunction(registerConversionConnectors);

        return true;
    }

    OSG::StaticInitFuncWrapper initConvConns(registerConversionConnectorsInit);
}
