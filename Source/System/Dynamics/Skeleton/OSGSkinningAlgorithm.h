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

#ifndef _OSGSKINNINGALGORITHM_H_
#define _OSGSKINNINGALGORITHM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkinningAlgorithmBase.h"

#include "OSGSkinnedGeometry.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkinningAlgorithm class. See \ref
           PageDynamicsSkinningAlgorithm for a description.
*/

class OSG_DYNAMICS_DLLMAPPING SkinningAlgorithm : public SkinningAlgorithmBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkinningAlgorithmBase         Inherited;
    typedef SkinningAlgorithm             Self;

    typedef SkinnedGeometry::RenderModeE  RenderModeE;

    /*---------------------------------------------------------------------*/
    /*! \name Execute                                                      */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume  &volume ) = 0;

    virtual void execute     (DrawEnv *drawEnv);

    virtual ActionBase::ResultE intersectEnter(Action *action) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

            SkinnedGeometry *getSkin      (void) const;
    virtual RenderModeE      getRenderMode(void) const = 0;

    /*---------------------------------------------------------------------*/
    /*! \name  Sync                                                        */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Output                                                       */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkinningAlgorithmBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkinningAlgorithm(void);
    SkinningAlgorithm(const SkinningAlgorithm &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkinningAlgorithm(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkinningAlgorithmBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkinningAlgorithm &source);
};

typedef SkinningAlgorithm *SkinningAlgorithmP;

OSG_END_NAMESPACE

#include "OSGSkinningAlgorithmBase.inl"
#include "OSGSkinningAlgorithm.inl"

#endif /* _OSGSKINNINGALGORITHM_H_ */
