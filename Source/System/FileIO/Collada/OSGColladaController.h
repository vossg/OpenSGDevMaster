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
class domNode;
class domSkin;


OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceController;
class ColladaNode;


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

    class ColladaControllerInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaInstInfo            Inherited;
        typedef ColladaControllerInstInfo  Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaControllerInstInfo);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaNode               *colInstParent,
                   ColladaInstanceController *colInst,
                   Node                      *parentN       );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Access                                                   */
        /*! \{                                                             */

        inline Node *getParentNode(void) const;

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

                 ColladaControllerInstInfo(
                     ColladaNode               *colInstParent,
                     ColladaInstanceController *colInst,
                     Node                      *parentN       );
        virtual ~ColladaControllerInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        NodeUnrecPtr _parentN;
    };

    OSG_GEN_MEMOBJPTR(ColladaControllerInstInfo);

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
        domNode     *jointNode;
        ColladaNode *colJointNode;

        Int16        jointId;
        Matrix       invBindMatrix;
    };

    typedef std::vector<JointInfo>         JointInfoStore;
    typedef JointInfoStore::iterator       JointInfoStoreIt;
    typedef JointInfoStore::const_iterator JointInfoStoreConstIt;

    typedef std::vector<Int16>             JointIdMap;
    typedef JointIdMap::iterator           JointIdMapIt;
    typedef JointIdMap::const_iterator     JointIdMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Helper functions                                             */
    /*! \{                                                                 */

    void  readSkin           (domSkin                   *skin        );
    void  readBindShapeMatrix(domSkin                   *skin        );
    void  resolveJoints      (domSkin                   *skin,
                              ColladaInstanceController *colInstCtrl,
                              JointInfoStore            &jointStore,
                              JointIdMap                &jointIdMap  );
    void  remapJointIds      (domSkin                   *skin,
                              ColladaInstanceController *colInstCtrl,
                              const JointInfoStore      &jointStore,
                              const JointIdMap          &jointIdMap  );
    Int32 findJoint          (const JointInfoStore      &jointStore,
                              domNode                   *joint       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    Matrix           _matBindShape;
    SkeletonUnrecPtr _skeleton;
};

OSG_GEN_MEMOBJPTR(ColladaController);

OSG_END_NAMESPACE

#include "OSGColladaController.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADACONTROLLER_H_
