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

#ifndef _OSGDRAWER_H_
#define _OSGDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawerBase.h"
#include "OSGCSMWindow.h"

OSG_BEGIN_NAMESPACE

class DrawThread;

/*! \brief Drawer class. See \ref
           PageContribCSMDrawer for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING Drawer : public DrawerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DrawerBase Inherited;
    typedef Drawer     Self;

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

    void setSyncCount     (UInt32   uiSyncCount );
    void setSwapCount     (UInt32   uiSwapCount );
    void setParallel      (bool     bParallel   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

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

    // Variables should all be in DrawerBase.

    RenderAction *_pAction;

    DrawThread   *_pDrawThread;

    Thread       *_pSyncFromThread;
    Barrier      *_pSyncBarrier;
    Barrier      *_pSwapBarrier;

    UInt32        _uiSyncCount;
    UInt32        _uiSwapCount;
    bool          _bParallel;
    bool          _bRun;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Drawer(void);
    Drawer(const Drawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Drawer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void runParallel        (void               );

    void frameRenderActivate(void               );
    void frameSwapActivate  (void               );
    void frameExit          (void               );
    
    void activate           (UInt32 uiWindow = 0);
    void frameRender        (UInt32 uiWindow = 0);
    void frameSwap          (UInt32 uiWindow = 0);
    void deactivate         (UInt32 uiWindow = 0);

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
    friend class DrawerBase;
    friend class DrawThread;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Drawer &source);
};

typedef Drawer *DrawerP;


class OSG_CONTRIBCSM_DLLMAPPING DrawThread : public Thread
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static DrawThread *get (Char8 *szName);
    static DrawThread *find(Char8 *szName);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void setDrawer (Drawer *pDrawer);
    void setRunning(bool    bVal   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Thread        Inherited;

    static  MPThreadType _type;

    Drawer *_pDrawer;

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static BaseThread *create(const Char8  *szName, 
                                    UInt32  uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    DrawThread(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DrawThread(void); 

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
    DrawThread(const DrawThread &source);
    void operator =(const DrawThread &source);
};


OSG_END_NAMESPACE

#include "OSGDrawerBase.inl"
#include "OSGDrawer.inl"

#endif /* _OSGDRAWER_H_ */
