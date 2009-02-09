/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGSHAREDOBJECTHANDLER_H_
#define _OSGSHAREDOBJECTHANDLER_H_
#ifdef __sgi
#pragma once
#endif


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBaseTypes.h"
#include "OSGMemoryObject.h"

#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

#ifndef DOXYGEN_SHOULD_SKIP_THIS

class SharedObjectHandler;
class SharedObject;

#endif

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

#ifdef WIN32
typedef HMODULE  SharedHandle;
#else
typedef void    *SharedHandle;
#endif

typedef void *AnonSymbolHandle;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

typedef OSG::SharedObject *SharedObjectP;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseTypeSystem
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING SharedObject : public MemoryObject
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum SharedObjectType
    {
        Invalid       = 0x0000,
        Application   = 0x0001,
        SharedLibrary = 0x0002
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef MemoryObject Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class SharedObjectHandler;

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
    SharedObject(const SharedObject &source);
	// prohibit default functions (move to 'public' if you need one)
    void operator =(const SharedObject &source);

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

    static TChar _szApplicationObjectName[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    tstring          _szName;
    SharedHandle     _pHandle;

    SharedObjectType _type;    

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    SharedObject(const TChar *szName);

    virtual ~SharedObject(void); 

    bool close(void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

          bool             open     (      void               );
          AnonSymbolHandle getSymbol(const TChar *szSymbolName);

          bool             isOpen   (      void               );

          bool             reOpen   (      void               );

    const tstring         &getName  (      void               );
    const TChar           *getCName (      void               );

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    void dump(void);

    /*------------------------- comparison ----------------------------------*/
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


typedef OSG::SharedObjectHandler *SharedObjectHandlerP;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseTypeSystem
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING SharedObjectHandler
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef std::map<tstring, SharedObjectP>     SharedObjectMap;

    typedef SharedObjectMap::iterator            SharedObjectMapIt;

    typedef SharedObjectMap::const_iterator      SharedObjectMapConstIt;


    typedef std::vector<tstring>                 NameStore;
    typedef std::vector<tstring>::iterator       NameStoreIt;
    typedef std::vector<tstring>::const_iterator NameStoreConstIt;

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

    friend  OSG_BASE_DLLMAPPING bool osgDoInit(Int32   argc, 
                                               Char8 **argv,
                                               UInt16  major, 
                                               UInt16  minor, 
                                               UInt16  release,
                                               bool    debug, 
                                               bool    dll, 
                                               bool    mt     );
    friend  OSG_BASE_DLLMAPPING bool osgExit  (void           );

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
    SharedObjectHandler(const SharedObjectHandler &source);
	// prohibit default functions (move to 'public' if you need one)
    void operator =(const SharedObjectHandler &source);

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

    static SharedObjectHandlerP _the;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    SharedObjectMap _mSharedObjects;
    
    NameStore       _vLoadedNames;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    SharedObjectHandler(void);

    virtual ~SharedObjectHandler(void); 

    bool initialize(void);
    void terminate (void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static SharedObjectHandlerP the(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    SharedObjectP getSharedObject   (const TChar         *szName );
    SharedObjectP getOSGSharedObject(const TChar         *szName );
    SharedObjectP findSharedObject  (const TChar         *szName ) const;

    void          removeSharedObject(const TChar         *szName );
    void          removeSharedObject(      SharedObjectP  pObject);

    /*------------------------- your_category -------------------------------*/

    void registerLoadedObject(const TChar *szName);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/
    
    /*------------------------- comparison ----------------------------------*/

    void dump(void);

    /*------------------------- comparison ----------------------------------*/
};

OSG_END_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif

#endif /* _OSGSHAREDOBJECTHANDLER_H_ */
