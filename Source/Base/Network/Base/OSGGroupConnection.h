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


#ifndef _GROUPCONNECTION_H_
#define _GROUPCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>
#include <set>

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGConnection.h"
#include "OSGTime.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkBase
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING GroupConnection : public Connection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             GroupConnection ( int zeroCopyThreshold );
    virtual ~GroupConnection ( void                  ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   type info                                  */
    /*! \{                                                                 */

    virtual const ConnectionType *getType (void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   connection                                 */
    /*! \{                                                                 */

    virtual void    disconnect  (      Channel     channel   ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   channel handling                           */
    /*! \{                                                                 */
    
    UInt32  getChannelCount  (void           );
    void    addSelection     (Channel channel);
    void    subSelection     (Channel channel);
    void    clearSelection   (void           );
    void    resetSelection   (void           );
    UInt32  getSelectionCount(void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   group address                              */
    /*! \{                                                                 */
    
    void        setDestination(const std::string &destination);
    std::string getDestination(void                          );

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                   protected fields                           */
    /*! \{                                                                 */

    std::vector<UInt8>        _selection;
    std::string               _destination;
    std::set<Channel>         _disconnectedChannel;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   protected types                            */
    /*! \{                                                                 */

    typedef Int32 ChannelIndex;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   internal channel handling                  */
    /*! \{                                                                 */

    Channel newChannelIndex(ChannelIndex index);
    void    delChannelIndex(ChannelIndex index);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   channel index mapping                      */
    /*! \{                                                                 */

    ChannelIndex channelToIndex (Channel      channel ) const;
    Channel      indexToChannel (ChannelIndex index   ) const;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name                   private fields                             */
    /*! \{                                                                 */

    std::vector<ChannelIndex> _channelToIndex;
    std::vector<Channel>      _indexToChannel;
    std::list<Channel>        _reuseChannel;

    /*! \}                                                                 */
    typedef Connection Inherited;

	// prohibit default functions (move to 'public' if you need one)
    GroupConnection(const GroupConnection &source);
    GroupConnection& operator =(const GroupConnection &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef GroupConnection *GroupConnectionP;

OSG_END_NAMESPACE

#endif /* _CONNECTION_H_ */
