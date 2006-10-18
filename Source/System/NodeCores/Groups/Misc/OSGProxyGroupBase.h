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
 **     class ProxyGroup
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGPROXYGROUPBASE_H_
#define _OSGPROXYGROUPBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGGroupDef.h"

#include "OSGBaseTypes.h"

#include "OSGGroup.h" // Parent

#include "OSGBoolFields.h" // Enabled type
#include "OSGStringFields.h" // Url type
#include "OSGNodeFields.h" // Root type
#include "OSGUInt32Fields.h" // State type
#include "OSGBoolFields.h" // ConcurrentLoad type
#include "OSGDynamicVolumeFields.h" // Volume type
#include "OSGUInt32Fields.h" // Indices type
#include "OSGUInt32Fields.h" // Triangles type
#include "OSGUInt32Fields.h" // Positions type
#include "OSGUInt32Fields.h" // Geometries type
#include "OSGStringFields.h" // AbsoluteUrl type
#include "OSGUInt8Fields.h" // Inline type

#include "OSGProxyGroupFields.h"

OSG_BEGIN_NAMESPACE

class ProxyGroup;

//! \brief ProxyGroup Base Class.

class OSG_GROUP_DLLMAPPING ProxyGroupBase : public Group
{
  public:

    typedef Group Inherited;
    typedef Group ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    typedef PointerFwdBuilder<GroupPtr, 
                              GroupConstPtr, 
                              ProxyGroup>::ObjPtr         ObjPtr;
    typedef PointerFwdBuilder<GroupPtr, 
                              GroupConstPtr, 
                              ProxyGroup>::ObjPtrConst    ObjPtrConst;
    typedef PointerFwdBuilder<GroupPtr, 
                              GroupConstPtr,
                              ProxyGroup>::ObjConstPtr    ObjConstPtr;
    typedef PointerFwdBuilder<GroupPtr, 
                              GroupConstPtr,
                              ProxyGroup>::ObjPtrArg      ObjPtrArg;
    typedef PointerFwdBuilder<GroupPtr, 
                              GroupConstPtr,
                              ProxyGroup>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerFwdBuilder<GroupPtr, 
                              GroupConstPtr,
                              ProxyGroup>::ObjPtrConstArg ObjPtrConstArg;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        EnabledFieldId = Inherited::NextFieldId,
        UrlFieldId = EnabledFieldId + 1,
        RootFieldId = UrlFieldId + 1,
        StateFieldId = RootFieldId + 1,
        ConcurrentLoadFieldId = StateFieldId + 1,
        VolumeFieldId = ConcurrentLoadFieldId + 1,
        IndicesFieldId = VolumeFieldId + 1,
        TrianglesFieldId = IndicesFieldId + 1,
        PositionsFieldId = TrianglesFieldId + 1,
        GeometriesFieldId = PositionsFieldId + 1,
        AbsoluteUrlFieldId = GeometriesFieldId + 1,
        InlineFieldId = AbsoluteUrlFieldId + 1,
        NextFieldId = InlineFieldId + 1
    };

    static const OSG::BitVector EnabledFieldMask = 
        (TypeTraits<BitVector>::One << EnabledFieldId);
    static const OSG::BitVector UrlFieldMask = 
        (TypeTraits<BitVector>::One << UrlFieldId);
    static const OSG::BitVector RootFieldMask = 
        (TypeTraits<BitVector>::One << RootFieldId);
    static const OSG::BitVector StateFieldMask = 
        (TypeTraits<BitVector>::One << StateFieldId);
    static const OSG::BitVector ConcurrentLoadFieldMask = 
        (TypeTraits<BitVector>::One << ConcurrentLoadFieldId);
    static const OSG::BitVector VolumeFieldMask = 
        (TypeTraits<BitVector>::One << VolumeFieldId);
    static const OSG::BitVector IndicesFieldMask = 
        (TypeTraits<BitVector>::One << IndicesFieldId);
    static const OSG::BitVector TrianglesFieldMask = 
        (TypeTraits<BitVector>::One << TrianglesFieldId);
    static const OSG::BitVector PositionsFieldMask = 
        (TypeTraits<BitVector>::One << PositionsFieldId);
    static const OSG::BitVector GeometriesFieldMask = 
        (TypeTraits<BitVector>::One << GeometriesFieldId);
    static const OSG::BitVector AbsoluteUrlFieldMask = 
        (TypeTraits<BitVector>::One << AbsoluteUrlFieldId);
    static const OSG::BitVector InlineFieldMask = 
        (TypeTraits<BitVector>::One << InlineFieldId);
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


#ifdef OSG_1_COMPAT
           SFBool *getSFEnabled(void);
#endif
           SFBool *editSFEnabled(void);
     const SFBool *getSFEnabled (void) const;

#ifdef OSG_1_COMPAT
           SFString *getSFUrl(void);
#endif
           SFString *editSFUrl(void);
     const SFString *getSFUrl (void) const;
     const SFNodePtr *getSFRoot (void) const;

#ifdef OSG_1_COMPAT
           SFUInt32 *getSFState(void);
#endif
           SFUInt32 *editSFState(void);
     const SFUInt32 *getSFState (void) const;

#ifdef OSG_1_COMPAT
           SFBool *getSFConcurrentLoad(void);
#endif
           SFBool *editSFConcurrentLoad(void);
     const SFBool *getSFConcurrentLoad (void) const;

#ifdef OSG_1_COMPAT
           SFDynamicVolume *getSFVolume(void);
#endif
           SFDynamicVolume *editSFVolume(void);
     const SFDynamicVolume *getSFVolume (void) const;

#ifdef OSG_1_COMPAT
           SFUInt32 *getSFIndices(void);
#endif
           SFUInt32 *editSFIndices(void);
     const SFUInt32 *getSFIndices (void) const;

#ifdef OSG_1_COMPAT
           SFUInt32 *getSFTriangles(void);
#endif
           SFUInt32 *editSFTriangles(void);
     const SFUInt32 *getSFTriangles (void) const;

#ifdef OSG_1_COMPAT
           SFUInt32 *getSFPositions(void);
#endif
           SFUInt32 *editSFPositions(void);
     const SFUInt32 *getSFPositions (void) const;

#ifdef OSG_1_COMPAT
           SFUInt32 *getSFGeometries(void);
#endif
           SFUInt32 *editSFGeometries(void);
     const SFUInt32 *getSFGeometries (void) const;

#ifdef OSG_1_COMPAT
           MFUInt8 *getMFInline(void);
#endif
           MFUInt8 *editMFInline(void);
     const MFUInt8 *getMFInline (void) const;


#ifdef OSG_1_COMPAT
           bool &getEnabled(void);
#endif
           bool &editEnabled(void);
     const bool &getEnabled (void) const;

#ifdef OSG_1_COMPAT
           std::string &getUrl(void);
#endif
           std::string &editUrl(void);
     const std::string &getUrl (void) const;

           NodePtrConst getRoot(void) const;

#ifdef OSG_1_COMPAT
           UInt32 &getState(void);
#endif
           UInt32 &editState(void);
     const UInt32 &getState (void) const;

#ifdef OSG_1_COMPAT
           bool &getConcurrentLoad(void);
#endif
           bool &editConcurrentLoad(void);
     const bool &getConcurrentLoad (void) const;

#ifdef OSG_1_COMPAT
           DynamicVolume &getVolume(void);
#endif
           DynamicVolume &editVolume(void);
     const DynamicVolume &getVolume (void) const;

#ifdef OSG_1_COMPAT
           UInt32 &getIndices(void);
#endif
           UInt32 &editIndices(void);
     const UInt32 &getIndices (void) const;

#ifdef OSG_1_COMPAT
           UInt32 &getTriangles(void);
#endif
           UInt32 &editTriangles(void);
     const UInt32 &getTriangles (void) const;

#ifdef OSG_1_COMPAT
           UInt32 &getPositions(void);
#endif
           UInt32 &editPositions(void);
     const UInt32 &getPositions (void) const;

#ifdef OSG_1_COMPAT
           UInt32 &getGeometries(void);
#endif
           UInt32 &editGeometries(void);
     const UInt32 &getGeometries (void) const;

#ifdef OSG_1_COMPAT
           UInt8 &getInline(const UInt32 index);
           MFUInt8 &getInline(void);
#endif
           UInt8 &editInline(const UInt32 index);
     const UInt8 &getInline (const UInt32 index) const;
           MFUInt8 &editInline(void);
     const MFUInt8 &getInline(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setEnabled(const bool &value);
     void setUrl(const std::string &value);
     void setRoot(NodePtrConstArg value);
     void setState(const UInt32 &value);
     void setConcurrentLoad(const bool &value);
     void setVolume(const DynamicVolume &value);
     void setIndices(const UInt32 &value);
     void setTriangles(const UInt32 &value);
     void setPositions(const UInt32 &value);
     void setGeometries(const UInt32 &value);

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


    void pushToInline           (const UInt8& value   );
    void insertIntoInline      (UInt32                uiIndex,
                                    const UInt8& value   );
    void replaceInInline  (UInt32                uiIndex,
                                    const UInt8& value   );
    void replaceInInline (const UInt8& pOldElem,
                                    const UInt8& pNewElem);
    void removeFromInline (UInt32                uiIndex );
    void removeFromInline(const UInt8& value   );
    void clearInline            (void                          );


 

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

    static  ProxyGroupPtr create     (void); 
    static  ProxyGroupPtr createEmpty(void); 

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

    SFBool _sfEnabled;
    SFString _sfUrl;
    SFNodePtr _sfRoot;
    SFUInt32 _sfState;
    SFBool _sfConcurrentLoad;
    SFDynamicVolume _sfVolume;
    SFUInt32 _sfIndices;
    SFUInt32 _sfTriangles;
    SFUInt32 _sfPositions;
    SFUInt32 _sfGeometries;
    SFString _sfAbsoluteUrl;
    MFUInt8 _mfInline;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ProxyGroupBase(void);
    ProxyGroupBase(const ProxyGroupBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ProxyGroupBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const ProxyGroup *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


#ifdef OSG_1_COMPAT
           SFString *getSFAbsoluteUrl(void);
#endif
           SFString *editSFAbsoluteUrl(void);
     const SFString *getSFAbsoluteUrl (void) const;


#ifdef OSG_1_COMPAT
           std::string &getAbsoluteUrl(void);
#endif
           std::string &editAbsoluteUrl(void);
     const std::string &getAbsoluteUrl(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setAbsoluteUrl(const std::string &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */



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

            void execSync (      ProxyGroupBase *pFrom,
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

            void execSync (      ProxyGroupBase *pFrom,
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
    void operator =(const ProxyGroupBase &source);
};

typedef ProxyGroupBase *ProxyGroupBaseP;

/** Type specific RefPtr type for ProxyGroup. */
typedef RefPtr<ProxyGroupPtr> ProxyGroupRefPtr;

typedef osgIF<
    ProxyGroupBase::isNodeCore,

    CoredNodePtr<ProxyGroup>,
    FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC>::_IRet

        ProxyGroupNodePtr;

OSG_END_NAMESPACE

#define OSGPROXYGROUPBASE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGPROXYGROUPBASE_H_ */
