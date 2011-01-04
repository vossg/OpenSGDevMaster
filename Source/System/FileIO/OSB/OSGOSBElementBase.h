/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#ifndef _OSGOSBELEMENTBASE_H_
#define _OSGOSBELEMENTBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGFieldContainer.h"
#include "OSGOSBLog.h"

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

class OSBRootElement;

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBElementBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    /*! \nohierarchy
     */
    class BinaryReadHandler : public BinaryDataHandler
    {
      public:
        BinaryReadHandler(std::istream &inStream);

        virtual ~BinaryReadHandler(void);

        inline  void skip(UInt32       size            );

      protected:
        virtual void read(MemoryHandle mem, UInt32 size);

      private:
        std::vector<UInt8>  _readMemory;
        std::istream       &_is;

        BinaryReadHandler(const BinaryReadHandler &source);
        void operator =  (const BinaryReadHandler &source);
    };

    /*! \nohierarchy
     */
    class BinaryWriteHandler : public BinaryDataHandler
    {
      public:
        BinaryWriteHandler(std::ostream &outStream);

        virtual ~BinaryWriteHandler(void);

      protected:
        virtual void write(MemoryHandle mem, UInt32 size);

      private:
        std::vector<UInt8>  _writeMemory;
        std::ostream       &_os;

        BinaryWriteHandler(const BinaryWriteHandler &source);
        void operator =   (const BinaryWriteHandler &source);
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */

    static const UInt16      OSGOSBHeaderVersion100;
    static const UInt16      OSGOSBHeaderVersion200;
//     static const UInt16      OSGOSBHeaderVersion201;

    static const std::string OSGOSB_HEADER_ID_1;
    static const std::string OSGOSB_HEADER_ID_2;
//     static const std::string OSGOSB_HEADER_ID_201;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBElementBase(OSBRootElement *root, const UInt16 version);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBElementBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name State access                                                 */
    /*! \{                                                                 */

    inline FieldContainer       *getContainer(void                       );
    inline void                  setContainer(FieldContainer * const cont);

    inline const OSBRootElement *getRoot (void) const;
    inline       OSBRootElement *editRoot(void);

    inline UInt32 getFCIdFile(void           ) const;
    inline void   setFCIdFile(UInt32 fcIdFile);
    
    inline UInt16 getVersion(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read    (const std::string &typeName) = 0;
    virtual void postRead(      void                 ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing                                                      */
    /*! \{                                                                 */

    virtual void preWrite(FieldContainer * const fc) = 0;
    virtual void write   (      void               ) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Protected Types                                              */
    /*! \{                                                                 */

    /*! \nohierarchy
     */
    class PtrFieldInfo
    {
      public:
        typedef std::vector<UInt32>          PtrIdStore;
        typedef PtrIdStore::iterator         PtrIdStoreIt;
        typedef PtrIdStore::const_iterator   PtrIdStoreConstIt;

        typedef std::vector<UInt16>          BindingStore;
        typedef BindingStore::iterator       BindingStoreIt;
        typedef BindingStore::const_iterator BindingStoreConstIt;

        PtrFieldInfo(FieldContainer * const fc, UInt32 fieldId);
        ~PtrFieldInfo(void);

        inline FieldContainer    *getContainer(void) const;
        inline UInt32             getFieldId  (void) const;

        inline const PtrIdStore          &getIdStore       (void) const;
        inline       PtrIdStore          &editIdStore      (void);
        inline       PtrIdStoreConstIt    beginIdStore     (void) const;
        inline       PtrIdStoreIt         beginIdStore     (void);
        inline       PtrIdStoreConstIt    endIdStore       (void) const;
        inline       PtrIdStoreIt         endIdStore       (void);

        inline const BindingStore        &getBindingStore  (void) const;
        inline       BindingStore        &editBindingStore (void);
        inline       BindingStoreConstIt  beginBindingStore(void) const;
        inline       BindingStoreIt       beginBindingStore(void);
        inline       BindingStoreConstIt  endBindingStore  (void) const;
        inline       BindingStoreIt       endBindingStore  (void);

        void setHandledField(bool bVal);
        bool getHandledField(void     ) const;

      private:
        FieldContainer   *_fc;
        UInt32            _fieldId;
        PtrIdStore        _ptrIds;
        BindingStore      _bindings;
        bool              _bHandledField;
    };

    typedef std::list<PtrFieldInfo>             PtrFieldList;
    typedef PtrFieldList::iterator              PtrFieldListIt;
    typedef PtrFieldList::const_iterator        PtrFieldListConstIt;

    typedef std::map<UInt32, UInt32>            FieldContainerIdMap;
    typedef FieldContainerIdMap::iterator       FieldContainerIdMapIt;
    typedef FieldContainerIdMap::const_iterator FieldContainerIdMapConstIt;

    typedef std::list<FieldContainer *>         FieldContainerList;
    typedef FieldContainerList::iterator        FieldContainerListIt;
    typedef FieldContainerList::const_iterator  FieldContainerListConstIt;

    typedef std::set<UInt32>                    FieldContainerIdSet;
    typedef FieldContainerIdSet::iterator       FieldContainerIdSetIt;
    typedef FieldContainerIdSet::const_iterator FieldContainerIdSetConstIt;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    FieldContainerUnrecPtr  _container;
    OSBRootElement         *_rootElement;
    UInt32                  _fcIdFile;
    UInt16                  _version;

    /*!\brief prohibit default function (move to 'public' if needed)       */
    OSBElementBase(const OSBElementBase &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const OSBElementBase &source);
};

OSG_END_NAMESPACE

#include "OSGOSBElementBase.inl"

#endif /* _OSGOSBELEMENTBASE_H_ */
