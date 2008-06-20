/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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

#ifndef _OSGCSMVRMLNODEHELPER_H_
#define _OSGCSMVRMLNODEHELPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContribCSMDef.h"
#include "OSGVRMLNodeHelper.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Group Helper
*/

class OSG_CONTRIBCSM_DLLMAPPING VRMLTimeSensorHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLTimeSensorHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8                * szFieldType,
                                   const UInt32                 uiFieldTypeId,
                                   const Char8                * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual void endNode(FieldContainer *pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLTimeSensorHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelper;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLTimeSensorHelper(const VRMLTimeSensorHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLTimeSensorHelper &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief VRML Group Helper
*/

class OSG_CONTRIBCSM_DLLMAPPING VRMLInterpolatorHelper : public VRMLNodeHelper
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLInterpolatorHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual bool prototypeAddField(const Char8                * szFieldType,
                                   const UInt32                 uiFieldTypeId,
                                   const Char8                * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainer       * pFC,
                                   const Char8                * szFieldname,
                                         FieldContainer       *&pFieldFC,
                                         EditFieldHandlePtr    &pField,
                                   const FieldDescriptionBase *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual void endNode(FieldContainer *pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    static VRMLNodeHelper *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLInterpolatorHelper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    static VRMLNodeHelperFactoryBase::RegisterHelper _regHelperOrientation;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef VRMLNodeHelper Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLInterpolatorHelper(const VRMLInterpolatorHelper &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLInterpolatorHelper &source);
};


OSG_END_NAMESPACE

#endif /* _OSGCSMVRMLNODEHELPER_H_ */
