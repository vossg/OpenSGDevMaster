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

#ifndef _OSGXMLSCANPARSESKEL_H_
#define _OSGXMLSCANPARSESKEL_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"

#ifdef OSG_WITH_EXPAT

#include <vector>
#include <stack>
#include <map>

#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifndef DOXYGEN_SHOULD_SKIP_THIS

class ScanParseSkel;

typedef ScanParseSkel *ScanParseSkelP;

#endif

/*! \ingroup GrpSystemFileIOScanParse
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING XMLScanParseSkel
{
  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    enum CBResult
    {
        NoError = 0x0000,
        Error   = 0x0001
    };

    typedef boost::function<CBResult (      XMLScanParseSkel *,
                                      const std::string      &)> XMLCallback1;
    typedef boost::function<CBResult (      XMLScanParseSkel *,
                                      const std::string      &,
                                      const std::string      &)> XMLCallback2;

    struct XMLCallbacks
    {
        XMLCallback1 _startElementCB;
        XMLCallback2 _handleAttributeCB;
        XMLCallback1 _endElementCB;
        XMLCallback1 _handleDataBlockCB;
    };

    typedef CBResult (XMLScanParseSkel::*XMLCB1)(const std::string &);
    typedef CBResult (XMLScanParseSkel::*XMLCB2)(const std::string &,
                                                 const std::string &);

    typedef std::map<std::string, XMLCallbacks *>           CallbackMap;
    typedef std::map<std::string, XMLCallbacks *>::iterator CallbackMapIt;

    typedef std::stack<           XMLCallbacks *>           CallbackStack;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    XMLScanParseSkel(const XMLScanParseSkel &source);
    void operator =(const XMLScanParseSkel &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void handleChar  (      void  * pUserData, 
                             const Char8 * szData, 
                                   Int32   iLength);
    static void startElement(      void  * pUserData, 
                             const Char8 * szName, 
                             const Char8 **vAtts);

    static void endElement  (      void  * pUserData, 
                             const Char8 * szName);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt32               _uiLoadOptions;
    CBResult             _eErrorState;

    std::string          _szDataLine;
    std::string          _szAttrName;
    std::string          _szAttrValue;

    std::stack<UInt32>   _sOptionStack;

    XMLCallbacks         _oIgnoreCB;
    CallbackMap          _mCallbackMap;
    CallbackStack        _sCallbackStack;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void     startElement         (const std::string &szName );
    void     handleAttribute      (const std::string &szName,
                                   const std::string &szValue);
    void     endElement           (const std::string &szName );
    void     handleCharBlock      (const std::string &szData );


    CBResult ignoreStartElement   (const std::string &szName );
    CBResult ignoreHandleAttribute(const std::string &szName,
                                   const std::string &szValue);
    CBResult ignoreEndElement     (const std::string &szName );
    CBResult ignoreHandleCharBlock(const std::string &szData );

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    XMLScanParseSkel(void);
    virtual ~XMLScanParseSkel(void); 

    /*------------------------- your_category -------------------------------*/
    
    virtual void scanStream(      std::istream &sInputStream);

    virtual void scanFile  (const Char8        *szFilename  );

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};

OSG_END_NAMESPACE

#endif

#endif /* _OSGXMLSCANPARSESKEL_H_ */
