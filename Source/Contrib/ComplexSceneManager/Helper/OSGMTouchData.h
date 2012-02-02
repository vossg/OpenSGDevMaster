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

#ifndef _OSGMTOUCHDATA_H_
#define _OSGMTOUCHDATA_H_

#include "OSGContribCSMDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class Window;

class OSG_CONTRIBCSM_DLLMAPPING MTouchData
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    struct OSG_CONTRIBCSM_DLLMAPPING MTouchBlob
    {
        UInt32  _uiEvent;

        Int32   _iCursorId;
        Vec3f   _vPosition;

        UInt32  _uiCoordSys;

        MTouchBlob(){};

        MTouchBlob(UInt32 uiEvent,
                   Int32  iCursorId,
                   Real32 rX,
                   Real32 rY,
                   UInt32 uiCoordSys = MTouchData::GlobalRel);

        //~MTouchBlob(void);

        bool operator ==(const MTouchBlob &rhs) const;
        bool operator !=(const MTouchBlob &rhs) const;
        bool operator < (const MTouchBlob &rhs) const;
    };

    typedef std::vector<MTouchBlob>                 MTouchBlobStore;
    typedef std::vector<MTouchBlob>::iterator       MTouchBlobStoreIt;
    typedef std::vector<MTouchBlob>::const_iterator MTouchBlobStoreConstIt;

    typedef std::vector<UInt32>                 ActiveBlobsStore;
    typedef std::vector<UInt32>::iterator       ActiveBlobsStoreIt;
    typedef std::vector<UInt32>::const_iterator ActiveBlobsStoreConstIt;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const UInt32 AddCursor    = 0x0001;
    static const UInt32 RemoveCursor = 0x0002;
    static const UInt32 UpdateCursor = 0x0003;

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

    MTouchBlobStore  _vBlobs;
    ActiveBlobsStore _vActiveBlobs;

//    Window    *_pWindow;

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

    MTouchData(void);
    MTouchData(const MTouchData &source);

    virtual ~MTouchData(void); 

    /*------------------------- your_category -------------------------------*/

    void addCursor   (UInt32 uiId, 
                      Real32 rX, 
                      Real32 rY,
                      UInt32 uiCoordSys = GlobalRel);
    void updateCursor(UInt32 uiId, 
                      Real32 rX, 
                      Real32 rY,
                      UInt32 uiCoordSys = GlobalRel);
    void removeCursor(UInt32 uiId                  );

    /*------------------------- your_operators ------------------------------*/

    void prepSubmission(void);
    void clear         (void);
    void dump          (void) const;

    /*------------------------- your_operators ------------------------------*/

    MTouchBlobStore &getBlobStore(void);

    /*------------------------- assignment ----------------------------------*/

    void operator = (const MTouchData &rhs);
    bool operator ==(const MTouchData &rhs) const;

    /*------------------------- comparison ----------------------------------*/
};


template <>
struct FieldTraits<MTouchData> : public FieldTraitsTemplateBase<MTouchData>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<MTouchData>  Self;

    enum             { Convertible = Self::NotConvertible  };

    static OSG_CONTRIBCSM_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFMTouchData";    }

    static const Char8      *getMName     (void) { return "MFMTouchData";    }

    static       MTouchData  getDefault   (void) { return MTouchData(); }

    static       UInt32      getBinSize(const MTouchData &oObject)
    {
        return 0; //oObject.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const MTouchData *pObjectStore,
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
                          const MTouchData         &oObject)
    {
    	//pMem.putValue(oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const MTouchData        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            MTouchData        &oObject)
    {
        //pMem.getValue(oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            MTouchData        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

OSG_END_NAMESPACE

#include "OSGMTouchData.inl"

#endif
