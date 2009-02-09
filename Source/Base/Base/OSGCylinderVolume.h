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

#ifndef _OSGCYLINDERVOLUME_H_
#define _OSGCYLINDERVOLUME_H_

#include "OSGVolume.h"
#include "OSGVolumeFunctions.h"
#include "OSGLine.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

class Line;

/*! 3D cylinder in space defined by axis and radius.

    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseVolume
 */

class OSG_BASE_DLLMAPPING CylinderVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CylinderVolume(void);

    CylinderVolume(const Pnt3r          &p, 
                   const Vec3r          &d, 
                         Real            r);
    CylinderVolume(const CylinderVolume &c);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    ~CylinderVolume(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */
    
            void getAxis        (Pnt3r &apos,  
                                 Vec3r &adir  ) const;
            Real getRadius      (void         ) const;

    virtual void getCenter      (Pnt3r &center) const;
    virtual Real getScalarVolume(void         ) const;
    virtual void getBounds      (Pnt3r &min,   
                                 Pnt3r &max   ) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

     void setValue (const Pnt3r &p, const Vec3r &d, Real r);
     void setAxis  (const Pnt3r &p, const Vec3r &d        );
     void setRadius(      Real r                          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Extend                                */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3r          &pt    );
    virtual void extendBy(const Volume         &volume);

            void extendBy(const CylinderVolume &obj   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Intersect                             */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3r          &point ) const;
    virtual bool intersect  (const Line           &line  ) const;
    virtual bool intersect  (const Line           &line,
                                   Real           &enter, 
                                   Real           &exit  ) const;

    virtual bool intersect  (const Volume         &volume) const;
            bool intersect  (const CylinderVolume &volume) const;
    virtual bool isOnSurface(const Pnt3r          &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Transform                             */
    /*! \{                                                                 */

    virtual void transform(const Matrixr &mat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Operator                              */
    /*! \{                                                                 */

    CylinderVolume &operator = (const CylinderVolume &rhs);

    bool            operator ==(const CylinderVolume &rhs) const;

    bool            operator !=(const CylinderVolume &rhs) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Output                                */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    typedef Volume Inherited;

  private:

    Pnt3r _axisPos;
    Vec3r _axisDir;
    Real  _radius;

};

OSG_END_NAMESPACE

#include "OSGCylinderVolume.inl"

#endif // _OSGCYLINDERVOLUME_H_
