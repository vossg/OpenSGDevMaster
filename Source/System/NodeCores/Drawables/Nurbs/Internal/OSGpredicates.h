/* GTS - Library for the manipulation of triangulated surfaces
 * Copyright (C) 1999 St�phane Popinet
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
/* Header file for robust predicates by Jonathan Richard Shewchuk */

#ifndef __OSG_PREDICATES_H__
#define __OSG_PREDICATES_H__

#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

//#ifdef __cplusplus
//extern "C" {
//#endif

OSG_DRAWABLE_DLLMAPPING
double orient2d            (double * pa,
                            double * pb,
                            double * pc);

OSG_DRAWABLE_DLLMAPPING
double orient3d            (double * pa,
                            double * pb,
                            double * pc,
                            double * pd);

OSG_DRAWABLE_DLLMAPPING
double incircle            (double * pa,
                            double * pb,
                            double * pc,
                            double * pd);

OSG_DRAWABLE_DLLMAPPING
double insphere            (double * pa,
                            double * pb,
                            double * pc,
                            double * pd,
                            double * pe);

OSG_DRAWABLE_DLLMAPPING
void exactinit             ();

//#ifdef __cplusplus
//}
//#endif
OSG_END_NAMESPACE

#endif /* __OSG_PREDICATES_H__ */
