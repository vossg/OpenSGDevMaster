/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _CLUSTERCONNECTINFO_H_
#define _CLUSTERCONNECTINFO_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGClusterDef.h"
#include "OSGMemoryObject.h"
#include "OSGRefCountPtr.h"
#include "OSGTransitPtr.h"
#include "OSGGroupConnection.h"
#include "OSGPointConnection.h"

#include <vector>
#include <map>

OSG_BEGIN_NAMESPACE

class RemoteAspect;
class ClusterNetwork;
OSG_GEN_MEMOBJPTR(ClusterNetwork);

/*! \ingroup GrpClusterBase
    \ingroup GrpLibOSGCluster
 */

class OSG_CLUSTER_DLLMAPPING ClusterNetwork : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef std::vector<Connection     *> ConnectionsT;
    typedef std::map   <UInt32,
                        ClusterNetwork *> ConnectionInfoMapT;

    enum 
    {
        ALL_NODES   = 0xf00000 
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    Connection      *getMainConnection      (void);
    GroupConnection *getMainGroupConnection (void);
    PointConnection *getMainPointConnection (void);

    Connection      *getConnection      (UInt32 id);
    GroupConnection *getGroupConnection (UInt32 id);
    PointConnection *getPointConnection (UInt32 id);

    RemoteAspect    *getAspect          (void     );
    ConnectionsT    &getConnection      (void     );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setAspect        (RemoteAspect *aspect    );
    void setMainConnection(Connection   *connection);
    void setConnection    (UInt32        id,
                           Connection   *connection);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   establish connection                       */
    /*! \{                                                                 */

    void connectAllPointToPoint(           UInt32  thidId,
                                const std::string &connectionType);
    void connectAllGroupToPoint(           UInt32  thidId,
                                const std::string &connectionType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  static access                               */
    /*! \{                                                                 */

    static ClusterNetwork *getInstance(UInt32 ClusterWindowId);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MemoryObject Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ClusterNetwork(UInt32 clusterWindowId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ClusterNetwork(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    RemoteAspect *_aspect;
    Connection   *_mainConnection;
    ConnectionsT  _connection;
    UInt32        _id;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    ClusterNetwork(const ClusterNetwork &source);
    ClusterNetwork &operator =(const ClusterNetwork &source);

    static ConnectionInfoMapT _map;
};

OSG_END_NAMESPACE

#endif /* _CLUSTERCONNECTINFO_H_ */
