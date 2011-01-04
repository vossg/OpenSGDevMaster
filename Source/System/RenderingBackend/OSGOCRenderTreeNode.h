/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                    Copyright (C) 2010 by the OpenSG Forum                 *
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

#ifndef _OSGOCRENDERTREENODE_H_
#define _OSGOCRENDERTREENODE_H_

#include "OSGRenderTreeNode.h"
#include "OSGBoxVolume.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemRenderingBackendBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING OCRenderTreeNode : public RenderTreeNode
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef RenderTreeNode  Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name          Constructors & Destructor                           */
    /*! \{                                                                 */

             OCRenderTreeNode(void);
    virtual ~OCRenderTreeNode(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    void             setVolume    (const BoxVolume &vol      );
    const BoxVolume &getVolume    (void                      ) const;

    void             setResultNum (UInt32           resultNum);
    UInt32           getResultNum (void                      ) const;

    void             setIsRendered(bool             value    );
    bool             getIsRendered(void                      ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Reset                                    */
    /*! \{                                                                 */

    void reset(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    BoxVolume _bVol;
    UInt32    _resultNum;
    bool      _isRendered;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*! \brief prohibit default function (move to 'public' if needed) */
    OCRenderTreeNode(const OCRenderTreeNode &source);
    /*! \brief prohibit default function (move to 'public' if needed) */
    void operator =(const OCRenderTreeNode &source);
};

OSG_END_NAMESPACE

#include "OSGOCRenderTreeNode.inl"

#endif // _OSGOCRENDERTREENODE_H_
