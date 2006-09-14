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

#include "OSGMultiPassMaterial.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MultiPassMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiPassMaterial::initMethod(InitPhase ePhase)
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

MultiPassMaterial::MultiPassMaterial(void) :
    Inherited()
{
}

MultiPassMaterial::MultiPassMaterial(const MultiPassMaterial &source) :
    Inherited(source)
{
}

MultiPassMaterial::~MultiPassMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiPassMaterial::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MultiPassMaterial::addMaterial(MaterialPtr pMat)
{
    if(pMat == NullFC)
        return;

    _mfMaterials.push_back(pMat);

    addRef(pMat);
}

void MultiPassMaterial::subMaterial(MaterialPtr pMat)
{
    if(pMat == NullFC)
        return;

    UInt32 i;
    
    for(i = 0; i < _mfMaterials.size(); ++i)
    {
        if(_mfMaterials[i] == pMat)
        {
            subRef(pMat);

            _mfMaterials.erase(_mfMaterials.begin() + i);

            return;
        }
    }

    SWARNING << "MultiPassMaterial::subMaterial(" 
             << this 
             << ") has no material "
             << pMat << std::endl;
}

bool MultiPassMaterial::hasMaterial(MaterialPtr pMat)
{
    UInt32 i;

    for(i = 0; i < _mfMaterials.size(); ++i)
    {
        if(_mfMaterials[i] == pMat)
            return true;
    }

    return false;
}


#ifdef OLD
/*! Draw the geometry with this material.
*/

void MultiPassMaterial::draw(MaterialDrawable* geo, DrawActionBase * action)
{
}

/*! Draw the function behind the functor with this material. The functored
    function should be very careful changing OpenGL state, better just use
    glBegin(), glEnd() and the standard stuff in between.
*/

void MultiPassMaterial::draw(DrawFunctor& func, DrawActionBase * action)
{
}

/*! Create a OSG::State that represents this Material and return it.
*/

StatePtr MultiPassMaterial::makeState(void)
{
    return NullFC;
}
#endif

/*! Rebuild the internal State. Just collects the chunks in the State.
*/

void MultiPassMaterial::rebuildState(void)
{
    for(UInt32 i = 0; i < _mfMaterials.size(); ++i)
    {
        if(_mfMaterials[i] != NullFC)
            _mfMaterials[i]->rebuildState();
    }
}

StatePtr MultiPassMaterial::getState(UInt32 index)
{
    if(index >= _mfMaterials.size())
    {
        SWARNING << "MultiPassMaterial::getState: index out of range!" 
                 << std::endl;

        return NullFC;
    }

    if(_mfMaterials[index] != NullFC)
        return _mfMaterials[index]->getState();

    return NullFC;
}

UInt32 MultiPassMaterial::getNPasses(void)
{
    return _mfMaterials.size();
}

/*! Check if the Material (i.e. any of its materials) is transparent..
*/

bool MultiPassMaterial::isTransparent(void) const
{
    MFMaterialPtr::const_iterator it      = _mfMaterials.begin();
    MFMaterialPtr::const_iterator matsEnd = _mfMaterials.end();

#if 0
    for(; it != matsEnd; ++it)
    {
        if((*it) == NullFC)
            return false;

        if(!(*it)->isTransparent())
            return false;
    }

    return true;
#endif

    // ok just check the first (base) material.
    if(  it                   != matsEnd && 
       (*it)                  != NullFC  && 
       (*it)->isTransparent() == true)
    {
        return true;
    }

    return false;

}

void MultiPassMaterial::dump(      UInt32    , 
                             const BitVector ) const
{
    SLOG << "Dump MultiPassMaterial NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGMULTIPASSMATERIALBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMULTIPASSMATERIALBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMULTIPASSMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

