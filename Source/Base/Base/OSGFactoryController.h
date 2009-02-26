/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2003 by the OpenSG Forum                    *
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

#ifndef _OSGFACTORYCONTROLLER_H_
#define _OSGFACTORYCONTROLLER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBaseTypes.h"
#include "OSGBaseInitFunctions.h"
#include "OSGSingletonHolder.h"

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class FactoryBase;
class TypeFactoryBase;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief Accessible via #FactoryController
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseTypeSystem
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING FactoryControllerBase
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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

    typedef std::map<std::string, FactoryBase *> FactoryMap;

    typedef FactoryMap::      iterator           FactoryMapIt;
    typedef FactoryMap::const_iterator           FactoryMapConstIt;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    template <class SingletonT>
    friend class SingletonHolder;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    friend OSG_BASE_DLLMAPPING  bool osgDoInit(Int32   argc, 
                                               Char8 **argv,
                                               UInt16  major, 
                                               UInt16  minor, 
                                               UInt16  release,
                                               bool    debug, 
                                               bool    dll, 
                                               bool    mt     );
    friend OSG_BASE_DLLMAPPING  bool osgExit  (void           );

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

    //! prohibit default function (move to 'public' if needed) 
    FactoryControllerBase(const FactoryControllerBase &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const FactoryControllerBase &source);

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

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    TypeFactoryBase *_pTypeFactory;
    FactoryMap       _mFactoryMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FactoryControllerBase(void);
    virtual ~FactoryControllerBase(void); 

    bool initialize(void);
    bool terminate (void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    bool         registerTypeFactory      (      TypeFactoryBase *pFactory);
    bool         registerFactory          (      FactoryBase     *pFactory);

    FactoryBase *findFactory              (const Char8           *szName  );

    bool         initializePendingElements(void                           );
};

#if defined(WIN32) 
#    if !defined(OSG_COMPILE_FACTORYCONTROLLER)
//OSG_BASE_EXPIMP_TMPL 
//template class OSG_BASE_DLLMAPPING SingletonHolder<FactoryControllerBase>;
#    endif
#endif

/*! \typedef OSG::SingletonHolder<OSG::FactoryControllerBase> FactoryController;
    \ingroup GrpBaseBaseTypeSystem
    \relatesalso OSG::FactoryControllerBase
 */

typedef OSG::SingletonHolder<OSG::FactoryControllerBase> FactoryController;

OSG_END_NAMESPACE

#endif /* _OSGFACTORYCONTROLLER_HPP_ */
