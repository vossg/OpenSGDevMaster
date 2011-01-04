

#ifndef _OSGCOLLADAFILETYPE_H_
#define _OSGCOLLADAFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOCollada
    \ingroup GrpLibOSGFileIO
 */

class OSG_FILEIO_DLLMAPPING ColladaFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef SceneFileType   Inherited;
    typedef ColladaFileType Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Name                                                         */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    virtual NodeTransitPtr
        read(      std::istream &is,
             const Char8        *fileNameOrExtension,
                   Resolver      resolver            = NULL) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

    ColladaFileType(const Char8  *suffixArray[],
                          UInt16  suffixByteCount,
                          bool    override,
                          UInt32  overridePriority,
                          UInt32  flags);

    virtual ~ColladaFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static const Char8           *_suffixA[];
    static       ColladaFileType  _the;
};

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAFILETYPE_H_
