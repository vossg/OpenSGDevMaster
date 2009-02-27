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


#ifndef _GROUPSOCKPIPELINE_H_
#define _GROUPSOCKPIPELINE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGGroupSockConnection.h"
#include "OSGTime.h"
#include "OSGStreamSocket.h"
#include "OSGDgramQueue.h"

OSG_BEGIN_NAMESPACE

class PointSockPipeline;

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING GroupSockPipeline : 
    public GroupSockConnection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             GroupSockPipeline ( void );
    virtual ~GroupSockPipeline ( void ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   type info                                  */
    /*! \{                                                                 */

    virtual const ConnectionType *getType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   connection                                 */
    /*! \{                                                                 */

    virtual Channel     connectPoint(const std::string &address,
                                           Time        timeout=-1 );
    virtual void        disconnect  (      Channel     channel    );
    virtual Channel     acceptPoint (      Time        timeout=-1 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   create                                     */
    /*! \{                                                                 */

    static GroupConnection *create(void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Members                                    */
    /*! \{                                                                 */

    StreamSocket               _next;
    bool                       _initialized;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   IO Implementation                          */
    /*! \{                                                                 */

    virtual void write            (MemoryHandle mem, UInt32 size);
    virtual void writeBuffer      (void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class PointSockPipeline;
    
    /*---------------------------------------------------------------------*/
    /*! \name               private helpers                                */
    /*! \{                                                                 */

    void initialize(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   static members                             */
    /*! \{                                                                 */

    static ConnectionType _type;

    /*! \}                                                                 */

    typedef GroupSockConnection Inherited;

	// prohibit default functions (move to 'public' if you need one)
    GroupSockPipeline(const GroupSockPipeline &source);
    GroupSockPipeline& operator =(const GroupSockPipeline &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef GroupSockPipeline *GroupSockPipelineP;

OSG_END_NAMESPACE

#endif /* _GROUPSOCKPIPELINE_H_ */
