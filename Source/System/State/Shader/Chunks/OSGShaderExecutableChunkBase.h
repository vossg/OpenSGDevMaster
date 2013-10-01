/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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
 **     class ShaderExecutableChunk
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSHADEREXECUTABLECHUNKBASE_H_
#define _OSGSHADEREXECUTABLECHUNKBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGSystemDef.h"

//#include "OSGBaseTypes.h"

#include "OSGStateChunk.h" // Parent

#include "OSGShaderProgramFields.h"     // VertexShader type
#include "OSGShaderProgramVariablesFields.h" // Variables type
#include "OSGSysFields.h"               // VariableLocations type
#include "OSGBaseFields.h"              // GeometryInputType type
#include "OSGShaderAttributeFields.h"   // Attributes type

#include "OSGShaderExecutableChunkFields.h"

OSG_BEGIN_NAMESPACE


class ShaderExecutableChunk;

//! \brief ShaderExecutableChunk Base Class.

class OSG_SYSTEM_DLLMAPPING ShaderExecutableChunkBase : public StateChunk
{
  public:

    typedef StateChunk Inherited;
    typedef StateChunk ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(ShaderExecutableChunk);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        VertexShaderFieldId = Inherited::NextFieldId,
        TessControlShaderFieldId = VertexShaderFieldId + 1,
        TessEvaluationShaderFieldId = TessControlShaderFieldId + 1,
        GeometryShaderFieldId = TessEvaluationShaderFieldId + 1,
        FragmentShaderFieldId = GeometryShaderFieldId + 1,
        VariablesFieldId = FragmentShaderFieldId + 1,
        VariableLocationsFieldId = VariablesFieldId + 1,
        ProceduralVariableLocationsFieldId = VariableLocationsFieldId + 1,
        GeometryVerticesOutFieldId = ProceduralVariableLocationsFieldId + 1,
        GeometryInputTypeFieldId = GeometryVerticesOutFieldId + 1,
        GeometryOutputTypeFieldId = GeometryInputTypeFieldId + 1,
        AttributesFieldId = GeometryOutputTypeFieldId + 1,
        GLIdFieldId = AttributesFieldId + 1,
        PointSizeFieldId = GLIdFieldId + 1,
        NextFieldId = PointSizeFieldId + 1
    };

    static const OSG::BitVector VertexShaderFieldMask =
        (TypeTraits<BitVector>::One << VertexShaderFieldId);
    static const OSG::BitVector TessControlShaderFieldMask =
        (TypeTraits<BitVector>::One << TessControlShaderFieldId);
    static const OSG::BitVector TessEvaluationShaderFieldMask =
        (TypeTraits<BitVector>::One << TessEvaluationShaderFieldId);
    static const OSG::BitVector GeometryShaderFieldMask =
        (TypeTraits<BitVector>::One << GeometryShaderFieldId);
    static const OSG::BitVector FragmentShaderFieldMask =
        (TypeTraits<BitVector>::One << FragmentShaderFieldId);
    static const OSG::BitVector VariablesFieldMask =
        (TypeTraits<BitVector>::One << VariablesFieldId);
    static const OSG::BitVector VariableLocationsFieldMask =
        (TypeTraits<BitVector>::One << VariableLocationsFieldId);
    static const OSG::BitVector ProceduralVariableLocationsFieldMask =
        (TypeTraits<BitVector>::One << ProceduralVariableLocationsFieldId);
    static const OSG::BitVector GeometryVerticesOutFieldMask =
        (TypeTraits<BitVector>::One << GeometryVerticesOutFieldId);
    static const OSG::BitVector GeometryInputTypeFieldMask =
        (TypeTraits<BitVector>::One << GeometryInputTypeFieldId);
    static const OSG::BitVector GeometryOutputTypeFieldMask =
        (TypeTraits<BitVector>::One << GeometryOutputTypeFieldId);
    static const OSG::BitVector AttributesFieldMask =
        (TypeTraits<BitVector>::One << AttributesFieldId);
    static const OSG::BitVector GLIdFieldMask =
        (TypeTraits<BitVector>::One << GLIdFieldId);
    static const OSG::BitVector PointSizeFieldMask =
        (TypeTraits<BitVector>::One << PointSizeFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef MFUncountedShaderProgramPtr MFVertexShaderType;
    typedef MFUncountedShaderProgramPtr MFTessControlShaderType;
    typedef MFUncountedShaderProgramPtr MFTessEvaluationShaderType;
    typedef MFUncountedShaderProgramPtr MFGeometryShaderType;
    typedef MFUncountedShaderProgramPtr MFFragmentShaderType;
    typedef SFUnrecChildShaderProgramVariablesPtr SFVariablesType;
    typedef MFInt32           MFVariableLocationsType;
    typedef MFInt32           MFProceduralVariableLocationsType;
    typedef SFUInt32          SFGeometryVerticesOutType;
    typedef SFGLenum          SFGeometryInputTypeType;
    typedef SFGLenum          SFGeometryOutputTypeType;
    typedef MFShaderAttribute MFAttributesType;
    typedef SFUInt32          SFGLIdType;
    typedef SFBool            SFPointSizeType;

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

            const SFUnrecChildShaderProgramVariablesPtr *getSFVariables      (void) const;
                  SFUnrecChildShaderProgramVariablesPtr *editSFVariables      (void);

                  SFUInt32            *editSFGeometryVerticesOut(void);
            const SFUInt32            *getSFGeometryVerticesOut (void) const;

                  SFGLenum            *editSFGeometryInputType(void);
            const SFGLenum            *getSFGeometryInputType (void) const;

                  SFGLenum            *editSFGeometryOutputType(void);
            const SFGLenum            *getSFGeometryOutputType (void) const;

                  MFShaderAttribute   *editMFAttributes     (void);
            const MFShaderAttribute   *getMFAttributes      (void) const;

                  SFUInt32            *editSFGLId           (void);
            const SFUInt32            *getSFGLId            (void) const;

                  SFBool              *editSFPointSize      (void);
            const SFBool              *getSFPointSize       (void) const;


                  ShaderProgramVariables * getVariables      (void) const;

                  UInt32              &editGeometryVerticesOut(void);
                  UInt32               getGeometryVerticesOut (void) const;

                  GLenum              &editGeometryInputType(void);
            const GLenum              &getGeometryInputType (void) const;

                  GLenum              &editGeometryOutputType(void);
            const GLenum              &getGeometryOutputType (void) const;

                  ShaderAttribute     &editAttributes     (const UInt32 index);
            const ShaderAttribute     &getAttributes      (const UInt32 index) const;

                  UInt32              &editGLId           (void);
                  UInt32               getGLId            (void) const;

                  bool                &editPointSize      (void);
                  bool                 getPointSize       (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

            void setVariables      (ShaderProgramVariables * const value);
            void setGeometryVerticesOut(const UInt32 value);
            void setGeometryInputType(const GLenum &value);
            void setGeometryOutputType(const GLenum &value);
            void setGLId           (const UInt32 value);
            void setPointSize      (const bool value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual SizeT  getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  ShaderExecutableChunkTransitPtr  create          (void);
    static  ShaderExecutableChunk           *createEmpty     (void);

    static  ShaderExecutableChunkTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  ShaderExecutableChunk            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  ShaderExecutableChunkTransitPtr  createDependent  (BitVector bFlags);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerTransitPtr shallowCopy     (void) const;
    virtual FieldContainerTransitPtr shallowCopyLocal(
                                       BitVector bFlags = FCLocal::All) const;
    virtual FieldContainerTransitPtr shallowCopyDependent(
                                                      BitVector bFlags) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    MFUncountedShaderProgramPtr _mfVertexShader;
    MFUncountedShaderProgramPtr _mfTessControlShader;
    MFUncountedShaderProgramPtr _mfTessEvaluationShader;
    MFUncountedShaderProgramPtr _mfGeometryShader;
    MFUncountedShaderProgramPtr _mfFragmentShader;
    SFUnrecChildShaderProgramVariablesPtr _sfVariables;
    MFInt32           _mfVariableLocations;
    MFInt32           _mfProceduralVariableLocations;
    SFUInt32          _sfGeometryVerticesOut;
    SFGLenum          _sfGeometryInputType;
    SFGLenum          _sfGeometryOutputType;
    MFShaderAttribute _mfAttributes;
    SFUInt32          _sfGLId;
    SFBool            _sfPointSize;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderExecutableChunkBase(void);
    ShaderExecutableChunkBase(const ShaderExecutableChunkBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderExecutableChunkBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const ShaderExecutableChunk *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Child linking                                                */
    /*! \{                                                                 */

    virtual bool unlinkChild(FieldContainer * const pChild,
                             UInt16           const childFieldId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleVertexShader    (void) const;
    EditFieldHandlePtr editHandleVertexShader   (void);
    GetFieldHandlePtr  getHandleTessControlShader (void) const;
    EditFieldHandlePtr editHandleTessControlShader(void);
    GetFieldHandlePtr  getHandleTessEvaluationShader (void) const;
    EditFieldHandlePtr editHandleTessEvaluationShader(void);
    GetFieldHandlePtr  getHandleGeometryShader  (void) const;
    EditFieldHandlePtr editHandleGeometryShader (void);
    GetFieldHandlePtr  getHandleFragmentShader  (void) const;
    EditFieldHandlePtr editHandleFragmentShader (void);
    GetFieldHandlePtr  getHandleVariables       (void) const;
    EditFieldHandlePtr editHandleVariables      (void);
    GetFieldHandlePtr  getHandleVariableLocations (void) const;
    EditFieldHandlePtr editHandleVariableLocations(void);
    GetFieldHandlePtr  getHandleProceduralVariableLocations (void) const;
    EditFieldHandlePtr editHandleProceduralVariableLocations(void);
    GetFieldHandlePtr  getHandleGeometryVerticesOut (void) const;
    EditFieldHandlePtr editHandleGeometryVerticesOut(void);
    GetFieldHandlePtr  getHandleGeometryInputType (void) const;
    EditFieldHandlePtr editHandleGeometryInputType(void);
    GetFieldHandlePtr  getHandleGeometryOutputType (void) const;
    EditFieldHandlePtr editHandleGeometryOutputType(void);
    GetFieldHandlePtr  getHandleAttributes      (void) const;
    EditFieldHandlePtr editHandleAttributes     (void);
    GetFieldHandlePtr  getHandleGLId            (void) const;
    EditFieldHandlePtr editHandleGLId           (void);
    GetFieldHandlePtr  getHandlePointSize       (void) const;
    EditFieldHandlePtr editHandlePointSize      (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


                  MFInt32             *editMFVariableLocations(void);
            const MFInt32             *getMFVariableLocations (void) const;

                  MFInt32             *editMFProceduralVariableLocations(void);
            const MFInt32             *getMFProceduralVariableLocations (void) const;


                  Int32               &editVariableLocations(const UInt32 index);
                  Int32                getVariableLocations (const UInt32 index) const;

                  Int32               &editProceduralVariableLocations(const UInt32 index);
                  Int32                getProceduralVariableLocations (const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      ShaderExecutableChunkBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainer *createAspectCopy(
                                    const FieldContainer *pRefAspect) const;
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
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderExecutableChunkBase &source);
};

typedef ShaderExecutableChunkBase *ShaderExecutableChunkBaseP;

OSG_END_NAMESPACE

#endif /* _OSGSHADEREXECUTABLECHUNKBASE_H_ */
