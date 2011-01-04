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

#ifndef _OSGSORTFIRSTWINDOW_H_
#define _OSGSORTFIRSTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGClusterViewBuffer.h"
#include "OSGSortFirstWindowBase.h"
#include "OSGTileLoadBalancer.h"
#include "OSGCamera.h"
#include "OSGRenderNode.h"

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 

    \ingroup GrpClusterWindowObj
    \ingroup GrpLibOSGCluster
    \includebasedoc
 */

class OSG_CLUSTER_DLLMAPPING SortFirstWindow : public SortFirstWindowBase
{
  private:

    typedef SortFirstWindowBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name      client window funcitons                                 */
    /*! \{                                                                 */

    virtual void clientInit   (void                    );
    virtual void clientPreSync(void                    );

    virtual void clientRender (RenderActionBase *action);
    virtual void clientSwap   (void                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      server window funcitons                                 */
    /*! \{                                                                 */

    virtual void serverInit  (Window           *window,
                              UInt32            id    );
#ifdef OSG_OLD_RENDER_ACTION
    virtual void serverRender(WindowPtr         window,
                              UInt32            id,
                              DrawActionBase   *action);
#endif

    virtual void serverRender(Window           *window,
                              UInt32            id,
                              RenderActionBase *action);

    virtual void serverSwap (Window            *window,
                             UInt32             id    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SortFirstWindow(void);
    SortFirstWindow(const SortFirstWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SortFirstWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                utilities                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    static ClusterViewBuffer  _bufferHandler;

    TileLoadBalancer         *_tileLoadBalancer;
    RenderNode               *_renderNode;

    friend class FieldContainer;
    friend class SortFirstWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SortFirstWindow &source);
};

typedef SortFirstWindow *SortFirstWindowP;

OSG_END_NAMESPACE

#include "OSGSortFirstWindow.inl"
#include "OSGSortFirstWindowBase.inl"

#endif /* _OSGSORTFIRSTWINDOW_H_ */
