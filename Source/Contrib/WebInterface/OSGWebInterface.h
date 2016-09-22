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

#ifndef _OSGWEBINTERFACE_H_
#define _OSGWEBINTERFACE_H_

#include <string>
#include <map>
#include <sstream>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGContribWebInterfaceDef.h>

#include <OpenSG/OSGStreamSocket.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGMemoryObject.h>
#include <OpenSG/OSGNode.h>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBWEBINTERFACE_DLLMAPPING WebInterface : public MemoryObject
{
  public:
    
    typedef std::map<std::string, std::string> ParameterT;

    typedef void (WebInterface::*MethodT)(      std::ostream &,
                                          const char*,
                                                ParameterT   &);

    typedef std::map<std::string, MethodT> HandlerT;

    OSG_GEN_INTERNAL_MEMOBJPTR(WebInterface);

    typedef boost::function<ObjTransitPtr (UInt32)> CreateFunc;

    /*---------------------------------------------------------------------*/
    /*! \name                  request handling                            */
    /*! \{                                                                 */

    static ObjTransitPtr create        (UInt32     port       = 8080);
    static void          setCreatorFunc(CreateFunc createFunc       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  request handling                            */
    /*! \{                                                                 */

    virtual void handleRequests(void                );
    virtual bool waitRequest   (double duration = -1);
    virtual void flush         (void                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    virtual void setSystemContainer(      FieldContainer *system);
    virtual void setRoot           (      Node           *root  );
    virtual void setChangeList     (      ChangeList     *clist );
    
    virtual void setHeader         (const std::string    &header);
    virtual void setFooter         (const std::string    &footer);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual       FieldContainer *getSystemContainer(void);
    virtual       Node           *getRoot           (void);
    
    virtual const std::string    &getHeader         (void);
    virtual const std::string    &getFooter         (void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MemoryObject Inherited;

    static CreateFunc _createFunc;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WebInterface(void);
    WebInterface(UInt32 port);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WebInterface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                handler management                            */
    /*! \{                                                                 */

    void addHandler(const Char8 *key, MethodT method);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                url encoding/decoding                         */
    /*! \{                                                                 */

    std::string encodeUrl(const std::string &path,
                          const ParameterT  &param);

    void        decodeUrl(const std::string &url,
                                std::string &path,
                                ParameterT  &param);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    std::string createFCViewReference(      FieldContainer   *fcPtr,
                                            UInt32            id=0  );

    const char *getParam             (      ParameterT       &param,
                                      const char             *name  );

    void        setParam             (      ParameterT       &param,
                                      const char             *name ,
                                      const char             *value );
                                      
    void        treeViewNode         (std::ostream     &os,
                                      Node             *node,
                                      ParameterT       &param );
                                      
    const char *getNodeName          (const FieldContainer  *fcPtr);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool        checkRequest         (std::string &url        );
    std::string getDefaultHeader     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  web page handler                            */
    /*! \{                                                                 */

    void rootHandler      (std::ostream &os,
                           const char   *path,ParameterT &param);
    void changelistHandler(std::ostream &os,
                           const char   *path,ParameterT &param);
    void fcViewHandler    (std::ostream &os,
                           const char   *path,ParameterT &param);
    void fcEditHandler    (std::ostream &os,
                           const char   *path,ParameterT &param);
    void treeViewHandler  (std::ostream &os,
                           const char   *path,ParameterT &param);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  private members                             */
    /*! \{                                                                 */

    StreamSocket            _socket;
    StreamSocket            _accepted;
    std::stringstream       _body;
    HandlerT                _handler;
    NodeUnrecPtr            _root;
    FieldContainerUnrecPtr  _systemContainer;
    std::string             _header;
    std::string             _footer;
    ChangeList             *_clist;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    WebInterface(const WebInterface &other);
    void operator=(const WebInterface &rhs);
};

OSG_GEN_MEMOBJPTR(WebInterface);

OSG_END_NAMESPACE

#endif
