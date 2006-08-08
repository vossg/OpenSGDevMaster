/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000-2002 by the OpenSG Forum               *
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


#ifndef _OSGVRMLNODEDESCS_H_
#define _OSGVRMLNODEDESCS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include <vector>
#include <string>

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include "OSGFieldContainerPtr.h"
#include "OSGField.h"
#include "OSGFieldContainer.h"
#include "OSGFieldContainerAttachment.h"
#include "OSGDynamicAttachmentMixin.h"
#include "OSGFieldContainerFieldTraits.h"
#include "OSGGeoProperty.h"
#include "OSGGeoProperties.h"
//#include "OSGSFSysTypes.h"
#include "OSGSimpleMaterial.h"
#include "OSGImageFields.h"
//#include "OSGSFVecTypes.h"
//#include "OSGSFFieldContainerPtr.h"
#include "OSGComponentTransform.h"

OSG_BEGIN_NAMESPACE

class VRMLAppearanceDesc;
class VRMLMaterialDesc;
class VRMLImageTextureDesc;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \hideinhierarchy */

// TODO rename it to VRMLGenericAtt ????
struct GenericAttDesc
{
    typedef FieldContainerAttachment    Parent;
    typedef FieldContainerAttachmentPtr ParentPtr;

    // TODO rename it to VRMLGenericAtt ????
    static const Char8 *getTypeName      (void) { return "GenericAtt"; }
    static const Char8 *getParentTypeName(void) { return "Attachment"; }
    static const Char8 *getGroupName     (void) { return "VRMLGenAtt"; }

    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescriptionBase **getDesc      (void) { return NULL; }
};

typedef DynFieldAttachment<GenericAttDesc>  GenericAtt;
typedef GenericAtt::ObjPtr                  GenericAttPtr;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILEVRMLNODEDESCINST
#if defined(OSG_WIN32_CL) && _MSC_VER > 1300
OSG_ABSTR_FC_DLLEXPORT_DECL(DynFieldAttachment,
                            GenericAttDesc,
                            )
#else
OSG_ABSTR_FC_DLLEXPORT_DECL(DynFieldAttachment,
                            GenericAttDesc,
                            OSG_FILEIO_DLLMAPPING)
#endif
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GenericAttPtr> :
    public FieldTraitsFCPtrBase<GenericAttPtr>
{
    static DataType                 _type;
    typedef FieldTraits<GenericAttPtr>  Self;

    enum                            { StringConvertable = 0x00  };
    enum                            { bHasParent        = 0x01  };

    static DataType &getType (void) { return _type;             }
    static Char8    *getSName(void) { return "SFGenericAttPtr"; }
    static Char8    *getMName(void) { return "MFGenericAttPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class FieldTraitsRecurseMapper<GenericAttPtr, true> */
/*! \hideinhierarchy                                     */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */

typedef SField<GenericAttPtr>       SFGenericPtr;
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILEVRMLNODEDESCINST

OSG_FIELD_DLLEXPORT_DECL1(SField, 
                          GenericAttPtr, 
                          OSG_FILEIO_DLLMAPPING)
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldMulti */

typedef MField<GenericAttPtr>       MFGenericAttPtr;
#endif

#ifndef OSG_COMPILEVRMLNODEDESCINST

OSG_FIELD_DLLEXPORT_DECL1(MField, 
                          GenericAttPtr,
                          OSG_FILEIO_DLLMAPPING)
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief General VRML Node Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static UInt32 getIndent  (void);
    static void   incIndent  (void);
    static void   decIndent  (void);
    static void   resetIndent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLNodeDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLNodeDesc (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual       void              init                 (const Char8 *szName);

    virtual       void              reset                (void);

    virtual       void              setOnEndSave         (const Char8 *szName);
    virtual       void              clearOnEndSave       (void);
    virtual       bool              getOnEndSave         (void);
    virtual const Char8            *getSavename          (void);
    virtual       FieldContainerPtr getSaveFieldContainer(void);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual const Field *getField       (const Char8             * szFieldname);

    virtual void   getFieldAndDesc(      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Prototypes                                 */
    /*! \{                                                                 */

    virtual bool prototypeAddField     (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName);

    virtual void prototypeAddFieldValue(const Char8 *szFieldVal);

    virtual void endProtoInterface     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      FieldValue                              */
    /*! \{                                                                 */

    virtual void addFieldValue(      Field             *pField,
                               const Char8             *szFieldVal);

    virtual bool use          (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_USE_HASH_COMPARE
    typedef 
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            const Char8  *,  
            UInt32,
            HashCmpString> FieldNameTypeHash;
#else
    typedef
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            const Char8 *,
            UInt32,
            OSG_STDEXTENSION_NAMESPACE::hash<const Char8 *>,
            EQString                                      > FieldNameTypeHash;
#endif
#else
    typedef
        std::map<     const Char8 *,  UInt32,   LTString> FieldNameTypeHash;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static UInt32             _uiIndent;

           FieldNameTypeHash  _mFieldTypes;

           GenericAttPtr      _pGenAtt;

           FieldContainerPtr  _pNodeProto;
           FieldContainerPtr  _pNodeCoreProto;

           const Field        *_pCurrField;

           std::string        _szCurrentName;
           bool               _bSaveOnEnd;



    const Field *getField(      FieldContainerPtr  pFC1,
                          FieldContainerPtr  pFC2,
                          GenericAttPtr      pGenAtt,
                    const Char8             *szFieldname);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLNodeDesc(const VRMLNodeDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLNodeDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Shape Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLShapeDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLShapeDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLShapeDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init           (const Char8            *szName);

            void setMaterialDesc(      VRMLMaterialDesc *pMaterialDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (FieldContainerPtr        pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialDesc *_pMaterialDesc;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLShapeDesc(const VRMLShapeDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLShapeDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Geometry Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLGeometryDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryDesc(bool bIsFaceSet);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr  pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Field Value                                 */
    /*! \{                                                                 */

    virtual void addFieldValue(      Field *pField,
                               const Char8 *szFieldVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool                   _bIsFaceSet;

    bool                   _bInIndex;
    UInt32                 _uiNumVertices;

    GeoIntegralPropertyPtr _pTypeField;
    GeoIntegralPropertyPtr _pLengthField;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryDesc(const VRMLGeometryDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Point Set Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLGeometryPointSetDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryPointSetDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryPointSetDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr  pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Field Value                                 */
    /*! \{                                                                 */

    virtual void addFieldValue(      Field *pField,
                               const Char8 *szFieldVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool                   _bInIndex;
    UInt32                 _uiNumVertices;

    GeoIntegralPropertyPtr _pTypeField;
    GeoIntegralPropertyPtr _pLengthField;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryPointSetDesc(const VRMLGeometryPointSetDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryPointSetDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Gemetry Part Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLGeometryPartDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryPartDesc(Char8 *szVRMLPartname,
                         Char8 *szOSGPartname,
                         Char8 *szOSGProtoname);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryPartDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    Char8 *_szVRMLPartname;
    Char8 *_szOSGPartname;
    Char8 *_szOSGProtoname;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryPartDesc(const VRMLGeometryPartDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryPartDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Gemetry Object Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLGeometryObjectDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryObjectDesc(Char8 *szVRMLObjectname);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryObjectDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    Char8 *_szVRMLObjectname;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryObjectDesc(const VRMLGeometryObjectDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryObjectDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Appearance Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLAppearanceDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLAppearanceDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLAppearanceDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init           (const Char8            *szName);

    virtual void setMaterialDesc(      VRMLMaterialDesc *pMaterialDesc);


    virtual FieldContainerPtr getSaveFieldContainer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Field Value                                */
    /*! \{                                                                 */

    virtual bool use(FieldContainerPtr pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialDesc    *_pMaterialDesc;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLAppearanceDesc(const VRMLAppearanceDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLAppearanceDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Material Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLMaterialDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLMaterialDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLMaterialDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void        init              (const Char8 *szName);

    virtual void        reset             (      void);

    virtual MaterialPtr getDefaultMaterial(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFReal32         _defaultAmbientIntensity;
    SFColor3f        _defaultDiffuseColor;
    SFColor3f        _defaultEmissiveColor;
    SFReal32         _defaultShininess;
    SFColor3f        _defaultSpecularColor;
    SFReal32         _defaultTransparency;

    SFReal32         _ambientIntensity;
    SFColor3f        _diffuseColor;
    SFColor3f        _emissiveColor;
    SFReal32         _shininess;
    SFColor3f        _specularColor;
    SFReal32         _transparency;

    ChunkMaterialPtr _pDefMat;
    MaterialChunkPtr _pMat;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLMaterialDesc(const VRMLMaterialDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLMaterialDesc &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Texture Transform Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLTextureTransformDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLTextureTransformDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLTextureTransformDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec2f _defaultCenter;
    SFReal32 _defaultRotation;
    SFVec2f _defaultScale;
    SFVec2f _defaultTranslation;

    SFVec2f _center;
    SFReal32 _rotation;
    SFVec2f _scale;
    SFVec2f _translation;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLTextureTransformDesc(const VRMLTextureTransformDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLTextureTransformDesc &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Image Texture Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLImageTextureDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLImageTextureDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLImageTextureDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFString _defaultURL;
    SFBool   _defaultRepeatS;
    SFBool   _defaultRepeatT;

    MFString _url;
    SFBool   _repeatS;
    SFBool   _repeatT;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLImageTextureDesc(const VRMLImageTextureDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLImageTextureDesc &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Pixel Texture Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLPixelTextureDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLPixelTextureDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLPixelTextureDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field                                     */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Node                                      */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Field Value                                 */
    /*! \{                                                                 */

    virtual void addFieldValue(      Field *pField,
                               const Char8 *szFieldVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFImagePtr _defaultImage;
    SFBool     _defaultRepeatS;
    SFBool     _defaultRepeatT;

    SFImagePtr _image;
    SFBool     _repeatS;
    SFBool     _repeatT;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLPixelTextureDesc(const VRMLPixelTextureDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLPixelTextureDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Level Of Detail Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLLODDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLLODDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLLODDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLLODDesc(const VRMLLODDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLLODDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Switch Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLSwitchDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLSwitchDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLSwitchDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLSwitchDesc(const VRMLSwitchDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLSwitchDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Group Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLGroupDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGroupDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGroupDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec3f _defaultBoxCenter;
    SFVec3f _defaultBoxSize;

    SFVec3f _boxCenter;
    SFVec3f _boxSize;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGroupDesc(const VRMLGroupDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGroupDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Extrusion Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLExtrusionDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLExtrusionDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLExtrusionDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLExtrusionDesc(const VRMLExtrusionDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLExtrusionDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Inline Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLInlineDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLInlineDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLInlineDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8       *szTypename,
                                        const Char8       *szName,
                                        FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (FieldContainerPtr);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec3f _defaultBoxCenter;
    SFVec3f _defaultBoxSize;

    SFVec3f _boxCenter;
    SFVec3f _boxSize;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLInlineDesc(const VRMLInlineDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLInlineDesc &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Viewpoint Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLViewpointDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLViewpointDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLViewpointDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void                  init            (const Char8 *szName);

    virtual void                  reset           (      void         );

    virtual ComponentTransformPtr getDefaultBeacon(      void         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLViewpointDesc(const VRMLViewpointDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLViewpointDesc &source);
};

#if 0

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Directional Light Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLDirectionalLightDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLDirectionalLightDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLDirectionalLightDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFReal32  _defaultAmbientIntensity;
    SFColor3f _defaultDiffuseColor;
    SFColor3f _defaultEmissiveColor;
    SFReal32  _defaultShininess;
    SFColor3f _defaultSpecularColor;
    SFReal32  _defaultTransparency;

    SFReal32  _ambientIntensity;
    SFColor3f _diffuseColor;
    SFColor3f _emissiveColor;
    SFReal32  _shininess;
    SFColor3f _specularColor;
    SFReal32  _transparency;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLDirectionalLightDesc(const VRMLDirectionalLightDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLDirectionalLightDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Point Light Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLPointLightDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLPointLightDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLPointLightLightDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFReal32  _defaultAmbientIntensity;
    SFColor3f _defaultDiffuseColor;
    SFColor3f _defaultEmissiveColor;
    SFReal32  _defaultShininess;
    SFColor3f _defaultSpecularColor;
    SFReal32  _defaultTransparency;

    SFReal32  _ambientIntensity;
    SFColor3f _diffuseColor;
    SFColor3f _emissiveColor;
    SFReal32  _shininess;
    SFColor3f _specularColor;
    SFReal32  _transparency;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLDirectionalLightDesc(const VRMLDirectionalLightDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLDirectionalLightDesc &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Directional Light Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLDirectionalLightDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLDirectionalLightDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLDirectionalLightDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                   const Field             *&pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFReal32  _defaultAmbientIntensity;
    SFColor3f _defaultDiffuseColor;
    SFColor3f _defaultEmissiveColor;
    SFReal32  _defaultShininess;
    SFColor3f _defaultSpecularColor;
    SFReal32  _defaultTransparency;

    SFReal32  _ambientIntensity;
    SFColor3f _diffuseColor;
    SFColor3f _emissiveColor;
    SFReal32  _shininess;
    SFColor3f _specularColor;
    SFReal32  _transparency;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLDirectionalLightDesc(const VRMLDirectionalLightDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLDirectionalLightDesc &source);
};
#endif

OSG_END_NAMESPACE

#define OSGVRMLNODEDESCS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLNODEDESCS_H_ */


