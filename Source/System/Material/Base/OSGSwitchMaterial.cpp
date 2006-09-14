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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGSwitchMaterial.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SwitchMaterial

*/

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
    // ACHTUNG _pState wird der State vom jeweiligen aktiven Material 
    // zugewiesen. wenn nun die Materialien zerstoert werden dann wird im 
    // Material::~Material ein subRefCP(_pState) aufgerufen. Dieser 
    // subRefCP wuerde dann nochmal mit dem gleichen ungueltigen pointer 
    // fuer das SwitchMaterial aufgerufen werden und
    // das kracht natürlich, deswegen wird er jetzt einfach auf NullFC gesetzt!

    _pState = NullFC;
}

/*----------------------------- class specific ----------------------------*/

void SwitchMaterial::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SwitchMaterial::addMaterial(MaterialPtr mat)
{
    if(mat == NullFC)
        return;

    pushToMaterials(mat);
}

void SwitchMaterial::subMaterial(MaterialPtr mat)
{
    if(mat == NullFC)
        return;

    removeFromMaterials(mat);
}

bool SwitchMaterial::hasMaterial(MaterialPtr mat)
{
    UInt32 i;

    for(i = 0; i < _mfMaterials.size(); ++i)
    {
        if(_mfMaterials[i] == mat)
            return true;
    }

    return false;
}

MaterialPtr SwitchMaterial::getMaterial(UInt32 index)
{
    if(index >= _mfMaterials.size())
    {
        FWARNING(("SwitchMaterial::getMaterial : index %u out of range\n", 
                  index));

        return NullFC;
    }

    return _mfMaterials[index];
}

MaterialPtr SwitchMaterial::getCurrentMaterial(void)
{
    UInt32 choice = getChoice();

    if(choice >= _mfMaterials.size())
    {
        FWARNING(("SwitchMaterial::getCurrentMaterial : current choice %u "
                  "out of range\n", choice));

        return NullFC;
    }
    return _mfMaterials[choice];
}

#if OLD
/*! Draw the geometry with this material.
*/

void SwitchMaterial::draw(Geometry *OSG_CHECK_ARG(geo), DrawActionBase *OSG_CHECK_ARG(action))
{
}

/*! Draw the function behind the functor with this material. The functored
    function should be very careful changing OpenGL state, better just use
    glBegin(), glEnd() and the standard stuff in between.
*/

void SwitchMaterial::draw(DrawFunctor &OSG_CHECK_ARG(func), DrawActionBase *OSG_CHECK_ARG(action))
{
}

/*! Create a OSG::State that represents this Material and return it.
*/

StatePtr SwitchMaterial::makeState(void)
{
    UInt32 choice = getChoice();
    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
            SWARNING << "SwitchMaterial::makeState: choice index (" << choice << ") out of range!" << std::endl;
        if(getSortKey() != OSG::getDefaultMaterial()->getSortKey())
        {
            SwitchMaterialPtr tmpPtr(*this);
            beginEditCP(tmpPtr, SwitchMaterial::SortKeyFieldMask);
                setSortKey(OSG::getDefaultMaterial()->getSortKey());
            endEditCP(tmpPtr, SwitchMaterial::SortKeyFieldMask);
        }
        return OSG::getDefaultMaterial()->makeState();
    }

    if(_mfMaterials[choice] != NullFC)
    {
        if(getSortKey() != _mfMaterials[choice]->getSortKey())
        {
            SwitchMaterialPtr tmpPtr(*this);
            beginEditCP(tmpPtr, SwitchMaterial::SortKeyFieldMask);
                setSortKey(_mfMaterials[choice]->getSortKey());
            endEditCP(tmpPtr, SwitchMaterial::SortKeyFieldMask);
        }
        return _mfMaterials[choice]->makeState();
    }

    if(getSortKey() != OSG::getDefaultMaterial()->getSortKey())
    {
        SwitchMaterialPtr tmpPtr(*this);
        beginEditCP(tmpPtr, SwitchMaterial::SortKeyFieldMask);
            setSortKey(OSG::getDefaultMaterial()->getSortKey());
        endEditCP(tmpPtr, SwitchMaterial::SortKeyFieldMask);
    }
    return OSG::getDefaultMaterial()->makeState();
}
#endif

/*! Rebuild the internal State. Just collects the chunks in the State.
*/

void SwitchMaterial::rebuildState(void)
{
    UInt32 choice = getChoice();

    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
        {
            SWARNING << "SwitchMaterial::rebuildState: choice index (" 
                     << choice << ") out of range!" 
                     << std::endl;
        }

        if(getSortKey() != OSG::getDefaultMaterial()->getSortKey())
        {
            setSortKey(OSG::getDefaultMaterial()->getSortKey());
        }

        OSG::getDefaultMaterial()->rebuildState();

        //_pState = OSG::getDefaultMaterial()->getState();
        return;
    }

    if(_mfMaterials[choice] != NullFC)
    {
        if(getSortKey() != _mfMaterials[choice]->getSortKey())
        {
            setSortKey(_mfMaterials[choice]->getSortKey());
        }

        _mfMaterials[choice]->rebuildState();
        //_pState = _mfMaterials[choice]->getState();
    }
    else
    {
        if(getSortKey() != OSG::getDefaultMaterial()->getSortKey())
        {
            setSortKey(OSG::getDefaultMaterial()->getSortKey());
        }

        OSG::getDefaultMaterial()->rebuildState();
        //_pState = OSG::getDefaultMaterial()->getState();
    }
}

StatePtr SwitchMaterial::getState(UInt32 index)
{
    UInt32 choice = getChoice();

    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
        {
            SWARNING << "SwitchMaterial::getState: choice index out of range!"
                     << std::endl;
        }

        return NullFC;
    }

    if(_mfMaterials[choice] != NullFC)
    {
        if(_mfMaterials[choice]->getState(index) == NullFC)
            rebuildState();

        return _mfMaterials[choice]->getState(index);
    }

    return NullFC;
}


UInt32 SwitchMaterial::getNPasses(void) const
{
    UInt32 choice = getChoice();

    if(choice >= _mfMaterials.size())
    {
        if(!_mfMaterials.empty())
        {
            SWARNING << "SwitchMaterial::getNPasses: choice index out of "
                     << "range!" 
                     << std::endl;
        }

        return 1;
    }

    if(_mfMaterials[choice] != NullFC)
        return _mfMaterials[choice]->getNPasses();

    return 1;
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

    if(_mfMaterials[choice] != NullFC)
        return _mfMaterials[choice]->isTransparent();

    return false;
}

void SwitchMaterial::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SwitchMaterial NI" << std::endl;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGSWITCHMATERIALBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSWITCHMATERIALBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSWITCHMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

