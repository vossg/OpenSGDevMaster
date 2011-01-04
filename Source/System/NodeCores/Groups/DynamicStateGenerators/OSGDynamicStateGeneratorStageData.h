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

#ifndef _OSGDYNAMICSTATEGENERATORSTAGEDATA_H_
#define _OSGDYNAMICSTATEGENERATORSTAGEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicStateGeneratorStageDataBase.h"
#include "OSGFrameBufferObject.h"
#include "OSGState.h"

OSG_BEGIN_NAMESPACE

/*! \brief DynamicStateGeneratorStageData class. See \ref
           PageGroupDynamicStateGeneratorStageData for a description.
    \ingroup GrpGroupDynamicStateGeneratorsObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
*/

class OSG_GROUP_DLLMAPPING DynamicStateGeneratorStageData : 
    public DynamicStateGeneratorStageDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DynamicStateGeneratorStageDataBase Inherited;
    typedef DynamicStateGeneratorStageData     Self;

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

    bool addChunk(StateChunk *chunk, 
                  Int32       slot = State::AutoSlotReplace);

    bool subChunk(StateChunk *chunk, 
                  Int32       slot = State::AutoSlotReplace);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    MFUnrecStateChunkPtr::const_iterator beginChunks(void) const;
    MFUnrecStateChunkPtr::const_iterator endChunks  (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DynamicStateGeneratorStageDataBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DynamicStateGeneratorStageData(void);
    DynamicStateGeneratorStageData(
        const DynamicStateGeneratorStageData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynamicStateGeneratorStageData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    void pushToChunks(StateChunk * const value);
    void clearChunks (void                    );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DynamicStateGeneratorStageDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DynamicStateGeneratorStageData &source);
};

typedef DynamicStateGeneratorStageData *DynamicStateGeneratorStageDataP;

OSG_END_NAMESPACE

#include "OSGDynamicStateGeneratorStageDataBase.inl"
#include "OSGDynamicStateGeneratorStageData.inl"

#endif /* _OSGDYNAMICSTATEGENERATORSTAGEDATA_H_ */
