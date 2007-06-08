/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGSHLFUNCTIONS_H_
#define _OSGSHLFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSHLChunk.h"


OSG_BEGIN_NAMESPACE

OSG_STATE_DLLMAPPING
SHLChunkPtr generate1DConvolutionFilterFP(Real32 fBlurWidth,
                                          bool   vertical, 
                                          bool   tex2D, 
                                          Int32  imgWidth, 
                                          Int32  imgHeight);

OSG_STATE_DLLMAPPING
SHLChunkPtr generate2DShrinkHalfFilterFP(UInt32 uiTexCoord = 0);

OSG_END_NAMESPACE

#endif /* _OSGSHLFUNCTIONS_H_ */
