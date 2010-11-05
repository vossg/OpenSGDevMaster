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

#ifndef _OSGSTATISTICSFOREGROUND_H_
#define _OSGSTATISTICSFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStatisticsForegroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Statistics Foregrounds base class.
    \ingroup GrpSystemStatisticsObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING StatisticsForeground :
    public StatisticsForegroundBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef StatisticsForegroundBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   draw                                       */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *pEnv) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in StatisticsForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StatisticsForeground(void);
    StatisticsForeground(const StatisticsForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StatisticsForeground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    void onCreateAspect(const StatisticsForeground *createAspect,
                        const StatisticsForeground *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    virtual void onDestroyAspect(UInt32 uiContainerId,
                                 UInt32 uiAspect     );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class StatisticsForegroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StatisticsForeground &source);
};

typedef StatisticsForeground             *StatisticsForegroundP;

OSG_END_NAMESPACE

#include "OSGStatisticsForegroundBase.inl"
#include "OSGStatisticsForeground.inl"

#endif /* _OSGSTATISTICSFOREGROUND_H_ */
