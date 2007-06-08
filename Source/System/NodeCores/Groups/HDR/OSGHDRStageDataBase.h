/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class HDRStageData
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGHDRSTAGEDATABASE_H_
#define _OSGHDRSTAGEDATABASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGGroupDef.h"

#include "OSGBaseTypes.h"

#include "OSGStageData.h" // Parent

#include "OSGChunkMaterialFields.h" // ToneMappingMaterial type
#include "OSGFrameBufferObjectFields.h" // BlurRenderTarget type
#include "OSGChunkMaterialFields.h" // BlurMaterial type
#include "OSGSHLChunkFields.h" // HBlurShader type
#include "OSGSHLChunkFields.h" // VBlurShader type
#include "OSGUInt32Fields.h" // Width type
#include "OSGUInt32Fields.h" // Height type
#include "OSGFrameBufferObjectFields.h" // ShrinkRenderTarget type
#include "OSGChunkMaterialFields.h" // ShrinkMaterial type

#include "OSGHDRStageDataFields.h"

OSG_BEGIN_NAMESPACE

class HDRStageData;

//! \brief HDRStageData Base Class.

class OSG_GROUP_DLLMAPPING HDRStageDataBase : public StageData
{
  public:

    typedef StageData Inherited;
    typedef StageData ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    typedef BundlePointerBuilder<
        HDRStageData>::ObjPtr         ObjPtr;

    typedef BundlePointerBuilder<
        HDRStageData>::ObjPtrConst    ObjPtrConst;

    typedef BundlePointerBuilder<
        HDRStageData>::ObjConstPtr    ObjConstPtr;

    typedef BundlePointerBuilder<
        HDRStageData>::ObjPtrArg      ObjPtrArg;

    typedef BundlePointerBuilder<
        HDRStageData>::ObjConstPtrArg ObjConstPtrArg;

    typedef BundlePointerBuilder<
        HDRStageData>::ObjPtrConstArg ObjPtrConstArg;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        ToneMappingMaterialFieldId = Inherited::NextFieldId,
        BlurRenderTargetFieldId = ToneMappingMaterialFieldId + 1,
        BlurMaterialFieldId = BlurRenderTargetFieldId + 1,
        HBlurShaderFieldId = BlurMaterialFieldId + 1,
        VBlurShaderFieldId = HBlurShaderFieldId + 1,
        WidthFieldId = VBlurShaderFieldId + 1,
        HeightFieldId = WidthFieldId + 1,
        ShrinkRenderTargetFieldId = HeightFieldId + 1,
        ShrinkMaterialFieldId = ShrinkRenderTargetFieldId + 1,
        NextFieldId = ShrinkMaterialFieldId + 1
    };

    static const OSG::BitVector ToneMappingMaterialFieldMask =
        (TypeTraits<BitVector>::One << ToneMappingMaterialFieldId);
    static const OSG::BitVector BlurRenderTargetFieldMask =
        (TypeTraits<BitVector>::One << BlurRenderTargetFieldId);
    static const OSG::BitVector BlurMaterialFieldMask =
        (TypeTraits<BitVector>::One << BlurMaterialFieldId);
    static const OSG::BitVector HBlurShaderFieldMask =
        (TypeTraits<BitVector>::One << HBlurShaderFieldId);
    static const OSG::BitVector VBlurShaderFieldMask =
        (TypeTraits<BitVector>::One << VBlurShaderFieldId);
    static const OSG::BitVector WidthFieldMask =
        (TypeTraits<BitVector>::One << WidthFieldId);
    static const OSG::BitVector HeightFieldMask =
        (TypeTraits<BitVector>::One << HeightFieldId);
    static const OSG::BitVector ShrinkRenderTargetFieldMask =
        (TypeTraits<BitVector>::One << ShrinkRenderTargetFieldId);
    static const OSG::BitVector ShrinkMaterialFieldMask =
        (TypeTraits<BitVector>::One << ShrinkMaterialFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldBundleType &getClassType   (void);
    static UInt32           getClassTypeId (void);
    static UInt16           getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldBundleType &getType         (void);
    virtual const FieldBundleType &getType         (void) const;

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

            const SFChunkMaterialPtr  *getSFToneMappingMaterial (void) const;
            const SFFrameBufferObjectPtr *getSFBlurRenderTarget (void) const;
            const SFChunkMaterialPtr  *getSFBlurMaterial    (void) const;
            const SFSHLChunkPtr       *getSFHBlurShader     (void) const;
            const SFSHLChunkPtr       *getSFVBlurShader     (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFUInt32            *getSFWidth           (void);
#endif
                  SFUInt32            *editSFWidth          (void);
            const SFUInt32            *getSFWidth           (void) const;

#ifdef OSG_1_GET_COMPAT
                  SFUInt32            *getSFHeight          (void);
#endif
                  SFUInt32            *editSFHeight         (void);
            const SFUInt32            *getSFHeight          (void) const;
            const SFFrameBufferObjectPtr *getSFShrinkRenderTarget (void) const;
            const SFChunkMaterialPtr  *getSFShrinkMaterial  (void) const;


                  ChunkMaterialPtrConst getToneMappingMaterial(void) const;

                  FrameBufferObjectPtrConst getBlurRenderTarget(void) const;

                  ChunkMaterialPtrConst getBlurMaterial   (void) const;

                  SHLChunkPtrConst getHBlurShader    (void) const;

                  SHLChunkPtrConst getVBlurShader    (void) const;

#ifdef OSG_1_GET_COMPAT
                  UInt32              &getWidth           (void);
#endif
                  UInt32              &editWidth          (void);
            const UInt32              &getWidth           (void) const;

#ifdef OSG_1_GET_COMPAT
                  UInt32              &getHeight          (void);
#endif
                  UInt32              &editHeight         (void);
            const UInt32              &getHeight          (void) const;

                  FrameBufferObjectPtrConst getShrinkRenderTarget(void) const;

                  ChunkMaterialPtrConst getShrinkMaterial (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setToneMappingMaterial(ChunkMaterialPtrConstArg value);
            void setBlurRenderTarget(FrameBufferObjectPtrConstArg value);
            void setBlurMaterial   (ChunkMaterialPtrConstArg value);
            void setHBlurShader    (SHLChunkPtrConstArg value);
            void setVBlurShader    (SHLChunkPtrConstArg value);
            void setWidth          (const UInt32 &value);
            void setHeight         (const UInt32 &value);
            void setShrinkRenderTarget(FrameBufferObjectPtrConstArg value);
            void setShrinkMaterial (ChunkMaterialPtrConstArg value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    virtual void pushToField     (      FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    virtual void insertIntoMField(const UInt32               uiIndex,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    virtual void replaceInMField (const UInt32               uiIndex,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    virtual void replaceInMField (      FieldBundlePConstArg pOldElement,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    virtual void removeFromMField(const UInt32               uiIndex,
                                  const UInt32               uiFieldId  );

    virtual void removeFromMField(      FieldBundlePConstArg pElement,
                                  const UInt32               uiFieldId  );

    virtual void clearField      (const UInt32               uiFieldId  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  HDRStageDataP create     (void);
    static  HDRStageDataP createEmpty(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldBundleP shallowCopy(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFChunkMaterialPtr _sfToneMappingMaterial;
    SFFrameBufferObjectPtr _sfBlurRenderTarget;
    SFChunkMaterialPtr _sfBlurMaterial;
    SFSHLChunkPtr     _sfHBlurShader;
    SFSHLChunkPtr     _sfVBlurShader;
    SFUInt32          _sfWidth;
    SFUInt32          _sfHeight;
    SFFrameBufferObjectPtr _sfShrinkRenderTarget;
    SFChunkMaterialPtr _sfShrinkMaterial;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    HDRStageDataBase(void);
    HDRStageDataBase(const HDRStageDataBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HDRStageDataBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const HDRStageData *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HDRStageDataBase &source);
};

/** Type specific RefPtr type for HDRStageData. */
typedef RefPtr<HDRStageDataP> HDRStageDataRefP;


OSG_END_NAMESPACE

#endif /* _OSGHDRSTAGEDATABASE_H_ */
