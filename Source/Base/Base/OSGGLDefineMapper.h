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

#ifndef _OSGGLDEFINEMAPPER_H_
#define _OSGGLDEFINEMAPPER_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGBaseDef.h"
#include "OSGSingletonHolder.h"
#include "OSGGLEXT.h"

#include "map"
#include "string"

OSG_BEGIN_NAMESPACE

template<typename ValueT>
class StringValueMapper
{
    /*==========================  PUBLIC  =================================*/

  public:

    const std::string &toString        (const ValueT       eval) const;
          ValueT       fromString      (const Char8       *sval) const;

          void         addToValuePair  (const std::string &sval, 
                                        const      ValueT   val);
          void         addFromValuePair(const      ValueT   val, 
                                        const std::string &sval);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map<std::string,      ValueT> MapToValue;
    typedef std::map<     ValueT, std::string> MapFromValue; 

    MapToValue   _mToValue;
    MapFromValue _mFromValue;

    static const std::string szUnknown;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StringValueMapper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StringValueMapper(void);

    /*==========================  PRIVATE  ================================*/

  private:
};

/*! \brief Accessible via #GLDefineMapper
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseGL
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING GLDefineMapperBase : 
    public StringValueMapper<GLenum>
{
    /*==========================  PUBLIC  =================================*/

  public:

    GLenum fromString     (const      Char8  *sval) const;

    void   addToEnumPair  (const std::string &sval, const      GLenum  eval);
    void   addFromEnumPair(const      GLenum  eval, const std::string &sval);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef StringValueMapper<GLenum> Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    GLDefineMapperBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GLDefineMapperBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    void initMaps(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    template <class SingletonT>
    friend class SingletonHolder;
};


/*! \typedef OSG::SingletonHolder<GLDefineMapperBase> GLDefineMapper;
    \ingroup GrpBaseBaseGL
    \relatesalso OSG::GLDefineMapperBase
 */

typedef SingletonHolder<GLDefineMapperBase> GLDefineMapper;

OSG_END_NAMESPACE

#include <OSGGLDefineMapper.inl>

#endif // _OSGGLDEFINEMAPPER_H_
