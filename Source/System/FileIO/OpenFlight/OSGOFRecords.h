/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGOFRECORDS_H_
#define _OSGOFRECORDS_H_

#include "boost/function.hpp"

#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGSingletonHolder.h"
#include "OSGNode.h"
#include "OSGMaterialChunk.h"
#include "OSGMemoryObject.h"

#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OFRecord;
class OFDatabase;

class Geometry;

/*! \brief General VRML Node Desc
    \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */ 

struct OFRecordHeader
{
    UInt16 sOpCode;
    UInt16 sLength;

    bool read(std::istream &is)
    {
        is.read(reinterpret_cast<char *>(&sOpCode), 2);
        is.read(reinterpret_cast<char *>(&sLength), 2);

        sOpCode = osgNetToHost(sOpCode);
        sLength = osgNetToHost(sLength);

        return is.good();
    }
};

/*! \ingroup GrpFileIOOpenFlight
 */

typedef TransitPtr<OFRecord> OFRecordTransitPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFRecordFactoryBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    typedef boost::function<
        OFRecordTransitPtr (const OFRecordHeader &,
                                  OFDatabase     & )> CreateRecord;

    /*! \nohierarchy
     */
    class OSG_FILEIO_DLLMAPPING RegisterRecord
    {
      public:

        RegisterRecord(CreateRecord fCreate,
                       UInt16       sRecordOpCode);
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    void registerRecord(CreateRecord fRecord,
                        UInt16       sRecordOpCode);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Prototypes                                 */
    /*! \{                                                                 */

    OFRecordTransitPtr createRecord(const OFRecordHeader &oHeader,
                                          OFDatabase     &oDB     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      FieldValue                              */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    template <class SingletonT>
    friend class SingletonHolder;

    typedef std::map<UInt16,
                     CreateRecord> NameRecordCreateMap;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OFRecordFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OFRecordFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    NameRecordCreateMap _mRegisteredRecords;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    OFRecordFactoryBase(const OFRecordFactoryBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OFRecordFactoryBase &source);
};

#if defined(WIN32)
OSG_FILEIO_EXPIMP_TMPL
template class OSG_FILEIO_DLLMAPPING SingletonHolder<OFRecordFactoryBase>;
#endif

/*! \ingroup GrpFileIOOpenFlight
 */

typedef SingletonHolder<OFRecordFactoryBase> OFRecordFactory;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFRecord : public MemoryObject
{
  public:
    /*---------------------------------------------------------------------*/

    enum CategoryE
    {
      RC_Control      = 0,
      RC_Primary      = 1,
      RC_Ancillary    = 2,
      RC_Continuation = 3,

      RC_Undefined    = 4
    };

    /*---------------------------------------------------------------------*/

    static const Char8 *getOpCodeString  (UInt16    sOpCode);
    static const Char8 *getCategoryString(CategoryE cat    );

    /*---------------------------------------------------------------------*/

    virtual UInt16       getOpCode        (void) const = 0;
            const Char8 *getOpCodeString  (void) const;

    virtual CategoryE    getCategory      (void) const = 0;
            const Char8 *getCategoryString(void) const;

    /*---------------------------------------------------------------------*/

    virtual bool read        (std::istream &is      );
    virtual bool readContinue(std::istream &is,
                              UInt16        uiLength);

    virtual NodeTransitPtr convertToNode(void);

    virtual bool           addChild     (OFRecord *pChild) = 0;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/

    OFDatabase &_oDB;
    UInt16      _sLength;

    /*---------------------------------------------------------------------*/

    void readChar8 (std::istream &is, Char8  *cVal, UInt32 iSize);

    /*---------------------------------------------------------------------*/

    template<class ValueT>
    UInt32 readVal(std::istream &is,  ValueT &val);

    /*---------------------------------------------------------------------*/

             OFRecord(const OFRecordHeader &oHeader,
                            OFDatabase     &oDB    );
    virtual ~OFRecord(void);
};

/*! \ingroup GrpFileIOOpenFlight
 */

typedef RefCountPtr<OFRecord, MemObjRefCountPolicy> OFRecordRCPtr;

//---------------------------------------------------------------------------
//  Forward declarations
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
 */
class OFPrimaryRecord;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFPrimaryRecord,
                    MemObjRefCountPolicy>  OFPrimaryRecordRCPtr;

/*! \ingroup GrpFileIOOpenFlight
 */
class OFAncillaryRecord;
/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFAncillaryRecord,
                    MemObjRefCountPolicy>  OFAncillaryRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OFPrimaryRecord : public OFRecord
{
  public:
    static const CategoryE Category = RC_Primary;

    /*---------------------------------------------------------------------*/
    
    static  CategoryE getClassCategory(void);
    virtual CategoryE getCategory     (void) const;

    /*---------------------------------------------------------------------*/

    virtual bool addChild(OFRecord *pChild);

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;

  protected:
    typedef OFRecord  Inherited;

    typedef std::vector<OFPrimaryRecordRCPtr  >  PrimaryStore;
    typedef std::vector<OFAncillaryRecordRCPtr>  AncillaryStore;

             OFPrimaryRecord(const OFRecordHeader &oHeader,
                                   OFDatabase     &oDB    );
    virtual ~OFPrimaryRecord(void                         ) = 0;

    PrimaryStore   _primaryChildren;
    AncillaryStore _ancillaryChildren;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OFAncillaryRecord : public OFRecord
{
  public:
    static const CategoryE Category = RC_Ancillary;

    /*---------------------------------------------------------------------*/

    static  CategoryE getClassCategory(void);
    virtual CategoryE getCategory     (void) const;

    /*---------------------------------------------------------------------*/

    virtual bool           addChild     (OFRecord *pChild);
    virtual NodeTransitPtr convertToNode(void            );
    virtual NodeTransitPtr convert      (Node     *pNode );

  protected:
    typedef OFRecord  Inherited;

             OFAncillaryRecord(const OFRecordHeader &oHeader,
                                     OFDatabase     &oDB    );
    virtual ~OFAncillaryRecord(void                         ) = 0;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OFControlRecord : public OFRecord
{
  public:
    static const CategoryE Category = RC_Control;

    /*---------------------------------------------------------------------*/

    static  CategoryE getClassCategory(void);
    virtual CategoryE getCategory     (void) const;

    /*---------------------------------------------------------------------*/

    virtual bool addChild(OFRecord *pChild);

  protected:
    typedef OFRecord  Inherited;

             OFControlRecord(const OFRecordHeader &oHeader,
                                   OFDatabase     &oDB    );
    virtual ~OFControlRecord(void                         ) = 0;
};

/*! \ingroup GrpFileIOOpenFlight
 */
typedef RefCountPtr<OFControlRecord,
                    MemObjRefCountPolicy>  OFControlRecordRCPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOOpenFlight
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OFUnknownRecord : public OFRecord
{
  protected:

    typedef OFRecord Inherited;

    /*---------------------------------------------------------------------*/

    UInt16                     _sOpCode;
    std::vector<OFRecordRCPtr> _vChildren;

    /*---------------------------------------------------------------------*/

             OFUnknownRecord(const OFRecordHeader &oHeader,
                                   OFDatabase     &oDB    );
    virtual ~OFUnknownRecord(void                         );

    /*---------------------------------------------------------------------*/

    friend class OFRecordFactoryBase;

  public:

    virtual bool           read         (std::istream &is    );
    virtual NodeTransitPtr convertToNode(void                );
    virtual bool           addChild     (OFRecord     *pChild);

    /*---------------------------------------------------------------------*/

    virtual UInt16    getOpCode  (void) const;
    virtual CategoryE getCategory(void) const;

    /*---------------------------------------------------------------------*/

    virtual void dump(UInt32 uiIndent) const;
};

OSG_END_NAMESPACE

#include "OSGOFRecords.inl"

#endif /* _OSGOFRECORDS_H_ */
