/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGRENDERPARTITIONBASE_H_
#define _OSGRENDERPARTITIONBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGDrawTask.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class TreeBuilderBase;
class OcclusionCullingTreeBuilder;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief RenderPartition is the core class for keeping track of the actions 
           necessary to draw a scene. 

    \ingroup GrpSystemActionBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING RenderPartitionBase : public DrawTask
{
  public:

    typedef DrawTask Inherited;

    //-----------------------------------------------------------------------
    //   constants                                                             
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum CopyOnPush
    {
        CopyNothing       = 0x0000,

        CopyStateOverride = 0x0001,

        CopyViewing       = 0x0002,
        CopyProjection    = 0x0004,
        CopyVisibility    = 0x0008,

        CopyTarget        = 0x0010,
        CopyWindow        = 0x0020,

        CopyViewportSize  = 0x0040,
        CopyFrustum       = 0x0080,

        CopyNearFar       = 0x0100,

        CopyVPCamera      = 0x0200,

        CopyMatrix        = 0x0400,

        CopyAll           = 0xFFFF
    };

    enum Mode
    {
        StateSorting     = 0x0001,
        TransformSorting = 0x0002,
        SimpleCallback   = 0x0003,
        OcclusionCulling = 0x0004
    };

    enum SetupMode
    {
        EmptySetup      = 0x0000,
        ProjectionSetup = 0x0001,
        ViewportSetup   = 0x0002,
        BackgroundSetup = 0x0004,
        FullSetup       = 0x0007
    };

    enum SetupBit
    {
        PassiveBit = 0x00010000
    };

    static const UInt32 Setup   = Inherited::LastType + 1;
    static const UInt32 Execute = Inherited::LastType + 2;
    static const UInt32 Full    = Inherited::LastType + 3;

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    void setTaskType(UInt32 uiTaskType);

    /*------------------------- assignment ----------------------------------*/
    
    bool getCorrectNegScale(void     ) const;
    void setCorrectNegScale(bool bVal);

    bool getZWriteTrans    (void     ) const;
    void setZWriteTrans    (bool bVal);

    /*------------------------- comparison ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    // What to do
    bool     _bSortTrans;
    bool     _bZWriteTrans;
    bool     _bCorrectNegScale;
    UInt8    _ubState;

    // Stat
    UInt32   _uiNumMatrixChanges;
    UInt32   _uiNumTriangles;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    RenderPartitionBase(void);

    virtual ~RenderPartitionBase(void); 

    /*-------------------------- comparison ---------------------------------*/

    /*-------------------------- comparison ---------------------------------*/

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class TreeBuilderBase;
    friend class OcclusionCullingTreeBuilder;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------
   
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*!\brief prohibit default function (move to 'public' if needed) */
    RenderPartitionBase(const RenderPartitionBase &source);
    void operator =(const RenderPartitionBase &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include "OSGRenderPartitionBase.inl"

#endif /* _OSGRENDERPARTITIONBASE_H_ */


