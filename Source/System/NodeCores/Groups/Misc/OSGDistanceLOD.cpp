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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <OSGAction.h>
#include <OSGCamera.h>
#include <OSGRenderAction.h>

//just for debug
#include <iostream>
//just for debug

#include "OSGDistanceLOD.h"

OSG_USING_NAMESPACE

/*! \class osg::DistanceLOD

  This Node manages the different levels of detail available for a Geometry
  and decides which one should be rendered, according to the distance from the
  current camera. The details of the selection process are taken from VRML97
  standard. 

  The node chooses which child to render based on the range values in the Range
  multi-field and the current distance of the camera from the object.  
  The children should be ordered from the highest level of detail to the 
  lowest level of detail. The range values specify the distances at which to 
  switch between the different children.
  
  The center field is a translation offset in the local coordinate system that
  specified the center of the object for distance calculations.  In order to
  calculate which level to display, first the distance is calculate from the 
  viewpoint to the center point of the LOD node (which corresponding 
  transformations).  If the distance is less than the first range value, then 
  the first LOD is drawn. If it is between the first and the second values, 
  then the second LOD is drawn, and so on.
  
  \example Setting up a osg::DistanceLOD
  
  Here is an example of setting up an lod core with a center and a range.
  You would also need to add children for the 4 LODs.
  
  \code
  DistanceLOD lod = DistanceLOD::create();

  // this is supposed to be the center of the LOD model,
  // that is, this is the point the distance is measured from
  lod->setCenter(12,1,5);
  // now we add the distances when models will change
  lod->editMFRange()->push_back(6.0);
  lod->editMFRange()->push_back(12.0);
  lod->editMFRange()->push_back(24.0);    
  \endcode
  
  \endexample
 */

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void DistanceLOD::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void DistanceLOD::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump DistanceLOD NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DistanceLOD::DistanceLOD(void) :
    Inherited()
{
}

DistanceLOD::DistanceLOD(const DistanceLOD &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DistanceLOD::~DistanceLOD(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void DistanceLOD::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        typedef ActionBase::ResultE (DistanceLOD::*Callback)(Action *);

        Callback enter = &DistanceLOD::render<RenderAction>;

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(enter));
    }
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGDistanceLOD.cpp,v $";
    static Char8 cvsid_hpp[] = OSGDISTANCELOD_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGDISTANCELOD_INLINE_CVSID;
}

    

