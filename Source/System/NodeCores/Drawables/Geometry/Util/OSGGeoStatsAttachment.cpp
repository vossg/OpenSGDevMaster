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

#include <OSGConfig.h>

#include "OSGContainerPtrFuncs.h"
#include "OSGGeoStatsAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeoStatsAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoStatsAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoStatsAttachment::initMethod(InitPhase ePhase)
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

GeoStatsAttachment::GeoStatsAttachment(void) :
    Inherited()
{
}

GeoStatsAttachment::GeoStatsAttachment(const GeoStatsAttachment &source) :
    Inherited(source)
{
}

GeoStatsAttachment::~GeoStatsAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoStatsAttachment::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeoStatsAttachment::dump(      UInt32    ,
                              const BitVector ) const
{
    SLOG << "Dump GeoStatsAttachment NI" << std::endl;
}



void GeoStatsAttachment::calc(GeometryPtrArg geo)
{
    if(geo == NullFC)
    {
        FINFO(("GeoStatsAttachment::calc: No geometry given.\n"));
        return;
    }

}


#if 0
/*! Access the GeoStatsAttachemnt in \a arg, if it has one. Return NullFC
otherwise.
*/
GeoStatsAttachmentPtr GeoStatsAttachment::get(AttachmentContainer *arg)
{
    return dynamic_cast<GeoStatsAttachmentPtr>(
            arg->findAttachment(GeoStatsAttachment::getClassType()));

}
#endif

/*------------------------------------------------------------------------*/
/*                              Updates                                   */






/*------------------------------------------------------------------------*/
/*                             Operators                                  */

OSG_BEGIN_NAMESPACE

#if 0
void operator +=(GeoStatsAttachmentPtr op, GeoStatsAttachmentPtr arg)
{
    (*op) += arg;
}

void operator -=(GeoStatsAttachmentPtr op, GeoStatsAttachmentPtr arg)
{
    (*op) -= arg;
}
#endif

OSG_END_NAMESPACE
