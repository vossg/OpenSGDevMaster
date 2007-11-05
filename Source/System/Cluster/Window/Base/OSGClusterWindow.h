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

#ifndef _OSGCLUSTERWINDOW_H_
#define _OSGCLUSTERWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGClusterWindowBase.h"
#include "OSGStatElemTypes.h"
#include "OSGImageComposer.h"

OSG_BEGIN_NAMESPACE

class StatCollector;
class Connection;
class ClusterServer;
class RemoteAspect;
class ClusterNetwork;
class RenderActionBase;

class OSG_CLUSTER_DLLMAPPING ClusterWindow : public ClusterWindowBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ClusterWindowBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   window functions                           */
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
    /*! \name            GL implementation functions                       */
    /*! \{                                                                 */

    virtual void(*getFunctionByName (const Char8 *s))();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void  activate          (void                           );
    virtual void  deactivate        (void                           );
    virtual bool  swap              (void                           );
    virtual void  init              (void                           );
#ifdef OSG_OLD_RENDER_ACTION
    virtual void  render            (DrawActionBase *action = NULL);
    virtual void  renderAllViewports(DrawActionBase *action = NULL);
#endif

    virtual void  render            (RenderActionBase *action);
    virtual void  renderAllViewports(RenderActionBase *action);
    virtual void  frameInit         (void                             );
    virtual void  frameExit         (void                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            asynchronous initialization                       */
    /*! \{                                                                 */

    typedef bool (*connectioncbfp)(std::string server, Real32 progress);

    bool initAsync      (connectioncbfp fp);
    void setConnectionCB(connectioncbfp fp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               connection pool                                */
    /*! \{                                                                 */

    ClusterNetwork *getNetwork(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistics                                 */
    /*! \{                                                                 */

    StatCollector *getStatistics(void               ) const;
    void           setStatistics(StatCollector *stat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Calibration                                */
    /*! \{                                                                 */

#if 0
    bool loadCalibration(std::istream &in);
    bool saveCalibration(std::ostream &out);

    bool loadFilter(std::istream &in);
    bool updateFilter(WindowPtr window, UInt32 id, RenderActionBase *action);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Exceptions                                 */
    /*! \{                                                                 */

    class OSG_CLUSTER_DLLMAPPING AsyncCancel : public Exception 
    {
      public:
        AsyncCancel();
    };

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name      client window funcitons                                 */
    /*! \{                                                                 */

    virtual void clientInit   (void                    );
    virtual void clientPreSync(void                    );
#ifdef OSG_OLD_RENDER_ACTION
    virtual void clientRender (DrawActionBase   *action);
#endif

    virtual void clientRender (RenderActionBase *action);
    virtual void clientSwap   (void                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      server window funcitons                                 */
    /*! \{                                                                 */

    virtual void serverInit  (WindowPtr         window,
                              UInt32            id    );
#ifdef OSG_OLD_RENDER_ACTION
    virtual void serverRender(WindowPtr         window,
                              UInt32            id,
                              DrawActionBase *action);
#endif

    virtual void serverRender(WindowPtr         window,
                              UInt32            id,
                              RenderActionBase *action);
    virtual void serverSwap  (WindowPtr         window,
                              UInt32            id    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors / Destructor                   */
    /*! \{                                                                 */

    ClusterWindow(void);
    ClusterWindow(const ClusterWindow &source);

    virtual ~ClusterWindow(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               unsynced thread variables                      */
    /*! \{                                                                 */

    bool               _firstFrame;
    StatCollector     *_statistics;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              init method                                     */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/
    /*! \name               private members                                */
    /*! \{                                                                 */

    connectioncbfp  _connectionFP;
    ClusterNetwork *_network;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    friend class FieldContainer;
    friend class ClusterWindowBase;
    friend class ClusterServer;
    friend class ClusterClient;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ClusterWindow &source);
};

typedef ClusterWindow *ClusterWindowP;

OSG_END_NAMESPACE

#include "OSGClusterWindow.inl"
#include "OSGClusterWindowBase.inl"

#endif /* _OSGCLUSTERWINDOW_H_ */
