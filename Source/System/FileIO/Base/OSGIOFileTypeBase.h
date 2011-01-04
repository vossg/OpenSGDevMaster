/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#ifndef _OSGIOFILETYPEBASE_H_
#define _OSGIOFILETYPEBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGLog.h"

#include <boost/lexical_cast.hpp>
#include <map>
#include <stack>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFileIOBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING IOFileTypeBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef IOFileTypeBase Self;
    
    enum
    {
        OSG_READ_SUPPORTED  = 1,  /**< The file type supports reading. */
        OSG_WRITE_SUPPORTED = 2   /**< The file type supports writing. */
    };
    
    /*! \nohierarchy
     */

    struct IOOption
    {
        IOOption(void                                             );
        IOOption(const IOOption    &other                         );
        IOOption(const std::string &name, const std::string &value);
    
        std::string optName;
        std::string optValue;
    };
  
    typedef std::map  <std::string, IOOption> OptionSet;
    typedef std::stack<OptionSet            > OptionStack;
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Flags                                                        */
    /*! \{                                                                 */
    
    UInt32 getFlags(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Option Handling Helpers                                      */
    /*! \{                                                                 */

    static bool hasOption  (const OptionSet   &optSet,
                            const std::string &name   );

    template <class ValueTypeT>
    static bool setOptionAs(      OptionSet   &optSet,
                            const std::string &name,
                            const ValueTypeT  &value  );
    static void setOption  (      OptionSet   &optSet,
                            const std::string &name,
                            const std::string &value  );

    static bool unsetOption(      OptionSet  &optSet,
                            const std::string &name   );

    template <class ValueTypeT>
    static bool getOptionAs(const OptionSet   &optSet,
                            const std::string &name,
                                  ValueTypeT  &value  );
    static bool getOption  (const OptionSet   &optSet,
                            const std::string &name,
                                  std::string &value  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Option Handling                                              */
    /*! \{                                                                 */
    
    void              pushOptions(bool               copyTop = true);
    void              popOptions (void                             );
    
    OptionSet const  &getOptions (void                             ) const;
    OptionSet        &editOptions(void                             );
    
    bool              hasOption  (const std::string &name          ) const;
                                  
    template <class ValueTypeT>
    bool              setOptionAs(const std::string &name,
                                  const ValueTypeT  &value         );
    void              setOption  (const std::string &name,
                                  const std::string &value         );
                                  
    bool              unsetOption(const std::string &name          );
                                  
    template <class ValueTypeT>
    bool              getOptionAs(const std::string &name,
                                        ValueTypeT  &value         ) const;
    bool              getOption  (const std::string &name,
                                        std::string &value         ) const;
        
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
  
    IOFileTypeBase(UInt32 const  flags);
    IOFileTypeBase(Self   const &other);
    
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    virtual ~IOFileTypeBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    UInt32       _flags;
    OptionStack  _optStack;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

#include "OSGIOFileTypeBase.inl"

#endif // _OSGIOFILETYPEBASE_H_
