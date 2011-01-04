/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGSIMPLETEXTUREDMATERIAL_H_
#define _OSGSIMPLETEXTUREDMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextureObjChunk.h"
#include "OSGTexGenChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleTexturedMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Simple textured Material wrapping standard OpenGL lighting and a
           single texture.  See \ref 
           PageSystemMaterialTexturedSimpleMaterial for a description.

    \ingroup GrpDrawablesMaterialObj
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING SimpleTexturedMaterial : 
    public SimpleTexturedMaterialBase
{
    /*==========================  PUBLIC  =================================*/

  public:

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

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Rendering                                  */
    /*! \{                                                                 */

    virtual void rebuildState (void);

    virtual bool isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Updates                                   */
    /*! \{                                                                 */

    inline void imageChanged(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // these chunks are used for rendering the material

    TextureObjChunkUnrecPtr _textureChunk;
    TexGenChunkUnrecPtr     _texGenChunk;
    TextureEnvChunkUnrecPtr _texEnvChunk;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleTexturedMaterial(void);
    SimpleTexturedMaterial(const SimpleTexturedMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleTexturedMaterial(void); 

    /*! \}                                                                 */ 
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helper                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helper                                   */
    /*! \{                                                                 */

    void prepareLocalChunks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef SimpleTexturedMaterialBase Inherited;

    friend class FieldContainer;
    friend class SimpleTexturedMaterialBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleTexturedMaterial &source);
};

typedef SimpleTexturedMaterial              *SimpleTexturedMaterialP;

OSG_END_NAMESPACE

#include "OSGSimpleTexturedMaterialBase.inl"
#include "OSGSimpleTexturedMaterial.inl"

#endif /* _OSGTEXTUREDSIMPLEMATERIAL_H_ */
