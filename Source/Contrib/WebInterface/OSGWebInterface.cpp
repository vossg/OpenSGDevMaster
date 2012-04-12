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

#include "OSGConfig.h"
#include "OSGFieldContainerFields.h"
#include "OSGNodeCore.h"
#include "OSGLog.h"
#include "OSGNameAttachment.h"
#include "OSGRootGroup.h"

#include "OSGWebInterface.h"

OSG_USING_NAMESPACE

/*! \class osg::WebInterface

The WebInterface class provides a simple access to all
FieldContainers in a running OpenSG application. If
handleRequests() is called in each render loop, it is
possible to connect the interface with a standard web
browser http://hostname:8888. In glut applications the
idle functions could be used. It is possible to add 
new features to the interface by subclassing and adding
new handlers.

*/

WebInterface::CreateFunc WebInterface::_createFunc = NULL;

WebInterface::ObjTransitPtr WebInterface::create(UInt32 port)
{
    if(_createFunc)
    {
        return _createFunc(port);
    }
    else
    {
        return WebInterfaceTransitPtr(new WebInterface(port));
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Cunstruct a WebInterface for the given port. If the port
  is used, try to bind to the following port number.
*/
WebInterface::WebInterface(UInt32 port) :
     Inherited      (                  ),
    _socket         (                  ),
    _accepted       (                  ),
    _body           (                  ),
    _handler        (                  ),
    _root           (NULL              ),
    _systemContainer(NULL              ),
    _header         (getDefaultHeader()),
    _footer         (                  ),
    _clist          (NULL              )
{
    bool bound=false;

    _socket.open();
    _socket.setReusePort(true);

    do
    {
        try
        {
            _socket.bind(SocketAddress(SocketAddress::ANY,port));
            _socket.listen();

            bound = true;
        }
        catch(SocketException &) 
        {
            port++;
        }
    }
    while(!bound);

    FLOG(("WebInterface bound to port:%d\n",port));

    // register bas handlers
    addHandler("/"          , &WebInterface::rootHandler);
    addHandler("/changelist", &WebInterface::changelistHandler);
    addHandler("/fcview"    , &WebInterface::fcViewHandler);
    addHandler("/fcedit"    , &WebInterface::fcEditHandler);
    addHandler("/treeview"  , &WebInterface::treeViewHandler);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor 
 */

WebInterface::~WebInterface(void)
{
    _socket.close();
}

/*-------------------------------------------------------------------------*/
/*                            request handling                             */

/*! Handle all incoming http requests. Return, if no request is
  pending
*/

void WebInterface::handleRequests(void)
{
    std::string         path,url;
    ParameterT          param;
    HandlerT::iterator  hI;

    while(checkRequest(url))
    {
        decodeUrl(url,path,param);
        // write http header

        _body.str("");
        _body <<
            "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Server: OpenSGMicroWebInterface\r\n"
            "Expires: 0\r\n";

        // find handler
        hI = _handler.find(path);

        if(hI != _handler.end())
        {
            (this->*hI->second)(_body,path.c_str(),param);
        }
        else
        {
            _body << "Content-Type: text/html\r\n"
                     "\r\n"
                     "<html>Invalid path</html>";
        }

        _body.flush();
        _accepted.setDelay(false);

        // finish request
        _accepted.send(_body.str().c_str(), _body.str().length());

        // close connection
        _accepted.close();
    }
}

/*! Flush the data that's alrady in the stream to allow incremental creation
   and updates on slow operaitons
*/

void WebInterface::flush(void)
{
    _body.flush();
    _accepted.setDelay(false);

    // finish request
    _accepted.send(_body.str().c_str(), _body.str().length());
    _body.str("");
}

/*! Suspend processing until a http request is pending for the
  given duration in seconds. If duration is < 0. waitRequest
  will wait vor ever
*/

bool WebInterface::waitRequest(double duration)
{
    try
    {
        if(!_socket.waitReadable(duration))
            return false;
    }
    catch(SocketException &)
    {
        return false;
    }

    return true;
}

/*-------------------------------------------------------------------------*/
/*                             set                                         */

/*! Set the ChangeList. By default the ChangeList of the current thread is
    used, but it can be overriden by this function.
 */

void WebInterface::setChangeList(ChangeList *clist)
{
    _clist = clist;
}

/*! Set the scenegraph root node.
 */

void WebInterface::setSystemContainer(FieldContainer *system)
{
    _systemContainer = system;
}

/*! Set the scenegraph root node.
 */
void WebInterface::setRoot(Node *root)
{
    _root = root;
}

/*! Set the html header.
 */
void WebInterface::setHeader(const std::string &header)
{
    _header = header;
}

/*! Set the html footer.
 */
void WebInterface::setFooter(const std::string &footer)
{
    _footer = footer;
}

/*-------------------------------------------------------------------------*/
/*                             get                                         */


/*! Get the scenegraph root node.
 */

FieldContainer *WebInterface::getSystemContainer(void)
{
    return _systemContainer;
}

/*! Get the scenegraph root node.
 */

Node *WebInterface::getRoot(void)
{
    return _root;
}

/*! Get the html header.
 */

const std::string &WebInterface::getHeader(void)
{
    return _header;
}

/*! Get the html footer.
 */

const std::string &WebInterface::getFooter(void)
{
    return _footer;
}

/*-------------------------------------------------------------------------*/
/*                            handler management                           */

/*! Add a new page handler 
 */
void WebInterface::addHandler(const Char8 *path, MethodT method)
{
    // This is a workaround for gcc 3.1 on OS X

    HandlerT::value_type newEntry(path, method);

    std::pair<HandlerT::iterator, bool> retVal;
    
    retVal = _handler.insert(newEntry);

    if(retVal.second == false)
        retVal.first->second = method;

//    _handler[IDString(path)] = method;
}

/*-------------------------------------------------------------------------*/
/*                         url encoding/decoding                           */

/*! Encode the given path and params into a valid http url.
 */

std::string WebInterface::encodeUrl(const std::string &path,
                                    const ParameterT  &param)
{
    std::string result=path;
    ParameterT::const_iterator pI;
    unsigned int c;
    char ch;

    const char *hex="0123456789abcdef";

    if(param.size())
        result += "?";

    for(pI = param.begin() ; pI != param.end() ; ++pI)
    {
        if(pI != param.begin())
            result += '&';

        result += pI->first.c_str();

        if(!pI->second.empty())
            result += '=';

        for(c = 0 ; c < UInt32(pI->second.length()) ; ++c)
        {
            ch = pI->second.c_str()[c];

            switch(ch)
            {
                case ' ':
                    result += '+';
                    break;
                case '+':
                case ';':
                case '/':
                case '?':
                case ':':
                case '@':
                case '&':
                case '=':
                    result += '%';
                    result += hex[ch / 16];
                    result += hex[ch & 15];
                    break;
                default:
                    result += ch;
            }
        }
    }

    return result;
}

/*! strip and decode parameter values from a given URL. Parameter,
  value paires are stored in a string map. 
*/

void WebInterface::decodeUrl(const std::string &url,
                                   std::string &path,
                                   ParameterT  &param)
{
    std::string::const_iterator sI=url.begin();
    std::string                 name,value;
    char                        bu[2];
    int                         c;

    path = "";
    param.clear();
   
    while(sI !=url.end() && *sI != ' ' && *sI != '?') 
        path += *(sI++);

    if(sI !=url.end() && *sI == '?')
    {
        do
        {
            name = value = "";
            // read name

            while(++sI != url.end() && 
                  *sI != ' '        && 
                  *sI != '='        && 
                  *sI != '&'          ) 
            {
                name += *sI;
            }

            if(sI != url.end() && *sI == '=')
            {
                // read value
                while(++sI != url.end() && *sI != ' ' && *sI != '&') 
                {
                    switch(*sI)
                    {
                        case '+': value += ' ';
                            break;

                        case '%': 
                            for(c = 0 ; c < 2 ; ++c)
                            {
                                bu[c] = *(++sI);

                                if(bu[c] >= 'A')
                                {
                                    bu[c] = bu[c] - 'A' + 10; 
                                }
                                else
                                {
                                    if(bu[c] >= 'a')
                                        bu[c] = bu[c] - 'a' + 10; 
                                    else
                                        bu[c] -= '0';
                                }
                            }

                            value += char(bu[0]*16+bu[1]);
                            break;

                        default:
                            value += *sI;
                    }
                }
            }

            setParam(param,name.c_str(),value.c_str());

        } while(sI != url.end() && *sI == '&');
    }
}

/*-------------------------------------------------------------------------*/
/*                         helper                                          */

/*! Helper function. Create a link to a node view html page.
 */

std::string WebInterface::createFCViewReference(FieldContainer *fcPtr,
                                                UInt32          fcId)
{
    std::stringstream                   result;

    if(fcPtr == NULL)
    {
        if(fcId)
            result << "Unknown(" << fcId << ")";
        else
            result << "NullFC";
    }
    else
    {
        result << "<a href =\"fcview?id="
               << fcPtr->getId()
               << "\">"
               << fcPtr->getType().getName()
               << " ("
               << fcPtr->getId()
               << ")"
               << "</a>";
    }

    return result.str();
}

/*! get parameter. If the parameter is not set, NULL
    is returned.
 */

const char *WebInterface::getParam(ParameterT &param, const char *name)
{
    ParameterT::iterator pI = param.find(std::string(name));

    if(pI == param.end())
        return NULL;
    else
        return pI->second.c_str();
}

/*! set parameter to the given value. If value is NULL, the
    parameter is removed.
 */
void WebInterface::setParam(      ParameterT &param,
                            const char       *name,
                            const char       *value)
{
    if(!value)
        param.erase(std::string(name));
    else
        param[std::string(name)] = std::string(value);
}

/*! Handle pending http requests. The requested url is return in
  url. If no request is pending, false is returned.
*/
bool WebInterface::checkRequest(std::string &url)
{
    std::string name,value;
    char bu[4];
    char ch;

    url = "";

    try
    {
        if(!_socket.waitReadable(0))
            return false;
    }
    catch(SocketException &)
    {
        return false;
    }

    _accepted = _socket.accept();

    if(_accepted.recv(bu,4) && strncmp(bu,"GET ",4) == 0)
    {
        while(_accepted.recv(&ch, 1) && ch != ' ') 
            url += ch;
    }

    do
        while(_accepted.recv(&ch, 1) && ch != '\n');

    while(_accepted.recv(&ch, 1) && ch != '\r');

    _accepted.recv(&ch, 1);

    if(url.empty())
        return false;
    else
        return true;
}

/*! Traversal function for the treeViewHandler
 */
void WebInterface::treeViewNode(std::ostream &os,
                                Node         *node,
                                ParameterT    &param)
{
    ParameterT::const_iterator pI;
    char                       idstr[32];
    std::string                folder;

    if(node == NULL)
    {
        os << "<li>NullFC</li>\n";
        return;
    }

    sprintf(idstr,"%u",node->getId());

    if(param.count(std::string(idstr)))
    {
        setParam(param,"close",idstr);
        folder = encodeUrl("treeview",param);
        setParam(param,"close",NULL);
        os << "<li><a href=\"" << folder << "\">&nbsp - &nbsp</a>";
    }
    else
    {
        setParam(param,"open",idstr);
        folder = encodeUrl("treeview",param);
        setParam(param,"open",NULL);
        os << "<li><a href=\"" << folder << "\">&nbsp + &nbsp</a>";
    }

    os << "&nbsp &nbsp &nbsp "
       << "<b>" << getNodeName(node) << "</b>&nbsp &nbsp &nbsp "
       << createFCViewReference(node);
       
    if(node->getCore() != NULL)
    {
        os <<  "&nbsp &nbsp &nbsp Core: "
           << createFCViewReference(node->getCore());
    }
    os << "</li>";

    if(param.count(std::string(idstr)))
    {
        os << "<ul>\n";
        Node::MFChildrenType::const_iterator nI = 
            node->getMFChildren()->begin();

        for(; nI != node->getMFChildren()->end(); ++nI)
        {
            treeViewNode(os,*nI,param);
        }

        RootGroup *pRG = dynamic_cast<RootGroup *>(node->getCore());

        if(pRG != NULL)
        {
            treeViewNode(os, pRG->getRoot(), param);
        }

        os << "</ul>\n";
    }
}

/*-------------------------------------------------------------------------*/
/*                      web page handler                                   */

/*! main page
 */
void WebInterface::rootHandler(      std::ostream &os,
                               const char         *,
                                     ParameterT   &  )
{
    os << "Content-Type: text/html\r\n"
          "\r\n"
          "<html>" 
       << _header;

    os << "<h1>OpenSG Web Interface</h1>"
       << "<ui>"
       << "<li><a href=\"changelist\">ChangeList</a>"
       << "<li><a href=\"treeview\">SceneGraph</a>"
       << "<li><b>" << getNodeName(_systemContainer) << "</b>&nbsp &nbsp &nbsp "
       << createFCViewReference(_systemContainer)
       << "</ui>";
    os << _footer << "</html>";
}

/*! View the current changelist
 */
void WebInterface::changelistHandler(std::ostream &os,
                                     const char *,
                                     ParameterT &)
{
#if 0
    ChangeList::idrefd_const_iterator   createdI;
    ChangeList::changed_const_iterator  changedI;
    ChangeList::idrefd_const_iterator   destroyedI;
    FieldContainerPtr                   fcPtr;
    ChangeList                          *changeList;
    std::string                         type,mask;
    int                                 col=0;
    const int                           createdCols=6;
    const int                           changedCols=3;
    const int                           destroyedCols=6;

    if(_clist == NULL)
    {
        changeList=OSG::Thread::getCurrentChangeList();
    }
    else
    {
        changeList = _clist;
    }
    
    os << "Content-Type: text/html\r\n"
          "\r\n"
          "<html>" << _header
       << "<h1>ChangeList</h1>";
    
    // created
    os << "<h2>Created</h2>"
       << "<table><tr>";
    for(col = 0 ; col < createdCols ; ++col)
        os << "<th>FieldContainer</th>";
    os << "</tr>\n";
    for(col = 0,createdI = changeList->beginCreated();
        createdI != changeList->endCreated(); createdI++)
    {
        fcPtr = FieldContainerFactory::the()->getContainer(*createdI);
        if(!col)
            os << "<tr>";
        os << "<td>" << createFCViewReference(fcPtr) << "</td>";
        col = (col+1) % createdCols;
        if(!col)
            os << "</tr>\n";
    }
    while(col && col++ < createdCols)
        os << "<td>&nbsp;</td>";
    os << "</tr>\n</table>\n";

    // Changed
    os << "<h2>Changed</h2>"
       << "<table><tr>";
    for(col = 0 ; col < changedCols ; ++col)
        os << "<th>FieldContainer</th><th>Change Mask</th>";
    os << "</tr>\n";
    for(col = 0,changedI = changeList->beginChanged();
        changedI != changeList->endChanged(); 
        changedI++)
    {
        fcPtr = FieldContainerFactory::the()->getContainer(changedI->first);
        mask = "Unknown";
        if(fcPtr != NullFC)
        {
            if(changedI->second == FieldBits::AllFields)
                mask = "AllFields";
            else
            {
                mask = "";
                for(unsigned int i=0;i<fcPtr->getType().getNumFieldDescs();i++)
                {
                    FieldDescription *desc=fcPtr->getType().getFieldDescription(i+1);
                    if(desc->getFieldMask() & changedI->second)
                    {
                        if(!mask.empty())
                            mask += "<br>";
                        mask += desc->getName().str();
                    }
                }
            }
        }
        if(!col)
            os << "<tr>";
        os << "<td>"
           << createFCViewReference(fcPtr)
           << "</td><td>"
           << mask 
           << "</td>";
        col = (col+1) % changedCols;
        if(!col)
            os << "</tr>\n";
    }
    while(col && col++ < changedCols)
        os << "<td>&nbsp;</td>";
    os << "</tr>\n</table>\n";

    // destroyed
    os << "<h2>Destroyed</h2>"
       << "<table><tr>";
    for(col = 0 ; col < destroyedCols ; ++col)
        os << "<th>FieldContainer</th>";
    os << "</tr>\n";
    for(col = 0,destroyedI = changeList->beginDestroyed();
        destroyedI != changeList->endDestroyed(); destroyedI++)
    {
        fcPtr = FieldContainerFactory::the()->getContainer(*destroyedI);
        if(!col)
            os << "<tr>";
        os << "<td>" << createFCViewReference(fcPtr,*destroyedI) << "</td>";
        col = (col+1) % destroyedCols;
        if(!col)
            os << "</tr>\n";
    }
    while(col && col++ < destroyedCols)
        os << "<td>&nbsp;</td>";
    os << "</tr>\n</table>\n";
    os << _footer << "</html>";
#endif
}

/*! FieldContainer view handler
 */

void WebInterface::fcViewHandler(      std::ostream &os,
                                 const char         *,
                                       ParameterT   &param)
{
    FieldContainer                     *fcPtr;//,*childFc;
    std::string                         type,value;
    UInt32                              id;
//    Field                              *field;
//    MFFieldContainerPtr                *mfFCPtr;

    if(!getParam(param,"id"))
    {
        os << "Content-Type: text/html\r\n"
              "\r\n"
              "<html>" 
           << _header
           << "id missing"
           << _footer << "</html>";
        return;
    }

    id = atoi(getParam(param,"id"));

    os << "Content-Type: text/html\r\n"
          "\r\n"
          "<html>" 
       << _header;

    fcPtr = FieldContainerFactory::the()->getContainer(id);

    if(fcPtr == NULL)
    {
        os << "NullFC";
    }
    else
    {
        os << "<h1>"
           << fcPtr->getTypeName()
           << " " << getNodeName(fcPtr)
           << "</h1>"
           << "<table><tr><th>Field</th><th>Field Type</th><th>&nbsp;</th>"
           << "<th>Value</th></tr>\n";


        UInt32 numFields = fcPtr->getNumFields();

        for(UInt32 field = 1; field <= numFields; field++)
        {
            GetFieldHandlePtr fHandle = fcPtr->getField(field);

            if(fHandle == NULL || fHandle->isValid() == false)
            {
                continue;
            }

            os << "<tr><td>"
               << fHandle->getName()
               << "</td><td>"
               << fHandle->getType().getCName()
               << "</td><td>";

            GetMapFieldHandlePtr sfMap = 
                boost::dynamic_pointer_cast<GetMapFieldHandle>(fHandle);

            FieldContainerPtrSFieldBase::GetHandlePtr sfFCPtr = 
                boost::dynamic_pointer_cast<
                    FieldContainerPtrSFieldBase::GetHandle>(fHandle);
    
            FieldContainerPtrMFieldBase::GetHandlePtr mfFCPtr = 
                boost::dynamic_pointer_cast<
                    FieldContainerPtrMFieldBase::GetHandle>(fHandle);

            if(sfMap != NULL && sfMap->isValid() == true)
            {         
                os << "</td><td>\n";
#if 0
                AttachmentMap &am = static_cast<SFAttachmentMap *>(field)->getValue();
                AttachmentMap::const_iterator mI;
                for(mI = am.begin() ; mI != am.end() ; ++mI)
                {
                    if(mI != am.begin())
                        os << "\n<br>";
                    os << createFCViewReference(mI->second);
                }
#endif
            }
            else
            {
                if(sfFCPtr != NULL || mfFCPtr != NULL)
                {
                    os << "</td><td>\n";

                    if(mfFCPtr != NULL && mfFCPtr->isValid() == true)
                    {
                        UInt32 mfSize = (*mfFCPtr)->size();

                        for(UInt32 j = 0 ; j < mfSize; ++j)
                        {
                            if(j>0)
                                os << "\n<br>";

                            os << createFCViewReference((*(*mfFCPtr))[j]);
                        }
                    }
                    else if(sfFCPtr != NULL && sfFCPtr->isValid() == true)
                    {
                        os << createFCViewReference((*sfFCPtr)->getValue());
                    }
                }
                else
                {
                    OutStream outstream(os);

                    os << "<form action=\"fcedit\">"
                       << "<input type=\"submit\" value=\"Edit\">"
                       << "<input type=\"hidden\" name=\"id\" value=\""
                       << fcPtr->getId()
                       << "\">"
                       << "<input type=\"hidden\" name=\"field\" value=\""
                       << fHandle->getDescription()->getFieldId()
                       << "\">"
                       << "</form>"
                       << "</td><td>\n";

                    fHandle->pushValueToStream(outstream); // << value;
                }
            }

            os << "</td></tr>\n";
        }

        os << "</table>";
    }

    os << _footer << "</html>";
}

/*! Edit field value
 */

void WebInterface::fcEditHandler(std::ostream &os,
                                 const char *,
                                 ParameterT &param)
{
#if 0
    FieldContainerPtr fcPtr=NullFC;
    std::string       value="";
    UInt32            cid=0;
    UInt32            fid=0;
    Field            *field;
    FieldDescription *desc=NULL;

    if(getParam(param,"id"))
    {
        cid = atoi(getParam(param,"id"));
        fcPtr = FieldContainerFactory::the()->getContainer(cid);
    }
    if(getParam(param,"field"))
    {
        fid = atoi(getParam(param,"field"));
    }
    if(fcPtr == NullFC)
    {
        os << "Content-Type: text/html\r\n"
              "\r\n"
              "<html>" << _header
           << "Unknown field container"
           << _footer << "</html>";
        return;
    }
    field = fcPtr->getField(fid);
    if(field == NULL)
    {
        os << "Content-Type: text/html\r\n"
              "\r\n"
              "<html>" << _header
           << "Unknown field in container"
           << _footer << "</html>";
        return;
    }
    desc=fcPtr->getType().getFieldDescription(fid);
    if(getParam(param,"value"))
    {
        beginEditCP(fcPtr,desc->getFieldMask());
        field->pushValueByStr(getParam(param,"value"));
        endEditCP(fcPtr,desc->getFieldMask());
    }
    field->getValueByStr(value);
    os << "Content-Type: text/html\r\n"
          "\r\n"
          "<html>" << _header
       << "<h1>Edit "
       << fcPtr->getTypeName()
       << "."
       << desc->getName().str()
       << "</h1>\n"
       << "<form action=\"fcedit\">"
       << "<textarea name=\"value\" cols=\"50\" rows=\"10\">"
       << value
       << "</textarea><p>"
       << "<input type=\"submit\" value=\" Change \">"
       << "<input type=\"hidden\" name=\"id\" value=\""
       << cid
       << "\">"
       << "<input type=\"hidden\" name=\"field\" value=\""
       << fid
       << "\">"
       << "</form>"
       << _footer << "</html>";
#endif
}

/*! Show scenegraph tree. For each leave to open, a parameter with
  the container id must be set. The parameters open and closed
  are used to open or close folders.
*/
void WebInterface::treeViewHandler(      std::ostream &os,
                                   const char         *,
                                         ParameterT   &param)
{
    ParameterT::iterator pI;

    // open folder
    if(getParam(param,"open"))
    {
        setParam(param,getParam(param,"open"),"");
        setParam(param,"open",NULL);
    }        

    // close folder
    if(getParam(param,"close"))
    {
        setParam(param,getParam(param,"close"),NULL);
        setParam(param,"close",NULL);
    }        

    // Changed 
    os << "Content-Type: text/html\r\n"
          "\r\n"
          "<html>" << _header
       << "<h1>Scenegraph</h1>\n"
       << "<ul>\n";

    treeViewNode(os,_root,param);

    os << "</ul>"
       << _footer << "</html>";
}

/*! Returns the name of a field container.
*/
const char *WebInterface::getNodeName(const FieldContainer *fcPtr)
{
    static const char *unnamed = "";
    
    if(fcPtr == NULL)
        return unnamed;
    
    const AttachmentContainer *acPtr = 
            dynamic_cast<const AttachmentContainer *>(fcPtr);
    
    if(acPtr == NULL)
        return unnamed;
    
    const Char8 *name = getName(acPtr);

    if(name == NULL)
        return unnamed;
    
    return name;
}

/*! Returns the default html header.
*/
std::string WebInterface::getDefaultHeader(void)
{
    std::stringstream header;

    header << "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" "
           << "width=\"100%\">"
           << "<tr bgcolor=\"#E5E5E5\">"
           << "<td valign=center><a href=\"/\"><font color=\"#004faf\">"
           << "Home</font></a></td>"
           << "<td valign=center><a href=\"changelist\"><font color="
           << "\"#004faf\">Changelist</font></a></td>"
           << "<td valign=center><a href=\"treeview\"><font color"
           << "=\"#004faf\">Scenegraph</font></a></td>"
           << "</tr></table>";

    return header.str();
}
