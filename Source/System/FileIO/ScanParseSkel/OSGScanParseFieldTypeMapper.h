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

#ifndef _OSGSCANPARSEFIELDTYPEMAPPER_H_
#define _OSGSCANPARSEFIELDTYPEMAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include <map>

OSG_BEGIN_NAMESPACE

//! FieldTypeMapper, provides functions to map from system to scanner types  
//! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib 

template <class BaseT>
class ScanParseFieldTypeMapper : public BaseT 
{
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef          BaseT                       Inherited;

    typedef typename Inherited::BuildInFieldType BuildInFieldTypes;

    typedef          std::map<BuildInFieldTypes, 
                              UInt32           > IntExtMap;
    typedef          std::map<UInt32,        
                              BuildInFieldTypes> ExtIntMap;

    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ScanParseFieldTypeMapper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ScanParseFieldTypeMapper(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setExtIntMapping(BuildInFieldTypes eBuildInType, 
                          UInt32            uiMappedType);

    void setIntExtMapping(UInt32            uiMappedType, 
                          BuildInFieldTypes eBuildInType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Map                                     */
    /*! \{                                                                 */

    virtual Int32 mapExtIntFieldType(const Char8 *szFieldname,
                                     const Int32  iFieldTypeId);

    virtual Int32 mapIntExtFieldType(const Char8 *szFieldname,
                                     const Int32  iFieldTypeId);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    IntExtMap _mIntExt;
    ExtIntMap _mExtInt;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ScanParseFieldTypeMapper(const ScanParseFieldTypeMapper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ScanParseFieldTypeMapper &source);
};

OSG_END_NAMESPACE

#include "OSGScanParseFieldTypeMapper.inl"

#define OSGSCANPARSEFIELDTYPEMAPPER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSCANPARSEFIELDTYPEMAPPER_H_ */
