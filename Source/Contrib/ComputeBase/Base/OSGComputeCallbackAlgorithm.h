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

#ifndef _OSGCOMPUTECALLBACKALGORITHM_H_
#define _OSGCOMPUTECALLBACKALGORITHM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComputeCallbackAlgorithmBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComputeCallbackAlgorithm class. See \ref
           PageGroupComputeCallbackAlgorithm for a description.
*/

class OSG_CONTRIBCOMPUTEBASE_DLLMAPPING ComputeCallbackAlgorithm : 
    public ComputeCallbackAlgorithmBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComputeCallbackAlgorithmBase Inherited;
    typedef ComputeCallbackAlgorithm     Self;

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

    void setCallback(ComputeFunctor func,
                     std::string    createSymbol);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual ActionBase::ResultE renderEnter(Action          *pAction );
    virtual ActionBase::ResultE renderLeave(Action          *pAction );
    virtual void                execute    (HardwareContext *pContext, 
                                            DrawEnv         *pEnv    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CallbackAlgorithmBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComputeCallbackAlgorithm(void);
    ComputeCallbackAlgorithm(const ComputeCallbackAlgorithm &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComputeCallbackAlgorithm(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComputeCallbackAlgorithmBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComputeCallbackAlgorithm &source);
};

typedef ComputeCallbackAlgorithm *ComputeCallbackAlgorithmP;

OSG_END_NAMESPACE

#include "OSGComputeCallbackAlgorithmBase.inl"
#include "OSGComputeCallbackAlgorithm.inl"

#endif /* _OSGCOMPUTECALLBACKALGORITHM_H_ */
