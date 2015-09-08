/**
    tktk

    tktk - Copyright (C) 2015 Stanislav Demyanovich <stan@angrybubo.com>

    This software is provided 'as-is', without any express or
    implied warranty. In no event will the authors be held
    liable for any damages arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute
    it freely, subject to the following restrictions:

    1.  The origin of this software must not be misrepresented;
        you must not claim that you wrote the original software.
        If you use this software in a product, an acknowledgment
        in the product documentation would be appreciated but
        is not required.

    2.  Altered source versions must be plainly marked as such,
        and must not be misrepresented as being the original software.

    3.  This notice may not be removed or altered from any
        source distribution.
*/

#ifndef TKTK_UTIL_TYPE_MAP_HPP
#define TKTK_UTIL_TYPE_MAP_HPP

#include <cstdint>
#include <atomic>
#include <unordered_map>

namespace tktk
{
namespace util
{

template < typename ValueType >
class TypeMap
{

private:
    using MapImpl = std::unordered_map< uint32_t, ValueType >;

public:
    using Iterator = typename MapImpl::iterator;
    using ConstIterator = typename MapImpl::const_iterator;
    using ValueType = typename ValueType;

inline ConstIterator begin() const noexcept
{
	return ( mMap.begin() );
}
inline ConstIterator end() const noexcept
{
	return ( mMap.end() );
}

inline Iterator begin() noexcept
{
	return ( mMap.begin() );
}
inline Iterator end() noexcept
{
	return ( mMap.end() );
}

template < typename TypeKey >
Iterator find() noexcept
{
	return ( mMap.find( getUniqueTypeId< TypeKey >() ) );
}

template < typename TypeKey >
ConstIterator find() const noexcept
{
	return ( mMap.find( getUniqueTypeId< TypeKey >() ) );
}

template < typename TypeKey >
void insert( VT&& value ) noexcept
{
	mMap[ getUniqueTypeId< TypeKey >() ] = std::forward< ValueType >( value );
}

private:

template< typename TypeKey >
inline static int getUniqueTypeId() noexcept
{
	static const int id = mNextTypeId++;
	return id;
}

private:
static std::atomic_int mNextTypeId;
MapImpl mMap;
};

template< typename ValueType >
std::atomic_int TypeMap< ValueType >::mNextTypeId{ 0 };


} //namespace util
} //namespace tktk

#endif /* end of include guard: TKTK_UTIL_TYPE_MAP_HPP */