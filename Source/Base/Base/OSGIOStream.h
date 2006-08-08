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

#ifndef _OSGIOSTREAM_H_
#define _OSGIOSTREAM_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include <iostream>
#include <iomanip>
#include <fstream>

#ifdef WIN32
#define OSG_STREAM_API __cdecl
#else
#define OSG_STREAM_API
#endif

OSG_BEGIN_NAMESPACE

class Fixed32;

struct SetIndent
{
    SetIndent(unsigned int uiIndent) : _uiIndent(uiIndent) {}

    unsigned int _uiIndent;
};

struct _IncIndent {};
struct _DecIndent {};
struct _BeginElem {};
struct _EndElem   {};
struct _EndElemNL {};

typedef void (*_IncIndent_)(_IncIndent);
typedef void (*_DecIndent_)(_DecIndent);
typedef void (*_BeginElem_)(_BeginElem);
typedef void (*_EndElem_  )(_EndElem  );
typedef void (*_EndElemNL_)(_EndElemNL);

OSG_BASE_DLLMAPPING void IncIndent(_IncIndent);
OSG_BASE_DLLMAPPING void DecIndent(_DecIndent);
OSG_BASE_DLLMAPPING void BeginElem(_BeginElem);
OSG_BASE_DLLMAPPING void EndElem  (_EndElem  );
OSG_BASE_DLLMAPPING void EndElemNL(_EndElemNL);

class OSG_BASE_DLLMAPPING OutStream
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    OutStream(std::ostream &baseStream);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OutStream(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

    OutStream &operator<<(               long        __n);
    OutStream &operator<<(      unsigned long        __n);

    OutStream &operator<<(               bool        __n);
    OutStream &operator<<(               char        __c);

    OutStream &operator<<(               short       __n);
    OutStream &operator<<(      unsigned short       __n);
        
    OutStream &operator<<(               int         __n);
    OutStream &operator<<(      unsigned int         __n);

    OutStream &operator<<(               long long   __n);
    OutStream &operator<<(      unsigned long long   __n);
    
    OutStream &operator<<(                    double __f);
    OutStream &operator<<(                    float  __f);
        
    OutStream &operator<<(               long double __f);

    OutStream &operator<<(const          Fixed32    &val);
    
    OutStream &operator<<(const void                *__p);

    OutStream &operator<<(const char                *__p);
    OutStream &operator<<(const std::string         &__s);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

#ifndef WIN32
    OutStream &operator<<(std::_Setbase      __f);
#else
    template <class Arg>
    OutStream &operator<<(std::_Smanip<Arg> &__f);
#endif

    OutStream &operator<<(std::ostream& (OSG_STREAM_API *__pf)(std::ostream&));

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

    virtual OutStream &operator<<( SetIndent);
    virtual OutStream &operator<<(_IncIndent_);
    virtual OutStream &operator<<(_DecIndent_);
    
    virtual OutStream &operator<<(_BeginElem_);
    virtual OutStream &operator<<(_EndElem_  );
    virtual OutStream &operator<<(_EndElemNL_);

    /*! \}                                                                 */
    /*==========================  PROTECTRED  =============================*/

  protected:

    std::ostream *_pBaseStream;

    /*==========================  PRIVATE  ================================*/

  private:
};


template<class ParentT>
class FileStreamMixin : public ParentT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParentT Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    FileStreamMixin(const char *szFileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FileStreamMixin(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

    void close(void);
    
    operator bool (void);

    /*! \}                                                                 */
    /*==========================  PROTECTRED  =============================*/

  protected:

    std::ofstream _oFileStream;

    /*==========================  PRIVATE  ================================*/

  private:
};


template<class ParentT>
class IndentOutStreamMixin : public ParentT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParentT Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    IndentOutStreamMixin(std::ostream &baseStream); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~IndentOutStreamMixin(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

    virtual IndentOutStreamMixin &operator<<(SetIndent setIndent);

    virtual IndentOutStreamMixin &operator<<(_IncIndent_);
    virtual IndentOutStreamMixin &operator<<(_DecIndent_);    
    virtual IndentOutStreamMixin &operator<<(_BeginElem_);
    virtual IndentOutStreamMixin &operator<<(_EndElem_  );
    virtual IndentOutStreamMixin &operator<<(_EndElemNL_);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   formated output                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PROTECTRED  =============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    std::string  _szIndent;
    unsigned int _uiIndentStep;

  private:
};



class OSG_BASE_DLLMAPPING InStream
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    InStream(std::istream &baseStream);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~InStream(void);

    /*! \}                                                                 */
    /*==========================  PROTECTRED  =============================*/

  protected:

    std::istream *_pBaseStream;

    /*==========================  PRIVATE  ================================*/

  private:
};


typedef FileStreamMixin                     <OutStream>   FileOutStream;
typedef FileStreamMixin<IndentOutStreamMixin<OutStream> > IndentFileOutStream;

OSG_END_NAMESPACE

#include "OSGIOStream.inl"

#endif // _OSG_IOSTREAM_H_
