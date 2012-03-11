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

#ifndef _OSGSTACKEDTRANSFORM_H_
#define _OSGSTACKEDTRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStackedTransformBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief StackedTransform class. See \ref
           PageGroupStackedTransform for a description.
*/

class OSG_GROUP_DLLMAPPING StackedTransform : public StackedTransformBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef StackedTransformBase Inherited;
    typedef StackedTransform     Self;

    static std::string TranslateName;
    static std::string RotateXName;
    static std::string RotateYName;
    static std::string RotateZName;
    static std::string ScaleName;

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
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrix &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    TransformationElement *getElement(const std::string &szName) const;

    template <typename ElementType>
    ElementType           *getElement(const std::string &szName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    void pushToNamedTransformElements      (
        TransformationElement       * const pValue,
        std::string           const &       szName);

    void insertIntoNamedTransformElements  (
        UInt32               uiIndex,
        TransformationElement       * const pValue,
        std::string           const &       szName);

    void replaceInNamedTransformElements   (
        UInt32                              uiIndex,
        TransformationElement       * const pValue,
        std::string           const &       szName);

    void replaceObjInNamedTransformElements(
        TransformationElement       * const pOldElem,
        TransformationElement       * const pNewElem,
        std::string           const &       szName);

    void removeFromNamedTransformElements  (
        std::string           const &       szName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in StackedTransformBase.

    Matrix _mTransformation;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StackedTransform(void);
    StackedTransform(const StackedTransform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StackedTransform(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume    (Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Intersect & Render                              */
    /*! \{                                                                 */

    Action::ResultE intersectEnter     (Action *action);
    Action::ResultE intersectLeave     (Action *action);

    Action::ResultE renderEnter        (Action *action);
    Action::ResultE renderLeave        (Action *action);

    void            updateTransform    (void          );
    void            invalidateTransform(void          );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class StackedTransformBase;
    friend class TransformationElement;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StackedTransform &source);
};

typedef StackedTransform *StackedTransformP;

OSG_END_NAMESPACE

#include "OSGStackedTransformBase.inl"
#include "OSGStackedTransform.inl"

#endif /* _OSGSTACKEDTRANSFORM_H_ */
