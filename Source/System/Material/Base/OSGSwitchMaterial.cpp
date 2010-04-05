/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include "OSGSwitchMaterial.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSwitchMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGSwitchMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SwitchMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SwitchMaterial::SwitchMaterial(void) :
    Inherited()
{
}

SwitchMaterial::SwitchMaterial(const SwitchMaterial &source) :
    Inherited(source)
{
}

SwitchMaterial::~SwitchMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SwitchMaterial::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SwitchMaterial::addMaterial(Material *mat)
{
    if(mat == NULL)
        return;

    pushToMaterials(mat);
}

void SwitchMaterial::subMaterial(Material *mat)
{
    if(mat == NULL)
        return;

    removeObjFromMaterials(mat);
}

bool SwitchMaterial::hasMaterial(Material *mat) const
{
    UInt32 i;

    for(i = 0; i < _mfMaterials.size(); ++i)
    {
        if(_mfMaterials[i] == mat)
            return true;
    }

    return false;
}

Material *SwitchMaterial::getMaterial(UInt32 index) const
{
    if(index >= _mfMaterials.size())
    {
        FWARNING(("SwitchMaterial::getMaterial : index %u out of range\n", 
                  index));

        return NULL;
    }

    return _mfMaterials[index];
}

Material *SwitchMaterial::getCurrentMaterial(void) const
{
    UInt32 choice = getChoice();

    if(choice >= _mfMaterials.size())
    {
        FWARNING(("SwitchMaterial::getCurrentMaterial : current choice %u "
                  "out of range\n", choice));

        return NULL;
    }
    return _mfMaterials[choice];
}


/*! Check if the Material (i.e. any of its materials) is transparent..
 */

bool SwitchMaterial::isTransparent(void) const
{
    UInt32 choice = getChoice();

    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
        {
            SWARNING << "SwitchMaterial::isTransparent: choice index out "
                     << "of range!" 
                     << std::endl;
        }

        return false;
    }

    if(_mfMaterials[choice] != NULL)
        return _mfMaterials[choice]->isTransparent();

    return false;
}

/*! Check if the Material (i.e. any of its materials) is transparent..
*/
PrimeMaterial *SwitchMaterial::finalize(MaterialMapKey  oKey,
                                        Window         *pWin) 
{
    UInt32 choice = getChoice();

    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
        {
            SWARNING << "SwitchMaterial::finalize choice index out "
                     << "of range!" 
                     << std::endl;
        }

        return NULL;
    }

    if(_mfMaterials[choice] != NULL)
        return _mfMaterials[choice]->finalize(oKey, pWin);

    return NULL;
}

void SwitchMaterial::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SwitchMaterial NI" << std::endl;
}
