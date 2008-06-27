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

#ifndef _OSGDRAWMANAGER_H_
#define _OSGDRAWMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawManagerBase.h"
#include "OSGDrawer.h"

OSG_BEGIN_NAMESPACE

/*! \brief DrawManager class. See \ref
           PageContribCSMDrawManager for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING DrawManager : public DrawManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DrawManagerBase Inherited;
    typedef DrawManager     Self;

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

    bool init    (void);
    void shutdown(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void frame(Time oTime, UInt32 uiFrame);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual FieldContainer *findNamedComponent(const Char8 *szName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DrawManagerBase.

    Thread  *_pThread;
    Barrier *_pSyncBarrier;
    Barrier *_pSwapBarrier;

#ifdef OSG_GLOBAL_SYNC_LOCK
    Lock    *_pSyncLock;
#endif


    UInt32   _uiSyncCount;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DrawManager(void);
    DrawManager(const DrawManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DrawManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DrawManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DrawManager &source);
};

typedef DrawManager *DrawManagerP;

OSG_END_NAMESPACE

#include "OSGDrawManagerBase.inl"
#include "OSGDrawManager.inl"

#endif /* _OSGDRAWMANAGER_H_ */
