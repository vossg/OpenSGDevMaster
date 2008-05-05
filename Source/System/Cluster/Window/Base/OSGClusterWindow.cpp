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

#include <stdlib.h>
#include <stdio.h>

#include <sstream>

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGClusterWindow.h"
#include "OSGDgramSocket.h"
#include "OSGStreamSocket.h"
#include "OSGRemoteAspect.h"
#include "OSGConnection.h"
#include "OSGBinaryMessage.h"
#include "OSGRemoteAspect.h"
#include "OSGConnectionFactory.h"
#include "OSGClusterNetwork.h"
#include "OSGGroupSockConnection.h"

#if 0
#include "OSGDisplayCalibration.h"
#include "OSGImageComposer.h"
#endif

OSG_USING_NAMESPACE

/** \class OSG::ClusterWindow
 *  \ingroup GrpSystemCluster
 *  \brief Abstract base class for cluster configurations
 *
 * A ClusterWindow describes a clustering algorithm. A ClusterWindow
 * inherits the ability to connect rendering servers and initiate
 * remote rendering. By configuring the cluster algorithm with an
 * OpenSG Window structure, it is possible to use cluster rendering
 * in the same way as rendering in a GLUT or Qt window.
 *
 **/

/*-------------------------------------------------------------------------*/
/*                          window functions                               */

//! react to field changes

void ClusterWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes

void ClusterWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ClusterWindow NI" << std::endl;
}

void (*ClusterWindow::getFunctionByName(const Char8 *))()
{
    return NULL;
}

/*! init cluster window. connect to all servers
 */

void ClusterWindow::init(void)
{
    GroupConnection    *connection;
    RemoteAspect       *remoteAspect;
    int                 c,i,id;
    MFString::const_iterator  s;
    Connection::Channel channel;
    bool                directConnect=false;

    if(getNetwork()->getMainConnection())
    {
        SWARNING << "init called twice" << std::endl;
        return;
    }

    // create connection
    if(getConnectionType().empty())
    {
        setConnectionType("StreamSock");
    }

    connection = ConnectionFactory::the()->createGroup(getConnectionType());

    if(connection == NULL)
    {
        SFATAL << "Unknown connection type " 
               << getConnectionType() 
               << std::endl;
        return;
    }

    connection->setDestination(getConnectionDestination());
    connection->setInterface  (getConnectionInterface  ());
    connection->setParams     (getConnectionParams     ());

    getNetwork()->setMainConnection(connection);

    // create remote aspect

    remoteAspect = new RemoteAspect();

    getNetwork()->setAspect(remoteAspect);

    if(_statistics)
        remoteAspect->setStatistics(_statistics);

    // autostart servers
    std::string server;
    std::string autostart;
    std::string env;

    Real32 progress = 0.0f;
    Real32 progressStep = 1.0f / Real32(getMFServers()->size());

    if(getMFAutostart()->size())
    {
        progressStep /= 2;
        std::vector<FILE*>           pipes;

        for(id=0 ; id<getMFServers()->size() ; ++id)
        {
            std::ostringstream command;

            server    = (*getMFServers())[id];
            int pos=server.find(":");
            if(pos>=0)
                server.erase(pos);

            autostart = (*getMFAutostart())[id % getMFAutostart()->size()];

            for(c = 0 ; c < autostart.length() ; ++c)
            {
                if(autostart[c] == '%' && c+1 < autostart.length())  
                    switch(autostart[++c])
                    {
                        case 's': 
                            command << server;
                            break;
                        case 'n': 
                            command << (*getMFServers())[id];
                            break;
                        case 'i':
                            command << id;
                            break;
                        case '{':
                            env = "" ;
                            while(++c < autostart.length() &&
                                  autostart[c] != '}')
                                env += autostart[c];
                            if(getenv(env.c_str()))
                                command << getenv(env.c_str());
                            break;
                        case '%':
                            command << '%';
                            break;
                        default:
                            command << '%' << autostart[c];
                    }
                else
                    command << autostart[c];
            } 
            SINFO << command.str() << std::endl;
#ifdef WIN32
            FILE *pipe = _popen(command.str().c_str(),"r");
#else
            FILE *pipe = popen(command.str().c_str(),"r");
#endif
            if(!pipe)
                SFATAL << "Error starting: " << command << std::endl;
            pipes.push_back(pipe);
        }

        for(id = 0 ; id < getMFServers()->size() ; ++id)
        {
            if(pipes[id]) 
            {
                // update progress
                if(_connectionFP != NULL)
                {
                    std::string message;
                    message += "Starting:" + (*getMFServers())[id]; 

                    if(!_connectionFP(message, progress))
                    {
                        // abort, cleanup remaining pipes
                        for( ; id<getMFServers()->size() ; ++id)
                        {
                            if(pipes[id]) 
                            {
#ifdef WIN32
                                _pclose(pipes[id]);
#else
                                pclose(pipes[id]);
#endif
                            }
                            throw AsyncCancel();
                        }
                    }
                }
                SINFO << "Waiting for " 
                      << getServers(id) 
                      << " to start."
                      << std::endl;

                int result;
                std::string line="";

                while((result=fgetc(pipes[id])) != EOF)
                {
                    line += result;

                    if(result == '\n')
                    {
                        SINFO << line;
                        line = "";
                    }
                }

                if(!line.empty())
                    SINFO << line << std::endl;
#ifdef WIN32
                _pclose(pipes[id]);
#else
                pclose(pipes[id]);
#endif
                SINFO << getServers(id) << " started." << std::endl;

                progress += progressStep;
            }
        }
    }

    // connect to all servers
    for(s = getMFServers()->begin();
        s!= getMFServers()->end();
        s++)
    {
        DgramSocket      serviceSock;
        BinaryMessage    msg;
        std::string      respServer;
        std::string      respAddress;
        bool             retry=true;

        if(strstr((*s).c_str(),":"))
            directConnect = true;
        else
            directConnect = false;

        SINFO << "Connect to " << (*s) << std::endl;

        serviceSock.open();
        serviceSock.setTTL(8);

        // set interface
        if(!getServiceInterface().empty())
        {
            serviceSock.setMCastInterface(
                SocketAddress(getServiceInterface().c_str()));
        }

        while(retry)
        {
            try
            {
                // update progress
                if(_connectionFP != NULL)
                {
                    std::string message;
                    message += "Connecting:" + *s; 
                    if(!_connectionFP(message, progress))
                    {
                        serviceSock.close();
                        throw AsyncCancel();
                    }
                }

                // try to connect with the servers name
                try 
                {
                    if(directConnect)
                    {
                        channel = connection->connectPoint(*s,0.5);
                        if(channel >= 0) 
                        {
                            retry = false;
                            
                            SINFO << "Connected with address:" 
                                  << *s
                                  << std::endl;
                            break;
                        }
                    }
                }
                catch(...)
                {
                }

                // find server
                msg.clear();
                msg.putString(*s);
                msg.putString(getConnectionType());
                    
                if(_sfServiceAddress.getValue().size() != 0)
                {
                    SINFO << "send request to:" 
                          << _sfServiceAddress.getValue()
                          << std::endl;
                    
                    serviceSock.sendTo(
                        msg,SocketAddress(
                            _sfServiceAddress.getValue().c_str(),
                            getServicePort()));
                }
                SINFO << "send request to:" 
                      << SocketAddress(SocketAddress::BROADCAST,
                                       getServicePort()).getHost().c_str()
                      << std::endl;

                serviceSock.sendTo(
                    msg,SocketAddress(SocketAddress::BROADCAST,
                                      getServicePort()));

                if(serviceSock.waitReadable(0.1))
                {
                    SocketAddress from;
                    serviceSock.recvFrom(msg, from);
                    msg.getString(respServer);
                    msg.getString(respAddress);

                    if(respServer == *s)
                    {
                        GroupSockConnection *pointSock =
                            dynamic_cast<GroupSockConnection*> (connection);

                        if(pointSock != NULL)
                        {
                            /* for all socket connections ignore the
                               incomming host and use the host from
                               the last response. */

                            char port[16];

                            if(sscanf(respAddress.c_str(),
                                      "%*[^:]:%15s",port) == 1)
                            {
                                respAddress = from.getHost() + ":" + port;
                            }
                        }

                        SINFO << "Found at address "
                              << respAddress
                              << std::endl;

                        // connect to server
                        channel = connection->connectPoint(respAddress);

                        if(channel >= 0)
                            retry=false;
                    }
                }
            }
            catch(AsyncCancel &)
            {
                throw;
            }
            catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
            {
                SINFO << e.what() << std::endl;
            }
        }

        serviceSock.close();

        progress += progressStep;
    }

    // determine byte order
    UInt8 serverLittleEndian;
    UInt8 forceNetworkOrder=false;
#if BYTE_ORDER == LITTLE_ENDIAN
    UInt8 littleEndian = true;
#else
    UInt8 littleEndian = false;
#endif

    for(UInt32 i=0;i<getMFServers()->size();++i)
    {
        channel = connection->selectChannel();
        connection->subSelection(channel);
        connection->getValue(serverLittleEndian);

        if(serverLittleEndian != littleEndian)
        {
            forceNetworkOrder=true;
        }
    }
    connection->resetSelection();
    // tell the servers the encoding mode
    connection->putValue(forceNetworkOrder);
    connection->flush();
    connection->setNetworkOrder((forceNetworkOrder != 0));

    if(forceNetworkOrder)
    {
        SINFO << "Run clustering in network order mode" << std::endl;
    }

    // inform connection finished
    if(_connectionFP != NULL)
        _connectionFP("ok", 1.0);
}

bool ClusterWindow::initAsync(connectioncbfp fp)
{
    bool result;
    connectioncbfp saveFP = _connectionFP;

    _connectionFP = fp;

    try 
    {
        init();
        result = true;
    }
    catch(AsyncCancel &e)
    {
        result = false;
    }
    _connectionFP = saveFP;

    return result;
}

void ClusterWindow::setConnectionCB(connectioncbfp fp)
{
    _connectionFP = fp;
}

#ifdef OSG_OLD_RENDER_ACTION
void ClusterWindow::render(DrawActionBase *action)
{
    activate();
    frameInit();
    renderAllViewports(action);
    swap();
    frameExit();
}
#endif

void ClusterWindow::render(RenderActionBase *action)
{
    activate();
    frameInit();
    renderAllViewports(action);
    swap();
    frameExit();
}

void ClusterWindow::activate(void)
{
}

void ClusterWindow::deactivate(void)
{
}

bool ClusterWindow::swap(void)
{
    if(getNetwork()->getMainConnection() && getNetwork()->getAspect())
    {
        clientSwap();
    }

    return true;
}

#ifdef OSG_OLD_RENDER_ACTION
void ClusterWindow::renderAllViewports(DrawActionBase *action)
{
    if(getNetwork()->getMainConnection() && getNetwork()->getAspect())
    {
        clientRender(action);
    }
}
#endif

void ClusterWindow::renderAllViewports(RenderActionBase *action)
{
    if(getNetwork()->getMainConnection() && getNetwork()->getAspect())
    {
        clientRender(action);
    }
}

void ClusterWindow::frameInit(void)
{
    Connection   *connection   = getNetwork()->getMainConnection();
    RemoteAspect *remoteAspect = getNetwork()->getAspect();

    if(remoteAspect && connection)
    {
        if(_firstFrame)
        {
            setFrameCount(0);

            // send sync

            commitChanges();
            remoteAspect->sendSync(*connection);

            ChangeList *cl = ChangeList::create();

            cl->clear();
            cl->merge(*Thread::getCurrentChangeList());

            Thread::getCurrentChangeList()->clear();

            // init client window
            clientInit();
            // last chance to modifie before sync
            clientPreSync();
            // send sync
            commitChanges();
            remoteAspect->sendSync(*connection);

//            cl.merge(*Thread::getCurrentChangeList());
//            Thread::getCurrentChangeList()->clear();
            Thread::getCurrentChangeList()->merge(*cl);

            OSG::subRef(cl);

            _firstFrame = false;
        }
        else
        {
            setFrameCount(getFrameCount() + 1);
            clientPreSync();

            commitChanges();
            remoteAspect->sendSync(*connection);
        }
    }
}

void ClusterWindow::frameExit(void)
{
}

/*-------------------------------------------------------------------------*/
/*                          statistics                                     */

void ClusterWindow::setStatistics(StatCollector *statistics)
{
    _statistics = statistics;
    if(getNetwork()->getAspect())
        getNetwork()->getAspect()->setStatistics(statistics);
}

/*-------------------------------------------------------------------------*/
/*                          calibration                                    */

#if 0
/*! load color and projection calibration file from xml
 */
bool ClusterWindow::loadCalibration(std::istream &in)
{
    ClusterWindowPtr ptr(this);
    DisplayCalibrationPtr calibPtr;
    xmlpp::xmlcontextptr ctxptr(new xmlpp::xmlcontext());
    xmlpp::xmldocument doc(ctxptr);
    xmlpp::xmlnodelist servers;
    xmlpp::xmlnodelist colors;
    xmlpp::xmlnodelist points;
    xmlpp::xmlnodelist rows;
    xmlpp::xmlnodelist::const_iterator sI;
    xmlpp::xmlnodelist::const_iterator nI;
    xmlpp::xmlnodelist::const_iterator cI;
    xmlpp::xmlnodelist::const_iterator rI;
    xmlpp::xmlnodelist::const_iterator pI;
    xmlpp::xmlstring serverTag("server");
    xmlpp::xmlstring colorTag("color");
    xmlpp::xmlstring rowTag("row");
    xmlpp::xmlstring pointTag("point");
    Matrix colorMatrix;
    Real32 gamma;
    xmlpp::xmlnodeptr nP;

    getCalibration().clear();
    try
    {
        doc.load(in,ctxptr);
        servers = doc.select_nodes(serverTag);
        // loop through servers
        for(sI = servers.begin() ; sI != servers.end(); ++sI)
        {
            // create new calibration structure
            calibPtr = DisplayCalibration::create();

            addRef(calibPtr);

            getCalibration().push_back(calibPtr);

            // server name
            if((*sI)->get_attrmap().count("name"))
                calibPtr->setServer((*sI)->get_attrmap()["name"]);
            
            // loop over childs
            for(nI  = (*sI)->get_nodelist().begin();
                nI != (*sI)->get_nodelist().end(); 
                ++nI) 
            {
                if((*nI)->get_name() == "colormatrix")
                {
                    nP = (*nI);
                    do
                        nP = nP->get_nodelist().front();
                    while (nP->get_nodelist().size() == 1);
                    if(nP->get_type() == xmlpp::xml_nt_cdata) 
                        calibPtr->getColorMatrix().setValue(nP->get_cdata().c_str());
                }

                if((*nI)->get_name() == "scaledown")
                {
                    nP = (*nI);
                    do
                        nP = nP->get_nodelist().front();
                    while (nP->get_nodelist().size() == 1);
                    if(nP->get_type() == xmlpp::xml_nt_cdata) 
                        sscanf(nP->get_cdata().c_str(),"%f",&calibPtr->getScaleDown());
                }

                if((*nI)->get_name() == "gamma")
                {
                    nP = (*nI);
                    do
                        nP = nP->get_nodelist().front();
                    while (nP->get_nodelist().size() == 1);
                    if(nP->get_type() == xmlpp::xml_nt_cdata) 
                        sscanf(nP->get_cdata().c_str(),"%f",&calibPtr->getGamma());
                }

                if((*nI)->get_name() == "gammaramp")
                {
                    colors = (*nI)->select_nodes(colorTag);
                    for(cI = colors.begin() ; cI != colors.end(); ++cI)
                    {   
                        nP = (*cI);
                        do
                            nP = nP->get_nodelist().front();
                        while (nP->get_nodelist().size() == 1);
                        if(nP->get_type() == xmlpp::xml_nt_cdata) 
                        {
                            Color3f col;
                            col.setValue(nP->get_cdata().c_str());
                            calibPtr->getGammaRamp().push_back(col);
                        }
                    }
                }
                if((*nI)->get_name() == "grid")
                {
                    rows = (*nI)->select_nodes(rowTag);
                    calibPtr->getGridHeight() = 0;
                    for(rI = rows.begin() ; rI != rows.end(); ++rI)
                    {   
                        calibPtr->getGridHeight()++;
                        calibPtr->getGridWidth() = 0;
                        points = (*rI)->select_nodes(pointTag);
                        for(pI = points.begin() ; pI != points.end(); ++pI)
                        {   
                            nP = (*pI);
                            do
                                nP = nP->get_nodelist().front();
                            while (nP->get_nodelist().size() == 1);
                            if(nP->get_type() == xmlpp::xml_nt_cdata) 
                            {
                                Vec2f pos;
                                calibPtr->getGridWidth()++;
                                pos.setValueFromCString(nP->get_cdata().c_str());
                                calibPtr->getGrid().push_back(pos);
                            }
                        }
                    }
                }
            }
        }
    }
    catch (xmlpp::xmlerror e)
    {
        // parser error
        xmlpp::xmllocation where( ctxptr->get_location() );
        xmlpp::xmlstring errmsg( e.get_strerror() );
        SFATAL << "XML error line " << where.get_line() << " "
               << "at position " << where.get_pos()
               << ": error: " << errmsg.c_str()
               << std::endl;
        return false;
    }
    return true;
}

/*! save color and projection calibration file to xml
 */
bool ClusterWindow::saveCalibration(std::ostream &out)
{
    DisplayCalibrationPtr calibPtr;
    UInt32 c;
    UInt32 color,row,col,pos;

    out << "<?xml version=\"1.0\"?>\n"
        << "<displaycalibration>\n";

    for(c = 0; c < getCalibration().size(); ++c)
    {
        calibPtr = getCalibration()[0];

        out << "<server name=\"" << calibPtr->getServer() << "\">\n";
        out << "<gamma>" << calibPtr->getGamma() << "</gamma>\n";
        out << "<scaledown>" << calibPtr->getScaleDown() << "</scaledown>\n";
        out << "<colormatrix>\n"
            << calibPtr->getColorMatrix()
            << "</colormatrix>\n";
        out << "<gammaramp>\n";

        for(color=0 ; color< calibPtr->getGammaRamp().size() ; ++color)
        {
            out << "<color>" 
                << calibPtr->getGammaRamp()[color] 
                << "</color>\n";
        }

        out << "</gammaramp>\n";
        out << "<grid>\n";

        for(row=0 ; row< calibPtr->getGridHeight() ; ++row)
        {
            out << "<row>\n";

            for(col=0 ; col< calibPtr->getGridWidth() ; ++col)
            {
                pos = row*calibPtr->getGridHeight()+col;
                out << "<point>";

                if(pos < calibPtr->getGrid().size())
                {
                    out << calibPtr->getGrid()[pos][0] << " "
                        << calibPtr->getGrid()[pos][1];
                }
                else
                {
                    out << col << " " << row;
                }

                out << "</point>\n";
            }

            out << "</row>\n";
        }

        out << "</grid>\n";
        out << "</server>\n";
    }

    out << "</displaycalibration>\n";

    return true;
}

bool ClusterWindow::loadFilter(std::istream &in)
{
    ClusterWindowPtr ptr(this);
    DisplayFilterForegroundPtr filterFgnd;
    ColorDisplayFilterPtr colorFilter;
    DistortionDisplayFilterPtr distortionFilter;
    ResolutionDisplayFilterPtr resolutionFilter;
    xmlpp::xmlcontextptr ctxptr(new xmlpp::xmlcontext());
    xmlpp::xmldocument doc(ctxptr);
    xmlpp::xmlnodelist servers;
    xmlpp::xmlnodelist colors;
    xmlpp::xmlnodelist points;
    xmlpp::xmlnodelist::const_iterator sI;
    xmlpp::xmlnodelist::const_iterator fI;
    xmlpp::xmlnodelist::const_iterator nI;
    xmlpp::xmlnodelist::const_iterator cI;
    xmlpp::xmlnodelist::const_iterator pI;
    xmlpp::xmlstring serverTag("server");
    xmlpp::xmlstring colorTag("color");
    xmlpp::xmlstring pointTag("point");
    xmlpp::xmlnodeptr nP;
    
    beginEditCP(ptr, FilterFieldMask | DirtyFieldMask);
        getFilter().clear();
        setDirty(true);
    endEditCP(ptr, FilterFieldMask | DirtyFieldMask);
    
    try
    {
        doc.load(in, ctxptr);
        servers = doc.select_nodes(serverTag);
        
        // loop through servers
        for(sI = servers.begin(); sI != servers.end(); ++sI)
        {
            // create new display filter foreground
            filterFgnd = DisplayFilterForeground::create();
            addRefCP(filterFgnd);
            
            beginEditCP(ptr, FilterFieldMask);
                getFilter().push_back(filterFgnd);
            endEditCP(ptr, FilterFieldMask);
            
            beginEditCP(filterFgnd);
            
            // server name
            if((*sI)->get_attrmap().count("name"))
                filterFgnd->setServer((*sI)->get_attrmap()["name"]);
            
            // loop over outer children, i.e. the filters
            for(fI  = (*sI)->get_nodelist().begin();
                fI != (*sI)->get_nodelist().end(); ++fI)
            {
                if ((*fI)->get_name() == "colordisplayfilter")
                {
                    colorFilter = ColorDisplayFilter::create();
                    addRefCP(colorFilter);
                    
                    filterFgnd->getFilter().push_back(colorFilter);
                    
                    beginEditCP(colorFilter);
                    
                    // loop over inner children, i.e. the params
                    for(nI  = (*fI)->get_nodelist().begin();
                        nI != (*fI)->get_nodelist().end(); ++nI) 
                    {
                        if((*nI)->get_name() == "colormatrix")
                        {
                            nP = (*nI);
                            do
                                nP = nP->get_nodelist().front();
                            while (nP->get_nodelist().size() == 1);
                            
                            if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                colorFilter->getMatrix().setValue(nP->get_cdata().c_str());
                        }
                        if((*nI)->get_name() == "gamma")
                        {
                            nP = (*nI);
                            do
                                nP = nP->get_nodelist().front();
                            while (nP->get_nodelist().size() == 1);
                            
                            if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                sscanf(nP->get_cdata().c_str(),"%f",
                                    &colorFilter->getGamma());
                        }
                        if((*nI)->get_name() == "size")
                        {
                            nP = (*nI);
                            do
                                nP = nP->get_nodelist().front();
                            while (nP->get_nodelist().size() == 1);
                            
                            if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                sscanf(nP->get_cdata().c_str(),"%d %d %d",
                                    &colorFilter->getWidth(),
                                    &colorFilter->getHeight(),
                                    &colorFilter->getDepth());
                        }
                        if((*nI)->get_name() == "shadingtable")
                        {
                            colors = (*nI)->select_nodes(colorTag);
                            
                            for(cI = colors.begin(); cI != colors.end(); ++cI)
                            {
                                nP = (*cI);
                                do
                                    nP = nP->get_nodelist().front();
                                while (nP->get_nodelist().size() == 1);
                                
                                if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                {
                                    Color3f col;
                                    col.setValue(nP->get_cdata().c_str());
                                    colorFilter->getTable().push_back(col);
                                }
                            }
                        }
                    }
                    endEditCP(colorFilter);
                } // colordisplayfilter
                
                if ((*fI)->get_name() == "resolutiondisplayfilter")
                {
                    resolutionFilter = ResolutionDisplayFilter::create();
                    addRefCP(resolutionFilter);
                    
                    filterFgnd->getFilter().push_back(resolutionFilter);
                    
                    beginEditCP(resolutionFilter);
                    
                    for(nI  = (*fI)->get_nodelist().begin();
                        nI != (*fI)->get_nodelist().end(); ++nI) 
                    {
                        if((*nI)->get_name() == "downscale")
                        {
                            nP = (*nI);
                            do
                                nP = nP->get_nodelist().front();
                            while (nP->get_nodelist().size() == 1);
                            
                            if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                sscanf(nP->get_cdata().c_str(),"%f",
                                    &resolutionFilter->getDownScale());
                        }
                    }
                    endEditCP(resolutionFilter);
                } // resolutiondisplayfilter
                
                if ((*fI)->get_name() == "distortiondisplayfilter")
                {
                    distortionFilter = DistortionDisplayFilter::create();
                    addRefCP(distortionFilter);
                    
                    filterFgnd->getFilter().push_back(distortionFilter);
                    
                    beginEditCP(distortionFilter);
                    
                    for(nI  = (*fI)->get_nodelist().begin();
                        nI != (*fI)->get_nodelist().end(); ++nI) 
                    {
                        if((*nI)->get_name() == "rows")
                        {
                            nP = (*nI);
                            do
                                nP = nP->get_nodelist().front();
                            while (nP->get_nodelist().size() == 1);
                            
                            if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                sscanf(nP->get_cdata().c_str(),"%d",
                                    &distortionFilter->getRows());
                        }
                        if((*nI)->get_name() == "cols")
                        {
                            nP = (*nI);
                            do
                                nP = nP->get_nodelist().front();
                            while (nP->get_nodelist().size() == 1);
                            
                            if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                sscanf(nP->get_cdata().c_str(),"%d",
                                    &distortionFilter->getColumns());
                        }
                        if((*nI)->get_name() == "positions")
                        {
                            points = (*nI)->select_nodes(pointTag);
                            
                            for(pI = points.begin(); pI != points.end(); ++pI)
                            {   
                                nP = (*pI);
                                do
                                    nP = nP->get_nodelist().front();
                                while (nP->get_nodelist().size() == 1);
                                
                                if(nP->get_type() == xmlpp::xml_nt_cdata) 
                                {
                                    Vec2f pos;
                                    pos.setValueFromCString(nP->get_cdata().c_str());
                                    distortionFilter->getPositions().push_back(pos);
                                }
                            }
                        }
                    }
                    endEditCP(distortionFilter);
                } // distortiondisplayfilter
            }
            
            endEditCP(filterFgnd);
        } // servers
    }
    catch (xmlpp::xmlerror e)
    {
        // parser error
        xmlpp::xmllocation where( ctxptr->get_location() );
        xmlpp::xmlstring errmsg( e.get_strerror() );
        SFATAL << "XML error line " << where.get_line() << " "
               << "at position " << where.get_pos()
               << ": error: " << errmsg.c_str()
               << std::endl;
        return false;
    }
    return true;
}
#endif

/*-------------------------------------------------------------------------*/
/*                          exceptions                                     */

ClusterWindow::AsyncCancel::AsyncCancel()
{
}

/*-------------------------------------------------------------------------*/
/*                         client methods                                  */

/*! init client window. In a derived cluster window this method is called
 *  before the first sync with the rendering servers. There is no default 
 *  action.
 */
void ClusterWindow::clientInit(void)
{
}

/** client frame before sync
 *  
 * In a derived cluster window this method is called before 
 * sync with the rendering servers. Default aciton is to activate
 * and init the client window.
 **/

void ClusterWindow::clientPreSync( void )
{
    if(getClientWindow() != NullFC)
    {
        getClientWindow()->activate ();
        getClientWindow()->frameInit();
    }
}

/** initiate client rendering
 *  
 * In a derived cluster window this method is called after the 
 * sync with all rendering servers. Default aciton is to render all
 * viewports of the client window.
 **/

#ifdef OSG_OLD_RENDER_ACTION
void ClusterWindow::clientRender(DrawActionBase *action)
{
    if(getClientWindow() != NullFC)
    {
        getClientWindow()->renderAllViewports(action);
    }
}
#endif

void ClusterWindow::clientRender(RenderActionBase *action)
{
    if(getClientWindow() != NullFC)
    {
        getClientWindow()->renderAllViewports(action);
    }
}

/** swap client window
 *  
 * In a derived cluster window this method is called after rendering
 * Default aciton is to swap the local client window.
 **/

void ClusterWindow::clientSwap( void )
{
    if(getClientWindow() != NullFC)
    {
        getClientWindow()->swap     ();
        getClientWindow()->frameExit();
    }

#if 0
    if(getDirty() == true)
    {
        setDirty(false);
    }
#endif
}

/*-------------------------------------------------------------------------*/
/*                         server methods                                  */

#if 0
bool ClusterWindow::updateFilter(WindowPtr window, UInt32 id, 
                                 RenderActionBase *action)
{
    bool found = false;

    if (!getFilter().empty() && getDirty())
    {
        UInt32 c, p;
        
        ClusterWindowPtr ptr(this);
        
        beginEditCP(ptr, DirtyFieldMask);
            setDirty(false);
        endEditCP(ptr, DirtyFieldMask);
        
        // for all viewports
        for(p=0; p<window->getPort().size(); ++p) 
        {
            // search filter foregrounds
            for(c=0; c<getFilter().size(); ++c)
            {
                std::string name = getServers()[id];
                char portName[64];
                
                if(window->getPort().size() > 1)
                {
                    sprintf(portName,"[%d]",p);
                    name = name + portName;
                }
                
                DisplayFilterForegroundPtr filterFgnd = getFilter()[c];
                
                if(filterFgnd->getServer() == name)
                {
                    beginEditCP(window->getPort()[p], Viewport::ForegroundsFieldMask);
                    
                    // first remove old filters, if any
                    for (Int32 n=window->getPort()[p]->getForegrounds().size(), j=n-1; 
                            j>=0; j--) 
                    {
                        MFForegroundPtr::iterator fgndIt = 
                            window->getPort()[p]->getForegrounds().begin() + j;
                        if ( (*fgndIt) == filterFgnd )
                            window->getPort()[p]->getForegrounds().erase(fgndIt);
                    }
                    
                    // then add new one
                    window->getPort()[p]->getForegrounds().push_back(filterFgnd);
                    
                    endEditCP(window->getPort()[p], Viewport::ForegroundsFieldMask);

                    found = true;
                    break;
                }
            }
        }
    }

    return found;
}
#endif


/** initialise the cluster window on the server side
 *  
 * This method is called after the first sync.
 *  
 * \param window     server render window
 * \param id         server id
 **/

void ClusterWindow::serverInit(WindowPtr,
                               UInt32   )
{
}

/** render server window
 *  
 * This method is called after synchronisation of all changes with the
 * rendering client. Default action is to render all viewports with the
 * given action
 *  
 * !param window     server render window
 * !param id         server id
 * !param action     action
 **/

#ifdef OSG_OLD_RENDER_ACTION
void ClusterWindow::serverRender( WindowPtr window,
                                  UInt32 id,
                                  DrawActionBase *action )
{
    window->activate();
    window->frameInit();
    window->renderAllViewports(action);

#if 0
    RenderOptionsPtr ro;

    RenderAction *ract = dynamic_cast<RenderAction *>(action);
    if(ract != NULL)
    {
        MFViewportPtr::iterator       portIt  = window->getPort().begin();
        MFViewportPtr::const_iterator portEnd = window->getPort().end();
        // try to find option as an attachment of window
        OSG::RenderOptionsPtr winRo = OSG::RenderOptionsPtr::dcast(
            window->findAttachment(OSG::RenderOptions::getClassType()));
        ract->setWindow(window.getCPtr());
        while(portIt != portEnd)
        {
            // try to find option an attachment at the viewport
            OSG::RenderOptionsPtr vpRo = OSG::RenderOptionsPtr::dcast(
                (*portIt)->findAttachment(OSG::RenderOptions::getClassType()));
            // try to find option an attachment at the root node
            OSG::RenderOptionsPtr rootRo = NullFC;
            if((*portIt)->getRoot() != NullFC)
            {
                rootRo = OSG::RenderOptionsPtr::dcast(
                    (*portIt)->getRoot()->findAttachment(OSG::RenderOptions::getClassType()));
            }
            if(rootRo != NullFC)
                ro = rootRo;
            else
                if(vpRo != NullFC)
                    ro = vpRo;
                else
                    ro = winRo;
            if(ro != NullFC)
                ro->activateOptions(ract);
            (*portIt)->render(ract);
            ++portIt;
        }
    } else {
        if(action)
            window->renderAllViewports(action);
    }

    // do calibration
    DisplayCalibrationPtr calibPtr=NullFC;
    UInt32 c, p;
    
    // for all viewports
    for(p = 0 ; p<window->getPort().size() ; ++p) 
    {
        // search calibration 
        for(c=0 ; c<getCalibration().size() ; ++c)
        {
            std::string name = getServers()[id];
            char portName[64];
            if(window->getPort().size() > 1)
            {
                sprintf(portName,"[%d]",p);
                name = name + portName;
            }
            if(getCalibration()[c]->getServer() == name)
            {
                calibPtr = getCalibration()[c];
                calibPtr->calibrate(window->getPort()[p],action);
                break;
            }
        }
    }
#endif
}
#endif

void ClusterWindow::serverRender( WindowPtr window,
                                  UInt32 id,
                                  RenderActionBase *action )
{
    window->activate();
    window->frameInit();
    window->renderAllViewports(action);

#if 0
    // do calibration
    UInt32 c;

    DisplayCalibrationPtr calibPtr = NullFC;

    for(c = 0 ; c < getCalibration().size() ;++c)
    {
        if(getCalibration()[c]->getServer() == getServers()[id])
        {
            calibPtr = getCalibration()[c];
            break;
        }
    }

    if(calibPtr != NullFC)
        calibPtr->calibrate(window,action);
#endif
}

/** swap server window
 *  
 * <code>serverSwap</code> is called after rendering. Default action is
 * to swap the rendering window. 
 *  
 * !param window     server render window
 * !param id         server id
 * !param connection connection to client
 **/
void ClusterWindow::serverSwap( WindowPtr window,
                                UInt32)
{
    window->swap     ();
    window->frameExit();
}

/*-------------------------------------------------------------------------*/
/*                         constructor / destructor                        */

//! Constructor

ClusterWindow::ClusterWindow(void) :
     Inherited(),
    _firstFrame(true),
    _statistics(NULL),
    _connectionFP(NULL),
    _network(NULL)
{
}

//! Copy Constructor

ClusterWindow::ClusterWindow(const ClusterWindow &source) :
    Inherited(source),
    _firstFrame(true),
    _statistics(NULL),
    _connectionFP(source._connectionFP),
    _network(NULL)
{
}

//! Destructor

ClusterWindow::~ClusterWindow(void)
{
    if(_network)
        subRef(_network);

    _network = NULL;
}

/*-------------------------------------------------------------------------*/
/*                           connection pool                               */

/*! Get connection pool
 */
ClusterNetwork *ClusterWindow::getNetwork(void)
{
    if(!_network)
    {
        _network = ClusterNetwork::getInstance(this->getId());

        addRef(_network);
    }
    return _network;
}

/*! initialize the static features of the class, e.g. action callbacks
 */

void ClusterWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void ClusterWindow::exitMethod(InitPhase ePhase)
{
    Inherited::exitMethod(ePhase);
}
