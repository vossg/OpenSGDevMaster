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

#ifndef _OSGCSMLOGGER_H_
#define _OSGCSMLOGGER_H_

#include "OSGCSMLoggerBase.h"
#include "OSGFileContextHandlerMixin.h"

OSG_BEGIN_NAMESPACE

/*! \brief CSMLogger class. See \ref
           PageContribCSMLogger for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING CSMLogger : 
    public FileContextHandlerMixin<CSMLoggerBase, CSMLogger>
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FileContextHandlerMixin<CSMLoggerBase, CSMLogger> Inherited;
    typedef CSMLogger                                         Self;

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

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CSMLoggerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CSMLogger(void);
    CSMLogger(const CSMLogger &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CSMLogger(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void postOSGLoading(FileContextAttachment * const pContext);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void doLog(FieldContainer *pContainer, 
               BitVector       bvFlags   ,
               UInt32          origin    ,
               UInt32          uiRefFieldId,
               BitVector       uiRefFieldMask);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class  FieldContainer;
    friend class  CSMLoggerBase;
    friend class  FileContextHandlerMixin<CSMLoggerBase, CSMLogger>;
    friend struct OSGSceneFileType::PostLoadingDispatcher<CSMLogger>;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CSMLogger &source);
};

typedef CSMLogger *CSMLoggerP;

OSG_END_NAMESPACE

#include "OSGCSMLoggerBase.inl"
#include "OSGCSMLogger.inl"

#endif /* _OSGCSMLogger_H_ */
