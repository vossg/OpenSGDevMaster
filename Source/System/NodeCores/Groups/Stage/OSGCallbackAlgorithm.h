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

#ifndef _OSGCALLBACKALGORITHM_H_
#define _OSGCALLBACKALGORITHM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCallbackAlgorithmBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CallbackAlgorithm class. See \ref
           PageGroupCallbackAlgorithm for a description.
    \ingroup GrpGroupStageObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
*/

class OSG_GROUP_DLLMAPPING CallbackAlgorithm : public CallbackAlgorithmBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CallbackAlgorithmBase Inherited;
    typedef CallbackAlgorithm     Self;

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

    void setCallback(RenderFunctor func,
                     std::string   createSymbol);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual ActionBase::ResultE renderEnter(Action  *pAction);
    virtual ActionBase::ResultE renderLeave(Action  *pAction);
    virtual void                execute    (DrawEnv *pEnv   );

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

    CallbackAlgorithm(void);
    CallbackAlgorithm(const CallbackAlgorithm &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CallbackAlgorithm(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CallbackAlgorithmBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CallbackAlgorithm &source);
};

typedef CallbackAlgorithm *CallbackAlgorithmP;

OSG_END_NAMESPACE

#include "OSGCallbackAlgorithmBase.inl"
#include "OSGCallbackAlgorithm.inl"

#endif /* _OSGCALLBACKALGORITHM_H_ */
