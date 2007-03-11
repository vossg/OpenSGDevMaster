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

#include "OSGFileIODef.h"
#include "OSGFieldContainerAttachment.h"
#include "OSGDynamicAttachmentMixin.h"
#include "OSGSingletonHolder.h"

#include "OSGVecSFields.h"
#include "OSGVecMFields.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

class VRMLNodeHelper;
typedef boost::shared_ptr<VRMLNodeHelper>       VRMLNodeHelperPtr;  /**< Smart ptr to a node helper. */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \hideinhierarchy */

// TODO rename it to VRMLGenericAtt ????

struct VRMLGenericAttDesc
{
    typedef FieldContainerAttachment    Parent;
    typedef FieldContainerAttachmentPtr ParentPtr;

    static const Char8 *getTypeName      (void) { return "VRMLGenericAtt"; }
    static const Char8 *getParentTypeName(void) 
    {
        return "FieldContainerAttachment"; 
    }
    static const Char8 *getGroupName     (void) { return "VRMLGenAtt"; }


    static InitContainerF         getInitMethod(void) { return NULL; }

    static FieldDescriptionBase **getDesc      (void) { return NULL; }
};

typedef DynFieldAttachment<VRMLGenericAttDesc>  VRMLGenericAtt;
typedef VRMLGenericAtt::ObjPtr                  VRMLGenericAttPtr;
    


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief General VRML Node Desc
*/

class OSG_FILEIO_DLLMAPPING VRMLNodeHelperFactoryBase 
{
    /*==========================  PUBLIC  =================================*/

  public :
    typedef boost::function< boost::shared_ptr<VRMLNodeHelper> (void)> CreateHelper;

    class RegisterHelper
    {
      public:
        
        RegisterHelper(      CreateHelper  fCreate, 
                       const Char8        *szNodeName);
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

    void registerNodeHelper(      CreateHelper  fHelper,
                            const Char8        *szNodeName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Prototypes                                 */
    /*! \{                                                                 */

    VRMLNodeHelperPtr createHelper(const Char8 *szNodeName);

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

typedef SingletonHolder<VRMLNodeHelperFactoryBase> VRMLNodeHelperFactory;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief General VRML Node Desc
    \ingroup GrpSystemFileIOVRML
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

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

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

    virtual void   getFieldAndDesc(      FieldContainerPtr      pFC,
                                   const Char8                * szFieldname,
                                         FieldContainerPtr     &pFieldFC,
                                         Field                *&pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual 
    void addFieldValue         (      Field                *pField,
                                const FieldDescriptionBase *pFieldDesc,
                                const Char8                *szFieldVal);

    virtual 
    void setContainerFieldValue(      FieldContainerPtr     pFC,
                                const FieldDescriptionBase *pFieldDesc,
                                      FieldContainerPtr     pFieldFC  );

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

    bool                  _bProtoInterfaceDone;

    VRMLGenericAttPtr     _pGenAttProto;
    FieldContainerPtr     _pNodeProto;
    FieldContainerPtr     _pNodeCoreProto;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec3f            ::Description _sfVec3fDesc;
    SFFieldContainerPtr::Description _sfFCPtrDesc;
    SFReal32           ::Description _sfReal32Desc;
    SFColor3f          ::Description _sfColor3fDesc;
    MFString           ::Description _mfStringDesc;
    SFBool             ::Description _sfBoolDesc;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    const Field *getField(      FieldContainerPtr  pFC1,
                                FieldContainerPtr  pFC2,
                                VRMLGenericAttPtr  pGenAtt,
                          const Char8             *szFieldname);

          void   getField(const Char8                * szFieldname,
                                FieldContainerPtr     &pFieldFC,
                                Field                *&pField,
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
*/

class OSG_FILEIO_DLLMAPPING VRMLDefaultHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelperPtr create(void);

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
*/

class OSG_FILEIO_DLLMAPPING VRMLGroupHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGroupHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8                * szFieldType,
                                   const UInt32                 uiFieldTypeId,
                                   const Char8                * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr      pFC,
                                   const Char8                * szFieldname,
                                         FieldContainerPtr     &pFieldFC,
                                         Field                *&pField,
                                   const FieldDescriptionBase *&pDesc);

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
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelperPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGroupHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec3f _defaultBoxCenter;
    SFVec3f _defaultBoxSize;

    SFVec3f _boxCenter;
    SFVec3f _boxSize;

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
    VRMLGroupHelper(const VRMLGroupHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGroupHelper &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------
class VRMLMaterialHelper;
typedef boost::shared_ptr<VRMLMaterialHelper>       VRMLMaterialHelperPtr;

/*! \brief VRML Material Desc
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

    virtual MaterialPtr getDefaultMaterial(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr       pFC,
                                   const Char8                 * szFieldname,
                                         FieldContainerPtr      &pFieldFC,
                                         Field                 *&pField,
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
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelperPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLMaterialHelper(void);

    /*! \}                                                                 */
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
class VRMLShapeHelper;
typedef boost::shared_ptr<VRMLShapeHelper>  VRMLShapeHelperPtr;

/*! \brief VRML Shape Helper
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

            void setMaterialHelper(VRMLMaterialHelperPtr pMaterialHelper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr      pFC,
                                   const Char8                * szFieldname,
                                         FieldContainerPtr     &pFieldFC,
                                         Field                *&pField,
                                   const FieldDescriptionBase *&pDesc);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

     virtual void endNode(FieldContainerPtr pFC);

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

    static VRMLNodeHelperPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLShapeHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialHelperPtr _pMaterialHelper;

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
class VRMLAppearanceHelper;
typedef boost::shared_ptr<VRMLAppearanceHelper>  VRMLAppearanceHelperPtr;

/*! \brief VRML Appearance Helper
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

    virtual void setMaterialHelper(VRMLMaterialHelperPtr pMaterialDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr      pFC,
                                   const Char8                * szFieldname,
                                         FieldContainerPtr     &pFieldFC,
                                         Field                *&pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual void endNode(FieldContainerPtr);

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

    static VRMLNodeHelperPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLAppearanceHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialHelperPtr _pMaterialHelper;

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

    virtual void getFieldAndDesc  (      FieldContainerPtr      pFC,
                                   const Char8                * szFieldname,
                                         FieldContainerPtr     &pFieldFC,
                                         Field                *&pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual void endNode(FieldContainerPtr pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Field Value                                 */
    /*! \{                                                                 */

    virtual 
    void setContainerFieldValue(      FieldContainerPtr     pFC,
                                const FieldDescriptionBase *pFieldDesc,
                                      FieldContainerPtr     pFieldFC  );

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

    static VRMLNodeHelperPtr create(void);

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

    virtual void getFieldAndDesc  (      FieldContainerPtr      pFC,
                                   const Char8                * szFieldname,
                                         FieldContainerPtr     &pFieldFC,
                                         Field                *&pField,
                                   const FieldDescriptionBase *&pDesc);

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
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelperPtr create(void);

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

/*! \brief VRML Image Texture Helper
*/

class OSG_FILEIO_DLLMAPPING VRMLImageTextureHelper : public VRMLNodeHelper
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

    virtual void getFieldAndDesc  (      FieldContainerPtr      pFC,
                                   const Char8                * szFieldname,
                                         FieldContainerPtr     &pFieldFC,
                                         Field                *&pField,
                                   const FieldDescriptionBase *&pDesc);

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
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelperPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLImageTextureHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    MFString _defaultURL;
    SFBool   _defaultRepeatS;
    SFBool   _defaultRepeatT;

    MFString _url;
    SFBool   _repeatS;
    SFBool   _repeatT;

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
    VRMLImageTextureHelper(const VRMLImageTextureHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLImageTextureHelper &source);
};


OSG_END_NAMESPACE

#define OSGVRMLNODEHELPER_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGVRMLNODEHELPER_H_ */


