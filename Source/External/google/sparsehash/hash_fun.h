
#ifndef _HASH_FUN_H_
#define _HASH_FUN_H_

#ifndef HASH_NAMESPACE
#define HASH_NAMESPACE osg_hash
#endif

namespace osg_hash
{
template <class KeyT>
struct hash {};


#ifndef WIN32

template <>
struct hash<OSG::Int16>
{
    size_t operator()(OSG::Int16 __x) const
    {
        return static_cast<size_t>(__x);
    }
};

template <>
struct hash<OSG::UInt16>
{
    size_t operator()(OSG::UInt16 __x) const
    {
        return static_cast<size_t>(__x);
    }
};

#else

template <>
struct hash<SHORT>
{
    size_t operator()(SHORT __x) const
    {
        return static_cast<size_t>(__x);
    }
};


template <>
struct hash<USHORT>
{
    size_t operator()(USHORT __x) const
    {
        return static_cast<size_t>(__x);
    }
};

#endif // WIN32

}

#endif // _HASH_FUN_H_
