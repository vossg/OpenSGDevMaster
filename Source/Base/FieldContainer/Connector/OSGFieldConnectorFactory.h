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

#ifndef _OSGFIELDCONNECTORFACTORY_H_
#define _OSGFIELDCONNECTORFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGFactoryBase.h"
#include "OSGSingletonHolder.h"
//#include "OSGFieldDescriptionBase.h"

#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

class Field;
class FieldType;
class BasicFieldConnector;

/*! \ingroup GrpBaseField
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING FieldConnectorFactoryBase : public FactoryBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    BasicFieldConnector *createConnector(
        const FieldDescriptionBase *pSrcDesc,
        const Field                *pSrc,
        const FieldDescriptionBase *pDstDesc,
              Field                *pDst        ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    void registerConnector(const FieldType           &oSrcType,
                           const FieldType           &oDstType,
                                 BasicFieldConnector *pSrcToDst,
                                 BasicFieldConnector *pDstToSrc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      The                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef FactoryBase Inherited;

    typedef std::map<UInt32, 
                     BasicFieldConnector *>                 ConnectorMap;
    typedef std::map<UInt32, 
                     BasicFieldConnector *>::iterator       ConnectorMapIt;
    typedef std::map<UInt32, 
                     BasicFieldConnector *>::const_iterator ConnectorMapConstIt;

    typedef std::map<UInt32, 
                     ConnectorMap        *>                 EntryMap;
    typedef std::map<UInt32, 
                     ConnectorMap        *>::iterator       EntryMapIt;
    typedef std::map<UInt32, 
                     ConnectorMap        *>::const_iterator EntryMapConstIt;

    EntryMap mConnectorMap;

    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldConnectorFactoryBase(void);
    virtual ~FieldConnectorFactoryBase(void);

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
    FieldConnectorFactoryBase(const FieldConnectorFactoryBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldConnectorFactoryBase &source);
};

#if defined(WIN32)
OSG_BASE_EXPIMP_TMPL
template class OSG_BASE_DLLMAPPING SingletonHolder<FieldConnectorFactoryBase>;
#endif

/*! \typedef OSG::SingletonHolder<OSG::FieldConnectorFactoryBase> FieldConnectorFactory;
    \ingroup GrpBaseField
    \relatesalso OSG::FieldConnectorFactoryBase
 */

typedef OSG::SingletonHolder<OSG::FieldConnectorFactoryBase> FieldConnectorFactory;

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONNECTORFACTORY_H_ */


