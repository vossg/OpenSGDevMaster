/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGSHADERPARAMETERCHUNK_H_
#define _OSGSHADERPARAMETERCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderParameterChunkBase.h"
#include "OSGVector.h"
#include "OSGMatrix.h"

#include "OSGSysMFields.h"
#include "OSGVecMFields.h"
#include "OSGMathMFields.h"
#include "OSGShaderParameter.h"

OSG_BEGIN_NAMESPACE

class ShaderParameterAccess;

/*! \brief ShaderParameterChunk class. See \ref 
    PageSystemShaderParameterChunk for a description.
*/

class OSG_STATE_DLLMAPPING ShaderParameterChunk : 
    public ShaderParameterChunkBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderParameterChunkBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 ShaderParameterChunk Access                  */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    bool setUniformParameter   (const Char8 *name,       bool      value);
    bool setUniformParameter   (const Char8 *name,       Int32     value);
    bool setUniformParameter   (const Char8 *name,       Real32    value);
    bool setUniformParameter   (const Char8 *name, const Vec2f    &value);
    bool setUniformParameter   (const Char8 *name, const Vec3f    &value);
    bool setUniformParameter   (const Char8 *name, const Vec4f    &value);
    bool setUniformParameter   (const Char8 *name, const Matrix   &value);
    bool setUniformParameter   (const Char8 *name, const Pnt2f    &value);
    bool setUniformParameter   (const Char8 *name, const Pnt3f    &value);
    
    bool setUniformParameter   (const Char8 *name, const MFInt32  &value);
    bool setUniformParameter   (const Char8 *name, const MFReal32 &value);
    bool setUniformParameter   (const Char8 *name, const MFVec2f  &value);
    bool setUniformParameter   (const Char8 *name, const MFVec3f  &value);
    bool setUniformParameter   (const Char8 *name, const MFVec4f  &value);
    bool setUniformParameter   (const Char8 *name, const MFMatrix &value);
    bool setUniformParameter   (const Char8 *name, const MFPnt2f  &value);
    bool setUniformParameter   (const Char8 *name, const MFPnt3f  &value);

    bool getUniformParameter   (const Char8 *name,       bool     &value);
    bool getUniformParameter   (const Char8 *name,       Int32    &value);
    bool getUniformParameter   (const Char8 *name,       Real32   &value);
    bool getUniformParameter   (const Char8 *name,       Vec2f    &value);
    bool getUniformParameter   (const Char8 *name,       Vec3f    &value);
    bool getUniformParameter   (const Char8 *name,       Vec4f    &value);
    bool getUniformParameter   (const Char8 *name,       Matrix   &value);
    bool getUniformParameter   (const Char8 *name,       Pnt2f    &value);
    bool getUniformParameter   (const Char8 *name,       Pnt3f    &value);

    bool getUniformParameter   (const Char8 *name,       MFInt32  &value);
    bool getUniformParameter   (const Char8 *name,       MFReal32 &value);
    bool getUniformParameter   (const Char8 *name,       MFVec2f  &value);
    bool getUniformParameter   (const Char8 *name,       MFVec3f  &value);
    bool getUniformParameter   (const Char8 *name,       MFVec4f  &value);
    bool getUniformParameter   (const Char8 *name,       MFMatrix &value);
    bool getUniformParameter   (const Char8 *name,       MFPnt2f  &value);
    bool getUniformParameter   (const Char8 *name,       MFPnt3f  &value);
    
    bool subUniformParameter   (const Char8 *name);

    void clearUniformParameters(      void       );
#endif

    bool addUniformVariable   (const Char8 *name,       bool      value);
    bool addUniformVariable   (const Char8 *name,       Int32     value);
    bool addUniformVariable   (const Char8 *name,       Real32    value);
    bool addUniformVariable   (const Char8 *name, const Vec2f    &value);
    bool addUniformVariable   (const Char8 *name, const Vec3f    &value);
    bool addUniformVariable   (const Char8 *name, const Vec4f    &value);
    bool addUniformVariable   (const Char8 *name, const Matrix   &value);
    bool addUniformVariable   (const Char8 *name, const Pnt2f    &value);
    bool addUniformVariable   (const Char8 *name, const Pnt3f    &value);
    
    bool addUniformVariable   (const Char8 *name, const MFInt32  &value);
    bool addUniformVariable   (const Char8 *name, const MFReal32 &value);
    bool addUniformVariable   (const Char8 *name, const MFVec2f  &value);
    bool addUniformVariable   (const Char8 *name, const MFVec3f  &value);
    bool addUniformVariable   (const Char8 *name, const MFVec4f  &value);
    bool addUniformVariable   (const Char8 *name, const MFMatrix &value);
    bool addUniformVariable   (const Char8 *name, const MFPnt2f  &value);
    bool addUniformVariable   (const Char8 *name, const MFPnt3f  &value);

    bool updateUniformVariable(const Char8 *name,       bool      value);
    bool updateUniformVariable(const Char8 *name,       Int32     value);
    bool updateUniformVariable(const Char8 *name,       Real32    value);
    bool updateUniformVariable(const Char8 *name, const Vec2f    &value);
    bool updateUniformVariable(const Char8 *name, const Vec3f    &value);
    bool updateUniformVariable(const Char8 *name, const Vec4f    &value);
    bool updateUniformVariable(const Char8 *name, const Matrix   &value);
    bool updateUniformVariable(const Char8 *name, const Pnt2f    &value);
    bool updateUniformVariable(const Char8 *name, const Pnt3f    &value);
    
    bool updateUniformVariable(const Char8 *name, const MFInt32  &value);
    bool updateUniformVariable(const Char8 *name, const MFReal32 &value);
    bool updateUniformVariable(const Char8 *name, const MFVec2f  &value);
    bool updateUniformVariable(const Char8 *name, const MFVec3f  &value);
    bool updateUniformVariable(const Char8 *name, const MFVec4f  &value);
    bool updateUniformVariable(const Char8 *name, const MFMatrix &value);
    bool updateUniformVariable(const Char8 *name, const MFPnt2f  &value);
    bool updateUniformVariable(const Char8 *name, const MFPnt3f  &value);

    bool getUniformVariable   (const Char8 *name,       bool     &value);
    bool getUniformVariable   (const Char8 *name,       Int32    &value);
    bool getUniformVariable   (const Char8 *name,       Real32   &value);
    bool getUniformVariable   (const Char8 *name,       Vec2f    &value);
    bool getUniformVariable   (const Char8 *name,       Vec3f    &value);
    bool getUniformVariable   (const Char8 *name,       Vec4f    &value);
    bool getUniformVariable   (const Char8 *name,       Matrix   &value);
    bool getUniformVariable   (const Char8 *name,       Pnt2f    &value);
    bool getUniformVariable   (const Char8 *name,       Pnt3f    &value);

    bool getUniformVariable   (const Char8 *name,       MFInt32  &value);
    bool getUniformVariable   (const Char8 *name,       MFReal32 &value);
    bool getUniformVariable   (const Char8 *name,       MFVec2f  &value);
    bool getUniformVariable   (const Char8 *name,       MFVec3f  &value);
    bool getUniformVariable   (const Char8 *name,       MFVec4f  &value);
    bool getUniformVariable   (const Char8 *name,       MFMatrix &value);
    bool getUniformVariable   (const Char8 *name,       MFPnt2f  &value);
    bool getUniformVariable   (const Char8 *name,       MFPnt3f  &value);

    bool addOSGVariable       (const Char8 *name                       );
    
    bool subUniformVariable   (const Char8 *name);

    void clearUniformVariables(      void       );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShaderParameterChunkBase.

    void onCreate (const ShaderParameterChunk *source = NULL);
    void onDestroy(      UInt32                uiId         );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderParameterChunk(void);
    ShaderParameterChunk(const ShaderParameterChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderParameterChunk(void); 

    /*---------------------------------------------------------------------*/
    /*! \name                  Parameter Access                            */
    /*! \{                                                                 */

    ShaderParameterAccess *_parameter_access;
    bool                   _cleared_parameters;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderParameterChunkBase;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderParameterChunk &source);
};

typedef ShaderParameterChunk *ShaderParameterChunkP;

OSG_END_NAMESPACE

#include "OSGShaderParameterChunkBase.inl"
#include "OSGShaderParameterChunk.inl"

#endif /* _OSGSHADERPARAMETERCHUNK_H_ */
