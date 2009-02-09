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

#ifndef _OSGSPHEREVOLUME_H_
#define _OSGSPHEREVOLUME_H_

#include "OSGVolume.h"
#include "OSGVolumeFunctions.h"

OSG_BEGIN_NAMESPACE

class Line;

/*! Sphere in 3D space defined by center and radius.
  
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseVolume  
 */

class OSG_BASE_DLLMAPPING SphereVolume : public Volume 
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    SphereVolume(void);

    SphereVolume(const SphereVolume &obj);
    SphereVolume(const Pnt3r        &c, 
                       Real          r  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    ~SphereVolume(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    void setValue (const Pnt3r &c, 
                         Real r);
    void setCenter(const Pnt3r &c);
    void setRadius(      Real r);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get Values                                */
    /*! \{                                                                 */

            const Pnt3r &getCenter      (void         ) const;
                  Real   getRadius      (void         ) const;

    virtual       void   getCenter      (Pnt3r &center) const;
    virtual       Real   getScalarVolume(void         ) const;
    virtual       void   getBounds      (Pnt3r &min,  
                                         Pnt3r &max   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Extending                                  */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3r        &pt    );
    virtual void extendBy(const Volume       &volume);
            void extendBy(const SphereVolume &bb    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Intersection                                 */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3r        &point ) const;
    virtual bool intersect  (const Line         &line  ) const;
    virtual bool intersect  (const Line         &line,
                                   Real         &enter, 
                                   Real         &exit  ) const;

    virtual bool intersect  (const Volume       &volume) const;
            bool intersect  (const SphereVolume &sphere) const;

    virtual bool isOnSurface(const Pnt3r        &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void transform(const Matrixr &mat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

    SphereVolume &operator = (const SphereVolume &rhs);

    bool          operator ==(const SphereVolume &rhs) const;
    bool          operator !=(const SphereVolume &rhs) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Volume Inherited;

    /*==========================  PRIVATE  ================================*/

  private:

    Pnt3r _center;
    Real  _radius;

};

OSG_END_NAMESPACE

#include "OSGSphereVolume.inl"

#endif // _OSGSPHEREVOLUME_H_
