// OpenSG example: ClipPlaneCaps2
//
// Demonstrates the use of the ClipPlaneChunk, StencilChunk for capping of
// clipped geometry.
//
// This example uses VisitSubTree cores in order to minimize the memory
// footprint and in order cleanly separate the scene from the clipping
// graph structure.
//
// This examples allows creation of a box and a torus. Additionally, two clip
// planes can be set up. On clipping the geometry caps are used to repair the
// clipped geometry.
//
// User interface:
//  a) mouse => standard navigator
//  b) keyboard =>
//      '1': enable/disable clip plane 0
//      '2': enable/disable clip plane 1
//      '3': enable/disable box geometry
//      '4': enable/disable torus geometry
//      'n': move clip plane 0 opposite to the normal direction of the plane
//      'm': move clip plane 0 in the normal direction of the plane
//      ',': move clip plane 1 opposite to the normal direction of the plane
//      '.': move clip plane 1 in the normal direction of the plane
//      'q': move box in -x direction
//      'w': move box in +x direction
//      'a': move box in -y direction
//      's': move box in +y direction
//      'y': move box in -z direction
//      'x': move box in +z direction
//      'e': move torus in -x direction
//      'r': move torus in +x direction
//      'd': move torus in -y direction
//      'f': move torus in +y direction
//      'c': move torus in -z direction
//      'v': move torus in +z direction
//      'p': create a png from scene with the graphviz tool output 
//
// This example was contributed by Johannes Brunen

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

#ifdef OSG_BUILD_ACTIVE

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGNameAttachment.h>

#include <OSGMultiSwitch.h>
#include <OSGVisitSubTree.h>
#include <OSGGroupingStage.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGChunkMaterial.h>
#include <OSGMultiPassMaterial.h>
#include <OSGClipPlaneChunk.h>
#include <OSGStencilChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGMaterialChunk.h>
#include <OSGColorMaskChunk.h>
#include <OSGDepthChunk.h>
#include <OSGFieldContainerUtils.h>
#include <OSGSceneGraphUtils.h>
#include <OSGContainerCollection.h>
#include <OSGDotFileGeneratorGraphOp.h>

#else // OSG_BUILD_ACTIVE

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGNameAttachment.h>

#include <OpenSG/OSGMultiSwitch.h>
#include <OpenSG/OSGVisitSubTree.h>
#include <OpenSG/OSGGroupingStage.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMultiPassMaterial.h>
#include <OpenSG/OSGClipPlaneChunk.h>
#include <OpenSG/OSGStencilChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGColorMaskChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGFieldContainerUtils.h>
#include <OpenSG/OSGSceneGraphUtils.h>
#include <OpenSG/OSGContainerCollection.h>
#include <OpenSG/OSGDotFileGeneratorGraphOp.h>


#endif // OSG_BUILD_ACTIVE

//
// Graphviz related globals
//
const char* graphviz_dot_executale = "c:/utils/python32/tools/Graphviz/bin/dot.exe";
const char* graphviz_output_file   = "d:/out.dot";

//
// the number of clipping planes supported by the demo. Define a plane color
// for each.
//
const int iNumClipPlanes = 2;
OSG::Color4f planeCol[iNumClipPlanes] = { OSG::Color4f(0.f,1.f,0.f,1.f), OSG::Color4f(0.f,0.f,1.f,1.f) };

//
// convenience type
//
typedef std::vector<OSG::NodeRefPtr> VecNodesT; 

//
// transport container for the actual clip plane data
//
struct ClipPlaneData
{
    OSG::Vec4f _equation;
    bool       _enabled;
};

typedef std::vector<ClipPlaneData> VecCPData;

//
// The clipplane scene manager extension smart pointer
//
class ClippingSceneManager;
typedef boost::shared_ptr<ClippingSceneManager> ClippingSceneManagerPtr;

//
// global state
//
VecCPData               vecClipPlaneData;      // transport clip plane info
VecNodesT               vecGeometries;         // box and torus
ClippingSceneManagerPtr mgr;

//
// for each clip plane these data are necessary
//
struct ClipPlaneDetails
{
    OSG::ClipPlaneChunkRefPtr  _clipPlaneChunk;
    OSG::NodeRefPtr            _clipPlaneBeacon;
    OSG::GeometryRefPtr        _planeGeometryCore;
    OSG::TransformRefPtr       _planeTrafoCore;
    OSG::MaterialChunkRefPtr   _planeMaterialChunk;
    OSG::PolygonChunkRefPtr    _planePolygonChunk;
};

typedef std::vector<ClipPlaneDetails> VecCPDetailsT;

//
// Some global convenience functions
//

//----- createChunkMaterial ---------------------------------------------------

OSG::ChunkMaterialTransitPtr createChunkMaterial(const OSG::Color3f& col)
{
    using namespace OSG;

    ChunkMaterialUnrecPtr mat = ChunkMaterial::create();

    MaterialChunkUnrecPtr materialChunk = MaterialChunk::create();
    PolygonChunkUnrecPtr  polygonChunk  = PolygonChunk::create();

    materialChunk->setAmbient      (Color4f(0.5*col[0],  0.5*col[1],  0.5*col[2],  1.0f));
    materialChunk->setDiffuse      (Color4f(    col[0],      col[1],      col[2],  1.0f));
    materialChunk->setEmission     (Color4f(      0.0f,        0.0f,        0.0f,  1.0f));
    materialChunk->setSpecular     (Color4f(      0.8f,        0.8f,        0.8f,  1.0f));
    materialChunk->setShininess    (20.f);

    polygonChunk->setFrontMode(GL_FILL);
    polygonChunk->setBackMode(GL_FILL);
    polygonChunk->setOffsetFactor(1.f);
    polygonChunk->setOffsetBias(1.f);
    polygonChunk->setOffsetFill(true);
    polygonChunk->setCullFace(GL_NONE);

    mat->addChunk(materialChunk);
    mat->addChunk(polygonChunk);

    return ChunkMaterialTransitPtr(mat);
}

//----- BuildGeometry ---------------------------------------------------------

enum {
    TORUS_GEOMETRY = 1,
    BOX_GEOMETRY = 2
};

OSG::NodeTransitPtr BuildGeometry(int kind, const OSG::Matrix& matrix, const OSG::Color3f& color)
{
    using namespace OSG;

    GeometryUnrecPtr geometryCore = NULL;

    switch (kind)
    {
        case TORUS_GEOMETRY: geometryCore = makeTorusGeo(2, 6, 8, 16);       break;
        case BOX_GEOMETRY:   geometryCore = makeBoxGeo(15, 15, 15, 1, 1, 1); break;
        default:
            assert(false);
    }

    ChunkMaterialUnrecPtr material = createChunkMaterial(color);
    geometryCore->setMaterial(material);

    TransformUnrecPtr transformCore = Transform::create();
    transformCore->setMatrix(matrix);

    NodeUnrecPtr transformNode = makeNodeFor(transformCore);
    NodeUnrecPtr geometryNode  = makeNodeFor(geometryCore);

    setName(transformNode,  "transformNode");
    setName(geometryNode,   "geometryNode");

    transformNode->addChild(geometryNode);

    return NodeTransitPtr(transformNode);
}

//----- BuildProxyGeometry ----------------------------------------------------

OSG::NodeTransitPtr BuildProxyGeometry(int kind, const OSG::Matrix& matrix, const OSG::Color3f& color)
{
    using namespace OSG;

    NodeUnrecPtr prototype = BuildGeometry(kind, Matrix(), color);

    VisitSubTreeUnrecPtr visitTreeCore = VisitSubTree::create();
    visitTreeCore->setSubTreeRoot(prototype);

    ContainerCollectionUnrecPtr cc = ContainerCollection::create();
    cc->addContainer(prototype);

    TransformUnrecPtr transformCore = Transform::create();
    transformCore->setMatrix(matrix);

    NodeUnrecPtr visitTreeNode = makeNodeFor(visitTreeCore);
    visitTreeNode->addAttachment(cc);

    NodeUnrecPtr prototype_proxy = Node::create();
    prototype_proxy->setCore(transformCore);
    prototype_proxy->addChild(visitTreeNode);

    setName(prototype,            "prototype");
    setName(prototype_proxy,      "prototype_proxy");
    setName(visitTreeNode,        "visitTreeNode");

    return NodeTransitPtr(prototype_proxy);
}

//
// The clipplane scene manager extension
//
class ClippingSceneManager
{
public:
    OSG::Node*  getInternalRoot         ()                                                  { return _root;         }
    OSG::Node*  getRoot                 ()                                                  { return _clippingRoot; }
    void        setRoot                 (OSG::Node* root);

    void        showAll                 ()                                                  { _mgr->showAll();       }
    void        redraw                  ()                                                  { _mgr->redraw();        }
    void        resize                  (OSG::UInt16 width,  OSG::UInt16 height)            { _mgr->resize(width,height); }
    void        mouseMove               (OSG::Int16 x, OSG::Int16 y)                        { _mgr->mouseMove(x,y); }
    void        mouseButtonPress        (OSG::UInt16 button, OSG::Int16 x, OSG::Int16 y)    { _mgr->mouseButtonPress(button,x,y); }
    void        mouseButtonRelease      (OSG::UInt16 button, OSG::Int16 x, OSG::Int16 y)    { _mgr->mouseButtonRelease(button,x,y); }
    void        key                     (OSG::UChar8 key,    OSG::Int16 x, OSG::Int16 y)    { _mgr->key(key,x,y); }

    void        updateClipPlanes        (const VecCPData& vec);
    void        createClipPlaneDetails  ();

public:
    static ClippingSceneManagerPtr  
                create                  (OSG::SimpleSceneManager* mgr);
       
               ~ClippingSceneManager    ();
private:
                ClippingSceneManager    (OSG::SimpleSceneManager* mgr);

    void        initialize              ();

private:
    void                            updateClipPlaneState        (int numEnabled);

    void                            createClipSubGraph          (int i);

    OSG::NodeTransitPtr             createClipSubGraphPartFst   (int i) const;
    OSG::NodeTransitPtr             createClipSubGraphPartSec   (int i) const;

    OSG::MaterialGroupTransitPtr    create_mat_group_fst        (int i) const;
    OSG::MaterialGroupTransitPtr    create_mat_group_sec        (int i) const;
    
    OSG::ChunkMaterialTransitPtr    material_1                  (int i) const;
    OSG::ChunkMaterialTransitPtr    material_2                  (int i) const;
    OSG::ChunkMaterialTransitPtr    material_3                  (std::size_t i) const;

    OSG::NodeTransitPtr             create_plane_node           (OSG::MaterialGroup* mgrp_sec, int i) const;

private:
    OSG::SimpleSceneManagerRefPtr   _mgr;
    OSG::ChunkMaterialRefPtr        _overrideMaterial;

    OSG::NodeRefPtr                 _root;
    OSG::NodeRefPtr                 _internalRoot;
    OSG::NodeRefPtr                 _clippingRoot;
    OSG::NodeRefPtr                 _clipPlaneRoot;

    OSG::ContainerCollectionRefPtr  _container;

    VecCPDetailsT                   _vecClipPlaneDetails;
    VecCPData                       _vecClipPlaneDataLast;
};

//----- create ----------------------------------------------------------------

ClippingSceneManagerPtr 
ClippingSceneManager::create(OSG::SimpleSceneManager* mgr)
{
    assert(mgr);
    return ClippingSceneManagerPtr(new ClippingSceneManager(mgr));
}

//----- ctor ------------------------------------------------------------------

ClippingSceneManager::ClippingSceneManager(OSG::SimpleSceneManager* mgr)
: _mgr(mgr)
, _overrideMaterial(NULL)
, _root(NULL)
, _internalRoot(NULL)
, _clippingRoot(NULL)
, _clipPlaneRoot(NULL)
, _vecClipPlaneDetails()
, _vecClipPlaneDataLast()
{
    initialize();
}

//----- dtor ------------------------------------------------------------------

ClippingSceneManager::~ClippingSceneManager()
{
    _vecClipPlaneDataLast.clear();
    _vecClipPlaneDetails.clear();
    
    _clipPlaneRoot = NULL;
    _clippingRoot = NULL;
    _internalRoot = NULL;
    _root = NULL;
    _overrideMaterial = NULL;
    _mgr = NULL;
}

//----- setRoot ---------------------------------------------------------------

void ClippingSceneManager::setRoot(OSG::Node* root)
{
    using namespace OSG;

    if (_clippingRoot)
        _internalRoot->subChild(_clippingRoot);

    _clippingRoot = root;

    if (_clippingRoot) {
        setName(_clippingRoot, "_clippingRoot");
        _internalRoot->addChild(_clippingRoot);
    }
}

//----- initialize ------------------------------------------------------------

void ClippingSceneManager::initialize()
{
    using namespace OSG;

    _root          = makeNodeFor(Group::create());
    _internalRoot  = makeNodeFor(Group::create());
    _clippingRoot  = makeNodeFor(Group::create());
    _clipPlaneRoot = makeNodeFor(GroupingStage::create());

    _overrideMaterial = ChunkMaterial::create();

    MaterialChunkOverrideGroupUnrecPtr mat_grp = MaterialChunkOverrideGroup::create();
    mat_grp->setMaterial(_overrideMaterial);

    NodeUnrecPtr overrideNode = makeNodeFor(mat_grp);
    
    _root->addChild(overrideNode);
    _root->addChild(_clipPlaneRoot);
   
    overrideNode->addChild(_internalRoot);
    _internalRoot->addChild(_clippingRoot);

    //
    // for storing clipplane beacon we use a container
    // collection attachment which we attach to the scene
    // node. Otherwise the scene could not be saved correctly,
    // as the beacons would be lost.
    //
    _container = ContainerCollection::create();
    _root->addAttachment(_container);

    //
    //  For each clip plane we provide a ClipPlaneChunk, the plane geometry,
    //  the plane transform core and at least a plane color conveniently in
    //  a vector of type VecCPDetailsT. The next function call
    //  initializes this data structure.
    //
    createClipPlaneDetails();

    assert(_mgr->getWindow() != NULL);

    _mgr->setRoot(_root);

    //
    // For illustration purpose only
    //
    setName(_root,          "_root");
    setName(_internalRoot,  "_internalRoot");
    setName(_clippingRoot , "_clippingRoot");
    setName(_clipPlaneRoot, "_clipPlaneRoot");
    setName(overrideNode,   "overrideNode");
}

//----- createClipPlaneDetails ------------------------------------------------

void ClippingSceneManager::createClipPlaneDetails()
{
    using namespace OSG;

    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneDetails details;

        //
        // Create clip plane chunk
        //
        details._clipPlaneBeacon = Node::create();
        details._clipPlaneBeacon->setCore(Transform::create());

        _container->addContainer(details._clipPlaneBeacon);

        details._clipPlaneChunk = ClipPlaneChunk::create();
        details._clipPlaneChunk->setEquation(Vec4f(1,0,0,0));
        details._clipPlaneChunk->setEnable(false);
        details._clipPlaneChunk->setBeacon(details._clipPlaneBeacon);

        //
        // Create plane geometry
        //
        details._planeGeometryCore = makePlaneGeo(100.f, 100.f, 128, 128);
        details._planeGeometryCore->setMaterial(NULL);

        //
        // Create plane transformation core
        //
        Matrix mat;
        mat.setIdentity();

        details._planeTrafoCore = Transform::create();
        details._planeTrafoCore->setMatrix(mat);

        //
        // Define plane color
        //
        details._planeMaterialChunk = MaterialChunk::create();
        details._planeMaterialChunk->setLit(true);
        details._planeMaterialChunk->setDiffuse  (planeCol[i]);
        details._planeMaterialChunk->setSpecular (Color4f(0.8f, 0.8f, 0.8f, 1.0f));
        details._planeMaterialChunk->setShininess(20);

        details._planePolygonChunk = PolygonChunk::create();
        details._planePolygonChunk->setFrontMode(GL_FILL);
        details._planePolygonChunk->setBackMode(GL_FILL);
        details._planePolygonChunk->setCullFace(GL_NONE);

        _vecClipPlaneDetails.push_back(details);

        setName(details._clipPlaneBeacon, "_clipPlaneBeacon");
    }
}

//----- updateClipPlanes ------------------------------------------------------

void ClippingSceneManager::updateClipPlanes(const VecCPData& vec)
{
    using namespace OSG;

    std::size_t sz  = vec.size();
    int numEnabled = 0;

    std::size_t num = _vecClipPlaneDetails.size();
    for (std::size_t i = 0; i < num; ++i)
    {
        ClipPlaneChunk *clipPlaneChunk =
            _vecClipPlaneDetails[i]._clipPlaneChunk;

        clipPlaneChunk->setEnable(false);

        if(i < sz)
        {
            const ClipPlaneData& data = vec[i];

            //
            // Update the clip plane chunk
            //
            clipPlaneChunk->setEquation(data._equation);
            clipPlaneChunk->setEnable  (data._enabled );

            if (data._enabled)
                numEnabled++;

            //
            // and the plane transform core
            //
            Matrix rotMat;
            Vec4f v1(0.f, 0.f, -1.f, 0.f);
            Quaternion q(Vec3f(v1), Vec3f(data._equation));
            rotMat.setTransform(q);

            Matrix mat;
            Vec3f v2(0.0f, 0.0f, data._equation[3]);
            mat.setTranslate(v2);

            mat.multLeft(rotMat);

            _vecClipPlaneDetails[i]._planeTrafoCore->setMatrix(mat);
        }
    }

    bool update = _vecClipPlaneDataLast.size() != sz;

    if (!update) {
        for (std::size_t i = 0; i < sz; ++i) {
            if (_vecClipPlaneDataLast[i]._enabled != vec[i]._enabled) {
                update = true;
                break;
            }
        }
    } 
    
    if (update) {
        updateClipPlaneState(numEnabled);
        _vecClipPlaneDataLast = vec;
    }
}

//----- updateClipPlaneState --------------------------------------------------

void ClippingSceneManager::updateClipPlaneState(int numEnabled)
{
    using namespace OSG;

    StateChunk* curr = _overrideMaterial->find(ClipPlaneChunk::getClassType());
    while (curr) {
        _overrideMaterial->subChunk(curr);
        curr = _overrideMaterial->find(ClipPlaneChunk::getClassType());
    }

    if (numEnabled > 0)
    {
        _clipPlaneRoot->clearChildren();

        std::size_t sz = _vecClipPlaneDetails.size();
        for (std::size_t i = 0; i < sz; ++i)
        {
            ClipPlaneChunk* clipPlaneChunk = _vecClipPlaneDetails[i]._clipPlaneChunk;
            if (clipPlaneChunk->getEnable())
            {
                _overrideMaterial->addChunk(clipPlaneChunk);

                createClipSubGraph(static_cast<int>(i));
            }
        }

    } else
        _clipPlaneRoot->clearChildren();

    commitChanges();
}

//----- createClipSubGraph ----------------------------------------------------

void ClippingSceneManager::createClipSubGraph(int i)
{
    using namespace OSG;

    NodeUnrecPtr node_1 = createClipSubGraphPartFst(i);
    NodeUnrecPtr node_2 = createClipSubGraphPartSec(i);

    _clipPlaneRoot->addChild(node_1);
    _clipPlaneRoot->addChild(node_2);

    setName(node_1, "clipSubGraphPartFst");
    setName(node_2, "clipSubGraphPartSec");
}

//----- createClipSubGraphPartFst ---------------------------------------------

OSG::NodeTransitPtr ClippingSceneManager::createClipSubGraphPartFst(int i) const
{
    using namespace OSG;

    VisitSubTreeUnrecPtr visitor = VisitSubTree::create();
    visitor->setSubTreeRoot(_internalRoot);
    NodeUnrecPtr visit_node = makeNodeFor(visitor);

    NodeUnrecPtr node = makeNodeFor(  create_mat_group_fst(i)  );
    node->addChild(visit_node);

    return NodeTransitPtr(node);
}

//----- createClipSubGraphPartSec ---------------------------------------------

OSG::NodeTransitPtr ClippingSceneManager::createClipSubGraphPartSec(int i) const
{
    using namespace OSG;

    MaterialGroupUnrecPtr mgrp = create_mat_group_sec(i);
    return NodeTransitPtr(create_plane_node(mgrp, i));
}

//----- create_mat_group_fst --------------------------------------------------

OSG::MaterialGroupTransitPtr ClippingSceneManager::create_mat_group_fst(int i) const
{
    using namespace OSG;

    ChunkMaterialUnrecPtr mat1 = material_1(i);
    ChunkMaterialUnrecPtr mat2 = material_2(i);

    MultiPassMaterialUnrecPtr mat = MultiPassMaterial::create();
    mat->addMaterial(mat1);
    mat->addMaterial(mat2);

    mat->setSortKey(2*i + 0);

    setName(mat, "setSortKey(2*i + 0)");

    MaterialGroupUnrecPtr mgrp = MaterialGroup::create();
    mgrp->setMaterial(mat);

    return MaterialGroupTransitPtr(mgrp);
}

//----- create_mat_group_sec --------------------------------------------------

OSG::MaterialGroupTransitPtr ClippingSceneManager::create_mat_group_sec(int i) const
{
    using namespace OSG;

    ChunkMaterialUnrecPtr mat = material_3(i);

    mat->setSortKey(2*i + 1);

    setName(mat, "setSortKey(2*i + 1)");

    MaterialGroupUnrecPtr mgrp = MaterialGroup::create();
    mgrp->setMaterial(mat);

    return MaterialGroupTransitPtr(mgrp);
}

//----- create_plane_node -----------------------------------------------------

OSG::NodeTransitPtr ClippingSceneManager::create_plane_node(
    OSG::MaterialGroup* mgrp,
    int i) const
{
    using namespace OSG;

    NodeUnrecPtr planeGeoNode = Node::create();
    planeGeoNode->setCore(_vecClipPlaneDetails[i]._planeGeometryCore);

    NodeUnrecPtr planeTrafoNode = Node::create();
    planeTrafoNode->setCore(_vecClipPlaneDetails[i]._planeTrafoCore);
    planeTrafoNode->addChild(planeGeoNode);

    NodeUnrecPtr materialNode = Node::create();
    materialNode->setCore(mgrp);
    materialNode->addChild(planeTrafoNode);

    setName(planeGeoNode,   "planeGeoNode");
    setName(planeTrafoNode, "planeTrafoNode");
    setName(materialNode,   "planeMaterialNode");

    return NodeTransitPtr(materialNode);
}

//----- material_1 ------------------------------------------------------------

OSG::ChunkMaterialTransitPtr ClippingSceneManager::material_1(int i) const
{
    using namespace OSG;

    StencilChunkUnrecPtr stencilChunk = StencilChunk::create();
    stencilChunk->setClearBuffer(1);
    stencilChunk->setStencilFunc(GL_ALWAYS);
    stencilChunk->setStencilValue(0);
    stencilChunk->setStencilMask(0x0);
    stencilChunk->setStencilOpFail(GL_KEEP);
    stencilChunk->setStencilOpZFail(GL_KEEP);
    stencilChunk->setStencilOpZPass(GL_INCR);

    setName(stencilChunk, "1 GL_ALWAYS\\n0 0x0n\\nGL_KEEP GL_KEEP GL_INCR");

    DepthChunkUnrecPtr depthChunk = DepthChunk::create();
    depthChunk->setEnable(false);

    PolygonChunkUnrecPtr polygonChunk = PolygonChunk::create();
    polygonChunk->setFrontMode(GL_FILL);
    polygonChunk->setBackMode(GL_FILL);
    polygonChunk->setCullFace(GL_FRONT);

    ColorMaskChunkUnrecPtr colorMaskChunk = ColorMaskChunk::create();
    colorMaskChunk->setMaskR(false);
    colorMaskChunk->setMaskG(false);
    colorMaskChunk->setMaskB(false);
    colorMaskChunk->setMaskA(false);

    setName(colorMaskChunk, "4xfalse");

    ChunkMaterialUnrecPtr mat = ChunkMaterial::create();
    mat->addChunk(stencilChunk);
    mat->addChunk(depthChunk);
    mat->addChunk(polygonChunk);
    mat->addChunk(colorMaskChunk);
    mat->addChunk(_vecClipPlaneDetails[i]._clipPlaneChunk);

    return ChunkMaterialTransitPtr(mat);
}

//----- material_2 ------------------------------------------------------------

OSG::ChunkMaterialTransitPtr ClippingSceneManager::material_2(int i) const
{
    using namespace OSG;

    StencilChunkUnrecPtr stencilChunk = StencilChunk::create();
    stencilChunk->setClearBuffer(0);
    stencilChunk->setStencilFunc(GL_ALWAYS);
    stencilChunk->setStencilValue(0);
    stencilChunk->setStencilMask(0x0);
    stencilChunk->setStencilOpFail(GL_KEEP);
    stencilChunk->setStencilOpZFail(GL_KEEP);
    stencilChunk->setStencilOpZPass(GL_DECR);

    setName(stencilChunk, "0 GL_ALWAYS\\n0 0x0\\nGL_KEEP GL_KEEP GL_DECR");

    DepthChunkUnrecPtr depthChunk = DepthChunk::create();
    depthChunk->setEnable(false);

    PolygonChunkUnrecPtr polygonChunk = PolygonChunk::create();
    polygonChunk->setFrontMode(GL_FILL);
    polygonChunk->setBackMode(GL_FILL);
    polygonChunk->setCullFace(GL_BACK);

    ColorMaskChunkUnrecPtr colorMaskChunk = ColorMaskChunk::create();
    colorMaskChunk->setMaskR(false);
    colorMaskChunk->setMaskG(false);
    colorMaskChunk->setMaskB(false);
    colorMaskChunk->setMaskA(false);

    setName(colorMaskChunk, "4xfalse");

    ChunkMaterialUnrecPtr mat = ChunkMaterial::create();
    mat->addChunk(stencilChunk);
    mat->addChunk(depthChunk);
    mat->addChunk(polygonChunk);
    mat->addChunk(colorMaskChunk);
    mat->addChunk(_vecClipPlaneDetails[i]._clipPlaneChunk);

    return ChunkMaterialTransitPtr(mat);
}

//----- material_3 ------------------------------------------------------------

OSG::ChunkMaterialTransitPtr ClippingSceneManager::material_3(std::size_t i) const
{
    using namespace OSG;

    StencilChunkUnrecPtr stencilChunk = StencilChunk::create();
    stencilChunk->setClearBuffer(0);
    stencilChunk->setStencilFunc(GL_NOTEQUAL);
    stencilChunk->setStencilValue(0);
    stencilChunk->setStencilMask(~0x0);
    stencilChunk->setStencilOpFail(GL_KEEP);
    stencilChunk->setStencilOpZFail(GL_KEEP);
    stencilChunk->setStencilOpZPass(GL_KEEP);

    setName(stencilChunk, "0 GL_NOTEQUAL\\n0 ~0x0\\nGL_KEEP GL_KEEP GL_KEEP");

    ChunkMaterialUnrecPtr mat = ChunkMaterial::create();

    mat->addChunk(_vecClipPlaneDetails[i]._planeMaterialChunk);
    mat->addChunk(_vecClipPlaneDetails[i]._planePolygonChunk);

    std::size_t iNumClipPlanes = _vecClipPlaneDetails.size();
    for (std::size_t j = 0; j < iNumClipPlanes; ++j) {
        if (i != j && _vecClipPlaneDetails[j]._clipPlaneChunk->getEnable())
            mat->addChunk(_vecClipPlaneDetails[j]._clipPlaneChunk);
    }
    mat->addChunk(stencilChunk);

    return ChunkMaterialTransitPtr(mat);
}

//
// scene management functions
//

/*----- create_and_exe_dot_file ---------------------------------------------*/

void create_and_exe_dot_file(OSG::Node*  node)
{
    using namespace OSG;

    namespace fs = ::boost::filesystem;

    fs::path dot_file(graphviz_output_file); dot_file.replace_extension(".dot");
    fs::path png_file(graphviz_output_file); png_file.replace_extension(".png");

    if (fs::exists(dot_file))
        fs::remove(dot_file);

    if (fs::exists(png_file))
        fs::remove(png_file);

    DotFileGeneratorGraphOpRefPtr go = DotFileGeneratorGraphOp::create();

    std::string param("filename=");
    go->setParams(param + dot_file.string());
    go->setParams("max_node_children=10 no_name_attachments=true no_ranks=true");

    go->traverse(node);

    if (!fs::exists(dot_file))
        return;

    fs::path exe_file(graphviz_dot_executale);
    if (!fs::exists(exe_file))
        return;

    std::string cmd = exe_file.string();
    cmd += " -T png " + dot_file.string() + " -o " + png_file.string();

    system(cmd.c_str()) ;
}

//----- cleanup ---------------------------------------------------------------

void cleanup(void)
{
    vecGeometries.clear();
    mgr.reset();
}

//----- display ---------------------------------------------------------------

void display(void)
{
    // render

    mgr->redraw();

    // all done, swap
    glutSwapBuffers();
}

//----- reshape ---------------------------------------------------------------

void reshape(int w, int h)
{
    mgr->resize(w,h);
    glutPostRedisplay();
}

//----- mouse -----------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

//----- motion ----------------------------------------------------------------

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//----- keyboard --------------------------------------------------------------

void keyboard(unsigned char k, int, int)
{
    static OSG::Real32 val0 = 0.f;
    static OSG::Real32 val1 = 0.f;

    static OSG::Real32 x1 = 0.f;
    static OSG::Real32 y1 = 0.f;
    static OSG::Real32 z1 = 0.f;

    static OSG::Real32 x2 = 0.f;
    static OSG::Real32 y2 = 0.f;
    static OSG::Real32 z2 = 0.f;

    switch(k)
    {
    case ' ':
        {
            OSG::SceneGraphPrinter sgp(mgr->getRoot());
            sgp.printDownTree(std::cout);
        }
        break;

    case '1':   // enable/disable clip plane 0
        {
            vecClipPlaneData[0]._enabled = !vecClipPlaneData[0]._enabled;
            mgr->updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '2':   // enable/disable clip plane 1
        {
            vecClipPlaneData[1]._enabled = !vecClipPlaneData[1]._enabled;
            mgr->updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '3':   // enable/disable box geometry
        {
            if(vecGeometries[0] == NULL)
            {
                OSG::Matrix matrix;
                OSG::Vec3f v(10.f,  0.f, 15.f);
                matrix.setTranslate(v);

                //OSG::NodeUnrecPtr boxTree = BuildGeometry(BOX_GEOMETRY, matrix, OSG::Color3f(0.0f, 0.6f, 0.7f));
                OSG::NodeUnrecPtr boxTree = BuildProxyGeometry(BOX_GEOMETRY, matrix, OSG::Color3f(0.0f, 0.6f, 0.7f));

                vecGeometries[0] = boxTree;
                mgr->getRoot()->addChild(boxTree);
            }
            else
            {
                mgr->getRoot()->subChild(vecGeometries[0]);
                vecGeometries[0] = NULL;
            }

//             mgr->showAll();
//             mgr->redraw();
        }
        break;
    case '4':   // enable/disable torus geometry
        {
            if (vecGeometries[1] == NULL)
            {
                OSG::Matrix matrix;
                OSG::Vec3f v( 0.f, 10.f, 0.f);
                matrix.setTranslate(v);

                OSG::NodeUnrecPtr torusTree = BuildGeometry(TORUS_GEOMETRY, matrix, OSG::Color3f(0.7f, 0.2f, 0.0f));
                //OSG::NodeUnrecPtr torusTree = BuildProxyGeometry(TORUS_GEOMETRY, matrix, OSG::Color3f(0.7f, 0.2f, 0.0f));

                vecGeometries[1] = torusTree;
                mgr->getRoot()->addChild(torusTree);
            }
            else
            {
                mgr->getRoot()->subChild(vecGeometries[1]);
                vecGeometries[1] = NULL;
            }

//             mgr->showAll();
//             mgr->redraw();
        }
        break;

    case '5':
        {
            OSG::SceneFileHandler::the()->write(mgr->getRoot(), 
                                                "clipplane_model.osb", true);
        }
        break;
    case 'n':   // move clip plane 0 opposite to the normal direction of the plane
        {
            val0 -= 0.2f;
            vecClipPlaneData[0]._equation[3] = val0;
            mgr->updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'm':   // move clip plane 0 in the normal direction of the plane
        {
            val0 += 0.2f;
            vecClipPlaneData[0]._equation[3] = val0;
            mgr->updateClipPlanes(vecClipPlaneData);
        }
        break;
    case ',':   // move clip plane 1 opposite to the normal direction of the plane
        {
            val1 -= 0.2f;
            vecClipPlaneData[1]._equation[3] = val1;
            mgr->updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '.':   // move clip plane 1 in the normal direction of the plane
        {
            val1 += 0.2f;
            vecClipPlaneData[1]._equation[3] = val1;
            mgr->updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'q':   // move box in -x direction
        {
            x1 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'w':   // move box in +x direction
        {
            x1 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'a':   // move box in -y direction
        {
            y1 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 's':   // move box in +y direction
        {
            y1 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'y':   // move box in -z direction
        {
            z1 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'x':   // move box in +z direction
        {
            z1 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'e':   // move torus in -x direction
        {
            x2 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'r':   // move torus in +x direction
        {
            x2 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'd':   // move torus in -y direction
        {
            y2 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'f':   // move torus in +y direction
        {
            y2 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'c':   // move torus in -z direction
        {
            z2 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'v':   // move torus in +z direction
        {
            z2 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;

    case 'p':   // create a png from scene with the graphviz tool output 
        {
            create_and_exe_dot_file(mgr->getInternalRoot());
        }
        break;

    case 27:
        {
            cleanup();

            OSG::osgExit();
            exit(0);
        }
        break;
    }

    glutPostRedisplay();
}

//----- doMain ----------------------------------------------------------------

int doMain(int argc, char **argv)
{
    //
    // This might be necessary depending on the
    // used platform to ensure that the corresponding
    // libraries get loaded.
    //
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    OSG::preloadSharedObject("OSGContribPLY");

    OSG::osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);

    glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    OSG::PassiveWindowRefPtr pwin=OSG::PassiveWindow::create();
    pwin->init();

    // create the SimpleSceneManager helper
    OSG::SimpleSceneManagerRefPtr simple_mgr = OSG::SimpleSceneManager::create();

    // create the window and initial camera/viewport
    simple_mgr->setWindow(pwin);

    // and the clipplane extension
    mgr = ClippingSceneManager::create(simple_mgr);

    //
    // The scene
    //
    OSG::NodeUnrecPtr scene = makeNodeFor(OSG::Group::create());
    scene->setCore(OSG::Group::create());

    // tell the manager what to manage
    mgr->setRoot(scene);

    //
    // A place for accessing the box and torus.
    //
    vecGeometries.push_back(NULL);
    vecGeometries.push_back(NULL);

    //
    // Build concrete clipping planes and update the clip plane details.
    //
    ClipPlaneData data1;
    ClipPlaneData data2;

    data1._equation = OSG::Vec4f(0,0,1,0);
    data1._enabled  = true;

    data2._equation = OSG::Vec4f(1,0,0,0);
    data2._enabled  = false;

    vecClipPlaneData.push_back(data1);
    vecClipPlaneData.push_back(data2);

    keyboard('3',-1,-1);
    keyboard('4',-1,-1);

    mgr->updateClipPlanes(vecClipPlaneData);

    // show the whole scene
    mgr->showAll();
    mgr->redraw();

    pwin->dumpExtensions();

    return 0;
}

//----- main ------------------------------------------------------------------

int main(int argc, char *argv[])
{
    doMain(argc, argv);

    // GLUT main loop
    glutMainLoop();

    //
    // Clean up the global held data
    //
    cleanup();

    OSG::osgExit();

    return 0;
}
