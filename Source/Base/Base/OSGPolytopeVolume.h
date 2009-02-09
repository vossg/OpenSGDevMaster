/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSG_POLYTOPEVOLUME_H_
#define _OSG_POLYTOPEVOLUME_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGVolume.h"
#include "OSGPlane.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

/*! \brief 3D shadow frustum defined by n planes.
    \author dstaneker
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseVolume
 */

class OSG_BASE_DLLMAPPING PolytopeVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/
  public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
      
    PolytopeVolume(                                             ); 
    PolytopeVolume(const UInt16&                                );
    PolytopeVolume(const PolytopeVolume &obj                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    inline ~PolytopeVolume(); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */
    
    const           Plane & getNear         (void           ) const;
    const           Plane * getPlanes       (void           ); 
    const           Plane * getPlanes       (void           ) const; 
    virtual         void    getCenter       (Pnt3f &center  ) const;
    virtual         Real32  getScalarVolume (void           ) const;
    virtual         void    getBounds       ( Pnt3f &minPnt,
                                              Pnt3f &maxPnt ) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    void setPlane(const Plane&, const UInt16);
                                    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Extending                                 */
    /*! \{                                                                 */

    virtual         void extendBy   (const Pnt3f            &pt         );
                    void extendBy   (const Volume           &volume     );   
                    void extendBy   (const PolytopeVolume    &bb        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */

    bool intersect      (const Pnt3f            &point       ) const;
    bool intersect      (const Line             &line        ) const;
    bool intersect      (const Line             &line,
                         Real32           &minDist,
                         Real32           &maxDist           ) const;

    bool intersect    (const Volume           &volume ) const;
    bool intersect    (const PolytopeVolume    &bb    ) const;
    virtual bool isOnSurface (const Pnt3f            &point  ) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Transformation                            */
    /*! \{                                                                 */
  
    virtual void transform      (const Matrix           &m          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */
    
    PolytopeVolume &operator = (const PolytopeVolume &rhs);

    bool            operator ==(const PolytopeVolume &rhs) const;
    bool            operator !=(const PolytopeVolume &rhs) const;

   /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */


    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;
    
    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    UInt16 _numPlanes;
    Plane* _planes;
};

OSG_END_NAMESPACE

#include "OSGPolytopeVolume.inl"

#endif /* _OSG_POLYTOPEVOLUME_H_ */
