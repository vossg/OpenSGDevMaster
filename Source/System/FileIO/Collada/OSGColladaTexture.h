/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADATEXTURE_H_
#define _OSGCOLLADATEXTURE_H_

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaExtraHandler.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTextureTransformChunk.h"

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaEffect;
class ColladaSampler2D;

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaTexture : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaElement Inherited;
    typedef ColladaTexture Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaTexture);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */
    static ColladaElementTransitPtr create(daeElement    *elem, 
                                           ColladaGlobal *global);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read(ColladaElement *colElemParent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    ColladaEffect   *getEffect (void                    ) const;
    void             setEffect (ColladaEffect *colEffect);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    TextureObjChunk       *getTexture      (void) const;
    TextureEnvChunk       *getTexEnv       (void) const;
    TextureEnvChunk       *editTexEnv      (void);
    TextureTransformChunk *getTexTransform (void) const;
    TextureTransformChunk *editTexTransform(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

                  bool        hasAlpha      (void) const;
                  bool        hasBinaryAlpha(void) const;

    virtual const std::string getSemantic   (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::vector<ColladaExtraHandlerRefPtr> ExtraHandlerStore;
    typedef ExtraHandlerStore::iterator            ExtraHandlerStoreIt;
    typedef ExtraHandlerStore::const_iterator      ExtraHandlerStoreConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaTexture(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaTexture(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    void readSampler(      ColladaSampler2D *colSampler);
    void readImage  (const Char8            *texId     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    ColladaEffect                 *_colEffect;
    TextureObjChunkUnrecPtr        _texObj;
    TextureEnvChunkUnrecPtr        _texEnv;
    TextureTransformChunkUnrecPtr  _texTransform;
    ExtraHandlerStore              _extraHandlers;

};

OSG_GEN_MEMOBJPTR(ColladaTexture);

OSG_END_NAMESPACE

// #include "OSGColladaTexture.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADATEXTURE_H_
