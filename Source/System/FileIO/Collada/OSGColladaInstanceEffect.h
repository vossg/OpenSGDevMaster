/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAINSTANCEEFFECT_H_
#define _OSGCOLLADAINSTANCEEFFECT_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstanceElement.h"
#include "OSGColladaEffect.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGMaterial.h"

#include <dom/domEffect.h>

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaInstanceEffect
    : public ColladaInstanceElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstanceElement  Inherited;
    typedef ColladaInstanceEffect   Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaInstanceEffect);

    // map <texture texcoord="Symbol"> to material texture slot
    typedef std::map<std::string, UInt32>     TCSymbolToSlotMap;
    typedef TCSymbolToSlotMap::iterator       TCSymbolToSlotMapIt;
    typedef TCSymbolToSlotMap::const_iterator TCSymbolToSlotMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Craete                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void      read   (void                  );
    virtual Material *process(ColladaElement *parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual ColladaEffect *getTargetElem   (void) const;
    virtual domEffect     *getTargetDOMElem(void) const;

    const TCSymbolToSlotMap &getTCMap (void) const;
    TCSymbolToSlotMap       &editTCMap(void);

    bool                     findTC   (const std::string &tcSymbol,
                                             UInt32      &texSlot  ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaInstanceEffect(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaInstanceEffect(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    TCSymbolToSlotMap _tcMap;
};

OSG_GEN_MEMOBJPTR(ColladaInstanceEffect);

OSG_END_NAMESPACE

// #include "OSGColladaInstanceEffect.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEEFFECT_H_
