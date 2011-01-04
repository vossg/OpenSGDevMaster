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

OSG_BEGIN_NAMESPACE


#if defined(__sgi)

const UInt32 OSGDIRFLAG   = IFDIR;
const UInt32 OSGREADFLAG  = IREAD;
const UInt32 OSGWRITEFLAG = IWRITE;

#elif defined(__linux) || defined(__APPLE__) || defined(__hpux) || defined(__sun)

const UInt32 OSGDIRFLAG   = S_IFDIR;
const UInt32 OSGREADFLAG  = S_IRUSR;
const UInt32 OSGWRITEFLAG = S_IWUSR;

#elif defined(WIN32)

const UInt32 OSGDIRFLAG       = FILE_ATTRIBUTE_DIRECTORY;
const UInt32 OSGREADONLYFLAG  = FILE_ATTRIBUTE_READONLY;

#else
#error "Could not find your system, check your system/compiler combination"
#endif

/*!  File Functions
     \ingroup GrpBaseBaseFileSystem
 */

namespace File
{
    /*! \name File Functions           
        @{                             
     */

    /*! \ingroup GrpBaseBaseFileSystem 
     */
    inline
    bool tstAttr(const OSG::TChar  *szFilename,
                       OSG::UInt32  uiAccessFlags)
    {
        bool  returnValue = false;

#ifndef WIN32
        Int32 rc          = 0;
        
        struct  stat statBuffer;
        
        if(szFilename != NULL)
        {
            rc =  stat(szFilename, &statBuffer);

            if(rc == 0 && ! (statBuffer.st_mode & OSGDIRFLAG))
            {
                if(uiAccessFlags & AccessFlags::IsReadable)
                {
                    if(statBuffer.st_mode & OSGREADFLAG)
                    {
                        returnValue = true;
                    }
                }
                
                if(uiAccessFlags & AccessFlags::IsWriteable)
                {
                    if(statBuffer.st_mode & OSGWRITEFLAG)
                    {
                        returnValue = true;
                    }
                }
            }
        }
#else
        DWORD rc          = 0;
               
        if(szFilename != NULL)
        {
            rc = GetFileAttributes(szFilename);
            
            if((rc != INVALID_FILE_ATTRIBUTES) && 
               ((rc & OSGDIRFLAG) == 0x0000))
            {
                if(uiAccessFlags & AccessFlags::IsReadable)
                {
                    returnValue = true;
                }
                
                if(uiAccessFlags & AccessFlags::IsWriteable)
                {
                    if(rc & OSGREADONLYFLAG)
                    {
                        returnValue = false;
                    }
                    else
                    {
                        returnValue = true;
                    }
                }
            }
        }
#endif
        
        return returnValue;
    }

    /*! @} */
}

/*!  Directory Functions
     \ingroup GrpBaseBaseFileSystem
 */

namespace Directory
{
    /*! \name Directory Functions      
        @{                             
     */

    /*! \fn bool Directory::tstAttr(const OSG::TChar  *szDirname,
                                          OSG::UInt32  uiAccessFlags)
        \ingroup GrpBaseBaseFileSystem
     */
    inline
    bool tstAttr(const OSG::TChar  *szDirname,
                       OSG::UInt32  uiAccessFlags)
    {
        bool  returnValue = false;
#ifndef WIN32
        Int32 rc          = 0;
        
        struct  stat statBuffer;
        
        if(szDirname != NULL)
        {
            rc = stat(szDirname, &statBuffer);
            
            if(rc == 0 && (statBuffer.st_mode & OSGDIRFLAG))
            {
                if(uiAccessFlags & AccessFlags::IsReadable)
                {
                    if(statBuffer.st_mode & OSGREADFLAG)
                    {
                        returnValue = true;
                    }
                    else
                    {
                        returnValue = false;
                    }
                }
                
                if(uiAccessFlags & AccessFlags::IsWriteable)
                {
                    if(statBuffer.st_mode & OSGWRITEFLAG)
                    {
                        returnValue = true;
                    }
                    else
                    {
                        returnValue = false;
                    }
                }
            }
        }
#else
        DWORD rc          = 0;
               
        if(szDirname != NULL)
        {
            rc = GetFileAttributes(szDirname);
            
            if((rc != INVALID_FILE_ATTRIBUTES) && (rc & OSGDIRFLAG))
            {
                if(uiAccessFlags & AccessFlags::IsReadable)
                {
                    returnValue = true;
                }
                
                if(uiAccessFlags & AccessFlags::IsWriteable)
                {
                    if(rc & OSGREADONLYFLAG)
                    {
                        returnValue = false;
                    }
                    else
                    {
                        returnValue = true;
                    }
                }
            }
        }
#endif
        return returnValue;
    }

#ifdef __sgi
#pragma set woff 1209
#endif

    /*! \ingroup GrpBaseBaseFileSystem
     */

    inline
    OSG::Char8 *getCurrent(void)
    {
        UInt32 uiCurrentNameSize = 256;
        
        Char8 *returnValue = new Char8[uiCurrentNameSize];
        Char8 *szTmpBuf;
        
        while(1)
        {
#ifndef WIN32
            szTmpBuf =  getcwd(returnValue, uiCurrentNameSize);
#else
            szTmpBuf = _getcwd(returnValue, uiCurrentNameSize);
#endif
            if(szTmpBuf != NULL)
                break;
            
            uiCurrentNameSize *= 2;
            delete [] returnValue;
            
            returnValue = new Char8[uiCurrentNameSize];
        }
        
        return returnValue;
    }
    
#ifdef __sgi
#pragma reset woff 1209
#endif
    
    /*! \ingroup GrpBaseBaseFileSystem
     */
    inline
    bool setCurrent(const OSG::Char8 *szDirname)
    {
        bool returnValue = false;
        
        if(szDirname != NULL)
        {
#ifndef WIN32
            if(chdir(szDirname) == 0)
                returnValue = true;
#else
            if(_chdir(szDirname) == 0)
                returnValue = true;
#endif
        }
        
        return returnValue;
    }

    /*! \ingroup GrpBaseBaseFileSystem
     */

    inline
    std::vector<TChar *> *getEntries(const TChar *szDirname,
                                     const TChar *szPattern)
    {
        std::vector<TChar *> *returnValue = NULL;
        
        if(szDirname != NULL)
        {
            if(tstAttr(szDirname, AccessFlags::IsReadable) == true)
            {
#ifndef WIN32
                DIR    *pDir        = opendir(szDirname);
                dirent *pDirEntry   = NULL;
                Char8  *szEntryName = NULL;
                
                if(pDir != NULL)
                {
                    returnValue = new std::vector<Char8 *>;

                    do
                    {
                        pDirEntry = readdir(pDir);
                        
                        if(pDirEntry != NULL)
                        {
                            osgStringDup(pDirEntry->d_name, szEntryName);
                            
                            if(szPattern != NULL)
                            {
                                if(fnmatch(szPattern, szEntryName, 0) == 0)
                                {
                                    returnValue->push_back(szEntryName);
                                }
                                else
                                {
                                    delete [] szEntryName;
                                }
                            }
                            else
                            {
                                returnValue->push_back(szEntryName);
                            }

                            szEntryName = NULL;
                        }
                    }
                    while(pDirEntry != NULL);
                    
                    closedir(pDir);
                }
#else
                tstring          szTmpDirname;
                
                bool             bVal;
                WIN32_FIND_DATA  pDirEntry;
                HANDLE           pDir;
                TChar           *szEntryName = NULL;
                
                if(szPattern == NULL)
                {
					szTmpDirname.assign(szDirname);
                    szTmpDirname += OSGT("\\*");
                }
                else
                {
					szTmpDirname.assign(szDirname);

					szTmpDirname += OSGT("\\");

					szTmpDirname += szPattern;
                }
                
                pDir = FindFirstFile(szTmpDirname.c_str(), &pDirEntry);
                
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 171)
#endif
                
                if(INVALID_HANDLE_VALUE != pDir)
                {
                    returnValue = new std::vector<TChar *>;
                    
                    do
                    {
                        osgStringDup(pDirEntry.cFileName, szEntryName);
                        
                        returnValue->push_back(szEntryName);
                        szEntryName = NULL;
                        
                        bVal = (FindNextFile(pDir, &pDirEntry) != FALSE);
                    }
                    while(bVal == true);
                    
                    FindClose(pDir);
                }
                
#ifdef OSG_WIN32_ICL
#pragma warning (error : 171)
#endif
                
#endif
            }
        }
        
        return returnValue;
    }

    /*! @} */
}

/*!  Directory Functions
     \ingroup GrpBaseBaseFileSystem
 */

namespace Path
{
    /*! \name Path Functions      
        @{                             
     */

    /*! \ingroup GrpBaseBaseFileSystem
     */
    inline
    static void fixWinNetworkPath(std::string &path)
    {
#ifdef WIN32
        // HACK but on windows network paths like \\Server\bla doesn't work, 
        // but
        // //Server/bla works ...

        if((path.length() >  2   ) &&
           (path[0]       == '\\') &&
           (path[1]       == '\\')  )
        {
            for(UInt32 i = 0; i < path.length(); ++i)
            {
                if(path[i] == '\\')
                {
                    path[i] = '/';
                }
            }
        }
#endif
    }
    /*! @} */
}

OSG_END_NAMESPACE
