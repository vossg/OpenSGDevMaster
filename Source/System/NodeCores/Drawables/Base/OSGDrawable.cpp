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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGDrawable.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGDrawableBase.cpp file.
// To modify it, please change the .fcd file (OSGDrawable.fcd) and
// regenerate the base file.

/*----------------------------- class variables ---------------------------*/

StatElemDesc<StatIntElem    > Drawable::statNTriangles(
    "NTriangles",
    "number of rendered triangles");

StatElemDesc<StatIntElem    > Drawable::statNLines(
    "NLines",
    "number of rendered lines");

StatElemDesc<StatIntElem    > Drawable::statNPoints(
    "NPoints",
    "number of rendered points");

StatElemDesc<StatIntElem    > Drawable::statNVertices(
    "NVertices",
    "number of transformed vertices");

StatElemDesc<StatIntElem    > Drawable::statNPrimitives(
    "NPrimitives",
    "number of rendered primitive groups");

StatElemDesc<StatIntOnceElem> Drawable::statNGeoBytes(
    "NGeoBytes",
    "memory usages of geometry on the gfx card");

StatElemDesc<StatIntElem    > Drawable::statNDrawFunctors(
    "NDrawFunctors",
    "number of draw functors dropped");

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
Drawable::Drawable(void) :
    Inherited()
{
}

//! Copy Constructor
Drawable::Drawable(const Drawable &source) :
    Inherited(source)
{
}

//! Destructor
Drawable::~Drawable(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void Drawable::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes
void Drawable::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes
void Drawable::dump(      UInt32    , 
                    const BitVector ) const
{
    SLOG << "Dump Drawable NI" << std::endl;
}

