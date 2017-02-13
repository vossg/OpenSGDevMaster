/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifndef _OSGBOXVOLUME_INL_
#define _OSGBOXVOLUME_INL_

OSG_BEGIN_NAMESPACE

/*! Default constructor - leaves box totally empty
*/

inline
BoxVolume::BoxVolume(void) : 
     Inherited(             ),
    _min      (0.f, 0.f, 0.f), 
    _max      (0.f, 0.f, 0.f)
{
}


inline
BoxVolume::BoxVolume(Real32 xmin, Real32 ymin, Real32 zmin,
                     Real32 xmax, Real32 ymax, Real32 zmax) :
     Inherited(             ), 
    _min      (0.f, 0.f, 0.f), 
    _max      (0.f, 0.f, 0.f)
{ 
    setBounds(xmin, ymin, zmin, xmax, ymax, zmax);
}


inline
BoxVolume::BoxVolume(const Pnt3f &min, const Pnt3f &max) :
     Inherited(             ), 
    _min      (0.f, 0.f, 0.f), 
    _max      (0.f, 0.f, 0.f)
{ 
    setBounds(min, max);
}


inline
BoxVolume::BoxVolume(const BoxVolume &obj) :
     Inherited(obj     ), 
    _min      (obj._min), 
    _max      (obj._max) 
{
}


inline
BoxVolume::~BoxVolume(void) 
{
}


inline
const Pnt3f &BoxVolume::getMin(void) const
{
    return _min;
}


inline
const Pnt3f &BoxVolume::getMax(void) const
{
    return _max;
}


inline
void BoxVolume::getBounds(Real32 &xmin, 
                          Real32 &ymin, 
                          Real32 &zmin,
                          Real32 &xmax, 
                          Real32 &ymax, 
                          Real32 &zmax) const
{
    _min.getSeparateValues(xmin, ymin, zmin);
    _max.getSeparateValues(xmax, ymax, zmax);
}


inline
void BoxVolume::getOrigin(Real32 &originX, 
                          Real32 &originY, 
                          Real32 &originZ) const
{
    originX = _min[0];
    originY = _min[1];
    originZ = _min[2];
}


inline
void BoxVolume::getSize(Real32 &sizeX, 
                        Real32 &sizeY, 
                        Real32 &sizeZ) const
{
    sizeX = _max[0] - _min[0];
    sizeY = _max[1] - _min[1];
    sizeZ = _max[2] - _min[2];
}


inline
void BoxVolume::getSize(Vec3f &vec) const
{
    vec.setValues(_max[0] - _min[0], _max[1] - _min[1], _max[2] - _min[2]);
}


inline
void BoxVolume::setBounds(Real32 w, Real32 h, Real32 d)
{
    _min.setValues(-w / 2.0f, -h / 2.0f, -d / 2.0f);
    _max.setValues( w / 2.0f,  h / 2.0f,  d / 2.0f);

    Volume::setValid   (true );
    Volume::setEmpty   (false);
    Volume::setInfinite(false);
}


inline
void BoxVolume::setBounds(Real32 xmin, 
                          Real32 ymin, 
                          Real32 zmin,
                          Real32 xmax, 
                          Real32 ymax, 
                          Real32 zmax)
{
    _min.setValues(osgMin(xmin,xmax), osgMin(ymin,ymax), osgMin(zmin,zmax));
    _max.setValues(osgMax(xmin,xmax), osgMax(ymin,ymax), osgMax(zmin,zmax));

    Volume::setValid   (true );
    Volume::setEmpty   (false);
    Volume::setInfinite(false);
}


inline
void BoxVolume::setBounds(const Pnt3f &min, const Pnt3f &max)
{
    setBounds(min[0],min[1],min[2], max[0],max[1],max[2]);
}

inline
Pnt3f &BoxVolume::editMin(void)
{
    return _min;
}


inline
Pnt3f &BoxVolume::editMax(void)
{
    return _max;
}

inline
void BoxVolume::extendBy(const BoxVolume &volume)
{
    OSG::extend(*this, volume);
}

inline
bool BoxVolume::operator !=(const BoxVolume &rhs) const
{
    return !(*this == rhs);
}

OSG_END_NAMESPACE

#endif // _OSG_BOXVOLUME_INL_
