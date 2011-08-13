/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#ifndef _OSGFASTTRIANGLEITERATOR_H_
#define _OSGFASTTRIANGLEITERATOR_H_

#include "OSGConfig.h"
#include "OSGDrawableDef.h"
#include "OSGPrimitiveIterator.h"

OSG_BEGIN_NAMESPACE

class OSG_DRAWABLE_DLLMAPPING FastTriangleIterator : public PrimitiveIterator
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name  Constructors / Destructor                                   */
    /*! \{                                                                 */

    FastTriangleIterator(      void                        );
    FastTriangleIterator(const FastTriangleIterator &source);
    FastTriangleIterator(const Geometry             *geo   );
    FastTriangleIterator(const Node                 *node  );

    virtual ~FastTriangleIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name  Set                                                         */
    /*! \{                                                                 */

    virtual void setToBegin(void);
    virtual void setToEnd  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name  Get                                                         */
    /*! \{                                                                 */

    inline Int32   getIndex(Int32 which) const;
    inline Int32   getIndex(void       ) const;

    inline Int32   getPropertyIndex(UInt16 att, Int32 which) const;
    template <class ReturnT>
    inline ReturnT getPropertyValue(UInt16 att, Int32 which) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Operators                              */
    /*! \{                                                                 */

           FastTriangleIterator &operator++(void);
    inline FastTriangleIterator  operator++(int );

    FastTriangleIterator &seek      (Int32 index);

    FastTriangleIterator &operator= (const FastTriangleIterator &source);
    bool                  operator< (const FastTriangleIterator &rhs   ) const;
    bool                  operator==(const FastTriangleIterator &rhs   ) const;
    bool                  operator!=(const FastTriangleIterator &rhs   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    typedef PrimitiveIterator  Inherited;

    void   startPrim       (void);
    UInt32 getTrisInActPrim(void) const;
    UInt32 getTriInActPrim (void) const;

    Int32  _triIndex;
    UInt32 _actPrimIndex;
    UInt32 _triPntIndex[3];
};

OSG_END_NAMESPACE

#include "OSGFastTriangleIterator.inl"

#endif // _OSGFASTTRIANGLEITERATOR_H_
