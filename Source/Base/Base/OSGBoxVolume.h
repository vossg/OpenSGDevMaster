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

#ifndef _OSGBOXVOLUME_H_
#define _OSGBOXVOLUME_H_

#include "OSGVolume.h"
#include "OSGPlane.h"
#include "OSGVolumeFunctions.h"

OSG_BEGIN_NAMESPACE

/*! 3D box defined by min and max point.

    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseVolume
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING BoxVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum Corner
    {
        NEAR_LEFT_BOTTOM = 0,         // Min-Min-Min
        NEAR_RIGHT_BOTTOM,            // Max-Min-Min
        NEAR_RIGHT_TOP,               // Max-Max-Min
        NEAR_LEFT_TOP,                // Min-Max-Min
        FAR_LEFT_BOTTOM,              // Min-Min-Max
        FAR_RIGHT_BOTTOM,             // Max-Min-Max
        FAR_RIGHT_TOP,                // Max-Max-Max
        FAR_LEFT_TOP,                 // Min-Max-Max
        CORNER_COUNT
    };

    enum AABBPlane
    {
        PLANE_NEAR = 0,
        PLANE_FAR,
        PLANE_LEFT,
        PLANE_RIGHT,
        PLANE_BOTTOM,
        PLANE_TOP,
        AABB_PLANE_COUNT
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BoxVolume(      void          );

    BoxVolume(      Real32 xmin, 
                    Real32 ymin, 
                    Real32 zmin,
                    Real32 xmax, 
                    Real32 ymax, 
                    Real32 zmax   );

    BoxVolume(const Pnt3f     &min,
              const Pnt3f     &max);
    BoxVolume(const BoxVolume &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    ~BoxVolume();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
            const Pnt3f &getMin         (void                       ) const;    
            const Pnt3f &getMax         (void                       ) const;

    virtual       void   getCenter      (Pnt3f  &center             ) const;

    virtual       Real32 getScalarVolume(void                       ) const;

    virtual       void   getBounds      (Pnt3f  &min, 
                                         Pnt3f  &max                ) const;


                  void   getBounds      (Real32 &xmin, 
                                         Real32 &ymin, 
                                         Real32 &zmin,
                                         Real32 &xmax,
                                         Real32 &ymax, 
                                         Real32 &zmax               ) const;
                  void   getCorners     (Pnt3f  &nlt,    Pnt3f &nlb,
                                         Pnt3f  &nrt,    Pnt3f &nrb,
                                         Pnt3f  &flt,    Pnt3f &flb,
                                         Pnt3f  &frt,    Pnt3f &frb ) const;

                  Pnt3f  getCorner      (Corner cornerId) const;
                  Plane  getPlane       (AABBPlane planeId) const;
    

                  void   getOrigin      (Real32 &originX, 
                                         Real32 &originY, 
                                         Real32 &originZ            ) const;
                  void   getSize        (Real32 &sizeX, 
                                         Real32 &sizeY, 
                                         Real32 &sizeZ              ) const;
                  void   getSize        (Vec3f  &vec                ) const;    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setBounds(      Real32  w,         
                         Real32  h,    
                         Real32  d   );
    void setBounds(      Real32  xmin,      
                         Real32  ymin, 
                         Real32  zmin,
                         Real32  xmax,      
                         Real32  ymax, 
                         Real32  zmax);
    void setBounds(const Pnt3f  &min, 
                   const Pnt3f  &max );

    void setBoundsByCenterAndSize(const Pnt3f &center, 
                                  const Vec3f &size  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Extend                                  */
    /*! \{                                                                 */

    Pnt3f &editMin(void);    
    Pnt3f &editMax(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Extend                                  */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3f     &pt    );
    virtual void extendBy(const Volume    &volume);
            void extendBy(const BoxVolume &bb    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Intersect                               */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3f     &point ) const;
    virtual bool intersect  (const Line      &line  ) const;
    virtual bool intersect  (const Line      &line,
                                   Real32    &min, 
                                   Real32    &max   ) const;
    virtual bool intersect  (const Volume    &volume) const;

            bool intersect  (const BoxVolume &bb    ) const;

    virtual bool isOnSurface(const Pnt3f     &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Transform                               */
    /*! \{                                                                 */

    virtual void transform(const Matrix &m);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Operators                               */
    /*! \{                                                                 */

    BoxVolume &operator = (const BoxVolume &rhs);

    bool       operator ==(const BoxVolume &rhs) const;
    bool       operator !=(const BoxVolume &rhs) const;

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

    Pnt3f _min;
    Pnt3f _max;
};

OSG_END_NAMESPACE

#include "OSGBoxVolume.inl"

#endif // _OSGBOXVOLUME_H_
