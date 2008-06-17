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
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"

#if 0
#include "OSGGeoImmediatePumpGroup.h"
#endif

#include <OSGAction.h>
#include <OSGRenderAction.h>
//#include <OSGIntersectAction.h>
#include <OSGDrawEnv.h>
#if 0
//#include <OSGIntersectActor.h>

#include "OSGFaceIterator.h"
#include "OSGLineIterator.h"
#include "OSGEdgeIterator.h"
#endif
#include "OSGTriangleIterator.h"
#include "OSGPrimitiveIterator.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGeometryBase.cpp file.
// To modify it, please change the .fcd file (OSGGeometry.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

#if 0
Geometry::PumpGroupStorage Geometry::_pumps;
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Geometry::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
#if 0
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Geometry::intersect));
#endif

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionHandler));
    }
}


/*! A little helper function to map the OpenGL primitive type to a name.
*/
#if 0
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
#endif

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

// This shoudl go into Attachment
void Geometry::freeParent(FieldContainerAttachmentPtr value,
                          FieldContainerPtr           obj)
{
    if(value != NullFC)
    {
        value->subParent(obj);

        subRef(value);
    }
}

Geometry::~Geometry(void)
{
}

void Geometry::onCreate(const Geometry *)
{
    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

    setClassicGLId(
        Window::registerGLObject(
            boost::bind(&Geometry::handleClassicGL, this, _1, _2, _3),
            &Geometry::handleClassicDestroyGL));

    setAttGLId(
        Window::registerGLObject(
            boost::bind(&Geometry::handleAttGL, this, _1, _2, _3),
            &Geometry::handleAttDestroyGL));
}

void Geometry::onDestroy(UInt32)
{
    if(getClassicGLId() > 0)
        Window::destroyGLObject(getClassicGLId(), 1);
    if(getAttGLId() > 0)
        Window::destroyGLObject(getAttGLId(), 1);
}

/*------------------------------ access -----------------------------------*/

void Geometry::adjustVolume(Volume & volume)
{
    volume.setValid();
    volume.setEmpty();

#if 0
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
#endif

}


/*! OpenGL object handler. Used for DisplayList caching.
*/
void Geometry::handleClassicGL(DrawEnv                 *pEnv, 
                               UInt32                   id, 
                               Window::GLObjectStatusE  mode)
{
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

#if 0
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
    else
    {
        SWARNING << "Geometry(" << this << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

#endif
}

void Geometry::handleClassicDestroyGL(DrawEnv                 *pEnv, 
                                      UInt32                   id, 
                                      Window::GLObjectStatusE  mode)
{
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

#if 0
    if(mode == Window::destroy)
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
        SWARNING << "Geometry::handleClassicDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

void Geometry::handleAttGL(DrawEnv                 *pEnv, 
                           UInt32                   id, 
                           Window::GLObjectStatusE  mode)
{
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

#if 0
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
    else
    {
        SWARNING << "Geometry(" << this << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

void Geometry::handleAttDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode)
{
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

#if 0
    if(mode == Window::destroy)
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
        SWARNING << "Geometry::handleAttDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

Action::ResultE Geometry::drawPrimitives(DrawEnv *pEnv)
{
    // !!! HACK this needs to be decided by the used material/state
    bool usesShader = false;    

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_NORMAL_ARRAY);

    GeoIntegralPropertyPtr pTypes   = this->getTypes  ();
    GeoIntegralPropertyPtr pLengths = this->getLengths();
    GeoIntegralPropertyPtr pIdx     = this->getIndex  (PositionsIndex);
    
    GeoVectorPropertyPtr pPos   = this->getProperty(PositionsIndex);
    GeoVectorPropertyPtr pNorms = this->getProperty(NormalsIndex  );

	glVertexPointer(3, 
                    GL_FIXED, 
                    pPos->getStride(), 
                    pPos->getData  ());
	glNormalPointer(GL_FIXED,    
                    pNorms->getStride(), 
                    pNorms->getData  ());

    GeoUInt16PropertyPtr index = dynamic_cast<GeoUInt16PropertyPtr>(pIdx    ); 
    GeoUInt16PropertyPtr lens  = dynamic_cast<GeoUInt16PropertyPtr>(pLengths); 
    GeoUInt8PropertyPtr  types = dynamic_cast<GeoUInt8PropertyPtr >(pTypes  ); 
    
    const GeoUInt16Property::StoredFieldType *idx  = index->getFieldPtr();
    const GeoUInt16Property::StoredFieldType *len  = lens ->getFieldPtr();
    const GeoUInt8Property ::StoredFieldType *typ  = types->getFieldPtr();

    UInt32 uiSize    = len->size();
    UInt32 uiCurrIdx = 0;

    if(typ->size() < uiSize)
    {
        uiSize = typ->size();
    }

    for(UInt32 i = 0; i  < uiSize; ++i)
    {
        glDrawElements((*typ)[i], 
                       (*len)[i], 
                       GL_UNSIGNED_SHORT, 
                       &((*idx)[uiCurrIdx]));

        uiCurrIdx += (*len)[i];
    }

	glDisableClientState (GL_VERTEX_ARRAY);
	glDisableClientState (GL_NORMAL_ARRAY);

#if 0    
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
#endif
    return Action::Continue;
}


Action::ResultE Geometry::intersect(Action * action)
{
#if 0
/*
    IntersectAction  *ia = dynamic_cast<IntersectAction*>(action);
    const BoxVolume  &bv = ia->getActNode()->getVolume(true);

    if(bv.isValid() && !bv.intersect(ia->getLine()))
    {
        return Action::Skip; //bv missed -> can not hit children
    }

    TriangleIterator it  = this->beginTriangles();
    TriangleIterator end = this->endTriangles  ();
    Real32 t;
    Vec3f norm;

    for(; it != end; ++it)
    {
        if(ia->getLine().intersect(it.getPosition(0),
                                     it.getPosition(1),
                                     it.getPosition(2), t, &norm))
        {
            ia->setHit(t, ia->getActNode(), it.getIndex(), norm);
        }
    }
*/
#endif

    return Action::Continue;
}

/*----------------------------- class specific ----------------------------*/

void Geometry::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
#if 0
    // invalidate the dlist cache
    if(getDlistCache())
    {
        if(getClassicGLId() == 0)
        {
            setClassicGLId(
                Window::registerGLObject(
                    boost::bind(&Geometry::handleClassicGL, this, _1, _2),
                    1));
        }
        if(getAttGLId() == 0)
        {
            setAttGLId(
                Window::registerGLObject(
                    boost::bind(&Geometry::handleAttGL, this, _1, _2),
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
#endif

    Inherited::changed(whichField, origin, details);
}

void Geometry::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Geometry NI" << std::endl;
}

// Iterators

/*-------------------------- Primitive Iterator --------------------------------*/

/*! Return a PrimitiveIterator poiting to the beginning of the Geometry.
*/
PrimitiveIterator Geometry::beginPrimitives(void) const
{
    PrimitiveIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a PrimitiveIterator poiting to the end of the Geometry.
*/
PrimitiveIterator Geometry::endPrimitives(void) const
{
    PrimitiveIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a TriangleIterator poiting to the beginning of the Geometry.
*/
TriangleIterator Geometry::beginTriangles(void) const
{
    TriangleIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a TriangleIterator poiting to the end of the Geometry.
*/
TriangleIterator Geometry::endTriangles(void) const
{
    TriangleIterator it(this);

    it.setToEnd();

    return it;
}
#if 0
/*! Return a FaceIterator poiting to the beginning of the Geometry.
*/
FaceIterator Geometry::beginFaces(void) const
{
    FaceIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a FaceIterator poiting to the end of the Geometry.
*/
FaceIterator Geometry::endFaces(void) const
{
    FaceIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a LineIterator poiting to the beginning of the Geometry.
*/
LineIterator Geometry::beginLines(void) const
{
    LineIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a LineIterator poiting to the end of the Geometry.
*/
LineIterator Geometry::endLines(void) const
{
    LineIterator it(this);

    it.setToEnd();

    return it;
}

/*! Return a EdgeIterator poiting to the beginning of the Geometry.
*/
EdgeIterator Geometry::beginEdges(void) const
{
    EdgeIterator it(this);

    it.setToBegin();

    return it;
}

/*! Return a EdgeIterator poiting to the end of the Geometry.
*/
EdgeIterator Geometry::endEdges(void) const
{
    EdgeIterator it(this);

    it.setToEnd();

    return it;
}
#endif


