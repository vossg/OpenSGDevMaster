/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2007 by the OpenSG Forum                    *
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

#ifndef _OSGOSBROOTELEMENT_H_
#define _OSGOSBROOTELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGOSBCommonElement.h"
#include "OSGOSBElementFactoryHelper.h"
#include "OSGNFIOOptions.h"
#include "OSGBinaryDataHandler.h"

// TODO: Add infrastructure for file level and element level options
//       Keep it simple: Option object serializes to a string and must be able
//       to parse that string.

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBRootElement : public OSBCommonElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OSBCommonElement                      Inherited;
    typedef OSBRootElement                        Self;

    typedef Inherited::BinaryReadHandler          BinaryReadHandler;
    typedef Inherited::BinaryWriteHandler         BinaryWriteHandler;

    typedef Inherited::PtrFieldList               PtrFieldList;
    typedef Inherited::PtrFieldListIt             PtrFieldListIt;
    typedef Inherited::PtrFieldListConstIt        PtrFieldListConstIt;

    typedef Inherited::FieldContainerIdMap        FieldContainerIdMap;
    typedef Inherited::FieldContainerIdMapIt      FieldContainerIdMapIt;
    typedef Inherited::FieldContainerIdMapConstIt FieldContainerIdMapConstIt;

    typedef Inherited::FieldContainerList         FieldContainerList;
    typedef Inherited::FieldContainerListIt       FieldContainerListIt;
    typedef Inherited::FieldContainerListConstIt  FieldContainerListConstIt;

    typedef Inherited::FieldContainerIdSet        FieldContainerIdSet;
    typedef Inherited::FieldContainerIdSetIt      FieldContainerIdSetIt;
    typedef Inherited::FieldContainerIdSetConstIt FieldContainerIdSetConstIt;

    typedef std::list<OSBElementBase *>           ElementList;
    typedef ElementList::iterator                 ElementListIt;
    typedef ElementList::const_iterator           ElementListConstIt;

    typedef std::map<UInt32, OSBElementBase *>    IdElemMap;
    typedef IdElemMap::iterator                   IdElemMapIt;
    typedef IdElemMap::const_iterator             IdElemMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBRootElement(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBRootElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

            void initialiseRead(      std::istream      &inStream);
            void terminateRead (      void                       );

    virtual void read          (const std::string       &typeName);
    virtual void postRead      (      void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing                                                      */
    /*! \{                                                                 */

            void initialiseWrite(std::ostream   &outStream);
            void terminateWrite (void                     );

    virtual void preWrite       (FieldContainer * const fc);
    virtual void write          (void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name State access                                                 */
    /*! \{                                                                 */

    inline       BinaryReadHandler   *getReadHandler   (void);
    inline       BinaryWriteHandler  *getWriteHandler  (void);

    inline const NFIOOptions         &getOptions       (void) const;
    inline       NFIOOptions         &editOptions      (void);

    inline       void                 setHeaderVersion (const UInt16 version);
    inline       UInt16               getHeaderVersion (void) const;

    inline const FieldContainerIdMap &getIdMap         (void) const;
    inline       FieldContainerIdMap &editIdMap        (void);

    inline const PtrFieldList        &getPtrFieldList  (void) const;
    inline       PtrFieldList        &editPtrFieldList (void);

    inline const ElementList         &getElementList   (void) const;
    inline       ElementList         &editElementList  (void);

    inline const IdElemMap           &getIdElemMap     (void) const;
    inline       IdElemMap           &editIdElemMap    (void);

    inline const FieldContainerList  &getContainerList (void) const;
    inline       FieldContainerList  &editContainerList(void);

    inline const FieldContainerIdSet &getIdSet         (void) const;
    inline       FieldContainerIdSet &editIdSet        (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Helper methods                                               */
    /*! \{                                                                 */

    void mapPtrField(const PtrFieldInfo &ptrField);

    void dumpIdMap(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static OSBElementRegistrationHelper<OSBRootElement>  _regHelper;

           BinaryReadHandler                            *_readHandler;
           BinaryWriteHandler                           *_writeHandler;

           NFIOOptions                                   _options;
           ElementList                                   _elements;
           IdElemMap                                     _idElemMap;

           UInt16                                        _readHeaderVersion;
           FieldContainerIdMap                           _readIdMap;
           PtrFieldList                                  _readPtrFields;

           FieldContainerList                            _writeFCList;
           FieldContainerIdSet                           _writeIdSet;
};

OSG_END_NAMESPACE

#include "OSGOSBRootElement.inl"

#endif /* _OSGOSBROOTELEMENT_H_ */
