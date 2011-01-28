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

#ifndef _REMOTEASPECT_H_
#define _REMOTEASPECT_H_
#ifdef __sgi
#pragma once
#endif

#include <map>
#include <set>
#include <boost/function.hpp>

#include "OSGClusterDef.h"
#include "OSGStatElemTypes.h"
#include "OSGFieldContainerFactory.h"

OSG_BEGIN_NAMESPACE

class Connection;
class ChangeList;
class StatCollector;

/*! \ingroup GrpClusterBase
    \ingroup GrpLibOSGCluster
 */

class OSG_CLUSTER_DLLMAPPING RemoteAspect
{ 
    /*==========================  PUBLIC  =================================*/

  public:

    /** Message types */

    enum DataTypes 
    {
        SYNCENDED = 1,
        CREATED   = 2,
        DESTROYED = 3,
        NEWTYPE   = 4,
        CHANGED   = 5,
        ADDREFED  = 6,
        SUBREFED  = 7,
        IDMAPPING = 8
    };

    /** functor called for changed containers **/
    typedef boost::function<bool (FieldContainer * const, 
                                  RemoteAspect   *      )> Functor;


    /** Map remote to local id **/
    typedef std::map<UInt64,UInt32>    LocalFCMapT;

    /** Map local to remote id **/
    typedef std::map<UInt32,UInt64>    RemoteFCMapT;

    /** Map remote to local type **/
    typedef std::map<UInt32,UInt32>    LocalTypeMapT;

    /** id set **/
    typedef std::set<UInt32>           IdSetT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RemoteAspect(UInt32 aspectId = 0);
    virtual ~RemoteAspect(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Remote aspect functionaliy                 */
    /*! \{                                                                 */

    void receiveSync      (      Connection         &connection,
                                 bool               applyToChangelist = false);
    void sendSync         (      Connection         &connection,
                                 ChangeList         *changeList       = NULL );
    void registerCreated  (const FieldContainerType &type, 
                           const Functor            &func                    );
    void registerDestroyed(const FieldContainerType &type, 
                           const Functor            &func                    );
    void registerChanged  (const FieldContainerType &type, 
                           const Functor            &func                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Static Remote aspect functionaliy              */
    /*! \{                                                                 */

    static void addFieldFilter(UInt32 typeId,BitVector mask);
    static void subFieldFilter(UInt32 typeId,BitVector mask);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Statistics                                 */
    /*! \{                                                                 */

    void setStatistics(StatCollector *stat);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map<UInt32, BitVector>         FieldFilter;
    typedef std::vector<FieldContainerUnrecPtr> FieldContainerVector;

    /*---------------------------------------------------------------------*/
    /*! \name                   member                                     */
    /*! \{                                                                 */

    /** Aspect id **/
    UInt32                            _aspectId;

    /** remote id to fieldcontainer mapping **/
    LocalFCMapT                       _localFC;
    /** local to remote fieldcontainer mapping **/
    RemoteFCMapT                      _remoteFC;
    /** remote typeid mapping **/
    LocalTypeMapT                     _localType;

    /** indicates fc was sent **/
    IdSetT                            _sentFC;
    /** indicates fc was received **/
    IdSetT                            _receivedFC;

    /** indicates remote knows this fc **/
    IdSetT                            _mappedFC;
    /** indicates mapped type **/
    IdSetT                            _mappedType;

    UInt32                            _remoteAspectId;

    std::vector<Functor>              _createdFunctors;
    std::vector<Functor>              _destroyedFunctors;
    std::vector<Functor>              _changedFunctors;
    StatCollector                    *_statistics;

    static FieldFilter                _fieldFilter;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 protected helper functions                   */
    /*! \{                                                                 */

    bool   callCreated  (FieldContainer * const node);
    bool   callDestroyed(FieldContainer * const node);
    bool   callChanged  (FieldContainer * const node);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name               Receive Helper functions                       */
    /*! \{                                                                 */

    void receiveNewType  (Connection                &con,
                          FieldContainerFactoryBase *fcFactory    );
    void receiveCreated  (Connection                &con,
                          FieldContainerFactoryBase *fcFactory,
                          FieldContainerVector      &newContainers);
    void receiveChanged  (Connection                &con,
                          FieldContainerFactoryBase *fcFactory    );
    void receiveAddRefed (Connection                &con,
                          FieldContainerFactoryBase *fcFactory,
                          ChangeList                *pChangeList  );
    void receiveSubRefed (Connection                &con,
                          FieldContainerFactoryBase *fcFactory,
                          ChangeList                *pChangeList  );
    void receiveIdMapping(Connection                &con          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Send Helper functions                        */
    /*! \{                                                                 */

    void sendCreated  (Connection     &con,
                       FieldContainer *fcPtr      );
    void sendChanged  (Connection     &con,
                       FieldContainer *fcPtr,
                       BitVector       changedMask);
    void sendAddRefed (Connection     &con,
                       FieldContainer *fcPtr,
                       UInt32          localId    );
    void sendSubRefed (Connection     &con,
                       FieldContainer *fcPtr,
                       UInt32          localId    );
    void sendIdMapping(Connection     &con        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Helper functions                             */
    /*! \{                                                                 */

    void clearFCMapping    (UInt32      localId,
                            UInt32      remoteId );
    bool getLocalId        (UInt32      remoteId,
                            UInt32     &localId  );
    UInt64 getFullRemoteId (UInt32      remoteId );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 static elements                              */
    /*! \{                                                                 */

    static bool _defaultCreatedFunction  (FieldContainer * const fcp,
                                          RemoteAspect   *       aspect);
    static bool _defaultDestroyedFunction(FieldContainer * const fcp,
                                          RemoteAspect   *       aspect);
    static bool _defaultChangedFunction  (FieldContainer * const fcp,
                                          RemoteAspect   *       aspect);

    static StatElemDesc<StatTimeElem> statSyncTime;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    friend struct RemoteAspectFieldContainerMapper;

	// prohibit default functions (move to 'public' if you need one)

    RemoteAspect(const RemoteAspect &source);
    RemoteAspect &operator =(const RemoteAspect &source);
};

// class pointer
typedef RemoteAspect *RemoteAspectP;

/*! \ingroup GrpClusterBase
    \ingroup GrpLibOSGCluster
 */

struct RemoteAspectFieldContainerMapper : public ContainerIdMapper
{                                              
    virtual UInt32 map(UInt32 uiId);

    RemoteAspect *_remoteAspect;
};

OSG_END_NAMESPACE

#endif /* _REMOTEASPECT_H_ */
