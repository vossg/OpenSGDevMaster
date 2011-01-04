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
    \ingroup GrpLibOSGBase
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
    SphereVolume(const Pnt3f        &c, 
                       Real32        r  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    ~SphereVolume(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    void setValue (const Pnt3f  &c, 
                         Real32  r);
    void setCenter(const Pnt3f  &c);
    void setRadius(      Real32  r);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get Values                                */
    /*! \{                                                                 */

            const Pnt3f  &getCenter      (void         ) const;
                  Real32  getRadius      (void         ) const;

    virtual       void    getCenter      (Pnt3f &center) const;
    virtual       Real32  getScalarVolume(void         ) const;
    virtual       void    getBounds      (Pnt3f &min,  
                                          Pnt3f &max   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Extending                                  */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3f        &pt    );
    virtual void extendBy(const Volume       &volume);
            void extendBy(const SphereVolume &bb    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Intersection                                 */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3f        &point ) const;
    virtual bool intersect  (const Line         &line  ) const;
    virtual bool intersect  (const Line         &line,
                                   Real32       &enter, 
                                   Real32       &exit  ) const;

    virtual bool intersect  (const Volume       &volume) const;
            bool intersect  (const SphereVolume &sphere) const;

    virtual bool isOnSurface(const Pnt3f        &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void transform(const Matrix &mat);

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

    virtual void dump (      UInt32     uiIndent = 0,
                       const BitVector  bvFlags  = 0) const;
    virtual void print(std::ostream    &os          ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Volume Inherited;

    /*==========================  PRIVATE  ================================*/

  private:

    Pnt3f  _center;
    Real32 _radius;

};

OSG_END_NAMESPACE

#include "OSGSphereVolume.inl"

#endif // _OSGSPHEREVOLUME_H_
