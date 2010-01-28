/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADALIGHT_H_
#define _OSGCOLLADALIGHT_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaInstInfo.h"
#include "OSGLightModelChunk.h"

#include <dom/domLight.h>
#include <dom/domTechnique.h>

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceLight;
class ColladaLight;
OSG_GEN_MEMOBJPTR(ColladaLight);


class OSG_FILEIO_DLLMAPPING ColladaLight : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaLight               Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaLight);

    // forward decl
    class ColladaLightInstInfo;
    OSG_GEN_MEMOBJPTR(ColladaLightInstInfo);


    class ColladaLightInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaInstInfo       Inherited;
        typedef ColladaLightInstInfo  Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaLightInstInfo);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaElement       *colInstParent,
                   ColladaInstanceLight *colInst,
                   Node                 *beaconN       );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Process                                                  */
        /*! \{                                                             */

        virtual void process(void);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Access                                                   */
        /*! \{                                                             */

        Node *getBeacon(void) const;

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 ColladaLightInstInfo(
                     ColladaElement       *colInstParent,
                     ColladaInstanceLight *colInst,
                     Node                 *beaconN       );
        virtual ~ColladaLightInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        Node *_beacon;
    };

    // forward decl
    class ColladaLightAmbientInstInfo;
    OSG_GEN_MEMOBJPTR(ColladaLightAmbientInstInfo);

    class ColladaLightAmbientInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaInstInfo              Inherited;
        typedef ColladaLightAmbientInstInfo  Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaLightAmbientInstInfo);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaElement       *colInstParent,
                   ColladaInstanceLight *colInst       );

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

                 ColladaLightAmbientInstInfo(
                     ColladaElement       *colInstParent,
                     ColladaInstanceLight *colInst       );
        virtual ~ColladaLightAmbientInstInfo(void        );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
    };

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

    virtual void  read          (ColladaElement  *colElemParent);
    virtual Node *createInstance(ColladaInstInfo *colInstInfo  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Ambient Light                                                */
    /*! \{                                                                 */

    void createAmbientLight(ColladaLightAmbientInstInfo *colInstInfo);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    // forward decl
    class LightLoaderState;
    OSG_GEN_MEMOBJPTR(LightLoaderState);


    class LightLoaderState : public ColladaLoaderState
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaLoaderState    Inherited;
        typedef LightLoaderState      Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(LightLoaderState);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static LightLoaderStateTransitPtr create(void);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Access                                                   */
        /*! \{                                                             */

        LightModelChunk *getLightModelChunk(void                  ) const;
        void             setLightModelChunk(LightModelChunk *chunk);

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 LightLoaderState(void);
        virtual ~LightLoaderState(void);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        LightModelChunkUnrecPtr _lightModel;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaLight(daeElement    *elem,
                          ColladaGlobal *global);
    virtual ~ColladaLight(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Helper Functions                                             */
    /*! \{                                                                 */

    Node *createInstanceTechnique(ColladaLightInstInfo          *colInstInfo,
                                  domTechnique                  *tech        );
    Node *createInstanceCommon   (ColladaLightInstInfo          *colInstInfo,
                                  domLight::domTechnique_common *tech        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;
    static const std::string                _loaderStateName;
};

OSG_END_NAMESPACE

// #include "OSGColladaLight.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADALIGHT_H_
