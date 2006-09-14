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

#ifndef _OSGSIMPLESTATISTICSFOREGROUND_H_
#define _OSGSIMPLESTATISTICSFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSimpleStatisticsForegroundBase.h"
#include "OSGTextTXFFace.h"
#include "OSGTextureChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief Simple Statistics Foreground class. See \ref
    PageSystemWindowForegroundStatisticsSimple for a description.
*/

class OSG_UTIL_DLLMAPPING SimpleStatisticsForeground : 
    public SimpleStatisticsForegroundBase
{
  public:

    typedef SimpleStatisticsForegroundBase                    Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Draw                                    */
    /*! \{                                                                 */

    virtual void draw(DrawEnv *pEnv, Viewport *pPort);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Convenience Functions                          */
    /*! \{                                                                 */

    void addElement(StatElemDescBase &desc, const Char8 *format = NULL);
    void addElement(Int32            id,    const Char8 *format = NULL);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SimpleStatisticsForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleStatisticsForeground(void);
    SimpleStatisticsForeground(const SimpleStatisticsForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleStatisticsForeground(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    static TextTXFFace*    _face;

    static TextureChunkPtr _texchunk;

    friend class SimpleStatisticsForegroundBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;


    static void initText(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleStatisticsForeground &source);
};

typedef SimpleStatisticsForeground       *SimpleStatisticsForegroundP;

OSG_END_NAMESPACE

#include "OSGSimpleStatisticsForegroundBase.inl"
#include "OSGSimpleStatisticsForeground.inl"

#define OSGSIMPLESTATISTICSFOREGROUND_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGSIMPLESTATISTICSFOREGROUND_H_ */
