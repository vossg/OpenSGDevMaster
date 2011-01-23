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

#ifndef _OSGFIELDDESCFACTORY_H_
#define _OSGFIELDDESCFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGFactoryBase.h"
#include "OSGSingletonHolder.h"
#include "OSGFieldDescriptionBase.h"

#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

class Field;
class FieldType;

/*! \ingroup GrpBaseField
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING FieldDescFactoryBase : public FactoryBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 AutoFlags = 0xFF000000;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    Field *createField(      UInt32  typeId);
    Field *createField(const Char8  *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32     getNumFieldTypes  (void                );
    
    static FieldType *getFieldType      (      UInt32  typeId);
    static FieldType *getFieldType      (const Char8  *szName);

    const  Char8     *getFieldTypeName  (UInt32 typeId       );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      The                                     */
    /*! \{                                                                 */

    FieldDescriptionBase *
        createByName   (const Char8               *szFieldTypename, 
                        const Char8               *szFieldname,
                              FieldEditMethod      fEditMethod,
                              FieldGetMethod       fGetMethod,
                              UInt32               uiFieldFlags = AutoFlags);

    FieldDescriptionBase *
        createByNameIdx(const Char8               *szFieldTypename, 
                        const Char8               *szFieldname,
                              FieldIndexEditMethod fEditMethod,
                              FieldIndexGetMethod  fGetMethod,
                              UInt32               uiFieldFlags = AutoFlags);


    FieldDescriptionBase *
        create   (      UInt32               uiFieldTypeId, 
                  const Char8               *szFieldname,
                        FieldEditMethod      fEditMethod,
                        FieldGetMethod       fGetMethod,
                        UInt32               uiFieldFlags = AutoFlags);

    FieldDescriptionBase *
        createIdx(      UInt32               uiFieldTypeId, 
                  const Char8               *szFieldname,
                        FieldIndexEditMethod fEditMethod,
                        FieldIndexGetMethod  fGetMethod,
                        UInt32               uiFieldFlags = AutoFlags);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef FactoryBase Inherited;


    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

    typedef std::pair<FieldDescCreator, 
                      IndexedFieldDescCreator>            DescCreators;
    typedef std::map <std::string, 
                      DescCreators      >                 NameCreatorMap;
    typedef std::map <std::string, 
                      DescCreators      >::iterator       NameCreatorMapIt;
    typedef std::map <std::string, 
                      DescCreators      >::const_iterator NameCreatorMapConstIt;

    typedef std::vector<DescCreators    >                 CreatorStore;

    NameCreatorMap _mNameCreatorMap;
    CreatorStore   _vCreators;

    void registerDescription(const Char8                   *szFieldTypename,
                                   UInt32                   uiTypeId,
                                   FieldDescCreator         fCreator,
                                   IndexedFieldDescCreator  fIdxCreator    );

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldDescFactoryBase(void);
    virtual ~FieldDescFactoryBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

    virtual bool initialize                          (void);
    virtual bool terminate                           (void);

    virtual bool initializePendingElements           (void);

    virtual bool initializeFactoryPost               (void);
    virtual bool initializePendingElementsFactoryPost(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template <class SingletonT>
    friend class SingletonHolder;


    friend class FieldType;
    friend class Field;

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldDescFactoryBase(const FieldDescFactoryBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldDescFactoryBase &source);
};

/*! \typedef OSG::SingletonHolder<OSG::FieldDescFactoryBase> FieldDescFactory;
    \ingroup GrpBaseField
    \relatesalso OSG::FieldDescFactoryBase
 */

typedef OSG::SingletonHolder<OSG::FieldDescFactoryBase> FieldDescFactory;

OSG_END_NAMESPACE

#endif /* _OSGFIELDDESCFACTORY_H_ */


