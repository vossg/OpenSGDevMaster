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

#ifndef _CONNECTIONTYPE_H_
#define _CONNECTIONTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseDef.h"

OSG_BEGIN_NAMESPACE

class PointConnection;
class GroupConnection;

/*! \brief Types for Connection, see XXX for details.
    \ingroup GrpBaseNetwork
*/

class OSG_BASE_DLLMAPPING ConnectionType 
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Types                                  */
    /*! \{                                                                 */

    typedef PointConnection *(*CreatePointFunction)(void);
    typedef GroupConnection *(*CreateGroupFunction)(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ConnectionType(CreateGroupFunction,
                   const std::string &name);
    ConnectionType(CreatePointFunction,
                   const std::string &name);
    ConnectionType(const ConnectionType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ConnectionType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    std::string         getName       (void) const;
    CreateGroupFunction getCreateGroup(void) const;
    CreatePointFunction getCreatePoint(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   creation                                   */
    /*! \{                                                                 */

    PointConnection *createPoint(void);
    GroupConnection *createGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    ConnectionType &operator =(const ConnectionType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator < (const ConnectionType &other) const;
    bool operator == (const ConnectionType &other) const;
    bool operator != (const ConnectionType &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    CreateGroupFunction _createGroup;
    CreatePointFunction _createPoint;
    std::string         _name;

    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#endif /* _CONNECTIONTYPE_H_ */
