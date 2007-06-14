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

#ifndef _OSGIMAGECOMPOSER_H_
#define _OSGIMAGECOMPOSER_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGImageComposerBase.h"
#include "OSGWindow.h"
#include "OSGClusterWindow.h"
#include "OSGViewport.h"

OSG_BEGIN_NAMESPACE

class OSG_CLUSTER_DLLMAPPING ImageComposer : public ImageComposerBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ImageComposerBase                          Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      setup                                                   */
    /*! \{                                                                 */

    void setup(bool             isClient,
               UInt32           clusterId,
               WindowPtr        localWindow, 
               ClusterWindowPtr clusterWindow);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      composition                                             */
    /*! \{                                                                 */

    virtual void open           (void            );
    virtual void composeViewport(ViewportPtr port);
    virtual void composeWindow  (void            );
    virtual void close          (void            );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      features                                                */
    /*! \{                                                                 */

    virtual bool   getClientRendering(void);
    virtual UInt32 getUsableServers  (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  protected variables                         */
    /*! \{                                                                 */

    bool             _isClient;
    UInt32           _clusterId;
    UInt32           _clusterSize;
    UInt32           _serverCount;
    WindowPtr        _localWindow;
    ClusterWindowPtr _clusterWindow;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  get                                         */
    /*! \{                                                                 */
    
    bool             isClient     (void);
    UInt32           clusterId    (void);
    UInt32           clusterSize  (void);
    UInt32           serverCount  (void);
    WindowPtr        localWindow  (void);
    ClusterWindowPtr clusterWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  helpers                                     */
    /*! \{                                                                 */

    bool getScreenAlignedBBox(NodePtr        root,
                              ViewportPtr    vp,
                              UInt32        &l,
                              UInt32        &b,
                              UInt32        &r,
                              UInt32        &t,
                              UInt32        &front,
                              UInt32        &back);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ImageComposer(void);
    ImageComposer(const ImageComposer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ImageComposer(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ImageComposerBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ImageComposer &source);
};

typedef ImageComposer *ImageComposerP;

OSG_END_NAMESPACE

#include "OSGImageComposerBase.inl"
#include "OSGImageComposer.inl"

#endif /* _OSGIMAGECOMPOSER_H_ */
