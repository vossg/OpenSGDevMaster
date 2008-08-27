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

class OSG_BASE_DLLMAPPING GLDefineMapperBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    const std::string &toString  (const GLenum  eval) const;
          GLenum       fromString(const Char8  *sval) const;


    void addToEnumPair  (const std::string &sval, const      GLenum  eval);
    void addFromEnumPair(const      GLenum  eval, const std::string &sval);

    /*=========================  PROTECTED  ===============================*/

  protected:

#if 0
    struct GLEnum
    {
        GLEnum(const GLenum val);

        GLenum val(void) const;

        bool operator <(const GLEnum &rhs) const;

      protected:

        GLenum _val;
    };
#endif

    typedef std::map<std::string,      GLenum> MapToEnum;
    typedef std::map<     GLenum, std::string> MapFromEnum; 

    static const std::string szUnknown;

    MapToEnum   _mToEnum;
    MapFromEnum _mFromEnum;

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

#if defined(WIN32)
#    if !defined(OSG_COMPILE_GLDEFINEMAPPER)
//OSG_BASE_EXPIMP_TMPL 
//template class OSG_BASE_DLLMAPPING SingletonHolder<GLDefineMapperBase>;
#    endif
#endif

typedef SingletonHolder<GLDefineMapperBase> GLDefineMapper;

OSG_END_NAMESPACE

#include "OSGGLDefineMapper.inl"

#endif // _OSGGLDEFINEMAPPER_H_
