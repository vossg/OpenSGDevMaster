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

#ifndef _OSGGESTUREDATA_H_
#define _OSGGESTUREDATA_H_

#include "OSGContribCSMDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class Window;
class CSMWindow;

class OSG_CONTRIBCSM_DLLMAPPING GestureData
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    struct OSG_CONTRIBCSM_DLLMAPPING GestureBlob
    {
        UInt32  _uiEvent;

        Int32   _iGestureId;
        Vec3f   _vPosition;

        UInt32  _uiCoordSys;

        std::string _szGesture;

        GestureBlob(){};

        GestureBlob(UInt32 uiEvent,
                   Int32  iGestureId,
                   const std::string& szGesture, 
                   Real32 rX,
                   Real32 rY,
                   UInt32 uiCoordSys = GestureData::GlobalRel);

        //~GestureBlob(void);

        bool operator ==(const GestureBlob &rhs) const;
        bool operator !=(const GestureBlob &rhs) const;
        bool operator < (const GestureBlob &rhs) const;
    };

    typedef std::vector<GestureBlob>                 GestureBlobStore;
    typedef std::vector<GestureBlob>::iterator       GestureBlobStoreIt;
    typedef std::vector<GestureBlob>::const_iterator GestureBlobStoreConstIt;

    typedef std::vector<UInt32>                 ActiveBlobsStore;
    typedef std::vector<UInt32>::iterator       ActiveBlobsStoreIt;
    typedef std::vector<UInt32>::const_iterator ActiveBlobsStoreConstIt;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const UInt32 AddGesture    = 0x0001;
    static const UInt32 RemoveGesture = 0x0002;
    static const UInt32 UpdateGesture = 0x0003;

    static const UInt32 GlobalRel    = 0x0001;
    static const UInt32 GlobalAbs    = 0x0002;
    static const UInt32 WindowRel    = 0x0010;
    static const UInt32 WindowAbs    = 0x0020;

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

    GestureBlobStore  _vBlobs;
    ActiveBlobsStore _vActiveBlobs;

    Window    *_pWindow;
    CSMWindow    *_pCSMWindow;

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

    GestureData(void);
    GestureData(const GestureData &source);

    virtual ~GestureData(void); 

    /*------------------------- your_category -------------------------------*/

    void setWindow( Window* pWindow );
    Window* getWindow( void ) const;

    void setCSMWindow( CSMWindow* pCSMWindow );
    CSMWindow* getCSMWindow( void ) const;

    void addGesture   (UInt32 uiId, 
                      const std::string& szGesture, 
                      Real32 rX, 
                      Real32 rY,
                      UInt32 uiCoordSys = GlobalRel);
    void updateGesture(UInt32 uiId, 
                      const std::string& szGesture, 
                      Real32 rX, 
                      Real32 rY,
                      UInt32 uiCoordSys = GlobalRel);
    void removeGesture(UInt32 uiId                  );

    /*------------------------- your_operators ------------------------------*/

    void prepSubmission(void);
    void clear         (void);
    void dump          (void) const;

    /*------------------------- your_operators ------------------------------*/

    GestureBlobStore &getBlobStore(void);

    /*------------------------- assignment ----------------------------------*/

    void operator = (const GestureData &rhs);
    bool operator ==(const GestureData &rhs) const;

    /*------------------------- comparison ----------------------------------*/
};


template <>
struct FieldTraits<GestureData> : public FieldTraitsTemplateBase<GestureData>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<GestureData>  Self;

    enum             { Convertible = Self::NotConvertible  };

    static OSG_CONTRIBCSM_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFGestureData";    }

    static const Char8      *getMName     (void) { return "MFGestureData";    }

    static       GestureData  getDefault   (void) { return GestureData(); }

    static       UInt32      getBinSize(const GestureData &oObject)
    {
        return 0; //oObject.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const GestureData *pObjectStore,
                                             UInt32      uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }


    static void copyToBin(      BinaryDataHandler  &pMem, 
                          const GestureData         &oObject)
    {
    	//pMem.putValue(oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const GestureData        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            GestureData        &oObject)
    {
        //pMem.getValue(oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            GestureData        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

OSG_END_NAMESPACE

#include "OSGGestureData.inl"

#endif
