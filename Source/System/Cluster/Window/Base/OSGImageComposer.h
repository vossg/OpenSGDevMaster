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

/*! \ingroup GrpClusterWindowComposer
    \ingroup GrpLibOSGCluster
    \includebasedoc
 */

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
    /*! \name      setup                                                   */
    /*! \{                                                                 */

    void setup(bool           isClient,
               UInt32         clusterId,
               Window        *localWindow, 
               ClusterWindow *clusterWindow);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      composition                                             */
    /*! \{                                                                 */

    virtual void open           (void          );
    virtual void startFrame     (void          );
    virtual void startViewport  (Viewport *port);
    virtual void composeViewport(Viewport *port);
    virtual void composeWindow  (void          );
    virtual void close          (void          );
    
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

    bool           _isClient;
    UInt32         _clusterId;
    UInt32         _clusterSize;
    UInt32         _serverCount;
    Window        *_localWindow;
    ClusterWindow *_clusterWindow;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  get                                         */
    /*! \{                                                                 */
    
    bool           isClient     (void);
    UInt32         clusterId    (void);
    UInt32         clusterSize  (void);
    UInt32         serverCount  (void);
    Window        *localWindow  (void);
    ClusterWindow *clusterWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  helpers                                     */
    /*! \{                                                                 */

    bool getScreenAlignedBBox(Node     *root,
                              Viewport *vp,
                              UInt32   &l,
                              UInt32   &b,
                              UInt32   &r,
                              UInt32   &t,
                              UInt32   &front,
                              UInt32   &back);

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
    static void exitMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ImageComposerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ImageComposer &source);
};

typedef ImageComposer *ImageComposerP;

OSG_END_NAMESPACE

#include "OSGImageComposerBase.inl"
#include "OSGImageComposer.inl"

#endif /* _OSGIMAGECOMPOSER_H_ */
