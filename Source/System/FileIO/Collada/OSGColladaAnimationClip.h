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

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceAnimation;
class ColladaAnimation;


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
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    void                  setCurrTemplate(AnimKeyFrameTemplate *animTmpl);
    AnimKeyFrameTemplate *getCurrTemplate(void                          ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    class ColladaAnimationInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        typedef ColladaInstInfo          Inherited;
        typedef ColladaAnimationInstInfo Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaAnimationInstInfo);

        static ColladaInstInfoTransitPtr
            create(ColladaAnimationClip     *colInstParent,
                   ColladaInstanceAnimation *colInst,
                   ColladaAnimation         *colAnim,
                   AnimKeyFrameTemplate     *animTmpl      );

        virtual void      process(void);

        ColladaAnimation     *getAnim    (void) const;
        AnimKeyFrameTemplate *getTemplate(void) const;

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 ColladaAnimationInstInfo(
                     ColladaAnimationClip     *colInstParent,
                     ColladaInstanceAnimation *colInst,
                     ColladaAnimation         *colAnim,
                     AnimKeyFrameTemplate     *animTmpl      );
        virtual ~ColladaAnimationInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        ColladaAnimation             *_colAnim;
        AnimKeyFrameTemplateUnrecPtr  _animTmpl;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaAnimationClip(daeElement    *elem,
                                  ColladaGlobal *global);
    virtual ~ColladaAnimationClip(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    void handleInstanceAnimation(ColladaInstInfo *instInfo);

    static ColladaElementRegistrationHelper _regHelper;

    AnimKeyFrameTemplateUnrecPtr _currAnimTmpl;
};

OSG_GEN_MEMOBJPTR(ColladaAnimationClip);

OSG_END_NAMESPACE

// #include "OSGColladaAnimationClip.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAANIMATIONCLIP_H_
