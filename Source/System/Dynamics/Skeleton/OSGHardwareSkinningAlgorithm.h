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

#ifndef _OSGHARDWARESKINNINGALGORITHM_H_
#define _OSGHARDWARESKINNINGALGORITHM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGHardwareSkinningAlgorithmBase.h"

#include "OSGShaderProgramChunk.h"
#include "OSGShaderProgramVariableChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief HardwareSkinningAlgorithm class. See \ref
           PageDynamicsHardwareSkinningAlgorithm for a description.
*/

class OSG_DYNAMICS_DLLMAPPING HardwareSkinningAlgorithm : public HardwareSkinningAlgorithmBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HardwareSkinningAlgorithmBase Inherited;
    typedef HardwareSkinningAlgorithm     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Execute                                 */
    /*! \{                                                                 */

    virtual void                adjustVolume(Volume  &volume );

    virtual ActionBase::ResultE renderEnter (Action  *action );
    virtual ActionBase::ResultE renderLeave (Action  *action );

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

    // Variables should all be in HardwareSkinningAlgorithmBase.

    static const std::string _vpVertexSkinning;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HardwareSkinningAlgorithm(void);
    HardwareSkinningAlgorithm(const HardwareSkinningAlgorithm &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HardwareSkinningAlgorithm(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HardwareSkinningAlgorithmBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HardwareSkinningAlgorithm &source);
};

typedef HardwareSkinningAlgorithm *HardwareSkinningAlgorithmP;

OSG_END_NAMESPACE

#include "OSGHardwareSkinningAlgorithmBase.inl"
#include "OSGHardwareSkinningAlgorithm.inl"

#endif /* _OSGHARDWARESKINNINGALGORITHM_H_ */
