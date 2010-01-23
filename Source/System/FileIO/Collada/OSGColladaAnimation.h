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

#ifndef _OSGCOLLADAANIMATION_H_
#define _OSGCOLLADAANIMATION_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaInstInfo.h"
#include "OSGColladaSource.h"

#include "OSGAnimKeyFrameTemplate.h"

// forward decl
class domAnimation;
class domInputLocal;
class domChannel;
class domSampler;


OSG_BEGIN_NAMESPACE

// forward decl
class ColladaAnimation;
OSG_GEN_MEMOBJPTR(ColladaAnimation);
class ColladaAnimationClip;
class ColladaInstanceAnimation;


class OSG_FILEIO_DLLMAPPING ColladaAnimation 
    : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaAnimation           Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaAnimation);

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
                   ColladaAnimation         *colInstTarget,
                   AnimKeyFrameTemplate     *animTmpl      );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Access                                                   */
        /*! \{                                                             */

        ColladaAnimation     *getAnim    (void) const;
        AnimKeyFrameTemplate *getTemplate(void) const;

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Process                                                  */
        /*! \{                                                             */

        virtual void process(void);

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 ColladaAnimationInstInfo(
                     ColladaAnimationClip     *colInstParent,
                     ColladaInstanceAnimation *colInst,
                     ColladaAnimation         *colInstTarget,
                     AnimKeyFrameTemplate     *animTmpl      );
        virtual ~ColladaAnimationInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        ColladaAnimationRefPtr       _colInstTarget;
        AnimKeyFrameTemplateUnrecPtr _animTmpl;
    };

    OSG_GEN_MEMOBJPTR(ColladaAnimationInstInfo);

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

    virtual void                  read          (ColladaElement  *colElemParent);
    virtual AnimKeyFrameTemplate *createInstance(ColladaInstInfo *colInstInfo  );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaAnimation(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaAnimation(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    typedef std::map<std::string, ColladaSourceRefPtr> SourceMap;
    typedef SourceMap::iterator                        SourceMapIt;
    typedef SourceMap::const_iterator                  SourceMapConstIt;

    struct DataSourceInfo
    {
        AnimKeyFrameDataSourceUnrecPtr _dataSource;
        std::string                    _target;
        UInt32                         _firstKey;
        UInt32                         _lastKey;
    };

    void readAnim           (domAnimation           *anim          );
    void createInstanceAnim (domAnimation           *anim,
                             ColladaElement         *colInstParent,
                             ColladaInstanceElement *colInst,
                             AnimKeyFrameTemplate   *animTmpl      );

    void createDataSource   (domChannel             *channel,
                             domSampler             *sampler,
                             DataSourceInfo         &dsInfo        );
    void handleInput        (domChannel             *channel,
                             domSampler             *sampler,
                             ColladaAnimationClip   *colAnimClip,
                             AnimKeyFrameTemplate   *animTmpl,
                             DataSourceInfo         &dsInfo        );
    void handleOutput       (domChannel             *channel,
                             domSampler             *sampler,
                             AnimKeyFrameTemplate   *animTmpl,
                             DataSourceInfo         &dsInfo        );
    void handleInterpolation(domChannel             *channel,
                             domSampler             *sampler, 
                             AnimKeyFrameTemplate   *animTmpl,
                             DataSourceInfo         &dsInfo        );

    domInputLocal *findInput(domSampler *sampler, const std::string &semantic);
    
    static ColladaElementRegistrationHelper _regHelper;

    SourceMap _sourceMap;
};

OSG_END_NAMESPACE

// #include "OSGColladaAnimation.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAANIMATION_H_
