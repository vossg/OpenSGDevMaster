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

#ifndef _OSGPATHHANDLER_H
#define _OSGPATHHANDLER_H
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include <cstdlib>
#include <fcntl.h>
#include <list>
#include <string>
#include <stack>

#ifndef WIN32
#include <unistd.h>
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseFileSystem
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING PathHandler
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    PathHandler(void);
    PathHandler(const Char8 *initialPathList);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PathHandler(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          std::string  findFile      (const Char8 *fileName        );

    const std::string &getBaseFile   (      void                   ) const;

          std::string  extractPath   (const Char8       *szFilename);

          std::string extractFilename(const std::string &szPath    ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void push_backPath       (const Char8 *pathList);
    void push_backCurrentDir (      void           );

    void push_backUnixPath   (const Char8 *pathList);
    void push_backWin32Path  (const Char8 *pathList);

    void push_frontPath      (const Char8 *pathList);
    void push_frontCurrentDir(      void           );

    void subPath             (const Char8 *pathList);
    void push_frontUnixPath  (const Char8 *pathList);
    void push_frontWin32Path (const Char8 *pathList);

    void subUnixPath         (const Char8 *pathList);
    void subWin32Path        (const Char8 *pathList);

    void clearPathList       (      void           );

    void setBaseFile         (const Char8 *fileName);
    void clearBaseFile       (      void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void pushState      (void);
    void popState       (void);

    void clearStateStack(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    enum PathType
    {
        Win32Path     = 0x0001,
        UnixPath      = 0x0002,

        AbsPath       = 0x0100,

        PlatformMask  = 0x00FF,
        TypeMask      = 0xFF00
    };
    
    typedef std::list<std::string>           PathList;
    typedef std::list<std::string>::iterator PathListIter;

    typedef std::pair<PathList, std::string> HandlerState;

    /*---------------------------------------------------------------------*/
    /*! \name                    Static Constants                          */
    /*! \{                                                                 */

    static const Char8       _dirSepWin32;
    static const Char8       _pathSepWin32;

    static const Char8       _dirSepUnix;
    static const Char8       _pathSepUnix;

    static const Char8       _dirSep;
    static const Char8       _pathSep;

    static const Char8       _dirSepOther;
    static const Char8       _pathSepOther;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    PathList                 _pathList;
    std::string              _baseFilePath;

    std::stack<HandlerState> _sState;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    void        validateList        (      PathList    &pathList  );
   
    PathType    analysePathList     (const Char8       *pathList  );
    PathType    analysePath         (const Char8       *path      );

    void        expandWin32Path     (      std::string &path      );
    void        expandUnixPath      (      std::string &path      );
    
    void        push_backPathList   (      PathList    &pathList  );
    void        push_frontPathList  (      PathList    &pathList  );

    void        subPathList         (const PathList    &pathList  );

    void        convertPath         (      std::string &path      );

    void        convertWin32PathList(      PathList    &result    );
    void        convertUnixPathList (      PathList    &result    );

    void        splitPathList       (const Char8       *pathList, 
                                     const Char8        pathSep,
                                           PathList    &result    );
    void        parsePathList       (const Char8       *pathList, 
                                           PathList    &result    );
    void        parseUnixPathList   (const Char8       *pathList, 
                                           PathList    &result    );
    void        parseWin32PathList  (const Char8       *pathList, 
                                           PathList    &result    );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    PathHandler(const PathHandler &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PathHandler &source);
};

OSG_END_NAMESPACE

#endif /* _OSGPATHHANDLER_H */
