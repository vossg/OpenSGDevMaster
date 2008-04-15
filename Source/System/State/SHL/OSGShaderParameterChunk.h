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

    bool setUniformParameter(const Char8 *name,       bool    value);
    bool setUniformParameter(const Char8 *name,       Int32   value);
    bool setUniformParameter(const Char8 *name,       Real32  value);
    bool setUniformParameter(const Char8 *name, const Vec2f  &value);
    bool setUniformParameter(const Char8 *name, const Vec3f  &value);
    bool setUniformParameter(const Char8 *name, const Vec4f  &value);
    bool setUniformParameter(const Char8 *name, const Matrix &value);
    bool setUniformParameter(const Char8 *name, const Pnt2f  &value);
    bool setUniformParameter(const Char8 *name, const Pnt3f  &value);
    
    bool    setUniformParameter(const char *name, const MFInt32  &value);
    bool    setUniformParameter(const char *name, const MFReal32 &value);
    bool    setUniformParameter(const char *name, const MFVec2f  &value);
    bool    setUniformParameter(const char *name, const MFVec3f  &value);
    bool    setUniformParameter(const char *name, const MFVec4f  &value);
    bool    setUniformParameter(const char *name, const MFMatrix &value);
    bool    setUniformParameter(const char *name, const MFPnt2f  &value);
    bool    setUniformParameter(const char *name, const MFPnt3f  &value);

    bool getUniformParameter(const Char8 *name,       bool   &value);
    bool getUniformParameter(const Char8 *name,       Int32  &value);
    bool getUniformParameter(const Char8 *name,       Real32 &value);
    bool getUniformParameter(const Char8 *name,       Vec2f  &value);
    bool getUniformParameter(const Char8 *name,       Vec3f  &value);
    bool getUniformParameter(const Char8 *name,       Vec4f  &value);
    bool getUniformParameter(const Char8 *name,       Matrix &value);
    bool getUniformParameter(const Char8 *name,       Pnt2f  &value);
    bool getUniformParameter(const Char8 *name,       Pnt3f  &value);

    bool    getUniformParameter(const char *name, MFInt32  &value);
    bool    getUniformParameter(const char *name, MFReal32 &value);
    bool    getUniformParameter(const char *name, MFVec2f  &value);
    bool    getUniformParameter(const char *name, MFVec3f  &value);
    bool    getUniformParameter(const char *name, MFVec4f  &value);
    bool    getUniformParameter(const char *name, MFMatrix &value);
    bool    getUniformParameter(const char *name, MFPnt2f  &value);
    bool    getUniformParameter(const char *name, MFPnt3f  &value);
    
    bool subUniformParameter(const Char8 *name);
    
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
