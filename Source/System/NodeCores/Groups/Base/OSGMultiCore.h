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

#ifndef _OSGMULTICORE_H_
#define _OSGMULTICORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiCoreBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiCore class. See \ref
    PageSystemMultiCore for a description.
    \ingroup GrpSystemNodeCoreGroupsCores
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING MultiCore : public MultiCoreBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiCoreBase                         Inherited;
    typedef MultiCore                             Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    UInt32 getNCores (void                     ) const;
    Int32  findCore  (NodeCore * const pCore   ) const;
    void   insertCore(UInt32           corendex, 
                      NodeCore * const coreP   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    const MFUnrecChildNodeCorePtr *getMFCores(      void        ) const;

          NodeCore                *getCores  (const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    void addCore         (      NodeCore                * const value   );
    void assignCoresFrom (const MFUnrecChildNodeCorePtr &       value   );
    void subCore         (      UInt32                          uiIndex );
    void subCoreByObj    (      NodeCore                * const value   );
    void clearCores      (      void                                    );

    void replaceCore     (      UInt32                          uiIndex,
                                NodeCore                * const value   );
    
    void replaceCoreByObj(      NodeCore                * const pOldElem,
                                NodeCore                * const pNewElem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrix &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MultiCoreBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiCore(void);
    MultiCore(const MultiCore &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiCore(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume    (Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter    (Action *action                 );
    ActionBase::ResultE renderLeave    (Action *action                 );

    ActionBase::ResultE actionEnterFrom(Action *action, NodeCore *pFrom);
    ActionBase::ResultE actionLeaveFrom(Action *action, NodeCore *pFrom);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiCoreBase;
    friend class Action;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiCore &source);
};

typedef MultiCore *MultiCoreP;

OSG_END_NAMESPACE

#include "OSGMultiCoreBase.inl"
#include "OSGMultiCore.inl"

#endif /* _OSGMULTICORE_H_ */
