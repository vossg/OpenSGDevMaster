#ifndef WIN32
#ifndef HASH_NAMESPACE
#define HASH_NAMESPACE __gnu_cxx
#endif

#include <ext/hash_fun.h>
#else
#ifndef HASH_NAMESPACE
#define HASH_NAMESPACE osg_hash
#endif

namespace osg_hash
{
template<class KeyT>
struct hash {};

template<>
struct hash<SHORT>
{
    size_t operator()(SHORT __x) const
    {
        return __x;
    }
};


template<>
struct hash<USHORT>
{
    size_t operator()(USHORT __x) const
    {
        return __x;
    }
};

}

#endif
