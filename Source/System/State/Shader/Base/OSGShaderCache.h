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

#ifndef _OSGSHADERCACHE_H_
#define _OSGSHADERCACHE_H_

#ifdef __sgi
#pragma once
#endif

//#define OSG_SHC_USE_REF     1
//#define OSG_SHC_REF_CLEANUP 1
//#define OSG_ASSERT_TREE     1

#include "OSGShaderCacheTree.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemShaderBase
    \ingroup GrpLibOSGSystem
    \nohierarchy
 */

class OSG_SYSTEM_DLLMAPPING ShaderCache
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ActiveShaderExeTree                              ShaderExeTree;
    typedef ActiveShaderVarTree                              ShaderVarTree;

    typedef ShaderExeTree::IdStore                           IdStore;

#ifdef OSG_SHC_USE_REF
    typedef std::pair  <IdStore, 
                        ShaderExecutableChunkUnrecPtr       > StoreElement;
    typedef std::pair  <IdStore, 
                        ShaderExecutableVarChunkUnrecPtr    > StoreVarElement;

    typedef std::vector<StoreElement                        > ShaderStore;
    typedef std::vector<StoreVarElement                     > ShaderVarStore;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Statistic                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    ShaderExecutableChunk    *findShader   (const IdStore &vIds);
    ShaderExecutableVarChunk *findShaderVar(const IdStore &vIds);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void addShader   (const IdStore                  &vIds,
                            ShaderExecutableChunk    *pShader);

    void addShaderVar(const IdStore                  &vIds,
                            ShaderExecutableVarChunk *pVar   );

    void clear       (      void                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ShaderCache(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ShaderCache(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#ifdef OSG_SHC_USE_REF
    ShaderStore    _vShaderStore;
    ShaderVarStore _vShaderVarStore;
#endif

    ShaderExeTree  _oExeTree;
    ShaderVarTree  _oVarTree;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    void updateRemoveCallback  (ShaderExecutableChunk    *pShader   );
    void clearShRemoveCallback (ShaderExecutableChunk    *pShader   );

    void updateRemoveCallback  (ShaderExecutableVarChunk *pVar      );
    void clearVaRemoveCallback (ShaderExecutableVarChunk *pVar      );

    void removeShaderProgram   (FieldContainer           *pContainer, 
                                ConstFieldMaskArg         whichField);

    void removeShaderVar       (FieldContainer           *pContainer, 
                                ConstFieldMaskArg         whichField);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    ShaderCache(const ShaderCache &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const ShaderCache &source);
};

OSG_END_NAMESPACE

#include "OSGShaderCache.inl"

#endif /* _OSGSHADERCACHE_H_ */
