/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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
#ifndef _OSG_BSPLINETRIMMEDSURFACE_H_
#define _OSG_BSPLINETRIMMEDSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>


#include "OSGdctptypes.h"
#include "OSGBSplineTensorSurface.h"
#include "OSGBSplineCurve2D.h"
#include <fstream>
#include <string>
#include <iomanip>

OSG_BEGIN_NAMESPACE

typedef std::vector<BSplineCurve2D> bscvector;
typedef std::vector<bscvector>      trimmingloop;


class OSG_DRAWABLE_DLLMAPPING BSplineTrimmedSurface
{

// FIXME: proper support for getting/setting stuph
  public:
    BSplineTrimmedSurface()
    {
    }
    ~BSplineTrimmedSurface() {}

    // I/O support - FIXME: read( char *fname ) outta be supported , etc
    int  read(std::istream &infile);
    int  write(std::ostream &outfile);
    void normalize(void);

    BSplineTensorSurface& getSurface(void)
    {
        return surf;
    }
    trimmingloop& getTrimmingLoops(void)
    {
        return trimming;
    }
    int setSurface(BSplineTensorSurface &ts)
    {
        surf = ts; return 0;
    }
    int setTrimmingLoops(trimmingloop &t)
    {
        trimming = t; return 0;
    }

    //! flips the surface
    void flip(void);

  protected:
// file format constants
    static const char ff_const_1[];
    static const char ff_const_2[];
    static const char ff_const_3[];

    BSplineTensorSurface surf; // the surface itself
    trimmingloop         trimming; // the trimming loops. each bscvector contains one trimming loop.

};

OSG_END_NAMESPACE

#endif /* _OSG_BSPLINETRIMMEDSURFACE_H_ */
