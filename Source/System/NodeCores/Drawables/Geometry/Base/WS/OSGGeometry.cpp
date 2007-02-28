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

#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGeometry.h"
#include "OSGGeoImmediatePumpGroup.h"

#include <OSGAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>
#include <OSGDrawEnv.h>

//#include <OSGIntersectActor.h>

#include "OSGTriangleIterator.h"
#include "OSGPrimitiveIterator.h"
#include "OSGFaceIterator.h"
#include "OSGLineIterator.h"
#include "OSGEdgeIterator.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeometryBase.cpp file.
// To modify it, please change the .fcd file (OSGGeometry.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

Geometry::PumpGroupStorage Geometry::_pumps;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Geometry::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Geometry::intersect));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionHandler));
    }
}


/*! A little helper function to map the OpenGL primitive type to a name.
*/
const char *Geometry::mapType(UInt8 type)
{
    switch(type)
    {
    case GL_POINTS:         return "Points";
    case GL_LINES:          return "Lines";
    case GL_LINE_LOOP:      return "LineLoop";
    case GL_LINE_STRIP:     return "LineStrip";
    case GL_TRIANGLES:      return "Triangles";
    case GL_TRIANGLE_STRIP: return "TriangleStrip";
    case GL_TRIANGLE_FAN:   return "TriangleFan";
    case GL_QUADS:          return "Quads";
    case GL_QUAD_STRIP:     return "QuadStrip";
    case GL_POLYGON:        return "Polygon";
    }

    return "Unknown Primitive";
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Geometry::Geometry(void) :
    Inherited()
{
}

Geometry::Geometry(const Geometry &source) :
    Inherited(source)
{
}

Geometry::~Geometry(void)
{
    UInt16 i;

    if(getClassicGLId() > 0)
        Window::destroyGLObject(getClassicGLId(), 1);
    if(getAttGLId() > 0)
        Window::destroyGLObject(getAttGLId(), 1);
}

void Geometry::onCreate(const Geometry *)
{
    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

    GeometryPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    setClassicGLId(
        Window::registerGLObject(
            boost::bind(&Geometry::handleClassicGL, tmpPtr, _1, _2),
            1));

    setAttGLId(
        Window::registerGLObject(
            boost::bind(&Geometry::handleAttGL, tmpPtr, _1, _2),
            1));
}

/*------------------------------ access -----------------------------------*/

void Geometry::adjustVolume(Volume & volume)
{
    volume.setValid();
    volume.setEmpty();

    GeoVectorPropertyPtr pos = getPositions();

    if(pos == NullFC)
        return;                  // Node has no points, no volume

    Pnt3f p;

    PrimitiveIterator it,end = this->endPrimitives();

    for(it = this->beginPrimitives(); it != end; ++it)
    {
        for(UInt32 v=0; v < it.getLength(); ++v)
        {
            volume.extendBy(it.getPosition(v));
        }
    }
}


/*! OpenGL object handler. Used for DisplayList caching.
*/
void Geometry::handleClassicGL(DrawEnv *pEnv, UInt32 idstatus)
{
    Window::GLObjectStatusE  mode;
    UInt32                   id;
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            glid = glGenLists(1);
            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        glNewList(glid, GL_COMPILE);

        GeoPumpGroup::PropertyCharacteristics prop;

        prop = GeoPumpGroup::characterizeGeometry(this);

        GeoPumpGroup::GeoPump pump;

        pump = GeoPumpGroup::findGeoPump(pEnv, prop);

        if (pump)
        {
            pump(pEnv, this);
        }
        else
        {
            SWARNING << "Geometry::handleGL: no Pump found for geometry "
                     << this
                     << std::endl;
        }

        glEndList();
    }
    else if(mode == Window::destroy)
    {
        glid = pWin->getGLObjectId(id);

        glDeleteLists(glid, 1);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry(" << this << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

}
void Geometry::handleAttGL(DrawEnv *pEnv, UInt32 idstatus)
{
    Window::GLObjectStatusE  mode;
    UInt32                   id;
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            glid = glGenLists(1);
            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        glNewList(glid, GL_COMPILE);

        GeoPumpGroup::PropertyCharacteristics prop;

        prop = GeoPumpGroup::characterizeGeometry(this);
        prop |= GeoPumpGroup::UsesShader;

        GeoPumpGroup::GeoPump pump;

        pump = GeoPumpGroup::findGeoPump(pEnv, prop);

        if (pump)
        {
            pump(pEnv, this);
        }
        else
        {
            SWARNING << "Geometry::handleGL: no Pump found for geometry "
                     << this
                     << std::endl;
        }

        glEndList();
    }
    else if(mode == Window::destroy)
    {
        glid = pWin->getGLObjectId(id);

        glDeleteLists(glid, 1);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry(" << this << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

}

Action::ResultE Geometry::drawPrimitives(DrawEnv *pEnv)
{
    // !!! HACK this needs to be decided by the used material/state
    bool usesShader = false;

    // store glColor.
    Color4f color;

    if(getColors() != NullFC)
        glGetFloatv(GL_CURRENT_COLOR, color.getValuesRGBA());

    if(getDlistCache() == true)
    {
        Int32 glid;

        if(usesShader)
        {
            glid = getAttGLId();
        }
        else
        {
            glid = getClassicGLId();
        }

        pEnv->getWindow()->validateGLObject(glid, pEnv);
        glCallList(pEnv->getWindow()->getGLObjectId(glid));
    }
    else
    {
        GeoPumpGroup::PropertyCharacteristics prop;

        prop = GeoPumpGroup::characterizeGeometry(this);

        if(usesShader)
            prop |= GeoPumpGroup::UsesShader;

        GeoPumpGroup::GeoPump pump;
        pump = GeoPumpGroup::findGeoPump(pEnv, prop);

        if (pump)
        {
            pump(pEnv, this);
        }
        else
        {
            SWARNING << "Geometry::drawPrimitives: no Pump found for geometry "
                     << this
                     << std::endl;
        }
    }

    // restore glColor.
    if(getColors() != NullFC)
        glColor4fv(color.getValuesRGBA());

/*
    StatCollector *coll = action->getStatistics();

    if(coll != NULL)
    {
        StatIntElem *el = coll->getElem(Drawable::statNTriangles,false);
        if(el)
        {
            GeometryPtr geo(this);
            UInt32 ntri,nl,np,is;

            calcPrimitiveCount(geo, ntri, nl, np);
            el->add(ntri);
            coll->getElem(Drawable::statNLines)->add(nl);
            coll->getElem(Drawable::statNLines)->add(np);

            if(getIndices() == NullFC)
            {
                if(getPositions() != NullFC)
                {
                    is = getPositions()->getSize();
                }
                else
                {
                    is = 0;
                }
            }
            else
            {
                is = getIndexMapping().size();
                is = getIndices()->getSize() /(is ? is : 1);
            }
            coll->getElem(Drawable::statNVertices)->add(is);
        }
    }
*/
    return Action::Continue;
}

/*! The IntersectAction callback for Geometry. It computes if the ray used in
    the IntersectAction \a action hits this object and if that is the case,
    which triangle is hit.

    \param[in] action IntersectAction performing the intersect test.
    \return Action result code, \see OSG::Action.

    \note This method is registered with the IntersectAction and automatically
    called from there, you probably never have to call it manually.
*/
Action::ResultE Geometry::intersect(Action * action)
{
    IntersectAction      *ia = dynamic_cast<IntersectAction*>(action);
    ia->getActNode()->updateVolume();
    const DynamicVolume  &dv = ia->getActNode()->getVolume();

    if(dv.isValid() && !dv.intersect(ia->getLine()))
    {
        return Action::Skip; //bv missed -> can not hit children
    }

    TriangleIterator it  = this->beginTriangles();
    TriangleIterator end = this->endTriangles  ();
    Real32           t;
    Vec3f            norm;

    for(; it != end; ++it)
    {
        if(ia->getLine().intersect(it.getPosition(0),
                                   it.getPosition(1),
                                   it.getPosition(2), t, &norm))
        {
            ia->setHit(t, ia->getActNode(), it.getIndex(), norm);
        }
    }

    return Action::Continue;
}

/*----------------------------- class specific ----------------------------*/

void Geometry::changed(ConstFieldMaskArg whichField, UInt32 origin)
{

    // invalidate the dlist cache
    if(getDlistCache())
    {
        GeometryPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

        if(getClassicGLId() == 0)
        {
            setClassicGLId(
                Window::registerGLObject(
                    boost::bind(&Geometry::handleClassicGL, tmpPtr, _1, _2),
                    1));
        }
        if(getAttGLId() == 0)
        {
            setAttGLId(
                Window::registerGLObject(
                    boost::bind(&Geometry::handleAttGL, tmpPtr, _1, _2),
                    1));
        }

        Window::refreshGLObject(getClassicGLId());
        Window::refreshGLObject(getAttGLId());
    }
    else
    {
        if(getClassicGLId() != 0)
        {
            Window::destroyGLObject(getClassicGLId(), 1);
            setClassicGLId(0);
        }
        if(getAttGLId() != 0)
        {
            Window::destroyGLObject(getAttGLId(), 1);
            setAttGLId(0);
        }
    }

    Inherited::changed(whichField, origin);
}

void Geometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Geometry NI" << std::endl;
}

UInt32 Geometry::indexOccurrence(GeoIntegralPropertyPtrConstArg value)
{
    UInt32 returnValue = 0;

    for(UInt32 i = 0; i < _mfPropIndices.size(); ++i)
    {
        if(_mfPropIndices[i] != NullFC && _mfPropIndices[i] == value)
        {
            ++returnValue;
        }
    }

    return returnValue;
}


// Iterators


/*-------------------------- Primitive Iterator --------------------------------*/

/*! Return a PrimitiveIterator poiting to the beginning of the Geometry.
*/
PrimitiveIterator Geometry::beginPrimitives(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    PrimitiveIterator it(tmpPtr);

    it.setToBegin();

    return it;
}

/*! Return a PrimitiveIterator poiting to the end of the Geometry.
*/
PrimitiveIterator Geometry::endPrimitives(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    PrimitiveIterator it(tmpPtr);

    it.setToEnd();

    return it;
}

/*! Return a TriangleIterator poiting to the beginning of the Geometry.
*/
TriangleIterator Geometry::beginTriangles(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    TriangleIterator it(tmpPtr);

    it.setToBegin();

    return it;
}

/*! Return a TriangleIterator poiting to the end of the Geometry.
*/
TriangleIterator Geometry::endTriangles(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    TriangleIterator it(tmpPtr);

    it.setToEnd();

    return it;
}

/*! Return a FaceIterator poiting to the beginning of the Geometry.
*/
FaceIterator Geometry::beginFaces(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    FaceIterator it(tmpPtr);

    it.setToBegin();

    return it;
}

/*! Return a FaceIterator poiting to the end of the Geometry.
*/
FaceIterator Geometry::endFaces(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    FaceIterator it(tmpPtr);

    it.setToEnd();

    return it;
}

/*! Return a LineIterator poiting to the beginning of the Geometry.
*/
LineIterator Geometry::beginLines(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    LineIterator it(tmpPtr);

    it.setToBegin();

    return it;
}

/*! Return a LineIterator poiting to the end of the Geometry.
*/
LineIterator Geometry::endLines(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    LineIterator it(tmpPtr);

    it.setToEnd();

    return it;
}

/*! Return a EdgeIterator poiting to the beginning of the Geometry.
*/
EdgeIterator Geometry::beginEdges(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    EdgeIterator it(tmpPtr);

    it.setToBegin();

    return it;
}

/*! Return a EdgeIterator poiting to the end of the Geometry.
*/
EdgeIterator Geometry::endEdges(void) const
{
    GeometryConstPtr tmpPtr = Inherited::constructPtr<Geometry>(this);

    EdgeIterator it(tmpPtr);

    it.setToEnd();

    return it;
}
