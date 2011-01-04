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

#ifndef _OSGVRMLNODEHELPER_H_
#define _OSGVRMLNODEHELPER_H_
#ifdef __sgi
#pragma once
#endif

#define OSG_VRML_IMAGETEXTURE_MAP

#include "OSGFileIODef.h"
#include "OSGAttachment.h"
#include "OSGDynamicAttachmentMixin.h"
#include "OSGSingletonHolder.h"

#include "OSGVecSFields.h"
#include "OSGVecMFields.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGVRMLAttachment.h"
#include "OSGImage.h"

#include "OSGDeprecatedCPP.h"

OSG_BEGIN_NAMESPACE

class VRMLNodeHelper;
class Image;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

struct VRMLGenericAttDesc
{
    typedef VRMLAttachment  Parent;
    typedef VRMLAttachment *ParentPtr;

    static const Char8 *getTypeName      (void) { return "VRMLGenericAtt"; }
    static const Char8 *getParentTypeName(void) 
    {
        return "VRMLAttachment"; 
    }
    static const Char8 *getGroupName     (void) { return "VRMLGenAtt"; }


    static InitContainerF         getInitMethod(void) { return NULL; }

    static FieldDescriptionBase **getDesc      (void) { return NULL; }
};

/*! \ingroup GrpFileIOWRLObj
 */

typedef DynFieldAttachment<VRMLGenericAttDesc>  VRMLGenericAtt;

/*! \ingroup GrpFileIOWRLObj
 */
typedef VRMLGenericAtt::ObjUnrecPtr             VRMLGenericAttUnrecPtr;



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief General VRML Node Desc
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLNodeHelperFactoryBase 
{
    /*==========================  PUBLIC  =================================*/

  public :

    typedef boost::function<VRMLNodeHelper *(void)>  CreateHelper;

    /*! \nohierarchy
     */
    class OSG_FILEIO_DLLMAPPING RegisterHelper
    {
      public:
        
        RegisterHelper(      CreateHelper       fCreate, 
                       const Char8             *szNodeName,
                             InitFuncF          fStaticInit);
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

    void registerNodeHelper(      CreateHelper       fHelper,
                            const Char8             *szNodeName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Prototypes                                 */
    /*! \{                                                                 */

    VRMLNodeHelper *createHelper(const Char8 *szNodeName);

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

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_USE_HASH_COMPARE
    typedef 
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            const Char8  *,  
            CreateHelper,
            HashCmpString                    > NameHelperCreateMap;

#else
    typedef 
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            const Char8  *,  
            CreateHelper, 
            OSG_STDEXTENSION_NAMESPACE::hash<
                const Char8 *>, 
            EQString                         > NameHelperCreateMap;  
#endif
#else
    typedef 
        std::map<const Char8 *,  
                       CreateHelper, 
                       LTString              > NameHelperCreateMap;
#endif



    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLNodeHelperFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLNodeHelperFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */


    NameHelperCreateMap _mRegisteredNodeHelperHash;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLNodeHelperFactoryBase(const VRMLNodeHelperFactoryBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLNodeHelperFactoryBase &source);
};

/*! \ingroup GrpFileIOWRLObj
 */

typedef SingletonHolder<VRMLNodeHelperFactoryBase> VRMLNodeHelperFactory;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief General VRML Node Desc
    \ingroup GrpFileIOWRLObj
    \nohierarchy

    This is a helper that knows how to load and handle construction of a single
    VRML node type.  This class will have one derived class for all node
    types that can be handled by the loader.
*/

class OSG_FILEIO_DLLMAPPING VRMLNodeHelper 
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
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLNodeHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void reset(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual 
        FieldContainerTransitPtr beginNode(const Char8          *szTypename,
                                           const Char8          *szName,
                                                 FieldContainer *pCurrentFC);

    virtual 
        void                     endNode  (      FieldContainer *          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual void mapFieldname(const std::string &szVRMLNodeName,
                                    std::string &szFieldName   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Prototypes                                 */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField     (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName);

    virtual void endProtoInterface     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      FieldValue                              */
    /*! \{                                                                 */

    virtual void   getFieldAndDesc(      FieldContainer        *pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual 
    void addFieldValue         (      EditFieldHandlePtr    pField,
                                const FieldDescriptionBase *pFieldDesc,
                                const Char8                *szFieldVal);

    virtual 
    void addImageValue         (      EditFieldHandlePtr    pField,
                                const FieldDescriptionBase *pFieldDesc,
                                      Image                *pImage    );

    virtual 
    void setContainerFieldValue(      FieldContainer       *pFC,
                                const FieldDescriptionBase *pFieldDesc,
                                      FieldContainer       *pFieldFC  );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLNodeHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static UInt32             _uiIndent;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool                   _bProtoInterfaceDone;

    VRMLGenericAttUnrecPtr _pGenAttProto;
    FieldContainerUnrecPtr _pNodeProto;
    FieldContainerUnrecPtr _pNodeCoreProto;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec3f                 ::Description _sfVec3fDesc;
    SFUnrecFieldContainerPtr::Description _sfFCPtrDesc;
    SFUnrecImagePtr         ::Description _sfImagePtrDesc;
    SFReal32                ::Description _sfReal32Desc;
    SFColor3f               ::Description _sfColor3fDesc;
    MFString                ::Description _mfStringDesc;
    SFBool                  ::Description _sfBoolDesc;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    GetFieldHandlePtr getField(      FieldContainer        *pFC1,
                                     FieldContainer        *pFC2,
                                     VRMLGenericAtt        * pGenAtt,
                               const Char8                 *szFieldname);

          void        getField(const Char8                 *szFieldname,
                                     FieldContainer       *&pFieldFC,
                                     EditFieldHandlePtr    &pField,
                               const FieldDescriptionBase *&pDesc      );

    FieldDescriptionBase *getFieldDescription(const Char8  *szFieldName,
                                              const UInt32  uiFieldTypeId);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLNodeHelper(const VRMLNodeHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLNodeHelper &source);
};





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Group Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLDefaultHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLDefaultHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual 
        FieldContainerTransitPtr beginNode(const Char8          *szTypename,
                                           const Char8          *szName,
                                                 FieldContainer *pCurrentFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLDefaultHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLDefaultHelper(const VRMLDefaultHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLDefaultHelper &source);
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Group Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

template<class ContainerT>
class VRMLGenericHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGenericHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    static bool initStatic(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual void mapFieldname(const std::string &szVRMLNodeName,
                                    std::string &szFieldName   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:


    typedef std::map<std::string,  
                     std::string>         FieldNameMap;

    typedef FieldNameMap::const_iterator  FieldNameMapConstIt;

    static  FieldNameMap                 _mFieldNameMap;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGenericHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGenericHelper(const VRMLGenericHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGenericHelper &source);
};

#define OSG_INST_GENERICVRMLHELPER(OSGNODE)                 \
                                                            \
    template<>                                              \
    VRMLGenericHelper< OSGNODE >::FieldNameMap              \
        VRMLGenericHelper< OSGNODE >::_mFieldNameMap =      \
            VRMLGenericHelper< OSGNODE >::FieldNameMap();   \
                                                            \
    template class VRMLGenericHelper< OSGNODE >

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Material Desc
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLMaterialHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLMaterialHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void        init              (const Char8 *szName);

    virtual void        reset             (      void);

    virtual Material   *getDefaultMaterial(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainer        * pFC,
                                   const Char8                 * szFieldname,
                                         FieldContainer        *&pFieldFC,
                                         EditFieldHandlePtr     &pField,
                                   const FieldDescriptionBase  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual 
        FieldContainerTransitPtr beginNode(const Char8             *szTypename,
                                           const Char8             *szName,
                                                 FieldContainer    *pCurrentFC);

    virtual 
        void                     endNode  (      FieldContainer *             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Type Specific                              */
    /*! \{                                                                 */
    
    const std::string &getName(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLMaterialHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFReal32              _defaultAmbientIntensity;
    SFColor3f             _defaultDiffuseColor;
    SFColor3f             _defaultEmissiveColor;
    SFReal32              _defaultShininess;
    SFColor3f             _defaultSpecularColor;
    SFReal32              _defaultTransparency;

    SFReal32              _ambientIntensity;
    SFColor3f             _diffuseColor;
    SFColor3f             _emissiveColor;
    SFReal32              _shininess;
    SFColor3f             _specularColor;
    SFReal32              _transparency;

    ChunkMaterialUnrecPtr _pDefMat;
    MaterialChunkUnrecPtr _pMat;

    std::string           _szName;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLMaterialHelper(const VRMLMaterialHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLMaterialHelper &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Shape Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLShapeHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLShapeHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init             (const Char8              *szName         );

            void setMaterialHelper(      VRMLMaterialHelper *pMaterialHelper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

     virtual void endNode(FieldContainer *pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLShapeHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialHelper *_pMaterialHelper;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLShapeHelper(const VRMLShapeHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLShapeHelper &source);
};





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Appearance Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLAppearanceHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLAppearanceHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init             (const Char8              *szName       );

    virtual void setMaterialHelper(      VRMLMaterialHelper *pMaterialDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual void endNode(FieldContainer *);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Field Value                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLAppearanceHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialHelper *_pMaterialHelper;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLAppearanceHelper(const VRMLAppearanceHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLAppearanceHelper &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Indexed Geometry Help
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLIndexedGeometryHelper : 
    public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLIndexedGeometryHelper(void);

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

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual void endNode(FieldContainer *pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Field Value                                 */
    /*! \{                                                                 */

    virtual 
    void setContainerFieldValue(      FieldContainer       *pFC,
                                const FieldDescriptionBase *pFieldDesc,
                                      FieldContainer       *pFieldFC  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLIndexedGeometryHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool   _bIsFaceSet;
    UInt16 _uiPropertyIndex;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperIFS;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperILS;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLIndexedGeometryHelper(const VRMLIndexedGeometryHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLIndexedGeometryHelper &source);
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Gemetry Part Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLGeometryPartHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryPartHelper(void);

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

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual void mapFieldname(const std::string &szVRMLNodeName,
                                    std::string &szFieldName   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryPartHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    std::string _szVRMLPartname;
    std::string _szOSGPartname;
    std::string _szOSGProtoname;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperCoordinate;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperNormal;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperColor;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperTexCoordinate;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryPartHelper(const VRMLGeometryPartHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryPartHelper &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Gemetry Object Desc
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLGeometryObjectHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryObjectHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual void endNode(FieldContainer *);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    enum GeoObjectType
    {
        UnknownGeo  = 0x0000,
        BoxGeo      = 0x0001,
        SphereGeo   = 0x0002,
        ConeGeo     = 0x0003,
        CylinderGeo = 0x0004,
        TeapotGeo   = 0x0005,
        PlaneGeo    = 0x0006
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryObjectHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    GeoObjectType _eVRMLObjectType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperSphere;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperBox;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperCone;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperCylinder;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperTeapot;
    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperPlane;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryObjectHelper(const VRMLGeometryObjectHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryObjectHelper &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Texture Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLTextureHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLTextureHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual 
        FieldContainerTransitPtr beginNode(const Char8             *szTypename,
                                           const Char8             *szName,
                                                 FieldContainer    *pCurrentFC);

    virtual 
        void                     endNode  (      FieldContainer    *          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLTextureHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFBool      _defaultRepeatS;
    SFBool      _defaultRepeatT;

    SFBool      _repeatS;
    SFBool      _repeatT;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLTextureHelper(const VRMLTextureHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLTextureHelper &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Image Texture Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLImageTextureHelper : public VRMLTextureHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLImageTextureHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual 
        FieldContainerTransitPtr beginNode(const Char8             *szTypename,
                                           const Char8             *szName,
                                                 FieldContainer    *pCurrentFC);

    virtual 
        void                     endNode  (      FieldContainer    *          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map<std::string, Image *> UrlImageMap;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLImageTextureHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    MFString    _defaultURL;

    MFString    _url;

#ifdef OSG_VRML_IMAGETEXTURE_MAP
    UrlImageMap _urlImageMap;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLTextureHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLImageTextureHelper(const VRMLImageTextureHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLImageTextureHelper &source);
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Image Texture Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLPixelTextureHelper : public VRMLTextureHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLPixelTextureHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual 
    void addImageValue(      EditFieldHandlePtr    pField,
                       const FieldDescriptionBase *pFieldDesc,
                             Image                *pImage    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual 
        FieldContainerTransitPtr beginNode(const Char8             *szTypename,
                                           const Char8             *szName,
                                                 FieldContainer    *pCurrentFC);

    virtual 
        void                     endNode  (      FieldContainer    *          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLPixelTextureHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ImageUnrecPtr _pImage;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLTextureHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLPixelTextureHelper(const VRMLPixelTextureHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLPixelTextureHelper &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Group Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLInlineHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLInlineHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual void endNode(FieldContainer *pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLInlineHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLInlineHelper(const VRMLInlineHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLInlineHelper &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Shape Helper
    \ingroup GrpFileIOWRLObj
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING VRMLSwitchHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLSwitchHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLSwitchHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLSwitchHelper(const VRMLSwitchHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLSwitchHelper &source);
};

OSG_END_NAMESPACE

#include "OSGVRMLNodeHelper.inl"

#endif /* _OSGVRMLNODEHELPER_H_ */


