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

#ifndef _OSGSEPIACOMPOSER_H_
#define _OSGSEPIACOMPOSER_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_WITH_SEPIA
#include <sepiart.h>
#endif

#include "OSGSepiaComposerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SepiaComposer class. See \ref 
           PageSystemSepiaComposer for a description.

    \ingroup GrpClusterWindowComposer
    \ingroup GrpLibOSGCluster
    \includebasedoc
 */

class OSG_CLUSTER_DLLMAPPING SepiaComposer : public SepiaComposerBase
{
  private:

    typedef SepiaComposerBase Inherited;

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

    virtual bool getClientRendering(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      composition                                             */
    /*! \{                                                                 */

    virtual void open         (void);
    virtual void composeWindow(void);
    virtual void close        (void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    unsigned int _descphysaddr;   /* descriptor for physical addresses */
    void*        _descvirtaddr;   /* descriptor for virtual addresses */
#ifdef OSG_WITH_SEPIA
    Pam          _pam;            /* board description structure */
#endif
    int          _frame;          /* number of the current frame */
    void*        _pbuffer;        /* pointer to the pixel buffer */
    void*        _zbuffer;        /* pointer to the z-buffer */
    int          _fromNode;
    int          _toNode;
    unsigned int _dmaBufferHandle;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SepiaComposer(void);
    SepiaComposer(const SepiaComposer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SepiaComposer(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      helper function                         */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SepiaComposerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SepiaComposer &source);
};

typedef SepiaComposer *SepiaComposerP;

OSG_END_NAMESPACE

#include "OSGSepiaComposerBase.inl"

#endif /* _OSGSEPIACOMPOSER_H_ */
