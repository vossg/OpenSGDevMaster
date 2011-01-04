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

#include "OSGConfig.h"

#include "OSGOSGSceneFileType.h"

#include "OSGOSGWriter.h"

#include "OSGOSGLoader.h"

OSG_USING_NAMESPACE


/*! \class OSG::OSGSceneFileType
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Char8 *OSGSceneFileType::_suffixA[] =  { "osg" };

OSGSceneFileType OSGSceneFileType::_the(_suffixA,
                                        sizeof(_suffixA),
                                        false,
                                        10,
                                        OSG_READ_SUPPORTED | 
                                        OSG_WRITE_SUPPORTED);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSGSceneFileType &OSGSceneFileType::the(void)
{
    return _the;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

const Char8 *OSGSceneFileType::getName(void) const
{
    return "OSG Ascii Geometry";
}


NodeTransitPtr OSGSceneFileType::read(      std::istream &is, 
                                      const Char8        *,
                                            Resolver      resolver) const
{
    OSGLoader *_pFile = new OSGLoader(_endNodeFunctors);

    NodeTransitPtr returnValue = _pFile->scanStream(is, resolver);

    if(returnValue->getNChildren() == 1)
    {
        returnValue = returnValue->getChild(0);
    }

    delete _pFile;

    commitChanges();

    return returnValue;
}

FieldContainerTransitPtr OSGSceneFileType::readContainer(
    const Char8    *fileName,
          Resolver  resolver) const
{
    if(fileName == NULL)
    {
        SWARNING << "cannot read NULL file" << std::endl;
        return FieldContainerTransitPtr(NULL);
    }

    OSGLoader *_pFile = new OSGLoader(_endNodeFunctors);

    std::ifstream is(fileName, std::ios::binary);

    FieldContainerTransitPtr returnValue = 
        _pFile->scanStreamContainer(is, resolver);

    delete _pFile;

    commitChanges();

    return returnValue;
}

bool OSGSceneFileType::write(Node * const  root, 
                             std::ostream &os,
                             Char8  const *    ) const
{
    if(!os)
    {
        FFATAL(("Can not open output stream!\n"));
        return false;
    }

    IndentOutStreamMixin<OutStream> iOStream(os);

    OSGWriter writer(iOStream, 4);
    writer.write(root);

    return true;
}

bool OSGSceneFileType::writeContainer(FieldContainer * const  pContainer, 
                                      Char8            const *fileName) const
{
    if(fileName == NULL)
    {
        SWARNING << "cannot write NULL file" << std::endl;
        return false;
    }

    std::ofstream os(fileName, std::ios::binary);

    IndentOutStreamMixin<OutStream> iOStream(os);

    OSGWriter writer(iOStream, 4);

    writer.write(pContainer);

    return true;
}

/*---------------------------- properties ---------------------------------*/

void OSGSceneFileType::registerEndNodeCallback(const FieldContainerType &type, 
                                               const Functor            &func)
{
    _endNodeFunctors.resize(type.getId() + 1, NULL);

    _endNodeFunctors[type.getId()] = func;
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Constructor
 */

OSGSceneFileType::OSGSceneFileType(const char   *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority,
                                         UInt32  flags) :
     Inherited(suffixArray,
               suffixByteCount,
               override,
               overridePriority,
               flags),
    _endNodeFunctors()
{
    return;
}


/** \brief Destructor
 */

OSGSceneFileType::~OSGSceneFileType(void)
{
}

void OSGSceneFileType::terminate(void)
{
    _endNodeFunctors.clear();
}

