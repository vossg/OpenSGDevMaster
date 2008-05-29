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

#ifndef _OSGDYNAMICVOLUME_H_
#define _OSGDYNAMICVOLUME_H_

#include "OSGBaseFunctions.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseVolume  
 */

class OSG_BASE_DLLMAPPING DynamicVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum Type 
    { 
        BOX_VOLUME, 
        SPHERE_VOLUME 
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DynamicVolume(      Type           type = BOX_VOLUME);
    DynamicVolume(const DynamicVolume &obj              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynamicVolume(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */

    const Volume &getInstance    (void     ) const;
          Volume &getInstance    (void     );
          void    instanceChanged(void     );


          Type    getType        (void     ) const;
          void    setVolumeType  (Type type);
          void    morphToType    (Type type);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    virtual void getCenter      (Pnt3r &center) const;
    virtual Real getScalarVolume(void         ) const;
    virtual void getBounds      (Pnt3r &min,   
                                 Pnt3r &max   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Extend                                 */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3r  &pt    );
    virtual void extendBy(const Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3r  &point ) const;
    virtual bool intersect  (const Line   &line  ) const;
    virtual bool intersect  (const Line   &line,
                                   Real   &enter, 
                                   Real   &exit  ) const;
    virtual bool intersect  (const Volume &volume) const;
    virtual bool isOnSurface(const Pnt3r  &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Transform                              */
    /*! \{                                                                 */

    virtual void transform (const Matrixr &matrix);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Output                                 */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Operators                              */
    /*! \{                                                                 */

    DynamicVolume &operator = (const DynamicVolume &rhs);

    bool           operator ==(const DynamicVolume &rhs) const;
    bool           operator !=(const DynamicVolume &rhs ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Volume Inherited;

    /*==========================  PRIVATE  ================================*/

  private:

    Type   _type;
    Real64 _volumeMem[5]; // use Real64 to create the 32 bytes for alignment 
                          // safety. This assumes that Real64 has the most 
                          // stringent alignment requirements!!!
};

OSG_BASE_DLLMAPPING
std::ostream &operator <<(      std::ostream  &outStream,
                          const DynamicVolume &vol);
OSG_END_NAMESPACE

#include "OSGDynamicVolume.inl"

#endif // _OSGDYNAMICVOLUME_H_
