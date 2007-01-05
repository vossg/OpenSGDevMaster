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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGRenderAction.h>
#include "OSGLightEngine.h"
#include "OSGLight.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGLightBase.cpp file.
// To modify it, please change the .fcd file (OSGLight.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

void Light::setAmbient(Real rRed, 
                       Real rGreen, 
                       Real rBlue, 
                       Real rAlpha)
{
    editSField(AmbientFieldMask);

    _sfAmbient.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void Light::setDiffuse(Real rRed, 
                       Real rGreen, 
                       Real rBlue, 
                       Real rAlpha)
{
    editSField(DiffuseFieldMask);

    _sfDiffuse.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void Light::setSpecular(Real rRed, 
                        Real rGreen, 
                        Real rBlue, 
                        Real rAlpha)
{
    editSField(SpecularFieldMask);

    _sfSpecular.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

/*-------------------------------------------------------------------------*/
/*                             Chunk                                       */

LightChunkPtr Light::getChunk(void)
{
    return _pChunk;
}

void Light::makeChunk(void)
{
    if(_pChunk == NullFC)
    {
        _pChunk = LightChunk::create();
    }

    _pChunk->setBeacon  (getBeacon  ());
    _pChunk->setAmbient (getAmbient ());
    _pChunk->setDiffuse (getDiffuse ());
    _pChunk->setSpecular(getSpecular());
}

/*-------------------------------------------------------------------------*/
/*                             Sync                                     */

void Light::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    makeChunk();
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void Light::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Light::Light(void) :
     Inherited  (      ),
    _pChunk     (NullFC),
    _pEngineData(NULL  )
{
}

Light::Light(const Light &source) :
     Inherited  (source             ),
    _pChunk     (source._pChunk     ),
    _pEngineData(NULL               )
{
    setLightEngineData(source._pEngineData);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Light::~Light(void)
{
    subRef(_pChunk     );
    subRef(_pEngineData);
}

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

Action::ResultE Light::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->dropLight(this);

    return Action::Continue;
}

Action::ResultE Light::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->undropLight(this);

    return Action::Continue;
}

void Light::setLightEngineData(LightEngineData *pData)
{
    addRef( pData      );
    subRef(_pEngineData);

    _pEngineData = pData;
    
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

//! initialize the static features of the class, e.g. action callbacks

void Light::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGLIGHT_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGLIGHT_INLINE_CVSID;
}

