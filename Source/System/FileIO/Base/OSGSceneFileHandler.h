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

#include <boost/function.hpp>

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGSceneFileType.h"
#include "OSGPathHandler.h"
#include "OSGSingletonHolder.h"

OSG_BEGIN_NAMESPACE

class GraphOpSeq;

/*! \brief Brief OSGSceneFileHandler
    \ingroup GrpSystemFileIOBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING SceneFileHandlerBase
{
    /*==========================  PUBLIC  =================================*/

    typedef NodeTransitPtr (*FileIOReadCBF )(SceneFileType         *type,
                                             std::istream          &is, 
                                             Char8           const *ext );

    typedef bool           (*FileIOWriteCBF)(SceneFileType *        type,
                                             Node          * const  node, 
                                             std::ostream          &os,
                                             Char8           const *ext, 
                                             bool                   compress);


    typedef SceneFileType::Resolver Resolver;

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

    typedef void (*progresscbfp) (      UInt32  p    );
    typedef void (*filenamecbfp) (const Char8  *fname);

    void          setReadProgressCB (progresscbfp fp,
                                     bool         use_thread = true);
    progresscbfp  getReadProgressCB (void                          );

    void          setReadBeginCB    (filenamecbfp fp               );
    filenamecbfp  getReadBeginCB    (void                          );

    void          setReadEndCB      (filenamecbfp fp               );
    filenamecbfp  getReadEndCB      (void                          );

    void          updateReadProgress(void                          );
    void          updateReadProgress(UInt32       p                );

    void         setWriteProgressCB (progresscbfp fp               );
    progresscbfp getWriteProgressCB (void                          );

    void         setWriteBeginCB    (filenamecbfp fp               );
    filenamecbfp getWriteBeginCB    (void                          );

    void         setWriteEndCB      (filenamecbfp fp               );
    filenamecbfp getWriteEndCB      (void                          );

    void         updateWriteProgress(UInt32       p                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodeTransitPtr read(      std::istream &is, 
                                const Char8        *ext,
                                      GraphOpSeq   *graphOpSeq = 
                                                           _defaultgraphOpSeq,
                                       Resolver     resolver   = NULL);

    virtual NodeTransitPtr read(const  Char8       *fileName,
                                       GraphOpSeq  *graphOpSeq = 
                                                           _defaultgraphOpSeq,
                                       Resolver     resolver   = NULL);

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

    virtual bool write(Node         * const  node, 
                       std::ostream         &os, 
                       Char8          const *ext, 
                       bool                  compress = false);

    virtual bool write(Node         * const  node, 
                       Char8          const *fileName, 
                       bool                  compress = false);
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
    /*! \name                   PathHandler                                */
    /*! \{                                                                 */

    Resolver getGlobalResolver(void              ) const;
    void     setGlobalResolver(Resolver oResolver);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   DefaultGraphOp                             */
    /*! \{                                                                 */
    
    virtual GraphOpSeq *getDefaultGraphOp(void                  );
    virtual void        setDefaultGraphOp(GraphOpSeq *graphOpSeq);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Options                                                      */
    /*! \{                                                                 */

    template <class ValueTypeT>
    bool              setOptionAs(const std::string &suffix,
                                  const std::string &name,
                                  const ValueTypeT  &value  );
    bool              setOption  (const std::string &suffix,
                                  const std::string &name,
                                  const std::string &value  );
    
    bool              unsetOption(const std::string &suffix,
                                  const std::string &name   );
    
    template <class ValueTypeT>
    bool              getOptionAs(const std::string &suffix,
                                  const std::string &name,
                                        ValueTypeT  &value  );
    bool              getOption  (const std::string &suffix,
                                  const std::string &name,
                                        std::string &value  );

#if defined(OSG_1_COMPAT)
    void setOptions(const std::string &suffix,
                    const std::string &osg1Options);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debug                                      */
    /*! \{                                                                 */

    void print (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::list<             SceneFileType *> FileTypeList;
    typedef std::map <std::string, FileTypeList  *> FileTypeMap;

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    static bool terminateSceneFileTypes  (void);
           bool doTerminateSceneFileTypes(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    void triggerReadBegin (const Char8 *fname);
    void triggerReadEnd   (const Char8 *fname);

    void triggerWriteBegin(const Char8 *fname);
    void triggerWriteEnd  (const Char8 *fname);


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class SceneFileType;

    template <class SingletonT>
    friend class SingletonHolder;

    std::string initPathHandler(const Char8        *fileName);
    
    /*! \nohierarchy
     */

    struct progressS
    {
        UInt64 length;
        std::istream *is;
    };

           void initReadProgress     (std::istream &is);
           void terminateReadProgress(void            );
    static void readProgress         (void *data      );

           progresscbfp   _readProgressFP;
           filenamecbfp   _readBeginFP;
           filenamecbfp   _readEndFP;

           progressS      _progressData;
           bool           _readReady;
           bool           _useProgressThread;

           progresscbfp   _writeProgressFP;
           filenamecbfp   _writeBeginFP;
           filenamecbfp   _writeEndFP;

           PathHandler   *_pathHandler;
           PathHandler    _defaultPathHandler;
    static GraphOpSeq    *_defaultgraphOpSeq;
    
           FileIOReadCBF  _readFP;
           FileIOWriteCBF _writeFP;

           Resolver       _oGlobalResolver;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SceneFileHandlerBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    SceneFileHandlerBase(const SceneFileHandlerBase &source);
};

/*! \typedef OSG::SingletonHolder<OSG::SceneFileHandlerBase> SceneFileHandler;
    \ingroup GrpSystemFileIOBase
    \relatesalso OSG::SceneFileHandlerBase
 */

typedef SingletonHolder<SceneFileHandlerBase> SceneFileHandler;

typedef SceneFileHandler* SceneFileHandlerP;

OSG_END_NAMESPACE

#include "OSGSceneFileHandler.inl"

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
