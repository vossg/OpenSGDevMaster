
#ifndef _OSGDEFAULTFIELDCONFIGS_H_
#define _OSGDEFAULTFIELDCONFIGS_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContainerForwards.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGDefaultFieldConfigs.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/
/* PointerFieldConfigBase<ObjectTypeT>                                       */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
struct PointerFieldConfigBase
{
    /*---------------------------------------------------------------------*/
    /*! \name Template Arguments                                           */
    /*! \{                                                                 */

    typedef ObjectTypeT              ObjectType;
    
    typedef PointerFieldConfigBase   Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Pointer Types                                                */
    /*! \{                                                                 */

    OSG_GEN_NAMED_PTR(ObjectType, Object);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Types                                            */
    /*! \{                                                                 */
    
    typedef ObjectPtr                ValueType;
    typedef ObjectPtrConst           ConstValueType;
    
    typedef ObjectPtrConst           ArgumentType;
    
    typedef ObjectPtr      *         PtrType;
    typedef ObjectPtrConst *         ConstPtrType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

/*---------------------------------------------------------------------------*/
/* ChildMFieldConfig<ObjectTypeT,                                            */
/*                   NamespaceI  >                                           */
/*---------------------------------------------------------------------------*/

// forward declarations
template <class ObjectTypeT>
class ChildMFieldIterator;

template <class ObjectTypeT>
class ChildMFieldConstIterator;

template <class ObjectTypeT>
class ChildMFieldReferenceProxy;

template <class ObjectTypeT>
class ChildSFieldReferenceProxy;


template <class ObjectTypeT, Int32 NamespaceI = 0>
struct ChildFieldConfig 
    : public PointerFieldConfigBase<ObjectTypeT>
{
    /*---------------------------------------------------------------------*/
    /*! \name Template Arguments                                           */
    /*! \{                                                                 */
    
    typedef ObjectTypeT                             ObjectType;
        
    typedef ChildFieldConfig                        Self;
    typedef PointerFieldConfigBase<ObjectTypeT>     Inherited;
                                                     
    OSG_INHERIT_NAMED_PTR_TMPL(Inherited, Object);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Types                                            */
    /*! \{                                                                 */
    
    typedef ChildMFieldReferenceProxy<ObjectType>   MFieldRefType;
    typedef ChildSFieldReferenceProxy<ObjectType>   SFieldRefType;
    typedef ObjectPtrConst &                        MFieldConstRefType;
    typedef ObjectPtrConst &                        SFieldConstRefType;
    
    typedef ChildMFieldIterator     <ObjectType >   ItType;
    typedef ChildMFieldConstIterator<ObjectType >   ConstItType;
    typedef std::reverse_iterator   <ItType     >   ReverseItType;
    typedef std::reverse_iterator   <ConstItType>   ConstReverseItType;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static UInt32           const Namespace  = NamespaceI;
    static FieldType::Class const fieldClass = FieldType::CHILD_POINTER_FIELD;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

/*---------------------------------------------------------------------------*/
/* ParentMFieldConfig<ObjectTypeT,                                           */
/*                    NamespaceI  >                                          */
/*---------------------------------------------------------------------------*/

// forward declarations
template <class ObjectTypeT>
class ParentMFieldConstIterator;

template <class ObjectTypeT>
class ParentMFieldConstReferenceProxy;

template <class ObjectTypeT>
class ParentSFieldConstReferenceProxy;


template <class ObjectTypeT, Int32 NamespaceI = 0>
struct ParentFieldConfig
    : public PointerFieldConfigBase<ObjectTypeT>
{
    /*---------------------------------------------------------------------*/
    /*! \name Template Arguments                                           */
    /*! \{                                                                 */
    
    typedef ObjectTypeT                                  ObjectType;
    
    typedef ParentFieldConfig                            Self;
    typedef PointerFieldConfigBase<ObjectTypeT>          Inherited;
    
    OSG_INHERIT_NAMED_PTR_TMPL(Inherited, Object);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Types                                            */
    /*! \{                                                                 */
    
    typedef ParentMFieldConstReferenceProxy<ObjectType>  MFieldConstRefType;
    typedef ParentSFieldConstReferenceProxy<ObjectType>  SFieldConstRefType;
    
    typedef ParentMFieldConstIterator      <ObjectType>  ConstItType;
    typedef std::reverse_iterator          <ConstItType> ConstReverseItType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static UInt32           const Namespace  = NamespaceI;
    static FieldType::Class const fieldClass = FieldType::PARENT_POINTER_FIELD;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

/*---------------------------------------------------------------------------*/
/* UnrecordedMFieldConfig<ObjectTypeT,                                       */
/*                        NamespaceI  >                                      */
/*---------------------------------------------------------------------------*/

// forward declarations
template <class ObjectTypeT>
class UnrecordedMFieldIterator;

template <class ObjectTypeT>
class UnrecordedMFieldConstIterator;

template <class ObjectTypeT>
class UnrecordedMFieldReferenceProxy;

template <class ObjectTypeT>
class UnrecordedSFieldReferenceProxy;


template <class ObjectTypeT, Int32 NamespaceI = 0>
struct UnrecordedFieldConfig 
    : public PointerFieldConfigBase<ObjectTypeT>
{
    /*---------------------------------------------------------------------*/
    /*! \name Template Arguments                                           */
    /*! \{                                                                 */
    
    typedef ObjectTypeT                                  ObjectType;
        
    typedef UnrecordedFieldConfig                        Self;
    typedef PointerFieldConfigBase<ObjectTypeT>          Inherited;
    
    OSG_INHERIT_NAMED_PTR_TMPL(Inherited, Object);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Types                                            */
    /*! \{                                                                 */
    
    typedef UnrecordedMFieldReferenceProxy<ObjectType>   MFieldRefType;
    typedef UnrecordedSFieldReferenceProxy<ObjectType>   SFieldRefType;
    typedef ObjectPtrConst &                             MFieldConstRefType;
    typedef ObjectPtrConst &                             SFieldConstRefType;
    
    typedef UnrecordedMFieldIterator     <ObjectType >   ItType;
    typedef UnrecordedMFieldConstIterator<ObjectType >   ConstItType;
    typedef std::reverse_iterator        <ItType     >   ReverseItType;
    typedef std::reverse_iterator        <ConstItType>   ConstReverseItType;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static UInt32           const Namespace  = NamespaceI;
    static FieldType::Class const fieldClass = FieldType::UNRECORDED_POINTER_FIELD;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

/*---------------------------------------------------------------------------*/
/* WeakMFieldConfig<ObjectTypeT,                                             */
/*                  NamespaceI  >                                            */
/*---------------------------------------------------------------------------*/

// forward declarations
template <class ObjectTypeT>
class WeakMFieldIterator;

template <class ObjectTypeT>
class WeakMFieldConstIterator;

template <class ObjectTypeT>
class WeakMFieldReferenceProxy;

template <class ObjectTypeT>
class WeakSFieldReferenceProxy;


template <class ObjectTypeT, Int32 NamespaceI = 0>
struct WeakFieldConfig 
    : public PointerFieldConfigBase<ObjectTypeT>
{
    /*---------------------------------------------------------------------*/
    /*! \name Template Arguments                                           */
    /*! \{                                                                 */
    
    typedef ObjectTypeT                            ObjectType;
        
    typedef WeakFieldConfig                        Self;
    typedef PointerFieldConfigBase<ObjectTypeT>    Inherited;
    
    OSG_INHERIT_NAMED_PTR_TMPL(Inherited, Object);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Types                                            */
    /*! \{                                                                 */
    
    typedef WeakMFieldReferenceProxy<ObjectType>   MFieldRefType;
    typedef WeakSFieldReferenceProxy<ObjectType>   SFieldRefType;
    typedef ObjectPtrConst &                       MFieldConstRefType;
    typedef ObjectPtrConst &                       SFieldConstRefType;
    
    typedef WeakMFieldIterator     <ObjectType >   ItType;
    typedef WeakMFieldConstIterator<ObjectType >   ConstItType;
    typedef std::reverse_iterator  <ItType     >   ReverseItType;
    typedef std::reverse_iterator  <ConstItType>   ConstReverseItType;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static UInt32           const Namespace  = NamespaceI;
    static FieldType::Class const fieldClass = FieldType::WEAK_POINTER_FIELD;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

#endif // _OSGDEFAULTFIELDCONFIGS_H_
