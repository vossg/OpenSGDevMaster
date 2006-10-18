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
 **     class PolygonBackground
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGPOLYGONBACKGROUNDBASE_H_
#define _OSGPOLYGONBACKGROUNDBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGBaseTypes.h"

#include "OSGBackground.h" // Parent

#include "OSGMaterialFields.h" // Material type
#include "OSGVec3fFields.h" // TexCoords type
#include "OSGPnt2fFields.h" // Positions type
#include "OSGBoolFields.h" // NormalizedX type
#include "OSGBoolFields.h" // NormalizedY type
#include "OSGUInt16Fields.h" // AspectHeight type
#include "OSGUInt16Fields.h" // AspectWidth type

#include "OSGPolygonBackgroundFields.h"

OSG_BEGIN_NAMESPACE

class PolygonBackground;

//! \brief PolygonBackground Base Class.

class OSG_WINDOW_DLLMAPPING PolygonBackgroundBase : public Background
{
  public:

    typedef Background Inherited;
    typedef Background ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    typedef PointerFwdBuilder<BackgroundPtr, 
                              BackgroundConstPtr, 
                              PolygonBackground>::ObjPtr         ObjPtr;
    typedef PointerFwdBuilder<BackgroundPtr, 
                              BackgroundConstPtr, 
                              PolygonBackground>::ObjPtrConst    ObjPtrConst;
    typedef PointerFwdBuilder<BackgroundPtr, 
                              BackgroundConstPtr,
                              PolygonBackground>::ObjConstPtr    ObjConstPtr;
    typedef PointerFwdBuilder<BackgroundPtr, 
                              BackgroundConstPtr,
                              PolygonBackground>::ObjPtrArg      ObjPtrArg;
    typedef PointerFwdBuilder<BackgroundPtr, 
                              BackgroundConstPtr,
                              PolygonBackground>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerFwdBuilder<BackgroundPtr, 
                              BackgroundConstPtr,
                              PolygonBackground>::ObjPtrConstArg ObjPtrConstArg;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        MaterialFieldId = Inherited::NextFieldId,
        TexCoordsFieldId = MaterialFieldId + 1,
        PositionsFieldId = TexCoordsFieldId + 1,
        NormalizedXFieldId = PositionsFieldId + 1,
        NormalizedYFieldId = NormalizedXFieldId + 1,
        AspectHeightFieldId = NormalizedYFieldId + 1,
        AspectWidthFieldId = AspectHeightFieldId + 1,
        NextFieldId = AspectWidthFieldId + 1
    };

    static const OSG::BitVector MaterialFieldMask = 
        (TypeTraits<BitVector>::One << MaterialFieldId);
    static const OSG::BitVector TexCoordsFieldMask = 
        (TypeTraits<BitVector>::One << TexCoordsFieldId);
    static const OSG::BitVector PositionsFieldMask = 
        (TypeTraits<BitVector>::One << PositionsFieldId);
    static const OSG::BitVector NormalizedXFieldMask = 
        (TypeTraits<BitVector>::One << NormalizedXFieldId);
    static const OSG::BitVector NormalizedYFieldMask = 
        (TypeTraits<BitVector>::One << NormalizedYFieldId);
    static const OSG::BitVector AspectHeightFieldMask = 
        (TypeTraits<BitVector>::One << AspectHeightFieldId);
    static const OSG::BitVector AspectWidthFieldMask = 
        (TypeTraits<BitVector>::One << AspectWidthFieldId);
    static const OSG::BitVector NextFieldMask = 
        (TypeTraits<BitVector>::One << NextFieldId);


    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldContainerType &getClassType   (void); 
    static UInt32              getClassTypeId (void); 
    static UInt16              getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType         (void); 
    virtual const FieldContainerType &getType         (void) const; 

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

     const SFMaterialPtr *getSFMaterial (void) const;

#ifdef OSG_1_COMPAT
           MFVec3f *getMFTexCoords(void);
#endif
           MFVec3f *editMFTexCoords(void);
     const MFVec3f *getMFTexCoords (void) const;

#ifdef OSG_1_COMPAT
           MFPnt2f *getMFPositions(void);
#endif
           MFPnt2f *editMFPositions(void);
     const MFPnt2f *getMFPositions (void) const;

#ifdef OSG_1_COMPAT
           SFBool *getSFNormalizedX(void);
#endif
           SFBool *editSFNormalizedX(void);
     const SFBool *getSFNormalizedX (void) const;

#ifdef OSG_1_COMPAT
           SFBool *getSFNormalizedY(void);
#endif
           SFBool *editSFNormalizedY(void);
     const SFBool *getSFNormalizedY (void) const;

#ifdef OSG_1_COMPAT
           SFUInt16 *getSFAspectHeight(void);
#endif
           SFUInt16 *editSFAspectHeight(void);
     const SFUInt16 *getSFAspectHeight (void) const;

#ifdef OSG_1_COMPAT
           SFUInt16 *getSFAspectWidth(void);
#endif
           SFUInt16 *editSFAspectWidth(void);
     const SFUInt16 *getSFAspectWidth (void) const;


           MaterialPtrConst getMaterial(void) const;

#ifdef OSG_1_COMPAT
           Vec3f &getTexCoords(const UInt32 index);
           MFVec3f &getTexCoords(void);
#endif
           Vec3f &editTexCoords(const UInt32 index);
     const Vec3f &getTexCoords (const UInt32 index) const;
           MFVec3f &editTexCoords(void);
     const MFVec3f &getTexCoords(void) const;

#ifdef OSG_1_COMPAT
           Pnt2f &getPositions(const UInt32 index);
           MFPnt2f &getPositions(void);
#endif
           Pnt2f &editPositions(const UInt32 index);
     const Pnt2f &getPositions (const UInt32 index) const;
           MFPnt2f &editPositions(void);
     const MFPnt2f &getPositions(void) const;

#ifdef OSG_1_COMPAT
           bool &getNormalizedX(void);
#endif
           bool &editNormalizedX(void);
     const bool &getNormalizedX (void) const;

#ifdef OSG_1_COMPAT
           bool &getNormalizedY(void);
#endif
           bool &editNormalizedY(void);
     const bool &getNormalizedY (void) const;

#ifdef OSG_1_COMPAT
           UInt16 &getAspectHeight(void);
#endif
           UInt16 &editAspectHeight(void);
     const UInt16 &getAspectHeight (void) const;

#ifdef OSG_1_COMPAT
           UInt16 &getAspectWidth(void);
#endif
           UInt16 &editAspectWidth(void);
     const UInt16 &getAspectWidth (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setMaterial(MaterialPtrConstArg value);
     void setNormalizedX(const bool &value);
     void setNormalizedY(const bool &value);
     void setAspectHeight(const UInt16 &value);
     void setAspectWidth(const UInt16 &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    virtual void pushToField     (      FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void insertIntoMField(const UInt32                    uiIndex, 
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void replaceInMField (const UInt32                    uiIndex,
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void removeFromMField(const UInt32                    uiIndex, 
                                  const UInt32                    uiFieldId  );
    
    virtual void removeFromMField(      FieldContainerPtrConstArg pElement, 
                                  const UInt32                    uiFieldId  );

    virtual void clearField      (const UInt32                    uiFieldId  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */


    void pushToTexCoords           (const Vec3f& value   );
    void insertIntoTexCoords      (UInt32                uiIndex,
                                    const Vec3f& value   );
    void replaceInTexCoords  (UInt32                uiIndex,
                                    const Vec3f& value   );
    void replaceInTexCoords (const Vec3f& pOldElem,
                                    const Vec3f& pNewElem);
    void removeFromTexCoords (UInt32                uiIndex );
    void removeFromTexCoords(const Vec3f& value   );
    void clearTexCoords            (void                          );


 


    void pushToPositions           (const Pnt2f& value   );
    void insertIntoPositions      (UInt32                uiIndex,
                                    const Pnt2f& value   );
    void replaceInPositions  (UInt32                uiIndex,
                                    const Pnt2f& value   );
    void replaceInPositions (const Pnt2f& pOldElem,
                                    const Pnt2f& pNewElem);
    void removeFromPositions (UInt32                uiIndex );
    void removeFromPositions(const Pnt2f& value   );
    void clearPositions            (void                          );


 

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

    static  PolygonBackgroundPtr create     (void); 
    static  PolygonBackgroundPtr createEmpty(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerPtr shallowCopy(void) const; 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFMaterialPtr _sfMaterial;
    MFVec3f _mfTexCoords;
    MFPnt2f _mfPositions;
    SFBool _sfNormalizedX;
    SFBool _sfNormalizedY;
    SFUInt16 _sfAspectHeight;
    SFUInt16 _sfAspectWidth;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PolygonBackgroundBase(void);
    PolygonBackgroundBase(const PolygonBackgroundBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PolygonBackgroundBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const PolygonBackground *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_FIELDCONTAINERPTR
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);

            void execSync (      PolygonBackgroundBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      PolygonBackgroundBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

#if 0
    virtual void execBeginEditV(ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);

            void execBeginEdit (ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainerPtr createAspectCopy(void) const;
#endif

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
    void operator =(const PolygonBackgroundBase &source);
};

typedef PolygonBackgroundBase *PolygonBackgroundBaseP;

/** Type specific RefPtr type for PolygonBackground. */
typedef RefPtr<PolygonBackgroundPtr> PolygonBackgroundRefPtr;

typedef osgIF<
    PolygonBackgroundBase::isNodeCore,

    CoredNodePtr<PolygonBackground>,
    FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC>::_IRet

        PolygonBackgroundNodePtr;

OSG_END_NAMESPACE

#define OSGPOLYGONBACKGROUNDBASE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGPOLYGONBACKGROUNDBASE_H_ */
