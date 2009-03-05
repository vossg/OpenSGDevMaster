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

OSG_BEGIN_NAMESPACE

/*! \brief Material using variant set.  See \ref 
    PageSystemMaterialVariantMaterial for a description.
*/

class OSG_SYSTEM_DLLMAPPING VariantMaterial : public VariantMaterialBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef VariantMaterialBase Inherited;
    typedef VariantMaterial     Self;

    OSG_RC_FIRST_FIELD_DECL(MaterialStore);
    OSG_RC_LAST_FIELD_DECL (MaterialStore);

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

    virtual UInt32 getBinSize (ConstFieldMaskArg   whichField);
    virtual void   copyToBin  (BinaryDataHandler  &pMem,
                               ConstFieldMaskArg   whichField);
    virtual void   copyFromBin(BinaryDataHandler  &pMem,
                               ConstFieldMaskArg   whichField);

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

    virtual PrimeMaterial *finalize(MaterialMapKey oKey);

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

    SFMaterialPtrMap _sfMaterialStore;

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

#ifdef OSG_MT_CPTR_ASPECT
    void execSync  (      VariantMaterial   *pFrom,
                          ConstFieldMaskArg  whichField,
                          AspectOffsetStore &oOffsets,
                          ConstFieldMaskArg  syncMode  ,
                    const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    EditFieldHandlePtr editHandleMaterialStore(void);
    GetFieldHandlePtr  getHandleMaterialStore (void) const;

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
