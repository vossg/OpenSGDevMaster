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

#ifndef _OSGFCDPTRTESTFCCUSTOMACCESS_H_
#define _OSGFCDPTRTESTFCCUSTOMACCESS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFCDPtrTestFCCustomAccessBase.h"
#include "OSGFCDTestFC.h"
#include "OSGFCDSParTestFC.h"

OSG_BEGIN_NAMESPACE

/*! \brief FCDPtrTestFCCustomAccess class. See \ref
           PageSystemFCDPtrTestFCCustomAccess for a description.
*/

class OSG_SYSTEM_DLLMAPPING FCDPtrTestFCCustomAccess : public FCDPtrTestFCCustomAccessBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FCDPtrTestFCCustomAccessBase Inherited;
    typedef FCDPtrTestFCCustomAccess     Self;

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

    void setFieldSFPub_ptr (FCDTestFC * const value);
    void setFieldSFPub_weakptr(FCDTestFC * const value);
    void setFieldSFPub_mpchildptr(FCDTestFC * const value);
    void setFieldSFPub_spchildptr(FCDSParTestFC * const value);

    void pushToFieldMFPub_ptr           (FCDTestFC * const value   );
    void pushToFieldMFPub_weakptr           (FCDTestFC * const value   );
    void pushToFieldMFPub_mpchildptr           (FCDTestFC * const value   );
    void pushToFieldMFPub_spchildptr           (FCDSParTestFC * const value   );

    void clearFieldMFPub_ptr            (void                          );
    void clearFieldMFPub_weakptr            (void                          );
    void clearFieldMFPub_mpchildptr            (void                          );
    void clearFieldMFPub_spchildptr            (void                          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FCDPtrTestFCCustomAccessBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FCDPtrTestFCCustomAccess(void);
    FCDPtrTestFCCustomAccess(const FCDPtrTestFCCustomAccess &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FCDPtrTestFCCustomAccess(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setFieldSFPro_ptr (FCDTestFC * const value);
    void setFieldSFPro_weakptr(FCDTestFC * const value);
    void setFieldSFPro_mpchildptr(FCDTestFC * const value);
    void setFieldSFPro_spchildptr(FCDSParTestFC * const value);

    void pushToFieldMFPro_ptr           (FCDTestFC * const value   );
    void pushToFieldMFPro_weakptr           (FCDTestFC * const value   );
    void pushToFieldMFPro_mpchildptr           (FCDTestFC * const value   );
    void pushToFieldMFPro_spchildptr           (FCDSParTestFC * const value   );

    void clearFieldMFPro_ptr            (void                          );
    void clearFieldMFPro_weakptr            (void                          );
    void clearFieldMFPro_mpchildptr            (void                          );
    void clearFieldMFPro_spchildptr            (void                          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */

    void setFieldSFPri_ptr (FCDTestFC * const value);
    void setFieldSFPri_weakptr(FCDTestFC * const value);
    void setFieldSFPri_mpchildptr(FCDTestFC * const value);
    void setFieldSFPri_spchildptr(FCDSParTestFC * const value);

    void pushToFieldMFPri_ptr           (FCDTestFC * const value   );
    void pushToFieldMFPri_weakptr           (FCDTestFC * const value   );
    void pushToFieldMFPri_mpchildptr           (FCDTestFC * const value   );
    void pushToFieldMFPri_spchildptr           (FCDSParTestFC * const value   );

    void clearFieldMFPri_ptr            (void                          );
    void clearFieldMFPri_weakptr            (void                          );
    void clearFieldMFPri_mpchildptr            (void                          );
    void clearFieldMFPri_spchildptr            (void                          );

    friend class FieldContainer;
    friend class FCDPtrTestFCCustomAccessBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FCDPtrTestFCCustomAccess &source);
};

typedef FCDPtrTestFCCustomAccess *FCDPtrTestFCCustomAccessP;

OSG_END_NAMESPACE

#include "OSGFCDPtrTestFCCustomAccessBase.inl"
#include "OSGFCDPtrTestFCCustomAccess.inl"

#endif /* _OSGFCDPTRTESTFCCUSTOMACCESS_H_ */
