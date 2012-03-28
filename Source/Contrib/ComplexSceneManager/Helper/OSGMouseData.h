/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifndef _OSGMOUSEDATA_H_
#define _OSGMOUSEDATA_H_

#include "OSGContribCSMDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"

OSG_BEGIN_NAMESPACE

class Window;

class OSG_CONTRIBCSM_DLLMAPPING MouseData
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const Int32 ButtonDown      = 0x0000;
    static const Int32 ButtonUp        = 0x0001;

    static const Int32 LeftButton      = 0x0000;
    static const Int32 MiddleButton    = 0x0001;
    static const Int32 RightButton     = 0x0002;
    static const Int32 WheelUpButton   = 0x0003;
    static const Int32 WheelDownButton = 0x0004;

    static const Int32 NoModifier      = 0x0001;
    static const Int32 ShiftActive     = 0x0002;
    static const Int32 CtrlActive      = 0x0004;
    static const Int32 AltActive       = 0x0008;

    static const UInt32 AbsValues       = 0x0001;
    static const UInt32 RelValues       = 0x0002;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    //! prohibit default function (move to 'public' if needed) 

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Int32      _iButton;
    Int32      _iState;
    Int32      _iModifier;
    Real32     _rX;
    Real32     _rY;
    Window    *_pWindow;
    UInt32     _uiMode;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    MouseData(void);
    MouseData(const MouseData &source);

    ~MouseData(void); 

    /*------------------------- your_category -------------------------------*/

    void setData(Int32      iButton, 
                 Int32      iState,
                 Int32      iModifier,
                 Real32     x,       
                 Real32     y,
                 Window    *pWindow,
                 UInt32     uiMode = AbsValues);

    void setData(Real32  x,       
                 Real32  y,
                 Window *pWindow,
                 UInt32  uiMode = AbsValues);

    /*------------------------- your_operators ------------------------------*/

    Int32      getButton  (void) const;
    Int32      getState   (void) const;
    Int32      getModifier(void) const;
    Real32     getX       (void) const;
    Real32     getY       (void) const;
    Window    *getWindow  (void) const;
    UInt32     getMode    (void) const;

    /*------------------------- assignment ----------------------------------*/

    void operator = (const MouseData &rhs);
    bool operator ==(const MouseData &rhs) const;

    /*------------------------- comparison ----------------------------------*/
};


template <>
struct FieldTraits<MouseData> : public FieldTraitsTemplateBase<MouseData>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<MouseData>  Self;

    enum             { Convertible = Self::NotConvertible  };

    static OSG_CONTRIBCSM_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFMouseData";    }

    static const Char8      *getMName     (void) { return "MFMouseData";    }

    static       MouseData   getDefault   (void) { return MouseData(); }

#if 0
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
#endif

    static       UInt32    getBinSize (const MouseData &oObject)
    {
        return 0; //oObject.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const MouseData *pObjectStore,
                                             UInt32     uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }


    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const MouseData           &oObject)
    {
    	//pMem.putValue(oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const MouseData         *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            MouseData         &oObject)
    {
        //pMem.getValue(oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            MouseData         *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

OSG_END_NAMESPACE

#include "OSGMouseData.inl"

#endif
