/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include <math.h>

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGTriangleIterator.h"
#include "OSGTileGeometryLoad.h"

OSG_USING_NAMESPACE

/** \class osg::TileGeometryLoad
 *  \ingroup Cluster
 *  \brief TileGeometryLoad holds the load caused by geometry rendering
 *
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 */

TileGeometryLoad::TileGeometryLoad(UInt32 nodeId,
                                   bool useFaceDistribution):
    _nodeId(nodeId),
    _faces(0),
    _useFaceDistribution(useFaceDistribution),
    _valid(false)
{
    if(_directions.size()==0)
    {
        // create directions for face distribution
        _directions.push_back(
            Plane(Vec3f( 1, 0, 0)              ,Pnt3f(0,0,0)));
        _directions.push_back(
            Plane(Vec3f( 0, 1, 0)              ,Pnt3f(0,0,0)));
        _directions.push_back(
            Plane(Vec3f( 0, 0, 1)              ,Pnt3f(0,0,0)));

        _directions.push_back(
            Plane(Vec3f( 1, 1, 1)*(1/osgSqrt(3.0f)),Pnt3f(0,0,0)));
        _directions.push_back(
            Plane(Vec3f(-1, 1, 1)*(1/osgSqrt(3.0f)),Pnt3f(1,0,0)));
        _directions.push_back(
            Plane(Vec3f( 1,-1, 1)*(1/osgSqrt(3.0f)),Pnt3f(0,1,0)));
        _directions.push_back(
            Plane(Vec3f( 1, 1,-1)*(1/osgSqrt(3.0f)),Pnt3f(0,0,1)));

        _directions.push_back(
            Plane(Vec3f( 1, 1, 0)*(1/osgSqrt(2.0f)),Pnt3f(0,0,0)));
        _directions.push_back(
            Plane(Vec3f( 1,-1, 0)*(1/osgSqrt(2.0f)),Pnt3f(0,1,0)));
        _directions.push_back(
            Plane(Vec3f( 0, 1, 1)*(1/osgSqrt(2.0f)),Pnt3f(0,0,0)));
        _directions.push_back(
            Plane(Vec3f( 0,-1, 1)*(1/osgSqrt(2.0f)),Pnt3f(0,1,0)));
        _directions.push_back(
            Plane(Vec3f( 1, 0, 1)*(1/osgSqrt(2.0f)),Pnt3f(0,0,0)));
        _directions.push_back(
            Plane(Vec3f(-1, 0, 1)*(1/osgSqrt(2.0f)),Pnt3f(1,0,0)));


    }
    updateGeometry();
}

/*! copy Constructor
 */

TileGeometryLoad::TileGeometryLoad(const TileGeometryLoad &source):
    _nodeId(source._nodeId),
    _useFaceDistribution(source._useFaceDistribution),
    _valid(source._valid)
{
    _min[0]           = source._min[0];
    _min[1]           = source._min[1];
    _max[0]           = source._max[0];
    _max[1]           = source._max[1];
    _faces            = source._faces;
    _visible          = source._visible;
    _faceDistribution = source._faceDistribution;
    _areaSize         = source._areaSize;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/** Destructor documentation
 **/
TileGeometryLoad::~TileGeometryLoad(void)
{
}

/** Update the view dependend load parameters
 **/

void TileGeometryLoad::updateView(Matrix &viewing,
                                  Matrix &projection,
                                  Real32 rNear,
                                  UInt32 width,
                                  UInt32 height)
{
    Vec3f                        vol[2];
    Pnt3f                        pnt;
    Real32                       minx = 0.0,miny = 0.0;
    Real32                       maxx = 0.0,maxy = 0.0;
    Matrix                      *p;
    Real32                       bestScalX;
    UInt32                       bestDirX = 0;
    Real32                       bestScalY;
    UInt32                       bestDirY = 0;

    NodePtr node = dynamic_cast<NodePtr>(FieldContainerFactory::the()->getContainer(_nodeId));
    if(node == NullFC)
        return;

    // get whole transformation
    Matrix m=node->getToWorld();
    m.multLeft(viewing);
    // get transformed volume
    node->updateVolume();
    DynamicVolume volume=node->getVolume();
    // bug in osg base
    /*
    if(volume.isEmpty())
    {
        _visible=false;
        return;
    }
    */
    volume.transform(m);
    // get min,max
    volume.getBounds(vol[0], vol[1]);
    // min < rNear
    if(vol[0][2] > -rNear)
    {
        _visible=false;
        return;
    }

    // find best directon for face distribution
    if(_useFaceDistribution)
    {
        Real32 scal;
        Vec3f xdir(m[0][0],m[1][0],m[2][0]);
        Vec3f ydir(m[0][1],m[1][1],m[2][1]);
        xdir.normalize();
        ydir.normalize();
        bestScalX=bestScalY=0;
        for(UInt32 dir=0;dir<_directions.size();++dir)
        {
            scal=_directions[dir].getNormal()*xdir;
            if(scal>bestScalX)
            {
                bestScalX=scal;
                bestDirX =dir*2;
            }
            if((-scal)>bestScalX)
            {
                bestScalX=-scal;
                bestDirX =dir*2+1;
            }
            scal=_directions[dir].getNormal()*ydir;
            if(scal>bestScalY)
            {
                bestScalY=scal;
                bestDirY =dir*2;
            }
            if((-scal)>bestScalY)
            {
                bestScalY=-scal;
                bestDirY =dir*2+1;
            }
        }
        // cout << "x " << xdir << " " << _directions[bestDirX>>1].getNormal() << endl;
        // cout << "y " << ydir << " " << _directions[bestDirY>>1].getNormal() << endl;
        _faceDistDirX=bestDirX;
        _faceDistDirY=bestDirY;
        // cout << "best X:" << bestDirX << endl;
        // cout << "best Y:" << bestDirY << endl;
    }

    if(vol[1][2] > -rNear)
    {
        // volume lays on the fron clipping plane
        vol[1][2] = -rNear;
        p=&projection;
    }
    else
    {
        // volume lays on the visible side of the clipping plane
        node->getVolume().getBounds(vol[0], vol[1]);
        m.multLeft(projection);
        p=&m;
    }
    // create corners of a bounding box
    for(int i=0;i<8;++i)
    {
        p->multFullMatrixPnt(Pnt3f( vol[ (i   )&1 ][0] ,
                                    vol[ (i>>1)&1 ][1] ,
                                    vol[ (i>>2)&1 ][2]) , pnt);
        if(i>0)
        {
            if(minx > pnt[0]) minx = pnt[0];
            if(miny > pnt[1]) miny = pnt[1];
            if(maxx < pnt[0]) maxx = pnt[0];
            if(maxy < pnt[1]) maxy = pnt[1];
        }
        else
        {
            maxx = minx = pnt[0];
            maxy = miny = pnt[1];
        }
    }
    // visible ?
    if(maxx<-1 || maxy<-1 ||
       minx> 1 || miny> 1)
    {
        _visible = false;
    }
    else
    {
        minx=width  * ( minx + 1.0f ) / 2.0f - .5f;
        maxx=width  * ( maxx + 1.0f ) / 2.0f + .5f;
        miny=height * ( miny + 1.0f ) / 2.0f - .5f;
        maxy=height * ( maxy + 1.0f ) / 2.0f + .5f;
        _min[0]=(Int32)minx;
        _max[0]=(Int32)maxx;
        _min[1]=(Int32)miny;
        _max[1]=(Int32)maxy;

        _areaSize =
            (Real32)( _max[0] - _min[0] + 1 ) *
            (Real32)( _max[1] - _min[1] + 1 );
        /* Don't clip!
        if(_min[0]<0) _min[0]=0;
        if(_min[1]<0) _min[1]=0;
        if(_max[0]>=width ) _max[0]=width-1;
        if(_max[1]>=height) _max[1]=height-1;
        */
        _visible = true;
    }
}

/** Update geometry dependend load parameters
 *
 * This funciton should only be called when geometies have changed.
 *
 * todo: Use a simple cost estimation mechanism for rapidly changeing
 *       geometries.
 *
 **/
void TileGeometryLoad::updateGeometry()
{
    NodePtr node = dynamic_cast<NodePtr>(FieldContainerFactory::the()->getContainer(_nodeId));
    if(node == NullFC)
        return;

    const OSG::Volume *volume = &(node->getVolume().getInstance());
    TriangleIterator   f;
    int                p,s;
    Vec3f              vmin,vmax;
    Pnt3f              pos;
    Real32             min = 0.0,max = 0.0;
    PrimitiveIterator  it;
    NodeCorePtr        core;
    GeometryPtr        geo;
    const Real32       sq2 = osgSqrt(2.0f);
    const Real32       sq3 = osgSqrt(3.0f);

    _faces = 0;
    core=node->getCore();
    if(node->getCore() == NullFC)
        return;
    geo=dynamic_cast<GeometryPtr>(core);
    if(geo == NullFC)
        return;

    // get volume min,max
    volume->getBounds(vmin,vmax);

    // count faces
    for(f=geo->beginTriangles() ; f!=geo->endTriangles() ; ++f)
    {
        ++_faces;
    }
    if(_useFaceDistribution)
    {
        _faceDistribution.resize(_directions.size()*2);
        // loop through all directions
        for(UInt32 d=0;d<_directions.size();++d)
        {
            // init dist
            _faceDistribution[d*2  ].resize(FACE_DISTRIBUTION_SAMPLING_COUNT);
            _faceDistribution[d*2+1].resize(FACE_DISTRIBUTION_SAMPLING_COUNT);
            for(s=0;s<FACE_DISTRIBUTION_SAMPLING_COUNT;++s)
            {
                _faceDistribution[d*2  ][s]=0;
                _faceDistribution[d*2+1][s]=0;
            }
            // loop over all faces
            for(f=geo->beginTriangles() ;
                f!=geo->endTriangles() ;
                ++f)
            {
                for(p=0;p<3;++p)
                {
                    // get point and rescale
                    pos=(f.getPosition(p) - vmin);
                    pos[0]/=vmax[0]-vmin[0];
                    pos[1]/=vmax[1]-vmin[1];
                    pos[2]/=vmax[2]-vmin[2];
                    if(p==0)
                    {
                        max=min=_directions[d].distance(pos);
                    }
                    else
                    {
                        max=osgMax(max,_directions[d].distance(pos));
                        min=osgMin(min,_directions[d].distance(pos));
                    }
                }
                if(d>=7)
                {
                    min/=sq2;
                    max/=sq2;
                }
                else if(d>=3)
                {
                    min/=sq3;
                    max/=sq3;
                }
                _faceDistribution
                    [d*2  ]
                    [(int)(ceil(min*
                                (FACE_DISTRIBUTION_SAMPLING_COUNT-1)))]++;
                _faceDistribution
                    [d*2+1]
                    [(int)(ceil((1-max)*
                                (FACE_DISTRIBUTION_SAMPLING_COUNT-1)))]++;
            }
        }
        for(UInt32 d=0;d<_directions.size();++d)
        {
            _faceDistribution[d*2  ][0]/=_faces;
            _faceDistribution[d*2+1][0]/=_faces;
            for(s=1;s<FACE_DISTRIBUTION_SAMPLING_COUNT;++s)
            {
                _faceDistribution[d*2  ][s]/=_faces;
                _faceDistribution[d*2+1][s]/=_faces;
                _faceDistribution[d*2  ][s]+=_faceDistribution[d*2  ][s-1];
                _faceDistribution[d*2+1][s]+=_faceDistribution[d*2+1][s-1];
            }
#if 0
            printf("--> ");
            for(s=0;s<FACE_DISTRIBUTION_SAMPLING_COUNT;++s)
                printf("%4.3f ",_faceDistribution[d*2  ][s]);
            printf("\n<-- ");
            for(s=0;s<FACE_DISTRIBUTION_SAMPLING_COUNT;++s)
                printf("%4.3f ",_faceDistribution[d*2+1][s]);
            printf("\n");
#endif
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
TileGeometryLoad& TileGeometryLoad::operator=(const TileGeometryLoad &source)
{
    if(this == &source)
        return *this;
    _min[0]              = source._min[0];
    _min[1]              = source._min[1];
    _max[0]              = source._max[0];
    _max[1]              = source._max[1];
    _faces               = source._faces;
    _visible             = source._visible;
    _faceDistribution    = source._faceDistribution;
    _faceDistDirX        = source._faceDistDirX;
    _faceDistDirY        = source._faceDistDirY;
    _nodeId              = source._nodeId;
    _useFaceDistribution = source._useFaceDistribution;
    _areaSize            = source._areaSize;

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             dump                                        */

void TileGeometryLoad::dump(void)
{
    if(_visible)
    {
        SLOG << "Min/Max     :"
             << _min[0] << " " << _min[1] << " / "
             << _max[0] << " " << _max[1] << std::endl;
    }
    else
    {
        SLOG << "invisible " << std::endl;
    }
    SLOG << "Faces       :" << _faces << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             get                                         */

/** Return min valuse in window coordinates
 **/
const Int32 *TileGeometryLoad::getMin()
{
    return _min;
}

/** Return max valuse in window coordinates
 **/
const Int32 *TileGeometryLoad::getMax()
{
    return _max;
}

/** Is the geometry visible in the current viewport
 **/
bool TileGeometryLoad::isVisible() const
{
    return _visible;
}

/** Get Node ptr
 **/
NodePtr TileGeometryLoad::getNode() const
{
    return dynamic_cast<NodePtr>(FieldContainerFactory::the()->getContainer(_nodeId));
}

/** Get number of faces in the geometry
 **/
UInt32 TileGeometryLoad::getFaces()
{
    return _faces;
}

/** Which part of the faces are visible
 **/
Real32 TileGeometryLoad::getVisibleFraction( const Int32 wmin[2],
                                             const Int32 wmax[2],
                                                   Int32 viswmin[2],
                                                   Int32 viswmax[2] )
{
    Real32 x,y;

    if(_visible==false)
        return 0;

    // get visible area
    if(!getVisibleArea(wmin,wmax,viswmin,viswmax))
    {
        // not in region
        return 0;
    }
    // geometry complete in region?
    if(viswmin[0] == _min[0] &&
       viswmin[1] == _min[1] &&
       viswmax[0] == _max[0] &&
       viswmax[1] == _max[1])
    {
        return 1;
    }

    if(_useFaceDistribution)
    {
        x=1.0f/(_max[0]-_min[0]+1);
        y=1.0f/(_max[1]-_min[1]+1);
        return
            (getFaceDistribution(_faceDistDirX^1,
                                 1.0f - (viswmin[0] - _min[0]    ) * x) +
             getFaceDistribution(_faceDistDirX,
                                       (viswmax[0] - _min[0] + 1) * x) - 1)
            *
            (getFaceDistribution(_faceDistDirY^1,
                                 1.0f - (viswmin[1] - _min[1]    ) * y) +
             getFaceDistribution(_faceDistDirY,
                                       (viswmax[1] - _min[1] + 1) * y) - 1);
    }
    else
    {
        return
            ((Real32)(viswmax[0] - viswmin[0] + 1) *
             (Real32)(viswmax[1] - viswmin[1] + 1)) / _areaSize;
    }
}

/** Which area overlaps the given region
 **/
bool TileGeometryLoad::getVisibleArea( const Int32 wmin[2],
                                       const Int32 wmax[2],
                                             Int32 viswmin[2],
                                             Int32 viswmax[2]      )
{
    viswmin[0] = osgMax(wmin[0],_min[0]);
    viswmin[1] = osgMax(wmin[1],_min[1]);
    viswmax[0] = osgMin(wmax[0],_max[0]);
    viswmax[1] = osgMin(wmax[1],_max[1]);
    // not in region
    if(viswmin[0] > viswmax[0] ||
       viswmin[1] > viswmax[1])
        return false;
    else
        return true;
}

/** Check if one part of the geometry lays in the given region
 *
 * \param min    [ minx, miny ]
 * \param max    [ maxx, maxy ]
 *
 **/
bool TileGeometryLoad::checkRegion( Int32 min[2],
                                    Int32 max[2] )
{
    if(min[0] > _max[0] ||
       max[0] < _min[0] ||
       min[1] > _max[1] ||
       max[1] < _min[1])
        return false;
    else
        return true;
}

void TileGeometryLoad::setValid(bool s)
{
    _valid = s;
}

bool TileGeometryLoad::isInvalid(void)
{
    return !_valid;
}

/*-------------------------------------------------------------------------*/
/*                              static                                     */

std::vector<Plane>    TileGeometryLoad::_directions;
