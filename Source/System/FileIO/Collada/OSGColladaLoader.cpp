/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2006 by the OpenSG Forum                   *
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

/*! \file OSGColladaLoader.cpp
    \ingroup GrpFoundationLoader
 */

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGColladaLoader.h"
#include "OSGPathHandler.h"

#include <OSGColladaLog.h>
#include <OSGColladaGlobal.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

ColladaLoader::ColladaLoader(void) :
    _pPathHandler(NULL)
{
    _pPathHandler = new PathHandler;
}

ColladaLoader::~ColladaLoader(void)
{
    delete _pPathHandler;
}

NodeTransitPtr ColladaLoader::read(      std::istream  &is,
                                   const Char8         *szFileName)
{
    NodeTransitPtr returnValue(NULL);

#ifdef OSG_WITH_COLLADA
    _pPathHandler->clearPathList();
    _pPathHandler->clearBaseFile();
    _pPathHandler->push_frontCurrentDir();

    _pPathHandler->setBaseFile(szFileName);

    OSG_COLLADA_LOG(("ColladaLoader::read [%s]\n", szFileName));

    ColladaGlobalRefPtr colGlobal = ColladaGlobal::create();
    
    colGlobal->setDocPath(szFileName);
    
    colGlobal->read();
    
    returnValue = colGlobal->getRootNode();
#endif // OSG_WITH_COLLADA

    return returnValue;
}

/*-------------------------- assignment -----------------------------------*/
