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
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING CylinderVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CylinderVolume(void);

    CylinderVolume(const Pnt3f          &p, 
                   const Vec3f          &d, 
                         Real32          r);
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
    
            void   getAxis        (Pnt3f &apos,  
                                   Vec3f &adir  ) const;
            Real32 getRadius      (void         ) const;

    virtual void   getCenter      (Pnt3f &center) const;
    virtual Real32 getScalarVolume(void         ) const;
    virtual void   getBounds      (Pnt3f &min,   
                                   Pnt3f &max   ) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

     void setValue (const Pnt3f  &p, const Vec3f &d, Real32 r);
     void setAxis  (const Pnt3f  &p, const Vec3f &d          );
     void setRadius(      Real32  r                          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Extend                                */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3f          &pt    );
    virtual void extendBy(const Volume         &volume);

            void extendBy(const CylinderVolume &obj   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Intersect                             */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3f          &point ) const;
    virtual bool intersect  (const Line           &line  ) const;
    virtual bool intersect  (const Line           &line,
                                   Real32         &enter, 
                                   Real32         &exit  ) const;

    virtual bool intersect  (const Volume         &volume) const;
            bool intersect  (const CylinderVolume &volume) const;
    virtual bool isOnSurface(const Pnt3f          &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Transform                             */
    /*! \{                                                                 */

    virtual void transform(const Matrix &mat);

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

    virtual void dump (      UInt32     uiIndent = 0,
                       const BitVector  bvFlags  = 0) const;
    virtual void print(std::ostream    &os          ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    typedef Volume Inherited;

  private:

    Pnt3f  _axisPos;
    Vec3f  _axisDir;
    Real32 _radius;

};

OSG_END_NAMESPACE

#include "OSGCylinderVolume.inl"

#endif // _OSGCYLINDERVOLUME_H_
