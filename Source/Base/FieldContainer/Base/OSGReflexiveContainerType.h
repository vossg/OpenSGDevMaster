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

#ifndef _OSGREFLEXIVECONTAINERTYPE_H_
#define _OSGREFLEXIVECONTAINERTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDataType.h"
#include "OSGContainerForwards.h"

#include <vector>
#include<map>

OSG_BEGIN_NAMESPACE

class ReflexiveContainerType;

/*! \ingroup GrpBaseFieldContainerBase
 */

typedef void (*InitalInsertDescFunc)(OSG::ReflexiveContainerType &);

/*! \class ReflexiveContainerType
    \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING ReflexiveContainerType : public DataType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Constants                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ReflexiveContainerType(const Char8                *szName,
                           const Char8                *szParentName   = NULL,
                           const Char8                *szGroupName    = NULL,
                           const UInt32                uiNameSpace    =    0,
                                 InitalInsertDescFunc  descInsertFunc = NULL,
                                 bool                  bDescsAddable  = false,
                                 BitVector             bvUnmarkedOnCreate = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ReflexiveContainerType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    UInt16 getGroupId(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    FieldDescriptionBase *getFieldDesc    (      UInt32  uiFieldId  );
    FieldDescriptionBase *getFieldDesc    (      UInt32  uiFieldId  ) const;

    FieldDescriptionBase *getFieldDesc    (const Char8  *szFieldName);
    FieldDescriptionBase *getFieldDesc    (const Char8  *szFieldName) const;

    UInt32                getNumFieldDescs(      void               ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    BitVector getUnmarkedOnCreate        (      void                  ) const;
    void      setFieldsUnmarkedOnCreate  (const BitVector bvFieldMasks);
    void      clearFieldsUnmarkedOnCreate(const BitVector bvFieldMasks);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    void addInitialDesc(FieldDescriptionBase *pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    UInt32 addDescription(const FieldDescriptionBase &desc     );
    bool   subDescription(      UInt32                uiFieldId);

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

    void dumpFieldInfo(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    typedef std::map   <std::string, FieldDescriptionBase *> DescMap;
    typedef std::vector<             FieldDescriptionBase *> DescVec;

    typedef DescMap::iterator                                DescMapIt;
    typedef DescMap::const_iterator                          DescMapConstIt;

    typedef DescVec::iterator                                DescVecIt;
    typedef DescVec::const_iterator                          DescVecConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    ReflexiveContainerType(const ReflexiveContainerType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt16               _uiGroupId;

    bool                 _bDescsAddable;
    std::string          _szGroupName;

    DescVec              _vInitialDescs;

	DescMap              _mDescMap;
    DescVec              _vDescVec;

    InitalInsertDescFunc _descInsertFunc;

    BitVector            _bvUnmarkedOnCreate;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

            bool initFields      (void);
            bool initParentFields(void);


	virtual bool initialize      (void);
    virtual void terminate       (void);

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

    typedef DataType Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ReflexiveContainerType &source);
};

OSG_END_NAMESPACE

#include "OSGReflexiveContainerType.inl"

#endif /* _OSGREFLEXIVECONTAINERTYPE_H_ */
