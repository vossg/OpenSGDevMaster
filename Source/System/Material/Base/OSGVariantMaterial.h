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


#ifndef _OSGVARIANTMATERIAL_H_
#define _OSGVARIANTMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPrimeMaterial.h"
#include "OSGVariantMaterialBase.h"
#include "OSGMapCacheHandlerMixin.h"

OSG_BEGIN_NAMESPACE

class VariantMaterial;

/*! \ingroup GrpSystemMaterialBase
    \nohierarchy
*/

struct VarMatMapCache
{
    typedef VariantMaterialBase                   ParentT;
    typedef VariantMaterial                       FinalContainer;

    typedef SFMaterialPtrMap                      MapCacheField;
    typedef MapCacheField::StoredType             MapCache;
    typedef SFMaterialPtrMap::EditHandle::KeyPool MapKeyPool;

    typedef MapCache::mapped_type                 MapCacheElement;
    typedef MapCache::key_type                    MapCacheKey;

    typedef PrimeMaterial                         FinalizedElement;

    static void setFallback(ParentT *pContainer, MapCacheElement pElem)
    {
        pContainer->setFallbackMaterial(pElem);
    }
                     
    static MapCacheElement getFallback(ParentT *pContainer)
    {
        return pContainer->getFallbackMaterial();
    }

    static const Char8 *getFieldName(void)
    {
        return "materialStore";
    }
};

/*! \brief Material using variant set.  See \ref 
    PageSystemMaterialVariantMaterial for a description.
    \ingroup GrpSystemMaterialBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING VariantMaterial : 
    public MapCacheHandlerMixin<VarMatMapCache>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MapCacheHandlerMixin<VarMatMapCache> Inherited;
    typedef VariantMaterial                      Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual PrimeMaterial *finalize(MapCacheKey  oKey,
                                    Window      *pWin);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void             addMaterial(PrimeMaterial  * const materialP,
                                 MaterialMapKey         key    = 0);

    void             subMaterial(MaterialMapKey         key    = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    PrimeMaterial *findMaterial(MaterialMapKey key) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual bool isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    const SFMaterialPtrMap *getSFMaterialStore(void) const;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Find                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Find                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Find                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Find                                    */
    /*! \{                                                                 */

#if 0
    virtual bool operator == (const VariantMaterial &other) const;
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SFMaterialPtrMap::StoredType          MaterialPtrMap;
    typedef MaterialPtrMap  ::iterator            MaterialPtrMapIt;
    typedef MaterialPtrMap  ::const_iterator      MaterialPtrMapConstIt;

    typedef SFMaterialPtrMap::EditHandle::KeyPool MapKeyPool;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static void classDescInserter(TypeObject &oType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VariantMaterial(void);
    VariantMaterial(const VariantMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VariantMaterial(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VariantMaterialBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VariantMaterial &source);
};

typedef VariantMaterial              *VariantMaterialP;

OSG_END_NAMESPACE

#include "OSGVariantMaterialBase.inl"
#include "OSGVariantMaterial.inl"

#endif /* _OSGVARIANTMATERIAL_H_ */
