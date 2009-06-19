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

#define OSG_COMPILECUBESLIBLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGDrawableStatsAttachment.h>
#include <OpenSG/OSGRenderAction.h>

#include "OSGCubes.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCubesBase.cpp file.
// To modify it, please change the .fcd file (OSGCubes.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Cubes::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionEnterHandler));
        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionLeaveHandler));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Cubes::Cubes(void) :
    Inherited()
{
}

Cubes::Cubes(const Cubes &source) :
    Inherited(source)
{
}

Cubes::~Cubes(void)
{
}

/*----------------------------- class specific ----------------------------*/

/*! Draw the cubes. We just use OpenGL immediate mode for simplicity.
 */
Action::ResultE Cubes::drawPrimitives(DrawEnv *drawEnv)
{
    Action::ResultE res = Action::Continue;

    if(getMFPosition()->size() != getMFLength()->size() ||
       getMFPosition()->size() != getMFColor ()->size()   )
    {
        SWARNING << "Cubes::drawPrimitives: Inconsistent attributes!"
                 << std::endl;
        return res;
    }

    const MFPositionType *pos = getMFPosition();
    const MFLengthType   *len = getMFLength  ();
    const MFColorType    *col = getMFColor   ();

    glBegin(GL_QUADS);

    for(UInt32 i = 0; i < pos->size(); ++i)
    {
        glColor3fv((*col)[i].getValues());

        const Pnt3f &p = (*pos)[i];
        Real32       l = (*len)[i] / 2.f;

        glNormal3f(0.f, 0.f, -1.f);
        glVertex3f(p[0] - l, p[1] - l, p[2] - l);
        glVertex3f(p[0] + l, p[1] - l, p[2] - l);
        glVertex3f(p[0] + l, p[1] + l, p[2] - l);
        glVertex3f(p[0] - l, p[1] + l, p[2] - l);

        glNormal3f(0.f, 0.f, 1.f);
        glVertex3f(p[0] - l, p[1] - l, p[2] + l);
        glVertex3f(p[0] + l, p[1] - l, p[2] + l);
        glVertex3f(p[0] + l, p[1] + l, p[2] + l);
        glVertex3f(p[0] - l, p[1] + l, p[2] + l);

        glNormal3f(-1.f, 0.f, 0.f);
        glVertex3f(p[0] - l, p[1] - l, p[2] - l);
        glVertex3f(p[0] - l, p[1] - l, p[2] + l);
        glVertex3f(p[0] - l, p[1] + l, p[2] + l);
        glVertex3f(p[0] - l, p[1] + l, p[2] - l);

        glNormal3f(1.f, 0.f, 0.f);
        glVertex3f(p[0] + l, p[1] - l, p[2] + l);
        glVertex3f(p[0] + l, p[1] - l, p[2] - l);
        glVertex3f(p[0] + l, p[1] + l, p[2] - l);
        glVertex3f(p[0] + l, p[1] + l, p[2] + l);

        glNormal3f(0.f, 1.f, 0.f);
        glVertex3f(p[0] - l, p[1] + l, p[2] + l);
        glVertex3f(p[0] + l, p[1] + l, p[2] + l);
        glVertex3f(p[0] + l, p[1] + l, p[2] - l);
        glVertex3f(p[0] - l, p[1] + l, p[2] - l);

        glNormal3f(0.f, -1.f, 0.f);
        glVertex3f(p[0] - l, p[1] - l, p[2] - l);
        glVertex3f(p[0] + l, p[1] - l, p[2] - l);
        glVertex3f(p[0] + l, p[1] - l, p[2] + l);
        glVertex3f(p[0] - l, p[1] - l, p[2] + l);
    }

    glEnd();

    return res;
}

void Cubes::fill(DrawableStatsAttachment *stats)
{
    if(getMFPosition()->size() != getMFLength()->size() ||
       getMFPosition()->size() != getMFColor ()->size()   )
    {
        SWARNING << "Cubes::fill: Inconsistent attributes!"
                 << std::endl;
        return;
    }

    stats->setVertices (getMFPosition()->size() * 24);
    stats->setTriangles(getMFPosition()->size() * 12);
    stats->setValid(true);
}

/*! Extend the given volume to contain all cubes.
 */
void Cubes::adjustVolume(Volume &volume)
{
    volume.setValid();

    const MFPositionType *pos = getMFPosition();
    const MFLengthType   *len = getMFLength  ();

    // iterate over all cubes
    for(UInt32 i = 0; i < pos->size(); ++i)
    {
        const Pnt3f &p = (*pos)[i];
        Real32       l = (*len)[i] / 2.f;

        // adjust volume to contain all corners of the cube
        for(Int16 z = -1; z <= 1; z += 2)
        {
            for(Int16 y = -1; y <= 1; y += 2)
            {
                for(Int16 x = -1; x <= 1; x += 2)
                {
                    volume.extendBy(Pnt3f(p[0] + x * l,
                                          p[1] + y * l,
                                          p[2] + z * l ));
                }
            }
        }
    }
}


void Cubes::changed(ConstFieldMaskArg whichField,
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Cubes::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Cubes NI" << std::endl;
}

OSG_END_NAMESPACE
