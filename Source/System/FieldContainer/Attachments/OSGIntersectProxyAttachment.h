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

#ifndef _OSGINTERSECTPROXYATTACHMENT_H_
#define _OSGINTERSECTPROXYATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGIntersectProxyAttachmentBase.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

/*! \brief IntersectProxyAttachment class. See \ref
           PageSystemIntersectProxyAttachment for a description.
*/

class OSG_SYSTEM_DLLMAPPING IntersectProxyAttachment : public IntersectProxyAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef IntersectProxyAttachmentBase Inherited;
    typedef IntersectProxyAttachment     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                    Intersect                                 */
    /*! \{                                                                 */

    virtual Action::ResultE intersectEnter(Node* node, Action* action) = 0;

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

    // Variables should all be in IntersectProxyAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    IntersectProxyAttachment(void);
    IntersectProxyAttachment(const IntersectProxyAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~IntersectProxyAttachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class IntersectProxyAttachmentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const IntersectProxyAttachment &source);
};

typedef IntersectProxyAttachment *IntersectProxyAttachmentP;

OSG_END_NAMESPACE

#include "OSGIntersectProxyAttachmentBase.inl"
#include "OSGIntersectProxyAttachment.inl"

#endif /* _OSGINTERSECTPROXYATTACHMENT_H_ */
