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

#ifndef _OSGUNSKINNEDSKINNINGALGORITHM_H_
#define _OSGUNSKINNEDSKINNINGALGORITHM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUnskinnedSkinningAlgorithmBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief UnskinnedSkinningAlgorithm class. See \ref
           PageDynamicsUnskinnedSkinningAlgorithm for a description.
*/

class OSG_DYNAMICS_DLLMAPPING UnskinnedSkinningAlgorithm : public UnskinnedSkinningAlgorithmBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UnskinnedSkinningAlgorithmBase Inherited;
    typedef UnskinnedSkinningAlgorithm     Self;

    typedef SkinnedGeometry::RenderModeE   RenderModeE;

    /*---------------------------------------------------------------------*/
    /*! \name                      Execute                                 */
    /*! \{                                                                 */

    virtual void                adjustVolume  (Volume  &volume );

    virtual ActionBase::ResultE renderEnter   (Action  *action );
    virtual ActionBase::ResultE renderLeave   (Action  *action );

    virtual ActionBase::ResultE intersectEnter(Action  *action );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual RenderModeE getRenderMode(void) const;

    /*! \}                                                                 */
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

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UnskinnedSkinningAlgorithmBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UnskinnedSkinningAlgorithm(void);
    UnskinnedSkinningAlgorithm(const UnskinnedSkinningAlgorithm &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UnskinnedSkinningAlgorithm(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UnskinnedSkinningAlgorithmBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UnskinnedSkinningAlgorithm &source);
};

typedef UnskinnedSkinningAlgorithm *UnskinnedSkinningAlgorithmP;

OSG_END_NAMESPACE

#include "OSGUnskinnedSkinningAlgorithmBase.inl"
#include "OSGUnskinnedSkinningAlgorithm.inl"

#endif /* _OSGUNSKINNEDSKINNINGALGORITHM_H_ */
