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

#ifndef _OSGGEOPROPERTY_H_
#define _OSGGEOPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoPropertyBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

class Window;

/*! \brief GeoProperty class. See \ref
           PageSystemGeoProperty for a description.
    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING GeoProperty : public GeoPropertyBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoPropertyBase                             Inherited;

    static const UInt32 UsageUnspecified      = 0x00000000;
    
    static const UInt32 UsageSpaceMask        = 0x0000000F;
    
    static const UInt32 UsageObjectSpace      = 0x00000001;  // pos
    static const UInt32 UsageTangentSpace     = 0x00000002;  // norm, binorm, tang
    static const UInt32 UsageParameterSpace   = 0x00000004;  // tex coord
    static const UInt32 UsageColorSpace       = 0x00000008;  // color
    
    static const UInt32 UsageSystemSet        = 0x10000000;  // mark as set by OpenSG
    
    
    static const UInt32 VectorTypeScalar      = 0x00000000;
    static const UInt32 VectorTypePoint       = 0x00000001;
    static const UInt32 VectorTypeVector      = 0x00000002;
    static const UInt32 VectorTypeColor       = 0x00000003;
    
    /*---------------------------------------------------------------------*/
    /*! \name                 Property Interface                           */
    /*! \{                                                                 */

    virtual       UInt32                 getFormat    (void) const = 0;
    virtual       UInt32                 getFormatSize(void) const = 0;
    virtual       UInt32                 getVectorType(void) const = 0;
    virtual       UInt32                 getStride    (void) const = 0;
    virtual       UInt32                 getDimension (void) const = 0;
    virtual       UInt32                 getSize      (void) const;
    virtual       UInt32                 size         (void) const = 0;
    virtual const UInt8                 *getData      (void) const
    { return NULL;  }
#ifdef OSG_1_COMPAT
    virtual       UInt8                 *editData     (void) 
    { return NULL;  }
#endif
    virtual       GeoPropertyTransitPtr  clone        (void)       = 0;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass * getClass         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    inline static        UInt32            getStaticClassId (void);
    inline static  const StateChunkClass * getStaticClass   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void activate      (DrawEnv *pEnv, UInt32 index = 0) = 0;

    virtual void changeFrom    (DrawEnv    *pEnv,
                                StateChunk *old,
                                UInt32      index = 0)  = 0;

    virtual void deactivate    (DrawEnv *pEnv, UInt32 index = 0) = 0;

    virtual bool isTransparent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Limited Access                             */
    /*! \{                                                                 */

    UInt32 getGLId(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Helper                                 */
    /*! \{                                                                 */

    inline static UInt32 MapFormatToSize(GLenum format);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoPropertyBase.

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt32                   uiOptions);
    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoProperty(void);
    GeoProperty(const GeoProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoProperty(void);

    /*! \}                                                                 */

    virtual GLenum getBufferType(void) = 0; // buffer type for VBOs

    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL Extensions Used                         */
    /*! \{                                                                 */

    static UInt32 _extVertexBufferObject;
    static UInt32 _extMultitexture;
    static UInt32 _arbVertexProgram;
    static UInt32 _extSecondaryColor;
    static UInt32 _funcBindBuffer;
    static UInt32 _funcMapBuffer;
    static UInt32 _funcUnmapBuffer;
    static UInt32 _funcBufferData;
    static UInt32 _funcBufferSubData;
    static UInt32 _funcDeleteBuffers;
    static UInt32 _funcGenBuffers;
    static UInt32 _funcglVertexAttribPointerARB;
    static UInt32 _funcglEnableVertexAttribArrayARB;
    static UInt32 _funcglDisableVertexAttribArrayARB;

    static UInt32 _glClientActiveTextureARB;
    static UInt32 _glSecondaryColorPointerEXT;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeoPropertyBase;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoProperty &source);
};

typedef GeoProperty *GeoPropertyP;

OSG_END_NAMESPACE

#include "OSGGeoPropertyBase.inl"
#include "OSGGeoProperty.inl"

#endif /* _OSGGEOPROPERTY_H_ */
