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

#ifndef _OSGCONNECTORATTACHMENT_H_
#define _OSGCONNECTORATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConnectorAttachmentBase.h"

OSG_BEGIN_NAMESPACE

class BasicFieldConnector;

/*! \ingroup GrpBaseFieldContainerConnector
    \ingroup GrpLibOSGBase
    \includebasedoc
 */

class OSG_BASE_DLLMAPPING ConnectorAttachment : 
    public ConnectorAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ConnectorAttachmentBase Inherited;
    typedef ConnectorAttachment     Self;

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

    void addConnection  (BasicFieldConnector *pConnector);

    void processChanged (FieldContainer      *pObj, 
                         BitVector            whichField,
                         UInt32               origin    );

    void targetDestroyed(FieldContainer      *pObj, 
                         BitVector            whichField,
                         UInt32               origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool hasConnectionTo   (const FieldContainer *pDst) const;
    void removeConnectionTo(const FieldContainer *pDst); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void removeConnections(      BitVector       bSrcMask,
                           const FieldContainer *pDst,
                                 BitVector       bDstMask);  

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::vector<BasicFieldConnector *> ConnectionStore;
    typedef std::map   <FieldContainer *, 
                        UInt32               > ConnectionCount;

    // Variables should all be in ConnectorAttachmentBase.

    ConnectionStore _vConnections;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ConnectorAttachment(void);
    ConnectorAttachment(const ConnectorAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ConnectorAttachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual bool unlinkParent(FieldContainer * const pParent,
                              UInt16           const parentFieldId);

    virtual void resolveLinks(void                                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void countConnections(ConnectionCount &mCount);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ConnectorAttachmentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ConnectorAttachment &source);
};

typedef ConnectorAttachment *ConnectorAttachmentP;

OSG_BASE_DLLMAPPING
void addConnector(OSG::AttachmentContainer *pContainer,
                  OSG::BasicFieldConnector *pConn     );

OSG_BASE_DLLMAPPING
void subConnector(OSG::AttachmentContainer *pSrcContainer, 
                  OSG::BitVector            bSrcMask,
                  OSG::FieldContainer      *pDstContainer, 
                  OSG::BitVector            bDstMask     );

OSG_END_NAMESPACE

#include "OSGConnectorAttachmentBase.inl"
#include "OSGConnectorAttachment.inl"

#endif /* _OSGCONNECTORATTACHMENT_H_ */
