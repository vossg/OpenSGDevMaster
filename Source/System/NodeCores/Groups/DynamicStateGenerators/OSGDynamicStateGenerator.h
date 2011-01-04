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

#ifndef _OSGDYNAMICSTATEGENERATOR_H_
#define _OSGDYNAMICSTATEGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicStateGeneratorBase.h"
#include "OSGFrameBufferObject.h"

OSG_BEGIN_NAMESPACE

/*! \brief DynamicStateGenerator class. See \ref
           PageGroupDynamicStateGenerator for a description.
    \ingroup GrpGroupDynamicStateGeneratorsObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
*/

class OSG_GROUP_DLLMAPPING DynamicStateGenerator : 
    public DynamicStateGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DynamicStateGeneratorBase Inherited;
    typedef DynamicStateGenerator     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    FrameBufferObject *getRenderTarget(void) const;

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

    // Variables should all be in DynamicStateGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DynamicStateGenerator(void);
    DynamicStateGenerator(const DynamicStateGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynamicStateGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Render                                  */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DynamicStateGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DynamicStateGenerator &source);
};

typedef DynamicStateGenerator *DynamicStateGeneratorP;

OSG_END_NAMESPACE

#include "OSGDynamicStateGeneratorBase.inl"
#include "OSGDynamicStateGenerator.inl"

#endif /* _OSGDYNAMICSTATEGENERATOR_H_ */
