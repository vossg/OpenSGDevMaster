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

  protected:

    BitVector       _bSrcMask;
    BitVector       _bDstMask;

    FieldContainer *_pDst;
};


template <class FieldT>
class SFieldConnector : public BasicFieldConnector
{
    typedef BasicFieldConnector Inherited;

  public:

    SFieldConnector(const FieldT    *pSrcField,
                          BitVector  bSrcMask,
                          FieldT    *pDstField,
                          BitVector  bDstMask);

    virtual ~SFieldConnector(void);

    virtual void process(void);

  protected:
    
    const FieldT    *_pSrcField;

    
          FieldT    *_pDstField;
};

template <class FieldT>
class MFieldConnector : public BasicFieldConnector
{
    typedef BasicFieldConnector Inherited;

  public:

    MFieldConnector(const FieldT    *pSrcField,
                          BitVector  bSrcMask,
                          FieldT    *pDstField,
                          BitVector  bDstMask);

    virtual ~MFieldConnector(void);

    virtual void process(void);

  protected:
    
    const FieldT    *_pSrcField;

    
          FieldT    *_pDstField;
};

OSG_BASE_DLLMAPPING
bool addConnection(AttachmentContainer *pSrcContainer, const Char8 *szSrcName,
                   FieldContainer      *pDstContainer, const Char8 *szDstName);

OSG_BASE_DLLMAPPING
bool subConnection(AttachmentContainer *pSrcContainer, const Char8 *szSrcName,
                   FieldContainer      *pDstContainer, const Char8 *szDstName);


OSG_END_NAMESPACE

#include "OSGFieldConnector.inl"

#endif
