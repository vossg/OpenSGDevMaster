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

#ifndef _OSGCOLLADAANIMATIONCLIP_H_
#define _OSGCOLLADAANIMATIONCLIP_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaInstInfo.h"

#include "OSGAnimKeyFrameTemplate.h"

// Existing exporters for Maya are not producing useable <animation_clip> tags
// when exporting baked transforms (see code.google.com/p/opencollada issue 45
// for more details).
// A workaround that can help in certain situations is to instantiate simply
// all animations from a clip and assume they all belong to that clip.

// #define OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK 1

OSG_BEGIN_NAMESPACE


class OSG_FILEIO_DLLMAPPING ColladaAnimationClip : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaElement        Inherited;
    typedef ColladaAnimationClip  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaAnimationClip);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr create(daeElement    *elem, 
                                           ColladaGlobal *global);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read(ColladaElement *colElemParent);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaAnimationClip(daeElement    *elem,
                                  ColladaGlobal *global);
    virtual ~ColladaAnimationClip(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;
};

OSG_GEN_MEMOBJPTR(ColladaAnimationClip);

OSG_END_NAMESPACE

// #include "OSGColladaAnimationClip.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAANIMATIONCLIP_H_
