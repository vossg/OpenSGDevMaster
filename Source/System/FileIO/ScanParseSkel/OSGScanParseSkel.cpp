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

#include "OSGConfig.h"

#include <iostream>

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
#include <fstream>
#endif

#include "OSGScanParseSkel.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGScanParseLexer.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ScanParseSkel::ScanParseSkel(void) :
    _bMapTypeIds      (false),
    _szReferenceHeader(NULL ),
    _pLexer           (NULL )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ScanParseSkel::~ScanParseSkel(void)
{
    delete _pLexer;
}

/*-------------------------------------------------------------------------*/
/*                                Scan                                     */

extern int OSGScanParseSkel_parse(void *);

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
void ScanParseSkel::scanStream(std::istream &is)
{
    if(is.good())
    {
        delete _pLexer;

        _pLexer = new OSGScanParseLexer(this, &is);

        OSGScanParseSkel_parse(this);

        reset();
    }
}

#endif

void ScanParseSkel::scanFile(const Char8 *szFilename)
{
    if(szFilename == NULL)
        return;

#ifdef OSG_FLEX_USE_IOSTREAM_INPUT
    std::ifstream is(szFilename);

    if(is.good())
    {
        PNOTICE << "Loading Stream: " << szFilename << std::endl;

        scanStream(is);

        is.close();
    }
#else
    FILE *pInFile = fopen(szFilename, "r");

    if(pInFile != NULL)
    {
        PNOTICE << "Loading File : " << szFilename << std::endl;

        OSGScanParseSkel_in = pInFile;

        OSGScanParseSkel_parse(this);

        fclose(pInFile);
    }
#endif
}

Int32 ScanParseSkel::lex(void)
{
    Int32 returnValue = -1;

    if(_pLexer != NULL)
        returnValue = _pLexer->yylex();

    return returnValue;
}

const Char8 *ScanParseSkel::getText(void)
{
    const Char8 *returnValue = NULL;

    if(_pLexer != NULL)
        returnValue = _pLexer->YYText();

    return returnValue;
}

void ScanParseSkel::expectType(Int32 iNextType)
{
    if(_pLexer != NULL)
        _pLexer->expectType(iNextType);
}


void ScanParseSkel::handleError(const Char8 *szErrorText)
{
    if(_pLexer == NULL)
        return;

    FWARNING(("-----> %s in Line %d, read\n", 
              szErrorText, 
              _pLexer->lineno(), 
              _pLexer->YYText()));
}
 

/*-------------------------------------------------------------------------*/
/*                             Prototypes                                  */

bool ScanParseSkel::verifyHeader(const Char8 *szHeader)
{
    bool returnValue = true;

    if(szHeader == NULL)
    {
        SLOG << "Error Null Header String Read" << std::endl;
        return false;
    }

    if(_szReferenceHeader != NULL)
    {
        if(strncmp(szHeader,
                   _szReferenceHeader,
                   stringlen(_szReferenceHeader)) != 0)
        {
            SLOG << "Error : Header [" << szHeader << "] does not "
                    << "match reference [" << _szReferenceHeader << "]"
                    << std::endl;

            returnValue = false;
        }
    }
    else
    {
        SLOG << "Error Null Reference Header, Check disabled " << std::endl;
        return true;
    }

    return returnValue;
}

void ScanParseSkel::beginProto(const Char8 *)
{
}

void ScanParseSkel::endProto(void)
{
}

void ScanParseSkel::beginExternProto(const Char8 *)
{
}

void ScanParseSkel::endExternProtoInterface(void)
{
}

void ScanParseSkel::endExternProto(void)
{
}

void ScanParseSkel::beginScript(const Char8 *)
{
}

void ScanParseSkel::endScript(void)
{
}

void ScanParseSkel::beginEventInDecl (const Char8  *,
                                      const UInt32  ,
                                      const Char8  *)
{
}

void ScanParseSkel::beginEventOutDecl(const Char8  *,
                                      const UInt32  ,
                                      const Char8  *)
{
}

void ScanParseSkel::endEventDecl(void)
{
}

void ScanParseSkel::beginFieldDecl(const Char8  *,
                                   const UInt32  ,
                                   const Char8  *)
{
}

void ScanParseSkel::endFieldDecl(void)
{
}

void ScanParseSkel::beginExposedFieldDecl(const Char8  *,
                                          const UInt32  ,
                                          const Char8  *)
{
}

void ScanParseSkel::endExposedFieldDecl(void)
{
}


void ScanParseSkel::addExternEventInDecl (const Char8  *,
                                          const UInt32  ,
                                          const Char8  *)
{
}

void ScanParseSkel::addExternEventOutDecl(const Char8  *,
                                          const UInt32  ,
                                          const Char8  *)
{
}

void ScanParseSkel::addExternFieldDecl(const Char8  *,
                                       const UInt32  ,
                                       const Char8  *)
{
}

void ScanParseSkel::addExternExposedFieldDecl(const Char8  *,
                                              const UInt32  ,
                                              const Char8  *)
{
}

/*-------------------------------------------------------------------------*/
/*                               Fields                                    */

void ScanParseSkel::beginField(const Char8 *,
                               const UInt32)
{
}

void ScanParseSkel::endField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Nodes                                     */

void ScanParseSkel::beginNode(const Char8 *,
                              const Char8 *)
{
}

void ScanParseSkel::endNode(void)
{
}

void ScanParseSkel::nullNode(void)
{
}

void ScanParseSkel::use(const Char8 *szName)
{
    PINFO << "Use : " << szName << std::endl;
}

void ScanParseSkel::is(const Char8 *)
{
}

void ScanParseSkel::profileElement(const Char8 *szProfileName)
{
    fprintf(stderr, "PROFILE %s\n", szProfileName);
}

void ScanParseSkel::componentElement    (const Char8 *szComponentName)
{
    fprintf(stderr, "COMPONENT %s\n", szComponentName);
}

void ScanParseSkel::metaElement  (const Char8 *szMetaKey,
                                  const Char8 *szMetaValue)
{
    fprintf(stderr, "META %s %s\n", szMetaKey, szMetaValue);
}

void ScanParseSkel::importElement(const Char8 *szInlineName,
                                  const Char8 *szNodeName,
                                  const Char8 *szImportAs   )
{
    fprintf(stderr, "IMPORT %s.%s AS %s\n", 
                    szInlineName, szNodeName, szImportAs);
}

void ScanParseSkel::exportElement(const Char8 *szNodeName,
                                  const Char8 *szExportAs )
{
    fprintf(stderr, "EXPORT %s AS %s\n", szNodeName, szExportAs);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void ScanParseSkel::addFieldValue(const Char8 *)
{
}

void ScanParseSkel::addRoute(const Char8 *,
                             const Char8 *,
                             const Char8 *,
                             const Char8 *)
{
}

/*-------------------------------------------------------------------------*/
/*                           Type Information                              */

bool ScanParseSkel::getMapFieldTypes(void)
{
    return _bMapTypeIds;
}

Int32 ScanParseSkel::mapExtIntFieldType(const Char8*, const Int32 iFieldType)
{
    return iFieldType;
}

UInt32 ScanParseSkel::getFieldType(const Char8 *)
{
    return 0;
}

/*-------------------------------------------------------------------------*/
/*                               Set                                       */

void ScanParseSkel::reset(void)
{
}

void ScanParseSkel::setMapTypeIds(bool bVal)
{
    _bMapTypeIds = bVal;
}

void ScanParseSkel::setReferenceHeader(const Char8 *szReferenceHeader)
{
    stringDup(szReferenceHeader, _szReferenceHeader);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSCANPARSESKEL_HEADER_CVSID;
}
