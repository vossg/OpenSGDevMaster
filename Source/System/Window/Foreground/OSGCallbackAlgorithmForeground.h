/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGCALLBACKALGORITHMFOREGROUND_H_
#define _OSGCALLBACKALGORITHMFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCallbackAlgorithmForegroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CallbackAlgorithmForeground class. See \ref
           PageWindowCallbackAlgorithmForeground for a description.
*/

class OSG_WINDOW_DLLMAPPING CallbackAlgorithmForeground : public CallbackAlgorithmForegroundBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CallbackAlgorithmForegroundBase Inherited;
    typedef CallbackAlgorithmForeground     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                      Draw                                    */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *pEnv);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CallbackAlgorithmForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CallbackAlgorithmForeground(void);
    CallbackAlgorithmForeground(const CallbackAlgorithmForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CallbackAlgorithmForeground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CallbackAlgorithmForegroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CallbackAlgorithmForeground &source);
};

typedef CallbackAlgorithmForeground *CallbackAlgorithmForegroundP;

OSG_END_NAMESPACE

#include "OSGCallbackAlgorithmForegroundBase.inl"
#include "OSGCallbackAlgorithmForeground.inl"

#endif /* _OSGCALLBACKALGORITHMFOREGROUND_H_ */
