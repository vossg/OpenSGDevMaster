/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGNFIOBASE_H_
#define _OSGNFIOBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <iostream>

#include "OSGFileIODef.h"
#include "OSGNode.h"

#include "OSGBinaryDataHandler.h"

#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"
#include "OSGAttachmentMapSFields.h"

#include "OSGNFIOOptions.h"

OSG_BEGIN_NAMESPACE

/* \brief NFIOBase class.
          Base class for native file io.
*/

class OSG_FILEIO_DLLMAPPING NFIOBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    NFIOBase                     (const char *name);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~NFIOBase            (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Read/Write                                */
    /*! \{                                                                 */

    static NodePtr  read    (std::istream &is,
                             const std::string &options);
    static bool     write   (const NodePtr &node, std::ostream &os,
                             const std::string &options);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Options                                 */
    /*! \{                                                                 */

    static const NFIOOptions &getOptions(void);

    /*! \}                                                                 */
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual void              initialise(void);
    virtual void              terminate(void);

    /*! \}                                                                 */
    /*! \name                      Read                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr readFC(const std::string &typeName) = 0;

    static std::string readFCFields    (const FieldContainerPtr &fc,
                                        const std::string &exclude = "",
                                        const std::string &endMarkers = "");
    static void readSFFieldContainerPtr(const FieldContainerPtr &fc,
                                        UInt32 fieldId,
                                        const Field *field                );
    static void readMFFieldContainerPtr(const FieldContainerPtr &fc,
                                        UInt32 fieldId,
                                        const Field *field                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Write                                     */
    /*! \{                                                                 */

    virtual void writeFC(const FieldContainerPtr &fc) = 0;

    static void writeFCFields           (const FieldContainerPtr &fc,
                                         const std::string &exclude = "",
                                         bool endMarker = true);
    static void writeSFFieldContainerPtr(SFFieldContainerPtr *field  );
    static void writeMFFieldContainerPtr(MFFieldContainerPtr *field  );
    static void writeSFAttachmentMap    (SFFieldContainerAttachmentPtrMap *amap);
    //static void writeSFAttachmentMap    (SFAttachmentMap *amap       );

    static void readEndMarker           (void                        );
    static void writeEndMarker          (void                        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    PostProcess                               */
    /*! \{                                                                 */

    virtual void postProcessFC(const FieldContainerPtr &fc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Skip                                      */
    /*! \{                                                                 */

    static void skipFCFields(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Binary Read/Write Handler                    */
    /*! \{                                                                 */

    /*! Helper class to put BinaryDataHandler interface on an istream. */
    class BinaryReadHandler : public BinaryDataHandler
    {
      public:
        BinaryReadHandler(std::istream &is);
        virtual ~BinaryReadHandler();

        void read(MemoryHandle mem, UInt32 size);
        void skip(UInt32 size);

      private:

        std::vector<UInt8>  _readMemory;
        std::istream &_is;

        BinaryReadHandler(const BinaryReadHandler &source);
        void operator =(const BinaryReadHandler &source);
    };

    /*! Helper class to put BinaryDataHandler interface on an ostream. */
    class BinaryWriteHandler : public BinaryDataHandler
    {
      public:
        BinaryWriteHandler(std::ostream &os);
        virtual ~BinaryWriteHandler();

        void write(MemoryHandle mem, UInt32 size);

      private:

        std::vector<UInt8> _writeMemory;
        std::ostream &_os;

        BinaryWriteHandler(const BinaryWriteHandler &source);
        void operator =(const BinaryWriteHandler &source);
    };

    static BinaryReadHandler    *_in;
    static BinaryWriteHandler   *_out;

    UInt16 _version;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
//private:

    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initialiseAll(void);
    static void terminateAll(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Read                                    */
    /*! \{                                                                 */

    static FieldContainerPtr readFieldContainer(void);

    /*! Wrap info about an fc.
    * This class is used to store information about
    * fc's that we need to revisit to fix up their ptrs.
    */
    struct fcInfo
    {
        fcInfo(const FieldContainerPtr &fc,
               UInt32 fieldId, UInt32 id, const Field *field            );
        fcInfo(const FieldContainerPtr &fc,
               UInt32 fieldId, const Field *field                       );

        bool isMultiField(void) const;

        FieldContainerPtr   _fc;          /*!< The fc we reference. */
        UInt32              _fieldId;     /*!< Id of the field that needs patched. */
        UInt32              _id;          /*!< fcptr id, if 0, we wrap a mfield. */
        const Field        *_field;       /*!< ptr to the field in the fc. */
        std::vector<UInt32>   _ids;       /*!< If mfield, list of ids to replace. */
    };

    static void addReadFieldContainer  (const FieldContainerPtr &fc,
                                        UInt32 id                   );
    static void chargeFieldPtr         (const fcInfo &info          );

    typedef std::map<UInt32, UInt32> fcMap;

    static fcMap                _fcMap;      /*!< Map file ptr id to instatiated ptr id. */
    static std::list<fcInfo>    _fieldList;  /*!< List of fields that need ptr remapping. */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Write                                  */
    /*! \{                                                                 */

    static void getFCCount          (const FieldContainerPtr &fc, UInt32 &count);
    static void writeFieldContainer (const FieldContainerPtr &fc);
    static void writeFCId           (const FieldContainerPtr &fc);

    //static UInt32                        _id;
    static std::list<FieldContainerPtr>  _fcList;        /*!< List of all fc's encountered. */
    static std::set<UInt32>              _fcSet;         /*!< Set of all fc ids encountered. */
    //typedef std::map<FieldContainerPtr, UInt32> IdMap;
    //static IdMap                         _ids;
    static UInt16                        _header_version;

    static NFIOOptions _options;

};

OSG_END_NAMESPACE

#endif /* _OSGNFIOBASE_H_ */
