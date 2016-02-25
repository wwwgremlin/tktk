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

#include <tktk/ecs/System.hpp>

namespace tktk
{
namespace ecs
{

System::System() noexcept
{
}

System::~System() noexcept
{
    // Unregister and destroy processors
    auto it( mProcessors.begin() );
    while ( it != mProcessors.end() )
    {
        auto procPtr( it->second );
        delete procPtr;
        mProcessors.remove( it++ );
    }
}

void System::setup() noexcept
{
    auto it = mProcessors.begin();
    while ( it != mProcessors.end() )
    {
        it->second->setup( this );
        ++it;
    }
}


Entity::Handle System::addEntity() noexcept
{
    util::Id64 eId{ mEntityPool.createElement() };
    Entity::Handle handle( eId, this );
    return ( handle );
}

void System::removeEntity( Entity::Handle& eHandle ) noexcept
{
    //         util::Id64 cId = handle->getComponentId< T >();

    if ( !eHandle.isValid() )
    {
        return;
    }

    auto it( eHandle->map.begin() );
    while ( it != eHandle->map.end() )
    {
        Component::Handle ucHandle = it->second;
        if ( ucHandle.isValid() )
        {
            ucHandle.getProcessor()->destroyElement( ucHandle.getId() ); //destroy the Component
        }
        eHandle->map.remove( it++ ); //remove entry from map
    }

    mEntityPool.destroyElement( eHandle.getId() );
    eHandle.invalidate();
}

// for use from entity handle
void System::removeEntity( const util::Id64& eId  ) noexcept
{
    mEntityPool.destroyElement( eId );
}

bool System::isEntityValid( const Entity::Handle& handle ) const noexcept
{
    return ( mEntityPool.isIdValid( handle.getId() ) );
}

// for use from entity handle
bool System::isIdValid( const util::Id64& eId ) const noexcept
{
    return ( mEntityPool.isIdValid( eId ) );
}

Entity* System::getEntityPtr( const Entity::Handle& handle ) const noexcept
{
    return ( getEntityPtr( handle.getId() ) );
}

// for use from entity handle
Entity* System::getEntityPtr( const util::Id64& eId ) const noexcept
{
    if ( !mEntityPool.isIdValid( eId ) )
    {
        return ( nullptr );
    }
    return ( mEntityPool.getPtr( eId.index() ) );
}

} //namespace ecs
} //namespace tktk
