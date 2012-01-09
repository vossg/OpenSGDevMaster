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
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

#include "OSGMoveManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MoveManipulator
 * The MoveHandle is used for moving objects. It consist of three axis which
 * can be picked and translated and one center box to translate freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MoveManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MoveManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MoveManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MoveManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MoveManipulator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MoveManipulator::MoveManipulator(void) :
    Inherited()
{
}

MoveManipulator::MoveManipulator(const MoveManipulator &source) :
    Inherited(source)
{
}

MoveManipulator::~MoveManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MoveManipulator::changed(ConstFieldMaskArg whichField,
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MoveManipulator::dump(      UInt32    uiIndent,
                           const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr MoveManipulator::makeHandleGeo()
{
    return makeCone(0.75f, 0.1f, 12, true, true);
}

/*! The mouseMove is called by the viewer when the mouse is moved in the
    viewer and this handle is the active one.

    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */
void MoveManipulator::mouseMove(const Int16 x,
                            const Int16 y)
{
    //SLOG << "==============================" << endLog;
    //SLOG << "Manipulator::mouseMove() enter x=" << x << " y=" << y << endLog;

    // get the beacon's core (must be ComponentTransform) and it's center
    if( getTarget() != NULL )
    {
        // get transformation of beacon
        Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());

        if( t != NULL )
        {
            Vec3f      translation;       // for matrix decomposition
            Quaternion rotation;
            Vec3f      scaleFactor;
            Quaternion scaleOrientation;

            t->getMatrix().getTransform(translation, rotation, scaleFactor,
                                        scaleOrientation);

            OSG::Line viewray;
            getViewport()->getCamera()->calcViewRay(viewray, x, y, *getViewport());
            
            //SLOG << "Manipulator::mouseMove(): viewray: " << viewray << endLog;

            Line axis(getAxisBase(), getAxisDirection()); // HACK: Should add a Line Fieldtype

            //SLOG << "Manipulator::mouseMove(): axis: " << axis << endLog;

            Real32 axist, viewrayt;
            
            axis.getClosestPoints(viewray, axist, viewrayt);
            
            // Only accept cases where the closest point is not behind the viewer
            if (viewrayt >= 0)
            {
                axist /= getAxisDirection().length();

                //SLOG << "Manipulator::mouseMove(): axist=" << axist << " viewrayt=" << viewrayt <<endLog;

                Vec3f rot_axis;

                rotation.multVec(getActiveAxis(), rot_axis);
                Vec3f trans = getBaseTranslation() + rot_axis * axist;

                Matrix m;

                m.setTransform(trans, rotation, scaleFactor, scaleOrientation);

                t->setMatrix(m);
            }
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
    updateHandleTransform();

    //SLOG << "Manipulator::mouseMove() leave\n" << std::flush;
}

/*! The mouseButtonPress is called by the viewer when the mouse is
    pressed in the viewer above a subhandle of this handle.

    \param button the button pressed
    \param x the x-pos of the mouse (pixel)
    \param y the y-pos of the mouse (pixel)
 */

void MoveManipulator::mouseButtonPress(const UInt16 button,
                                   const Int16  x,
                                   const Int16  y     )
{
    Transform *t = dynamic_cast<Transform *>(getTarget()->getCore());
    
    if (t == NULL)
    {
        SWARNING << "Manipulator::mouseButtonPress() target is not a Transform!" << endLog;
        return;
    }

    //SLOG << "Manipulator::mouseButtonPress() button=" << button << " x=" << x << " y=" << y  << std::endl << endLog;

    OSG::Line viewray;
    getViewport()->getCamera()->calcViewRay(viewray, x, y, *getViewport());

    OSG::Node *scene = getTarget();
    while (scene->getParent() != 0)
    {
        scene = scene->getParent();
    }

    OSG::IntersectActionRefPtr act = OSG::IntersectAction::create();
    act->setLine( viewray );
    act->apply( scene );

    //SLOG << "Manipulator::mouseButtonPress() viewray=" << viewray << " scene=" << scene << endLog;
 
    if ( act->didHit() )
    {
        //SLOG << "Manipulator::mouseButtonPress() hit! at " << act->getHitPoint() << endLog;

        // Get manipulator axis into world space
        OSG::Matrix m = getTarget()->getToWorld();

        Pnt3f origin(0,0,0), base, dummy;
        Vec3f dir;

        m.multFull(origin, base);
        m.multFull(getActiveAxis(), dir);

        Line axis(base, dir);
        
        //SLOG << "Manipulator::mouseButtonPress() world axis=" << axis << endLog;

        Pnt3f apoint;
        axis.getClosestPoints(viewray, apoint, dummy);

        //SLOG << "Manipulator::mouseButtonPress() apoint " << apoint << endLog;
   
        setAxisBase(apoint);
        setAxisDirection(dir);

        Vec3f      translation;       // for matrix decomposition
        Quaternion rotation;
        Vec3f      scaleFactor;
        Quaternion scaleOrientation;

        t->getMatrix().getTransform(translation, rotation, scaleFactor,
                                    scaleOrientation);

        setBaseTranslation(translation);
        
        setActive(true);
    }

    act = NULL;
}

void MoveManipulator::mouseButtonRelease(const UInt16 button,
                                     const Int16  x,
                                     const Int16  y     )
{
    //SLOG << "Manipulator::mouseButtonRelease() button=" << button << " x=" << x << " y=" << y  << std::endl << endLog;
    setActive(false);
}
