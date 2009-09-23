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

OSG_BEGIN_NAMESPACE

template <class ValueTypeT>
const Color3<ValueTypeT> Color3<ValueTypeT>::Null;


template <class ValueTypeT> inline
void Color3<ValueTypeT>::convertFromHSV(      ValueType *rgbP,
                                        const Real32     h,
                                        const Real32     s,
                                        const Real32     v)
{
    if(rgbP == NULL)
        return;

    Int32  i;
    Real32 f;
    Real32 p;
    Real32 q;
    Real32 t;

    if(s)
    {
        f = (h == 360) ? 0.0 : (h / 60.0);
        i = Int32(f);

        f = f - Real32(i);

        p = v * (1.0 -  s           );
        q = v * (1.0 - (s *      f) );
        t = v * (1.0 - (s * (1 - f)));

        switch (i)
        {
            case 0:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(t);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(p);
                break;
            case 1:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(q);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(p);
                break;
            case 2:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(t);
                break;
            case 3:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(q);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(v);
                break;
            case 4:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(t);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(v);
                break;
            case 5:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(q);
                break;
            default:
                std::cerr << "ERROR i not in [0, 5] in Color::setHSV()!"
                     << std::endl;
                break;
        }
    }
    else
    {
        rgbP[0] = rgbP[1] = rgbP[2] =
            TypeTraits<ValueTypeT>::getPortion(v);
    }
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::convertToHSV(const ValueType *rgbP,
                                            Real32    &h,
                                            Real32    &s,
                                            Real32    &v)
{
    if(rgbP == NULL)
        return;

    const Real32 r        = TypeTraits<ValueTypeT>::getFraction(rgbP[0]);
    const Real32 g        = TypeTraits<ValueTypeT>::getFraction(rgbP[1]);
    const Real32 b        = TypeTraits<ValueTypeT>::getFraction(rgbP[2]);

    const Int32  maxIndex = maxPart(rgbP);
    const Int32  minIndex = minPart(rgbP);

    const Real32 max      = TypeTraits<ValueTypeT>::getFraction(
        rgbP[maxIndex]);

    const Real32 min      = TypeTraits<ValueTypeT>::getFraction(
        rgbP[minIndex]);

    const Real32 delta    = max - min;

    v = max;
    s = max ? (max - min) / max : 0.0;

    if(s)
    {
        switch(maxIndex)
        {
            case 0: // red part is max;
                h = (( g - b) / delta) * 60.0;
                break;
            case 1: // green part is max;
                h = (2.0 + (( b - r) / delta)) * 60.0;
                break;
            case 2: // blue part is max
                h = (4.0 + (( r - g) / delta)) * 60.0;
                break;
        }

        if(h < 0.0)
            h += 360.0;
    }
    else
    {
        h = 0.0;
    }
}


template <class ValueTypeT> inline
UInt32 Color3<ValueTypeT>::maxPart(const ValueType *rgbP)
{
    if(rgbP[0] > rgbP[1])
    {
        if(rgbP[2] > rgbP[0])
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (rgbP[2] > rgbP[1])
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}


template <class ValueTypeT> inline
UInt32 Color3<ValueTypeT>::minPart(const ValueType *rgbP)
{
    if(rgbP[0] < rgbP[1])
    {
        if(rgbP[2] < rgbP[0])
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(rgbP[2] < rgbP[1])
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}

template <class ValueTypeT> inline
Color3<ValueTypeT>::Color3(void)
{
    setValues(TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement());
}


template <class ValueTypeT> inline
Color3<ValueTypeT>::Color3(const 
        Vector<ValueTypeT, 3> &source) :
    Inherited(source)
{
}


template <class ValueTypeT> inline
Color3<ValueTypeT>::Color3(const ValueType red,
                           const ValueType green,
                           const ValueType blue)
{
    setValues(red, green, blue);
}


template <class ValueTypeT> inline
Color3<ValueTypeT>::~Color3(void)
{
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::clear(void)
{
    setValues(TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement());
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setValuesRGB(const ValueType red,
                                      const ValueType green,
                                      const ValueType blue)
{
    setValues(red, green, blue);
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setValuesHSV(const Real32 h,
                                      const Real32 s,
                                      const Real32 v)
{
    convertFromHSV(this->getValues(), h, s, v);
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setRandom(void)
{
    Real32 rf = 1.0 / Real32(RAND_MAX);

    setValuesRGB(TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                 TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                 TypeTraits<ValueTypeT>::getPortion(rf * rand()));
}

/*! method to set the rgb values (BBGGRR)
 */

template <class ValueTypeT> inline
void Color3<ValueTypeT>::setRGB(UInt32 rgbPack)
{
    for(Int32 i = 0; i < 3; ++i)
    {
        Real32 rTmp = Real32(rgbPack & 255) / 255.0f;

        (*this)[i] = TypeTraits<ValueTypeT>::getPortion(rTmp);

        rgbPack >>= 8;
    }
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setValue(const Char8 *szString)
{
    this->setValueFromCString(szString);
}


/*! method to get a packed rgb value (BBGGRR)
 */

template <class ValueTypeT> inline
UInt32 Color3<ValueTypeT>::getRGB(void) const
{
    UInt32 pack = 0;

    for(Int32 i = 2; i >= 0; --i)
    {
        pack = (pack << 8) | 
            Int32(TypeTraits<ValueTypeT>::getFraction((*this)[i]) *
                  255.0f                                          +
                  0.5f                                            );
    }

    return pack;
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::getValuesRGB(ValueType &red,
                                      ValueType &green,
                                      ValueType &blue) const
{
    red   = (*this)[0];
    green = (*this)[1];
    blue  = (*this)[2];
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::getValuesHSV(Real32 &h,
                                      Real32 &s,
                                      Real32 &v) const
{
    convertToHSV(this->getValues(), h, s, v);
}


template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType
    Color3<ValueTypeT>::red(void) const
{
    return (*this)[0];
}

template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType
    Color3<ValueTypeT>::green(void) const
{
    return (*this)[1];
}

template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType
    Color3<ValueTypeT>::blue(void) const
{
    return (*this)[2];
}


template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType *
    Color3<ValueTypeT>::getValuesRGB(void)
{
    return this->getValues();
}

template <class ValueTypeT> inline
const typename Color3<ValueTypeT>::ValueType *
    Color3<ValueTypeT>::getValuesRGB(void) const
{
    return this->getValues();
}




template <class ValueTypeT>
const Color4<ValueTypeT> Color4<ValueTypeT>::Null;


template <class ValueTypeT> inline
Color4<ValueTypeT>::Color4(void)
{
    setValues(TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement());
}


template <class ValueTypeT> inline
Color4<ValueTypeT>::Color4(const 
        Vector<ValueTypeT, 4> &source) :
    Inherited(source)
{
}


template <class ValueTypeT> inline
Color4<ValueTypeT>::Color4(const ValueType red,
                           const ValueType green,
                           const ValueType blue,
                           const ValueType alpha)
{
    setValues(red, green, blue, alpha);
}


template <class ValueTypeT> inline
Color4<ValueTypeT>::~Color4(void)
{
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::clear(void)
{
    setValues(TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement(),
              TypeTraits<ValueTypeT>::getZeroElement());
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::setValuesRGBA(const ValueType red,
                                       const ValueType green,
                                       const ValueType blue,
                                       const ValueType alpha)
{
    setValues(red, green, blue, alpha);
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::setValuesHSV(const Real32 h,
                                      const Real32 s,
                                      const Real32 v)
{
    Color3<ValueType>::convertFromHSV(this->getValues(), h, s, v);

    (*this)[3] = TypeTraits<ValueTypeT>::getOneElement();
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::setRandom(void)
{
    Real32 rf = 1.0 / Real32(RAND_MAX);

    setValuesRGBA(TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                  TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                  TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                  TypeTraits<ValueTypeT>::getPortion(rf * rand()));
}

/*! method to set the rgb values (ABGGRR)
 */

template <class ValueTypeT> inline
void Color4<ValueTypeT>::setRGBA(UInt32 rgbPack)
{
    for(Int32 i = 0; i < 4; ++i)
    {
        Real32 rTmp = Real32(rgbPack & 255) / 255.0f;

        (*this)[i] = TypeTraits<ValueTypeT>::getPortion(rTmp);

        rgbPack >>= 8;
    }
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::setValue(const Char8 *szString)
{
    this->setValueFromCString(szString);
}



/*! method to get a packed rgb value (ABGGRR)
 */

template <class ValueTypeT> inline
UInt32 Color4<ValueTypeT>::getRGBA(void) const
{
    UInt32 pack = 0;

    for(Int32 i = 3; i >= 0; --i)
    {
        pack = (pack << 8) | 
            Int32(TypeTraits<ValueTypeT>::getFraction((*this)[i]) *
                  255.0f                                        +
                  0.5f                                           );
    }

    return pack;
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::getValuesRGBA(ValueType &red,
                                       ValueType &green,
                                       ValueType &blue,
                                       ValueType &alpha) const
{
    red   = (*this)[0];
    green = (*this)[1];
    blue  = (*this)[2];
    alpha = (*this)[3];
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::getValuesHSV(Real32 &h,
                                      Real32 &s,
                                      Real32 &v) const
{
    Color3<ValueType>::convertToHSV(this->getValues(), h, s, v);
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::red(void) const
{
    return (*this)[0];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::green(void) const
{
    return (*this)[1];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::blue(void) const
{
    return (*this)[2];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::alpha(void) const
{
    return (*this)[3];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType *
    Color4<ValueTypeT>::getValuesRGBA(void)
{
    return this->getValues();
}


template <class ValueTypeT> inline
const typename Color4<ValueTypeT>::ValueType *
    Color4<ValueTypeT>::getValuesRGBA(void) const
{
    return this->getValues();
}

OSG_END_NAMESPACE
