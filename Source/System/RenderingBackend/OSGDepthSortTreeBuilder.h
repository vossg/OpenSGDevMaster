/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#ifndef _OSGDEPTHSORTTREEBUILDER_H_
#define _OSGDEPTHSORTTREEBUILDER_H_

#include "OSGConfig.h"
#include "OSGSystemDef.h"
#include "OSGScalarSortTreeBuilder.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemRenderingBackendTreeBuild
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING DepthSortTreeBuilder : public ScalarSortTreeBuilder
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef ScalarSortTreeBuilder  Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Constructors & Destructor                         */
    /*! \{                                                                 */

             DepthSortTreeBuilder(void);
    virtual ~DepthSortTreeBuilder(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Tree Operations                               */
    /*! \{                                                                 */

    virtual void add(RenderActionBase    *pAction,
                     RenderPartitionBase *pPart,
                     DrawFunctor         &drawFunc,
                     State               *pState,
                     StateOverride       *pStateOverride);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                                                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    DepthSortTreeBuilder(const DepthSortTreeBuilder &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =     (const DepthSortTreeBuilder &source);
};

OSG_END_NAMESPACE

#endif // _OSGDEPTHSORTTREEBUILDER_H_
