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

#include "OSGFCDPtrTestFCCustomAccess.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFCDPtrTestFCCustomAccessBase.cpp file.
// To modify it, please change the .fcd file (OSGFCDPtrTestFCCustomAccess.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FCDPtrTestFCCustomAccess::initMethod(InitPhase ePhase)
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

FCDPtrTestFCCustomAccess::FCDPtrTestFCCustomAccess(void) :
    Inherited()
{
}

FCDPtrTestFCCustomAccess::FCDPtrTestFCCustomAccess(const FCDPtrTestFCCustomAccess &source) :
    Inherited(source)
{
}

FCDPtrTestFCCustomAccess::~FCDPtrTestFCCustomAccess(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FCDPtrTestFCCustomAccess::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FCDPtrTestFCCustomAccess::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FCDPtrTestFCCustomAccess NI" << std::endl;
}

void FCDPtrTestFCCustomAccess::setFieldSFPub_ptr(FCDTestFC * const  value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPub_weakptr(FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPub_mpchildptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPub_spchildptr(
    FCDSParTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPub_ptr(FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPub_weakptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPub_mpchildptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPub_spchildptr(
    FCDSParTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPub_ptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPub_weakptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPub_mpchildptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPub_spchildptr(void)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPro_ptr(FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPro_weakptr(FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPro_mpchildptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPro_spchildptr(
    FCDSParTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPro_ptr(FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPro_weakptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPro_mpchildptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPro_spchildptr(
    FCDSParTestFC * const value)
{
}


void FCDPtrTestFCCustomAccess::clearFieldMFPro_ptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPro_weakptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPro_mpchildptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPro_spchildptr(void)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPri_ptr(FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPri_weakptr(FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPri_mpchildptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::setFieldSFPri_spchildptr(
    FCDSParTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPri_ptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPri_weakptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPri_mpchildptr(
    FCDTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::pushToFieldMFPri_spchildptr(
    FCDSParTestFC * const value)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPri_ptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPri_weakptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPri_mpchildptr(void)
{
}

void FCDPtrTestFCCustomAccess::clearFieldMFPri_spchildptr(void)
{
}


OSG_END_NAMESPACE
