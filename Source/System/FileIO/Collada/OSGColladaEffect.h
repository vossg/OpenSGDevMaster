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

#ifndef _OSGCOLLADAEFFECT_H_
#define _OSGCOLLADAEFFECT_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGMaterial.h"

#include <dom/domImage.h>
#include <dom/domCommon_color_or_texture_type.h>

// forward decl
class domProfile_COMMON;
class domProfile_GLSL;
class domProfile_CG;
class domEffect;
class domInstance_effect;


OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaEffect : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaEffect              Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaEffect);

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

    virtual void      read          (void                            );
    virtual Material *createInstance(ColladaInstanceElement *instElem);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaEffect(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaEffect(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Profile Handlers                                             */
    /*! \{                                                                 */

    virtual void      readProfileCommon(domProfile_COMMON *prof);
    virtual void      readProfileGLSL  (domProfile_GLSL   *prof);
    virtual void      readProfileCG    (domProfile_CG     *prof);

    virtual Material *createInstanceProfileCommon(
        domProfile_COMMON  *prof,       domEffect *effect,
        domInstance_effect *instEffect                    );
    virtual Material *createInstanceProfileGLSL(
        domProfile_GLSL    *prof,       domEffect *effect,
        domInstance_effect *instEffect                    );
    virtual Material *createInstanceProfileCG(
        domProfile_CG      *prof,       domEffect *effect,
        domInstance_effect *instEffect                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/



    void readImageArray(const domImage_Array &images);
    void fillTexColor  (
        domCommon_color_or_texture_type                *colTex,
        domCommon_color_or_texture_type::domColorRef   &colOut,
        domCommon_color_or_texture_type::domTextureRef &texOut );

    static ColladaElementRegistrationHelper _regHelper;
};

OSG_GEN_MEMOBJPTR(ColladaEffect);

OSG_END_NAMESPACE

// #include "OSGColladaEffect.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAEFFECT_H_
