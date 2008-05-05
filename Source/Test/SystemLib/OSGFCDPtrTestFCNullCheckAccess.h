/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGFCDPTRTESTFCNULLCHECKACCESS_H_
#define _OSGFCDPTRTESTFCNULLCHECKACCESS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFCDPtrTestFCNullCheckAccessBase.h"
#include "OSGFCDTestFC.h"
#include "OSGFCDSParTestFC.h"

OSG_BEGIN_NAMESPACE

/*! \brief FCDPtrTestFCNullCheckAccess class. See \ref
           PageSystemFCDPtrTestFCNullCheckAccess for a description.
*/

class OSG_SYSTEM_DLLMAPPING FCDPtrTestFCNullCheckAccess : public FCDPtrTestFCNullCheckAccessBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FCDPtrTestFCNullCheckAccessBase Inherited;
    typedef FCDPtrTestFCNullCheckAccess     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FCDPtrTestFCNullCheckAccessBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FCDPtrTestFCNullCheckAccess(void);
    FCDPtrTestFCNullCheckAccess(const FCDPtrTestFCNullCheckAccess &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FCDPtrTestFCNullCheckAccess(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FCDPtrTestFCNullCheckAccessBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FCDPtrTestFCNullCheckAccess &source);
};

typedef FCDPtrTestFCNullCheckAccess *FCDPtrTestFCNullCheckAccessP;

OSG_END_NAMESPACE

#include "OSGFCDPtrTestFCNullCheckAccessBase.inl"
#include "OSGFCDPtrTestFCNullCheckAccess.inl"

#endif /* _OSGFCDPTRTESTFCNULLCHECKACCESS_H_ */
