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

#ifndef _OSGFRAMEHANDLER_H_
#define _OSGFRAMEHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFrameHandlerBase.h"
#include "OSGFrameTask.h"

OSG_BEGIN_NAMESPACE

/*! \brief FrameHandler class. See \ref
           PageDynamicsFrameHandler for a description.
*/

class OSG_DYNAMICS_DLLMAPPING FrameHandler : public FrameHandlerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FrameHandlerBase Inherited;
    typedef FrameHandler     Self;

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

    static void          setGlobalInstance(FrameHandler *pHandler);
    static FrameHandler *the              (void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void addTask   (FrameTask *pTask);
    void removeTask(FrameTask *pTask);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */
    
    bool init    (void);
    void frame   (void);
    void shutdown(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FrameHandlerBase.

    static bool                 _bRegistersInstanceRelease;
    static FrameHandlerUnrecPtr _pGlobalInstance;

    static bool releaseGlobalInstance(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FrameHandler(void);
    FrameHandler(const FrameHandler &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FrameHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FrameHandlerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FrameHandler &source);
};

typedef FrameHandler *FrameHandlerP;

OSG_END_NAMESPACE

#include "OSGFrameHandlerBase.inl"
#include "OSGFrameHandler.inl"

#endif /* _OSGFRAMEHANDLER_H_ */
