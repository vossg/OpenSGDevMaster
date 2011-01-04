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

#ifndef _OSGGEOBUILDER_H_
#define _OSGGEOBUILDER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoProperties.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

/*! \brief A helper class to simplify building geometry.
    \ingroup GrpDrawablesGeometryUtils
    \nohierarchy
 */

class OSG_DRAWABLE_DLLMAPPING GeoBuilder
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                Con/Destructors                               */
    /*! \{                                                                 */

    GeoBuilder(void);

    ~GeoBuilder();

    void reset(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Property Access                               */
    /*! \{                                                                 */

    template <class Type>
    UInt32 vertex(Type data)
    {
        getProperty(Geometry::PositionsIndex)->addValue(data);

        return finishVertex();
    }

    template <class Type>
    void normal(Type data)
    {
        getProperty(Geometry::NormalsIndex)->addValue(data);
    }

    template <class Type>
    void color(Type data)
    {
        getProperty(Geometry::ColorsIndex)->addValue(data);
    }

    template <class Type>
    void texcoord(UInt16 unit, Type data)
    {
        getProperty(Geometry::TexCoordsIndex + unit)->addValue(data);
    }

    template <class Type>
    UInt32 prop(UInt16 index, Type data)
    {
        getProperty(index)->addValue(data);

        if(index == 0)
            return finishVertex();
        else
            return 0;
    }

    template <class VType, class NType>
    UInt32 fullVertex(VType vert, NType norm)
    {
        normal(norm);
        return vertex(vert);
    }

    template <class VType, class NType, class CType>
    UInt32 fullVertex(VType vert, NType norm, CType col)
    {
        color(col);
        normal(norm);
        return vertex(vert);
    }

    template <class VType, class NType, class CType, class TType>
    UInt32 fullVertex(VType vert, NType norm, CType col, TType tc)
    {
        color(col);
        normal(norm);
        texcoord(0, tc);
        return vertex(vert);
    }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Face Creation                               */
    /*! \{                                                                 */

    void begin(UInt32 type);

    void index(UInt32 index);

    void end(void);

    void line(UInt32 start        );
    void line(UInt32 i1, UInt32 i2);

    void tri(UInt32 start                   );
    void tri(UInt32 i1, UInt32 i2, UInt32 i3);

    void quad(UInt32 start                              );
    void quad(UInt32 i1, UInt32 i2, UInt32 i3, UInt32 i4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Object Access                               */
    /*! \{                                                                 */

    Geometry *getGeometry(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name               Property Helper                               */
    /*! \{                                                                 */

    GeoVectorProperty *getProperty(UInt32 index);

    UInt32 finishVertex(void);

    void addType(Int32 type);
    void addLength(UInt32 length);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    GeometryUnrecPtr _geo;

    UInt32 _actLen;
     Int32 _actType;

    static const char* _defaultPropTypes[Geometry::MaxAttribs];
};

OSG_END_NAMESPACE

#include "OSGGeoBuilder.inl"

#endif /* _OSGGEOBUILDER_H_ */
