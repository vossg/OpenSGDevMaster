/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGCOMPLEXSCENEMANAGER_H_
#define _OSGCOMPLEXSCENEMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/function.hpp>

#include "OSGComplexSceneManagerBase.h"
#include "OSGCSMDrawManager.h"
#include "OSGPathHandler.h"
#include "OSGSceneFileType.h"
#include "OSGSensorTask.h"
#include "OSGCSMKeySensorHelper.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComplexSceneManager class. See \ref
           PageContribCSMComplexSceneManager for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING ComplexSceneManager : 
    public ComplexSceneManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComplexSceneManagerBase Inherited;
    typedef ComplexSceneManager     Self;

    typedef boost::function<void (void)> MainLoopFuncF;

    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    static ComplexSceneManager *the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    static void startFrom(const std::string &szParamFilename);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool init     (int argc, char **argv);
    void terminate(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void setMainloop(MainLoopFuncF fMainloop);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void run  (void);
    void frame(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void key(Int32 x,
             Int32 y,
             Int32 iState,
             Char8 cKey  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual FieldContainer *findNamedComponent(const Char8 *szName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SceneFileType::Resolver             Resolver;

    // Variables should all be in ComplexSceneManagerBase.

    static Time                                 SystemTime;
    static ComplexSceneManagerUnrecPtr         _the;
    static PathHandler                         _oPathHandler;
    static std::vector<FieldContainerUnrecPtr> _vStaticGlobals;

           MainLoopFuncF                       _fMainloop;
           CSMKeySensorHelper                  _oKeyHelper;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComplexSceneManager(void);
    ComplexSceneManager(const ComplexSceneManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComplexSceneManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    FieldContainer *resolve(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate(const ComplexSceneManager *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void  addGlobals(const std::string &filename);
    void  addData   (const std::string &filename);

    Node *findNode  (const std::string &filename) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    bool init    (const std::vector<std::string> &vParams);
    void shutdown(      void                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void updateKeySensor(KeySensor *pSensor);
    void removeKeySensor(KeySensor *pSensor);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static FieldContainer           *resolveStatic(const Char8       *szName  );
    static FieldContainerTransitPtr  readOSGFile  (const std::string &filename,
                                                         Resolver     resolver);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void addStaticGlobals(const Char8                    *szFilename);

    static void scanParamFile   (const Char8                    *szFilename,
                                       std::vector<std::string> &vParams   );

    static void scanPreSystem(         std::vector<std::string> &vParams   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComplexSceneManagerBase;
    friend class KeySensor;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComplexSceneManager &source);
};

typedef ComplexSceneManager *ComplexSceneManagerP;

OSG_END_NAMESPACE

#include "OSGComplexSceneManagerBase.inl"
#include "OSGComplexSceneManager.inl"

#endif /* _OSGCOMPLEXSCENEMANAGER_H_ */
