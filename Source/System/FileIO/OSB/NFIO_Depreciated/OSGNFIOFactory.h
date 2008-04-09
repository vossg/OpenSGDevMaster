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

#ifndef _OSGNFIOFACTORY_H_
#define _OSGNFIOFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include<string>
#include<map>

#include "OSGFileIODef.h"
#include "OSGNFIOBase.h"

OSG_BEGIN_NAMESPACE

/* \brief NFIONFIOFactory class.
          NFIOFactory for registering file io.
*/

class OSG_FILEIO_DLLMAPPING NFIOFactory
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     access                                   */
    /*! \{                                                                 */

    void        add(const std::string &name, NFIOBase *base );
    void        sub(const NFIOBase *base                    );
    NFIOBase   *get(const std::string &name                 );

    typedef std::map<std::string, NFIOBase *> registryMap;
    registryMap &getMap(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static NFIOFactory &the(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:


    /*==========================  PRIVATE  ================================*/
private:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    NFIOFactory(void);

    /*! \}                                                                 */

    /*! The registry. Maps from name to NFIOBase instance. */
    registryMap _registry;
};

OSG_END_NAMESPACE

#endif /* _OSGNFIOFACTORY_H_ */
