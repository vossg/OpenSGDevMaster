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

OSG_BEGIN_NAMESPACE

inline
OutStream &OutStream::operator<<(long __n)
{
    (*_pBaseStream) << __n;
    
    return *this;
}

inline
OutStream &OutStream::operator<<(unsigned long __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(bool __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(char __c)
{
    (*_pBaseStream) << __c;

    return *this;
}

inline
OutStream &OutStream::operator<<(short __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(unsigned short __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(int __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(unsigned int __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(long long __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(unsigned long long __n)
{
    (*_pBaseStream) << __n;

    return *this;
}

inline
OutStream &OutStream::operator<<(double __f)
{
    (*_pBaseStream) << __f;

    return *this;
}

inline
OutStream &OutStream::operator<<(float __f)
{
    (*_pBaseStream) << __f;

    return *this;
}

inline
OutStream &OutStream::operator<<(long double __f)
{
    (*_pBaseStream) << __f;

    return *this;
}

inline
OutStream &OutStream::operator<<(const void *__p)
{
    (*_pBaseStream) << __p;

    return *this;
}

inline
OutStream &OutStream::operator<<(const char *__p)
{
    (*_pBaseStream) << __p;

    return *this;
}

inline
OutStream &OutStream::operator<<(const std::string &__s)
{
#ifndef WIN32
    (*_pBaseStream) << __s;
#else
    (*_pBaseStream) << __s.c_str();
#endif

    return *this;
}

#ifndef WIN32
# ifndef _LIBCPP_VERSION
inline
OutStream &OutStream::operator<<(std::_Setbase __f)
{
    (*_pBaseStream) << __f;
    
    return *this;
}
#else
inline
OutStream &OutStream::operator<<(std::__iom_t3 __f)
{
    (*_pBaseStream) << __f;

    return *this;
}
# endif
#else
template <class Arg> inline
OutStream &OutStream::operator<<(std::_Smanip<Arg> &__f)
{
    (*_pBaseStream) << __f;
    
    return *this;
}
#endif

inline
OutStream &OutStream::operator<<(
    std::ostream& (OSG_STREAM_API *__pf)(std::ostream &))
{
    __pf(*(this->_pBaseStream));

    return *this;
}

inline
OutStream &OutStream::operator<<(SetIndent)
{
    return *this;
}

inline
OutStream &OutStream::operator<<(_IncIndent_)
{
    return *this;
}

inline
OutStream &OutStream::operator<<(_DecIndent_)
{
    return *this;
}
    
inline
OutStream &OutStream::operator<<(_BeginElem_)
{
    return *this;
}

inline
OutStream &OutStream::operator<<(_EndElem_)
{
    return *this;
}

inline
OutStream &OutStream::operator<<(_EndElemNL_)
{
    return *this;
}



//---------------------------------------------------------------------------
//  FileStreamMixin
//---------------------------------------------------------------------------

template <class ParentT> inline
FileStreamMixin<ParentT>::FileStreamMixin(const char *szFileName) : 
    Inherited  (_oFileStream),
   _oFileStream( szFileName )
{
}

template <class ParentT> inline
FileStreamMixin<ParentT>::~FileStreamMixin(void) 
{
    if(_oFileStream.is_open() == true)
    {
        _oFileStream.close();
    }
}

template <class ParentT> inline
void FileStreamMixin<ParentT>::close(void) 
{
    _oFileStream.close(); 
}

template <class ParentT> inline
FileStreamMixin<ParentT>::operator bool (void) 
{
    return _oFileStream.good(); 
}

//---------------------------------------------------------------------------
//  CErrStreamMixin
//---------------------------------------------------------------------------

template<class ParentT> inline
CErrStreamMixin<ParentT>::CErrStreamMixin(void) : 
    Inherited(std::cerr)
{
}

template<class ParentT> inline
CErrStreamMixin<ParentT>::~CErrStreamMixin(void)
{
}

//---------------------------------------------------------------------------
//  IndentOutStreamMixin
//---------------------------------------------------------------------------

template <class ParentT> inline
IndentOutStreamMixin<ParentT>::IndentOutStreamMixin(std::ostream &baseStream) :
     Inherited   (baseStream),
    _szIndent    (          ),
    _uiIndentStep(         4)
{
}

template <class ParentT> inline
IndentOutStreamMixin<ParentT>::~IndentOutStreamMixin(void)
{
}

template <class ParentT> inline
IndentOutStreamMixin<ParentT> &IndentOutStreamMixin<ParentT>::operator<<(
    SetIndent setIndent)
{
    _uiIndentStep = setIndent._uiIndent;
    
    return *this;
}

template <class ParentT> inline
IndentOutStreamMixin<ParentT> &IndentOutStreamMixin<ParentT>::operator<<(
    _IncIndent_)
{
    _szIndent.append(_uiIndentStep, ' ');
    
    return *this;
}

template <class ParentT> inline
IndentOutStreamMixin<ParentT> &IndentOutStreamMixin<ParentT>::operator<<(
    _DecIndent_)
{
    std::string::iterator sIt = _szIndent.end();
    
    sIt -= _uiIndentStep;
    
    _szIndent.erase(sIt, _szIndent.end());
    
    return *this;
}

template <class ParentT> inline
IndentOutStreamMixin<ParentT> &IndentOutStreamMixin<ParentT>::operator<<(
    _BeginElem_)
{
    *(static_cast<Inherited *>(this)) << _szIndent;

    return *this;
}

template <class ParentT> inline
IndentOutStreamMixin<ParentT> &IndentOutStreamMixin<ParentT>::operator<<(
    _EndElem_)
{
    return *this;
}

template <class ParentT> inline
IndentOutStreamMixin<ParentT> &IndentOutStreamMixin<ParentT>::operator<<(
    _EndElemNL_)
{
    *(static_cast<Inherited *>(this)) << "\n";

    return *this;
}

OSG_END_NAMESPACE

