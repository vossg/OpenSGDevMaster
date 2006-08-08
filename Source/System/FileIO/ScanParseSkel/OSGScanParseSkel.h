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

#ifndef _OSGSCANPARSESKEL_H_
#define _OSGSCANPARSESKEL_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGScanParseSkel.tab.h"
#include "OSGScanParseSkelBase.h"

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
#include <iosfwd>
#endif

class OSGScanParseLexer;

OSG_BEGIN_NAMESPACE

//! Parser / Scanner Skeleton for VRML97 syntax based file formats
//! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib

class OSG_SYSTEM_DLLMAPPING ScanParseSkel : public ScanParseSkelBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum BuildInFieldType
    {
        OSGsfBool      = TOK_SFBOOL,
        OSGsfColor     = TOK_SFCOLOR,
        OSGsfColorRGBA = TOK_SFCOLORRGBA,
        OSGsfDouble    = TOK_SFDOUBLE,
        OSGsfFloat     = TOK_SFFLOAT,
        OSGsfImage     = TOK_SFIMAGE,
        OSGsfInt32     = TOK_SFINT32,
        OSGsfMatrix3d  = TOK_SFMATRIX3D,
        OSGsfMatrix3f  = TOK_SFMATRIX3F,
        OSGsfMatrix4d  = TOK_SFMATRIX4D,
        OSGsfMatrix4f  = TOK_SFMATRIX4F,
        OSGsfNode      = TOK_SFNODE,
        OSGsfRotation  = TOK_SFROTATION,
        OSGsfString    = TOK_SFSTRING,
        OSGsfTime      = TOK_SFTIME,
        OSGsfVec2d     = TOK_SFVEC2D,
        OSGsfVec2f     = TOK_SFVEC2F,
        OSGsfVec3d     = TOK_SFVEC3D,
        OSGsfVec3f     = TOK_SFVEC3F,
        OSGsfVec4d     = TOK_SFVEC4D,
        OSGsfVec4f     = TOK_SFVEC4F,
        OSGmfBool      = TOK_MFBOOL,
        OSGmfColor     = TOK_MFCOLOR,
        OSGmfColorRGBA = TOK_MFCOLORRGBA,
        OSGmfDouble    = TOK_MFDOUBLE,
        OSGmfFloat     = TOK_MFFLOAT,
        OSGmfImage     = TOK_MFIMAGE,
        OSGmfInt32     = TOK_MFINT32,
        OSGmfMatrix3d  = TOK_MFMATRIX3D,
        OSGmfMatrix3f  = TOK_MFMATRIX3F,
        OSGmfMatrix4d  = TOK_MFMATRIX4D,
        OSGmfMatrix4f  = TOK_MFMATRIX4F,
        OSGmfNode      = TOK_MFNODE,
        OSGmfRotation  = TOK_MFROTATION,
        OSGmfString    = TOK_MFSTRING,
        OSGmfTime      = TOK_MFTIME,
        OSGmfVec2d     = TOK_MFVEC2D,
        OSGmfVec2f     = TOK_MFVEC2F,
        OSGmfVec3d     = TOK_MFVEC3D,
        OSGmfVec3f     = TOK_MFVEC3F,
        OSGmfVec4d     = TOK_MFVEC4D,
        OSGmfVec4f     = TOK_MFVEC4F,

        OSGmfColor4f   = TOK_MFCOLORRGBA,
        OSGmfColor4i   = TOK_MFCOLOR4I,
        OSGmfColor3f   = TOK_MFCOLOR,
        OSGmfMatrix    = TOK_MFMATRIX4F,
        OSGmfPnt2f     = TOK_MFPNT2F,
        OSGmfPnt3f     = TOK_MFPNT3F,
        OSGmfPnt4f     = TOK_MFPNT4F,
        OSGmfPlane     = TOK_MFPLANE,
        OSGsfColor4f   = TOK_SFCOLORRGBA,
        OSGsfColor4i   = TOK_SFCOLOR4I,
        OSGsfColor3f   = TOK_SFCOLOR,
        OSGsfMatrix    = TOK_SFMATRIX4F,
        OSGsfPnt2f     = TOK_SFPNT2F,
        OSGsfPnt3f     = TOK_SFPNT3F,
        OSGsfPnt4f     = TOK_SFPNT4F,
        OSGsfPlane     = TOK_SFPLANE,
        OSGsfVolume    = TOK_SFVOLUME
    };

    enum
    {
        LastOption = 0x0001
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ScanParseSkel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ScanParseSkel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Scan                                    */
    /*! \{                                                                 */

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
    virtual       void   scanStream (      std::istream &is         );
#endif

    virtual       void   scanFile   (const Char8        *szFilename );

    virtual       Int32  lex        (      void                     );
    virtual const Char8 *getText    (      void                     );
                  void   expectType (      Int32         iNextType  ); 

    virtual       void   handleError(const Char8        *szErrorText);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Prototypes                               */
    /*! \{                                                                 */

    virtual bool verifyHeader             (const Char8 *szHeader);

    virtual void beginProto               (const Char8 *szProtoname);
    virtual void endProto                 (void);

    virtual void beginExternProto         (const Char8 *szProtoname);
    virtual void endExternProtoInterface  (void                    );
    virtual void endExternProto           (void                    );

    virtual void beginScript              (const Char8 *szProtoname);
    virtual void endScript                (void);

    virtual void beginEventInDecl         (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void beginEventOutDecl        (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void endEventDecl             (void);

    virtual void beginFieldDecl           (const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    virtual void endFieldDecl             (void);

    virtual void beginExposedFieldDecl    (const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    virtual void endExposedFieldDecl      (void);


    virtual void addExternEventInDecl     (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void addExternEventOutDecl    (const Char8  *szEventType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szEventName);

    virtual void addExternFieldDecl       (const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    virtual void addExternExposedFieldDecl(const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Fields                                   */
    /*! \{                                                                 */

    virtual void beginField(const Char8  *szFieldname,
                            const UInt32  uiFieldTypeId);

    virtual void endField  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Nodes                                    */
    /*! \{                                                                 */

    virtual void beginNode(const Char8 *szNodeTypename,
                           const Char8 *szNodename);

    virtual void endNode  (void);

    virtual void nullNode (void);
    virtual void use      (const Char8 *szName);
    virtual void is       (const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Misc                                     */
    /*! \{                                                                 */

    virtual void addFieldValue    (const Char8 *szFieldVal     );

    virtual void addRoute         (const Char8 *szOutNodename,
                                   const Char8 *szOutFieldname,
                                   const Char8 *szInNodename,
                                   const Char8 *szInFieldname  );

    virtual void profileElement   (const Char8 *szProfileName  );

    virtual void componentElement (const Char8 *szComponentName);

    virtual void metaElement      (const Char8 *szMetaKey,
                                   const Char8 *szMetaValue    );

    virtual void importElement    (const Char8 *szInlineName,
                                   const Char8 *szNodeName,
                                   const Char8 *szImportAs     );

    virtual void exportElement    (const Char8 *szNodeName,
                                   const Char8 *szExportAs     );


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Type Information                             */
    /*! \{                                                                 */

    bool           getMapFieldTypes  (void);

    virtual Int32  mapExtIntFieldType(const Char8 *szFieldname,
                                      const Int32  iFieldTypeId);

    virtual UInt32 getFieldType      (const Char8 *szFieldname);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool               _bMapTypeIds;
    Char8             *_szReferenceHeader;
    OSGScanParseLexer *_pLexer;

    void reset             (      void);

    void setMapTypeIds     (      bool   bVal);

    void setReferenceHeader(const Char8 *szReferenceHeader);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ScanParseSkel(const ScanParseSkel &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ScanParseSkel &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#define OSGSCANPARSESKEL_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSCANPARSESKEL_H_ */

