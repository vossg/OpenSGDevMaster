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

#include "OSGGLEXT.h"

#include "OSGLightModelChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGLightModelChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGLightModelChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
StateChunkClass LightModelChunk::_class("LightModel");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LightModelChunk::initMethod(InitPhase ePhase)
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

LightModelChunk::LightModelChunk(void) :
    Inherited()
{
}

LightModelChunk::LightModelChunk(const LightModelChunk &source) :
    Inherited(source)
{
}

LightModelChunk::~LightModelChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

const StateChunkClass *LightModelChunk::getClass(void) const
{
    return &_class;
}

void LightModelChunk::changed(ConstFieldMaskArg whichField,
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LightModelChunk::dump(      UInt32    uiIndent,
                           const BitVector bvFlags  ) const
{
    Inherited::dump(uiIndent, bvFlags);

    if((bvFlags & AmbientFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "ambient " << _sfAmbient.getValue() << "\n";
    }

    if((bvFlags & ColorControlFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "colorControl "
             << GLDefineMapper::the()->toString(_sfColorControl.getValue())
             << "\n";
    }

    if((bvFlags & LocalViewerFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "localViewer " << _sfLocalViewer.getValue() << "\n";
    }
}

/*------------------------------ State ------------------------------------*/

void LightModelChunk::activate(DrawEnv *pEnv, UInt32)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, 
                   _sfAmbient.getValue().getValuesRGBA());

    if(_sfColorControl.getValue() != GL_SINGLE_COLOR)
    {
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, _sfColorControl.getValue());
    }

    if(_sfLocalViewer.getValue())
    {
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    }
    else
    {
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    }
#endif
}

void LightModelChunk::changeFrom(DrawEnv    *pEnv, 
                                 StateChunk *old_chunk, 
                                 UInt32               )
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    LightModelChunk *old = dynamic_cast<LightModelChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "LightModelChunk::changeFrom: caught "
                   "non-LightModelChunk!\n"));
        return;
    }

    // LightModelChunk didn't change so do nothing.
    if(old == this)
        return;

    if(old->_sfAmbient.getValue() != _sfAmbient.getValue())
    {
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, 
                      _sfAmbient.getValue().getValuesRGBA());
    }

    if(_sfColorControl.getValue() != old->_sfColorControl.getValue())
    {
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, _sfColorControl.getValue());
    }

    if(_sfLocalViewer.getValue() != old->_sfLocalViewer.getValue())
    {
        if(_sfLocalViewer.getValue())
        {
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
        }
        else
        {
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
        }
    }
#endif
}

void LightModelChunk::deactivate(DrawEnv *pEnv, UInt32 )
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    if(_sfColorControl.getValue() != GL_SINGLE_COLOR)
    {
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
    }

    if(_sfLocalViewer.getValue())
    {
       glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    }
#endif
}

/*-------------------------- Comparison -----------------------------------*/

Real32 LightModelChunk::switchCost(StateChunk *)
{
    return 0;
}

bool LightModelChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool LightModelChunk::operator == (const StateChunk &other) const
{
    LightModelChunk const *tother = dynamic_cast<LightModelChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getAmbient     () != tother->getAmbient     () ||
       getColorControl() != tother->getColorControl() ||
       getLocalViewer () != tother->getLocalViewer ()   )
        return false;

    return true;
}

bool LightModelChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}
