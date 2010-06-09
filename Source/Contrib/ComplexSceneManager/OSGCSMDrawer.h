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

#ifndef _OSGCSMDRAWER_H_
#define _OSGCSMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCSMDrawerBase.h"
#include "OSGCSMWindow.h"

OSG_BEGIN_NAMESPACE

class CSMDrawThread;

OSG_GEN_MEMOBJPTR(CSMDrawThread);

/*! \brief CSMDrawer class. See \ref
           PageContribCSMDrawer for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING CSMDrawer : public CSMDrawerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CSMDrawerBase Inherited;
    typedef CSMDrawer     Self;

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

    bool init          (void);
    void endDrawThread (void);
    void shutdown      (void);
    void joinDrawThread(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void setSyncFromThread(Thread  *pThread     );
    void setSyncBarrier   (Barrier *pSyncBarrier);
    void setSwapBarrier   (Barrier *pSwapBarrier);
#ifdef OSG_GLOBAL_SYNC_LOCK
    void setSyncLock      (Lock    *pSyncLock   );
#endif

    void setSyncCount     (UInt32   uiSyncCount );
    void setSwapCount     (UInt32   uiSwapCount );
    void setParallel      (bool     bParallel   );

    void postSync         (void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void resolveLinks       (void);
    virtual void terminateGLContexts(void);

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

    // Variables should all be in CSMDrawerBase.

    RenderAction        *_pAction;

    CSMDrawThreadRefPtr  _pDrawThread;

    Thread              *_pSyncFromThread;
    Barrier             *_pSyncBarrier;
    Barrier             *_pSwapBarrier;
#ifdef OSG_GLOBAL_SYNC_LOCK
    Lock                *_pSyncLock;
#endif

    UInt32               _uiSyncCount;
    UInt32               _uiSwapCount;
    bool                 _bParallel;
    bool                 _bRun;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CSMDrawer(void);
    CSMDrawer(const CSMDrawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CSMDrawer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void render             (void               );

    void runParallel        (void               );

    void frameRenderNoFinish(void               );
    void frameFinish        (void               );
    void frameExit          (void               );
    
#if 0
    void activate           (UInt32 uiWindow = 0);
    void frameRender        (UInt32 uiWindow = 0);
    void frameSwap          (UInt32 uiWindow = 0);
    void deactivate         (UInt32 uiWindow = 0);
#endif

    void setRunning         (bool   bVal        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CSMDrawerBase;
    friend class CSMDrawThread;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CSMDrawer &source);
};

typedef CSMDrawer *CSMDrawerP;


class OSG_CONTRIBCSM_DLLMAPPING CSMDrawThread : public Thread
{

    /*==========================  PUBLIC  =================================*/

  public:

    OSG_GEN_INTERNAL_MEMOBJPTR(CSMDrawThread);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static ObjTransitPtr  get (Char8 *szName, bool bGlobal);
    static CSMDrawThread *find(Char8 *szName);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void setDrawer (CSMDrawer *pDrawer);
    void setRunning(bool       bVal   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Thread        Inherited;

    static  MPThreadType _type;

    CSMDrawer *_pDrawer;

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static BaseThread *create(const Char8  *szName, 
                                    UInt32  uiId,
                                    bool    bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    CSMDrawThread(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~CSMDrawThread(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual void workProc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
   /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    CSMDrawThread(const CSMDrawThread &source);
    void operator =(const CSMDrawThread &source);
};

OSG_END_NAMESPACE

#include "OSGCSMDrawerBase.inl"
#include "OSGCSMDrawer.inl"

#endif /* _OSGCSMDRAWER_H_ */
