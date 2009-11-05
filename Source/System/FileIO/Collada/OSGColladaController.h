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

#ifndef _OSGCOLLADACONTROLLER_H_
#define _OSGCOLLADACONTROLLER_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaGeometry.h"
#include "OSGColladaElementFactoryHelper.h"

#include "OSGSkeleton.h"

// forward decl
class domSkin;
class domLookat;
class domMatrix;
class domRotate;
class domScale;
class domSkew;
class domTranslate;
class domNode;

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceController;


class OSG_FILEIO_DLLMAPPING ColladaController : public ColladaGeometry
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaGeometry    Inherited;
    typedef ColladaController  Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaController);

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

    virtual void  read          (void                            );
    virtual Node *createInstance(ColladaInstanceElement *instElem);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaController(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaController(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Internal Types                                               */
    /*! \{                                                                 */

    struct JointInfo
    {
        domNode      *jointNode;

        Matrix        invBindMatrix;
        NodeUnrecPtr  topN;
        NodeUnrecPtr  bottomN;
    };

    typedef std::vector<JointInfo>         JointInfoStore;
    typedef JointInfoStore::iterator       JointInfoStoreIt;
    typedef JointInfoStore::const_iterator JointInfoStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Helper functions                                             */
    /*! \{                                                                 */

    void  readSkin     (domSkin                   *skin        );
    void  resolveJoints(domSkin                   *skin,
                        ColladaInstanceController *colInstCtrl,
                        JointInfoStore            &jointStore  );
    SkeletonTransitPtr
          buildSkeleton  (JointInfoStore &jointStore);
    void  buildTransforms(JointInfo      &jointInfo );
    void  buildLookAt    (domLookat    *lookAt,    JointInfo &jointInfo);
    void  buildMatrix    (domMatrix    *matrix,    JointInfo &jointInfo);
    void  buildRotate    (domRotate    *rotate,    JointInfo &jointInfo);
    void  buildScale     (domScale     *scale,     JointInfo &jointInfo);
    void  buildSkew      (domSkew      *skew,      JointInfo &jointInfo);
    void  buildTranslate (domTranslate *translate, JointInfo &jointInfo);

    void  prependXForm   (Node         *node,      JointInfo &jointInfo);
    void  appendXForm    (Node         *node,      JointInfo &jointInfo);

    Int32 findJoint    (const JointInfoStore      &jointStore,
                        domNode                   *joint       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    Matrix _matBindShape;
};

OSG_GEN_MEMOBJPTR(ColladaController);

OSG_END_NAMESPACE

// #include "OSGColladaController.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADACONTROLLER_H_
