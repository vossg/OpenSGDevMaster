/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGBASEFIELDTRAITS_H_
#define _OSGBASEFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGColor.h"
#include "OSGTime.h"
#include "OSGSphereVolume.h"
#include "OSGBoxVolume.h"
#include "OSGPlane.h"
#include "OSGGL.h"
#include "OSGGLDefineMapper.h"

#include <iomanip>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Color3f> : public FieldTraitsVec3TemplateBase<Color3f>
{
  private:

    static  DataType             _type;

  public:

    typedef FieldTraits<Color3f>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFColor3f";   }

    static const Char8    *getMName     (void) { return "MFColor3f";   }

    static const Color3f   getDefault   (void) { return Color3f();     }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Color3fx> : public FieldTraitsVec3TemplateBase<Color3fx>
{
  private:

    static  DataType              _type;

  public:

    typedef FieldTraits<Color3fx>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFColor3fx";   }

    static const Char8    *getMName     (void) { return "MFColor3fx";   }

    static const Color3fx  getDefault   (void) { return Color3fx();     }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Color4f> : public FieldTraitsVec4TemplateBase<Color4f>
{
  private:
    
    static  DataType             _type;
    
  public:

    typedef FieldTraits<Color4f>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFColor4f";   }

    static const Char8    *getMName     (void) { return "MFColor4f";   }

    static       Color4f   getDefault   (void){ return Color4f();      }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Color4fx> : public FieldTraitsVec4TemplateBase<Color4fx>
{
  private:
    
    static  DataType              _type;
    
  public:

    typedef FieldTraits<Color4fx>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFColor4fx";   }

    static const Char8    *getMName     (void) { return "MFColor4fx";   }

    static       Color4fx  getDefault   (void){ return Color4fx();      }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Color3ub> : public FieldTraitsVec3TemplateBase<Color3ub>
{
  private:

    static  DataType              _type;

  public:

    typedef FieldTraits<Color3ub>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFColor3ub";  }
    static const Char8    *getMName     (void) { return "MFColor3ub";  }

    static       Color3ub  getDefault   (void) { return Color3ub();    }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Color4ub> : public FieldTraitsVec4TemplateBase<Color4ub>
{
  private:

    static  DataType              _type;

  public:

    typedef FieldTraits<Color4ub>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFColor4ub";  }

    static const Char8    *getMName     (void) { return "MFColor4ub";  }

    static       Color4ub  getDefault   (void) { return Color4ub();    }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<std::string> : public FieldTraitsTemplateBase<std::string>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<std::string>  Self;

    enum             { Convertible = (Self::FromStringConvertible |
                                      Self::ToStreamConvertible   )  };

    static OSG_BASE_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFString";    }

    static const Char8      *getMName     (void) { return "MFString";    }

    static       std::string getDefault   (void) { return std::string(); }

    static void putToStream(const std::string &val,
                                  OutStream   &outStr)
    {
        outStr << "\"";
        outStr << val;
        outStr << "\"";
    }

    static bool      getFromCString(      std::string  &outVal,
                                    const Char8       *&inVal)
    {
        outVal.assign(inVal);

        return true;
    }

    static       UInt32    getBinSize (const std::string &oObject)
    {
        return oObject.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const std::string *pObjectStore,
                                                  UInt32  uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }


    static void copyToBin(           BinaryDataHandler   &pMem, 
                          const std::string              &oObject)
    {
    	pMem.putValue(oObject);
    }

    static void copyToBin(           BinaryDataHandler &pMem, 
                          const std::string            *pObjectStore,
                                     UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(     BinaryDataHandler &pMem, 
                            std::string            &oObject)
    {
        pMem.getValue(oObject);
    }

    static void copyFromBin(     BinaryDataHandler &pMem, 
                            std::string            *pObjectStore,
                                 UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Time, 1> : public FieldTraitsPODTemplateBase<Time, 1>
{
  private:

    static  DataType             _type;

  public:

    typedef FieldTraits<Time, 1>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFTime";      }

    static const Char8    *getMName     (void) { return "MFTime";      }

    static       Time      getDefault   (void) { return Time();        }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<BoxVolume> : 
    public FieldTraitsTemplateBase<BoxVolume>
{
  private:

    static  DataType                   _type;

  public:

    typedef FieldTraits<BoxVolume>  Self;

    enum                  { Convertible = (Self::FromStringConvertible |
                                           Self::ToStreamConvertible   )     };

    static OSG_BASE_DLLMAPPING
                 DataType  &getType     (void);

    static const Char8     *getSName    (void) { return "SFBoxVolume"; }

    static const Char8     *getMName    (void) { return "MFBoxVolume"; }

    static const BoxVolume  getDefault  (void) { return BoxVolume();   }


    static bool getFromCString(      BoxVolume  &outVal,
                               const Char8     *&inVal)
    {
        Real32 valStore[  6];
        Char8  str     [256];

        UInt32  length = strlen(inVal);
        Char8  *c      = str;
    
        if(length > 256)
        {
            std::cerr << "FieldDataTraits<BoxVolume>::getFromString(): "
                      << "Input too long" << std::endl;

            return false;
        }

        strncpy(str, inVal, length);

        while(*c != '\0')
        {
            if(*c == '[')
                *c = ' ';
            if(*c == ']')
                *c = ' ';
            if(*c == ',')
                *c = ' ';

            c++;
        }
        
        Int32 iState;

        Int16 count = sscanf(str, "%d %f %f %f %f %f %f",
                             &iState,
                             &valStore[0], 
                             &valStore[1], 
                             &valStore[2],
                             &valStore[3], 
                             &valStore[4], 
                             &valStore[5]);
        
        if(count == 7)
        {
            outVal.setState(iState);

            outVal.setBounds(valStore[0],
                             valStore[1],
                             valStore[2],
                             valStore[3],
                             valStore[4],
                             valStore[5]);

            return true;
        }
        else
        {
            outVal.setBounds(0.f, 0.f, 0.f, 
                             0.f, 0.f, 0.f);
            
            return false;
        }
    }


    static void putToStream(const BoxVolume &val,
                                  OutStream &str)
    {
        Pnt3f min, max;

        typedef TypeTraits<Pnt3f::ValueType> TypeTrait;
        typedef TypeTraits<UInt16>           StateTypeTrait;

        StateTypeTrait::putToStream(val.getState(), str);
        str << " ";

        val.getBounds(min, max);
        
        TypeTrait::putToStream(min[0], str);
        str << " ";
        
        TypeTrait::putToStream(min[1], str);
        str << " ";
        
        TypeTrait::putToStream(min[2], str);
        str << " ";
        
        TypeTrait::putToStream(max[0], str);
        str << " ";
        
        TypeTrait::putToStream(max[1], str);
        str << " ";
        
        TypeTrait::putToStream(max[2], str);
    }

    static UInt32 getBinSize(const BoxVolume &oObject)
    {
        UInt32  size = sizeof(UInt16);

        size += sizeof(Pnt3f) + sizeof(Pnt3f);

        return size;
    }


    static UInt32 getBinSize(const BoxVolume *pObjectStore,
                                   UInt32     uiNumObjects)
    {
        UInt32 size = 0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const BoxVolume         &oObject)
    {
        
        UInt16 state = oObject.getState();
        
        pMem.putValue(state);
        
        pMem.putValues(&(oObject.getMin()[0]), 3);
        pMem.putValues(&(oObject.getMax()[0]), 3);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const BoxVolume         *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            BoxVolume         &oObject)
    {
        Pnt3f min,max;
        UInt16 state;
        
        pMem.getValue (state       );
        pMem.getValues(&(min[0]), 3);
        pMem.getValues(&(max[0]), 3);
        
        oObject.setBounds(min, max);
        oObject.setState (state   );
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            BoxVolume         *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<BitVector, 1> : public FieldTraitsTemplateBase<BitVector, 1>
{
  private:

    static  DataType                  _type;

  public:

    typedef FieldTraits<BitVector, 1>  Self;

    enum              { Convertible = Self::NotConvertible             };

    static OSG_BASE_DLLMAPPING
                 DataType  &getType (void);

    static const Char8     *getSName(void)   { return "SFBitVector";   }

    static const Char8     *getMName(void)   { return "MFBitVector";   }

    static       BitVector  getDefault(void) { return BitVector();     }
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<GLenum, 1> : public FieldTraitsPODTemplateBase<GLenum, 1>
{
  private:

    static  DataType               _type;

  public:

    typedef FieldTraits<GLenum, 1>  Self;

    enum             { Convertible = (Self::ToStreamConvertible  |
                                      Self::FromStringConvertible)     };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFGLenum";          }
    static const Char8    *getMName     (void) { return "MFGLenum";          }

    static       GLenum    getDefault   (void) { return 0;                   }

    static void putToStream(const GLenum    &val,
                                  OutStream &str)
    {
#ifdef OSG_GL_DEFMAPPER
        const std::string &oVal = GLDefineMapper::the()->toString(val);

        str << "GL_" << oVal;
#else
        str << std::setbase(16);

        str << "0x";
        TypeTraits<GLenum>::putToStream(val, str);

        str << std::setbase(10);
#endif
    }

#ifdef OSG_GL_DEFMAPPER
    static bool getFromCString(      GLenum   &outVal,
                               const Char8   *&inVal )
    {
        outVal = GLDefineMapper::the()->fromString(inVal);

        return true;
    }
#endif
};


/*! \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase 
 */

template <>
struct FieldTraits<Plane> : public FieldTraitsTemplateBase<Plane>
{
  private:

    static  DataType           _type;

  public:

    typedef FieldTraits<Plane>  Self;

    enum             { Convertible = Self::NotConvertible               };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFPlane";      }

    static const Char8    *getMName     (void) { return "MFPlane";      }

    static       Plane     getDefault   (void) { return Plane();        }

    static       UInt32    getBinSize (const Plane &)
    {
        return sizeof(Real32) * 4;
    }

    static       UInt32    getBinSize (const Plane     *,
                                             UInt32     uiNumObjects)
    {
        return sizeof(Real32) * 4 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Plane            &oObject)
    {
        const Vec3f  &normal   = oObject.getNormal            ();
              Real32  distance = oObject.getDistanceFromOrigin();

        pMem.putValues(&normal[0], 3);
        pMem.putValue ( distance    );
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const Plane             *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Plane             &oObject)
    {
        Vec3f  normal;
        Real32 distance;

        pMem.getValues(&normal[0], 3);
        pMem.getValue ( distance    );

        oObject.set(normal, distance);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            Plane             *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

OSG_END_NAMESPACE

#endif /* _OSGBASEFIELDTRAITS_H_ */

