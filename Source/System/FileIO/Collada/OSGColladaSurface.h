/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADASURFACE_H_
#define _OSGCOLLADASURFACE_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaElement.h"
#include "OSGColladaElementFactoryHelper.h"

#include "OSGImage.h"

// forward decl
class domFx_surface_common;

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaSurface : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaElement  Inherited;
    typedef ColladaSurface  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaSurface);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    Image *getImage(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaSurface(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaSurface(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    virtual void readUntyped(domFx_surface_common *surface);
    virtual void read1D     (domFx_surface_common *surface);
    virtual void read2D     (domFx_surface_common *surface);
    virtual void read3D     (domFx_surface_common *surface);
    virtual void readRect   (domFx_surface_common *surface);
    virtual void readCube   (domFx_surface_common *surface);
    virtual void readDepth  (domFx_surface_common *surface);

    static ColladaElementRegistrationHelper _regHelper;

    ImageUnrecPtr _image;
};

OSG_GEN_MEMOBJPTR(ColladaSurface);

OSG_END_NAMESPACE

// #include "OSGColladaSurface.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADASURFACE_H_
