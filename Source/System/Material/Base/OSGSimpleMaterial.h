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

#ifndef _OSGSIMPLEMATERIAL_H_
#define _OSGSIMPLEMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGMaterialChunk.h"
#include "OSGBlendChunk.h"
#include "OSGSimpleMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Simple Material wrapping standard OpenGL lighting.  See \ref 
    PageSystemMaterialSimpleMaterial for a description.

    \ingroup GrpSystemMaterialBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING SimpleMaterial : public SimpleMaterialBase
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
    /*! \name                      Output                                  */
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

    /*=========================  PROTECTED  ===============================*/

  protected:

    // these chunks are used for rendering the material

    MaterialChunkUnrecPtr _materialChunk;
    BlendChunkUnrecPtr    _blendChunk;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleMaterial(void);
    SimpleMaterial(const SimpleMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleMaterial(void);

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

    typedef SimpleMaterialBase Inherited;

    friend class FieldContainer;
    friend class SimpleMaterialBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleMaterial &source);
};

typedef SimpleMaterial              *SimpleMaterialP;

OSG_END_NAMESPACE

#include "OSGSimpleMaterialBase.inl"
#include "OSGSimpleMaterial.inl"

#endif /* _OSGSIMPLEMATERIAL_H_ */
