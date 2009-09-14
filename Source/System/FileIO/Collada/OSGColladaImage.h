/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAIMAGE_H_
#define _OSGCOLLADAIMAGE_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaImage.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGColladaElement.h"

#include "OSGImage.h"

// forward declarations
class domImage;

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaImage : public ColladaElement
{
  public:
    typedef ColladaElement                          Inherited;
    typedef ColladaImage                            Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    static inline ObjTransitPtr create(domImage      *image,
                                       ColladaGlobal *global);
    
    virtual void read(void);

    inline Image *getImage(void);
    
  protected:
             ColladaImage(domImage *image, ColladaGlobal *global);
    virtual ~ColladaImage(void                                  );
    
    ImageUnrecPtr _image;
};

typedef ColladaImage::ObjRefPtr     ColladaImageRefPtr;
typedef ColladaImage::ObjTransitPtr ColladaImageTransitPtr;

OSG_END_NAMESPACE

#include "OSGColladaImage.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAIMAGE_H_
