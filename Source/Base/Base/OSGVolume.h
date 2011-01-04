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

#ifndef _OSGVOLUME_H_
#define _OSGVOLUME_H_

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGVector.h"
#include "OSGMatrixFwd.h"

#include <iosfwd>

OSG_BEGIN_NAMESPACE

class Line;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseVolume
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING Volume 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Volume(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     State                                    */
    /*! \{                                                                 */

    void   setValid     (const bool   value = true);
    bool   isValid      (      void               ) const;

    void   setEmpty     (const bool   value = true);
    bool   isEmpty      (      void               ) const;

    void   setStatic    (const bool   value = true);
    bool   isStatic     (      void               ) const;

    void   setInfinite  (const bool   value = true);
    bool   isInfinite   (      void               ) const;

    bool   isUntouchable(      void               ) const;

    UInt16 getState     (      void               ) const;
    void   setState     (      UInt16 state       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Values                                 */
    /*! \{                                                                 */

    virtual void   getCenter      (Pnt3f &center) const = 0;

    virtual Real32 getScalarVolume(void         ) const = 0;

    virtual void   getBounds      (Pnt3f &min, 
                                   Pnt3f &max   ) const = 0;

            Pnt3f  getMin         (void         ) const;
            Pnt3f  getMax         (void         ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Extending                                  */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3f  &pt    ) = 0;
    virtual void extendBy(const Volume &volume) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Intersection                                */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3f  &point ) const = 0;
    virtual bool intersect  (const Line   &line  ) const = 0;
    virtual bool intersect  (const Line   &line,
                                   Real32 &enter, 
                                   Real32 &exit  ) const = 0;
    virtual bool intersect  (const Volume &volume) const = 0;

    virtual bool isOnSurface(const Pnt3f  &point ) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void transform(const Matrix &matrix) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump (      UInt32     uiIndent = 0,
                       const BitVector  bvFlags  = 0) const = 0;
    virtual void print(std::ostream    &os          ) const = 0;

    /*! \}                                                                 */

    bool operator ==(const Volume &other) const;
    bool operator !=(const Volume &other) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt16 _state;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Volume(void);
    Volume(const Volume &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    void printState(std::ostream &os) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    enum State
    {
        OSGVALID    = 1,
        OSGEMPTY    = 2,
        OSGSTATIC   = 4,
        OSGINFINITE = 8
    };
};

typedef Volume* VolumeP;

/*! helper functions to dump a volume. Useful for debuggers.
    \ingroup GrpBaseBaseVolume
    \relatesalso Volume
 */
OSG_BASE_DLLMAPPING 
void volDump(Volume *vol);


std::ostream& operator<<(std::ostream& os, const Volume& vol);

OSG_END_NAMESPACE

#include "OSGVolume.inl"

#endif // _OSGVOLUME_H_
