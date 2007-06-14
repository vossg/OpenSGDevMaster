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

#ifdef OSG_WITH_EXPAT

#include "expat.h"

#include <iostream>
#include <string>

#include "OSGXMLScanParseSkel.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"

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

#define OSGXMLBUFSIZE 4096

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void XMLScanParseSkel::handleChar(      void  *pUserData, 
                                  const Char8 *szData, 
                                        Int32  iLength)
{
    XMLScanParseSkel *pSkel = static_cast<XMLScanParseSkel *>(pUserData);

    if(iLength != 1 || szData[0] != '\n')
    {
        bool bFound = false;

        for(int i = 0; i < iLength; ++i)
        {
            if(isspace(szData[i]) == 0)
            {
                bFound = true;
                break;
            }
        }

        if(bFound == true)
        {
            pSkel->_szDataLine.append(szData, iLength);
        }
    }
    
    if(pSkel->_szDataLine.size() != 0    &&
       iLength                   == 1    &&
       szData[0]                 == '\n'   )
    {
        pSkel->_szDataLine.append(" ", 1);
    }
}

void XMLScanParseSkel::startElement(      void  * pUserData, 
                                    const Char8 * szName, 
                                    const Char8 **vAtts     )
{
    std::string szElementName(szName);

    XMLScanParseSkel *pSkel = static_cast<XMLScanParseSkel *>(pUserData);

    pSkel->startElement(szName);
    
    if(vAtts != NULL)
    {
        int j = 0;

        while(vAtts[j] != NULL)
        {
            pSkel->_szAttrName.assign (vAtts[j++]);
            pSkel->_szAttrValue.assign(vAtts[j++]);

            pSkel->handleAttribute(pSkel->_szAttrName, 
                                   pSkel->_szAttrValue);
        }
    }

    pSkel->_szDataLine.clear();
}

void XMLScanParseSkel::endElement(      void  *pUserData, 
                                  const Char8 *szName   )
{
    XMLScanParseSkel *pSkel = static_cast<XMLScanParseSkel *>(pUserData);

    if(pSkel->_szDataLine.size() != 0)
    {
        pSkel->_szDataLine += '\0';

        pSkel->handleCharBlock(pSkel->_szDataLine);

        pSkel->_szDataLine.clear();
    }

    std::string szElementName(szName);

    pSkel->endElement(szName);
}

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

void XMLScanParseSkel::startElement(const std::string &szName)
{
    if(_eErrorState != NoError)
        return;

    CallbackMapIt it = _mCallbackMap.find(szName);

    if(it != _mCallbackMap.end())
    {
        _sCallbackStack.push(it->second);
    }
    else
    {
        _sCallbackStack.push(&_oIgnoreCB);
    }

    _eErrorState = _sCallbackStack.top()->_startElementCB(this, szName);
}

void XMLScanParseSkel::handleAttribute(const std::string &szName,
                                       const std::string &szValue)
{
    if(_eErrorState != NoError)
        return;

    _eErrorState = _sCallbackStack.top()->_handleAttributeCB(this, 
                                                             szName, 
                                                             szValue);
}

void XMLScanParseSkel::endElement(const std::string &szName)
{
    if(_eErrorState != NoError)
        return;

    _eErrorState = _sCallbackStack.top()->_endElementCB(this, szName);

    _sCallbackStack.pop();
}

void XMLScanParseSkel::handleCharBlock(const std::string &szData)
{
    if(_eErrorState != NoError)
        return;

    _eErrorState = _sCallbackStack.top()->_handleDataBlockCB(this, szData);
}


XMLScanParseSkel::CBResult XMLScanParseSkel::ignoreStartElement(
    const std::string &szName)
{
    fprintf(stderr, "ignore %s\n", szName.c_str());

    return NoError;
}

XMLScanParseSkel::CBResult XMLScanParseSkel::ignoreHandleAttribute(
    const std::string &szName,
    const std::string &szValue)
{
    return NoError;
}

XMLScanParseSkel::CBResult XMLScanParseSkel::ignoreEndElement(
    const std::string &szName)
{
    fprintf(stderr, "ignore end %s\n", szName.c_str());
    
    return NoError;
}

XMLScanParseSkel::CBResult XMLScanParseSkel::ignoreHandleCharBlock(
    const std::string &szData)
{
    fprintf(stderr, " szLine : %d -%s-\n", szData.size(), szData.c_str());

    return NoError;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

XMLScanParseSkel::XMLScanParseSkel(void) :
    _uiLoadOptions (      0),
    _eErrorState   (NoError),
    _szDataLine    (       ),
    _szAttrName    (       ),
    _szAttrValue   (       ),
    _sOptionStack  (       ),
    _oIgnoreCB     (       ),
    _mCallbackMap  (       ),
    _sCallbackStack(       )
{
    _oIgnoreCB._startElementCB    = &XMLScanParseSkel::ignoreStartElement;
    _oIgnoreCB._handleAttributeCB = &XMLScanParseSkel::ignoreHandleAttribute;
    _oIgnoreCB._endElementCB      = &XMLScanParseSkel::ignoreEndElement;
    _oIgnoreCB._handleDataBlockCB = &XMLScanParseSkel::ignoreHandleCharBlock;
}

/** \brief Destructor
 */

XMLScanParseSkel::~XMLScanParseSkel(void)
{
    CallbackMapIt it = _mCallbackMap.begin();
    
    while(it != _mCallbackMap.end())
    {
        delete it->second;
        
        it->second = NULL;

        ++it;
    }
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

void XMLScanParseSkel::scanStream(std::istream &is)
{
    while(_sOptionStack.empty() == false)
    {
        _sOptionStack.pop();
    }

    while(_sCallbackStack.empty() == false)
    {
        _sCallbackStack.pop();
    }

    if(is.good())
    {
        Char8 szBuffer[OSGXMLBUFSIZE];

        XML_Parser parser = XML_ParserCreate(NULL);

        int done;

        XML_SetUserData            (parser, this                    );
        XML_SetElementHandler      (parser, startElement, endElement);
        XML_SetCharacterDataHandler(parser, handleChar              );

        _sCallbackStack.push(&_oIgnoreCB);

        do
        {
            is.read(szBuffer, OSGXMLBUFSIZE);

            std::streamsize len = is.gcount();

            done = len < OSGXMLBUFSIZE;

            if(XML_Parse(parser, szBuffer, len, done) == XML_STATUS_ERROR) 
            {
                fprintf(stderr,
                        "%s at line %d %d %d %d\n",
                        XML_ErrorString(XML_GetErrorCode(parser)),
                        XML_GetCurrentLineNumber(parser),
                        done,
                        OSGXMLBUFSIZE, len);
                break;
            }
        } while (!done && (_eErrorState == NoError));

        XML_ParserFree(parser);
    }
}

void XMLScanParseSkel::scanFile(const Char8 *szFilename)
{
    if(szFilename == NULL)
        return;

    std::ifstream is(szFilename);

    while(_sOptionStack.empty() == false)
    {
        _sOptionStack.pop();
    }

    if(is.good())
    {
        fprintf(stderr, "Loading Stream: %s\n", szFilename);

        scanStream(is);

        is.close();
    }
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

#endif
