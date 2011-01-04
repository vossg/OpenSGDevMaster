/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifndef _OSGOSGWRITER_H_
#define _OSGOSGWRITER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include <iostream>

#include <string>
#include <map>
#include <vector>

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGFieldContainer.h"
#include "OSGSystemDef.h"

OSG_BEGIN_NAMESPACE

/*! \brief Brief OSGWriter
    \ingroup GrpSystemFileIOOSG
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING OSGWriter
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSGWriter(OutStream &stream, UInt32 indentStep = 4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~OSGWriter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    void write(            FieldContainer *  container );
    void write(std::vector<FieldContainer *> containers);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
      
    static const UInt32 DefaultSFWidth;
    static const UInt32 DefaultMFWidth; 

    /*! \nohierarchy
     */

    struct FCInfoHelper
    {
        bool        written;
        bool        hasName;
        std::string containerName;
        
        void        setName      (FieldContainer * const pFC);
		             
        FCInfoHelper(void);
    };
    
    typedef std::map<FieldContainer *, FCInfoHelper> FCInfoHelperMap;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FCInfoHelperMap                _visitedFCMap;
    OutStream                     &_outStream;

    void visitContainer(FieldContainer    * const pFC    );
    void visitField    (GetFieldHandlePtr         hF     );

    void writeContainer(FieldContainer    * const pFC    ,
                        bool                      bIndent);
    void writeField    (GetFieldHandlePtr         hF     );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGWriter(const OSGWriter &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OSGWriter &source);
};

OSG_END_NAMESPACE
    
#endif /* _OSGOSGWRITER_H_ */








