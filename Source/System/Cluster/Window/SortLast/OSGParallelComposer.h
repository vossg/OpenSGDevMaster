/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGPARALLELCOMPOSER_H_
#define _OSGPARALLELCOMPOSER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParallelComposerBase.h"


#ifdef OSG_WITH_PARALLEL
#include <cei_pc.h>
#endif

#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif

OSG_BEGIN_NAMESPACE

/*! \brief ParallelComposer class. See \ref 
           PageSystemParallelComposer for a description.

    \ingroup GrpClusterWindowComposer
    \ingroup GrpLibOSGCluster
    \includebasedoc
 */

class OSG_CLUSTER_DLLMAPPING ParallelComposer : public ParallelComposerBase
{
  private:

    typedef ParallelComposerBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      features                                                */
    /*! \{                                                                 */

    virtual bool clientRendering (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      composition                                             */
    /*! \{                                                                 */

    virtual void open           (               );
    virtual void composeViewport(Viewport *port );
    virtual void close          (void           );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      features                                                */
    /*! \{                                                                 */

    virtual bool   getClientRendering(void);
    virtual UInt32 getUsableServers  (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt32          _usableServers;
    UInt32          _wWidth;
    UInt32          _wHeight;
    Real64          _fRenderRequest[6]; 
    char**          _serverList;
    char            _serviceAddr[256];    
    UInt8*          _bufColor;
    UInt8*          _bufDepth;
    UInt8*          _bufRet;
    bool            _createContext;
#ifdef OSG_WITH_PARALLEL
    PCint           _rowPixels;
    PCcontext       _context;
#endif
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParallelComposer(void);
    ParallelComposer(const ParallelComposer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParallelComposer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              compose                                         */
    /*! \{                                                                 */

    void writeBuffer();
    void readBuffer();
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
  
    // helper functions
    void            createCtx (Viewport *port);
    void            endFrame  (UInt32    id  );
    UInt32          beginFrame(void          );
    void            drawFrame (void          );
    void            renderRead(void          );

    friend class FieldContainer;
    friend class ParallelComposerBase;


    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParallelComposer &source);

};

typedef ParallelComposer *ParallelComposerP;

OSG_END_NAMESPACE

#include "OSGParallelComposerBase.inl"
#include "OSGParallelComposer.inl"

#endif /* _OSGPARALLELCOMPOSER_H_ */
