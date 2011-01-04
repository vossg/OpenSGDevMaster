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

#ifndef _OSGCOLOR_H_
#define _OSGCOLOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVector.h"
#include <iostream>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
 */

template <class ValueTypeT>
class Color3 : public Vector<ValueTypeT, 3>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ValueTypeT            ValueType;
    typedef Vector<ValueTypeT, 3> Inherited;

    static const Color3 Null;

    /*---------------------------------------------------------------------*/
    /*! \name                      Class Specific                          */
    /*! \{                                                                 */

    static void   convertFromHSV(      ValueType     *rgbP,
                                 const Real32         h,
                                 const Real32         s,
                                 const Real32         v   );


    static void   convertToHSV  (const ValueType     *rgbP,
                                       Real32        &h,
                                       Real32        &s,
                                       Real32        &v   );

    static UInt32 minPart       (const ValueType     *rgbP);
    static UInt32 maxPart       (const ValueType     *rgbP);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    Color3(      void                         );
    Color3(const Vector<ValueTypeT, 3> &source);
    Color3(      ValueType              red,
                 ValueType              green,
                 ValueType              blue  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Destructors                            */
    /*! \{                                                                 */

    ~Color3(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                           Set                                */
    /*! \{                                                                 */

    void clear        (     void               );

    void setValuesRGB(const ValueType  red,
                      const ValueType  green,
                      const ValueType  blue    );

    void setValuesHSV(const Real32     h,
                      const Real32     s,
                      const Real32     v       );

    void setRandom   (      void               );
    void setRGB      (      UInt32     rgbPack );

    void setValue    (const Char8     *szString);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                           Get                                */
    /*! \{                                                                 */

          UInt32     getRGB       (void           ) const;

          void       getValuesRGB(ValueType &red,
                                  ValueType &green,
                                  ValueType &blue ) const;

          void       getValuesHSV(Real32    &h,
                                  Real32    &s,
                                  Real32    &v    ) const;

          ValueType  red         (void            ) const;
          ValueType  green       (void            ) const;
          ValueType  blue        (void            ) const;

          ValueType *getValuesRGB(void            );
    const ValueType *getValuesRGB(void            ) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
};

/*! \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
 */

template <class ValueTypeT>
class Color4 : public Vector< ValueTypeT, 4 >
{
    /*==========================  PUBLIC  =================================*/ 
  public:

    typedef ValueTypeT            ValueType;
    typedef Vector<ValueTypeT, 4> Inherited;

    static const Color4 Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Color4(      void                           );
    Color4(const Vector< ValueTypeT, 4 > &source);
    Color4(const ValueType                red,
           const ValueType                green,
           const ValueType                blue,
           const ValueType                alpha );

    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */
    
    ~Color4(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void clear        (      void           );

    void setValuesRGBA(const ValueType red,
                       const ValueType green,
                       const ValueType blue,
                       const ValueType alpha);

    void setValuesHSV (const Real32 h,
                       const Real32 s,
                       const Real32 v       );

    void setRandom    (      void           );
    void setRGBA      (      UInt32 rgbPack );    

    void setValue     (const Char8 *szString);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */
    
          UInt32    getRGBA       (void            ) const;

          void      getValuesRGBA (ValueType &red,
                                   ValueType &green,
                                   ValueType &blue,
                                   ValueType &alpha) const;

          void      getValuesHSV  (Real32    &h,
                                   Real32    &s,
                                   Real32    &v    ) const;

          ValueType red           (void            ) const;
          ValueType green         (void            ) const;
          ValueType blue          (void            ) const;
          ValueType alpha         (void            ) const;

          ValueType *getValuesRGBA(void            );
    const ValueType *getValuesRGBA(void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Operators                              */
    /*! \{                                                                 */
   
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
};

template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::ostream &operator <<(
          std::ostream       &outStream,
    const Color3<ValueTypeT> &color     );

template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::istream &operator >>(
    std::istream       &inStream,
    Color3<ValueTypeT> &color    );

template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::ostream &operator <<(
          std::ostream       &outStream,
    const Color4<ValueTypeT> &color     );

template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::istream &operator >>(
    std::istream       &inStream,
    Color4<ValueTypeT> &color    );

/*---------------------------------------------------------------------*/
/*! \name Color Types                                                  */
/*! \{                                                                 */

/*! \var OSG::Color3<OSG::Real32> Color3f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Color3
 */
typedef OSG::Color3<OSG::Real32> Color3f;


/*! \var OSG::Color3<OSG::Fixed32> Color3f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Color3
 */
typedef OSG::Color3<OSG::Fixed32> Color3fx;


/*! \var OSG::Color4<OSG::Real32> Color4f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Color4
 */
typedef OSG::Color4<OSG::Real32> Color4f;


/*! \var OSG::Color4<OSG::Fixed32> Color4f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Color4
 */
typedef OSG::Color4<OSG::Fixed32> Color4fx;


/*! \var OSG::Color3<OSG::UInt8> Color3ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Color3
 */
typedef OSG::Color3<OSG::UInt8> Color3ub;


/*! \var OSG::Color4<OSG::UInt8> Color4ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Color4
 */
typedef OSG::Color4<OSG::UInt8> Color4ub;

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGColor.inl"

#endif /* _OSG_COLOR_H_ */
