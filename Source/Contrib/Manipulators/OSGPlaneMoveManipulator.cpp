/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEMANIPULATORSLIB

#include "OSGConfig.h"
#include "OSGPlane.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"
#include "OSGSimpleMaterial.h"
#include "OSGNameAttachment.h"
#include "OSGGeoBuilder.h"
#include "OSGLineChunk.h"

#include "OSGPlaneMoveManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PlaneMoveManipulator
 * The MoveHandle is used for moving objects. It consist of three axis which
 * can be picked and translated and one center box to translate freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PlaneMoveManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &PlaneMoveManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &PlaneMoveManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&PlaneMoveManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&PlaneMoveManipulator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PlaneMoveManipulator::PlaneMoveManipulator(void) :
    Inherited()
{
}

PlaneMoveManipulator::PlaneMoveManipulator(const PlaneMoveManipulator &source) :
    Inherited(source)
{
}

PlaneMoveManipulator::~PlaneMoveManipulator(void)
{
}

void PlaneMoveManipulator::onCreate()
{
}

void PlaneMoveManipulator::onCreate(const PlaneMoveManipulator* source)
{
    // Skip direct parent, don't want the default geometry creation
    Transform::onCreate(source);

    SimpleMaterialUnrecPtr pMat = SimpleMaterial::create();
    pMat->setDiffuse(Color3f(.5, .5, .5));
    pMat->setLit    (false              );
    setMaterialX(pMat);

    pMat = SimpleMaterial::create();
    pMat->setDiffuse(Color3f(0, 1, 0));
    pMat->setLit    (false           );
    LineChunkUnrecPtr lc = LineChunk::create();
    lc->setWidth(3);
    pMat->addChunk(lc);
    setMaterialY(pMat);

    pMat = SimpleMaterial::create();
    pMat->setDiffuse(Color3f(0., 0., 1.));
    pMat->setLit    (true               );
    setMaterialZ(pMat);

//    SimpleMaterial *simpleMat;
//    Geometry       *geo;

    setExternalUpdateHandler(NULL);

    // add a name attachment
    NameUnrecPtr nameN = Name::create();
    nameN->editFieldPtr()->setValue("XYManipulator");
    addAttachment(nameN);

    // make the axis line. Not really a handle, but easier to manage this way.
       
    GeoBuilder b;
    
    b.vertex(Pnt3f(0,0,0));
    b.vertex(Pnt3f(0,getLength()[1],0));
    
    b.line(0, 1);
    
    GeometryUnrecPtr g = b.getGeometry();
    
    g->setMaterial(getMaterialY());
    
    NodeUnrecPtr pNode = makeNodeFor(g);
    setTransYNode(pNode);

    // make the plane handle

    pNode = Node::create();
    setTransXNode(pNode);

    g = makePlaneGeo(getLength()[0] / 2.f, getLength()[2] / 2.f, 1, 1);
    g->setMaterial(getMaterialX());   
    pNode = makeNodeFor(g);
    
    OSG::ComponentTransformUnrecPtr transHandleXC = ComponentTransform::create();

    setHandleXNode(pNode);

    getTransXNode()->setCore (transHandleXC   );
    getTransXNode()->addChild(getHandleXNode());

    transHandleXC->setTranslation(Vec3f(0, getLength()[1], 0));
    transHandleXC->setRotation   (Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(90)));

    //
    // make the rotate handle

    pNode = Node::create();
    setTransZNode(pNode);

    g = makeCylinderGeo(0.05f, 0.1f, 16, true, true, true);
    g->setMaterial(getMaterialZ());   
    pNode = makeNodeFor(g);
    
    OSG::ComponentTransformUnrecPtr transHandleZC = ComponentTransform::create();

    setHandleZNode(pNode);

    getTransZNode()->setCore (transHandleZC   );
    getTransZNode()->addChild(getHandleZNode());

    transHandleZC->setTranslation(Vec3f(0, getLength()[1], 0));

    commitChanges();
}

/*----------------------------- class specific ----------------------------*/

void PlaneMoveManipulator::changed(ConstFieldMaskArg whichField,
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PlaneMoveManipulator::dump(      UInt32    uiIndent,
                           const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr PlaneMoveManipulator::makeHandleGeo()
{
    return Node::create();
}

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void PlaneMoveManipulator::mouseMove(const Int16 x,
                            const Int16 y)
{
    SLOG << "==============================" << endLog;
    SLOG << "PlaneMoveManipulator::mouseMove() enter x=" << x << " y=" << y << endLog;

    // get the beacon's core (must be ComponentTransform) and it's center
    if( getTarget() == NULL )
    {
        SWARNING << "Handle has no target.\n";
        return;
        
    }
    // get transformation of beacon
    Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());

    if( t == NULL )
    {
        SWARNING << "handled object has no parent transform!\n";
        return;
    }

    Vec3f      translation;       // for matrix decomposition
    Quaternion rotation;
    Vec3f      scaleFactor;
    Quaternion scaleOrientation;

    t->getMatrix().getTransform(translation, rotation, scaleFactor,
                                scaleOrientation);

    OSG::Line viewray;
    getViewport()->getCamera()->calcViewRay(viewray, x, y, *getViewport());

    SLOG << "Manipulator::mouseMove(): viewray: " << viewray << endLog;

    // Get manipulator axes into world space
    OSG::Matrix tm = getTarget()->getToWorld();
    
    Vec3f rot_axis;
    tm.multFull(Vec3f(0,1,0), rot_axis);

    Plane pl(rot_axis, getClickPoint());

    Pnt3f plpoint;
    
    if (pl.intersect(viewray, plpoint) == true) // Ignore moving out of the plane...
    {
        SLOG << "Manipulator::mouseMove(): plpoint: " << plpoint << endLog;
         
        Vec3f      trans = getBaseTranslation();
        Quaternion rot   = getBaseRotation();

        // Get manipulator axes into world space
        Vec3f xp,zp;

        tm.multFull(Vec3f(1,0,0), xp);
        tm.multFull(Vec3f(0,0,1), zp);
        
        if (getActiveSubHandle() == getHandleXNode())
        {
            Line xaxis(getClickPoint(), xp);
            Line zaxis(getClickPoint(), zp);

            Real32 fx = xaxis.getClosestPointT(plpoint);
            Real32 fz = zaxis.getClosestPointT(plpoint);

            SLOG << "Manipulator::mouseMove(): xaxis: " << xaxis << " zaxis: " << zaxis <<endLog;
            SLOG << "Manipulator::mouseMove(): fx: " << fx << " fz: " << fz <<endLog;
        
            // Alternative: transform hitpoint into manip space
            OSG::Matrix m = getTarget()->getToWorld();
            m.invert();
            
            Pnt3f mpoint;
            m.mult(plpoint, mpoint);
            
            SLOG << "Manipulator::mouseMove(): mpoint:" << mpoint << endLog;

            trans = trans + xp * fx + zp * fz;
        }
        else if (getActiveSubHandle() == getHandleZNode())
        {
            Pnt3f wcenter;
            
            tm.multFull(Pnt3f(0,getLength()[1],0), wcenter);
            
            Vec3f vclick, vcurrent;
            
            vclick = getClickPoint() - wcenter;
            vcurrent = plpoint - wcenter;
            
            vclick.normalize();
            vcurrent.normalize();
            
            Real32 a = vclick.enclosedAngle(vcurrent);
            
            SLOG << "Manipulator::mouseMove(): wcenter:" << wcenter << "" <<endLog;
            SLOG << "Manipulator::mouseMove(): vclick:" << vclick << " vcurrent:" << vcurrent <<endLog;
            SLOG << "Manipulator::mouseMove(): angle:" << a << " deg: " << osgRad2Degree(a) << endLog;
        }
        
        Matrix m;

        m.setTransform(trans, rot, scaleFactor, scaleOrientation);

        t->setMatrix(m);
        
    }

    setLastMousePos(Pnt2f(Real32(x), Real32(y)));
    updateHandleTransform();

    //SLOG << "Manipulator::mouseMove() leave\n" << std::flush;
}

/*! The mouseButtonPress is called by the viewer when the mouse is
    pressed in the viewer above a subhandle of this handle.

    \param button the button pressed
    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */

void PlaneMoveManipulator::mouseButtonPress(const UInt16 button,
                                   const Int16  x,
                                   const Int16  y     )
{
    Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());
    
    if (t == NULL)
    {
        SWARNING << "PlaneMoveManipulator::mouseButtonPress() target is not a Transform!" << endLog;
        return;
    }

    SLOG << "PlaneMoveManipulator::mouseButtonPress() button=" << button << " x=" << x << " y=" << y  << std::endl << endLog;

    OSG::Line viewray;
    getViewport()->getCamera()->calcViewRay(viewray, x, y, *getViewport());

    OSG::Node *scene = getTarget();
    while (scene->getParent() != 0)
    {
        scene = scene->getParent();
    }

    OSG::IntersectAction *act = OSG::IntersectAction::create();
    act->setLine( viewray );
    act->apply( scene );

    SLOG << "PlaneMoveManipulator::mouseButtonPress() viewray=" << viewray << " scene=" << scene << endLog;
 
    if ( act->didHit() )
    {
        SLOG << "PlaneMoveManipulator::mouseButtonPress() hit! at " << act->getHitPoint() << endLog;

        // Get manipulator plane into world space
        OSG::Matrix m = getTarget()->getToWorld();

        Vec3f      translation;       // for matrix decomposition
        Quaternion rotation;
        Vec3f      scaleFactor;
        Quaternion scaleOrientation;

        t->getMatrix().getTransform(translation, rotation, scaleFactor,
                                    scaleOrientation);

        Vec3f rot_axis;
        rotation.multVec(Vec3f(0,1,0), rot_axis);

        Plane pl(rot_axis, act->getHitPoint());

        SLOG << "PlaneMoveManipulator::mouseButtonPress() world plane: " << pl << endLog;
 
        setClickPoint(act->getHitPoint());

        setBaseTranslation(translation);
        setBaseRotation(rotation);
        
        setActive(true);
    }

    delete act;
}

void PlaneMoveManipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
    //SLOG << "Manipulator::mouseButtonRelease() button=" << button << " x=" << x << " y=" << y  << std::endl << endLog;
    setActive(false);
}
