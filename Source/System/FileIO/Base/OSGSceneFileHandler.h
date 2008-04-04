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

#ifndef _OSGSCENEFILEHANDLER_H_
#define _OSGSCENEFILEHANDLER_H_
#ifdef  __sgi
#pragma  once
#endif

#include <string>
#include <list>
#include <map>
#include <iostream>

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGSceneFileType.h"
#include "OSGPathHandler.h"
#include "OSGSingletonHolder.h"

OSG_BEGIN_NAMESPACE

class GraphOpSeq;

/*! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib
 *  \brief Brief OSGSceneFileHandler
 */

class OSG_SYSTEM_DLLMAPPING SceneFileHandlerBase
{
    /*==========================  PUBLIC  =================================*/

    typedef NodeTransitPtr (*FileIOReadCBF )(      SceneFileType *type,
                                                   std::istream  &is, 
                                             const Char8         *ext );

    typedef bool           (*FileIOWriteCBF)(      SceneFileType *type,
                                             const NodePtr       &node, 
                                                   std::ostream  &os,
                                             const Char8         *ext, 
                                                   bool           compress);

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual SceneFileType *getFileType(const Char8 *fileNameOrExtension);

    virtual int getSuffixList(std::list<const Char8*> &suffixList,
                              UInt32                   flags = (
                                  SceneFileType::OSG_READ_SUPPORTED |
                                  SceneFileType::OSG_WRITE_SUPPORTED));

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Progress                                   */
    /*! \{                                                                 */

    typedef void (*progresscbfp) (UInt32 p);

    void          setReadProgressCB (progresscbfp fp,
                                     bool         use_thread = true);
    progresscbfp  getReadProgressCB (void                          );

    void          updateReadProgress(void                          );
    void          updateReadProgress(UInt32       p                );

    void         setWriteProgressCB (progresscbfp fp               );
    progresscbfp getWriteProgressCB (void                          );

    void         updateWriteProgress(UInt32       p                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodeTransitPtr read(      std::istream &is, 
                                const Char8        *ext,
                                      GraphOpSeq   *graphOpSeq = 
                                                           _defaultgraphOpSeq);

    virtual NodeTransitPtr read(const  Char8       *fileName,
                                       GraphOpSeq  *graphOpSeq = 
                                                           _defaultgraphOpSeq);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read Callback                              */
    /*! \{                                                                 */

    void          setReadCB(FileIOReadCBF fp);
    FileIOReadCBF getReadCB(void            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(const NodePtr      &node, 
                             std::ostream &os, 
                       const Char8        *ext, 
                             bool          compress = false);
    virtual bool write(const NodePtr      &node, 
                       const Char8        *fileName, 
                             bool          compress = false);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Write Callback                                 */
    /*! \{                                                                 */

    void           setWriteCB(FileIOWriteCBF fp);
    FileIOWriteCBF getWriteCB(void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   PathHandler                                */
    /*! \{                                                                 */

    virtual PathHandler* getPathHandler(void                    );
    virtual void         setPathHandler(PathHandler *pathHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   DefaultGraphOp                             */
    /*! \{                                                                 */
    
    virtual GraphOpSeq *getDefaultGraphOp(void                  );
    virtual void        setDefaultGraphOp(GraphOpSeq *graphOpSeq);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Options                                    */
    /*! \{                                                                 */

    virtual       bool   setOptions(const Char8 *suffix, 
                                    const Char8 *options);
    virtual const Char8 *getOptions(const Char8 *suffix);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debug                                      */
    /*! \{                                                                 */

    void print (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::list<          SceneFileType *> FileTypeList;
    typedef std::map <IDString, FileTypeList  *> FileTypeMap;

    struct FindOverride
    {
        UInt32 uiRefPriority;

        bool operator() (SceneFileType *fileTypeP);
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FileTypeMap _suffixTypeMap;


    bool         addSceneFileType(SceneFileType &fileType);
    bool         subSceneFileType(SceneFileType &fileType);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SceneFileHandlerBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneFileHandlerBase(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class SceneFileType;

    template <class SingletonT>
    friend class SingletonHolder;

    std::string initPathHandler(const Char8        *fileName);
    
    struct progressS
    {
        UInt64 length;
        std::istream *is;
    };

           void initReadProgress     (std::istream &is);
           void terminateReadProgress(void            );
    static void readProgress         (void *data      );

           progresscbfp   _readProgressFP;
           progressS      _progressData;
           bool           _readReady;
           bool           _useProgressThread;

           progresscbfp   _writeProgressFP;

           PathHandler   *_pathHandler;
           PathHandler    _defaultPathHandler;
    static GraphOpSeq    *_defaultgraphOpSeq;
    
           FileIOReadCBF  _readFP;
           FileIOWriteCBF _writeFP;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SceneFileHandlerBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    SceneFileHandlerBase(const SceneFileHandlerBase &source);
};


#if defined(WIN32)
#    if !defined(OSG_COMPILE_SCENEFILEHANDLER)
OSG_SYSTEM_EXPIMP_TMPL 
template class OSG_SYSTEM_DLLMAPPING SingletonHolder<SceneFileHandlerBase>;
#    endif
#endif

typedef SingletonHolder<SceneFileHandlerBase> SceneFileHandler;

typedef SceneFileHandler* SceneFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
