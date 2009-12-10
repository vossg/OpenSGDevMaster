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

#ifndef _OSGCOLLADANODE_H_
#define _OSGCOLLADANODE_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaInstInfo.h"
#include "OSGNode.h"
#include "OSGSkeleton.h"

// forward decl
class domLookat;
class domMatrix;
class domRotate;
class domScale;
class domSkew;
class domTranslate;
class domNode;
class domInstance_node;
class domInstance_geometry;
class domInstance_controller;


OSG_BEGIN_NAMESPACE

// forward decl
class ColladaVisualScene;
class ColladaInstanceGeometry;
class ColladaInstanceController;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaNode : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaNode                Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaNode);

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

    virtual void  read          (ColladaElement         *colElemParent );
    virtual Node *createInstance(ColladaElement         *colInstParent,
                                 ColladaInstanceElement *colInst       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    bool      isJoint      (void          ) const;
    Skeleton *getSkeleton  (void          ) const;

    Node     *getTopNode   (UInt32 instIdx) const;
    Node     *getBottomNode(UInt32 instIdx) const;

    Node     *getNodeBySid (UInt32 instIdx, const std::string &sid) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaNode(daeElement    *elem,
                         ColladaGlobal *global);
    virtual ~ColladaNode(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    class ColladaGeometryInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaInstInfo          Inherited;
        typedef ColladaGeometryInstInfo  Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaGeometryInstInfo);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Class specific                                           */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaNode             *colInstParent,
                   ColladaInstanceGeometry *colInst,
                   Node                    *attachN       );

        virtual void process(void);

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 ColladaGeometryInstInfo(
                     ColladaNode             *colInstParent,
                     ColladaInstanceGeometry *colInst,
                     Node                    *attachN       );
        virtual ~ColladaGeometryInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
    };

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
        /*! \name Class specific                                           */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaNode               *colInstParent,
                   ColladaInstanceController *colInst,
                   Node                      *attachN       );

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
                     Node                      *attachN       );
        virtual ~ColladaControllerInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    void readLookAt   (domLookat    *lookat   );
    void readMatrix   (domMatrix    *matrix   );
    void readRotate   (domRotate    *rotate   );
    void readScale    (domScale     *scale    );
    void readSkew     (domSkew      *skew     );
    void readTranslate(domTranslate *translate);

    void readNode                (domNode                *node     );
    void addNode                 (domNode                *node,
                                  Node                   *attachN  );

    void readInstanceNode        (domInstance_node       *instNode );
    void addInstanceNode         (domInstance_node       *instNode,
                                  Node                   *attachN  );

    void readInstanceGeometry    (domInstance_geometry   *instGeo  );
    void addInstanceGeometry     (domInstance_geometry   *instGeo,
                                  Node                   *attachN  );
    void handleInstanceGeometry  (ColladaInstInfo        *instInfo );

    void readInstanceController  (domInstance_controller *instCtrl );
    void addInstanceController   (domInstance_controller *instCtrl,
                                  Node                   *attachN  );
    void handleInstanceController(ColladaInstInfo        *instInfo );

    void appendXForm(Node         *nodeN                      );
    void cloneXForms(NodeUnrecPtr &topN, NodeUnrecPtr &bottomN);

    Node *createInstanceNode (ColladaElement         *colInstParent,
                              ColladaInstanceElement *colInst,
                              domNode                *node          );
    Node *createInstanceJoint(ColladaElement         *colInstParent,
                              ColladaInstanceElement *colInst,
                              domNode                *node          );

    static ColladaElementRegistrationHelper _regHelper;
    static Int16                            _jointId;

    InstanceStore    _bottomInstStore;

    NodeUnrecPtr     _xformTopN;
    NodeUnrecPtr     _xformBottomN;

    SkeletonUnrecPtr _skel;
};

OSG_GEN_MEMOBJPTR(ColladaNode);

OSG_END_NAMESPACE

// #include "OSGColladaNode.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADANODE_H_
