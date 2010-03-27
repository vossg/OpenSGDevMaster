/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2006 by the OpenSG Forum                    *
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

#ifndef _OSGFIXED_H_
#define _OSGFIXED_H_

#ifndef _OSGBASETYPES_H_
#error  Include OSGBaseTypes.h instead of OSGFixed.h
#endif

#ifdef DOXYGEN_SHOULD_SKIP_THIS
OSG_BEGIN_NAMESPACE
#endif

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING Fixed32
{
  public:

    //-------------
    // Constructors
    //-------------

    Fixed32(void);
    Fixed32(const Real32 source);
    Fixed32(const UInt32 source);
    Fixed32(const Fixed32 &source);

    ~Fixed32(void);

    //------------
    // Unary minus
    //------------

    Fixed32 operator - () const;

    void setFixedValue(Int32 src);

    //-----------
    // Assignment
    //-----------

    Fixed32 &operator = (const Fixed32 rhs);

    Fixed32 &operator +=(const Fixed32 rhs);
    Fixed32 &operator -=(const Fixed32  rhs);
    Fixed32 &operator *=(const Fixed32 rhs);
    Fixed32 &operator /=(const Fixed32 rhs);

    Fixed32  operator + (const Fixed32 rhs) const;
    Fixed32  operator - (const Fixed32 rhs) const;
    Fixed32  operator * (const Fixed32 rhs) const;
    Fixed32  operator / (const Fixed32 rhs) const;

    bool operator ==(const Fixed32 rhs) const;
    bool operator !=(const Fixed32 rhs) const;
    bool operator < (const Fixed32 rhs) const;
    bool operator > (const Fixed32 rhs) const;
    bool operator <=(const Fixed32 rhs) const;
    bool operator >=(const Fixed32 rhs) const;

//    operator Real32 () const;

    Int32 getValue(void      ) const;
    void  setValue(Int32 iVal);

    static Fixed32 abs(Fixed32 rhs);
    static Fixed32 sqrt(Fixed32 rhs);

    static Fixed32 sin(Fixed32 rhs);
    static Fixed32 cos(Fixed32 rhs);
    static Fixed32 tan(Fixed32 rhs);

    static Real32 toFloat(Fixed32 rhs);
  protected:

    Fixed32(const Int32 source);

  private:

    Int32 _value;
};

/*! \relates Fixed32
 */
Fixed32 operator -(const OSG::Real32 lhs, const Fixed32 rhs);

/*! \relates Fixed32
 */
Fixed32 operator /(const OSG::Real32 lhs, const Fixed32 rhs);

/*! \relates Fixed32
 */
Fixed32 operator *(const OSG::Real32 lhs, const Fixed32 rhs);

/*! \relates Fixed32
 */
std::ostream &operator << (std::ostream &os, const Fixed32  fVal);

/*! \relates Fixed32
 */
std::istream &operator >> (std::istream &is,       Fixed32 &fVal);

#ifdef DOXYGEN_SHOULD_SKIP_THIS
OSG_END_NAMESPACE
#endif

#include "OSGFixed.inl"

#endif /* _OSGFIXED_H_ */
