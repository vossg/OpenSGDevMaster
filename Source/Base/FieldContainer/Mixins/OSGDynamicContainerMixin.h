/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGDYNAMICCONTAINERMIXIN_H_
#define _OSGDYNAMICCONTAINERMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseDef.h"

#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"
#include "OSGContainerDefines.h"
#include "OSGDynFieldContainerInterface.h"
#include "OSGConceptPropertyChecks.h"

#include "boost/bind.hpp"

#define OSG_FIELD_CONTAINER_ABSTR_TMPL_DECL                                   \
    OSG_RC_TYPE_FUNCTIONS_DECL;                                               \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_FIELD_CONTAINER_ABSTR_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)     \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_CLASS, OSG_TMPL_PARAM)

#define OSG_FIELD_CONTAINER_ABSTR_TMPL_NO_TYPE_DEF(OSG_CLASS, OSG_TMPL_PARAM) \
        OSG_FIELD_CONTAINER_ABSTR_INL_TMPL_DEF(OSG_CLASS, OSG_TMPL_PARAM)

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFieldContainerMixins
    \ingroup GrpLibOSGBase
 */

template <class ParentT>
class DynFieldContainer : public ParentT,
                          public DynFieldContainerInterface 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename ParentT::Desc                      Desc;
    typedef          ParentT                            Inherited;
    typedef          DynFieldContainerInterface         Interface;

    typedef typename Desc::ParentT                      ParentContainer;

    typedef          DynFieldContainer<ParentT>         Self;

    OSG_GEN_INTERNALPTR(Self);

    typedef typename Inherited::TypeObject              TypeObject;
    typedef typename TypeObject::InitPhase              InitPhase;

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_ABSTR_TMPL_DECL;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Dynamic Field Access                            */
    /*! \{                                                                 */

            UInt32 addField(const FieldDescriptionBase &fieldDesc    );
    virtual UInt32 addField(const UInt32                uiFieldTypeId,
                            const Char8                *szFieldName  );

    virtual UInt32 addField(const Char8                *szFieldType,
                            const Char8                *szFieldName  );
            void   subField(      UInt32                fieldId      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Dynamic Field Access                            */
    /*! \{                                                                 */

    GetFieldHandlePtr  getDynamicField      (       UInt32  index ) const;
    EditFieldHandlePtr editDynamicField     (       UInt32  index );

    GetFieldHandlePtr  getDynamicFieldByName (const Char8  *szName) const;
    EditFieldHandlePtr editDynamicFieldByName(const Char8  *szName);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Clone                                   */
    /*! \{                                                                 */

#if 0
    FieldContainer *emptyCopy(void);
    FieldContainer *clone    (void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    TypeObject           _localType;

    UInt32               _uiDescStartIdx;
    std::vector<Field *> _dynFieldsV;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DynFieldContainer(      void                     );
    DynFieldContainer(const DynFieldContainer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynFieldContainer(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

#if 0
#ifdef OSG_MT_CPTR_ASPECT
    virtual 
    FieldContainer* createAspectCopy(const FieldContainer *pRefAspect) const;
#endif
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer     &oFrom,
                                 ConstFieldMaskArg   whichField,
                                 AspectOffsetStore  &oOffsets,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo);

            void execSync (      DynFieldContainer  *pFrom,
                                 ConstFieldMaskArg   whichField,
                                 AspectOffsetStore  &oOffsets,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    virtual       TypeObject &getFinalType(void)       = 0;
    virtual const TypeObject &getFinalType(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

//    static void initMethod(InitPhase ePhase);
//    static void exitMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
 
  private:

    friend class FieldContainer;
    
    /*!\brief prohibit default functions (move to 'public' if needed) */
    void operator =(const DynFieldContainer &source);

    void addPointerValue(FieldContainer *pVal, UInt32 uiFieldId);
    void setPointerValue(FieldContainer *pVal, UInt32 uiFieldId);
};

OSG_END_NAMESPACE

#define OSG_DYNFIELDCONTAINER_INST(DESC)                                      \
template <>                                                                   \
DynFieldContainer< DESC >::TypeObject                                         \
    DynFieldContainer< DESC >::_type(                                         \
        Desc::getTypeName      (),                                            \
        Desc::getParentTypeName(),                                            \
        Desc::getGroupName     (),                                            \
        0,                                                                    \
        NULL,                                                                 \
        NULL,                                                                 \
        NULL,                                                                 \
        NULL,                                                                 \
        true,                                                                 \
        0);                                                                   \
                                                                              \
template<> OSG_DLL_EXPORT                                                     \
DynFieldContainer< DESC >::TypeObject &                                       \
    DynFieldContainer< DESC >::getClassType(void)                             \
{                                                                             \
    return Self::_type;                                                       \
}

#include "OSGDynamicContainerMixin.inl"

#endif /* _OSGDYNAMICCONTAINERMIXIN_H_ */
