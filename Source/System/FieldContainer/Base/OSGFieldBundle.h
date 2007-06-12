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

#ifndef _OSGFIELDBUNDLE_H_
#define _OSGFIELDBUNDLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGReflexiveContainer.h"
#include "OSGFieldBundleType.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

class FieldBundle : public ReflexiveContainer
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ReflexiveContainer Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                    Type definitions                          */
    /*! \{                                                                 */
    
    typedef FieldBundleType                                TypeObject;

    OSG_GEN_INTERNALPTR(FieldBundle);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Get Class Type Information                       */
    /*! \{                                                                 */

    static OSG_SYSTEM_DLLMAPPING TypeObject &getClassType   (void); 
    static OSG_SYSTEM_DLLMAPPING UInt32      getClassTypeId (void);
    static OSG_SYSTEM_DLLMAPPING UInt16      getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual       TypeObject &getType(void);
    
    OSG_SYSTEM_DLLMAPPING
    virtual const TypeObject &getType(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void editSField(ConstFieldMaskArg whichField);

    template<class FieldT>
    void editMField(ConstFieldMaskArg whichField,
                    FieldT            &oField   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual ObjPtr shallowCopy(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    void  addReference(void);

    OSG_SYSTEM_DLLMAPPING
    void  subReference(void);

    OSG_SYSTEM_DLLMAPPING
    Int32 getRefCount (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING
    virtual void pushToField     (      FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void insertIntoMField(const UInt32               uiIndex,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void replaceInMField (const UInt32               uiIndex,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void replaceInMField (      FieldBundlePConstArg pOldElement,
                                        FieldBundlePConstArg pNewElement,
                                  const UInt32               uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void removeFromMField(const UInt32               uiIndex,
                                  const UInt32               uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void removeFromMField(      FieldBundlePConstArg pElement,
                                  const UInt32               uiFieldId  );

    OSG_SYSTEM_DLLMAPPING
    virtual void clearField      (const UInt32               uiFieldId  );

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

    static TypeObject _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    Int32 _iRefCount;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    FieldBundle(void);

    OSG_SYSTEM_DLLMAPPING 
    FieldBundle(const FieldBundle &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    virtual ~FieldBundle(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjPtr &result, 
                              const          ObjectT         *prototypeP);

    template <class ObjectT>
    static void newPtr       (      typename ObjectT::ObjPtr &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    template <class ObjectT>
    static typename ObjectT::     ObjPtr constructPtr(      ObjectT *pObj);

    template <class ObjectT>
    static typename ObjectT::ObjConstPtr constructPtr(const ObjectT *pObj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING       
    virtual bool deregister(UInt32 uiBundleId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */
    
    OSG_SYSTEM_DLLMAPPING
    virtual void registerChangedContainerV(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldBundle &source);
};

OSG_END_NAMESPACE

#include "OSGFieldBundle.inl"
#include "OSGContainerPtrFuncs.h"

#endif /* _OSGFIELDBUNDLE_H_ */
