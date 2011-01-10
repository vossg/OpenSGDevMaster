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
class domInstance_light;
class domInstance_geometry;
class domInstance_controller;


OSG_BEGIN_NAMESPACE

// forward decl
class ColladaVisualScene;
class ColladaInstanceNode;
class ColladaInstanceLight;
class ColladaInstanceGeometry;
class ColladaInstanceController;

class ColladaNode;
OSG_GEN_MEMOBJPTR(ColladaNode);


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

    typedef std::vector<std::string>     NodePath;
    typedef NodePath::iterator           NodePathIt;
    typedef NodePath::const_iterator     NodePathConstIt;


    class ColladaNodeInstInfo : public ColladaInstInfo
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaInstInfo      Inherited;
        typedef ColladaNodeInstInfo  Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(ColladaNodeInstInfo);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static  ColladaInstInfoTransitPtr
            create(ColladaElement      *colInstParent,
                   ColladaInstanceNode *colInst,
                   Node                *parentN       );

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

                 ColladaNodeInstInfo(
                     ColladaElement      *colInstParent,
                     ColladaInstanceNode *colInst,
                     Node                *parentN       );
        virtual ~ColladaNodeInstInfo(void               );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        ColladaNodeRefPtr _colInstTarget;
        NodeUnrecPtr      _parentN;
    };

    OSG_GEN_MEMOBJPTR(ColladaNodeInstInfo);

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
    /*! \name Types                                                        */
    /*! \{                                                                 */

    class NodeLoaderState;
    OSG_GEN_MEMOBJPTR(NodeLoaderState);

    class NodeLoaderState : public ColladaLoaderState
    {
        /*==========================  PUBLIC  =============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name Types                                                    */
        /*! \{                                                             */

        typedef ColladaLoaderState   Inherited;
        typedef NodeLoaderState      Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(NodeLoaderState);

        typedef std::vector<Matrix>          MatrixStack;
        typedef MatrixStack::iterator        MatrixStackIt;
        typedef MatrixStack::const_iterator  MatrixStackConstIt;

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Create                                                   */
        /*! \{                                                             */

        static NodeLoaderStateTransitPtr create(void);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name Access                                                   */
        /*! \{                                                             */

        void            pushNodePath(const std::string &nodeId);
        void            popNodePath (void                     );
        const NodePath &getNodePath (void                     ) const;
        void            dumpNodePath(void                     ) const;

        void            pushMatrix    (const Matrix &matrix);
        void            popMatrix     (void                );
        const Matrix   &getWorldMatrix(void                ) const;

        Skeleton       *getSkeleton(void             ) const;
        void            setSkeleton(Skeleton *skel   );

        Int16           getJointId (void             ) const;
        void            setJointId (Int16     jointId);

        /*! \}                                                             */
        /*=========================  PROTECTED  ===========================*/
      protected:
        /*-----------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                  */
        /*! \{                                                             */

                 NodeLoaderState(void);
        virtual ~NodeLoaderState(void);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/

        NodePath         _nodePath;
        SkeletonUnrecPtr _skel;
        Int16            _jointId;

        Matrix           _worldMatrix;
        MatrixStack      _matrixStack;
    };

    typedef std::map<std::string, Node *> SIdNodeMap;
    typedef SIdNodeMap::iterator          SIdNodeMapIt;
    typedef SIdNodeMap::const_iterator    SIdNodeMapConstIt;
        
    struct InstData
    {
         InstData(void);
        ~InstData(void);
        
        NodePath              _nodePath;
        Matrix                _localMatrix;

        SkeletonUnrecPtr      _skel;
        NodeUnrecPtr          _topN;
        NodeUnrecPtr          _bottomN;
        SIdNodeMap            _sidMap;
    };

    typedef std::vector<InstData>          InstDataStore;
    typedef InstDataStore::iterator        InstDataStoreIt;
    typedef InstDataStore::const_iterator  InstDataStoreConstIt;

    /*! \}                                                                 */
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

    Node *createInstanceNode (ColladaInstInfo *colInstInfo, domNode *node);
    Node *createInstanceJoint(ColladaInstInfo *colInstInfo, domNode *node);

    void handleLookAt   (domLookat    *lookat,
                         InstData     &instData  );
    void handleMatrix   (domMatrix    *matrix,
                         InstData     &instData  );
    void handleRotate   (domRotate    *rotate,
                         InstData     &instData  );
    void handleScale    (domScale     *scale,
                         InstData     &instData  );
    void handleSkew     (domSkew      *skew,
                         InstData     &instData  );
    void handleTranslate(domTranslate *translate,
                         InstData     &instData  );

    void appendXForm     (const Matrix      &m,
                          const std::string &xformSID,
                          InstData          &instData   );
    void appendChild     (domNode           *child,
                          Node              *childN,
                          InstData          &instData   );

    void readNode                 (domNode                *child     );
    void handleNode               (domNode                *child,
                                   InstData               &instData  );

    void readInstanceNode         (domInstance_node       *instNode  );
    void handleInstanceNode       (domInstance_node       *instNode,
                                   InstData               &instData  );

    void readInstanceLight        (domInstance_light      *instLight );
    void handleInstanceLight      (domInstance_light      *instLight,
                                   InstData               &instData  );

    void readInstanceGeometry     (domInstance_geometry   *instGeo   );
    void handleInstanceGeometry   (domInstance_geometry   *instGeo,
                                   InstData               &instData  );

    void readInstanceController   (domInstance_controller *instCtrl  );
    void handleInstanceController (domInstance_controller *instCtrl,
                                   InstData               &instData  );

    static ColladaElementRegistrationHelper _regHelper;
    static const std::string                _loaderStateName;

    InstDataStore _instDataStore;
};

OSG_END_NAMESPACE

#include "OSGColladaNode.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADANODE_H_
