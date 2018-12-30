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


#ifndef _POINTCONNECTION_H_
#define _POINTCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>
#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGConnection.h"
#include "OSGTime.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkBase
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING PointConnection : public Connection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             PointConnection ( int zeroCopyThreshold );
    virtual ~PointConnection ( void                  ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   type info                                  */
    /*! \{                                                                 */

    virtual const ConnectionType *getType (void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   connection                                 */
    /*! \{                                                                 */

    virtual Channel connectGroup(const std::string &address,
                                       Time        timeout=-1) = 0;
    virtual void    disconnect  (      void                  ) = 0;
    virtual Channel acceptGroup (      Time        timeout=-1) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   synchronisation                            */
    /*! \{                                                                 */

    virtual bool wait  (Time timeout=-1) OSG_THROW (ReadError )  = 0;
    virtual void signal(void           ) OSG_THROW (WriteError) = 0;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                   members                                    */
    /*! \{                                                                 */

    bool _pointToPoint;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef Connection Inherited;

	// prohibit default functions (move to 'public' if you need one)
    PointConnection(const PointConnection &source);
    PointConnection& operator =(const PointConnection &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef PointConnection *PointConnectionP;

OSG_END_NAMESPACE

#endif /* _CONNECTION_H_ */
