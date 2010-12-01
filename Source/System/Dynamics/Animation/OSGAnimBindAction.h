/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2009 by the OpenSG Forum                   *
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

#ifndef _OSGANIMBINDACTION_H_
#define _OSGANIMBINDACTION_H_

#include "OSGConfig.h"
#include "OSGDynamicsDef.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

// forward decl
class AnimTemplate;
OSG_GEN_CONTAINERPTR(AnimTemplate);
class Animation;
OSG_GEN_CONTAINERPTR(Animation   );
class AnimDataSource;

/*---------------------------------------------------------------------------*\
 * AnimBindAction                                                            *
\*---------------------------------------------------------------------------*/

class OSG_DYNAMICS_DLLMAPPING AnimBindAction : public Action
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef Action         Inherited;
    typedef AnimBindAction Self;

    typedef std::map<std::string, AnimDataSource *> DataSourceMap;
    typedef DataSourceMap::iterator                 DataSourceMapIt;
    typedef DataSourceMap::const_iterator           DataSourceMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    virtual ~AnimBindAction(void);

    static AnimBindAction *create(void);

    static void registerEnterDefault(const FieldContainerType &type,
                                     const Action::Functor    &func );
    static void registerLeaveDefault(const FieldContainerType &type,
                                     const Action::Functor    &func );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    AnimTemplate *getTemplate(void                  ) const;
    void          setTemplate(AnimTemplate *animTmpl);

    Animation    *getAnim    (void                  ) const;
    void          setAnim    (Animation    *anim    );


    ResultE       bindFields (AttachmentContainer *attCon);

    void          fillSourceMap(NodeCore      *core,
                                DataSourceMap &dsMap) const;
    void          markUsed     (const std::string &targetId);



    void splitTargetId(const std::string &targetIdFull,
                             std::string &targetId,
                             std::string &subTargetId  );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    AnimBindAction(void                        );
    AnimBindAction(const AnimBindAction &source);

    virtual FunctorStore *getDefaultEnterFunctors(void);
    virtual FunctorStore *getDefaultLeaveFunctors(void);

    virtual ResultE       start(void       );
    virtual ResultE       stop (ResultE res);

    static  bool          terminateEnter         (void);
    static  bool          terminateLeave         (void);

    static FunctorStore *_defaultEnterFunctors;
    static FunctorStore *_defaultLeaveFunctors;


  private:
    AnimTemplateUnrecPtr _animTmpl;
    AnimationUnrecPtr    _anim;
    DataSourceMap        _dsMap;
};

OSG_DYNAMICS_DLLMAPPING Action::ResultE
bindEnterDefault(NodeCore *core, Action *action);

OSG_DYNAMICS_DLLMAPPING Action::ResultE
bindSkeletonEnter(NodeCore *core, Action *action);

OSG_END_NAMESPACE

#include "OSGAnimBindAction.inl"

#endif // _OSGANIMBINDACTION_H_
