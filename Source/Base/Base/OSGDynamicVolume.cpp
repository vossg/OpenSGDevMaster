/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#include "OSGConfig.h"

#include "new"

// Class declarations
#include "OSGDynamicVolume.h"

#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/*-------------------------- constructor ----------------------------------*/

DynamicVolume::DynamicVolume(Type type) :
     Inherited(    ),
    _type     (type)
{
    setVolumeType(type);
}

DynamicVolume::DynamicVolume(const DynamicVolume &obj) :
     Volume(obj      ),
    _type  (obj._type)
{
    switch(_type) 
    {
        case BOX_VOLUME:
            new (_volumeMem) 
                BoxVolume   (*((OSG::BoxVolume    *)(obj._volumeMem)));
            break;

        case SPHERE_VOLUME:
            new (_volumeMem) 
                SphereVolume(*((OSG::SphereVolume *)(obj._volumeMem)));
            break;
    }
}

void DynamicVolume::setVolumeType(Type type)
{
    _type = type;

    switch(type)
    {
        case BOX_VOLUME:
            new (_volumeMem) BoxVolume;
            break;
        case SPHERE_VOLUME:
            new (_volumeMem) SphereVolume;
            break;
    }

    instanceChanged();
}

void DynamicVolume::morphToType(Type type)
{
    Pnt3r         min;
    Pnt3r         max;
    Vec3r         vec;
    BoxVolume    *bv;
    SphereVolume *sv;

    if(type == _type)
    {
        return;
    }
    else
    {
        switch(type) 
        {
            case BOX_VOLUME:

                getBounds(min, max);

                bv = new (_volumeMem) BoxVolume;

                bv->setBounds(min,max);

                break;

            case SPHERE_VOLUME:

                getBounds(min, max);

                sv = new (_volumeMem) SphereVolume;

                vec.setValues(max.x(), max.y(), max.z());

                vec -= Vec3r(min.x(), min.y(), min.z());

                sv->setValue(vec, vec.length()/2.f);

                break;
        }
    }

    instanceChanged();
}

/*! gives the center of the volume */

void DynamicVolume::getCenter(Pnt3r &center) const
{
    getInstance().getCenter(center);
}


/*! gives the scalar volume of the volume */

Real DynamicVolume::getScalarVolume(void) const
{
    return getInstance().getScalarVolume();
}


/*! gives the boundaries of the volume */

void DynamicVolume::getBounds(Pnt3r &min, Pnt3r &max) const
{
    getInstance().getBounds(min,max);
}


/*! extends (if necessary) to contain the given 3D point */

void DynamicVolume::extendBy(const Pnt3r &pt)
{
    getInstance    ().extendBy(pt);
    instanceChanged();
}


/*! extend the volume by the given volume */

void DynamicVolume::extendBy(const Volume &volume)
{
    getInstance    ().extendBy(volume);
    instanceChanged();
}


/*! Returns true if intersection of given point and Volume is not empty */

bool DynamicVolume::intersect(const Pnt3r &point) const
{
    return getInstance().intersect(point);
}

/*! intersect the volume with the given Line */

bool DynamicVolume::intersect(const Line &line ) const
{
    return getInstance().intersect(line);
}

/*! intersect the volume with the given Line */

bool DynamicVolume::intersect(const Line        &line,
                                    Real &enter, 
                                    Real &exit ) const
{
    return getInstance().intersect(line, enter, exit);
}

/*! intersect the volume with another volume */

bool DynamicVolume::intersect(const Volume &volume) const
{
    return getInstance().intersect(volume);
}

/*! check if the point is on the volume's surface */

bool DynamicVolume::isOnSurface(const Pnt3r &point) const
{
    return getInstance().isOnSurface(point);
}

/*! transform the volume bye the given matrix */

void DynamicVolume::transform(const Matrixr &matrix)
{
    getInstance    ().transform(matrix);
    instanceChanged();
}

/*! print the volume */

void DynamicVolume::dump(UInt32 uiIndent, const BitVector bvFlags) const
{
    PLOG << "Dyn:";
    
    getInstance().dump(uiIndent, bvFlags);
}


bool 
    DynamicVolume::operator ==(const DynamicVolume &OSG_CHECK_ARG(other)) const
{
    return false; 
}


DynamicVolume &DynamicVolume::operator =(const DynamicVolume &source)
{
    _type = source._type;

    switch(_type)
    {
        case BOX_VOLUME:
            new (_volumeMem)
                BoxVolume   (*((OSG::BoxVolume    *)(source._volumeMem)));
            break;

        case SPHERE_VOLUME:
            new (_volumeMem)
                SphereVolume(*((OSG::SphereVolume *)(source._volumeMem)));
            break;
    }

    instanceChanged();

    return *this;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
