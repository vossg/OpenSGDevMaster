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

#ifndef _OSGHARDWARECONTEXT_H_
#define _OSGHARDWARECONTEXT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGHardwareContextBase.h"
#include "OSGHardwareContextThread.h"

OSG_BEGIN_NAMESPACE

/*! \brief HardwareContext class. See \ref
           PageBaseHardwareContext for a description.
*/

class OSG_BASE_DLLMAPPING HardwareContext : public HardwareContextBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HardwareContextBase Inherited;
    typedef HardwareContext     Self;

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

    // Variables should all be in HardwareContextBase.

    HardwareContextThreadRefPtr _pContextThread;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HardwareContext(void);
    HardwareContext(const HardwareContext &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HardwareContext(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    void onCreate       (const HardwareContext *source = NULL);
    
    void onCreateAspect (const HardwareContext *createAspect,
                         const HardwareContext *source = NULL);
    
    void onDestroy      (      UInt32           uiContainerId);
    
    void onDestroyAspect(      UInt32           uiContainerId,
                               UInt32           uiAspect     );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HardwareContextBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HardwareContext &source);
};

typedef HardwareContext *HardwareContextP;

OSG_END_NAMESPACE

#include "OSGHardwareContextBase.inl"
#include "OSGHardwareContext.inl"

#endif /* _OSGHARDWARECONTEXT_H_ */
