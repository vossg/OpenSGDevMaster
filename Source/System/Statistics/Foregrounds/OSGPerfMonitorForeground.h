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

#ifndef _OSGPERFMONITORFOREGROUND_H_
#define _OSGPERFMONITORFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPerfMonitorForegroundBase.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTextTXFFace.h"

OSG_BEGIN_NAMESPACE

/*! \brief PerfMonitorForeground class. See \ref
           PageUtilPerfMonitorForeground for a description.
    \ingroup GrpUtilStatisticsObj
    \ingroup GrpLibOSGUtil
    \includebasedoc
*/

class OSG_UTIL_DLLMAPPING PerfMonitorForeground : 
    public PerfMonitorForegroundBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    enum Mode
    {
        Text     = 0,      /**< Only display raw text information. */
        PercentLines,      /**< Display line chart of percentage of siblings. */
        PercentTotalLines, /**< Display line chart of percentage of total. */
        MaxLines,          /**< Display line chart scaled by max value in sample. */
        ThreadTiming,      /**< Display thread timing/call diagram. */
        MODE_END           /**< The end of the list of modes. */
    };

    typedef PerfMonitorForegroundBase Inherited;
    typedef PerfMonitorForeground     Self;

    /** Cycle to the next display mode. */
    void cycleMode(int increment = 1);

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
    /*---------------------------------------------------------------------*/
    /*! \name                   draw                                       */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PerfMonitorForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PerfMonitorForeground(void);
    PerfMonitorForeground(const PerfMonitorForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PerfMonitorForeground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void initText(const std::string &family, Real32 size);

    /*==========================  PRIVATE  ================================*/

  private:

    TextTXFFaceRefPtr       _face;           /**< The face we are using for the text in the UI. */

    TextureObjChunkUnrecPtr _texchunk;       /**< The texture holding the text face. */
    TextureEnvChunkUnrecPtr _texenvchunk;    /**< The texture env for the text face. */

    std::map<unsigned, std::string> mode_names; /**< Map from mode to string of the mode name. */

    friend class FieldContainer;
    friend class PerfMonitorForegroundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PerfMonitorForeground &source);
};

typedef PerfMonitorForeground *PerfMonitorForegroundP;

OSG_END_NAMESPACE

#include "OSGPerfMonitorForegroundBase.inl"
#include "OSGPerfMonitorForeground.inl"

#endif /* _OSGPERFMONITORFOREGROUND_H_ */
