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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "OSGConfig.h"
#include "OSGGroupConnection.h"

OSG_BEGIN_NAMESPACE

/** \class OSG::GroupConnection
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

GroupConnection::GroupConnection(int zeroCopyThreshold):
    Connection(zeroCopyThreshold)
{
}

/*! Destructor
 */

GroupConnection::~GroupConnection(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            channel handling                             */

/*! number of connected channels
 */
UInt32 GroupConnection::getChannelCount(void)
{
    return _selection.size();
}

/*! mark the given channel as selectable
 */
void GroupConnection::addSelection(Channel channel)
{
    ChannelIndex index = _channelToIndex[channel];
    _selection[index] = true;
}

/*! mark the given channel as not selectable
 */
void GroupConnection::subSelection(Channel channel)
{
    ChannelIndex index = _channelToIndex[channel];
    _selection[index] = false;
}

/*! mark all channels as selectable
 */
void GroupConnection::clearSelection(void)
{
    std::fill(_selection.begin(),_selection.end(),false);
}

/*! mark all channels as not selectable
 */
void GroupConnection::resetSelection(void)
{
    std::fill(_selection.begin(),_selection.end(),true);
}

/*! get number of sockets in the selection
 */
UInt32 GroupConnection::getSelectionCount(void)
{
    UInt32 selectionCount=0;
    std::vector<UInt8>::iterator i;
    for(i=_selection.begin() ; i!=_selection.end() ; ++i)
        if(*i)
            selectionCount++;
    return selectionCount;
}

/*-------------------------------------------------------------------------*/
/*                           internal channel handling                     */

/*! set destination address used to broadcast or multicast to all
    connected points. On Multicast connections this could be 224.22.22.1 
    or something like that. 
 */
void GroupConnection::setDestination(const std::string &destination)
{
    _destination = destination;
}

/*! get destination address 
 */
std::string GroupConnection::getDestination(void)
{
    return _destination;
}

/*-------------------------------------------------------------------------*/
/*                           internal channel handling                     */

/*! create a new channel
 */
Connection::Channel GroupConnection::newChannelIndex(ChannelIndex index)
{
    Channel channel;
    if(_reuseChannel.begin() != _reuseChannel.end())
    {
        channel = *(_reuseChannel.begin());
        _reuseChannel.pop_front();
    }
    else
    {
        channel = _channelToIndex.size();
        _channelToIndex.resize(channel+1);
    }
    if(index >= static_cast<ChannelIndex>(_indexToChannel.size()))
        _indexToChannel.resize(index+1);
    if(index >= static_cast<ChannelIndex>(_selection.size()))
        _selection.resize(index+1);
    // enable selection
    _selection[index] = true;
    // set index to channel mapping
    _indexToChannel[index] = channel;
    // set channel to index mapping
    _channelToIndex[channel] = index;
    return channel;
}

/*! remove a channel. 
 */
void GroupConnection::delChannelIndex(ChannelIndex index)
{
    Channel channel = _indexToChannel[index];
    // erase from indexed arrays
    _selection     .erase(_selection.begin()      + index);
    _indexToChannel.erase(_indexToChannel.begin() + index);
    // move to reuse
    _reuseChannel.push_back(channel);
}

/*-------------------------------------------------------------------------*/
/*                      channel / index mapping                            */

GroupConnection::ChannelIndex 
    GroupConnection::channelToIndex(Channel channel) const
{
    return _channelToIndex[channel];
}

Connection::Channel GroupConnection::indexToChannel(ChannelIndex index) const
{
    return _indexToChannel[index];
}

OSG_END_NAMESPACE
