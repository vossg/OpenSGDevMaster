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

#ifndef _OSGOSBCOMMONELEMENT_H_
#define _OSGOSBCOMMONELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGOSBElementBase.h"

#include <string>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBCommonElement : public OSBElementBase
{
   /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OSBElementBase                       Inherited;
    typedef OSBCommonElement                     Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */

    static const UInt8 FCPtrUnknown;
    static const UInt8 FCPtrFieldContainer;
    static const UInt8 FCPtrNode;
    static const UInt8 FCPtrNodeCore;
    static const UInt8 FCPtrAttachment;
    static const UInt8 FCPtrMaterial;
    static const UInt8 FCPtrStateChunk;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBCommonElement(OSBRootElement *root, UInt16 version);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBCommonElement(void);

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
    virtual void write   (void                     ) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Reading Helper methods                                       */
    /*! \{                                                                 */

    bool readFieldContainerHeader(std::string &typeName,
                                  UInt32      &fcId);

    bool           readFieldHeader       (const std::string    &endMarkers,
                                                std::string    &fieldName,
                                                std::string    &fieldTypeName,
                                                UInt32         &fieldSize     );
    bool           readFieldHeaderContinue(
                                         const std::string &endMarkers,
                                         const std::string &fieldName,
                                               std::string &fieldTypeName,
                                               UInt32      &fieldSize         );
    bool           readFieldContent      (const std::string    &fieldName,
                                          const std::string    &fieldTypeName,
                                          const UInt32          fieldSize,
                                          const std::string    &excludeFields,
                                                PtrFieldListIt &ptrFieldIt    );
    std::string    readFields            (const std::string    &excludeFields,
                                          const std::string    &endMarkers    );
    std::string    readFieldsContinue    (const std::string &fieldName,
                                          const std::string &excludeFields,
                                          const std::string &endMarkers       );
    void           skipFields            (      void                          );
    PtrFieldListIt readPtrSingleField    (const UInt32          fieldId       );
    PtrFieldListIt readPtrMultiField     (const UInt32          fieldId,
                                          const UInt32          fieldSize     );
    PtrFieldListIt readAttachmentMapField(const UInt32          fieldId,
                                          const UInt32          fieldSize     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Prewriting Helper Methods                                    */
    /*! \{                                                                 */

    void preWritePtrSingleField    (const UInt32          fieldId      );
    void preWritePtrMultiField     (const UInt32          fieldId      );
    void preWriteAttachmentMapField(const UInt32          fieldId      );
    void preWriteMapField          (const UInt32          fieldId      );
    void preWriteFieldContainer    (      FieldContainer *fc,
                                    const std::string    &excludeFields);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing Helper Methods                                       */
    /*! \{                                                                 */

    void writeFieldContainerHeader(FieldContainer * const   fc            );
    void writeFieldHeader         (const std::string       &fieldName,
                                   const std::string       &fieldTypeName,
                                   const UInt32             fieldSize     );
    void writeFieldContent        (const UInt32             fieldId       );
    void writeFields              (const std::string       &excludeFields,
                                   const bool               endMarker     );
    void writeEndMarker           (      void                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Map Helper Methods                                           */
    /*! \{                                                                 */

    void handleAttachmentMapElementPreWrite(FieldContainer *refedFC);
    void handleMapElementPreWrite          (FieldContainer *refedFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Misc Helper Methods                                          */
    /*! \{                                                                 */


    FieldContainerTransitPtr 
                      createReplacementFC(const UInt8             fcPtrType);
    UInt8             getFCPtrType       (FieldContainer * const container);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*!\brief prohibit default function (move to 'public' if needed)       */
    OSBCommonElement(const OSBCommonElement &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const OSBCommonElement &source);
};

OSG_END_NAMESPACE

#endif /* _OSGOSBCOMMONELEMENT_H_ */
