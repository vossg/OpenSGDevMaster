/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifndef _OSGFIELDCONNECTOR_H_
#define _OSGFIELDCONNECTOR_H_

#include "OSGBaseDef.h"

OSG_BEGIN_NAMESPACE

class Field;

/*! \ingroup GrpBaseFieldContainerConnector
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING BasicFieldConnector
{
  public:

    BasicFieldConnector(BitVector bSrcMask,
                        BitVector bDstMask);

    virtual ~BasicFieldConnector(void);

    void setTargetContainer(FieldContainer *pDst);

    bool match(BitVector fieldMask);

    bool match(      BitVector       bSrcMask,
               const FieldContainer *pDst,
                     BitVector       bDstMask);

    virtual void process(void) = 0;

    FieldContainer *getDst(void) const;

    virtual BasicFieldConnector *clone(const Field     *pSrcField,
                                             BitVector  bSrcMask,
                                             Field     *pDstField,
                                             BitVector  bDstMask) = 0;

  protected:

    BitVector       _bSrcMask;
    BitVector       _bDstMask;

    FieldContainer *_pDst;
};

/*! \ingroup GrpBaseFieldContainerConnector
    \ingroup GrpLibOSGBase
 */

template <class SrcFieldT, class DstFieldT>
class SFieldConnector : public BasicFieldConnector
{
    typedef BasicFieldConnector                   Inherited;
    typedef SFieldConnector<SrcFieldT, DstFieldT> Self;

  public:

    SFieldConnector(const SrcFieldT *pSrcField,
                          BitVector  bSrcMask,
                          DstFieldT *pDstField,
                          BitVector  bDstMask);

    virtual ~SFieldConnector(void);

    virtual void process(void);

    virtual BasicFieldConnector *clone(const Field     *pSrcField,
                                             BitVector  bSrcMask,
                                             Field     *pDstField,
                                             BitVector  bDstMask);

  protected:
    
    const SrcFieldT *_pSrcField;
          DstFieldT *_pDstField;
};

/*! \ingroup GrpBaseFieldContainerConnector
    \ingroup GrpLibOSGBase
 */

template <class SrcFieldT, class DstFieldT>
class MFieldConnector : public BasicFieldConnector
{
    typedef BasicFieldConnector                   Inherited;
    typedef MFieldConnector<SrcFieldT, DstFieldT> Self;

  public:

    MFieldConnector(const SrcFieldT *pSrcField,
                          BitVector  bSrcMask,
                          DstFieldT *pDstField,
                          BitVector  bDstMask);

    virtual ~MFieldConnector(void);

    virtual void process(void);

    virtual BasicFieldConnector *clone(const Field     *pSrcField,
                                             BitVector  bSrcMask,
                                             Field     *pDstField,
                                             BitVector  bDstMask);

  protected:
    
    const SrcFieldT *_pSrcField;
          DstFieldT *_pDstField;
};

OSG_BASE_DLLMAPPING
bool addConnection(      OSG::AttachmentContainer *pSrcContainer, 
                   const OSG::Char8               *szSrcName,
                         OSG::FieldContainer      *pDstContainer, 
                   const OSG::Char8               *szDstName    );

OSG_BASE_DLLMAPPING
bool subConnection(      OSG::AttachmentContainer *pSrcContainer, 
                   const OSG::Char8               *szSrcName,
                         OSG::FieldContainer      *pDstContainer, 
                   const OSG::Char8               *szDstName);


OSG_END_NAMESPACE

#include "OSGFieldConnector.inl"

#endif
