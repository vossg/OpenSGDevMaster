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

#ifndef _OSGCSMCLUSTERWINOPTIONS_H_
#define _OSGCSMCLUSTERWINOPTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCSMClusterWinOptionsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CSMClusterWinOptions class. See \ref
           PageContribCSMCSMClusterWinOptions for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING CSMClusterWinOptions : public CSMClusterWinOptionsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CSMClusterWinOptionsBase Inherited;
    typedef CSMClusterWinOptions     Self;

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

    // Variables should all be in CSMClusterWinOptionsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CSMClusterWinOptions(void);
    CSMClusterWinOptions(const CSMClusterWinOptions &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CSMClusterWinOptions(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CSMClusterWinOptionsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CSMClusterWinOptions &source);
};

typedef CSMClusterWinOptions *CSMClusterWinOptionsP;

OSG_END_NAMESPACE

#include "OSGCSMClusterWinOptionsBase.inl"
#include "OSGCSMClusterWinOptions.inl"

#endif /* _OSGCSMCLUSTERWINOPTIONS_H_ */
