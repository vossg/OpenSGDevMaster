/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGBOOSTPATHATTACHMENT_H_
#define _OSGBOOSTPATHATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBoostPathAttachmentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief BoostPathAttachment class. See \ref
           PageBoostPathAttachment for a description.
*/

class OSG_SYSTEM_DLLMAPPING BoostPathAttachment : public BoostPathAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef BoostPathAttachmentBase Inherited;
    typedef BoostPathAttachment     Self;

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
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FilePathAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BoostPathAttachment(void);
    BoostPathAttachment(const BoostPathAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BoostPathAttachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BoostPathAttachmentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const BoostPathAttachment &source);
};

typedef BoostPathAttachment *BoostPathAttachmentP;

const BoostPath *getBoostPath(const AttachmentContainer *pContainer);

      void       setBoostPath(      AttachmentContainer *pContainer, 
                              const BoostPath           &oPath     );

OSG_END_NAMESPACE

#include "OSGBoostPathAttachmentBase.inl"
#include "OSGBoostPathAttachment.inl"

#endif /* _OSGBOOSTPATHATTACHMENT_H_ */
