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

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BoxVolume(      void          );

    BoxVolume(      Real xmin, 
                    Real ymin, 
                    Real zmin,
                    Real xmax, 
                    Real ymax, 
                    Real zmax     );

    BoxVolume(const Pnt3r     &min,
              const Pnt3r     &max);
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
    
            const Pnt3r &getMin         (void          ) const;    
            const Pnt3r &getMax         (void          ) const;

    virtual       void   getCenter      (Pnt3r &center ) const;

    virtual       Real   getScalarVolume(void          ) const;

    virtual       void   getBounds      (Pnt3r &min, 
                                         Pnt3r &max    ) const;


                  void   getBounds      (Real  &xmin, 
                                         Real  &ymin, 
                                         Real  &zmin,
                                         Real  &xmax,
                                         Real  &ymax, 
                                         Real  &zmax   ) const;
    

                  void   getOrigin      (Real  &originX, 
                                         Real  &originY, 
                                         Real  &originZ) const;
                  void   getSize        (Real  &sizeX, 
                                         Real  &sizeY, 
                                         Real  &sizeZ  ) const;
                  void   getSize        (Vec3r &vec    ) const;    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setBounds(      Real   w,         
                         Real   h,    
                         Real   d   );
    void setBounds(      Real   xmin,      
                         Real   ymin, 
                         Real   zmin,
                         Real   xmax,      
                         Real   ymax, 
                         Real   zmax);
    void setBounds(const Pnt3r &min, 
                   const Pnt3r &max );

    void setBoundsByCenterAndSize(const Pnt3r &center, 
                                  const Vec3r &size  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Extend                                  */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3r     &pt    );
    virtual void extendBy(const Volume    &volume);
            void extendBy(const BoxVolume &bb    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Intersect                               */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3r     &point ) const;
    virtual bool intersect  (const Line      &line  ) const;
    virtual bool intersect  (const Line      &line,
                                   Real      &min, 
                                   Real      &max   ) const;
    virtual bool intersect  (const Volume    &volume) const;

            bool intersect  (const BoxVolume &bb    ) const;

    virtual bool isOnSurface(const Pnt3r     &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Transform                               */
    /*! \{                                                                 */

    virtual void transform(const Matrixr &m);

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

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Volume Inherited;

    /*==========================  PRIVATE  ================================*/

  private:

    Pnt3r _min;
    Pnt3r _max;
};

OSG_END_NAMESPACE

#include "OSGBoxVolume.inl"

#endif // _OSGBOXVOLUME_H_
