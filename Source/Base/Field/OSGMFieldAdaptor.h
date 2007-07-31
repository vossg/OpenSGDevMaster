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

#ifndef _OSGMFIELDADAPTOR_H_
#define _OSGMFIELDADAPTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseField
 */

template<class ValueT, class ParentT, Int32 iNamespace = 0>
class MFieldAdaptor : public ParentT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          MFieldAdaptor<ValueT, 
                                   ParentT,
                                   iNamespace>          Self;

    typedef          MFieldVector <ValueT    >          StorageType;

    typedef typename StorageType::reference             reference;
    typedef typename StorageType::const_reference       const_reference;

    typedef typename StorageType::iterator              iterator;
    typedef typename StorageType::const_iterator        const_iterator;

    typedef typename 
                    StorageType::reverse_iterator       reverse_iterator;
    typedef typename 
                    StorageType::const_reverse_iterator const_reverse_iterator;


    typedef          FieldTraits      <ValueT, 
                                       iNamespace>      MFieldTraits;

    typedef typename MFieldTraits::ArgumentType         ArgumentType;
    typedef typename MFieldTraits::ParentContainerPtr   ParentContainerPtr;

    typedef typename
    boost::mpl::if_<boost::mpl::bool_<MFieldTraits::bIsPointerField>,
                    EditFCPtrMFieldHandle<Self>,
                    EditMFieldHandle     <Self>  >::type  EditHandle;

    typedef boost::shared_ptr<EditHandle> EditHandlePtr;

    typedef typename
    boost::mpl::if_<boost::mpl::bool_<MFieldTraits::bIsPointerField>,
                    GetFCPtrMFieldHandle<Self> ,
                    GetMFieldHandle     <Self> >::type  GetHandle;

    typedef boost::shared_ptr<GetHandle> GetHandlePtr;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static const FieldType &getClassType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    MFieldAdaptor(void);
    MFieldAdaptor(const MFieldAdaptor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~MFieldAdaptor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Index Operator                              */
    /*! \{                                                                 */

          reference operator [](UInt32 index);
    const_reference operator [](UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    iterator               begin    (void                              );
    iterator               end      (void                              );

    reverse_iterator       rbegin   (void                              );
    reverse_iterator       rend     (void                              );

    
    const_iterator         begin    (void                              ) const;
    const_iterator         end      (void                              ) const;
    
    const_reverse_iterator rbegin   (void                              ) const;
    const_reverse_iterator rend     (void                              ) const;

    reference              front    (void                              );
    const_reference        front    (void                              ) const;
    
    reference              back     (void                              );
    const_reference        back     (void                              ) const;

    iterator               insert   (iterator     pos, 
                                     ArgumentType value                );
    iterator               erase    (iterator     pos                  );
    
    iterator               find     (ArgumentType value                );
    const_iterator         find     (ArgumentType value                ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          StorageType &getValues(void);
    const StorageType &getValues(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

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

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static FieldType _fieldType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

    template<class To>
          To &dcast(void);

    template<class To>
    const To &dcast(void) const;

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

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
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_HELPER_FCT)
    const FieldType &fieldTypeExportHelper(void);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ParentT Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MFieldAdaptor &source);
};

OSG_END_NAMESPACE

#include "OSGMFieldAdaptor.inl"

#endif /* _OSGMFIELDADAPTOR_H_ */
