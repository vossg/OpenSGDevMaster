/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2000-2002 by OpenSG Forum                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of th4e GNU Library General Public License as published    *
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
ExceptionBinaryDataHandler::ReadError::ReadError(const Char8 *reason) : 
    Exception() 
{
    _what += "BinaryDataHandler ReadError: ";
    _what += reason;
}

inline
ExceptionBinaryDataHandler::WriteError::WriteError(const Char8 *reason) : 
    Exception() 
{
    _what += "BinaryDataHandler WriteError: ";
    _what += reason;
}

inline 
void ExceptionBinaryDataHandler::putValue(const bool &value)
{
    // on Mac OS X a bool is four bytes long on all other
    // platfroms it is one byte long. So we write now always
    // one byte out.
    // put(&value, sizeof(bool));
    UInt8 temp = UInt8(value);
    put(&temp, sizeof(UInt8));
}

inline 
void ExceptionBinaryDataHandler::putValue(const UInt8 &value)
{
    put(&value, sizeof(UInt8));
}

inline 
void ExceptionBinaryDataHandler::putValue(const UInt16 &value)
{
    UInt16 z = osgHostToNet<UInt16>(value);

    put(&z, sizeof(UInt16));
}

inline 
void ExceptionBinaryDataHandler::putValue(const UInt32 &value)
{
    UInt32 z = osgHostToNet<UInt32>(value);

    put(&z, sizeof(UInt32));
}

inline 
void ExceptionBinaryDataHandler::putValue(const UInt64 &value)
{
    UInt64 z = osgHostToNet<UInt64>(value);

    put(&z, sizeof(UInt64));
}

inline 
void ExceptionBinaryDataHandler::putValue(const Int8 &value)
{
    put(&value, sizeof(Int8));
}

inline 
void ExceptionBinaryDataHandler::putValue(const Int16 &value)
{
    Int16 z = osgHostToNet<Int16>(value);

    put(&z, sizeof(Int16));
}

inline 
void ExceptionBinaryDataHandler::putValue(const Int32 &value)
{
    Int32 z = osgHostToNet<Int32>(value);

    put(&z, sizeof(Int32));
}

inline 
void ExceptionBinaryDataHandler::putValue(const Int64 &value)
{
    Int64 z = osgHostToNet<Int64>(value);

    put(&z, sizeof(Int64));

}

inline 
void ExceptionBinaryDataHandler::putValue(const Real16 &value)
{
    UInt16 v = osgHostToNet<UInt16>(value.getBits());

    put(&v, sizeof(Real16));
}

inline
void ExceptionBinaryDataHandler::putValue(const Fixed32 &value)
{
    Int32 v = osgHostToNet<Int32>(value.getValue());

    put(&v, sizeof(Int32));
}

inline 
void ExceptionBinaryDataHandler::putValue(const Real32 &value)
{
    UInt32 v = osgHostToNetFP(value);

    put(&v, sizeof(UInt32));
}

inline 
void ExceptionBinaryDataHandler::putValue(const Real64 &value)
{
    UInt64 v = osgHostToNetFP(value);

    put(&v, sizeof(UInt64));
}

inline 
void ExceptionBinaryDataHandler::putValue(const Real128 &value)
{
#if 0
    UInt64 v = osgHostToNetFP(value);

    put(&v, sizeof(UInt64));
#endif
    OSG_ASSERT(false); // have to implement this
}

inline 
void ExceptionBinaryDataHandler::putValue(const std::string &value)
{
    UInt32 len = UInt32(value.length()) + 1;

    putValue(len);

    if(len != 0)
    {
        put(value.c_str(), len);
    }
}

#ifdef OSG_GLENUM_NEQ_UINT32
inline 
void ExceptionBinaryDataHandler::putValue(const GLenum &value)
{
    UInt32 z = osgHostToNet(value);

    put(&z, sizeof(UInt32));
}
#endif

inline 
void ExceptionBinaryDataHandler::putValues(const bool *value, SizeT size)
{
    for(SizeT i = 0; i < size; ++i)
        putValue(value[i]);
}

inline 
void ExceptionBinaryDataHandler::putValues(const UInt8 *value, SizeT size)
{
    put(value, size * sizeof(UInt8));
}

inline 
void ExceptionBinaryDataHandler::putValues(const UInt16 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN

    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(UInt16));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const UInt32 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(UInt32));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const UInt64 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(UInt64));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Int8 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Int8));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Int16 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Int16));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Int32 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Int32));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Int64 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Int64));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Real16 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Real16));
    }
}

inline
void ExceptionBinaryDataHandler::putValues(const Fixed32 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Fixed32));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Real32 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Real32));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Real64 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Real64));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const Real128 *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(Real128));
    }
}

inline 
void ExceptionBinaryDataHandler::putValues(const std::string *value, 
                                                 SizeT        size )
{
    for(SizeT i = 0; i<size; ++i)
    {
        putValue(value[i]);
    }
}

#ifdef OSG_GLENUM_NEQ_UINT32
inline 
void ExceptionBinaryDataHandler::putValues(const GLenum *value, SizeT size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            putValue(value[i]);
        }
    }
    else
#endif
    {
        put(value, size * sizeof(UInt32));
    }
}
#endif

inline 
void ExceptionBinaryDataHandler::getValue(bool &value) OSG_THROW (ReadError)
{
    //get(&value, sizeof(bool));
    UInt8 temp;
    get(&temp, sizeof(UInt8));
    value = (temp != 0);
}

inline 
void ExceptionBinaryDataHandler::getValue(UInt8 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(UInt8));
}

inline 
void ExceptionBinaryDataHandler::getValue(UInt16 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(UInt16));

    value = osgNetToHost<UInt16>(value);
}

inline 
void ExceptionBinaryDataHandler::getValue(UInt32 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(UInt32));

    value = osgNetToHost<UInt32>(value);
}

inline 
void ExceptionBinaryDataHandler::getValue(UInt64 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(UInt64));

    value = osgNetToHost<UInt64>(value);
}

inline 
void ExceptionBinaryDataHandler::getValue(Int8 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(Int8));
}

inline 
void ExceptionBinaryDataHandler::getValue(Int16 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(Int16));

    value = osgNetToHost<Int16>(value);
}

inline 
void ExceptionBinaryDataHandler::getValue(Int32 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(Int32));

    value = osgNetToHost<Int32>(value);
}

inline 
void ExceptionBinaryDataHandler::getValue(Int64 &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(Int64));

    value = osgNetToHost<Int64>(value);
}

inline 
void ExceptionBinaryDataHandler::getValue(Real16 &value) OSG_THROW (ReadError)
{
    UInt16 v;

    get(&v, sizeof(Real16));

    v     = osgNetToHost<UInt16>(v);
    value.setBits(v);
}

inline
void ExceptionBinaryDataHandler::getValue(Fixed32 &value) OSG_THROW (ReadError)
{
    Int32 v;

    get(&v, sizeof(Int32));

    v = osgNetToHost<Int32>(v);

    value.setValue(v);
}

inline
void ExceptionBinaryDataHandler::getValue(Real32 &value) OSG_THROW (ReadError)
{
    UInt32 v;
    get(&v, sizeof(UInt32));

    value = osgNetToHostFP(v);
}

inline
void ExceptionBinaryDataHandler::getValue(Real64 &value) OSG_THROW (ReadError)
{
    UInt64 v;
    get(&v, sizeof(UInt64));

    value = osgNetToHostFP(v);
}

inline
void ExceptionBinaryDataHandler::getValue(Real128 &value) OSG_THROW (ReadError)
{
#if 0
    UInt64 v;
    get(&v, sizeof(UInt64));

    value = osgNetToHostFP(v);
#endif

    OSG_ASSERT(false); // have to implement this
}

inline 
void ExceptionBinaryDataHandler::getValue(
    std::string &value) OSG_THROW (ReadError)
{
    UInt32  len(0);
    Char8  *str = NULL;

    getValue(len);

    if(len != 0)
    {
        str = new Char8[len + 1];
        
        get(str, len);

        str[len] = 0;
        
        value = str;
        
        delete [] str;
    }
    else
    {
        value.erase();
    }
}

#ifdef OSG_GLENUM_NEQ_UINT32
inline
void ExceptionBinaryDataHandler::getValue(GLenum &value) OSG_THROW (ReadError)
{
    get(&value, sizeof(UInt32));

    value = osgNetToHost(value);
}
#endif

inline 
void ExceptionBinaryDataHandler::getValues(bool   *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    for(SizeT i = 0; i < size; ++i)
        getValue(value[i]);
}

inline 
void ExceptionBinaryDataHandler::getValues(UInt8  *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(UInt8));
}

inline 
void ExceptionBinaryDataHandler::getValues(UInt16 *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(UInt16));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            value[i] = osgNetToHost<UInt16>(value[i]);
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(UInt32 *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(UInt32));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            value[i] = osgNetToHost<UInt32>(value[i]);
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(UInt64 *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(UInt64));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            value[i] = osgNetToHost<UInt64>(value[i]);
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Int8   *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Int8));
}

inline 
void ExceptionBinaryDataHandler::getValues(Int16  *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Int16));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            value[i] = osgNetToHost<Int16>(value[i]);
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Int32  *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Int32));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            value[i] = osgNetToHost<Int32>(value[i]);
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Int64  *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Int64));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            value[i] = osgNetToHost<Int64>(value[i]);
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Real16 *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Real16));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        UInt16 *intValue = reinterpret_cast<UInt16 *>(value);

        for(SizeT i = 0; i < size; ++i)
        {
            value[i].setBits(osgNetToHost<UInt16>(intValue[i]));
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Fixed32 *value, 
                                           SizeT    size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Int32));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        Int32 *intValue = reinterpret_cast<Int32 *>(value);

        for(SizeT i = 0; i < size; ++i)
        {
            value[i].setValue(osgNetToHost<Int32>(intValue[i]));
        }
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Real32 *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Real32));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        osgSwapMem<sizeof(Real32)>(value, size);
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Real64 *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(Real64));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        osgSwapMem<sizeof(Real64)>(value, size);
    }
#endif
}

inline 
void ExceptionBinaryDataHandler::getValues(Real128 *value, 
                                           SizeT    size ) OSG_THROW (ReadError)
{
#if 0
    get(value, size * sizeof(Real128));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        osgSwapMem<sizeof(Real64)>(value, size);
    }
#endif
#endif

    OSG_ASSERT(false);
}

inline 
void ExceptionBinaryDataHandler::getValues(
    std::string *value, 
    SizeT        size ) OSG_THROW (ReadError)
{
    for(SizeT i = 0; i < size; ++i)
    {
        getValue(value[i]);
    }
}

#ifdef OSG_GLENUM_NEQ_UINT32
inline 
void ExceptionBinaryDataHandler::getValues(GLenum *value, 
                                           SizeT   size ) OSG_THROW (ReadError)
{
    get(value, size * sizeof(UInt32));

#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder == true)
    {
        for(SizeT i = 0; i < size; ++i)
        {
            value[i] = osgNetToHost(value[i]);
        }
    }
#endif
}
#endif

inline
ExceptionBinaryDataHandler::MemoryBlock::MemoryBlock(MemoryHandle m,
                                                     UInt32       s,
                                                     UInt32       ds) : 
    _mem     (m ),
    _size    (s ),
    _dataSize(ds)
{
}

inline
MemoryHandle ExceptionBinaryDataHandler::MemoryBlock::getMem(void)
{
    return _mem;
}

inline
void ExceptionBinaryDataHandler::MemoryBlock::setMem(MemoryHandle mem)
{
    _mem = mem;
}

inline
UInt32 ExceptionBinaryDataHandler::MemoryBlock::getSize(void)
{
    return _size;
}

inline
void ExceptionBinaryDataHandler::MemoryBlock::setSize(UInt32 size)
{
    _size = size;
}

inline
UInt32 ExceptionBinaryDataHandler::MemoryBlock::getDataSize(void)
{
    return _dataSize;
}

inline
void ExceptionBinaryDataHandler::MemoryBlock::setDataSize(UInt32 dataSize)
{
    _dataSize = dataSize;
}

inline
ExceptionBinaryDataHandler::BuffersT::iterator 
    ExceptionBinaryDataHandler::readBufBegin(void)
{
    return _readBuffers.begin();
}

inline
ExceptionBinaryDataHandler::BuffersT::iterator 
    ExceptionBinaryDataHandler::readBufEnd(void)
{
    return _readBuffers.end();
}

inline
ExceptionBinaryDataHandler::BuffersT::iterator 
    ExceptionBinaryDataHandler::writeBufBegin(void)
{
    return _writeBuffers.begin();
}

inline
ExceptionBinaryDataHandler::BuffersT::iterator 
    ExceptionBinaryDataHandler::writeBufEnd(void)
{
    return _writeBuffers.end();
}

OSG_END_NAMESPACE
