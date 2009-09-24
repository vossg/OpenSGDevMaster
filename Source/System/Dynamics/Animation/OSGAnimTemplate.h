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

#ifndef _OSGANIMTEMPLATE_H_
#define _OSGANIMTEMPLATE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimTemplateBase.h"
#include "OSGAnimDataSource.h"

OSG_BEGIN_NAMESPACE

// forward decl
class Animation;
OSG_GEN_CONTAINERPTR(Animation);


/*! \brief AnimTemplate class. See \ref
           PageDynamicsAnimTemplate for a description.
*/

class OSG_DYNAMICS_DLLMAPPING AnimTemplate : public AnimTemplateBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimTemplateBase Inherited;
    typedef AnimTemplate     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Instantiate                                */
    /*! \{                                                                 */

    virtual AnimationTransitPtr instantiate(Node *rootNode) = 0;

    Int32 findTargetId(const std::string &targetId,
                             Int32        offset   = 0) const;

    Real32 getLength(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimTemplateBase.
    
    mutable Real32 _animLength;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimTemplate(void);
    AnimTemplate(const AnimTemplate &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimTemplate(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helpers                                   */
    /*! \{                                                                 */

    virtual void updateLength(void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimTemplateBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimTemplate &source);
};

typedef AnimTemplate *AnimTemplateP;

OSG_END_NAMESPACE

#include "OSGAnimTemplateBase.inl"
#include "OSGAnimTemplate.inl"

#endif /* _OSGANIMTEMPLATE_H_ */
