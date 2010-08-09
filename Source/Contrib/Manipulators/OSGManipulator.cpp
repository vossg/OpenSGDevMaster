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
#include "OSGBaseFunctions.h"
#include "OSGSimpleMaterial.h"
#include "OSGTransform.h"
#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"
#include "OSGWindow.h"
#include "OSGNameAttachment.h"
#include "OSGCamera.h"

#include "OSGManipulator.h"
#include "OSGSimpleGeometryExt.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Manipulator
Baseclass for all Manipulators
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

//! initialize the static features of the class, e.g. action callbacks

void Manipulator::initMethod(InitPhase)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Manipulator::Manipulator(void) :
    Inherited(),
    _activeParent( NULL ),
    _externalUpdateHandler( NULL )
{
}

Manipulator::Manipulator(const Manipulator &source) :
    Inherited(source)
{
    //TODO: empty copy constructor?!?!?!?
}

Manipulator::~Manipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Manipulator::setExternalUpdateHandler(ExternalUpdateHandler* h)
{
    _externalUpdateHandler = h;
}

void Manipulator::callExternalUpdateHandler()
{
    if ( NULL != _externalUpdateHandler )
    {
        _externalUpdateHandler->update(this->getTarget());
    }
}

//! react to field changes

void Manipulator::changed(ConstFieldMaskArg whichField,
                          UInt32            origin,
                          BitVector         details    )
{
    Inherited::changed(whichField, origin, details);

    if ( (whichField & TargetFieldMask) == TargetFieldMask )
    {
        reverseTransform();
    }
    else if ( (whichField & ParentsFieldMask) == ParentsFieldMask )
    {
        Node *parent;

        if ( !getParents().empty() )
        {
            //std::cout << "parent size= " << parents.getSize() << std::endl;
            parent = dynamic_cast<Node *>(getParents()[0]); // Dangerous! multiple parents?
        }
        else
        {
            parent = NULL;
        }

        //std::cout << "  Parent=       " << parent << std::endl;
        //std::cout << "  activeParent= " << _activeParent << std::endl;

        if ( parent != _activeParent )
        {
            if ( NULL != parent )
            {
                // remove old childs from a loaded osb file.
                while(parent->getNChildren() > 0)
                {
                    parent->subChild(parent->getChild(0));
                }
                addHandleGeo(parent);
            }

            if ( _activeParent != NULL )
            {
                subHandleGeo(_activeParent);
            }

            _activeParent = parent;
        }
    }
}

void Manipulator::addHandleGeo(Node *n)
{
    n->addChild(getTransXNode());
    n->addChild(getTransYNode());
    n->addChild(getTransZNode());
    n->addChild(getAxisLinesN());
}

void Manipulator::subHandleGeo(Node *n)
{
    n->subChild(getTransXNode());
    n->subChild(getTransYNode());
    n->subChild(getTransZNode());
    n->subChild(getAxisLinesN());
}

void Manipulator::reverseTransform()
{
    if ( getTarget() != NULL )
    {
        Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());
        Matrix     m,n,o;

        Vec3f      translation;
        Quaternion rotation;
        Vec3f      scaleFactor;
        Quaternion scaleOrientation;

        m = t->getMatrix();
        m.getTransform(translation, rotation, scaleFactor, scaleOrientation);

        if( false == o.invertFrom(m) )
        {
            SWARNING << "Matrix is SINGULAR!!!\n";
        }
        else
        {
            n.setIdentity (           );
            n.setTransform(translation);
            n.setRotate   (rotation   );
            n.multLeft    (o          );

            setMatrix(n);
        }
    }
}

//! output the instance for debug purposes

void Manipulator::dump(      UInt32    ,
                       const BitVector ) const
{
    SLOG << "Dump Manipulator NI" << std::endl;
}

void Manipulator::onCreate()
{
}

void Manipulator::onCreate(const Manipulator* source)
{
    Inherited::onCreate(source);

    SimpleMaterialUnrecPtr pMat = SimpleMaterial::create();

    setMaterialX(pMat);

    pMat = SimpleMaterial::create();

    setMaterialY(pMat);

    pMat = SimpleMaterial::create();

    setMaterialZ(pMat);

    SimpleMaterial *simpleMat;
    Geometry       *geo;

    setExternalUpdateHandler(NULL);

    // add a name attachment
    NameUnrecPtr nameN = Name::create();
    nameN->editFieldPtr()->setValue("XManipulator");
    addAttachment(nameN);

    // make the axis lines
    NodeUnrecPtr pNode = makeCoordAxis(getLength()[0], 2.0, false);
    setAxisLinesN(pNode);

    // make the red x-axis transform and handle

    pNode = Node::create();
    setTransXNode(pNode);
    OSG::ComponentTransformUnrecPtr transHandleXC = ComponentTransform::create();

    pNode = makeHandleGeo();
    setHandleXNode(pNode);
    pMat = SimpleMaterial::create();
    setMaterialX  (pMat );

    getTransXNode()->setCore (transHandleXC   );
    getTransXNode()->addChild(getHandleXNode());

    transHandleXC->setTranslation(Vec3f(getLength()[0], 0, 0)                   );
    transHandleXC->setRotation   (Quaternion(Vec3f(0, 0, 1), osgDegree2Rad(-90)));

    simpleMat = dynamic_cast<SimpleMaterial *>(getMaterialX());

    simpleMat->setDiffuse(Color3f(1, 0, 0));
    simpleMat->setLit    (true            );

    geo = dynamic_cast<Geometry *>(getHandleXNode()->getCore());
    geo->setMaterial(simpleMat);

    //
    // make the green y-axis transform and handle

    pNode = Node::create();
    setTransYNode(pNode);
    OSG::ComponentTransformUnrecPtr transHandleYC = ComponentTransform::create();
    pNode = makeHandleGeo();
    setHandleYNode(pNode);
    pMat = SimpleMaterial::create();
    setMaterialY(pMat);

    getTransYNode()->setCore (transHandleYC   );
    getTransYNode()->addChild(getHandleYNode());

    transHandleYC->setTranslation(Vec3f(0, getLength()[1], 0)                    );
//    transHandleYC->setRotation   ( Quaternion(Vec3f(0, 0, 1), osgDegree2Rad(-90)));

    simpleMat = dynamic_cast<SimpleMaterial *>(getMaterialY());
    simpleMat->setDiffuse(Color3f(0, 1, 0));
    simpleMat->setLit    (true            );

    geo = dynamic_cast<Geometry *>(getHandleYNode()->getCore());
    geo->setMaterial(simpleMat);

    //
    // make the blue z-axis transform and handle

    pNode = Node::create();
    setTransZNode(pNode);
    OSG::ComponentTransformUnrecPtr transHandleZC = ComponentTransform::create();
    pNode = makeHandleGeo();
    setHandleZNode(pNode);
    pMat = SimpleMaterial::create();
    setMaterialZ  (pMat);

    getTransZNode()->setCore (transHandleZC   );
    getTransZNode()->addChild(getHandleZNode());

    transHandleZC->setTranslation(Vec3f(0, 0, getLength()[2])                  );
    transHandleZC->setRotation   (Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(90)));

    simpleMat = dynamic_cast<SimpleMaterial *>(getMaterialZ());
    simpleMat->setDiffuse(Color3f(0, 0, 1));
    simpleMat->setLit    (true            );

    geo = dynamic_cast<Geometry *>(getHandleZNode()->getCore());
    geo->setMaterial(simpleMat);

    commitChanges();
}

void Manipulator::onDestroy()
{
}

void Manipulator::resolveLinks(void)
{
    Inherited::resolveLinks();

    _activeParent  = NULL;
}

Pnt2f Manipulator::calcScreenProjection(const Pnt3f    &       p,
                                              Viewport * const port)
{
    Camera  *cam;
    Matrix   proj, projtrans, view;
    Pnt3f    pnt;

    if( port != NULL )
    {
        cam = port->getCamera();

        cam->getProjection(proj, port->getPixelWidth(),
                           port->getPixelHeight());
        cam->getProjectionTranslation(projtrans, port->getPixelWidth(),
                                      port->getPixelHeight());
        cam->getViewing(view, port->getPixelWidth(), port->getPixelHeight());

        Matrix wctocc = proj;
        wctocc.mult(projtrans);
        wctocc.mult(view);

        wctocc.multFull(p, pnt);

        Real32 rx = (pnt[0] + 1.0) /2 * port->getPixelWidth();
        Real32 ry = (pnt[1] + 1.0) /2 * port->getPixelHeight();

        return Pnt2f(rx, ry);
    }
    else
    {
        SWARNING << "calcScreenProjection(const Pnt3f&, "
                    "Viewport * const port="
                 << port << ")\n";
        return Pnt2f(0.0f, 0.0f);
    }
}

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void Manipulator::mouseMove(const Int16 x,
                            const Int16 y)
{
    //SLOG << "Manipulator::mouseMove() enter\n" << std::flush;

    // get the beacon's core (must be ComponentTransform) and it's center
    if( getTarget() != NULL )
    {
        // get transformation of beacon
        Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());

        if( t != NULL )
        {
            UInt16     coord(0);          // active coordinate: X=0, Y=1, Z=2

            Int16      xDiff;             // the mousepos x delta
            Int16      yDiff;             // the mousepos y delta

            Vec3f      centerV;           // center of beacon
            Vec3f      handleCenterV;     // center of subhandle
            Vec2f      mouseScreenV;      // mouse move vector
            Vec2f      handleScreenV;     // handle vec in (cc)
            Real32     handleScreenVLen;  // len of handle vec in (cc)

            Vec3f      translation;       // for matrix decomposition
            Quaternion rotation;
            Vec3f      scaleFactor;
            Quaternion scaleOrientation;

            // TODO: das ist ja schon ein wenig haesslich
            static const Vec3f coordVector[3] = {
                Vec3f(1.0f, 0.0f, 0.0f),
                Vec3f(0.0f, 1.0f, 0.0f),
                Vec3f(0.0f, 0.0f, 1.0f)
            };

            //  check for the active handle
            if(     getActiveSubHandle() == getHandleXNode())
            {
                coord = 0;
            }
            else if(getActiveSubHandle() == getHandleYNode())
            {
                coord = 1;
            }
            else if(getActiveSubHandle() == getHandleZNode())
            {
                coord = 2;
            }

            // TODO: only for debugging, -> FDEBUG
            //SLOG << "moving " << ( coord == 0 ? "x\n" :
            //                       coord == 1 ? "y\n" :
            //                       "z\n" )
            //     << std::flush;

            // calculate diffs between current and last mouse position
            xDiff = x - Int16(getLastMousePos()[0]);
            yDiff = y - Int16(getLastMousePos()[1]);

            // set the vector resulting from user mouse movement and calc its length
            mouseScreenV.setValues(xDiff, -yDiff);

            t->getMatrix().getTransform(translation, rotation, scaleFactor,
                                        scaleOrientation);


            // calculate the camera coordinate of the center
            centerV            = translation;
            Pnt2f centerPixPos = calcScreenProjection(centerV.addToZero(),
                                                      getViewport());


            // calculate the camera coordinate of the handle center
            handleCenterV            = centerV + coordVector[coord]*getLength()[coord];
            Pnt2f handleCenterPixPos = calcScreenProjection(handleCenterV.addToZero(),
                                                            getViewport());

            handleScreenV    = handleCenterPixPos - centerPixPos;
            handleScreenVLen = handleScreenV.length();

            Real32 s = handleScreenV.dot(mouseScreenV) / handleScreenVLen;

            doMovement(t, coord, s * getLength()[coord] * 0.01, translation,
                       rotation, scaleFactor, scaleOrientation);
        }
        else
        {
            SWARNING << "handled object has no parent transform!\n";
        }
        callExternalUpdateHandler();
    }
    else
    {
        SWARNING << "Handle has no target.\n";
    }

    setLastMousePos(Pnt2f(Real32(x), Real32(y)));
    reverseTransform();

    //SLOG << "Manipulator::mouseMove() leave\n" << std::flush;
}

/*! The mouseButtonPress is called by the viewer when the mouse is
    pressed in the viewer above a subhandle of this handle.

    \param button the button pressed
    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */

void Manipulator::mouseButtonPress(const UInt16 button,
                                   const Int16  x,
                                   const Int16  y     )
{
    setLastMousePos(Pnt2f(Real32(x), Real32(y)));
    setActive(true);
}

void Manipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
    setActive(false);
}
