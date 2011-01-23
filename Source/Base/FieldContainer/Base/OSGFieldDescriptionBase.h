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

#ifndef _OSGFIELDDESCRIPTIONBASE_H_
#define _OSGFIELDDESCRIPTIONBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/function.hpp>
#include <boost/functional.hpp>

#include "OSGBaseTypes.h"
#include "OSGFieldType.h"
#include "OSGContainerForwards.h"
#include "OSGField.h"
#include "OSGFieldConnector.h"

OSG_BEGIN_NAMESPACE

class Field;

template <class AttachmentDescT>
class DynFieldAttachment;

class BasicFieldConnector;

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING FieldDescriptionBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef std::vector<      std::string         > StringVector;
    typedef std::vector<const FieldContainerType *> TypePtrVector;
    typedef std::vector<      UInt16              > TypeIdVector;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldDescriptionBase(const FieldType       &elementType,
                         const Char8           *szName,
                         const std::string      fieldDocumentation,
                         const UInt32           uiFieldId,
                         const BitVector        vFieldMask,
                         const bool             bInternal,
                         const UInt32           uiFieldFlags,
                               FieldEditMethod  fEditMethod,
                               FieldGetMethod   fGetMethod);

    FieldDescriptionBase(const FieldType            &elementType,
                         const Char8                *szName,
                         const std::string           fieldDocumentation,
                         const UInt32                uiFieldId,
                         const BitVector             vFieldMask,
                         const bool                  bInternal,
                         const UInt32                uiFieldFlags,
                               FieldIndexEditMethod  fIndexedEditMethod,
                               FieldIndexGetMethod   fIndexedGetMethod);

    FieldDescriptionBase(const FieldDescriptionBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldDescriptionBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    const Char8       *getCName       (void                        ) const;
          std::string  getName        (void                        ) const;

          std::string  getDocumentation (void                      ) const;

          UInt32       getTypeId      (void                        ) const;

          BitVector    getFieldMask   (void                        ) const;
          void         setFieldMask   (ConstFieldMaskArg vFieldMask);

          UInt32       getFieldId     (void                        ) const;
          void         setFieldId     (UInt32 uiFieldId            );

    const FieldType   &getFieldType   (void                        ) const;

          bool         isInternal     (void                        ) const;

          void         setFlags       (UInt32 uiFlags              );
          UInt32       getFlags       (void                        ) const;

          bool         isValid        (void                        ) const;

          bool         isSField       (void                        ) const;
          bool         isMField       (void                        ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    EditFieldHandlePtr editField(      ReflexiveContainer &oContainer) const;
    GetFieldHandlePtr  getField (const ReflexiveContainer &oContainer) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Set from String                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Set from Field                           */
    /*! \{                                                                 */

    virtual Field *createField(void          ) const = 0;
    virtual void   destroyField(Field *pField) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    virtual FieldDescriptionBase *clone(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    virtual 
        GetFieldHandlePtr  createGetHandler (const Field          *pField,
                                                   FieldContainer *pCnt  ) = 0;
    virtual 
        EditFieldHandlePtr createEditHandler(      Field          *pField,
                                                   FieldContainer *pCnt  ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    virtual BasicFieldConnector *createConnector(
        const Field                *pSrc,
        const FieldDescriptionBase *pDstDesc,
              Field                *pDst        ) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    template <class AttachmentDescT>
    friend class DynFieldAttachment;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

          std::string           _szName;
          std::string           _documentation; 

    const FieldType            &_fieldType;

          UInt32                _uiFieldId;
          BitVector             _vFieldMask;

          bool                  _bInternal;
          UInt32                _uiFieldFlags;

          FieldEditMethod       _fEditMethod;
          FieldGetMethod        _fGetMethod;
          FieldIndexEditMethod  _fIndexedEditMethod;
          FieldIndexGetMethod   _fIndexedGetMethod;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual void beginEdit(Field              *pField,
                           UInt32              uiAspect,
                           AspectOffsetStore  &oOffsets) = 0;

    virtual bool isShared (Field              *pField  ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldDescriptionBase &source);
};

//---------------------------------------------------------------------------
//   Class
//---------------------------------------------------------------------------

/*! FieldDescriptionBase point less than
    \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct FieldDescriptionBasePLT
{
    bool operator()(const FieldDescriptionBase *pElemDesc1,
                    const FieldDescriptionBase *pElemDesc2) const;
};


//---------------------------------------------------------------------------
//   Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */

template<class    DescT, 
         enum     FieldType::Cardinality eFieldCard, 
         typename RefCountPolicy                     = NoRefCounts, 
         enum     FieldType::Class       eFieldClass = FieldType::ValueField>
class FieldDescription : public FieldDescriptionBase
{
  protected:

    typedef          FieldDescription<DescT,
                                      eFieldCard,
                                      RefCountPolicy,
                                      eFieldClass> Self;


    typedef FieldDescriptionBase                              Inherited;

    typedef typename
        boost::mpl::if_c<
            eFieldCard == FieldType::SingleField,
            SField<typename DescT::ValueType,
                            DescT::iNamespace>,
            MField<typename DescT::ValueType,
                            DescT::iNamespace,
                   typename DescT::MFAlloc   >    >::type     HandledVField;

    typedef typename
        boost::mpl::if_c<
            eFieldCard == FieldType::SingleField,
            PointerSField<typename DescT::ValueType,
                                   RefCountPolicy,
                                   DescT::iNamespace>,
            PointerMField<typename DescT::ValueType,
                                   RefCountPolicy,
                                   DescT::iNamespace> >::type HandledPField;

    typedef typename
        boost::mpl::if_c<
            eFieldCard == FieldType::SingleField,
            ParentPointerSField<typename DescT::ValueType,
                                         RefCountPolicy,
                                         DescT::iNamespace>,
            ParentPointerMField<typename DescT::ValueType,
                                         RefCountPolicy,
                                         DescT::iNamespace> 
            >::type HandledPPField;

    typedef typename
        boost::mpl::if_c<
            eFieldCard == FieldType::SingleField,
            ChildPointerSField<typename DescT::ValueType,
                                        RefCountPolicy,
                                        DescT::iNamespace>,
            ChildPointerMField<typename DescT::ValueType,
                                        RefCountPolicy,
                                        DescT::iNamespace>
            >::type HandledChField;

    typedef typename
        boost::mpl::if_c<
            eFieldClass == FieldType::ValueField,
            HandledVField,
            HandledPField                           >::type HandledFieldA;

    typedef typename
        boost::mpl::if_c<
            eFieldClass == FieldType::ParentPtrField,
            HandledPPField,
            HandledFieldA                           >::type HandledFieldB;

    typedef typename
        boost::mpl::if_c<
            eFieldClass == FieldType::ChildPtrField,
            HandledChField,
            HandledFieldB                           >::type HandledField;

    typedef typename HandledField::GetHandle    GetHandle;
    typedef typename HandledField::GetHandlePtr GetHandlePtr;

    typedef typename HandledField::EditHandle    EditHandle;
    typedef typename HandledField::EditHandlePtr EditHandlePtr;

    /*! \nohierarchy */
    struct SFieldFunctions
    {
        typedef SFieldConnector<HandledField>     FConnector;

        static void beginEdit(HandledField       *pField,
                              UInt32              uiAspect,
                              AspectOffsetStore  &oOffsets);

        static bool isShared (HandledField       *pField  );
    };

    /*! \nohierarchy */
    struct MFieldFunctions
    {
        typedef MFieldConnector<HandledField>     FConnector;

        static void beginEdit(HandledField       *pField,
                              UInt32              uiAspect,
                              AspectOffsetStore  &oOffsets);

        static bool isShared (HandledField       *pField  );
    };

    /*! \nohierarchy */
    struct DefaultFieldCreateHandler
    {
        static Field *createField(void)
        {
            return new HandledField();
        }

        static BasicFieldConnector   *createConnector(
            const FieldDescriptionBase *pSrcDesc,
            const HandledField         *pSrc,
            const FieldDescriptionBase *pDstDesc,
                  HandledField         *pDst    );    
    };
    
    /*! \nohierarchy */
    struct ChildFieldCreateHandler
    {
        static Field *createField(void)
        {
            return NULL;
        }

        static BasicFieldConnector   *createConnector(
            const FieldDescriptionBase *,
            const Field                *,
            const FieldDescriptionBase *,
                  Field                *)
        {
            return NULL;
        }
    };

    /*! \nohierarchy */
    struct DefaultCreateEditHandler
    {
        static EditFieldHandlePtr createHandler(Field            *pField,
                                                FieldDescription *pDesc,
                                                FieldContainer   *pCnt  )
        {
            HandledField *pTypedField = pDesc->dcast(pField);
            
            EditHandlePtr returnValue(new EditHandle(pTypedField, pDesc, pCnt));
            
            return returnValue;
        }
    };

    /*! \nohierarchy */
    struct ParentCreateEditHandler
    {
        static EditFieldHandlePtr createHandler(Field            *pField,
                                                FieldDescription *pDesc,
                                                FieldContainer   *pCnt  )
        {
            EditFieldHandlePtr returnValue;
            
            return returnValue;
        }
    };

    typedef typename
        boost::mpl::if_c<
            (eFieldClass == FieldType::ChildPtrField ||
             eFieldClass == FieldType::ParentPtrField  ),
            ChildFieldCreateHandler,
            DefaultFieldCreateHandler               >::type FieldCreateHandler;

    typedef typename
        boost::mpl::if_c<
            eFieldClass == FieldType::ParentPtrField,
            ParentCreateEditHandler,
            DefaultCreateEditHandler                >::type CreateEditHandler;

    typedef typename
        boost::mpl::if_c<
            eFieldCard == FieldType::SingleField,
            SFieldFunctions,
            MFieldFunctions                         >::type FieldFunctions;


    virtual void beginEdit(Field              *pField,
                           UInt32              uiAspect,
                           AspectOffsetStore  &oOffsets);

    virtual bool isShared (Field              *pField  );

  public:

    FieldDescription(const FieldType        &elementType,
                     const Char8            *szName,
                     std::string             documentation,
                     const UInt32            uiFieldId,
                     const BitVector         vFieldMask,
                     const bool              bInternal,
                     const UInt32            uiFieldFlags,
                           FieldEditMethod   fEditMethod,
                           FieldGetMethod    fGetMethod   );

    FieldDescription(const FieldType            &elementType,
                     const Char8                *szName,
                           std::string           documentation,
                     const UInt32                uiFieldId,
                     const BitVector             vFieldMask,
                     const bool                  bInternal,
                     const UInt32                uiFieldFlags,
                           FieldIndexEditMethod  fIndexedEditMethod,
                           FieldIndexGetMethod   fIndexedGetMethod );

    FieldDescription(const FieldDescription &source);

    virtual ~FieldDescription(void);

    const   HandledField         *dcast_const (const Field *pField) const;
            HandledField         *dcast       (      Field *pField) const;

    virtual Field                *createField (void         ) const;
    virtual void                  destroyField(Field *pField) const;

    virtual FieldDescriptionBase *clone       (void         ) const;

    virtual 
        GetFieldHandlePtr   createGetHandler (const Field          *pField,
                                                    FieldContainer *pCnt  );
    virtual 
        EditFieldHandlePtr  createEditHandler(      Field          *pField,
                                                    FieldContainer *pCnt  );

    virtual BasicFieldConnector   *createConnector(
        const Field                *pSrc,
        const FieldDescriptionBase *pDstDesc,
              Field                *pDst    ) const;
};

OSG_END_NAMESPACE

#include "OSGFieldDescriptionBase.inl"

#endif /* _OSGFIELDDESCRIPTIONBASE_H_ */
